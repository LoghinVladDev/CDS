// NOLINT(llvm-header-guard)
// Created by loghin on 24/07/22.
//

#ifndef __CDS_SHARED_MAP_SERVER_DISPATCHER_HPP__ // NOLINT(llvm-header-guard)
#define __CDS_SHARED_MAP_SERVER_DISPATCHER_HPP__ // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
#pragma once

#include "MutableCollectionServerDispatcher.hpp"

namespace cds {       // NOLINT(modernize-concat-nested-namespaces)
namespace __hidden {  // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
namespace __impl {    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
/// \interface Server-Dispatcher-Type Class part of the Collection Communication Model, to be
///      extended in derived classes as a dispatcher between server requests received
///      through Collection Communication Channels and base implementation. If provides
///      the standard calls required by the server, and enforces the function signatures
///      via template parameters.
///
/// \interface A dispatcher acts as the next layer, a connector between the derived class, that acts
///      as an interface to its' implementation class. This dispatcher interface contains the function
///      required only for the Map used handlers.
///
/// \tparam __Server                 is the type of the server interface type (i.e. Array)
/// \tparam __Service                is the type of the implementation service (i.e. shared/__Array)
/// \tparam __Element                is the enclosed element (i.e. int in Array \< int \>)
/// \tparam __AbstractIterator       is the abstract iterator type used by the remove function. Can be same as iterator type, if accepting only iterator
/// \tparam __AbstractConstIterator  is the abstract const iterator type used by the remove const function. Can be same as const iterator type, if accepting only const iterator
/// \tparam __Iterator               is the iterator type returned by begin & end (i.e. __a_Iterator for shared/__Array)
/// \tparam __ConstIterator          is the const iterator type returned by begin & end (i.e. __a_ConstIterator for shared/__Array)
/// \tparam __beginFunction              is the function of the implementation used to obtain a begin iterator (i.e. shared/__Array::__a_begin)
/// \tparam __beginFunction              is the function of the implementation used to obtain an end iterator (i.e. shared/__Array::__a_end)
/// \tparam __cbeginFunction             is the function of the implementation used to obtain a begin const iterator (i.e. shared/__Array::__a_cbegin)
/// \tparam __cendFunction               is the function of the implementation used to obtain an end const iterator (i.e. shared/__Array::__a_cbegin)
/// \tparam __newAddressFunction         is the function of the implementation used to obtain a new element address (i.e. shared/__Array::__a_newAddress)
/// \tparam __removeFunction             is the function of the implementation used to remove an iterator (i.e. shared/__Array::__a_removeIterator)
/// \tparam __removeConstFunction        is the function of the implementation used to remove a const iterator (i.e. shared/__Array::__a_removeConstIterator)
/// \tparam __removeArrayFunction        is the function of the implementation used to remove multiple iterators (i.e. shared/__Array::__a_removeIteratorArray)
/// \tparam __removeConstArrayFunction   is the function of the implementation used to remove multiple const iterators (i.e. shared/__Array::__a_removeConstIteratorArray)
/// \tparam __findFunction               is the function of the implementation used to find an element and return an iterator (i.e. shared/__HashTable::__ht_find)
/// \tparam __findConstFunction          is the function of the implementation used to find an element and return a const iterator (i.e. shared/__HashTable::__ht_findConst)
///
/// \extends __MutableCollectionServerDispatcher
///
/// \test All Tests involving Collections apply
/// \test Suite: CTS-00001, Group: All, Test Cases: All
///
/// \namespace cds::__hidden::__impl
/// \internal library-private
template <
    typename                                                                                        __Server,                   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                                                        __Service,                  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                                                        __Element,                  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                                                        __Key,                      // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
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
    functional::MapperMemberFunction <__Service, Size, __AbstractConstIterator const* const*, Size> __removeConstArrayFunction, // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp,*-member-init)
    functional::MapperMemberFunction <__Service, __Iterator, __Key const&>                          __findFunction,             // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp,*-member-init)
    functional::MapperConstMemberFunction <__Service, __ConstIterator, __Key const&>                __findConstFunction         // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp,*-member-init)
> class __MapServerDispatcher :                                                                                                 // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __MutableCollectionServerDispatcher <
        __Server, __Service, __Element,
        __AbstractIterator, __AbstractConstIterator, __Iterator, __ConstIterator,
        __beginFunction, __endFunction, __cbeginFunction, __cendFunction,
        __newAddressFunction,
        __removeFunction, __removeConstFunction, __removeArrayFunction, __removeConstArrayFunction
    > {
protected:
  /// \brief Function provided by the dispatcher interface calling the received __findConstFunction, and is used by the server to construct a new delegate iterator using the received iterator
  /// \param [in] element : __Element cref = Constant Reference to an element to look for
  /// \exceptsafe
  /// \return __AbstractDelegateIterator ptr = Address to newly created delegate iterator
  ///
  /// \test Suite: TBA, Group: TBA, Test Cases: TBA
  /// \protected
  static auto __find ( // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      __Server*     pServer,
      __Key const&  key
  ) noexcept(false) -> __AbstractDelegateIterator <__Element>*;

  /// \brief Function provided by the dispatcher interface calling the received __findConstFunction, and is used by the server to construct a new delegate iterator using the received iterator
  /// \param [in] element : __Element cref = Constant Reference to an element to look for
  /// \exceptsafe
  /// \return __AbstractDelegateIterator ptr = Address to newly created delegate iterator
  ///
  /// \test Suite: TBA, Group: TBA, Test Cases: TBA
  /// \protected
  static auto __findConst ( // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      __Server const* pServer,
      __Key const&    key
  ) noexcept -> __AbstractDelegateIterator <__Element const>*;

  /// \brief Function provided by the dispatcher interface calling the received __findConstFunction, and is used by the server to return the received iterator. Used by local clients
  /// \param [in] element : __Element cref = Constant Reference to an element to look for
  /// \exceptsafe
  /// \return __Iterator = An iterator indicating to the element given as a parameter
  ///
  /// \test Suite: TBA, Group: TBA, Test Cases: TBA
  /// \protected
  static auto __findLocal ( // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      __Server*     pServer,
      __Key const&  key
  ) noexcept(false) -> __Iterator;

  /// \brief Function provided by the dispatcher interface calling the received __findConstFunction, and is used by the server to return the received iterator. Used by local clients
  /// \param [in] element : __Element cref = Constant Reference to an element to look for
  /// \exceptsafe
  /// \return __ConstIterator = An iterator indicating to the element given as a parameter
  ///
  /// \test Suite: TBA, Group: TBA, Test Cases: TBA
  /// \protected
  static auto __findConstLocal ( // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      __Server const* pServer,
      __Key const&    key
  ) noexcept -> __ConstIterator;
};

} // namespace __impl
} // namespace __hidden
} // namespace cds

#endif // __CDS_SHARED_MAP_SERVER_DISPATCHER_HPP__

