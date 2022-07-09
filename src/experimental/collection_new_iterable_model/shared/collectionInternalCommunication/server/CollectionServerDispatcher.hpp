//
// Created by loghin on 09/07/22.
//

#ifndef __CDS_SHARED_COLLECTION_SERVER_DISPATCHER_HPP__
#define __CDS_SHARED_COLLECTION_SERVER_DISPATCHER_HPP__

namespace cds {                 // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {    // NOLINT(modernize-concat-nested-namespaces)
        namespace __hidden {    // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier)
            namespace __impl {  // NOLINT(bugprone-reserved-identifier)

                template <
                        typename __ServerType,                                                                          // NOLINT(bugprone-reserved-identifier)
                        typename __ServiceType,                                                                         // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType,                                                                         // NOLINT(bugprone-reserved-identifier)
                        typename __ConstIteratorType,                                                                   // NOLINT(bugprone-reserved-identifier)
                        __ElementType * ( __ServiceType :: *  __newAddressFunction ) ( __ElementType const *, bool * ), // NOLINT(bugprone-reserved-identifier)
                        bool ( __ServiceType :: * __removeConstFunction ) ( __ConstIteratorType const & )               // NOLINT(bugprone-reserved-identifier)
                > class __CollectionServerDispatcher {                                                                  // NOLINT(bugprone-reserved-identifier)

                protected:
                    auto __newAddress ( // NOLINT(bugprone-reserved-identifier)
                            __ElementType const * pReferenceElement,
                            bool                * pNewElementCreated
                    ) noexcept -> __ElementType *;

                protected:
                    auto __removeConst ( // NOLINT(bugprone-reserved-identifier)
                            __ConstIteratorType const * pIterator
                    ) noexcept -> bool;
                };

            }
        }
    }
}

#endif // __CDS_SHARED_COLLECTION_SERVER_DISPATCHER_HPP__
