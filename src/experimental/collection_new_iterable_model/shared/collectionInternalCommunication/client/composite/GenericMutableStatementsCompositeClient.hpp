/*
 * Created by loghin on 6/26/22.
 */

#ifndef __CDS_EX_SHARED_GENERIC_MUTABLE_STATEMENTS_COMPOSITE_CLIENT_HPP__
#define __CDS_EX_SHARED_GENERIC_MUTABLE_STATEMENTS_COMPOSITE_CLIENT_HPP__ /* NOLINT(bugprone-reserved-identifier) */

#warning No longer an experimental feature. Use the non-experimental header.
#include "../../../../../../shared/collectionInternalCommunication/client/composite/GenericMutableStatementsCompositeClient.hpp"

namespace cds {                 /* NOLINT(modernize-concat-nested-namespaces) */
    namespace experimental {    /* NOLINT(modernize-concat-nested-namespaces) */
        namespace __hidden {    /* NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier) */
            namespace __impl {  /* NOLINT(bugprone-reserved-identifier) */

                template <
                        typename                                                                                __ReceiverType,     /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                                                __ElementType       /* NOLINT(bugprone-reserved-identifier) */
                > using __GenericMutableStatementsCompositeClient __CDS_DeprecatedHint("No longer an experimental feature.") =      /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __GenericMutableStatementsCompositeClient < __ReceiverType, __ElementType >;


                template <
                        typename                                                                                __ReceiverType,     /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                                                __ElementType       /* NOLINT(bugprone-reserved-identifier) */
                > using __LocalGenericMutableStatementsCompositeClient __CDS_DeprecatedHint("No longer an experimental feature.") = /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __LocalGenericMutableStatementsCompositeClient < __ReceiverType, __ElementType >;

            }
        }
    }
}

#endif /* __CDS_EX_SHARED_GENERIC_MUTABLE_STATEMENTS_COMPOSITE_CLIENT_HPP__ */
