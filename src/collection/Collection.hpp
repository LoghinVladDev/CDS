//
// Created by loghin on 15.01.2021.
//

#ifndef CDS_COLLECTION_HPP
#define CDS_COLLECTION_HPP

#include <functional>

#ifdef COLLECTION_FORCE_EXPLICIT_CONVERSIONS
#ifndef COLLECTION_EXPLICIT_CONVERSION
#define COLLECTION_EXPLICIT_CONVERSION explicit
#endif
#else
#ifndef COLLECTION_EXPLICIT_CONVERSION
#define COLLECTION_EXPLICIT_CONVERSION
#endif
#endif

#include "../std-types.h"
#include <CDS/Pointer>

#if defined(__cpp_concepts) && !defined(_MSC_VER)

template <typename T>
concept Comparable = requires ( const T & a, const T & b ) {
    std::is_convertible < decltype(a < b), bool >::value;
};

#endif

#include <type_traits>
#include <CDS/Object>

#include <CDS/Traits>
#include <CDS/Concepts>

template <class T>
class Comparator {
public:
    virtual auto operator () (const T &, const T &) const noexcept -> bool = 0;
};

template < typename C >
class Sequence;

template <class T>
class Collection : public Object {
public:
    using ElementType = T;
    using ElementRef = T &;
    using ElementMRef = T &&;
    using ElementCRef = T const &;
    using ElementPtr = T *;
    using ElementPtrRef = ElementPtr &;
    using ElementCPtr = T const *;

protected:
    class CollectionOutOfBounds : public std::exception {
    public:
        __CDS_NoDiscard auto what() const noexcept -> StringLiteral override {
            return "Accessed Collection Iterator/Index Out of Range";
        }
    };

    Collection() noexcept = default;

public:

    class Iterator : public Object {
        friend class Collection < T >;

    private:
        Collection < T > * pBaseCollection {nullptr};

    protected:
        Iterator(const Iterator &) noexcept = default;
        Iterator(Iterator &&) noexcept = default;

        explicit Iterator ( Collection < T > * pBase ) noexcept : pBaseCollection(pBase) { }

        constexpr auto of ( Collection const * pCollection ) const noexcept -> bool {
            return this->pBaseCollection == pCollection;
        }

    public:
        Iterator() noexcept = delete;
        ~Iterator() noexcept override = default;

        __CDS_OptimalInline auto operator = (Iterator const & obj) noexcept -> Iterator & { // NOLINT(bugprone-unhandled-self-assignment)
            this->pBaseCollection = obj.pBaseCollection;
            return * this;
        }

        __CDS_cpplang_ConstexprPureAbstract virtual auto next (  ) noexcept -> Iterator & = 0;
        __CDS_cpplang_ConstexprPureAbstract virtual auto equals ( const Iterator & ) const noexcept -> bool = 0;
        __CDS_cpplang_ConstexprPureAbstract virtual auto value() const noexcept -> T& = 0;

        __CDS_cpplang_VirtualConstexpr virtual auto operator ++ () noexcept -> Iterator & { this->next(); return * this; }

        __CDS_OptimalInline auto operator == ( const Iterator & o ) const noexcept -> bool { return this->equals(o ); }
        __CDS_OptimalInline auto operator != ( const Iterator & o ) const noexcept -> bool { return ! this->equals(o ); }
        __CDS_OptimalInline auto operator * () const noexcept -> T& { return this->value(); }

        __CDS_NoDiscard auto copy () const noexcept -> Iterator * override = 0;
    };

    class ConstIterator : public Object {
        friend class Collection < T >;

    private:
        Collection < T > const * pBaseCollection {nullptr};

    protected:
        ConstIterator(const ConstIterator &) noexcept = default;
        ConstIterator(ConstIterator &&) noexcept = default;

        explicit ConstIterator(Collection const * pBase) noexcept : pBaseCollection(pBase) { }

        constexpr auto of ( Collection const * pCollection ) const noexcept -> bool {
            return this->pBaseCollection == pCollection;
        }

