/*
 * Created by loghin on 6/26/22.
 */

#ifndef __CDS_EX_SHARED_REMOVE_BY_COMPOSITE_CLIENT_HPP__
#define __CDS_EX_SHARED_REMOVE_BY_COMPOSITE_CLIENT_HPP__ /* NOLINT(bugprone-reserved-identifier) */

#warning No longer an experimental feature. Use the non-experimental header.
#include "../../../../../../shared/iterableInternalCommunication/client/composite/RemoveByCompositeClient.hpp"

namespace cds {                 /* NOLINT(modernize-concat-nested-namespaces) */
    namespace experimental {    /* NOLINT(modernize-concat-nested-namespaces) */
        namespace __hidden {    /* NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier) */
            namespace __impl {  /* NOLINT(bugprone-reserved-identifier) */

                template <
                        typename __IterableType,        /* NOLINT(bugprone-reserved-identifier) */
                        typename __ElementType          /* NOLINT(bugprone-reserved-identifier) */
                > using __RemoveByCompositeClient __CDS_DeprecatedHint("No longer an experimental feature.") =
                        cds :: __hidden :: __impl :: __RemoveByCompositeClient < __IterableType, __ElementType >;


                template <
                        typename __IterableType,        /* NOLINT(bugprone-reserved-identifier) */
                        typename __ElementType          /* NOLINT(bugprone-reserved-identifier) */
                > using __LocalRemoveByCompositeClient __CDS_DeprecatedHint("No longer an experimental feature.") =
                        cds :: __hidden :: __impl :: __LocalRemoveByCompositeClient < __IterableType, __ElementType >;

            }
        }
    }
}

#endif /* __CDS_EX_SHARED_REMOVE_BY_COMPOSITE_CLIENT_HPP__ */
