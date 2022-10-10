/*
 * Created by loghin on 6/28/22.
 */

#ifndef __CDS_EX_SHARED_CONST_ITERATOR_RELATIVE_INSERTION_PRIMITIVE_CLIENT_HPP__
#define __CDS_EX_SHARED_CONST_ITERATOR_RELATIVE_INSERTION_PRIMITIVE_CLIENT_HPP__ /* NOLINT(bugprone-reserved-identifier) */

#warning No longer an experimental feature. Use the non-experimental header.
#include "../../../../../../shared/collectionInternalCommunication/client/primitive/ConstIteratorRelativeInsertionPrimitiveClient.hpp"

namespace cds {                 /* NOLINT(modernize-concat-nested-namespaces) */
    namespace experimental {    /* NOLINT(modernize-concat-nested-namespaces) */
        namespace __hidden {    /* NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier) */
            namespace __impl {  /* NOLINT(bugprone-reserved-identifier) */

                template <
                        typename __ReceiverType,                                                                                                /* NOLINT(bugprone-reserved-identifier) */
                        typename __ElementType                                                                                                  /* NOLINT(bugprone-reserved-identifier) */
                > using __AbstractConstIteratorRelativeInsertionPrimitiveClient __CDS_DeprecatedHint("No longer an experimental feature.") =    /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __AbstractConstIteratorRelativeInsertionPrimitiveClient < __ReceiverType, __ElementType >;


                template <
                        typename __ReceiverType,                                                                                            /* NOLINT(bugprone-reserved-identifier) */
                        typename __ElementType,                                                                                             /* NOLINT(bugprone-reserved-identifier) */
                        typename __IteratorType                                                                                             /* NOLINT(bugprone-reserved-identifier) */
                > using __LocalConstIteratorRelativeInsertionPrimitiveClient __CDS_DeprecatedHint("No longer an experimental feature.") =   /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __LocalConstIteratorRelativeInsertionPrimitiveClient < __ReceiverType, __ElementType, __IteratorType >;

            }
        }
    }
}

#endif /* __CDS_EX_SHARED_CONST_ITERATOR_RELATIVE_INSERTION_PRIMITIVE_CLIENT_HPP__ */
