/*
 * Created by loghin on 6/26/22.
 */

#ifndef __CDS_SHARED_DELEGATE_FORWARD_CONST_ITERABLE_PRIMITIVE_CLIENT_IMPL_HPP__ /* NOLINT(llvm-header-guard) */
#define __CDS_SHARED_DELEGATE_FORWARD_CONST_ITERABLE_PRIMITIVE_CLIENT_IMPL_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

namespace cds {             /* NOLINT(modernize-concat-nested-namespaces) */
    namespace __hidden {    /* NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        namespace __impl {  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            template <
                    typename __ReceiverType,            /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ElementType,             /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    bool     __bidirectional            /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > __CDS_OptimalInline auto __DelegateForwardConstIterablePrimitiveClient <
                    __ReceiverType,
                    __ElementType,
                    __bidirectional
            > :: begin () const noexcept -> ConstIterator {

                /* begin const is cbegin */
                return this->cbegin();
            }


            template <
                    typename __ReceiverType,            /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ElementType,             /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    bool     __bidirectional            /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > __CDS_OptimalInline auto __DelegateForwardConstIterablePrimitiveClient <
                    __ReceiverType,
                    __ElementType,
                    __bidirectional
            > :: end () const noexcept -> ConstIterator {

                /* end const is cend */
                return this->cend();
            }


            template <
                    typename __ReceiverType,            /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ElementType,             /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    bool     __bidirectional            /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > __CDS_OptimalInline auto __DelegateForwardConstIterablePrimitiveClient <
                    __ReceiverType,
                    __ElementType,
                    __bidirectional
            > :: cbegin () const noexcept -> ConstIterator {

                using __ReceiverBeginHandlerType    = cds :: functional :: MapperFunction < __AbstractDelegateIterator < __ElementType const > *, __ReceiverType const * >;
                auto const pReceiver                = reinterpret_cast < __ReceiverType const * > ( this );

                /* Construct a ConstIterator with the current collection and the result from calling the received server member function of type __cirt_begin.
                 * Member function is acquired from the Collection Communication Channel */
                return ConstIterator (
                        pReceiver,
                        reinterpret_cast < __ReceiverBeginHandlerType > ( pReceiver->__cicchObtainGenericConstHandler ( __CollectionInternalRequestType :: __cirt_begin ) ) ( pReceiver )
                );
            }


            template <
                    typename __ReceiverType,            /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ElementType,             /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    bool     __bidirectional            /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > __CDS_OptimalInline auto __DelegateForwardConstIterablePrimitiveClient <
                    __ReceiverType,
                    __ElementType,
                    __bidirectional
            > :: cend () const noexcept -> ConstIterator {

                using __ReceiverEndHandlerType  = cds :: functional :: MapperFunction < __AbstractDelegateIterator < __ElementType const > *, __ReceiverType const * >;
                auto const pReceiver            = reinterpret_cast < __ReceiverType const * > ( this );

                /* Construct a ConstIterator with the current collection and the result from calling the received server member function of type __cirt_end.
                 * Member function is acquired from the Collection Communication Channel */

                /* Construct a ConstIterator with the current collection and the result from calling the received server member function of type __cirt_begin.
                 * Member function is acquired from the Collection Communication Channel */
                return ConstIterator (
                        pReceiver,
                        reinterpret_cast < __ReceiverEndHandlerType > ( pReceiver->__cicchObtainGenericConstHandler ( __CollectionInternalRequestType :: __cirt_end ) ) ( pReceiver )
                );
            }


            template <
                    typename __ReceiverType,        /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ConstIteratorType    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > constexpr auto __LocalDelegateForwardConstIterablePrimitiveClient <
                    __ReceiverType,
                    __ConstIteratorType
            > :: begin () const noexcept -> ConstIterator {

                return __ReceiverType :: __cbeginLocal (
                        reinterpret_cast < __ReceiverType const * > ( this )
                );
            }


            template <
                    typename __ReceiverType,        /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ConstIteratorType    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > constexpr auto __LocalDelegateForwardConstIterablePrimitiveClient <
                    __ReceiverType,
                    __ConstIteratorType
            > :: end () const noexcept -> ConstIterator {

                return __ReceiverType :: __cendLocal (
                        reinterpret_cast < __ReceiverType const * > ( this )
                );
            }


            template <
                    typename __ReceiverType,        /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ConstIteratorType    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > constexpr auto __LocalDelegateForwardConstIterablePrimitiveClient <
                    __ReceiverType,
                    __ConstIteratorType
            > :: cbegin () const noexcept -> ConstIterator {

                return __ReceiverType :: __cbeginLocal (
                        reinterpret_cast < __ReceiverType const * > ( this )
                );
            }


            template <
                    typename __ReceiverType,        /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ConstIteratorType    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > constexpr auto __LocalDelegateForwardConstIterablePrimitiveClient <
                    __ReceiverType,
                    __ConstIteratorType
            > :: cend () const noexcept -> ConstIterator {

                return __ReceiverType :: __cendLocal (
                        reinterpret_cast < __ReceiverType const * > ( this )
                );
            }

        } /* namespace __impl */
    } /* namespace __hidden */
} /* namespace cds */

#endif /* __CDS_SHARED_DELEGATE_FORWARD_CONST_ITERABLE_PRIMITIVE_CLIENT_IMPL_HPP__ */
