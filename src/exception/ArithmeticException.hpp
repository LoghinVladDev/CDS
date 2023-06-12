//
// Created by loghin on 30/11/22.
//

#ifndef __CDS_ARITHMETIC_EXCEPTION_HPP__ // NOLINT(llvm-header-guard)
#define __CDS_ARITHMETIC_EXCEPTION_HPP__ // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
#pragma once

#include <CDS/exception/RuntimeException>

namespace cds {
class ArithmeticException : public RuntimeException {
public:
  using RuntimeException::RuntimeException;
  ArithmeticException() noexcept : RuntimeException("Arithmetic Exception") {}
};
} // namespace cds

namespace cds {
namespace meta {
namespace __impl {
template<>
struct __TypeParseTraits<ArithmeticException> {
  constexpr static StringLiteral name = "ArithmeticException";
};
} // namespace __impl
} // namespace meta
} // namespace cds

#endif // __CDS_ARITHMETIC_EXCEPTION_HPP__
