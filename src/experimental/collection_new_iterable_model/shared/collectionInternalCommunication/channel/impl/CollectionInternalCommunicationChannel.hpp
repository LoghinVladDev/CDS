//
// Created by loghin on 6/26/22.
//

#ifndef __CDS_SHARED_COLLECTION_INTERNAL_COMMUNICATION_CHANNEL_IMPL_HPP__
#define __CDS_SHARED_COLLECTION_INTERNAL_COMMUNICATION_CHANNEL_IMPL_HPP__

namespace cds {                 // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {    // NOLINT(modernize-concat-nested-namespaces)
        namespace __hidden {    // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier)
            namespace __impl {  // NOLINT(bugprone-reserved-identifier)

                template <
                        typename __ReceiverType,            // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType              // NOLINT(bugprone-reserved-identifier)
                > __CDS_cpplang_ConstexprDestructor __CollectionInternalCommunicationChannel <
                        __ReceiverType,
                        __ElementType
                > :: ~__CollectionInternalCommunicationChannel () noexcept = default;


                template <
                        typename __ReceiverType,    // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType      // NOLINT(bugprone-reserved-identifier)
                > auto __CDS_cpplang_VirtualConstexpr __CollectionInternalCommunicationChannel <
                        __ReceiverType,
                        __ElementType
                > :: __cicch_obtainGenericHandler (
                        __CollectionInternalRequestType requestType
                ) noexcept -> __GenericHandler {

                    return nullptr;
                }


                template <
                        typename __ReceiverType,    // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType      // NOLINT(bugprone-reserved-identifier)
                > auto __CDS_cpplang_VirtualConstexpr __CollectionInternalCommunicationChannel <
                        __ReceiverType,
                        __ElementType
                > :: __cicch_obtainGenericConstHandler (
                        __CollectionInternalRequestType requestType
                ) const noexcept -> __GenericConstHandler {

                    return nullptr;
                }

            }
        }
    }
}

#endif // __CDS_SHARED_COLLECTION_INTERNAL_COMMUNICATION_CHANNEL_IMPL_HPP__
