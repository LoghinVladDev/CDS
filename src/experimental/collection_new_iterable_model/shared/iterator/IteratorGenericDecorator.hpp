/*
 * Created by loghin on 14/08/22.
 */

#ifndef __CDS_EX_SHARED_ITERATOR_GENERIC_DECORATOR_HPP__
#define __CDS_EX_SHARED_ITERATOR_GENERIC_DECORATOR_HPP__ /* NOLINT(bugprone-reserved-identifier) */

#warning No longer an experimental feature. Use the non-experimental header.
#include "../../../../shared/iterator/IteratorGenericDecorator.hpp"

namespace cds { /* NOLINT(modernize-concat-nested-namespaces) */
    namespace experimental {

        namespace __hidden {    /* NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier) */
            namespace __impl {  /* NOLINT(bugprone-reserved-identifier) */

                template <
                        typename __DecoratedIteratorType,                                               /* NOLINT(bugprone-reserved-identifier) */
                        typename __ValueAtType                                                          /* NOLINT(bugprone-reserved-identifier) */
                > using __ValueAtFunction __CDS_DeprecatedHint("No longer an experimental feature.") =  /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __ValueAtFunction < __DecoratedIteratorType, __ValueAtType >;

            }
        }

        template <
                typename                                                                            __DecoratedIteratorType,    /* NOLINT(bugprone-reserved-identifier) */
                typename                                                                            __ValueAtType,              /* NOLINT(bugprone-reserved-identifier) */
                __hidden :: __impl :: __ValueAtFunction < __DecoratedIteratorType, __ValueAtType >  __valueAt                   /* NOLINT(bugprone-reserved-identifier) */
        > using ForwardIteratorGenericDecorator __CDS_DeprecatedHint("No longer an experimental feature.") =                    /* NOLINT(bugprone-reserved-identifier) */
                cds :: ForwardIteratorGenericDecorator < __DecoratedIteratorType, __ValueAtType, __valueAt >;

    }
}

#endif /* __CDS_EX_SHARED_ITERATOR_GENERIC_DECORATOR_HPP__ */
