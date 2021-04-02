//
// Created by loghin on 31.03.2021.
//

#ifndef CDS_VIEW_HPP
#define CDS_VIEW_HPP

#include <CDS/Object>
#include <CDS/Collection>
#include <Concepts.hpp>


#if defined(__cpp_concepts)
#define _ITERABLE_CONSTRAINT requires Iterable < Type > || ConstIterable < Type >
#define _PRINTABLE_CONSTRAINT requires HasToString < Type >
#define _AVERAGE_ITERABLE_CONSTRAINT requires Iterable < Type > && Integral < ViewValue >
#else
#define _ITERABLE_CONSTRAINT
#define _PRINTABLE_CONSTRAINT
#endif

#include <ostream>

#include <functional>
#include <CDS/LinkedList>
#include <CDS/Reference>
#include <CDS/Optional>
#include <CDS/Pair>

#include <iostream>
//#include <unordered_set>
#include <CDS/UnorderedSet>


template < typename T >
class View : public Object {
public:
    using Type                  = T;
    using IterableValue         = decltype ( ((typename Type::Iterator *)nullptr)->value() );
    using StoredPredicate       = std::function < bool (IterableValue) >;
    using StoredMapper          = std::function < std::remove_reference_t<IterableValue> (IterableValue ) >;
    using StoredSorter          = std::function < bool (IterableValue, IterableValue) >;

    using ViewValue             = typename std::remove_reference<IterableValue>::type;

private:
    class Sortable {
    private:
        class Node {
        private:
            Node        * pNext {nullptr};
            ViewValue     _value;
        public:
            constexpr explicit Node (ViewValue v) noexcept : _value(v), pNext(nullptr) { }
            constexpr Node (Node * p, ViewValue v) noexcept : _value(v), pNext(p) { }

            constexpr auto next () noexcept -> Node * & { return this->pNext; }
            constexpr auto value () noexcept -> ViewValue & { return this->_value; }
        };

        Node         * front  {nullptr};
        View         * pView  {nullptr};

    public:
        Sortable() noexcept = delete;
        Sortable(Type const & obj, View * pView) noexcept :
                pView(pView) {
            for ( auto v : obj )
                this->push(v);
        }

        Sortable(Sortable const & obj) noexcept :
                pView(obj.pView) {
            for ( auto & v : obj )
                this->push(v);
        }

        Sortable(Sortable && other) noexcept :
                pView(std::exchange(other.pView, nullptr)) {
            while ( other.front != nullptr ) {
                auto node = other.front;
                other.front = other.front->next();

                this->push(node->value());
                delete node;
            }
        }

        ~Sortable() noexcept {
            while ( this->front != nullptr ) {
                auto node = this->front;
                this->front = this->front->next();
                delete node;
            }
        }

        auto push ( ViewValue & v ) noexcept -> void;

        class Iterator {
        private:
            Sortable::Node * _pNode;

        public:
            constexpr Iterator () noexcept = default;
            constexpr Iterator (Iterator const &) noexcept = default;
            constexpr Iterator (Iterator &&) noexcept = default;
            constexpr explicit Iterator (Sortable::Node * pNode) noexcept :
                    _pNode(pNode) {

            }

            constexpr ~Iterator () noexcept = default;

            constexpr auto next () noexcept -> Iterator & { this->_pNode = this->_pNode->next(); return * this; }
            constexpr auto value () const noexcept -> ViewValue & { return this->_pNode->value(); }

            constexpr auto operator == (Iterator const & o) const noexcept -> bool { return this->_pNode == o._pNode; }
            constexpr auto operator != (Iterator const & o) const noexcept -> bool { return this->_pNode != o._pNode; }

            constexpr auto operator * () const noexcept -> ViewValue & { return this->value(); }

            constexpr auto operator ++ () noexcept -> Iterator & { return this->next(); }
            constexpr auto operator ++ (int) noexcept -> Iterator { auto copy = * this; this->next(); return copy; }
        };

        constexpr auto begin () noexcept -> Iterator { return Iterator (this->front); }
        constexpr auto end () noexcept -> Iterator { return Iterator (nullptr); }
    };

    Type                     const * _pObject {nullptr};

    LinkedList < Pair < StoredPredicate *, Index > >                _predicates;
    LinkedList < Pair < StoredMapper *, Index > >                   _mappers;
//    LinkedList < Pair < std::unordered_set < ViewValue >, Index > > mutable _distinctInstances;
    LinkedList < Pair < UnorderedSet < ViewValue >, Index > > mutable _distinctInstances;

    bool                             _sorted {false};
    Sortable                       * _pSortable {nullptr};
    StoredSorter                   * _sorter {nullptr};

