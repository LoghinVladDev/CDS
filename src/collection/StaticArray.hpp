/* NOLINT(llvm-header-guard)
 * Created by loghin on 16/02/23.
 */

#ifndef __CDS_STATIC_ARRAY_HPP__ /* NOLINT(llvm-header-guard) */
#define __CDS_STATIC_ARRAY_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

#include <CDS/Iterable>
#include <CDS/Function>
#include <CDS/meta/TypeTraits>

#include "../shared/iterator/AddressIterator.hpp"
#include "../shared/iterator/IteratorSort.hpp"

#include "../shared/iterableInternalCommunication/client/composite/ReplaceCompositeClient.hpp" /* NOLINT(llvm-include-order) */
#include "../shared/iterableInternalCommunication/client/composite/ReplaceOfCompositeClient.hpp"
#include "../shared/iterableInternalCommunication/client/composite/ReplaceByCompositeClient.hpp"

#include "../shared/iterableInternalCommunication/client/primitive/IndexedOperationsPrimitiveClient.hpp"

#include "../shared/iterableInternalCommunication/client/composite/IndicesCompositeClient.hpp"  /* NOLINT(llvm-include-order) */
#include "../shared/iterableInternalCommunication/client/composite/IndicesOfCompositeClient.hpp"
#include "../shared/iterableInternalCommunication/client/composite/IndicesByCompositeClient.hpp"

#include "../shared/iterableInternalCommunication/server/IterableServer.hpp"
#include "../shared/iterableInternalCommunication/server/IterableServerDispatcher.hpp"

#include "../shared/array/StaticArrayBase.hpp"

#include "staticArray/Constructs.hpp"

namespace cds {

