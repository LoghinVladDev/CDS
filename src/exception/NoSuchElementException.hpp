//
// Created by loghin on 30/11/22.
//

#ifndef __CDS_NO_SUCH_ELEMENT_EXCEPTION_HPP__ // NOLINT(llvm-header-guard)
#define __CDS_NO_SUCH_ELEMENT_EXCEPTION_HPP__ // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
#pragma once

#include <CDS/exception/RuntimeException>

namespace cds {
class NoSuchElementException : public RuntimeException {
public:
  using RuntimeException::RuntimeException;
  NoSuchElementException() noexcept : RuntimeException("No such Element exists") {}
};
} // namespace cds

namespace cds {
namespace meta {
namespace __impl {
template<>
struct __TypeParseTraits<NoSuchElementException> {
  constexpr static StringLiteral name = "NoSuchElementException";
};
} // namespace __impl
} // namespace meta
} // namespace cds

#endif // __CDS_NO_SUCH_ELEMENT_EXCEPTION_HPP__
