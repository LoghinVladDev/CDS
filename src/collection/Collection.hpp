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

    class DelegateIterator : public Object {
    protected:
        DelegateIterator () noexcept = default;

    public:
        virtual auto next () noexcept -> DelegateIterator & = 0;
        virtual auto previous () noexcept -> DelegateIterator & {
            return * this;
        }

        virtual auto value () const noexcept -> ElementRef = 0;
        virtual auto equals ( DelegateIterator const & ) const noexcept -> bool = 0;

        __CDS_NoDiscard virtual auto isValid () const noexcept -> bool {
            return true;
        }

        auto copy () const noexcept -> DelegateIterator * override = 0;

        ~DelegateIterator () noexcept override = default;
    };

    class DelegateConstIterator : public Object {
    protected:
        DelegateConstIterator () noexcept = default;

    public:
        virtual auto next () noexcept -> DelegateConstIterator & = 0;
        virtual auto previous () noexcept -> DelegateConstIterator & {
            return * this;
        }

        virtual auto value () const noexcept -> ElementCRef = 0;
        virtual auto equals ( DelegateConstIterator const & ) const noexcept -> bool = 0;

        __CDS_NoDiscard virtual auto isValid () const noexcept -> bool {
            return true;
        }

        auto copy () const noexcept -> DelegateConstIterator * override = 0;

        ~DelegateConstIterator () noexcept override = default;
    };

    class AbstractIterator : public Object {
    protected:
        ForeignPointer < Collection const > pCollection { nullptr };

        AbstractIterator () noexcept = default;
        AbstractIterator ( AbstractIterator const & it ) noexcept :
                pCollection ( it.pCollection ) {

        }

        AbstractIterator ( AbstractIterator && ) noexcept = default;

    public:
        auto operator = ( AbstractIterator const & it ) noexcept -> AbstractIterator & = default;
        auto operator = ( AbstractIterator && ) noexcept -> AbstractIterator & = default;
        ~AbstractIterator() noexcept override = default;

        explicit AbstractIterator ( Collection const * pCollection ) noexcept :
                pCollection ( pCollection ) {

        }

        __CDS_NoDiscard auto of ( Collection const * pOtherCollection ) const noexcept -> bool {
            return this->pCollection->get() == pOtherCollection;
        }
    };

