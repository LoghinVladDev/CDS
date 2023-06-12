//
// Created by loghin on 30/11/22.
//

#ifndef __CDS_ILLEGAL_ARGUMENT_EXCEPTION_HPP__ // NOLINT(llvm-header-guard)
#define __CDS_ILLEGAL_ARGUMENT_EXCEPTION_HPP__ // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
#pragma once

#include <CDS/exception/RuntimeException>

namespace cds {
class IllegalArgumentException : public RuntimeException {
public:
  using RuntimeException::RuntimeException;
  IllegalArgumentException() noexcept : RuntimeException("Illegal Argument Exception") {}
};
} // namespace cds

namespace cds {
namespace meta {
namespace __impl {
template<>
struct __TypeParseTraits<IllegalArgumentException> {
  constexpr static StringLiteral name = "IllegalArgumentException";
};
} // namespace __impl
} // namespace meta
} // namespace cds

#endif // __CDS_ILLEGAL_ARGUMENT_EXCEPTION_HPP__
