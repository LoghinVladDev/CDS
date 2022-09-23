/*
 * Created by loghin on 6/27/22.
 */

#ifndef __CDS_EX_LIST_HPP__
#define __CDS_EX_LIST_HPP__ /* NOLINT(bugprone-reserved-identifier) */

#include <CDS/Function>
#include <CDS/experimental/MutableCollection>

#include "shared/delegateIterator/BidirectionalDelegateWrapperIterator.hpp"

#include "shared/collectionInternalCommunication/client/primitive/DelegateBackwardIterablePrimitiveClient.hpp"
#include "shared/collectionInternalCommunication/client/primitive/DelegateBackwardConstIterablePrimitiveClient.hpp"
#include "shared/collectionInternalCommunication/client/primitive/IteratorRelativeInsertionPrimitiveClient.hpp"
#include "shared/collectionInternalCommunication/client/primitive/ConstIteratorRelativeInsertionPrimitiveClient.hpp"
#include "shared/collectionInternalCommunication/client/primitive/BoundaryInsertionPrimitiveClient.hpp"
#include "shared/collectionInternalCommunication/client/primitive/IndexedOperationsPrimitiveClient.hpp"

#include "shared/collectionInternalCommunication/client/composite/ReplaceCompositeClient.hpp"
#include "shared/collectionInternalCommunication/client/composite/ReplaceOfCompositeClient.hpp"
#include "shared/collectionInternalCommunication/client/composite/ReplaceByCompositeClient.hpp"
#include "shared/collectionInternalCommunication/client/composite/IndicesCompositeClient.hpp"
#include "shared/collectionInternalCommunication/client/composite/IndicesOfCompositeClient.hpp"
#include "shared/collectionInternalCommunication/client/composite/IndicesByCompositeClient.hpp"

#include "list/ListConstructs.hpp"

namespace cds { /* NOLINT(modernize-concat-nested-namespaces) */
    namespace experimental {

