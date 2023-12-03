//
// Created by loghin on 22/09/2021.
//

#ifndef CDS_META_COMPILER_HPP
#define CDS_META_COMPILER_HPP

namespace cds {
// Base Types
using U8 = unsigned char;
using U16 = unsigned short;
using U32 = unsigned int;

using S8 = signed char;
using S16 = signed short;
using S32 = signed int;

using Byte = U8;

#if defined __x86_64__ && !defined __ILP32__ // native 64 bit
using U64 = unsigned long int;
using S64 = signed long int;
using Size = U64;
using SSize = S64;
using Idx = S64;
using Address = U64;
#else // 32 bit
using U64 = unsigned long long int;
using S64 = signed long long int;
using Size = U32;
using SSize = S32;
using Idx = S32;
using Address = U32;
#endif

namespace compiler {
// standard specific
#define CDS_ATTR_JOIN_LATE(prefix, opt) prefix ## opt
#define CDS_ATTR(opt) CDS_ATTR_JOIN_LATE(CDS_ATTR_, opt)

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
#define CDS_ATTR_nodiscard(...)
#define CDS_ATTR_inline
#define CDS_ATTR_constexpr(std) CDS_ATTR_JOIN_LATE(CDS_ATTR_constexpr_, std)

#if __cplusplus >= 201103L
#define CDS_ATTR_constexpr_11 constexpr
#undef CDS_ATTR_noreturn
#define CDS_ATTR_noreturn CDS_ATTR_NEWSTYLE(noreturn)
#undef CDS_ATTR_maybe_unused
#define CDS_ATTR_maybe_unused CDS_ATTR_OLDSTYLE(maybe_unused)
#undef CDS_ATTR_carries_dependency
#define CDS_ATTR_carries_dependency CDS_ATTR_NEWSTYLE(carries_dependency)
#else
#define CDS_ATTR_constexpr_11 inline
#endif

#if __cplusplus >= 201402L
#define CDS_ATTR_constexpr_14 constexpr
#undef CDS_ATTR_deprecated
#define CDS_ATTR_deprecated(message) CDS_ATTR_NEWSTYLE(deprecated(message))
#else
#define CDS_ATTR_constexpr_14 inline
#endif

#if __cplusplus >= 201703L
#define CDS_ATTR_constexpr_17 constexpr
#define CDS_ATTR_ctad true
#undef CDS_ATTR_fallthrough
#define CDS_ATTR_fallthrough CDS_ATTR_NEWSTYLE(fallthrough)
#undef CDS_ATTR_maybe_unused
#define CDS_ATTR_maybe_unused CDS_ATTR_NEWSTYLE(maybe_unused)
#undef CDS_ATTR_nodiscard
#define CDS_ATTR_nodiscard CDS_ATTR_NEWSTYLE(nodiscard)
#else
#define CDS_ATTR_constexpr_17 inline
#define CDS_ATTR_ctad false
#endif

#if __cplusplus >= 202002L
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
#else
#define CDS_ATTR_constexpr_20 inline
#define CDS_ATTR_spaceship false
#define CDS_ATTR_explicit explicit
#define CDS_ATTR_implicit
#endif

#if __cplusplus >= 202302L
#endif

struct StdCpp11 {
  constexpr static int version = 11;
  constexpr static char const* literal = "cpp-11";
};
struct StdCpp14 {
  constexpr static int version = 14;
  constexpr static char const* literal = "cpp-14";
};
struct StdCpp17 {
  constexpr static int version = 17;
  constexpr static char const* literal = "cpp-17";
};
struct StdCpp20 {
  constexpr static int version = 20;
  constexpr static char const* literal = "cpp-20";
};
struct StdCpp23 {
  constexpr static int version = 23;
  constexpr static char const* literal = "cpp-23";
};

#if __cplusplus > 202002L
using CurrentStd = StdCpp23;
#elif __cplusplus > 201703L
using CurrentStd = StdCpp20;
#elif __cplusplus > 201402L
using CurrentStd = StdCpp17;
#elif __cplusplus > 201103L
using CurrentStd = StdCpp14;
#else
using CurrentStd = StdCpp11;
#endif

// compiler & platform specific
#ifdef _MSC_VER
#define CDS_ATTR_inheritsEBOs __declspec(empty_bases)
#define CDS_ATTR_msvc true

struct CurrentCompiler {
  constexpr static char const* name = "Microsoft Visual C++";
  constexpr static char const* id = "msvc";
  constexpr static int version = MSVC_VERSION
};
#else
#define CDS_ATTR_inheritsEBOs
#define CDS_ATTR_msvc false
#endif

#ifdef __clang__
#define CDS_ATTR_clang true

struct CurrentCompiler {
  constexpr static char const* name = "LLVM clang";
  constexpr static char const* id = "clang";
  constexpr static int version = __clang_major__ * 10000 + __clang_minor__ * 100 + __clang_patchlevel__;
};
#else
#define CDS_ATTR_clang false
#endif

#if defined(__GNUC__) && !defined(__clang__)
#define CDS_ATTR_gcc true

struct CurrentCompiler {
  constexpr static char const* name = "GNU gcc";
  constexpr static char const* id = "gcc";
  constexpr static int version = __GNUC__ * 10000 + __GNUC_MINOR__ * 100 + __GNUC_PATCHLEVEL__;
};
#else
#define CDS_ATTR_gcc false
#endif

#ifdef __MINGW64__
#define CDS_ATTR_mingw64 true

struct CurrentCompiler {
  constexpr static char const* name = "MINGW gcc-64";
  constexpr static char const* id = "mingw-64";
  constexpr static int version = __MINGW64_VERSION_MAJOR * 10000 + __MINGW64_VERSION_MINOR * 100 + __MINGW64_VERSION_BUGFIX;
};
#else
#define CDS_ATTR_mingw64 false
#endif
}
} // namespace cds

#endif // CDS_META_COMPILER_HPP
