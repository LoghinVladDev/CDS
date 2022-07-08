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
                    friend class __DelegateForwardIterablePrimitiveClient;                  // NOLINT(bugprone-reserved-identifier)

                private:
                    template < typename, typename, bool >
                    friend class __DelegateBackwardIterablePrimitiveClient;                 // NOLINT(bugprone-reserved-identifier)

                private:
                    template < typename, typename, bool >
                    friend class __DelegateForwardConstIterablePrimitiveClient;             // NOLINT(bugprone-reserved-identifier)

                private:
                    template < typename, typename, bool >
                    friend class __DelegateBackwardConstIterablePrimitiveClient;            // NOLINT(bugprone-reserved-identifier)

                private:
                    template < typename, typename >
                    friend class __AbstractIteratorRemovePrimitiveClient;                   // NOLINT(bugprone-reserved-identifier)

                private:
                    template < typename, typename >
                    friend class __AbstractConstIteratorRemovePrimitiveClient;              // NOLINT(bugprone-reserved-identifier)

                private:
                    template < typename, typename, typename >
                    friend class __RandomInsertionPrimitiveClient;                          // NOLINT(bugprone-reserved-identifier)

                private:
                    template < typename, typename, typename >
                    friend class __BoundaryInsertionPrimitiveClient;                        // NOLINT(bugprone-reserved-identifier)

                private:
                    template < typename, typename, typename >
                    friend class __AbstractIteratorRelativeInsertionPrimitiveClient;        // NOLINT(bugprone-reserved-identifier)

                private:
                    template < typename, typename, typename >
                    friend class __AbstractConstIteratorRelativeInsertionPrimitiveClient;   // NOLINT(bugprone-reserved-identifier)

                private:
                    using __GenericHandler  = void ( __ReceiverType :: * ) ();               // NOLINT(bugprone-reserved-identifier)

                private:
                    using __GenericConstHandler  = void ( __ReceiverType :: * ) () const;    // NOLINT(bugprone-reserved-identifier)

                protected:
                    __CDS_NoDiscard __CDS_cpplang_VirtualConstexpr virtual auto __cicch_obtainGenericHandler ( // NOLINT(bugprone-reserved-identifier)
                            __CollectionInternalRequestType requestType
                    ) noexcept -> __GenericHandler;

                protected:
                    __CDS_NoDiscard __CDS_cpplang_VirtualConstexpr virtual auto __cicch_obtainGenericConstHandler ( // NOLINT(bugprone-reserved-identifier)
                            __CollectionInternalRequestType requestType
                    ) const noexcept -> __GenericConstHandler;

                public:
                    __CDS_cpplang_ConstexprDestructor ~__CollectionInternalCommunicationChannel () noexcept override;
                };

            }
        }
    }
}

#include "../../delegateIterator/impl/AbstractDelegateIterator.hpp"

#endif // __CDS_SHARED_COLLECTION_INTERNAL_COMMUNICATION_HPP__
