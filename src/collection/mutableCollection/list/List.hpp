/* NOLINT(llvm-header-guard)
 * Created by loghin on 15.01.2021.
 */

#ifndef __CDS_LIST_HPP__ /* NOLINT(llvm-header-guard) */
#define __CDS_LIST_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

#include <CDS/Function>
#include <CDS/MutableCollection>
#include <CDS/exception/OutOfBoundsException>

#include "../../../shared/delegateIterator/BidirectionalDelegateWrapperIterator.hpp"

#include "../../../shared/collectionInternalCommunication/client/primitive/DelegateBackwardIterablePrimitiveClient.hpp"         /* NOLINT(llvm-include-order) */
#include "../../../shared/collectionInternalCommunication/client/primitive/DelegateBackwardConstIterablePrimitiveClient.hpp"
#include "../../../shared/collectionInternalCommunication/client/primitive/IteratorRelativeInsertionPrimitiveClient.hpp"
#include "../../../shared/collectionInternalCommunication/client/primitive/ConstIteratorRelativeInsertionPrimitiveClient.hpp"
#include "../../../shared/collectionInternalCommunication/client/primitive/BoundaryInsertionPrimitiveClient.hpp"
#include "../../../shared/collectionInternalCommunication/client/primitive/IndexedOperationsPrimitiveClient.hpp"

#include "../../../shared/collectionInternalCommunication/client/composite/ReplaceCompositeClient.hpp"                          /* NOLINT(llvm-include-order) */
#include "../../../shared/collectionInternalCommunication/client/composite/ReplaceOfCompositeClient.hpp"
#include "../../../shared/collectionInternalCommunication/client/composite/ReplaceByCompositeClient.hpp"
#include "../../../shared/collectionInternalCommunication/client/composite/IndicesCompositeClient.hpp"
#include "../../../shared/collectionInternalCommunication/client/composite/IndicesOfCompositeClient.hpp"
#include "../../../shared/collectionInternalCommunication/client/composite/IndicesByCompositeClient.hpp"

#include "list/Constructs.hpp"

namespace cds {

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
     * @namespace cds
     * @public
     */
    template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    class List :                        /* NOLINT(cppcoreguidelines-virtual-class-destructor) */
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

    public: /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @typedef public alias for __ElementType, the type of the contained elements,
         * publicly accessible, useful in sfinae statements - decltype ( List ) :: ElementType
         * @public
         */
        using ElementType                           = __ElementType;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @typedef protected alias for MutableCollection \< __ElementType \> base extended class - providing mutable iterable properties
         * @protected
         */
        using MutableCollectionBase = MutableCollection < __ElementType >;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @typedef protected alias for __ListDelegateForwardIterableClient base interface - providing begin / end for Abstract Bidirectional Mutable Iterators
         * @protected
         */
        using DelegateForwardIterableClient         = __hidden :: __impl :: __ListDelegateForwardIterableClient < __ElementType >;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @typedef protected alias for __ListDelegateBackwardIterableClient base interface - providing rbegin / rend for Abstract Bidirectional Mutable Reverse Iterators
         * @protected
         */
        using DelegateBackwardIterableClient        = __hidden :: __impl :: __ListDelegateBackwardIterableClient < __ElementType >;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @typedef protected alias for __ListDelegateForwardConstIterableClient base interface - providing cbegin / cend for Abstract Bidirectional Immutable Iterators
         * @protected
         */
        using DelegateForwardConstIterableClient    = __hidden :: __impl :: __ListDelegateForwardConstIterableClient < __ElementType >;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @typedef protected alias for DelegateBackwardConstIterableClient base interface - providing crbegin / crend for Abstract Bidirectional Immutable Reverse Iterators
         * @protected
         */
        using DelegateBackwardConstIterableClient   = __hidden :: __impl :: __ListDelegateBackwardConstIterableClient < __ElementType >;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @typedef protected alias for __ListBoundaryInsertionClient base interface - providing boundary insertion functions
         * @protected
         */
        using BoundaryInsertionClient               = __hidden :: __impl :: __ListBoundaryInsertionClient < __ElementType >;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @typedef protected alias for __ListIteratorRelativeInsertionClient base interface - providing iterator relative insertion functions
         * @protected
         */
        using IteratorRelativeInsertionClient       = __hidden :: __impl :: __ListIteratorRelativeInsertionClient < __ElementType >;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @typedef protected alias for __ListConstIteratorRelativeInsertionClient base interface - providing const iterator relative insertion functions
         * @protected
         */
        using ConstIteratorRelativeInsertionClient  = __hidden :: __impl :: __ListConstIteratorRelativeInsertionClient < __ElementType >;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @typedef protected alias for __ListIndexedOperationsClient base interface - providing index based operations
         * @protected
         */
        using IndexedOperationsClient               = __hidden :: __impl :: __ListIndexedOperationsClient < __ElementType >;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @typedef protected alias for __ListReplaceClient base interface - providing replace operations
         * @protected
         */
        using ReplaceClient                         = __hidden :: __impl :: __ListReplaceClient < __ElementType >;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @typedef protected alias for __ListReplaceOfCollectionClient base interface - providing replace of collection operations
         * @protected
         */
        using ReplaceOfCollectionClient             = __hidden :: __impl :: __ListReplaceOfCollectionClient < __ElementType >;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @typedef protected alias for __ListReplaceOfInitializerListClient base interface - providing replace of initializer list operations
         * @protected
         */
        using ReplaceOfInitializerListClient        = __hidden :: __impl :: __ListReplaceOfInitializerListClient < __ElementType >;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @typedef protected alias for __ListReplaceByClient base interface - providing replace by predicate operations
         * @protected
         */
        using ReplaceByClient                       = __hidden :: __impl :: __ListReplaceByClient < __ElementType >;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @typedef protected alias for __ListIndicesClient base interface - providing index query operations
         * @protected
         */
        using IndicesClient                         = __hidden :: __impl :: __ListIndicesClient < __ElementType >;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @typedef protected alias for __ListIndicesOfCollectionClient base interface - providing indices of collection elements query operations
         * @protected
         */
        using IndicesOfCollectionClient             = __hidden :: __impl :: __ListIndicesOfCollectionClient < __ElementType >;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @typedef protected alias for __ListIndicesOfInitializerListClient base interface - providing indices of initializer list elements query operations
         * @protected
         */
        using IndicesOfInitializerListClient        = __hidden :: __impl :: __ListIndicesOfInitializerListClient < __ElementType >;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @typedef protected alias for __ListIndicesByClient base interface - providing indices of elements validated by predicate query operations
         * @protected
         */
        using IndicesByClient                       = __hidden :: __impl :: __ListIndicesByClient < __ElementType >;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @typedef imported protected alias for __GenericHandler, representing a generic member function pointer, represents a function returned at a request made through the Collection Communication Channel
         * @protected
         */
        using typename MutableCollectionBase :: __GenericHandler;        /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @typedef imported protected alias for __GenericConstHandler, representing a generic member const-function pointer, represents a function returned at a request made through the Collection Communication Channel
         * @protected
         */
        using typename MutableCollectionBase :: __GenericConstHandler;   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

    public: /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @typedef imported protected alias for Iterator, representing a forward mutable iterator
         * @public
         */
        using typename DelegateForwardIterableClient :: Iterator;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @typedef imported protected alias for ConstIterator, representing a forward immutable iterator
         * @public
         */
        using typename DelegateForwardConstIterableClient :: ConstIterator;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @typedef imported protected alias for ReverseIterator, representing a backward mutable iterator
         * @public
         */
        using typename DelegateBackwardIterableClient :: ReverseIterator;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @typedef imported protected alias for ConstReverseIterator, representing a backward immutable iterator
         * @public
         */
        using typename DelegateBackwardConstIterableClient :: ConstReverseIterator;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @brief Public constant representing an invalid list index. Used by index functions to denote the absence of an element.
         * @static
         * @public
         */
        static Index const invalidIndex = -1;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @brief Default Constructor
         * @exceptsafe
         * @test Suite: STS-00001, Group: All, Test Cases: All
         * @protected
         */
        constexpr List () noexcept;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
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

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
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

