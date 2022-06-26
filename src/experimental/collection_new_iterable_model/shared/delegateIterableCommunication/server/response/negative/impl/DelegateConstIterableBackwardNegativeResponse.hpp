//
// Created by loghin on 6/26/22.
//

#ifndef __CDS_SHARED_DELEGATE_CONST_ITERABLE_BACKWARD_NEGATIVE_RESPONSE_IMPL_HPP__
#define __CDS_SHARED_DELEGATE_CONST_ITERABLE_BACKWARD_NEGATIVE_RESPONSE_IMPL_HPP__

namespace cds {                 // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {    // NOLINT(modernize-concat-nested-namespaces)
        namespace __hidden {    // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier)
            namespace __impl {  // NOLINT(bugprone-reserved-identifier)

                template <
                        typename __ReceiverType,                    // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType,                     // NOLINT(bugprone-reserved-identifier)
                        typename __WrappedIteratorType              // NOLINT(bugprone-reserved-identifier)
                > __CDS_OptimalInline auto __DelegateConstIterableBackwardNegativeResponse <
                        __ReceiverType,
                        __ElementType,
                        __WrappedIteratorType
                > :: __dcibr_begin () const noexcept -> __AbstractDelegateIterator < __ElementType const > * {

                    return nullptr;
                }


                template <
                        typename __ReceiverType,                    // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType,                     // NOLINT(bugprone-reserved-identifier)
                        typename __WrappedIteratorType              // NOLINT(bugprone-reserved-identifier)
                > __CDS_OptimalInline auto __DelegateConstIterableBackwardNegativeResponse <
                        __ReceiverType,
                        __ElementType,
                        __WrappedIteratorType
                > :: __dcibr_end () const noexcept -> __AbstractDelegateIterator < __ElementType const > * {

                    return nullptr;
                }

            }
        }
    }
}

#endif // __CDS_SHARED_DELEGATE_CONST_ITERABLE_BACKWARD_NEGATIVE_RESPONSE_IMPL_HPP__
