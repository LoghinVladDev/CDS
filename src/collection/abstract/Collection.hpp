//
// Created by loghin on 15.01.2021.
//

#ifndef CDS_COLLECTION_HPP
#define CDS_COLLECTION_HPP

#ifdef COLLECTION_FORCE_EXPLICIT_CONVERSIONS
#ifndef COLLECTION_EXPLICIT_CONVERSION
#define COLLECTION_EXPLICIT_CONVERSION explicit
#endif
#else
#ifndef COLLECTION_EXPLICIT_CONVERSION
#define COLLECTION_EXPLICIT_CONVERSION
#endif
#endif

#include <CDS/std-types>
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

#include <type_traits>
#include <CDS/Object>

#include <CDS/Traits>
#include <CDS/Concepts>
#include <CDS/Comparator>

namespace cds {

    template < typename C >
    class Sequence;

}

namespace cds {

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
            constexpr DelegateIterator () noexcept = default;

        public:
            __CDS_cpplang_ConstexprPureAbstract virtual auto next () noexcept -> DelegateIterator & = 0;
            __CDS_cpplang_VirtualConstexpr virtual auto previous () noexcept -> DelegateIterator & {
                return * this;
            }

            __CDS_cpplang_ConstexprPureAbstract virtual auto value () const noexcept -> ElementRef = 0;
            __CDS_cpplang_ConstexprPureAbstract virtual auto equals ( DelegateIterator const & ) const noexcept -> bool = 0;

            __CDS_NoDiscard __CDS_cpplang_VirtualConstexpr virtual auto isValid () const noexcept -> bool {
                return true;
            }

            auto copy () const noexcept -> DelegateIterator * override = 0;

