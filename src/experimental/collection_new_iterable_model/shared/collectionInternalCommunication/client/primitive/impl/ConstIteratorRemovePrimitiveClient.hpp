/*
 * Created by loghin on 6/26/22.
 */

#ifndef __CDS_SHARED_CONST_ITERATOR_REMOVE_PRIMITIVE_CLIENT_IMPL_HPP__
#define __CDS_SHARED_CONST_ITERATOR_REMOVE_PRIMITIVE_CLIENT_IMPL_HPP__ /* NOLINT(bugprone-reserved-identifier) */

namespace cds {                 /* NOLINT(modernize-concat-nested-namespaces) */
    namespace experimental {    /* NOLINT(modernize-concat-nested-namespaces) */
        namespace __hidden {    /* NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier) */
            namespace __impl {  /* NOLINT(bugprone-reserved-identifier) */

                template <
                        typename __ReceiverType,                /* NOLINT(bugprone-reserved-identifier) */
                        typename __ElementType                  /* NOLINT(bugprone-reserved-identifier) */
                > auto __AbstractConstIteratorRemovePrimitiveClient <
                        __ReceiverType,
                        __ElementType
                > :: remove (
                        AbstractConstIterator const & iterator
                ) noexcept -> bool {

                    /* Since iterator is abstract, it is compatible with Collection Ownership -> has 'of' function. Check for ownership. If not owned, removal unsuccessful */
                    if ( ! iterator.of ( reinterpret_cast < __ReceiverType const * > ( this ) ) ) {
                        return false;
                    }

                    /* Acquire the member function to call from client and call it with extracted delegate as parameter, return value received from the call */
                    return (
                            reinterpret_cast < __ReceiverType * > ( this )->*
                            reinterpret_cast <
                                    bool ( __ReceiverType :: * ) (
                                            __GenericIterator
                                    )
                            > (
                                    reinterpret_cast < __ReceiverType * > ( this )->__cicch_obtainGenericHandler (
                                            __CollectionInternalRequestType :: __cirt_removeConst
                                    )
                            )
                    ) (
                            iterator._pDelegate->iterator()
                    );
                }


                template <
                        typename __ReceiverType,                /* NOLINT(bugprone-reserved-identifier) */
                        typename __ElementType                  /* NOLINT(bugprone-reserved-identifier) */
                > auto __AbstractConstIteratorRemovePrimitiveClient <
                        __ReceiverType,
                        __ElementType
                > :: removeAll (
                        AbstractConstIterator const * pIterators,
                        Size                          iteratorCount
                ) noexcept -> Size {

                    /* keep count of the number of successful removals */
                    Size removedCount   = 0ULL;

                    /* acquire the function pointer of the remove function */
                    auto pfnRemove      =
                            reinterpret_cast <
                                    bool ( __ReceiverType :: * ) (
                                            __GenericIterator
                                    )
                            > (
                                    reinterpret_cast < __ReceiverType * > ( this )->__cicch_obtainGenericHandler (
                                            __CollectionInternalRequestType :: __cirt_removeConst
                                    )
                            );

                    /* parse received iterator array */
                    for ( Size index = 0ULL; index < iteratorCount; ++ index ) {

                        /* Since iterator is abstract, it is compatible with Collection Ownership -> has 'of' function. Check for ownership. If not owned, move on to the next */
                        if ( ! pIterators [ index ].of ( reinterpret_cast < __ReceiverType const * > ( this ) ) ) {
                            continue;
                        }

                        /* call member function with extracted delegate as parameter. If removal successful, increase counter */
                        if ( ( reinterpret_cast < __ReceiverType * > ( this ) ->* pfnRemove ) ( pIterators [ index ]._pDelegate->iterator() ) ) {
                            removedCount ++;
                        }
                    }

                    return removedCount;
                }


                template <
                        typename __ReceiverType,                /* NOLINT(bugprone-reserved-identifier) */
                        typename __ElementType,                 /* NOLINT(bugprone-reserved-identifier) */
                        typename __IteratorType                 /* NOLINT(bugprone-reserved-identifier) */
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
                        typename __ReceiverType,                /* NOLINT(bugprone-reserved-identifier) */
                        typename __ElementType,                 /* NOLINT(bugprone-reserved-identifier) */
                        typename __IteratorType                 /* NOLINT(bugprone-reserved-identifier) */
                > auto __LocalConstIteratorRemovePrimitiveClient <
                        __ReceiverType,
                        __ElementType,
                        __IteratorType
                > :: removeAll (
                        ConstIterator   const * pIterators,
                        Size                    iteratorCount
                ) noexcept -> Size {

                    /* keep count of the number of successful removals */
                    Size removedCount   = 0ULL;

                    /* acquire the function pointer of the remove function. Local client -> acquire dispatcher-generated function */
                    auto pfnRemove      = & __ReceiverType :: __removeConst;

                    /* parse received iterator array */
                    for ( Size index = 0ULL; index < iteratorCount; ++ index ) {

                        /* call member function. If removal successful, increase counter */
                        if ( ( reinterpret_cast < __ReceiverType * > ( this ) ->* pfnRemove ) ( & pIterators [ index ] ) ) {
                            removedCount ++;
                        }
                    }

                    return removedCount;
                }

            }
        }
    }
}

#endif /* __CDS_SHARED_CONST_ITERATOR_REMOVE_PRIMITIVE_CLIENT_IMPL_HPP__ */
