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
#include <CDS/Function>
#include <CDS/Traits>

#if defined(__CDS_ThreadSafeObjects)

#include <CDS/Mutex>
#define __CDS_Collection_OperationalLock this->multithreadingProtection.lock(); /* NOLINT(bugprone-reserved-identifier) */
#define __CDS_Collection_OperationalUnlock this->multithreadingProtection.unlock(); /* NOLINT(bugprone-reserved-identifier) */

#else

#define __CDS_Collection_OperationalLock /* NOLINT(bugprone-reserved-identifier) */
#define __CDS_Collection_OperationalUnlock /* NOLINT(bugprone-reserved-identifier) */

#endif

#if __CDS_cpplang_Concepts_available == true

template <typename T>
concept Comparable = requires ( T const & a, T const & b ) {
    std::is_convertible < decltype(a < b), bool >::value;
};

#endif

#include <type_traits>
#include <CDS/Object>

#include <CDS/Traits>
#include <CDS/Concepts>

template < typename T >
class Comparator {
public:
    virtual auto operator () (T const &, T const &) const noexcept -> bool = 0;
};

template < typename C >
class Sequence;

template < typename T >
class Collection : public Object {
public:
    using ElementType = T;

protected:
    using ElementRef = T &;
    using ElementMRef = T &&;
    using ElementCRef = T const &;
    using ElementPtr = T *;
    using ElementPtrRef = ElementPtr &;
    using ElementCPtr = T const *;
    using InitializerList = std :: initializer_list < T > const &;

    constexpr Collection() noexcept = default;

public:

    class Iterator : public Object {
        friend class Collection < T >;

    private:
        Collection < T > * pBaseCollection {nullptr};

    protected:
        constexpr Iterator(Iterator const &) noexcept = default;
        constexpr Iterator(Iterator &&) noexcept = default;

        constexpr explicit Iterator ( Collection < T > * pBase ) noexcept : pBaseCollection(pBase) { }

        constexpr auto of ( Collection const * pCollection ) const noexcept -> bool {
            return this->pBaseCollection == pCollection;
        }

    public:
        constexpr Iterator() noexcept = delete;
        __CDS_cpplang_ConstexprDestructor ~Iterator() noexcept override = default;

        __CDS_cpplang_NonConstConstexprMemberFunction auto operator = (Iterator const & obj) noexcept -> Iterator & { // NOLINT(bugprone-unhandled-self-assignment)
            this->pBaseCollection = obj.pBaseCollection;
            return * this;
        }

        __CDS_cpplang_ConstexprPureAbstract virtual auto next () noexcept -> Iterator & = 0;
        __CDS_cpplang_ConstexprPureAbstract virtual auto equals ( const Iterator & ) const noexcept -> bool = 0;
        __CDS_cpplang_ConstexprPureAbstract virtual auto value () const noexcept -> T& = 0;

        __CDS_cpplang_VirtualConstexpr virtual auto operator ++ () noexcept -> Iterator & { return this->next(); }

        __CDS_cpplang_VirtualConstexpr auto operator == ( Iterator const & o ) const noexcept -> bool { return this->equals( o ); }
        __CDS_cpplang_VirtualConstexpr auto operator != ( Iterator const & o ) const noexcept -> bool { return ! this->equals( o ); }
        __CDS_cpplang_VirtualConstexpr auto operator * () const noexcept -> T& { return this->value(); }

        __CDS_NoDiscard auto copy () const noexcept -> Iterator * override = 0;
    };

    class ConstIterator : public Object {
        friend class Collection < T >;

    private:
        Collection < T > const * pBaseCollection {nullptr};

    protected:
        constexpr ConstIterator(ConstIterator const &) noexcept = default;
        constexpr ConstIterator(ConstIterator &&) noexcept = default;

        constexpr explicit ConstIterator(Collection const * pBase) noexcept : pBaseCollection(pBase) { }

        constexpr auto of ( Collection const * pCollection ) const noexcept -> bool {
            return this->pBaseCollection == pCollection;
        }

    public:
        constexpr ConstIterator() noexcept = delete;
        __CDS_cpplang_ConstexprDestructor ~ConstIterator() noexcept override = default;

