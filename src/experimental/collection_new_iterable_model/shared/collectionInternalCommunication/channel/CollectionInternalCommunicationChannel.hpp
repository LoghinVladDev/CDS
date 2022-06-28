//
// Created by loghin on 6/26/22.
//

#ifndef __CDS_SHARED_COLLECTION_INTERNAL_COMMUNICATION_HPP__
#define __CDS_SHARED_COLLECTION_INTERNAL_COMMUNICATION_HPP__

#include "../CollectionInternalRequest.hpp"
#include "../CollectionInternalRequestResponse.hpp"
#include "../../delegateIterator/AbstractDelegateIterator.hpp"

namespace cds {                 // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {    // NOLINT(modernize-concat-nested-namespaces)
        namespace __hidden {    // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier)
            namespace __impl {  // NOLINT(bugprone-reserved-identifier)

                template <
                        typename __ReceiverType,                    // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType                      // NOLINT(bugprone-reserved-identifier)
                > class __CollectionInternalCommunicationChannel :  // NOLINT(bugprone-reserved-identifier)
                        public cds :: Object {                      // NOLINT(bugprone-reserved-identifier)

                private:
                    template < typename, typename, bool >
                    friend class __DelegateForwardIterableClient;       // NOLINT(bugprone-reserved-identifier)

                private:
                    template < typename, typename, bool >
                    friend class __DelegateBackwardIterableClient;      // NOLINT(bugprone-reserved-identifier)

                private:
                    template < typename, typename, bool >
                    friend class __DelegateForwardConstIterableClient;  // NOLINT(bugprone-reserved-identifier)

                private:
                    template < typename, typename, bool >
                    friend class __DelegateBackwardConstIterableClient; // NOLINT(bugprone-reserved-identifier)

                private:
                    template < typename, typename >
                    friend class __AbstractIteratorRemoveClient;        // NOLINT(bugprone-reserved-identifier)

                private:
                    template < typename, typename >
                    friend class __AbstractConstIteratorRemoveClient;   // NOLINT(bugprone-reserved-identifier)

                private:
                    template < typename, typename, typename >
                    friend class __RandomInsertionClient;               // NOLINT(bugprone-reserved-identifier)

                private:
                    template < typename, typename, typename >
                    friend class __BoundaryInsertionClient;             // NOLINT(bugprone-reserved-identifier)

                protected:
                    __CDS_NoDiscard virtual auto __cicch_transmitRequest ( // NOLINT(bugprone-reserved-identifier)
                            __CollectionInternalRequest         const * pRequest,
                            __CollectionInternalRequestResponse       * pResponse
                    ) noexcept -> bool = 0;

                protected:
                    __CDS_NoDiscard virtual auto __cicch_transmitConstRequest ( // NOLINT(bugprone-reserved-identifier)
                            __CollectionInternalRequest         const * pRequest,
                            __CollectionInternalRequestResponse       * pResponse
                    ) const noexcept -> bool = 0;

                public:
                    __CDS_cpplang_ConstexprDestructor ~__CollectionInternalCommunicationChannel () noexcept override;
                };

            }
        }
    }
}

#include "../../delegateIterator/impl/AbstractDelegateIterator.hpp"

#endif // __CDS_SHARED_COLLECTION_INTERNAL_COMMUNICATION_HPP__
