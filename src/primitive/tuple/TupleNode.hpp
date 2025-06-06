//
// Created by loghin on 6/3/24.
//

#ifndef CDS_PRIMITIVE_TUPLE_NODE_HPP
#define CDS_PRIMITIVE_TUPLE_NODE_HPP
#pragma once

#include <cds/meta/Semantics>

#include "../../meta/Ignore.hpp"

namespace cds {
namespace impl {
using meta::EnableIf;
using meta::Conditional;
using meta::RemoveRef;
using meta::RemoveCVRef;
using meta::IsAssignable;
using meta::IsConstructible;
using meta::IsConst;
using meta::AddConst;
using meta::AddLValRef;
using meta::Bool;
using meta::And;
using meta::Not;
using meta::IsSame;
using meta::IsEqCompatible;
using meta::IsNoexceptConstructible;
using meta::ReturnIf;
using meta::All;
using meta::IsNoexceptDefaultConstructible;
using meta::lvalue;

template <Size idx, typename...> struct TupleNode {
  template <typename... Types> CDS_ATTR(constexpr(14))
  auto operator=(TupleNode<idx, Types...> const& node) noexcept -> TupleNode& {
    ignore = node;
    return *this;
  }

  template <typename... Types> CDS_ATTR(constexpr(14))
  auto operator=(TupleNode<idx, Types...>&& node) noexcept -> TupleNode& {
    ignore = node;
    return *this;
  }
};

template <Size idx> CDS_ATTR(2(nodiscard, constexpr(11))) auto operator==(
    CDS_ATTR(unused) TupleNode<idx> const& l,
    CDS_ATTR(unused) TupleNode<idx> const& r
) noexcept -> bool {
  return true;
}

template <Size idx, typename T, typename... R> struct TupleNode<idx, T, R...> : TupleNode<idx + 1u, R...> {
  using Data = T;
  using NextNode = TupleNode<idx + 1u, R...>;

  CDS_ATTR(2(nodiscard, constexpr(11))) auto upper() const noexcept -> NextNode const& {
    return *static_cast<NextNode const*>(this);
  }

  CDS_ATTR(constexpr(11)) TupleNode() CDS_ATTR(noexcept(All<IsNoexceptDefaultConstructible, T, R...>::value)) = default;

  template <typename Arg, typename... Args, typename = EnableIf<Bool<
      IsConstructible<T, Arg>::value && IsConstructible<NextNode, Args...>::value
  >>> CDS_ATTR(2(implicit, constexpr(11))) TupleNode(Arg&& param, Args&&... remaining) CDS_ATTR(noexcept(
      noexcept(NextNode(fwd<Args>(remaining)...))
      && noexcept(T(fwd<Arg>(param)))
  )) :
      NextNode(fwd<Args>(remaining)...),
      _nodeData(fwd<Arg>(param)) {}

  template <typename OT, typename... OR, typename = EnableIf<Not<IsSame<TupleNode, TupleNode<idx, OT, OR...>>>>>
  CDS_ATTR(2(explicit, constexpr(11))) TupleNode(
      TupleNode<idx, OT, OR...> const& other
  ) CDS_ATTR(noexcept(
      IsNoexceptConstructible<Data, OT const&>::value
      && IsNoexceptConstructible<NextNode, typename TupleNode<idx, OT, OR...>::NextNode const&>::value
  )) :
      NextNode{static_cast<typename TupleNode<idx, OT, OR...>::NextNode const&>(other)},
      _nodeData{other._nodeData} {}

  template <typename OT, typename... OR, typename = EnableIf<Not<IsSame<TupleNode, TupleNode<idx, OT, OR...>>>>>
  CDS_ATTR(2(explicit, constexpr(11))) TupleNode(
      TupleNode<idx, OT, OR...>&& other
  ) CDS_ATTR(noexcept(
      IsNoexceptConstructible<Data, OT&&>::value
      && IsNoexceptConstructible<NextNode, typename TupleNode<idx, OT, OR...>::NextNode&&>::value
  )) :
      NextNode{static_cast<typename TupleNode<idx, OT, OR...>::NextNode&&>(other)},
      _nodeData{mv(other._nodeData)} {}

  template <Size oIdx, typename OT, typename... OR> CDS_ATTR(2(nodiscard, constexpr(11)))
  auto operator==(TupleNode<oIdx, OT, OR...> const& other) const noexcept
      -> ReturnIf<bool, And<Bool<oIdx == idx>, IsEqCompatible<T, OT>, Bool<sizeof...(R) == sizeof...(OR)>>> {
    return _nodeData == other._nodeData
        && upper() == other.upper();
  }

  template <typename... UTypes> CDS_ATTR(constexpr(14))
  auto operator=(TupleNode<idx, UTypes...> const& node) CDS_ATTR(noexcept(
      noexcept(lvalue<T>() = node._nodeData)
      && noexcept(NextNode::operator=(static_cast<typename TupleNode<idx, UTypes...>::NextNode const&>(node)))
  )) -> TupleNode& {
    _nodeData = node._nodeData;
    return static_cast<TupleNode&>(NextNode::operator=(
        static_cast<typename TupleNode<idx, UTypes...>::NextNode const&>(node)));
  }

  template <
      typename... UTypes, typename = EnableIf<Bool<
          IsAssignable<TupleNode, TupleNode<idx, UTypes...>&&>::value &&
          IsAssignable<NextNode, typename TupleNode<idx, UTypes...>::NextNode&&>::value
      >>
  > CDS_ATTR(constexpr(14)) auto operator=(TupleNode<idx, UTypes...>&& node) CDS_ATTR(noexcept(
      noexcept(lvalue<T>() = mv(node._nodeData))
      && noexcept(NextNode::operator=(static_cast<typename TupleNode<idx, UTypes...>::NextNode&&>(node)))
  )) -> TupleNode& {
    _nodeData = node._nodeData;
    return static_cast<TupleNode&>(NextNode::operator=(
        static_cast<typename TupleNode<idx, UTypes...>::NextNode&&>(node)));
  }

  T _nodeData;
};

namespace tupleNodeTraits {
using meta::False;
using meta::True;

template <typename> struct IsTupleNode : False {};
template <Size idx, typename... Types> struct IsTupleNode<TupleNode<idx, Types...>> : True {};

template <Size, typename> struct NodeTypeInfo {};
template <Size reqIdx, Size idx, typename T, typename... R> struct NodeTypeInfo<reqIdx, TupleNode<idx, T, R...>> {
    using Current = TupleNode<idx, T, R...>;
    using Type = Conditional<
        Bool<reqIdx == idx>,
        Current,
        typename NodeTypeInfo<reqIdx, typename Current::NextNode>::Type
    >;
};


template <Size reqIdx, Size idx> struct NodeTypeInfo<reqIdx, TupleNode<idx>> {
    using Current = meta::Void<>;
    using Type = meta::Void<>;
};

template <Size idx, typename NType> using TargetNode = typename NodeTypeInfo<idx, RemoveCVRef<NType>>::Type;
template <Size idx, typename NType> using TargetData = typename TargetNode<idx, RemoveCVRef<NType>>::Data;
} // namespace tupleNodeTraits

using tupleNodeTraits::IsTupleNode;
using tupleNodeTraits::TargetData;
using tupleNodeTraits::TargetNode;

template <Size requestedIndex, Size nodeIdx, typename... Types> CDS_ATTR(2(nodiscard, constexpr(11))) auto tupleNodeGet(
    TupleNode<nodeIdx, Types...> const& node
) noexcept -> TargetData<requestedIndex, TupleNode<nodeIdx, Types...>> const& {
  return static_cast<TargetNode<requestedIndex, TupleNode<nodeIdx, Types...>> const&>(node)._nodeData;
}

template <Size requestedIndex, Size nodeIdx, typename... Types> CDS_ATTR(2(nodiscard, constexpr(11))) auto tupleNodeGet(
    TupleNode<nodeIdx, Types...>& node
) noexcept -> TargetData<requestedIndex, TupleNode<nodeIdx, Types...>>& {
  return static_cast<TargetNode<requestedIndex, TupleNode<nodeIdx, Types...>>&>(node)._nodeData;
}

template <Size requestedIndex, Size nodeIdx, typename... Types> CDS_ATTR(2(nodiscard, constexpr(11))) auto tupleNodeGet(
    TupleNode<nodeIdx, Types...>&& node
) noexcept -> TargetData<requestedIndex, TupleNode<nodeIdx, Types...>> {
  return static_cast<TargetNode<requestedIndex, TupleNode<nodeIdx, Types...>>&&>(mv(node))._nodeData;
}

template <Size idx> CDS_ATTR(2(nodiscard, constexpr(11)))
auto tupleHash(CDS_ATTR(unused) TupleNode<idx> const&) noexcept -> Size {
    return 0U;
}

template <Size idx, typename Current, typename... Types>
CDS_ATTR(2(nodiscard, constexpr(11))) auto tupleHash(TupleNode<idx, Current, Types...> const& node) noexcept -> Size {
  return cds::functional::Hash<>()(node._nodeData)
    + tupleHash(static_cast<TupleNode<idx + 1U, Types...> const&>(node)) * 31;
}
} // namespace impl
} // namespace cds

#endif // CDS_PRIMITIVE_TUPLE_NODE_HPP
