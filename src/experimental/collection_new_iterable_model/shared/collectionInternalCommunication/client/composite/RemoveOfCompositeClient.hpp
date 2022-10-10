/*
 * Created by loghin on 6/26/22.
 */

#ifndef __CDS_EX_SHARED_REMOVE_OF_COMPOSITE_CLIENT_HPP__
#define __CDS_EX_SHARED_REMOVE_OF_COMPOSITE_CLIENT_HPP__ /* NOLINT(bugprone-reserved-identifier) */

#warning No longer an experimental feature. Use the non-experimental header.
#include "../../../../../../shared/collectionInternalCommunication/client/composite/RemoveOfCompositeClient.hpp"

namespace cds {                 /* NOLINT(modernize-concat-nested-namespaces) */
    namespace experimental {    /* NOLINT(modernize-concat-nested-namespaces) */
        namespace __hidden {    /* NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier) */
            namespace __impl {  /* NOLINT(bugprone-reserved-identifier) */

                template <
                        typename                                                                                __ReceiverType,     /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                                                __ElementType,      /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                                                __FromIterableType, /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __ContainsFunction < __FromIterableType, __ElementType >   __containsFunction  /* NOLINT(bugprone-reserved-identifier) */
                > using __RemoveOfCompositeClient __CDS_DeprecatedHint("No longer an experimental feature.") =                      /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __RemoveOfCompositeClient < __ReceiverType, __ElementType, __FromIterableType, __containsFunction >;


                template <
                        typename                                                                                __ReceiverType,     /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                                                __ElementType,      /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                                                __FromIterableType, /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __ContainsFunction < __FromIterableType, __ElementType >   __containsFunction  /* NOLINT(bugprone-reserved-identifier) */
                > using __LocalRemoveOfCompositeClient __CDS_DeprecatedHint("No longer an experimental feature.") =                 /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __LocalRemoveOfCompositeClient < __ReceiverType, __ElementType, __FromIterableType, __containsFunction >;

            }
        }
    }
}

#endif /* __CDS_EX_SHARED_REMOVE_OF_COMPOSITE_CLIENT_HPP__ */
