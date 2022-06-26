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

                    __DelegateIterableRequest request {
                            __DelegateIterableRequestType :: __dirt_remove,
                            reinterpret_cast < void const * > ( & iterator )
                    };

                    __DelegateIterableResponse response; // NOLINT(cppcoreguidelines-pro-type-member-init)

                    auto const requestAvailabilityStatus = static_cast < __ReceiverType * > ( this )->__dich_transmitRequest (
                            & request,
                            & response
                    );

                    return requestAvailabilityStatus && response._status;
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

                    __DelegateIterableRequest request {
                            __DelegateIterableRequestType :: __dirt_remove,
                            nullptr
                    };

                    __DelegateIterableResponse response; // NOLINT(cppcoreguidelines-pro-type-member-init)
                    Size                       removedCount = 0ULL;

                    for ( Size index = 0ULL; index < iteratorCount; ++ index ) {

                        request._pData = reinterpret_cast < void const * > ( & pIterators [ index ] );
                        auto const requestAvailabilityStatus = static_cast < __ReceiverType * > ( this )->__dich_transmitRequest (
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

#endif // __CDS_SHARED_ABSTRACT_ITERATOR_REMOVE_CLIENT_IMPL_HPP__