        __CDS_cpplang_NonConstConstexprMemberFunction auto operator = (ConstIterator const & obj) noexcept -> ConstIterator & { // NOLINT(bugprone-unhandled-self-assignment)
            this->pBaseCollection = obj.pBaseCollection;
            return * this;
        }

        __CDS_cpplang_ConstexprPureAbstract virtual auto next ( ) noexcept -> ConstIterator & = 0;
        __CDS_cpplang_ConstexprPureAbstract virtual auto equals ( ConstIterator const & ) const noexcept -> bool = 0;
        __CDS_cpplang_ConstexprPureAbstract virtual auto value ( ) const noexcept -> ElementCRef = 0;

        __CDS_cpplang_VirtualConstexpr virtual auto operator ++ () noexcept -> ConstIterator & { return this->next(); }

        __CDS_cpplang_VirtualConstexpr auto operator == ( ConstIterator const & o ) const noexcept -> bool { return this->equals(o ); }
        __CDS_cpplang_VirtualConstexpr auto operator != ( ConstIterator const & o ) const noexcept -> bool { return ! this->equals(o ); }
        __CDS_cpplang_VirtualConstexpr auto operator * () const noexcept -> ElementCRef { return this->value(); }

        __CDS_NoDiscard auto copy () const noexcept -> ConstIterator * override = 0;
    };

protected:
    virtual auto beginPtr () noexcept -> Iterator * = 0;
    virtual auto endPtr () noexcept -> Iterator * = 0;
    __CDS_MaybeUnused virtual auto beginPtr () const noexcept -> ConstIterator * = 0;
    __CDS_MaybeUnused virtual auto endPtr () const noexcept -> ConstIterator * = 0;

    __CDS_MaybeUnused __CDS_OptimalInline static auto beginPtr ( Collection & o ) noexcept -> Iterator * { return o.beginPtr(); }
    __CDS_MaybeUnused __CDS_OptimalInline static auto endPtr ( Collection & o ) noexcept -> Iterator * { return o.endPtr(); }
    __CDS_MaybeUnused __CDS_OptimalInline static auto beginPtr ( Collection const & o ) noexcept -> ConstIterator * { return o.beginPtr(); }
    __CDS_MaybeUnused __CDS_OptimalInline static auto endPtr ( Collection const & o ) noexcept -> ConstIterator * { return o.endPtr(); }

    __CDS_OptimalInline static auto iteratorIsOf ( Iterator const & it, Collection const & collection ) noexcept -> bool {
        return it.of(& collection);
    }

    __CDS_MaybeUnused __CDS_OptimalInline static auto iteratorIsOf ( ConstIterator const & it, Collection const & collection ) noexcept -> bool {
        return it.of(& collection);
    }

#if defined(__CDS_ThreadSafeObjects)
        Mutex mutable multithreadingProtection;
#endif

public:
    __CDS_MaybeUnused virtual auto remove ( ElementCRef, Size ) noexcept -> bool = 0;
    __CDS_MaybeUnused __CDS_OptimalInline virtual auto removeAll ( ElementCRef o ) noexcept -> bool { return this->remove( o, this->size() ); }
    __CDS_MaybeUnused __CDS_OptimalInline virtual auto removeFirst ( ElementCRef o ) noexcept -> bool { return this->remove( o, 1 ); }
    __CDS_MaybeUnused virtual auto removeLast ( ElementCRef o ) noexcept -> bool = 0;

    __CDS_MaybeUnused virtual auto removeOf ( Collection const &, Size ) noexcept -> bool = 0;
    __CDS_MaybeUnused __CDS_OptimalInline virtual auto removeFirstOf ( Collection const & o ) noexcept -> bool { return this->removeOf( o, 1 ); }
    __CDS_MaybeUnused __CDS_OptimalInline virtual auto removeAllOf ( Collection const & o ) noexcept -> bool { return this->removeOf ( o, this->size() ); }
    __CDS_MaybeUnused virtual auto removeLastOf ( Collection const & ) noexcept -> bool = 0;

