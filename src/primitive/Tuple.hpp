//
// Created by loghin on 6/3/24.
//

#ifndef CDS_PRIMITIVE_TUPLE_HPP
#define CDS_PRIMITIVE_TUPLE_HPP
#pragma once

#include <cds/functional/Hash>

#include "string/StringBaseDecl.hpp"
#include "tuple/TupleNode.hpp"

namespace cds {
template <typename... Types> class Tuple : private impl::TupleNode<0U, Types...> {
  template <typename, typename> friend struct functional::Hash;
  template <typename...> friend class Tuple;

public:
  using BaseNode = impl::TupleNode<0U, Types...>;
  using BaseNode::BaseNode;

  template <Size index> CDS_ATTR(2(nodiscard, constexpr(11))) auto get() const& noexcept
      -> decltype(impl::tupleNodeGet<index>(meta::lvalue<BaseNode const>())) {
    return impl::tupleNodeGet<index>(static_cast<BaseNode const&>(*this));
  }

  template <Size index> CDS_ATTR(2(nodiscard, constexpr(14))) auto get()& noexcept
      -> decltype(impl::tupleNodeGet<index>(meta::lvalue<BaseNode>())) {
    return impl::tupleNodeGet<index>(static_cast<BaseNode&>(*this));
  }

  template <Size index> CDS_ATTR(2(nodiscard, constexpr(14))) auto get()&& noexcept
      -> decltype(impl::tupleNodeGet<index>(meta::rvalue<BaseNode>())) {
    return impl::tupleNodeGet<index>(static_cast<BaseNode&&>(cds::move(*this)));
  }

  template <typename... OtherTypes>
  CDS_ATTR(2(nodiscard, constexpr(11))) auto operator==(Tuple<OtherTypes...> const& tuple) const noexcept -> bool {
    return static_cast<BaseNode const&>(*this) == static_cast<impl::TupleNode<0U, OtherTypes...> const&>(tuple);
  }

  template <typename... OtherTypes>
  CDS_ATTR(2(nodiscard, constexpr(11))) auto operator!=(Tuple<OtherTypes...> const& tuple) const noexcept -> bool {
    return !(static_cast<BaseNode const&>(*this) == static_cast<impl::TupleNode<0U, OtherTypes...> const&>(tuple));
  }

  template <typename C = char, typename U = impl::StringUtils<C, meta::StringTraits<C>>, typename A = Allocator<C>>
  CDS_ATTR(2(nodiscard, constexpr(20))) auto toString(A&& alloc = A()) const CDS_ATTR(noexcept(false)) ->
      impl::BaseString<C, U, A>;

  template <typename... UTypes> CDS_ATTR(constexpr(14))
  auto operator=(Tuple<UTypes...> const& tuple) CDS_ATTR(noexcept(noexcept(
      BaseNode::operator=(static_cast<typename Tuple<UTypes...>::BaseNode const&>(tuple))
  ))) -> Tuple& {
    return static_cast<Tuple&>(BaseNode::operator=(static_cast<typename Tuple<UTypes...>::BaseNode const&>(tuple)));
  }

  template <typename... UTypes> CDS_ATTR(constexpr(14))
  auto operator=(Tuple<UTypes...>&& tuple) CDS_ATTR(noexcept(noexcept(
      BaseNode::operator=(static_cast<typename Tuple<UTypes...>::BaseNode&&>(tuple))
  ))) -> Tuple& {
    return static_cast<Tuple&>(BaseNode::operator=(static_cast<typename Tuple<UTypes...>::BaseNode&&>(tuple)));
  }
};

namespace functional {
template <typename... Types> struct Hash<Tuple<Types...>, void> {
  CDS_ATTR(2(nodiscard, constexpr(11))) auto operator()(Tuple<Types...> const& tuple) const noexcept -> Size {
    using BaseType = cds::impl::TupleNode<0U, Types...>;
    return cds::impl::tupleHash(static_cast<BaseType const&>(tuple));
  }
};
} // namespace functional

namespace impl {
template <Size idx, typename... Types> CDS_ATTR(2(nodiscard, constexpr(11))) auto get(Tuple<Types...> const& tuple)
    noexcept -> decltype(tuple.template get<idx>()) {
  return tuple.template get<idx>();
}

template <Size idx, typename... Types> CDS_ATTR(2(nodiscard, constexpr(14))) auto get(Tuple<Types...>& tuple)
    noexcept -> decltype(tuple.template get<idx>()) {
  return tuple.template get<idx>();
}

template <Size idx, typename... Types> CDS_ATTR(2(nodiscard, constexpr(14))) auto get(Tuple<Types...>&& tuple)
    noexcept -> decltype(cds::move(tuple).template get<idx>()) {
  return cds::move(tuple).template get<idx>();
}

template <typename... Types> CDS_ATTR(2(nodiscard, constexpr(14))) auto tie(Types&... args) noexcept
    -> Tuple<Types&...> {
  return Tuple<Types&...>(args...);
}

template <typename... Types> CDS_ATTR(2(nodiscard, constexpr(14))) auto forwardAsTuple(Types&&... args) noexcept
    -> Tuple<Types&&...> {
  return Tuple<Types&&...>{fwd<Types>(args)...};
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
} // namespace impl

template <typename... Types> CDS_ATTR(2(nodiscard, constexpr(11))) auto makeTuple(Types&&... values)
    CDS_ATTR(noexcept(noexcept(impl::inlayHints::Tuple<Types...>(cds::forward<Types>(values)...))))
    -> impl::inlayHints::Tuple<Types...> {
  return impl::inlayHints::Tuple<Types...>{cds::forward<Types>(values)...};
}

template <> class Tuple<> {
public:
  template <typename... Types> CDS_ATTR(2(nodiscard, constexpr(11))) static auto of(Types&&... values)
      CDS_ATTR(noexcept(noexcept(impl::inlayHints::Tuple<Types...>(cds::forward<Types>(values)...))))
      -> impl::inlayHints::Tuple<Types...> {
    return impl::inlayHints::Tuple<Types...>{cds::forward<Types>(values)...};
  }
};

using impl::get;
using impl::tie;
using impl::forwardAsTuple;

#if CDS_ATTR(ctad)
template <typename... Ts> Tuple(Ts...) -> Tuple<Ts...>;
#endif // #if CDS_ATTR(ctad)
} // namespace cds

namespace std {
template <typename... Types> struct tuple_size<cds::Tuple<Types...>> :
    cds::meta::Integral<std::size_t, sizeof...(Types)> {};

template <std::size_t idx, typename... Types> struct tuple_element<idx, cds::Tuple<Types...>> {
  using type = typename cds::impl::TargetNode<idx, cds::impl::TupleNode<0U, Types...>>::Data;
};
} // namespace std

#include "../common/TupleString.hpp"
#include "../format/TupleFormatter.hpp"

#endif // CDS_PRIMITIVE_TUPLE_HPP
