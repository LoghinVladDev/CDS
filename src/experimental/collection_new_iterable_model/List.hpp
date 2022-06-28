//
// Created by loghin on 6/27/22.
//

#ifndef __CDS_EX_LIST_HPP__
#define __CDS_EX_LIST_HPP__

#include <CDS/experimental/MutableCollection>

#include "shared/delegateIterator/BidirectionalDelegateWrapperIterator.hpp"

#include "shared/collectionInternalCommunication/client/DelegateBackwardIterableClient.hpp"
#include "shared/collectionInternalCommunication/client/DelegateBackwardConstIterableClient.hpp"
#include "shared/collectionInternalCommunication/client/AbstractIteratorRelativeInsertionClient.hpp"
#include "shared/collectionInternalCommunication/client/AbstractConstIteratorRelativeInsertionClient.hpp"
#include "shared/collectionInternalCommunication/client/BoundaryInsertionClient.hpp"

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {

        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        class List :
                public MutableCollection < __ElementType >,
                public __hidden :: __impl :: __DelegateForwardIterableClient <
                        List < __ElementType >,
                        __ElementType,
                        true
                >,
                public __hidden :: __impl :: __DelegateBackwardIterableClient <
                        List < __ElementType >,
                        __ElementType,
                        true
                >,
                public __hidden :: __impl :: __DelegateForwardConstIterableClient <
                        List < __ElementType >,
                        __ElementType,
                        true
                >,
                public __hidden :: __impl :: __DelegateBackwardConstIterableClient <
                        List < __ElementType >,
                        __ElementType,
                        true
                >,
                public __hidden :: __impl :: __BoundaryInsertionClient <
                        List < __ElementType >,
                        __ElementType,
                        __ElementType
                >,
                public __hidden :: __impl :: __AbstractIteratorRelativeInsertionClient <
                        List < __ElementType >,
                        __ElementType,
                        __ElementType
                >,
                public __hidden :: __impl :: __AbstractConstIteratorRelativeInsertionClient <
                        List < __ElementType >,
                        __ElementType,
                        __ElementType
                > {

        public:
            using ElementType = __ElementType;

        protected:
            using DelegateForwardIterableClient =
                    __hidden :: __impl :: __DelegateForwardIterableClient <
                            List < __ElementType >,
                            __ElementType,
                            true
                    >;

        protected:
            using DelegateBackwardIterableClient =
                    __hidden :: __impl :: __DelegateBackwardIterableClient <
                            List < __ElementType >,
                            __ElementType,
                            true
                    >;

        protected:
            using DelegateForwardConstIterableClient =
                    __hidden :: __impl :: __DelegateForwardConstIterableClient <
                            List < __ElementType >,
                            __ElementType,
                            true
                    >;

        protected:
            using DelegateBackwardConstIterableClient =
                    __hidden :: __impl :: __DelegateBackwardConstIterableClient <
                            List < __ElementType >,
                            __ElementType,
                            true
                    >;

        protected:
            using BoundaryInsertionClient =
                    __hidden :: __impl :: __BoundaryInsertionClient <
                            List < __ElementType >,
                            __ElementType,
                            __ElementType
                    >;

        protected:
            using AbstractIteratorRelativeInsertionClient =
                    __hidden :: __impl :: __AbstractIteratorRelativeInsertionClient <
                            List < __ElementType >,
                            __ElementType,
                            __ElementType
                    >;

        protected:
            using AbstractConstIteratorRelativeInsertionClient =
                    __hidden :: __impl :: __AbstractConstIteratorRelativeInsertionClient <
                            List < __ElementType >,
                            __ElementType,
                            __ElementType
                    >;

        protected:
            using MutableCollection = MutableCollection < __ElementType >;

        protected:
            constexpr List () noexcept;

        protected:
            constexpr List (
                    List const & list
            ) noexcept;

        protected:
            constexpr List (
                    List && list
            ) noexcept;

        protected:
            __CDS_cpplang_ConstexprDestructor ~List () noexcept override;

        public: using DelegateForwardIterableClient :: begin;
        public: using DelegateForwardIterableClient :: end;

        public: using DelegateBackwardIterableClient :: rbegin;
        public: using DelegateBackwardIterableClient :: rend;

        public: using DelegateForwardConstIterableClient :: begin;
        public: using DelegateForwardConstIterableClient :: end;
        public: using DelegateForwardConstIterableClient :: cbegin;
        public: using DelegateForwardConstIterableClient :: cend;

        public: using DelegateBackwardConstIterableClient :: rbegin;
        public: using DelegateBackwardConstIterableClient :: rend;
        public: using DelegateBackwardConstIterableClient :: crbegin;
        public: using DelegateBackwardConstIterableClient :: crend;

        public: using BoundaryInsertionClient :: pushBack;
        public: using BoundaryInsertionClient :: pushBackAll;
        public: using BoundaryInsertionClient :: pushBackAllOf;
        public: using BoundaryInsertionClient :: pushFront;
        public: using BoundaryInsertionClient :: pushFrontAll;
        public: using BoundaryInsertionClient :: pushFrontAllOf;
        public: using BoundaryInsertionClient :: emplaceBack;
        public: using BoundaryInsertionClient :: emplaceFront;

        public: using AbstractIteratorRelativeInsertionClient :: insertBefore;
        public: using AbstractIteratorRelativeInsertionClient :: insertAllBefore;
        public: using AbstractIteratorRelativeInsertionClient :: insertAllOfBefore;
        public: using AbstractIteratorRelativeInsertionClient :: insertAfter;
        public: using AbstractIteratorRelativeInsertionClient :: insertAllAfter;
        public: using AbstractIteratorRelativeInsertionClient :: insertAllOfAfter;
        public: using AbstractIteratorRelativeInsertionClient :: emplaceBefore;
        public: using AbstractIteratorRelativeInsertionClient :: emplaceAfter;

        public: using AbstractConstIteratorRelativeInsertionClient :: insertBefore;
        public: using AbstractConstIteratorRelativeInsertionClient :: insertAllBefore;
        public: using AbstractConstIteratorRelativeInsertionClient :: insertAllOfBefore;
        public: using AbstractConstIteratorRelativeInsertionClient :: insertAfter;
        public: using AbstractConstIteratorRelativeInsertionClient :: insertAllAfter;
        public: using AbstractConstIteratorRelativeInsertionClient :: insertAllOfAfter;
        public: using AbstractConstIteratorRelativeInsertionClient :: emplaceBefore;
        public: using AbstractConstIteratorRelativeInsertionClient :: emplaceAfter;

        public:
            __CDS_NoDiscard auto toString () const noexcept -> String override;

        public:
            auto clear () noexcept -> void override = 0;

        public:
            virtual auto get (
                    Index index
            ) noexcept ( false ) -> ElementType &;

        public:
            virtual auto get (
                    Index index
            ) const noexcept ( false ) -> ElementType const &;

        public:
            template <
                    typename __CollectionType,
                    typename __TElementType = __ElementType,
                    cds :: meta :: EnableIf <
                            cds :: meta :: isCopyConstructible < __TElementType > ()
                    > = 0
            > auto sub (
                    __CollectionType  & storeIn,
                    Index               from,
                    Index               in
            ) const noexcept -> __CollectionType &;

        public:
            template <
                    typename __CollectionType,
                    typename __TElementType = __ElementType,
                    cds :: meta :: EnableIf <
                            cds :: meta :: isCopyConstructible < __TElementType > ()
                    > = 0
            > auto sub (
                    Index               from,
                    Index               in
            ) const noexcept -> __CollectionType;

        public:
            template <
                    template < typename ... > class __CollectionType,
                    typename __TElementType = __ElementType,
                    cds :: meta :: EnableIf <
                            cds :: meta :: isCopyConstructible < __TElementType > ()
                    > = 0
            > auto sub (
                    Index               from,
                    Index               in
            ) const noexcept -> __CollectionType < __ElementType >;

        public:
            auto operator [] (
                    Index index
            ) noexcept (false) -> ElementType &;

        public:
            auto operator [] (
                    Index index
            ) const noexcept (false) -> ElementType const &;

        public:
            virtual auto popFront () noexcept -> void = 0;

        public:
            virtual auto popBack () noexcept -> void = 0;

        };

    }
}

#include "shared/delegateIterator/impl/BidirectionalDelegateWrapperIterator.hpp"

#include "shared/collectionInternalCommunication/client/impl/DelegateBackwardIterableClient.hpp"
#include "shared/collectionInternalCommunication/client/impl/DelegateBackwardConstIterableClient.hpp"
#include "shared/collectionInternalCommunication/client/impl/AbstractIteratorRelativeInsertionClient.hpp"
#include "shared/collectionInternalCommunication/client/impl/AbstractConstIteratorRelativeInsertionClient.hpp"
#include "shared/collectionInternalCommunication/client/impl/BoundaryInsertionClient.hpp"

#include "list/impl/List.hpp"

#endif // __CDS_EX_LIST_HPP__
