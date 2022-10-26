/*
 * Created by loghin on 01.03.2021.
 */

#ifndef __CDS_ARRAY_HPP__ /* NOLINT(llvm-header-guard) */
#define __CDS_ARRAY_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

#include <CDS/List>

#include "array/Predeclaration.hpp"

#include "../../../../shared/iterator/IteratorSort.hpp"                                         /* NOLINT(llvm-include-order) */
#include "../../../../shared/iterator/AddressIterator.hpp"

#include "../../../../shared/collectionInternalCommunication/server/ListServerDispatcher.hpp"

#include "../../../../shared/array/ArrayBase.hpp"

#include "../../../../shared/delegateIterator/AbstractDelegateIterator.hpp"
#include "../../../../shared/delegateIterator/DelegateIterator.hpp"

#include "../../../../shared/collectionInternalCommunication/server/ListServer.hpp"

#include "array/Constructs.hpp"

namespace cds {

    template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
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

    private:    /* NOLINT(readability-redundant-access-specifiers) */
        friend __hidden :: __impl :: __ListServer < Array < __ElementType >, __ElementType >; /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using Implementation                        = __hidden :: __impl :: __ArrayImplementation < __ElementType >;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using Server                                = __hidden :: __impl :: __ArrayServer < __ElementType >;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using RandomInsertionClient                 = __hidden :: __impl :: __ArrayRandomInsertionClient < __ElementType >;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using BoundaryInsertionClient               = __hidden :: __impl :: __ArrayBoundaryInsertionClient < __ElementType >;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using IteratorRelativeInsertionClient       = __hidden :: __impl :: __ArrayIteratorRelativeInsertionClient < __ElementType >;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using ConstIteratorRelativeInsertionClient  = __hidden :: __impl :: __ArrayConstIteratorRelativeInsertionClient < __ElementType >;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using FindOfCollectionClient                = __hidden :: __impl :: __ArrayFindOfCollectionClient < __ElementType >;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using FindOfInitializerListClient           = __hidden :: __impl :: __ArrayFindOfInitializerListClient < __ElementType >;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using FindConstOfCollectionClient           = __hidden :: __impl :: __ArrayFindConstOfCollectionClient < __ElementType >;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using FindConstOfInitializerListClient      = __hidden :: __impl :: __ArrayFindConstOfInitializerListClient < __ElementType >;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using FindByClient                          = __hidden :: __impl :: __ArrayFindByClient < __ElementType >;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using FindConstByClient                     = __hidden :: __impl :: __ArrayFindConstByClient < __ElementType >;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using IteratorRemoveClient                  = __hidden :: __impl :: __ArrayIteratorRemoveClient < __ElementType >;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using ConstIteratorRemoveClient             = __hidden :: __impl :: __ArrayConstIteratorRemoveClient < __ElementType >;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using RemoveOfCollectionClient              = __hidden :: __impl :: __ArrayRemoveOfCollectionClient < __ElementType >;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using RemoveOfInitializerListClient         = __hidden :: __impl :: __ArrayRemoveOfInitializerListClient < __ElementType >;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using RemoveByClient                        = __hidden :: __impl :: __ArrayRemoveByClient < __ElementType >;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using GenericStatementsClient               = __hidden :: __impl :: __ArrayGenericStatementsClient < __ElementType >;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using GenericConstStatementsClient          = __hidden :: __impl :: __ArrayGenericConstStatementsClient < __ElementType >;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using ReplaceClient                         = __hidden :: __impl :: __ArrayReplaceClient < __ElementType >;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using ReplaceOfCollectionClient             = __hidden :: __impl :: __ArrayReplaceOfCollectionClient < __ElementType >;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using ReplaceOfInitializerListClient        = __hidden :: __impl :: __ArrayReplaceOfInitializerListClient < __ElementType >;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using ReplaceByClient                       = __hidden :: __impl :: __ArrayReplaceByClient < __ElementType >;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using ContainsOfCollectionClient            = __hidden :: __impl :: __ArrayContainsOfCollectionClient < __ElementType >;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using ContainsOfInitializerListClient       = __hidden :: __impl :: __ArrayContainsOfInitializerListClient < __ElementType >;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using IndexedOperationsClient               = __hidden :: __impl :: __ArrayIndexedOperationsClient < __ElementType >;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using IndicesClient                         = __hidden :: __impl :: __ArrayIndicesClient < __ElementType >;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using IndicesOfCollectionClient             = __hidden :: __impl :: __ArrayIndicesOfCollectionClient < __ElementType >;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using IndicesOfInitializerListClient        = __hidden :: __impl :: __ArrayIndicesOfInitializerListClient < __ElementType >;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using IndicesByClient                       = __hidden :: __impl :: __ArrayIndicesByClient < __ElementType >;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using DelegateForwardIterableClient         = __hidden :: __impl :: __ArrayDelegateForwardIterableClient < __ElementType >;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using DelegateForwardConstIterableClient    = __hidden :: __impl :: __ArrayDelegateForwardConstIterableClient < __ElementType >;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using DelegateBackwardIterableClient        = __hidden :: __impl :: __ArrayDelegateBackwardIterableClient < __ElementType >;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using DelegateBackwardConstIterableClient   = __hidden :: __impl :: __ArrayDelegateBackwardConstIterableClient < __ElementType >;


