//
// Created by loghin on 6/26/22.
//

#ifndef __CDS_SHARED_DELEGATE_ITERABLE_BACKWARD_NEGATIVE_RESPONSE_IMPL_HPP__
#define __CDS_SHARED_DELEGATE_ITERABLE_BACKWARD_NEGATIVE_RESPONSE_IMPL_HPP__

namespace cds {                 // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {    // NOLINT(modernize-concat-nested-namespaces)
        namespace __hidden {    // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier)
            namespace __impl {  // NOLINT(bugprone-reserved-identifier)

                template <
                        typename __ReceiverType,                    // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType,                     // NOLINT(bugprone-reserved-identifier)
                        typename __WrappedIteratorType              // NOLINT(bugprone-reserved-identifier)
                > __CDS_OptimalInline auto __DelegateIterableBackwardNegativeResponse <
                        __ReceiverType,
                        __ElementType,
                        __WrappedIteratorType
                > :: __dibr_begin () noexcept -> __AbstractDelegateIterator < __ElementType > * {

                    return nullptr;
                }


                template <
                        typename __ReceiverType,                    // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType,                     // NOLINT(bugprone-reserved-identifier)
                        typename __WrappedIteratorType              // NOLINT(bugprone-reserved-identifier)
                > __CDS_OptimalInline auto __DelegateIterableBackwardNegativeResponse <
                        __ReceiverType,
                        __ElementType,
                        __WrappedIteratorType
                > :: __dibr_end () noexcept -> __AbstractDelegateIterator < __ElementType > * {

                    return nullptr;
                }

            }
        }
    }
}

#endif // __CDS_SHARED_DELEGATE_ITERABLE_BACKWARD_NEGATIVE_RESPONSE_IMPL_HPP__