    public:
        ConstIterator() noexcept = delete;
        ~ConstIterator() noexcept override = default;

        __CDS_OptimalInline auto operator = (ConstIterator const & obj) noexcept -> ConstIterator & { // NOLINT(bugprone-unhandled-self-assignment)
            this->pBaseCollection = obj.pBaseCollection;
            return * this;
        }

        __CDS_cpplang_ConstexprPureAbstract virtual auto next (  ) noexcept -> ConstIterator & = 0;
        __CDS_cpplang_ConstexprPureAbstract virtual auto equals ( const ConstIterator & ) const noexcept -> bool = 0;
        __CDS_cpplang_ConstexprPureAbstract virtual auto value () const noexcept -> const T& = 0;

        __CDS_cpplang_VirtualConstexpr virtual auto operator ++ () noexcept -> ConstIterator & { this->next(); return * this; }

        __CDS_OptimalInline auto operator == ( const ConstIterator & o ) const noexcept -> bool { return this->equals(o ); }
        __CDS_OptimalInline auto operator != ( const ConstIterator & o ) const noexcept -> bool { return ! this->equals(o ); }
        __CDS_OptimalInline auto operator * () const noexcept -> const T& { return this->value(); }

        __CDS_NoDiscard auto copy () const noexcept -> ConstIterator * override = 0;
    };
protected:
    virtual auto beginPtr () noexcept -> Iterator * = 0;
    virtual auto endPtr () noexcept -> Iterator * = 0;
    __CDS_MaybeUnused virtual auto beginPtr () const noexcept -> ConstIterator * = 0;
    __CDS_MaybeUnused virtual auto endPtr () const noexcept -> ConstIterator * = 0;

    __CDS_MaybeUnused static __CDS_OptimalInline auto beginPtr ( Collection < T > & o ) noexcept -> Iterator * { return o.beginPtr(); }
    __CDS_MaybeUnused static __CDS_OptimalInline auto endPtr ( Collection < T > & o ) noexcept -> Iterator * { return o.endPtr(); }
    __CDS_MaybeUnused static __CDS_OptimalInline auto beginPtr ( const Collection < T > & o ) noexcept -> ConstIterator * { return o.beginPtr(); }
    __CDS_MaybeUnused static __CDS_OptimalInline auto endPtr ( const Collection < T > & o ) noexcept -> ConstIterator * { return o.endPtr(); }

    static __CDS_OptimalInline auto iteratorIsOf ( Iterator const & it, Collection < T > const & collection ) noexcept -> bool {
        return it.of(& collection);
    }

    __CDS_MaybeUnused static __CDS_OptimalInline auto iteratorIsOf ( ConstIterator const & it, Collection < T > const & collection ) noexcept -> bool {
        return it.of(& collection);
    }

//    virtual auto findPtr ( T & ) noexcept -> Iterator & = 0;
//    virtual auto findPtr ( const T & ) const noexcept -> ConstIterator & = 0;

public:
    __CDS_MaybeUnused virtual auto remove ( const T &, Size ) noexcept -> bool = 0;
    __CDS_MaybeUnused virtual auto __CDS_OptimalInline removeAll ( const T & o ) noexcept -> bool { return this->remove( o, this->size() ); }
    __CDS_MaybeUnused virtual auto __CDS_OptimalInline removeFirst ( const T & o ) noexcept -> bool { return this->remove( o, 1 ); }
    __CDS_MaybeUnused virtual auto removeLast ( const T & o ) noexcept -> bool = 0;

    __CDS_MaybeUnused virtual auto removeOf ( const Collection &, Size ) noexcept -> bool = 0;
    __CDS_MaybeUnused virtual auto __CDS_OptimalInline removeFirstOf ( const Collection & o ) noexcept -> bool { return this->removeOf( o, 1 ); }
    __CDS_MaybeUnused virtual auto __CDS_OptimalInline removeAllOf ( const Collection & o ) noexcept -> bool { return this->removeOf ( o, this->size() ); }
    __CDS_MaybeUnused virtual auto removeLastOf ( const Collection & ) noexcept -> bool = 0;