    private:    /* NOLINT(readability-redundant-access-specifiers) */
        friend BoundaryInsertionClient;

    private:    /* NOLINT(readability-redundant-access-specifiers) */
        friend RandomInsertionClient;

    private:    /* NOLINT(readability-redundant-access-specifiers) */
        friend IteratorRemoveClient;

    private:    /* NOLINT(readability-redundant-access-specifiers) */
        friend ConstIteratorRemoveClient;

    private:    /* NOLINT(readability-redundant-access-specifiers) */
        friend IteratorRelativeInsertionClient;

    private:    /* NOLINT(readability-redundant-access-specifiers) */
        friend ConstIteratorRelativeInsertionClient;

    private:    /* NOLINT(readability-redundant-access-specifiers) */
        friend IndexedOperationsClient;

    private:    /* NOLINT(readability-redundant-access-specifiers) */
        friend DelegateForwardIterableClient;

    private:    /* NOLINT(readability-redundant-access-specifiers) */
        friend DelegateForwardConstIterableClient;

    private:    /* NOLINT(readability-redundant-access-specifiers) */
        friend DelegateBackwardIterableClient;

    private:    /* NOLINT(readability-redundant-access-specifiers) */
        friend DelegateBackwardConstIterableClient;


    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using ElementType                   = __ElementType;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using ListBase                  = List < __ElementType >;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using typename ListBase :: __GenericHandler;        /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using typename ListBase :: __GenericConstHandler;   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */


    public: /* NOLINT(readability-redundant-access-specifiers) */
        using typename DelegateForwardIterableClient :: Iterator;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using typename DelegateForwardConstIterableClient :: ConstIterator;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using typename DelegateBackwardIterableClient :: ReverseIterator;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using typename DelegateBackwardConstIterableClient :: ConstReverseIterator;


    private:    /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto __cicch_obtainGenericHandler ( /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                __hidden :: __impl :: __CollectionInternalRequestType requestType
        ) noexcept -> __GenericHandler override;

    private:    /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto __cicch_obtainGenericConstHandler ( /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                __hidden :: __impl :: __CollectionInternalRequestType requestType
        ) const noexcept -> __GenericConstHandler override;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using DelegateForwardIterableClient :: begin;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using DelegateForwardIterableClient :: end;


    public: /* NOLINT(readability-redundant-access-specifiers) */
        using DelegateForwardConstIterableClient :: begin;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using DelegateForwardConstIterableClient :: end;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using DelegateForwardConstIterableClient :: cbegin;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using DelegateForwardConstIterableClient :: cend;


    public: /* NOLINT(readability-redundant-access-specifiers) */
        using DelegateBackwardIterableClient :: rbegin;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using DelegateBackwardIterableClient :: rend;


    public: /* NOLINT(readability-redundant-access-specifiers) */
        using DelegateBackwardConstIterableClient :: rbegin;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using DelegateBackwardConstIterableClient :: rend;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using DelegateBackwardConstIterableClient :: crbegin;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using DelegateBackwardConstIterableClient :: crend;


    public: /* NOLINT(readability-redundant-access-specifiers) */
        using RandomInsertionClient :: insert;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using RandomInsertionClient :: insertAll;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using RandomInsertionClient :: insertAllOf;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using RandomInsertionClient :: add;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using RandomInsertionClient :: addAll;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using RandomInsertionClient :: addAllOf;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using RandomInsertionClient :: emplace;


