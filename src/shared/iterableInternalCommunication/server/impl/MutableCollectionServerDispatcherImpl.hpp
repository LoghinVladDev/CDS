// NOLINT(llvm-header-guard)
// Created by loghin on 09/07/22.
//

#ifndef __CDS_SHARED_MUTABLE_COLLECTION_SERVER_DISPATCHER_IMPL_HPP__ // NOLINT(llvm-header-guard) 
#define __CDS_SHARED_MUTABLE_COLLECTION_SERVER_DISPATCHER_IMPL_HPP__ // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
#pragma once

#include "CollectionServerDispatcherImpl.hpp"

namespace cds {       // NOLINT(modernize-concat-nested-namespaces) 
namespace __hidden {  // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier) 
namespace __impl {    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
template <
    typename                                                                                        __Server,                   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                                                        __Service,                  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                                                        __Element,                  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                                                        __AbstractIterator,         // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                                                        __AbstractConstIterator,    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                                                        __Iterator,                 // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                                                        __ConstIterator,            // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::SupplierMemberFunction <__Service, __Iterator>                                      __beginFunction,            // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp,*-member-init)
    functional::SupplierMemberFunction <__Service, __Iterator>                                      __endFunction,              // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp,*-member-init)
    functional::SupplierConstMemberFunction <__Service, __ConstIterator>                            __cbeginFunction,           // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp,*-member-init)
    functional::SupplierConstMemberFunction <__Service, __ConstIterator>                            __cendFunction,             // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp,*-member-init)
    functional::MapperMemberFunction <__Service, __Element*, __Element const*, bool*>               __newAddressFunction,       // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp,*-member-init)
    functional::PredicateMemberFunction <__Service, __AbstractIterator const&>                      __removeFunction,           // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp,*-member-init)
    functional::PredicateMemberFunction <__Service, __AbstractConstIterator const&>                 __removeConstFunction,      // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp,*-member-init)
    functional::MapperMemberFunction <__Service, Size, __AbstractIterator const* const*, Size>      __removeArrayFunction,      // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp,*-member-init)
    functional::MapperMemberFunction <__Service, Size, __AbstractConstIterator const* const*, Size> __removeConstArrayFunction  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp,*-member-init)
> __CDS_OptimalInline auto __MutableCollectionServerDispatcher <
    __Server, __Service, __Element,
    __AbstractIterator, __AbstractConstIterator, __Iterator, __ConstIterator,
    __beginFunction, __endFunction, __cbeginFunction, __cendFunction,
    __newAddressFunction,
    __removeFunction, __removeConstFunction, __removeArrayFunction, __removeConstArrayFunction
>::__begin (__Server* pServer) noexcept(false) -> __AbstractDelegateIterator <__Element>* {
  // call the template received member function and wrap iterator in a new delegate 
  return Memory::instance().create <__DelegateIterator <__Element, __Iterator>> ((pServer->*__beginFunction)());
}


template <
    typename                                                                                        __Server,                   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                                                        __Service,                  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                                                        __Element,                  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                                                        __AbstractIterator,         // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                                                        __AbstractConstIterator,    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                                                        __Iterator,                 // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                                                        __ConstIterator,            // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::SupplierMemberFunction <__Service, __Iterator>                                      __beginFunction,            // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp,*-member-init)
    functional::SupplierMemberFunction <__Service, __Iterator>                                      __endFunction,              // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp,*-member-init)
    functional::SupplierConstMemberFunction <__Service, __ConstIterator>                            __cbeginFunction,           // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp,*-member-init)
    functional::SupplierConstMemberFunction <__Service, __ConstIterator>                            __cendFunction,             // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp,*-member-init)
    functional::MapperMemberFunction <__Service, __Element*, __Element const*, bool*>               __newAddressFunction,       // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp,*-member-init)
    functional::PredicateMemberFunction <__Service, __AbstractIterator const&>                      __removeFunction,           // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp,*-member-init)
    functional::PredicateMemberFunction <__Service, __AbstractConstIterator const&>                 __removeConstFunction,      // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp,*-member-init)
    functional::MapperMemberFunction <__Service, Size, __AbstractIterator const* const*, Size>      __removeArrayFunction,      // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp,*-member-init)
    functional::MapperMemberFunction <__Service, Size, __AbstractConstIterator const* const*, Size> __removeConstArrayFunction  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp,*-member-init)
> __CDS_OptimalInline auto __MutableCollectionServerDispatcher <
    __Server, __Service, __Element,
    __AbstractIterator, __AbstractConstIterator, __Iterator, __ConstIterator,
    __beginFunction, __endFunction, __cbeginFunction, __cendFunction,
    __newAddressFunction,
    __removeFunction, __removeConstFunction, __removeArrayFunction, __removeConstArrayFunction
>::__end (__Server* pServer) noexcept(false) -> __AbstractDelegateIterator <__Element>* {
  // call the template received member function and wrap iterator in a new delegate 
  return Memory::instance().create <__DelegateIterator <__Element, __Iterator>> ((pServer->*__endFunction)());
}


template <
    typename                                                                                        __Server,                   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                                                        __Service,                  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                                                        __Element,                  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                                                        __AbstractIterator,         // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                                                        __AbstractConstIterator,    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                                                        __Iterator,                 // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                                                        __ConstIterator,            // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::SupplierMemberFunction <__Service, __Iterator>                                      __beginFunction,            // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp,*-member-init)
    functional::SupplierMemberFunction <__Service, __Iterator>                                      __endFunction,              // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp,*-member-init)
    functional::SupplierConstMemberFunction <__Service, __ConstIterator>                            __cbeginFunction,           // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp,*-member-init)
    functional::SupplierConstMemberFunction <__Service, __ConstIterator>                            __cendFunction,             // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp,*-member-init)
    functional::MapperMemberFunction <__Service, __Element*, __Element const*, bool*>               __newAddressFunction,       // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp,*-member-init)
    functional::PredicateMemberFunction <__Service, __AbstractIterator const&>                      __removeFunction,           // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp,*-member-init)
    functional::PredicateMemberFunction <__Service, __AbstractConstIterator const&>                 __removeConstFunction,      // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp,*-member-init)
    functional::MapperMemberFunction <__Service, Size, __AbstractIterator const* const*, Size>      __removeArrayFunction,      // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp,*-member-init)
    functional::MapperMemberFunction <__Service, Size, __AbstractConstIterator const* const*, Size> __removeConstArrayFunction  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp,*-member-init)