    Index                            _instanceHolderIndex {-1};

    bool                             _owner {false};

    auto requestSorted () noexcept -> void _ITERABLE_CONSTRAINT {
        this->_pSortable = new Sortable(*this->_pObject, this);
    }

    auto validate ( ViewValue value ) const noexcept -> bool _ITERABLE_CONSTRAINT {
        if ( ! this->_predicates.all( [& value, this]( auto & pPair ) {
//            return (*pPred)(value);
            auto tempVal = value;
            auto predIndex = pPair.getSecond();
            this->_mappers.forEach([& tempVal, &predIndex](auto & mPair){
                if ( mPair.getSecond() < predIndex )
                    tempVal = (*mPair.getFirst())(tempVal);
            });

            return (*pPair.getFirst())(tempVal);
        } ) )
            return false;
        for ( auto & distinctInstance : this->_distinctInstances ) {
            auto tempVal = value;
            auto distIndex = distinctInstance.getSecond();
            this->_mappers.forEach([& tempVal, &distIndex](auto & mPair){
                if ( mPair.getSecond() < distIndex )
                    tempVal = (*mPair.getFirst())(tempVal);
            });
            if ( distinctInstance.getFirst().contains(tempVal) )
                return false;

            distinctInstance.getFirst().insert(tempVal);
        }

        return true;
    }

public:

    class Queryable : public Object {
    private:
        Optional < ViewValue > value;

    public:
        Queryable() noexcept = default;
        Queryable( Queryable const & ) noexcept = default;
        Queryable( Queryable && ) noexcept = default;

        explicit Queryable( ViewValue v ) noexcept _ITERABLE_CONSTRAINT : value({v}) {}

        auto orElse ( ViewValue replacement ) noexcept -> ViewValue _ITERABLE_CONSTRAINT {
            return this->value.hasValue() ? this->value.value() : replacement;
        }

        template < typename Action >
        auto ifPresent ( Action const & action ) noexcept -> void _ITERABLE_CONSTRAINT {
            if ( this->value.hasValue() ) action ( this->value.value() );
        }

        [[nodiscard]] auto toString() const noexcept -> String override {
            return this->value.toString();
        }
    };

    class Iterator {
    private:
        View                    * _pView;

        typename Type::ConstIterator * regular {nullptr};
        typename Sortable::Iterator * sorted {nullptr};

        bool usingSortable {false};
    public:
        Iterator () noexcept _ITERABLE_CONSTRAINT = delete;
        Iterator ( Iterator const & it ) noexcept _ITERABLE_CONSTRAINT :
                _pView(it._pView),
                regular(it.regular == nullptr ? nullptr : new typename Type::Iterator(*it.regular)),
                sorted(it.sorted == nullptr ? nullptr : new typename Sortable::Iterator(*it.sorted)),
                usingSortable(it.usingSortable){

        };

        Iterator ( Iterator && it ) noexcept _ITERABLE_CONSTRAINT :
                _pView(it._pView),
                regular(std::exchange(it.regular, nullptr)),
                sorted(std::exchange(it.sorted, nullptr)),
                usingSortable(it.usingSortable){

        };

        Iterator (View * pView, typename Type::ConstIterator const & it) noexcept _ITERABLE_CONSTRAINT :
                _pView(pView),
                regular(new typename Type::ConstIterator(it)),
                sorted(nullptr),
                usingSortable(false){
            while ( (*this->regular) != this->_pView->_pObject->end() && ! this->_pView->validate(this->value(true)) )
                this->regular->next();
        }

        Iterator (View * pView, typename Sortable::Iterator const & itSortable ) noexcept _ITERABLE_CONSTRAINT :
                _pView(pView),
                usingSortable(true),
                sorted(new typename Sortable::Iterator(itSortable)),
                regular(nullptr) {
            while ( (*this->sorted) != this->_pView->_pSortable->end() && ! this->_pView->validate(this->value(true)) )
                this->sorted->next();
        }

        ~Iterator () noexcept {
            delete this->sorted;
            delete this->regular;
        }

        [[nodiscard]] inline auto value (bool pureRequired = false) const noexcept -> typename std::remove_reference<IterableValue>::type _ITERABLE_CONSTRAINT {
            auto v = this->usingSortable ? this->sorted->value() : this->regular->value();
            if ( pureRequired )
                return v;

            this->_pView->_mappers.forEach([&v](auto mPair){ v = (*mPair.getFirst())(v); });
            return v;
        }

