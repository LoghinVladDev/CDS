//
// Created by loghin on 6/26/22.
//

#ifndef __CDS_SHARED_DELEGATE_FORWARD_CONST_ITERABLE_CLIENT_IMPL_HPP__
#define __CDS_SHARED_DELEGATE_FORWARD_CONST_ITERABLE_CLIENT_IMPL_HPP__

namespace cds {                 // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {    // NOLINT(modernize-concat-nested-namespaces)
        namespace __hidden {    // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier)
            namespace __impl {  // NOLINT(bugprone-reserved-identifier)

                template <
                        typename __ReceiverType,            // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType,             // NOLINT(bugprone-reserved-identifier)
                        bool     __bidirectional            // NOLINT(bugprone-reserved-identifier)
                > __CDS_OptimalInline auto __DelegateForwardConstIterableClient <
                        __ReceiverType,
                        __ElementType,
                        __bidirectional
                > :: begin () const noexcept -> ConstIterator {

                    return this->cbegin();
                }


                template <
                        typename __ReceiverType,            // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType,             // NOLINT(bugprone-reserved-identifier)
                        bool     __bidirectional            // NOLINT(bugprone-reserved-identifier)
                > __CDS_OptimalInline auto __DelegateForwardConstIterableClient <
                        __ReceiverType,
                        __ElementType,
                        __bidirectional
                > :: end () const noexcept -> ConstIterator {

                    return this->cend();
                }


                template <
                        typename __ReceiverType,            // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType,             // NOLINT(bugprone-reserved-identifier)
                        bool     __bidirectional            // NOLINT(bugprone-reserved-identifier)
                > __CDS_OptimalInline auto __DelegateForwardConstIterableClient <
                        __ReceiverType,
                        __ElementType,
                        __bidirectional
                > :: cbegin () const noexcept -> ConstIterator {

                    __CollectionInternalRequest const request {
                            __CollectionInternalRequestType :: __cirt_begin,
                            nullptr
                    };

                    __CollectionInternalRequestResponse response; // NOLINT(cppcoreguidelines-pro-type-member-init)

                    auto const requestAvailabilityStatus = static_cast < __ReceiverType const * > ( this )->__cicch_transmitConstRequest (
                            & request,
                            & response
                    );

                    if ( ! requestAvailabilityStatus || ! response._status ) {
                        return ConstIterator ();
                    }

                    return ConstIterator (
                            static_cast < __ReceiverType const * > ( this ),
                            reinterpret_cast < __AbstractDelegateIterator < __ElementType const > * > ( response._pData )
                    );
                }


                template <
                        typename __ReceiverType,            // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType,             // NOLINT(bugprone-reserved-identifier)
                        bool     __bidirectional            // NOLINT(bugprone-reserved-identifier)
                > __CDS_OptimalInline auto __DelegateForwardConstIterableClient <
                        __ReceiverType,
                        __ElementType,
                        __bidirectional
                > :: cend () const noexcept -> ConstIterator {

                    __CollectionInternalRequest const request {
                            __CollectionInternalRequestType :: __cirt_end,
                            nullptr
                    };

                    __CollectionInternalRequestResponse response; // NOLINT(cppcoreguidelines-pro-type-member-init)

                    auto const requestAvailabilityStatus = static_cast < __ReceiverType const * > ( this )->__cicch_transmitConstRequest (
                            & request,
                            & response
                    );

                    if ( ! requestAvailabilityStatus || ! response._status ) {
                        return ConstIterator ();
                    }

                    return ConstIterator (
                            static_cast < __ReceiverType const * > ( this ),
                            reinterpret_cast < __AbstractDelegateIterator < __ElementType const > * > ( response._pData )
                    );
                }

            }
        }
    }
}

#endif // __CDS_SHARED_DELEGATE_FORWARD_CONST_ITERABLE_CLIENT_IMPL_HPP__
