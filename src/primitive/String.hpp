//
// Created by loghin on 22.01.2021.
//

#ifndef CDS_PRIMITIVE_STRING_HPP
#define CDS_PRIMITIVE_STRING_HPP
#pragma once

#include "string/StringBase.hpp"

namespace cds {
using String = impl::BaseString<char>;
using WideString = impl::BaseString<wchar_t>;

namespace meta {
namespace impl {
namespace primitiveTypeInfoNames {
template <typename = void> struct String { static char constexpr name[7u] = "String"; };
template <typename = void> struct WideString { static char constexpr name[11u] = "WideString"; };

// ODR before cpp17
template <typename T> char const String<T>::name[7u];
template <typename T> char const WideString<T>::name[11u];
} // namespace primitiveTypeInfoNames
} // namespace impl
template <> struct TypeInfo<String> : impl::primitiveTypeInfoNames::String<> {};
template <> struct TypeInfo<WideString> : impl::primitiveTypeInfoNames::WideString<> {};
} // namespace meta
} // namespace cds

#endif // CDS_PRIMITIVE_STRING_HPP
