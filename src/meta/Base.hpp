//
// Created by loghin on 11/29/23.
//

#ifndef CDS_META_BASE_HPP
#define CDS_META_BASE_HPP

#include "Compiler.hpp"
#include <type_traits>

namespace cds {
namespace meta {
template <typename...> using Void = void;

template <typename T> auto value() -> T;
template <typename T> auto reference() -> T&;
template <typename T> auto address() -> T*;

namespace impl {
template <typename T, T v> struct Integral {
  static constexpr T value = v;
  using ValueType = T;
  using Type = Integral;
};


template <bool v> using Bool = Integral<bool, v>;
using True = Bool<true>::Type;
using False = Bool<false>::Type;


template <bool, typename, typename> struct Conditional { using Type = void; };
template <typename T, typename F> struct Conditional<true, T, F> { using Type = T; };
template <typename T, typename F> struct Conditional<false, T, F> { using Type = F; };


template <typename, typename = void> struct IsCdsIntegral : False {};
template <typename, typename = void> struct IsStdIntegral : False {};
template <typename T> struct IsCdsIntegral<T, Void<typename T::Type>> : True {};
template <typename T> struct IsStdIntegral<T, Void<typename T::type>> : True {};


template <typename T, typename = typename IsCdsIntegral<T>::Type, typename = typename IsStdIntegral<T>::Type> struct ConvertIntegral {
  using ValueType = void;
  using Type = void;
};

template <typename T> struct ConvertIntegral<T, True, False> : T {};
template <typename T> struct ConvertIntegral<T, False, True> : Integral<typename T::value_type, T::value> {};


template <typename F, typename... R> struct And : Bool<F::value && And<R...>::value> {};
template <typename I> struct And<I>: Bool<I::value> {};

template <typename F, typename... R> struct Or : Bool<F::value || Or<R...>::value> {};
template <typename I> struct Or<I>: Bool<I::value> {};


template <bool, typename = void> struct EnableIf {};
template <typename R> struct EnableIf<true, R> {
  using Type = R;
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

template <typename T> struct IsTriviallyCopyable : ConvertIntegral<std::is_trivially_copyable<T>> {};
template <typename T, typename... A> struct IsTriviallyConstructible : ConvertIntegral<std::is_trivially_constructible<T, A...>> {};
template <typename T, typename A> struct IsTriviallyAssignable : ConvertIntegral<std::is_trivially_assignable<T, A>> {};
template <typename T> struct IsTriviallyDestructible : ConvertIntegral<std::is_trivially_destructible<T>> {};
template <typename T> struct IsTriviallyDefaultConstructible : ConvertIntegral<std::is_trivially_default_constructible<T>> {};
template <typename T> struct IsTriviallyCopyConstructible : ConvertIntegral<std::is_trivially_copy_constructible<T>> {};
template <typename T> struct IsTriviallyMoveConstructible : ConvertIntegral<std::is_trivially_move_constructible<T>> {};
template <typename T> struct IsTriviallyCopyAssignable : ConvertIntegral<std::is_trivially_copy_assignable<T>> {};
template <typename T> struct IsTriviallyMoveAssignable : ConvertIntegral<std::is_trivially_move_assignable<T>> {};

template <typename T> struct IsDefaultConstructible : ConvertIntegral<std::is_default_constructible<T>> {};
template <typename T> struct IsCopyConstructible : ConvertIntegral<std::is_copy_constructible<T>> {};
template <typename T> struct IsMoveConstructible : ConvertIntegral<std::is_move_constructible<T>> {};
template <typename T> struct IsCopyAssignable : ConvertIntegral<std::is_copy_assignable<T>> {};
template <typename T> struct IsMoveAssignable : ConvertIntegral<std::is_move_assignable<T>> {};

template <typename, typename = void> struct IsObjectFunction : False {};
template <typename T> struct IsObjectFunction<T, Void<decltype(&T::operator())>> : True {};

template <typename, typename = void> struct IsStaticFunction : False {};
template <typename T> struct IsStaticFunction<T> : And<IsFunction<T>, Bool<!IsObjectFunction<T>::value>> {};

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


template <typename F, typename T, typename = Or<IsVoid<F>, IsFunction<T>, IsArray<T>>> class IsConvertible : public IsVoid<T> {};
template <typename F, typename T> class IsConvertible<F, T, False> {
  template <typename T1> static auto convert(T1) -> void;
  template <typename F1, typename T1, typename = decltype(convert<T1>(value<F1>()))> static auto test(int) -> True;
  template <typename, typename> static auto test(...) -> False;

public:
  using Type = decltype(test<F, T>(0));
};


template <typename, typename> struct IsSame : False {};
template <typename T> struct IsSame<T, T> : True {};


template <typename T> struct AddPointer { using Type = typename RemoveRef<T>::Type; };
template <typename T> struct AddConst { using Type = T const; };
template <typename T> struct AddVolatile { using Type = T volatile; };
template <typename T, typename = IsReferenceable<T>> struct AddLValRef { using Type = T; };
template <typename T> struct AddLValRef<T, True> { using Type = T&; };
template <typename T, typename = IsReferenceable<T>> struct AddRValRef { using Type = T; };
template <typename T> struct AddRValRef<T, True> { using Type = T&&; };


template <template <typename...> class Formula, typename... Params> struct BindLeft {
  template <typename... TParams> using Type = Formula <Params..., TParams...>;
};

template <template <typename...> class Formula, typename... Params> struct BindRight {
  template <typename... TParams> using Type = Formula <TParams..., Params...>;
};

template <int> struct Ph {};
template <typename> struct IsPh : False {};
template <int i> struct IsPh<Ph<i>> : True {};

template <typename> struct GetPh {};
template <int i> struct GetPh<Ph<i>> { static constexpr int value = i; };

template <typename...> struct Pack {};
template <typename...> struct PackPop {};
template <typename F, typename... R> struct PackPop<Pack<F, R...>> {
  using Type = Pack<R...>;
  using Result = F;
};

template <> struct PackPop<Pack<>> {
  using Type = Pack<>;
  using Result = void;
};

template <int, typename...> struct PackPeek {};
template <int i, typename F, typename... R> struct PackPeek<i, Pack<F, R...>> {
  using Type = Pack <F, R...>;
  using Result = typename Conditional<
      i == 1,
      F,
      typename PackPeek<
          i - 1,
          Pack<R...>
      >::Result
  >::Type;
};

template <typename, typename> struct BoundPackPop {};
template <typename PhT, typename F, typename... R> struct BoundPackPop <PhT, Pack<F, R...>> : Conditional<
    GetPh<PhT>::value == 0,
    PackPop<Pack<F, R...>>,
    PackPeek<GetPh<PhT>::value, Pack<F, R...>>
>::Type {};

template <template <typename...> class Formula, typename Pack, typename ParamPack>
struct BindApply {
private:
  using NextPack = typename PackPop<Pack>::Type;
  using Current = typename PackPop<Pack>::Result;
  static constexpr bool ph = IsPh<Current>::value;
  using NextParam = typename Conditional<
      ph,
      typename BoundPackPop<Current, ParamPack>::Result,
      Current
  >::Type;

public:
  template <typename... UnboundParams> using Type = typename Conditional<
      ph,
      BindApply<
          Formula,
          NextPack,
          typename BoundPackPop<Current, ParamPack>::Type
      >,
      BindApply<
          Formula,
          NextPack,
          ParamPack
      >
  >::Type::template Type<UnboundParams..., NextParam>;
};

template <template <typename...> class Formula> struct BindApply<Formula, Pack<>, Pack<>> {
  template <typename... UnboundParams> using Type = Formula<UnboundParams...>;
};

template <template <typename...> class Formula, typename UnusedParamPack> struct BindApply<Formula, Pack<>, UnusedParamPack> {
  template <typename... UnboundParams> using Type = Formula<UnboundParams...>;
};

template <template <typename...> class Formula, typename UnusedPack> struct BindApply<Formula, UnusedPack, Pack<>> {
  template <typename...> using Type = void;
};

template <template <typename...> class Formula, typename... TParams> struct Bind {
  template <typename... Params> using Type = typename BindApply<Formula, Pack<TParams...>, Pack<Params...>>::template Type<>;
};

template <template <typename...> class, typename...> struct All {};
template <template <typename...> class Formula, typename F, typename... R> struct All<Formula, F, R...> : And<
    Formula<F>,
    All<Formula, R...>
> {};

template <template <typename...> class Formula, typename P> struct All<Formula, P> : Formula<P> {};

template <template <typename...> class, typename...> struct Any {};
template <template <typename...> class Formula, typename F, typename... R> struct Any<Formula, F, R...> : Or<
    Formula<F>,
    Any<Formula, R...>
> {};

template <template <typename...> class Formula, typename P> struct Any<Formula, P> : Formula<P> {};

template <template <typename...> class Formula, typename... TParams> struct None: Bool<All<Formula, TParams...>::value> {};
}

template <typename Type, Type value> using Integral = typename impl::Integral<Type, value>::Type;

template <bool value> using Bool = impl::Bool<value>;
using True = impl::True;
using False = impl::False;

template <bool condition, typename IfTrue, typename IfFalse> using Conditional = typename impl::Conditional<condition, IfTrue, IfFalse>::Type;

template <typename... Integrals> using And = typename impl::And<Integrals...>::Type;
template <typename... Integrals> using Or = typename impl::Or<Integrals...>::Type;
template <typename Integral> using Not = typename Bool<!Integral::value>::Type;

template <bool condition, typename Replacement> using EnableIf = typename impl::EnableIf<condition, Replacement>::Type;

template <typename Type> using RemoveConst = typename impl::RemoveConst<Type>::Type;
template <typename Type> using RemoveVolatile = typename impl::RemoveVolatile<Type>::Type;
template <typename Type> using RemoveConstVolatile = typename RemoveConst<RemoveVolatile<Type>>::Type;
template <typename Type> using RemoveRef = typename impl::RemoveRef<Type>::Type;
template <typename Type> using RemovePointer = typename impl::RemovePointer<Type, RemoveConstVolatile<Type>>::Type;
template <typename Type> using RemoveExtent = typename impl::RemoveExtent<Type>::Type;
template <typename Type> using RemoveAllExtents = typename impl::RemoveAllExtents<Type>::Type;

template <typename Type> using IsReferenceable = impl::IsReferenceable<Type>;
template <typename Type> using IsVoid = impl::IsVoid<RemoveConstVolatile<Type>>;

template <typename Type> using IsEnum = impl::IsEnum<Type>;
template <typename Type> using IsUnion = impl::IsUnion<Type>;
template <typename Type> using IsClass = impl::IsClass<Type>;
template <typename Type> using IsFunction = impl::IsFunction<Type>;
template <typename Type> using IsFundamental = impl::IsFundamental<Type>;
template <typename Type> using IsIntegral = impl::IsIntegral<Type>;
template <typename Type> using IsFloating = impl::IsFloating<Type>;
template <typename Type> using IsArithmetic = impl::IsArithmetic<Type>;
template <typename Type> using IsSigned = impl::IsSigned<Type>;

template <typename Type> using IsTriviallyCopyable = impl::IsTriviallyCopyable<Type>;
template <typename Type, typename... Arguments> using IsTriviallyConstructible = impl::IsTriviallyConstructible<Type, Arguments...>;
template <typename Type, typename Argument> using IsTriviallyAssignable = impl::IsTriviallyAssignable<Type, Argument>;
template <typename Type> using IsTriviallyDestructible = impl::IsTriviallyDestructible<Type>;
template <typename Type> using IsTriviallyDefaultConstructible = impl::IsTriviallyDefaultConstructible<Type>;
template <typename Type> using IsTriviallyCopyConstructible = impl::IsTriviallyCopyConstructible<Type>;
template <typename Type> using IsTriviallyMoveConstructible = impl::IsTriviallyMoveConstructible<Type>;
template <typename Type> using IsTriviallyCopyAssignable = impl::IsTriviallyCopyAssignable<Type>;
template <typename Type> using IsTriviallyMoveAssignable = impl::IsTriviallyMoveAssignable<Type>;
template <typename Type> using IsDefaultConstructible = impl::IsDefaultConstructible<Type>;
template <typename Type> using IsCopyConstructible = impl::IsCopyConstructible<Type>;
template <typename Type> using IsMoveConstructible = impl::IsMoveConstructible<Type>;
template <typename Type> using IsCopyAssignable = impl::IsCopyAssignable<Type>;
template <typename Type> using IsMoveAssignable = impl::IsMoveAssignable<Type>;

template <typename Type> using IsStaticFunction = impl::IsStaticFunction<Type>;
template <typename Type> using IsObjectFunction = impl::IsObjectFunction<Type>;

template <typename Type> using IsArray = impl::IsArray<Type>;
template <typename Type> using IsBoundedArray = impl::IsBoundedArray<Type>;
template <typename Type> using IsUnboundedArray = impl::IsUnboundedArray<Type>;
template <typename Type> using IsPointer = impl::IsPointer<Type>;
template <typename Type> using IsLValRef = impl::IsLValRef<Type>;
template <typename Type> using IsRValRef = impl::IsRValRef<Type>;
template <typename Type> using IsRef = impl::IsRef<Type>;
template <typename Type> using IsConst = impl::IsConst<Type>;
template <typename Type> using IsVolatile = impl::IsVolatile<Type>;
template <typename Type> using IsConstVolatile = impl::IsConstVolatile<Type>;

template <typename From, typename To> using IsConvertible = typename impl::IsConvertible<From, To>::Type;
template <typename Left, typename Right> using IsSame = typename impl::IsSame<Left, Right>::Type;

template <typename Type> using AddPointer = typename impl::AddPointer<Type>::Type;
template <typename Type> using AddConst = typename impl::AddConst<Type>::Type;
template <typename Type> using AddVolatile = typename impl::AddVolatile<Type>::Type;
template <typename Type> using AddConstVolatile = AddConst<AddVolatile<Type>>;
template <typename Type> using AddLValRef = typename impl::AddLValRef<Type>::Type;
template <typename Type> using AddRValRef = typename impl::AddRValRef<Type>::Type;

template <template <typename...> class Formula, typename... TParams> struct Bind : impl::Bind<Formula, TParams...> {};
template <template <typename...> class Formula, typename... TParams> struct BindLeft : impl::BindLeft<Formula, TParams...> {};
template <template <typename...> class Formula, typename... TParams> struct BindRight : impl::BindRight<Formula, TParams...> {};
template <template <typename...> class Formula, typename... TParams> struct All : impl::All<Formula, TParams...> {};
template <template <typename...> class Formula, typename... TParams> struct Any : impl::Any<Formula, TParams...> {};
template <template <typename...> class Formula, typename... TParams> struct None : impl::None<Formula, TParams...> {};
}
}

#endif // CDS_META_BASE_HPP
