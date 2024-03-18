//
// Created by loghin on 3/17/24.
//

#ifndef CDS_STRING_ABSTRACT_HPP
#define CDS_STRING_ABSTRACT_HPP
#pragma once

#include <cds/meta/StringTraits>

#include "StringViewBaseDecl.hpp"

#include "../../stdlib/string.hpp"
#include "../../stdlib/string_view.hpp"

namespace cds {
namespace impl {
using meta::True;
using meta::False;
using meta::Null;

namespace stringAbstractDetail {
template <typename C, Size s> struct Array {
  template <typename T> CDS_ATTR(2(nodiscard, constexpr(11))) static auto length(T&&) noexcept -> Size {
    return s;
  }

  template <typename T> CDS_ATTR(2(nodiscard, constexpr(11))) static auto data(T&& data) noexcept -> C const* {
    return cds::forward<T>(data);
  }
};

template <typename C> struct Pointer {
  CDS_ATTR(2(nodiscard, constexpr(14))) static auto length(C const* ptr) noexcept -> Size {
    if (ptr == nullptr) {
      return 0u;
    }

    auto head = ptr;
    for (; *head != '\0'; ++head);
    return head - ptr;
  }

  CDS_ATTR(2(nodiscard, constexpr(14))) static auto data(C* ptr) noexcept -> C* {
    return ptr;
  }
};

template <typename C> struct StringView {
  template <typename T> CDS_ATTR(2(nodiscard, constexpr(11))) static auto length(T&& sv) noexcept -> Size {
    return cds::forward<T>(sv).length();
  }

  template <typename T> CDS_ATTR(2(nodiscard, constexpr(11))) static auto data(T&& sv) noexcept -> C const* {
    return cds::forward<T>(sv).data();
  }
};
} // namespace stringAbstractDetail

template <typename = void> struct StringAbstract : False {};

template <> struct StringAbstract<void> {
  template <typename T, typename A = StringAbstract<T>>
  CDS_ATTR(2(nodiscard, constexpr(11))) static auto length(T&& s) noexcept -> decltype(A::length(cds::forward<T>(s))) {
    return A::length(cds::forward<T>(s));
  }

  template <typename T, typename A = StringAbstract<T>>
  CDS_ATTR(2(nodiscard, constexpr(11))) static auto data(T&& s) noexcept -> decltype(A::data(cds::forward<T>(s))) {
    return A::data(cds::forward<T>(s));
  }
};

template <> struct StringAbstract<Null> : False {
  CDS_ATTR(2(nodiscard, constexpr(11))) static auto length(Null) noexcept -> Size {
    return 0u;
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) static auto data(Null) noexcept -> Null {
    return nullptr;
  }
};

template <typename C, Size s> struct StringAbstract<C[s]> : stringAbstractDetail::Array<C, s - 1>, True {};
template <typename C, Size s> struct StringAbstract<C const[s]> : stringAbstractDetail::Array<C, s - 1>, True {};
template <typename C, Size s> struct StringAbstract<C(&)[s]> : stringAbstractDetail::Array<C, s - 1>, True {};
template <typename C, Size s> struct StringAbstract<C const(&)[s]> : stringAbstractDetail::Array<C, s - 1>, True {};

template <typename C> struct StringAbstract<C*> : stringAbstractDetail::Pointer<C>, True {};
template <typename C> struct StringAbstract<C*&> : stringAbstractDetail::Pointer<C>, True {};
template <typename C> struct StringAbstract<C* const> : stringAbstractDetail::Pointer<C>, True {};
template <typename C> struct StringAbstract<C* const&> : stringAbstractDetail::Pointer<C>, True {};

template <typename C, typename U> struct StringAbstract<BaseStringView<C, U>> :
    stringAbstractDetail::StringView<C>, True {};
template <typename C, typename U> struct StringAbstract<BaseStringView<C, U>&> :
    stringAbstractDetail::StringView<C>, True {};
template <typename C, typename U> struct StringAbstract<BaseStringView<C, U> const> :
    stringAbstractDetail::StringView<C>, True {};
template <typename C, typename U> struct StringAbstract<BaseStringView<C, U> const&> :
    stringAbstractDetail::StringView<C>, True {};

#if CDS_ATTR(std_compat)
template <typename C, typename T, typename A> struct StringAbstract<std::basic_string<C, T, A>> :
    stringAbstractDetail::StringView<C>, True {};
template <typename C, typename T, typename A> struct StringAbstract<std::basic_string<C, T, A>&> :
    stringAbstractDetail::StringView<C>, True {};
template <typename C, typename T, typename A> struct StringAbstract<std::basic_string<C, T, A> const> :
    stringAbstractDetail::StringView<C>, True {};
template <typename C, typename T, typename A> struct StringAbstract<std::basic_string<C, T, A> const&> :
    stringAbstractDetail::StringView<C>, True {};

#if CDS_ATTR(cpp17)
template <typename C, typename T> struct StringAbstract<std::basic_string_view<C, T>> :
    stringAbstractDetail::StringView<C>, True {};
template <typename C, typename T> struct StringAbstract<std::basic_string_view<C, T>&> :
    stringAbstractDetail::StringView<C>, True {};
template <typename C, typename T> struct StringAbstract<std::basic_string_view<C, T> const> :
    stringAbstractDetail::StringView<C>, True {};
template <typename C, typename T> struct StringAbstract<std::basic_string_view<C, T> const&> :
    stringAbstractDetail::StringView<C>, True {};
#endif
#endif
} // namespace impl
} // namespace cds

#endif // CDS_STRING_ABSTRACT_HPP
