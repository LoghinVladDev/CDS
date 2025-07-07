//
// Created by loghin on 6/3/24.
//

#ifndef CDS_PRIMITIVE_TUPLE_HPP
#define CDS_PRIMITIVE_TUPLE_HPP
#pragma once

#include <cds/functional/Hash>

#include "../common/SpecialMemberFunctionHelper.hpp"
#include "../stdlib/ostream.hpp"
#include "tuple/ForwardTupleNode.hpp"

namespace cds {
namespace impl {
using meta::And;
using meta::All;
using meta::DoesNotHide;
using meta::EnableIf;
using meta::IsConstructible;
using meta::IsCopyConstructible;
using meta::IsMoveConstructible;
using meta::IsCopyAssignable;
using meta::IsMoveAssignable;
using meta::IsNoexceptConstructible;
using meta::IsNoexceptAssignable;
using meta::IsSame;
using meta::True;
using meta::False;
using meta::RemoveRef;
using meta::impl::Pack;
using meta::impl::SfinaeCtorBase;
using meta::impl::SfinaeAssignBase;

template <typename... Types> class Tuple;

struct TupleAccess {
  template <typename... Types> CDS_ATTR(2(nodiscard, constexpr(11)))
  auto operator()(Tuple<Types...> const& tuple) const noexcept -> typename Tuple<Types...>::BaseNode const& {
    return tuple;
  }

  template <typename... Types> CDS_ATTR(2(nodiscard, constexpr(11)))
  auto operator()(Tuple<Types...>& tuple) const noexcept -> typename Tuple<Types...>::BaseNode& {
    return tuple;
  }

  template <typename... Types> CDS_ATTR(2(nodiscard, constexpr(11)))
  auto operator()(Tuple<Types...> const&& tuple) const noexcept -> typename Tuple<Types...>::BaseNode const&& {
    return mv(tuple);
  }

