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

                    __CollectionInternalRequest const request {
                        __CollectionInternalRequestType :: __cirt_removeConst,
                        reinterpret_cast < void const * > ( & iterator )
                    };

                    __CollectionInternalRequestResponse response; // NOLINT(cppcoreguidelines-pro-type-member-init)

                    auto const requestAvailabilityStatus = static_cast < __ReceiverType * > ( this )->__cicch_transmitRequest (
                            & request,
                            & response
                    );

                    return requestAvailabilityStatus && response._status;
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

                    __CollectionInternalRequest request {
                            __CollectionInternalRequestType :: __cirt_removeConst,
                            nullptr
                    };

                    __CollectionInternalRequestResponse response; // NOLINT(cppcoreguidelines-pro-type-member-init)
                    Size                                removedCount = 0ULL;

                    for ( Size index = 0ULL; index < iteratorCount; ++ index ) {

                        request._pData = reinterpret_cast < void const * > ( & pIterators [ index ] );
                        auto const requestAvailabilityStatus = static_cast < __ReceiverType * > ( this )->__cicch_transmitRequest (
                                & request,
                                & response
                        );

                        if ( requestAvailabilityStatus && response._status ) {
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