    public: /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @brief Destructor
         * @exceptsafe
         * @test Suite: STS-00001, Group: All, Test Cases: All
         * @public
         */
        __CDS_cpplang_ConstexprDestructor ~List () noexcept override;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @brief Deleted Copy Assignment Operator
         * @param [in] list : List cref = Constant Reference to a list to copy data from
         * @exceptsafe
         * @return List ref = Reference to the modified object
         *
         * @test N/A
         * @public
         */
        auto operator = (
                List const & /* list */
        ) noexcept -> List & = delete;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @brief Deleted Move Assignment Operator
         * @param [in, out] list : List mref = Move Reference to a list to move data from
         * @exceptsafe
         * @return List ref = Reference to the modified object
         *
         * @test N/A
         * @public
         */
        auto operator = (
                List && /* list */
        ) noexcept -> List & = delete;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @inherit begin function inherited from DelegateForwardIterableClient interface.
         * Will hide the variant inherited from MutableCollection, which is unidirectional
         * and will use the bidirectional one provided by this inheritance
         * @test Suite: LTS-00001, Group: LTG-00200-IT, Test Cases: {
         *      LTC-00201-IT-perValueCheck,
         *      LTC-00205-IT-perValueBwdCheck,
         *      LTC-00209-IT-itMutabilityRange,
         *      LTC-00210-IT-itMutabilityStd
         * }
         * @public
         */
        using DelegateForwardIterableClient :: begin;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @inherit end function inherited from DelegateForwardIterableClient interface.
         * Will hide the variant inherited from MutableCollection, which is unidirectional
         * and will use the bidirectional one provided by this inheritance
         * @test Suite: LTS-00001, Group: LTG-00200-IT, Test Cases: {
         *      LTC-00201-IT-perValueCheck,
         *      LTC-00205-IT-perValueBwdCheck,
         *      LTC-00209-IT-itMutabilityRange,
         *      LTC-00210-IT-itMutabilityStd
         * }
         * @public
         */
        using DelegateForwardIterableClient :: end;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @inherit reverse begin function inherited from DelegateBackwardIterableClient interface.
         * @test Suite: LTS-00001, Group: LTG-00200-IT, Test Cases: {
         *      LTC-00203-IT-perValueRevCheck,
         *      LTC-00207-IT-perValueRevBwdCheck,
         *      LTC-00211-IT-itMutabilityStdRev
         * }
         * @public
         */
        using DelegateBackwardIterableClient :: rbegin;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @inherit reverse end function inherited from DelegateBackwardIterableClient interface.
         * @test Suite: LTS-00001, Group: LTG-00200-IT, Test Cases: {
         *      LTC-00203-IT-perValueRevCheck,
         *      LTC-00207-IT-perValueRevBwdCheck,
         *      LTC-00211-IT-itMutabilityStdRev
         * }
         * @public
         */
        using DelegateBackwardIterableClient :: rend;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @inherit const begin function inherited from DelegateForwardConstIterableClient interface.
         * Will hide the variant inherited from MutableCollection, which is unidirectional
         * and will use the bidirectional one provided by this inheritance
         * @test Suite: LTS-00001, Group: LTG-00200-IT, Test Cases: {
         *      LTC-00202-IT-perValueImmCheck,
         *      LTC-00206-IT-perValueBwdImmCheck
         * }
         * @public
         */
        using DelegateForwardConstIterableClient :: begin;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @inherit const end function inherited from DelegateForwardConstIterableClient interface.
         * Will hide the variant inherited from MutableCollection, which is unidirectional
         * and will use the bidirectional one provided by this inheritance
         * @test Suite: LTS-00001, Group: LTG-00200-IT, Test Cases: {
         *      LTC-00202-IT-perValueImmCheck,
         *      LTC-00206-IT-perValueBwdImmCheck
         * }
         * @public
         */
        using DelegateForwardConstIterableClient :: end;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @inherit const begin function inherited from DelegateForwardConstIterableClient interface.
         * Will hide the variant inherited from MutableCollection, which is unidirectional
         * and will use the bidirectional one provided by this inheritance
         * @test Suite: LTS-00001, Group: LTG-00200-IT, Test Cases: {
         *      LTC-00202-IT-perValueImmCheck,
         *      LTC-00206-IT-perValueBwdImmCheck
         * }
         * @public
         */
        using DelegateForwardConstIterableClient :: cbegin;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @inherit const end function inherited from DelegateForwardConstIterableClient interface.
         * Will hide the variant inherited from MutableCollection, which is unidirectional
         * and will use the bidirectional one provided by this inheritance
         * @test Suite: LTS-00001, Group: LTG-00200-IT, Test Cases: {
         *      LTC-00202-IT-perValueImmCheck,
         *      LTC-00206-IT-perValueBwdImmCheck
         * }
         * @public
         */
        using DelegateForwardConstIterableClient :: cend;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @inherit const reverse begin function inherited from DelegateBackwardConstIterableClient interface.
         * @test Suite: LTS-00001, Group: LTG-00200-IT, Test Cases: {
         *      LTC-00204-IT-perValueRevImmCheck,
         *      LTC-00208-IT-perValueRevBwdImmCheck
         * }
         * @public
         */
        using DelegateBackwardConstIterableClient :: rbegin;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @inherit const reverse end function inherited from DelegateBackwardConstIterableClient interface.
         * @test Suite: LTS-00001, Group: LTG-00200-IT, Test Cases: {
         *      LTC-00204-IT-perValueRevImmCheck,
         *      LTC-00208-IT-perValueRevBwdImmCheck
         * }
         * @public
         */
        using DelegateBackwardConstIterableClient :: rend;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @inherit const reverse begin function inherited from DelegateBackwardConstIterableClient interface.
         * @test Suite: LTS-00001, Group: LTG-00200-IT, Test Cases: {
         *      LTC-00204-IT-perValueRevImmCheck,
         *      LTC-00208-IT-perValueRevBwdImmCheck
         * }
         * @public
         */
        using DelegateBackwardConstIterableClient :: crbegin;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @inherit const reverse end function inherited from DelegateBackwardConstIterableClient interface.
         * @test Suite: LTS-00001, Group: LTG-00200-IT, Test Cases: {
         *      LTC-00204-IT-perValueRevImmCheck,
         *      LTC-00208-IT-perValueRevBwdImmCheck
         * }
         * @public
         */
        using DelegateBackwardConstIterableClient :: crend;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @inherit pushBack function inherited from BoundaryInsertionClient interface.
         * @test Suite: LTS-00001, Group: LTG-00300-BI, Test Cases: {
         *      LTC-00301-IT-pushBackCopy1,
         *      LTC-00302-IT-pushBackCopy2,
         *      LTC-00303-IT-pushBackCopy3,
         *      LTC-00304-IT-pushBackMove1,
         *      LTC-00305-IT-pushBackMove2
         * }
         * @public
         */
        using BoundaryInsertionClient :: pushBack;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @inherit pushBackAll function inherited from BoundaryInsertionClient interface.
         * @test Suite: LTS-00001, Group: LTG-00300-BI, Test Cases: {
         *      LTC-00311-IT-pushBackValues
         * }
         * @public
         */
        using BoundaryInsertionClient :: pushBackAll;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @inherit pushBackAllOf function inherited from BoundaryInsertionClient interface.
         * @test Suite: LTS-00001, Group: LTG-00300-BI, Test Cases: {
         *      LTC-00311-IT-pushBackAllOfInitList,
         *      LTC-00312-IT-pushBackAllOfColl,
         *      LTC-00315-IT-pushBackItRange1,
         *      LTC-00317-IT-pushBackItRange2,
         *      LTC-00319-IT-pushBackItRange3
         * }
         * @public
         */
        using BoundaryInsertionClient :: pushBackAllOf;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @inherit pushBack function inherited from BoundaryInsertionClient interface.
         * @test Suite: LTS-00001, Group: LTG-00300-BI, Test Cases: {
         *      LTC-00306-IT-pushFrontCopy1,
         *      LTC-00307-IT-pushFrontCopy2,
         *      LTC-00308-IT-pushFrontCopy3,
         *      LTC-00309-IT-pushFrontMove1,
         *      LTC-00310-IT-pushFrontMove2
         * }
         * @public
         */
        using BoundaryInsertionClient :: pushFront;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @inherit pushFrontAll function inherited from BoundaryInsertionClient interface.
         * @test Suite: LTS-00001, Group: LTG-00300-BI, Test Cases: {
         *      LTC-00312-IT-pushFrontValues
         * }
         * @public
         */
        using BoundaryInsertionClient :: pushFrontAll;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @inherit pushFrontAllOf function inherited from BoundaryInsertionClient interface.
         * @test Suite: LTS-00001, Group: LTG-00300-BI, Test Cases: {
         *      LTC-00313-IT-pushFrontAllOfInitList,
         *      LTC-00314-IT-pushFrontAllOfColl,
         *      LTC-00316-IT-pushFrontItRange1,
         *      LTC-00318-IT-pushFrontItRange2,
         *      LTC-00320-IT-pushFrontItRange3
         * }
         * @public
         */
        using BoundaryInsertionClient :: pushFrontAllOf;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @inherit emplaceBack function inherited from BoundaryInsertionClient interface.
         * @test Suite: LTS-00001, Group: LTG-00300-BI, Test Cases: {
         *      LTC-00324-IT-emplaceBack
         * }
         * @public
         */
        using BoundaryInsertionClient :: emplaceBack;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @inherit emplaceFront function inherited from BoundaryInsertionClient interface.
         * @test Suite: LTS-00001, Group: LTG-00300-BI, Test Cases: {
         *      LTC-00323-IT-emplaceFront
         * }
         * @public
         */
        using BoundaryInsertionClient :: emplaceFront;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @inherit insertBefore function inherited from IteratorRelativeInsertionClient interface.
         * @test Suite: LTS-00001, Group: LTG-00400-RI, Test Cases: {
         *      LTC-00401-IT-insertBeforeItCase1SingleValue1OffsetCase1,
         *      LTC-00402-IT-insertBeforeItCase1SingleValue1OffsetCase2,
         *      LTC-00403-IT-insertBeforeItCase1SingleValue1OffsetCase3,
         *      LTC-00404-IT-insertBeforeItCase1SingleValue1OffsetCase4,
         *      LTC-00405-IT-insertBeforeItCase1SingleValue2OffsetCase1,
         *      LTC-00406-IT-insertBeforeItCase1SingleValue2OffsetCase2,
         *      LTC-00407-IT-insertBeforeItCase1SingleValue2OffsetCase3,
         *      LTC-00408-IT-insertBeforeItCase1SingleValue2OffsetCase4,
         *      LTC-00409-IT-insertBeforeItCase1SingleValue3OffsetCase1,
         *      LTC-00410-IT-insertBeforeItCase1SingleValue3OffsetCase2,
         *      LTC-00411-IT-insertBeforeItCase1SingleValue3OffsetCase3,
         *      LTC-00412-IT-insertBeforeItCase1SingleValue3OffsetCase4,
         *      LTC-00413-IT-insertBeforeItCase3SingleValue1OffsetCase1,
         *      LTC-00414-IT-insertBeforeItCase3SingleValue1OffsetCase2,
         *      LTC-00415-IT-insertBeforeItCase3SingleValue1OffsetCase3,
         *      LTC-00416-IT-insertBeforeItCase3SingleValue1OffsetCase4,
         *      LTC-00417-IT-insertBeforeItCase3SingleValue2OffsetCase1,
         *      LTC-00418-IT-insertBeforeItCase3SingleValue2OffsetCase2,
         *      LTC-00419-IT-insertBeforeItCase3SingleValue2OffsetCase3,
         *      LTC-00420-IT-insertBeforeItCase3SingleValue2OffsetCase4,
         *      LTC-00421-IT-insertBeforeItCase3SingleValue3OffsetCase1,
         *      LTC-00422-IT-insertBeforeItCase3SingleValue3OffsetCase2,
         *      LTC-00423-IT-insertBeforeItCase3SingleValue3OffsetCase3,
         *      LTC-00424-IT-insertBeforeItCase3SingleValue3OffsetCase4
         * }
         * @public
         */
        using IteratorRelativeInsertionClient :: insertBefore;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @inherit insertAllBefore function inherited from IteratorRelativeInsertionClient interface.
         * @test Suite: LTS-00001, Group: LTG-00400-RI, Test Cases: {
         *      LTC-00593-IT-insertAllBeforeItCase1PackOffsetCase1,
         *      LTC-00594-IT-insertAllBeforeItCase1PackOffsetCase2,
         *      LTC-00595-IT-insertAllBeforeItCase1PackOffsetCase3,
         *      LTC-00596-IT-insertAllBeforeItCase1PackOffsetCase4,
         *      LTC-00601-IT-insertAllBeforeItCase3PackOffsetCase1,
         *      LTC-00602-IT-insertAllBeforeItCase3PackOffsetCase2,
         *      LTC-00603-IT-insertAllBeforeItCase3PackOffsetCase3,
         *      LTC-00604-IT-insertAllBeforeItCase3PackOffsetCase4
         * }
         * @public
         */
        using IteratorRelativeInsertionClient :: insertAllBefore;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @inherit insertAllOfBefore function inherited from IteratorRelativeInsertionClient interface.
         * @test Suite: LTS-00001, Group: LTG-00400-RI, Test Cases: {
         *      LTC-00497-IT-insertAllOfBeforeItCase1MultipleValues1OffsetCase1,
         *      LTC-00498-IT-insertAllOfBeforeItCase1MultipleValues1OffsetCase2,
         *      LTC-00499-IT-insertAllOfBeforeItCase1MultipleValues1OffsetCase3,
         *      LTC-00500-IT-insertAllOfBeforeItCase1MultipleValues1OffsetCase4,
         *      LTC-00501-IT-insertAllOfBeforeItCase1MultipleValues2OffsetCase1,
         *      LTC-00502-IT-insertAllOfBeforeItCase1MultipleValues2OffsetCase2,
         *      LTC-00503-IT-insertAllOfBeforeItCase1MultipleValues2OffsetCase3,
         *      LTC-00504-IT-insertAllOfBeforeItCase1MultipleValues2OffsetCase4,
         *      LTC-00505-IT-insertAllOfBeforeItCase1MultipleValues3OffsetCase1,
         *      LTC-00506-IT-insertAllOfBeforeItCase1MultipleValues3OffsetCase2,
         *      LTC-00507-IT-insertAllOfBeforeItCase1MultipleValues3OffsetCase3,
         *      LTC-00508-IT-insertAllOfBeforeItCase1MultipleValues3OffsetCase4,
         *      LTC-00509-IT-insertAllOfBeforeItCase3MultipleValues1OffsetCase1,
         *      LTC-00510-IT-insertAllOfBeforeItCase3MultipleValues1OffsetCase2,
         *      LTC-00511-IT-insertAllOfBeforeItCase3MultipleValues1OffsetCase3,
         *      LTC-00512-IT-insertAllOfBeforeItCase3MultipleValues1OffsetCase4,
         *      LTC-00513-IT-insertAllOfBeforeItCase3MultipleValues2OffsetCase1,
         *      LTC-00514-IT-insertAllOfBeforeItCase3MultipleValues2OffsetCase2,
         *      LTC-00515-IT-insertAllOfBeforeItCase3MultipleValues2OffsetCase3,
         *      LTC-00516-IT-insertAllOfBeforeItCase3MultipleValues2OffsetCase4,
         *      LTC-00517-IT-insertAllOfBeforeItCase3MultipleValues3OffsetCase1,
         *      LTC-00518-IT-insertAllOfBeforeItCase3MultipleValues3OffsetCase2,
         *      LTC-00519-IT-insertAllOfBeforeItCase3MultipleValues3OffsetCase3,
         *      LTC-00520-IT-insertAllOfBeforeItCase3MultipleValues3OffsetCase4
         * }
         * @public
         */
        using IteratorRelativeInsertionClient :: insertAllOfBefore;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @inherit insertAfter function inherited from IteratorRelativeInsertionClient interface.
         * @test Suite: LTS-00001, Group: LTG-00400-RI, Test Cases: {
         *      LTC-00449-IT-insertAfterItCase1SingleValue1OffsetCase1,
         *      LTC-00450-IT-insertAfterItCase1SingleValue1OffsetCase2,
         *      LTC-00451-IT-insertAfterItCase1SingleValue1OffsetCase3,
         *      LTC-00452-IT-insertAfterItCase1SingleValue1OffsetCase4,
         *      LTC-00453-IT-insertAfterItCase1SingleValue2OffsetCase1,
         *      LTC-00454-IT-insertAfterItCase1SingleValue2OffsetCase2,
         *      LTC-00455-IT-insertAfterItCase1SingleValue2OffsetCase3,
         *      LTC-00456-IT-insertAfterItCase1SingleValue2OffsetCase4,
         *      LTC-00457-IT-insertAfterItCase1SingleValue3OffsetCase1,
         *      LTC-00458-IT-insertAfterItCase1SingleValue3OffsetCase2,
         *      LTC-00459-IT-insertAfterItCase1SingleValue3OffsetCase3,
         *      LTC-00460-IT-insertAfterItCase1SingleValue3OffsetCase4,
         *      LTC-00461-IT-insertAfterItCase3SingleValue1OffsetCase1,
         *      LTC-00462-IT-insertAfterItCase3SingleValue1OffsetCase2,
         *      LTC-00463-IT-insertAfterItCase3SingleValue1OffsetCase3,
         *      LTC-00464-IT-insertAfterItCase3SingleValue1OffsetCase4,
         *      LTC-00465-IT-insertAfterItCase3SingleValue2OffsetCase1,
         *      LTC-00466-IT-insertAfterItCase3SingleValue2OffsetCase2,
         *      LTC-00467-IT-insertAfterItCase3SingleValue2OffsetCase3,
         *      LTC-00468-IT-insertAfterItCase3SingleValue2OffsetCase4,
         *      LTC-00469-IT-insertAfterItCase3SingleValue3OffsetCase1,
         *      LTC-00470-IT-insertAfterItCase3SingleValue3OffsetCase2,
         *      LTC-00471-IT-insertAfterItCase3SingleValue3OffsetCase3,
         *      LTC-00472-IT-insertAfterItCase3SingleValue3OffsetCase4
         * }
         * @public
         */
        using IteratorRelativeInsertionClient :: insertAfter;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @inherit insertAllAfter function inherited from IteratorRelativeInsertionClient interface.
         * @test Suite: LTS-00001, Group: LTG-00400-RI, Test Cases: {
         *      LTC-00609-IT-insertAllAfterItCase1PackOffsetCase1,
         *      LTC-00610-IT-insertAllAfterItCase1PackOffsetCase2,
         *      LTC-00611-IT-insertAllAfterItCase1PackOffsetCase3,
         *      LTC-00612-IT-insertAllAfterItCase1PackOffsetCase4,
         *      LTC-00617-IT-insertAllAfterItCase3PackOffsetCase1,
         *      LTC-00618-IT-insertAllAfterItCase3PackOffsetCase2,
         *      LTC-00619-IT-insertAllAfterItCase3PackOffsetCase3,
         *      LTC-00620-IT-insertAllAfterItCase3PackOffsetCase4
         * }
         * @public
         */
        using IteratorRelativeInsertionClient :: insertAllAfter;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @inherit insertAllOfAfter function inherited from IteratorRelativeInsertionClient interface.
         * @test Suite: LTS-00001, Group: LTG-00400-RI, Test Cases: {
         *      LTC-00545-IT-insertAllOfAfterItCase1MultipleValues1OffsetCase1,
         *      LTC-00546-IT-insertAllOfAfterItCase1MultipleValues1OffsetCase2,
         *      LTC-00547-IT-insertAllOfAfterItCase1MultipleValues1OffsetCase3,
         *      LTC-00548-IT-insertAllOfAfterItCase1MultipleValues1OffsetCase4,
         *      LTC-00549-IT-insertAllOfAfterItCase1MultipleValues2OffsetCase1,
         *      LTC-00550-IT-insertAllOfAfterItCase1MultipleValues2OffsetCase2,
         *      LTC-00551-IT-insertAllOfAfterItCase1MultipleValues2OffsetCase3,
         *      LTC-00552-IT-insertAllOfAfterItCase1MultipleValues2OffsetCase4,
         *      LTC-00553-IT-insertAllOfAfterItCase1MultipleValues3OffsetCase1,
         *      LTC-00554-IT-insertAllOfAfterItCase1MultipleValues3OffsetCase2,
         *      LTC-00555-IT-insertAllOfAfterItCase1MultipleValues3OffsetCase3,
         *      LTC-00556-IT-insertAllOfAfterItCase1MultipleValues3OffsetCase4,
         *      LTC-00557-IT-insertAllOfAfterItCase3MultipleValues1OffsetCase1,
         *      LTC-00558-IT-insertAllOfAfterItCase3MultipleValues1OffsetCase2,
         *      LTC-00559-IT-insertAllOfAfterItCase3MultipleValues1OffsetCase3,
         *      LTC-00560-IT-insertAllOfAfterItCase3MultipleValues1OffsetCase4,
         *      LTC-00561-IT-insertAllOfAfterItCase3MultipleValues2OffsetCase1,
         *      LTC-00562-IT-insertAllOfAfterItCase3MultipleValues2OffsetCase2,
         *      LTC-00563-IT-insertAllOfAfterItCase3MultipleValues2OffsetCase3,
         *      LTC-00564-IT-insertAllOfAfterItCase3MultipleValues2OffsetCase4,
         *      LTC-00565-IT-insertAllOfAfterItCase3MultipleValues3OffsetCase1,
         *      LTC-00566-IT-insertAllOfAfterItCase3MultipleValues3OffsetCase2,
         *      LTC-00567-IT-insertAllOfAfterItCase3MultipleValues3OffsetCase3,
         *      LTC-00568-IT-insertAllOfAfterItCase3MultipleValues3OffsetCase4
         * }
         * @public
         */
        using IteratorRelativeInsertionClient :: insertAllOfAfter;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @inherit emplaceBefore function inherited from IteratorRelativeInsertionClient interface.
         * @test Suite: LTS-00001, Group: LTG-00400-RI, Test Cases: {
         *      LTC-00401-IT-insertBeforeItCase1SingleValue1OffsetCase1,
         *      LTC-00402-IT-insertBeforeItCase1SingleValue1OffsetCase2,
         *      LTC-00403-IT-insertBeforeItCase1SingleValue1OffsetCase3,
         *      LTC-00404-IT-insertBeforeItCase1SingleValue1OffsetCase4,
         *      LTC-00405-IT-insertBeforeItCase1SingleValue2OffsetCase1,
         *      LTC-00406-IT-insertBeforeItCase1SingleValue2OffsetCase2,
         *      LTC-00407-IT-insertBeforeItCase1SingleValue2OffsetCase3,
         *      LTC-00408-IT-insertBeforeItCase1SingleValue2OffsetCase4,
         *      LTC-00409-IT-insertBeforeItCase1SingleValue3OffsetCase1,
         *      LTC-00410-IT-insertBeforeItCase1SingleValue3OffsetCase2,
         *      LTC-00411-IT-insertBeforeItCase1SingleValue3OffsetCase3,
         *      LTC-00412-IT-insertBeforeItCase1SingleValue3OffsetCase4,
         *      LTC-00413-IT-insertBeforeItCase3SingleValue1OffsetCase1,
         *      LTC-00414-IT-insertBeforeItCase3SingleValue1OffsetCase2,
         *      LTC-00415-IT-insertBeforeItCase3SingleValue1OffsetCase3,
         *      LTC-00416-IT-insertBeforeItCase3SingleValue1OffsetCase4,
         *      LTC-00417-IT-insertBeforeItCase3SingleValue2OffsetCase1,
         *      LTC-00418-IT-insertBeforeItCase3SingleValue2OffsetCase2,
         *      LTC-00419-IT-insertBeforeItCase3SingleValue2OffsetCase3,
         *      LTC-00420-IT-insertBeforeItCase3SingleValue2OffsetCase4,
         *      LTC-00421-IT-insertBeforeItCase3SingleValue3OffsetCase1,
         *      LTC-00422-IT-insertBeforeItCase3SingleValue3OffsetCase2,
         *      LTC-00423-IT-insertBeforeItCase3SingleValue3OffsetCase3,
         *      LTC-00424-IT-insertBeforeItCase3SingleValue3OffsetCase4
         * }
         * @public
         */
        using IteratorRelativeInsertionClient :: emplaceBefore;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @inherit emplaceAfter function inherited from IteratorRelativeInsertionClient interface.
         * @test Suite: LTS-00001, Group: LTG-00400-RI, Test Cases: {
         *      LTC-00449-IT-insertAfterItCase1SingleValue1OffsetCase1,
         *      LTC-00450-IT-insertAfterItCase1SingleValue1OffsetCase2,
         *      LTC-00451-IT-insertAfterItCase1SingleValue1OffsetCase3,
         *      LTC-00452-IT-insertAfterItCase1SingleValue1OffsetCase4,
         *      LTC-00453-IT-insertAfterItCase1SingleValue2OffsetCase1,
         *      LTC-00454-IT-insertAfterItCase1SingleValue2OffsetCase2,
         *      LTC-00455-IT-insertAfterItCase1SingleValue2OffsetCase3,
         *      LTC-00456-IT-insertAfterItCase1SingleValue2OffsetCase4,
         *      LTC-00457-IT-insertAfterItCase1SingleValue3OffsetCase1,
         *      LTC-00458-IT-insertAfterItCase1SingleValue3OffsetCase2,
         *      LTC-00459-IT-insertAfterItCase1SingleValue3OffsetCase3,
         *      LTC-00460-IT-insertAfterItCase1SingleValue3OffsetCase4,
         *      LTC-00461-IT-insertAfterItCase3SingleValue1OffsetCase1,
         *      LTC-00462-IT-insertAfterItCase3SingleValue1OffsetCase2,
         *      LTC-00463-IT-insertAfterItCase3SingleValue1OffsetCase3,
         *      LTC-00464-IT-insertAfterItCase3SingleValue1OffsetCase4,
         *      LTC-00465-IT-insertAfterItCase3SingleValue2OffsetCase1,
         *      LTC-00466-IT-insertAfterItCase3SingleValue2OffsetCase2,
         *      LTC-00467-IT-insertAfterItCase3SingleValue2OffsetCase3,
         *      LTC-00468-IT-insertAfterItCase3SingleValue2OffsetCase4,
         *      LTC-00469-IT-insertAfterItCase3SingleValue3OffsetCase1,
         *      LTC-00470-IT-insertAfterItCase3SingleValue3OffsetCase2,
         *      LTC-00471-IT-insertAfterItCase3SingleValue3OffsetCase3,
         *      LTC-00472-IT-insertAfterItCase3SingleValue3OffsetCase4
         * }
         * @public
         */
        using IteratorRelativeInsertionClient :: emplaceAfter;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @inherit insertBefore function inherited from ConstIteratorRelativeInsertionClient interface.
         * @test Suite: LTS-00001, Group: LTG-00400-RI, Test Cases: {
         *      LTC-00425-IT-insertBeforeItCase2SingleValue1OffsetCase1,
         *      LTC-00426-IT-insertBeforeItCase2SingleValue1OffsetCase2,
         *      LTC-00427-IT-insertBeforeItCase2SingleValue1OffsetCase3,
         *      LTC-00428-IT-insertBeforeItCase2SingleValue1OffsetCase4,
         *      LTC-00429-IT-insertBeforeItCase2SingleValue2OffsetCase1,
         *      LTC-00430-IT-insertBeforeItCase2SingleValue2OffsetCase2,
         *      LTC-00431-IT-insertBeforeItCase2SingleValue2OffsetCase3,
         *      LTC-00432-IT-insertBeforeItCase2SingleValue2OffsetCase4,
         *      LTC-00433-IT-insertBeforeItCase2SingleValue3OffsetCase1,
         *      LTC-00434-IT-insertBeforeItCase2SingleValue3OffsetCase2,
         *      LTC-00435-IT-insertBeforeItCase2SingleValue3OffsetCase3,
         *      LTC-00436-IT-insertBeforeItCase2SingleValue3OffsetCase4,
         *      LTC-00437-IT-insertBeforeItCase4SingleValue1OffsetCase1,
         *      LTC-00438-IT-insertBeforeItCase4SingleValue1OffsetCase2,
         *      LTC-00439-IT-insertBeforeItCase4SingleValue1OffsetCase3,
         *      LTC-00440-IT-insertBeforeItCase4SingleValue1OffsetCase4,
         *      LTC-00441-IT-insertBeforeItCase4SingleValue2OffsetCase1,
         *      LTC-00442-IT-insertBeforeItCase4SingleValue2OffsetCase2,
         *      LTC-00443-IT-insertBeforeItCase4SingleValue2OffsetCase3,
         *      LTC-00444-IT-insertBeforeItCase4SingleValue2OffsetCase4,
         *      LTC-00445-IT-insertBeforeItCase4SingleValue3OffsetCase1,
         *      LTC-00446-IT-insertBeforeItCase4SingleValue3OffsetCase2,
         *      LTC-00447-IT-insertBeforeItCase4SingleValue3OffsetCase3,
         *      LTC-00448-IT-insertBeforeItCase4SingleValue3OffsetCase4
         * }
         * @public
         */
        using ConstIteratorRelativeInsertionClient :: insertBefore;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @inherit insertAllBefore function inherited from ConstIteratorRelativeInsertionClient interface.
         * @test Suite: LTS-00001, Group: LTG-00400-RI, Test Cases: {
         *      LTC-00597-IT-insertAllBeforeItCase2PackOffsetCase1,
         *      LTC-00598-IT-insertAllBeforeItCase2PackOffsetCase2,
         *      LTC-00599-IT-insertAllBeforeItCase2PackOffsetCase3,
         *      LTC-00600-IT-insertAllBeforeItCase2PackOffsetCase4,
         *      LTC-00605-IT-insertAllBeforeItCase4PackOffsetCase1,
         *      LTC-00606-IT-insertAllBeforeItCase4PackOffsetCase2,
         *      LTC-00607-IT-insertAllBeforeItCase4PackOffsetCase3,
         *      LTC-00608-IT-insertAllBeforeItCase4PackOffsetCase4
         * }
         * @public
         */
        using ConstIteratorRelativeInsertionClient :: insertAllBefore;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @inherit insertAllOfBefore function inherited from ConstIteratorRelativeInsertionClient interface.
         * @test Suite: LTS-00001, Group: LTG-00400-RI, Test Cases: {
         *      LTC-00521-IT-insertAllOfBeforeItCase2MultipleValues1OffsetCase1,
         *      LTC-00522-IT-insertAllOfBeforeItCase2MultipleValues1OffsetCase2,
         *      LTC-00523-IT-insertAllOfBeforeItCase2MultipleValues1OffsetCase3,
         *      LTC-00524-IT-insertAllOfBeforeItCase2MultipleValues1OffsetCase4,
         *      LTC-00525-IT-insertAllOfBeforeItCase2MultipleValues2OffsetCase1,
         *      LTC-00526-IT-insertAllOfBeforeItCase2MultipleValues2OffsetCase2,
         *      LTC-00527-IT-insertAllOfBeforeItCase2MultipleValues2OffsetCase3,
         *      LTC-00528-IT-insertAllOfBeforeItCase2MultipleValues2OffsetCase4,
         *      LTC-00529-IT-insertAllOfBeforeItCase2MultipleValues3OffsetCase1,
         *      LTC-00530-IT-insertAllOfBeforeItCase2MultipleValues3OffsetCase2,
         *      LTC-00531-IT-insertAllOfBeforeItCase2MultipleValues3OffsetCase3,
         *      LTC-00532-IT-insertAllOfBeforeItCase2MultipleValues3OffsetCase4,
         *      LTC-00533-IT-insertAllOfBeforeItCase4MultipleValues1OffsetCase1,
         *      LTC-00534-IT-insertAllOfBeforeItCase4MultipleValues1OffsetCase2,
         *      LTC-00535-IT-insertAllOfBeforeItCase4MultipleValues1OffsetCase3,
         *      LTC-00536-IT-insertAllOfBeforeItCase4MultipleValues1OffsetCase4,
         *      LTC-00537-IT-insertAllOfBeforeItCase4MultipleValues2OffsetCase1,
         *      LTC-00538-IT-insertAllOfBeforeItCase4MultipleValues2OffsetCase2,
         *      LTC-00539-IT-insertAllOfBeforeItCase4MultipleValues2OffsetCase3,
         *      LTC-00540-IT-insertAllOfBeforeItCase4MultipleValues2OffsetCase4,
         *      LTC-00541-IT-insertAllOfBeforeItCase4MultipleValues3OffsetCase1,
         *      LTC-00542-IT-insertAllOfBeforeItCase4MultipleValues3OffsetCase2,
         *      LTC-00543-IT-insertAllOfBeforeItCase4MultipleValues3OffsetCase3,
         *      LTC-00544-IT-insertAllOfBeforeItCase4MultipleValues3OffsetCase4
         * }
         * @public
         */
        using ConstIteratorRelativeInsertionClient :: insertAllOfBefore;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @inherit insertAfter function inherited from ConstIteratorRelativeInsertionClient interface.
         * @test Suite: LTS-00001, Group: LTG-00400-RI, Test Cases: {
         *      LTC-00473-IT-insertAfterItCase2SingleValue1OffsetCase1,
         *      LTC-00474-IT-insertAfterItCase2SingleValue1OffsetCase2,
         *      LTC-00475-IT-insertAfterItCase2SingleValue1OffsetCase3,
         *      LTC-00476-IT-insertAfterItCase2SingleValue1OffsetCase4,
         *      LTC-00477-IT-insertAfterItCase2SingleValue2OffsetCase1,
         *      LTC-00478-IT-insertAfterItCase2SingleValue2OffsetCase2,
         *      LTC-00479-IT-insertAfterItCase2SingleValue2OffsetCase3,
         *      LTC-00480-IT-insertAfterItCase2SingleValue2OffsetCase4,
         *      LTC-00481-IT-insertAfterItCase2SingleValue3OffsetCase1,
         *      LTC-00482-IT-insertAfterItCase2SingleValue3OffsetCase2,
         *      LTC-00483-IT-insertAfterItCase2SingleValue3OffsetCase3,
         *      LTC-00484-IT-insertAfterItCase2SingleValue3OffsetCase4,
         *      LTC-00485-IT-insertAfterItCase4SingleValue1OffsetCase1,
         *      LTC-00486-IT-insertAfterItCase4SingleValue1OffsetCase2,
         *      LTC-00487-IT-insertAfterItCase4SingleValue1OffsetCase3,
         *      LTC-00488-IT-insertAfterItCase4SingleValue1OffsetCase4,
         *      LTC-00489-IT-insertAfterItCase4SingleValue2OffsetCase1,
         *      LTC-00490-IT-insertAfterItCase4SingleValue2OffsetCase2,
         *      LTC-00491-IT-insertAfterItCase4SingleValue2OffsetCase3,
         *      LTC-00492-IT-insertAfterItCase4SingleValue2OffsetCase4,
         *      LTC-00493-IT-insertAfterItCase4SingleValue3OffsetCase1,
         *      LTC-00494-IT-insertAfterItCase4SingleValue3OffsetCase2,
         *      LTC-00495-IT-insertAfterItCase4SingleValue3OffsetCase3,
         *      LTC-00496-IT-insertAfterItCase4SingleValue3OffsetCase4
         * }
         * @public
         */
        using ConstIteratorRelativeInsertionClient :: insertAfter;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @inherit insertAllAfter function inherited from ConstIteratorRelativeInsertionClient interface.
         * @test Suite: LTS-00001, Group: LTG-00400-RI, Test Cases: {
         *      LTC-00613-IT-insertAllAfterItCase2PackOffsetCase1,
         *      LTC-00614-IT-insertAllAfterItCase2PackOffsetCase2,
         *      LTC-00615-IT-insertAllAfterItCase2PackOffsetCase3,
         *      LTC-00616-IT-insertAllAfterItCase2PackOffsetCase4,
         *      LTC-00621-IT-insertAllAfterItCase4PackOffsetCase1,
         *      LTC-00622-IT-insertAllAfterItCase4PackOffsetCase2,
         *      LTC-00623-IT-insertAllAfterItCase4PackOffsetCase3,
         *      LTC-00624-IT-insertAllAfterItCase4PackOffsetCase4
         * }
         * @public
         */
        using ConstIteratorRelativeInsertionClient :: insertAllAfter;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @inherit insertAllOfAfter function inherited from ConstIteratorRelativeInsertionClient interface.
         * @test Suite: LTS-00001, Group: LTG-00400-RI, Test Cases: {
         *      LTC-00569-IT-insertAllOfAfterItCase2MultipleValues1OffsetCase1,
         *      LTC-00570-IT-insertAllOfAfterItCase2MultipleValues1OffsetCase2,
         *      LTC-00571-IT-insertAllOfAfterItCase2MultipleValues1OffsetCase3,
         *      LTC-00572-IT-insertAllOfAfterItCase2MultipleValues1OffsetCase4,
         *      LTC-00573-IT-insertAllOfAfterItCase2MultipleValues2OffsetCase1,
         *      LTC-00574-IT-insertAllOfAfterItCase2MultipleValues2OffsetCase2,
         *      LTC-00575-IT-insertAllOfAfterItCase2MultipleValues2OffsetCase3,
         *      LTC-00576-IT-insertAllOfAfterItCase2MultipleValues2OffsetCase4,
         *      LTC-00577-IT-insertAllOfAfterItCase2MultipleValues3OffsetCase1,
         *      LTC-00578-IT-insertAllOfAfterItCase2MultipleValues3OffsetCase2,
         *      LTC-00579-IT-insertAllOfAfterItCase2MultipleValues3OffsetCase3,
         *      LTC-00580-IT-insertAllOfAfterItCase2MultipleValues3OffsetCase4,
         *      LTC-00581-IT-insertAllOfAfterItCase4MultipleValues1OffsetCase1,
         *      LTC-00582-IT-insertAllOfAfterItCase4MultipleValues1OffsetCase2,
         *      LTC-00583-IT-insertAllOfAfterItCase4MultipleValues1OffsetCase3,
         *      LTC-00584-IT-insertAllOfAfterItCase4MultipleValues1OffsetCase4,
         *      LTC-00585-IT-insertAllOfAfterItCase4MultipleValues2OffsetCase1,
         *      LTC-00586-IT-insertAllOfAfterItCase4MultipleValues2OffsetCase2,
         *      LTC-00587-IT-insertAllOfAfterItCase4MultipleValues2OffsetCase3,
         *      LTC-00588-IT-insertAllOfAfterItCase4MultipleValues2OffsetCase4,
         *      LTC-00589-IT-insertAllOfAfterItCase4MultipleValues3OffsetCase1,
         *      LTC-00590-IT-insertAllOfAfterItCase4MultipleValues3OffsetCase2,
         *      LTC-00591-IT-insertAllOfAfterItCase4MultipleValues3OffsetCase3,
         *      LTC-00592-IT-insertAllOfAfterItCase4MultipleValues3OffsetCase4
         * }
         * @public
         */
        using ConstIteratorRelativeInsertionClient :: insertAllOfAfter;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @inherit emplaceBefore function inherited from ConstIteratorRelativeInsertionClient interface.
         * @test Suite: LTS-00001, Group: LTG-00400-RI, Test Cases: {
         *      LTC-00425-IT-insertBeforeItCase2SingleValue1OffsetCase1,
         *      LTC-00426-IT-insertBeforeItCase2SingleValue1OffsetCase2,
         *      LTC-00427-IT-insertBeforeItCase2SingleValue1OffsetCase3,
         *      LTC-00428-IT-insertBeforeItCase2SingleValue1OffsetCase4,
         *      LTC-00429-IT-insertBeforeItCase2SingleValue2OffsetCase1,
         *      LTC-00430-IT-insertBeforeItCase2SingleValue2OffsetCase2,
         *      LTC-00431-IT-insertBeforeItCase2SingleValue2OffsetCase3,
         *      LTC-00432-IT-insertBeforeItCase2SingleValue2OffsetCase4,
         *      LTC-00433-IT-insertBeforeItCase2SingleValue3OffsetCase1,
         *      LTC-00434-IT-insertBeforeItCase2SingleValue3OffsetCase2,
         *      LTC-00435-IT-insertBeforeItCase2SingleValue3OffsetCase3,
         *      LTC-00436-IT-insertBeforeItCase2SingleValue3OffsetCase4,
         *      LTC-00437-IT-insertBeforeItCase4SingleValue1OffsetCase1,
         *      LTC-00438-IT-insertBeforeItCase4SingleValue1OffsetCase2,
         *      LTC-00439-IT-insertBeforeItCase4SingleValue1OffsetCase3,
         *      LTC-00440-IT-insertBeforeItCase4SingleValue1OffsetCase4,
         *      LTC-00441-IT-insertBeforeItCase4SingleValue2OffsetCase1,
         *      LTC-00442-IT-insertBeforeItCase4SingleValue2OffsetCase2,
         *      LTC-00443-IT-insertBeforeItCase4SingleValue2OffsetCase3,
         *      LTC-00444-IT-insertBeforeItCase4SingleValue2OffsetCase4,
         *      LTC-00445-IT-insertBeforeItCase4SingleValue3OffsetCase1,
         *      LTC-00446-IT-insertBeforeItCase4SingleValue3OffsetCase2,
         *      LTC-00447-IT-insertBeforeItCase4SingleValue3OffsetCase3,
         *      LTC-00448-IT-insertBeforeItCase4SingleValue3OffsetCase4
         * }
         * @public
         */
        using ConstIteratorRelativeInsertionClient :: emplaceBefore;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @inherit emplaceAfter function inherited from ConstIteratorRelativeInsertionClient interface.
         * @test Suite: LTS-00001, Group: LTG-00400-RI, Test Cases: {
         *      LTC-00473-IT-insertAfterItCase2SingleValue1OffsetCase1,
         *      LTC-00474-IT-insertAfterItCase2SingleValue1OffsetCase2,
         *      LTC-00475-IT-insertAfterItCase2SingleValue1OffsetCase3,
         *      LTC-00476-IT-insertAfterItCase2SingleValue1OffsetCase4,
         *      LTC-00477-IT-insertAfterItCase2SingleValue2OffsetCase1,
         *      LTC-00478-IT-insertAfterItCase2SingleValue2OffsetCase2,
         *      LTC-00479-IT-insertAfterItCase2SingleValue2OffsetCase3,
         *      LTC-00480-IT-insertAfterItCase2SingleValue2OffsetCase4,
         *      LTC-00481-IT-insertAfterItCase2SingleValue3OffsetCase1,
         *      LTC-00482-IT-insertAfterItCase2SingleValue3OffsetCase2,
         *      LTC-00483-IT-insertAfterItCase2SingleValue3OffsetCase3,
         *      LTC-00484-IT-insertAfterItCase2SingleValue3OffsetCase4,
         *      LTC-00485-IT-insertAfterItCase4SingleValue1OffsetCase1,
         *      LTC-00486-IT-insertAfterItCase4SingleValue1OffsetCase2,
         *      LTC-00487-IT-insertAfterItCase4SingleValue1OffsetCase3,
         *      LTC-00488-IT-insertAfterItCase4SingleValue1OffsetCase4,
         *      LTC-00489-IT-insertAfterItCase4SingleValue2OffsetCase1,
         *      LTC-00490-IT-insertAfterItCase4SingleValue2OffsetCase2,
         *      LTC-00491-IT-insertAfterItCase4SingleValue2OffsetCase3,
         *      LTC-00492-IT-insertAfterItCase4SingleValue2OffsetCase4,
         *      LTC-00493-IT-insertAfterItCase4SingleValue3OffsetCase1,
         *      LTC-00494-IT-insertAfterItCase4SingleValue3OffsetCase2,
         *      LTC-00495-IT-insertAfterItCase4SingleValue3OffsetCase3,
         *      LTC-00496-IT-insertAfterItCase4SingleValue3OffsetCase4
         * }
         * @public
         */
        using ConstIteratorRelativeInsertionClient :: emplaceAfter;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using IndexedOperationsClient :: sub;

