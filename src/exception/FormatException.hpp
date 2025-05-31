//
// Created by loghin on 12/11/24.
//

#ifndef CDS_FORMAT_FORMAT_EXCEPTION_HPP
#define CDS_FORMAT_FORMAT_EXCEPTION_HPP
#pragma once

#include <cds/exception/Exception>
#include "../primitive/string/StringBase.hpp"

namespace cds {
namespace impl {
namespace except {
class FormatException : public Exception {
public:
  using Exception::Exception;

#if CDS_ATTR(msvc)
  explicit FormatException(char const* message) noexcept : Exception{}, _message{message} {}
#endif

  FormatException() noexcept : _message{""} {}
  explicit FormatException(String message) noexcept : _message{cds::move(message)} {}
  explicit FormatException(std::exception const& exception) noexcept : _message{exception.what()} {}
  ~FormatException() noexcept override = default;

  CDS_ATTR(2(nodiscard, constexpr(20))) auto message() const noexcept -> StringView override {
    return {_message};
  }

private:
  String const _message;
};
} // namespace except
} // namespace impl

using impl::except::FormatException;
} // namespace cds

#endif // #ifndef CDS_FORMAT_FORMAT_EXCEPTION_HPP
