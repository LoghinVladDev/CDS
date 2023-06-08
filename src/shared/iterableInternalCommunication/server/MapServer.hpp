// NOLINT(llvm-header-guard)
// Created by loghin on 7/3/22.
//

#ifndef __CDS_SHARED_MAP_SERVER_HPP__ // NOLINT(llvm-header-guard)
#define __CDS_SHARED_MAP_SERVER_HPP__ // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
#pragma once

namespace cds {       // NOLINT(modernize-concat-nested-namespaces)
namespace __hidden {  // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
namespace __impl {    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

/// \interface Server-Type Class part of Collection Communication Model, to be extended in derived classes that act
///      as a router for requests made through Collection Communication Channels. Provides the
///      request table that is standard for Map-Type Collections. Also enforces existence
///      of these functions in the derived class. It does NOT enforce the type of these
///      functions, and this must be either done manually, or a Dispatcher has to be used
///
/// \interface A dispatcher acts as the next layer, a connector between the derived class, that acts
///      as an interface to its' implementation class ( i.e. HashMap = interface, shared/__HashTable =
///          implementation, and shared/__HashTable::__MapDispatcher = dispatcher. The HashMap class
///          must derive the implementation, the dispatcher and the MapServer, as the
///          Server will receive requests, it will handle them to the dispatcher, which will
///          handle them to the implementation, statically, without branching
///      )
///
/// \tparam __Receiver is the type of the interface ( HashMap / LinkedHashMap / TreeMap / ... )
/// \tparam __Element is the type enclosed in the interface collection ( MapEntry \< int, int \> from HashMap \< int, int \> )
///
/// \test All Tests involving Collections apply
/// \test Suite: CTS-00001, Group: All, Test Cases: All
///
/// \namespace cds::__hidden::__impl
/// \internal library-private
template <typename __Receiver, typename __Element>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __MapServer {                                 // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
protected:
  /// \typedef Alias for a generic function of the target Collection.
  /// \private
  using __GenericHandler      = functional::ConsumerFunction <Iterable <__Element>*>;    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

  /// \typedef Alias for a generic const function of the target Collection.
  /// \private
  using __GenericConstHandler = functional::ConsumerFunction <Iterable <__Element> const*>;    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

  /// \brief Function used to acquire the Map Server Generic Handlers, to be used in
  ///      __cicch_obtainGenericHandler in the 'interface' class ( i.e. HashMap / LinkedHashMap / TreeMap / ... )
  /// \exceptsafe
  /// \return __GenericHandler cptr = Address to the array of Immutable Generic Handlers
  ///
  /// \test Suite: CTS-00001, Group: All, Test Cases: All
  /// \protected
  __CDS_NoDiscard constexpr auto __ms_handlers () const noexcept -> __GenericHandler const*; // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

  /// \brief Function used to acquire the Map Server Generic Const Handlers, to be used in
  ///      __cicch_obtainGenericConstHandler in the 'interface' class ( i.e. HashMap / LinkedHashMap / TreeMap / ... )
  /// \exceptsafe
  /// \return __GenericConstHandler cptr = Address to the array of Immutable Generic Const Handlers
  ///
  /// \test Suite: CTS-00001, Group: All, Test Cases: All
  /// \protected
  __CDS_NoDiscard constexpr auto __ms_constHandlers () const noexcept -> __GenericConstHandler const*;   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

private:
  /// \brief routing table of the generic functions. One for each request type.
  /// \static
  /// \private
  static __GenericHandler const __routingTable [   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp,*-c-arrays)
      static_cast <uint32> (__IterableInternalRequest::__iir_requestCountDoNotUse)
  ];

  /// \brief routing table of the generic const functions. One for each request type.
  /// \static
  /// \private
  static __GenericConstHandler const __constRoutingTable [   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp,*-c-arrays)
      static_cast <uint32> (__IterableInternalRequest::__iir_requestCountDoNotUse)
  ];
};

} // namespace __impl
} // namespace __hidden
} // namespace cds

#endif // __CDS_SHARED_MAP_SERVER_HPP__