> __CDS_cpplang_NonConstConstexprMemberFunction auto __MutableCollectionServerDispatcher <
    __Server, __Service, __Element,
    __AbstractIterator, __AbstractConstIterator, __Iterator, __ConstIterator,
    __beginFunction, __endFunction, __cbeginFunction, __cendFunction,
    __newAddressFunction,
    __removeFunction, __removeConstFunction, __removeArrayFunction, __removeConstArrayFunction
>::__beginLocal (__Server* pServer) noexcept -> __Iterator {
  // call the template received member function
  return (pServer->*__beginFunction)();
}


template <
    typename                                                                                        __Server,                   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                                                        __Service,                  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                                                        __Element,                  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                                                        __AbstractIterator,         // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                                                        __AbstractConstIterator,    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                                                        __Iterator,                 // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                                                        __ConstIterator,            // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::SupplierMemberFunction <__Service, __Iterator>                                      __beginFunction,            // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp,*-member-init)
    functional::SupplierMemberFunction <__Service, __Iterator>                                      __endFunction,              // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp,*-member-init)
    functional::SupplierConstMemberFunction <__Service, __ConstIterator>                            __cbeginFunction,           // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp,*-member-init)
    functional::SupplierConstMemberFunction <__Service, __ConstIterator>                            __cendFunction,             // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp,*-member-init)
    functional::MapperMemberFunction <__Service, __Element*, __Element const*, bool*>               __newAddressFunction,       // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp,*-member-init)
    functional::PredicateMemberFunction <__Service, __AbstractIterator const&>                      __removeFunction,           // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp,*-member-init)
    functional::PredicateMemberFunction <__Service, __AbstractConstIterator const&>                 __removeConstFunction,      // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp,*-member-init)
    functional::MapperMemberFunction <__Service, Size, __AbstractIterator const* const*, Size>      __removeArrayFunction,      // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp,*-member-init)
    functional::MapperMemberFunction <__Service, Size, __AbstractConstIterator const* const*, Size> __removeConstArrayFunction  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp,*-member-init)
> __CDS_cpplang_NonConstConstexprMemberFunction auto __MutableCollectionServerDispatcher <
    __Server, __Service, __Element,
    __AbstractIterator, __AbstractConstIterator, __Iterator, __ConstIterator,
    __beginFunction, __endFunction, __cbeginFunction, __cendFunction,
    __newAddressFunction,
    __removeFunction, __removeConstFunction, __removeArrayFunction, __removeConstArrayFunction
