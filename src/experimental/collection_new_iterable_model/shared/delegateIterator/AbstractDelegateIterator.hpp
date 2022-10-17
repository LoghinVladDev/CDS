/*
 * Created by loghin on 6/26/22.
 */

#ifndef __CDS_EX_SHARED_ABSTRACT_DELEGATE_ITERATOR_HPP__
#define __CDS_EX_SHARED_ABSTRACT_DELEGATE_ITERATOR_HPP__ /* NOLINT(bugprone-reserved-identifier) */

#warning No longer an experimental feature. Use the non-experimental header.
#include "../../../../shared/delegateIterator/AbstractDelegateIterator.hpp"

namespace cds {                 /* NOLINT(modernize-concat-nested-namespaces) */
    namespace experimental {    /* NOLINT(modernize-concat-nested-namespaces) */
        namespace __hidden {    /* NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier) */
            namespace __impl {  /* NOLINT(bugprone-reserved-identifier) */

                using __GenericIterator             __CDS_DeprecatedHint("No longer an experimental feature.") =    /* NOLINT(bugprone-reserved-identifier) */
                        cds :: meta :: Iterator const *;

                template < typename __ElementType >                                                                 /* NOLINT(bugprone-reserved-identifier) */
                using __AbstractDelegateIterator    __CDS_DeprecatedHint("No longer an experimental feature.") =    /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __AbstractDelegateIterator < __ElementType >;

            }
        }
    }
}

#endif /* __CDS_SHARED_ABSTRACT_DELEGATE_ITERATOR_HPP__ */
