//
// Created by loghin on 12/8/23.
//

#ifndef CDS_PRIMITIVE_STRING_PATTERN_HPP
#define CDS_PRIMITIVE_STRING_PATTERN_HPP
#pragma once

#include <cds/Utility>
#include <cds/meta/StdLib>
#include <cds/meta/StringTraits>
#include <cds/iterator/AddressIterator>
#include <cds/memory/Allocator>

#include "StringUtils.hpp"

#include <ostream>

namespace cds {
namespace impl {
using meta::EnableIf;
using meta::Not;
using meta::Decay;
using meta::All;
using meta::True;
using meta::False;
using meta::IsRef;
using meta::Nullptr;

using meta::lvalue;
using meta::rvalue;
using meta::inConstexpr;

template <typename> struct PatternUtils {};

template <typename C, Size s> struct ArrPatternUtils {
  template <typename T> CDS_ATTR(2(nodiscard, constexpr(11))) static auto length(T&&) noexcept -> Size {
    return s;
  }

  template <typename T> CDS_ATTR(2(nodiscard, constexpr(11))) static auto data(T&& data) noexcept -> C const* {
    return cds::forward<T>(data);
  }
};

template <typename C, Size s> struct PatternUtils<C(&)[s]> : ArrPatternUtils<C, s - 1> {};
template <typename C, Size s> struct PatternUtils<C const(&)[s]> : ArrPatternUtils<C, s - 1> {};

template <typename C> struct PtrPatternUtils {
  using Utils = StringUtils<C, StringTraits<C>>;

  CDS_ATTR(2(nodiscard, constexpr(14))) static auto length(C const* ptr) noexcept -> Size {
    return Utils::length(ptr);
  }

  CDS_ATTR(2(nodiscard, constexpr(14))) static auto data(C const* ptr) noexcept -> C const* {
    return ptr;
  }
};

template <typename C> struct PatternUtils<C*> : PtrPatternUtils<C> {};
template <typename C> struct PatternUtils<C*&> : PtrPatternUtils<C> {};
template <typename C> struct PatternUtils<C const*> : PtrPatternUtils<C> {};
template <typename C> struct PatternUtils<C const*&> : PtrPatternUtils<C> {};

template <typename C> struct BSVPatternUtils {
  template <typename T> CDS_ATTR(2(nodiscard, constexpr(11))) static auto length(T&& sv) noexcept -> Size {
    return cds::forward<T>(sv).length();
  }

  template <typename T> CDS_ATTR(2(nodiscard, constexpr(11))) static auto data(T&& sv) noexcept -> C const* {
    return cds::forward<T>(sv).data();
  }
};

template <typename C, typename U> struct PatternUtils<BaseStringView<C, U>> : BSVPatternUtils<C> {};
template <typename C, typename U> struct PatternUtils<BaseStringView<C, U>&> : BSVPatternUtils<C> {};
template <typename C, typename U> struct PatternUtils<BaseStringView<C, U> const> : BSVPatternUtils<C> {};
template <typename C, typename U> struct PatternUtils<BaseStringView<C, U> const&> : BSVPatternUtils<C> {};

template <typename T> constexpr auto allocate(std::size_t s) -> T* {
  return static_cast<T*>(::operator new(s));
}

template <typename S, typename A> class KMPBase : private A {
public:
  using Utils = PatternUtils<S>;

  template <typename FS, typename FA> CDS_ATTR(constexpr(20)) KMPBase(FS&& needle, FA&& alloc)
      CDS_ATTR(noexcept(noexcept(A(cds::forward<FA>(alloc)).allocate(0)))) :
      A{cds::forward<FA>(alloc)},
      _pat{cds::forward<FS>(needle)},
      _lps{A::allocate(len())} {
    construct(_lps, 0);
    Size idx = 1u;
    Size parseIdx = 0;
    auto const* pattern = Utils::data(cds::forward<FS>(needle));
    while (idx < len()) {
      if (pattern[idx] == pattern[parseIdx]) {
        construct(_lps + idx++, ++parseIdx);
      } else if (parseIdx > 0) {
        parseIdx = _lps[parseIdx - 1];
      } else {
        construct(_lps + idx++, 0);
      }
    }
  }

  template <typename Ref = IsRef<S>, EnableIf<Ref> = 0>
  CDS_ATTR(2(explicit, constexpr(14))) KMPBase(KMPBase&& pred) noexcept :
      A{cds::move(pred)}, _pat{pred._pat}, _lps{cds::exchange(pred._lps, nullptr)} {}

  template <typename Ref = IsRef<S>, EnableIf<Not<Ref>> = 0>
  CDS_ATTR(2(explicit, constexpr(14))) KMPBase(KMPBase&& pred)
      CDS_ATTR(noexcept(noexcept(S(cds::move(pred._pat))))) :
      A{cds::move(pred)}, _pat{cds::move(pred._pat)}, _lps{cds::exchange(pred._lps, nullptr)} {}

  KMPBase(KMPBase const&) noexcept = delete;
  auto operator=(KMPBase const&) noexcept -> KMPBase& = delete;
  auto operator=(KMPBase&&) noexcept -> KMPBase& = delete;

  CDS_ATTR(constexpr(20)) ~KMPBase() noexcept {
    destruct(_lps, _lps + len());
    A::deallocate(_lps, len());
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto len() const
      CDS_ATTR(noexcept(noexcept(Utils::length(value<S>())))) -> Size {
    return Utils::length(_pat);
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto data() const
      CDS_ATTR(noexcept(noexcept(Utils::data(value<S>())))) -> decltype(Utils::data(value<S>())) {
    return Utils::data(_pat);
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto lps() const noexcept -> Size const* {
    return _lps;
  }

private:
  S _pat;
  Size* _lps;
};
} // namespace impl
} // namespace cds

#endif // CDS_PRIMITIVE_STRING_PATTERN_HPP
