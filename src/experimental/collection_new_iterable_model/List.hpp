//
// Created by loghin on 6/27/22.
//

#ifndef __CDS_EX_LIST_HPP__
#define __CDS_EX_LIST_HPP__

#include <CDS/experimental/MutableCollection>

#include "shared/delegateIterator/BidirectionalDelegateWrapperIterator.hpp"

#include "shared/collectionInternalCommunication/client/primitive/DelegateBackwardIterablePrimitiveClient.hpp"
#include "shared/collectionInternalCommunication/client/primitive/DelegateBackwardConstIterablePrimitiveClient.hpp"
#include "shared/collectionInternalCommunication/client/primitive/IteratorRelativeInsertionPrimitiveClient.hpp"
#include "shared/collectionInternalCommunication/client/primitive/ConstIteratorRelativeInsertionPrimitiveClient.hpp"
#include "shared/collectionInternalCommunication/client/primitive/BoundaryInsertionPrimitiveClient.hpp"
#include "shared/collectionInternalCommunication/client/primitive/IndexedOperationsPrimitiveClient.hpp"

#include "shared/collectionInternalCommunication/client/composite/SortCompositeClient.hpp"
#include "shared/collectionInternalCommunication/client/composite/ReplaceCompositeClient.hpp"
#include "shared/collectionInternalCommunication/client/composite/ReplaceOfCompositeClient.hpp"
#include "shared/collectionInternalCommunication/client/composite/ReplaceByCompositeClient.hpp"
#include "shared/collectionInternalCommunication/client/composite/IndicesCompositeClient.hpp"
#include "shared/collectionInternalCommunication/client/composite/IndicesOfCompositeClient.hpp"
#include "shared/collectionInternalCommunication/client/composite/IndicesByCompositeClient.hpp"

