//
// Created by loghin on 6/26/22.
//

#ifndef __CDS_SHARED_DELEGATE_ITERABLE_BACKWARD_POSITIVE_RESPONSE_HPP__
#define __CDS_SHARED_DELEGATE_ITERABLE_BACKWARD_POSITIVE_RESPONSE_HPP__

namespace cds {                 // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {    // NOLINT(modernize-concat-nested-namespaces)
        namespace __hidden {    // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier)
            namespace __impl {  // NOLINT(bugprone-reserved-identifier)

                template <
                        typename __ReceiverType,                        // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType,                         // NOLINT(bugprone-reserved-identifier)
                        typename __WrappedIteratorType                  // NOLINT(bugprone-reserved-identifier)
                > class __DelegateIterableBackwardPositiveResponse {    // NOLINT(bugprone-reserved-identifier)

                protected:
                    using __dibpr_DelegateIterator = __DelegateIterator < __ElementType, __WrappedIteratorType >;   // NOLINT(bugprone-reserved-identifier)

                protected:
                    auto __dibr_begin () noexcept -> __AbstractDelegateIterator < __ElementType > *;                // NOLINT(bugprone-reserved-identifier)

                protected:
                    auto __dibr_end () noexcept -> __AbstractDelegateIterator < __ElementType > *;                  // NOLINT(bugprone-reserved-identifier)
                };

            }
        }
    }
}

#endif // __CDS_SHARED_DELEGATE_ITERABLE_BACKWARD_POSITIVE_RESPONSE_HPP__
