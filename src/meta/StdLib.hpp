//
// Created by loghin on 22/09/2021.
//

#ifndef CDS_META_STD_LIB_HPP
#define CDS_META_STD_LIB_HPP
#pragma once

#include <cds/meta/Compiler>
#include <cds/meta/ObjectTraits>
#include <type_traits>

#ifdef __GLIBCXX__
#define CDS_ATTR_stdlibcxx true
#if CDS_ATTR(cpp20)
#include <memory>
#include <bit>
#else // #if CDS_ATTR(cpp20)
#include <cds/meta/Semantics>
#include <cstring>
#endif // #if CDS_ATTR(cpp20) #else
#else // #ifdef __GLIBCXX__
#define CDS_ATTR_stdlibcxx false
#endif // #ifdef __GLIBCXX__ #else

#ifdef _LIBCPP_VERSION
#define CDS_ATTR_libcxx true
#if CDS_ATTR(cpp20)
#include <memory>
#include <bit>
#else // #if CDS_ATTR(cpp20)
#include <cds/meta/Semantics>
#include <cstring>
#endif // #if CDS_ATTR(cpp20) #else
#else // #ifdef _LIBCPP_STD_VER
#define CDS_ATTR_libcxx false
#endif // #ifdef _LIBCPP_STD_VER #else

#ifdef _MSC_VER
// Check for usages of other libs. Otherwise, default msvc stdlib
#define CDS_ATTR_msvclibcxx true
#if CDS_ATTR(cpp20)
#include <memory>
#include <bit>
#else // #if CDS_ATTR(cpp20)
#endif // #if CDS_ATTR(cpp20) #else
#else // #ifdef _MSC_VER
#define CDS_ATTR_msvclibcxx false
#endif // #ifdef _MSC_VER #else

#if CDS_ATTR(stdlibcxx)
namespace cds {
namespace meta {
CDS_ATTR(2(nodiscard, constexpr(11))) auto inConstexpr() noexcept -> bool {
  return std::__is_constant_evaluated();
}
} // namespace meta

namespace impl {
#if CDS_ATTR(cpp20)
template <typename T, typename... A> CDS_ATTR(constexpr(20)) auto construct(T* location, A&&... args)
    CDS_ATTR(noexcept(noexcept(std::construct_at(location, std::forward<A>(args)...))))
    -> decltype(std::construct_at(location, std::forward<A>(args)...)) {
  return std::construct_at(location, std::forward<A>(args)...);
}

template <typename T> CDS_ATTR(constexpr(20))
auto destruct(T* location) noexcept -> void {
  std::destroy_at(location);
}
#else // #if CDS_ATTR(cpp20)
template <typename T, typename... A> inline auto construct(T* location, A&&... args)
    CDS_ATTR(noexcept(noexcept(::new(static_cast<void*>(location)) T(cds::forward<A>(args)...))))
    -> decltype(::new(static_cast<void*>(location)) T(cds::forward<A>(args)...)) {
  return ::new(static_cast<void*>(location)) T(cds::forward<A>(args)...);
}

template <typename T> inline auto destruct(T* location) noexcept -> void {
  location->~T();
}
#endif // #if CDS_ATTR(cpp20) #else
} // namespace impl

#if CDS_ATTR(cpp20)
template <typename T, typename F> CDS_ATTR(2(nodiscard, constexpr(20))) auto bitCast(F const& from) noexcept -> T {
  return std::bit_cast<T>(from);
}
#else // #if CDS_ATTR(cpp20)
template <typename T, typename F> CDS_ATTR(nodiscard) auto bitCast(F const& from) noexcept -> T {
  static_assert(
      meta::And<
          meta::Eq<meta::Int<sizeof(F)>, meta::Int<sizeof(T)>>,
          meta::IsTriviallyCopyable<F>,
          meta::IsTriviallyCopyable<T>,
          meta::IsTriviallyConstructible<T>
          >::value,
      "type constraints not satisfied for memory-safe bit-cast"
  );
  T result;
  std::memcpy(&result, &from, sizeof(T));
  return result;
}
#endif // #if CDS_ATTR(cpp20) #else
} // namespace cds
#endif // #if CDS_ATTR(stdlibcxx)