    __CDS_MaybeUnused virtual auto removeNotOf ( const Collection &, Size ) noexcept -> bool = 0;
    __CDS_MaybeUnused virtual auto __CDS_OptimalInline removeFirstNotOf ( const Collection & o ) noexcept -> bool { return this->removeNotOf ( o, 1 ); }
    __CDS_MaybeUnused virtual auto __CDS_OptimalInline removeAllNotOf ( const Collection & o ) noexcept -> bool  { return this->removeNotOf( o, this->size() ); }
    __CDS_MaybeUnused virtual auto removeLastNotOf ( const Collection & ) noexcept -> bool = 0;

    __CDS_MaybeUnused virtual auto removeOf ( const std::initializer_list<T> &, Size ) noexcept -> bool = 0;
    __CDS_MaybeUnused virtual auto __CDS_OptimalInline removeFirstOf ( const std::initializer_list<T> & o ) noexcept -> bool { return this->removeOf( o, 1 ); }
    __CDS_MaybeUnused virtual auto __CDS_OptimalInline removeAllOf ( const std::initializer_list<T> & o ) noexcept -> bool { return this->removeOf ( o, this->size() ); }
    __CDS_MaybeUnused virtual auto removeLastOf ( const std::initializer_list<T> & ) noexcept -> bool = 0;

    __CDS_MaybeUnused virtual auto removeNotOf ( const std::initializer_list<T> &, Size ) noexcept -> bool = 0;
    __CDS_MaybeUnused virtual auto __CDS_OptimalInline removeFirstNotOf ( const std::initializer_list<T> & o ) noexcept -> bool { return this->removeNotOf ( o, 1 ); }
    __CDS_MaybeUnused virtual auto __CDS_OptimalInline removeAllNotOf ( const std::initializer_list<T> & o ) noexcept -> bool  { return this->removeNotOf( o, this->size() ); }
    __CDS_MaybeUnused virtual auto removeLastNotOf ( const std::initializer_list<T> & ) noexcept -> bool = 0;

protected:

    static auto iListContains ( std :: initializer_list < T > const & list, ElementCRef what ) noexcept -> bool {
        for ( auto & e : list )
            if ( Type < T > :: compare (e, what) )
                return true;

        return false;
    }

    virtual auto allocInsertGetPtr ( ElementCRef ) noexcept -> ElementPtrRef = 0;

public:

    template < typename V = T, typename std :: enable_if < Type < V > :: copyConstructible, int > :: type = 0 >
    __CDS_OptimalInline auto add (ElementCRef element) noexcept -> void {
        auto & p = this->allocInsertGetPtr(element);
        if ( p == nullptr )
            p = new ElementType(element);
    }

    template < typename V = T, typename std :: enable_if < Type < V > :: moveConstructible, int > :: type = 0 >
    __CDS_OptimalInline auto add (ElementMRef element) noexcept -> void {
        auto & p = this->allocInsertGetPtr(element);
        if ( p == nullptr )
            p = new ElementType(element);
    }

    virtual auto clear () noexcept -> void = 0;

    __CDS_MaybeUnused __CDS_NoDiscard virtual auto size () const noexcept -> Size = 0;
    __CDS_MaybeUnused virtual auto makeUnique () noexcept -> void = 0;

    virtual auto contains ( ElementCRef e ) const noexcept -> bool {
        for ( auto i = UniquePointer < ConstIterator > ( this->beginPtr() ), end = UniquePointer < ConstIterator > ( this->endPtr() ); ! i->equals(* end); i->next() )
            if ( Type < ElementCRef > ::compare ( i->value (), e ) )
                return true;
        return false;
    }

#define COMMA ,

