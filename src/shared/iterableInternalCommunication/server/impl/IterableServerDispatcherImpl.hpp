// NOLINT(llvm-header-guard)
// Created by loghin on 09/07/22.
//

#ifndef __CDS_SHARED_ITERABLE_SERVER_DISPATCHER_IMPL_HPP__ // NOLINT(llvm-header-guard)
#define __CDS_SHARED_ITERABLE_SERVER_DISPATCHER_IMPL_HPP__ // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
#pragma once

namespace cds {       // NOLINT(modernize-concat-nested-namespaces)
namespace __hidden {  // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
namespace __impl {    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <
    typename                                                              __Server,         // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                              __Service,        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                              __Element,        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                              __ConstIterator,  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::SupplierConstMemberFunction <__Service, __ConstIterator>  __cbeginFunction, // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-member-init)
    functional::SupplierConstMemberFunction <__Service, __ConstIterator>  __cendFunction    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-member-init)
> __CDS_OptimalInline auto __IterableServerDispatcher <
    __Server, __Service, __Element, __ConstIterator,
    __cbeginFunction, __cendFunction
>::__cbegin (__Server const* pServer) noexcept(false) -> __AbstractDelegateIterator <__Element const>* {
  // call the template received member function and wrap iterator in a new delegate
  return Memory::instance().create <__DelegateIterator <__Element const, __ConstIterator>> ((pServer->*__cbeginFunction)());
}


template <
    typename                                                              __Server,         // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                              __Service,        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                              __Element,        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                              __ConstIterator,  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::SupplierConstMemberFunction <__Service, __ConstIterator>  __cbeginFunction, // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-member-init)
    functional::SupplierConstMemberFunction <__Service, __ConstIterator>  __cendFunction    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-member-init)
> __CDS_OptimalInline auto __IterableServerDispatcher <
    __Server, __Service, __Element, __ConstIterator,
    __cbeginFunction, __cendFunction
>::__cend (__Server const* pServer) noexcept(false) -> __AbstractDelegateIterator <__Element const>* {
  // call the template received member function and wrap iterator in a new delegate
  return Memory::instance ().create <__DelegateIterator <__Element const, __ConstIterator>> ((pServer->*__cendFunction)());
}


template <
    typename                                                              __Server,         // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                              __Service,        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                              __Element,        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                              __ConstIterator,  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::SupplierConstMemberFunction <__Service, __ConstIterator>  __cbeginFunction, // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-member-init)
    functional::SupplierConstMemberFunction <__Service, __ConstIterator>  __cendFunction    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-member-init)
> constexpr auto __IterableServerDispatcher <
    __Server, __Service, __Element, __ConstIterator,
    __cbeginFunction, __cendFunction
>::__cbeginLocal (__Server const* pServer) noexcept -> __ConstIterator {
  // call the template received member function
  return (pServer->*__cbeginFunction)();
}


template <
    typename                                                              __Server,         // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                              __Service,        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                              __Element,        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                              __ConstIterator,  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::SupplierConstMemberFunction <__Service, __ConstIterator>  __cbeginFunction, // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-member-init)
    functional::SupplierConstMemberFunction <__Service, __ConstIterator>  __cendFunction    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-member-init)
> constexpr auto __IterableServerDispatcher <
    __Server, __Service, __Element, __ConstIterator,
    __cbeginFunction, __cendFunction
>::__cendLocal (__Server const* pServer) noexcept -> __ConstIterator {
  // call the template received member function
  return (pServer->*__cendFunction)();
}

} // namespace __impl
} // namespace __hidden
} // namespace cds

#endif // __CDS_SHARED_ITERABLE_SERVER_DISPATCHER_IMPL_HPP__
