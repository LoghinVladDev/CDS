//
// Created by loghin on 31.03.2021.
//

#ifndef CDS_VIEW_HPP
#define CDS_VIEW_HPP

#include <CDS/Object>
#include <CDS/Collection>
#include <Concepts.hpp>


#if defined(__cpp_concepts)
#define _ITERABLE_CONSTRAINT requires Iterable < Type >
#define _PRINTABLE_CONSTRAINT requires HasToString < Type >
#else
#define _ITERABLE_CONSTRAINT
#define _PRINTABLE_CONSTRAINT
#endif

#include <ostream>

#include <functional>
#include <CDS/LinkedList>
#include <CDS/Reference>
#include <CDS/Optional>

#include <iostream>


template < typename T >
//#if defined(__cpp_concepts)
//    requires Iterable < T >
//#endif
class View : public Object {
public:
    using Type                  = T;
    using IterableValue         = decltype ( ((typename Type::Iterator *)nullptr)->value() );
    using Predicate             = std::function < bool (IterableValue) >;
    using Mapper                = std::function < std::remove_reference_t<IterableValue> ( IterableValue ) >;

    using ViewValue             = typename std::remove_reference<IterableValue>::type;

private:
    Type * _pObject {nullptr};

    LinkedList < Predicate * > _predicates;
    LinkedList < Mapper * >    _mappers;

    auto validate ( IterableValue value ) const noexcept -> bool {
        return this->_predicates.all( [& value]( auto * pPred ) { return (*pPred)(value); } );
    }

public:

    class Queryable : public Object {
    private:
        Optional < ViewValue > value;

    public:
        Queryable() noexcept = default;
        Queryable( Queryable const & ) noexcept = default;
        Queryable( Queryable && ) noexcept = default;

        explicit Queryable( ViewValue v ) noexcept : value({v}) {}

        auto orElse ( ViewValue replacement ) noexcept -> ViewValue {
            return this->value.hasValue() ? this->value.value() : replacement;
        }

        template < typename Action >
        auto ifPresent ( Action const & action ) noexcept -> void {
            if ( this->value.hasValue() ) action ( this->value.value() );
        }

        [[nodiscard]] auto toString() const noexcept -> String override {
            return this->value.toString();
        }
    };

    class Iterator {
    private:
        View                    * _pView;
        typename Type::Iterator   _it;

    public:
        Iterator () noexcept _ITERABLE_CONSTRAINT = delete;
        Iterator ( Iterator const & it ) noexcept _ITERABLE_CONSTRAINT = default;
        Iterator ( Iterator && it ) noexcept _ITERABLE_CONSTRAINT = default;

        Iterator (View * pView, typename Type::Iterator const & it) noexcept _ITERABLE_CONSTRAINT :
                _pView(pView),
                _it(it) {
            while ( ! this->_pView->validate(this->_it.value()) && this->_it != this->_pView->_pObject->end() )
                this->_it.next();
        }

        ~Iterator () noexcept = default;

        [[nodiscard]] inline auto value () const noexcept -> typename std::remove_reference<IterableValue>::type _ITERABLE_CONSTRAINT {
            auto v = this->_it.value();
            this->_pView->_mappers.forEach([& v](auto * pMapper){ v = (*pMapper)(v); });
            return v;
        }

        [[nodiscard]] inline auto next () noexcept -> Iterator & _ITERABLE_CONSTRAINT {
            this->_it.next();
            while ( ! this->_pView->validate(this->_it.value()) && this->_it != this->_pView->_pObject->end() )
                this->_it.next();
            return * this;
        }

        inline auto operator == ( Iterator const & obj ) const noexcept -> bool _ITERABLE_CONSTRAINT {
            return this->_it == obj._it && this->_pView->_pObject == obj._pView->_pObject;
        }

        inline auto operator != ( Iterator const & obj ) const noexcept -> bool _ITERABLE_CONSTRAINT {
            return this->_it != obj._it || this->_pView->_pObject != obj._pView->_pObject;
        }