    __CDS_MaybeUnused virtual auto removeNotOf ( Collection const &, Size ) noexcept -> bool = 0;
    __CDS_MaybeUnused __CDS_OptimalInline virtual auto removeFirstNotOf ( Collection const & o ) noexcept -> bool { return this->removeNotOf ( o, 1 ); }
    __CDS_MaybeUnused __CDS_OptimalInline virtual auto removeAllNotOf ( Collection const & o ) noexcept -> bool  { return this->removeNotOf( o, this->size() ); }
    __CDS_MaybeUnused virtual auto removeLastNotOf ( Collection const & ) noexcept -> bool = 0;

    __CDS_MaybeUnused virtual auto removeOf ( InitializerList, Size ) noexcept -> bool = 0;
    __CDS_MaybeUnused __CDS_OptimalInline virtual auto removeFirstOf ( InitializerList o ) noexcept -> bool { return this->removeOf( o, 1 ); }
    __CDS_MaybeUnused __CDS_OptimalInline virtual auto removeAllOf ( InitializerList o ) noexcept -> bool { return this->removeOf ( o, this->size() ); }
    __CDS_MaybeUnused virtual auto removeLastOf ( InitializerList ) noexcept -> bool = 0;

    __CDS_MaybeUnused virtual auto removeNotOf ( InitializerList, Size ) noexcept -> bool = 0;
    __CDS_MaybeUnused __CDS_OptimalInline virtual auto removeFirstNotOf ( InitializerList list ) noexcept -> bool { return this->removeNotOf ( list, 1 ); }
    __CDS_MaybeUnused __CDS_OptimalInline virtual auto removeAllNotOf ( InitializerList list ) noexcept -> bool  { return this->removeNotOf( list, this->size() ); }
    __CDS_MaybeUnused virtual auto removeLastNotOf ( InitializerList ) noexcept -> bool = 0;

protected:

    __CDS_cpplang_VirtualConstexpr static auto iListContains ( InitializerList list, ElementCRef what ) noexcept -> bool {
        for ( auto & e : list )
            if ( Type < T > :: compare (e, what) )
                return true;

        return false;
    }

    virtual auto allocInsertGetPtr ( ElementCRef ) noexcept -> ElementPtrRef = 0;

public:

    template < typename V = T, EnableIf < Type < V > :: copyConstructible > = 0 >
    __CDS_OptimalInline auto add (ElementCRef element) noexcept -> void {

        __CDS_Collection_OperationalLock

        auto & p = this->allocInsertGetPtr(element);
        if ( p == nullptr )
            p = Memory :: instance().create < ElementType > (element);

        __CDS_Collection_OperationalUnlock

    }

    template < typename V = T, EnableIf < Type < V > :: moveConstructible > = 0 >
    __CDS_OptimalInline auto add (ElementMRef element) noexcept -> void {

        __CDS_Collection_OperationalLock

        auto & p = this->allocInsertGetPtr(element);
        if ( p == nullptr )
            p = Memory :: instance().create < ElementType > (element);

        __CDS_Collection_OperationalUnlock

    }

    virtual auto clear () noexcept -> void = 0;

    __CDS_MaybeUnused __CDS_NoDiscard __CDS_cpplang_ConstexprPureAbstract virtual auto size () const noexcept -> Size = 0;
    __CDS_MaybeUnused virtual auto makeUnique () noexcept -> void = 0;

    __CDS_OptionalInline virtual auto contains ( ElementCRef e ) const noexcept -> bool {

        __CDS_Collection_OperationalLock

        for (
                auto
                    i = UniquePointer < ConstIterator > ( this->beginPtr() ),
                    end = UniquePointer < ConstIterator > ( this->endPtr() );
                ! i->equals(* end);
                i->next()
        )
            if ( Type < ElementType > :: compare ( i->value (), e ) ) {

                __CDS_Collection_OperationalUnlock
                return true;

            }

        __CDS_Collection_OperationalUnlock
        return false;
    }

#define COMMA ,

    template < typename Action >
    __CDS_MaybeUnused auto forEach (
            Action const &
    ) noexcept ( noexcept ( ( * Type < Action > :: unsafeAddress () ) ( Type < ElementType > :: unsafeReference() ) ) )
            -> void __CDS_Requires ( IsActionOver < Action COMMA T > );

