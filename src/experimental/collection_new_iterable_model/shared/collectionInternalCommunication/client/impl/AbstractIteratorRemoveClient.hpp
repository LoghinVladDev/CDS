//
// Created by loghin on 6/26/22.
//

#ifndef __CDS_SHARED_ABSTRACT_ITERATOR_REMOVE_CLIENT_IMPL_HPP__
#define __CDS_SHARED_ABSTRACT_ITERATOR_REMOVE_CLIENT_IMPL_HPP__

namespace cds {                 // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {    // NOLINT(modernize-concat-nested-namespaces)
        namespace __hidden {    // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier)
            namespace __impl {  // NOLINT(bugprone-reserved-identifier)

                template < typename __ElementType >         // NOLINT(bugprone-reserved-identifier)
                class __AbstractDelegateWrapperIterator;    // NOLINT(bugprone-reserved-identifier)

                template <
                        typename __ReceiverType,                // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType                  // NOLINT(bugprone-reserved-identifier)
                > auto __AbstractIteratorRemoveClient <
                        __ReceiverType,
                        __ElementType
                > :: remove (
                        AbstractIterator const & iterator
                ) noexcept -> bool {

                    return (
                            static_cast < __ReceiverType * > ( this )->*
                            reinterpret_cast <
                                    bool ( __ReceiverType :: * ) (
                                            __AbstractDelegateIterator < __ElementType > const *
                                    )
                            > (
                                    static_cast < __ReceiverType * > ( this )->__cicch_obtainGenericHandler (
                                            __CollectionInternalRequestType :: __cirt_remove
                                    )
                            )
                    ) (
                            iterator._pDelegate
                    );
                }


                template <
                        typename __ReceiverType,                // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType                  // NOLINT(bugprone-reserved-identifier)
                > auto __AbstractIteratorRemoveClient <
                        __ReceiverType,
                        __ElementType
                > :: removeAll (
                        AbstractIterator const * pIterators,
                        Size                     iteratorCount
                ) noexcept -> Size {

                    Size removedCount   = 0ULL;
                    auto pfnRemove      =
                            reinterpret_cast <
                                    bool ( __ReceiverType :: * ) (
                                            __AbstractDelegateIterator < __ElementType > const *
                                    )
                            > (
                                    static_cast < __ReceiverType * > ( this )->__cicch_obtainGenericHandler (
                                            __CollectionInternalRequestType :: __cirt_remove
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

#endif // __CDS_SHARED_ABSTRACT_ITERATOR_REMOVE_CLIENT_IMPL_HPP__