  template <typename... Types> CDS_ATTR(2(nodiscard, constexpr(11)))
  auto operator()(Tuple<Types...>&& tuple) const noexcept -> typename Tuple<Types...>::BaseNode&& {
    return mv(tuple);
  }
};

template <template <typename...> class, typename, typename> struct TupleAll;

template <template <typename...> class Pred, typename... Ts>
struct TupleAll<Pred, Pack<>, Pack<Ts...>> : False {};

template <template <typename...> class Pred, typename... Ts>
struct TupleAll<Pred, Pack<Ts...>, Pack<>> : False {};

template <template <typename...> class Pred, typename T0, typename T1>
struct TupleAll<Pred, Pack<T0>, Pack<T1>> : Pred<T0, T1> {};

template <template <typename...> class Pred, typename T0, typename... Ts0, typename T1, typename... Ts1>
struct TupleAll<Pred, Pack<T0, Ts0...>, Pack<T1, Ts1...>> :
    And<Pred<T0, T1>, TupleAll<Pred, Pack<Ts0...>, Pack<Ts1...>>> {};

template <typename... Types> class Tuple :
    private FwdTupleNode<0U, Types...>,
    public SfinaeCtorBase<All<IsCopyConstructible, Types...>, All<IsMoveConstructible, Types...>>,
    public SfinaeAssignBase<All<IsCopyAssignable, Types...>, All<IsMoveAssignable, Types...>> {

  friend struct TupleAccess;
  using BaseNode = FwdTupleNode<0U, Types...>;

  CDS_ATTR(2(nodiscard, constexpr(11))) auto base() const& noexcept -> BaseNode const& {
    return *this;
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto base()& noexcept -> BaseNode& {
    return *this;
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto base() const&& noexcept -> BaseNode const&& {
    return mv(*this);
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto base()&& noexcept -> BaseNode&& {
    return mv(*this);
  }

public:
  using BaseNode::BaseNode;
  using BaseNode::operator=;

  template <typename... Args> CDS_ATTR(2(implicit, constexpr(11))) Tuple(InPlace, Args&&... args)
      CDS_ATTR(noexcept(TupleAll<IsNoexceptConstructible, Pack<Types...>, Pack<Args&&...>>::value)) :
      BaseNode{InPlace{}, fwd<Args>(args)...} {}

  template <typename... Args, typename = EnableIf<And<
      DoesNotHide<Tuple, Args...>,
      TupleAll<IsConstructible, Pack<Types...>, Pack<Args&&...>>
  >>> CDS_ATTR(2(implicit, constexpr(11))) Tuple(Args&&... args)
      CDS_ATTR(noexcept(TupleAll<IsNoexceptConstructible, Pack<Types...>, Pack<Args&&...>>::value)) :
      BaseNode{InPlace{}, fwd<Args>(args)...} {}

  template <typename... OtherTypes, typename = EnableIf<Not<IsSame<Tuple, Tuple<OtherTypes...>>>>>
  CDS_ATTR(2(explicit, constexpr(11))) Tuple(Tuple<OtherTypes...> const& other)
      CDS_ATTR(noexcept(TupleAll<IsNoexceptConstructible, Pack<Types...>, Pack<OtherTypes const&...>>::value)) :
      BaseNode{TupleAccess{}(other)} {}

  template <typename... OtherTypes, typename = EnableIf<Not<IsSame<Tuple, Tuple<OtherTypes...>>>>>
  CDS_ATTR(2(explicit, constexpr(11))) Tuple(Tuple<OtherTypes...>&& other)
      CDS_ATTR(noexcept(TupleAll<IsNoexceptConstructible, Pack<Types...>, Pack<OtherTypes&&...>>::value)) :
      BaseNode{TupleAccess{}(mv(other))} {}

  template <typename... OtherTypes> CDS_ATTR(constexpr(14))
  auto operator=(Tuple<OtherTypes...> const& tuple)
      CDS_ATTR(noexcept(TupleAll<IsNoexceptAssignable, Pack<Types...>, Pack<OtherTypes const&...>>::value)) -> Tuple& {
    base() = TupleAccess{}(tuple);
    return *this;
  }

  template <typename... OtherTypes> CDS_ATTR(constexpr(14))
  auto operator=(Tuple<OtherTypes...>&& tuple)
      CDS_ATTR(noexcept(TupleAll<IsNoexceptAssignable, Pack<Types...>, Pack<OtherTypes&&...>>::value)) -> Tuple& {
    base() = TupleAccess{}(mv(tuple));
    return *this;
  }

  template <Size index> CDS_ATTR(2(nodiscard, constexpr(11))) auto get() const& noexcept
      -> RemoveRef<decltype(upcast<index>(base()).leaf()._data)> const& {
    return upcast<index>(base()).leaf()._data;
  }

  template <Size index> CDS_ATTR(2(nodiscard, constexpr(11))) auto get()& noexcept
      -> RemoveRef<decltype(upcast<index>(base()).leaf()._data)>& {
    return upcast<index>(base()).leaf()._data;
  }

  template <Size index> CDS_ATTR(2(nodiscard, constexpr(11))) auto get()&& noexcept
      -> RemoveRef<decltype(upcast<index>(base()).leaf()._data)>&& {
    return mv(upcast<index>(mv(base())).leaf()._data);
  }

  template <Size index> CDS_ATTR(2(nodiscard, constexpr(11))) auto get() const&& noexcept
      -> RemoveRef<decltype(upcast<index>(base()).leaf()._data)> const&& {
    return mv(upcast<index>(mv(base())).leaf()._data);
  }
};

template <typename... Ts0, typename... Ts1> CDS_ATTR(2(nodiscard, constexpr(11)))
auto operator==(Tuple<Ts0...> const& lhs, Tuple<Ts1...> const& rhs) noexcept -> bool {
  return TupleAccess{}(lhs) == TupleAccess{}(rhs);
}

template <typename... Ts0, typename... Ts1> CDS_ATTR(2(nodiscard, constexpr(11)))
auto operator!=(Tuple<Ts0...> const& lhs, Tuple<Ts1...> const& rhs) noexcept -> bool {
  return TupleAccess{}(lhs) != TupleAccess{}(rhs);
}

template <Size index, typename... Types> CDS_ATTR(2(nodiscard, constexpr(11))) auto get(Tuple<Types...> const& tuple)
    noexcept -> RemoveRef<decltype(upcast<index>(TupleAccess{}(tuple)).leaf()._data)> const& {
  return upcast<index>(TupleAccess{}(tuple)).leaf()._data;
}

template <Size index, typename... Types> CDS_ATTR(2(nodiscard, constexpr(11))) auto get(Tuple<Types...> const&& tuple)
    noexcept -> RemoveRef<decltype(upcast<index>(TupleAccess{}(mv(tuple))).leaf()._data)> const&& {
  return mv(upcast<index>(TupleAccess{}(mv(tuple))).leaf()._data);
}

template <Size index, typename... Types> CDS_ATTR(2(nodiscard, constexpr(14))) auto get(Tuple<Types...>& tuple)
    noexcept -> RemoveRef<decltype(upcast<index>(TupleAccess{}(tuple)).leaf()._data)>& {
  return upcast<index>(TupleAccess{}(tuple)).leaf()._data;
}

template <Size index, typename... Types> CDS_ATTR(2(nodiscard, constexpr(14))) auto get(Tuple<Types...>&& tuple)
    noexcept -> RemoveRef<decltype(upcast<index>(TupleAccess{}(mv(tuple))).leaf()._data)>&& {
  return mv(upcast<index>(TupleAccess{}(mv(tuple))).leaf()._data);
}

template <typename... Types> CDS_ATTR(2(nodiscard, constexpr(14))) auto tie(Types&... args) noexcept
    -> Tuple<Types&...> {
  return Tuple<Types&...>(InPlace{}, args...);
}

template <typename... Types> CDS_ATTR(2(nodiscard, constexpr(14))) auto forwardAsTuple(Types&&... args) noexcept
    -> Tuple<Types&&...> {
  return Tuple<Types&&...>{InPlace{}, fwd<Types>(args)...};
}

template <typename C, typename... Types> auto operator<<(std::basic_ostream<C>& out, Tuple<> const& tuple)
    noexcept -> std::basic_ostream<C>& {
  return out << "()";
}

template <typename C, typename... Types> auto operator<<(std::basic_ostream<C>& out, Tuple<Types...> const& tuple)
    noexcept -> std::basic_ostream<C>& {
  return out << "(" << TupleAccess{}(tuple) << ")";
}

namespace decayedTuple {
using meta::impl::Pack;
using meta::impl::PackPop;
using meta::Decay;
template <typename...> struct DecayedTuple {};
template <typename T, typename... R> struct DecayedTuple<T, R...> {
  using Current = T;
  using Type = Tuple<Decay<Current>, typename DecayedTuple<R>::Current...>;
};
} // namespace decayedTuple

namespace inlayHints {
template <typename... Types> using Tuple = typename decayedTuple::DecayedTuple<Types...>::Type;
} // namespace inlayHints

template <typename... Types> CDS_ATTR(2(nodiscard, constexpr(11))) auto tupleOf(Types&&... values)
    CDS_ATTR(noexcept(noexcept(inlayHints::Tuple<Types...>(fwd<Types>(values)...))))
    -> inlayHints::Tuple<Types...> {
  return inlayHints::Tuple<Types...>{InPlace{}, fwd<Types>(values)...};
}

template <> class Tuple<> {
public:
  template <typename... Types> CDS_ATTR(2(nodiscard, constexpr(11))) static auto of(Types&&... values)
      CDS_ATTR(noexcept(noexcept(inlayHints::Tuple<Types...>(fwd<Types>(values)...))))
      -> inlayHints::Tuple<Types...> {
    return inlayHints::Tuple<Types...>{InPlace{}, fwd<Types>(values)...};
  }

  Tuple() = default;
  Tuple(Tuple const&) = default;
  Tuple(Tuple&&) = default;
  ~Tuple() = default;
  auto operator=(Tuple const&) -> Tuple& = default;
  auto operator=(Tuple&&) -> Tuple& = default;

  CDS_ATTR(constexpr(11)) Tuple(InPlace) noexcept {}
};

#if CDS_ATTR(ctad)
template <typename... Ts> Tuple(Ts...) -> Tuple<Ts...>;
#endif // #if CDS_ATTR(ctad)
} // namespace impl

using impl::Tuple;

using impl::get;
using impl::tie;
using impl::forwardAsTuple;
using impl::tupleOf;

namespace functional {
template <typename... Types> struct Hash<Tuple<Types...>, void> : Hash<cds::impl::FwdTupleNode<0, Types...>> {
  CDS_ATTR(2(nodiscard, constexpr(11))) auto operator()(Tuple<Types...> const& tuple) const noexcept
      -> Size {
    return Hash<cds::impl::FwdTupleNode<0, Types...>>::operator()(cds::impl::TupleAccess{}(tuple));
  }
};
} // namespace functional
} // namespace cds

namespace std {
template <typename... Types> struct tuple_size<cds::Tuple<Types...>> :
    cds::meta::Integral<std::size_t, sizeof...(Types)> {};

template <std::size_t idx, typename... Types> struct tuple_element<idx, cds::Tuple<Types...>> {
  using type = typename cds::impl::TupleNodeUpCaster<idx, cds::impl::FwdTupleNode<0U, Types...>>::Type::Leaf::Type;
};
} // namespace std

#include "../format/TupleFormatter.hpp"

#endif // CDS_PRIMITIVE_TUPLE_HPP