        /**
         * @class Abstract Object representing any List-Type Linear Iterable Container. Order of elements preserved.
         * @tparam __ElementType is the type of elements contained in the List
         *
         * @extends [public]    MutableCollection - Base MutableCollection Class, inheriting properties of mutable/immutable forward iterable container-type
         *
         * @implements [public] __ListDelegateForwardIterableClient - Abstract Mutable Bidirectional Iterator Request Client - begin / end
         * @implements [public] __ListDelegateBackwardIterableClient - Abstract Mutable Bidirectional Reverse Iterator Request Client - rbegin / rend
         * @implements [public] __ListDelegateForwardConstIterableClient - Abstract Immutable Bidirectional Iterator Request Client - cbegin / cend
         * @implements [public] __ListDelegateForwardConstIterableClient - Abstract Immutable Bidirectional Reverse Iterator Request Client - crbegin / crend
         * @implements [public] __ListBoundaryInsertionClient - Insertion at List boundaries Client - pushFront / pushFrontAll / pushFrontAllOf / emplaceFront / pushBack / pushBackAll / pushBackAllOf / emplaceBack
         * @implements [public] __ListIteratorRelativeInsertionClient - Insertion relative to given iterator position Client - insertBefore / insertAllBefore / insertAllOfBefore / emplaceBefore / insertAfter / insertAllAfter / insertAllOfAfter / emplaceAfter
         * @implements [public] __ListConstIteratorRelativeInsertionClient - Insertion relative to given const iterator position Client - insertBefore / insertAllBefore / insertAllOfBefore / emplaceBefore / insertAfter / insertAllAfter / insertAllOfAfter / emplaceAfter
         * @implements [public] __ListIndexedOperationsClient - List Operations using indices. operator[], sub < list >, sub ( list )
         * @implements [public] __ListReplaceClient - Replace singular element values - replace / replaceFirst / replaceLast / replaceAll
         * @implements [public] __ListReplaceOfCollectionClient - Replace Client for replacing values belonging to a given collection - replaceOf / replaceFirstOf / replaceLastOf / replaceAllOf / replaceNotOf / replaceFirstNotOf / replaceLastNotOf / replaceAllNotOf
         * @implements [public] __ListReplaceOfInitializerListClient - Replace Client for replacing values belonging to a given initializer list - replaceOf / replaceFirstOf / replaceLastOf / replaceAllOf / replaceNotOf / replaceFirstNotOf / replaceLastNotOf / replaceAllNotOf
         * @implements [public] __ListReplaceByClient - Replace Client for replacing values validated by a given predicate - replaceThat / replaceFirstThat / replaceLastThat / replaceAllThat
         * @implements [public] __ListIndicesClient - Client used for identifying indices of a given element - indexOf / firstIndexOf / lastIndexOf / indicesOf
         * @implements [public] __ListIndicesOfCollectionClient - Client used for identifying indices of the elements found in the given collection - indicesOfFrom / firstIndexOfFrom / lastIndexOfFrom / allIndicesOfFrom / indicesOfNotFrom / firstIndexOfNotFrom / lastIndexOfNotFrom / allIndicesOfNotFrom
         * @implements [public] __ListIndicesOfInitializerListClient - Client used for identifying indices of the elements found in the given initializer list - indicesOfFrom / firstIndexOfFrom / lastIndexOfFrom / allIndicesOfFrom / indicesOfNotFrom / firstIndexOfNotFrom / lastIndexOfNotFrom / allIndicesOfNotFrom
         * @implements [public] __ListIndicesByClient - Client used for identifying indices of the elements validated by a given predicate - indicesOfThat / indexOfFirstThat / indexOfLastThat / indicesOfAllThat
         *
         * @test Suite: CTS-00001, Group: All - requirement for running, Test Cases: All - requirement for running
         * @test Suite: MCTS-00001, Group: All - requirement for running, Test Cases: All - requirement for running
         * @test Suite: LTS-00001, Group: All, Test Cases: All
         *
         * @namespace cds :: experimental
         * @public
         */
        template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
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
                public __hidden :: __impl :: __ListReplaceClient < __ElementType >,
                public __hidden :: __impl :: __ListReplaceOfCollectionClient < __ElementType >,
                public __hidden :: __impl :: __ListReplaceOfInitializerListClient < __ElementType >,
                public __hidden :: __impl :: __ListReplaceByClient < __ElementType >,
                public __hidden :: __impl :: __ListIndicesClient < __ElementType >,
                public __hidden :: __impl :: __ListIndicesOfCollectionClient < __ElementType >,
                public __hidden :: __impl :: __ListIndicesOfInitializerListClient < __ElementType >,
                public __hidden :: __impl :: __ListIndicesByClient < __ElementType > {

        public:
            /**
             * @typedef public alias for __ElementType, the type of the contained elements,
             * publicly accessible, useful in sfinae statements - decltype ( List ) :: ElementType
             * @public
             */
            using ElementType                           = __ElementType;

        protected:
            /**
             * @typedef protected alias for MutableCollection \< __ElementType \> base extended class - providing mutable iterable properties
             * @protected
             */
            using MutableCollectionBase = MutableCollection < __ElementType >;

        protected:
            /**
             * @typedef protected alias for __ListDelegateForwardIterableClient base interface - providing begin / end for Abstract Bidirectional Mutable Iterators
             * @protected
             */
            using DelegateForwardIterableClient         = __hidden :: __impl :: __ListDelegateForwardIterableClient < __ElementType >;

        protected:
            /**
             * @typedef protected alias for __ListDelegateBackwardIterableClient base interface - providing rbegin / rend for Abstract Bidirectional Mutable Reverse Iterators
             * @protected
             */
            using DelegateBackwardIterableClient        = __hidden :: __impl :: __ListDelegateBackwardIterableClient < __ElementType >;

        protected:
            /**
             * @typedef protected alias for __ListDelegateForwardConstIterableClient base interface - providing cbegin / cend for Abstract Bidirectional Immutable Iterators
             * @protected
             */
            using DelegateForwardConstIterableClient    = __hidden :: __impl :: __ListDelegateForwardConstIterableClient < __ElementType >;

        protected:
            /**
             * @typedef protected alias for DelegateBackwardConstIterableClient base interface - providing crbegin / crend for Abstract Bidirectional Immutable Reverse Iterators
             * @protected
             */
            using DelegateBackwardConstIterableClient   = __hidden :: __impl :: __ListDelegateBackwardConstIterableClient < __ElementType >;

        protected:
            /**
             * @typedef protected alias for __ListBoundaryInsertionClient base interface - providing boundary insertion functions
             * @protected
             */
            using BoundaryInsertionClient               = __hidden :: __impl :: __ListBoundaryInsertionClient < __ElementType >;

        protected:
            /**
             * @typedef protected alias for __ListIteratorRelativeInsertionClient base interface - providing iterator relative insertion functions
             * @protected
             */
            using IteratorRelativeInsertionClient       = __hidden :: __impl :: __ListIteratorRelativeInsertionClient < __ElementType >;

        protected:
            /**
             * @typedef protected alias for __ListConstIteratorRelativeInsertionClient base interface - providing const iterator relative insertion functions
             * @protected
             */
            using ConstIteratorRelativeInsertionClient  = __hidden :: __impl :: __ListConstIteratorRelativeInsertionClient < __ElementType >;

        protected:
            /**
             * @typedef protected alias for __ListIndexedOperationsClient base interface - providing index based operations
             * @protected
             */
            using IndexedOperationsClient               = __hidden :: __impl :: __ListIndexedOperationsClient < __ElementType >;

        protected:
            /**
             * @typedef protected alias for __ListReplaceClient base interface - providing replace operations
             * @protected
             */
            using ReplaceClient                         = __hidden :: __impl :: __ListReplaceClient < __ElementType >;

        protected:
            /**
             * @typedef protected alias for __ListReplaceOfCollectionClient base interface - providing replace of collection operations
             * @protected
             */
            using ReplaceOfCollectionClient             = __hidden :: __impl :: __ListReplaceOfCollectionClient < __ElementType >;

        protected:
            /**
             * @typedef protected alias for __ListReplaceOfInitializerListClient base interface - providing replace of initializer list operations
             * @protected
             */
            using ReplaceOfInitializerListClient        = __hidden :: __impl :: __ListReplaceOfInitializerListClient < __ElementType >;

        protected:
            /**
             * @typedef protected alias for __ListReplaceByClient base interface - providing replace by predicate operations
             * @protected
             */
            using ReplaceByClient                       = __hidden :: __impl :: __ListReplaceByClient < __ElementType >;

        protected:
            /**
             * @typedef protected alias for __ListIndicesClient base interface - providing index query operations
             * @protected
             */
            using IndicesClient                         = __hidden :: __impl :: __ListIndicesClient < __ElementType >;

        protected:
            /**
             * @typedef protected alias for __ListIndicesOfCollectionClient base interface - providing indices of collection elements query operations
             * @protected
             */
            using IndicesOfCollectionClient             = __hidden :: __impl :: __ListIndicesOfCollectionClient < __ElementType >;

        protected:
            /**
             * @typedef protected alias for __ListIndicesOfInitializerListClient base interface - providing indices of initializer list elements query operations
             * @protected
             */
            using IndicesOfInitializerListClient        = __hidden :: __impl :: __ListIndicesOfInitializerListClient < __ElementType >;

        protected:
            /**
             * @typedef protected alias for __ListIndicesByClient base interface - providing indices of elements validated by predicate query operations
             * @protected
             */
            using IndicesByClient                       = __hidden :: __impl :: __ListIndicesByClient < __ElementType >;

        protected:
            /**
             * @typedef imported protected alias for __GenericHandler, representing a generic member function pointer, represents a function returned at a request made through the Collection Communication Channel
             * @protected
             */
            using typename MutableCollectionBase :: __GenericHandler;        /* NOLINT(bugprone-reserved-identifier) */

        protected:
            /**
             * @typedef imported protected alias for __GenericConstHandler, representing a generic member const-function pointer, represents a function returned at a request made through the Collection Communication Channel
             * @protected
             */
            using typename MutableCollectionBase :: __GenericConstHandler;   /* NOLINT(bugprone-reserved-identifier) */

        public:
            /**
             * @brief Public constant representing an invalid list index. Used by index functions to denote the absence of an element.
             * @static
             * @public
             */
            static Index const invalidIndex = -1;

        protected:
            /**
             * @brief Default Constructor
             * @exceptsafe
             * @test Suite: STS-00001, Group: All, Test Cases: All
             * @protected
             */
            constexpr List () noexcept;

        protected:
            /**
             * @brief Copy Constructor
             * @param [in] list : List cref = Constant Reference to a list to copy the data from
             * @exceptsafe
             * @test Suite: STS-00001, Group: All, Test Cases: All
             * @protected
             */
            constexpr List (
                    List const & list
            ) noexcept;

        protected:
            /**
             * @brief Move Constructor
             * @param [in, out] list : List mref = Move Reference to a list to acquire and release the data from
             * @exceptsafe
             * @test Suite: STS-00001, Group: All, Test Cases: All
             * @protected
             */
            constexpr List (
                    List && list
            ) noexcept;

        protected:
            /**
             * @brief Destructor
             * @exceptsafe
             * @test Suite: STS-00001, Group: All, Test Cases: All
             * @public
             */
            __CDS_cpplang_ConstexprDestructor ~List () noexcept override;

        public:     using DelegateForwardIterableClient :: begin;
        public:     using DelegateForwardIterableClient :: end;

        public:     using DelegateBackwardIterableClient :: rbegin;
        public:     using DelegateBackwardIterableClient :: rend;

        public:     using DelegateForwardConstIterableClient :: begin;
        public:     using DelegateForwardConstIterableClient :: end;
        public:     using DelegateForwardConstIterableClient :: cbegin;
        public:     using DelegateForwardConstIterableClient :: cend;

        public:     using DelegateBackwardConstIterableClient :: rbegin;
        public:     using DelegateBackwardConstIterableClient :: rend;
        public:     using DelegateBackwardConstIterableClient :: crbegin;
        public:     using DelegateBackwardConstIterableClient :: crend;

        public:     using BoundaryInsertionClient :: pushBack;
        public:     using BoundaryInsertionClient :: pushBackAll;
        public:     using BoundaryInsertionClient :: pushBackAllOf;
        public:     using BoundaryInsertionClient :: pushFront;
        public:     using BoundaryInsertionClient :: pushFrontAll;
        public:     using BoundaryInsertionClient :: pushFrontAllOf;
        public:     using BoundaryInsertionClient :: emplaceBack;
        public:     using BoundaryInsertionClient :: emplaceFront;

        public:     using IteratorRelativeInsertionClient :: insertBefore;
        public:     using IteratorRelativeInsertionClient :: insertAllBefore;
        public:     using IteratorRelativeInsertionClient :: insertAllOfBefore;
        public:     using IteratorRelativeInsertionClient :: insertAfter;
        public:     using IteratorRelativeInsertionClient :: insertAllAfter;
        public:     using IteratorRelativeInsertionClient :: insertAllOfAfter;
        public:     using IteratorRelativeInsertionClient :: emplaceBefore;
        public:     using IteratorRelativeInsertionClient :: emplaceAfter;

        public:     using ConstIteratorRelativeInsertionClient :: insertBefore;
        public:     using ConstIteratorRelativeInsertionClient :: insertAllBefore;
        public:     using ConstIteratorRelativeInsertionClient :: insertAllOfBefore;
        public:     using ConstIteratorRelativeInsertionClient :: insertAfter;
        public:     using ConstIteratorRelativeInsertionClient :: insertAllAfter;
        public:     using ConstIteratorRelativeInsertionClient :: insertAllOfAfter;
        public:     using ConstIteratorRelativeInsertionClient :: emplaceBefore;
        public:     using ConstIteratorRelativeInsertionClient :: emplaceAfter;

        public:     using IndexedOperationsClient :: sub;

        public:
            /**
             * @inherit operator [] for index operations.
             * @test Suite: LTS-00001, Group: LTG-00100-MF, Test Cases: {
             *      LTC-00107-MF-getOp,
             *      LTC-00118-MF-getCircularRightOp,
             *      LTC-00119-MF-getCircularLeftOp,
             *      LTC-00120-MF-getOpThrow
             * }
             * @public
             */
            using IndexedOperationsClient :: operator[];

        public:     using IndexedOperationsClient :: removeAt;

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

        public:
            /**
             * @brief String conversion function, used to obtain String representation of the List
             * @exceptsafe
             * @return String = string representation
             * @test Suite: LTS-00001, Group: LTG-00100-MF, Test Cases: { LTC-00101-MF-toString }
             * @public
             */
            __CDS_NoDiscard auto toString () const noexcept -> String override;

        public:
            /**
             * @brief Function used to clear the list, removing all elements from it
             * @exceptsafe
             * @test Suite: LTS-00001, Group: LTG-00100-MF, Test Cases: { LTC-00102-MF-clear }
             * @public
             */
            auto clear () noexcept -> void override = 0;

        public:
            /**
             * @brief Function used to remove the first element from the list, if any is present.
             * @exceptsafe
             * @test Suite: LTS-00001, Group: LTG-00100-MF, Test Cases: { LTC-00104-MF-popFront }
             * @public
             */
            virtual auto popFront () noexcept -> void = 0;

        public:
            /**
             * @brief Function used to remove the last element from the list, if any is present.
             * @exceptsafe
             * @test Suite: LTS-00001, Group: LTG-00100-MF, Test Cases: { LTC-00106-MF-popBack }
             * @public
             */
            virtual auto popBack () noexcept -> void = 0;

        public:
            /**
             * @brief Function used to peek at the front of the list, acquiring a mutable reference to the first enclosed element
             * @throws cds::OutOfBoundsException if list is empty
             * @return __ElementType ref = Mutable Reference to the first element
             * @test Suite: LTS-00001, Group: LTG-00100-MF, Test Cases: { LTC-00103-MF-front, LTC-00110-MF-frontThrow }
             * @public
             */
            __CDS_NoDiscard __CDS_cpplang_VirtualConstexpr virtual auto front () noexcept (false) -> ElementType & = 0;

        public:
            /**
             * @brief Function used to peek at the front of the list, acquiring an immutable reference to the first enclosed element
             * @throws cds::OutOfBoundsException if list is empty
             * @return __ElementType cref = Immutable Reference to the first element
             * @test Suite: LTS-00001, Group: LTG-00100-MF, Test Cases: { LTC-00103-MF-front, LTC-00110-MF-frontThrow }
             * @public
             */
            __CDS_NoDiscard __CDS_cpplang_VirtualConstexpr virtual auto front () const noexcept (false) -> ElementType const & = 0;

        public:
            /**
             * @brief Function used to peek at the back of the list, acquiring a mutable reference to the last enclosed element
             * @throws cds::OutOfBoundsException if list is empty
             * @return __ElementType ref = Mutable Reference to the last element
             * @test Suite: LTS-00001, Group: LTG-00100-MF, Test Cases: { LTC-00105-MF-back, LTC-00111-MF-backThrow }
             * @public
             */
            __CDS_NoDiscard __CDS_cpplang_VirtualConstexpr virtual auto back () noexcept (false) -> ElementType & = 0;

        public:
            /**
             * @brief Function used to peek at the last of the list, acquiring an immutable reference to the last enclosed element
             * @throws cds::OutOfBoundsException if list is empty
             * @return __ElementType cref = Immutable Reference to the last element
             * @test Suite: LTS-00001, Group: LTG-00100-MF, Test Cases: { LTC-00105-MF-back, LTC-00111-MF-backThrow }
             * @public
             */
            __CDS_NoDiscard __CDS_cpplang_VirtualConstexpr virtual auto back () const noexcept (false) -> ElementType const & = 0;

        public:
            /**
             * @brief Function used to obtain an element via its index in the list. The implementation will adjust the index circularly, if given value is out of index bounds.
             * @throws cds::OutOfBoundsException if list is empty
             * @return __ElementType ref = Mutable Reference to the element at the requested index
             * @test Suite: LTS-00001, Group: LTG-00100-MF, Test Cases: {
             *      LTC-00107-MF-get,
             *      LTC-00108-MF-getCircularRight,
             *      LTC-00109-MF-getCircularLeft,
             *      LTC-00112-MF-getThrow
             * }
             * @public
             */
            __CDS_NoDiscard __CDS_cpplang_VirtualConstexpr virtual auto get (
                    Index index
            ) noexcept ( false ) -> ElementType & = 0;

        public:
            /**
             * @brief Function used to obtain an element via its index in the list. The implementation will adjust the index circularly, if given value is out of index bounds.
             * @throws cds::OutOfBoundsException if list is empty
             * @return __ElementType cref = Immutable Reference to the element at the requested index
             * @test Suite: LTS-00001, Group: LTG-00100-MF, Test Cases: {
             *      LTC-00107-MF-get,
             *      LTC-00108-MF-getCircularRight,
             *      LTC-00109-MF-getCircularLeft,
             *      LTC-00112-MF-getThrow
             * }
             * @public
             */
            __CDS_NoDiscard __CDS_cpplang_VirtualConstexpr virtual auto get (
                    Index index
            ) const noexcept ( false ) -> ElementType const & = 0;

        public:
            /**
             * @brief Function used to sort the elements with the requested ordering, given as parameter. Parameter must be a callable object ( function / lambda / functor ). Default ordering, if no parameter given, is ascending
             * @param comparator : cds :: Function < bool ( ElementType, ElementType ) > cref = Constant Reference to wrapped callable
             * @exceptsafe
             * @test Suite: LTS-00001, Group: LTG-00100-MF, Test Cases: {
             *      LTC-00121-MF-sortAscFn,
             *      LTC-00122-MF-sortDescFn,
             *      LTC-00123-MF-sortAscLambda,
             *      LTC-00124-MF-sortDescLambda,
             *      LTC-00125-MF-sortAscFunctor,
             *      LTC-00126-MF-sortDescFunctor,
             *      LTC-00127-MF-sortDefault
             * }
             * @public
             */
            virtual auto sort ( /* NOLINT(google-default-arguments) */
                    cds :: Function < auto ( __ElementType const &, __ElementType const & ) -> bool > const & comparator = & cds :: predicates :: lessThan < __ElementType >
            ) noexcept -> void = 0;

        public:
            /**
             * @brief Function used to remove an element from the list via given index
             * @param index : Index = index of the element to be removed
             * @exceptsafe
             * @return bool = true if removal was done, false otherwise
             * @test Suite: LTS-00001, Group: LTG-00100-MF, Test Cases: {
             *      LTC-00113-MF-removeAtEmpty,
             *      LTC-00114-MF-removeAtFront,
             *      LTC-00115-MF-removeAtBack,
             *      LTC-00116-MF-removeAt
             * }
             * @public
             */
            virtual auto removeAt (
                    Index index
            ) noexcept -> bool = 0;

        protected:
            /**
             * @brief Function used to circularly adapt an index based on the current list bounds
             * @param index : Index = requested index to bound
             * @exceptsafe
             * @return Index = bounded index
             * @test Suite: LTS-00001, Group: LTG-00100-MF, Test Cases: {
             *      LTC-00108-MF-getCircularRight,
             *      LTC-00109-MF-getCircularLeft
             * }
             * @public
             */
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

#include "shared/collectionInternalCommunication/client/composite/impl/ReplaceCompositeClient.hpp"
#include "shared/collectionInternalCommunication/client/composite/impl/ReplaceOfCompositeClient.hpp"
#include "shared/collectionInternalCommunication/client/composite/impl/ReplaceByCompositeClient.hpp"
#include "shared/collectionInternalCommunication/client/composite/impl/IndicesCompositeClient.hpp"
#include "shared/collectionInternalCommunication/client/composite/impl/IndicesOfCompositeClient.hpp"
#include "shared/collectionInternalCommunication/client/composite/impl/IndicesByCompositeClient.hpp"

#include "list/impl/List.hpp"

#endif /* __CDS_EX_LIST_HPP__ */
