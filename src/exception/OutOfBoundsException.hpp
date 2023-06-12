//
// Created by loghin on 30/11/22.
//

#ifndef __CDS_OUT_OF_BOUNDS_EXCEPTION_HPP__ // NOLINT(llvm-header-guard)
#define __CDS_OUT_OF_BOUNDS_EXCEPTION_HPP__ // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
#pragma once

#include <CDS/exception/RuntimeException>

namespace cds {
class OutOfBoundsException : public RuntimeException {
public:
  using RuntimeException::RuntimeException;
  OutOfBoundsException() noexcept : RuntimeException("Out of Bounds Access for Object") {}
  OutOfBoundsException(Index requested, Index capacity) noexcept :
      RuntimeException(String(64, '\0') + "Out of Bounds: Requested: '" + requested + "', capacity: '" + capacity + "'") {}
};
} // namespace cds

namespace cds {
namespace meta {
namespace __impl {
template<>
struct __TypeParseTraits<OutOfBoundsException> {
  constexpr static StringLiteral name = "OutOfBoundsException";
};
} // namespace __impl
} // namespace meta
} // namespace cds

#endif // __CDS_OUT_OF_BOUNDS_EXCEPTION_HPP__
