//
// Created by loghin on 4/26/22.
//

#ifndef __CDS_SHARED_ITERABLE_INTERNAL_REQUEST_TYPE_HPP__ // NOLINT(llvm-header-guard)
#define __CDS_SHARED_ITERABLE_INTERNAL_REQUEST_TYPE_HPP__ // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
#pragma once

namespace cds {       // NOLINT(modernize-concat-nested-namespaces)
namespace __hidden {  // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
namespace __impl {    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

/// \enum The types of delegate iterator requests the Iterable Base Object can make to its Derived Objects when acquiring an Iterator Delegate Implementation
/// \test Suite: CTS-00001, Group: CTG-00050-IT, Test Cases: All
enum class __IterableInternalRequest {          // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

  /// Represents a Request for a Beginning Iterator, Advancing Forward
  __iir_begin                        = 0x00u,    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

  /// Represents a Request for an End Iterator, Advancing Forward
  __iir_end                          = 0x01u,    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

  /// Represents a Request for a Beginning Iterator, Advancing Backwards ( reverse iteration )
  __iir_rbegin                       = 0x02u,    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

  /// Represents a Request for a End Iterator, Advancing Backwards ( reverse iteration )
  __iir_rend                         = 0x03u,    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

  /// Represents a Request for a removal of an element pointed to at by an iterator
  __iir_remove                       = 0x04u,    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

  /// Represents a Request for a removal of an element pointed to at by a const iterator
  __iir_removeConst                  = 0x05u,    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

  /// Represents a Request for a removal of multiple iterators via a pointer array
  __iir_removeArray                  = 0x06u,    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

  /// Represents a Request for a removal of multiple const iterators via a pointer array
  __iir_removeConstArray             = 0x07u,    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

  /// Represents a Request for a new element address
  __iir_newAddress                   = 0x08u,    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

  /// Represents a Request for a new element address at the front of the iterable
  __iir_newFrontAddress              = 0x09u,    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

  /// Represents a Request for a new element address at the back of the iterable
  __iir_newBackAddress               = 0x0Au,    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

  /// Represents a Request for multiple elements addresses at the front of the iterable
  __iir_newFrontAddressArray         = 0x0Bu,    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

  /// Represents a Request for multiple elements addresses at the back of the iterable
  __iir_newBackAddressArray          = 0x0Cu,    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

  /// Represents a Request for a new element address before a given abstract iterator
  __iir_newBeforeAddress             = 0x0Du,    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

  /// Represents a Request for a new element address before a given abstract const iterator
  __iir_newBeforeAddressConst        = 0x0Eu,    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

  /// Represents a Request for a new element address after a given abstract iterator
  __iir_newAfterAddress              = 0x0Fu,    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

  /// Represents a Request for a new element address after a given abstract const iterator
  __iir_newAfterAddressConst         = 0x10u,    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

  /// Represents a Request for multiple element addresses before a given abstract iterator
  __iir_newBeforeAddressArray        = 0x11u,    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

  /// Represents a Request for multiple element addresses before a given abstract const iterator
  __iir_newBeforeAddressArrayConst   = 0x12u,    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

  /// Represents a Request for multiple element addresses after a given abstract iterator
  __iir_newAfterAddressArray         = 0x13u,    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

  /// Represents a Request for multiple element addresses after a given abstract const iterator
  __iir_newAfterAddressArrayConst    = 0x14u,    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

  /// Represents a Request for finding an iterator to an element by key/value
  __iir_find                         = 0x15u,    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

  /// Represents a Request for finding a const iterator to an element by key/value
  __iir_findConst                    = 0x16u,    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

  /// Represents the number of possible requests, not to be used in requests
  __iir_requestCountDoNotUse         = 0x17u     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
};

} // namespace __impl
} // namespace __hidden
} // namespace cds

#endif // __CDS_SHARED_ITERABLE_INTERNAL_REQUEST_TYPE_HPP__
