//
// Created by loghin on 30/11/22.
//

#ifndef __CDS_DIVIDE_BY_ZERO_EXCEPTION_HPP__ // NOLINT(llvm-header-guard)
#define __CDS_DIVIDE_BY_ZERO_EXCEPTION_HPP__ // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
#pragma once

#include <CDS/exception/ArithmeticException>

namespace cds {
class DivideByZeroException : public ArithmeticException {
public:
  using ArithmeticException::ArithmeticException;
  DivideByZeroException() noexcept : ArithmeticException("Divide by Zero Exception") {}
};
} // namespace cds

namespace cds {
namespace meta {
namespace __impl {
template<>
struct __TypeParseTraits<DivideByZeroException> {
  constexpr static StringLiteral name = "DivideByZeroException";
};
} // namespace __impl
} // namespace meta
} // namespace cds

#endif // __CDS_DIVIDE_BY_ZERO_EXCEPTION_HPP__