            __CDS_cpplang_ConstexprDestructor ~DelegateIterator () noexcept override = default;
        };

        class DelegateConstIterator : public Object {
        protected:
            constexpr DelegateConstIterator () noexcept = default;

        public:
            __CDS_cpplang_ConstexprPureAbstract virtual auto next () noexcept -> DelegateConstIterator & = 0;
            __CDS_cpplang_VirtualConstexpr virtual auto previous () noexcept -> DelegateConstIterator & {
                return * this;
            }

            __CDS_cpplang_ConstexprPureAbstract virtual auto value () const noexcept -> ElementCRef = 0;
            __CDS_cpplang_ConstexprPureAbstract virtual auto equals ( DelegateConstIterator const & ) const noexcept -> bool = 0;

            __CDS_NoDiscard __CDS_cpplang_VirtualConstexpr virtual auto isValid () const noexcept -> bool {
                return true;
            }

            auto copy () const noexcept -> DelegateConstIterator * override = 0;

            __CDS_cpplang_ConstexprDestructor ~DelegateConstIterator () noexcept override = default;
        };

        class AbstractIterator : public Object {
        protected:
            ForeignPointer < Collection const > pCollection { nullptr }; // NOLINT(clion-misra-cpp2008-11-0-1)

            constexpr AbstractIterator () noexcept = default;
            constexpr AbstractIterator ( AbstractIterator const & iterator ) noexcept :
                    pCollection (iterator.pCollection ) {

            }

            constexpr AbstractIterator ( AbstractIterator && ) noexcept = default;

        public:
            __CDS_cpplang_NonConstConstexprMemberFunction auto operator = ( AbstractIterator const & iterator ) noexcept -> AbstractIterator & = default;
            __CDS_cpplang_NonConstConstexprMemberFunction auto operator = ( AbstractIterator && ) noexcept -> AbstractIterator & = default;
            __CDS_cpplang_ConstexprDestructor ~AbstractIterator() noexcept override = default;

            constexpr explicit AbstractIterator ( Collection const * pCollection ) noexcept :
                    pCollection ( pCollection ) {

            }

            __CDS_NoDiscard constexpr auto of ( Collection const * pOtherCollection ) const noexcept -> bool {
                return this->pCollection == pOtherCollection;
            }
        };

    public:

        class Iterator : public AbstractIterator { // NOLINT(cppcoreguidelines-virtual-class-destructor)
        private:
            friend class Collection;
            UniquePointer < DelegateIterator > pDelegate { nullptr };

        public:
            constexpr Iterator () noexcept = default;
            constexpr Iterator ( Iterator && iterator ) noexcept = default;

            __CDS_OptimalInline Iterator ( Iterator const & iterator ) noexcept :
                    AbstractIterator (iterator ),
                    pDelegate (iterator.pDelegate->copy() ) {

            }

            explicit constexpr Iterator ( Collection const * pCollection, UniquePointer < DelegateIterator > && pMoveDelegate ) noexcept :
                    AbstractIterator ( pCollection ),
                    pDelegate ( std :: forward < UniquePointer < DelegateIterator > > ( pMoveDelegate ) ) {

            }

            __CDS_cpplang_ConstexprDestructor ~Iterator () noexcept override = default;

            __CDS_OptimalInline auto operator = ( Iterator const & iterator ) noexcept -> Iterator & {
                if ( this == & iterator ) {
                    return *this;
                }

                this->pDelegate = iterator.pDelegate->copy();
                this->pCollection = iterator.pCollection;
                return * this;
            }

            __CDS_cpplang_NonConstConstexprMemberFunction auto operator = ( Iterator && iterator ) noexcept -> Iterator & = default;

            __CDS_cpplang_VirtualConstexpr auto operator ++ () noexcept -> Iterator & {
                this->pDelegate->next();
                return * this;
            }

            __CDS_cpplang_ConstexprDestructor auto operator ++ (int) noexcept -> Iterator {
                auto copy (*this);
                this->pDelegate->next();
                return copy;
            }

            __CDS_cpplang_VirtualConstexpr auto operator -- () noexcept -> Iterator & {
                this->pDelegate->previous();
                return * this;
            }

            __CDS_cpplang_ConstexprDestructor auto operator -- (int) noexcept -> Iterator {
                auto copy (*this);
                this->pDelegate->previous();
                return copy;
            }

            __CDS_NoDiscard __CDS_MaybeUnused __CDS_cpplang_VirtualConstexpr auto isValid () const noexcept -> bool {
                return
                        this->pDelegate != nullptr &&
                        this->pDelegate->isValid();
            }

            __CDS_cpplang_VirtualConstexpr auto operator == ( Iterator const & iterator ) const noexcept -> bool {
                if ( this == & iterator ) {
                    return true;
                }

                return
                        this->pCollection == iterator.pCollection &&
                        this->pDelegate->equals( * iterator.pDelegate );
            }

            __CDS_cpplang_VirtualConstexpr auto operator != ( Iterator const & iterator ) const noexcept -> bool {
                if ( this == & iterator ) {
                    return false;
                }

                return
                        this->pCollection != iterator.pCollection ||
                        ! this->pDelegate->equals ( * iterator.pDelegate ); // NOLINT(clion-misra-cpp2008-5-3-1)
            }

            __CDS_cpplang_VirtualConstexpr auto operator * () const noexcept -> ElementRef {
                return this->pDelegate->value();
            }

            __CDS_cpplang_VirtualConstexpr auto operator -> () const noexcept -> ElementPtr {
                return & ( * ( * this ) );
            }
        };

        class ConstIterator : public AbstractIterator { // NOLINT(cppcoreguidelines-virtual-class-destructor)
        private:
            friend class Collection;
            UniquePointer < DelegateConstIterator > pDelegate { nullptr };

        public:
            constexpr ConstIterator () noexcept = default;
            constexpr ConstIterator ( ConstIterator && iterator ) noexcept = default;

            __CDS_OptimalInline ConstIterator ( ConstIterator const & iterator ) noexcept :
                    AbstractIterator (iterator ),
                    pDelegate (iterator.pDelegate->copy() ) {

            }

            explicit constexpr ConstIterator ( Collection const * pCollection, UniquePointer < DelegateConstIterator > && pMoveDelegate ) noexcept :
                    AbstractIterator ( pCollection ),
                    pDelegate ( std :: forward < UniquePointer < DelegateConstIterator > > ( pMoveDelegate ) ) {

            }

            __CDS_cpplang_ConstexprDestructor ~ConstIterator () noexcept override = default;

             __CDS_OptimalInline auto operator = ( ConstIterator const & iterator ) noexcept -> ConstIterator & {
                if ( this == & iterator ) {
                    return *this;
                }

                this->pDelegate = iterator.pDelegate->copy();
                this->pCollection = iterator.pCollection;
                return * this;
            }

            __CDS_cpplang_NonConstConstexprMemberFunction auto operator = ( ConstIterator && iterator ) noexcept -> ConstIterator & = default;

            __CDS_cpplang_VirtualConstexpr auto operator ++ () noexcept -> ConstIterator & {
                this->pDelegate->next();
                return * this;
            }

            __CDS_cpplang_ConstexprDestructor auto operator ++ (int) noexcept -> ConstIterator {
                auto copy (*this);
                this->pDelegate->next();
                return copy;
            }

            __CDS_cpplang_VirtualConstexpr auto operator -- () noexcept -> ConstIterator & {
                this->pDelegate->previous();
                return * this;
            }

            __CDS_cpplang_ConstexprDestructor auto operator -- (int) noexcept -> ConstIterator {
                auto copy (*this);
                this->pDelegate->previous();
                return copy;
            }

            __CDS_NoDiscard __CDS_MaybeUnused __CDS_cpplang_VirtualConstexpr auto isValid () const noexcept -> bool {
                return
                        this->pDelegate != nullptr &&
                        this->pDelegate->isValid();
            }

            __CDS_cpplang_VirtualConstexpr auto operator == ( ConstIterator const & iterator ) const noexcept -> bool {
                if ( this == & iterator ) {
                    return true;
                }

                return
                        this->pCollection == iterator.pCollection &&
                        this->pDelegate->equals( * iterator.pDelegate );
            }

            __CDS_cpplang_VirtualConstexpr auto operator != ( ConstIterator const & iterator ) const noexcept -> bool {
                if ( this == & iterator ) {
                    return false;
                }

                return
                        this->pCollection != iterator.pCollection ||
                        ! this->pDelegate->equals ( * iterator.pDelegate ); // NOLINT(clion-misra-cpp2008-5-3-1)
            }

            __CDS_cpplang_VirtualConstexpr auto operator * () const noexcept -> ElementCRef {
                return this->pDelegate->value();
            }

            __CDS_cpplang_VirtualConstexpr auto operator -> () const noexcept -> ElementCPtr {
                return & ( * ( * this ) );
            }
        };

        class ReverseIterator : public AbstractIterator { // NOLINT(cppcoreguidelines-virtual-class-destructor)
        private:
            friend class Collection;
            UniquePointer < DelegateIterator > pDelegate { nullptr };

        public:
            constexpr ReverseIterator () noexcept = default;
            constexpr ReverseIterator ( ReverseIterator && iterator ) noexcept = default;

            __CDS_OptimalInline ReverseIterator ( ReverseIterator const & iterator ) noexcept :
                    AbstractIterator (iterator ),
                    pDelegate (iterator.pDelegate->copy() ) {

            }

            explicit constexpr ReverseIterator ( Collection const * pCollection, UniquePointer < DelegateIterator > && pMoveDelegate ) noexcept :
                    AbstractIterator ( pCollection ),
                    pDelegate ( std :: forward < UniquePointer < DelegateIterator > > ( pMoveDelegate ) ){

            }

            __CDS_cpplang_ConstexprDestructor ~ReverseIterator () noexcept override = default;

            __CDS_OptimalInline auto operator = ( ReverseIterator const & iterator ) noexcept -> ReverseIterator & {
                if ( this == & iterator ) {
                    return *this;
                }

                this->pDelegate = iterator.pDelegate->copy();
                this->pCollection = iterator.pCollection;
                return * this;
            }

            __CDS_cpplang_NonConstConstexprMemberFunction auto operator = ( ReverseIterator && iterator ) noexcept -> ReverseIterator & = default;

            __CDS_cpplang_VirtualConstexpr auto operator ++ () noexcept -> ReverseIterator & {
                this->pDelegate->next();
                return * this;
            }

            __CDS_cpplang_ConstexprDestructor auto operator ++ (int) noexcept -> ReverseIterator {
                auto copy (*this);
                this->pDelegate->next();
                return copy;
            }

            __CDS_cpplang_VirtualConstexpr auto operator -- () noexcept -> ReverseIterator & {
                this->pDelegate->previous();
                return * this;
            }

            __CDS_cpplang_ConstexprDestructor auto operator -- (int) noexcept -> ReverseIterator {
                auto copy (*this);
                this->pDelegate->previous();
                return copy;
            }

            __CDS_NoDiscard __CDS_MaybeUnused __CDS_cpplang_VirtualConstexpr auto isValid () const noexcept -> bool {
                return
                        this->pDelegate != nullptr &&
                        this->pDelegate->isValid();
            }

            __CDS_cpplang_VirtualConstexpr auto operator == ( ReverseIterator const & iterator ) const noexcept -> bool {
                if ( this == & iterator ) {
                    return true;
                }

                return
                        this->pCollection == iterator.pCollection &&
                        this->pDelegate->equals( * iterator.pDelegate );
            }

            __CDS_cpplang_VirtualConstexpr auto operator != ( ReverseIterator const & iterator ) const noexcept -> bool {
                if ( this == & iterator ) {
                    return false;
                }

                return
                        this->pCollection != iterator.pCollection ||
                        ! this->pDelegate->equals ( * iterator.pDelegate ); // NOLINT(clion-misra-cpp2008-5-3-1)
            }

            __CDS_cpplang_VirtualConstexpr auto operator * () const noexcept -> ElementRef {
                return this->pDelegate->value();
            }

            __CDS_cpplang_VirtualConstexpr auto operator -> () const noexcept -> ElementPtr {
                return & ( * ( * this ) );
            }
        };

        class ConstReverseIterator : public AbstractIterator { // NOLINT(cppcoreguidelines-virtual-class-destructor)
        private:
            friend class Collection;
            UniquePointer < DelegateConstIterator > pDelegate { nullptr };

        public:
            constexpr ConstReverseIterator () noexcept = default;
            constexpr ConstReverseIterator ( ConstReverseIterator && iterator ) noexcept = default;

            __CDS_OptimalInline ConstReverseIterator ( ConstReverseIterator const & iterator ) noexcept :
                    AbstractIterator (iterator ),
                    pDelegate (iterator.pDelegate->copy() ) {

            }

            explicit constexpr ConstReverseIterator ( Collection const * pCollection, UniquePointer < DelegateConstIterator > && pMoveDelegate ) noexcept :
                    AbstractIterator ( pCollection ),
                    pDelegate ( std :: forward < UniquePointer < DelegateConstIterator > > ( pMoveDelegate ) ){

            }

            __CDS_cpplang_ConstexprDestructor ~ConstReverseIterator () noexcept override = default;

            __CDS_OptimalInline auto operator = ( ConstReverseIterator const & iterator ) noexcept -> ConstReverseIterator & {
                if ( this == & iterator ) {
                    return * this;
                }

                this->pDelegate = iterator.pDelegate->copy();
                this->pCollection = iterator.pCollection;
                return * this;
            }

            __CDS_cpplang_NonConstConstexprMemberFunction auto operator = ( ConstReverseIterator && iterator ) noexcept -> ConstReverseIterator & = default;

            __CDS_cpplang_VirtualConstexpr auto operator ++ () noexcept -> ConstReverseIterator & {
                this->pDelegate->next();
                return * this;
            }

            __CDS_cpplang_ConstexprDestructor auto operator ++ (int) noexcept -> ConstReverseIterator {
                auto copy (*this);
                this->pDelegate->next();
                return copy;
            }

            __CDS_cpplang_VirtualConstexpr auto operator -- () noexcept -> ConstReverseIterator & {
                this->pDelegate->previous();
                return * this;
            }

            __CDS_cpplang_ConstexprDestructor auto operator -- (int) noexcept -> ConstReverseIterator {
                auto copy (*this);
                this->pDelegate->previous();
                return copy;
            }

            __CDS_NoDiscard __CDS_MaybeUnused __CDS_cpplang_VirtualConstexpr auto isValid () const noexcept -> bool {
                return this->pDelegate != nullptr && this->pDelegate->isValid();
            }

            __CDS_cpplang_VirtualConstexpr auto operator == ( ConstReverseIterator const & iterator ) const noexcept -> bool {
                if ( this == & iterator ) {
                    return true;
                }

                return
                        this->pCollection == iterator.pCollection &&
                        this->pDelegate->equals( * iterator.pDelegate );
            }

            __CDS_cpplang_VirtualConstexpr auto operator != ( ConstReverseIterator const & iterator ) const noexcept -> bool {
                if ( this == & iterator ) {
                    return false;
                }

                return
                        this->pCollection != iterator.pCollection ||
                        ! this->pDelegate->equals ( * iterator.pDelegate ); // NOLINT(clion-misra-cpp2008-5-3-1)
            }

            __CDS_cpplang_VirtualConstexpr auto operator * () const noexcept -> ElementCRef {
                return this->pDelegate->value();
            }

            __CDS_cpplang_VirtualConstexpr auto operator -> () const noexcept -> ElementCPtr {
                return & ( * ( * this ) );
            }
        };

    protected:
        constexpr static auto acquireDelegate ( Iterator const & pIterator ) noexcept -> DelegateIterator * {
            return pIterator.pDelegate.get();
        }

        enum class DelegateIteratorRequestType {
            FORWARD_BEGIN,
            FORWARD_END,
            BACKWARD_BEGIN,
            BACKWARD_END
        };

        __CDS_cpplang_VirtualConstexpr virtual auto delegateIterator ( DelegateIteratorRequestType ) noexcept -> UniquePointer < DelegateIterator > {
            return nullptr;
        }

        __CDS_cpplang_VirtualConstexpr virtual auto delegateConstIterator ( DelegateIteratorRequestType ) const noexcept -> UniquePointer < DelegateConstIterator > {
            return nullptr;
        }

    #if defined(__CDS_ThreadSafeObjects)
        Mutex mutable multithreadingProtection;
    #endif

    public:
        __CDS_NoDiscard __CDS_MaybeUnused __CDS_OptimalInline auto begin () noexcept (false) -> Iterator {
            auto pDelegate = this->delegateIterator( DelegateIteratorRequestType :: FORWARD_BEGIN );
            if ( pDelegate.isNull() ) {
                throw NotImplementedException("Iterator");
            }

            return Iterator ( this, std :: move ( pDelegate ) );
        }

        __CDS_NoDiscard __CDS_MaybeUnused __CDS_OptimalInline auto end () noexcept (false) -> Iterator {
            auto pDelegate = this->delegateIterator( DelegateIteratorRequestType :: FORWARD_END );
            if ( pDelegate.isNull() ) {
                throw NotImplementedException("Iterator");
            }

            return Iterator ( this, std :: move ( pDelegate ) );
        }

        __CDS_NoDiscard __CDS_MaybeUnused __CDS_OptimalInline auto cbegin () const noexcept (false) -> ConstIterator {
            auto pDelegate = this->delegateConstIterator( DelegateIteratorRequestType :: FORWARD_BEGIN );
            if ( pDelegate.isNull() ) {
                throw NotImplementedException("ConstIterator");
            }

            return ConstIterator ( this, std :: move ( pDelegate ) );
        }

        __CDS_NoDiscard __CDS_MaybeUnused __CDS_OptimalInline auto cend () const noexcept (false) -> ConstIterator {
            auto pDelegate = this->delegateConstIterator( DelegateIteratorRequestType :: FORWARD_END );
            if ( pDelegate.isNull() ) {
                throw NotImplementedException("ConstIterator");
            }

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
            if ( pDelegate.isNull() ) {
                throw NotImplementedException("ReverseIterator");
            }

            return ReverseIterator ( this, std :: move ( pDelegate ) );
        }

        __CDS_NoDiscard __CDS_MaybeUnused __CDS_OptimalInline auto rend () noexcept (false) -> ReverseIterator {
            auto pDelegate = this->delegateIterator( DelegateIteratorRequestType :: BACKWARD_END );
            if ( pDelegate.isNull() ) {
                throw NotImplementedException("ReverseIterator");
            }

            return ReverseIterator ( this, std :: move ( pDelegate ) );
        }

        __CDS_NoDiscard __CDS_MaybeUnused __CDS_OptimalInline auto crbegin () const noexcept (false) -> ConstReverseIterator {
            auto pDelegate = this->delegateConstIterator( DelegateIteratorRequestType :: BACKWARD_BEGIN );
            if ( pDelegate.isNull() ) {
                throw NotImplementedException("ConstReverseIterator");
            }

            return ConstReverseIterator ( this, std :: move ( pDelegate ) );
        }

        __CDS_NoDiscard __CDS_MaybeUnused __CDS_OptimalInline auto crend () const noexcept (false) -> ConstReverseIterator {
            auto pDelegate = this->delegateConstIterator( DelegateIteratorRequestType :: BACKWARD_END );
            if ( pDelegate.isNull() ) {
                throw NotImplementedException("ConstReverseIterator");
            }

            return ConstReverseIterator ( this, std :: move ( pDelegate ) );
        }

        __CDS_NoDiscard __CDS_MaybeUnused __CDS_OptimalInline auto rbegin () const noexcept (false) -> ConstReverseIterator {
            return this->crbegin();
        }

        __CDS_NoDiscard __CDS_MaybeUnused __CDS_OptimalInline auto rend () const noexcept (false) -> ConstReverseIterator {
            return this->crend();
        }

        __CDS_MaybeUnused virtual auto remove ( ElementCRef, Size ) noexcept -> bool = 0;
        __CDS_MaybeUnused virtual auto removeLast ( ElementCRef ) noexcept -> bool = 0;

        __CDS_MaybeUnused virtual auto removeOf ( Collection const &, Size ) noexcept -> bool = 0;
        __CDS_MaybeUnused virtual auto removeLastOf ( Collection const & ) noexcept -> bool = 0;

        __CDS_MaybeUnused virtual auto removeNotOf ( Collection const &, Size ) noexcept -> bool = 0;
        __CDS_MaybeUnused virtual auto removeLastNotOf ( Collection const & ) noexcept -> bool = 0;

        __CDS_MaybeUnused virtual auto removeOf ( InitializerList, Size ) noexcept -> bool = 0;
        __CDS_MaybeUnused virtual auto removeLastOf ( InitializerList ) noexcept -> bool = 0;

        __CDS_MaybeUnused virtual auto removeNotOf ( InitializerList, Size ) noexcept -> bool = 0;
        __CDS_MaybeUnused virtual auto removeLastNotOf ( InitializerList ) noexcept -> bool = 0;

        __CDS_MaybeUnused __CDS_OptimalInline virtual auto removeAll ( ElementCRef element ) noexcept -> bool {
            return this->remove(element, this->size() );
        }

        __CDS_MaybeUnused __CDS_OptimalInline virtual auto removeFirst ( ElementCRef element ) noexcept -> bool {
            return this->remove( element, 1 );
        }

        __CDS_MaybeUnused __CDS_OptimalInline virtual auto removeFirstOf ( Collection const & elements ) noexcept -> bool {
            return this->removeOf( elements, 1 );
        }

        __CDS_MaybeUnused __CDS_OptimalInline virtual auto removeAllOf ( Collection const & elements ) noexcept -> bool {
            return this->removeOf ( elements, this->size() );
        }

        __CDS_MaybeUnused __CDS_OptimalInline virtual auto removeFirstNotOf ( Collection const & elements ) noexcept -> bool {
            return this->removeNotOf (elements, 1 );
        }

        __CDS_MaybeUnused __CDS_OptimalInline virtual auto removeAllNotOf ( Collection const & elements ) noexcept -> bool  {
            return this->removeNotOf( elements, this->size() );
        }

        __CDS_MaybeUnused __CDS_OptimalInline virtual auto removeFirstOf ( InitializerList elements ) noexcept -> bool {
            return this->removeOf( elements, 1 );
        }

        __CDS_MaybeUnused __CDS_OptimalInline virtual auto removeAllOf ( InitializerList elements ) noexcept -> bool {
            return this->removeOf ( elements, this->size() );
        }

        __CDS_MaybeUnused __CDS_OptimalInline virtual auto removeFirstNotOf ( InitializerList elements ) noexcept -> bool {
            return this->removeNotOf ( elements, 1 );
        }

        __CDS_MaybeUnused __CDS_OptimalInline virtual auto removeAllNotOf ( InitializerList elements ) noexcept -> bool  {
            return this->removeNotOf( elements, this->size() );
        }

    protected:

        __CDS_cpplang_VirtualConstexpr static auto iListContains ( InitializerList list __CDS_MaybeUnused, ElementCRef what __CDS_MaybeUnused ) noexcept -> bool {
            for ( auto const & element __CDS_MaybeUnused : list ) {
                if ( Type < T > :: compare ( element, what ) ) {
                    return true;
                }
            }

            return false;
        }

        virtual auto allocInsertGetPtr ( ElementCRef ) noexcept -> ElementPtrRef = 0;

    public:

        template < typename V = T, EnableIf < Type < V > :: copyConstructible > = 0 >
        __CDS_OptimalInline auto add (ElementCRef element) noexcept -> void {

            __CDS_Collection_OperationalLock

            auto & pObject = this->allocInsertGetPtr(element);
            if (pObject == nullptr ) {
                pObject = Memory :: instance().create < ElementType > (element);
            }

            __CDS_Collection_OperationalUnlock

        }

        template < typename V = T, EnableIf < Type < V > :: moveConstructible > = 0 >
        __CDS_OptimalInline auto add (ElementMRef element) noexcept -> void {

            __CDS_Collection_OperationalLock

            auto & pObject = this->allocInsertGetPtr(element);
            if (pObject == nullptr ) {
                pObject = Memory :: instance().create < ElementType > (element);
            }

            __CDS_Collection_OperationalUnlock

        }

        virtual auto clear () noexcept -> void = 0;

        __CDS_MaybeUnused __CDS_NoDiscard __CDS_cpplang_ConstexprPureAbstract virtual auto size () const noexcept -> Size = 0;
        __CDS_MaybeUnused virtual auto makeUnique () noexcept -> void = 0;

        __CDS_OptionalInline virtual auto contains ( ElementCRef object __CDS_MaybeUnused ) const noexcept -> bool {

            __CDS_Collection_OperationalLock

            for ( auto const & element __CDS_MaybeUnused : * this ) {
                if ( Type < ElementType > :: compare (element, object ) ) {

                    __CDS_Collection_OperationalUnlock
                    return true;

                }
            }

            __CDS_Collection_OperationalUnlock
            return false;
        }

        template < typename Action >
        __CDS_MaybeUnused auto forEach (
                Action const & action __CDS_MaybeUnused
        ) noexcept ( noexcept ( ( * Type < Action > :: unsafeAddress () ) ( Type < ElementType > :: unsafeReference() ) ) )
                -> void __CDS_Requires ( ActionOver < Action, T > ) {

            __CDS_Collection_OperationalLock

            for ( auto & element __CDS_MaybeUnused : * this ) {
                action(element);
            }

            __CDS_Collection_OperationalUnlock

        }

        template < typename Action >
        __CDS_MaybeUnused auto forEach (
                Action const & action __CDS_MaybeUnused
        ) const noexcept ( noexcept ( ( * Type < Action > :: unsafeAddress () ) ( Type < ElementType const > :: unsafeReference() ) ) )
                -> void __CDS_Requires ( ActionOver < Action, T > ) {

            __CDS_Collection_OperationalLock

            for ( auto const & element __CDS_MaybeUnused : * this ) {
                action(element);
            }

            __CDS_Collection_OperationalUnlock

        }

        template < typename Predicate = Function < bool ( ElementCRef ) > >
        __CDS_MaybeUnused __CDS_OptimalInline auto some (
                Size                count       __CDS_MaybeUnused,
                Predicate   const & predicate   __CDS_MaybeUnused = []( ElementCRef ) noexcept -> bool { return true; }
        ) noexcept ( noexcept ( ( * Type < Predicate > :: unsafeAddress () ) ( Type < ElementType > :: unsafeReference() ) ) )
                -> bool __CDS_Requires( PredicateOver < Predicate, T > ) {

            Size trueCount __CDS_MaybeUnused = 0u;
            for ( auto & element __CDS_MaybeUnused : * this ) {
                if (predicate (element ) && trueCount < count ) {
                    trueCount++;
                }

                if ( trueCount > count ) {
                    return false;
                }
            }


            return trueCount == count;
        }

        template < typename Predicate = Function < bool ( ElementCRef ) > >
        __CDS_MaybeUnused __CDS_OptimalInline auto some (
                Size                count       __CDS_MaybeUnused,
                Predicate   const & predicate   __CDS_MaybeUnused = []( ElementCRef ) noexcept -> bool { return true; }
        ) const noexcept ( noexcept ( ( * Type < Predicate > :: unsafeAddress () ) ( Type < ElementType const > :: unsafeReference() ) ) )
                -> bool __CDS_Requires( PredicateOver < Predicate, T > ) {

            Size trueCount __CDS_MaybeUnused = 0u;
            for ( auto & element __CDS_MaybeUnused : * this ) {
                if (predicate (element ) && trueCount < count ) {
                    trueCount++;
                }

                if ( trueCount > count ) {
                    return false;
                }
            }

            return trueCount == count;
        }

        template < typename Predicate = Function < bool ( ElementCRef ) > >
        __CDS_MaybeUnused __CDS_OptimalInline auto atLeast (
                Size                count       __CDS_MaybeUnused,
                Predicate   const & predicate   __CDS_MaybeUnused = []( ElementCRef ) noexcept -> bool { return true; }
        ) noexcept ( noexcept ( ( * Type < Predicate > :: unsafeAddress () ) ( Type < ElementType > :: unsafeReference() ) ) )
                -> bool __CDS_Requires( PredicateOver < Predicate, T > ) {

            Size trueCount __CDS_MaybeUnused = 0u;
            for ( auto & element __CDS_MaybeUnused : * this ) {
                if (predicate(element) && trueCount < count) {
                    trueCount++;
                }

                if (trueCount >= count) {
                    return true;
                }
            }

            return false;
        }

        template < typename Predicate = Function < bool ( ElementCRef ) > >
        __CDS_MaybeUnused __CDS_OptimalInline auto atLeast (
                Size                count       __CDS_MaybeUnused,
                Predicate   const & predicate   __CDS_MaybeUnused = []( ElementCRef ) noexcept -> bool { return true; }
        ) const noexcept ( noexcept ( ( * Type < Predicate > :: unsafeAddress () ) ( Type < ElementType const > :: unsafeReference() ) ) )
                -> bool __CDS_Requires( PredicateOver < Predicate, T > ) {

            Size trueCount __CDS_MaybeUnused = 0u;
            for ( auto & element __CDS_MaybeUnused : * this ) {
                if (predicate(element) && trueCount < count) {
                    trueCount++;
                }

                if (trueCount >= count) {
                    return true;
                }
            }

            return trueCount >= count;
        }

        template < typename Predicate = Function < bool ( ElementCRef ) > >
        __CDS_MaybeUnused __CDS_OptimalInline auto atMost (
                Size                count       __CDS_MaybeUnused,
                Predicate   const & predicate   __CDS_MaybeUnused = []( ElementCRef ) noexcept -> bool { return true; }
        ) noexcept ( noexcept ( ( * Type < Predicate > :: unsafeAddress () ) ( Type < ElementType > :: unsafeReference() ) ) )
                -> bool __CDS_Requires( PredicateOver < Predicate, T > ) {

            Size trueCount __CDS_MaybeUnused = 0u;
            for ( auto & element __CDS_MaybeUnused : * this ) {
                if (predicate (element ) && trueCount < count ) {
                    trueCount++;
                }

                if ( trueCount > count ) {
                    return false;
                }
            }

            return true;
        }

        template < typename Predicate = Function < bool ( ElementCRef ) > >
        __CDS_MaybeUnused __CDS_OptimalInline auto atMost (
                Size                count       __CDS_MaybeUnused,
                Predicate const &   predicate   __CDS_MaybeUnused = []( ElementCRef ) noexcept -> bool { return true; }
        ) const noexcept ( noexcept ( ( * Type < Predicate > :: unsafeAddress () ) ( Type < ElementType const > :: unsafeReference() ) ) )
                -> bool __CDS_Requires( PredicateOver < Predicate, T > ) {

            Size trueCount __CDS_MaybeUnused = 0u;
            for ( auto & element __CDS_MaybeUnused : * this ) {
                if (predicate (element ) && trueCount < count ) {
                    ++ trueCount;
                }
                if ( trueCount > count ) {
                    return false;
                }
            }

            return trueCount <= count;
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

            return this->atMost ( count, predicate );
        }

        template < typename Predicate = Function < bool ( ElementCRef ) > >
        __CDS_MaybeUnused __CDS_OptimalInline auto lessThan (
                Size                count,
                Predicate   const & predicate = []( ElementCRef ) noexcept -> bool { return true; }
        ) const noexcept ( noexcept ( ( * Type < Predicate > :: unsafeAddress () ) ( Type < ElementType const > :: unsafeReference() ) ) )
                -> bool __CDS_Requires( PredicateOver < Predicate, T > ) {

            return this->atMost ( count, predicate );
        }

        template < typename Predicate = Function < bool ( ElementCRef ) > >
        __CDS_MaybeUnused auto count (
                Predicate const & predicate __CDS_MaybeUnused = []( ElementCRef ) noexcept -> bool { return true; }
        ) noexcept ( noexcept ( ( * Type < Predicate > :: unsafeAddress () ) ( Type < ElementType > :: unsafeReference() ) ) )
                -> Size __CDS_Requires( PredicateOver < Predicate, T > )  {

            Size trueCount __CDS_MaybeUnused = 0u;

            __CDS_Collection_OperationalLock

            for ( auto & element __CDS_MaybeUnused : * this ) {
                if (predicate(element)) {
                    trueCount++;
                }
            }

            __CDS_Collection_OperationalUnlock

            return trueCount;
        }

        template < typename Predicate = Function < bool ( ElementCRef ) > >
        __CDS_MaybeUnused auto count (
                Predicate const & predicate __CDS_MaybeUnused = []( ElementCRef ) noexcept -> bool { return true; }
        ) const noexcept ( noexcept ( ( * Type < Predicate > :: unsafeAddress () ) ( Type < ElementType const > :: unsafeReference() ) ) )
                -> Size __CDS_Requires( PredicateOver < Predicate, T > ) {

            Size trueCount __CDS_MaybeUnused = 0u;

            __CDS_Collection_OperationalLock

            for ( auto const & element __CDS_MaybeUnused : * this ) {
                if (predicate(element)) {
                    ++ trueCount;
                }
            }

            __CDS_Collection_OperationalUnlock

            return trueCount;
        }

        template < typename Predicate = Function < bool ( ElementCRef ) > >
        __CDS_MaybeUnused __CDS_OptimalInline auto any (
                Predicate const & predicate = [](ElementCRef ) noexcept -> bool { return true; }
        ) noexcept ( noexcept ( ( * Type < Predicate > :: unsafeAddress () ) ( Type < ElementType > :: unsafeReference() ) ) )
                -> bool __CDS_Requires( PredicateOver < Predicate, T > ) {

            return this->atLeast (1, predicate );
        }

        template < typename Predicate = Function < bool ( ElementCRef ) > >
        __CDS_MaybeUnused __CDS_OptimalInline auto any (
                Predicate const & predicate = [](ElementCRef ) noexcept -> bool { return true; }
        ) const noexcept ( noexcept ( ( * Type < Predicate > :: unsafeAddress () ) ( Type < ElementType const > :: unsafeReference() ) ) )
                -> bool __CDS_Requires( PredicateOver < Predicate, T > ) {

            return this->atLeast (1, predicate );
        }

        template < typename Predicate >
        __CDS_MaybeUnused __CDS_OptimalInline auto all (
                Predicate const & predicate
        ) noexcept ( noexcept ( ( * Type < Predicate > :: unsafeAddress () ) ( Type < ElementType > :: unsafeReference() ) ) )
                -> bool __CDS_Requires( PredicateOver < Predicate, T > ) {

            return ! this->any ( [&predicate] (T & element) noexcept -> bool { // NOLINT(clion-misra-cpp2008-5-3-1)
                return ! predicate(element); // NOLINT(clion-misra-cpp2008-5-3-1)
            });
        }

        template < typename Predicate >
        __CDS_MaybeUnused __CDS_OptimalInline auto all (
                Predicate const & predicate
        ) const noexcept ( noexcept ( ( * Type < Predicate > :: unsafeAddress () ) ( Type < ElementType const > :: unsafeReference() ) ) )
                -> bool __CDS_Requires( PredicateOver < Predicate, T > ) {

            return ! this->any ( [&predicate] (ElementCRef element) noexcept -> bool { // NOLINT(clion-misra-cpp2008-5-3-1)
                return ! predicate(element); // NOLINT(clion-misra-cpp2008-5-3-1)
            });
        }

        __CDS_OptimalInline virtual COLLECTION_EXPLICIT_CONVERSION operator bool () const noexcept { // NOLINT(google-explicit-constructor)
            return this->size() != 0;
        }

        __CDS_NoDiscard auto toString () const noexcept -> String override = 0;

        __CDS_cpplang_ConstexprDestructor ~Collection() noexcept override = default;

        __CDS_OptimalInline friend auto operator << (std::ostream & stream, Collection const & collection ) noexcept -> std::ostream & {
            return ( stream << collection.toString() );
        }

        __CDS_NoDiscard __CDS_MaybeUnused __CDS_cpplang_ConstexprPureAbstract virtual auto empty () const noexcept -> bool = 0;
    };

}


__CDS_RegisterParseTypeTemplateT(Collection) // NOLINT(clion-misra-cpp2008-8-0-1)

#endif //CDS_COLLECTION_HPP