>::__endLocal (__Server* pServer) noexcept -> __Iterator {
  // call the template received member function 
  return (pServer->*__endFunction)();
}


template <
    typename                                                                                        __Server,                   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                                                        __Service,                  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                                                        __Element,                  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                                                        __AbstractIterator,         // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                                                        __AbstractConstIterator,    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                                                        __Iterator,                 // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                                                        __ConstIterator,            // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::SupplierMemberFunction <__Service, __Iterator>                                      __beginFunction,            // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp,*-member-init)
    functional::SupplierMemberFunction <__Service, __Iterator>                                      __endFunction,              // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp,*-member-init)
    functional::SupplierConstMemberFunction <__Service, __ConstIterator>                            __cbeginFunction,           // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp,*-member-init)
    functional::SupplierConstMemberFunction <__Service, __ConstIterator>                            __cendFunction,             // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp,*-member-init)
    functional::MapperMemberFunction <__Service, __Element*, __Element const*, bool*>               __newAddressFunction,       // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp,*-member-init)
    functional::PredicateMemberFunction <__Service, __AbstractIterator const&>                      __removeFunction,           // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp,*-member-init)
    functional::PredicateMemberFunction <__Service, __AbstractConstIterator const&>                 __removeConstFunction,      // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp,*-member-init)
    functional::MapperMemberFunction <__Service, Size, __AbstractIterator const* const*, Size>      __removeArrayFunction,      // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp,*-member-init)
    functional::MapperMemberFunction <__Service, Size, __AbstractConstIterator const* const*, Size> __removeConstArrayFunction  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp,*-member-init)
> __CDS_OptimalInline auto __MutableCollectionServerDispatcher <
    __Server, __Service, __Element,
    __AbstractIterator, __AbstractConstIterator, __Iterator, __ConstIterator,
    __beginFunction, __endFunction, __cbeginFunction, __cendFunction,
    __newAddressFunction,
    __removeFunction, __removeConstFunction, __removeArrayFunction, __removeConstArrayFunction
>::__remove (__Server* pServer, __AbstractIterator const* pIterator) noexcept(false) -> bool {
  // call the template received member function 
  return (pServer->*__removeFunction) (*pIterator);
}


template <
    typename                                                                                        __Server,                   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                                                        __Service,                  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                                                        __Element,                  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                                                        __AbstractIterator,         // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                                                        __AbstractConstIterator,    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                                                        __Iterator,                 // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                                                        __ConstIterator,            // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::SupplierMemberFunction <__Service, __Iterator>                                      __beginFunction,            // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp,*-member-init)
    functional::SupplierMemberFunction <__Service, __Iterator>                                      __endFunction,              // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp,*-member-init)
    functional::SupplierConstMemberFunction <__Service, __ConstIterator>                            __cbeginFunction,           // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp,*-member-init)
    functional::SupplierConstMemberFunction <__Service, __ConstIterator>                            __cendFunction,             // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp,*-member-init)
    functional::MapperMemberFunction <__Service, __Element*, __Element const*, bool*>               __newAddressFunction,       // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp,*-member-init)
    functional::PredicateMemberFunction <__Service, __AbstractIterator const&>                      __removeFunction,           // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp,*-member-init)
    functional::PredicateMemberFunction <__Service, __AbstractConstIterator const&>                 __removeConstFunction,      // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp,*-member-init)
    functional::MapperMemberFunction <__Service, Size, __AbstractIterator const* const*, Size>      __removeArrayFunction,      // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp,*-member-init)
    functional::MapperMemberFunction <__Service, Size, __AbstractConstIterator const* const*, Size> __removeConstArrayFunction  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp,*-member-init)
> __CDS_OptimalInline auto __MutableCollectionServerDispatcher <
    __Server, __Service, __Element,
    __AbstractIterator, __AbstractConstIterator, __Iterator, __ConstIterator,
    __beginFunction, __endFunction, __cbeginFunction, __cendFunction,
    __newAddressFunction,
    __removeFunction, __removeConstFunction, __removeArrayFunction, __removeConstArrayFunction
>::__removeArray (
    __Server*                         pServer,
    __AbstractIterator const* const*  ppIterators,
    Size                              iteratorArrayCount
) noexcept(false) -> Size {
  // call the template received member function 
  return (pServer->*__removeArrayFunction) (ppIterators, iteratorArrayCount);
}
} // namespace __impl 
} // namespace __hidden 
} // namespace cds 

#endif // __CDS_SHARED_MUTABLE_COLLECTION_SERVER_DISPATCHER_IMPL_HPP__ 
