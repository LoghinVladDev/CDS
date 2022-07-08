//
// Created by loghin on 6/26/22.
//

#ifndef __CDS_SHARED_DELEGATE_BACKWARD_CONST_ITERABLE_PRIMITIVE_CLIENT_IMPL_HPP__
#define __CDS_SHARED_DELEGATE_BACKWARD_CONST_ITERABLE_PRIMITIVE_CLIENT_IMPL_HPP__

namespace cds {                 // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {    // NOLINT(modernize-concat-nested-namespaces)
        namespace __hidden {    // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier)
            namespace __impl {  // NOLINT(bugprone-reserved-identifier)

                template <
                        typename __ReceiverType,            // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType,             // NOLINT(bugprone-reserved-identifier)
                        bool     __bidirectional            // NOLINT(bugprone-reserved-identifier)
                > __CDS_OptimalInline auto __DelegateBackwardConstIterablePrimitiveClient <
                        __ReceiverType,
                        __ElementType,
                        __bidirectional
                > :: rbegin () const noexcept -> ConstReverseIterator {

                    return this->crbegin();
                }


                template <
                        typename __ReceiverType,            // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType,             // NOLINT(bugprone-reserved-identifier)
                        bool     __bidirectional            // NOLINT(bugprone-reserved-identifier)
                > __CDS_OptimalInline auto __DelegateBackwardConstIterablePrimitiveClient <
                        __ReceiverType,
                        __ElementType,
                        __bidirectional
                > :: rend () const noexcept -> ConstReverseIterator {

                    return this->crend();
                }


                template <
                        typename __ReceiverType,            // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType,             // NOLINT(bugprone-reserved-identifier)
                        bool     __bidirectional            // NOLINT(bugprone-reserved-identifier)
                > __CDS_OptimalInline auto __DelegateBackwardConstIterablePrimitiveClient <
                        __ReceiverType,
                        __ElementType,
                        __bidirectional
                > :: crbegin () const noexcept -> ConstReverseIterator {

                    return ConstReverseIterator (
                            static_cast < __ReceiverType const * > ( this ), (
                                    static_cast < __ReceiverType const * > ( this )->*
                                    reinterpret_cast <
                                            __AbstractDelegateIterator < __ElementType const > * ( __ReceiverType :: * ) () const
                                    > (
                                            static_cast < __ReceiverType const * > ( this )->__cicch_obtainGenericConstHandler (
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
                > __CDS_OptimalInline auto __DelegateBackwardConstIterablePrimitiveClient <
                        __ReceiverType,
                        __ElementType,
                        __bidirectional
                > :: crend () const noexcept -> ConstReverseIterator {

                    return ConstReverseIterator (
                            static_cast < __ReceiverType const * > ( this ), (
                                    static_cast < __ReceiverType const * > ( this )->*
                                    reinterpret_cast <
                                            __AbstractDelegateIterator < __ElementType const > * ( __ReceiverType :: * ) () const
                                    > (
                                            static_cast < __ReceiverType const * > ( this )->__cicch_obtainGenericConstHandler (
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

#endif // __CDS_SHARED_DELEGATE_BACKWARD_CONST_ITERABLE_PRIMITIVE_CLIENT_IMPL_HPP__
