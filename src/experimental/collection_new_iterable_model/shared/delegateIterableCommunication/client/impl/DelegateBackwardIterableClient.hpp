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
                > :: rbegin () noexcept -> __dbic_Iterator {

                    return __dbic_Iterator (
                            static_cast < __ReceiverType * > ( this ),
                            static_cast < __ReceiverType * > ( this )->__dich_transmitRequest (
                                    __DelegateIteratorRequestType :: __dirt_rbegin
                            )
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
                > :: rend () noexcept -> __dbic_Iterator {

                    return __dbic_Iterator (
                            static_cast < __ReceiverType * > ( this ),
                            static_cast < __ReceiverType * > ( this )->__dich_transmitRequest (
                                    __DelegateIteratorRequestType :: __dirt_rend
                            )
                    );
                }

            }
        }
    }
}

#endif // __CDS_SHARED_DELEGATE_BACKWARD_ITERABLE_CLIENT_IMPL_HPP__
