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
template <typename T, typename = void> struct IsReferenceable : False {};
template <typename T> struct IsReferenceable<T, Void<T&>> : True {};

template <typename> struct IsVoid : False {};
template <> struct IsVoid<void> : True {};

template <typename T> struct IsEnum : ConvertIntegral<std::is_enum<T>> {};
template <typename T> struct IsUnion : ConvertIntegral<std::is_union<T>> {};
template <typename T> struct IsClass : ConvertIntegral<std::is_class<T>> {};
template <typename T> struct IsFunction : ConvertIntegral<std::is_function<T>> {};
template <typename T> struct IsFundamental : ConvertIntegral<std::is_fundamental<T>> {};
template <typename T> struct IsIntegral : ConvertIntegral<std::is_integral<T>> {};
template <typename T> struct IsFloating : ConvertIntegral<std::is_floating_point<T>> {};
template <typename T> struct IsArithmetic : ConvertIntegral<std::is_arithmetic<T>> {};

template <typename T, bool = IsArithmetic<T>::value> struct IsSigned : False {};
template <typename T> struct IsSigned<T, true> : Bool<T(-1) < T(0)> {};

template <typename> struct IsArray : False {};
template <typename T, Size s> struct IsArray<T[s]> : True {};
template <typename T> struct IsArray<T[]> : True {};

template <typename> struct IsBoundedArray : False {};
template <typename T, Size s> struct IsBoundedArray<T[s]> : True {};

template <typename> struct IsUnboundedArray : False {};
template <typename T> struct IsUnboundedArray<T[]> : True {};

template <typename> struct IsPointer : False {};
template <typename T> struct IsPointer<T*> : True {};

template <typename> struct IsLValRef : False {};
template <typename T> struct IsLValRef<T&> : True {};

template <typename> struct IsRValRef : False {};
template <typename T> struct IsRValRef<T&&> : True {};

template <typename T> struct IsRef : Or<IsLValRef<T>, IsRValRef<T>> {};

template <typename> struct IsConst : False {};
template <typename T> struct IsConst<T const> : True {};

template <typename> struct IsVolatile : False {};
template <typename T> struct IsVolatile<T volatile> : True {};

template <typename T> struct IsConstVolatile : And<IsConst<T>, IsVolatile<T>> {};

template <typename F, typename T, typename = typename Or<IsVoid<F>, IsFunction<T>, IsArray<T>>::Type> class IsConvertible : public IsVoid<T> {};
template <typename F, typename T> class IsConvertible<F, T, False> {
  template <typename T1> static auto convert(T1) -> void;
  template <typename F1, typename T1, typename = decltype(convert<T1>(value<F1>()))> static auto test(int) -> True;
  template <typename, typename> static auto test(...) -> False;

public:
  using Type = decltype(test<F, T>(0));
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

  template <typename T, typename V, bool _ = true> using CommonByConditional = decltype(_ ? value<T>() : value<V>());
  template <typename T, typename V> static auto firstTest(int) -> Success<typename Decay<CommonByConditional<T, V>>::Type>;
  template <typename T, typename V> static auto secondTest(int) -> Success<typename RemoveConst<typename RemoveVolatile<CommonByConditional<T const&, V const&>>::Type>::Type>;
  template <typename, typename> static auto secondTest(...) -> Failure;
  template <typename T, typename V> static auto firstTest(...) -> decltype(secondTest<T, V>(0));
};

template <typename T, typename V, typename DT = typename Decay<T>::Type, typename DV = typename Decay<V>::Type> struct CommonDecayed {
  using Type = Common<DT, DV>;
};

template <typename T, typename V> struct CommonDecayed<T, V, T, V> {
  using Type = decltype(CommonHelper::firstTest<T, V>(0));
};

template <typename, typename, typename = void> struct Fold {};
template <typename C, typename... R> struct Fold<C, Pack<R...>, Void<typename C::Type>> : Common<typename C::Type, R...> {};
template <typename C, typename R> struct Fold<C, R, void> {};

template <typename T, typename V> struct Common<T, V> : CommonDecayed<T, V>::Type {};
template <typename T, typename V, typename... R> struct Common<T, V, R...> : Fold<Common<T, V>, Pack<R...>> {};
} // namespace impl

template <typename Type> using RemoveConst = typename impl::RemoveConst<Type>::Type;
template <typename Type> using RemoveVolatile = typename impl::RemoveVolatile<Type>::Type;
template <typename Type> using RemoveConstVolatile = RemoveConst<RemoveVolatile<Type>>;
template <typename Type> using RemoveRef = typename impl::RemoveRef<Type>::Type;
template <typename Type> using RemoveCVRef = RemoveRef<RemoveConstVolatile<Type>>;
template <typename Type> using RemovePointer = typename impl::RemovePointer<Type, RemoveConstVolatile<Type>>::Type;
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

template <typename Type> using Decay = typename impl::Decay<Type>::Type;
template <typename... Types> using Common = typename impl::Common<Types...>::Type;
} // namespace meta
} // namespace cds

#endif // CDS_META_TYPE_TRAITS_HPP
