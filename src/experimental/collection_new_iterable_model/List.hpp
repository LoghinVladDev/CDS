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
#include "shared/collectionInternalCommunication/client/IndexedOperationsClient.hpp"
#include "shared/collectionInternalCommunication/client/SortingClient.hpp"
#include "shared/collectionInternalCommunication/client/ReplacingClient.hpp"
#include "shared/collectionInternalCommunication/client/ReplacingOfClient.hpp"
#include "shared/collectionInternalCommunication/client/FunctionalReplacingClient.hpp"
#include "shared/collectionInternalCommunication/client/IndicesClient.hpp"
#include "shared/collectionInternalCommunication/client/IndicesOfClient.hpp"
#include "shared/collectionInternalCommunication/client/FunctionalIndicesClient.hpp"

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
                >,
                public __hidden :: __impl :: __IndexedOperationsClient <
                        List < __ElementType >,
                        __ElementType
                >,
                public __hidden :: __impl :: __SortingClient <
                        List < __ElementType >,
                        __ElementType
                >,
                public __hidden :: __impl :: __ReplacingClient <
                        List < __ElementType >,
                        __ElementType
                >,
                public __hidden :: __impl :: __ReplacingOfClient <
                        List < __ElementType >,
                        __ElementType,
                        Collection < __ElementType >,
                        & __hidden :: __impl :: __collectionContains < __ElementType >
                >,
                public __hidden :: __impl :: __ReplacingOfClient <
                        List < __ElementType >,
                        __ElementType,
                        std :: initializer_list < __ElementType >,
                        & __hidden :: __impl :: __initializerListContains < __ElementType, & cds :: meta :: equals >
                >,
                public __hidden :: __impl :: __FunctionalReplacingClient <
                        List < __ElementType >,
                        __ElementType
                >,
                public __hidden :: __impl :: __IndicesClient <
                        List < __ElementType >,
                        __ElementType
                >,
                public __hidden :: __impl :: __IndicesOfClient <
                        List < __ElementType >,
                        __ElementType,
                        Collection < __ElementType >,
                        & __hidden :: __impl :: __collectionContains < __ElementType >
                >,
                public __hidden :: __impl :: __IndicesOfClient <
                        List < __ElementType >,
                        __ElementType,
                        std :: initializer_list < __ElementType >,
                        & __hidden :: __impl :: __initializerListContains < __ElementType, & cds :: meta :: equals >
                >,
                public __hidden :: __impl :: __FunctionalIndicesClient <
                        List < __ElementType >,
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
            using IndexedOperationsClient =
                    __hidden :: __impl :: __IndexedOperationsClient <
                            List < __ElementType >,
                            __ElementType
                    >;

        protected:
            using SortingClient =
                    __hidden :: __impl :: __SortingClient <
                            List < __ElementType >,
                            __ElementType
                    >;

        protected:
            using ReplacingClient =
                    __hidden :: __impl :: __ReplacingClient <
                            List < __ElementType >,
                            __ElementType
                    >;

        protected:
            using ReplacingOfCollectionClient =
                    __hidden :: __impl :: __ReplacingOfClient <
                            List < __ElementType >,
                            __ElementType,
                            Collection < __ElementType >,
                            & __hidden :: __impl :: __collectionContains < __ElementType >
                    >;

        protected:
            using ReplacingOfInitializerListClient =
                    __hidden :: __impl :: __ReplacingOfClient <
                            List < __ElementType >,
                            __ElementType,
                            std :: initializer_list < __ElementType >,
                            & __hidden :: __impl :: __initializerListContains < __ElementType, & cds :: meta :: equals >
                    >;

        protected:
            using FunctionalReplacingClient =
                    __hidden :: __impl :: __FunctionalReplacingClient <
                            List < __ElementType >,
                            __ElementType
                    >;

        protected:
            using IndicesClient =
                    __hidden :: __impl :: __IndicesClient <
                            List < __ElementType >,
                            __ElementType
                    >;

        protected:
            using IndicesOfCollectionClient =
                    __hidden :: __impl :: __IndicesOfClient <
                            List < __ElementType >,
                            __ElementType,
                            Collection < __ElementType >,
                            & __hidden :: __impl :: __collectionContains < __ElementType >
                    >;

        protected:
            using IndicesOfInitializerListClient =
                    __hidden :: __impl :: __IndicesOfClient <
                            List < __ElementType >,
                            __ElementType,
                            std :: initializer_list < __ElementType >,
                            & __hidden :: __impl :: __initializerListContains < __ElementType, & cds :: meta :: equals >
                    >;

        protected:
            using FunctionalIndcesClient =
                    __hidden :: __impl :: __FunctionalIndicesClient <
                            List < __ElementType >,
                            __ElementType
                    >;

        protected:
            using MutableCollection = MutableCollection < __ElementType >;

        public:
            static Index const invalidIndex = -1;

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

        public: using IndexedOperationsClient :: sub;
        public: using IndexedOperationsClient :: operator[];
        public: using IndexedOperationsClient :: removeAt;

        public: using SortingClient :: sort;

        public: using ReplacingClient :: replace;
        public: using ReplacingClient :: replaceFirst;
        public: using ReplacingClient :: replaceLast;
        public: using ReplacingClient :: replaceAll;

        public: using ReplacingOfCollectionClient :: replaceOf;
        public: using ReplacingOfCollectionClient :: replaceFirstOf;
        public: using ReplacingOfCollectionClient :: replaceLastOf;
        public: using ReplacingOfCollectionClient :: replaceAllOf;
        public: using ReplacingOfCollectionClient :: replaceNotOf;
        public: using ReplacingOfCollectionClient :: replaceFirstNotOf;
        public: using ReplacingOfCollectionClient :: replaceLastNotOf;
        public: using ReplacingOfCollectionClient :: replaceAllNotOf;

        public: using ReplacingOfInitializerListClient :: replaceOf;
        public: using ReplacingOfInitializerListClient :: replaceFirstOf;
        public: using ReplacingOfInitializerListClient :: replaceLastOf;
        public: using ReplacingOfInitializerListClient :: replaceAllOf;
        public: using ReplacingOfInitializerListClient :: replaceNotOf;
        public: using ReplacingOfInitializerListClient :: replaceFirstNotOf;
        public: using ReplacingOfInitializerListClient :: replaceLastNotOf;
        public: using ReplacingOfInitializerListClient :: replaceAllNotOf;

        public: using FunctionalReplacingClient :: replaceThat;
        public: using FunctionalReplacingClient :: replaceFirstThat;
        public: using FunctionalReplacingClient :: replaceLastThat;
        public: using FunctionalReplacingClient :: replaceAllThat;
        public: using FunctionalReplacingClient :: replaceThatBy;
        public: using FunctionalReplacingClient :: replaceFirstThatBy;
        public: using FunctionalReplacingClient :: replaceLastThatBy;
        public: using FunctionalReplacingClient :: replaceAllThatBy;

        public: using IndicesClient :: indicesOf;
        public: using IndicesClient :: firstIndexOf;
        public: using IndicesClient :: lastIndexOf;
        public: using IndicesClient :: allIndicesOf;

        public: using IndicesOfCollectionClient :: indicesOfFrom;
        public: using IndicesOfCollectionClient :: firstIndexOfFrom;
        public: using IndicesOfCollectionClient :: lastIndexOfFrom;
        public: using IndicesOfCollectionClient :: allIndicesOfFrom;
        public: using IndicesOfCollectionClient :: indicesOfNotFrom;
        public: using IndicesOfCollectionClient :: firstIndexOfNotFrom;
        public: using IndicesOfCollectionClient :: lastIndexOfNotFrom;
        public: using IndicesOfCollectionClient :: allIndicesOfNotFrom;

        public: using IndicesOfInitializerListClient :: indicesOfFrom;
        public: using IndicesOfInitializerListClient :: firstIndexOfFrom;
        public: using IndicesOfInitializerListClient :: lastIndexOfFrom;
        public: using IndicesOfInitializerListClient :: allIndicesOfFrom;
        public: using IndicesOfInitializerListClient :: indicesOfNotFrom;
        public: using IndicesOfInitializerListClient :: firstIndexOfNotFrom;
        public: using IndicesOfInitializerListClient :: lastIndexOfNotFrom;
        public: using IndicesOfInitializerListClient :: allIndicesOfNotFrom;

        public: using FunctionalIndcesClient :: indicesOfThat;
        public: using FunctionalIndcesClient :: firstIndexOfThat;
        public: using FunctionalIndcesClient :: lastIndexOfThat;
        public: using FunctionalIndcesClient :: allIndicesOfThat;

        public:
            __CDS_NoDiscard auto toString () const noexcept -> String override;

        public:
            auto clear () noexcept -> void override = 0;

        public:
            virtual auto popFront () noexcept -> void = 0;

        public:
            virtual auto popBack () noexcept -> void = 0;

        public:
            virtual auto front () noexcept (false) -> ElementType & = 0;

        public:
            virtual auto front () const noexcept (false) -> ElementType const & = 0;

        public:
            virtual auto back () noexcept (false) -> ElementType & = 0;

        public:
            virtual auto back () const noexcept (false) -> ElementType const & = 0;

        public:
            virtual auto makeUnique () noexcept -> void = 0;

        protected:
            virtual auto get (
                    Index index
            ) noexcept ( false ) -> ElementType & = 0;

        protected:
            virtual auto get (
                    Index index
            ) const noexcept ( false ) -> ElementType const & = 0;

        public:
            virtual auto removeAt (
                    Index index
            ) noexcept -> bool = 0;
        };

    }
}

