//
// Created by loghin on 2/8/24.
//

#ifndef CDS_MEMORY_BYTE_STORAGE_HPP
#define CDS_MEMORY_BYTE_STORAGE_HPP
#pragma once

#include <cds/meta/Semantics>
#include <cds/meta/StdLib>

namespace cds {
namespace impl {
template <typename T, Size s = sizeof(T)> struct ByteStorage {
  static constexpr auto size = s;
  using Type = T;

  template <typename... A> auto construct(A&&... args)
      CDS_ATTR(noexcept(noexcept(impl::construct(meta::address<T>(), cds::forward<A>(args)...))))
      -> decltype(impl::construct(meta::address<T>(), cds::forward<A>(args)...)) {
    return impl::construct(static_cast<T*>(static_cast<void*>(byteData)), cds::forward<A>(args)...);
  }

  auto destruct() noexcept -> void {
    impl::destruct(static_cast<T*>(static_cast<void*>(byteData)));
  }

  auto obj() const noexcept -> T const& {
    return *static_cast<T const*>(static_cast<void const*>(byteData));
  }

  auto obj() noexcept -> T& {
    return *static_cast<T*>(static_cast<void*>(byteData));
  }

  alignas(T) Byte byteData[size];
};
} // namespace impl
} // namespace cds

#endif // CDS_MEMORY_BYTE_STORAGE_HPP
