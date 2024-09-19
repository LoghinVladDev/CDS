#ifndef CDS_PRIMITIVE_UNION_NODE_HPP
#define CDS_PRIMITIVE_UNION_NODE_HPP
#pragma once

#include <cds/exception/UnionTypeException>
#include "UnionNodeV2.hpp"

namespace cds {
namespace impl {
using meta::EnableIf;
using meta::IsDefaultConstructible;
using meta::IsNoexceptConstructible;
using meta::IsNoexceptDefaultConstructible;
using meta::False;
using meta::Not;
using meta::RemoveCVRef;
using meta::impl::Pack;
using meta::AddConst;
using meta::AddLValRef;
using meta::AddRValRef;
using meta::IsConst;
using meta::And;
using meta::Or;

template <Size, typename...> union UnionNode {
  template <typename...> using EmplaceNoexcept = True;

  template <typename T> CDS_ATTR(2(constexpr(14), explicit)) UnionNode(CDS_ATTR(unused) T&&) noexcept {
    CDS_ATTR(unlikely) unreachable();
  }

  CDS_ATTR(constexpr(14)) auto destruct(CDS_ATTR(unused) Size) const noexcept -> void {}
  CDS_ATTR(constexpr(14)) auto copyConstruct(CDS_ATTR(unused) Size, CDS_ATTR(unused) UnionNode const&)
      const noexcept -> void {
    CDS_ATTR(unlikely) unreachable();
  }

  CDS_ATTR(constexpr(14)) auto moveConstruct(CDS_ATTR(unused) Size, CDS_ATTR(unused) UnionNode&&) const noexcept
      -> void {
    CDS_ATTR(unlikely) unreachable();
  }

  CDS_ATTR(constexpr(14)) auto copyAssign(CDS_ATTR(unused) Size, CDS_ATTR(unused) UnionNode const&) const noexcept
      -> void {
    CDS_ATTR(unlikely) unreachable();
  }

  CDS_ATTR(constexpr(14)) auto moveAssign(CDS_ATTR(unused) Size, CDS_ATTR(unused) UnionNode&&) const noexcept
      -> void {
    CDS_ATTR(unlikely) unreachable();
  }

  template <typename> auto raise(CDS_ATTR(unused) Size) const noexcept -> void {
    CDS_ATTR(unlikely) unreachable();
  }

  template <typename RT, typename... A> auto emplace(CDS_ATTR(unused) A&&...) const noexcept -> RT& {
    CDS_ATTR(unlikely) unreachable();
  }
};

template <Size, typename...> union TrivialUnionNode {
  template <typename...> using EmplaceNoexcept = True;

  template <typename T> CDS_ATTR(2(constexpr(14), explicit)) TrivialUnionNode(CDS_ATTR(unused) T&&) noexcept {
    CDS_ATTR(unlikely) unreachable();
  }

  CDS_ATTR(constexpr(14)) auto copyConstruct(CDS_ATTR(unused) Size, CDS_ATTR(unused) TrivialUnionNode const&)
      const noexcept -> void {
    CDS_ATTR(unlikely) unreachable();
  }

  CDS_ATTR(constexpr(14)) auto moveConstruct(CDS_ATTR(unused) Size, CDS_ATTR(unused) TrivialUnionNode&&) const noexcept
      -> void {
    CDS_ATTR(unlikely) unreachable();
  }

  CDS_ATTR(constexpr(14)) auto copyAssign(CDS_ATTR(unused) Size, CDS_ATTR(unused) TrivialUnionNode const&)
      const noexcept -> void {
    CDS_ATTR(unlikely) unreachable();
  }

  CDS_ATTR(constexpr(14)) auto moveAssign(CDS_ATTR(unused) Size, CDS_ATTR(unused) TrivialUnionNode&&) const noexcept
      -> void {
    CDS_ATTR(unlikely) unreachable();
  }

  template <typename> auto raise(CDS_ATTR(unused) Size) const noexcept -> void {
    CDS_ATTR(unlikely) unreachable();
  }

  template <typename RT, typename... A> auto emplace(CDS_ATTR(unused) A&&...) const noexcept -> RT& {
    CDS_ATTR(unlikely) unreachable();
  }
};

namespace unionBestMatch {
using meta::Conditional;
using meta::IsSame;
using meta::IsConstructible;
using meta::Any;
using meta::Integral;
using meta::impl::IsCdsIntegral;
using meta::True;
using meta::Common;
using meta::IsVoid;

template <typename, typename> struct Best {
  using Type = void;
};

template <typename T> struct Best<T, Pack<>> {
  using Type = void;
};

template <typename T, typename F> struct Best<T, Pack<F>> {
  using IsIdeal = typename IsSame<T, F>::Type;
  using IsMatching = typename IsConstructible<F, T>::Type;
  using MatchingOrVoid = Conditional<IsMatching, F, void>;
  using IdealOrMatching = Conditional<IsIdeal, F, MatchingOrVoid>;
  using Type = IdealOrMatching;
};

template <typename T, typename F, typename... A> struct Best<T, Pack<F, A...>> {
  using IsIdeal = typename IsSame<RemoveCVRef<T>, F>::Type;
  using IsMatching = typename IsConstructible<F, T>::Type;
  template <typename FF> struct TIsIdeal : IsSame<T, FF>::Type {};
  using AnyIdealAhead = typename Any<TIsIdeal, A...>::Type;
  using Next = Best<T, Pack<A...>>;
  using MatchingOrAnyAhead = Conditional<IsMatching, F, typename Next::Type>;
  using IdealAheadOrMatching = Conditional<AnyIdealAhead, typename Next::Type, MatchingOrAnyAhead>;
  using IdealOrIdealAhead = Conditional<IsIdeal, F, IdealAheadOrMatching>;
  using Type = IdealOrIdealAhead;
};

template <typename T, typename A, typename P> struct IsBest : IsSame<T, typename Best<A, P>::Type> {};

template <typename, typename...> struct IndexOf {};
template <typename T> struct IndexOf<T> {
  using Type = void;
};

template <typename T, typename F> struct IndexOf<T, F> {
  using Type = Conditional<IsSame<T, F>, Integral<Size, 0u>, void>;
};

template <typename T, typename F, typename N, typename = typename IsVoid<N>::Type> struct IndexOfSelection {
  using Type = Conditional<IsSame<T, F>, Integral<Size, 0u>, void>;
};

template <typename T, typename F, typename N> struct IndexOfSelection<T, F, N, False> {
  using Type = Conditional<IsSame<T, F>, Integral<Size, 0u>, Integral<Size, 1u + N::value>>;
};

template <typename T, typename F, typename... R> struct IndexOf<T, F, R...> {
  using Type = typename IndexOfSelection<T, F, typename IndexOf<T, R...>::Type>::Type;
};
} // namespace unionBestMatch

template <typename T, typename A, typename... Ts> struct IsUnionBestMatch :
    unionBestMatch::IsBest<RemoveCVRef<T>, A, Pack<RemoveCVRef<Ts>...>> {};

template <typename A, typename... Ts> struct UnionBestMatch :
    unionBestMatch::Best<A, Pack<RemoveCVRef<Ts>...>> {
  using Type = typename unionBestMatch::Best<A, Pack<RemoveCVRef<Ts>...>>::Type;
  using Noexcept = typename IsNoexceptConstructible<RemoveCVRef<Type>, A>::Type;
};

template <typename A, typename... Ts> struct IndexOfBestMatch {
  using Type = typename unionBestMatch::IndexOf<typename UnionBestMatch<A, Ts...>::Type, Ts...>::Type;
};

template <Size idx, typename T, typename... R> union UnionNode<idx, T, R...> {
  using Data = T;
  using NextNode = UnionNode<idx + 1u, R...>;

  template <typename... Args> using NextEmplaceNoexcept = typename NextNode::template EmplaceNoexcept<Args...>;
  template <typename... Args> using EmplaceNoexcept = IsNoexceptConstructible<Data, Args...>;

  template <typename TT = T, EnableIf<IsDefaultConstructible<TT>> = 0>
  CDS_ATTR(constexpr(11)) UnionNode() CDS_ATTR(noexcept(IsNoexceptDefaultConstructible<T>::value)) : _nodeData{} {}

  CDS_ATTR(constexpr(14)) UnionNode(Size cIdx, UnionNode const& node) CDS_ATTR(noexcept(
      noexcept(Data{node._nodeData})
      && noexcept(lvalue<UnionNode>().copyConstruct(cIdx, node))
  )) {
    copyConstruct(cIdx, node);
  }

  CDS_ATTR(constexpr(14)) UnionNode(Size cIdx, UnionNode&& node) CDS_ATTR(noexcept(
      noexcept(Data{cds::move(node._nodeData)})
      && noexcept(lvalue<UnionNode>().moveConstruct(cIdx, cds::move(node)))
  )) {
    moveConstruct(cIdx, cds::move(node));
  }

  template <typename Arg, EnableIf<IsUnionBestMatch<T, Arg, T, R...>> = 0>
  CDS_ATTR(2(constexpr(11), explicit)) UnionNode(Arg&& arg)
      CDS_ATTR(noexcept(UnionBestMatch<Arg, T, R...>::Noexcept::value)) :
      _nodeData(cds::forward<Arg>(arg)) {}

  template <typename Arg, EnableIf<Not<IsUnionBestMatch<T, Arg, T, R...>>> = 0>
  CDS_ATTR(2(constexpr(11), explicit)) UnionNode(Arg&& arg)
      CDS_ATTR(noexcept(UnionBestMatch<Arg, T, R...>::Noexcept::value)) :
      _nextNode{cds::forward<Arg>(arg)} {}

  template <typename Arg, EnableIf<IsUnionBestMatch<T, Arg, T, R...>> = 0>
  CDS_ATTR(constexpr(14)) auto set(Arg&& arg)
      CDS_ATTR(noexcept(UnionBestMatch<Arg, T, R...>::Noexcept::value)) -> void {
    _nodeData = cds::forward<Arg>(arg);
  }

  template <typename Arg, EnableIf<Not<IsUnionBestMatch<T, Arg, T, R...>>> = 0>
  CDS_ATTR(constexpr(14)) auto set(Arg&& arg)
      CDS_ATTR(noexcept(UnionBestMatch<Arg, T, R...>::Noexcept::value)) -> void {
    _nextNode.set(cds::forward<Arg>(arg));
  }

  template <typename RT, typename... Args> CDS_ATTR(constexpr(14))
  auto emplace(Args&&... args) CDS_ATTR(noexcept(EmplaceNoexcept<Args...>::value))
      -> ReturnIf<RT&, IsSame<RT, T>> {
    return *construct(&_nodeData, cds::forward<Args>(args)...);
  }

  template <typename RT, typename... Args> CDS_ATTR(constexpr(14))
  auto emplace(Args&&... args) CDS_ATTR(noexcept(NextEmplaceNoexcept<Args...>::value))
      -> ReturnIf<RT&, Not<IsSame<RT, T>>> {
    return _nextNode.template emplace<RT>(cds::forward<Args>(args)...);
  }

  CDS_ATTR(constexpr(14)) auto destruct(Size dIdx) noexcept -> void {
    if (idx == dIdx) {
      _nodeData.~Data();
    } else {
      _nextNode.destruct(dIdx);
    }
  }

  template <typename RT> auto raise(Size rIdx) const CDS_ATTR(noexcept(false)) -> void {
    if (rIdx == idx) {
      CDS_ATTR(throw(UnionTypeException::of<T, RT>()));
    }
    _nextNode.template raise<RT>(rIdx);
  }

  CDS_ATTR(constexpr(20)) ~UnionNode() noexcept {}

  CDS_ATTR(constexpr(20)) auto copyConstruct(Size cIdx, UnionNode const& node) CDS_ATTR(noexcept(
      noexcept(Data{node._nodeData})
      && noexcept(lvalue<NextNode>().copyConstruct(cIdx, node._nextNode))
  )) -> void {
    if (cIdx == idx) {
      construct(&_nodeData, node._nodeData);
    } else {
      _nextNode.copyConstruct(cIdx, node._nextNode);
    }
  }

  CDS_ATTR(constexpr(20)) auto moveConstruct(Size cIdx, UnionNode&& node) CDS_ATTR(noexcept(
      noexcept(Data{cds::move(node._nodeData)})
      && noexcept(lvalue<NextNode>().moveConstruct(cIdx, cds::move(node._nextNode)))
  )) -> void {
    if (cIdx == idx) {
      construct(&_nodeData, cds::move(node._nodeData));
    } else {
      _nextNode.moveConstruct(cIdx, cds::move(node._nextNode));
    }
  }

  CDS_ATTR(constexpr(20)) auto copyAssign(Size cIdx, UnionNode const& node) CDS_ATTR(noexcept(
      noexcept(Data{node._nodeData})
      && noexcept(lvalue<NextNode>().copyAssign(cIdx, node._nextNode))
  )) -> void {
    if (cIdx == idx) {
      _nodeData = node._nodeData;
    } else {
      _nextNode.copyAssign(cIdx, node._nextNode);
    }
  }

  CDS_ATTR(constexpr(20)) auto moveAssign(Size cIdx, UnionNode&& node) CDS_ATTR(noexcept(
      noexcept(Data{cds::move(node._nodeData)})
      && noexcept(lvalue<NextNode>().moveAssign(cIdx, cds::move(node._nextNode)))
  )) -> void {
    if (cIdx == idx) {
      _nodeData = cds::move(node._nodeData);
    } else {
      _nextNode.moveAssign(cIdx, cds::move(node._nextNode));
    }
  }

  Data _nodeData;
  NextNode _nextNode;
};

template <Size idx, typename T, typename... R> union TrivialUnionNode<idx, T, R...> {
  using Data = T;
  using NextNode = TrivialUnionNode<idx + 1u, R...>;

  template <typename... Args> using NextEmplaceNoexcept = typename NextNode::template EmplaceNoexcept<Args...>;
  template <typename... Args> using EmplaceNoexcept = IsNoexceptConstructible<Data, Args...>;

  template <typename TT = T, EnableIf<IsDefaultConstructible<TT>> = 0>
  CDS_ATTR(constexpr(11)) TrivialUnionNode() CDS_ATTR(noexcept(IsNoexceptDefaultConstructible<T>::value)) :
      _nodeData{} {}

  CDS_ATTR(constexpr(14)) TrivialUnionNode(Size cIdx, TrivialUnionNode const& node) CDS_ATTR(noexcept(
      noexcept(Data{node._nodeData})
      && noexcept(lvalue<TrivialUnionNode>().copyConstruct(cIdx, node))
  )) {
    copyConstruct(cIdx, node);
  }

  CDS_ATTR(constexpr(14)) TrivialUnionNode(Size cIdx, TrivialUnionNode&& node) CDS_ATTR(noexcept(
      noexcept(Data{cds::move(node._nodeData)})
      && noexcept(lvalue<TrivialUnionNode>().moveConstruct(cIdx, cds::move(node)))
  )) {
    moveConstruct(cIdx, cds::move(node));
  }

  template <typename Arg, EnableIf<IsUnionBestMatch<T, Arg, T, R...>> = 0>
  CDS_ATTR(2(constexpr(11), explicit)) TrivialUnionNode(Arg&& arg)
      CDS_ATTR(noexcept(UnionBestMatch<Arg, T, R...>::Noexcept::value)) :
      _nodeData(cds::forward<Arg>(arg)) {}

  template <typename Arg, EnableIf<Not<IsUnionBestMatch<T, Arg, T, R...>>> = 0>
  CDS_ATTR(2(constexpr(11), explicit)) TrivialUnionNode(Arg&& arg)
      CDS_ATTR(noexcept(UnionBestMatch<Arg, T, R...>::Noexcept::value)) :
      _nextNode{cds::forward<Arg>(arg)} {}

  template <typename Arg, EnableIf<IsUnionBestMatch<T, Arg, T, R...>> = 0>
  CDS_ATTR(constexpr(14)) auto set(Arg&& arg)
      CDS_ATTR(noexcept(UnionBestMatch<Arg, T, R...>::Noexcept::value)) -> void {
    _nodeData = cds::forward<Arg>(arg);
  }

  template <typename Arg, EnableIf<Not<IsUnionBestMatch<T, Arg, T, R...>>> = 0>
  CDS_ATTR(constexpr(14)) auto set(Arg&& arg)
      CDS_ATTR(noexcept(UnionBestMatch<Arg, T, R...>::Noexcept::value)) -> void {
    _nextNode.set(cds::forward<Arg>(arg));
  }

  template <typename RT, typename... Args> CDS_ATTR(constexpr(14))
  auto emplace(Args&&... args) CDS_ATTR(noexcept(EmplaceNoexcept<Args...>::value))
      -> ReturnIf<RT&, IsSame<RT, T>> {
    return *construct(&_nodeData, cds::forward<Args>(args)...);
  }

  template <typename RT, typename... Args> CDS_ATTR(constexpr(14))
  auto emplace(Args&&... args) CDS_ATTR(noexcept(NextEmplaceNoexcept<Args...>::value))
      -> ReturnIf<RT&, Not<IsSame<RT, T>>> {
    return _nextNode.template emplace<RT>(cds::forward<Args>(args)...);
  }

  template <typename RT> auto raise(Size rIdx) const CDS_ATTR(noexcept(false)) -> void {
    if (rIdx == idx) {
      CDS_ATTR(throw(UnionTypeException::of<T, RT>()));
    }
    _nextNode.template raise<RT>(rIdx);
  }

  ~TrivialUnionNode() noexcept = default;

  CDS_ATTR(constexpr(20)) auto copyConstruct(Size cIdx, TrivialUnionNode const& node) CDS_ATTR(noexcept(
      noexcept(Data{node._nodeData})
      && noexcept(lvalue<NextNode>().copyConstruct(cIdx, node._nextNode))
  )) -> void {
    if (cIdx == idx) {
      construct(&_nodeData, node._nodeData);
    } else {
      _nextNode.copyConstruct(cIdx, node._nextNode);
    }
  }

  CDS_ATTR(constexpr(20)) auto moveConstruct(Size cIdx, TrivialUnionNode&& node) CDS_ATTR(noexcept(
      noexcept(Data{cds::move(node._nodeData)})
      && noexcept(lvalue<NextNode>().moveConstruct(cIdx, cds::move(node._nextNode)))
  )) -> void {
    if (cIdx == idx) {
      construct(&_nodeData, cds::move(node._nodeData));
    } else {
      _nextNode.moveConstruct(cIdx, cds::move(node._nextNode));
    }
  }

  CDS_ATTR(constexpr(20)) auto copyAssign(Size cIdx, TrivialUnionNode const& node) CDS_ATTR(noexcept(
      noexcept(Data{node._nodeData})
      && noexcept(lvalue<NextNode>().copyAssign(cIdx, node._nextNode))
  )) -> void {
    if (cIdx == idx) {
      _nodeData = node._nodeData;
    } else {
      _nextNode.copyAssign(cIdx, node._nextNode);
    }
  }

  CDS_ATTR(constexpr(20)) auto moveAssign(Size cIdx, TrivialUnionNode&& node) CDS_ATTR(noexcept(
      noexcept(Data{cds::move(node._nodeData)})
      && noexcept(lvalue<NextNode>().moveAssign(cIdx, cds::move(node._nextNode)))
  )) -> void {
    if (cIdx == idx) {
      _nodeData = cds::move(node._nodeData);
    } else {
      _nextNode.moveAssign(cIdx, cds::move(node._nextNode));
    }
  }

  Data _nodeData;
  NextNode _nextNode;
};

template <Size, typename, typename...> struct IdealUnionNodeBase {
  using Type = void;
};

template <Size idx, typename T, typename F> struct IdealUnionNodeBase<idx, T, F> {
  using Type = Conditional<IsSame<T, F>, UnionNode<idx, F>, void>;
};

template <Size idx, typename T, typename F, typename... R> struct IdealUnionNodeBase<idx, T, F, R...> {
  using Type = Conditional<IsSame<T, F>, UnionNode<idx, F, R...>, typename IdealUnionNodeBase<idx + 1, T, R...>::Type>;
};

template <typename T, typename N, typename = typename IsSame<RemoveCVRef<T>, RemoveCVRef<typename N::Data>>::Type>
struct UnionNodeCast {};

template <typename T, typename N> struct UnionNodeCast<T, N, True> {
  template <typename A> CDS_ATTR(2(nodiscard, constexpr(11))) auto operator()(A&& n) const noexcept -> T {
    return cds::forward<A>(n)._nodeData;
  }
};

template <typename T, typename N> struct UnionNodeCast<T, N, False> {
  template <typename A, typename NN = typename RemoveCVRef<A>::NextNode> CDS_ATTR(2(nodiscard, constexpr(11)))
  auto operator()(A&& n) const noexcept -> T {
    return UnionNodeCast<T, NN>()(cds::forward<A>(n)._nextNode);
  }
};

template <typename T, typename... Ts> CDS_ATTR(2(nodiscard, constexpr(11)))
auto unionGet(UnionNode<0u, Ts...> const& node) noexcept -> T const& {
  return UnionNodeCast<T const&, UnionNode<0u, Ts...>>()(node);
}

template <typename T, typename... Ts> CDS_ATTR(2(nodiscard, constexpr(11)))
auto unionGet(UnionNode<0u, Ts...>& node) noexcept -> T& {
  return UnionNodeCast<T&, UnionNode<0u, Ts...>>()(node);
}

template <Size, typename, typename...> struct IdealTrivialUnionNodeBase {
  using Type = void;
};

template <Size idx, typename T, typename F> struct IdealTrivialUnionNodeBase<idx, T, F> {
  using Type = Conditional<IsSame<T, F>, TrivialUnionNode<idx, F>, void>;
};

template <Size idx, typename T, typename F, typename... R> struct IdealTrivialUnionNodeBase<idx, T, F, R...> {
  using Type = Conditional<
      IsSame<T, F>,
      TrivialUnionNode<idx, F, R...>,
      typename IdealTrivialUnionNodeBase<idx + 1, T, R...>::Type
  >;
};

template <typename T, typename N, typename = typename IsSame<RemoveCVRef<T>, RemoveCVRef<typename N::Data>>::Type>
struct TrivialUnionNodeCast {};

template <typename T, typename N> struct TrivialUnionNodeCast<T, N, True> {
  template <typename A> CDS_ATTR(2(nodiscard, constexpr(11))) auto operator()(A&& n) const noexcept -> T {
    return cds::forward<A>(n)._nodeData;
  }
};

template <typename T, typename N> struct TrivialUnionNodeCast<T, N, False> {
  template <typename A, typename NN = typename RemoveCVRef<A>::NextNode> CDS_ATTR(2(nodiscard, constexpr(11)))
  auto operator()(A&& n) const noexcept -> T {
    return TrivialUnionNodeCast<T, NN>()(cds::forward<A>(n)._nextNode);
  }
};

template <typename T, typename... Ts> CDS_ATTR(2(nodiscard, constexpr(11)))
auto unionGet(TrivialUnionNode<0u, Ts...> const& node) noexcept -> T const& {
  return TrivialUnionNodeCast<T const&, TrivialUnionNode<0u, Ts...>>()(node);
}

template <typename T, typename... Ts> CDS_ATTR(2(nodiscard, constexpr(11)))
auto unionGet(TrivialUnionNode<0u, Ts...>& node) noexcept -> T& {
  return TrivialUnionNodeCast<T&, TrivialUnionNode<0u, Ts...>>()(node);
}

using meta::IsTriviallyDestructible;
using meta::lvalue;
using meta::EnableIf;
using meta::Not;
using meta::IsSame;
using meta::RemoveCVRef;
template <typename> struct AllTrivialInPack : False {};
template <typename... A> struct AllTrivialInPack<Pack<A...>> : All<IsTriviallyDestructible, A...> {};

template <typename P, typename = typename AllTrivialInPack<P>::Type> struct UnionStorageBase {};

template <typename... T> struct UnionStorageBase<Pack<T...>, True> {
  using Data = TrivialUnionNode<0u, T...>;

  CDS_ATTR(2(nodiscard, constexpr(11))) auto valueless() const noexcept -> bool {
    return _idx == sizeof... (T);
  }

  CDS_ATTR(constexpr(11)) UnionStorageBase() CDS_ATTR(noexcept(noexcept(Data{}))) : _data{}, _idx{0u} {}
  CDS_ATTR(constexpr(14)) UnionStorageBase(UnionStorageBase const& obj)
      CDS_ATTR(noexcept(noexcept(lvalue<Data>().copyConstruct(0u, obj._data)))) CDS_ATTR(try_list(
          _data(obj._idx, obj._data),
          _idx(sizeof...(T))
      )) {
        _idx = obj._idx;
      } CDS_ATTR(catch(..., {
        throw;
      }))

  CDS_ATTR(constexpr(14)) UnionStorageBase(UnionStorageBase&& obj)
      CDS_ATTR(noexcept(noexcept(Data{obj._idx, cds::move(obj._data)}))) :
      _data{obj._idx, cds::move(obj._data)},
      _idx{obj._idx} {}

  template <typename Arg, EnableIf<Not<IsSame<RemoveCVRef<Arg>, UnionStorageBase>>> = 0>
  CDS_ATTR(2(implicit, constexpr(11))) UnionStorageBase(Arg&& arg)
      CDS_ATTR(noexcept(noexcept(Data(cds::forward<Arg>(arg))))) :
      _data{cds::forward<Arg>(arg)},
      _idx{impl::IndexOfBestMatch<Arg, T...>::Type::value} {}

  CDS_ATTR(constexpr(14)) auto operator=(UnionStorageBase const& obj) CDS_ATTR(noexcept(
      noexcept(meta::lvalue<Data>().copyConstruct(0u, obj._data))
      && noexcept(meta::lvalue<Data>().copyAssign(0u, obj._data))
  )) -> UnionStorageBase& {
    if (this == &obj) {
      return *this;
    }

    CDS_ATTR(try) {
      if (_idx == obj._idx) {
        _data.copyAssign(_idx, obj._data);
      } else {
        _idx = obj._idx;
        _data.copyConstruct(_idx, obj._data);
      }
      return *this;
    } CDS_ATTR(catch(..., {
      _idx = sizeof... (T);
      throw;
    }))
  }

  CDS_ATTR(constexpr(14)) auto operator=(UnionStorageBase&& obj) CDS_ATTR(noexcept(
      noexcept(meta::lvalue<Data>().moveConstruct(0u, cds::move(obj._data)))
      && noexcept(meta::lvalue<Data>().moveAssign(0u, cds::move(obj._data)))
  )) -> UnionStorageBase& {
    if (this == &obj) {
      return *this;
    }

    CDS_ATTR(try) {
      if (_idx == obj._idx) {
        _data.moveAssign(_idx, cds::move(obj._data));
      } else {
        _idx = obj._idx;
        _data.moveConstruct(_idx, cds::move(obj._data));
      }
      return *this;
    } CDS_ATTR(catch(..., {
      _idx = sizeof... (T);
      throw;
    }))
  }

  template <typename Arg, EnableIf<Not<IsSame<RemoveCVRef<Arg>, UnionStorageBase>>> = 0>
  CDS_ATTR(constexpr(14)) auto operator=(Arg&& arg)
      CDS_ATTR(noexcept(noexcept(lvalue<Data>()
        .template emplace<typename UnionBestMatch<Arg, T...>::Type>(cds::forward<Arg>(arg))
      ))) -> UnionStorageBase& {
    CDS_ATTR(try) {
      if (valueless()) {
        _data.template emplace<typename UnionBestMatch<Arg, T...>::Type>(cds::forward<Arg>(arg));
        _idx = IndexOfBestMatch<Arg, T...>::Type::value;
      } else {
        _data.set(cds::forward<Arg>(arg));
      }
    } CDS_ATTR(catch(..., {
      _idx = sizeof... (T);
      throw;
    }))
    return *this;
  }

  template <typename T1, typename... Args>
  CDS_ATTR(constexpr(14)) auto emplace(Args&&... args)
      CDS_ATTR(noexcept(noexcept(meta::lvalue<Data>()
        .template emplace<typename impl::UnionBestMatch<T1, T...>::Type>(cds::forward<Args>(args)...)
      )))
      -> typename UnionBestMatch<T1, T...>::Type& {
    CDS_ATTR(try) {
      auto& value = _data
          .template emplace<typename UnionBestMatch<T1, T...>::Type>(cds::forward<Args>(args)...);
      _idx = IndexOfBestMatch<T1, T...>::Type::value;
      return value;
    } CDS_ATTR(catch(..., {
      _idx = sizeof... (T);
      throw;
    }))
  }

  ~UnionStorageBase() = default;

  Data _data;
  Size _idx;
};

template <typename... T> struct UnionStorageBase<Pack<T...>, False> {
  using Data = UnionNode<0u, T...>;

  CDS_ATTR(2(nodiscard, constexpr(11))) auto valueless() const noexcept -> bool {
    return _idx == sizeof... (T);
  }

  CDS_ATTR(constexpr(11)) UnionStorageBase() CDS_ATTR(noexcept(noexcept(Data{}))) : _data{}, _idx{0u} {}
  CDS_ATTR(constexpr(14)) UnionStorageBase(UnionStorageBase const& obj)
      CDS_ATTR(noexcept(noexcept(lvalue<Data>().copyConstruct(0u, obj._data)))) CDS_ATTR(try_list(
          _data(obj._idx, obj._data),
          _idx(sizeof...(T))
      )) {
        _idx = obj._idx;
      } CDS_ATTR(catch(..., {
        throw;
      }))

  CDS_ATTR(constexpr(14)) UnionStorageBase(UnionStorageBase&& obj)
      CDS_ATTR(noexcept(noexcept(Data{obj._idx, cds::move(obj._data)}))) :
      _data{obj._idx, cds::move(obj._data)},
      _idx{obj._idx} {}

  template <typename Arg, EnableIf<Not<IsSame<RemoveCVRef<Arg>, UnionStorageBase>>> = 0>
  CDS_ATTR(2(implicit, constexpr(11))) UnionStorageBase(Arg&& arg)
      CDS_ATTR(noexcept(noexcept(Data(cds::forward<Arg>(arg))))) :
      _data{cds::forward<Arg>(arg)},
      _idx{impl::IndexOfBestMatch<Arg, T...>::Type::value} {}

  CDS_ATTR(constexpr(20)) auto operator=(UnionStorageBase const& obj) CDS_ATTR(noexcept(
      noexcept(meta::lvalue<Data>().copyConstruct(0u, obj._data))
      && noexcept(meta::lvalue<Data>().copyAssign(0u, obj._data))
  )) -> UnionStorageBase& {
    if (this == &obj) {
      return *this;
    }

    CDS_ATTR(try) {
      if (_idx == obj._idx) {
        _data.copyAssign(_idx, obj._data);
      } else {
        _data.destruct(_idx);
        _idx = obj._idx;
        _data.copyConstruct(_idx, obj._data);
      }
      return *this;
    } CDS_ATTR(catch(..., {
      _idx = sizeof... (T);
      throw;
    }))
  }

  CDS_ATTR(constexpr(20)) auto operator=(UnionStorageBase&& obj) CDS_ATTR(noexcept(
      noexcept(meta::lvalue<Data>().moveConstruct(0u, cds::move(obj._data)))
      && noexcept(meta::lvalue<Data>().moveAssign(0u, cds::move(obj._data)))
  )) -> UnionStorageBase& {
    if (this == &obj) {
      return *this;
    }

    CDS_ATTR(try) {
      if (_idx == obj._idx) {
        _data.moveAssign(_idx, cds::move(obj._data));
      } else {
        _data.destruct(_idx);
        _idx = obj._idx;
        _data.moveConstruct(_idx, cds::move(obj._data));
      }
      return *this;
    } CDS_ATTR(catch(..., {
      _idx = sizeof... (T);
      throw;
    }))
  }

  template <typename Arg, EnableIf<Not<IsSame<RemoveCVRef<Arg>, UnionStorageBase>>> = 0>
  CDS_ATTR(constexpr(20)) auto operator=(Arg&& arg)
      CDS_ATTR(noexcept(noexcept(lvalue<Data>()
        .template emplace<typename UnionBestMatch<Arg, T...>::Type>(cds::forward<Arg>(arg))
      ))) -> UnionStorageBase& {
    if (_idx != IndexOfBestMatch<Arg, T...>::Type::value && !valueless()) {
      _data.destruct(cds::exchange(_idx, sizeof... (T)));
    }

    CDS_ATTR(try) {
      if (valueless()) {
        _data.template emplace<typename UnionBestMatch<Arg, T...>::Type>(cds::forward<Arg>(arg));
        _idx = impl::IndexOfBestMatch<Arg, T...>::Type::value;
      } else {
        _data.set(cds::forward<Arg>(arg));
      }
    } CDS_ATTR(catch(..., {
      _idx = sizeof... (T);
      throw;
    }))
    return *this;
  }

  template <typename T1, typename... Args>
  CDS_ATTR(constexpr(20)) auto emplace(Args&&... args)
      CDS_ATTR(noexcept(noexcept(meta::lvalue<Data>()
        .template emplace<typename impl::UnionBestMatch<T1, T...>::Type>(cds::forward<Args>(args)...)
      )))
      -> typename impl::UnionBestMatch<T1, T...>::Type& {
    if (!valueless()) {
      _data.destruct(cds::exchange(_idx, sizeof... (T)));
    }

    CDS_ATTR(try) {
      auto& value = _data
          .template emplace<typename impl::UnionBestMatch<T1, T...>::Type>(cds::forward<Args>(args)...);
      _idx = impl::IndexOfBestMatch<T1, T...>::Type::value;
      return value;
    } CDS_ATTR(catch(..., {
      _idx = sizeof... (T);
      throw;
    }))
  }

  CDS_ATTR(constexpr(20)) ~UnionStorageBase() noexcept {
    _data.destruct(_idx);
  }

  Data _data;
  Size _idx;
};
} // namespace impl
} // namespace cds

#endif // #ifndef CDS_PRIMITIVE_UNION_NODE_HPP
