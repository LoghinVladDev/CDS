// NOLINT(llvm-header-guard)
// Created by loghin on 09/07/22.
//

#ifndef __CDS_SHARED_MUTABLE_COLLECTION_SERVER_DISPATCHER_HPP__ // NOLINT(llvm-header-guard)
#define __CDS_SHARED_MUTABLE_COLLECTION_SERVER_DISPATCHER_HPP__ // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
#pragma once

#include "CollectionServerDispatcher.hpp"

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
///      required only for the MutableCollection used handlers.
///
/// \tparam __Server                 is the type of the server interface type (i.e. Array)
/// \tparam __Service                is the type of the implementation service (i.e. shared/__Array)
/// \tparam __Element                is the enclosed element (i.e. int in Array \< int \>)
/// \tparam __Iterator               is the iterator type returned by begin & end (i.e. __a_Iterator for shared/__Array)
/// \tparam __ConstIterator          is the const iterator type returned by begin & end (i.e. __a_ConstIterator for shared/__Array)
/// \tparam __beginFunction              is the function of the implementation used to obtain a begin iterator (i.e. shared/__Array::__a_begin)
/// \tparam __endFunction                is the function of the implementation used to obtain an end iterator (i.e. shared/__Array::__a_begin)
/// \tparam __newAddressFunction         is the function of the implementation used to obtain a new element address (i.e. shared/__Array::__a_newAddress)
/// \tparam __removeFunction             is the function of the implementation used to remove an iterator (i.e. shared/__Array::__a_removeIterator)
/// \tparam __removeConstFunction        is the function of the implementation used to remove a const iterator (i.e. shared/__Array::__a_removeConstIterator)
/// \tparam __removeArrayFunction        is the function of the implementation used to remove multiple iterators (i.e. shared/__Array::__a_removeIteratorArray)
/// \tparam __removeConstArrayFunction   is the function of the implementation used to remove multiple const iterators (i.e. shared/__Array::__a_removeConstIteratorArray)
///
/// \extends __CollectionServerDispatcher
///
/// \test All Tests involving Collections apply
/// \test Suite: CTS-00001, Group: All, Test Cases: All
/// \test Suite: MCTS-00001, Group: All, Test Cases: All
///
/// \namespace cds::__hidden::__impl
/// \internal library-private
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
> class __MutableCollectionServerDispatcher :                                                                                   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp,*-member-init)
    public __CollectionServerDispatcher <
        __Server, __Service, __Element,
        __AbstractConstIterator, __ConstIterator,
        __cbeginFunction, __cendFunction,
        __newAddressFunction,
        __removeConstFunction, __removeConstArrayFunction
    > {
protected:
  /// \brief Function provided by the dispatcher interface calling the received __beginFunction to construct a new delegate iterator using the received iterator
  /// \exceptsafe
  /// \return __AbstractDelegateIterator ptr = Address to newly created delegate iterator
  ///
  /// \test Suite: MCTS-00001, Group: MCTG-00050-IT, Test Cases: All
  /// \protected
  __CDS_NoDiscard static auto __begin (   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      __Server* pServer
  ) noexcept(false) -> __AbstractDelegateIterator <__Element>*;
  
  /// \brief Function provided by the dispatcher interface calling the received __endFunction to construct a new delegate iterator using the received iterator
  /// \exceptsafe
  /// \return __AbstractDelegateIterator ptr = Address to newly created delegate iterator
  ///
  /// \test Suite: MCTS-00001, Group: MCTG-00050-IT, Test Cases: All
  /// \protected
  __CDS_NoDiscard static auto __end ( // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      __Server* pServer
  ) noexcept(false) -> __AbstractDelegateIterator <__Element>*;

  /// \brief Function provided by the dispatcher interface calling the received __beginFunction to return the received iterator. Used by local clients
  /// \exceptsafe
  /// \return __ConstIterator = the const iterator returned by the function
  ///
  /// \test Suite: TBA, Group: TBA, Test Cases: TBA
  /// \protected
  __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction static auto __beginLocal (    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      __Server* pServer
  ) noexcept -> __Iterator;

  /// \brief Function provided by the dispatcher interface calling the received __endFunction to return the received iterator. Used by local clients
  /// \exceptsafe
  /// \return __ConstIterator = the const iterator returned by the function
  ///
  /// \test Suite: TBA, Group: TBA, Test Cases: TBA
  /// \protected
  __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction static auto __endLocal (  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      __Server* pServer
  ) noexcept -> __Iterator;

  /// \brief Function provided by the dispatcher interface calling the received __removeFunction, and is used by the server
  /// \param [in] pIterator : __Iterator cptr = Address to an Immutable Iterator to be removed
  /// \exceptsafe
  /// \return bool = true if iterator was removed, false otherwise
  ///
  /// \test Suite: MCTS-00001, Group: MCTG-00350-RAIT, Test Cases: All
  /// \test Suite: MCTS-00001, Group: MCTG-00400-RB, Test Cases: All
  /// \test Suite: MCTS-00001, Group: MCTG-00450-RO, Test Cases: All
  /// \protected
  static auto __remove ( // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      __Server*                 pServer,
      __AbstractIterator const* pIterator
  ) noexcept(false) -> bool;

  /// \brief Function provided by the dispatcher interface calling the received __removeArrayFunction, and is used by the server
  /// \param [in] ppIterators : __AbstractIterator cptr cptr = Address to an Immutable Array of Immutable Addresses to Iterators to be removed
  /// \param [in] iteratorArrayCount : Size = number of iterator addresses contained in the array
  /// \exceptsafe
  /// \return Size = number of iterators to be removed
  ///
  /// \test Suite: MCTS-00001, Group: MCTG-00400-RB, Test Cases: All
  /// \test Suite: MCTS-00001, Group: MCTG-00450-RO, Test Cases: All
  /// \protected
  static auto __removeArray ( // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      __Server*                         pServer,
      __AbstractIterator  const* const* ppIterators,
      Size                              iteratorArrayCount
  ) noexcept(false) -> Size;
};
} // namespace __impl
} // namespace __hidden
} // namespace cds

#endif // __CDS_SHARED_MUTABLE_COLLECTION_SERVER_DISPATCHER_HPP__
