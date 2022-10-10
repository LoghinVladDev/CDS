/*
 * Created by loghin on 6/26/22.
 */

#ifndef __CDS_SHARED_DELEGATE_BACKWARD_ITERABLE_PRIMITIVE_CLIENT_IMPL_HPP__
#define __CDS_SHARED_DELEGATE_BACKWARD_ITERABLE_PRIMITIVE_CLIENT_IMPL_HPP__ /* NOLINT(bugprone-reserved-identifier) */

namespace cds {             /* NOLINT(modernize-concat-nested-namespaces) */
    namespace __hidden {    /* NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier) */
        namespace __impl {  /* NOLINT(bugprone-reserved-identifier) */

            template <
                    typename __ReceiverType,            /* NOLINT(bugprone-reserved-identifier) */
                    typename __ElementType,             /* NOLINT(bugprone-reserved-identifier) */
                    bool     __bidirectional            /* NOLINT(bugprone-reserved-identifier) */
            > __CDS_OptimalInline auto __DelegateBackwardIterablePrimitiveClient <
                    __ReceiverType,
                    __ElementType,
                    __bidirectional
            > :: rbegin () noexcept -> ReverseIterator {

                using __ReceiverRBeginHandlerType   = __AbstractDelegateIterator < __ElementType > * ( __ReceiverType :: * ) ();
                auto const pReceiver                = reinterpret_cast < __ReceiverType * > ( this );

                return ReverseIterator (
                        pReceiver, (
                                pReceiver ->* reinterpret_cast < __ReceiverRBeginHandlerType > (
                                        pReceiver->__cicch_obtainGenericHandler (
                                                __CollectionInternalRequestType :: __cirt_rbegin
                                        )
                                )
                        ) ()
                );
            }


            template <
                    typename __ReceiverType,            /* NOLINT(bugprone-reserved-identifier) */
                    typename __ElementType,             /* NOLINT(bugprone-reserved-identifier) */
                    bool     __bidirectional            /* NOLINT(bugprone-reserved-identifier) */
            > __CDS_OptimalInline auto __DelegateBackwardIterablePrimitiveClient <
                    __ReceiverType,
                    __ElementType,
                    __bidirectional
            > :: rend () noexcept -> ReverseIterator {

                using __ReceiverREndHandlerType = __AbstractDelegateIterator < __ElementType > * ( __ReceiverType :: * ) ();
                auto const pReceiver            = reinterpret_cast < __ReceiverType * > ( this );

                return ReverseIterator (
                        pReceiver, (
                                pReceiver ->* reinterpret_cast < __ReceiverREndHandlerType > (
                                        reinterpret_cast < __ReceiverType * > ( this )->__cicch_obtainGenericHandler (
                                                __CollectionInternalRequestType :: __cirt_rend
                                        )
                                )
                        ) ()
                );
            }


            template <
                    typename __ReceiverType,        /* NOLINT(bugprone-reserved-identifier) */
                    typename __ReverseIteratorType  /* NOLINT(bugprone-reserved-identifier) */
            > __CDS_cpplang_NonConstConstexprMemberFunction auto __LocalDelegateBackwardIterablePrimitiveClient <
                    __ReceiverType,
                    __ReverseIteratorType
            > :: rbegin () noexcept -> ReverseIterator {

                return reinterpret_cast < __ReceiverType * > ( this )->__rbeginLocal();
            }


            template <
                    typename __ReceiverType,        /* NOLINT(bugprone-reserved-identifier) */
                    typename __ReverseIteratorType  /* NOLINT(bugprone-reserved-identifier) */
            > __CDS_cpplang_NonConstConstexprMemberFunction auto __LocalDelegateBackwardIterablePrimitiveClient <
                    __ReceiverType,
                    __ReverseIteratorType
            > :: rend () noexcept -> ReverseIterator {

                return reinterpret_cast < __ReceiverType * > ( this )->__rendLocal();
            }

        }
    }
}

#endif /* __CDS_SHARED_DELEGATE_BACKWARD_ITERABLE_PRIMITIVE_CLIENT_IMPL_HPP__ */