    template < typename Action >
    __CDS_MaybeUnused auto forEach ( Action const & ) noexcept ( noexcept ( ( * dataTypes :: unsafeAddress < Action > () ) ( Type < ElementType > :: unsafeReference() ) ) ) -> void __CDS_Requires ( IsActionOver < Action COMMA T > );
    template < typename Action >
    __CDS_MaybeUnused auto forEach ( Action const & ) const noexcept ( noexcept ( ( * dataTypes :: unsafeAddress < Action > () ) ( Type < ElementType const > :: unsafeReference() ) ) ) -> void __CDS_Requires ( IsActionOver < Action COMMA T > );

    template < typename Predicate = std::function < bool ( ElementType const & ) > >
    __CDS_MaybeUnused __CDS_OptimalInline auto some ( Size count, Predicate const & predicate = []( ElementType const & ) noexcept -> bool { return true; } ) noexcept ( noexcept ( ( * dataTypes :: unsafeAddress < Predicate > () ) ( Type < ElementType > :: unsafeReference() ) ) ) -> bool __CDS_Requires( IsPredicateOver < Predicate COMMA T > ) {
        return this->count(predicate) == count;
    }

    template < typename Predicate = std::function < bool ( ElementType const & ) > >
    __CDS_MaybeUnused __CDS_OptimalInline auto some ( Size count, Predicate const & predicate = []( ElementType const & ) noexcept -> bool { return true; } ) const noexcept ( noexcept ( ( * dataTypes :: unsafeAddress < Predicate > () ) ( Type < ElementType const > :: unsafeReference() ) ) ) -> bool __CDS_Requires( IsPredicateOver < Predicate COMMA T > ) {
        return this->count(predicate) == count;
    }

    template < typename Predicate = std::function < bool ( ElementType const & ) > >
    __CDS_MaybeUnused __CDS_OptimalInline auto atLeast ( Size count, Predicate const & predicate = []( ElementType const & ) noexcept -> bool { return true; } ) noexcept ( noexcept ( ( * dataTypes :: unsafeAddress < Predicate > () ) ( Type < ElementType > :: unsafeReference() ) ) ) -> bool __CDS_Requires( IsPredicateOver < Predicate COMMA T > ) {
        return this->count(predicate) >= count;
    }

    template < typename Predicate = std::function < bool ( ElementType const & ) > >
    __CDS_MaybeUnused __CDS_OptimalInline auto atLeast ( Size count, Predicate const & predicate = []( ElementType const & ) noexcept -> bool { return true; } ) const noexcept ( noexcept ( ( * dataTypes :: unsafeAddress < Predicate > () ) ( Type < ElementType const > :: unsafeReference() ) ) ) -> bool __CDS_Requires( IsPredicateOver < Predicate COMMA T > ) {
        return this->count(predicate) >= count;
    }

    template < typename Predicate = std::function < bool ( ElementType const & ) > >
    __CDS_MaybeUnused __CDS_OptimalInline auto atMost ( Size count, Predicate const & predicate = []( ElementType const & ) noexcept -> bool { return true; } ) noexcept ( noexcept ( ( * dataTypes :: unsafeAddress < Predicate > () ) ( Type < ElementType > :: unsafeReference() ) ) ) -> bool __CDS_Requires( IsPredicateOver < Predicate COMMA T > ) {
        return this->count(predicate) <= count;
    }

    template < typename Predicate = std::function < bool ( ElementType const & ) > >
    __CDS_MaybeUnused __CDS_OptimalInline auto atMost ( Size count, Predicate const & predicate = []( ElementType const & ) noexcept -> bool { return true; } ) const noexcept ( noexcept ( ( * dataTypes :: unsafeAddress < Predicate > () ) ( Type < ElementType const > :: unsafeReference() ) ) ) -> bool __CDS_Requires( IsPredicateOver < Predicate COMMA T > ) {
        return this->count(predicate) <= count;
    }

