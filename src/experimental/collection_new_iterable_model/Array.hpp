/*
 * Created by loghin on 7/2/22.
 */

#ifndef __CDS_EX_ARRAY_HPP__
#define __CDS_EX_ARRAY_HPP__ /* NOLINT(bugprone-reserved-identifier) */

#include <CDS/experimental/List>

#include "array/Predeclaration.hpp"

#include "shared/iterator/AddressIterator.hpp"

#include "shared/collectionInternalCommunication/server/ListServerDispatcher.hpp"

#include "shared/array/Array.hpp"

#include "shared/delegateIterator/AbstractDelegateIterator.hpp"
#include "shared/delegateIterator/DelegateIterator.hpp"

#include "shared/collectionInternalCommunication/server/ListServer.hpp"

#include "array/Constructs.hpp"

namespace cds { /* NOLINT(modernize-concat-nested-namespaces) */
    namespace experimental {

        template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
        class Array :
                public List < __ElementType >,
                protected __hidden :: __impl :: __ArrayServer < __ElementType >,
                public __hidden :: __impl :: __ArrayImplementation < __ElementType >,
                public __hidden :: __impl :: __ArrayDispatcher< __ElementType >,
                public __hidden :: __impl :: __ArrayRandomInsertionClient < __ElementType >,
                public __hidden :: __impl :: __ArrayBoundaryInsertionClient < __ElementType >,
                public __hidden :: __impl :: __ArrayIteratorRelativeInsertionClient < __ElementType >,
                public __hidden :: __impl :: __ArrayConstIteratorRelativeInsertionClient < __ElementType >,
                public __hidden :: __impl :: __ArrayFindOfCollectionClient < __ElementType >,
                public __hidden :: __impl :: __ArrayFindOfInitializerListClient < __ElementType >,
                public __hidden :: __impl :: __ArrayFindConstOfCollectionClient < __ElementType >,
                public __hidden :: __impl :: __ArrayFindConstOfInitializerListClient < __ElementType >,
                public __hidden :: __impl :: __ArrayFindByClient < __ElementType >,
                public __hidden :: __impl :: __ArrayFindConstByClient < __ElementType >,
                public __hidden :: __impl :: __ArrayIteratorRemoveClient < __ElementType >,
                public __hidden :: __impl :: __ArrayConstIteratorRemoveClient < __ElementType >,
                public __hidden :: __impl :: __ArrayRemoveOfCollectionClient < __ElementType >,
                public __hidden :: __impl :: __ArrayRemoveOfInitializerListClient < __ElementType >,
                public __hidden :: __impl :: __ArrayRemoveByClient < __ElementType >,
                public __hidden :: __impl :: __ArrayGenericStatementsClient < __ElementType >,
                public __hidden :: __impl :: __ArrayGenericConstStatementsClient < __ElementType >,
                public __hidden :: __impl :: __ArraySortClient < __ElementType >,
                public __hidden :: __impl :: __ArrayReplaceClient < __ElementType >,
                public __hidden :: __impl :: __ArrayReplaceOfCollectionClient < __ElementType >,
                public __hidden :: __impl :: __ArrayReplaceOfInitializerListClient < __ElementType >,
                public __hidden :: __impl :: __ArrayReplaceByClient < __ElementType >,
                public __hidden :: __impl :: __ArrayContainsOfCollectionClient < __ElementType >,
                public __hidden :: __impl :: __ArrayContainsOfInitializerListClient < __ElementType >,
                public __hidden :: __impl :: __ArrayIndexedOperationsClient < __ElementType >,
                public __hidden :: __impl :: __ArrayIndicesClient < __ElementType >,
                public __hidden :: __impl :: __ArrayIndicesOfCollectionClient < __ElementType >,
                public __hidden :: __impl :: __ArrayIndicesOfInitializerListClient < __ElementType >,
                public __hidden :: __impl :: __ArrayIndicesByClient < __ElementType >,
                public __hidden :: __impl :: __ArrayDelegateForwardIterableClient < __ElementType >,
                public __hidden :: __impl :: __ArrayDelegateForwardConstIterableClient < __ElementType >,
                public __hidden :: __impl :: __ArrayDelegateBackwardIterableClient < __ElementType >,
                public __hidden :: __impl :: __ArrayDelegateBackwardConstIterableClient < __ElementType > {

        private:
            template < typename, typename >
            friend class cds :: experimental :: __hidden :: __impl :: __ListServer; /* NOLINT(bugprone-reserved-identifier) */

        protected:  using Implementation                        = __hidden :: __impl :: __ArrayImplementation < __ElementType >;
        protected:  using Server                                = __hidden :: __impl :: __ArrayServer < __ElementType >;
        protected:  using RandomInsertionClient                 = __hidden :: __impl :: __ArrayRandomInsertionClient < __ElementType >;
        protected:  using BoundaryInsertionClient               = __hidden :: __impl :: __ArrayBoundaryInsertionClient < __ElementType >;
        protected:  using IteratorRelativeInsertionClient       = __hidden :: __impl :: __ArrayIteratorRelativeInsertionClient < __ElementType >;
        protected:  using ConstIteratorRelativeInsertionClient  = __hidden :: __impl :: __ArrayConstIteratorRelativeInsertionClient < __ElementType >;
        protected:  using FindOfCollectionClient                = __hidden :: __impl :: __ArrayFindOfCollectionClient < __ElementType >;
        protected:  using FindOfInitializerListClient           = __hidden :: __impl :: __ArrayFindOfInitializerListClient < __ElementType >;
        protected:  using FindConstOfCollectionClient           = __hidden :: __impl :: __ArrayFindConstOfCollectionClient < __ElementType >;
        protected:  using FindConstOfInitializerListClient      = __hidden :: __impl :: __ArrayFindConstOfInitializerListClient < __ElementType >;
        protected:  using FindByClient                          = __hidden :: __impl :: __ArrayFindByClient < __ElementType >;
        protected:  using FindConstByClient                     = __hidden :: __impl :: __ArrayFindConstByClient < __ElementType >;
        protected:  using IteratorRemoveClient                  = __hidden :: __impl :: __ArrayIteratorRemoveClient < __ElementType >;
        protected:  using ConstIteratorRemoveClient             = __hidden :: __impl :: __ArrayConstIteratorRemoveClient < __ElementType >;
        protected:  using RemoveOfCollectionClient              = __hidden :: __impl :: __ArrayRemoveOfCollectionClient < __ElementType >;
        protected:  using RemoveOfInitializerListClient         = __hidden :: __impl :: __ArrayRemoveOfInitializerListClient < __ElementType >;
        protected:  using RemoveByClient                        = __hidden :: __impl :: __ArrayRemoveByClient < __ElementType >;
        protected:  using GenericStatementsClient               = __hidden :: __impl :: __ArrayGenericStatementsClient < __ElementType >;
        protected:  using GenericConstStatementsClient          = __hidden :: __impl :: __ArrayGenericConstStatementsClient < __ElementType >;
        protected:  using SortClient                            = __hidden :: __impl :: __ArraySortClient < __ElementType >;
        protected:  using ReplaceClient                         = __hidden :: __impl :: __ArrayReplaceClient < __ElementType >;
        protected:  using ReplaceOfCollectionClient             = __hidden :: __impl :: __ArrayReplaceOfCollectionClient < __ElementType >;
        protected:  using ReplaceOfInitializerListClient        = __hidden :: __impl :: __ArrayReplaceOfInitializerListClient < __ElementType >;
        protected:  using ReplaceByClient                       = __hidden :: __impl :: __ArrayReplaceByClient < __ElementType >;
        protected:  using ContainsOfCollectionClient            = __hidden :: __impl :: __ArrayContainsOfCollectionClient < __ElementType >;
        protected:  using ContainsOfInitializerListClient       = __hidden :: __impl :: __ArrayContainsOfInitializerListClient < __ElementType >;
        protected:  using IndexedOperationsClient               = __hidden :: __impl :: __ArrayIndexedOperationsClient < __ElementType >;
        protected:  using IndicesClient                         = __hidden :: __impl :: __ArrayIndicesClient < __ElementType >;
        protected:  using IndicesOfCollectionClient             = __hidden :: __impl :: __ArrayIndicesOfCollectionClient < __ElementType >;
        protected:  using IndicesOfInitializerListClient        = __hidden :: __impl :: __ArrayIndicesOfInitializerListClient < __ElementType >;
        protected:  using IndicesByClient                       = __hidden :: __impl :: __ArrayIndicesByClient < __ElementType >;
        protected:  using DelegateForwardIterableClient         = __hidden :: __impl :: __ArrayDelegateForwardIterableClient < __ElementType >;
        protected:  using DelegateForwardConstIterableClient    = __hidden :: __impl :: __ArrayDelegateForwardConstIterableClient < __ElementType >;
        protected:  using DelegateBackwardIterableClient        = __hidden :: __impl :: __ArrayDelegateBackwardIterableClient < __ElementType >;
        protected:  using DelegateBackwardConstIterableClient   = __hidden :: __impl :: __ArrayDelegateBackwardConstIterableClient < __ElementType >;

        private:    friend BoundaryInsertionClient;
        private:    friend RandomInsertionClient;
        private:    friend IteratorRemoveClient;
        private:    friend ConstIteratorRemoveClient;
        private:    friend IteratorRelativeInsertionClient;
        private:    friend ConstIteratorRelativeInsertionClient;
        private:    friend IndexedOperationsClient;
        private:    friend DelegateForwardIterableClient;
        private:    friend DelegateForwardConstIterableClient;
        private:    friend DelegateBackwardIterableClient;
        private:    friend DelegateBackwardConstIterableClient;

        public: using ElementType                   = __ElementType;

        protected:  using ListBase                  = List < __ElementType >;

        protected:  using typename ListBase :: __GenericHandler;        /* NOLINT(bugprone-reserved-identifier) */
        protected:  using typename ListBase :: __GenericConstHandler;   /* NOLINT(bugprone-reserved-identifier) */

        public:     using typename DelegateForwardIterableClient :: Iterator;
        public:     using typename DelegateForwardConstIterableClient :: ConstIterator;
        public:     using typename DelegateBackwardIterableClient :: ReverseIterator;
        public:     using typename DelegateBackwardConstIterableClient :: ConstReverseIterator;

        private:
            __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto __cicch_obtainGenericHandler ( /* NOLINT(bugprone-reserved-identifier) */
                    __hidden :: __impl :: __CollectionInternalRequestType requestType
            ) noexcept -> __GenericHandler override;

        private:
            __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto __cicch_obtainGenericConstHandler ( /* NOLINT(bugprone-reserved-identifier) */
                    __hidden :: __impl :: __CollectionInternalRequestType requestType
            ) const noexcept -> __GenericConstHandler override;

        public:     using DelegateForwardIterableClient :: begin;
        public:     using DelegateForwardIterableClient :: end;

        public:     using DelegateForwardConstIterableClient :: begin;
        public:     using DelegateForwardConstIterableClient :: end;
        public:     using DelegateForwardConstIterableClient :: cbegin;
        public:     using DelegateForwardConstIterableClient :: cend;

        public:     using DelegateBackwardIterableClient :: rbegin;
        public:     using DelegateBackwardIterableClient :: rend;

        public:     using DelegateBackwardConstIterableClient :: rbegin;
        public:     using DelegateBackwardConstIterableClient :: rend;
        public:     using DelegateBackwardConstIterableClient :: crbegin;
        public:     using DelegateBackwardConstIterableClient :: crend;

        public:     using RandomInsertionClient :: insert;
        public:     using RandomInsertionClient :: insertAll;
        public:     using RandomInsertionClient :: insertAllOf;
        public:     using RandomInsertionClient :: add;
        public:     using RandomInsertionClient :: addAll;
        public:     using RandomInsertionClient :: addAllOf;
        public:     using RandomInsertionClient :: emplace;

        public:     using BoundaryInsertionClient :: pushBack;
        public:     using BoundaryInsertionClient :: pushBackAll;
        public:     using BoundaryInsertionClient :: pushBackAllOf;
        public:     using BoundaryInsertionClient :: pushFront;
        public:     using BoundaryInsertionClient :: pushFrontAll;
        public:     using BoundaryInsertionClient :: pushFrontAllOf;
        public:     using BoundaryInsertionClient :: append;
        public:     using BoundaryInsertionClient :: prepend;
        public:     using BoundaryInsertionClient :: emplaceBack;
        public:     using BoundaryInsertionClient :: emplaceFront;

        public:     using IteratorRelativeInsertionClient :: insertBefore;
        public:     using IteratorRelativeInsertionClient :: insertAllBefore;
        public:     using IteratorRelativeInsertionClient :: insertAllOfBefore;
        public:     using IteratorRelativeInsertionClient :: emplaceBefore;
        public:     using IteratorRelativeInsertionClient :: insertAfter;
        public:     using IteratorRelativeInsertionClient :: insertAllAfter;
        public:     using IteratorRelativeInsertionClient :: insertAllOfAfter;
        public:     using IteratorRelativeInsertionClient :: emplaceAfter;

        public:     using ConstIteratorRelativeInsertionClient :: insertBefore;
        public:     using ConstIteratorRelativeInsertionClient :: insertAllBefore;
        public:     using ConstIteratorRelativeInsertionClient :: insertAllOfBefore;
        public:     using ConstIteratorRelativeInsertionClient :: emplaceBefore;
        public:     using ConstIteratorRelativeInsertionClient :: insertAfter;
        public:     using ConstIteratorRelativeInsertionClient :: insertAllAfter;
        public:     using ConstIteratorRelativeInsertionClient :: insertAllOfAfter;
        public:     using ConstIteratorRelativeInsertionClient :: emplaceAfter;

        public:     using FindOfCollectionClient :: findOf;
        public:     using FindOfCollectionClient :: findFirstOf;
        public:     using FindOfCollectionClient :: findLastOf;
        public:     using FindOfCollectionClient :: findAllOf;
        public:     using FindOfCollectionClient :: findNotOf;
        public:     using FindOfCollectionClient :: findFirstNotOf;
        public:     using FindOfCollectionClient :: findLastNotOf;
        public:     using FindOfCollectionClient :: findAllNotOf;

        public:     using FindOfInitializerListClient :: findOf;
        public:     using FindOfInitializerListClient :: findFirstOf;
        public:     using FindOfInitializerListClient :: findLastOf;
        public:     using FindOfInitializerListClient :: findAllOf;
        public:     using FindOfInitializerListClient :: findNotOf;
        public:     using FindOfInitializerListClient :: findFirstNotOf;
        public:     using FindOfInitializerListClient :: findLastNotOf;
        public:     using FindOfInitializerListClient :: findAllNotOf;

        public:     using FindConstOfCollectionClient :: findOf;
        public:     using FindConstOfCollectionClient :: findFirstOf;
        public:     using FindConstOfCollectionClient :: findLastOf;
        public:     using FindConstOfCollectionClient :: findAllOf;
        public:     using FindConstOfCollectionClient :: findNotOf;
        public:     using FindConstOfCollectionClient :: findFirstNotOf;
        public:     using FindConstOfCollectionClient :: findLastNotOf;
        public:     using FindConstOfCollectionClient :: findAllNotOf;

        public:     using FindConstOfInitializerListClient :: findOf;
        public:     using FindConstOfInitializerListClient :: findFirstOf;
        public:     using FindConstOfInitializerListClient :: findLastOf;
        public:     using FindConstOfInitializerListClient :: findAllOf;
        public:     using FindConstOfInitializerListClient :: findNotOf;
        public:     using FindConstOfInitializerListClient :: findFirstNotOf;
        public:     using FindConstOfInitializerListClient :: findLastNotOf;
        public:     using FindConstOfInitializerListClient :: findAllNotOf;

        public:     using FindByClient :: findThat;
        public:     using FindByClient :: findFirstThat;
        public:     using FindByClient :: findLastThat;
        public:     using FindByClient :: findAllThat;

        public:     using FindConstByClient :: findThat;
        public:     using FindConstByClient :: findFirstThat;
        public:     using FindConstByClient :: findLastThat;
        public:     using FindConstByClient :: findAllThat;

        public:     using RemoveOfCollectionClient :: removeOf;
        public:     using RemoveOfCollectionClient :: removeFirstOf;
        public:     using RemoveOfCollectionClient :: removeLastOf;
        public:     using RemoveOfCollectionClient :: removeAllOf;
        public:     using RemoveOfCollectionClient :: removeNotOf;
        public:     using RemoveOfCollectionClient :: removeFirstNotOf;
        public:     using RemoveOfCollectionClient :: removeLastNotOf;
        public:     using RemoveOfCollectionClient :: removeAllNotOf;

        public:     using RemoveOfInitializerListClient :: removeOf;
        public:     using RemoveOfInitializerListClient :: removeFirstOf;
        public:     using RemoveOfInitializerListClient :: removeLastOf;
        public:     using RemoveOfInitializerListClient :: removeAllOf;
        public:     using RemoveOfInitializerListClient :: removeNotOf;
        public:     using RemoveOfInitializerListClient :: removeFirstNotOf;
        public:     using RemoveOfInitializerListClient :: removeLastNotOf;
        public:     using RemoveOfInitializerListClient :: removeAllNotOf;

        public:     using RemoveByClient :: removeThat;
        public:     using RemoveByClient :: removeFirstThat;
        public:     using RemoveByClient :: removeLastThat;
        public:     using RemoveByClient :: removeAllThat;

        public:     using GenericStatementsClient :: forEach;
        public:     using GenericStatementsClient :: some;
        public:     using GenericStatementsClient :: atLeast;
        public:     using GenericStatementsClient :: atMost;
        public:     using GenericStatementsClient :: moreThan;
        public:     using GenericStatementsClient :: fewerThan;
        public:     using GenericStatementsClient :: count;
        public:     using GenericStatementsClient :: any;
        public:     using GenericStatementsClient :: all;
        public:     using GenericStatementsClient :: none;

        public:     using GenericConstStatementsClient :: forEach;
        public:     using GenericConstStatementsClient :: some;
        public:     using GenericConstStatementsClient :: atLeast;
        public:     using GenericConstStatementsClient :: atMost;
        public:     using GenericConstStatementsClient :: moreThan;
        public:     using GenericConstStatementsClient :: fewerThan;
        public:     using GenericConstStatementsClient :: count;
        public:     using GenericConstStatementsClient :: any;
        public:     using GenericConstStatementsClient :: all;
        public:     using GenericConstStatementsClient :: none;

        public:     using SortClient :: sort;

        public:     using ReplaceClient :: replace;
        public:     using ReplaceClient :: replaceFirst;
        public:     using ReplaceClient :: replaceLast;
        public:     using ReplaceClient :: replaceAll;

        public:     using ReplaceOfCollectionClient :: replaceOf;
        public:     using ReplaceOfCollectionClient :: replaceFirstOf;
        public:     using ReplaceOfCollectionClient :: replaceLastOf;
        public:     using ReplaceOfCollectionClient :: replaceAllOf;
        public:     using ReplaceOfCollectionClient :: replaceNotOf;
        public:     using ReplaceOfCollectionClient :: replaceFirstNotOf;
        public:     using ReplaceOfCollectionClient :: replaceLastNotOf;
        public:     using ReplaceOfCollectionClient :: replaceAllNotOf;

        public:     using ReplaceOfInitializerListClient :: replaceOf;
        public:     using ReplaceOfInitializerListClient :: replaceFirstOf;
        public:     using ReplaceOfInitializerListClient :: replaceLastOf;
        public:     using ReplaceOfInitializerListClient :: replaceAllOf;
        public:     using ReplaceOfInitializerListClient :: replaceNotOf;
        public:     using ReplaceOfInitializerListClient :: replaceFirstNotOf;
        public:     using ReplaceOfInitializerListClient :: replaceLastNotOf;
        public:     using ReplaceOfInitializerListClient :: replaceAllNotOf;

        public:     using ReplaceByClient :: replaceThat;
        public:     using ReplaceByClient :: replaceFirstThat;
        public:     using ReplaceByClient :: replaceLastThat;
        public:     using ReplaceByClient :: replaceAllThat;
        public:     using ReplaceByClient :: replaceThatBy;
        public:     using ReplaceByClient :: replaceFirstThatBy;
        public:     using ReplaceByClient :: replaceLastThatBy;
        public:     using ReplaceByClient :: replaceAllThatBy;

        public:     using IndexedOperationsClient :: sub;

        public:     using IndicesClient :: indicesOf;
        public:     using IndicesClient :: firstIndexOf;
        public:     using IndicesClient :: lastIndexOf;
        public:     using IndicesClient :: allIndicesOf;

        public:     using IndicesOfCollectionClient :: indicesOfFrom;
        public:     using IndicesOfCollectionClient :: firstIndexOfFrom;
        public:     using IndicesOfCollectionClient :: lastIndexOfFrom;
        public:     using IndicesOfCollectionClient :: allIndicesOfFrom;
        public:     using IndicesOfCollectionClient :: indicesOfNotFrom;
        public:     using IndicesOfCollectionClient :: firstIndexOfNotFrom;
        public:     using IndicesOfCollectionClient :: lastIndexOfNotFrom;
        public:     using IndicesOfCollectionClient :: allIndicesOfNotFrom;

        public:     using IndicesOfInitializerListClient :: indicesOfFrom;
        public:     using IndicesOfInitializerListClient :: firstIndexOfFrom;
        public:     using IndicesOfInitializerListClient :: lastIndexOfFrom;
        public:     using IndicesOfInitializerListClient :: allIndicesOfFrom;
        public:     using IndicesOfInitializerListClient :: indicesOfNotFrom;
        public:     using IndicesOfInitializerListClient :: firstIndexOfNotFrom;
        public:     using IndicesOfInitializerListClient :: lastIndexOfNotFrom;
        public:     using IndicesOfInitializerListClient :: allIndicesOfNotFrom;

        public:     using IndicesByClient :: indicesOfThat;
        public:     using IndicesByClient :: firstIndexOfThat;
        public:     using IndicesByClient :: lastIndexOfThat;
        public:     using IndicesByClient :: allIndicesOfThat;

        public:     using ContainsOfCollectionClient :: containsAnyOf;
        public:     using ContainsOfCollectionClient :: containsAnyNotOf;
        public:     using ContainsOfCollectionClient :: containsAllOf;
        public:     using ContainsOfCollectionClient :: containsNoneOf;

        public:     using ContainsOfInitializerListClient :: containsAnyOf;
        public:     using ContainsOfInitializerListClient :: containsAnyNotOf;
        public:     using ContainsOfInitializerListClient :: containsAllOf;
        public:     using ContainsOfInitializerListClient :: containsNoneOf;

        public:     using IteratorRemoveClient :: remove;
        public:     using ConstIteratorRemoveClient :: remove;
        public:     using List < __ElementType > :: remove;

        public:
            constexpr Array () noexcept;

        public:
            Array ( /* NOLINT(google-explicit-constructor) */
                    Array const & array
            ) noexcept;

        public:
            constexpr Array (
                    Array && array
            ) noexcept;

        public:
            template <
                    typename __IteratorType,                    /* NOLINT(bugprone-reserved-identifier) */
                    typename __TElementType = __ElementType,    /* NOLINT(bugprone-reserved-identifier) */
                    cds :: meta :: EnableIf <
                            cds :: meta :: isCopyConstructible < __TElementType > ()
                    > = 0
            > Array (
                    __IteratorType const & begin,
                    __IteratorType const & end
            ) noexcept;

        public:
            template <
                    typename __TElementType = __ElementType, /* NOLINT(bugprone-reserved-identifier) */
                    cds :: meta :: EnableIf <
                            cds :: meta :: isCopyConstructible < __TElementType > ()
                    > = 0
            > Array (
                    std :: initializer_list < __ElementType > const & initializerList
            ) noexcept;

        public:
            template <
                    typename __TElementType = __ElementType, /* NOLINT(bugprone-reserved-identifier) */
                    cds :: meta :: EnableIf <
                            cds :: meta :: isDefaultConstructible < __TElementType > ()
                    > = 0
            > __CDS_Explicit Array (
                    Size size
            ) noexcept;

        public:
            template <
                    typename __TElementType = __ElementType, /* NOLINT(bugprone-reserved-identifier) */
                    cds :: meta :: EnableIf <
                            cds :: meta :: isCopyConstructible < __TElementType > ()
                    > = 0
            > Array (
                    Size                    size,
                    __ElementType   const & defaultValue
            ) noexcept;

        public:
            template <
                    typename __OtherElementType, /* NOLINT(bugprone-reserved-identifier) */
                    cds :: meta :: EnableIf <
                            cds :: meta :: isConvertible < __OtherElementType, __ElementType > ()
                    > = 0
            > __CDS_Explicit Array (
                    Collection < __OtherElementType > const & collection
            ) noexcept;

        public:
            ~Array () noexcept override;

        public:
            auto operator = (
                    Array const & array
            ) noexcept -> Array &;

        public:
            auto operator = (
                    Array && array
            ) noexcept -> Array &;

        public:
            template <
                    typename __OtherElementType, /* NOLINT(bugprone-reserved-identifier) */
                    cds :: meta :: EnableIf <
                            cds :: meta :: isConvertible < __OtherElementType, __ElementType > ()
                    > = 0
            > auto operator = (
                    Collection < __OtherElementType > const & collection
            ) noexcept -> Array &;

        public:
            auto reserve (
                    Size size
            ) noexcept -> void;

        public:
            auto shrink (
                    Size size
            ) noexcept -> void;


        public:
            template <
                    typename __TElementType = __ElementType, /* NOLINT(bugprone-reserved-identifier) */
                    cds :: meta :: EnableIf <
                            cds :: meta :: isDefaultConstructible < __TElementType > ()
                    > = 0
            > auto resize (
                    Size size
            ) noexcept -> void;


        public:
            template <
                    typename __TElementType = __ElementType, /* NOLINT(bugprone-reserved-identifier) */
                    cds :: meta :: EnableIf <
                            cds :: meta :: isCopyConstructible < __TElementType > ()
                    > = 0
            > auto resize (
                    Size                    size,
                    __ElementType   const & defaultValue
            ) noexcept -> void;

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

        public:
            __CDS_NoDiscard constexpr auto data () const noexcept -> __ElementType const *;

        public:
            __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction auto data () noexcept -> __ElementType *;

        public:
            __CDS_NoDiscard auto sequence () & noexcept -> Sequence < Array < __ElementType > >;

        public:
            __CDS_NoDiscard auto sequence () && noexcept -> Sequence < Array < __ElementType > >;

        public:
            __CDS_NoDiscard auto sequence () const & noexcept -> Sequence < Array < __ElementType > const >;

        public:
            __CDS_NoDiscard auto sequence () const && noexcept -> Sequence < Array < __ElementType > const >;
        };

    }
}

#include "array/impl/Array.hpp"

#include "shared/array/impl/Array.hpp"

#include "shared/iterator/impl/AddressIterator.hpp"

#include "shared/delegateIterator/impl/AbstractDelegateIterator.hpp"
#include "shared/delegateIterator/impl/DelegateIterator.hpp"

#include "shared/collectionInternalCommunication/server/impl/ListServer.hpp"
#include "shared/collectionInternalCommunication/server/impl/ListServerDispatcher.hpp"

#include "shared/array/impl/Sequence.hpp"
#include "array/impl/CTAD.hpp"

#endif /* __CDS_EX_ARRAY_HPP__ */
