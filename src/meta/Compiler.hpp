//
// Created by loghin on 22/09/2021.
//

#ifndef CDS_META_COMPILER_HPP
#define CDS_META_COMPILER_HPP
#pragma once

#define CDS_ATTR_JOIN_LATE(prefix, ...) prefix ## __VA_ARGS__
#define CDS_ATTR(...) CDS_ATTR_JOIN_LATE(CDS_ATTR_, __VA_ARGS__)

#define CDS_ATTR_OLDSTYLE(attr) __attribute__((attr))
#define CDS_ATTR_NEWSTYLE(attr) [[attr]]

#define CDS_ATTR_noreturn
#define CDS_ATTR_carries_dependency
#define CDS_ATTR_deprecated(...)
#define CDS_ATTR_fallthrough
#define CDS_ATTR_likely
#define CDS_ATTR_unlikely
#define CDS_ATTR_no_unique_address
#define CDS_ATTR_maybe_unused
#define CDS_ATTR_unused CDS_ATTR_maybe_unused
#define CDS_ATTR_nodiscard
#define CDS_ATTR_inline
#define CDS_ATTR_constexpr(std) CDS_ATTR_constexpr_ ## std
#define CDS_ATTR_always_constexpr constexpr
#define CDS_ATTR_noexcept(...) noexcept(!CDS_ATTR_exceptions || __VA_ARGS__)
#define CDS_ATTR_friend_noexcept(...) CDS_ATTR_noexcept(__VA_ARGS__)

#define CDS_ATTR_2(a, b) CDS_ATTR_ ## a CDS_ATTR_ ## b
#define CDS_ATTR_3(a, b, c) CDS_ATTR_ ## a CDS_ATTR_ ## b CDS_ATTR_ ## c


#ifdef CDS_OPTION_DEFAULT_POLY
#define CDS_ATTR_ns_poly_spec inline
#define CDS_ATTR_ns_non_poly_spec
#else // #ifdef CDS_OPTION_DEFAULT_POLY
#define CDS_ATTR_ns_poly_spec
#define CDS_ATTR_ns_non_poly_spec inline
#endif// #ifdef CDS_OPTION_DEFAULT_POLY #else


#define CDS_ATTR_std_compat_none 0
#define CDS_ATTR_std_compat_safe 1
#define CDS_ATTR_std_compat_unsafe 2


#ifndef CDS_OPTION_STD_COMPAT_MODE
#define CDS_ATTR_std_compat_mode CDS_ATTR_std_compat_safe
#else // #ifdef CDS_OPTION_STD_COMPAT_MODE
#if !(CDS_OPTION_STD_COMPAT_MODE >= CDS_ATTR(std_compat_none) && CDS_OPTION_STD_COMPAT_MODE <= CDS_ATTR(std_compat_unsafe))
#error Invalid stdlib compat mode
#else
#define CDS_ATTR_std_compat_mode CDS_OPTION_STD_COMPAT_MODE
#endif
#endif // #ifdef CDS_OPTION_STD_COMPAT_MODE #else

#if CDS_ATTR(std_compat_mode) == CDS_ATTR(std_compat_none)
#define CDS_ATTR_std_compat false
#else
#define CDS_ATTR_std_compat true
#endif

#ifdef CDS_OPTION_DISABLE_EXCEPTIONS
#define CDS_ATTR_exceptions false
#else // #ifdef CDS_OPTION_DISABLE_EXCEPTIONS
#define CDS_ATTR_exceptions true
#endif // #ifdef CDS_OPTION_DISABLE_EXCEPTIONS #else


#ifdef _MSC_VER
#define CDS_ATTR_std _MSVC_LANG
#else // #ifdef _MSC_VER
#define CDS_ATTR_std __cplusplus
#endif // #ifdef _MSC_VER #else


#define CDS_ATTR_std11 201103L
#define CDS_ATTR_std14 201402L
#define CDS_ATTR_std17 201703L
#define CDS_ATTR_std20 202002L
#define CDS_ATTR_std23 202302L


#if CDS_ATTR(std) >= CDS_ATTR(std11)
#define CDS_ATTR_cpp11 true
#define CDS_ATTR_constexpr_11 constexpr
#undef CDS_ATTR_noreturn
#define CDS_ATTR_noreturn CDS_ATTR_NEWSTYLE(noreturn)
#undef CDS_ATTR_maybe_unused
#define CDS_ATTR_maybe_unused CDS_ATTR_OLDSTYLE(unused)
#undef CDS_ATTR_carries_dependency
#define CDS_ATTR_carries_dependency CDS_ATTR_NEWSTYLE(carries_dependency)
#else // before cpp11
#define CDS_ATTR_cpp11 false
#define CDS_ATTR_constexpr_11 inline
#endif

#if CDS_ATTR(std) >= CDS_ATTR(std14)
#define CDS_ATTR_cpp14 true
#define CDS_ATTR_constexpr_14 constexpr
#undef CDS_ATTR_deprecated
#define CDS_ATTR_deprecated(message) CDS_ATTR_NEWSTYLE(deprecated(message))
#else // before cpp14
#define CDS_ATTR_cpp14 false
#define CDS_ATTR_constexpr_14 inline
#endif

