/*
 * Created by loghin on 6/26/22.
 */

#ifndef __CDS_SHARED_DELEGATE_FORWARD_ITERABLE_PRIMITIVE_CLIENT_IMPL_HPP__
#define __CDS_SHARED_DELEGATE_FORWARD_ITERABLE_PRIMITIVE_CLIENT_IMPL_HPP__ /* NOLINT(bugprone-reserved-identifier) */

namespace cds {                 /* NOLINT(modernize-concat-nested-namespaces) */
    namespace experimental {    /* NOLINT(modernize-concat-nested-namespaces) */
        namespace __hidden {    /* NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier) */
            namespace __impl {  /* NOLINT(bugprone-reserved-identifier) */

                template <
                        typename __ReceiverType,            /* NOLINT(bugprone-reserved-identifier) */
                        typename __ElementType,             /* NOLINT(bugprone-reserved-identifier) */
                        bool     __bidirectional            /* NOLINT(bugprone-reserved-identifier) */
                > auto __DelegateForwardIterablePrimitiveClient <
                        __ReceiverType,
                        __ElementType,
                        __bidirectional
                > :: begin () noexcept -> Iterator {

                    using __ReceiverBeginHandlerType    = __AbstractDelegateIterator < __ElementType > * ( __ReceiverType :: * ) ();
                    auto const pReceiver                = reinterpret_cast < __ReceiverType * > ( this );

                    return Iterator (
                            pReceiver, (
                                    pReceiver ->* reinterpret_cast < __ReceiverBeginHandlerType > (
                                            pReceiver->__cicch_obtainGenericHandler (
                                                    __CollectionInternalRequestType :: __cirt_begin
                                            )
                                    )
                            ) ()
                    );
                }


                template <
                        typename __ReceiverType,            /* NOLINT(bugprone-reserved-identifier) */
                        typename __ElementType,             /* NOLINT(bugprone-reserved-identifier) */
                        bool     __bidirectional            /* NOLINT(bugprone-reserved-identifier) */
                > auto __DelegateForwardIterablePrimitiveClient <
                        __ReceiverType,
                        __ElementType,
                        __bidirectional
                > :: end () noexcept -> Iterator {

                    using __ReceiverEndHandlerType  = __AbstractDelegateIterator < __ElementType > * ( __ReceiverType :: * ) ();
                    auto const pReceiver            = reinterpret_cast < __ReceiverType * > ( this );

                    return Iterator (
                            pReceiver, (
                                    pReceiver ->* reinterpret_cast < __ReceiverEndHandlerType > (
                                            pReceiver->__cicch_obtainGenericHandler (
                                                    __CollectionInternalRequestType :: __cirt_end
                                            )
                                    )
                            ) ()
                    );
                }


                template <
                        typename __ReceiverType,    /* NOLINT(bugprone-reserved-identifier) */
                        typename __IteratorType     /* NOLINT(bugprone-reserved-identifier) */
                > __CDS_cpplang_NonConstConstexprMemberFunction auto __LocalDelegateForwardIterablePrimitiveClient <
                        __ReceiverType,
                        __IteratorType
                > :: begin () noexcept -> Iterator {

                    return reinterpret_cast < __ReceiverType * > ( this )->__beginLocal();
                }


                template <
                        typename __ReceiverType,    /* NOLINT(bugprone-reserved-identifier) */
                        typename __IteratorType     /* NOLINT(bugprone-reserved-identifier) */
                > __CDS_cpplang_NonConstConstexprMemberFunction auto __LocalDelegateForwardIterablePrimitiveClient <
                        __ReceiverType,
                        __IteratorType
                > :: end () noexcept -> Iterator {

                    return reinterpret_cast < __ReceiverType * > ( this )->__endLocal();
                }

            }
        }
    }
}

#endif /* __CDS_SHARED_DELEGATE_FORWARD_ITERABLE_PRIMITIVE_CLIENT_IMPL_HPP__ */
