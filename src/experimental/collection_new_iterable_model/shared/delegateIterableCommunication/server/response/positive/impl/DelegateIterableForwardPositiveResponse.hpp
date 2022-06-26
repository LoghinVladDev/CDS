//
// Created by loghin on 6/26/22.
//

#ifndef __CDS_SHARED_DELEGATE_ITERABLE_FORWARD_POSITIVE_RESPONSE_IMPL_HPP__
#define __CDS_SHARED_DELEGATE_ITERABLE_FORWARD_POSITIVE_RESPONSE_IMPL_HPP__

namespace cds {                 // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {    // NOLINT(modernize-concat-nested-namespaces)
        namespace __hidden {    // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier)
            namespace __impl {  // NOLINT(bugprone-reserved-identifier)

                template <
                        typename __ReceiverType,                    // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType,                     // NOLINT(bugprone-reserved-identifier)
                        typename __WrappedIteratorType              // NOLINT(bugprone-reserved-identifier)
                > __CDS_OptimalInline auto __DelegateIterableForwardPositiveResponse <
                        __ReceiverType,
                        __ElementType,
                        __WrappedIteratorType
                > :: __difr_begin () noexcept -> __AbstractDelegateIterator < __ElementType > * {

                    return new __difpr_DelegateIterator ( static_cast < __ReceiverType * > ( this )->begin() );
                }


                template <
                        typename __ReceiverType,                    // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType,                     // NOLINT(bugprone-reserved-identifier)
                        typename __WrappedIteratorType              // NOLINT(bugprone-reserved-identifier)
                > __CDS_OptimalInline auto __DelegateIterableForwardPositiveResponse <
                        __ReceiverType,
                        __ElementType,
                        __WrappedIteratorType
                > :: __difr_end () noexcept -> __AbstractDelegateIterator < __ElementType > * {

                    return new __difpr_DelegateIterator ( static_cast < __ReceiverType * > ( this )->end() );
                }

            }
        }
    }
}

#endif // __CDS_SHARED_DELEGATE_ITERABLE_FORWARD_POSITIVE_RESPONSE_IMPL_HPP__
