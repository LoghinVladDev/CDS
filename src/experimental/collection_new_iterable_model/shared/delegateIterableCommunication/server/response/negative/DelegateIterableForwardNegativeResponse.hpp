//
// Created by loghin on 6/26/22.
//

#ifndef __CDS_SHARED_DELEGATE_ITERABLE_FORWARD_NEGATIVE_RESPONSE_HPP__
#define __CDS_SHARED_DELEGATE_ITERABLE_FORWARD_NEGATIVE_RESPONSE_HPP__

namespace cds {                 // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {    // NOLINT(modernize-concat-nested-namespaces)
        namespace __hidden {    // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier)
            namespace __impl {  // NOLINT(bugprone-reserved-identifier)

                template <
                        typename __ReceiverType,                    // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType,                     // NOLINT(bugprone-reserved-identifier)
                        typename __WrappedIteratorType              // NOLINT(bugprone-reserved-identifier)
                > class __DelegateIterableForwardNegativeResponse { // NOLINT(bugprone-reserved-identifier)

                protected:
                    auto __difr_begin () noexcept -> __AbstractDelegateIterator < __ElementType > *;                // NOLINT(bugprone-reserved-identifier)

                protected:
                    auto __difr_end () noexcept -> __AbstractDelegateIterator < __ElementType > *;                  // NOLINT(bugprone-reserved-identifier)
                };

            }
        }
    }
}

#endif // __CDS_SHARED_DELEGATE_ITERABLE_FORWARD_NEGATIVE_RESPONSE_HPP__
