/*
 * Created by loghin on 6/26/22.
 */

#ifndef __CDS_EX_SHARED_DELEGATE_ITERATOR_HPP__
#define __CDS_EX_SHARED_DELEGATE_ITERATOR_HPP__ /* NOLINT(bugprone-reserved-identifier) */

#warning No longer an experimental feature. Use the non-experimental header.
#include "../../../../shared/delegateIterator/DelegateIterator.hpp"

namespace cds {                 /* NOLINT(modernize-concat-nested-namespaces) */
    namespace experimental {    /* NOLINT(modernize-concat-nested-namespaces) */
        namespace __hidden {    /* NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier) */
            namespace __impl {  /* NOLINT(bugprone-reserved-identifier) */

                namespace meta {

                    template < typename __TWrappedIteratorType, typename = void >                                       /* NOLINT(bugprone-reserved-identifier) */
                    using __WrappedIteratorBidirectional __CDS_DeprecatedHint("No longer an experimental feature.") =   /* NOLINT(bugprone-reserved-identifier) */
                            cds :: __hidden :: __impl :: meta :: __WrappedIteratorBidirectional < __TWrappedIteratorType >;

                }

                template < typename __ElementType, typename __WrappedIteratorType >                     /* NOLINT(bugprone-reserved-identifier) */
                using __DelegateIterator __CDS_DeprecatedHint("No longer an experimental feature.") =   /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __DelegateIterator < __ElementType, __WrappedIteratorType >;

            }
        }
    }
}

#endif /* __CDS_EX_SHARED_DELEGATE_ITERATOR_HPP__ */
