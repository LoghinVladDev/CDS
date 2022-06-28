//
// Created by loghin on 6/26/22.
//

#ifndef __CDS_SHARED_COLLECTION_INTERNAL_REQUEST_HPP__
#define __CDS_SHARED_COLLECTION_INTERNAL_REQUEST_HPP__

#include "CollectionInternalRequestType.hpp"

namespace cds {                 // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {    // NOLINT(modernize-concat-nested-namespaces)
        namespace __hidden {    // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier)
            namespace __impl {  // NOLINT(bugprone-reserved-identifier)

                struct __CollectionInternalRequest { // NOLINT(bugprone-reserved-identifier)
                    __CollectionInternalRequestType         _type;
                    void                            const * _pData;
                };

            }
        }
    }
}

#endif // __CDS_SHARED_COLLECTION_INTERNAL_REQUEST_HPP__
