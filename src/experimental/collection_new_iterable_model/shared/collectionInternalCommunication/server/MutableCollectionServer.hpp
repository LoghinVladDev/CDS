/*
 * Created by loghin on 7/3/22.
 */

#ifndef __CDS_EX_SHARED_MUTABLE_COLLECTION_SERVER_HPP__
#define __CDS_EX_SHARED_MUTABLE_COLLECTION_SERVER_HPP__ /* NOLINT(bugprone-reserved-identifier) */

#warning No longer an experimental feature. Use the non-experimental header.
#include "../../../../../shared/collectionInternalCommunication/server/MutableCollectionServer.hpp"

namespace cds {                 /* NOLINT(modernize-concat-nested-namespaces) */
    namespace experimental {    /* NOLINT(modernize-concat-nested-namespaces) */
        namespace __hidden {    /* NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier) */
            namespace __impl {  /* NOLINT(bugprone-reserved-identifier) */

                template <
                        typename __ReceiverType,                                                                /* NOLINT(bugprone-reserved-identifier) */
                        typename __ElementType                                                                  /* NOLINT(bugprone-reserved-identifier) */
                > using __MutableCollectionServer __CDS_DeprecatedHint("No longer an experimental feature.") =  /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __MutableCollectionServer < __ReceiverType, __ElementType >;

            }
        }
    }
}

#endif /* __CDS_EX_SHARED_MUTABLE_COLLECTION_SERVER_HPP__ */
