//
// Created by loghin on 7/2/22.
//

#ifndef __CDS_EX_ARRAY_HPP__
#define __CDS_EX_ARRAY_HPP__

#include <CDS/experimental/List>

#include "shared/iterator/AddressIterator.hpp"

#include "shared/array/Array.hpp"

#include "shared/delegateIterator/AbstractDelegateIterator.hpp"
#include "shared/delegateIterator/DelegateIterator.hpp"

#include "shared/collectionInternalCommunication/server/ListServer.hpp"
#include "shared/collectionInternalCommunication/server/DelegateIterableServer.hpp"

#include "array/ArrayConstructs.hpp"

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {

        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        class Array :
                public List < __ElementType >,
                protected __hidden :: __impl :: __ArrayImplementation < __ElementType >,
                protected __hidden :: __impl :: __ArrayServer < __ElementType >,
                public __hidden :: __impl :: __ArrayRandomInsertionClient < __ElementType >,
                public __hidden :: __impl :: __ArrayBoundaryInsertionClient < __ElementType >,
                public __hidden :: __impl :: __ArrayIteratorRelativeInsertionClient < __ElementType >,
                public __hidden :: __impl :: __ArrayConstIteratorRelativeInsertionClient < __ElementType >,
                public __hidden :: __impl :: __ArrayIteratorRemoveClient < __ElementType >,
                public __hidden :: __impl :: __ArrayConstIteratorRemoveClient < __ElementType >,
                public __hidden :: __impl :: __ArrayDelegateIterableServer < __ElementType > {

        private:
            template < typename, typename >
            friend class cds :: experimental :: __hidden :: __impl :: __ListServer; // NOLINT(bugprone-reserved-identifier)

        protected:  using Implementation                        = __hidden :: __impl :: __ArrayImplementation < __ElementType >;
        protected:  using Server                                = __hidden :: __impl :: __ArrayServer < __ElementType >;
        protected:  using RandomInsertionClient                 = __hidden :: __impl :: __ArrayRandomInsertionClient < __ElementType >;
        protected:  using BoundaryInsertionClient               = __hidden :: __impl :: __ArrayBoundaryInsertionClient < __ElementType >;
        protected:  using IteratorRelativeInsertionClient       = __hidden :: __impl :: __ArrayIteratorRelativeInsertionClient < __ElementType >;
        protected:  using ConstIteratorRelativeInsertionClient  = __hidden :: __impl :: __ArrayConstIteratorRelativeInsertionClient < __ElementType >;
        protected:  using IteratorRemoveClient                  = __hidden :: __impl :: __ArrayIteratorRemoveClient < __ElementType >;
        protected:  using ConstIteratorRemoveClient             = __hidden :: __impl :: __ArrayConstIteratorRemoveClient < __ElementType >;
        protected:  using DelegateIterableServer                = __hidden :: __impl :: __ArrayDelegateIterableServer < __ElementType >;

        private: friend BoundaryInsertionClient;
        private: friend RandomInsertionClient;
        private: friend IteratorRemoveClient;
        private: friend ConstIteratorRemoveClient;

        public: using ElementType                   = __ElementType;
        public: using Iterator                      = typename Implementation :: __a_Iterator;
        public: using ConstIterator                 = typename Implementation :: __a_ConstIterator;
        public: using ReverseIterator               = typename Implementation :: __a_ReverseIterator;
        public: using ConstReverseIterator          = typename Implementation :: __a_ConstReverseIterator;

        private:
            __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto __cicch_obtainGenericHandler ( // NOLINT(bugprone-reserved-identifier)
                    __hidden :: __impl :: __CollectionInternalRequestType requestType
            ) noexcept -> void ( Collection < __ElementType > :: * ) () override;

        private:
            __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto __cicch_obtainGenericConstHandler ( // NOLINT(bugprone-reserved-identifier)
                    __hidden :: __impl :: __CollectionInternalRequestType requestType
            ) const noexcept -> void ( Collection < __ElementType > :: * ) () const override;

        public:
            constexpr Array () noexcept;

        public:
            ~Array () noexcept override;

        protected: using List < __ElementType > :: begin;
        protected: using List < __ElementType > :: end;
        protected: using List < __ElementType > :: cbegin;
        protected: using List < __ElementType > :: cend;
        protected: using List < __ElementType > :: rbegin;
        protected: using List < __ElementType > :: rend;
        protected: using List < __ElementType > :: crbegin;
        protected: using List < __ElementType > :: crend;

        public: using RandomInsertionClient :: insert;
        public: using RandomInsertionClient :: insertAll;
        public: using RandomInsertionClient :: insertAllOf;
        public: using RandomInsertionClient :: add;
        public: using RandomInsertionClient :: addAll;
        public: using RandomInsertionClient :: addAllOf;
        public: using RandomInsertionClient :: emplace;

        public: using BoundaryInsertionClient :: pushBack;
        public: using BoundaryInsertionClient :: pushBackAll;
        public: using BoundaryInsertionClient :: pushBackAllOf;
        public: using BoundaryInsertionClient :: pushFront;
        public: using BoundaryInsertionClient :: pushFrontAll;
        public: using BoundaryInsertionClient :: pushFrontAllOf;
        public: using BoundaryInsertionClient :: append;
        public: using BoundaryInsertionClient :: prepend;
        public: using BoundaryInsertionClient :: emplaceBack;
        public: using BoundaryInsertionClient :: emplaceFront;

        public: using IteratorRelativeInsertionClient :: insertBefore;
        public: using IteratorRelativeInsertionClient :: insertAllBefore;
        public: using IteratorRelativeInsertionClient :: insertAllOfBefore;
        public: using IteratorRelativeInsertionClient :: emplaceBefore;
        public: using IteratorRelativeInsertionClient :: insertAfter;
        public: using IteratorRelativeInsertionClient :: insertAllAfter;
        public: using IteratorRelativeInsertionClient :: insertAllOfAfter;
        public: using IteratorRelativeInsertionClient :: emplaceAfter;

        public: using ConstIteratorRelativeInsertionClient :: insertBefore;
        public: using ConstIteratorRelativeInsertionClient :: insertAllBefore;
        public: using ConstIteratorRelativeInsertionClient :: insertAllOfBefore;
        public: using ConstIteratorRelativeInsertionClient :: emplaceBefore;
        public: using ConstIteratorRelativeInsertionClient :: insertAfter;
        public: using ConstIteratorRelativeInsertionClient :: insertAllAfter;
        public: using ConstIteratorRelativeInsertionClient :: insertAllOfAfter;
        public: using ConstIteratorRelativeInsertionClient :: emplaceAfter;

        public: using IteratorRemoveClient :: remove;
        public: using ConstIteratorRemoveClient :: remove;
        public: using List < __ElementType > :: remove;

        public:
            __CDS_NoDiscard constexpr auto begin () noexcept -> Iterator;

        public:
            __CDS_NoDiscard constexpr auto end () noexcept -> Iterator;

        public:
            __CDS_NoDiscard constexpr auto begin () const noexcept -> ConstIterator;

        public:
            __CDS_NoDiscard constexpr auto end () const noexcept -> ConstIterator;

        public:
            __CDS_NoDiscard constexpr auto cbegin () const noexcept -> ConstIterator;

        public:
            __CDS_NoDiscard constexpr auto cend () const noexcept -> ConstIterator;

        public:
            __CDS_NoDiscard constexpr auto rbegin () noexcept -> ReverseIterator;

        public:
            __CDS_NoDiscard constexpr auto rend () noexcept -> ReverseIterator;

        public:
            __CDS_NoDiscard constexpr auto rbegin () const noexcept -> ConstReverseIterator;

        public:
            __CDS_NoDiscard constexpr auto rend () const noexcept -> ConstReverseIterator;

        public:
            __CDS_NoDiscard constexpr auto crbegin () const noexcept -> ConstReverseIterator;

        public:
            __CDS_NoDiscard constexpr auto crend () const noexcept -> ConstReverseIterator;

        public:
            auto clear () noexcept -> void override;

        public:
            __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto size () const noexcept -> Size override;

        public:
            auto popFront () noexcept -> void override;

        public:
            auto popBack () noexcept -> void override;

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
                    Index index
            ) noexcept (false) -> ElementType & override;

        public:
            __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto get (
                    Index index
            ) const noexcept (false) -> ElementType const & override;

        public:
            auto removeAt (
                    Index index
            ) noexcept -> bool override;

        private:
            auto __newAddress ( // NOLINT(bugprone-reserved-identifier)
                    __ElementType const * pReferenceElement,
                    bool                * pNewElementCreated
            ) noexcept -> ElementType *;

        private:
            auto __newFront () noexcept -> ElementType *; // NOLINT(bugprone-reserved-identifier)

        private:
            auto __newBack () noexcept -> ElementType *; // NOLINT(bugprone-reserved-identifier)

        private:
            auto __newFrontArray ( // NOLINT(bugprone-reserved-identifier)
                    Size              count,
                    ElementType    ** ppElements
            ) noexcept -> void;

        private:
            auto __newBackArray ( // NOLINT(bugprone-reserved-identifier)
                    Size              count,
                    ElementType    ** ppElements
            ) noexcept -> void;

        private:
            auto __remove ( // NOLINT(bugprone-reserved-identifier)
                    AbstractAddressIterator < __ElementType > const * pIterator
            ) noexcept -> bool;

        private:
            auto __removeConst ( // NOLINT(bugprone-reserved-identifier)
                    AbstractAddressIterator < __ElementType const > const * pIterator
            ) noexcept -> bool;
        };

    }
}

#include "array/impl/Array.hpp"

#include "shared/array/impl/Array.hpp"

#include "shared/iterator/impl/AddressIterator.hpp"

#include "shared/delegateIterator/impl/AbstractDelegateIterator.hpp"
#include "shared/delegateIterator/impl/DelegateIterator.hpp"

#include "shared/collectionInternalCommunication/server/impl/ListServer.hpp"
#include "shared/collectionInternalCommunication/server/impl/DelegateIterableServer.hpp"

#endif // __CDS_EX_ARRAY_HPP__