    template < typename Action >
    __CDS_MaybeUnused auto forEach (
            Action const &
    ) const noexcept ( noexcept ( ( * Type < Action > :: unsafeAddress () ) ( Type < ElementType const > :: unsafeReference() ) ) )
            -> void __CDS_Requires ( IsActionOver < Action COMMA T > );

    template < typename Predicate = Function < bool ( ElementCRef ) > >
    __CDS_MaybeUnused __CDS_OptimalInline auto some (
            Size                count,
            Predicate   const & predicate = []( ElementCRef ) noexcept -> bool { return true; }
    ) noexcept ( noexcept ( ( * Type < Predicate > :: unsafeAddress () ) ( Type < ElementType > :: unsafeReference() ) ) )
            -> bool __CDS_Requires( IsPredicateOver < Predicate COMMA T > ) {

        return this->count(predicate) == count;
    }

    template < typename Predicate = Function < bool ( ElementCRef ) > >
    __CDS_MaybeUnused __CDS_OptimalInline auto some (
            Size                count,
            Predicate   const & predicate = []( ElementCRef ) noexcept -> bool { return true; }
    ) const noexcept ( noexcept ( ( * Type < Predicate > :: unsafeAddress () ) ( Type < ElementType const > :: unsafeReference() ) ) )
            -> bool __CDS_Requires( IsPredicateOver < Predicate COMMA T > ) {

        return this->count(predicate) == count;
    }

    template < typename Predicate = Function < bool ( ElementCRef ) > >
    __CDS_MaybeUnused __CDS_OptimalInline auto atLeast (
            Size                count,
            Predicate   const & predicate = []( ElementCRef ) noexcept -> bool { return true; }
    ) noexcept ( noexcept ( ( * Type < Predicate > :: unsafeAddress () ) ( Type < ElementType > :: unsafeReference() ) ) )
            -> bool __CDS_Requires( IsPredicateOver < Predicate COMMA T > ) {

        return this->count(predicate) >= count;
    }

    template < typename Predicate = Function < bool ( ElementCRef ) > >
    __CDS_MaybeUnused __CDS_OptimalInline auto atLeast (
            Size                count,
            Predicate   const & predicate = []( ElementCRef ) noexcept -> bool { return true; }
    ) const noexcept ( noexcept ( ( * Type < Predicate > :: unsafeAddress () ) ( Type < ElementType const > :: unsafeReference() ) ) )
            -> bool __CDS_Requires( IsPredicateOver < Predicate COMMA T > ) {

        return this->count(predicate) >= count;
    }

    template < typename Predicate = Function < bool ( ElementCRef ) > >
    __CDS_MaybeUnused __CDS_OptimalInline auto atMost (
            Size                count,
            Predicate   const & predicate = []( ElementCRef ) noexcept -> bool { return true; }
    ) noexcept ( noexcept ( ( * Type < Predicate > :: unsafeAddress () ) ( Type < ElementType > :: unsafeReference() ) ) )
            -> bool __CDS_Requires( IsPredicateOver < Predicate COMMA T > ) {

        return this->count(predicate) <= count;
    }

    template < typename Predicate = Function < bool ( ElementCRef ) > >
    __CDS_MaybeUnused __CDS_OptimalInline auto atMost (
            Size count,
            Predicate const & predicate = []( ElementCRef ) noexcept -> bool { return true; }
    ) const noexcept ( noexcept ( ( * Type < Predicate > :: unsafeAddress () ) ( Type < ElementType const > :: unsafeReference() ) ) )
            -> bool __CDS_Requires( IsPredicateOver < Predicate COMMA T > ) {

        return this->count(predicate) <= count;
    }

    template < typename Predicate = Function < bool ( ElementCRef ) > >
    __CDS_MaybeUnused __CDS_OptimalInline auto moreThan (
            Size                count,
            Predicate   const & predicate = []( ElementCRef ) noexcept -> bool { return true; }
    ) noexcept ( noexcept ( ( * Type < Predicate > :: unsafeAddress () ) ( Type < ElementType > :: unsafeReference() ) ) )
            -> bool __CDS_Requires( IsPredicateOver < Predicate COMMA T > ) {

        return this->atLeast ( count, predicate );
    }

