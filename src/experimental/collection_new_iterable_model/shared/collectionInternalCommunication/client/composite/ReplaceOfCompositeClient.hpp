/*
 * Created by loghin on 6/30/2022.
 */

#ifndef __CDS_EX_SHARED_REPLACE_OF_COMPOSITE_CLIENT_HPP__
#define __CDS_EX_SHARED_REPLACE_OF_COMPOSITE_CLIENT_HPP__ /* NOLINT(bugprone-reserved-identifier) */

#warning No longer an experimental feature. Use the non-experimental header.
#include "../../../../../../shared/iterableInternalCommunication/client/composite/ReplaceOfCompositeClient.hpp"

namespace cds {                 /* NOLINT(modernize-concat-nested-namespaces) */
    namespace experimental {    /* NOLINT(modernize-concat-nested-namespaces) */
        namespace __hidden {    /* NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier) */
            namespace __impl {  /* NOLINT(bugprone-reserved-identifier) */

                template <
                        typename                                                                                __ReceiverType,     /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                                                __ElementType,      /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                                                __OfCollectionType, /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __ContainsFunction < __OfCollectionType, __ElementType >   __contains          /* NOLINT(bugprone-reserved-identifier) */
                > using __ReplaceOfCompositeClient __CDS_DeprecatedHint("No longer an experimental feature.") =                     /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __ReplaceOfCompositeClient < __ReceiverType, __ElementType, __OfCollectionType, __contains >;

                template <
                        typename                                                                                __ReceiverType,     /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                                                __ElementType,      /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                                                __OfCollectionType, /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __ContainsFunction < __OfCollectionType, __ElementType >   __contains          /* NOLINT(bugprone-reserved-identifier) */
                > using __LocalReplaceOfCompositeClient __CDS_DeprecatedHint("No longer an experimental feature.") =                /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __LocalReplaceOfCompositeClient < __ReceiverType, __ElementType, __OfCollectionType, __contains >;

            }
        }
    }
}

#endif /* __CDS_EX_SHARED_REPLACE_OF_COMPOSITE_CLIENT_HPP__ */
