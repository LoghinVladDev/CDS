/*
 * Created by loghin on 6/26/22.
 */

#ifndef __CDS_SHARED_DELEGATE_BACKWARD_CONST_ITERABLE_PRIMITIVE_CLIENT_IMPL_HPP__
#define __CDS_SHARED_DELEGATE_BACKWARD_CONST_ITERABLE_PRIMITIVE_CLIENT_IMPL_HPP__ /* NOLINT(bugprone-reserved-identifier) */

namespace cds {             /* NOLINT(modernize-concat-nested-namespaces) */
    namespace __hidden {    /* NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier) */
        namespace __impl {  /* NOLINT(bugprone-reserved-identifier) */

            template <
                    typename __ReceiverType,            /* NOLINT(bugprone-reserved-identifier) */
                    typename __ElementType,             /* NOLINT(bugprone-reserved-identifier) */
                    bool     __bidirectional            /* NOLINT(bugprone-reserved-identifier) */
            > __CDS_OptimalInline auto __DelegateBackwardConstIterablePrimitiveClient <
                    __ReceiverType,
                    __ElementType,
                    __bidirectional
            > :: rbegin () const noexcept -> ConstReverseIterator {

                return this->crbegin();
            }


            template <
                    typename __ReceiverType,            /* NOLINT(bugprone-reserved-identifier) */
                    typename __ElementType,             /* NOLINT(bugprone-reserved-identifier) */
                    bool     __bidirectional            /* NOLINT(bugprone-reserved-identifier) */
            > __CDS_OptimalInline auto __DelegateBackwardConstIterablePrimitiveClient <
                    __ReceiverType,
                    __ElementType,
                    __bidirectional
            > :: rend () const noexcept -> ConstReverseIterator {

                return this->crend();
            }


            template <
                    typename __ReceiverType,            /* NOLINT(bugprone-reserved-identifier) */
                    typename __ElementType,             /* NOLINT(bugprone-reserved-identifier) */
                    bool     __bidirectional            /* NOLINT(bugprone-reserved-identifier) */
            > __CDS_OptimalInline auto __DelegateBackwardConstIterablePrimitiveClient <
                    __ReceiverType,
                    __ElementType,
                    __bidirectional
            > :: crbegin () const noexcept -> ConstReverseIterator {

                using __ReceiverRBeginHandlerType   = __AbstractDelegateIterator < __ElementType const > * ( __ReceiverType :: * ) () const;
                auto const pReceiver                = reinterpret_cast < __ReceiverType const * > ( this );

                return ConstReverseIterator (
                        pReceiver, (
                                pReceiver ->* reinterpret_cast < __ReceiverRBeginHandlerType > (
                                        pReceiver->__cicch_obtainGenericConstHandler (
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
            > __CDS_OptimalInline auto __DelegateBackwardConstIterablePrimitiveClient <
                    __ReceiverType,
                    __ElementType,
                    __bidirectional
            > :: crend () const noexcept -> ConstReverseIterator {

                using __ReceiverREndHandlerType = __AbstractDelegateIterator < __ElementType const > * ( __ReceiverType :: * ) () const;
                auto const pReceiver            = reinterpret_cast < __ReceiverType const * > ( this );

                return ConstReverseIterator (
                        pReceiver, (
                                pReceiver ->* reinterpret_cast < __ReceiverREndHandlerType > (
                                        pReceiver->__cicch_obtainGenericConstHandler (
                                                __CollectionInternalRequestType :: __cirt_rend
                                        )
                                )
                        ) ()
                );
            }


            template <
                    typename __ReceiverType,            /* NOLINT(bugprone-reserved-identifier) */
                    typename __ConstReverseIteratorType /* NOLINT(bugprone-reserved-identifier) */
            > constexpr auto __LocalDelegateBackwardConstIterablePrimitiveClient <
                    __ReceiverType,
                    __ConstReverseIteratorType
            > :: rbegin () const noexcept -> ConstReverseIterator {

                return reinterpret_cast < __ReceiverType const * > ( this )->__crbeginLocal();
            }


            template <
                    typename __ReceiverType,            /* NOLINT(bugprone-reserved-identifier) */
                    typename __ConstReverseIteratorType /* NOLINT(bugprone-reserved-identifier) */
            > constexpr auto __LocalDelegateBackwardConstIterablePrimitiveClient <
                    __ReceiverType,
                    __ConstReverseIteratorType
            > :: rend () const noexcept -> ConstReverseIterator {

                return reinterpret_cast < __ReceiverType const * > ( this )->__crendLocal();
            }


            template <
                    typename __ReceiverType,            /* NOLINT(bugprone-reserved-identifier) */
                    typename __ConstReverseIteratorType /* NOLINT(bugprone-reserved-identifier) */
            > constexpr auto __LocalDelegateBackwardConstIterablePrimitiveClient <
                    __ReceiverType,
                    __ConstReverseIteratorType
            > :: crbegin () const noexcept -> ConstReverseIterator {

                return reinterpret_cast < __ReceiverType const * > ( this )->__crbeginLocal();
            }


            template <
                    typename __ReceiverType,            /* NOLINT(bugprone-reserved-identifier) */
                    typename __ConstReverseIteratorType /* NOLINT(bugprone-reserved-identifier) */
            > constexpr auto __LocalDelegateBackwardConstIterablePrimitiveClient <
                    __ReceiverType,
                    __ConstReverseIteratorType
            > :: crend () const noexcept -> ConstReverseIterator {

                return reinterpret_cast < __ReceiverType const * > ( this )->__crendLocal();
            }

        }
    }
}

#endif /* __CDS_SHARED_DELEGATE_BACKWARD_CONST_ITERABLE_PRIMITIVE_CLIENT_IMPL_HPP__ */