public:

    class Iterator : public AbstractIterator {
    private:
        UniquePointer < DelegateIterator > pDelegate { nullptr };

    public:
        Iterator () noexcept = default;
        Iterator ( Iterator && it ) noexcept = default;

        Iterator ( Iterator const & it ) noexcept :
                AbstractIterator ( it ),
                pDelegate ( it.pDelegate->copy() ) {

        }

        explicit Iterator ( Collection const * pCollection, UniquePointer < DelegateIterator > && pMoveDelegate ) noexcept :
                AbstractIterator ( pCollection ),
                pDelegate ( std :: forward < UniquePointer < DelegateIterator > > ( pMoveDelegate ) ) {

        }

        ~Iterator () noexcept override = default;

        auto operator = ( Iterator const & it ) noexcept -> Iterator & {
            if ( this == & it ) return * this;

            this->pDelegate = it.pDelegate->copy();
            this->pCollection = it.pCollection;
            return * this;
        }

        auto operator = ( Iterator && it ) noexcept -> Iterator & = default;

        auto operator ++ () noexcept -> Iterator & {
            this->pDelegate->next();
            return * this;
        }

        auto operator ++ (int) noexcept -> Iterator {
            auto copy (*this);
            this->pDelegate->next();
            return copy;
        }

        auto operator -- () noexcept -> Iterator & {
            this->pDelegate->previous();
            return * this;
        }

        auto operator -- (int) noexcept -> Iterator {
            auto copy (*this);
            this->pDelegate->previous();
            return copy;
        }

        __CDS_NoDiscard auto isValid () const noexcept -> bool {
            return ! this->pDelegate.isNull() && this->pDelegate->isValid();
        }

        auto operator == ( Iterator const & it ) const noexcept -> bool {
            if ( this == & it ) return true;
            return this->pCollection == it.pCollection && this->pDelegate->equals( * it.pDelegate );
        }

        auto operator != ( Iterator const & it ) const noexcept -> bool {
            if ( this == & it ) return false;
            return this->pCollection != it.pCollection || ! this->pDelegate->equals ( * it.pDelegate );
        }

        auto operator * () const noexcept -> ElementRef {
            return this->pDelegate->value();
        }
    };

    class ConstIterator : public AbstractIterator {
    private:
        UniquePointer < DelegateConstIterator > pDelegate { nullptr };

    public:
        ConstIterator () noexcept = default;
        ConstIterator ( ConstIterator && it ) noexcept = default;

        ConstIterator ( ConstIterator const & it ) noexcept :
                AbstractIterator ( it ),
                pDelegate ( it.pDelegate->copy() ) {

        }

        explicit ConstIterator ( Collection const * pCollection, UniquePointer < DelegateConstIterator > && pMoveDelegate ) noexcept :
                AbstractIterator ( pCollection ),
                pDelegate ( std :: forward < UniquePointer < DelegateConstIterator > > ( pMoveDelegate ) ) {

        }

        ~ConstIterator () noexcept override = default;

        auto operator = ( ConstIterator const & it ) noexcept -> ConstIterator & {
            if ( this == & it ) return * this;

            this->pDelegate = it.pDelegate->copy();
            this->pCollection = it.pCollection;
            return * this;
        }

        auto operator = ( ConstIterator && it ) noexcept -> ConstIterator & = default;

        auto operator ++ () noexcept -> ConstIterator & {
            this->pDelegate->next();
            return * this;
        }

        auto operator ++ (int) noexcept -> ConstIterator {
            auto copy (*this);
            this->pDelegate->next();
            return copy;
        }

        auto operator -- () noexcept -> ConstIterator & {
            this->pDelegate->previous();
            return * this;
        }

        auto operator -- (int) noexcept -> ConstIterator {
            auto copy (*this);
            this->pDelegate->previous();
            return copy;
        }

        __CDS_NoDiscard auto isValid () const noexcept -> bool {
            return ! this->pDelegate.isNull() && this->pDelegate->isValid();
        }

        auto operator == ( ConstIterator const & it ) const noexcept -> bool {
            if ( this == & it ) return true;
            return this->pCollection == it.pCollection && this->pDelegate->equals( * it.pDelegate );
        }

        auto operator != ( ConstIterator const & it ) const noexcept -> bool {
            if ( this == & it ) return false;
            return this->pCollection != it.pCollection || ! this->pDelegate->equals ( * it.pDelegate );
        }

        auto operator * () const noexcept -> ElementCRef {
            return this->pDelegate->value();
        }
    };

    class ReverseIterator : public AbstractIterator {
    private:
        UniquePointer < DelegateIterator > pDelegate { nullptr };

    public:
        ReverseIterator () noexcept = default;
        ReverseIterator ( ReverseIterator && it ) noexcept = default;

        ReverseIterator ( ReverseIterator const & it ) noexcept :
                AbstractIterator ( it ),
                pDelegate ( it.pDelegate->copy() ) {

        }

        explicit ReverseIterator ( Collection const * pCollection, UniquePointer < DelegateIterator > && pMoveDelegate ) noexcept :
                AbstractIterator ( pCollection ),
                pDelegate ( std :: forward < UniquePointer < DelegateIterator > > ( pMoveDelegate ) ){

        }

        ~ReverseIterator () noexcept override = default;

        auto operator = ( ReverseIterator const & it ) noexcept -> ReverseIterator & {
            if ( this == & it ) return * this;

            this->pDelegate = it.pDelegate->copy();
            this->pCollection = it.pCollection;
            return * this;
        }

        auto operator = ( ReverseIterator && it ) noexcept -> ReverseIterator & = default;

        auto operator ++ () noexcept -> ReverseIterator & {
            this->pDelegate->next();
            return * this;
        }

        auto operator ++ (int) noexcept -> ReverseIterator {
            auto copy (*this);
            this->pDelegate->next();
            return copy;
        }

        auto operator -- () noexcept -> ReverseIterator & {
            this->pDelegate->previous();
            return * this;
        }

        auto operator -- (int) noexcept -> ReverseIterator {
            auto copy (*this);
            this->pDelegate->previous();
            return copy;
        }

        __CDS_NoDiscard auto isValid () const noexcept -> bool {
            return ! this->pDelegate.isNull() && this->pDelegate->isValid();
        }

        auto operator == ( ReverseIterator const & it ) const noexcept -> bool {
            if ( this == & it ) return true;
            return this->pCollection == it.pCollection && this->pDelegate->equals( * it.pDelegate );
        }

        auto operator != ( ReverseIterator const & it ) const noexcept -> bool {
            if ( this == & it ) return false;
            return this->pCollection != it.pCollection || ! this->pDelegate->equals ( * it.pDelegate );
        }

        auto operator * () const noexcept -> ElementRef {
            return this->pDelegate->value();
        }
    };

    class ConstReverseIterator : public AbstractIterator {
    private:
        UniquePointer < DelegateConstIterator > pDelegate { nullptr };

    public:
        ConstReverseIterator () noexcept = default;
        ConstReverseIterator ( ConstReverseIterator && it ) noexcept = default;

        ConstReverseIterator ( ConstReverseIterator const & it ) noexcept :
                AbstractIterator ( it ),
                pDelegate ( it.pDelegate->copy() ) {

        }

        explicit ConstReverseIterator ( Collection const * pCollection, UniquePointer < DelegateConstIterator > && pMoveDelegate ) noexcept :
                AbstractIterator ( pCollection ),
                pDelegate ( std :: forward < UniquePointer < DelegateConstIterator > > ( pMoveDelegate ) ){

        }

        ~ConstReverseIterator () noexcept override = default;

        auto operator = ( ConstReverseIterator const & it ) noexcept -> ConstReverseIterator & {
            if ( this == & it ) return * this;

            this->pDelegate = it.pDelegate->copy();
            this->pCollection = it.pCollection;
            return * this;
        }

        auto operator = ( ConstReverseIterator && it ) noexcept -> ConstReverseIterator & = default;

        auto operator ++ () noexcept -> ConstReverseIterator & {
            this->pDelegate->next();
            return * this;
        }

        auto operator ++ (int) noexcept -> ConstReverseIterator {
            auto copy (*this);
            this->pDelegate->next();
            return copy;
        }

        auto operator -- () noexcept -> ConstReverseIterator & {
            this->pDelegate->previous();
            return * this;
        }

        auto operator -- (int) noexcept -> ConstReverseIterator {
            auto copy (*this);
            this->pDelegate->previous();
            return copy;
        }

        __CDS_NoDiscard auto isValid () const noexcept -> bool {
            return ! this->pDelegate.isNull() && this->pDelegate->isValid();
        }

        auto operator == ( ConstReverseIterator const & it ) const noexcept -> bool {
            if ( this == & it ) return true;
            return this->pCollection == it.pCollection && this->pDelegate->equals( * it.pDelegate );
        }

        auto operator != ( ConstReverseIterator const & it ) const noexcept -> bool {
            if ( this == & it ) return false;
            return this->pCollection != it.pCollection || ! this->pDelegate->equals ( * it.pDelegate );
        }

        auto operator * () const noexcept -> ElementCRef {
            return this->pDelegate->value();
        }
    };

