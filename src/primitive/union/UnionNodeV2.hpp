//
// Created by loghin on 9/18/24.
//

#ifndef CDS_PRIMITIVE_UNION_NODE_V2_HPP
#define CDS_PRIMITIVE_UNION_NODE_V2_HPP
#pragma once

namespace cds {
namespace impl {
namespace unionImpl {
using meta::All;
using meta::And;
using meta::Conditional;
using meta::Common;
using meta::False;
using meta::Integral;
using meta::IsCopyAssignable;
using meta::IsCopyConstructible;
using meta::IsDefaultConstructible;
using meta::IsDestructible;
using meta::IsMoveAssignable;
using meta::IsMoveConstructible;
using meta::IsNoexceptCopyAssignable;
using meta::IsNoexceptCopyConstructible;
using meta::IsNoexceptMoveAssignable;
using meta::IsNoexceptMoveConstructible;
using meta::IsTriviallyCopyAssignable;
using meta::IsTriviallyCopyConstructible;
using meta::IsTriviallyDefaultConstructible;
using meta::IsTriviallyDestructible;
using meta::IsTriviallyMoveAssignable;
using meta::IsTriviallyMoveConstructible;
using meta::Lt;
using meta::True;

using meta::impl::Pack;

struct Valueless {};
template <Size> struct InPlaceIndex {};

enum class UnionFunctionDetail {
  Trivial, NonTrivial, Deleted
};

enum class UnionFunctionType {
  Dtr, DefCtr, CopyCtr, CopyAssign, MoveCtr, MoveAssign
};

template <typename, typename> struct UnionFunctionSpec {};
template <> struct UnionFunctionSpec<True::Type, True::Type> {
  constexpr static auto value = UnionFunctionDetail::Trivial;
};
template <> struct UnionFunctionSpec<False::Type, True::Type> {
  constexpr static auto value = UnionFunctionDetail::NonTrivial;
};
template <> struct UnionFunctionSpec<False::Type, False::Type> {
  constexpr static auto value = UnionFunctionDetail::Deleted;
};

template <typename... Ts> struct UnpackedUnionDetails {
  constexpr static auto dtr = UnionFunctionSpec<
      typename All<IsTriviallyDestructible, Ts...>::Type,
      typename All<IsDestructible, Ts...>::Type
  >::value;
  constexpr static auto defCtr = UnionFunctionSpec<
      typename All<IsTriviallyDefaultConstructible, Ts...>::Type,
      typename All<IsDefaultConstructible, Ts...>::Type
  >::value;
  constexpr static auto copyCtr = UnionFunctionSpec<
      typename All<IsTriviallyCopyConstructible, Ts...>::Type,
      typename All<IsCopyConstructible, Ts...>::Type
  >::value;
  constexpr static auto copyAssign = UnionFunctionSpec<
      typename All<IsTriviallyCopyAssignable, Ts...>::Type,
      typename All<IsCopyAssignable, Ts...>::Type
  >::value;
  constexpr static auto moveCtr = UnionFunctionSpec<
      typename All<IsTriviallyMoveConstructible, Ts...>::Type,
      typename All<IsMoveConstructible, Ts...>::Type
  >::value;
  constexpr static auto moveAssign = UnionFunctionSpec<
      typename All<IsTriviallyMoveAssignable, Ts...>::Type,
      typename All<IsMoveAssignable, Ts...>::Type
  >::value;
};

template <typename> struct UnionDetails {};
template <typename... Types> struct UnionDetails<Pack<Types...>> : UnpackedUnionDetails<Types...> {};

template <UnionFunctionDetail, typename...> union UnionStorage {};
template <UnionFunctionDetail detail> union UnionStorage<detail> {};

template <typename H, typename... T> union UnionStorage<UnionFunctionDetail::Trivial, H, T...> {
  CDS_ATTR(2(explicit, constexpr(11))) UnionStorage(CDS_ATTR(unused) Valueless) noexcept : _valueless{} {}

  template <typename... A> CDS_ATTR(2(explicit, constexpr(11)))
  UnionStorage(CDS_ATTR(unused) InPlaceIndex<0>, A&&... args)
      CDS_ATTR(noexcept(noexcept(H(cds::forward<A>(args)...)))) : _head{cds::forward<A>(args)...} {}

  template <Size inPlaceIndex, typename... A> CDS_ATTR(2(explicit, constexpr(11)))
  UnionStorage(CDS_ATTR(unused) InPlaceIndex<inPlaceIndex>, A&&... args)
      CDS_ATTR(noexcept(noexcept(H(cds::forward<A>(args)...)))) :
      _tail{InPlaceIndex<inPlaceIndex - 1>{}, cds::forward<A>(args)...} {}

  char _valueless;
  H _head;
  UnionStorage<UnionFunctionDetail::Trivial, T...> _tail;
  ~UnionStorage() noexcept = default;
};

template <typename H, typename... T> union UnionStorage<UnionFunctionDetail::NonTrivial, H, T...> {
  CDS_ATTR(2(explicit, constexpr(11))) UnionStorage(CDS_ATTR(unused) Valueless) noexcept : _valueless{} {}

  template <typename... A> CDS_ATTR(2(explicit, constexpr(11)))
  UnionStorage(CDS_ATTR(unused) InPlaceIndex<0>, A&&... args)
      CDS_ATTR(noexcept(noexcept(H(cds::forward<A>(args)...)))) : _head{cds::forward<A>(args)...} {}

  template <Size inPlaceIndex, typename... A> CDS_ATTR(2(explicit, constexpr(11)))
  UnionStorage(CDS_ATTR(unused) InPlaceIndex<inPlaceIndex>, A&&... args)
      CDS_ATTR(noexcept(noexcept(H(cds::forward<A>(args)...)))) :
      _tail{InPlaceIndex<inPlaceIndex - 1>{}, cds::forward<A>(args)...} {}

  char _valueless;
  H _head;
  UnionStorage<UnionFunctionDetail::NonTrivial, T...> _tail;
  CDS_ATTR(constexpr(20)) ~UnionStorage() noexcept {}
};

template <typename H, typename... T> union UnionStorage<UnionFunctionDetail::Deleted, H, T...> {
  CDS_ATTR(2(explicit, constexpr(11))) UnionStorage(CDS_ATTR(unused) Valueless) noexcept : _valueless{} {}

  template <typename... A> CDS_ATTR(2(explicit, constexpr(11)))
  UnionStorage(CDS_ATTR(unused) InPlaceIndex<0>, A&&... args)
      CDS_ATTR(noexcept(noexcept(H(cds::forward<A>(args)...)))) : _head{cds::forward<A>(args)...} {}

  template <Size inPlaceIndex, typename... A> CDS_ATTR(2(explicit, constexpr(11)))
  UnionStorage(CDS_ATTR(unused) InPlaceIndex<inPlaceIndex>, A&&... args)
      CDS_ATTR(noexcept(noexcept(H(cds::forward<A>(args)...)))) :
      _tail{InPlaceIndex<inPlaceIndex - 1>{}, cds::forward<A>(args)...} {}

  char _valueless;
  H _head;
  UnionStorage<UnionFunctionDetail::NonTrivial, T...> _tail;
  CDS_ATTR(constexpr(20)) ~UnionStorage() noexcept = delete;
};

template <typename Req> using UnionActiveIndex = Conditional<
    Lt<Req, limits::MaxOf<U8>>, limits::MaxOf<U8>, Conditional<
        Lt<Req, limits::MaxOf<U16>>, limits::MaxOf<U16>, Conditional<
            Lt<Req, limits::MaxOf<U32>>, limits::MaxOf<U32>, limits::MaxOf<U64>
        >
    >
>;

constexpr auto valuelessIndex = limits::u64Max;

template <UnionFunctionDetail, typename> struct UnionStorageBase {};
template <UnionFunctionDetail detail, typename... Types> struct UnionStorageBase<detail, Pack<Types...>> {
  using Index = UnionActiveIndex<Int<sizeof...(Types)>>;
  using Data = UnionStorage<detail, Types...>;

  CDS_ATTR(2(explicit, constexpr(11))) UnionStorageBase(Valueless tag) noexcept :
      _data{tag}, _index{Index::value} {}

  template <Size index, typename... A> CDS_ATTR(2(explicit, constexpr(11)))
  UnionStorageBase(InPlaceIndex<index> inPlaceIndex, A&&... args)
      CDS_ATTR(noexcept(noexcept(Data{inPlaceIndex, cds::forward<A>(args)...}))) :
      _data{inPlaceIndex, cds::forward<A>(args)...}, _index{index} {}

  CDS_ATTR(2(nodiscard, constexpr(11))) auto index() const noexcept -> Size {
    return valueless() ? valuelessIndex : static_cast<Size>(_index);
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto valueless() const noexcept -> bool {
    return _index == Index::value;
  }

  Data _data;
  typename Index::Type _index;
};

template <typename PackedTypes, UnionFunctionDetail = UnionDetails<PackedTypes>::dtr> struct UnionDestructionBase {};
template <typename PackedTypes> struct UnionDestructionBase<PackedTypes, UnionFunctionDetail::Trivial> :
    UnionStorageBase<UnionFunctionDetail::Trivial, PackedTypes> {
  using Base = UnionStorageBase<UnionFunctionDetail::Trivial, PackedTypes>;
  using typename Base::Index;
  using Base::_index;
  using Base::Base;

  ~UnionDestructionBase() noexcept = default;
  CDS_ATTR(constexpr(14)) auto destroy() noexcept -> void {
    _index = Index::value;
  }
};

template <typename PackedTypes> struct UnionDestructionBase<PackedTypes, UnionFunctionDetail::Deleted> :
    UnionStorageBase<UnionFunctionDetail::Deleted, PackedTypes> {
  using Base = UnionStorageBase<UnionFunctionDetail::Deleted, PackedTypes>;
  using Base::Base;
  ~UnionDestructionBase() = delete;
  auto destroy() noexcept -> void = delete;
};

template <Size, typename... T> struct GetUnionTypeImpl;
template <typename H, typename... T> struct GetUnionTypeImpl<0, H, T...> {
  using Type = H;
};

template <Size s, typename H, typename... T> struct GetUnionTypeImpl<s, H, T...> {
  using Type = typename GetUnionTypeImpl<s - 1, T...>::Type;
};

template <Size> struct GetUnionData;

template <> struct GetUnionData<0> {
  template <UnionFunctionDetail d, typename H, typename... T>
  CDS_ATTR(2(nodiscard, constexpr(11))) auto operator()(UnionStorage<d, H, T...> const& data) const noexcept
      -> H const& {
    return data._head;
  }
  template <UnionFunctionDetail d, typename H, typename... T>
  CDS_ATTR(2(nodiscard, constexpr(11))) auto operator()(UnionStorage<d, H, T...>& data) const noexcept
      -> H& {
    return data._head;
  }
  template <UnionFunctionDetail d, typename H, typename... T>
  CDS_ATTR(2(nodiscard, constexpr(11))) auto operator()(UnionStorage<d, H, T...>&& data) const noexcept
      -> H&& {
    return cds::move(data._head);
  }
};

template <Size idx> struct GetUnionData {
  template <UnionFunctionDetail d, typename H, typename... T>
  CDS_ATTR(2(nodiscard, constexpr(11))) auto operator()(UnionStorage<d, H, T...> const& data) const noexcept
      -> decltype(GetUnionData<idx - 1>()(data._tail)) {
    return GetUnionData<idx - 1>()(data._tail);
  }
  template <UnionFunctionDetail d, typename H, typename... T>
  CDS_ATTR(2(nodiscard, constexpr(11))) auto operator()(UnionStorage<d, H, T...>& data) const noexcept
      -> decltype(GetUnionData<idx - 1>()(data._tail)) {
    return GetUnionData<idx - 1>()(data._tail);
  }
  template <UnionFunctionDetail d, typename H, typename... T>
  CDS_ATTR(2(nodiscard, constexpr(11))) auto operator()(UnionStorage<d, H, T...>&& data) const noexcept
      -> decltype(GetUnionData<idx - 1>()(cds::move(data._tail))) {
    return GetUnionData<idx - 1>()(cds::move(data._tail));
  }
};

template <Size...> struct IndexSequence {};

template <Size h, Size... t> struct IndexSequenceImpl {
  using Type = typename IndexSequenceImpl <h - 1, h - 1, t...>::Type;
};

template <Size... s> struct IndexSequenceImpl<0u, s...> {
  using Type = IndexSequence <s...>;
};

template <Size size> using MakeIndexSequence = typename IndexSequenceImpl<size>::Type;

template <typename T, Size s> struct ArrayWr {
  T buf[s] = {};
  constexpr T const& operator[](Size idx) const noexcept { return buf[idx]; }
};

template <template <Size> class, typename> struct FunctionalVisitorTableImpl {};
template <template <Size> class F, Size... is> struct FunctionalVisitorTableImpl<F, IndexSequence<is...>> {
  // TODO: Check for discrepancies in arg types in All<Decay<F::visit>>
  template <typename... InvokeArgs>
  struct Table {

    // ODR Variant
    static constexpr Common<Decay<decltype(F<is>::template visit<InvokeArgs...>)>...> table[sizeof...(is)] = {
        F<is>::template visit<InvokeArgs...>...
    };

    // Non-ODR variant, cpp-11 unfriendly?
    // using Type = ArrayWr<Common<Decay<decltype(F<is>::template visit<InvokeArgs...>)>...>, sizeof...(is)>;
    // static constexpr Type makeTable() noexcept {
      // return Type{{F<is>::template visit<InvokeArgs...>...}};
    // }
  };
};

// ODR before cpp17
template <template <Size> class F, Size... is>
template <typename... InvokeArgs>
Common<Decay<decltype(F<is>::template visit<InvokeArgs...>)>...> const
FunctionalVisitorTableImpl<F, IndexSequence<is...>>::Table<InvokeArgs...>::table[sizeof...(is)];


template <template <Size> class F, Size size> struct FunctionalVisitorTable :
    FunctionalVisitorTableImpl<F, MakeIndexSequence<size>> {};

// template <Size idx, UnionFunctionDetail d, typename H, typename... T> CDS_ATTR(constexpr(14))
// auto unionDestroyVisitor(UnionStorage<d, H, T...>& data) noexcept -> void {
//   using Type = typename GetUnionType<idx, H, T...>::Type;
//   GetUnionData<idx>()(data).~Type();
// }

// template <Size idx> struct UnionGenericVisitor {
//    template <typename Visitor, UnionFunctionDetail d, typename... T> CDS_ATTR(constexpr(11))
//    static auto visit(Visitor&& visitor, UnionStorage<d, T...>& data) noexcept ->
//        meta::InvokeReturnOf<Visitor, UnionStorage<d, T...>&> {
//      return functional::invoke(cds::forward<Visitor>(visitor), data);
//    }
// };

template <Size, typename> struct GetUnionTypeImpl2 {};
template <Size idx, UnionFunctionDetail d, typename... T> struct GetUnionTypeImpl2<idx, UnionStorage<d, T...>> :
    GetUnionTypeImpl<idx, T...> {};

template <Size idx, typename T> using GetUnionType = typename GetUnionTypeImpl2<idx, RemoveCVRef<T>>::Type;

template <Size idx> struct UnionDestroyVisitor {
  template <typename Union> CDS_ATTR(constexpr(14)) static auto visit(Union& storage) noexcept -> void {
    using Type = GetUnionType<idx, Union>;
    GetUnionData<idx>()(storage).~Type();
  }
};

template <typename I, UnionFunctionDetail d, typename... T> CDS_ATTR(constexpr(14))
auto unionDestroy(I idx, UnionStorage<d, T...>& data) noexcept -> void {
  // Non-ODR-variant
  // constexpr auto table =
      // FunctionalVisitorTable<UnionDestroyVisitor, sizeof...(T)>::template Table<UnionStorage<d, T...>&>::makeTable();
  // return table[idx](data);

  // ODR-variant
  return FunctionalVisitorTable<UnionDestroyVisitor, sizeof...(T)>::
      template Table<UnionStorage<d, T...>&>::table[idx](data);
}

// template <Size idx> struct UnionConstructVisitor {
//   template <typename Union, typename... A>
//   CDS_ATTR(constexpr(14)) static auto visit(Union& storage, A&&... args)
//       CDS_ATTR(noexcept(noexcept(GetUnionType<idx, Union>{cds::forward<A>(args)...}))) -> void {
//     ignore = construct(&GetUnionData<idx>()(storage), cds::forward<A>(args)...);
//   }
// };
//
template <Size idx> struct UnionConstructVisitor {
  template <typename Union, typename A>
  CDS_ATTR(constexpr(14)) static auto visit(Union& storage, A&& otherStorage)
      /* CDS_ATTR(noexcept(noexcept(RemoveCVRef<GetUnionType<idx, Union>>{GetUnionData<idx>()(cds::forward<A>(otherStorage))}))) */ -> void {
    ignore = construct(&GetUnionData<idx>()(storage), GetUnionData<idx>()(cds::forward<A>(otherStorage)));
  }
};
//
// template <typename I, UnionFunctionDetail d, typename... T, typename... A> CDS_ATTR(constexpr(14))
// auto unionConstruct(I idx, UnionStorage<d, T...>& data, A&&... args) CDS_ATTR(noexcept(noexcept(
//     // somehow I do not trust this.
//     FunctionalVisitorTable<UnionConstructVisitor, sizeof...(T)>::
//         template Table<UnionStorage<d, T...>&, A&&...>::makeTable()[idx](data, cds::forward<A>(args)...)
// ))) -> void {
//   constexpr auto table =
//       FunctionalVisitorTable<UnionConstructVisitor, sizeof...(T)>::
//           template Table<UnionStorage<d, T...>&, A&&...>::makeTable();
//   return table[idx](data, cds::forward<A>(args)...);
// }
//
template <typename I, UnionFunctionDetail d, typename... T, typename A> CDS_ATTR(constexpr(14))
auto unionConstruct(I idx, UnionStorage<d, T...>& data, A&& other) /* CDS_ATTR(noexcept(noexcept(
    // false
    // somehow I do not trust this.
    // FunctionalVisitorTable<UnionConstructVisitor, sizeof...(T)>::
    // template Table<UnionStorage<d, T...>&, A&&>::makeTable()[idx](data, cds::forward<A>(other))
))) */ -> void {
  // constexpr auto table =
  //     FunctionalVisitorTable<UnionConstructVisitor, sizeof...(T)>::
  //         template Table<UnionStorage<d, T...>&, A&&>::makeTable();
  // return table[idx](data, cds::forward<A>(other));

  // ODR-variant
  return FunctionalVisitorTable<UnionConstructVisitor, sizeof...(T)>::
      template Table<UnionStorage<d, T...>&, A&&>::table[idx](data, cds::forward<A>(other));
}

template <Size idx> struct UnionAssignVisitor {
  template <typename Union, typename A>
  CDS_ATTR(constexpr(14)) static auto visit(Union& storage, A&& otherStorage) -> void {
    GetUnionData<idx>()(storage) = GetUnionData<idx>()(cds::forward<A>(otherStorage));
  }
};

template <typename I, UnionFunctionDetail d, typename... T, typename A> CDS_ATTR(constexpr(14))
auto unionAssign(I idx, UnionStorage<d, T...>& data, A&& other) -> void {
  return FunctionalVisitorTable<UnionAssignVisitor, sizeof...(T)>::
      template Table<UnionStorage<d, T...>&, A&&>::table[idx](data, cds::forward<A>(other));
}

template <typename PackedTypes> struct UnionDestructionBase<PackedTypes, UnionFunctionDetail::NonTrivial> :
    UnionStorageBase<UnionFunctionDetail::NonTrivial, PackedTypes> {
  using Base = UnionStorageBase<UnionFunctionDetail::NonTrivial, PackedTypes>;
  using typename Base::Index;
  using Base::_index;
  using Base::_data;
  using Base::valueless;
  using Base::Base;

  CDS_ATTR(constexpr(20)) ~UnionDestructionBase() noexcept {
    destroy();
  }

  CDS_ATTR(constexpr(14)) auto destroy() noexcept -> void {
    if (valueless()) {
      return;
    }

    unionDestroy(cds::exchange(_index, Index::value), _data);
  }
};

template <typename> struct UnionConstructionBase;
template <typename... Types> struct UnionConstructionBase<Pack<Types...>> : UnionDestructionBase<Pack<Types...>> {
  using Base = UnionDestructionBase<Pack<Types...>>;
  using Base::Base;
  using typename Base::Index;
  using Base::destroy;
  using Base::valueless;
  using Base::_data;
  using Base::_index;

  template <typename A> CDS_ATTR(constexpr(14)) auto constructFromUnion(A&& otherUnion)
      /* CDS_ATTR(noexcept(noexcept(unionConstruct(this->_index, this->_data, cds::forward<A>(otherUnion))))) */
      -> void {
    destroy();
    if (otherUnion.valueless()) {
      return;
    }

    unionConstruct(otherUnion.index(), _data, cds::forward<A>(otherUnion)._data);
    _index = otherUnion.index();
  }

  template <Size idx, typename... A> CDS_ATTR(constexpr(14)) auto emplace(A&&... args)
      -> typename GetUnionTypeImpl<idx, Types...>::Type {
    destroy();
    auto& data = *construct(&GetUnionData<idx>()(_data), cds::forward<A>(args)...);
    _index = idx;
    return data;
  }
};

template <typename> struct UnionAssignmentBase {};
template <typename... Types> struct UnionAssignmentBase<Pack<Types...>> : UnionConstructionBase<Pack<Types...>> {
  using Base = UnionConstructionBase<Pack<Types...>>;
  using Base::Base;
  using Base::index;
  using Base::valueless;
  using Base::destroy;
  using Base::_data;
  using Base::_index;

  template <typename A> CDS_ATTR(constexpr(14)) auto assignFromUnion(A&& otherUnion) -> void {
    if (valueless() == otherUnion.valueless()) {
      return;
    }

    if (otherUnion.valueless()) {
      return;
    }

    if (index() == otherUnion.index()) {
      unionAssign(otherUnion.index(), _data, otherUnion._data);
      return;
    }

    if (index() != otherUnion.index()) {
      destroy();
    }

    unionConstruct(otherUnion.index(), _data, otherUnion._data);
    _index = otherUnion.index();
  }

  // Implement bestmatch from oldver
  // template <typename A> CDS_ATTR(constexpr(14)) auto assign(A&& value) ->
};

template <typename PackedTypes, UnionFunctionDetail = UnionDetails<PackedTypes>::copyCtr>
struct UnionCopyConstructionBase {};

template <typename PackedTypes> struct UnionCopyConstructionBase<PackedTypes, UnionFunctionDetail::Trivial> :
    UnionAssignmentBase<PackedTypes> {
  using Base = UnionAssignmentBase<PackedTypes>;
  using Base::Base;

  UnionCopyConstructionBase(UnionCopyConstructionBase const&) = default;
  UnionCopyConstructionBase(UnionCopyConstructionBase&&) = default;
  auto operator=(UnionCopyConstructionBase const&) -> UnionCopyConstructionBase& = default;
  auto operator=(UnionCopyConstructionBase&&) -> UnionCopyConstructionBase& = default;
  ~UnionCopyConstructionBase() = default;
};

template <typename PackedTypes> struct UnionCopyConstructionBase<PackedTypes, UnionFunctionDetail::Deleted> :
    UnionAssignmentBase<PackedTypes> {
  using Base = UnionAssignmentBase<PackedTypes>;
  using Base::Base;

  UnionCopyConstructionBase(UnionCopyConstructionBase const&) = delete;
  UnionCopyConstructionBase(UnionCopyConstructionBase&&) = default;
  auto operator=(UnionCopyConstructionBase const&) -> UnionCopyConstructionBase& = default;
  auto operator=(UnionCopyConstructionBase&&) -> UnionCopyConstructionBase& = default;
  ~UnionCopyConstructionBase() = default;
};

template <typename... Types> struct UnionCopyConstructionBase<Pack<Types...>, UnionFunctionDetail::NonTrivial> :
    UnionAssignmentBase<Pack<Types...>> {
  using Base = UnionAssignmentBase<Pack<Types...>>;
  using Base::Base;
  using Base::constructFromUnion;

  CDS_ATTR(constexpr(14)) UnionCopyConstructionBase(UnionCopyConstructionBase const& other)
      CDS_ATTR(noexcept(All<IsNoexceptCopyConstructible, Types...>::value)) : Base{Valueless{}} {
    constructFromUnion(other);
  }

  UnionCopyConstructionBase(UnionCopyConstructionBase&&) = default;
  auto operator=(UnionCopyConstructionBase const&) -> UnionCopyConstructionBase& = default;
  auto operator=(UnionCopyConstructionBase&&) -> UnionCopyConstructionBase& = default;
  ~UnionCopyConstructionBase() = default;
};

template <typename PackedTypes, UnionFunctionDetail = UnionDetails<PackedTypes>::moveCtr>
struct UnionMoveConstructionBase;

template <typename PackedTypes> struct UnionMoveConstructionBase<PackedTypes, UnionFunctionDetail::Trivial> :
    UnionCopyConstructionBase<PackedTypes> {
  using Base = UnionCopyConstructionBase<PackedTypes>;
  using Base::Base;

  UnionMoveConstructionBase(UnionMoveConstructionBase const&) = default;
  UnionMoveConstructionBase(UnionMoveConstructionBase&&) = default;
  auto operator=(UnionMoveConstructionBase const&) -> UnionMoveConstructionBase& = default;
  auto operator=(UnionMoveConstructionBase&&) -> UnionMoveConstructionBase& = default;
  ~UnionMoveConstructionBase() = default;
};

template <typename PackedTypes> struct UnionMoveConstructionBase<PackedTypes, UnionFunctionDetail::Deleted> :
    UnionCopyConstructionBase<PackedTypes> {
  using Base = UnionCopyConstructionBase<PackedTypes>;
  using Base::Base;

  UnionMoveConstructionBase(UnionMoveConstructionBase const&) = default;
  UnionMoveConstructionBase(UnionMoveConstructionBase&&) = delete;
  auto operator=(UnionMoveConstructionBase const&) -> UnionMoveConstructionBase& = default;
  auto operator=(UnionMoveConstructionBase&&) -> UnionMoveConstructionBase& = default;
  ~UnionMoveConstructionBase() = default;
};

template <typename... Types> struct UnionMoveConstructionBase<Pack<Types...>, UnionFunctionDetail::NonTrivial> :
    UnionCopyConstructionBase<Pack<Types...>> {
  using Base = UnionCopyConstructionBase<Pack<Types...>>;
  using Base::Base;
  using Base::constructFromUnion;

  UnionMoveConstructionBase(UnionMoveConstructionBase const&) = default;

  CDS_ATTR(constexpr(14)) UnionMoveConstructionBase(UnionMoveConstructionBase&& other)
      CDS_ATTR(noexcept(All<IsNoexceptMoveConstructible, Types...>::value)) : Base{Valueless{}} {
    constructFromUnion(cds::move(other));
  }

  auto operator=(UnionMoveConstructionBase const&) -> UnionMoveConstructionBase& = default;
  auto operator=(UnionMoveConstructionBase&&) -> UnionMoveConstructionBase& = default;
  ~UnionMoveConstructionBase() = default;
};

template <typename PackedTypes, UnionFunctionDetail = UnionDetails<PackedTypes>::copyAssign>
struct UnionCopyAssignmentBase;

template <typename PackedTypes> struct UnionCopyAssignmentBase<PackedTypes, UnionFunctionDetail::Trivial> :
    UnionMoveConstructionBase<PackedTypes> {
  using Base = UnionMoveConstructionBase<PackedTypes>;
  using Base::Base;

  UnionCopyAssignmentBase(UnionCopyAssignmentBase const&) = default;
  UnionCopyAssignmentBase(UnionCopyAssignmentBase&&) = default;
  auto operator=(UnionCopyAssignmentBase const&) -> UnionCopyAssignmentBase& = default;
  auto operator=(UnionCopyAssignmentBase&&) -> UnionCopyAssignmentBase& = default;
  ~UnionCopyAssignmentBase() = default;
};

template <typename PackedTypes> struct UnionCopyAssignmentBase<PackedTypes, UnionFunctionDetail::Deleted> :
    UnionMoveConstructionBase<PackedTypes> {
  using Base = UnionMoveConstructionBase<PackedTypes>;
  using Base::Base;

  UnionCopyAssignmentBase(UnionCopyAssignmentBase const&) = default;
  UnionCopyAssignmentBase(UnionCopyAssignmentBase&&) = default;
  auto operator=(UnionCopyAssignmentBase const&) -> UnionCopyAssignmentBase& = delete;
  auto operator=(UnionCopyAssignmentBase&&) -> UnionCopyAssignmentBase& = default;
  ~UnionCopyAssignmentBase() = default;
};

template <typename... Types> struct UnionCopyAssignmentBase<Pack<Types...>, UnionFunctionDetail::NonTrivial> :
    UnionMoveConstructionBase<Pack<Types...>> {
  using Base = UnionMoveConstructionBase<Pack<Types...>>;
  using Base::Base;
  using Base::assignFromUnion;

  UnionCopyAssignmentBase(UnionCopyAssignmentBase const&) = default;
  UnionCopyAssignmentBase(UnionCopyAssignmentBase&&) = default;

  CDS_ATTR(constexpr(14)) auto operator=(UnionCopyAssignmentBase const& other) CDS_ATTR(noexcept(And<
      All<IsNoexceptCopyConstructible, Types...>,
      All<IsNoexceptCopyAssignable, Types...>
  >::value)) -> UnionCopyAssignmentBase& {
    if (this == &other) {
      return *this;
    }

    assignFromUnion(other);
    return *this;
  }

  auto operator=(UnionCopyAssignmentBase&&) -> UnionCopyAssignmentBase& = default;
  ~UnionCopyAssignmentBase() = default;
};

template <typename PackedTypes, UnionFunctionDetail = UnionDetails<PackedTypes>::moveAssign>
struct UnionMoveAssignmentBase;

template <typename PackedTypes> struct UnionMoveAssignmentBase<PackedTypes, UnionFunctionDetail::Trivial> :
    UnionCopyAssignmentBase<PackedTypes> {
  using Base = UnionCopyAssignmentBase<PackedTypes>;
  using Base::Base;

  UnionMoveAssignmentBase(UnionMoveAssignmentBase const&) = default;
  UnionMoveAssignmentBase(UnionMoveAssignmentBase&&) = default;
  auto operator=(UnionMoveAssignmentBase const&) -> UnionMoveAssignmentBase& = default;
  auto operator=(UnionMoveAssignmentBase&&) -> UnionMoveAssignmentBase& = default;
  ~UnionMoveAssignmentBase() = default;
};

template <typename PackedTypes> struct UnionMoveAssignmentBase<PackedTypes, UnionFunctionDetail::Deleted> :
    UnionCopyAssignmentBase<PackedTypes> {
  using Base = UnionCopyAssignmentBase<PackedTypes>;
  using Base::Base;

  UnionMoveAssignmentBase(UnionMoveAssignmentBase const&) = default;
  UnionMoveAssignmentBase(UnionMoveAssignmentBase&&) = default;
  auto operator=(UnionMoveAssignmentBase const&) -> UnionMoveAssignmentBase& = default;
  auto operator=(UnionMoveAssignmentBase&&) -> UnionMoveAssignmentBase& = delete;
  ~UnionMoveAssignmentBase() = default;
};

template <typename... Types> struct UnionMoveAssignmentBase<Pack<Types...>, UnionFunctionDetail::NonTrivial> :
    UnionCopyAssignmentBase<Pack<Types...>> {
  using Base = UnionCopyAssignmentBase<Pack<Types...>>;
  using Base::Base;
  using Base::assignFromUnion;

  UnionMoveAssignmentBase(UnionMoveAssignmentBase const&) = default;
  UnionMoveAssignmentBase(UnionMoveAssignmentBase&&) = default;
  auto operator=(UnionMoveAssignmentBase const&) -> UnionMoveAssignmentBase& = default;

  CDS_ATTR(constexpr(14)) auto operator=(UnionMoveAssignmentBase&& other) CDS_ATTR(noexcept(And<
      All<IsNoexceptMoveConstructible, Types...>,
      All<IsNoexceptMoveAssignable, Types...>
  >::value)) -> UnionMoveAssignmentBase& {
    if (this == &other) {
      return *this;
    }

    assignFromUnion(cds::move(other));
    return *this;
  }

  ~UnionMoveAssignmentBase() = default;
};
} // namespace unionImpl
} // namespace impl
} // namespace cds

#endif // CDS_PRIMITIVE_UNION_NODE_V2_HPP