#if CDS_ATTR(std) >= CDS_ATTR(std17)
#define CDS_ATTR_cpp17 true
#define CDS_ATTR_constexpr_17 constexpr
#define CDS_ATTR_ctad true
#define CDS_ATTR_sentinel true
#undef CDS_ATTR_fallthrough
#define CDS_ATTR_fallthrough CDS_ATTR_NEWSTYLE(fallthrough)
#undef CDS_ATTR_maybe_unused
#define CDS_ATTR_maybe_unused CDS_ATTR_NEWSTYLE(maybe_unused)
#undef CDS_ATTR_nodiscard
#define CDS_ATTR_nodiscard CDS_ATTR_NEWSTYLE(nodiscard)
#define CDS_ATTR_noexcept_fn_type true
#else // before cpp17
#define CDS_ATTR_cpp17 false
#define CDS_ATTR_constexpr_17 inline
#define CDS_ATTR_ctad false
#define CDS_ATTR_sentinel false
#define CDS_ATTR_noexcept_fn_type false
#endif

#if CDS_ATTR(std) >= CDS_ATTR(std20)
#define CDS_ATTR_cpp20 true
#define CDS_ATTR_constexpr_20 constexpr
#define CDS_ATTR_spaceship true
#undef CDS_ATTR_likely
#define CDS_ATTR_likely CDS_ATTR_NEWSTYLE(likely)
#undef CDS_ATTR_unlikely
#define CDS_ATTR_unlikely CDS_ATTR_NEWSTYLE(unlikely)
#undef CDS_ATTR_no_unique_address
#define CDS_ATTR_no_unique_address CDS_ATTR_NEWSTYLE(no_unique_address)
#define CDS_ATTR_explicit explicit(true)
#define CDS_ATTR_implicit explicit(false)
#else // before cpp20
#define CDS_ATTR_cpp20 false
#define CDS_ATTR_constexpr_20 inline
#define CDS_ATTR_spaceship false
#define CDS_ATTR_explicit explicit
#define CDS_ATTR_implicit
#endif

#if CDS_ATTR(std) >= CDS_ATTR(std23)
#define CDS_ATTR_cpp23 true
#define CDS_ATTR_constexpr_23 constexpr
#else // before cpp23
#define CDS_ATTR_cpp23 false
#define CDS_ATTR_constexpr_23 inline
#endif

