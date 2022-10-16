/*
 * Created by loghin on 6/26/22.
 */

#ifndef __CDS_SHARED_CONST_ITERATOR_REMOVE_PRIMITIVE_CLIENT_IMPL_HPP__ /* NOLINT(llvm-header-guard) */
#define __CDS_SHARED_CONST_ITERATOR_REMOVE_PRIMITIVE_CLIENT_IMPL_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

namespace cds {             /* NOLINT(modernize-concat-nested-namespaces) */
    namespace __hidden {    /* NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        namespace __impl {  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            template <
                    typename __ReceiverType,                /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ElementType                  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > auto __AbstractConstIteratorRemovePrimitiveClient <
                    __ReceiverType,
                    __ElementType
            > :: remove (
                    AbstractConstIterator const & iterator
            ) noexcept -> bool {

                using __ReceiverRemoveConstIteratorHandlerType  = bool ( __ReceiverType :: * ) ( __GenericIterator );
                auto pReceiver                                  = reinterpret_cast < __ReceiverType * > ( this );

                /* Since iterator is abstract, it is compatible with Collection Ownership -> has 'of' function. Check for ownership. If not owned, removal unsuccessful */
                if ( ! iterator.of ( pReceiver ) ) {
                    return false;
                }

                /* Acquire the member function to call from client and call it with extracted delegate as parameter, return value received from the call */
                return (
                        pReceiver ->* reinterpret_cast < __ReceiverRemoveConstIteratorHandlerType > (
                                pReceiver->__cicch_obtainGenericHandler (
                                        __CollectionInternalRequestType :: __cirt_removeConst
                                )
                        )
                ) (
                        iterator._pDelegate->iterator()
                );
            }


            template <
                    typename __ReceiverType,                /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ElementType                  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > auto __AbstractConstIteratorRemovePrimitiveClient <
                    __ReceiverType,
                    __ElementType
            > :: removeAll (
                    AbstractConstIterator const * pIterators,
                    Size                          iteratorCount
            ) noexcept -> Size {

                using __ReceiverRemoveConstIteratorArrayHandlerType = Size ( __ReceiverType :: * ) ( __GenericIterator const *, Size );
                using __ReceiverRemoveConstIteratorHandlerType      = bool ( __ReceiverType :: * ) ( __GenericIterator );

                auto pReceiver                  = reinterpret_cast < __ReceiverType * > ( this );
                auto genericIteratorArray       = cds :: __hidden :: __impl :: __allocation :: __allocPrimitiveArray < __GenericIterator > ( iteratorCount );
                Size genericIteratorArraySize   = 0ULL;
                Size removedIteratorCount       = 0ULL;

                for ( Size index = 0ULL; index < iteratorCount; ++ index ) {

                    if ( ! pIterators [ index ].of ( pReceiver ) ) {
                        continue;
                    }

                    genericIteratorArray [ genericIteratorArraySize ++ ] = pIterators [ index ]._pDelegate->iterator();
                }

                if ( genericIteratorArraySize >= 2ULL ) {

                    removedIteratorCount = (
                            pReceiver ->* reinterpret_cast < __ReceiverRemoveConstIteratorArrayHandlerType > (
                                    pReceiver->__cicch_obtainGenericHandler (
                                            __CollectionInternalRequestType :: __cirt_removeConstArray
                                    )
                            )
                    ) (
                            & genericIteratorArray [0ULL],
                            genericIteratorArraySize
                    );
                } else if ( genericIteratorArraySize == 1ULL ) {

                    removedIteratorCount = (
                            pReceiver ->* reinterpret_cast < __ReceiverRemoveConstIteratorHandlerType > (
                                    pReceiver->__cicch_obtainGenericHandler (
                                            __CollectionInternalRequestType :: __cirt_removeConst
                                    )
                            )
                    ) (
                            genericIteratorArray [0ULL]
                    ) ? 1ULL : 0ULL;
                }

                cds :: __hidden :: __impl :: __allocation :: __freePrimitiveArray ( genericIteratorArray );
                return removedIteratorCount;
            }


            template <
                    typename __ReceiverType,                /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ElementType,                 /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __IteratorType                 /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > auto __LocalConstIteratorRemovePrimitiveClient <
                    __ReceiverType,
                    __ElementType,
                    __IteratorType
            > :: remove (
                    ConstIterator const & iterator
            ) noexcept -> bool {

                /* local client, directly call the dispatcher-generated function for const removal */
                return reinterpret_cast < __ReceiverType * > ( this )->__removeConst ( & iterator );
            }


            template <
                    typename __ReceiverType,                /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ElementType,                 /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __IteratorType                 /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > auto __LocalConstIteratorRemovePrimitiveClient <
                    __ReceiverType,
                    __ElementType,
                    __IteratorType
            > :: removeAll (
                    ConstIterator   const * pIterators,
                    Size                    iteratorCount
            ) noexcept -> Size {

                auto pReceiver = reinterpret_cast < __ReceiverType * > ( this );
                if ( iteratorCount >= 2ULL ) {

                    return pReceiver->__removeConstArray (
                            & pIterators [0ULL],
                            iteratorCount
                    );

                } else if ( iteratorCount == 1ULL ) {

                    return pReceiver->__removeConst (
                            pIterators [0ULL]
                    ) ? 1ULL : 0ULL;
                }

                return 0ULL;
            }

        } /* namespace __impl */
    } /* namespace __hidden */
} /* namespace cds */

#endif /* __CDS_SHARED_CONST_ITERATOR_REMOVE_PRIMITIVE_CLIENT_IMPL_HPP__ */