    template < typename __ElementType, Size __size >    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    class __CDS_InheritsEBOs StaticArray :
            public Iterable < __ElementType >,
            protected __hidden :: __impl :: __StaticArrayServer < __ElementType, __size >,
            public __hidden :: __impl :: __StaticArrayImplementation < __ElementType, __size >,
            public __hidden :: __impl :: __StaticArrayDispatcher < __ElementType, __size >,
            public __hidden :: __impl :: __StaticArrayFindOfIterableClient < __ElementType, __size >,
            public __hidden :: __impl :: __StaticArrayFindOfInitializerListClient < __ElementType, __size >,
            public __hidden :: __impl :: __StaticArrayConstFindOfIterableClient < __ElementType, __size >,
            public __hidden :: __impl :: __StaticArrayConstFindOfInitializerListClient < __ElementType, __size >,
            public __hidden :: __impl :: __StaticArrayFindByClient < __ElementType, __size >,
            public __hidden :: __impl :: __StaticArrayConstFindByClient < __ElementType, __size >,
            public __hidden :: __impl :: __StaticArrayGenericStatementsClient < __ElementType, __size >,
            public __hidden :: __impl :: __StaticArrayGenericConstStatementsClient < __ElementType, __size >,
            public __hidden :: __impl :: __StaticArrayReplaceClient < __ElementType, __size >,
            public __hidden :: __impl :: __StaticArrayReplaceOfIterableClient < __ElementType, __size >,
            public __hidden :: __impl :: __StaticArrayReplaceOfInitializerListClient < __ElementType, __size >,
            public __hidden :: __impl :: __StaticArrayReplaceByClient < __ElementType, __size >,
            public __hidden :: __impl :: __StaticArrayIndexedOperationsClient < __ElementType, __size >,
            public __hidden :: __impl :: __StaticArrayIndicesClient < __ElementType, __size >,
            public __hidden :: __impl :: __StaticArrayIndicesOfIterableClient < __ElementType, __size >,
            public __hidden :: __impl :: __StaticArrayIndicesOfInitializerListClient < __ElementType, __size >,
            public __hidden :: __impl :: __StaticArrayIndicesByClient < __ElementType, __size >,
            public __hidden :: __impl :: __StaticArrayContainsOfIterableClient < __ElementType, __size >,
            public __hidden :: __impl :: __StaticArrayContainsOfInitializerListClient < __ElementType, __size >,
            public __hidden :: __impl :: __StaticArrayDelegateForwardIterableClient < __ElementType, __size >,
            public __hidden :: __impl :: __StaticArrayDelegateForwardConstIterableClient < __ElementType, __size >,
            public __hidden :: __impl :: __StaticArrayDelegateBackwardIterableClient < __ElementType, __size >,
            public __hidden :: __impl :: __StaticArrayDelegateBackwardConstIterableClient < __ElementType, __size > {

        static_assert (
                cds :: meta :: isDefaultConstructible < __ElementType > (),
                "Requires Default-Constructible Element Type"
        );

    private:                                            /* NOLINT(readability-redundant-access-specifiers) */
        friend __hidden :: __impl :: __IterableServer < /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                StaticArray < __ElementType, __size >,
                __ElementType
        >;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using Implementation                        = __hidden :: __impl :: __StaticArrayImplementation < __ElementType, __size >;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using Server                                = __hidden :: __impl :: __StaticArrayServer < __ElementType, __size >;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using FindOfIterableClient                  = __hidden :: __impl :: __StaticArrayFindOfIterableClient < __ElementType, __size >;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using FindOfInitializerListClient           = __hidden :: __impl :: __StaticArrayFindOfInitializerListClient < __ElementType, __size >;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using FindConstOfIterableClient             = __hidden :: __impl :: __StaticArrayConstFindOfIterableClient < __ElementType, __size >;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using FindConstOfInitializerListClient      = __hidden :: __impl :: __StaticArrayConstFindOfInitializerListClient < __ElementType, __size >;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using FindByClient                          = __hidden :: __impl :: __StaticArrayFindByClient < __ElementType, __size >;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using FindConstByClient                     = __hidden :: __impl :: __StaticArrayConstFindByClient < __ElementType, __size >;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using GenericStatementsClient               = __hidden :: __impl :: __StaticArrayGenericStatementsClient < __ElementType, __size >;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using GenericConstStatementsClient          = __hidden :: __impl :: __StaticArrayGenericConstStatementsClient < __ElementType, __size >;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using ReplaceClient                         = __hidden :: __impl :: __StaticArrayReplaceClient < __ElementType, __size >;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using ReplaceOfIterableClient               = __hidden :: __impl :: __StaticArrayReplaceOfIterableClient < __ElementType, __size >;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using ReplaceOfInitializerListClient        = __hidden :: __impl :: __StaticArrayReplaceOfInitializerListClient < __ElementType, __size >;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using ReplaceByClient                       = __hidden :: __impl :: __StaticArrayReplaceByClient < __ElementType, __size >;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using ContainsOfIterableClient              = __hidden :: __impl :: __StaticArrayContainsOfIterableClient < __ElementType, __size >;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using ContainsOfInitializerListClient       = __hidden :: __impl :: __StaticArrayContainsOfInitializerListClient < __ElementType, __size >;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using IndexedOperationsClient               = __hidden :: __impl :: __StaticArrayIndexedOperationsClient < __ElementType, __size >;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using IndicesClient                         = __hidden :: __impl :: __StaticArrayIndicesClient < __ElementType, __size >;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using IndicesOfIterableClient               = __hidden :: __impl :: __StaticArrayIndicesOfIterableClient < __ElementType, __size >;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using IndicesOfInitializerListClient        = __hidden :: __impl :: __StaticArrayIndicesOfInitializerListClient < __ElementType, __size >;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using IndicesByClient                       = __hidden :: __impl :: __StaticArrayIndicesByClient < __ElementType, __size >;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using DelegateForwardIterableClient         = __hidden :: __impl :: __StaticArrayDelegateForwardIterableClient < __ElementType, __size >;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using DelegateForwardConstIterableClient    = __hidden :: __impl :: __StaticArrayDelegateForwardConstIterableClient < __ElementType, __size >;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using DelegateBackwardIterableClient        = __hidden :: __impl :: __StaticArrayDelegateBackwardIterableClient < __ElementType, __size >;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using DelegateBackwardConstIterableClient   = __hidden :: __impl :: __StaticArrayDelegateBackwardConstIterableClient < __ElementType, __size >;


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

    public:
        using ElementType   = __ElementType;

    protected:
        using IterableBase = Iterable < __ElementType >;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using typename IterableBase :: __GenericHandler;        /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using typename IterableBase :: __GenericConstHandler;   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */


    public: /* NOLINT(readability-redundant-access-specifiers) */
        using typename DelegateForwardIterableClient :: Iterator;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using typename DelegateForwardConstIterableClient :: ConstIterator;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using typename DelegateBackwardIterableClient :: ReverseIterator;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using typename DelegateBackwardConstIterableClient :: ConstReverseIterator;

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
        using FindOfIterableClient :: findOf;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using FindOfIterableClient :: findFirstOf;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using FindOfIterableClient :: findLastOf;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using FindOfIterableClient :: findAllOf;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using FindOfIterableClient :: findNotOf;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using FindOfIterableClient :: findFirstNotOf;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using FindOfIterableClient :: findLastNotOf;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using FindOfIterableClient :: findAllNotOf;


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
        using FindConstOfIterableClient :: findOf;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using FindConstOfIterableClient :: findFirstOf;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using FindConstOfIterableClient :: findLastOf;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using FindConstOfIterableClient :: findAllOf;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using FindConstOfIterableClient :: findNotOf;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using FindConstOfIterableClient :: findFirstNotOf;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using FindConstOfIterableClient :: findLastNotOf;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using FindConstOfIterableClient :: findAllNotOf;


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
        using ReplaceOfIterableClient :: replaceOf;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using ReplaceOfIterableClient :: replaceFirstOf;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using ReplaceOfIterableClient :: replaceLastOf;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using ReplaceOfIterableClient :: replaceAllOf;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using ReplaceOfIterableClient :: replaceNotOf;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using ReplaceOfIterableClient :: replaceFirstNotOf;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using ReplaceOfIterableClient :: replaceLastNotOf;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using ReplaceOfIterableClient :: replaceAllNotOf;


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
        using IndicesOfIterableClient :: indicesOfFrom;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using IndicesOfIterableClient :: firstIndexOfFrom;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using IndicesOfIterableClient :: lastIndexOfFrom;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using IndicesOfIterableClient :: allIndicesOfFrom;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using IndicesOfIterableClient :: indicesOfNotFrom;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using IndicesOfIterableClient :: firstIndexOfNotFrom;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using IndicesOfIterableClient :: lastIndexOfNotFrom;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using IndicesOfIterableClient :: allIndicesOfNotFrom;


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
        using ContainsOfIterableClient :: containsAnyOf;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using ContainsOfIterableClient :: containsAnyNotOf;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using ContainsOfIterableClient :: containsAllOf;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using ContainsOfIterableClient :: containsNoneOf;


    public: /* NOLINT(readability-redundant-access-specifiers) */
        using ContainsOfInitializerListClient :: containsAnyOf;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using ContainsOfInitializerListClient :: containsAnyNotOf;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using ContainsOfInitializerListClient :: containsAllOf;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using ContainsOfInitializerListClient :: containsNoneOf;


    private:    /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto __iicch_obtainGenericHandler ( /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                __hidden :: __impl :: __IterableInternalRequest requestType
        ) noexcept -> __GenericHandler override;

    private:    /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto __iicch_obtainGenericConstHandler ( /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                __hidden :: __impl :: __IterableInternalRequest requestType
        ) const noexcept -> __GenericConstHandler override;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        constexpr StaticArray () noexcept = default;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        constexpr StaticArray (
                StaticArray const &
        ) noexcept = default;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        constexpr StaticArray (
                StaticArray &&
        ) noexcept = default;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_cpplang_ConstexprConstructorNonEmptyBody StaticArray (
                std :: initializer_list < __ElementType > const & initializerList
        ) noexcept;

    public:                                     /* NOLINT(readability-redundant-access-specifiers) */
        template < typename __IterableType >    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        __CDS_Explicit __CDS_cpplang_ConstexprConstructorNonEmptyBody StaticArray (
                __IterableType const & iterable
        ) noexcept;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        constexpr ~StaticArray () noexcept override = default;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_cpplang_NonConstConstexprMemberFunction auto operator = (
                StaticArray const &
        ) noexcept -> StaticArray & = default;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_cpplang_NonConstConstexprMemberFunction auto operator = (
                StaticArray &&
        ) noexcept -> StaticArray & = default;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_cpplang_NonConstConstexprMemberFunction auto operator = (
                std :: initializer_list < __ElementType > const & initializerList
        ) noexcept -> StaticArray &;

    public:                                     /* NOLINT(readability-redundant-access-specifiers) */
        template < typename __IterableType >    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        __CDS_cpplang_NonConstConstexprMemberFunction auto operator = (
                __IterableType const & iterable
        ) noexcept -> StaticArray &;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto operator == (
                StaticArray const & array
        ) const noexcept -> bool;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto operator != (
                StaticArray const & array
        ) const noexcept -> bool;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard constexpr auto size () const noexcept -> Size;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction auto front () noexcept (false) -> __ElementType &;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction auto back () noexcept (false) -> __ElementType &;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard constexpr auto front () const noexcept (false) -> __ElementType const &;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard constexpr auto back () const noexcept (false) -> __ElementType const &;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto get (
                Index index
        ) noexcept (false) -> __ElementType &;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto get (
                Index index
        ) const noexcept (false) -> __ElementType const &;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction auto data () noexcept -> __ElementType *;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard constexpr auto data () const noexcept -> __ElementType const *;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        template <
                typename __Comparator = decltype ( & cds :: predicates :: lessThan < __ElementType > )  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        > auto sort (
                __Comparator const & comparator = & cds :: predicates :: lessThan < __ElementType >
        ) noexcept -> void;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard auto sequence () & noexcept -> Sequence < StaticArray < __ElementType, __size > >;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard auto sequence () && noexcept -> Sequence < StaticArray < __ElementType, __size > >;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard auto sequence () const & noexcept -> Sequence < StaticArray < __ElementType, __size > const >;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard auto sequence () const && noexcept -> Sequence < StaticArray < __ElementType, __size > const >;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto operator [] (
                Index index
        ) const noexcept (false) -> ElementType const &;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto operator [] (
                Index index
        ) noexcept (false) -> ElementType &;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard auto toString () const noexcept(false) -> String override;

    private:  /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto circularAdjustedIndex (
                Index index
        ) const noexcept -> Index;
    };

} /* namespace cds */

