//
// Created by loghin on 7/7/25.
//

#ifndef CDS_PRIMITIVE_FORWARD_TUPLE_NODE_HPP
#define CDS_PRIMITIVE_FORWARD_TUPLE_NODE_HPP

#include <cds/functional/Hash>
#include <cds/functional/StreamPrint>
#include <cds/meta/Semantics>
#include <cds/meta/ObjectTraits>
#include <cds/meta/Tags>

namespace cds {
namespace impl {
using functional::streamPrint;

using meta::Bool;
using meta::Conditional;
using meta::EnableIf;
using meta::IsDefaultConstructible;
using meta::IsNoexceptDefaultConstructible;
using meta::Not;
using meta::InPlace;

template <Size idx, typename T> struct TupleLeaf {
  using Type = T;
  static auto constexpr index = idx;

  CDS_ATTR(2(nodiscard, constexpr(11))) auto leaf() const& noexcept -> TupleLeaf const& {
    return *this;
  }

  CDS_ATTR(2(nodiscard, constexpr(14))) auto leaf()& noexcept -> TupleLeaf& {
    return *this;
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto leaf() const&& noexcept -> TupleLeaf const&& {
    return mv(*this);
  }

  CDS_ATTR(2(nodiscard, constexpr(14))) auto leaf()&& noexcept -> TupleLeaf&& {
    return mv(*this);
  }

  TupleLeaf() = default;
  TupleLeaf(TupleLeaf const&) = default;
  TupleLeaf(TupleLeaf&&) = default;
  ~TupleLeaf() = default;

  auto operator=(TupleLeaf const&) -> TupleLeaf& = default;
  auto operator=(TupleLeaf&&) -> TupleLeaf& = default;

  template <typename A> CDS_ATTR(2(explicit, constexpr(11))) TupleLeaf(InPlace, A&& arg) : _data(fwd<A>(arg)) {}

  template <typename A> CDS_ATTR(2(explicit, constexpr(11))) TupleLeaf(TupleLeaf<idx, A> const& leaf) :
      _data(leaf._data) {}

  template <typename A> CDS_ATTR(2(explicit, constexpr(11))) TupleLeaf(TupleLeaf<idx, A>&& leaf) :
      _data(mv(leaf._data)) {}

  template <typename A> CDS_ATTR(constexpr(14)) auto operator=(TupleLeaf<idx, A> const& leaf) -> TupleLeaf& {
    _data = leaf._data;
    return *this;
  }

  template <typename A> CDS_ATTR(constexpr(14)) auto operator=(TupleLeaf<idx, A>&& leaf) -> TupleLeaf& {
    _data = mv(leaf._data);
    return *this;
  }

  T _data;
};

template <Size, typename...> struct FwdTupleNode;

template <Size idx, typename Type> struct FwdTupleNode<idx, Type> : TupleLeaf<idx, Type> {
  using Leaf = TupleLeaf<idx, Type>;
  using Next = void;

  using Leaf::leaf;

  FwdTupleNode() = default;
  FwdTupleNode(FwdTupleNode const&) = default;
  FwdTupleNode(FwdTupleNode&&) = default;
  ~FwdTupleNode() = default;

  auto operator=(FwdTupleNode const&) -> FwdTupleNode& = default;
  auto operator=(FwdTupleNode&&) -> FwdTupleNode& = default;

  template <typename A> CDS_ATTR(2(explicit, constexpr(11))) FwdTupleNode(InPlace, A&& arg) :
      Leaf{InPlace{}, fwd<A>(arg)} {}

  template <typename A> CDS_ATTR(2(explicit, constexpr(11))) FwdTupleNode(FwdTupleNode<idx, A> const& other) :
      Leaf{other.leaf()} {}

  template <typename A> CDS_ATTR(2(explicit, constexpr(11))) FwdTupleNode(FwdTupleNode<idx, A>&& other) :
      Leaf{mv(other).leaf()} {}

  template <typename A> CDS_ATTR(constexpr(14)) auto operator=(FwdTupleNode<idx, A> const& other) -> FwdTupleNode& {
    leaf() = other.leaf();
    return *this;
  }

  template <typename A> CDS_ATTR(constexpr(14)) auto operator=(FwdTupleNode<idx, A>&& other) -> FwdTupleNode& {
    leaf() = mv(other).leaf();
    return *this;
  }
};

template <Size idx, typename FirstType, typename... RemainingTypes>
struct FwdTupleNode<idx, FirstType, RemainingTypes...> :
    TupleLeaf<idx, FirstType>,
    FwdTupleNode<idx + 1, RemainingTypes...> {
  using Leaf = TupleLeaf<idx, FirstType>;
  using Next = FwdTupleNode<idx + 1, RemainingTypes...>;

  using Leaf::leaf;

  CDS_ATTR(2(nodiscard, constexpr(14))) auto next()& noexcept -> Next& {
    return *this;
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto next() const& noexcept -> Next const& {
    return *this;
  }

  CDS_ATTR(2(nodiscard, constexpr(14))) auto next()&& noexcept -> Next&& {
    return mv(*this);
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto next() const&& noexcept -> Next const&& {
    return mv(*this);
  }

  FwdTupleNode() = default;
  FwdTupleNode(FwdTupleNode const&) = default;
  FwdTupleNode(FwdTupleNode&&) = default;
  ~FwdTupleNode() = default;

  auto operator=(FwdTupleNode const&) -> FwdTupleNode& = default;
  auto operator=(FwdTupleNode&&) -> FwdTupleNode& = default;

  template <typename A, typename... R> CDS_ATTR(2(explicit, constexpr(11)))
  FwdTupleNode(InPlace, A&& arg, R&&... remaining) :
      Leaf{InPlace{}, fwd<A>(arg)}, Next{InPlace{}, fwd<R>(remaining)...} {}
  
  template <typename A, typename... R> CDS_ATTR(2(explicit, constexpr(11)))
  FwdTupleNode(FwdTupleNode<idx, A, R...> const& tuple) : Leaf{tuple.leaf()}, Next{tuple.next()} {}

  template <typename A, typename... R> CDS_ATTR(2(explicit, constexpr(11)))
  FwdTupleNode(FwdTupleNode<idx, A, R...>&& tuple) : Leaf{mv(tuple).leaf()}, Next{mv(tuple).next()} {}

  template <typename A, typename... R> CDS_ATTR(constexpr(14)) auto operator=(FwdTupleNode<idx, A, R...> const& tuple)
      -> FwdTupleNode& {
    leaf() = tuple.leaf();
    next() = tuple.next();
    return *this;
  }

  template <typename A, typename... R> CDS_ATTR(constexpr(14)) auto operator=(FwdTupleNode<idx, A, R...>&& tuple)
      -> FwdTupleNode& {
    leaf() = mv(tuple).leaf();
    next() = mv(tuple).next();
    return *this;
  }
};

template <Size idx, typename T0, typename T1> CDS_ATTR(2(nodiscard, constexpr(11)))
auto operator==(TupleLeaf<idx, T0> const& lhs, TupleLeaf<idx, T1> const& rhs) -> bool {
  return lhs._data == rhs._data;
}

template <Size idx, typename T0, typename T1> CDS_ATTR(2(nodiscard, constexpr(11)))
auto operator==(FwdTupleNode<idx, T0> const& lhs, FwdTupleNode<idx, T1> const& rhs) -> bool {
  return lhs.leaf() == rhs.leaf();
}

template <Size idx, typename T0, typename... R0, typename T1, typename... R1> CDS_ATTR(2(nodiscard, constexpr(11)))
auto operator==(FwdTupleNode<idx, T0, R0...> const& lhs, FwdTupleNode<idx, T1, R1...> const& rhs) -> bool {
  return lhs.leaf() == rhs.leaf() && rhs.next() == rhs.next();
}

template <Size idx, typename T0, typename T1> CDS_ATTR(2(nodiscard, constexpr(11)))
auto operator!=(TupleLeaf<idx, T0> const& lhs, TupleLeaf<idx, T1> const& rhs) -> bool {
  return lhs._data != rhs._data;
}

template <Size idx, typename T0, typename T1> CDS_ATTR(2(nodiscard, constexpr(11)))
auto operator!=(FwdTupleNode<idx, T0> const& lhs, FwdTupleNode<idx, T1> const& rhs) -> bool {
  return lhs.leaf() != rhs.leaf();
}

template <Size idx, typename T0, typename... R0, typename T1, typename... R1> CDS_ATTR(2(nodiscard, constexpr(11)))
auto operator!=(FwdTupleNode<idx, T0, R0...> const& lhs, FwdTupleNode<idx, T1, R1...> const& rhs) -> bool {
  return lhs.leaf() != rhs.leaf() || lhs.next() != rhs.next();
}

template <Size, typename> struct TupleNodeUpCaster;

template <Size idx> struct TupleNodeUpCaster<idx, void> {
  using Type = void;
};

template <Size idx, Size nodeIdx, typename... Ts> struct TupleNodeUpCaster<idx, FwdTupleNode<nodeIdx, Ts...>> {
  using Node = FwdTupleNode<nodeIdx, Ts...>;
  using Type = Conditional<Bool<idx == nodeIdx>, Node, typename TupleNodeUpCaster<idx, typename Node::Next>::Type>;
};

template <Size idx, Size nodeIdx, typename... Ts, typename Up = TupleNodeUpCaster<idx, FwdTupleNode<nodeIdx, Ts...>>>
CDS_ATTR(2(nodiscard, constexpr(11))) auto upcast(FwdTupleNode<nodeIdx, Ts...> const& node)
    -> typename Up::Type const& {
  return node;
}

template <Size idx, Size nodeIdx, typename... Ts, typename Up = TupleNodeUpCaster<idx, FwdTupleNode<nodeIdx, Ts...>>>
CDS_ATTR(2(nodiscard, constexpr(14))) auto upcast(FwdTupleNode<nodeIdx, Ts...>&& node)
    -> typename Up::Type&& {
  return mv(node);
}

template <Size idx, Size nodeIdx, typename... Ts, typename Up = TupleNodeUpCaster<idx, FwdTupleNode<nodeIdx, Ts...>>>
CDS_ATTR(2(nodiscard, constexpr(14))) auto upcast(FwdTupleNode<nodeIdx, Ts...>& node)
    -> typename Up::Type& {
  return node;
}

template <Size idx, Size nodeIdx, typename... Ts, typename Up = TupleNodeUpCaster<idx, FwdTupleNode<nodeIdx, Ts...>>>
CDS_ATTR(2(nodiscard, constexpr(11))) auto upcast(FwdTupleNode<nodeIdx, Ts...> const&& node)
    -> typename Up::Type const&& {
  return mv(node);
}

template <typename C, Size idx, typename T0>
auto operator<<(std::basic_ostream<C>& out, FwdTupleNode<idx, T0> const& node) noexcept
    -> std::basic_ostream<C>& {
  return streamPrint(out, node.leaf()._data);
}

template <typename C, Size idx, typename T0, typename... Ts>
auto operator<<(std::basic_ostream<C>& out, FwdTupleNode<idx, T0, Ts...> const& node) noexcept
    -> std::basic_ostream<C>& {
  return streamPrint(out, node.leaf()._data) << ", " << node.next();
}
} // namespace impl

namespace functional {
template <Size idx, typename Type> struct Hash<cds::impl::TupleLeaf<idx, Type>> :
    Hash<typename cds::impl::TupleLeaf<idx, Type>::Type> {
  CDS_ATTR(2(nodiscard, constexpr(11))) auto operator()(cds::impl::TupleLeaf<idx, Type> const& node) const noexcept
      -> Size {
    return Hash<typename cds::impl::TupleLeaf<idx, Type>::Type>::operator()(node._data);
  }
};

template <Size idx, typename Type> struct Hash<cds::impl::FwdTupleNode<idx, Type>> :
    Hash<typename cds::impl::FwdTupleNode<idx, Type>::Leaf> {
  CDS_ATTR(2(nodiscard, constexpr(11))) auto operator()(cds::impl::FwdTupleNode<idx, Type> const& node) const noexcept
      -> Size {
    return Hash<typename cds::impl::FwdTupleNode<idx, Type>::Leaf>::operator()(node.leaf());
  }
};

template <Size idx, typename Type, typename... RemainingTypes>
struct Hash<cds::impl::FwdTupleNode<idx, Type, RemainingTypes...>> :
    Hash<typename cds::impl::FwdTupleNode<idx, Type, RemainingTypes...>::Leaf>,
    Hash<typename cds::impl::FwdTupleNode<idx, Type, RemainingTypes...>::Next> {
  CDS_ATTR(2(nodiscard, constexpr(11)))
  auto operator()(cds::impl::FwdTupleNode<idx, Type, RemainingTypes...> const& node) const noexcept -> Size {
    return Hash<typename cds::impl::FwdTupleNode<idx, Type, RemainingTypes...>::Leaf>::operator()(node.leaf()) +
        Hash<typename cds::impl::FwdTupleNode<idx, Type, RemainingTypes...>::Next>::operator()(node.next()) * 31;
  }
};
} // namespace functional
} // namespace cds

#endif // #ifndef CDS_PRIMITIVE_FORWARD_TUPLE_NODE_HPP
