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

template <Size, typename...> struct TupleNode {};

template <Size idx> CDS_ATTR(2(nodiscard, constexpr(11))) auto operator==(
    CDS_ATTR(unused) TupleNode<idx> const& l,
    CDS_ATTR(unused) TupleNode<idx> const& r
) noexcept -> bool {
  return true;
}

template <Size nodeIndex, typename Current, typename... Remaining> struct TupleNode<nodeIndex, Current, Remaining...> :
    TupleNode<nodeIndex + 1U, Remaining...> {
  using Data = Current;
  using NextNode = TupleNode<nodeIndex + 1U, Remaining...>;

  CDS_ATTR(constexpr(11)) TupleNode() noexcept = default;

  template <typename CurrentArg, typename... RemainingArgs>
  CDS_ATTR(2(constexpr(11), explicit)) TupleNode(CurrentArg&& current, RemainingArgs&&... remaining) CDS_ATTR(noexcept(
      noexcept(NextNode(cds::forward<RemainingArgs>(remaining)...))
      && noexcept(Current(cds::forward<CurrentArg>(current)))
  )) :
      NextNode(cds::forward<RemainingArgs>(remaining)...),
      _nodeData(cds::forward<CurrentArg>(current)) {}

  template <Size otherNodeIdx, typename OtherCurrent, typename... OtherRemaining> CDS_ATTR(2(nodiscard, constexpr(11)))
  auto operator==(TupleNode<otherNodeIdx, OtherCurrent, OtherRemaining...> const& other) const noexcept
      -> ReturnIf<bool, And<
          Bool<otherNodeIdx == nodeIndex>,
          IsEqCompatible<Current, OtherCurrent>,
          Bool<sizeof...(Remaining) == sizeof...(OtherRemaining)>>
      > {
    return _nodeData == other._nodeData
        && static_cast<NextNode const&>(*this)
            == static_cast<typename TupleNode<otherNodeIdx, OtherCurrent, OtherRemaining...>::NextNode const&>(other);
  }

  Current _nodeData;
};

namespace tupleNodeTraits {
using meta::False;
using meta::True;

template <typename> struct IsTupleNode : False {};
template <Size index, typename... Types> struct IsTupleNode<TupleNode<index, Types...>> : True {};

template <Size, typename> struct NodeTypeInfo {};
template <Size reqIdx, Size curIdx, typename Cur, typename... Rem> struct NodeTypeInfo<reqIdx, TupleNode<curIdx, Cur, Rem...>> {
    using Current = TupleNode<curIdx, Cur, Rem...>;
    using Type = Conditional<
        Bool<reqIdx == curIdx>,
        Current,
        typename NodeTypeInfo<reqIdx, typename Current::NextNode>::Type
    >;
};


template <Size reqIdx, Size curIdx> struct NodeTypeInfo<reqIdx, TupleNode<curIdx>> {
    using Current = meta::Void<>;
    using Type = meta::Void<>;
};

template <Size idx, typename NType> using TargetNode = typename NodeTypeInfo<idx, RemoveCVRef<NType>>::Type;
template <Size idx, typename NType> using TargetData = typename TargetNode<idx, RemoveCVRef<NType>>::Data;
} // namespace tupleNodeTraits

using tupleNodeTraits::IsTupleNode;
using tupleNodeTraits::TargetData;
using tupleNodeTraits::TargetNode;

template <Size requestedIndex, typename Node, typename Target = TargetData<requestedIndex, RemoveCVRef<Node>>> using
    GetNodeReturn = AddLValRef<Conditional<IsConst<RemoveRef<Node>>, AddConst<Target>, Target>>;
template <Size requestedIndex, typename Node, typename Target = TargetNode<requestedIndex, RemoveCVRef<Node>>> using
    GetNodeRoot = AddLValRef<Conditional<IsConst<RemoveRef<Node>>, AddConst<Target>, Target>>;

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
auto tupleHash(TupleNode<idx> const& node) noexcept -> Size {
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