    template < typename Predicate = std::function < bool ( ElementType const & ) > >
    __CDS_MaybeUnused __CDS_OptimalInline auto moreThan ( Size count, Predicate const & predicate = []( ElementType const & ) noexcept -> bool { return true; } ) noexcept ( noexcept ( ( * dataTypes :: unsafeAddress < Predicate > () ) ( Type < ElementType > :: unsafeReference() ) ) ) -> bool __CDS_Requires( IsPredicateOver < Predicate COMMA T > ) {
        return this->atLeast ( count, predicate );
    }

    template < typename Predicate = std::function < bool ( ElementType const & ) > >
    __CDS_MaybeUnused __CDS_OptimalInline auto moreThan ( Size count, Predicate const & predicate = []( ElementType const & ) noexcept -> bool { return true; } ) const noexcept ( noexcept ( ( * dataTypes :: unsafeAddress < Predicate > () ) ( Type < ElementType const > :: unsafeReference() ) ) ) -> bool __CDS_Requires( IsPredicateOver < Predicate COMMA T > ) {
        return this->atLeast ( count, predicate );
    }

    template < typename Predicate = std::function < bool ( ElementType const & ) > >
    __CDS_MaybeUnused __CDS_OptimalInline auto lessThan ( Size count, Predicate const & predicate = []( ElementType const & ) noexcept -> bool { return true; } ) noexcept ( noexcept ( ( * dataTypes :: unsafeAddress < Predicate > () ) ( Type < ElementType > :: unsafeReference() ) ) ) -> bool __CDS_Requires( IsPredicateOver < Predicate COMMA T > ) {
        return this->lessThan ( count, predicate );
    }

    template < typename Predicate = std::function < bool ( ElementType const & ) > >
    __CDS_MaybeUnused __CDS_OptimalInline auto lessThan ( Size count, Predicate const & predicate = []( ElementType const & ) noexcept -> bool { return true; } ) const noexcept ( noexcept ( ( * dataTypes :: unsafeAddress < Predicate > () ) ( Type < ElementType const > :: unsafeReference() ) ) ) -> bool __CDS_Requires( IsPredicateOver < Predicate COMMA T > ) {
        return this->lessThan ( count, predicate );
    }

    template < typename Predicate = std::function < bool ( ElementType const & ) > >
    __CDS_MaybeUnused auto count ( Predicate const & = []( ElementType const & ) noexcept -> bool { return true; } ) noexcept ( noexcept ( ( * dataTypes :: unsafeAddress < Predicate > () ) ( Type < ElementType > :: unsafeReference() ) ) ) -> Size __CDS_Requires( IsPredicateOver < Predicate COMMA T > );

    template < typename Predicate = std::function < bool ( ElementType const & ) > >
    __CDS_MaybeUnused auto count ( Predicate const & = []( ElementType const & ) noexcept -> bool { return true; } ) const noexcept ( noexcept ( ( * dataTypes :: unsafeAddress < Predicate > () ) ( Type < ElementType const > :: unsafeReference() ) ) ) -> Size __CDS_Requires( IsPredicateOver < Predicate COMMA T > );

    template < typename Predicate >
    __CDS_MaybeUnused __CDS_OptimalInline auto any ( Predicate const & p ) noexcept ( noexcept ( ( * dataTypes :: unsafeAddress < Predicate > () ) ( Type < ElementType > :: unsafeReference() ) ) ) -> bool __CDS_Requires( IsPredicateOver < Predicate COMMA T > ) { return this->atLeast ( 1, p ); }
    template < typename Predicate >
    __CDS_MaybeUnused __CDS_OptimalInline auto any ( Predicate const & p ) const noexcept ( noexcept ( ( * dataTypes :: unsafeAddress < Predicate > () ) ( Type < ElementType const > :: unsafeReference() ) ) ) -> bool __CDS_Requires( IsPredicateOver < Predicate COMMA T > ) { return this->atLeast ( 1, p ); }