    public: /* NOLINT(readability-redundant-access-specifiers) */
        using BoundaryInsertionClient :: pushBack;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using BoundaryInsertionClient :: pushBackAll;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using BoundaryInsertionClient :: pushBackAllOf;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using BoundaryInsertionClient :: pushFront;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using BoundaryInsertionClient :: pushFrontAll;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using BoundaryInsertionClient :: pushFrontAllOf;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using BoundaryInsertionClient :: append;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using BoundaryInsertionClient :: prepend;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using BoundaryInsertionClient :: emplaceBack;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using BoundaryInsertionClient :: emplaceFront;


    public: /* NOLINT(readability-redundant-access-specifiers) */
        using IteratorRelativeInsertionClient :: insertBefore;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using IteratorRelativeInsertionClient :: insertAllBefore;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using IteratorRelativeInsertionClient :: insertAllOfBefore;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using IteratorRelativeInsertionClient :: emplaceBefore;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using IteratorRelativeInsertionClient :: insertAfter;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using IteratorRelativeInsertionClient :: insertAllAfter;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using IteratorRelativeInsertionClient :: insertAllOfAfter;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using IteratorRelativeInsertionClient :: emplaceAfter;


    public: /* NOLINT(readability-redundant-access-specifiers) */
        using ConstIteratorRelativeInsertionClient :: insertBefore;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using ConstIteratorRelativeInsertionClient :: insertAllBefore;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using ConstIteratorRelativeInsertionClient :: insertAllOfBefore;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using ConstIteratorRelativeInsertionClient :: emplaceBefore;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using ConstIteratorRelativeInsertionClient :: insertAfter;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using ConstIteratorRelativeInsertionClient :: insertAllAfter;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using ConstIteratorRelativeInsertionClient :: insertAllOfAfter;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using ConstIteratorRelativeInsertionClient :: emplaceAfter;


    public: /* NOLINT(readability-redundant-access-specifiers) */
        using FindOfCollectionClient :: findOf;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using FindOfCollectionClient :: findFirstOf;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using FindOfCollectionClient :: findLastOf;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using FindOfCollectionClient :: findAllOf;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using FindOfCollectionClient :: findNotOf;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using FindOfCollectionClient :: findFirstNotOf;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using FindOfCollectionClient :: findLastNotOf;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using FindOfCollectionClient :: findAllNotOf;


    public: /* NOLINT(readability-redundant-access-specifiers) */
        using FindOfInitializerListClient :: findOf;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using FindOfInitializerListClient :: findFirstOf;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using FindOfInitializerListClient :: findLastOf;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using FindOfInitializerListClient :: findAllOf;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using FindOfInitializerListClient :: findNotOf;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using FindOfInitializerListClient :: findFirstNotOf;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using FindOfInitializerListClient :: findLastNotOf;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using FindOfInitializerListClient :: findAllNotOf;


    public: /* NOLINT(readability-redundant-access-specifiers) */
        using FindConstOfCollectionClient :: findOf;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using FindConstOfCollectionClient :: findFirstOf;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using FindConstOfCollectionClient :: findLastOf;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using FindConstOfCollectionClient :: findAllOf;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using FindConstOfCollectionClient :: findNotOf;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using FindConstOfCollectionClient :: findFirstNotOf;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using FindConstOfCollectionClient :: findLastNotOf;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using FindConstOfCollectionClient :: findAllNotOf;


    public: /* NOLINT(readability-redundant-access-specifiers) */
        using FindConstOfInitializerListClient :: findOf;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using FindConstOfInitializerListClient :: findFirstOf;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using FindConstOfInitializerListClient :: findLastOf;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using FindConstOfInitializerListClient :: findAllOf;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using FindConstOfInitializerListClient :: findNotOf;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using FindConstOfInitializerListClient :: findFirstNotOf;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using FindConstOfInitializerListClient :: findLastNotOf;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using FindConstOfInitializerListClient :: findAllNotOf;


    public: /* NOLINT(readability-redundant-access-specifiers) */
        using FindByClient :: findThat;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using FindByClient :: findFirstThat;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using FindByClient :: findLastThat;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using FindByClient :: findAllThat;


