//
// Created by loghin on 6/13/22.
//

#ifndef __CDS_EX_LIST_SET_HPP__
#define __CDS_EX_LIST_SET_HPP__

#include <CDS/experimental/Set>

#include "shared/Node.hpp"

namespace cds { // NOLINT(modernize-concat-nested-namespaces)

    template < typename __CollectionType > // NOLINT(bugprone-reserved-identifier)
    class Sequence;

    namespace experimental {

        template <
                typename __ElementType // NOLINT(bugprone-reserved-identifier)
        > class ListSet : public Set < __ElementType > {

        public:
            using typename Set < __ElementType > :: ElementType;

        public:
            using typename Set < __ElementType > :: ConstIterator;

        public:
            using typename Set < __ElementType > :: ConstReverseIterator;

        protected:
            using typename Set < __ElementType > :: InitializerList;

        protected:
            using typename Set < __ElementType > :: DelegateConstIterator;

        protected:
            using typename Set < __ElementType > :: AbstractIterator;

        protected:
            using typename Set < __ElementType > :: AbstractDelegateIterator;

        protected:
            using typename Set < __ElementType > :: DelegateIteratorRequestType;

        private:
            class ListSetDelegateIterator;

        private:
            auto delegateConstIterator (
                    DelegateIteratorRequestType requestType
            ) const noexcept -> cds :: UniquePointer < DelegateConstIterator > override;

        protected:
            using Node = __hidden :: __impl :: __UnidirectionalNode < __ElementType >;

        protected:
            Node    * _pFront   { nullptr };

        protected:
            Size      _size     { 0ULL };

        protected:
            constexpr ListSet () noexcept;

        protected:
            ListSet (
                    ListSet const & set
            ) noexcept;

        protected:
            constexpr ListSet (
                    ListSet && set
            ) noexcept;

        protected:
            __CDS_Explicit constexpr ListSet (
                    Size size
            ) noexcept;

        public:
            ~ListSet() noexcept override;

        public:
            __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto size () const noexcept -> Size override;

        private:
            auto remove (
                    ListSetDelegateIterator const * pIterator
            ) noexcept -> bool;

        public:
            auto remove (
                    ConstIterator const & iterator
            ) noexcept -> bool override;

        public:
            auto remove (
                    ConstReverseIterator const & iterator
            ) noexcept -> bool override;

        protected:
            auto remove (
                    ConstIterator   const * pIterators,
                    Size                    iteratorCount
            ) noexcept -> Size override;

        protected:
            auto remove (
                    ConstReverseIterator    const * pIterators,
                    Size                            iteratorCount
            ) noexcept -> Size override;

        protected:
            auto pNewInsert (
                    ElementType const & referenceElement
            ) noexcept -> ElementType * & override = 0;

        public:
            auto clear () noexcept -> void override;
        };

    }
}

#include "listSet/DelegateIterator.hpp"

#include "listSet/impl/DelegateIterator.hpp"
#include "listSet/impl/ListSet.hpp"

#endif // __CDS_EX_LIST_SET_HPP__
