/*
 * Created by loghin on 6/26/22.
 */

#ifndef __CDS_SHARED_DELEGATE_FORWARD_ITERABLE_PRIMITIVE_CLIENT_IMPL_HPP__ /* NOLINT(llvm-header-guard) */
#define __CDS_SHARED_DELEGATE_FORWARD_ITERABLE_PRIMITIVE_CLIENT_IMPL_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

namespace cds {             /* NOLINT(modernize-concat-nested-namespaces) */
    namespace __hidden {    /* NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        namespace __impl {  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            template <
                    typename __ReceiverType,            /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ElementType,             /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    bool     __bidirectional            /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > auto __DelegateForwardIterablePrimitiveClient <
                    __ReceiverType,
                    __ElementType,
                    __bidirectional
            > :: begin () noexcept -> Iterator {

                using __ReceiverBeginHandlerType    = cds :: functional :: MapperFunction < __AbstractDelegateIterator < __ElementType > *, __ReceiverType * >;
                auto pReceiver                      = reinterpret_cast < __ReceiverType * > ( this );

                return Iterator (
                        pReceiver,
                        reinterpret_cast < __ReceiverBeginHandlerType > ( pReceiver->__cicch_obtainGenericHandler ( __CollectionInternalRequestType :: __cirt_begin ) ) ( pReceiver )
                );
            }


            template <
                    typename __ReceiverType,            /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ElementType,             /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    bool     __bidirectional            /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > auto __DelegateForwardIterablePrimitiveClient <
                    __ReceiverType,
                    __ElementType,
                    __bidirectional
            > :: end () noexcept -> Iterator {

                using __ReceiverEndHandlerType  = cds :: functional :: MapperFunction < __AbstractDelegateIterator < __ElementType > *, __ReceiverType * >;
                auto pReceiver                  = reinterpret_cast < __ReceiverType * > ( this );

                return Iterator (
                        pReceiver,
                        reinterpret_cast < __ReceiverEndHandlerType > ( pReceiver->__cicch_obtainGenericHandler ( __CollectionInternalRequestType :: __cirt_end ) ) ( pReceiver )
                );
            }


            template <
                    typename __ReceiverType,    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __IteratorType     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > __CDS_cpplang_NonConstConstexprMemberFunction auto __LocalDelegateForwardIterablePrimitiveClient <
                    __ReceiverType,
                    __IteratorType
            > :: begin () noexcept -> Iterator {

                return __ReceiverType :: __beginLocal (
                        reinterpret_cast < __ReceiverType * > ( this )
                );
            }


            template <
                    typename __ReceiverType,    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __IteratorType     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > __CDS_cpplang_NonConstConstexprMemberFunction auto __LocalDelegateForwardIterablePrimitiveClient <
                    __ReceiverType,
                    __IteratorType
            > :: end () noexcept -> Iterator {

                return __ReceiverType :: __endLocal (
                        reinterpret_cast < __ReceiverType * > ( this )
                );
            }

        } /* namespace __impl */
    } /* namespace __hidden */
} /* namespace cds */

#endif /* __CDS_SHARED_DELEGATE_FORWARD_ITERABLE_PRIMITIVE_CLIENT_IMPL_HPP__ */
