// NOLINT(llvm-header-guard)
// Created by loghin on 30/10/22.
//

#ifndef __CDS_SHARED_ITERABLE_SERVER_HPP__ // NOLINT(llvm-header-guard)
#define __CDS_SHARED_ITERABLE_SERVER_HPP__ // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
#pragma once

namespace cds {       // NOLINT(modernize-concat-nested-namespaces)
namespace __hidden {  // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
namespace __impl {    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

template <typename __Receiver, typename __Element>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __IterableServer {                            // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
protected:
  /// \typedef Alias for a generic function of the target Collection.
  /// \private
  using __GenericHandler      = functional::ConsumerFunction <Iterable <__Element>*>;    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

  /// \typedef Alias for a generic const function of the target Collection.
  /// \private
  using __GenericConstHandler = functional::ConsumerFunction <Iterable <__Element> const*>;    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

  /// \brief Function used to acquire the List Server Generic Handlers, to be used in
  ///      __cicch_obtainGenericHandler in the 'interface' class ( i.e. Array / LinkedList / ... )
  /// \exceptsafe
  /// \return __GenericHandler cptr = Address to the array of Immutable Generic Handlers
  ///
  /// \test Suite: CTS-00001, Group: All, Test Cases: All
  /// \protected
  __CDS_NoDiscard constexpr auto __is_handlers () const noexcept -> __GenericHandler const*; // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

  /// \brief Function used to acquire the List Server Generic Const Handlers, to be used in
  ///      __cicch_obtainGenericConstHandler in the 'interface' class ( i.e. Array / LinkedList / ... )
  /// \exceptsafe
  /// \return __GenericConstHandler cptr = Address to the array of Immutable Generic Const Handlers
  ///
  /// \test Suite: CTS-00001, Group: All, Test Cases: All
  /// \protected
  __CDS_NoDiscard constexpr auto __is_constHandlers () const noexcept -> __GenericConstHandler const*;   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

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

#endif // __CDS_SHARED_ITERABLE_SERVER_HPP__
