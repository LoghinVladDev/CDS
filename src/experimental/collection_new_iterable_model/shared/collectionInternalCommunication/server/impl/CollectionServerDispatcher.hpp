//
// Created by loghin on 09/07/22.
//

#ifndef __CDS_SHARED_COLLECTION_SERVER_DISPATCHER_IMPL_HPP__
#define __CDS_SHARED_COLLECTION_SERVER_DISPATCHER_IMPL_HPP__

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
                > __CDS_OptimalInline auto __CollectionServerDispatcher <
                        __ServerType,
                        __ServiceType,
                        __ElementType,
                        __ConstIteratorType,
                        __newAddressFunction,
                        __removeConstFunction
                > :: __newAddress (
                        __ElementType const * pReferenceElement,
                        bool                * pNewElementCreated
                ) noexcept -> __ElementType * {

                    return ( reinterpret_cast < __ServerType * > ( this ) ->* __newAddressFunction ) (
                            pReferenceElement,
                            pNewElementCreated
                    );
                }


                template <
                        typename __ServerType,                                                                          // NOLINT(bugprone-reserved-identifier)
                        typename __ServiceType,                                                                         // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType,                                                                         // NOLINT(bugprone-reserved-identifier)
                        typename __ConstIteratorType,                                                                   // NOLINT(bugprone-reserved-identifier)
                        __ElementType * ( __ServiceType :: *  __newAddressFunction ) ( __ElementType const *, bool * ), // NOLINT(bugprone-reserved-identifier)
                        bool ( __ServiceType :: * __removeConstFunction ) ( __ConstIteratorType const & )               // NOLINT(bugprone-reserved-identifier)
                > __CDS_OptimalInline auto __CollectionServerDispatcher <
                        __ServerType,
                        __ServiceType,
                        __ElementType,
                        __ConstIteratorType,
                        __newAddressFunction,
                        __removeConstFunction
                > :: __removeConst (
                        __ConstIteratorType const * pIterator
                ) noexcept -> bool {

                    return ( reinterpret_cast < __ServerType * > ( this ) ->* __removeConstFunction ) (
                            * pIterator
                    );
                }

            }
        }
    }
}

#endif // __CDS_SHARED_COLLECTION_SERVER_DISPATCHER_IMPL_HPP__
