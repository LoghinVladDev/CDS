// NOLINT(llvm-header-guard)
// Created by loghin on 09/07/22.
//

#ifndef __CDS_SHARED_COLLECTION_SERVER_DISPATCHER_HPP__ // NOLINT(llvm-header-guard)
#define __CDS_SHARED_COLLECTION_SERVER_DISPATCHER_HPP__ // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
#pragma once

#include "IterableServerDispatcher.hpp"

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
///      required only for the Collection used handlers.
///
/// \tparam __Server                 is the type of the server interface type (i.e. Array)
/// \tparam __Service                is the type of the implementation service (i.e. shared/__Array)
/// \tparam __Element                is the enclosed element (i.e. int in Array \< int \>)
/// \tparam __AbstractConstIterator  is the abstract const iterator type used by the remove const function. Can be same as const iterator type, if accepting only const iterator
/// \tparam __ConstIterator          is the const iterator type returned by begin & end (i.e. __a_ConstIterator for shared/__Array)
/// \tparam __cbeginFunction             is the function of the implementation used to obtain a begin const iterator (i.e. shared/__Array::__a_cbegin)
/// \tparam __cendFunction               is the function of the implementation used to obtain an end const iterator (i.e. shared/__Array::__a_cbegin)
/// \tparam __newAddressFunction         is the function of the implementation used to obtain a new element address (i.e. shared/__Array::__a_newAddress)
/// \tparam __removeConstFunction        is the function of the implementation used to remove a const iterator (i.e. shared/__Array::__a_removeConstIterator)
/// \tparam __removeConstArrayFunction   is the function of the implementation used to remove multiple const iterators (i.e. shared/__Array::__a_removeConstIteratorArray)
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
    typename                                                                                        __AbstractConstIterator,    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                                                        __ConstIterator,            // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::SupplierConstMemberFunction <__Service, __ConstIterator>                            __cbeginFunction,           // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::SupplierConstMemberFunction < __Service, __ConstIterator >                          __cendFunction,             // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::MapperMemberFunction <__Service, __Element*, __Element const*, bool*>               __newAddressFunction,       // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateMemberFunction <__Service, __AbstractConstIterator const&>                 __removeConstFunction,      // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::MapperMemberFunction <__Service, Size, __AbstractConstIterator const* const*, Size> __removeConstArrayFunction  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> class __CollectionServerDispatcher :                                                                                          // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __IterableServerDispatcher <__Server, __Service, __Element, __ConstIterator, __cbeginFunction, __cendFunction> {
protected:
  /// \brief Function provided by the dispatcher interface calling the received __newAddressFunction, and is used by the server
  /// \param [in] pReferenceElement : __Element cptr = Address to an Immutable element to be used as a reference for insertion ( i.e. Set duplicate avoidance )
  /// \param [in, out] pNewElementCreated : bool ptr = Address to a boolean variable to be set to 'true' if a new address was returned, 'false' otherwise
  /// \exceptsafe
  /// \return __Element ptr = An address to an element, to a new one or to an existing one
  ///
  /// \test Suite: CTS-00001, Group: CTG-00800-RI, Test Cases: All
  /// \protected
  static auto __newAddress ( // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      __Server*         pServer,
      __Element const*  pReferenceElement,
      bool*             pNewElementCreated
  ) noexcept(false) -> __Element*;

  /// \brief Function provided by the dispatcher interface calling the received __removeConstFunction, and is used by the server
  /// \param [in] pIterator : __AbstractConstIterator cptr = Address to an Immutable Constant Iterator to be removed
  /// \exceptsafe
  /// \return bool = true if iterator was removed, false otherwise
  ///
  /// \test Suite: CTS-00001, Group: CTG-00350-RAIT, Test Cases: All
  /// \test Suite: CTS-00001, Group: CTG-00400-RB, Test Cases: All
  /// \test Suite: CTS-00001, Group: CTG-00450-RO, Test Cases: All
  /// \protected
  static auto __removeConst ( // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      __Server*                       pServer,
      __AbstractConstIterator const*  pIterator
  ) noexcept(false) -> bool;

  /// \brief Function provided by the dispatcher interface calling the received __removeConstArrayFunction, and is used by the server
  /// \param [in] ppIterators : __AbstractConstIterator cptr cptr = Address to an Immutable Array of Immutable Addresses to Constant Iterators to be removed
  /// \param [in] iteratorArrayCount : Size = number of iterator addresses contained in the array
  /// \exceptsafe
  /// \return Size = number of iterators to be removed
  ///
  /// \test Suite: CTS-00001, Group: CTG-00400-RB, Test Cases: All
  /// \test Suite: CTS-00001, Group: CTG-00450-RO, Test Cases: All
  /// \protected
  static auto __removeConstArray ( // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      __Server*                             pServer,
      __AbstractConstIterator const* const* ppIterators,
      Size                                  iteratorArrayCount
  ) noexcept(false) -> Size;
};
} // namespace __impl
} // namespace __hidden
} // namespace cds

#endif // __CDS_SHARED_COLLECTION_SERVER_DISPATCHER_HPP__
