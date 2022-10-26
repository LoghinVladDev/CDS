/*
 * Created by loghin on 6/26/22.
 */

#ifndef __CDS_SHARED_COLLECTION_INTERNAL_COMMUNICATION_CHANNEL_IMPL_HPP__ /* NOLINT(llvm-header-guard) */
#define __CDS_SHARED_COLLECTION_INTERNAL_COMMUNICATION_CHANNEL_IMPL_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

namespace cds {             /* NOLINT(modernize-concat-nested-namespaces) */
    namespace __hidden {    /* NOLINT(bugprone-reserved-identifier, modernize-concat-nested-namespaces, cert-dcl37-c, cert-dcl51-cpp) */
        namespace __impl {  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            template <
                    typename __ReceiverType,            /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ElementType              /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > __CDS_cpplang_ConstexprDestructor __CollectionInternalCommunicationChannel <
                    __ReceiverType,
                    __ElementType
            > :: ~__CollectionInternalCommunicationChannel () noexcept = default;

        } /* namespace __impl */
    } /* namespace __hidden */
} /* namespace cds */

#endif /* __CDS_SHARED_COLLECTION_INTERNAL_COMMUNICATION_CHANNEL_IMPL_HPP__ */