#if CDS_ATTR(libcxx)
namespace cds {
namespace meta {
CDS_ATTR(2(nodiscard, constexpr(11))) auto inConstexpr() noexcept -> bool {
  return std::__libcpp_is_constant_evaluated();
}
} // namespace meta

namespace impl {
#if CDS_ATTR(cpp20)
template <typename T, typename... A> CDS_ATTR(constexpr(20)) auto construct(T* location, A&&... args)
    CDS_ATTR(noexcept(noexcept(std::construct_at(location, std::forward<A>(args)...))))
    -> decltype(std::construct_at(location, std::forward<A>(args)...)) {
  return std::construct_at(location, std::forward<A>(args)...);
}

template <typename T> CDS_ATTR(constexpr(20))
auto destruct(T* location) noexcept -> void {
  std::destroy_at(location);
}
#else // #if CDS_ATTR(cpp20)
template <typename T, typename... A> inline auto construct(T* location, A&&... args)
    CDS_ATTR(noexcept(noexcept(::new(static_cast<void*>(location)) T(cds::forward<A>(args)...))))
    -> decltype(::new(static_cast<void*>(location)) T(cds::forward<A>(args)...)) {
  return ::new(static_cast<void*>(location)) T(cds::forward<A>(args)...);
}

template <typename T> inline auto destruct(T* location) noexcept -> void {
  location->~T();
}
#endif // #if CDS_ATTR(cpp20) #else
} // namespace impl

#if CDS_ATTR(cpp20)
template <typename T, typename F> CDS_ATTR(2(nodiscard, constexpr(20))) auto bitCast(F const& from) noexcept -> T {
  return std::bit_cast<T>(from);
}
#else // #if CDS_ATTR(cpp20)
template <typename T, typename F> CDS_ATTR(nodiscard) auto bitCast(F const& from) noexcept -> T {
  static_assert(
      meta::And<
          meta::Eq<meta::Int<sizeof(F)>, meta::Int<sizeof(T)>>,
          meta::IsTriviallyCopyable<F>,
          meta::IsTriviallyCopyable<T>,
          meta::IsTriviallyConstructible<T>
          >::value,
      "type constraints not satisfied for memory-safe bit-cast"
  );
  T result;
  std::memcpy(&result, &from, sizeof(T));
  return result;
}
#endif // #if CDS_ATTR(cpp20) #else
} // namespace cds
#endif // #if CDS_ATTR(libcxx)

#if CDS_ATTR(msvclibcxx)
namespace cds {
namespace meta {
CDS_ATTR(2(nodiscard, constexpr(11))) auto inConstexpr() noexcept -> bool {
  return __builtin_is_constant_evaluated();
}
} // namespace meta

namespace impl {
#if CDS_ATTR(cpp20)
template <typename T, typename... A> CDS_ATTR(constexpr(20)) auto construct(T* location, A&&... args)
    CDS_ATTR(noexcept(noexcept(std::construct_at(location, std::forward<A>(args)...))))
    -> decltype(std::construct_at(location, std::forward<A>(args)...)) {
  return std::construct_at(location, std::forward<A>(args)...);
}

template <typename T> CDS_ATTR(constexpr(20))
auto destruct(T* location) noexcept -> void {
  std::destroy_at(location);
}
#else // #if CDS_ATTR(cpp20)
template <typename T, typename... A> inline auto construct(T* location, A&&... args)
    CDS_ATTR(noexcept(noexcept(::new(static_cast<void*>(location)) T(cds::forward<A>(args)...))))
    -> decltype(::new(static_cast<void*>(location)) T(cds::forward<A>(args)...)) {
  return ::new(static_cast<void*>(location)) T(cds::forward<A>(args)...);
}

template <typename T> inline auto destruct(T* location) noexcept -> void {
  location->~T();
}
#endif // #if CDS_ATTR(cpp20) #else
} // namespace impl

#if CDS_ATTR(cpp20)
template <typename T, typename F> CDS_ATTR(2(nodiscard, constexpr(20))) auto bitCast(F const& from) noexcept -> T {
  return std::bit_cast<T>(from);
}
#else // #if CDS_ATTR(cpp20)
template <typename T, typename F> CDS_ATTR(nodiscard) auto bitCast(F const& from) noexcept -> T {
  static_assert(
      meta::And<
          meta::Eq<meta::Int<sizeof(F)>, meta::Int<sizeof(T)>>,
          meta::IsTriviallyCopyable<F>,
          meta::IsTriviallyCopyable<T>,
          meta::IsTriviallyConstructible<T>
          >::value,
      "type constraints not satisfied for memory-safe bit-cast"
  );
  T result;
  std::memcpy(&result, &from, sizeof(T));
  return result;
}
#endif // #if CDS_ATTR(cpp20) #else
} // namespace cds
#endif // #if CDS_ATTR(msvclibcxx)

#endif // CDS_META_STD_LIB_HPP