#include "list/ListConstructs.hpp"

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {

        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        class List :
                public MutableCollection < __ElementType >,
                public __hidden :: __impl :: __ListDelegateForwardIterableClient < __ElementType >,
                public __hidden :: __impl :: __ListDelegateBackwardIterableClient < __ElementType >,
                public __hidden :: __impl :: __ListDelegateForwardConstIterableClient < __ElementType >,
                public __hidden :: __impl :: __ListDelegateBackwardConstIterableClient < __ElementType >,
                public __hidden :: __impl :: __ListBoundaryInsertionClient < __ElementType >,
                public __hidden :: __impl :: __ListIteratorRelativeInsertionClient < __ElementType >,
                public __hidden :: __impl :: __ListConstIteratorRelativeInsertionClient < __ElementType >,
                public __hidden :: __impl :: __ListIndexedOperationsClient < __ElementType >,
                public __hidden :: __impl :: __ListSortClient < __ElementType >,
                public __hidden :: __impl :: __ListReplaceClient < __ElementType >,
                public __hidden :: __impl :: __ListReplaceOfCollectionClient < __ElementType >,
                public __hidden :: __impl :: __ListReplaceOfInitializerListClient < __ElementType >,
                public __hidden :: __impl :: __ListReplaceByClient < __ElementType >,
                public __hidden :: __impl :: __ListIndicesClient < __ElementType >,
                public __hidden :: __impl :: __ListIndicesOfCollectionClient < __ElementType >,
                public __hidden :: __impl :: __ListIndicesOfInitializerListClient < __ElementType >,
                public __hidden :: __impl :: __ListIndicesByClient < __ElementType > {

        public:     using ElementType                           = __ElementType;
        protected:  using DelegateForwardIterableClient         = __hidden :: __impl :: __ListDelegateForwardIterableClient < __ElementType >;
        protected:  using DelegateBackwardIterableClient        = __hidden :: __impl :: __ListDelegateBackwardIterableClient < __ElementType >;
        protected:  using DelegateForwardConstIterableClient    = __hidden :: __impl :: __ListDelegateForwardConstIterableClient < __ElementType >;
        protected:  using DelegateBackwardConstIterableClient   = __hidden :: __impl :: __ListDelegateBackwardConstIterableClient < __ElementType >;
        protected:  using BoundaryInsertionClient               = __hidden :: __impl :: __ListBoundaryInsertionClient < __ElementType >;
        protected:  using IteratorRelativeInsertionClient       = __hidden :: __impl :: __ListIteratorRelativeInsertionClient < __ElementType >;
        protected:  using ConstIteratorRelativeInsertionClient  = __hidden :: __impl :: __ListConstIteratorRelativeInsertionClient < __ElementType >;
        protected:  using IndexedOperationsClient               = __hidden :: __impl :: __ListIndexedOperationsClient < __ElementType >;
        protected:  using SortClient                            = __hidden :: __impl :: __ListSortClient < __ElementType >;
        protected:  using ReplaceClient                         = __hidden :: __impl :: __ListReplaceClient < __ElementType >;
        protected:  using ReplaceOfCollectionClient             = __hidden :: __impl :: __ListReplaceOfCollectionClient < __ElementType >;
        protected:  using ReplaceOfInitializerListClient        = __hidden :: __impl :: __ListReplaceOfInitializerListClient < __ElementType >;
        protected:  using ReplaceByClient                       = __hidden :: __impl :: __ListReplaceByClient < __ElementType >;
        protected:  using IndicesClient                         = __hidden :: __impl :: __ListIndicesClient < __ElementType >;
        protected:  using IndicesOfCollectionClient             = __hidden :: __impl :: __ListIndicesOfCollectionClient < __ElementType >;
        protected:  using IndicesOfInitializerListClient        = __hidden :: __impl :: __ListIndicesOfInitializerListClient < __ElementType >;
        protected:  using IndicesByClient                       = __hidden :: __impl :: __ListIndicesByClient < __ElementType >;

        protected:
            using MutableCollectionBase = MutableCollection < __ElementType >;

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

        public: using IteratorRelativeInsertionClient :: insertBefore;
        public: using IteratorRelativeInsertionClient :: insertAllBefore;
        public: using IteratorRelativeInsertionClient :: insertAllOfBefore;
        public: using IteratorRelativeInsertionClient :: insertAfter;
        public: using IteratorRelativeInsertionClient :: insertAllAfter;
        public: using IteratorRelativeInsertionClient :: insertAllOfAfter;
        public: using IteratorRelativeInsertionClient :: emplaceBefore;
        public: using IteratorRelativeInsertionClient :: emplaceAfter;

        public: using ConstIteratorRelativeInsertionClient :: insertBefore;
        public: using ConstIteratorRelativeInsertionClient :: insertAllBefore;
        public: using ConstIteratorRelativeInsertionClient :: insertAllOfBefore;
        public: using ConstIteratorRelativeInsertionClient :: insertAfter;
        public: using ConstIteratorRelativeInsertionClient :: insertAllAfter;
        public: using ConstIteratorRelativeInsertionClient :: insertAllOfAfter;
        public: using ConstIteratorRelativeInsertionClient :: emplaceBefore;
        public: using ConstIteratorRelativeInsertionClient :: emplaceAfter;

        public: using IndexedOperationsClient :: sub;
        public: using IndexedOperationsClient :: operator[];
        public: using IndexedOperationsClient :: removeAt;

        public: using SortClient :: sort;

        public: using ReplaceClient :: replace;
        public: using ReplaceClient :: replaceFirst;
        public: using ReplaceClient :: replaceLast;
        public: using ReplaceClient :: replaceAll;

        public: using ReplaceOfCollectionClient :: replaceOf;
        public: using ReplaceOfCollectionClient :: replaceFirstOf;
        public: using ReplaceOfCollectionClient :: replaceLastOf;
        public: using ReplaceOfCollectionClient :: replaceAllOf;
        public: using ReplaceOfCollectionClient :: replaceNotOf;
        public: using ReplaceOfCollectionClient :: replaceFirstNotOf;
        public: using ReplaceOfCollectionClient :: replaceLastNotOf;
        public: using ReplaceOfCollectionClient :: replaceAllNotOf;

        public: using ReplaceOfInitializerListClient :: replaceOf;
        public: using ReplaceOfInitializerListClient :: replaceFirstOf;
        public: using ReplaceOfInitializerListClient :: replaceLastOf;
        public: using ReplaceOfInitializerListClient :: replaceAllOf;
        public: using ReplaceOfInitializerListClient :: replaceNotOf;
        public: using ReplaceOfInitializerListClient :: replaceFirstNotOf;
        public: using ReplaceOfInitializerListClient :: replaceLastNotOf;
        public: using ReplaceOfInitializerListClient :: replaceAllNotOf;

        public: using ReplaceByClient :: replaceThat;
        public: using ReplaceByClient :: replaceFirstThat;
        public: using ReplaceByClient :: replaceLastThat;
        public: using ReplaceByClient :: replaceAllThat;
        public: using ReplaceByClient :: replaceThatBy;
        public: using ReplaceByClient :: replaceFirstThatBy;
        public: using ReplaceByClient :: replaceLastThatBy;
        public: using ReplaceByClient :: replaceAllThatBy;

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

        public: using IndicesByClient :: indicesOfThat;
        public: using IndicesByClient :: firstIndexOfThat;
        public: using IndicesByClient :: lastIndexOfThat;
        public: using IndicesByClient :: allIndicesOfThat;

        public:
            __CDS_NoDiscard auto toString () const noexcept -> String override;

        public:
            auto clear () noexcept -> void override = 0;

        public:
            virtual auto popFront () noexcept -> void = 0;

        public:
            virtual auto popBack () noexcept -> void = 0;

        public:
            __CDS_NoDiscard __CDS_cpplang_VirtualConstexpr virtual auto front () noexcept (false) -> ElementType & = 0;

        public:
            __CDS_NoDiscard __CDS_cpplang_VirtualConstexpr virtual auto front () const noexcept (false) -> ElementType const & = 0;

        public:
            __CDS_NoDiscard __CDS_cpplang_VirtualConstexpr virtual auto back () noexcept (false) -> ElementType & = 0;

        public:
            __CDS_NoDiscard __CDS_cpplang_VirtualConstexpr virtual auto back () const noexcept (false) -> ElementType const & = 0;

        public:
            __CDS_NoDiscard __CDS_cpplang_VirtualConstexpr virtual auto get (
                    Index index
            ) noexcept ( false ) -> ElementType & = 0;

        public:
            __CDS_NoDiscard __CDS_cpplang_VirtualConstexpr virtual auto get (
                    Index index
            ) const noexcept ( false ) -> ElementType const & = 0;

        public:
            virtual auto removeAt (
                    Index index
            ) noexcept -> bool = 0;

        protected:
            __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto circularAdjustedIndex (
                    Index index
            ) const noexcept -> Index;
        };

    }
}

