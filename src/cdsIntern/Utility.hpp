//
// Created by loghin on 22/09/2021.
//

#ifndef __CDS_UTILITY_HPP__
#define __CDS_UTILITY_HPP__ // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

#include <type_traits>
#include "../prepro.h"
#include <CDS/memory/Allocation>
#include <CDS/Conversion>
#include <CDS/Limits>
#include <CDS/meta/TypeTraits>

#if __CDS_cpplang_core_version >= __CDS_cpplang_core_version_20
#include <bit>
#endif

namespace cds {
template <typename __Type, typename __SmartPointer> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_NoDiscard __CDS_MaybeUnused __CDS_OptimalInline auto copy (__Type const& object) noexcept(false) -> __SmartPointer {
  return SmartPointerType (copy (object));
}

template <typename __Type>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_NoDiscard __CDS_MaybeUnused constexpr auto compare (__Type const & left, __Type const & right) noexcept -> bool {
  return meta::equals (left, right);
}

template <typename __Type>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_MaybeUnused constexpr auto streamPrint (std::ostream& out, __Type const& object) noexcept -> std::ostream& {
  return meta::print (out, object);
}

template <typename __Type, typename = meta::EnableIf <meta::IsCopyConstructible <__Type>::value>> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_NoDiscard __CDS_OptimalInline auto copy (__Type const& obj) noexcept -> __Type* {
  return Memory::instance().create <__Type> (obj);
}

template <typename __Type, meta::EnableIf <meta::IsPrintable <__Type>::value> = 0>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto println (__Type const& obj) noexcept -> std::ostream& {
  return std::cout << obj << '\n';
}

template <typename __To, typename __From>   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto bitCast (__From from) noexcept -> __To {
  using namespace cds::meta;
  static_assert (sizeof (__From) == sizeof (__To), "Bit cast requires size-equal types");
  static_assert (IsTriviallyCopyable <__From>::value, "Types involved must be trivially copyable");
  static_assert (IsTriviallyCopyable <__To>::value, "Types involved must be trivially copyable");
  static_assert (IsTriviallyConstructible<__To>::value, "Target type must be trivially constructible");
#if __CDS_cpplang_core_version >= __CDS_cpplang_core_version_20
  return std::bit_cast <__To> (from);
#else
  __To value;
  (void) std::memcpy (&value, &from, sizeof(__From));
  return value;
#endif
}
} // namespace cds

#include "../shared/impl/arithmetic.hpp"
#include "../shared/impl/generalPredicates.hpp"


#endif // __CDS_UTILITY_HPP__