    template < typename Predicate = Function < bool ( ElementCRef ) > >
    __CDS_MaybeUnused __CDS_OptimalInline auto moreThan (
            Size                count,
            Predicate   const & predicate = []( ElementCRef ) noexcept -> bool { return true; }
    ) const noexcept ( noexcept ( ( * Type < Predicate > :: unsafeAddress () ) ( Type < ElementType const > :: unsafeReference() ) ) )
            -> bool __CDS_Requires( IsPredicateOver < Predicate COMMA T > ) {

        return this->atLeast ( count, predicate );
    }

    template < typename Predicate = Function < bool ( ElementCRef ) > >
    __CDS_MaybeUnused __CDS_OptimalInline auto lessThan (
            Size                count,
            Predicate   const & predicate = []( ElementCRef ) noexcept -> bool { return true; }
    ) noexcept ( noexcept ( ( * Type < Predicate > :: unsafeAddress () ) ( Type < ElementType > :: unsafeReference() ) ) )
            -> bool __CDS_Requires( IsPredicateOver < Predicate COMMA T > ) {

        return this->lessThan ( count, predicate );
    }

    template < typename Predicate = Function < bool ( ElementCRef ) > >
    __CDS_MaybeUnused __CDS_OptimalInline auto lessThan (
            Size                count,
            Predicate   const & predicate = []( ElementCRef ) noexcept -> bool { return true; }
    ) const noexcept ( noexcept ( ( * Type < Predicate > :: unsafeAddress () ) ( Type < ElementType const > :: unsafeReference() ) ) )
            -> bool __CDS_Requires( IsPredicateOver < Predicate COMMA T > ) {

        return this->lessThan ( count, predicate );
    }

    template < typename Predicate = Function < bool ( ElementCRef ) > >
    __CDS_MaybeUnused auto count (
            Predicate const & = []( ElementCRef ) noexcept -> bool { return true; }
    ) noexcept ( noexcept ( ( * Type < Predicate > :: unsafeAddress () ) ( Type < ElementType > :: unsafeReference() ) ) )
            -> Size __CDS_Requires( IsPredicateOver < Predicate COMMA T > );

    template < typename Predicate = Function < bool ( ElementCRef ) > >
    __CDS_MaybeUnused auto count (
            Predicate const & = []( ElementCRef ) noexcept -> bool { return true; }
    ) const noexcept ( noexcept ( ( * Type < Predicate > :: unsafeAddress () ) ( Type < ElementType const > :: unsafeReference() ) ) )
            -> Size __CDS_Requires( IsPredicateOver < Predicate COMMA T > );

    template < typename Predicate = Function < bool ( ElementCRef ) > >
    __CDS_MaybeUnused __CDS_OptimalInline auto any (
            Predicate const & p = []( ElementCRef ) noexcept -> bool { return true; }
    ) noexcept ( noexcept ( ( * Type < Predicate > :: unsafeAddress () ) ( Type < ElementType > :: unsafeReference() ) ) )
            -> bool __CDS_Requires( IsPredicateOver < Predicate COMMA T > ) {

        return this->atLeast ( 1, p );
    }

    template < typename Predicate = Function < bool ( ElementCRef ) > >
    __CDS_MaybeUnused __CDS_OptimalInline auto any (
            Predicate const & p = []( ElementCRef ) noexcept -> bool { return true; }
    ) const noexcept ( noexcept ( ( * Type < Predicate > :: unsafeAddress () ) ( Type < ElementType const > :: unsafeReference() ) ) )
            -> bool __CDS_Requires( IsPredicateOver < Predicate COMMA T > ) {

        return this->atLeast ( 1, p );
    }

    template < typename Predicate >
    __CDS_MaybeUnused __CDS_OptimalInline auto all (
            Predicate const & p
    ) noexcept ( noexcept ( ( * Type < Predicate > :: unsafeAddress () ) ( Type < ElementType > :: unsafeReference() ) ) )
            -> bool __CDS_Requires( IsPredicateOver < Predicate COMMA T > ) {

        return ! this->any ( [&p] (T & e) noexcept -> bool { return ! p(e); } );
    }

