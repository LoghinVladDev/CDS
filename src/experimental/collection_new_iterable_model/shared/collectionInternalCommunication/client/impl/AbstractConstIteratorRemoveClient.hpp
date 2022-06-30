//
// Created by loghin on 6/26/22.
//

#ifndef __CDS_SHARED_ABSTRACT_CONST_ITERATOR_REMOVE_CLIENT_IMPL_HPP__
#define __CDS_SHARED_ABSTRACT_CONST_ITERATOR_REMOVE_CLIENT_IMPL_HPP__

namespace cds {                 // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {    // NOLINT(modernize-concat-nested-namespaces)
        namespace __hidden {    // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier)
            namespace __impl {  // NOLINT(bugprone-reserved-identifier)

                template < typename __ElementType >         // NOLINT(bugprone-reserved-identifier)
                class __AbstractDelegateWrapperIterator;    // NOLINT(bugprone-reserved-identifier)

                template <
                        typename __ReceiverType,                // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType                  // NOLINT(bugprone-reserved-identifier)
                > auto __AbstractConstIteratorRemoveClient <
                        __ReceiverType,
                        __ElementType
                > :: remove (
                        AbstractConstIterator const & iterator
                ) noexcept -> bool {

                    return (
                            static_cast < __ReceiverType * > ( this )->*
                            reinterpret_cast <
                                    bool ( __ReceiverType :: * ) (
                                            __AbstractDelegateIterator < __ElementType const > const *
                                    )
                            > (
                                    static_cast < __ReceiverType * > ( this )->__cicch_obtainGenericHandler (
                                            __CollectionInternalRequestType :: __cirt_removeConst
                                    )
                            )
                    ) (
                            iterator._pDelegate
                    );
                }


                template <
                        typename __ReceiverType,                // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType                  // NOLINT(bugprone-reserved-identifier)
                > auto __AbstractConstIteratorRemoveClient <
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
                                            __AbstractDelegateIterator < __ElementType const > const *
                                    )
                            > (
                                    static_cast < __ReceiverType * > ( this )->__cicch_obtainGenericHandler (
                                            __CollectionInternalRequestType :: __cirt_removeConst
                                    )
                            );

                    for ( Size index = 0ULL; index < iteratorCount; ++ index ) {
                        if ( ( static_cast < __ReceiverType * > ( this ) ->* pfnRemove ) ( pIterators [ index ]._pDelegate ) ) {
                            removedCount ++;
                        }
                    }

                    return removedCount;
                }

            }
        }
    }
}

#endif // __CDS_SHARED_ABSTRACT_CONST_ITERATOR_REMOVE_CLIENT_IMPL_HPP__
