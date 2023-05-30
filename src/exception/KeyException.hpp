//
// Created by loghin on 30/11/22.
//

#ifndef __CDS_KEY_EXCEPTION_HPP__ // NOLINT(llvm-header-guard)
#define __CDS_KEY_EXCEPTION_HPP__ // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
#pragma once

#include <CDS/exception/RuntimeException>

namespace cds {
class KeyException : public RuntimeException {
public:
  using RuntimeException::RuntimeException;
  KeyException() noexcept : RuntimeException("Illegal Key Received") {}

  template <typename __KeyType> /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
  explicit KeyException (
      __KeyType const& key
  ) noexcept : RuntimeException(String(128u, '\0') + "Key Exception: Key '" + key + "' is invalid for Object") {}
};
} // namespace cds

namespace cds {
namespace meta {
namespace __impl {
template<>
struct __TypeParseTraits<KeyException> {
  constexpr static StringLiteral name = "KeyException";
};
} // namespace __impl
} // namespace meta
} // namespace cds

#endif // __CDS_KEY_EXCEPTION_HPP__
