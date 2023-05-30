//
// Created by loghin on 30/11/22.
//

#ifndef __CDS_EXCEPTION_HPP__ // NOLINT(llvm-header-guard)
#define __CDS_EXCEPTION_HPP__ // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
#pragma once

#include <CDS/String>

namespace cds {
class Exception : public Object, public std::exception {
public:
  __CDS_NoDiscard auto toString() const noexcept -> String override {
    return this->message();
  }

  __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto hash() const noexcept -> Size override {
    return this->message().hash();
  }

  __CDS_NoDiscard __CDS_cpplang_VirtualConstexpr virtual auto message() const noexcept -> StringView = 0;

protected:
  using Object::Object;

  __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto what () const noexcept -> StringLiteral override {
    return message().cStr();
  }
};
} // namespace cds

namespace cds {
namespace meta {
namespace __impl {
template<>
struct __TypeParseTraits<Exception> {
  constexpr static StringLiteral name = "Exception";
};
} // namespace __impl
} // namespace meta
} // namespace cds

#endif // __CDS_EXCEPTION_HPP__
