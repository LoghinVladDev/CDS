//
// Created by loghin on 6/26/22.
//

#ifndef __CDS_SHARED_COLLECTION_INTERNAL_REQUEST_RESPONSE_HPP__
#define __CDS_SHARED_COLLECTION_INTERNAL_REQUEST_RESPONSE_HPP__

namespace cds {                 // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {    // NOLINT(modernize-concat-nested-namespaces)
        namespace __hidden {    // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier)
            namespace __impl {  // NOLINT(bugprone-reserved-identifier)

                struct __CollectionInternalRequestResponse { // NOLINT(bugprone-reserved-identifier)
                    bool    _status;
                    void  * _pData;
                };

                struct __CollectionInternalRequestResponseInsert { // NOLINT(bugprone-reserved-identifier)
                    bool    _successful;
                    void  * _pElement;
                };

            }
        }
    }
}

#endif // __CDS_SHARED_COLLECTION_INTERNAL_REQUEST_RESPONSE_HPP__