#include "../shared/iterator/impl/AddressIterator.hpp"

#include "../shared/iterableInternalCommunication/client/composite/impl/ReplaceCompositeClient.hpp" /* NOLINT(llvm-include-order) */
#include "../shared/iterableInternalCommunication/client/composite/impl/ReplaceOfCompositeClient.hpp"
#include "../shared/iterableInternalCommunication/client/composite/impl/ReplaceByCompositeClient.hpp"

#include "../shared/iterableInternalCommunication/client/primitive/impl/IndexedOperationsPrimitiveClientImpl.hpp"

#include "../shared/iterableInternalCommunication/client/composite/impl/IndicesCompositeClient.hpp"  /* NOLINT(llvm-include-order) */
#include "../shared/iterableInternalCommunication/client/composite/impl/IndicesOfCompositeClient.hpp"
#include "../shared/iterableInternalCommunication/client/composite/impl/IndicesByCompositeClient.hpp"

#include "../shared/iterableInternalCommunication/server/impl/IterableServerImpl.hpp"
#include "../shared/iterableInternalCommunication/server/impl/IterableServerDispatcherImpl.hpp"

#include "../shared/array/impl/StaticArrayBaseImpl.hpp"

#include "staticArray/impl/StaticArray.hpp"

#endif /* __CDS_STATIC_ARRAY_HPP__ */
