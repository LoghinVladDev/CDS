//
// Created by loghin on 6/26/22.
//

#ifndef __CDS_SHARED_ITERABLE_INTERNAL_COMMUNICATION_CHANNEL_IMPL_HPP__ // NOLINT(llvm-header-guard)
#define __CDS_SHARED_ITERABLE_INTERNAL_COMMUNICATION_CHANNEL_IMPL_HPP__ // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
#pragma once

namespace cds {       // NOLINT(modernize-concat-nested-namespaces)
namespace __hidden {  // NOLINT(bugprone-reserved-identifier, modernize-concat-nested-namespaces, cert-dcl37-c, cert-dcl51-cpp)
namespace __impl {    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

template <typename __Receiver, typename __Element>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_ConstexprDestructor __IterableInternalCommunicationChannel <
    __Receiver,
    __Element
>::~__IterableInternalCommunicationChannel () noexcept = default;

} // namespace __impl
} // namespace __hidden
} // namespace cds

#endif // __CDS_SHARED_ITERABLE_INTERNAL_COMMUNICATION_CHANNEL_IMPL_HPP__