namespace cds {
using U8 = unsigned char;
using U16 = unsigned short;
using U32 = unsigned int;

using S8 = signed char;
using S16 = signed short;
using S32 = signed int;

enum class Byte : U8 {};

// compiler & platform specific
#ifdef _MSC_VER
#define CDS_ATTR_msvc true
#else // #ifdef _MSC_VER
#define CDS_ATTR_msvc false
#endif // #ifdef _MSC_VER #else

#ifdef __clang__
#define CDS_ATTR_clang true
#else // #ifdef __clang__
#define CDS_ATTR_clang false
#endif // #ifdef __clang__ #else

#if defined(__GNUC__) && !defined(__clang__)
#define CDS_ATTR_gcc true
#else // #if defined(__GNUC__) && !defined(__clang__)
#define CDS_ATTR_gcc false
#endif // #if defined(__GNUC__) && !defined(__clang__) #else

#ifdef __MINGW64__
#define CDS_ATTR_mingw64 true
#else // #ifdef __MINGW64__
#define CDS_ATTR_mingw64 false
#endif // #ifdef __MINGW64__ #else

#if CDS_ATTR(gcc) || CDS_ATTR(clang)
#if defined(__x86_64__) && !defined(__ILP32__)
#define CDS_ATTR_bitarch 64
#else // 32bit
#define CDS_ATTR_bitarch 32
#endif
#endif // #if CDS_ATTR(gcc) || CDS_ATTR(clang) #endif

#if CDS_ATTR(msvc)
#if _WIN64
#define CDS_ATTR_bitarch 64
#else
#define CDS_ATTR_bitarch 32
#endif
#endif // #if CDS_ATTR(msvc) #else

#if CDS_ATTR(bitarch) == 64 // native 64 bit
#if CDS_ATTR(msvc)
using U64 = unsigned long long int;
using S64 = signed long long int;
#else
using U64 = unsigned long int;
using S64 = signed long int;
#endif
using Size = U64;
using SSize = S64;
using Idx = S64;
using Address = U64;
#elif CDS_ATTR(bitarch) == 32
using U64 = unsigned long long int;
using S64 = signed long long int;
using Size = U32;
using SSize = S32;
using Idx = S32;
using Address = U32;
#else
static_assert(false, "Undefined architecture bits (reg/addr size)");
#endif

namespace limits {
constexpr U8 u8Min = 0x00U;
constexpr U8 u8Max = 0xffU;

constexpr U16 u16Min = 0x0000U;
constexpr U16 u16Max = 0xffffU;

constexpr U32 u32Min = 0x00000000LU;
constexpr U32 u32Max = 0xffffffffLU;

constexpr U64 u64Min = 0x0000000000000000LLU;
constexpr U64 u64Max = 0xffffffffffffffffLLU;

constexpr S8 s8Min = -0x80;
constexpr S8 s8Max = 0x7f;

constexpr S16 s16Min = -0x8000;
constexpr S16 s16Max = 0x7fff;

constexpr S32 s32Min = -0x80000000L;
constexpr S32 s32Max = 0x7fffffffL;

constexpr S64 s64Max = 0x7fffffffffffffffLL;
constexpr S64 s64Min = -s64Max - 1;
} // namespace limits

#if defined __x86_64__ && !defined __ILP32__ // native 64 bit
namespace limits {
constexpr Size sizeMin = u64Min;
constexpr Size sizeMax = u64Max;

constexpr SSize ssizeMin = s64Min;
constexpr SSize ssizeMax = s64Max;

constexpr Idx idxMin = s64Min;
constexpr Idx idxMax = s64Max;
} // namespace limits
#else // 32 bit
namespace limits {
constexpr Size sizeMin = u32Min;
constexpr Size sizeMax = u32Max;

constexpr SSize ssizeMin = s32Min;
constexpr SSize ssizeMax = s32Max;

constexpr Idx idxMin = s32Min;
constexpr Idx idxMax = s32Max;
} // namespace limits
#endif

namespace compiler {
struct StdCpp11 {
  constexpr static int version = 11;
  constexpr static auto const* literal = "cpp-11";
};
struct StdCpp14 {
  constexpr static int version = 14;
  constexpr static auto const* literal = "cpp-14";
};
struct StdCpp17 {
  constexpr static int version = 17;
  constexpr static auto const* literal = "cpp-17";
};
struct StdCpp20 {
  constexpr static int version = 20;
  constexpr static auto const* literal = "cpp-20";
};
struct StdCpp23 {
  constexpr static int version = 23;
  constexpr static auto const* literal = "cpp-23";
};

#if CDS_ATTR(std) > CDS_ATTR(std20)
using CurrentStd = StdCpp23;
#elif CDS_ATTR(std) > CDS_ATTR(std17)
using CurrentStd = StdCpp20;
#elif CDS_ATTR(std) > CDS_ATTR(std14)
using CurrentStd = StdCpp17;
#elif CDS_ATTR(std) > CDS_ATTR(std11)
using CurrentStd = StdCpp14;
#else
using CurrentStd = StdCpp11;
#endif

// compiler & platform specific
#ifdef _MSC_VER
#define CDS_ATTR_inheritsEBOs __declspec(empty_bases)
#define CDS_ATTR_ld_size 64

// msvc::no_unique_address
// https://devblogs.microsoft.com/cppblog/msvc-cpp20-and-the-std-cpp20-switch/#c20-no_unique_address
#if _MSC_VER >= 1929 && CDS_ATTR(std) >= CDS_ATTR(std14)
#undef CDS_ATTR_no_unique_address
#define CDS_ATTR_no_unique_address CDS_ATTR_NEWSTYLE(msvc::no_unique_address)
#endif // msvc::no_unique_address

// Replace instances of noexcept specifications in friend functions with nothing.
// MSVC front-end does not resolve these correctly.
#undef CDS_ATTR_friend_noexcept
#define CDS_ATTR_friend_noexcept(...)

struct CurrentCompiler {
  constexpr static char const* name = "Microsoft Visual C++";
  constexpr static char const* id = "msvc";
  constexpr static int version = _MSC_VER;
};
#else // #ifdef _MSC_VER
#define CDS_ATTR_inheritsEBOs
#endif // #ifdef _MSC_VER #else

#ifdef __clang__
#define CDS_ATTR_ld_size 80

struct CurrentCompiler {
  constexpr static auto const* name = "LLVM clang";
  constexpr static auto const* id = "clang";
  constexpr static int version = __clang_major__ * 10000 + __clang_minor__ * 100 + __clang_patchlevel__;
};
#endif // #ifdef __clang__ #else

#if defined(__GNUC__) && !defined(__clang__)
#define CDS_ATTR_ld_size 80

struct CurrentCompiler {
  constexpr static auto const* name = "GNU gcc";
  constexpr static auto const* id = "gcc";
  constexpr static int version = __GNUC__ * 10000 + __GNUC_MINOR__ * 100 + __GNUC_PATCHLEVEL__;
};
#endif // #if defined(__GNUC__) && !defined(__clang__) #else

#ifdef __MINGW64__

struct CurrentCompiler {
  constexpr static auto const* name = "MINGW gcc-64";
  constexpr static auto const* id = "mingw-64";
  constexpr static int version = __MINGW64_VERSION_MAJOR * 10000 + __MINGW64_VERSION_MINOR * 100 + __MINGW64_VERSION_BUGFIX;
};
#endif // #ifdef __MINGW64__ #else
} // namespace compiler
} // namespace cds

#endif // CDS_META_COMPILER_HPP
