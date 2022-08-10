//
// Created by loghin on 09/07/22.
//

#ifndef __CDS_SHARED_MAP_SERVER_DISPATCHER_IMPL_HPP__
#define __CDS_SHARED_MAP_SERVER_DISPATCHER_IMPL_HPP__

#include "MutableCollectionServerDispatcher.hpp"

namespace cds {                 // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {    // NOLINT(modernize-concat-nested-namespaces)
        namespace __hidden {    // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier)
            namespace __impl {  // NOLINT(bugprone-reserved-identifier)

                template <
                        typename __ServerType,                                                                                          // NOLINT(bugprone-reserved-identifier)
                        typename __ServiceType,                                                                                         // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType,                                                                                         // NOLINT(bugprone-reserved-identifier)
                        typename __KeyType,                                                                                             // NOLINT(bugprone-reserved-identifier)
                        typename __IteratorType,                                                                                        // NOLINT(bugprone-reserved-identifier)
                        typename __ConstIteratorType,                                                                                   // NOLINT(bugprone-reserved-identifier)
                        auto ( __ServiceType :: * __newAddressFunction )    ( __ElementType const *, bool * )   -> __ElementType *,     // NOLINT(bugprone-reserved-identifier)
                        auto ( __ServiceType :: * __removeFunction )        ( __IteratorType const & )          -> bool,                // NOLINT(bugprone-reserved-identifier)
                        auto ( __ServiceType :: * __removeConstFunction )   ( __ConstIteratorType const & )     -> bool,                // NOLINT(bugprone-reserved-identifier)
                        auto ( __ServiceType :: * __findFunction )          ( __KeyType const & )               -> __IteratorType,      // NOLINT(bugprone-reserved-identifier)
                        auto ( __ServiceType :: * __findConstFunction )     ( __KeyType const & ) const         -> __ConstIteratorType  // NOLINT(bugprone-reserved-identifier)
                > __CDS_OptimalInline auto __MapServerDispatcher <
                        __ServerType,
                        __ServiceType,
                        __ElementType,
                        __KeyType,
                        __IteratorType,
                        __ConstIteratorType,
                        __newAddressFunction,
                        __removeFunction,
                        __removeConstFunction,
                        __findFunction,
                        __findConstFunction
                > :: __find (
                        __KeyType const & key
                ) noexcept -> __IteratorType {

                    return ( reinterpret_cast < __ServerType * > ( this ) ->* __findFunction ) (
                            key
                    );
                }


                template <
                        typename __ServerType,                                                                                          // NOLINT(bugprone-reserved-identifier)
                        typename __ServiceType,                                                                                         // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType,                                                                                         // NOLINT(bugprone-reserved-identifier)
                        typename __KeyType,                                                                                             // NOLINT(bugprone-reserved-identifier)
                        typename __IteratorType,                                                                                        // NOLINT(bugprone-reserved-identifier)
                        typename __ConstIteratorType,                                                                                   // NOLINT(bugprone-reserved-identifier)
                        auto ( __ServiceType :: * __newAddressFunction )    ( __ElementType const *, bool * )   -> __ElementType *,     // NOLINT(bugprone-reserved-identifier)
                        auto ( __ServiceType :: * __removeFunction )        ( __IteratorType const & )          -> bool,                // NOLINT(bugprone-reserved-identifier)
                        auto ( __ServiceType :: * __removeConstFunction )   ( __ConstIteratorType const & )     -> bool,                // NOLINT(bugprone-reserved-identifier)
                        auto ( __ServiceType :: * __findFunction )          ( __KeyType const & )               -> __IteratorType,      // NOLINT(bugprone-reserved-identifier)
                        auto ( __ServiceType :: * __findConstFunction )     ( __KeyType const & ) const         -> __ConstIteratorType  // NOLINT(bugprone-reserved-identifier)
                > __CDS_OptimalInline auto __MapServerDispatcher <
                        __ServerType,
                        __ServiceType,
                        __ElementType,
                        __KeyType,
                        __IteratorType,
                        __ConstIteratorType,
                        __newAddressFunction,
                        __removeFunction,
                        __removeConstFunction,
                        __findFunction,
                        __findConstFunction
                > :: __findConst (
                        __KeyType const & key
                ) const noexcept -> __ConstIteratorType {

                    return ( reinterpret_cast < __ServerType const * > ( this ) ->* __findConstFunction ) (
                            key
                    );
                }

            }
        }
    }
}

#endif // __CDS_SHARED_MAP_SERVER_DISPATCHER_IMPL_HPP__
