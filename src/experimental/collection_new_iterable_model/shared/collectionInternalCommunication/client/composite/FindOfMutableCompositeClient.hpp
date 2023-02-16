/*
 * Created by loghin on 6/26/22.
 */

#ifndef __CDS_EX_SHARED_FIND_OF_MUTABLE_COMPOSITE_CLIENT_HPP__
#define __CDS_EX_SHARED_FIND_OF_MUTABLE_COMPOSITE_CLIENT_HPP__ /* NOLINT(bugprone-reserved-identifier) */

#warning No longer an experimental feature. Use the non-experimental header.
#include "../../../../../../shared/iterableInternalCommunication/client/composite/FindOfMutableCompositeClient.hpp"

namespace cds {                 /* NOLINT(modernize-concat-nested-namespaces) */
    namespace experimental {    /* NOLINT(modernize-concat-nested-namespaces) */
        namespace __hidden {    /* NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier) */
            namespace __impl {  /* NOLINT(bugprone-reserved-identifier) */

                template <
                        typename                                                                                __IterableType,         /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                                                __ElementType,          /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                                                __IteratorType,         /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                                                __FromIterableType,     /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __ContainsFunction < __FromIterableType, __ElementType >   __containsFunction,     /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __ContainsFunction < __FromIterableType, __ElementType >   __notContainsFunction   /* NOLINT(bugprone-reserved-identifier) */
                > using __FindOfMutableCompositeClient __CDS_DeprecatedHint("No longer an experimental feature.") =                     /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __FindOfMutableCompositeClient < __IterableType, __ElementType, __IteratorType, __FromIterableType, __containsFunction, __notContainsFunction >;


                template <
                        typename                                                                                __IterableType,         /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                                                __ElementType,          /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                                                __IteratorType,         /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                                                __FromIterableType,     /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __ContainsFunction < __FromIterableType, __ElementType >   __containsFunction,     /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __ContainsFunction < __FromIterableType, __ElementType >   __notContainsFunction   /* NOLINT(bugprone-reserved-identifier) */
                > using __LocalFindOfMutableCompositeClient __CDS_DeprecatedHint("No longer an experimental feature.") =                /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __LocalFindOfMutableCompositeClient < __IterableType, __ElementType, __IteratorType, __FromIterableType, __containsFunction, __notContainsFunction >;

            }
        }
    }
}

#endif /* __CDS_EX_SHARED_FIND_OF_MUTABLE_COMPOSITE_CLIENT_HPP__ */
