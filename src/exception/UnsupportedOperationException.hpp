//
// Created by loghin on 30/11/22.
//

#ifndef __CDS_UNSUPPORTED_OPERATION_EXCEPTION_HPP__ // NOLINT(llvm-header-guard)
#define __CDS_UNSUPPORTED_OPERATION_EXCEPTION_HPP__ // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
#pragma once

#include <CDS/exception/RuntimeException>

namespace cds {
class UnsupportedOperationException : public RuntimeException {
public:
  using RuntimeException::RuntimeException;
  UnsupportedOperationException() noexcept : RuntimeException("Unsupported Operation") {}
};
} // namespace cds

namespace cds {
namespace meta {
namespace __impl {
template<>
struct __TypeParseTraits<UnsupportedOperationException> {
  constexpr static StringLiteral name = "UnsupportedOperationException";
};
} // namespace __impl
} // namespace meta
} // namespace cds

#endif // __CDS_UNSUPPORTED_OPERATION_EXCEPTION_HPP__