    public: /* NOLINT(readability-redundant-access-specifiers) */
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

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using IndexedOperationsClient :: removeAt;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using ReplaceClient :: replace;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using ReplaceClient :: replaceFirst;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using ReplaceClient :: replaceLast;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using ReplaceClient :: replaceAll;


    public: /* NOLINT(readability-redundant-access-specifiers) */
        using ReplaceOfCollectionClient :: replaceOf;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using ReplaceOfCollectionClient :: replaceFirstOf;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using ReplaceOfCollectionClient :: replaceLastOf;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using ReplaceOfCollectionClient :: replaceAllOf;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using ReplaceOfCollectionClient :: replaceNotOf;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using ReplaceOfCollectionClient :: replaceFirstNotOf;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using ReplaceOfCollectionClient :: replaceLastNotOf;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using ReplaceOfCollectionClient :: replaceAllNotOf;


    public: /* NOLINT(readability-redundant-access-specifiers) */
        using ReplaceOfInitializerListClient :: replaceOf;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using ReplaceOfInitializerListClient :: replaceFirstOf;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using ReplaceOfInitializerListClient :: replaceLastOf;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using ReplaceOfInitializerListClient :: replaceAllOf;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using ReplaceOfInitializerListClient :: replaceNotOf;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using ReplaceOfInitializerListClient :: replaceFirstNotOf;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using ReplaceOfInitializerListClient :: replaceLastNotOf;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using ReplaceOfInitializerListClient :: replaceAllNotOf;


