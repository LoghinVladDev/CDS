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


template <int i> using Int = Integral<int, i>;


template <bool v> using Bool = Integral<bool, v>;
using True = Bool<true>::Type;
using False = Bool<false>::Type;


template <typename I, typename, typename> struct Conditional { using Type = void; };
template <typename T, typename F> struct Conditional<True, T, F> { using Type = T; };
template <typename T, typename F> struct Conditional<False, T, F> { using Type = F; };


template <typename, typename = void> struct IsCdsIntegral : False {};
template <typename, typename = void> struct IsStdIntegral : False {};
template <typename T> struct IsCdsIntegral<T, Void<typename T::Type>> : True {};
template <typename T> struct IsStdIntegral<T, Void<typename T::type>> : True {};


template <typename T, typename = typename IsCdsIntegral<T>::Type, typename = typename IsStdIntegral<T>::Type> struct ConvertIntegral {};
template <typename T> struct ConvertIntegral<T, True, False> : T {};
template <typename T> struct ConvertIntegral<T, False, True> : Integral<typename T::value_type, T::value> {};


template <typename F, typename... R> struct And : Bool<F::value && And<R...>::value> {};
template <typename I> struct And<I>: Bool<I::value> {};

template <typename F, typename... R> struct Or : Bool<F::value || Or<R...>::value> {};
template <typename I> struct Or<I>: Bool<I::value> {};

template <typename L, typename R, typename... P> struct Eq : Bool<L::value == R::value && Eq<R, P...>::value> {};
template <typename L, typename R> struct Eq<L, R> : Bool<L::value == R::value> {};
template <typename L, typename R> struct Ne : Bool<L::value != R::value> {};
template <typename L, typename R> struct Gt : Bool<(L::value > R::value)> {};
template <typename L, typename R> struct Ge : Bool<(L::value >= R::value)> {};
template <typename L, typename R> struct Lt : Bool<(L::value < R::value)> {};
template <typename L, typename R> struct Le : Bool<(L::value <= R::value)> {};


template <typename I, typename = void> struct EnableIf {};
template <typename R> struct EnableIf<True, R> {
  using Type = R;
};


template <typename, typename> struct IsSame : False {};
template <typename T> struct IsSame<T, T> : True {};


template <template <typename...> class Formula, typename... Params> struct BindLeft {
  template <typename... TParams> using Type = typename Formula <Params..., TParams...>::Type;
};

template <template <typename...> class Formula, typename... Params> struct BindRight {
  template <typename... TParams> using Type = Formula <TParams..., Params...>;
};

template <int> struct Ph {};
template <typename> struct IsPh : False {};
template <int i> struct IsPh<Ph<i>> : True {};

template <typename> struct GetPh : Int<0> {};
template <int i> struct GetPh<Ph<i>> : Int<i> {};

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
      typename Eq<Int<i>, Int<1>>::Type,
      F,
      typename PackPeek<
          i - 1,
          Pack<R...>
      >::Result
  >::Type;
};

template <int i> struct PackPeek<i, Pack<>> {
  using Type = Pack<>;
  using Result = void;
};

template <typename, typename> struct BoundPackPop {};
template <typename PhT, typename F, typename... R> struct BoundPackPop <PhT, Pack<F, R...>> : Conditional<
    typename Eq<GetPh<PhT>, Int<0>>::Type,
    PackPop<Pack<F, R...>>,
    PackPeek<GetPh<PhT>::value, Pack<F, R...>>
>::Type {};

template <template <typename...> class Formula, typename Pack, typename ParamPack>
struct BindApply {
private:
  using NextPack = typename PackPop<Pack>::Type;
  using Current = typename PackPop<Pack>::Result;
  using IsPh = typename IsPh<Current>::Type;
  using NextParam = typename Conditional<
      IsPh,
      typename BoundPackPop<Current, ParamPack>::Result,
      Current
  >::Type;

public:
  template <typename... UnboundParams> using Type = typename Conditional<
      IsPh,
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
template <template <typename...> class Formula, typename... TParams> struct None: Bool<!Any<Formula, TParams...>::value> {};
}

template <typename Type, Type value> using Integral = typename impl::Integral<Type, value>::Type;

template <int value> using Int = impl::Int<value>;
template <bool value> using Bool = impl::Bool<value>;
using True = impl::True;
using False = impl::False;

template <typename Integral, typename IfTrue, typename IfFalse> using Conditional =
    typename impl::Conditional<typename impl::ConvertIntegral<Integral>::Type, IfTrue, IfFalse>::Type;

template <typename Left, typename Right> struct IsSame : impl::IsSame<Left, Right>::Type {};

template <typename... Integrals> using And = typename impl::And<Integrals...>::Type;
template <typename... Integrals> using Or = typename impl::Or<Integrals...>::Type;
template <typename Integral> using Not = typename Bool<!Integral::value>::Type;
template <typename... Integrals> using Eq = typename impl::Eq<Integrals...>::Type;
template <typename LeftIntegral, typename RightIntegral> struct Ne : impl::Ne<LeftIntegral, RightIntegral>::Type {};
template <typename LeftIntegral, typename RightIntegral> struct Lt : impl::Lt<LeftIntegral, RightIntegral>::Type {};
template <typename LeftIntegral, typename RightIntegral> struct Le : impl::Le<LeftIntegral, RightIntegral>::Type {};
template <typename LeftIntegral, typename RightIntegral> struct Gt : impl::Gt<LeftIntegral, RightIntegral>::Type {};
template <typename LeftIntegral, typename RightIntegral> struct Ge : impl::Ge<LeftIntegral, RightIntegral>::Type {};

template <typename Integral, typename Replacement = int> using EnableIf =
    typename impl::EnableIf<typename impl::ConvertIntegral<Integral>::Type, Replacement>::Type;

template <typename Replacement, typename Integral> using ReturnIf = EnableIf<Integral, Replacement>;

template <template <typename...> class Formula, typename... TParams> struct Bind : impl::Bind<Formula, TParams...> {};
template <int index> using Ph = impl::Ph<index>;
template <template <typename...> class Formula, typename... TParams> struct BindLeft : impl::BindLeft<Formula, TParams...> {};
template <template <typename...> class Formula, typename... TParams> struct BindRight : impl::BindRight<Formula, TParams...> {};
template <template <typename...> class Formula, typename... TParams> using All = typename impl::All<Formula, TParams...>::Type;
template <template <typename...> class Formula, typename... TParams> using Any = typename impl::Any<Formula, TParams...>::Type;
template <template <typename...> class Formula, typename... TParams> using None = typename impl::None<Formula, TParams...>::Type;
}
}

#endif // CDS_META_BASE_HPP
