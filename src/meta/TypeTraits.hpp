//
// Created by loghin on 12/5/23.
//

#ifndef CDS_META_TYPE_TRAITS_HPP
#define CDS_META_TYPE_TRAITS_HPP
#pragma once

#include <cds/meta/Compiler>
#include <cds/meta/Base>
#include <type_traits>

namespace cds {
namespace meta {
namespace impl {
template <typename, typename = void> struct IsReferenceable : meta::False {};
template <typename T> struct IsReferenceable<T, Void<T&>> : meta::True {};

template <typename> struct IsVoid : meta::False {};
template <> struct IsVoid<void> : meta::True {};

template <typename T> struct IsEnum : ConvertIntegral<std::is_enum<T>> {};
template <typename T> struct IsUnion : ConvertIntegral<std::is_union<T>> {};
template <typename T> struct IsClass : ConvertIntegral<std::is_class<T>> {};
template <typename T> struct IsFundamental : ConvertIntegral<std::is_fundamental<T>> {};
template <typename T> struct IsIntegral : ConvertIntegral<std::is_integral<T>> {};
template <typename T> struct IsFloating : ConvertIntegral<std::is_floating_point<T>> {};
template <typename T> struct IsArithmetic : ConvertIntegral<std::is_arithmetic<T>> {};

template <typename T, bool = IsArithmetic<T>::value> struct IsSigned : meta::False {};
template <typename T> struct IsSigned<T, true> : meta::Bool<T(-1) < T(0)> {};

template <typename> struct IsArray : meta::False {};
template <typename T, Size s> struct IsArray<T[s]> : meta::True {};
template <typename T> struct IsArray<T[]> : meta::True {};

template <typename> struct IsBoundedArray : False {};
template <typename T, Size s> struct IsBoundedArray<T[s]> : meta::True {};

template <typename> struct IsUnboundedArray : meta::False {};
template <typename T> struct IsUnboundedArray<T[]> : meta::True {};

template <typename> struct IsPointer : meta::False {};
template <typename T> struct IsPointer<T*> : meta::True {};

template <typename> struct IsLValRef : meta::False {};
template <typename T> struct IsLValRef<T&> : meta::True {};

template <typename> struct IsRValRef : meta::False {};
template <typename T> struct IsRValRef<T&&> : meta::True {};

template <typename T> struct IsRef : meta::Or<IsLValRef<T>, IsRValRef<T>> {};

template <typename> struct IsConst : meta::False {};
template <typename T> struct IsConst<T const> : meta::True {};

template <typename> struct IsVolatile : meta::False {};
template <typename T> struct IsVolatile<T volatile> : meta::True {};

template <typename T> struct IsConstVolatile : meta::And<IsConst<T>, IsVolatile<T>> {};

#if CDS_ATTR(msvc)
#pragma warning(disable: 4180)
#endif
template <typename T> struct IsFunction :
    meta::And<Not<IsConst<T const>>, Not<IsRef<T>>>::Type {};
#if CDS_ATTR(msvc)
#pragma warning(default: 4180)
#endif

template <typename F, typename T, typename = typename meta::Or<IsVoid<F>, IsFunction<T>, IsArray<T>>::Type>
class IsConvertible : public IsVoid<T> {};

template <typename F, typename T> class IsConvertible<F, T, meta::False> {
  template <typename T1> static auto convert(T1) noexcept -> void;
  template <typename F1, typename T1, typename = decltype(IsConvertible::convert<T1>(meta::rvalue<F1>()))>
  static auto test(int) noexcept -> meta::True;
  template <typename, typename> static auto test(...) noexcept -> meta::False;

public:
  using Type = decltype(IsConvertible::test<F, T>(0));
};

template <typename T> struct RemoveConst { using Type = T; };
template <typename T> struct RemoveConst<T const> { using Type = T; };

template <typename T> struct RemoveVolatile { using Type = T; };
template <typename T> struct RemoveVolatile<T volatile> { using Type = T; };

template <typename T> struct RemoveRef { using Type = T; };
template <typename T> struct RemoveRef<T&> { using Type = T; };
template <typename T> struct RemoveRef<T&&> { using Type = T; };

template <typename T, typename> struct RemovePointer { using Type = T; };
template <typename T, typename V> struct RemovePointer<T, V*> { using Type = V; };

template <typename T> struct RemoveExtent { using Type = T; };
template <typename T, Size s> struct RemoveExtent<T[s]> { using Type = T; };
template <typename T> struct RemoveExtent<T[]> { using Type = T; };

template <typename T> struct RemoveAllExtents { using Type = T; };
template <typename T, Size s> struct RemoveAllExtents<T[s]> { using Type = typename RemoveAllExtents<T>::Type; };
template <typename T> struct RemoveAllExtents<T[]> { using Type = typename RemoveAllExtents<T>::Type; };

template <typename T, typename = void> struct AddPointer { using Type = T*; };
template <typename T> struct AddPointer<T&> { using Type = T*; };
template <typename T> struct AddPointer<T&&> { using Type = T*; };
template <typename T> struct AddConst { using Type = T const; };
template <typename T> struct AddVolatile { using Type = T volatile; };
template <typename T, typename = typename IsReferenceable<T>::Type> struct AddLValRef { using Type = T; };
template <typename T> struct AddLValRef<T, True> { using Type = T&; };
template <typename T, typename = typename IsReferenceable<T>::Type> struct AddRValRef { using Type = T; };
template <typename T> struct AddRValRef<T, True> { using Type = T&&; };

template <typename T, typename = typename IsArray<T>::Type, typename = typename IsFunction<T>::Type>
struct DecayHelper {};

template <typename T> struct DecayHelper<T, False, False> {
  using Type = typename RemoveConst<typename RemoveVolatile<T>::Type>::Type;
};

template <typename T> struct DecayHelper<T, True, False> {
  using Type = typename RemoveExtent<T>::Type*;
};

template <typename T> struct DecayHelper<T, False, True> {
  using Type = typename AddPointer<T>::Type;
};

template <typename T> struct Decay {
  using Type = typename DecayHelper<typename RemoveRef<T>::Type>::Type;
};

template <typename...> struct Common {};
template <> struct Common<> {};
template <typename T> struct Common<T> : Common<T, T> {};

struct CommonHelper {
  template <typename T> struct Success { using Type = T; };
  struct Failure {};