        [[nodiscard]] inline auto next () noexcept -> Iterator & _ITERABLE_CONSTRAINT {
            if ( this->usingSortable )
                this->sorted->next();
            else
                this->regular->next();
            while (
                    ( this->usingSortable ?
                        (* this->sorted) != this->_pView->_pSortable->end() :
                        (* this->regular) != this->_pView->_pObject->end()
                    ) &&
                    ! this->_pView->validate(this->value(true))
                )
                if ( this->usingSortable )
                    this->sorted->next();
                else
                    this->regular->next();
            return * this;
        }

        inline auto operator == ( Iterator const & obj ) const noexcept -> bool _ITERABLE_CONSTRAINT {
            return
                this->usingSortable ?
                    *this->sorted == *obj.sorted && this->_pView->_pSortable == obj._pView->_pSortable :
                    *this->regular == *obj.regular && this->_pView->_pObject == obj._pView->_pObject;
        }

        inline auto operator != ( Iterator const & obj ) const noexcept -> bool _ITERABLE_CONSTRAINT {
            return
                this->usingSortable ?
                    *this->sorted != *obj.sorted || this->_pView->_pSortable != obj._pView->_pSortable :
                    *this->regular != *obj.regular || this->_pView->_pObject != obj._pView->_pObject;
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
    View ( View const & obj ) noexcept _ITERABLE_CONSTRAINT :
            _pObject(obj._owner ? new Type(obj._pObject) : obj._pObject),
            _distinctInstances(obj._distinctInstances),
            _sorted(obj._sorted),
            _sorter(obj._sorter == nullptr ? nullptr : new StoredSorter( * obj._sorter)),
            _pSortable(obj._pSortable == nullptr ? nullptr : new Sortable(* obj._pSortable)),
            _instanceHolderIndex(obj._instanceHolderIndex),
            _owner(obj._owner){
        obj._predicates.forEach([this](auto & pPair){this->_predicates.pushBack({new StoredPredicate(*pPair.getFirst()), pPair.getSecond()});});
        obj._mappers.forEach([this](auto & mPair){this->_mappers.pushBack({new StoredMapper(*mPair.getFirst()), mPair.getSecond()});});
    }

    View ( View && obj ) noexcept _ITERABLE_CONSTRAINT:
            _pObject(std::exchange(obj._pObject, nullptr)),
            _distinctInstances(std::move(obj._distinctInstances)),
            _sorted(std::exchange(obj._sorted, false)),
            _sorter(std::exchange(obj._sorter, nullptr)),
            _pSortable(std::exchange(obj._pSortable, nullptr)),
            _instanceHolderIndex(std::exchange(obj._instanceHolderIndex, 0) + 1),
            _owner(std::exchange(obj._owner, false)){
        while ( ! obj._predicates.empty() ) this->_predicates.pushBack(obj._predicates.popFront());
        while ( ! obj._mappers.empty() ) this->_mappers.pushBack(obj._mappers.popFront());
    }

    View & operator = ( View const & obj ) noexcept _ITERABLE_CONSTRAINT {
        if ( this == & obj ) return * this;

        this->_pObject = obj._owner ? new Type(obj._pObject) : obj._pObject;
        this->_distinctInstances = obj._distinctInstances;
        this->_sorted = obj._sorted;
        this->_sorter = obj._sorter == nullptr ? nullptr : new StoredSorter( * obj._sorter );
        this->_pSortable = obj._pSortable == nullptr ? nullptr : new Sortable( * obj._pSortable);
        this->_instanceHolderIndex = obj._instanceHolderIndex;
        this->_owner = obj._owner;

        obj._predicates.forEach([this](auto & pPair){this->_predicates.pushBack({new StoredPredicate(*pPair.getFirst()), pPair.getSecond()});});
        obj._mappers.forEach([this](auto & mPair){this->_mappers.pushBack({new StoredMapper(*mPair.getFirst()), mPair.getSecond()});});

        return * this;
    }

    View & operator = ( View && obj ) noexcept _ITERABLE_CONSTRAINT {
        if ( this == & obj ) return * this;

        this->_pObject = std::exchange(obj._pObject, false);
        this->_distinctInstances = std::move(obj._distinctInstances);
        this->_sorted = std::exchange(obj._sorted, false);
        this->_sorter = std::exchange(obj._sorter, nullptr);
        this->_pSortable = std::exchange(obj._pSortable, nullptr);
        this->_instanceHolderIndex = std::exchange(obj._instanceHolderIndex, 0) + 1;
        this->_owner = std::exchange(obj._owner, false);

        while ( ! obj._predicates.empty() ) this->_predicates.pushBack(obj._predicates.popFront());
        while ( ! obj._mappers.empty() ) this->_mappers.pushBack(obj._mappers.popFront());
        return * this;
    }

    explicit View ( Type const & obj ) noexcept _ITERABLE_CONSTRAINT : _pObject( & obj ), _instanceHolderIndex(0) {}
    explicit View ( Type const * obj ) noexcept _ITERABLE_CONSTRAINT : _pObject( obj ), _instanceHolderIndex(0) {}
    explicit View ( Type && obj ) noexcept _ITERABLE_CONSTRAINT : _pObject( new Type(obj) ), _instanceHolderIndex(0) {}

    ~View() noexcept override {
        for ( auto pPair : this->_predicates )
            delete pPair.getFirst();
        for ( auto mPair : this->_mappers )
            delete mPair.getFirst();
        delete this->_sorter;
        delete this->_pSortable;

        if ( this->_owner )
            delete this->_pObject;
    };

    inline auto begin () noexcept -> Iterator _ITERABLE_CONSTRAINT {
        if ( ! this->_sorted )
            return Iterator(this, this->_pObject->begin());
        else {
            this->requestSorted();
            return Iterator(this, this->_pSortable->begin());
        }
    }

    inline auto end () noexcept -> Iterator _ITERABLE_CONSTRAINT {
        if ( ! this->_sorted )
            return Iterator(this, this->_pObject->end());
        else {
            this->requestSorted();
            return Iterator(this, this->_pSortable->end());
        }
    }

    template < typename Predicate >
    inline auto filter ( Predicate const & predicate ) && noexcept -> View _ITERABLE_CONSTRAINT {
        this->_predicates.pushBack({new StoredPredicate (predicate), this->_instanceHolderIndex});
        return std::move(* this);
    }

    template < typename Predicate >
    inline auto count ( Predicate const & predicate ) noexcept -> int _ITERABLE_CONSTRAINT {
        Index c = 0;
        for ( auto e : * this ) if ( predicate(e) ) c++;

        return c;
    }

    inline auto count ( ) noexcept -> int _ITERABLE_CONSTRAINT {
        Index c = 0;
        for ( auto e : * this ) c++;
        return c;
    }

    template < typename Action >
    inline auto forEach ( Action const & action ) noexcept -> void _ITERABLE_CONSTRAINT { for ( auto e : * this ) action (e); }

    template < typename Mapper >
    inline auto map ( Mapper const & mapper ) && noexcept -> View _ITERABLE_CONSTRAINT {
        this->_mappers.pushBack({new StoredMapper (mapper), this->_instanceHolderIndex});
        return std::move(* this);
    }

    template < typename Sorter >
    inline auto sorted ( Sorter const & sorter ) && noexcept -> View _ITERABLE_CONSTRAINT {
        if ( this->_sorter != nullptr )
            delete this->_sorter;

        this->_sorter = new StoredSorter(sorter);
        this->_sorted = true;
        return std::move(*this);
    }

    inline auto sorted () && noexcept -> View _ITERABLE_CONSTRAINT {
        if ( this->_sorter != nullptr )
            delete this->_sorter;

        this->_sorter = nullptr;
        this->_sorted = true;
        return std::move(*this);
    }

    inline auto average () noexcept -> ViewValue _AVERAGE_ITERABLE_CONSTRAINT {
        ViewValue avg = 0;
        Size n = 0;
        for ( auto e : * this ) {
            avg += e;
            n ++;
        }

        return avg/n;
    }

    auto distinct () && noexcept -> View _ITERABLE_CONSTRAINT {
        this->_distinctInstances.pushBack({{}, this->_instanceHolderIndex});
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

#include <Traits.hpp>

template <typename T>
auto View<T>::Sortable::push ( ViewValue & v ) noexcept -> void {
    auto map = [this] (ViewValue v) { this->pView->_mappers.forEach([&v](auto & mPair){v = (*mPair.getFirst())(v);}); return v; };

    auto s = [this, &map] (ViewValue & a, ViewValue & b) -> bool {
        if ( this->pView->_sorter == nullptr ) {
            if constexpr ( isComparableLess <ViewValue, ViewValue>::value ) {
                return map(a) < map(b);
            } else {
                return true;
            }
        }

        auto tempA = map(a);
        auto tempB = map(b);
        return (*this->pView->_sorter)(tempA, tempB);
    };

    if ( this->front == nullptr ) {
        this->front = new Node ( nullptr, v );
        return;
    }

    if ( s ( v, this->front->value() ) ) {
        this->front = new Node ( this->front, v );
        return;
    }

    auto head = this->front;
    while ( head->next() != nullptr && s ( head->next()->value(), v ) )
        head = head->next();

    head->next() = new Node ( head->next(), v );
}

#undef _ITERABLE_CONSTRAINT
#undef _PRINTABLE_CONSTRAINT
#undef _AVERAGE_ITERABLE_CONSTRAINT

#endif //CDS_VIEW_HPP
