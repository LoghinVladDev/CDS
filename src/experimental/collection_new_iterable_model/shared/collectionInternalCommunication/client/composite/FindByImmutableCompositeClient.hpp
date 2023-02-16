/*
 * Created by loghin on 6/27/22.
 */

#ifndef __CDS_EX_SHARED_FIND_BY_IMMUTABLE_COMPOSITE_CLIENT_HPP__
#define __CDS_EX_SHARED_FIND_BY_IMMUTABLE_COMPOSITE_CLIENT_HPP__ /* NOLINT(bugprone-reserved-identifier) */

#warning No longer an experimental feature. Use the non-experimental header.
#include "../../../../../../shared/iterableInternalCommunication/client/composite/FindByImmutableCompositeClient.hpp"

namespace cds {                 /* NOLINT(modernize-concat-nested-namespaces) */
    namespace experimental {    /* NOLINT(modernize-concat-nested-namespaces) */
        namespace __hidden {    /* NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier) */
            namespace __impl {  /* NOLINT(bugprone-reserved-identifier) */

                template <
                        typename                                                                                __ReceiverType, /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                                                __ElementType,  /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                                                __IteratorType  /* NOLINT(bugprone-reserved-identifier) */
                > using __FindByImmutableCompositeClient __CDS_DeprecatedHint("No longer an experimental feature.") =           /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __FindByImmutableCompositeClient < __ReceiverType, __ElementType, __IteratorType >;


                template <
                        typename                                                                                __ReceiverType, /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                                                __ElementType,  /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                                                __IteratorType  /* NOLINT(bugprone-reserved-identifier) */
                > using __LocalFindByImmutableCompositeClient __CDS_DeprecatedHint("No longer an experimental feature.") =      /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __LocalFindByImmutableCompositeClient < __ReceiverType, __ElementType, __IteratorType >;

            }
        }
    }
}

#endif /* __CDS_EX_SHARED_FIND_BY_IMMUTABLE_COMPOSITE_CLIENT_HPP__ */
