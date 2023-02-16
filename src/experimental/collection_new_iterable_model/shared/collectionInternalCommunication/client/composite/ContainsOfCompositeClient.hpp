/*
 * Created by loghin on 6/26/22.
 */

#ifndef __CDS_EX_SHARED_CONTAINS_OF_COMPOSITE_CLIENT_HPP__
#define __CDS_EX_SHARED_CONTAINS_OF_COMPOSITE_CLIENT_HPP__ /* NOLINT(bugprone-reserved-identifier) */

#warning No longer an experimental feature. Use the non-experimental header.
#include "../../../../../../shared/iterableInternalCommunication/client/composite/ContainsOfCompositeClient.hpp"

namespace cds {                 /* NOLINT(modernize-concat-nested-namespaces) */
    namespace experimental {    /* NOLINT(modernize-concat-nested-namespaces) */
        namespace __hidden {    /* NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier) */
            namespace __impl {  /* NOLINT(bugprone-reserved-identifier) */

                template <
                        typename                                                                                __ReceiverType,     /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                                                __ElementType,      /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                                                __FromIterableType, /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __ContainsFunction < __FromIterableType, __ElementType >   __contains          /* NOLINT(bugprone-reserved-identifier) */
                > using __ContainsOfCompositeClient __CDS_DeprecatedHint("No longer an experimental feature.") =                    /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __ContainsOfCompositeClient < __ReceiverType, __ElementType, __FromIterableType, __contains >;


                template <
                        typename                                                                                __ReceiverType,     /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                                                __ElementType,      /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                                                __FromIterableType, /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __ContainsFunction < __FromIterableType, __ElementType >   __contains          /* NOLINT(bugprone-reserved-identifier) */
                > using __LocalContainsOfCompositeClient __CDS_DeprecatedHint("No longer an experimental feature.") =               /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __LocalContainsOfCompositeClient < __ReceiverType, __ElementType, __FromIterableType, __contains >;

            }
        }
    }
}

#endif /* __CDS_EX_SHARED_CONTAINS_OF_COMPOSITE_CLIENT_HPP__ */
