// NOLINT(llvm-header-guard)
// Created by stefan on 10.10.2022.
//

#ifndef __CDS_SHARED_TREE_MAP_SERVER_DISPATCHER_IMPL_HPP__ // NOLINT(llvm-header-guard) 
#define __CDS_SHARED_TREE_MAP_SERVER_DISPATCHER_IMPL_HPP__ // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
#pragma once

#include "MapServerDispatcherImpl.hpp"

namespace cds {       // NOLINT(modernize-concat-nested-namespaces) 
namespace __hidden {  // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
namespace __impl {    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <
    typename                                                                                        __Server,                   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                                                        __Service,                  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                                                        __Element,                  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                                                        __Key,                      // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                                                        __AbstractIterator,         // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                                                        __AbstractConstIterator,    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                                                        __Iterator,                 // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                                                        __ConstIterator,            // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                                                        __ReverseIterator,          // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                                                        __ReverseConstIterator,     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::SupplierMemberFunction <__Service, __Iterator>                                      __beginFunction,            // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::SupplierMemberFunction <__Service, __Iterator>                                      __endFunction,              // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::SupplierMemberFunction <__Service, __ReverseIterator>                               __rbeginFunction,           // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::SupplierMemberFunction <__Service, __ReverseIterator>                               __rendFunction,             // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::SupplierConstMemberFunction <__Service, __ConstIterator>                            __cbeginFunction,           // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::SupplierConstMemberFunction <__Service, __ConstIterator>                            __cendFunction,             // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::SupplierConstMemberFunction <__Service, __ReverseConstIterator>                     __crbeginFunction,          // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::SupplierConstMemberFunction <__Service, __ReverseConstIterator>                     __crendFunction,            // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::MapperMemberFunction <__Service, __Element*, __Element const*, bool*>               __newAddressFunction,       // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateMemberFunction <__Service, __AbstractIterator const&>                      __removeFunction,           // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateMemberFunction <__Service, __AbstractConstIterator const&>                 __removeConstFunction,      // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::MapperMemberFunction <__Service, Size, __AbstractIterator const* const*, Size>      __removeArrayFunction,      // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::MapperMemberFunction <__Service, Size, __AbstractConstIterator const* const*, Size> __removeConstArrayFunction, // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::MapperMemberFunction <__Service, __Iterator, __Key const&>                          __findFunction,             // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::MapperConstMemberFunction <__Service, __ConstIterator, __Key const&>                __findConstFunction         // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> auto __TreeMapServerDispatcher <
    __Server, __Service, __Element, __Key, __AbstractIterator, __AbstractConstIterator,
    __Iterator, __ConstIterator, __ReverseIterator, __ReverseConstIterator,
    __beginFunction, __endFunction, __rbeginFunction, __rendFunction,
    __cbeginFunction, __cendFunction, __crbeginFunction, __crendFunction,
    __newAddressFunction,
    __removeFunction, __removeConstFunction, __removeArrayFunction, __removeConstArrayFunction,
    __findFunction, __findConstFunction
>::__rbeginLocal (__Server* pServer) noexcept -> __ReverseIterator {
  return (pServer->*__rbeginFunction) (); // NOLINT(*-reinterpret-cast) 
}


template <
    typename                                                                                        __Server,                   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                                                        __Service,                  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                                                        __Element,                  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                                                        __Key,                      // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                                                        __AbstractIterator,         // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                                                        __AbstractConstIterator,    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                                                        __Iterator,                 // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                                                        __ConstIterator,            // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                                                        __ReverseIterator,          // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                                                        __ReverseConstIterator,     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::SupplierMemberFunction <__Service, __Iterator>                                      __beginFunction,            // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::SupplierMemberFunction <__Service, __Iterator>                                      __endFunction,              // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::SupplierMemberFunction <__Service, __ReverseIterator>                               __rbeginFunction,           // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::SupplierMemberFunction <__Service, __ReverseIterator>                               __rendFunction,             // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::SupplierConstMemberFunction <__Service, __ConstIterator>                            __cbeginFunction,           // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::SupplierConstMemberFunction <__Service, __ConstIterator>                            __cendFunction,             // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::SupplierConstMemberFunction <__Service, __ReverseConstIterator>                     __crbeginFunction,          // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::SupplierConstMemberFunction <__Service, __ReverseConstIterator>                     __crendFunction,            // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::MapperMemberFunction <__Service, __Element*, __Element const*, bool*>               __newAddressFunction,       // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateMemberFunction <__Service, __AbstractIterator const&>                      __removeFunction,           // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateMemberFunction <__Service, __AbstractConstIterator const&>                 __removeConstFunction,      // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::MapperMemberFunction <__Service, Size, __AbstractIterator const* const*, Size>      __removeArrayFunction,      // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::MapperMemberFunction <__Service, Size, __AbstractConstIterator const* const*, Size> __removeConstArrayFunction, // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::MapperMemberFunction <__Service, __Iterator, __Key const&>                          __findFunction,             // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::MapperConstMemberFunction <__Service, __ConstIterator, __Key const&>                __findConstFunction         // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> auto __TreeMapServerDispatcher <
    __Server, __Service, __Element, __Key, __AbstractIterator, __AbstractConstIterator,
    __Iterator, __ConstIterator, __ReverseIterator, __ReverseConstIterator,
    __beginFunction, __endFunction, __rbeginFunction, __rendFunction,
    __cbeginFunction, __cendFunction, __crbeginFunction, __crendFunction,
    __newAddressFunction,
    __removeFunction, __removeConstFunction, __removeArrayFunction, __removeConstArrayFunction,
    __findFunction, __findConstFunction
>::__rendLocal (__Server* pServer) noexcept -> __ReverseIterator {
  return (pServer->*__rendFunction) ();   // NOLINT(*-reinterpret-cast)
}


template <
    typename                                                                                        __Server,                   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                                                        __Service,                  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                                                        __Element,                  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                                                        __Key,                      // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                                                        __AbstractIterator,         // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                                                        __AbstractConstIterator,    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                                                        __Iterator,                 // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                                                        __ConstIterator,            // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                                                        __ReverseIterator,          // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                                                        __ReverseConstIterator,     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::SupplierMemberFunction <__Service, __Iterator>                                      __beginFunction,            // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::SupplierMemberFunction <__Service, __Iterator>                                      __endFunction,              // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::SupplierMemberFunction <__Service, __ReverseIterator>                               __rbeginFunction,           // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::SupplierMemberFunction <__Service, __ReverseIterator>                               __rendFunction,             // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::SupplierConstMemberFunction <__Service, __ConstIterator>                            __cbeginFunction,           // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::SupplierConstMemberFunction <__Service, __ConstIterator>                            __cendFunction,             // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::SupplierConstMemberFunction <__Service, __ReverseConstIterator>                     __crbeginFunction,          // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::SupplierConstMemberFunction <__Service, __ReverseConstIterator>                     __crendFunction,            // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::MapperMemberFunction <__Service, __Element*, __Element const*, bool*>               __newAddressFunction,       // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateMemberFunction <__Service, __AbstractIterator const&>                      __removeFunction,           // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateMemberFunction <__Service, __AbstractConstIterator const&>                 __removeConstFunction,      // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::MapperMemberFunction <__Service, Size, __AbstractIterator const* const*, Size>      __removeArrayFunction,      // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::MapperMemberFunction <__Service, Size, __AbstractConstIterator const* const*, Size> __removeConstArrayFunction, // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::MapperMemberFunction <__Service, __Iterator, __Key const&>                          __findFunction,             // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::MapperConstMemberFunction <__Service, __ConstIterator, __Key const&>                __findConstFunction         // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> auto __TreeMapServerDispatcher <
    __Server, __Service, __Element, __Key, __AbstractIterator, __AbstractConstIterator,
    __Iterator, __ConstIterator, __ReverseIterator, __ReverseConstIterator,
    __beginFunction, __endFunction, __rbeginFunction, __rendFunction,
    __cbeginFunction, __cendFunction, __crbeginFunction, __crendFunction,
    __newAddressFunction,
    __removeFunction, __removeConstFunction, __removeArrayFunction, __removeConstArrayFunction,
    __findFunction, __findConstFunction
>::__crbeginLocal (__Server const* pServer) noexcept -> __ReverseConstIterator {
  return (pServer->*__crbeginFunction) ();  // NOLINT(*-reinterpret-cast)
}


template <
    typename                                                                                        __Server,                   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                                                        __Service,                  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                                                        __Element,                  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                                                        __Key,                      // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                                                        __AbstractIterator,         // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                                                        __AbstractConstIterator,    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                                                        __Iterator,                 // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                                                        __ConstIterator,            // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                                                        __ReverseIterator,          // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                                                        __ReverseConstIterator,     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::SupplierMemberFunction <__Service, __Iterator>                                      __beginFunction,            // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::SupplierMemberFunction <__Service, __Iterator>                                      __endFunction,              // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::SupplierMemberFunction <__Service, __ReverseIterator>                               __rbeginFunction,           // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::SupplierMemberFunction <__Service, __ReverseIterator>                               __rendFunction,             // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::SupplierConstMemberFunction <__Service, __ConstIterator>                            __cbeginFunction,           // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::SupplierConstMemberFunction <__Service, __ConstIterator>                            __cendFunction,             // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::SupplierConstMemberFunction <__Service, __ReverseConstIterator>                     __crbeginFunction,          // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::SupplierConstMemberFunction <__Service, __ReverseConstIterator>                     __crendFunction,            // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::MapperMemberFunction <__Service, __Element*, __Element const*, bool*>               __newAddressFunction,       // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateMemberFunction <__Service, __AbstractIterator const&>                      __removeFunction,           // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateMemberFunction <__Service, __AbstractConstIterator const&>                 __removeConstFunction,      // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::MapperMemberFunction <__Service, Size, __AbstractIterator const* const*, Size>      __removeArrayFunction,      // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::MapperMemberFunction <__Service, Size, __AbstractConstIterator const* const*, Size> __removeConstArrayFunction, // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::MapperMemberFunction <__Service, __Iterator, __Key const&>                          __findFunction,             // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::MapperConstMemberFunction <__Service, __ConstIterator, __Key const&>                __findConstFunction         // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> auto __TreeMapServerDispatcher <
    __Server, __Service, __Element, __Key, __AbstractIterator, __AbstractConstIterator,
    __Iterator, __ConstIterator, __ReverseIterator, __ReverseConstIterator,
    __beginFunction, __endFunction, __rbeginFunction, __rendFunction,
    __cbeginFunction, __cendFunction, __crbeginFunction, __crendFunction,
    __newAddressFunction,
    __removeFunction, __removeConstFunction, __removeArrayFunction, __removeConstArrayFunction,
    __findFunction, __findConstFunction
>::__crendLocal (__Server const* pServer) noexcept -> __ReverseConstIterator {
  return (pServer->*__crendFunction) ();    // NOLINT(*-reinterpret-cast)
}
} // namespace __impl 
} // namespace __hidden 
} // namespace cds 

#endif // __CDS_SHARED_TREE_MAP_SERVER_DISPATCHER_IMPL_HPP__ 
