//
// Created by loghin on 09/07/22.
//

#ifndef __CDS_SHARED_SET_SERVER_DISPATCHER_IMPL_HPP__
#define __CDS_SHARED_SET_SERVER_DISPATCHER_IMPL_HPP__

#include "CollectionServerDispatcher.hpp"

namespace cds {                 // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {    // NOLINT(modernize-concat-nested-namespaces)
        namespace __hidden {    // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier)
            namespace __impl {  // NOLINT(bugprone-reserved-identifier)

                template <
                        typename __ServerType,                                                                                          // NOLINT(bugprone-reserved-identifier)
                        typename __ServiceType,                                                                                         // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType,                                                                                         // NOLINT(bugprone-reserved-identifier)
                        typename __ConstIteratorType,                                                                                   // NOLINT(bugprone-reserved-identifier)
                        auto ( __ServiceType :: * __newAddressFunction )    ( __ElementType const *, bool * )   -> __ElementType *,     // NOLINT(bugprone-reserved-identifier)
                        auto ( __ServiceType :: * __removeConstFunction )   ( __ConstIteratorType const & )     -> bool,                // NOLINT(bugprone-reserved-identifier)
                        auto ( __ServiceType :: * __findConstFunction )     ( __ElementType const & ) const     -> __ConstIteratorType  // NOLINT(bugprone-reserved-identifier)
                > __CDS_OptimalInline auto __SetServerDispatcher <
                        __ServerType,
                        __ServiceType,
                        __ElementType,
                        __ConstIteratorType,
                        __newAddressFunction,
                        __removeConstFunction,
                        __findConstFunction
                > :: __findConst (
                        __ElementType const & element
                ) const noexcept -> __ConstIteratorType {

                    return ( reinterpret_cast < __ServerType const * > ( this ) ->* __findConstFunction ) (
                            element
                    );
                }

            }
        }
    }
}

#endif // __CDS_SHARED_SET_SERVER_DISPATCHER_IMPL_HPP__