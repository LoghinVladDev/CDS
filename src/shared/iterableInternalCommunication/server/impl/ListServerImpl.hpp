// NOLINT(llvm-header-guard)
// Created by loghin on 7/3/22.
//

#ifndef __CDS_SHARED_LIST_SERVER_IMPL_HPP__ // NOLINT(llvm-header-guard)
#define __CDS_SHARED_LIST_SERVER_IMPL_HPP__ // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
#pragma once

#ifdef _MSC_VER
#include "../../../impl/forceFunctionPointerCast.hpp"
#endif

namespace cds {       // NOLINT(modernize-concat-nested-namespaces)
namespace __hidden {  // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
namespace __impl {    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename __Receiver, typename __Element>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
typename __ListServer <__Receiver, __Element>::__GenericHandler const __ListServer <  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp,*-c-arrays)
    __Receiver, __Element
>::__routingTable [static_cast <uint32> (__IterableInternalRequest::__iir_requestCountDoNotUse)] = {  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp,*-c-arrays)
    bitCast <__GenericHandler> (&__Receiver::__begin),               // __cirt_begin                         - expected part of List       // NOLINT(*-reinterpret-cast) 
    bitCast <__GenericHandler> (&__Receiver::__end),                 // __cirt_end                           - expected part of List       // NOLINT(*-reinterpret-cast) 
    bitCast <__GenericHandler> (&__Receiver::__rbegin),              // __cirt_rbegin                        - expected part of List       // NOLINT(*-reinterpret-cast) 
    bitCast <__GenericHandler> (&__Receiver::__rend),                // __cirt_rend                          - expected part of List       // NOLINT(*-reinterpret-cast) 
    bitCast <__GenericHandler> (&__Receiver::__remove),              // __cirt_remove                        - expected part of List       // NOLINT(*-reinterpret-cast) 
    bitCast <__GenericHandler> (&__Receiver::__removeConst),         // __cirt_removeConst                   - expected part of List       // NOLINT(*-reinterpret-cast) 
    bitCast <__GenericHandler> (&__Receiver::__removeArray),         // __cirt_removeArray                   - expected part of List       // NOLINT(*-reinterpret-cast) 
    bitCast <__GenericHandler> (&__Receiver::__removeConstArray),    // __cirt_removeConstArray              - expected part of List       // NOLINT(*-reinterpret-cast) 
    bitCast <__GenericHandler> (&__Receiver::__newAddress),          // __cirt_newAddress                    - expected part of List       // NOLINT(*-reinterpret-cast) 
    bitCast <__GenericHandler> (&__Receiver::__newFront),            // __cirt_newFrontAddress               - expected part of List       // NOLINT(*-reinterpret-cast) 
    bitCast <__GenericHandler> (&__Receiver::__newBack),             // __cirt_newBackAddress                - expected part of List       // NOLINT(*-reinterpret-cast) 
    bitCast <__GenericHandler> (&__Receiver::__newFrontArray),       // __cirt_newFrontAddressArray          - expected part of List       // NOLINT(*-reinterpret-cast) 
    bitCast <__GenericHandler> (&__Receiver::__newBackArray),        // __cirt_newBackAddressArray           - expected part of List       // NOLINT(*-reinterpret-cast) 
    bitCast <__GenericHandler> (&__Receiver::__newBefore),           // __cirt_newBeforeAddress              - expected part of List       // NOLINT(*-reinterpret-cast) 
    bitCast <__GenericHandler> (&__Receiver::__newBeforeConst),      // __cirt_newBeforeAddressConst         - expected part of List       // NOLINT(*-reinterpret-cast) 
    bitCast <__GenericHandler> (&__Receiver::__newAfter),            // __cirt_newAfterAddress               - expected part of List       // NOLINT(*-reinterpret-cast) 
    bitCast <__GenericHandler> (&__Receiver::__newAfterConst),       // __cirt_newAfterAddressConst          - expected part of List       // NOLINT(*-reinterpret-cast) 
    bitCast <__GenericHandler> (&__Receiver::__newBeforeArray),      // __cirt_newBeforeAddressArray         - expected part of List       // NOLINT(*-reinterpret-cast) 
    bitCast <__GenericHandler> (&__Receiver::__newBeforeArrayConst), // __cirt_newBeforeAddressArrayConst    - expected part of List       // NOLINT(*-reinterpret-cast) 
    bitCast <__GenericHandler> (&__Receiver::__newAfterArray),       // __cirt_newAfterAddressArray          - expected part of List       // NOLINT(*-reinterpret-cast) 
    bitCast <__GenericHandler> (&__Receiver::__newAfterArrayConst),  // __cirt_newAfterAddressArrayConst     - expected part of List       // NOLINT(*-reinterpret-cast)
    nullptr,                                                                                // __cirt_find                          - not expected part of List 
    nullptr                                                                                 // __cirt_findConst                     - not expected part of List 
};


template <typename __Receiver, typename __Element>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
typename __ListServer <__Receiver, __Element>::__GenericConstHandler const __ListServer < // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp,*-c-arrays)
    __Receiver, __Element
>::__constRoutingTable [static_cast <uint32> (__IterableInternalRequest::__iir_requestCountDoNotUse)] = {  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp,*-c-arrays)
    bitCast <__GenericConstHandler> (&__Receiver::__cbegin),    // __cirt_begin                         - expected part of List       // NOLINT(*-reinterpret-cast) 
    bitCast <__GenericConstHandler> (&__Receiver::__cend),      // __cirt_end                           - expected part of List       // NOLINT(*-reinterpret-cast) 
    bitCast <__GenericConstHandler> (&__Receiver::__crbegin),   // __cirt_rbegin                        - expected part of List       // NOLINT(*-reinterpret-cast) 
    bitCast <__GenericConstHandler> (&__Receiver::__crend),     // __cirt_rend                          - expected part of List       // NOLINT(*-reinterpret-cast)
    nullptr,                                                             // __cirt_remove                        - not expected part of List
    nullptr,                                                             // __cirt_removeConst                   - not expected part of List
    nullptr,                                                             // __cirt_removeArray                   - not expected part of List
    nullptr,                                                             // __cirt_removeConstArray              - not expected part of List
    nullptr,                                                             // __cirt_newAddress                    - not expected part of List
    nullptr,                                                             // __cirt_newFrontAddress               - not expected part of List
    nullptr,                                                             // __cirt_newBackAddress                - not expected part of List
    nullptr,                                                             // __cirt_newFrontAddressArray          - not expected part of List
    nullptr,                                                             // __cirt_newBackAddressArray           - not expected part of List
    nullptr,                                                             // __cirt_newBeforeAddress              - not expected part of List
    nullptr,                                                             // __cirt_newBeforeAddressConst         - not expected part of List
    nullptr,                                                             // __cirt_newAfterAddress               - not expected part of List
    nullptr,                                                             // __cirt_newAfterAddressConst          - not expected part of List
    nullptr,                                                             // __cirt_newBeforeAddressArray         - not expected part of List
    nullptr,                                                             // __cirt_newBeforeAddressArrayConst    - not expected part of List
    nullptr,                                                             // __cirt_newAfterAddressArray          - not expected part of List
    nullptr,                                                             // __cirt_newAfterAddressArrayConst     - not expected part of List
    nullptr,                                                             // __cirt_find                          - not expected part of List
    nullptr                                                              // __cirt_findConst                     - not expected part of List
};


template <typename __Receiver, typename __Element>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
constexpr auto __ListServer <__Receiver, __Element>::__ls_handlers () const noexcept -> __GenericHandler const* {
  // return the first address in the routing table 
  return &__ListServer::__routingTable [0u];
}


template <typename __Receiver, typename __Element>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
constexpr auto __ListServer <__Receiver, __Element>::__ls_constHandlers () const noexcept -> __GenericConstHandler const* {
  // return the first address in the const routing table 
  return &__ListServer::__constRoutingTable [0u];
}
} // namespace __impl 
} // namespace __hidden 
} // namespace cds 

#endif // __CDS_SHARED_LIST_SERVER_IMPL_HPP__ 
