//
// Created by loghin on 6/3/24.
//

#ifndef CDS_PRIMITIVE_TUPLE_NODE_HPP
#define CDS_PRIMITIVE_TUPLE_NODE_HPP
#pragma once

#include <cds/meta/Semantics>

namespace cds {
namespace impl {
using meta::EnableIf;
using meta::Conditional;
using meta::RemoveRef;
using meta::RemoveCVRef;
using meta::IsConst;
using meta::AddConst;
using meta::AddLValRef;
using meta::Bool;
using meta::And;
using meta::IsEqCompatible;
using meta::ReturnIf;
using meta::All;
using meta::IsNoexceptDefaultConstructible;

template <Size, typename...> struct TupleNode {};

template <Size idx> CDS_ATTR(2(nodiscard, constexpr(11))) auto operator==(
    CDS_ATTR(unused) TupleNode<idx> const& l,
    CDS_ATTR(unused) TupleNode<idx> const& r
) noexcept -> bool {
  return true;
}

template <Size idx, typename T, typename... R> struct TupleNode<idx, T, R...> : TupleNode<idx + 1u, R...> {
  using Data = T;
  using NextNode = TupleNode<idx + 1u, R...>;

  CDS_ATTR(constexpr(11)) TupleNode() CDS_ATTR(noexcept(All<IsNoexceptDefaultConstructible, T, R...>::value)) = default;

  template <typename Arg, typename... Args>
  CDS_ATTR(constexpr(11)) TupleNode(Arg&& param, Args&&... remaining) CDS_ATTR(noexcept(
      noexcept(NextNode(cds::forward<Args>(remaining)...))
      && noexcept(T(cds::forward<Arg>(param)))
  )) :
      NextNode(cds::forward<Args>(remaining)...),
      _nodeData(cds::forward<Arg>(param)) {}

  template <Size oIdx, typename OT, typename... OR> CDS_ATTR(2(nodiscard, constexpr(11)))
  auto operator==(TupleNode<oIdx, OT, OR...> const& other) const noexcept
      -> ReturnIf<bool, And<Bool<oIdx == idx>, IsEqCompatible<T, OT>, Bool<sizeof...(R) == sizeof...(OR)>>> {
    return _nodeData == other._nodeData
        && static_cast<NextNode const&>(*this)
            == static_cast<typename TupleNode<oIdx, OT, OR...>::NextNode const&>(other);
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
  return static_cast<TargetNode<requestedIndex, TupleNode<nodeIdx, Types...>>&&>(cds::move(node))._nodeData;
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
