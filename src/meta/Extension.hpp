//
// Created by loghin on 3/16/24.
//

#ifndef CDS_META_EXTENSION_HPP
#define CDS_META_EXTENSION_HPP
#pragma once

#include <cds/meta/TypeTraits>

#include <initializer_list>

namespace cds {
namespace impl {
namespace extension {
using meta::IsSame;
using meta::Conditional;
using meta::RemoveRef;
using meta::IsRValRef;
using meta::Or;

namespace extendImpl {
using meta::False;
using meta::True;

template <typename> struct IsInitializerList : False {};
template <typename T> struct IsInitializerList<std::initializer_list<T>> : True {};

template <typename T, typename R = RemoveRef<T>> struct Extend {
  static_assert(!IsInitializerList<T>::value, "Cannot extend lifetime of std::initializer_list");
  using Type = Conditional<Or<IsRValRef<T>, IsSame<R, T>>, R, R&>;
};
} // namespace extendImpl

template <typename T> using Extend = typename extendImpl::Extend<T>::Type;
} // namespace extension
} // namespace impl
} // namespace cds

#endif // CDS_META_EXTENSION_HPP