    public: /* NOLINT(readability-redundant-access-specifiers) */
        using FindConstByClient :: findThat;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using FindConstByClient :: findFirstThat;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using FindConstByClient :: findLastThat;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using FindConstByClient :: findAllThat;


    public: /* NOLINT(readability-redundant-access-specifiers) */
        using RemoveOfCollectionClient :: removeOf;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using RemoveOfCollectionClient :: removeFirstOf;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using RemoveOfCollectionClient :: removeLastOf;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using RemoveOfCollectionClient :: removeAllOf;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using RemoveOfCollectionClient :: removeNotOf;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using RemoveOfCollectionClient :: removeFirstNotOf;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using RemoveOfCollectionClient :: removeLastNotOf;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using RemoveOfCollectionClient :: removeAllNotOf;


    public: /* NOLINT(readability-redundant-access-specifiers) */
        using RemoveOfInitializerListClient :: removeOf;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using RemoveOfInitializerListClient :: removeFirstOf;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using RemoveOfInitializerListClient :: removeLastOf;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using RemoveOfInitializerListClient :: removeAllOf;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using RemoveOfInitializerListClient :: removeNotOf;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using RemoveOfInitializerListClient :: removeFirstNotOf;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using RemoveOfInitializerListClient :: removeLastNotOf;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using RemoveOfInitializerListClient :: removeAllNotOf;


    public: /* NOLINT(readability-redundant-access-specifiers) */
        using RemoveByClient :: removeThat;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using RemoveByClient :: removeFirstThat;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using RemoveByClient :: removeLastThat;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using RemoveByClient :: removeAllThat;


    public: /* NOLINT(readability-redundant-access-specifiers) */
        using GenericStatementsClient :: forEach;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using GenericStatementsClient :: some;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using GenericStatementsClient :: atLeast;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using GenericStatementsClient :: atMost;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using GenericStatementsClient :: moreThan;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using GenericStatementsClient :: fewerThan;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using GenericStatementsClient :: count;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using GenericStatementsClient :: any;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using GenericStatementsClient :: all;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using GenericStatementsClient :: none;


    public: /* NOLINT(readability-redundant-access-specifiers) */
        using GenericConstStatementsClient :: forEach;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using GenericConstStatementsClient :: some;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using GenericConstStatementsClient :: atLeast;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using GenericConstStatementsClient :: atMost;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using GenericConstStatementsClient :: moreThan;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using GenericConstStatementsClient :: fewerThan;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using GenericConstStatementsClient :: count;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using GenericConstStatementsClient :: any;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using GenericConstStatementsClient :: all;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using GenericConstStatementsClient :: none;


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
        using IndexedOperationsClient :: sub;


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
        using ContainsOfCollectionClient :: containsAnyOf;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using ContainsOfCollectionClient :: containsAnyNotOf;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using ContainsOfCollectionClient :: containsAllOf;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using ContainsOfCollectionClient :: containsNoneOf;


    public: /* NOLINT(readability-redundant-access-specifiers) */
        using ContainsOfInitializerListClient :: containsAnyOf;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using ContainsOfInitializerListClient :: containsAnyNotOf;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using ContainsOfInitializerListClient :: containsAllOf;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using ContainsOfInitializerListClient :: containsNoneOf;


    public: /* NOLINT(readability-redundant-access-specifiers) */
        using IteratorRemoveClient :: remove;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using ConstIteratorRemoveClient :: remove;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using List < __ElementType > :: remove;