        inline auto operator ++ () noexcept -> Iterator & _ITERABLE_CONSTRAINT {
            return this->next();
        }

        inline auto operator ++ (int) noexcept -> Iterator _ITERABLE_CONSTRAINT {
            auto copy = * this;
            this->next();
            return copy;
        }

        inline auto operator * () const noexcept -> typename std::remove_reference<IterableValue>::type _ITERABLE_CONSTRAINT {
            return this->value();
        }
    };

    View () noexcept _ITERABLE_CONSTRAINT = delete;
    View ( View const & obj ) noexcept _ITERABLE_CONSTRAINT : _pObject(obj._pObject) {
        obj._predicates.forEach([this](auto * p){this->_predicates.pushBack(new Predicate(*p));});
        obj._mappers.forEach([this](auto * m){this->_mappers.pushBack(new Mapper(*m));});
    }

    View ( View && obj ) noexcept _ITERABLE_CONSTRAINT: _pObject(std::exchange(obj._pObject, nullptr)) {
        while ( ! obj._predicates.empty() ) this->_predicates.pushBack(obj._predicates.popFront());
        while ( ! obj._mappers.empty() ) this->_mappers.pushBack(obj._mappers.popFront());
    }

    View & operator = ( View const & obj ) noexcept _ITERABLE_CONSTRAINT {
        if ( this == & obj ) return * this;
        this->_pObject = obj._pObject;
        obj._predicates.forEach([this](auto * p){this->_predicates.pushBack(new Predicate(*p));});
        obj._mappers.forEach([this](auto * m){this->_mappers.pushBack(new Mapper(*m));});
        return * this;
    }

    View & operator = ( View && obj ) noexcept _ITERABLE_CONSTRAINT {
        if ( this == & obj ) return * this;
        this->_pObject = obj._pObject;
        while ( ! obj._predicates.empty() ) this->_predicates.pushBack(obj._predicates.popFront());
        while ( ! obj._mappers.empty() ) this->_mappers.pushBack(obj._mappers.popFront());
        return * this;
    }

    explicit View ( Type & obj ) noexcept _ITERABLE_CONSTRAINT : _pObject( & obj ) {}
    explicit View ( Type * obj ) noexcept _ITERABLE_CONSTRAINT : _pObject( obj ) {}
    explicit View ( Type && obj ) noexcept _ITERABLE_CONSTRAINT = delete;

    ~View() noexcept override {
        for ( auto * e : this->_predicates )
            delete e;
        for ( auto * m : this->_mappers )
            delete m;
    };

    inline auto begin () noexcept -> Iterator _ITERABLE_CONSTRAINT { return Iterator(this, this->_pObject->begin()); }
    inline auto end () noexcept -> Iterator _ITERABLE_CONSTRAINT { return Iterator(this, this->_pObject->end()); }

    template < typename Function >
    inline auto filter ( Function const & predicate ) && noexcept -> View _ITERABLE_CONSTRAINT {
        this->_predicates.pushBack(new Predicate (predicate));
        return std::move(* this);
    }

    template < typename Action >
    inline auto forEach ( Action const & action ) noexcept -> void _ITERABLE_CONSTRAINT { for ( auto e : * this ) action (e); }

    template < typename Modifier >
    inline auto map ( Modifier const & mapper ) && noexcept -> View _ITERABLE_CONSTRAINT {
        this->_mappers.pushBack(new Mapper(mapper));
        return std::move(* this);
    }

    auto findFirst () noexcept -> Queryable _ITERABLE_CONSTRAINT {
        for ( auto e : * this )
            return Queryable{e};
        return Queryable();
    }

    [[nodiscard]] auto toString() const noexcept -> String override {
        return String("View of ").append((String)*this->_pObject);
    }
};

#undef _ITERABLE_CONSTRAINT

#endif //CDS_VIEW_HPP
