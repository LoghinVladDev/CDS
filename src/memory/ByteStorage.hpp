//
// Created by loghin on 2/8/24.
//

#ifndef CDS_MEMORY_BYTE_STORAGE_HPP
#define CDS_MEMORY_BYTE_STORAGE_HPP
#pragma once

#include <cds/meta/StdLib>
#include <cds/meta/ObjectTraits>

namespace cds {
namespace impl {
using meta::EnableIf;
using meta::IsConstructible;
using meta::IsNoexceptConstructible;
using meta::address;

template <typename T, Size s = sizeof(T)> struct ByteStorage {
  static constexpr auto size = s;
  using Type = T;

  ByteStorage() = default;

  template <typename... A> CDS_ATTR(2(implicit, constexpr(26))) ByteStorage(A&&... args)
      CDS_ATTR(noexcept(noexcept(::new (address<T>()) T(fwd<A>(args)...)))) {
    ::new(byteData) T(fwd<A>(args)...);
  }

  template <typename... A> auto construct(A&&... args)
      CDS_ATTR(noexcept(noexcept(impl::construct(meta::address<T>(), fwd<A>(args)...))))
      -> decltype(impl::construct(address<T>(), fwd<A>(args)...)) {
    return impl::construct(static_cast<T*>(static_cast<void*>(byteData)), fwd<A>(args)...);
  }

  auto destruct() noexcept -> void {
    impl::destruct(static_cast<T*>(static_cast<void*>(byteData)));
  }

  CDS_ATTR(constexpr(26)) auto obj() const noexcept -> T const& {
    return *static_cast<T const*>(static_cast<void const*>(byteData));
  }

  CDS_ATTR(constexpr(26)) auto obj() noexcept -> T& {
    return *static_cast<T*>(static_cast<void*>(byteData));
  }

  alignas(T) Byte byteData[size];
};
} // namespace impl
} // namespace cds

#endif // CDS_MEMORY_BYTE_STORAGE_HPP
