//
// Created by loghin on 7/2/22.
//

#ifndef __CDS_EX_ARRAY_HPP__
#define __CDS_EX_ARRAY_HPP__

#include <CDS/experimental/List>
#include "shared/collectionInternalCommunication/server/ListServer.hpp"
#include "shared/iterator/AddressIterator.hpp"
#include "shared/array/Array.hpp"
#include "shared/delegateIterator/AbstractDelegateIterator.hpp"
#include "shared/delegateIterator/DelegateIterator.hpp"
#include "shared/collectionInternalCommunication/server/DelegateIterableServer.hpp"

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {

        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        class Array :
                public List < __ElementType >,
                protected __hidden :: __impl :: __Array <
                        __ElementType,
                        & cds :: meta :: equals < __ElementType >
                >,
                protected __hidden :: __impl :: __ListServer <
                        Array < __ElementType >,
                        __ElementType
                >,
                public __hidden :: __impl :: __LocalRandomInsertionClient <
                        Array < __ElementType >,
                        __ElementType,
                        __ElementType
                >,
                public __hidden :: __impl :: __LocalBoundaryInsertionClient <
                        Array < __ElementType >,
                        __ElementType,
                        __ElementType
                >,
                public __hidden :: __impl :: __DelegateIterableServer <
                        Array < __ElementType >,
                        __ElementType,
                        true,
                        true,
                        AddressIterator < __ElementType, false >,
                        AddressIterator < __ElementType const, false >,
                        AddressIterator < __ElementType, true >,
                        AddressIterator < __ElementType const, true >
                > {

        private:
            template < typename, typename >
            friend class cds :: experimental :: __hidden :: __impl :: __ListServer; // NOLINT(bugprone-reserved-identifier)

        protected:
            using ListServer =
                    __hidden :: __impl :: __ListServer <
                            Array < __ElementType >,
                            __ElementType
                    >;

        protected:
            using ArrayBase =
                    __hidden :: __impl :: __Array <
                            __ElementType,
                            & cds :: meta :: equals < __ElementType >
                    >;

        protected:
            using LocalRandomInsertionClient =
                    __hidden :: __impl :: __LocalRandomInsertionClient <
                            Array < __ElementType >,
                            __ElementType,
                            __ElementType
                    >;

        protected:
            using LocalBoundaryInsertionClient =
                    __hidden :: __impl :: __LocalBoundaryInsertionClient <
                            Array < __ElementType >,
                            __ElementType,
                            __ElementType
                    >;

        private: friend LocalBoundaryInsertionClient;
        private: friend LocalRandomInsertionClient;

        public: using ElementType           = __ElementType;
        public: using Iterator              = typename ArrayBase :: __a_Iterator;
        public: using ConstIterator         = typename ArrayBase :: __a_ConstIterator;
        public: using ReverseIterator       = typename ArrayBase :: __a_ReverseIterator;
        public: using ConstReverseIterator  = typename ArrayBase :: __a_ConstReverseIterator;

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

        public: using LocalRandomInsertionClient :: insert;
        public: using LocalRandomInsertionClient :: insertAll;
        public: using LocalRandomInsertionClient :: insertAllOf;
        public: using LocalRandomInsertionClient :: add;
        public: using LocalRandomInsertionClient :: addAll;
        public: using LocalRandomInsertionClient :: addAllOf;
        public: using LocalRandomInsertionClient :: emplace;

        public: using LocalBoundaryInsertionClient :: pushBack;
        public: using LocalBoundaryInsertionClient :: pushBackAll;
        public: using LocalBoundaryInsertionClient :: pushBackAllOf;
        public: using LocalBoundaryInsertionClient :: pushFront;
        public: using LocalBoundaryInsertionClient :: pushFrontAll;
        public: using LocalBoundaryInsertionClient :: pushFrontAllOf;
        public: using LocalBoundaryInsertionClient :: append;
        public: using LocalBoundaryInsertionClient :: prepend;
        public: using LocalBoundaryInsertionClient :: emplaceBack;
        public: using LocalBoundaryInsertionClient :: emplaceFront;

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
            auto __new ( // NOLINT(bugprone-reserved-identifier)
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
        };

    }
}

#include "array/impl/Array.hpp"
#include "shared/collectionInternalCommunication/server/impl/ListServer.hpp"
#include "shared/iterator/impl/AddressIterator.hpp"
#include "shared/array/impl/Array.hpp"
#include "shared/delegateIterator/impl/AbstractDelegateIterator.hpp"
#include "shared/delegateIterator/impl/DelegateIterator.hpp"
#include "shared/collectionInternalCommunication/server/impl/DelegateIterableServer.hpp"

#endif // __CDS_EX_ARRAY_HPP__
