/*
 * Created by loghin on 6/26/22.
 */

#ifndef __CDS_SHARED_ITERATOR_REMOVE_PRIMITIVE_CLIENT_IMPL_HPP__ 
#define __CDS_SHARED_ITERATOR_REMOVE_PRIMITIVE_CLIENT_IMPL_HPP__ /* NOLINT(bugprone-reserved-identifier) */

namespace cds {                 /* NOLINT(modernize-concat-nested-namespaces) */
    namespace experimental {    /* NOLINT(modernize-concat-nested-namespaces) */
        namespace __hidden {    /* NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier) */
            namespace __impl {  /* NOLINT(bugprone-reserved-identifier) */

                template <
                        typename __ReceiverType,                /* NOLINT(bugprone-reserved-identifier) */
                        typename __ElementType                  /* NOLINT(bugprone-reserved-identifier) */
                > auto __AbstractIteratorRemovePrimitiveClient <
                        __ReceiverType,
                        __ElementType
                > :: remove (
                        AbstractIterator const & iterator
                ) noexcept -> bool {

                    using __ReceiverRemoveIteratorHandlerType   = bool ( __ReceiverType :: * ) ( __GenericIterator );
                    auto pReceiver                              = reinterpret_cast < __ReceiverType * > ( this );

                    /* Since iterator is abstract, it is compatible with Collection Ownership -> has 'of' function. Check for ownership. If not owned, removal unsuccessful */
                    if ( ! iterator.of ( pReceiver ) ) {
                        return false;
                    }

                    /* Acquire the member function to call from client and call it with extracted delegate as parameter, return value received from the call */
                    return (
                            pReceiver ->* reinterpret_cast < __ReceiverRemoveIteratorHandlerType > (
                                    pReceiver->__cicch_obtainGenericHandler (
                                            __CollectionInternalRequestType :: __cirt_remove
                                    )
                            )
                    ) (
                            iterator._pDelegate->iterator()
                    );
                }


                template <
                        typename __ReceiverType,                /* NOLINT(bugprone-reserved-identifier) */
                        typename __ElementType                  /* NOLINT(bugprone-reserved-identifier) */
                > auto __AbstractIteratorRemovePrimitiveClient <
                        __ReceiverType,
                        __ElementType
                > :: removeAll (
                        AbstractIterator const * pIterators,
                        Size                     iteratorCount
                ) noexcept -> Size {

                    using __ReceiverRemoveIteratorArrayHandlerType  = Size ( __ReceiverType :: * ) ( __GenericIterator const *, Size );
                    using __ReceiverRemoveIteratorHandlerType       = bool ( __ReceiverType :: * ) ( __GenericIterator );

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
                                pReceiver ->* reinterpret_cast < __ReceiverRemoveIteratorArrayHandlerType > (
                                        pReceiver->__cicch_obtainGenericHandler (
                                                __CollectionInternalRequestType :: __cirt_removeArray
                                        )
                                )
                        ) (
                                & genericIteratorArray [0ULL],
                                genericIteratorArraySize
                        );
                    } else if ( genericIteratorArraySize == 1ULL ) {

                        removedIteratorCount = (
                                pReceiver ->* reinterpret_cast < __ReceiverRemoveIteratorHandlerType > (
                                        pReceiver->__cicch_obtainGenericHandler (
                                                __CollectionInternalRequestType :: __cirt_remove
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
                        typename __ReceiverType,                /* NOLINT(bugprone-reserved-identifier) */
                        typename __ElementType,                 /* NOLINT(bugprone-reserved-identifier) */
                        typename __IteratorType                 /* NOLINT(bugprone-reserved-identifier) */
                > auto __LocalIteratorRemovePrimitiveClient <
                        __ReceiverType,
                        __ElementType,
                        __IteratorType
                > :: remove (
                        Iterator const & iterator
                ) noexcept -> bool {

                    /* local client, directly call the dispatcher-generated function for const removal */
                    return reinterpret_cast < __ReceiverType * > ( this )->__remove ( & iterator );
                }


                template <
                        typename __ReceiverType,                /* NOLINT(bugprone-reserved-identifier) */
                        typename __ElementType,                 /* NOLINT(bugprone-reserved-identifier) */
                        typename __IteratorType                 /* NOLINT(bugprone-reserved-identifier) */
                > auto __LocalIteratorRemovePrimitiveClient <
                        __ReceiverType,
                        __ElementType,
                        __IteratorType
                > :: removeAll (
                        Iterator const * pIterators,
                        Size             iteratorCount
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

            }
        }
    }
}

#endif /* __CDS_SHARED_ITERATOR_REMOVE_PRIMITIVE_CLIENT_IMPL_HPP__ */
