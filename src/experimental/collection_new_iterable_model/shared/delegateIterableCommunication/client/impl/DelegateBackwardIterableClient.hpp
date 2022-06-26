//
// Created by loghin on 6/26/22.
//

#ifndef __CDS_SHARED_DELEGATE_BACKWARD_ITERABLE_CLIENT_IMPL_HPP__
#define __CDS_SHARED_DELEGATE_BACKWARD_ITERABLE_CLIENT_IMPL_HPP__

namespace cds {                 // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {    // NOLINT(modernize-concat-nested-namespaces)
        namespace __hidden {    // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier)
            namespace __impl {  // NOLINT(bugprone-reserved-identifier)

                template <
                        typename __ReceiverType,            // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType,             // NOLINT(bugprone-reserved-identifier)
                        bool     __bidirectional            // NOLINT(bugprone-reserved-identifier)
                > __CDS_OptimalInline auto __DelegateBackwardIterableClient <
                        __ReceiverType,
                        __ElementType,
                        __bidirectional
                > :: rbegin () noexcept -> ReverseIterator {

                    __DelegateIterableRequest const request {
                            __DelegateIterableRequestType :: __dirt_rbegin,
                            nullptr
                    };

                    __DelegateIterableResponse response; // NOLINT(cppcoreguidelines-pro-type-member-init)

                    auto const requestAvailabilityStatus = static_cast < __ReceiverType * > ( this )->__dich_transmitRequest (
                            & request,
                            & response
                    );

                    if ( ! requestAvailabilityStatus || ! response._status ) {
                        return ReverseIterator ();
                    }

                    return ReverseIterator (
                            static_cast < __ReceiverType * > ( this ),
                            reinterpret_cast < __AbstractDelegateIterator < __ElementType > * > ( response._pData )
                    );
                }


                template <
                        typename __ReceiverType,            // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType,             // NOLINT(bugprone-reserved-identifier)
                        bool     __bidirectional            // NOLINT(bugprone-reserved-identifier)
                > __CDS_OptimalInline auto __DelegateBackwardIterableClient <
                        __ReceiverType,
                        __ElementType,
                        __bidirectional
                > :: rend () noexcept -> ReverseIterator {

                    __DelegateIterableRequest const request {
                            __DelegateIterableRequestType :: __dirt_rend,
                            nullptr
                    };

                    __DelegateIterableResponse response; // NOLINT(cppcoreguidelines-pro-type-member-init)

                    auto const requestAvailabilityStatus = static_cast < __ReceiverType * > ( this )->__dich_transmitRequest (
                            & request,
                            & response
                    );

                    if ( ! requestAvailabilityStatus || ! response._status ) {
                        return ReverseIterator ();
                    }

                    return ReverseIterator (
                            static_cast < __ReceiverType * > ( this ),
                            reinterpret_cast < __AbstractDelegateIterator < __ElementType > * > ( response._pData )
                    );
                }

            }
        }
    }
}

#endif // __CDS_SHARED_DELEGATE_BACKWARD_ITERABLE_CLIENT_IMPL_HPP__
