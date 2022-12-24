/*
 * Created by loghin on 09/08/22.
 */

#ifndef __CDS_EX_SHARED_DELEGATE_FIND_UNIQUE_MUTABLE_PRIMITIVE_CLIENT_HPP__
#define __CDS_EX_SHARED_DELEGATE_FIND_UNIQUE_MUTABLE_PRIMITIVE_CLIENT_HPP__ /* NOLINT(bugprone-reserved-identifier) */

#warning No longer an experimental feature. Use the non-experimental header.
#include "../../../../../../shared/iterableInternalCommunication/client/primitive/FindUniqueMutablePrimitiveClient.hpp"

namespace cds {                 /* NOLINT(modernize-concat-nested-namespaces) */
    namespace experimental {    /* NOLINT(modernize-concat-nested-namespaces) */
        namespace __hidden {    /* NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier) */
            namespace __impl {  /* NOLINT(bugprone-reserved-identifier) */

                template <
                        typename __ReceiverType,                                                                        /* NOLINT(bugprone-reserved-identifier) */
                        typename __ElementType,                                                                         /* NOLINT(bugprone-reserved-identifier) */
                        typename __KeyType,                                                                             /* NOLINT(bugprone-reserved-identifier) */
                        bool     __bidirectional                                                                        /* NOLINT(bugprone-reserved-identifier) */
                > using __FindUniqueMutablePrimitiveClient __CDS_DeprecatedHint("No longer an experimental feature.") = /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __FindUniqueMutablePrimitiveClient < __ReceiverType, __ElementType, __KeyType, __bidirectional >;


                template <
                        typename __ReceiverType,                                                                                /* NOLINT(bugprone-reserved-identifier) */
                        typename __KeyType,                                                                                     /* NOLINT(bugprone-reserved-identifier) */
                        typename __IteratorType                                                                                 /* NOLINT(bugprone-reserved-identifier) */
                > using __LocalFindUniqueMutablePrimitiveClient __CDS_DeprecatedHint("No longer an experimental feature.") =    /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __LocalFindUniqueMutablePrimitiveClient < __ReceiverType, __KeyType, __IteratorType >;

            }
        }
    }
}

#endif /* __CDS_EX_SHARED_DELEGATE_FIND_UNIQUE_MUTABLE_PRIMITIVE_CLIENT_HPP__ */
