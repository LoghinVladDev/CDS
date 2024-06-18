//
// Created by loghin on 6/16/24.
//

#ifndef CDS_RUNTIME_EXCEPTION_HPP
#define CDS_RUNTIME_EXCEPTION_HPP
#pragma once

#include <cds/exception/Exception>
#include "../primitive/string/StringBase.hpp"

namespace cds {
class RuntimeException : public Exception {
  using String = impl::BaseString<char>;
  using StringView = impl::BaseStringView<char>;

public:
  using Exception::Exception;

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
} // namespace cds

#endif // #ifndef CDS_RUNTIME_EXCEPTION_HPP
