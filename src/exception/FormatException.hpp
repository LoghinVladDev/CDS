//
// Created by loghin on 30/11/22.
//

#ifndef __CDS_FORMAT_EXCEPTION_HPP__ // NOLINT(llvm-header-guard)
#define __CDS_FORMAT_EXCEPTION_HPP__ // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
#pragma once

#include <CDS/exception/IllegalArgumentException>

namespace cds {

class FormatException : public IllegalArgumentException {
public:
  using IllegalArgumentException::IllegalArgumentException;
  FormatException() noexcept : IllegalArgumentException("Argument Format Error") {}
};

} // namespace cds

namespace cds {
namespace meta {
namespace __impl {
template<>
struct __TypeParseTraits<FormatException> {
  constexpr static StringLiteral name = "FormatException";
};
} // namespace __impl
} // namespace meta
} // namespace cds

#endif // __CDS_FORMAT_EXCEPTION_HPP__
