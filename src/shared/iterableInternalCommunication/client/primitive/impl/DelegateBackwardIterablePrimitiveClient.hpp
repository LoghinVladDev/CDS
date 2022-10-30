/*
 * Created by loghin on 6/26/22.
 */

#ifndef __CDS_SHARED_DELEGATE_BACKWARD_ITERABLE_PRIMITIVE_CLIENT_IMPL_HPP__ /* NOLINT(llvm-header-guard) */
#define __CDS_SHARED_DELEGATE_BACKWARD_ITERABLE_PRIMITIVE_CLIENT_IMPL_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

namespace cds {             /* NOLINT(modernize-concat-nested-namespaces) */
    namespace __hidden {    /* NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        namespace __impl {  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            template <
                    typename __ReceiverType,            /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ElementType,             /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    bool     __bidirectional            /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > __CDS_OptimalInline auto __DelegateBackwardIterablePrimitiveClient <
                    __ReceiverType,
                    __ElementType,
                    __bidirectional
            > :: rbegin () noexcept -> ReverseIterator {

                using __ReceiverRBeginHandlerType   = cds :: functional :: MapperFunction < __AbstractDelegateIterator < __ElementType > *, __ReceiverType * >;
                auto pReceiver                      = reinterpret_cast < __ReceiverType * > ( this );

                return ReverseIterator (
                        pReceiver,
                        reinterpret_cast < __ReceiverRBeginHandlerType > ( pReceiver->__iicch_obtainGenericHandler ( __IterableInternalRequestType :: __iirt_rbegin ) ) ( pReceiver )
                );
            }


            template <
                    typename __ReceiverType,            /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ElementType,             /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    bool     __bidirectional            /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > __CDS_OptimalInline auto __DelegateBackwardIterablePrimitiveClient <
                    __ReceiverType,
                    __ElementType,
                    __bidirectional
            > :: rend () noexcept -> ReverseIterator {

                using __ReceiverREndHandlerType = cds :: functional :: MapperFunction < __AbstractDelegateIterator < __ElementType > *, __ReceiverType * >;
                auto pReceiver                  = reinterpret_cast < __ReceiverType * > ( this );

                return ReverseIterator (
                        pReceiver,
                        reinterpret_cast < __ReceiverREndHandlerType > ( pReceiver->__iicch_obtainGenericHandler ( __IterableInternalRequestType :: __iirt_rend ) ) ( pReceiver )
                );
            }


            template <
                    typename __ReceiverType,        /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ReverseIteratorType  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > __CDS_cpplang_NonConstConstexprMemberFunction auto __LocalDelegateBackwardIterablePrimitiveClient <
                    __ReceiverType,
                    __ReverseIteratorType
            > :: rbegin () noexcept -> ReverseIterator {

                return __ReceiverType :: __rbeginLocal (
                        reinterpret_cast < __ReceiverType * > ( this )
                );
            }


            template <
                    typename __ReceiverType,        /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ReverseIteratorType  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > __CDS_cpplang_NonConstConstexprMemberFunction auto __LocalDelegateBackwardIterablePrimitiveClient <
                    __ReceiverType,
                    __ReverseIteratorType
            > :: rend () noexcept -> ReverseIterator {

                return __ReceiverType :: __rendLocal (
                        reinterpret_cast < __ReceiverType * > ( this )
                );
            }

        } /* namespace __impl */
    } /* namespace __hidden */
} /* namespace cds */

#endif /* __CDS_SHARED_DELEGATE_BACKWARD_ITERABLE_PRIMITIVE_CLIENT_IMPL_HPP__ */
