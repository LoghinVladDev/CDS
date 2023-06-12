//
// Created by loghin on 30/11/22.
//

#ifndef __CDS_TYPE_EXCEPTION_HPP__ // NOLINT(llvm-header-guard)
#define __CDS_TYPE_EXCEPTION_HPP__ // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
#pragma once

#include <CDS/exception/RuntimeException>

namespace cds {
class TypeException : public RuntimeException {
public:
  using RuntimeException::RuntimeException;
  TypeException() noexcept : RuntimeException("Type Cast Exception") {}

  template < typename __FromType, typename __ToType > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
  TypeException () noexcept : RuntimeException(String(128u, '\0') +
      "Type Cast Exception: Cannot convert '" +
      cds::meta::Type<__FromType>::name() + "' to '" +
      cds::meta::Type<__ToType>::name() + "'"
  ) {}

  template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
  TypeException () noexcept : RuntimeException(String(64u, '\0') +
      "Type Cast Exception: Conversion to '" +
      cds::meta::Type<__ElementType>::name() +
      "' not possible"
  ) {}
};
} // namespace cds

namespace cds {
namespace meta {
namespace __impl {
template<>
struct __TypeParseTraits<TypeException> {
  constexpr static StringLiteral name = "TypeException";
};
} // namespace __impl
} // namespace meta
} // namespace cds

#endif // __CDS_TYPE_EXCEPTION_HPP__