  template <typename T, typename V, bool _ = true> using CommonByConditional
      = decltype(_ ? meta::rvalue<T>() : meta::rvalue<V>());

  template <typename T, typename V> static auto firstTest(int) noexcept
      -> Success<typename Decay<CommonByConditional<T, V>>::Type>;

  template <typename T, typename V>
  static auto secondTest(int) noexcept -> Success<typename RemoveConst<typename RemoveVolatile<
      CommonByConditional<T const&, V const&>
  >::Type>::Type>;

  template <typename, typename> static auto secondTest(...) noexcept -> Failure;
  template <typename T, typename V> static auto firstTest(...) noexcept -> decltype(CommonHelper::secondTest<T, V>(0));
};

struct NonDecayCommonHelper {
  template <typename T> struct Success { using Type = T; };
  struct Failure {};

  template <typename T, typename V, bool _ = true> using CommonByConditional
      = decltype(_ ? meta::value<T>() : meta::value<V>());

  template <typename T, typename V> static auto test(int) noexcept
      -> Success<CommonByConditional<T, V>>;

  template <typename T, typename V> static auto test(...) noexcept -> Failure;
};

template <typename T, typename V, typename DT = typename Decay<T>::Type, typename DV = typename Decay<V>::Type>
struct CommonDecayed { using Type = Common<DT, DV>; };

template <typename T, typename V> struct CommonDecayed<T, V, T, V> {
  using Type = decltype(CommonHelper::firstTest<T, V>(0));
};

template <typename, typename, typename = void> struct Fold {};
template <typename C, typename... R> struct Fold<C, Pack<R...>, Void<typename C::Type>> :
    Common<typename C::Type, R...> {};

template <typename C, typename R> struct Fold<C, R, void> {};

template <typename T, typename V> struct Common<T, V> : CommonDecayed<T, V>::Type {};
template <typename T, typename V, typename... R> struct Common<T, V, R...> : Fold<Common<T, V>, Pack<R...>> {};

template <typename... Ts> struct NonDecayedCommon;

template <typename T> struct NonDecayedCommon<T> {
  using Type = T;
};

template <typename T> struct NonDecayedCommon<T, T> {
  using Type = T;
};

template <typename T, typename V> struct NonDecayedCommon<T, V> {
  using Type = typename decltype(NonDecayCommonHelper::test<T, V>(0))::Type;
};

template <typename, typename, typename = void> struct NonDecayedFold {};
template <typename C, typename... R> struct NonDecayedFold<C, Pack<R...>, Void<typename C::Type>> :
    NonDecayedCommon<typename C::Type, R...> {};

template <typename T, typename V, typename... R> struct NonDecayedCommon<T, V, R...> :
    NonDecayedFold<NonDecayedCommon<T, V>, Pack<R...>> {};

template <typename T> struct SignedEquivalent {};
template <> struct SignedEquivalent<char> { using Type = signed char; };
template <> struct SignedEquivalent<U8> { using Type = S8; };
template <> struct SignedEquivalent<U16> { using Type = S16; };
template <> struct SignedEquivalent<U32> { using Type = S32; };
template <> struct SignedEquivalent<U64> { using Type = S64; };
#if (defined(__linux) || defined(__APPLE__)) && CDS_ATTR(bitarch) == 64
template <> struct SignedEquivalent<unsigned long long> { using Type = signed long long; };
#elif defined(WIN32) && CDS_ATTR(bitarch) == 64
template <> struct SignedEquivalent<unsigned long> { using Type = signed long; };
#endif

template <typename T> struct UnsignedEquivalent {};
template <> struct UnsignedEquivalent<char> { using Type = unsigned char; };
template <> struct UnsignedEquivalent<S8> { using Type = U8; };
template <> struct UnsignedEquivalent<S16> { using Type = U16; };
template <> struct UnsignedEquivalent<S32> { using Type = U32; };
template <> struct UnsignedEquivalent<S64> { using Type = U64; };
#if (defined(__linux) || defined(__APPLE__)) && CDS_ATTR(bitarch) == 64
template <> struct UnsignedEquivalent<signed long long> { using Type = unsigned long long; };
#elif defined(WIN32) && CDS_ATTR(bitarch) == 64
template <> struct SignedEquivalent<signed long> { using Type = unsigned long; };
#endif

template <typename T> struct TypeId { using Type = T; };
template <typename T> struct UnderlyingType { using Type = typename std::underlying_type<T>::type; };
template <typename T> struct IsEmpty : ConvertIntegral<std::is_empty<T>> {};

#if CDS_ATTR(clang) || CDS_ATTR(gcc)
template <typename T> struct IsFinal : Bool<__is_final(T)>::Type {};
#else
#error Define specifically for compiler intrinsic for C++11.
template <typename T> struct IsFinal : False {};
#endif // #if CDS_ATTR(clang) || CDS_ATTR(gcc)
} // namespace impl

template <typename Type> using RemoveConst = typename impl::RemoveConst<Type>::Type;
template <typename Type> using RemoveVolatile = typename impl::RemoveVolatile<Type>::Type;
template <typename Type> using RemoveConstVolatile = RemoveConst<RemoveVolatile<Type>>;
template <typename Type> using RemoveRef = typename impl::RemoveRef<Type>::Type;
template <typename Type> using RemoveCVRef = RemoveConstVolatile<RemoveRef<Type>>;
template <typename Type> using RemovePointer
    = typename impl::RemovePointer<Type, RemoveConstVolatile<Type>>::Type;

template <typename Type> using RemoveExtent = typename impl::RemoveExtent<Type>::Type;
template <typename Type> using RemoveAllExtents = typename impl::RemoveAllExtents<Type>::Type;

template <typename Type> using AddPointer = typename impl::AddPointer<Type>::Type;
template <typename Type> using AddConst = typename impl::AddConst<Type>::Type;
template <typename Type> using AddVolatile = typename impl::AddVolatile<Type>::Type;
template <typename Type> using AddConstVolatile = AddConst<AddVolatile<Type>>;
template <typename Type> using AddLValRef = typename impl::AddLValRef<Type>::Type;
template <typename Type> using AddRValRef = typename impl::AddRValRef<Type>::Type;

template <typename Type> struct IsReferenceable : impl::IsReferenceable<Type>::Type {};
template <typename Type> struct IsVoid : impl::IsVoid<RemoveConstVolatile<Type>>::Type {};

template <typename Type> struct IsEnum : impl::IsEnum<Type>::Type {};
template <typename Type> struct IsUnion : impl::IsUnion<Type>::Type {};
template <typename Type> struct IsClass : impl::IsClass<Type>::Type {};
template <typename Type> struct IsFunction : impl::IsFunction<Type>::Type {};
template <typename Type> struct IsFundamental : impl::IsFundamental<Type>::Type {};
template <typename Type> struct IsIntegral : impl::IsIntegral<Type>::Type {};
template <typename Type> struct IsFloating : impl::IsFloating<Type>::Type {};
template <typename Type> struct IsArithmetic : impl::IsArithmetic<Type>::Type {};
template <typename Type> struct IsSigned : impl::IsSigned<Type>::Type {};
template <typename Type> struct IsUnsigned : And<IsArithmetic<Type>, Not<IsSigned<Type>>> {};

template <typename Type> struct IsArray : impl::IsArray<Type>::Type {};
template <typename Type> struct IsBoundedArray : impl::IsBoundedArray<Type>::Type {};
template <typename Type> struct IsUnboundedArray : impl::IsUnboundedArray<Type>::Type {};
template <typename Type> struct IsPointer : impl::IsPointer<Type>::Type {};
template <typename Type> struct IsLValRef : impl::IsLValRef<Type>::Type {};
template <typename Type> struct IsRValRef : impl::IsRValRef<Type>::Type {};
template <typename Type> struct IsRef : impl::IsRef<Type>::Type {};
template <typename Type> struct IsConst : impl::IsConst<Type>::Type {};
template <typename Type> struct IsVolatile : impl::IsVolatile<Type>::Type {};
template <typename Type> struct IsConstVolatile : impl::IsConstVolatile<Type>::Type {};

template <typename From, typename To> struct IsConvertible : impl::IsConvertible<From, To>::Type {};

template <typename Left, typename Right> struct IsSameIgnoringCVRef :
    impl::IsSame<RemoveCVRef<Left>, RemoveCVRef<Right>>::Type {};

template <typename T> using SignedEquivalent = typename impl::SignedEquivalent<T>::Type;
template <typename T> using UnsignedEquivalent = typename impl::UnsignedEquivalent<T>::Type;

namespace impl {
namespace primitiveTypeInfoNames {
template <typename = void> struct Unknown { static char constexpr name[8u] = "unknown"; };
template <typename = void> struct Void { static char constexpr name[5u] = "void"; };
template <typename = void> struct Bool { static char constexpr name[5u] = "bool"; };
template <typename = void> struct WCharT { static char constexpr name[8u] = "wchar_t"; };
template <typename = void> struct Char16T { static char constexpr name[9u] = "char16_t"; };
template <typename = void> struct Char32T { static char constexpr name[9u] = "char32_t"; };
template <typename = void> struct SignedChar { static char constexpr name[12u] = "signed char"; };
template <typename = void> struct SignedShort { static char constexpr name[13u] = "signed short"; };
template <typename = void> struct SignedInt { static char constexpr name[11u] = "signed int"; };
template <typename = void> struct SignedLong { static char constexpr name[12u] = "signed long"; };
template <typename = void> struct UnsignedChar { static char constexpr name[14u] = "unsigned char"; };
template <typename = void> struct UnsignedShort { static char constexpr name[15u] = "unsigned short"; };
template <typename = void> struct UnsignedInt { static char constexpr name[13u] = "unsigned int"; };
template <typename = void> struct UnsignedLong { static char constexpr name[14u] = "unsigned long"; };
template <typename = void> struct Float { static char constexpr name[6u] = "float"; };
template <typename = void> struct Double { static char constexpr name[7u] = "double"; };

#if CDS_ATTR(cpp20)
template <typename = void> struct Char8T { static char constexpr name[8u] = "char8_t"; };
#endif // #if CDS_ATTR(cpp20)

// ODR before cpp17
template <typename T> char const Unknown<T>::name[8u];
template <typename T> char const Void<T>::name[5u];
template <typename T> char const Bool<T>::name[5u];
template <typename T> char const WCharT<T>::name[8u];
template <typename T> char const Char16T<T>::name[9u];
template <typename T> char const Char32T<T>::name[9u];
template <typename T> char const SignedChar<T>::name[12u];
template <typename T> char const SignedShort<T>::name[13u];
template <typename T> char const SignedInt<T>::name[11u];
template <typename T> char const SignedLong<T>::name[12u];
template <typename T> char const UnsignedChar<T>::name[14u];
template <typename T> char const UnsignedShort<T>::name[15u];
template <typename T> char const UnsignedInt<T>::name[13u];
template <typename T> char const UnsignedLong<T>::name[14u];
template <typename T> char const Float<T>::name[6u];
template <typename T> char const Double<T>::name[7u];

#if CDS_ATTR(cpp20)
template <typename T> char const Char8T<T>::name[8u];
#endif // #if CDS_ATTR(cpp20)
} // namespace primitiveTypeInfoNames
} // namespace impl

template <typename> struct TypeInfo : impl::primitiveTypeInfoNames::Unknown<> {};
template <template <typename...> class> struct TemplateTypeInfo : impl::primitiveTypeInfoNames::Unknown<> {};

template <> struct TypeInfo<void> : impl::primitiveTypeInfoNames::Void<> {};
template <> struct TypeInfo<bool> : impl::primitiveTypeInfoNames::Bool<> {};
template <> struct TypeInfo<wchar_t> : impl::primitiveTypeInfoNames::WCharT<> {};
template <> struct TypeInfo<char16_t> : impl::primitiveTypeInfoNames::Char16T<> {};
template <> struct TypeInfo<char32_t> : impl::primitiveTypeInfoNames::Char32T<> {};
template <> struct TypeInfo<signed char> : impl::primitiveTypeInfoNames::SignedChar<> {};
template <> struct TypeInfo<signed short> : impl::primitiveTypeInfoNames::SignedShort<> {};
template <> struct TypeInfo<signed int> : impl::primitiveTypeInfoNames::SignedInt<> {};
template <> struct TypeInfo<signed long> : impl::primitiveTypeInfoNames::SignedLong<> {};
template <> struct TypeInfo<unsigned char> : impl::primitiveTypeInfoNames::UnsignedChar<> {};
template <> struct TypeInfo<unsigned short> : impl::primitiveTypeInfoNames::UnsignedShort<> {};
template <> struct TypeInfo<unsigned int> : impl::primitiveTypeInfoNames::UnsignedInt<> {};
template <> struct TypeInfo<unsigned long> : impl::primitiveTypeInfoNames::UnsignedLong<> {};
template <> struct TypeInfo<float> : impl::primitiveTypeInfoNames::Float<> {};
template <> struct TypeInfo<double> : impl::primitiveTypeInfoNames::Double<> {};

#if CDS_ATTR(cpp20)
template <> struct TypeInfo<char8_t> : impl::primitiveTypeInfoNames::Char8T<> {};
#endif

template <typename Type> using Decay = typename impl::Decay<Type>::Type;
template <typename... Types> using Common = typename impl::Common<Types...>::Type;

template <typename T> using TypeId = typename impl::TypeId<T>::Type;

template <typename T> using UnderlyingType = typename impl::UnderlyingType<T>::Type;
template <typename T> struct IsEmpty : impl::IsEmpty<T>::Type {};
template <typename T> struct IsFinal : impl::IsFinal<T>::Type {};
} // namespace meta
} // namespace cds

#endif // CDS_META_TYPE_TRAITS_HPP
