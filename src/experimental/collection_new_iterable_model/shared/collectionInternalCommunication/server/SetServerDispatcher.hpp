//
// Created by loghin on 24/07/22.
//

#ifndef __CDS_SHARED_SET_SERVER_DISPATCHER_HPP__
#define __CDS_SHARED_SET_SERVER_DISPATCHER_HPP__

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
                > class __SetServerDispatcher :                                                                                         // NOLINT(bugprone-reserved-identifier)
                        public __CollectionServerDispatcher <
                                __ServerType,
                                __ServiceType,
                                __ElementType,
                                __ConstIteratorType,
                                __newAddressFunction,
                                __removeConstFunction
                        > {

                protected:
                    auto __findConst ( // NOLINT(bugprone-reserved-identifier)
                            __ElementType const & element
                    ) const noexcept -> __ConstIteratorType;
                };

            }
        }
    }
}

#endif // __CDS_SHARED_SET_SERVER_DISPATCHER_HPP__

