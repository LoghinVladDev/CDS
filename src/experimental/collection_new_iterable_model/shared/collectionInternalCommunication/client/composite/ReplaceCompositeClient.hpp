/*
 * Created by loghin on 6/30/2022.
 */

#ifndef __CDS_EX_SHARED_REPLACE_COMPOSITE_CLIENT_HPP__
#define __CDS_EX_SHARED_REPLACE_COMPOSITE_CLIENT_HPP__ /* NOLINT(bugprone-reserved-identifier) */

#warning No longer an experimental feature. Use the non-experimental header.
#include "../../../../../../shared/iterableInternalCommunication/client/composite/ReplaceCompositeClient.hpp"

namespace cds {                 /* NOLINT(modernize-concat-nested-namespaces) */
    namespace experimental {    /* NOLINT(modernize-concat-nested-namespaces) */
        namespace __hidden {    /* NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier) */
            namespace __impl {  /* NOLINT(bugprone-reserved-identifier) */

                template <
                        typename __ReceiverType,                                                                /* NOLINT(bugprone-reserved-identifier) */
                        typename __ElementType                                                                  /* NOLINT(bugprone-reserved-identifier) */
                > using __ReplaceCompositeClient __CDS_DeprecatedHint("No longer an experimental feature.") =   /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __ReplaceCompositeClient < __ReceiverType, __ElementType >;


                template <
                        typename __ReceiverType,                                                                    /* NOLINT(bugprone-reserved-identifier) */
                        typename __ElementType                                                                      /* NOLINT(bugprone-reserved-identifier) */
                > using __LocalReplaceCompositeClient __CDS_DeprecatedHint("No longer an experimental feature.") =  /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __LocalReplaceCompositeClient < __ReceiverType, __ElementType >;

            }
        }
    }
}

#endif /* __CDS_EX_SHARED_REPLACE_COMPOSITE_CLIENT_HPP__ */
