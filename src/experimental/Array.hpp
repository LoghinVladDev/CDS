//
// Created by loghin on 4/24/2022.
//

#ifndef __CDS_EX_ARRAY_HPP__
#define __CDS_EX_ARRAY_HPP__

#include <CDS/experimental/List>
#include "../shared/memory/PrimitiveAllocation.hpp"

namespace cds { // NOLINT(modernize-concat-nested-namespaces)

    template < typename __CollectionType > // NOLINT(bugprone-reserved-identifier)
    class Sequence;

    namespace experimental {

        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        class Array : public List < __ElementType > {
            
        public:
            using typename List < __ElementType > :: ElementType;

        public:
            using typename List < __ElementType > :: Iterator;
            
        public:
            using typename List < __ElementType > :: ConstIterator;
            
        public:
            using typename List < __ElementType > :: ReverseIterator;
            
        public:
            using typename List < __ElementType > :: ConstReverseIterator;

        protected:
            using typename List < __ElementType > :: InitializerList;
            
        protected:
            using typename List < __ElementType > :: DelegateIterator;
            
        protected:
            using typename List < __ElementType > :: DelegateConstIterator;
            
        protected:
            using typename List < __ElementType > :: AbstractIterator;
            
        protected:
            using typename List < __ElementType > :: AbstractDelegateIterator;

        private:
            class ArrayDelegateIterator;
            
        private:
            class ArrayDelegateConstIterator;
            
        private:
            using typename List < __ElementType > :: DelegateIteratorRequestType;

        private:
            auto delegateIterator (
                    DelegateIteratorRequestType requestType
            ) noexcept -> cds :: UniquePointer < DelegateIterator > override;

        private:
            auto delegateConstIterator (
                    DelegateIteratorRequestType requestType
            ) const noexcept -> cds :: UniquePointer < DelegateConstIterator > override;

        private:
            using NodeType = cds :: __hidden :: __impl :: __allocation :: __RawContainer < ElementType >;

        private:
            NodeType  * _pData       { nullptr };

        private:
            Size        _capacity    { 0ULL };

        protected:
            static Size const minCapacity = 32ULL;

        private:
            auto initializeByCopy (
                    Array const & array
            ) noexcept -> void;

        public:
            constexpr Array () noexcept = default;

        public:
            Array (
                    Array const & array
            ) noexcept;

        public:
            constexpr Array (
                    Array && array
            ) noexcept;

        public:
            template < typename __IteratorType, meta :: EnableIf < meta :: isIterator < __IteratorType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
            Array (
                    __IteratorType const & begin,
                    __IteratorType const & end
            ) noexcept;

        public:
            __CDS_Implicit Array ( // NOLINT(google-explicit-constructor)
                    InitializerList const & initializerList
            ) noexcept;

        public:
            template < typename __VElementType = __ElementType, meta :: EnableIf < meta :: isDefaultConstructible < __VElementType > () > > // NOLINT(bugprone-reserved-identifier)
            __CDS_Explicit Array (
                    Size size
            ) noexcept;

        public:
            template < typename __VElementType = __ElementType, meta :: EnableIf < meta :: isCopyConstructible < __VElementType > () > > // NOLINT(bugprone-reserved-identifier)
            Array (
                    Size                size,
                    ElementType const & defaultValue
            ) noexcept;

        public:
            template < typename __OtherElementType, meta :: EnableIf < meta :: isConvertible < __OtherElementType, __ElementType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
            __CDS_Explicit Array (
                    Collection < __OtherElementType > const & collection
            ) noexcept;

        public:
            ~Array () noexcept override;


        public:
            template < typename __VElementType = __ElementType, meta :: EnableIf < meta :: isDefaultConstructible < __VElementType > () > > // NOLINT(bugprone-reserved-identifier)
            auto resize (
                    Size
            ) noexcept -> void;

        public:
            template < typename __VElementType = __ElementType, meta :: EnableIf < meta :: isCopyConstructible < __VElementType > () > > // NOLINT(bugprone-reserved-identifier)
            auto resize (
                    Size,
                    ElementType const &
            ) noexcept -> void;

        public:
            auto shrink (
                    Size
            ) noexcept -> void;

        public:
            auto removeAt (
                    Index index
            ) noexcept -> bool override;

        public:
            auto removeAt (
                    Collection < Index > const & indices
            ) noexcept -> Size override;

        public:
            auto removeAt (
                    std :: initializer_list < Index > const & indices
            ) noexcept -> Size override;

        public:
            auto remove (
                    Iterator const & iterator
            ) noexcept -> bool override;

        public:
            auto remove (
                    ConstIterator const & iterator
            ) noexcept -> bool override;

        public:
            auto remove (
                    ReverseIterator const & iterator
            ) noexcept -> bool override;

        public:
            auto remove (
                    ConstReverseIterator const & iterator
            ) noexcept -> bool override;

        protected:
            auto remove (
                    Iterator    const * pIterators,
                    Size                iteratorCount
            ) noexcept -> Size override;

        protected:
            auto remove (
                    ConstIterator   const * pIterators,
                    Size                    iteratorCount
            ) noexcept -> Size override;

        protected:
            auto remove (
                    ReverseIterator const * pIterators,
                    Size                    iteratorCount
            ) noexcept -> Size override;

        protected:
            auto remove (
                    ConstReverseIterator    const * pIterators,
                    Size                            iteratorCount
            ) noexcept -> Size override;

        public:
            __CDS_NoDiscard constexpr auto data () const noexcept -> ElementType const * {
                return reinterpret_cast < ElementType const * > ( this->_pData );
            }

        public:
            __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction auto data () noexcept -> ElementType * {
                return reinterpret_cast < ElementType * > ( this->_pData );
            }

        protected:
            auto pNewBefore (
                    Index index
            ) noexcept -> ElementType *;

        protected:
            auto pNewAfter (
                    Index index
            ) noexcept -> ElementType *;

        protected:
            auto pNewFront () noexcept -> ElementType * override;

        protected:
            auto pNewBack () noexcept -> ElementType * override;

        protected:
            auto pNewBefore (
                    Iterator const & iterator
            ) noexcept -> ElementType * override;

        protected:
            auto pNewAfter (
                    Iterator const & iterator
            ) noexcept -> ElementType * override;

        protected:
            auto pNewBefore (
                    ConstIterator const & iterator
            ) noexcept -> ElementType * override;

        protected:
            auto pNewAfter (
                    ConstIterator const & iterator
            ) noexcept -> ElementType * override;

        protected:
            auto pNewBefore (
                    ReverseIterator const & iterator
            ) noexcept -> ElementType * override;

        protected:
            auto pNewAfter (
                    ReverseIterator const & iterator
            ) noexcept -> ElementType * override;

        protected:
            auto pNewBefore (
                    ConstReverseIterator const & iterator
            ) noexcept -> ElementType * override;

        protected:
            auto pNewAfter (
                    ConstReverseIterator const & iterator
            ) noexcept -> ElementType * override;

        public:
            __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto front () noexcept (false) -> ElementType & override;

        public:
            __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto front () const noexcept (false) -> ElementType const & override;

        public:
            __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto back () noexcept (false) -> ElementType & override;

        public:
            __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto back () const noexcept (false) -> ElementType const & override;

        public:
            __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto get (
                    Index
            ) noexcept (false) -> ElementType & override;

        public:
            __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto get (
                    Index
            ) const noexcept (false) -> ElementType const & override;

        public:
            __CDS_NoDiscard auto operator == (
                    Array const & array
            ) const noexcept -> bool;

        public:
            __CDS_NoDiscard auto operator != (
                    Array const & array
            ) const noexcept -> bool;

        public:
            auto clear () noexcept -> void override;

        public:
            auto makeUnique () noexcept -> void override;

        public:
            auto popFront () noexcept -> void override;

        public:
            auto popBack () noexcept -> void override;

        public:
            template < typename __VElementType = __ElementType, meta :: EnableIf < meta :: isCopyConstructible < __VElementType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
            auto operator = (
                    Array const & array
            ) noexcept -> Array &;

        public:
            auto operator = (
                    Array && array
            ) noexcept -> Array &;

        public:
            template < typename __OtherElementType, meta :: EnableIf < meta :: isConvertible < __OtherElementType, __ElementType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
            auto operator = (
                    Collection < __OtherElementType > const & collection
            ) noexcept -> Array &;

        public:
            auto sequence () & noexcept -> Sequence < Array < __ElementType > >;

        public:
            auto sequence () && noexcept -> Sequence < Array < __ElementType > >;

        public:
            auto sequence () const & noexcept -> Sequence < Array < __ElementType > const >;

        public:
            auto sequence () const && noexcept -> Sequence < Array < __ElementType > const >;

        };

    }
}

#include "array/ArrayDelegateIterator.hpp"
#include "array/ArrayDelegateConstIterator.hpp"

#include "../shared/memory/PrimitiveAllocation.hpp"
#include "array/impl/Array.hpp"
#include "array/impl/ArrayDelegateIterator.hpp"
#include "array/impl/ArrayDelegateConstIterator.hpp"
#include "array/CTAD.hpp"

#include "shared/array/impl/ArraySequence.hpp"

#include "shared/collection/FunctionalConstructors.hpp"
#include "shared/collection/impl/FunctionalConstructors.hpp"

#endif // __CDS_EX_ARRAY_HPP__
