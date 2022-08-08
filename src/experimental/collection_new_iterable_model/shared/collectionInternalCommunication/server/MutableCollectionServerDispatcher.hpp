//
// Created by loghin on 09/07/22.
//

#ifndef __CDS_SHARED_MUTABLE_COLLECTION_SERVER_DISPATCHER_HPP__
#define __CDS_SHARED_MUTABLE_COLLECTION_SERVER_DISPATCHER_HPP__

#include "CollectionServerDispatcher.hpp"

namespace cds {                 // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {    // NOLINT(modernize-concat-nested-namespaces)
        namespace __hidden {    // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier)
            namespace __impl {  // NOLINT(bugprone-reserved-identifier)

                template <
                        typename __ServerType,                                                                                      // NOLINT(bugprone-reserved-identifier)
                        typename __ServiceType,                                                                                     // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType,                                                                                     // NOLINT(bugprone-reserved-identifier)
                        typename __IteratorType,                                                                                    // NOLINT(bugprone-reserved-identifier)
                        typename __ConstIteratorType,                                                                               // NOLINT(bugprone-reserved-identifier)
                        auto ( __ServiceType :: * __newAddressFunction )    ( __ElementType const *, bool * )   -> __ElementType *, // NOLINT(bugprone-reserved-identifier)
                        auto ( __ServiceType :: * __removeFunction )        ( __IteratorType const & )          -> bool,            // NOLINT(bugprone-reserved-identifier)
                        auto ( __ServiceType :: * __removeConstFunction )   ( __ConstIteratorType const & )     -> bool             // NOLINT(bugprone-reserved-identifier)
                > class __MutableCollectionServerDispatcher :                                                                       // NOLINT(bugprone-reserved-identifier)
                        public __CollectionServerDispatcher <
                                __ServerType,
                                __ServiceType,
                                __ElementType,
                                __ConstIteratorType,
                                __newAddressFunction,
                                __removeConstFunction
                        > {

                protected:
                    auto __remove ( // NOLINT(bugprone-reserved-identifier)
                            __IteratorType const * pIterator
                    ) noexcept -> bool;
                };

            }
        }
    }
}

#endif // __CDS_SHARED_MUTABLE_COLLECTION_SERVER_DISPATCHER_HPP__
