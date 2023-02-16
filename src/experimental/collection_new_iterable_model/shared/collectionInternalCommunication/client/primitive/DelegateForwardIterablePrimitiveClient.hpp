/*
 * Created by loghin on 6/26/22.
 */

#ifndef __CDS_EX_SHARED_DELEGATE_FORWARD_ITERABLE_PRIMITIVE_CLIENT_HPP__
#define __CDS_EX_SHARED_DELEGATE_FORWARD_ITERABLE_PRIMITIVE_CLIENT_HPP__ /* NOLINT(bugprone-reserved-identifier) */

#warning No longer an experimental feature. Use the non-experimental header.
#include "../../../../../../shared/iterableInternalCommunication/client/primitive/DelegateForwardIterablePrimitiveClient.hpp"

namespace cds {                 /* NOLINT(modernize-concat-nested-namespaces) */
    namespace experimental {    /* NOLINT(modernize-concat-nested-namespaces) */
        namespace __hidden {    /* NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier) */
            namespace __impl {  /* NOLINT(bugprone-reserved-identifier) */

                template <
                        typename __ReceiverType,                                                                                /* NOLINT(bugprone-reserved-identifier) */
                        typename __ElementType,                                                                                 /* NOLINT(bugprone-reserved-identifier) */
                        bool     __bidirectional                                                                                /* NOLINT(bugprone-reserved-identifier) */
                > using __DelegateForwardIterablePrimitiveClient __CDS_DeprecatedHint("No longer an experimental feature.") =   /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __DelegateForwardIterablePrimitiveClient < __ReceiverType, __ElementType, __bidirectional >;


                template <
                        typename __ReceiverType,                                                                                    /* NOLINT(bugprone-reserved-identifier) */
                        typename __IteratorType                                                                                     /* NOLINT(bugprone-reserved-identifier) */
                > using __LocalDelegateForwardIterablePrimitiveClient __CDS_DeprecatedHint("No longer an experimental feature.") =  /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __LocalDelegateForwardIterablePrimitiveClient < __ReceiverType, __IteratorType >;

            }
        }
    }
}

#endif /* __CDS_EX_SHARED_DELEGATE_FORWARD_ITERABLE_PRIMITIVE_CLIENT_HPP__ */
