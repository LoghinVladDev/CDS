/*
 * Created by loghin on 6/26/22.
 */

#ifndef __CDS_EX_SHARED_ABSTRACT_DELEGATE_WRAPPER_ITERATOR_HPP__
#define __CDS_EX_SHARED_ABSTRACT_DELEGATE_WRAPPER_ITERATOR_HPP__ /* NOLINT(bugprone-reserved-identifier) */

#warning No longer an experimental feature. Use the non-experimental header.
#include "../../../../shared/delegateIterator/AbstractDelegateWrapperIterator.hpp"

namespace cds {                 /* NOLINT(modernize-concat-nested-namespaces) */
    namespace experimental {    /* NOLINT(modernize-concat-nested-namespaces) */
        namespace __hidden {    /* NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier) */
            namespace __impl {  /* NOLINT(bugprone-reserved-identifier) */

                template < typename __ElementType >                                                                     /* NOLINT(bugprone-reserved-identifier) */
                using __AbstractDelegateWrapperIterator __CDS_DeprecatedHint("No longer an experimental feature.") =    /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __AbstractDelegateWrapperIterator < __ElementType >;

            }
        }
    }
}

#endif /* __CDS_EX_SHARED_ABSTRACT_DELEGATE_WRAPPER_ITERATOR_HPP__ */
