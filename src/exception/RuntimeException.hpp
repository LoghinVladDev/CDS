//
// Created by loghin on 30/11/22.
//

#ifndef __CDS_RUNTIME_EXCEPTION_HPP__ // NOLINT(llvm-header-guard)
#define __CDS_RUNTIME_EXCEPTION_HPP__ // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
#pragma once

#include <CDS/exception/Exception>
#include <utility>

namespace cds {

class RuntimeException : public Exception {
public:
  using Exception::Exception;

  RuntimeException() noexcept : _message("Runtime Exception") {}
  explicit RuntimeException(String message) noexcept : _message(std::move(message)) {}
  explicit RuntimeException(std::exception const& exception) noexcept : _message(exception.what()) {}

  __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto message() const noexcept -> StringView override {
    return _message;
  }

  __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto hash() const noexcept -> Size override {
    return _message.hash();
  }

  __CDS_NoDiscard auto equals(Object const& object) const noexcept -> bool override {
    if (this == &object) {
      return true;
    }

    auto pException = dynamic_cast<decltype(this)>(&object);
    if (pException == nullptr) {
      return false;
    }

    return _message == pException->_message;
  }

private:
  String const _message;
};

} // namespace cds

namespace cds {
namespace meta {
namespace __impl {
template<>
struct __TypeParseTraits<RuntimeException> {
  constexpr static StringLiteral name = "RuntimeException";
};
} // namespace __impl
} // namespace meta
} // namespace cds


#endif /* __CDS_RUNTIME_EXCEPTION_HPP__ */