    public: /* NOLINT(readability-redundant-access-specifiers) */
        using ReplaceByClient :: replaceThat;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using ReplaceByClient :: replaceFirstThat;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using ReplaceByClient :: replaceLastThat;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using ReplaceByClient :: replaceAllThat;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using ReplaceByClient :: replaceThatBy;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using ReplaceByClient :: replaceFirstThatBy;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using ReplaceByClient :: replaceLastThatBy;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using ReplaceByClient :: replaceAllThatBy;


    public: /* NOLINT(readability-redundant-access-specifiers) */
        using IndicesClient :: indicesOf;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using IndicesClient :: firstIndexOf;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using IndicesClient :: lastIndexOf;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using IndicesClient :: allIndicesOf;


    public: /* NOLINT(readability-redundant-access-specifiers) */
        using IndicesOfCollectionClient :: indicesOfFrom;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using IndicesOfCollectionClient :: firstIndexOfFrom;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using IndicesOfCollectionClient :: lastIndexOfFrom;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using IndicesOfCollectionClient :: allIndicesOfFrom;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using IndicesOfCollectionClient :: indicesOfNotFrom;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using IndicesOfCollectionClient :: firstIndexOfNotFrom;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using IndicesOfCollectionClient :: lastIndexOfNotFrom;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using IndicesOfCollectionClient :: allIndicesOfNotFrom;