    template < typename Predicate >
    __CDS_MaybeUnused __CDS_OptimalInline auto all (
            Predicate const & p
    ) const noexcept ( noexcept ( ( * Type < Predicate > :: unsafeAddress () ) ( Type < ElementType const > :: unsafeReference() ) ) )
            -> bool __CDS_Requires( IsPredicateOver < Predicate COMMA T > ) {

        return ! this->any ( [&p] ( ElementCRef e) noexcept -> bool { return ! p(e); } );
    }

#undef COMMA

    __CDS_OptimalInline virtual COLLECTION_EXPLICIT_CONVERSION operator bool () const noexcept { // NOLINT(google-explicit-constructor)
        return this->size() != 0;
    }

    __CDS_NoDiscard auto toString () const noexcept -> String override = 0;

    __CDS_cpplang_ConstexprDestructor ~Collection() noexcept override = default;

    __CDS_OptimalInline friend auto operator << ( std::ostream & o, const Collection & c ) noexcept -> std::ostream & {
         return ( o << c.toString() );
    }

    __CDS_NoDiscard __CDS_MaybeUnused __CDS_cpplang_ConstexprPureAbstract virtual auto empty () const noexcept -> bool = 0;
};

#define COMMA ,

template < typename T >
template < typename Action >
auto Collection<T>::forEach (
        Action const & a
) noexcept ( noexcept ( ( * Type < Action > :: unsafeAddress() ) ( Type < ElementType > :: unsafeReference() ) ) )
        -> void __CDS_Requires( IsActionOver < Action COMMA T > ) {

    __CDS_Collection_OperationalLock

    for (
        auto
            it = UniquePointer < Collection :: Iterator > ( this->beginPtr() ),
            end = UniquePointer < Collection :: Iterator > ( this->endPtr() );
        ! it->equals( * end );
        it->next()
    )
        a ( it->value() );

    __CDS_Collection_OperationalUnlock

}

template < typename T >
template < typename Action >
auto Collection<T>::forEach (
        Action const & a
) const noexcept ( noexcept ( ( * Type < Action > :: unsafeAddress () ) ( Type < ElementType const > :: unsafeReference() ) ) )
        -> void __CDS_Requires( IsActionOver < Action COMMA T > ) {

    __CDS_Collection_OperationalLock

    for (
        auto
            it = UniquePointer < Collection :: ConstIterator > ( this->beginPtr() ),
            end = UniquePointer < Collection :: ConstIterator > ( this->endPtr() );
        ! it->equals( * end );
        it->next()
    )
        a ( it->value() );

    __CDS_Collection_OperationalUnlock

}

template < typename T >
template < typename Predicate >
auto Collection<T>::count (
        Predicate const & p
) noexcept ( noexcept ( ( * Type < Predicate > :: unsafeAddress () ) ( Type < ElementType > :: unsafeReference() ) ) )
        -> Size __CDS_Requires( IsPredicateOver < Predicate COMMA T > ) {

    Size trueCount = 0;

    __CDS_Collection_OperationalLock

    for (
        auto
            it = UniquePointer < Collection :: Iterator > ( this->beginPtr() ),
            end = UniquePointer < Collection :: Iterator > ( this->endPtr() );
        ! it->equals( * end );
        it->next()
    )
        if ( p ( it->value() ) )
            trueCount ++;

    __CDS_Collection_OperationalUnlock

    return trueCount;
}

template < typename T >
template < typename Predicate >
auto Collection<T>::count (
        Predicate const & p
) const noexcept ( noexcept ( ( * Type < Predicate > :: unsafeAddress () ) ( Type < ElementType const > :: unsafeReference() ) ) )
        -> Size __CDS_Requires( IsPredicateOver < Predicate COMMA T > ) {

    Size trueCount = 0;

    __CDS_Collection_OperationalLock

    for (
        auto
            it = UniquePointer < Collection :: ConstIterator > ( this->beginPtr() ),
            end = UniquePointer < Collection :: ConstIterator > ( this->endPtr() );
        ! it->equals( * end );
        it->next()
    )
        if ( p ( it->value() ) )
            trueCount ++;

    __CDS_Collection_OperationalUnlock

    return trueCount;
}

#undef COMMA

__CDS_RegisterParseTypeTemplateT(Collection)

#endif //CDS_COLLECTION_HPP
