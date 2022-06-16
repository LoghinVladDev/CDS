//
// Created by loghin on 6/13/22.
//

#ifndef __CDS_EX_HASH_SET_HPP__
#define __CDS_EX_HASH_SET_HPP__

#include <CDS/experimental/Set>
#include <CDS/Hasher>

#include "shared/Node.hpp"

namespace cds { // NOLINT(modernize-concat-nested-namespaces)

    template < typename __CollectionType > // NOLINT(bugprone-reserved-identifier)
    class Sequence;

    namespace experimental {

        template <
                typename __ElementType, // NOLINT(bugprone-reserved-identifier)
                typename __HashCalculator = cds :: utility :: LowCollisionDefaultHashFunction < __ElementType > // NOLINT(bugprone-reserved-identifier)
        > class HashSet : public Set < __ElementType > {

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
            class HashSetDelegateIterator;

        private:
            auto delegateConstIterator (
                    DelegateIteratorRequestType requestType
            ) const noexcept -> cds :: UniquePointer < DelegateConstIterator > override;

        private:
            using Node = __hidden :: __impl :: __UnidirectionalNode < __ElementType >;

        private:
            using BucketList = Node *;

        private:
            BucketList        * _listArray  { nullptr };

        private:
            __HashCalculator    _hashCalculator;

        public:
            constexpr HashSet () noexcept;

        public:
            HashSet (
                    HashSet const & set
            ) noexcept;

        public:
            constexpr HashSet (
                    HashSet && set
            ) noexcept;

        public:
            __CDS_Explicit HashSet (
                    __HashCalculator const & hashCalculator
            ) noexcept;

        public:
            template < typename __IteratorType, cds :: meta :: EnableIf < cds :: meta :: isIterator < __IteratorType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
            HashSet (
                    __IteratorType const & begin,
                    __IteratorType const & end
            ) noexcept;

        public:
            template < typename __IteratorType, cds :: meta :: EnableIf < cds :: meta :: isIterator < __IteratorType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
            HashSet (
                    __IteratorType      const & begin,
                    __IteratorType      const & end,
                    __HashCalculator    const & hashCalculator
            ) noexcept;

        public:
            __CDS_Implicit HashSet ( // NOLINT(google-explicit-constructor)
                    InitializerList const & initializerList
            ) noexcept;

        public:
            HashSet (
                    InitializerList     const & initializerList,
                    __HashCalculator    const & hashCalculator
            ) noexcept;

        public:
            template < typename __OtherElementType, cds :: meta :: EnableIf < cds :: meta :: isConvertible < __OtherElementType, __ElementType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
            __CDS_Explicit HashSet (
                    Collection < __OtherElementType >   const & collection
            ) noexcept;

        public:
            template < typename __OtherElementType, cds :: meta :: EnableIf < cds :: meta :: isConvertible < __OtherElementType, __ElementType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
            HashSet (
                    Collection < __OtherElementType >   const & collection,
                    __HashCalculator                    const & hashCalculator
            ) noexcept;

        public:
            ~HashSet() noexcept override;

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
                    HashSetDelegateIterator const * pIterator
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
            ) noexcept -> ElementType * & override;

        public:
            auto contains (
                    ElementType const & element
            ) const noexcept -> bool override;

        public:
            auto clear () noexcept -> void override;

        public:
            auto operator == (
                    HashSet const & set
            ) const noexcept -> bool;

        public:
            auto operator != (
                    HashSet const & set
            ) const noexcept -> bool;

        public:
            template < typename __VElementType = __ElementType, cds :: meta :: EnableIf < cds :: meta :: isCopyConstructible < __VElementType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
            auto operator = (
                    HashSet const & hashSet
            ) noexcept -> HashSet &;

        public:
            auto operator = (
                    HashSet && hashSet
            ) noexcept -> HashSet &;

        public:
            template < typename __OtherElementType, cds :: meta :: EnableIf < cds :: meta :: isConvertible < __OtherElementType, __ElementType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
            auto operator = (
                    Collection < __OtherElementType > const & collection
            ) noexcept -> HashSet &;

        public:
            auto sequence () & noexcept -> Sequence < HashSet < __ElementType, __HashCalculator > >;

        public:
            auto sequence () && noexcept -> Sequence < HashSet < __ElementType, __HashCalculator > >;

        public:
            auto sequence () const & noexcept -> Sequence < HashSet < __ElementType, __HashCalculator > const >;

        public:
            auto sequence () const && noexcept -> Sequence < HashSet < __ElementType, __HashCalculator > const >;
        };

    }
}

#include "hashSet/DelegateIterator.hpp"

#include "hashSet/impl/DelegateIterator.hpp"
#include "hashSet/impl/HashSet.hpp"

#include "hashSet/CTAD.hpp"

#include "shared/hashSet/impl/HashSetSequence.hpp"

#include "shared/collection/FunctionalConstructors.hpp"
#include "shared/collection/impl/FunctionalConstructors.hpp"


#endif // __CDS_EX_HASH_SET_HPP__