#include "shared/delegateIterator/impl/BidirectionalDelegateWrapperIterator.hpp"

#include "shared/collectionInternalCommunication/client/impl/DelegateBackwardIterableClient.hpp"
#include "shared/collectionInternalCommunication/client/impl/DelegateBackwardConstIterableClient.hpp"
#include "shared/collectionInternalCommunication/client/impl/AbstractIteratorRelativeInsertionClient.hpp"
#include "shared/collectionInternalCommunication/client/impl/AbstractConstIteratorRelativeInsertionClient.hpp"
#include "shared/collectionInternalCommunication/client/impl/BoundaryInsertionClient.hpp"
#include "shared/collectionInternalCommunication/client/impl/IndexedOperationsClient.hpp"
#include "shared/collectionInternalCommunication/client/impl/SortingClient.hpp"
#include "shared/collectionInternalCommunication/client/impl/ReplacingClient.hpp"
#include "shared/collectionInternalCommunication/client/impl/ReplacingOfClient.hpp"
#include "shared/collectionInternalCommunication/client/impl/FunctionalReplacingClient.hpp"
#include "shared/collectionInternalCommunication/client/impl/IndicesClient.hpp"
#include "shared/collectionInternalCommunication/client/impl/IndicesOfClient.hpp"
#include "shared/collectionInternalCommunication/client/impl/FunctionalIndicesClient.hpp"

#include "list/impl/List.hpp"

#endif // __CDS_EX_LIST_HPP__
