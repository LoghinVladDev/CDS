//
// Created by loghin on 6/16/24.
//

#ifndef CDS_EXCEPTION_HPP
#define CDS_EXCEPTION_HPP
#pragma once

#include <exception>
#include "../primitive/string/StringViewBase.hpp"

namespace cds {
namespace impl {
namespace except {
using String = BaseString<char>;
using StringView = BaseStringView<char>;

class Exception : public std::exception {
public:
  using std::exception::exception;

#if CDS_ATTR(msvc)
  Exception(char const*) = delete;
#endif

  ~Exception() noexcept override = default;
  CDS_ATTR(2(nodiscard, constexpr(20))) virtual auto message() const noexcept -> StringView = 0;

protected:
  CDS_ATTR(2(nodiscard, constexpr(20))) auto what() const noexcept -> char const* override {
    return message().data();
  }
};
} // namespace except
} // namespace impl
} // namespace cds

namespace cds {
using impl::except::Exception;
} // namespace cds

#endif // #ifndef CDS_EXCEPTION_HPP
