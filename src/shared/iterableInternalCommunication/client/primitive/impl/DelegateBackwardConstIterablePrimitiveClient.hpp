/*
 * Created by loghin on 6/26/22.
 */
 
#ifndef __CDS_SHARED_DELEGATE_BACKWARD_CONST_ITERABLE_PRIMITIVE_CLIENT_IMPL_HPP__ /* NOLINT(llvm-header-guard) */
#define __CDS_SHARED_DELEGATE_BACKWARD_CONST_ITERABLE_PRIMITIVE_CLIENT_IMPL_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

namespace cds {             /* NOLINT(modernize-concat-nested-namespaces) */
    namespace __hidden {    /* NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        namespace __impl {  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            template <
                    typename __ReceiverType,            /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ElementType,             /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    bool     __bidirectional            /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > __CDS_OptimalInline auto __DelegateBackwardConstIterablePrimitiveClient <
                    __ReceiverType,
                    __ElementType,
                    __bidirectional
            > :: rbegin () const noexcept -> ConstReverseIterator {

                return this->crbegin();
            }


            template <
                    typename __ReceiverType,            /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ElementType,             /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    bool     __bidirectional            /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > __CDS_OptimalInline auto __DelegateBackwardConstIterablePrimitiveClient <
                    __ReceiverType,
                    __ElementType,
                    __bidirectional
            > :: rend () const noexcept -> ConstReverseIterator {

                return this->crend();
            }


            template <
                    typename __ReceiverType,            /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ElementType,             /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    bool     __bidirectional            /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > __CDS_OptimalInline auto __DelegateBackwardConstIterablePrimitiveClient <
                    __ReceiverType,
                    __ElementType,
                    __bidirectional
            > :: crbegin () const noexcept -> ConstReverseIterator {

                using __ReceiverRBeginHandlerType   = cds :: functional :: MapperFunction < __AbstractDelegateIterator < __ElementType const > *, __ReceiverType const * >;
                auto const pReceiver                = reinterpret_cast < __ReceiverType const * > ( this );

                return ConstReverseIterator (
                        pReceiver,
                        reinterpret_cast < __ReceiverRBeginHandlerType > ( pReceiver->__iicch_obtainGenericConstHandler ( __IterableInternalRequestType :: __iirt_rbegin ) ) ( pReceiver )
                );
            }


            template <
                    typename __ReceiverType,            /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ElementType,             /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    bool     __bidirectional            /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > __CDS_OptimalInline auto __DelegateBackwardConstIterablePrimitiveClient <
                    __ReceiverType,
                    __ElementType,
                    __bidirectional
            > :: crend () const noexcept -> ConstReverseIterator {

                using __ReceiverREndHandlerType = cds :: functional :: MapperFunction < __AbstractDelegateIterator < __ElementType const > *, __ReceiverType const * >;
                auto const pReceiver            = reinterpret_cast < __ReceiverType const * > ( this );

                return ConstReverseIterator (
                        pReceiver,
                        reinterpret_cast < __ReceiverREndHandlerType > ( pReceiver->__iicch_obtainGenericConstHandler ( __IterableInternalRequestType :: __iirt_rend ) ) ( pReceiver )
                );
            }


            template <
                    typename __ReceiverType,            /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ConstReverseIteratorType /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > constexpr auto __LocalDelegateBackwardConstIterablePrimitiveClient <
                    __ReceiverType,
                    __ConstReverseIteratorType
            > :: rbegin () const noexcept -> ConstReverseIterator {

                return __ReceiverType :: __crbeginLocal (
                        reinterpret_cast < __ReceiverType const * > ( this )
                );
            }


            template <
                    typename __ReceiverType,            /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ConstReverseIteratorType /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > constexpr auto __LocalDelegateBackwardConstIterablePrimitiveClient <
                    __ReceiverType,
                    __ConstReverseIteratorType
            > :: rend () const noexcept -> ConstReverseIterator {

                return __ReceiverType :: __crendLocal (
                        reinterpret_cast < __ReceiverType const * > ( this )
                );
            }


            template <
                    typename __ReceiverType,            /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ConstReverseIteratorType /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > constexpr auto __LocalDelegateBackwardConstIterablePrimitiveClient <
                    __ReceiverType,
                    __ConstReverseIteratorType
            > :: crbegin () const noexcept -> ConstReverseIterator {

                return __ReceiverType :: __crbeginLocal (
                        reinterpret_cast < __ReceiverType const * > ( this )
                );
            }


            template <
                    typename __ReceiverType,            /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ConstReverseIteratorType /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > constexpr auto __LocalDelegateBackwardConstIterablePrimitiveClient <
                    __ReceiverType,
                    __ConstReverseIteratorType
            > :: crend () const noexcept -> ConstReverseIterator {

                return __ReceiverType :: __crendLocal (
                        reinterpret_cast < __ReceiverType const * > ( this )
                );
            }

        } /* namespace __impl */
    } /* namespace __hidden */
} /* namespace cds */

#endif /* __CDS_SHARED_DELEGATE_BACKWARD_CONST_ITERABLE_PRIMITIVE_CLIENT_IMPL_HPP__ */
