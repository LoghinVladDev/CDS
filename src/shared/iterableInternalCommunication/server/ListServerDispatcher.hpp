// NOLINT(llvm-header-guard)
// Created by loghin on 09/07/22.
//

#ifndef __CDS_SHARED_LIST_SERVER_DISPATCHER_HPP__ // NOLINT(llvm-header-guard)
#define __CDS_SHARED_LIST_SERVER_DISPATCHER_HPP__ // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
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
///      required only for the MutableCollection used handlers.
///
/// \tparam __Server                     is the type of the server interface type (i.e. Array)
/// \tparam __Service                    is the type of the implementation service (i.e. shared/__Array)
/// \tparam __Element                    is the enclosed element (i.e. int in Array \< int \>)
/// \tparam __AbstractIterator           is the abstract iterator type used by the remove, insert before/after functions. Can be same as iterator type, if accepting only iterator
/// \tparam __AbstractConstIterator      is the abstract const iterator type used by the remove const, insert before/after const functions. Can be same as const iterator type, if accepting only const iterator
/// \tparam __Iterator                   is the iterator type returned by begin & end (i.e. __a_Iterator for shared/__Array)
/// \tparam __ConstIterator              is the const iterator type returned by begin & end (i.e. __a_ConstIterator for shared/__Array)
/// \tparam __ReverseIterator            is the reverse iterator type returned by rbegin & rend (i.e. __a_ReverseIterator for shared/__Array)
/// \tparam __ConstReverseIterator       is the const reverse iterator type returned by rbegin & rend (i.e. __a_ConstReverseIterator for shared/__Array)
/// \tparam __beginFunction                  is the function of the implementation used to obtain a begin iterator (i.e. shared/__Array::__a_begin)
/// \tparam __beginFunction                  is the function of the implementation used to obtain an end iterator (i.e. shared/__Array::__a_end)
/// \tparam __cbeginFunction                 is the function of the implementation used to obtain a begin const iterator (i.e. shared/__Array::__a_cbegin)
/// \tparam __cendFunction                   is the function of the implementation used to obtain an end const iterator (i.e. shared/__Array::__a_cbegin)
/// \tparam __rbeginFunction                 is the function of the implementation used to obtain a reverse begin iterator (i.e. shared/__Array::__a_rbegin)
/// \tparam __rendFunction                   is the function of the implementation used to obtain an reverse end iterator (i.e. shared/__Array::__a_rend)
/// \tparam __crbeginFunction                is the function of the implementation used to obtain a reverse begin const iterator (i.e. shared/__Array::__a_crbegin)
/// \tparam __crendFunction                  is the function of the implementation used to obtain an reverse end const iterator (i.e. shared/__Array::__a_crbegin)
/// \tparam __newAddressFunction             is the function of the implementation used to obtain a new element address (i.e. shared/__Array::__a_newAddress)
/// \tparam __newFrontFunction               is the function of the implementation used to obtain a new element address at the front of the list (i.e. shared/__Array::__a_newFront)
/// \tparam __newBackFunction                is the function of the implementation used to obtain a new element address at the end of the list (i.e. shared/__Array::__a_newBack)
/// \tparam __newFrontArrayFunction          is the function of the implementation used to populate an array with new addresses at the front of the list (i.e. shared/__Array::__a_newFrontArray)
/// \tparam __newBackArrayFunction           is the function of the implementation used to populate an array with new addresses at the back of the list (i.e. shared/__Array::__a_newBackArray)
/// \tparam __newBeforeFunction              is the function of the implementation used to obtain a new element address before an iterator (i.e. shared/__Array::__a_newBefore)
/// \tparam __newBeforeConstFunction         is the function of the implementation used to obtain a new element address before a const iterator (i.e. shared/__Array::__a_newBeforeConst)
/// \tparam __newAfterFunction               is the function of the implementation used to obtain a new element address after an iterator (i.e. shared/__Array::__a_newAfter)
/// \tparam __newAfterConstFunction          is the function of the implementation used to obtain a new element address after a const iterator (i.e. shared/__Array::__a_newAfterConst)
/// \tparam __newBeforeArrayFunction         is the function of the implementation used to populate an array with new addresses before an iterator (i.e. shared/__Array::__a_newBeforeArray)
/// \tparam __newBeforeArrayConstFunction    is the function of the implementation used to populate an array with new addresses before a const iterator (i.e. shared/__Array::__a_newBeforeArrayConst)
/// \tparam __newAfterArrayFunction          is the function of the implementation used to populate an array with new addresses after an iterator (i.e. shared/__Array::__a_newAfterArray)
/// \tparam __newAfterArrayConstFunction     is the function of the implementation used to populate an array with new addresses after a const iterator (i.e. shared/__Array::__a_newAfterArrayConst)
/// \tparam __removeFunction                 is the function of the implementation used to remove an iterator (i.e. shared/__Array::__a_removeIterator)
/// \tparam __removeConstFunction            is the function of the implementation used to remove a const iterator (i.e. shared/__Array::__a_removeConstIterator)
/// \tparam __removeArrayFunction            is the function of the implementation used to remove multiple iterators (i.e. shared/__Array::__a_removeIteratorArray)
/// \tparam __removeConstArrayFunction       is the function of the implementation used to remove multiple const iterators (i.e. shared/__Array::__a_removeConstIteratorArray)
///
/// \extends __MutableCollectionServerDispatcher
///
/// \test All Tests involving Collections apply
/// \test Suite: CTS-00001, Group: All, Test Cases: All
///
/// \namespace cds::__hidden::__impl
/// \internal library-private
template <
    typename                                                                                            __Server,                       // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                                                            __Service,                      // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                                                            __Element,                      // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                                                            __AbstractIterator,             // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                                                            __AbstractConstIterator,        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                                                            __Iterator,                     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                                                            __ConstIterator,                // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                                                            __ReverseIterator,              // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                                                            __ConstReverseIterator,         // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::SupplierMemberFunction <__Service, __Iterator>                                          __beginFunction,                // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::SupplierMemberFunction <__Service, __Iterator>                                          __endFunction,                  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::SupplierConstMemberFunction <__Service, __ConstIterator>                                __cbeginFunction,               // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::SupplierConstMemberFunction <__Service, __ConstIterator>                                __cendFunction,                 // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::SupplierMemberFunction <__Service, __ReverseIterator>                                   __rbeginFunction,               // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::SupplierMemberFunction <__Service, __ReverseIterator>                                   __rendFunction,                 // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::SupplierConstMemberFunction <__Service, __ConstReverseIterator>                         __crbeginFunction,              // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::SupplierConstMemberFunction <__Service, __ConstReverseIterator>                         __crendFunction,                // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::MapperMemberFunction <__Service, __Element*, __Element const*, bool*>                   __newAddressFunction,           // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::SupplierMemberFunction <__Service, __Element*>                                          __newFrontFunction,             // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::SupplierMemberFunction <__Service, __Element*>                                          __newBackFunction,              // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::ConsumerMemberFunction <__Service, Size, __Element**>                                   __newFrontArrayFunction,        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::ConsumerMemberFunction <__Service, Size, __Element**>                                   __newBackArrayFunction,         // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::MapperMemberFunction <__Service, __Element*, __AbstractIterator const&>                 __newBeforeFunction,            // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::MapperMemberFunction <__Service, __Element*, __AbstractConstIterator const&>            __newBeforeConstFunction,       // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::MapperMemberFunction <__Service, __Element*, __AbstractIterator const&>                 __newAfterFunction,             // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::MapperMemberFunction <__Service, __Element*, __AbstractConstIterator const&>            __newAfterConstFunction,        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateMemberFunction <__Service, __AbstractIterator const&, Size, __Element**>       __newBeforeArrayFunction,       // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateMemberFunction <__Service, __AbstractConstIterator const&, Size, __Element**>  __newBeforeArrayConstFunction,  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateMemberFunction <__Service, __AbstractIterator const&, Size, __Element**>       __newAfterArrayFunction,        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateMemberFunction <__Service, __AbstractConstIterator const&, Size, __Element**>  __newAfterArrayConstFunction,   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateMemberFunction <__Service, __AbstractIterator const&>                          __removeFunction,               // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateMemberFunction <__Service, __AbstractConstIterator const&>                     __removeConstFunction,          // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::MapperMemberFunction <__Service, Size, __AbstractIterator const* const*, Size>          __removeArrayFunction,          // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::MapperMemberFunction <__Service, Size, __AbstractConstIterator const* const*, Size>     __removeConstArrayFunction      // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> class __ListServerDispatcher :                                                                                                        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp,*-member-init)
    public __MutableCollectionServerDispatcher <
        __Server, __Service, __Element,
        __AbstractIterator, __AbstractConstIterator, __Iterator, __ConstIterator,
        __beginFunction, __endFunction, __cbeginFunction, __cendFunction,
        __newAddressFunction,
        __removeFunction, __removeConstFunction, __removeArrayFunction, __removeConstArrayFunction
    > {
protected:
  /// \brief Function provided by the dispatcher interface calling the received __rbeginFunction to construct a new delegate iterator using the received iterator
  /// \exceptsafe
  /// \return __AbstractDelegateIterator ptr = Address to newly created delegate iterator
  ///
  /// \test Suite: TBA, Group: TBA, Test Cases: TBA
  /// \protected
  __CDS_NoDiscard static auto __rbegin (  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      __Server* pServer
  ) noexcept(false) -> __AbstractDelegateIterator <__Element>*;

  /// \brief Function provided by the dispatcher interface calling the received __rendFunction to construct a new delegate iterator using the received iterator
  /// \exceptsafe
  /// \return __AbstractDelegateIterator ptr = Address to newly created delegate iterator
  ///
  /// \test Suite: TBA, Group: TBA, Test Cases: TBA
  /// \protected
  __CDS_NoDiscard static auto __rend (    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      __Server* pServer
  ) noexcept(false) -> __AbstractDelegateIterator <__Element>*;

  /// \brief Function provided by the dispatcher interface calling the received __crbeginFunction to construct a new delegate iterator using the received iterator
  /// \exceptsafe
  /// \return __AbstractDelegateIterator ptr = Address to newly created delegate iterator
  ///
  /// \test Suite: TBA, Group: TBA, Test Cases: TBA
  /// \protected
  __CDS_NoDiscard static auto __crbegin ( // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      __Server const* pServer
  ) noexcept(false) -> __AbstractDelegateIterator <__Element const>*;
  
  /// \brief Function provided by the dispatcher interface calling the received __crendFunction to construct a new delegate iterator using the received iterator
  /// \exceptsafe
  /// \return __AbstractDelegateIterator ptr = Address to newly created delegate iterator
  ///
  /// \test Suite: TBA, Group: TBA, Test Cases: TBA
  /// \protected
  __CDS_NoDiscard static auto __crend (   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      __Server const* pServer
  ) noexcept(false) -> __AbstractDelegateIterator <__Element const>*;

  /// \brief Function provided by the dispatcher interface calling the received __rbeginFunction to return the received iterator. Used by local clients
  /// \exceptsafe
  /// \return __ConstIterator = the const iterator returned by the function
  ///
  /// \test Suite: TBA, Group: TBA, Test Cases: TBA
  /// \protected
  __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction static auto __rbeginLocal (   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      __Server* pServer
  ) noexcept -> __ReverseIterator;

  /// \brief Function provided by the dispatcher interface calling the received __rendFunction to return the received iterator. Used by local clients
  /// \exceptsafe
  /// \return __ConstIterator = the const iterator returned by the function
  ///
  /// \test Suite: TBA, Group: TBA, Test Cases: TBA
  /// \protected
  __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction static auto __rendLocal ( // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      __Server* pServer
  ) noexcept -> __ReverseIterator;

  /// \brief Function provided by the dispatcher interface calling the received __crbeginFunction to return the received iterator. Used by local clients
  /// \exceptsafe
  /// \return __ConstIterator = the const iterator returned by the function
  ///
  /// \test Suite: TBA, Group: TBA, Test Cases: TBA
  /// \protected
  __CDS_NoDiscard constexpr static auto __crbeginLocal (  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      __Server const* pServer
  ) noexcept -> __ConstReverseIterator;

  /// \brief Function provided by the dispatcher interface calling the received __crendFunction to return the received iterator. Used by local clients
  /// \exceptsafe
  /// \return __ConstIterator = the const iterator returned by the function
  ///
  /// \test Suite: TBA, Group: TBA, Test Cases: TBA
  /// \protected
  __CDS_NoDiscard constexpr static auto __crendLocal (    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      __Server const* pServer
  ) noexcept -> __ConstReverseIterator;

  /// \brief Function provided by the dispatcher interface calling the received __newFrontFunction, and is used by the server
  /// \exceptsafe
  /// \return __Element ptr = Address to the newly created element
  ///
  /// \test Suite: TBA, Group: TBA, Test Cases: TBA
  /// \protected
  static auto __newFront (    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      __Server* pServer
  ) noexcept(false) -> __Element*;

  /// \brief Function provided by the dispatcher interface calling the received __newBackFunction, and is used by the server
  /// \exceptsafe
  /// \return __Element ptr = Address to the newly created element
  ///
  /// \test Suite: TBA, Group: TBA, Test Cases: TBA
  /// \protected
  static auto __newBack ( // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      __Server* pServer
  ) noexcept(false) -> __Element*;

  /// \brief Function provided by the dispatcher interface calling the received __newFrontArrayFunction, and is used by the server
  /// \param [in] count : Size = number of elements to allocate
  /// \param [in] ppElements : __Element ptr ptr = Address to the array of addresses to populate
  /// \exceptsafe
  ///
  /// \test Suite: TBA, Group: TBA, Test Cases: TBA
  /// \protected
  static auto __newFrontArray ( // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      __Server*   pServer,
      Size        count,
      __Element** ppElements
  ) noexcept(false) -> void;

  /// \brief Function provided by the dispatcher interface calling the received __newBackArrayFunction, and is used by the server
  /// \param [in] count : Size = number of elements to allocate
  /// \param [in] ppElements : __Element ptr ptr = Address to the array of addresses to populate
  /// \exceptsafe
  ///
  /// \test Suite: TBA, Group: TBA, Test Cases: TBA
  /// \protected
  static auto __newBackArray ( // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      __Server*   pServer,
      Size        count,
      __Element** ppElements
  ) noexcept(false) -> void;

  /// \brief Function provided by the dispatcher interface calling the received __newBeforeFunction, and is used by the server
  /// \param [in] pIterator : __Iterator cptr = Address to an Immutable iterator
  /// \exceptsafe
  /// \return __Element ptr = Address to the newly created element
  ///
  /// \test Suite: TBA, Group: TBA, Test Cases: TBA
  /// \protected
  static auto __newBefore ( // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      __Server*                 pServer,
      __AbstractIterator const* pIterator
  ) noexcept(false) -> __Element*;

  /// \brief Function provided by the dispatcher interface calling the received __newBeforeConstFunction, and is used by the server
  /// \param [in] pIterator : __ConstIterator cptr = Address to an Immutable const iterator
  /// \exceptsafe
  /// \return __Element ptr = Address to the newly created element
  ///
  /// \test Suite: TBA, Group: TBA, Test Cases: TBA
  /// \protected
  static auto __newBeforeConst ( // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      __Server*                       pServer,
      __AbstractConstIterator const*  pIterator
  ) noexcept(false) -> __Element*;

  /// \brief Function provided by the dispatcher interface calling the received __newAfterFunction, and is used by the server
  /// \param [in] pIterator : __Iterator cptr = Address to an Immutable iterator
  /// \exceptsafe
  /// \return __Element ptr = Address to the newly created element
  ///
  /// \test Suite: TBA, Group: TBA, Test Cases: TBA
  /// \protected
  static auto __newAfter ( // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      __Server*                 pServer,
      __AbstractIterator const* pIterator
  ) noexcept(false) -> __Element*;

  /// \brief Function provided by the dispatcher interface calling the received __newAfterConstFunction, and is used by the server
  /// \param [in] pIterator : __ConstIterator cptr = Address to an Immutable const iterator
  /// \exceptsafe
  /// \return __Element ptr = Address to the newly created element
  ///
  /// \test Suite: TBA, Group: TBA, Test Cases: TBA
  /// \protected
  static auto __newAfterConst ( // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      __Server*                       pServer,
      __AbstractConstIterator const*  pIterator
  ) noexcept(false) -> __Element*;

  /// \brief Function provided by the dispatcher interface calling the received __newBeforeArrayFunction, and is used by the server
  /// \param [in] pIterator : __Iterator cptr = Address to an Immutable iterator
  /// \param [in] count : Size = number of elements to allocate
  /// \param [in, out] ppElements : __Element ptr ptr = Address to the array of addresses to populate
  /// \exceptsafe
  ///
  /// \test Suite: TBA, Group: TBA, Test Cases: TBA
  /// \protected
  static auto __newBeforeArray ( // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      __Server*                 pServer,
      __AbstractIterator const* pIterator,
      Size                      count,
      __Element**               ppElements
  ) noexcept(false) -> bool;

  /// \brief Function provided by the dispatcher interface calling the received __newBeforeArrayConstFunction, and is used by the server
  /// \param [in] pIterator : __ConstIterator cptr = Address to an Immutable const iterator
  /// \param [in] count : Size = number of elements to allocate
  /// \param [in, out] ppElements : __Element ptr ptr = Address to the array of addresses to populate
  /// \exceptsafe
  ///
  /// \test Suite: TBA, Group: TBA, Test Cases: TBA
  /// \protected
  static auto __newBeforeArrayConst ( // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      __Server*                       pServer,
      __AbstractConstIterator const*  pIterator,
      Size                            count,
      __Element**                     ppElements
  ) noexcept(false) -> bool;

  /// \brief Function provided by the dispatcher interface calling the received __newAfterArrayFunction, and is used by the server
  /// \param [in] pIterator : __Iterator cptr = Address to an Immutable iterator
  /// \param [in] count : Size = number of elements to allocate
  /// \param [in, out] ppElements : __Element ptr ptr = Address to the array of addresses to populate
  /// \exceptsafe
  ///
  /// \test Suite: TBA, Group: TBA, Test Cases: TBA
  /// \protected
  static auto __newAfterArray ( // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      __Server*                 pServer,
      __AbstractIterator const* pIterator,
      Size                      count,
      __Element**               ppElements
  ) noexcept(false) -> bool;

  /// \brief Function provided by the dispatcher interface calling the received __newAfterArrayConstFunction, and is used by the server
  /// \param [in] pIterator : __ConstIterator cptr = Address to an Immutable const iterator
  /// \param [in] count : Size = number of elements to allocate
  /// \param [in, out] ppElements : __Element ptr ptr = Address to the array of addresses to populate
  /// \exceptsafe
  ///
  /// \test Suite: TBA, Group: TBA, Test Cases: TBA
  /// \protected
  static auto __newAfterArrayConst ( // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      __Server*                       pServer,
      __AbstractConstIterator const*  pIterator,
      Size                            count,
      __Element**                     ppElements
  ) noexcept(false) -> bool;
};

} // namespace __impl
} // namespace __hidden
} // namespace cds

#endif // __CDS_SHARED_LIST_SERVER_DISPATCHER_HPP__
