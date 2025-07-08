//
// Created by loghin on 22.01.2021.
//

#ifndef CDS_PRIMITIVE_STRING_VIEW_HPP
#define CDS_PRIMITIVE_STRING_VIEW_HPP
#pragma once

#include "string/StringViewBase.hpp"

namespace cds {
using StringView = impl::BaseStringView<char>;
using WideStringView = impl::BaseStringView<wchar_t>;

namespace meta {
namespace impl {
namespace primitiveTypeInfoNames {
template <typename = void> struct StringView { static char constexpr name[11u] = "StringView"; };
template <typename = void> struct WideStringView { static char constexpr name[15u] = "WideStringView"; };

#if !CDS_ATTR(cpp17)
// ODR before cpp17
template <typename T> char const StringView<T>::name[11u];
template <typename T> char const WideStringView<T>::name[15u];
#endif
} // namespace primitiveTypeInfoNames
} // namespace impl
template <> struct TypeInfo<StringView> : impl::primitiveTypeInfoNames::StringView<> {};
template <> struct TypeInfo<WideStringView> : impl::primitiveTypeInfoNames::WideStringView<> {};
} // namespace meta
} // namespace cds

#endif // CDS_PRIMITIVE_STRING_VIEW_HPP
