/*
 * Created by loghin on 6/30/22.
 */

#ifndef __CDS_EX_SHARED_INDICES_OF_COMPOSITE_CLIENT_HPP__
#define __CDS_EX_SHARED_INDICES_OF_COMPOSITE_CLIENT_HPP__ /* NOLINT(bugprone-reserved-identifier) */

#warning No longer an experimental feature. Use the non-experimental header.
#include "../../../../../../shared/collectionInternalCommunication/client/composite/IndicesOfCompositeClient.hpp"

namespace cds {                 /* NOLINT(modernize-concat-nested-namespaces) */
    namespace experimental {    /* NOLINT(modernize-concat-nested-namespaces) */
        namespace __hidden {    /* NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier) */
            namespace __impl {  /* NOLINT(bugprone-reserved-identifier) */

                template <
                        typename                                                                                __ReceiverType,         /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                                                __ElementType,          /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                                                __FromCollectionType,   /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __ContainsFunction < __FromCollectionType, __ElementType > __contains              /* NOLINT(bugprone-reserved-identifier) */
                > using __IndicesOfCompositeClient __CDS_DeprecatedHint("No longer an experimental feature.") =                         /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __IndicesOfCompositeClient < __ReceiverType, __ElementType, __FromCollectionType, __contains >;

                template <
                        typename                                                                                __ReceiverType,         /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                                                __ElementType,          /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                                                __FromCollectionType,   /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __ContainsFunction < __FromCollectionType, __ElementType > __contains              /* NOLINT(bugprone-reserved-identifier) */
                > using __LocalIndicesOfCompositeClient __CDS_DeprecatedHint("No longer an experimental feature.") =                    /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __LocalIndicesOfCompositeClient < __ReceiverType, __ElementType, __FromCollectionType, __contains >;

            }
        }
    }
}

#endif /* __CDS_EX_SHARED_INDICES_OF_COMPOSITE_CLIENT_HPP__ */