    public: /* NOLINT(readability-redundant-access-specifiers) */
        constexpr Array () noexcept;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        Array ( /* NOLINT(google-explicit-constructor) */
                Array const & array
        ) noexcept;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        constexpr Array (
                Array && array
        ) noexcept;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        template <
                typename __IteratorType,                    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                typename __TElementType = __ElementType,    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                cds :: meta :: EnableIf <
                        cds :: meta :: isCopyConstructible < __TElementType > ()
                > = 0
        > Array (
                __IteratorType const & begin,
                __IteratorType const & end,
                Size                   count = 0ULL
        ) noexcept;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        template <
                typename __TElementType = __ElementType, /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                cds :: meta :: EnableIf <
                        cds :: meta :: isCopyConstructible < __TElementType > ()
                > = 0
        > Array (
                std :: initializer_list < __ElementType > const & initializerList
        ) noexcept;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        template <
                typename __TElementType = __ElementType, /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                cds :: meta :: EnableIf <
                        cds :: meta :: isDefaultConstructible < __TElementType > ()
                > = 0
        > __CDS_Explicit Array (
                Size size
        ) noexcept;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        template <
                typename __TElementType = __ElementType, /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                cds :: meta :: EnableIf <
                        cds :: meta :: isCopyConstructible < __TElementType > ()
                > = 0
        > Array (
                Size                    size,
                __ElementType   const & defaultValue
        ) noexcept;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        template < typename __IterableType > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        __CDS_Explicit Array (
                __IterableType const & iterable
        ) noexcept;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        ~Array () noexcept override;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        auto operator = (
                Array const & array
        ) noexcept -> Array &;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        auto operator = (
                Array && array
        ) noexcept -> Array &;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        auto operator = (
                std :: initializer_list < __ElementType > const & initializerList
        ) noexcept -> Array &;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        template < typename __IterableType > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        auto operator = (
                __IterableType const & iterable
        ) noexcept -> Array &;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto operator == (
                Array const & array
        ) const noexcept -> bool;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto operator != (
                Array const & array
        ) const noexcept -> bool;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        auto reserve (
                Size size
        ) noexcept -> void;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        auto shrink (
                Size size
        ) noexcept -> void;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        template <
                typename __TElementType = __ElementType, /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                cds :: meta :: EnableIf <
                        cds :: meta :: isDefaultConstructible < __TElementType > ()
                > = 0
        > auto resize (
                Size size
        ) noexcept -> void;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        template <
                typename __TElementType = __ElementType, /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                cds :: meta :: EnableIf <
                        cds :: meta :: isCopyConstructible < __TElementType > ()
                > = 0
        > auto resize (
                Size                    size,
                __ElementType   const & defaultValue
        ) noexcept -> void;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        auto clear () noexcept -> void override;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto size () const noexcept -> Size override;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        auto popFront () noexcept -> void override;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        auto popBack () noexcept -> void override;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto front () noexcept (false) -> ElementType & override;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto front () const noexcept (false) -> ElementType const & override;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto back () noexcept (false) -> ElementType & override;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto back () const noexcept (false) -> ElementType const & override;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto get (
                Index index
        ) noexcept (false) -> ElementType & override;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto get (
                Index index
        ) const noexcept (false) -> ElementType const & override;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        auto removeAt (
                Index index
        ) noexcept -> bool override;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard constexpr auto data () const noexcept -> __ElementType const *;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction auto data () noexcept -> __ElementType *;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        auto sort (
                cds :: Function < auto ( __ElementType const &, __ElementType const & ) -> bool > const & comparator
        ) noexcept -> void override;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        template <
                typename __Comparator = decltype ( & cds :: predicates :: lessThan < __ElementType > )  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        > auto sort (
                __Comparator const & comparator = & cds :: predicates :: lessThan < __ElementType >
        ) noexcept -> void;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard auto sequence () & noexcept -> Sequence < Array < __ElementType > >;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard auto sequence () && noexcept -> Sequence < Array < __ElementType > >;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard auto sequence () const & noexcept -> Sequence < Array < __ElementType > const >;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard auto sequence () const && noexcept -> Sequence < Array < __ElementType > const >;
    };

} /* namespace cds */

#include "array/impl/Array.hpp"

#include "../../../../shared/array/impl/ArrayBase.hpp"

#include "../../../../shared/iterator/impl/IteratorSort.hpp"                                            /* NOLINT(llvm-include-order) */
#include "../../../../shared/iterator/impl/AddressIterator.hpp"

#include "../../../../shared/delegateIterator/impl/AbstractDelegateIterator.hpp"
#include "../../../../shared/delegateIterator/impl/DelegateIterator.hpp"

#include "../../../../shared/collectionInternalCommunication/server/impl/ListServer.hpp"
#include "../../../../shared/collectionInternalCommunication/server/impl/ListServerDispatcher.hpp"

#include "../../../../shared/array/impl/Sequence.hpp"

#include "../../../../shared/collection/FunctionalConstructors.hpp"
#include "../../../../shared/collection/impl/FunctionalConstructors.hpp"

#include "array/impl/CTAD.hpp"

#endif /* __CDS_ARRAY_HPP__ */
