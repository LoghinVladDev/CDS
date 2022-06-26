//
// Created by loghin on 6/26/22.
//

#ifndef __CDS_SHARED_DELEGATE_ITERABLE_CHANNEL_HPP__
#define __CDS_SHARED_DELEGATE_ITERABLE_CHANNEL_HPP__

namespace cds {                 // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {    // NOLINT(modernize-concat-nested-namespaces)
        namespace __hidden {    // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier)
            namespace __impl {  // NOLINT(bugprone-reserved-identifier)

                template <
                        typename __ReceiverType,            // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType              // NOLINT(bugprone-reserved-identifier)
                > class __DelegateIterableChannel {    // NOLINT(bugprone-reserved-identifier)

                private:
                    friend class __DelegateForwardIterableClient < __ReceiverType, __ElementType, false >;

                private:
                    friend class __DelegateForwardIterableClient < __ReceiverType, __ElementType, true >;

                private:
                    friend class __DelegateForwardIterableClient < __ReceiverType, __ElementType, false >;

                private:
                    friend class __DelegateForwardIterableClient < __ReceiverType, __ElementType, true >;

                protected:
                    virtual auto __dich_transmitRequest ( // NOLINT(bugprone-reserved-identifier)
                            __DelegateIteratorRequestType requestType
                    ) noexcept -> __AbstractDelegateIterator < __ElementType > * = 0;
                };

            }
        }
    }
}

#endif // __CDS_SHARED_DELEGATE_ITERABLE_CHANNEL_HPP__
