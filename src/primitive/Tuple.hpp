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

template <typename... Types> using DecayedTuple = typename decayedTuple::DecayedTuple<Types...>::Type;
} // namespace impl

template <typename... Types> CDS_ATTR(2(nodiscard, constexpr(11))) auto makeTuple(Types&&... values)
    CDS_ATTR(noexcept(noexcept(impl::DecayedTuple<Types...>(cds::forward<Types>(values)...))))
    -> impl::DecayedTuple<Types...> {
  return impl::DecayedTuple<Types...>{cds::forward<Types>(values)...};
}
} // namespace cds

namespace std {
template <typename... Types> struct tuple_size<cds::Tuple<Types...>> :
    cds::meta::Integral<std::size_t, sizeof...(Types)> {};

template <std::size_t idx, typename... Types> struct tuple_element<idx, cds::Tuple<Types...>> {
  using type = typename cds::impl::TargetNode<idx, cds::impl::TupleNode<0U, Types...>>::Data;
};
} // namespace std

#include "../common/TupleString.hpp"

#endif // CDS_PRIMITIVE_TUPLE_HPP