    template < typename Predicate >
    __CDS_MaybeUnused __CDS_OptimalInline auto all ( Predicate const & p ) noexcept ( noexcept ( ( * dataTypes :: unsafeAddress < Predicate > () ) ( Type < ElementType > :: unsafeReference() ) ) ) -> bool __CDS_Requires( IsPredicateOver < Predicate COMMA T > ) { return ! this->any ( [&p] (T & e) noexcept -> bool { return ! p(e); } ); }
    template < typename Predicate >
    __CDS_MaybeUnused __CDS_OptimalInline auto all ( Predicate const & p ) const noexcept ( noexcept ( ( * dataTypes :: unsafeAddress < Predicate > () ) ( Type < ElementType const > :: unsafeReference() ) ) ) -> bool __CDS_Requires( IsPredicateOver < Predicate COMMA T > ) { return ! this->any ( [&p] (T const & e) noexcept -> bool { return ! p(e); } ); }

#undef COMMA

    virtual COLLECTION_EXPLICIT_CONVERSION operator bool () const noexcept { // NOLINT(google-explicit-constructor)
        return this->size() != 0;
    }

    __CDS_NoDiscard auto toString () const noexcept -> String override = 0;

    ~Collection() noexcept override = default;

    friend __CDS_OptimalInline auto operator << ( std::ostream & o, const Collection & c ) noexcept -> std::ostream & {
         return ( o << c.toString() );
    }

    __CDS_NoDiscard __CDS_MaybeUnused __CDS_cpplang_ConstexprPureAbstract virtual auto empty () const noexcept -> bool = 0;
};

#define COMMA ,

template < typename T >
template < typename Action >
auto Collection<T>::forEach ( Action const & a ) noexcept ( noexcept ( ( * dataTypes :: unsafeAddress < Action > () ) ( Type < ElementType > :: unsafeReference() ) ) ) -> void __CDS_Requires( IsActionOver < Action COMMA T > ) {
    auto begin = this->beginPtr();
    auto end = this->endPtr();

    for ( auto it = begin; ! it->equals( * end ); it->next() )
        a ( it->value() );

    delete begin;
    delete end;
}

template < typename T >
template < typename Action >
auto Collection<T>::forEach ( Action const & a ) const noexcept ( noexcept ( ( * dataTypes :: unsafeAddress < Action > () ) ( Type < ElementType const > :: unsafeReference() ) ) ) -> void __CDS_Requires( IsActionOver < Action COMMA T > ) {
    auto begin = this->beginPtr();
    auto end = this->endPtr();

    for ( auto it = begin; ! it->equals( * end ); it->next() )
        a ( it->value() );

    delete begin;
    delete end;
}

template < typename T >
template < typename Predicate >
auto Collection<T>::count ( Predicate const & p ) noexcept ( noexcept ( ( * dataTypes :: unsafeAddress < Predicate > () ) ( Type < ElementType > :: unsafeReference() ) ) ) -> Size __CDS_Requires( IsPredicateOver < Predicate COMMA T > ) {
    Size trueCount = 0;

    auto pBegin = this->beginPtr();
    auto pEnd = this->endPtr();

    for ( auto it = pBegin; ! it->equals( * pEnd ); it->next() )
        if ( p ( it->value() ) )
            trueCount ++;

    delete pBegin;
    delete pEnd;

    return trueCount;
}

template < typename T >
template < typename Predicate >
auto Collection<T>::count ( Predicate const & p ) const noexcept ( noexcept ( ( * dataTypes :: unsafeAddress < Predicate > () ) ( Type < ElementType const > :: unsafeReference() ) ) ) -> Size __CDS_Requires( IsPredicateOver < Predicate COMMA T > ) {
    Size trueCount = 0;

    auto pBegin = this->beginPtr();
    auto pEnd = this->endPtr();

    for ( auto it = pBegin; ! it->equals( * pEnd ); it->next() )
        if ( p ( it->value() ) )
            trueCount ++;

    delete pBegin;
    delete pEnd;

    return trueCount;
}

#undef COMMA

__CDS_RegisterParseTypeTemplateT(Collection)

#endif //CDS_COLLECTION_HPP
