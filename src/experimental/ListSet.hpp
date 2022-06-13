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
            using typename Collection < __ElementType > :: ElementType;

        public:
            using typename Collection < __ElementType > :: ConstIterator;

        public:
            using typename Collection < __ElementType > :: ConstReverseIterator;

        protected:
            using typename Collection < __ElementType > :: InitializerList;

        protected:
            using typename Collection < __ElementType > :: DelegateConstIterator;

        protected:
            using typename Collection < __ElementType > :: AbstractIterator;

        protected:
            using typename Collection < __ElementType > :: AbstractDelegateIterator;

        protected:
            using typename Collection < __ElementType > :: DelegateIteratorRequestType;

        private:
            class ListSetDelegateIterator;

        private:
            auto delegateConstIterator (
                    DelegateIteratorRequestType requestType
            ) const noexcept -> cds :: UniquePointer < DelegateConstIterator > override;

        private:
            using Node = __hidden :: __impl :: __UnidirectionalNode < __ElementType >;

        private:
            Node    * _pFront  { nullptr };

        public:
            constexpr ListSet () noexcept;

        public:
            ListSet (
                    ListSet const & set
            ) noexcept;

        public:
            constexpr ListSet (
                    ListSet && set
            ) noexcept;

        public:
            constexpr ListSet (
                    Size size
            ) noexcept;

        public:
            ~ListSet() noexcept override;

        public:
            auto remove (
                    ConstIterator const & iterator
            ) noexcept -> bool override;

        public:
            auto remove (
                    ConstReverseIterator const & iterator
            ) noexcept -> bool override;

        private:
            auto remove (
                    ListSetDelegateIterator const * pIterator
            ) noexcept -> bool;

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
            auto contains (
                    ElementType const & element
            ) const noexcept -> bool override;

        public:
            auto clear () noexcept -> void override;
        };

    }
}

#include "listSet/DelegateIterator.hpp"

#include "listSet/impl/DelegateIterator.hpp"
#include "listSet/impl/ListSet.hpp"

#endif // __CDS_EX_LIST_SET_HPP__
