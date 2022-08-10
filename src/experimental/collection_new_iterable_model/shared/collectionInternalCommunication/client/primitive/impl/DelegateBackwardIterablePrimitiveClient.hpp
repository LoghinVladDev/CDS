//
// Created by loghin on 6/26/22.
//

#ifndef __CDS_SHARED_DELEGATE_BACKWARD_ITERABLE_PRIMITIVE_CLIENT_IMPL_HPP__
#define __CDS_SHARED_DELEGATE_BACKWARD_ITERABLE_PRIMITIVE_CLIENT_IMPL_HPP__

namespace cds {                 // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {    // NOLINT(modernize-concat-nested-namespaces)
        namespace __hidden {    // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier)
            namespace __impl {  // NOLINT(bugprone-reserved-identifier)

                template <
                        typename __ReceiverType,            // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType,             // NOLINT(bugprone-reserved-identifier)
                        bool     __bidirectional            // NOLINT(bugprone-reserved-identifier)
                > __CDS_OptimalInline auto __DelegateBackwardIterablePrimitiveClient <
                        __ReceiverType,
                        __ElementType,
                        __bidirectional
                > :: rbegin () noexcept -> ReverseIterator {

                    return ReverseIterator (
                            reinterpret_cast < __ReceiverType * > ( this ), (
                                    reinterpret_cast < __ReceiverType * > ( this )->*
                                    reinterpret_cast <
                                            __AbstractDelegateIterator < __ElementType > * ( __ReceiverType :: * ) ()
                                    > (
                                            reinterpret_cast < __ReceiverType * > ( this )->__cicch_obtainGenericHandler (
                                                    __CollectionInternalRequestType :: __cirt_rbegin
                                            )
                                    )
                            ) ()
                    );
                }


                template <
                        typename __ReceiverType,            // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType,             // NOLINT(bugprone-reserved-identifier)
                        bool     __bidirectional            // NOLINT(bugprone-reserved-identifier)
                > __CDS_OptimalInline auto __DelegateBackwardIterablePrimitiveClient <
                        __ReceiverType,
                        __ElementType,
                        __bidirectional
                > :: rend () noexcept -> ReverseIterator {

                    return ReverseIterator (
                            reinterpret_cast < __ReceiverType * > ( this ), (
                                    reinterpret_cast < __ReceiverType * > ( this )->*
                                    reinterpret_cast <
                                            __AbstractDelegateIterator < __ElementType > * ( __ReceiverType :: * ) ()
                                    > (
                                            reinterpret_cast < __ReceiverType * > ( this )->__cicch_obtainGenericHandler (
                                                    __CollectionInternalRequestType :: __cirt_rend
                                            )
                                    )
                            ) ()
                    );
                }

            }
        }
    }
}

#endif // __CDS_SHARED_DELEGATE_BACKWARD_ITERABLE_PRIMITIVE_CLIENT_IMPL_HPP__
