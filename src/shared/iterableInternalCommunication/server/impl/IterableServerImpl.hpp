// NOLINT(llvm-header-guard)
// Created by loghin on 7/3/22.
//

#ifndef __CDS_SHARED_ITERABLE_SERVER_IMPL_HPP__   // NOLINT(llvm-header-guard)
#define __CDS_SHARED_ITERABLE_SERVER_IMPL_HPP__   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
#pragma once

namespace cds {       // NOLINT(modernize-concat-nested-namespaces)
namespace __hidden {  // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
namespace __impl {    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename __Receiver, typename __Element>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
typename __IterableServer <__Receiver, __Element>::__GenericHandler const __IterableServer <  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp,*-c-arrays)
    __Receiver, __Element
>::__routingTable [static_cast <uint32> (__IterableInternalRequest::__iir_requestCountDoNotUse)] = { // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp,*-c-arrays)
    nullptr,  // __iir_begin                         - not expected part of Iterable
    nullptr,  // __iir_end                           - not expected part of Iterable
    nullptr,  // __iir_rbegin                        - not expected part of Iterable
    nullptr,  // __iir_rend                          - not expected part of Iterable
    nullptr,  // __iir_remove                        - not expected part of Iterable
    nullptr,  // __iir_removeConst                   - not expected part of Iterable
    nullptr,  // __iir_removeArray                   - not expected part of Iterable
    nullptr,  // __iir_removeConstArray              - not expected part of Iterable
    nullptr,  // __iir_newAddress                    - not expected part of Iterable
    nullptr,  // __iir_newFrontAddress               - not expected part of Iterable
    nullptr,  // __iir_newBackAddress                - not expected part of Iterable
    nullptr,  // __iir_newFrontAddressArray          - not expected part of Iterable
    nullptr,  // __iir_newBackAddressArray           - not expected part of Iterable
    nullptr,  // __iir_newBeforeAddress              - not expected part of Iterable
    nullptr,  // __iir_newBeforeAddressConst         - not expected part of Iterable
    nullptr,  // __iir_newAfterAddress               - not expected part of Iterable
    nullptr,  // __iir_newAfterAddressConst          - not expected part of Iterable
    nullptr,  // __iir_newBeforeAddressArray         - not expected part of Iterable
    nullptr,  // __iir_newBeforeAddressArrayConst    - not expected part of Iterable
    nullptr,  // __iir_newAfterAddressArray          - not expected part of Iterable
    nullptr,  // __iir_newAfterAddressArrayConst     - not expected part of Iterable
    nullptr,  // __iir_find                          - not expected part of Iterable
    nullptr,  // __iir_findConst                     - not expected part of Iterable
};


template <typename __Receiver, typename __Element>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
typename __IterableServer <__Receiver, __Element>::__GenericConstHandler const __IterableServer < // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp,*-c-arrays)
    __Receiver, __Element
>::__constRoutingTable [static_cast <uint32> (__IterableInternalRequest::__iir_requestCountDoNotUse)] = {  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp,*-c-arrays)
    bitCast <__GenericConstHandler> (&__Receiver::__cbegin), // __iir_begin                         - expected part of Iterable
    bitCast <__GenericConstHandler> (&__Receiver::__cend),   // __iir_end                           - expected part of Iterable
    nullptr,                                                              // __iir_rbegin                        - not expected part of Iterable
    nullptr,                                                              // __iir_rend                          - not expected part of Iterable
    nullptr,                                                              // __iir_remove                        - not expected part of Iterable
    nullptr,                                                              // __iir_removeConst                   - not expected part of Iterable
    nullptr,                                                              // __iir_removeArray                   - not expected part of Iterable
    nullptr,                                                              // __iir_removeConstArray              - not expected part of Iterable
    nullptr,                                                              // __iir_newAddress                    - not expected part of Iterable
    nullptr,                                                              // __iir_newFrontAddress               - not expected part of Iterable
    nullptr,                                                              // __iir_newBackAddress                - not expected part of Iterable
    nullptr,                                                              // __iir_newFrontAddressArray          - not expected part of Iterable
    nullptr,                                                              // __iir_newBackAddressArray           - not expected part of Iterable
    nullptr,                                                              // __iir_newBeforeAddress              - not expected part of Iterable
    nullptr,                                                              // __iir_newBeforeAddressConst         - not expected part of Iterable
    nullptr,                                                              // __iir_newAfterAddress               - not expected part of Iterable
    nullptr,                                                              // __iir_newAfterAddressConst          - not expected part of Iterable
    nullptr,                                                              // __iir_newBeforeAddressArray         - not expected part of Iterable
    nullptr,                                                              // __iir_newBeforeAddressArrayConst    - not expected part of Iterable
    nullptr,                                                              // __iir_newAfterAddressArray          - not expected part of Iterable
    nullptr,                                                              // __iir_newAfterAddressArrayConst     - not expected part of Iterable
    nullptr,                                                              // __iir_find                          - not expected part of Iterable
    nullptr                                                               // __iir_findConst                     - not expected part of Iterable
};


template <typename __Receiver, typename __Element>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
constexpr auto __IterableServer <__Receiver, __Element>::__is_handlers () const noexcept -> __GenericHandler const* {
  // return the first address in the routing table
  return &__IterableServer::__routingTable [0u];
}


template <typename __Receiver, typename __Element>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
constexpr auto __IterableServer <__Receiver, __Element>::__is_constHandlers () const noexcept -> __GenericConstHandler const* {
  // return the first address in the const routing table
  return &__IterableServer::__constRoutingTable [0u];
}
} // namespace __impl
} // namespace __hidden
} // namespace cds

#endif // __CDS_SHARED_ITERABLE_SERVER_IMPL_HPP__