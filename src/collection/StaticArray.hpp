/*
 * Created by loghin on 16/02/23.
 */

#ifndef __CDS_STATIC_ARRAY_HPP__ /* NOLINT(llvm-header-guard) */
#define __CDS_STATIC_ARRAY_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

#include <CDS/Iterable>
#include <CDS/meta/TypeTraits>

#include "../shared/iterator/AddressIterator.hpp"

#include "../shared/iterableInternalCommunication/client/composite/ReplaceCompositeClient.hpp"
#include "../shared/iterableInternalCommunication/client/composite/ReplaceOfCompositeClient.hpp"
#include "../shared/iterableInternalCommunication/client/composite/ReplaceByCompositeClient.hpp"

#include "../shared/iterableInternalCommunication/client/primitive/IndexedOperationsPrimitiveClient.hpp"

#include "../shared/iterableInternalCommunication/client/composite/IndicesCompositeClient.hpp"
#include "../shared/iterableInternalCommunication/client/composite/IndicesOfCompositeClient.hpp"
#include "../shared/iterableInternalCommunication/client/composite/IndicesByCompositeClient.hpp"

#include "../shared/iterableInternalCommunication/server/IterableServer.hpp"
#include "../shared/iterableInternalCommunication/server/IterableServerDispatcher.hpp"

#include "../shared/array/StaticArrayBase.hpp"

#include "staticArray/Constructs.hpp"

namespace cds {

    template < typename __ElementType, Size __size >    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    class StaticArray :
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

    protected:
        using IterableBase = Iterable < __ElementType >;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using typename IterableBase :: __GenericHandler;        /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using typename IterableBase :: __GenericConstHandler;   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

    private:    /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto __iicch_obtainGenericHandler ( /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                __hidden :: __impl :: __IterableInternalRequestType requestType
        ) noexcept -> __GenericHandler override;

    private:    /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto __iicch_obtainGenericConstHandler ( /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                __hidden :: __impl :: __IterableInternalRequestType requestType
        ) const noexcept -> __GenericConstHandler override;
    };

} /* namespace cds */

#include "staticArray/impl/StaticArray.hpp"

#endif /* __CDS_STATIC_ARRAY_HPP__ */
