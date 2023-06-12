// NOLINT(llvm-header-guard)
// Created by loghin on 09/07/22.
//

#ifndef __CDS_SHARED_COLLECTION_SERVER_DISPATCHER_IMPL_HPP__ // NOLINT(llvm-header-guard)
#define __CDS_SHARED_COLLECTION_SERVER_DISPATCHER_IMPL_HPP__ // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
#pragma once

#include "IterableServerDispatcherImpl.hpp"

namespace cds {       // NOLINT(modernize-concat-nested-namespaces)
namespace __hidden {  // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
namespace __impl {    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <
    typename                                                                                        __Server,                   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                                                        __Service,                  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                                                        __Element,                  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                                                        __AbstractConstIterator,    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                                                        __ConstIterator,            // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::SupplierConstMemberFunction <__Service, __ConstIterator>                            __cbeginFunction,           // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::SupplierConstMemberFunction < __Service, __ConstIterator >                          __cendFunction,             // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::MapperMemberFunction <__Service, __Element*, __Element const*, bool*>               __newAddressFunction,       // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateMemberFunction <__Service, __AbstractConstIterator const&>                 __removeConstFunction,      // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::MapperMemberFunction <__Service, Size, __AbstractConstIterator const* const*, Size> __removeConstArrayFunction  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> __CDS_OptimalInline auto __CollectionServerDispatcher <
    __Server, __Service, __Element,
    __AbstractConstIterator, __ConstIterator,
    __cbeginFunction, __cendFunction,
    __newAddressFunction,
    __removeConstFunction, __removeConstArrayFunction
> :: __newAddress (
    __Server*         pServer,
    __Element const*  pReferenceElement,
    bool*             pNewElementCreated
) noexcept(false) -> __Element* {
  // call the template received member function
  return (pServer->*__newAddressFunction) (pReferenceElement, pNewElementCreated);
}


template <
    typename                                                                                        __Server,                   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                                                        __Service,                  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                                                        __Element,                  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                                                        __AbstractConstIterator,    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                                                        __ConstIterator,            // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::SupplierConstMemberFunction <__Service, __ConstIterator>                            __cbeginFunction,           // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::SupplierConstMemberFunction < __Service, __ConstIterator >                          __cendFunction,             // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::MapperMemberFunction <__Service, __Element*, __Element const*, bool*>               __newAddressFunction,       // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateMemberFunction <__Service, __AbstractConstIterator const&>                 __removeConstFunction,      // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::MapperMemberFunction <__Service, Size, __AbstractConstIterator const* const*, Size> __removeConstArrayFunction  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> __CDS_OptimalInline auto __CollectionServerDispatcher <
    __Server, __Service, __Element,
    __AbstractConstIterator, __ConstIterator,
    __cbeginFunction, __cendFunction,
    __newAddressFunction,
    __removeConstFunction, __removeConstArrayFunction
> :: __removeConst (
    __Server*                       pServer,
    __AbstractConstIterator const*  pIterator
) noexcept(false) -> bool {
  // call the template received member function
  return (pServer->*__removeConstFunction) (*pIterator);
}


template <
    typename                                                                                        __Server,                   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                                                        __Service,                  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                                                        __Element,                  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                                                        __AbstractConstIterator,    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                                                        __ConstIterator,            // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::SupplierConstMemberFunction <__Service, __ConstIterator>                            __cbeginFunction,           // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::SupplierConstMemberFunction < __Service, __ConstIterator >                          __cendFunction,             // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::MapperMemberFunction <__Service, __Element*, __Element const*, bool*>               __newAddressFunction,       // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateMemberFunction <__Service, __AbstractConstIterator const&>                 __removeConstFunction,      // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::MapperMemberFunction <__Service, Size, __AbstractConstIterator const* const*, Size> __removeConstArrayFunction  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> __CDS_OptimalInline auto __CollectionServerDispatcher <
    __Server, __Service, __Element,
    __AbstractConstIterator, __ConstIterator,
    __cbeginFunction, __cendFunction,
    __newAddressFunction,
    __removeConstFunction,__removeConstArrayFunction
> :: __removeConstArray (
    __Server*                             pServer,
    __AbstractConstIterator const* const* ppIterators,
    Size                                  iteratorArrayCount
) noexcept(false) -> Size {
  // call the template received member function
  return (pServer->*__removeConstArrayFunction) (ppIterators, iteratorArrayCount);
}
} // namespace __impl
} // namespace __hidden
} // namespace cds

#endif // __CDS_SHARED_COLLECTION_SERVER_DISPATCHER_IMPL_HPP__
