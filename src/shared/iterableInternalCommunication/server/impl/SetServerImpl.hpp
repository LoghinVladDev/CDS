// NOLINT(llvm-header-guard)
// Created by loghin on 7/3/22.
//

#ifndef __CDS_SHARED_SET_SERVER_IMPL_HPP__ // NOLINT(llvm-header-guard) 
#define __CDS_SHARED_SET_SERVER_IMPL_HPP__ // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
#pragma once

#ifdef _MSC_VER
#include "../../../impl/forceFunctionPointerCast.hpp"
#endif

namespace cds {       // NOLINT(modernize-concat-nested-namespaces) 
namespace __hidden {  // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
namespace __impl {    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename __ReceiverType, typename __ElementType>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
typename __SetServer <__ReceiverType, __ElementType>::__GenericHandler const __SetServer <  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-c-arrays)
    __ReceiverType, __ElementType
>::__routingTable [static_cast <uint32> (__IterableInternalRequest::__iir_requestCountDoNotUse)] = {  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-c-arrays)
    nullptr,                                                                            // __cirt_begin                         - not expected part of Set  
    nullptr,                                                                            // __cirt_end                           - not expected part of Set  
    nullptr,                                                                            // __cirt_rbegin                        - not expected part of Set  
    nullptr,                                                                            // __cirt_rend                          - not expected part of Set  
    nullptr,                                                                            // __cirt_remove                        - not expected part of Set
    bitCast <__GenericHandler> (&__ReceiverType::__removeConst),        // __cirt_removeConst                   - expected part of Set        // NOLINT(*-reinterpret-cast)
    nullptr,                                                                            // __cirt_removeArray                   - not expected part of Set
    bitCast <__GenericHandler> (&__ReceiverType::__removeConstArray),   // __cirt_removeConstArray              - expected part of Set        // NOLINT(*-reinterpret-cast) 
    bitCast <__GenericHandler> (&__ReceiverType::__newAddress),         // __cirt_newAddress                    - expected part of Set        // NOLINT(*-reinterpret-cast)
    nullptr,                                                                            // __cirt_newFrontAddress               - not expected part of Set  
    nullptr,                                                                            // __cirt_newBackAddress                - not expected part of Set  
    nullptr,                                                                            // __cirt_newFrontAddressArray          - not expected part of Set  
    nullptr,                                                                            // __cirt_newBackAddressArray           - not expected part of Set  
    nullptr,                                                                            // __cirt_newBeforeAddress              - not expected part of Set  
    nullptr,                                                                            // __cirt_newBeforeAddressConst         - not expected part of Set  
    nullptr,                                                                            // __cirt_newAfterAddress               - not expected part of Set  
    nullptr,                                                                            // __cirt_newAfterAddressConst          - not expected part of Set  
    nullptr,                                                                            // __cirt_newBeforeAddressArray         - not expected part of Set  
    nullptr,                                                                            // __cirt_newBeforeAddressArrayConst    - not expected part of Set  
    nullptr,                                                                            // __cirt_newAfterAddressArray          - not expected part of Set  
    nullptr,                                                                            // __cirt_newAfterAddressArrayConst     - not expected part of Set  
    nullptr,                                                                            // __cirt_find                          - not expected part of Set  
    nullptr,                                                                            // __cirt_findConst                     - not expected part of Set  
};


template <typename __ReceiverType, typename __ElementType>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
typename __SetServer <__ReceiverType, __ElementType>::__GenericConstHandler const __SetServer < // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-c-arrays)
    __ReceiverType, __ElementType
>::__constRoutingTable [static_cast <uint32> (__IterableInternalRequest::__iir_requestCountDoNotUse)] = {  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-c-arrays)
    bitCast <__GenericConstHandler> (&__ReceiverType::__cbegin),    // __cirt_begin                         - expected part of Set        // NOLINT(*-reinterpret-cast)
    bitCast <__GenericConstHandler> (&__ReceiverType::__cend),      // __cirt_end                           - expected part of Set        // NOLINT(*-reinterpret-cast)
    nullptr,                                                                        // __cirt_rbegin                        - not expected part of Set
    nullptr,                                                                        // __cirt_rend                          - not expected part of Set
    nullptr,                                                                        // __cirt_remove                        - not expected part of Set
    nullptr,                                                                        // __cirt_removeConst                   - not expected part of Set
    nullptr,                                                                        // __cirt_removeArray                   - not expected part of Set
    nullptr,                                                                        // __cirt_removeConstArray              - not expected part of Set
    nullptr,                                                                        // __cirt_newAddress                    - not expected part of Set
    nullptr,                                                                        // __cirt_newFrontAddress               - not expected part of Set
    nullptr,                                                                        // __cirt_newBackAddress                - not expected part of Set
    nullptr,                                                                        // __cirt_newFrontAddressArray          - not expected part of Set
    nullptr,                                                                        // __cirt_newBackAddressArray           - not expected part of Set
    nullptr,                                                                        // __cirt_newBeforeAddress              - not expected part of Set
    nullptr,                                                                        // __cirt_newBeforeAddressConst         - not expected part of Set
    nullptr,                                                                        // __cirt_newAfterAddress               - not expected part of Set
    nullptr,                                                                        // __cirt_newAfterAddressConst          - not expected part of Set
    nullptr,                                                                        // __cirt_newBeforeAddressArray         - not expected part of Set
    nullptr,                                                                        // __cirt_newBeforeAddressArrayConst    - not expected part of Set
    nullptr,                                                                        // __cirt_newAfterAddressArray          - not expected part of Set
    nullptr,                                                                        // __cirt_newAfterAddressArrayConst     - not expected part of Set
    nullptr,                                                                        // __cirt_find                          - not expected part of Set
    bitCast <__GenericConstHandler> (&__ReceiverType::__findConst)  // __cirt_findConst                     - expected part of Set        // NOLINT(*-reinterpret-cast)
};


template <typename __ReceiverType, typename __ElementType>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
constexpr auto __SetServer <__ReceiverType, __ElementType>::__ss_handlers () const noexcept -> __GenericHandler const* {
  // return the first address in the routing table 
  return &__SetServer::__routingTable [0u];
}


template <typename __ReceiverType, typename __ElementType>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
constexpr auto __SetServer <__ReceiverType, __ElementType>::__ss_constHandlers () const noexcept -> __GenericConstHandler const* {
  // return the first address in the const routing table 
  return &__SetServer::__constRoutingTable [0u];
}
} // namespace __impl 
} // namespace __hidden 
} // namespace cds 

#endif // __CDS_SHARED_SET_SERVER_IMPL_HPP__ 