#include "shared/delegateIterator/impl/BidirectionalDelegateWrapperIterator.hpp"

#include "shared/collectionInternalCommunication/client/primitive/impl/DelegateBackwardIterablePrimitiveClient.hpp"
#include "shared/collectionInternalCommunication/client/primitive/impl/DelegateBackwardConstIterablePrimitiveClient.hpp"
#include "shared/collectionInternalCommunication/client/primitive/impl/IteratorRelativeInsertionPrimitiveClient.hpp"
#include "shared/collectionInternalCommunication/client/primitive/impl/ConstIteratorRelativeInsertionPrimitiveClient.hpp"
#include "shared/collectionInternalCommunication/client/primitive/impl/BoundaryInsertionPrimitiveClient.hpp"
#include "shared/collectionInternalCommunication/client/primitive/impl/IndexedOperationsPrimitiveClient.hpp"

#include "shared/collectionInternalCommunication/client/composite/impl/SortCompositeClient.hpp"
#include "shared/collectionInternalCommunication/client/composite/impl/ReplaceCompositeClient.hpp"
#include "shared/collectionInternalCommunication/client/composite/impl/ReplaceOfCompositeClient.hpp"
#include "shared/collectionInternalCommunication/client/composite/impl/ReplaceByCompositeClient.hpp"
#include "shared/collectionInternalCommunication/client/composite/impl/IndicesCompositeClient.hpp"
#include "shared/collectionInternalCommunication/client/composite/impl/IndicesOfCompositeClient.hpp"
#include "shared/collectionInternalCommunication/client/composite/impl/IndicesByCompositeClient.hpp"

#include "list/impl/List.hpp"

#endif // __CDS_EX_LIST_HPP__
