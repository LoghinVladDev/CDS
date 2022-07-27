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
                        typename __ServerType,                                                                                              // NOLINT(bugprone-reserved-identifier)
                        typename __ServiceType,                                                                                             // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType,                                                                                             // NOLINT(bugprone-reserved-identifier)
                        typename __ConstIteratorType,                                                                                       // NOLINT(bugprone-reserved-identifier)
                        __ElementType * ( __ServiceType :: *  __newAddressFunction ) ( __ElementType const *, bool * ),                     // NOLINT(bugprone-reserved-identifier)
                        bool ( __ServiceType :: * __removeConstFunction ) ( __ConstIteratorType const & )                                   // NOLINT(bugprone-reserved-identifier)
                > class __SetServerDispatcher :
                        public __CollectionServerDispatcher <
                                __ServerType,
                                __ServiceType,
                                __ElementType,
                                __ConstIteratorType,
                                __newAddressFunction,
                                __removeConstFunction
                        > {

                };

            }
        }
    }
}

#endif // __CDS_SHARED_SET_SERVER_DISPATCHER_HPP__
