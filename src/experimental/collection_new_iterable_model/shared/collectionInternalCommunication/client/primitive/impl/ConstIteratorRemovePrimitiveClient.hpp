//
// Created by loghin on 6/26/22.
//

#ifndef __CDS_SHARED_CONST_ITERATOR_REMOVE_PRIMITIVE_CLIENT_IMPL_HPP__
#define __CDS_SHARED_CONST_ITERATOR_REMOVE_PRIMITIVE_CLIENT_IMPL_HPP__

namespace cds {                 // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {    // NOLINT(modernize-concat-nested-namespaces)
        namespace __hidden {    // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier)
            namespace __impl {  // NOLINT(bugprone-reserved-identifier)

                template <
                        typename __ReceiverType,                // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType                  // NOLINT(bugprone-reserved-identifier)
                > auto __AbstractConstIteratorRemovePrimitiveClient <
                        __ReceiverType,
                        __ElementType
                > :: remove (
                        AbstractConstIterator const & iterator
                ) noexcept -> bool {

                    if ( ! iterator.of ( reinterpret_cast < __ReceiverType const * > ( this ) ) ) {
                        return false;
                    }

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
                        typename __ReceiverType,                // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType                  // NOLINT(bugprone-reserved-identifier)
                > auto __AbstractConstIteratorRemovePrimitiveClient <
                        __ReceiverType,
                        __ElementType
                > :: removeAll (
                        AbstractConstIterator const * pIterators,
                        Size                          iteratorCount
                ) noexcept -> Size {

                    Size removedCount   = 0ULL;
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

                    for ( Size index = 0ULL; index < iteratorCount; ++ index ) {

                        if ( ! pIterators [ index ].of ( reinterpret_cast < __ReceiverType const * > ( this ) ) ) {
                            continue;
                        }

                        if ( ( reinterpret_cast < __ReceiverType * > ( this ) ->* pfnRemove ) ( pIterators [ index ]._pDelegate->iterator() ) ) {
                            removedCount ++;
                        }
                    }

                    return removedCount;
                }


                template <
                        typename __ReceiverType,                // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType,                 // NOLINT(bugprone-reserved-identifier)
                        typename __IteratorType                 // NOLINT(bugprone-reserved-identifier)
                > auto __LocalConstIteratorRemovePrimitiveClient <
                        __ReceiverType,
                        __ElementType,
                        __IteratorType
                > :: remove (
                        ConstIterator const & iterator
                ) noexcept -> bool {

                    return reinterpret_cast < __ReceiverType * > ( this )->__removeConst ( & iterator );
                }


                template <
                        typename __ReceiverType,                // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType,                 // NOLINT(bugprone-reserved-identifier)
                        typename __IteratorType                 // NOLINT(bugprone-reserved-identifier)
                > auto __LocalConstIteratorRemovePrimitiveClient <
                        __ReceiverType,
                        __ElementType,
                        __IteratorType
                > :: removeAll (
                        ConstIterator   const * pIterators,
                        Size                    iteratorCount
                ) noexcept -> Size {

                    Size removedCount   = 0ULL;
                    auto pfnRemove      = & __ReceiverType :: __removeConst;

                    for ( Size index = 0ULL; index < iteratorCount; ++ index ) {
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

#endif // __CDS_SHARED_CONST_ITERATOR_REMOVE_PRIMITIVE_CLIENT_IMPL_HPP__
