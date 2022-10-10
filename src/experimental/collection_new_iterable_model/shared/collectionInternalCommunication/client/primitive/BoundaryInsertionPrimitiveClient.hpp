/*
 * Created by loghin on 6/28/22.
 */

#ifndef __CDS_EX_SHARED_BOUNDARY_INSERTION_PRIMITIVE_CLIENT_HPP__
#define __CDS_EX_SHARED_BOUNDARY_INSERTION_PRIMITIVE_CLIENT_HPP__ /* NOLINT(bugprone-reserved-identifier) */

#warning No longer an experimental feature. Use the non-experimental header.
#include "../../../../../../shared/collectionInternalCommunication/client/primitive/BoundaryInsertionPrimitiveClient.hpp"

namespace cds {                 /* NOLINT(modernize-concat-nested-namespaces) */
    namespace experimental {    /* NOLINT(modernize-concat-nested-namespaces) */
        namespace __hidden {    /* NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier) */
            namespace __impl {  /* NOLINT(bugprone-reserved-identifier) */

                template <
                        typename __ReceiverType,                                                                        /* NOLINT(bugprone-reserved-identifier) */
                        typename __ElementType,                                                                         /* NOLINT(bugprone-reserved-identifier) */
                        typename __ReturnType                                                                           /* NOLINT(bugprone-reserved-identifier) */
                > using __BoundaryInsertionPrimitiveClient __CDS_DeprecatedHint("No longer an experimental feature.") = /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __BoundaryInsertionPrimitiveClient < __ReceiverType, __ElementType, __ReturnType >;


                template <
                        typename __ReceiverType,                                                                                /* NOLINT(bugprone-reserved-identifier) */
                        typename __ElementType,                                                                                 /* NOLINT(bugprone-reserved-identifier) */
                        typename __ReturnType                                                                                   /* NOLINT(bugprone-reserved-identifier) */
                > using __LocalBoundaryInsertionPrimitiveClient __CDS_DeprecatedHint("No longer an experimental feature.") =    /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __LocalBoundaryInsertionPrimitiveClient < __ReceiverType, __ElementType, __ReturnType >;

            }
        }
    }
}

#endif /* __CDS_EX_SHARED_BOUNDARY_INSERTION_PRIMITIVE_CLIENT_HPP__ */
