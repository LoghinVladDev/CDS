//
// Created by loghin on 6/16/24.
//

#ifndef CDS_RUNTIME_EXCEPTION_HPP
#define CDS_RUNTIME_EXCEPTION_HPP
#pragma once

#include <cds/exception/Exception>
#include "../primitive/string/StringBase.hpp"

namespace cds {
namespace impl {
namespace except {
class RuntimeException : public Exception {
public:
  using Exception::Exception;

#if CDS_ATTR(msvc)
  explicit RuntimeException(char const* message) noexcept : RuntimeException(String{message}) {}
#endif

  RuntimeException() noexcept : _message("") {}
  explicit RuntimeException(String message) noexcept : _message{cds::move(message)} {}
  explicit RuntimeException(std::exception const& exception) noexcept : _message{exception.what()} {}
  ~RuntimeException() noexcept override = default;

  CDS_ATTR(2(nodiscard, constexpr(20))) auto message() const noexcept -> StringView override {
    return {_message};
  }

private:
  String const _message;
};
} // namespace except
} // namespace impl
} // namespace cds

namespace cds {
using impl::except::RuntimeException;
} // namespace cds

#endif // #ifndef CDS_RUNTIME_EXCEPTION_HPP
