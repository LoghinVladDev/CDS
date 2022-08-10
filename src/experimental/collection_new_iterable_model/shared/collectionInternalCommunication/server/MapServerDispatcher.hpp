//
// Created by loghin on 24/07/22.
//

#ifndef __CDS_SHARED_MAP_SERVER_DISPATCHER_HPP__
#define __CDS_SHARED_MAP_SERVER_DISPATCHER_HPP__

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
                > class __MapServerDispatcher :                                                                                         // NOLINT(bugprone-reserved-identifier)
                        public __MutableCollectionServerDispatcher <
                                __ServerType,
                                __ServiceType,
                                __ElementType,
                                __IteratorType,
                                __ConstIteratorType,
                                __newAddressFunction,
                                __removeFunction,
                                __removeConstFunction
                        > {

                protected:
                    auto __find ( // NOLINT(bugprone-reserved-identifier)
                            __KeyType const & key
                    ) noexcept -> __IteratorType;

                protected:
                    auto __findConst ( // NOLINT(bugprone-reserved-identifier)
                            __KeyType const & key
                    ) const noexcept -> __ConstIteratorType;
                };

            }
        }
    }
}

#endif // __CDS_SHARED_MAP_SERVER_DISPATCHER_HPP__