    public: /* NOLINT(readability-redundant-access-specifiers) */
        using IndicesOfInitializerListClient :: indicesOfFrom;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using IndicesOfInitializerListClient :: firstIndexOfFrom;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using IndicesOfInitializerListClient :: lastIndexOfFrom;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using IndicesOfInitializerListClient :: allIndicesOfFrom;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using IndicesOfInitializerListClient :: indicesOfNotFrom;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using IndicesOfInitializerListClient :: firstIndexOfNotFrom;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using IndicesOfInitializerListClient :: lastIndexOfNotFrom;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using IndicesOfInitializerListClient :: allIndicesOfNotFrom;


    public: /* NOLINT(readability-redundant-access-specifiers) */
        using IndicesByClient :: indicesOfThat;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using IndicesByClient :: firstIndexOfThat;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using IndicesByClient :: lastIndexOfThat;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using IndicesByClient :: allIndicesOfThat;


    public: /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @brief String conversion function, used to obtain String representation of the List
         * @exceptsafe
         * @return String = string representation
         * @test Suite: LTS-00001, Group: LTG-00100-MF, Test Cases: { LTC-00101-MF-toString }
         * @public
         */
        __CDS_NoDiscard auto toString () const noexcept -> String override;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @brief Function used to clear the list, removing all elements from it
         * @exceptsafe
         * @test Suite: LTS-00001, Group: LTG-00100-MF, Test Cases: { LTC-00102-MF-clear }
         * @public
         */
        auto clear () noexcept -> void override = 0;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @brief Function used to remove the first element from the list, if any is present.
         * @exceptsafe
         * @test Suite: LTS-00001, Group: LTG-00100-MF, Test Cases: { LTC-00104-MF-popFront }
         * @public
         */
        virtual auto popFront () noexcept -> void = 0;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @brief Function used to remove the last element from the list, if any is present.
         * @exceptsafe
         * @test Suite: LTS-00001, Group: LTG-00100-MF, Test Cases: { LTC-00106-MF-popBack }
         * @public
         */
        virtual auto popBack () noexcept -> void = 0;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @brief Function used to peek at the front of the list, acquiring a mutable reference to the first enclosed element
         * @throws cds::OutOfBoundsException if list is empty
         * @return __ElementType ref = Mutable Reference to the first element
         * @test Suite: LTS-00001, Group: LTG-00100-MF, Test Cases: { LTC-00103-MF-front, LTC-00110-MF-frontThrow }
         * @public
         */
        __CDS_NoDiscard __CDS_cpplang_VirtualConstexpr virtual auto front () noexcept (false) -> ElementType & = 0;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @brief Function used to peek at the front of the list, acquiring an immutable reference to the first enclosed element
         * @throws cds::OutOfBoundsException if list is empty
         * @return __ElementType cref = Immutable Reference to the first element
         * @test Suite: LTS-00001, Group: LTG-00100-MF, Test Cases: { LTC-00103-MF-front, LTC-00110-MF-frontThrow }
         * @public
         */
        __CDS_NoDiscard __CDS_cpplang_VirtualConstexpr virtual auto front () const noexcept (false) -> ElementType const & = 0;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @brief Function used to peek at the back of the list, acquiring a mutable reference to the last enclosed element
         * @throws cds::OutOfBoundsException if list is empty
         * @return __ElementType ref = Mutable Reference to the last element
         * @test Suite: LTS-00001, Group: LTG-00100-MF, Test Cases: { LTC-00105-MF-back, LTC-00111-MF-backThrow }
         * @public
         */
        __CDS_NoDiscard __CDS_cpplang_VirtualConstexpr virtual auto back () noexcept (false) -> ElementType & = 0;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @brief Function used to peek at the last of the list, acquiring an immutable reference to the last enclosed element
         * @throws cds::OutOfBoundsException if list is empty
         * @return __ElementType cref = Immutable Reference to the last element
         * @test Suite: LTS-00001, Group: LTG-00100-MF, Test Cases: { LTC-00105-MF-back, LTC-00111-MF-backThrow }
         * @public
         */
        __CDS_NoDiscard __CDS_cpplang_VirtualConstexpr virtual auto back () const noexcept (false) -> ElementType const & = 0;

