//
// Created by loghin on 12/5/23.
//

#ifndef CDS_META_TYPE_TRAITS_HPP
#define CDS_META_TYPE_TRAITS_HPP
#pragma once

#include "Base.hpp"
#include <type_traits>

namespace cds {
namespace meta {
namespace impl {
template <typename T, typename = void> struct IsReferenceable : ::cds::meta::False {};
template <typename T> struct IsReferenceable<T, Void<T&>> : ::cds::meta::True {};

template <typename> struct IsVoid : ::cds::meta::False {};
template <> struct IsVoid<void> : ::cds::meta::True {};

template <typename T> struct IsEnum : ::cds::meta::impl::ConvertIntegral<std::is_enum<T>> {};
template <typename T> struct IsUnion : ::cds::meta::impl::ConvertIntegral<std::is_union<T>> {};
template <typename T> struct IsClass : ::cds::meta::impl::ConvertIntegral<std::is_class<T>> {};
template <typename T> struct IsFundamental : ::cds::meta::impl::ConvertIntegral<std::is_fundamental<T>> {};
template <typename T> struct IsIntegral : ::cds::meta::impl::ConvertIntegral<std::is_integral<T>> {};
template <typename T> struct IsFloating : ::cds::meta::impl::ConvertIntegral<std::is_floating_point<T>> {};
template <typename T> struct IsArithmetic : ::cds::meta::impl::ConvertIntegral<std::is_arithmetic<T>> {};

template <typename T, bool = IsArithmetic<T>::value> struct IsSigned : ::cds::meta::False {};
template <typename T> struct IsSigned<T, true> : ::cds::meta::Bool<T(-1) < T(0)> {};

template <typename> struct IsArray : ::cds::meta::False {};
template <typename T, Size s> struct IsArray<T[s]> : ::cds::meta::True {};
template <typename T> struct IsArray<T[]> : ::cds::meta::True {};

template <typename> struct IsBoundedArray : False {};
template <typename T, Size s> struct IsBoundedArray<T[s]> : ::cds::meta::True {};

template <typename> struct IsUnboundedArray : ::cds::meta::False {};
template <typename T> struct IsUnboundedArray<T[]> : ::cds::meta::True {};

template <typename> struct IsPointer : ::cds::meta::False {};
template <typename T> struct IsPointer<T*> : ::cds::meta::True {};

template <typename> struct IsLValRef : ::cds::meta::False {};
template <typename T> struct IsLValRef<T&> : ::cds::meta::True {};

template <typename> struct IsRValRef : ::cds::meta::False {};
template <typename T> struct IsRValRef<T&&> : ::cds::meta::True {};

template <typename T> struct IsRef : ::cds::meta::Or<IsLValRef<T>, IsRValRef<T>> {};

template <typename> struct IsConst : ::cds::meta::False {};
template <typename T> struct IsConst<T const> : ::cds::meta::True {};

template <typename> struct IsVolatile : ::cds::meta::False {};
template <typename T> struct IsVolatile<T volatile> : ::cds::meta::True {};

template <typename T> struct IsConstVolatile : ::cds::meta::And<IsConst<T>, IsVolatile<T>> {};

template <typename T> struct IsFunction :
    ::cds::meta::And<::cds::meta::Not<IsConst<T const>>, ::cds::meta::Not<IsRef<T>>>::Type {};

template <typename F, typename T, typename = typename ::cds::meta::Or<IsVoid<F>, IsFunction<T>, IsArray<T>>::Type>
class IsConvertible : public IsVoid<T> {};

template <typename F, typename T> class IsConvertible<F, T, ::cds::meta::False> {
  template <typename T1> static auto convert(T1) noexcept -> void;
  template <typename F1, typename T1, typename = decltype(IsConvertible::convert<T1>(::cds::meta::rvalue<F1>()))>
  static auto test(int) noexcept -> ::cds::meta::True;
  template <typename, typename> static auto test(...) noexcept -> ::cds::meta::False;

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

template <typename... Ts> struct Common {};
template <> struct Common<> {};
template <typename T> struct Common<T> : Common<T, T> {};

struct CommonHelper {
  template <typename T> struct Success { using Type = T; };
  struct Failure {};

  template <typename T, typename V, bool _ = true> using CommonByConditional
      = decltype(_ ? ::cds::meta::rvalue<T>() : ::cds::meta::rvalue<V>());

  template <typename T, typename V> static auto firstTest(int) noexcept
      -> CommonHelper::Success<typename Decay<CommonHelper::CommonByConditional<T, V>>::Type>;

  template <typename T, typename V>
  static auto secondTest(int) noexcept -> CommonHelper::Success<typename RemoveConst<typename RemoveVolatile<
      CommonHelper::CommonByConditional<T const&, V const&>
  >::Type>::Type>;

  template <typename, typename> static auto secondTest(...) noexcept -> CommonHelper::Failure;
  template <typename T, typename V> static auto firstTest(...) noexcept -> decltype(CommonHelper::secondTest<T, V>(0));
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
} // namespace impl

template <typename Type> using RemoveConst = typename ::cds::meta::impl::RemoveConst<Type>::Type;
template <typename Type> using RemoveVolatile = typename ::cds::meta::impl::RemoveVolatile<Type>::Type;
template <typename Type> using RemoveConstVolatile = ::cds::meta::RemoveConst<RemoveVolatile<Type>>;
template <typename Type> using RemoveRef = typename ::cds::meta::impl::RemoveRef<Type>::Type;
template <typename Type> using RemoveCVRef = ::cds::meta::RemoveRef<RemoveConstVolatile<Type>>;
template <typename Type> using RemovePointer
    = typename ::cds::meta::impl::RemovePointer<Type, RemoveConstVolatile<Type>>::Type;

template <typename Type> using RemoveExtent = typename ::cds::meta::impl::RemoveExtent<Type>::Type;
template <typename Type> using RemoveAllExtents = typename ::cds::meta::impl::RemoveAllExtents<Type>::Type;

template <typename Type> using AddPointer = typename ::cds::meta::impl::AddPointer<Type>::Type;
template <typename Type> using AddConst = typename ::cds::meta::impl::AddConst<Type>::Type;
template <typename Type> using AddVolatile = typename ::cds::meta::impl::AddVolatile<Type>::Type;
template <typename Type> using AddConstVolatile = ::cds::meta::AddConst<AddVolatile<Type>>;
template <typename Type> using AddLValRef = typename ::cds::meta::impl::AddLValRef<Type>::Type;
template <typename Type> using AddRValRef = typename ::cds::meta::impl::AddRValRef<Type>::Type;

template <typename Type> struct IsReferenceable : ::cds::meta::impl::IsReferenceable<Type>::Type {};
template <typename Type> struct IsVoid : ::cds::meta::impl::IsVoid<RemoveConstVolatile<Type>>::Type {};

template <typename Type> struct IsEnum : ::cds::meta::impl::IsEnum<Type>::Type {};
template <typename Type> struct IsUnion : ::cds::meta::impl::IsUnion<Type>::Type {};
template <typename Type> struct IsClass : ::cds::meta::impl::IsClass<Type>::Type {};
template <typename Type> struct IsFunction : ::cds::meta::impl::IsFunction<Type>::Type {};
template <typename Type> struct IsFundamental : ::cds::meta::impl::IsFundamental<Type>::Type {};
template <typename Type> struct IsIntegral : ::cds::meta::impl::IsIntegral<Type>::Type {};
template <typename Type> struct IsFloating : ::cds::meta::impl::IsFloating<Type>::Type {};
template <typename Type> struct IsArithmetic : ::cds::meta::impl::IsArithmetic<Type>::Type {};
template <typename Type> struct IsSigned : ::cds::meta::impl::IsSigned<Type>::Type {};

template <typename Type> struct IsArray : ::cds::meta::impl::IsArray<Type>::Type {};
template <typename Type> struct IsBoundedArray : ::cds::meta::impl::IsBoundedArray<Type>::Type {};
template <typename Type> struct IsUnboundedArray : ::cds::meta::impl::IsUnboundedArray<Type>::Type {};
template <typename Type> struct IsPointer : ::cds::meta::impl::IsPointer<Type>::Type {};
template <typename Type> struct IsLValRef : ::cds::meta::impl::IsLValRef<Type>::Type {};
template <typename Type> struct IsRValRef : ::cds::meta::impl::IsRValRef<Type>::Type {};
template <typename Type> struct IsRef : ::cds::meta::impl::IsRef<Type>::Type {};
template <typename Type> struct IsConst : ::cds::meta::impl::IsConst<Type>::Type {};
template <typename Type> struct IsVolatile : ::cds::meta::impl::IsVolatile<Type>::Type {};
template <typename Type> struct IsConstVolatile : ::cds::meta::impl::IsConstVolatile<Type>::Type {};

template <typename From, typename To> struct IsConvertible : ::cds::meta::impl::IsConvertible<From, To>::Type {};

template <typename Type> struct TypeInfo {
  constexpr static char const* name = "unknown";
};

template <template <typename...> class Type> struct TemplateTypeInfo {
  constexpr static char const* name = "unknown";
};

template <> struct TypeInfo<void> { constexpr static char const* name = "void"; };
template <> struct TypeInfo<bool> { constexpr static char const* name = "bool"; };
template <> struct TypeInfo<signed char> { constexpr static char const* name = "signed char"; };
template <> struct TypeInfo<signed short> { constexpr static char const* name = "signed short"; };
template <> struct TypeInfo<signed int> { constexpr static char const* name = "signed int"; };
template <> struct TypeInfo<signed long> { constexpr static char const* name = "signed long"; };
template <> struct TypeInfo<unsigned char> { constexpr static char const* name = "unsigned char"; };
template <> struct TypeInfo<unsigned short> { constexpr static char const* name = "unsigned short"; };
template <> struct TypeInfo<unsigned int> { constexpr static char const* name = "unsigned int"; };
template <> struct TypeInfo<unsigned long> { constexpr static char const* name = "unsigned long"; };
template <> struct TypeInfo<float> { constexpr static char const* name = "float"; };
template <> struct TypeInfo<double> { constexpr static char const* name = "double"; };

template <typename Type> using Decay = typename ::cds::meta::impl::Decay<Type>::Type;
template <typename... Types> using Common = typename ::cds::meta::impl::Common<Types...>::Type;
} // namespace meta
} // namespace cds

#endif // CDS_META_TYPE_TRAITS_HPP
