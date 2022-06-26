//
// Created by loghin on 6/26/22.
//

#ifndef __CDS_SHARED_DELEGATE_ITERABLE_RESPONSE_HPP__
#define __CDS_SHARED_DELEGATE_ITERABLE_RESPONSE_HPP__

namespace cds {                 // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {    // NOLINT(modernize-concat-nested-namespaces)
        namespace __hidden {    // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier)
            namespace __impl {  // NOLINT(bugprone-reserved-identifier)

                struct __DelegateIterableResponse { // NOLINT(bugprone-reserved-identifier)
                    bool    _status;
                    void  * _pData;
                };

            }
        }
    }
}

#endif // __CDS_SHARED_DELEGATE_ITERABLE_RESPONSE_HPP__
