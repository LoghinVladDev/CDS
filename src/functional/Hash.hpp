//
// Created by loghin on 2/10/24.
//

#ifndef CDS_FUNCTIONAL_HASH_HPP
#define CDS_FUNCTIONAL_HASH_HPP
#pragma once

#include <cds/meta/TypeTraits>
#include <cds/meta/Semantics>
#include <cds/meta/StdLib>

namespace cds {
namespace functional {
template <typename = void, typename = void> struct Hash {};
template <> struct Hash <void, void> {
  template <typename T, typename D = meta::RemoveCVRef<T>>
  CDS_ATTR(2(nodiscard, constexpr(11))) auto operator()(T&& object) const
      CDS_ATTR(noexcept(noexcept(meta::rvalue<Hash<D>>()(cds::forward<T>(object)))))
      -> decltype(meta::rvalue<Hash<D>>()(cds::forward<T>(object))) {
    return Hash<D>()(cds::forward<T>(object));
  }
};

template <typename T> struct Hash<T, meta::EnableIf<meta::And<meta::IsIntegral<T>, meta::IsUnsigned<T>>, void>> {
  CDS_ATTR(2(nodiscard, constexpr(11))) auto operator()(T value) const noexcept -> Size {
    return value;
  }
};

template <typename T> struct Hash<T, meta::EnableIf<meta::And<meta::IsIntegral<T>, meta::IsSigned<T>>, void>> {
  CDS_ATTR(2(nodiscard, constexpr(11))) auto operator()(T value) const noexcept -> Size {
    return static_cast<Size>(value);
  }
};

namespace impl {
template <typename T> struct IntegralOfEquivalentSize {};
template <> struct IntegralOfEquivalentSize<float> {
  static_assert(sizeof(float) == sizeof(U32), "Invalid Integral equivalent for floating point constant");
  using Type = U32;
};

template <> struct IntegralOfEquivalentSize<double> {
  static_assert(sizeof(double) == sizeof(U64), "Invalid Integral equivalent for floating point constant");
  using Type = U64;
};

template <> struct IntegralOfEquivalentSize<long double> {
  static_assert(sizeof(long double) == 16,
                "Invalid Integral equivalent for floating point constant");
  struct Type {
    U8 asBytes[16];
  };
};

template <Size n> CDS_ATTR(2(nodiscard, constexpr(14))) auto hash8(U8 const* buffer) noexcept -> U8 {
  U8 r = 0;
  for (Size i = 0; i != n; i+= sizeof(U8)) {
    r ^= buffer[i];
  }
  return r;
}

template <Size n> CDS_ATTR(2(nodiscard, constexpr(14))) auto hash16(U8 const* buffer) noexcept -> U16 {
  static_assert(n % sizeof(U16) == 0, "Byte Hash not implemented with partial sizes");
  U16 r = 0;
  for (Size i = 0; i != n; i+= sizeof(U16)) {
    r ^= static_cast<U16>(buffer[i + 0]) | (static_cast<U16>(buffer[i + 1]) << 8);
  }
  return r;
}

template <Size n> CDS_ATTR(2(nodiscard, constexpr(14))) auto hash32(U8 const* buffer) noexcept -> U32 {
  static_assert(n % sizeof(U32) == 0, "Byte Hash not implemented with partial sizes");
  U32 r = 0;
  for (Size i = 0; i != n; i+= sizeof(U32)) {
    r ^= static_cast<U32>(buffer[i + 0])
        | (static_cast<U32>(buffer[i + 1]) << 8)
        | (static_cast<U32>(buffer[i + 2]) << 16)
        | (static_cast<U32>(buffer[i + 3]) << 24);
  }
  return r;
}

template <Size n> CDS_ATTR(2(nodiscard, constexpr(14))) auto hash64(U8 const* buffer) noexcept -> U64 {
  static_assert(n % sizeof(U64) == 0, "Byte Hash not implemented with partial sizes");
  Size r = 0;
  for (Size i = 0; i != n; i+= sizeof(U64)) {
    r ^= static_cast<U64>(buffer[i + 0])
        | (static_cast<U64>(buffer[i + 1]) << 8)
        | (static_cast<U64>(buffer[i + 2]) << 16)
        | (static_cast<U64>(buffer[i + 3]) << 24)
        | (static_cast<U64>(buffer[i + 4]) << 32)
        | (static_cast<U64>(buffer[i + 5]) << 40)
        | (static_cast<U64>(buffer[i + 6]) << 48)
        | (static_cast<U64>(buffer[i + 7]) << 56);
  }
  return r;
}
} // namespace impl

template <> struct Hash<typename impl::IntegralOfEquivalentSize<long double>::Type, void> {
  CDS_ATTR(2(nodiscard, constexpr(14)))
  auto operator()(typename impl::IntegralOfEquivalentSize<long double>::Type const & value) const noexcept -> Size {
#if CDS_ATTR(ld_size) == 80
    return impl::hash64<8>(value.asBytes) + impl::hash16<2>(value.asBytes + 8);
#elif CDS_ATTR(ld_size) == 128  // #if CDS_ATTR(ld_size) == 80
    return impl::hash64<16>(value.asBytes);
#else // #if CDS_ATTR(ld_size) == 80 #elif CDS_ATTR(ld_size) == 128
    static_assert(true, "undefined LD equiv integral hash or undefined CDS_ATTR_ld_size");
#endif // #if CDS_ATTR(ld_size) == 80 #elif CDS_ATTR(ld_size) == 128 #else
  }
};

template <typename T> struct Hash<T, meta::EnableIf<meta::And<meta::IsFloating<T>, meta::IsSigned<T>>, void>> {
  CDS_ATTR(2(nodiscard, constexpr(20))) auto operator()(T value) const noexcept -> Size {
    using ET = typename impl::IntegralOfEquivalentSize<T>::Type;
    Hash<ET> const h;
    return h(bitCast<ET>(value));
  }
};

template <typename T> struct Hash<T*, void> {
  CDS_ATTR(2(nodiscard, constexpr(20))) auto operator()(T* value) const noexcept -> Size {
    return bitCast<Size>(value);
  }
};

template <> struct Hash<meta::Nullptr, void> {
  CDS_ATTR(2(nodiscard, constexpr(11))) auto operator()(meta::Nullptr) const noexcept -> Size {
    return 0;
  }
};
} // namespace functional
} // namespace cds

#endif // CDS_FUNCTIONAL_HASH_HPP