protected:
    enum class DelegateIteratorRequestType {
        FORWARD_BEGIN,
        FORWARD_END,
        BACKWARD_BEGIN,
        BACKWARD_END
    };

    virtual auto delegateIterator ( DelegateIteratorRequestType ) noexcept -> UniquePointer < DelegateIterator > {
        return nullptr;
    }

    virtual auto delegateConstIterator ( DelegateIteratorRequestType ) const noexcept -> UniquePointer < DelegateConstIterator > {
        return nullptr;
    }

#if defined(__CDS_ThreadSafeObjects)
    Mutex mutable multithreadingProtection;
#endif

public:
    __CDS_NoDiscard __CDS_MaybeUnused __CDS_OptimalInline auto begin () noexcept (false) -> Iterator {
        auto pDelegate = this->delegateIterator( DelegateIteratorRequestType :: FORWARD_BEGIN );
        if ( pDelegate.isNull() )
            throw NotImplementedException ( "Iterator" );

        return Iterator ( this, std :: move ( pDelegate ) );
    }

    __CDS_NoDiscard __CDS_MaybeUnused __CDS_OptimalInline auto end () noexcept (false) -> Iterator {
        auto pDelegate = this->delegateIterator( DelegateIteratorRequestType :: FORWARD_END );
        if ( pDelegate.isNull() )
            throw NotImplementedException ( "Iterator" );

        return Iterator ( this, std :: move ( pDelegate ) );
    }

    __CDS_NoDiscard __CDS_MaybeUnused __CDS_OptimalInline auto cbegin () const noexcept (false) -> ConstIterator {
        auto pDelegate = this->delegateConstIterator( DelegateIteratorRequestType :: FORWARD_BEGIN );
        if ( pDelegate.isNull() )
            throw NotImplementedException ( "ConstIterator" );

        return ConstIterator ( this, std :: move ( pDelegate ) );
    }

    __CDS_NoDiscard __CDS_MaybeUnused __CDS_OptimalInline auto cend () const noexcept (false) -> ConstIterator {
        auto pDelegate = this->delegateConstIterator( DelegateIteratorRequestType :: FORWARD_END );
        if ( pDelegate.isNull() )
            throw NotImplementedException ( "ConstIterator" );

        return ConstIterator ( this, std :: move ( pDelegate ) );
    }

    __CDS_NoDiscard __CDS_MaybeUnused __CDS_OptimalInline auto begin () const noexcept (false) -> ConstIterator {
        return this->cbegin();
    }

    __CDS_NoDiscard __CDS_MaybeUnused __CDS_OptimalInline auto end () const noexcept (false) -> ConstIterator {
        return this->cend();
    }

    __CDS_NoDiscard __CDS_MaybeUnused __CDS_OptimalInline auto rbegin () noexcept (false) -> ReverseIterator {
        auto pDelegate = this->delegateIterator( DelegateIteratorRequestType :: BACKWARD_BEGIN );
        if ( pDelegate.isNull() )
            throw NotImplementedException ( "ReverseIterator" );

        return ReverseIterator ( this, std :: move ( pDelegate ) );
    }

    __CDS_NoDiscard __CDS_MaybeUnused __CDS_OptimalInline auto rend () noexcept (false) -> ReverseIterator {
        auto pDelegate = this->delegateIterator( DelegateIteratorRequestType :: BACKWARD_END );
        if ( pDelegate.isNull() )
            throw NotImplementedException ( "ReverseIterator" );

        return ReverseIterator ( this, std :: move ( pDelegate ) );
    }

    __CDS_NoDiscard __CDS_MaybeUnused __CDS_OptimalInline auto crbegin () const noexcept (false) -> ConstReverseIterator {
        auto pDelegate = this->delegateConstIterator( DelegateIteratorRequestType :: BACKWARD_BEGIN );
        if ( pDelegate.isNull() )
            throw NotImplementedException ( "ConstReverseIterator" );

        return ConstReverseIterator ( this, std :: move ( pDelegate ) );
    }

    __CDS_NoDiscard __CDS_MaybeUnused __CDS_OptimalInline auto crend () const noexcept (false) -> ConstReverseIterator {
        auto pDelegate = this->delegateConstIterator( DelegateIteratorRequestType :: BACKWARD_END );
        if ( pDelegate.isNull() )
            throw NotImplementedException ( "ConstReverseIterator" );

        return ConstReverseIterator ( this, std :: move ( pDelegate ) );
    }

    __CDS_NoDiscard __CDS_MaybeUnused __CDS_OptimalInline auto rbegin () const noexcept (false) -> ConstReverseIterator {
        return this->crbegin();
    }

    __CDS_NoDiscard __CDS_MaybeUnused __CDS_OptimalInline auto rend () const noexcept (false) -> ConstReverseIterator {
        return this->crend();
    }

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

        for ( auto const & i : * this )
            if ( Type < ElementType > :: compare ( i, e ) ) {

                __CDS_Collection_OperationalUnlock
                return true;

            }

        __CDS_Collection_OperationalUnlock
        return false;
    }

    template < typename Action >
    __CDS_MaybeUnused auto forEach (
            Action const & action
    ) noexcept ( noexcept ( ( * Type < Action > :: unsafeAddress () ) ( Type < ElementType > :: unsafeReference() ) ) )
            -> void __CDS_Requires ( ActionOver < Action, T > ) {

        __CDS_Collection_OperationalLock

        for ( auto & it : * this )
            action ( it );

        __CDS_Collection_OperationalUnlock

    }

    template < typename Action >
    __CDS_MaybeUnused auto forEach (
            Action const & action
    ) const noexcept ( noexcept ( ( * Type < Action > :: unsafeAddress () ) ( Type < ElementType const > :: unsafeReference() ) ) )
            -> void __CDS_Requires ( ActionOver < Action, T > ) {

        __CDS_Collection_OperationalLock

        for ( auto const & it : * this )
            action ( it );

        __CDS_Collection_OperationalUnlock

    }

    template < typename Predicate = Function < bool ( ElementCRef ) > >
    __CDS_MaybeUnused __CDS_OptimalInline auto some (
            Size                count,
            Predicate   const & predicate = []( ElementCRef ) noexcept -> bool { return true; }
    ) noexcept ( noexcept ( ( * Type < Predicate > :: unsafeAddress () ) ( Type < ElementType > :: unsafeReference() ) ) )
            -> bool __CDS_Requires( PredicateOver < Predicate, T > ) {

        return this->count(predicate) == count;
    }

    template < typename Predicate = Function < bool ( ElementCRef ) > >
    __CDS_MaybeUnused __CDS_OptimalInline auto some (
            Size                count,
            Predicate   const & predicate = []( ElementCRef ) noexcept -> bool { return true; }
    ) const noexcept ( noexcept ( ( * Type < Predicate > :: unsafeAddress () ) ( Type < ElementType const > :: unsafeReference() ) ) )
            -> bool __CDS_Requires( PredicateOver < Predicate, T > ) {

        return this->count(predicate) == count;
    }

    template < typename Predicate = Function < bool ( ElementCRef ) > >
    __CDS_MaybeUnused __CDS_OptimalInline auto atLeast (
            Size                count,
            Predicate   const & predicate = []( ElementCRef ) noexcept -> bool { return true; }
    ) noexcept ( noexcept ( ( * Type < Predicate > :: unsafeAddress () ) ( Type < ElementType > :: unsafeReference() ) ) )
            -> bool __CDS_Requires( PredicateOver < Predicate, T > ) {

        return this->count(predicate) >= count;
    }

    template < typename Predicate = Function < bool ( ElementCRef ) > >
    __CDS_MaybeUnused __CDS_OptimalInline auto atLeast (
            Size                count,
            Predicate   const & predicate = []( ElementCRef ) noexcept -> bool { return true; }
    ) const noexcept ( noexcept ( ( * Type < Predicate > :: unsafeAddress () ) ( Type < ElementType const > :: unsafeReference() ) ) )
            -> bool __CDS_Requires( PredicateOver < Predicate, T > ) {

        return this->count(predicate) >= count;
    }

    template < typename Predicate = Function < bool ( ElementCRef ) > >
    __CDS_MaybeUnused __CDS_OptimalInline auto atMost (
            Size                count,
            Predicate   const & predicate = []( ElementCRef ) noexcept -> bool { return true; }
    ) noexcept ( noexcept ( ( * Type < Predicate > :: unsafeAddress () ) ( Type < ElementType > :: unsafeReference() ) ) )
            -> bool __CDS_Requires( PredicateOver < Predicate, T > ) {

        return this->count(predicate) <= count;
    }

    template < typename Predicate = Function < bool ( ElementCRef ) > >
    __CDS_MaybeUnused __CDS_OptimalInline auto atMost (
            Size count,
            Predicate const & predicate = []( ElementCRef ) noexcept -> bool { return true; }
    ) const noexcept ( noexcept ( ( * Type < Predicate > :: unsafeAddress () ) ( Type < ElementType const > :: unsafeReference() ) ) )
            -> bool __CDS_Requires( PredicateOver < Predicate, T > ) {

        return this->count(predicate) <= count;
    }

    template < typename Predicate = Function < bool ( ElementCRef ) > >
    __CDS_MaybeUnused __CDS_OptimalInline auto moreThan (
            Size                count,
            Predicate   const & predicate = []( ElementCRef ) noexcept -> bool { return true; }
    ) noexcept ( noexcept ( ( * Type < Predicate > :: unsafeAddress () ) ( Type < ElementType > :: unsafeReference() ) ) )
            -> bool __CDS_Requires( PredicateOver < Predicate, T > ) {

        return this->atLeast ( count, predicate );
    }

    template < typename Predicate = Function < bool ( ElementCRef ) > >
    __CDS_MaybeUnused __CDS_OptimalInline auto moreThan (
            Size                count,
            Predicate   const & predicate = []( ElementCRef ) noexcept -> bool { return true; }
    ) const noexcept ( noexcept ( ( * Type < Predicate > :: unsafeAddress () ) ( Type < ElementType const > :: unsafeReference() ) ) )
            -> bool __CDS_Requires( PredicateOver < Predicate, T > ) {

        return this->atLeast ( count, predicate );
    }

    template < typename Predicate = Function < bool ( ElementCRef ) > >
    __CDS_MaybeUnused __CDS_OptimalInline auto lessThan (
            Size                count,
            Predicate   const & predicate = []( ElementCRef ) noexcept -> bool { return true; }
    ) noexcept ( noexcept ( ( * Type < Predicate > :: unsafeAddress () ) ( Type < ElementType > :: unsafeReference() ) ) )
            -> bool __CDS_Requires( PredicateOver < Predicate, T > ) {

        return this->lessThan ( count, predicate );
    }

    template < typename Predicate = Function < bool ( ElementCRef ) > >
    __CDS_MaybeUnused __CDS_OptimalInline auto lessThan (
            Size                count,
            Predicate   const & predicate = []( ElementCRef ) noexcept -> bool { return true; }
    ) const noexcept ( noexcept ( ( * Type < Predicate > :: unsafeAddress () ) ( Type < ElementType const > :: unsafeReference() ) ) )
            -> bool __CDS_Requires( PredicateOver < Predicate, T > ) {

        return this->lessThan ( count, predicate );
    }

    template < typename Predicate = Function < bool ( ElementCRef ) > >
    __CDS_MaybeUnused auto count (
            Predicate const & predicate = []( ElementCRef ) noexcept -> bool { return true; }
    ) noexcept ( noexcept ( ( * Type < Predicate > :: unsafeAddress () ) ( Type < ElementType > :: unsafeReference() ) ) )
            -> Size __CDS_Requires( PredicateOver < Predicate, T > )  {

        Size trueCount = 0;

        __CDS_Collection_OperationalLock

        for ( auto & it : * this )
            if ( predicate ( it ) )
                trueCount ++;

        __CDS_Collection_OperationalUnlock

        return trueCount;
    }

    template < typename Predicate = Function < bool ( ElementCRef ) > >
    __CDS_MaybeUnused auto count (
            Predicate const & predicate = []( ElementCRef ) noexcept -> bool { return true; }
    ) const noexcept ( noexcept ( ( * Type < Predicate > :: unsafeAddress () ) ( Type < ElementType const > :: unsafeReference() ) ) )
            -> Size __CDS_Requires( PredicateOver < Predicate, T > ) {

        Size trueCount = 0;

        __CDS_Collection_OperationalLock

        for ( auto const & it : * this )
            if ( predicate ( it ) )
                trueCount ++;

        __CDS_Collection_OperationalUnlock

        return trueCount;
    }

    template < typename Predicate = Function < bool ( ElementCRef ) > >
    __CDS_MaybeUnused __CDS_OptimalInline auto any (
            Predicate const & p = []( ElementCRef ) noexcept -> bool { return true; }
    ) noexcept ( noexcept ( ( * Type < Predicate > :: unsafeAddress () ) ( Type < ElementType > :: unsafeReference() ) ) )
            -> bool __CDS_Requires( PredicateOver < Predicate, T > ) {

        return this->atLeast ( 1, p );
    }

    template < typename Predicate = Function < bool ( ElementCRef ) > >
    __CDS_MaybeUnused __CDS_OptimalInline auto any (
            Predicate const & p = []( ElementCRef ) noexcept -> bool { return true; }
    ) const noexcept ( noexcept ( ( * Type < Predicate > :: unsafeAddress () ) ( Type < ElementType const > :: unsafeReference() ) ) )
            -> bool __CDS_Requires( PredicateOver < Predicate, T > ) {

        return this->atLeast ( 1, p );
    }

    template < typename Predicate >
    __CDS_MaybeUnused __CDS_OptimalInline auto all (
            Predicate const & p
    ) noexcept ( noexcept ( ( * Type < Predicate > :: unsafeAddress () ) ( Type < ElementType > :: unsafeReference() ) ) )
            -> bool __CDS_Requires( PredicateOver < Predicate, T > ) {

        return ! this->any ( [&p] (T & e) noexcept -> bool { return ! p(e); } );
    }

    template < typename Predicate >
    __CDS_MaybeUnused __CDS_OptimalInline auto all (
            Predicate const & p
    ) const noexcept ( noexcept ( ( * Type < Predicate > :: unsafeAddress () ) ( Type < ElementType const > :: unsafeReference() ) ) )
            -> bool __CDS_Requires( PredicateOver < Predicate, T > ) {

        return ! this->any ( [&p] ( ElementCRef e) noexcept -> bool { return ! p(e); } );
    }

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

__CDS_RegisterParseTypeTemplateT(Collection)

#endif //CDS_COLLECTION_HPP