    public: /* NOLINT(readability-redundant-access-specifiers) */
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

    public: /* NOLINT(readability-redundant-access-specifiers) */
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

    public: /* NOLINT(readability-redundant-access-specifiers) */
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

    public: /* NOLINT(readability-redundant-access-specifiers) */
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

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
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

} /* namespace cds */

#include "../../../shared/delegateIterator/impl/BidirectionalDelegateWrapperIterator.hpp"

#include "../../../shared/collectionInternalCommunication/client/primitive/impl/DelegateBackwardIterablePrimitiveClient.hpp"            /* NOLINT(llvm-include-order) */
#include "../../../shared/collectionInternalCommunication/client/primitive/impl/DelegateBackwardConstIterablePrimitiveClient.hpp"
#include "../../../shared/collectionInternalCommunication/client/primitive/impl/IteratorRelativeInsertionPrimitiveClient.hpp"
#include "../../../shared/collectionInternalCommunication/client/primitive/impl/ConstIteratorRelativeInsertionPrimitiveClient.hpp"
#include "../../../shared/collectionInternalCommunication/client/primitive/impl/BoundaryInsertionPrimitiveClient.hpp"
#include "../../../shared/collectionInternalCommunication/client/primitive/impl/IndexedOperationsPrimitiveClient.hpp"

#include "../../../shared/collectionInternalCommunication/client/composite/impl/ReplaceCompositeClient.hpp"                             /* NOLINT(llvm-include-order) */
#include "../../../shared/collectionInternalCommunication/client/composite/impl/ReplaceOfCompositeClient.hpp"
#include "../../../shared/collectionInternalCommunication/client/composite/impl/ReplaceByCompositeClient.hpp"
#include "../../../shared/collectionInternalCommunication/client/composite/impl/IndicesCompositeClient.hpp"
#include "../../../shared/collectionInternalCommunication/client/composite/impl/IndicesOfCompositeClient.hpp"
#include "../../../shared/collectionInternalCommunication/client/composite/impl/IndicesByCompositeClient.hpp"

#include "list/impl/List.hpp"

#endif /* __CDS_LIST_HPP__ */
