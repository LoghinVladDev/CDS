//
// Created by loghin on 9/18/24.
//

#ifndef CDS_PRIMITIVE_UNION_NODE_HPP
#define CDS_PRIMITIVE_UNION_NODE_HPP
#pragma once

#include <cds/Optional>
#include <cds/exception/UnionTypeException>

#include "UnionDecl.hpp"

CDS_ATTR(disable_warning(gcc, "-Wterminate"))
CDS_ATTR(disable_warning(msvc, 4297))

namespace cds {
namespace impl {
namespace unionImpl {
using meta::Any;
using meta::All;
using meta::And;
using meta::Conditional;
using meta::Common;
using meta::False;
using meta::IndexSequence;
using meta::Integral;
using meta::IsAssignable;
using meta::IsCopyAssignable;
using meta::IsCopyConstructible;
using meta::IsDefaultConstructible;
using meta::IsDestructible;
using meta::IsMoveAssignable;
using meta::IsMoveConstructible;
using meta::IsNoexceptAssignable;
using meta::IsNoexceptConstructible;
using meta::IsNoexceptCopyAssignable;
using meta::IsNoexceptCopyConstructible;
using meta::IsNoexceptInvocable;
using meta::IsNoexceptMoveAssignable;
using meta::IsNoexceptMoveConstructible;
using meta::IsSame;
using meta::IsSameIgnoringCVRef;
using meta::IsTriviallyCopyAssignable;
using meta::IsTriviallyCopyConstructible;
using meta::IsTriviallyDefaultConstructible;
using meta::IsTriviallyDestructible;
using meta::IsTriviallyMoveAssignable;
using meta::IsTriviallyMoveConstructible;
using meta::Lt;
using meta::MakeIndexSequence;
using meta::True;

using meta::impl::NonDecayedCommon;
using meta::IsBaseOf;
using meta::impl::IsBaseOfIntrusiveICVR;
using meta::impl::Pack;

template <typename Req> using UnionActiveIndex = Conditional<
    Lt<Req, limits::MaxOf<U8>>, limits::MaxOf<U8>, Conditional<
        Lt<Req, limits::MaxOf<U16>>, limits::MaxOf<U16>, Conditional<
            Lt<Req, limits::MaxOf<U32>>, limits::MaxOf<U32>, limits::MaxOf<U64>
        >
    >
>;

constexpr auto valuelessIndex = limits::u64Max;

namespace bm {
template <template <typename, typename> class, Size, typename, typename> struct Best {
  // purposefully empty
};

template <template <typename, typename> class Matcher, Size idx, typename A> struct Best<Matcher, idx, A, Pack<>> {
  // purposefully empty
};

template <template <typename, typename> class Matcher, Size idx, typename A, typename T> struct Current :
    Integral<Size, idx> {
  struct IsIdeal : IsSame<A, T> {};
  struct IsMatching : Matcher<T, A> {};
};

template <template <typename, typename> class Matcher, Size idx, typename A, typename H>
struct Best<Matcher, idx, A, Pack<H>> : Current<Matcher, idx, A, H> {
  using typename Current<Matcher, idx, A, H>::IsIdeal;
  using typename Current<Matcher, idx, A, H>::IsMatching;
  struct Considered : Or<IsIdeal, IsMatching> {};
  using Type = Conditional<Considered, H, void>;
  constexpr static auto index = Considered::value ? idx : UnionActiveIndex<Integral<Size, idx>>::value;
};

template <template <typename, typename> class Matcher, Size idx, typename A, typename H, typename... T>
struct Best<Matcher, idx, A, Pack<H, T...>> : Current<Matcher, idx, A, H> {
  using typename Current<Matcher, idx, A, H>::IsIdeal;
  using typename Current<Matcher, idx, A, H>::IsMatching;
  template<typename InTail>
  struct IdealWithGiven : IsSame<A, InTail> {};
  struct AnyIdealAhead : Any<IdealWithGiven, T...> {};
  using Tail = Best<Matcher, idx + 1u, A, Pack<T...>>;
  struct Considered : Or<IsIdeal, And<Not<AnyIdealAhead>, IsMatching>> {};
  using Type = Conditional<Considered, H, typename Tail::Type>;
  constexpr static Size index = Considered::value ? idx : Tail::index;
};

template <Size, typename, typename> struct BestConstructible {
  // purposefully empty
};

template <Size idx, typename A> struct BestConstructible<idx, A, Pack<>> {
  // purposefully empty
};

template <Size, typename, typename> struct CurrentConstructible {};

template <Size idx, typename... A, typename T> struct CurrentConstructible<idx, Pack<A...>, T> : Integral<Size, idx> {
  struct IsIdeal : IsConstructible<T, A...> {};
};

template <Size idx, typename ArgPack, typename H> struct BestConstructible<idx, ArgPack, Pack<H>> :
    CurrentConstructible<idx, ArgPack, H> {
  using typename CurrentConstructible<idx, ArgPack, H>::IsIdeal;
  using Type = Conditional<IsIdeal, H, void>;
  constexpr static auto index = IsIdeal::value ? idx : UnionActiveIndex<Integral<Size, idx>>::value;
};

template <Size idx, typename ArgPack, typename H, typename... T>
struct BestConstructible<idx, ArgPack, Pack<H, T...>> : CurrentConstructible<idx, ArgPack, H> {
  using typename CurrentConstructible<idx, ArgPack, H>::IsIdeal;
  using Tail = BestConstructible<idx + 1, ArgPack, Pack<T...>>;
  using Type = Conditional<IsIdeal, H, typename Tail::Type>;
  constexpr static auto index = IsIdeal::value ? idx : Tail::index;
};
} // namespace bm

struct Valueless {
};

template <Size> struct InPlaceIndex {};

template <typename> struct IsNotInPlaceIndex : True {};

template <Size idx> struct IsNotInPlaceIndex<InPlaceIndex<idx>> : False {};

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

template <template <typename, typename> class Matcher, typename A, typename... T>
struct UnionBestMatch : bm::Best<Matcher, 0u, A, Pack<RemoveCVRef<T>...>> {};

template <template <typename, typename> class Matcher, typename A, typename... T>
using UnionBestMatchType = typename UnionBestMatch<Matcher, A, T...>::Type;

template <template <typename, typename> class Matcher, typename A, typename... T>
using UnionBestMatchIndex = Integral<Size, UnionBestMatch<Matcher, A, T...>::index>;

template <typename ArgPack, typename... T>
struct UnionBestConstructible : bm::BestConstructible<0u, ArgPack, Pack<RemoveCVRef<T>...>> {};

template <typename ArgPack, typename... T>
using UnionBestConstructibleType = typename UnionBestConstructible<ArgPack, T...>::Type;

template <typename ArgPack, typename... T>
using UnionBestConstructibleIndex = Integral<Size, UnionBestConstructible<ArgPack, T...>::index>;

template <typename T, typename A>
struct IsConstructibleAndAssignable : And<IsConstructible<T, A>, IsAssignable<T, A>> {};

template <typename T, typename A> struct IsConstructibleSingleArg : IsConstructible<T, A> {};

template <typename> struct UnionDetails {};

template <typename... Types> struct UnionDetails<Pack<Types...>> : UnpackedUnionDetails<Types...> {};

template <UnionFunctionDetail, typename...> union UnionStorage {};

template <UnionFunctionDetail detail> union UnionStorage<detail> {};

template <typename H, typename... T> union UnionStorage<UnionFunctionDetail::Trivial, H, T...> {
  using Tail = UnionStorage<UnionFunctionDetail::Trivial, T...>;

  CDS_ATTR(2(explicit, constexpr(11))) UnionStorage(CDS_ATTR(unused) Valueless) noexcept: _valueless{} {}

  // Use brackets instead of braces, arrows implicit conversions
  template <typename... A> CDS_ATTR(2(explicit, constexpr(11)))
  UnionStorage(CDS_ATTR(unused) InPlaceIndex<0>, A &&... args)
      CDS_ATTR(noexcept(noexcept(H(cds::forward<A>(args)...)))) : _head(cds::forward<A>(args)...) {}

  template <Size inPlaceIndex, typename... A> CDS_ATTR(2(explicit, constexpr(11)))
  UnionStorage(CDS_ATTR(unused) InPlaceIndex<inPlaceIndex>, A &&... args)
      CDS_ATTR(noexcept(noexcept(Tail{InPlaceIndex<inPlaceIndex - 1>{}, cds::forward<A>(args)...}))) :
      _tail{InPlaceIndex<inPlaceIndex - 1>{}, cds::forward<A>(args)...} {}

  ~UnionStorage() noexcept = default;

  char _valueless;
  H _head;
  Tail _tail;
};

template <typename H, typename... T> union UnionStorage<UnionFunctionDetail::NonTrivial, H, T...> {
  using Tail = UnionStorage<UnionFunctionDetail::NonTrivial, T...>;

  CDS_ATTR(2(explicit, constexpr(11))) UnionStorage(CDS_ATTR(unused) Valueless) noexcept: _valueless{} {}

  // Use brackets instead of braces, arrows implicit conversions
  template <typename... A> CDS_ATTR(2(explicit, constexpr(11)))
  UnionStorage(CDS_ATTR(unused) InPlaceIndex<0>, A &&... args)
      CDS_ATTR(noexcept(noexcept(H(cds::forward<A>(args)...)))) : _head(cds::forward<A>(args)...) {}

  template <Size inPlaceIndex, typename... A> CDS_ATTR(2(explicit, constexpr(11)))
  UnionStorage(CDS_ATTR(unused) InPlaceIndex<inPlaceIndex>, A &&... args)
      CDS_ATTR(noexcept(noexcept(Tail{InPlaceIndex<inPlaceIndex - 1>{}, cds::forward<A>(args)...}))) :
      _tail{InPlaceIndex<inPlaceIndex - 1>{}, cds::forward<A>(args)...} {}

  CDS_ATTR(constexpr(20)) ~UnionStorage() noexcept {}

  char _valueless;
  H _head;
  Tail _tail;
};

template <typename H, typename... T> union UnionStorage<UnionFunctionDetail::Deleted, H, T...> {
  using Tail = UnionStorage<UnionFunctionDetail::Deleted, T...>;

  CDS_ATTR(2(explicit, constexpr(11))) UnionStorage(CDS_ATTR(unused) Valueless) noexcept: _valueless{} {}

  // Use brackets instead of braces, arrows implicit conversions
  template <typename... A> CDS_ATTR(2(explicit, constexpr(11)))
  UnionStorage(CDS_ATTR(unused) InPlaceIndex<0>, A &&... args)
      CDS_ATTR(noexcept(noexcept(H(cds::forward<A>(args)...)))) : _head(cds::forward<A>(args)...) {}

  template <Size inPlaceIndex, typename... A> CDS_ATTR(2(explicit, constexpr(11)))
  UnionStorage(CDS_ATTR(unused) InPlaceIndex<inPlaceIndex>, A &&... args)
      CDS_ATTR(noexcept(noexcept(Tail{InPlaceIndex<inPlaceIndex - 1>{}, cds::forward<A>(args)...}))) :
      _tail{InPlaceIndex<inPlaceIndex - 1>{}, cds::forward<A>(args)...} {}

  CDS_ATTR(constexpr(20)) ~UnionStorage() noexcept = delete;

  char _valueless;
  H _head;
  Tail _tail;
};

template <Size, typename... T> struct GetUnionTypeImpl;

template <typename H, typename... T> struct GetUnionTypeImpl<0, H, T...> {
  using Type = H;
};

template <Size s, typename H, typename... T> struct GetUnionTypeImpl<s, H, T...> {
  using Type = typename GetUnionTypeImpl<s - 1, T...>::Type;
};

template <Size, typename> struct GetUnionTypeImpl2 {};

template <Size idx, UnionFunctionDetail d, typename... T> struct GetUnionTypeImpl2<idx, UnionStorage<d, T...>> :
    GetUnionTypeImpl<idx, T...> {};

template <Size idx, typename T> using GetUnionType = typename GetUnionTypeImpl2<idx, RemoveCVRef<T>>::Type;

template <unsigned> struct GetUnionData;

template <> struct GetUnionData<0> {
  template <UnionFunctionDetail d, typename H, typename... T> CDS_ATTR(2(nodiscard, constexpr(11)))
  auto operator()(UnionStorage<d, H, T...> const &data) const noexcept -> H const & {
    return data._head;
  }

  template <UnionFunctionDetail d, typename H, typename... T> CDS_ATTR(2(nodiscard, constexpr(11)))
  auto operator()(UnionStorage<d, H, T...> &data) const noexcept -> H & {
    return data._head;
  }

  template <UnionFunctionDetail d, typename H, typename... T> CDS_ATTR(2(nodiscard, constexpr(11)))
  auto operator()(UnionStorage<d, H, T...> &&data) const noexcept -> H && {
    return cds::move(data._head);
  }
};

template <unsigned idx> struct GetUnionData {
  template <UnionFunctionDetail d, typename H, typename... T> CDS_ATTR(2(nodiscard, constexpr(11)))
  auto operator()(UnionStorage<d, H, T...> const &data) const noexcept
      -> decltype(GetUnionData<idx - 1>()(data._tail)) {
    return GetUnionData<idx - 1>()(data._tail);
  }

  template <UnionFunctionDetail d, typename H, typename... T> CDS_ATTR(2(nodiscard, constexpr(11)))
  auto operator()(UnionStorage<d, H, T...> &data) const noexcept -> decltype(GetUnionData<idx - 1>()(data._tail)) {
    return GetUnionData<idx - 1>()(data._tail);
  }

  template <UnionFunctionDetail d, typename H, typename... T>
  CDS_ATTR(2(nodiscard, constexpr(11))) auto operator()(UnionStorage<d, H, T...> &&data) const noexcept
  -> decltype(GetUnionData<idx - 1>()(cds::move(data._tail))) {
    return GetUnionData<idx - 1>()(cds::move(data._tail));
  }
};


template <template <unsigned> class, typename> struct FunctionalVisitorTableImpl;
template <template <unsigned> class F, unsigned... is> struct FunctionalVisitorTableImpl<F, IndexSequence<is...>> {
  // TODO: Check for discrepancies in arg types in All<Decay<F::visit>>
  template<typename... InvokeArgs> struct Table {
    static constexpr Common<Decay<decltype(F<is>::template visit<InvokeArgs...>)>...> table[sizeof...(is)] = {
        F<is>::template visit<InvokeArgs...>...
    };
  };
};

template <template <unsigned> class F, unsigned size> struct FunctionalVisitorTable :
    FunctionalVisitorTableImpl<F, MakeIndexSequence<size>> {};

// ODR before cpp17
template <template <unsigned> class F, unsigned... is> template<typename... InvokeArgs>
Common<Decay<decltype(F<is>::template visit<InvokeArgs...>)>...> const
    FunctionalVisitorTableImpl<F, IndexSequence<is...>>::Table<InvokeArgs...>::table[sizeof...(is)];

template <unsigned idx> struct UnionDestroyVisitor {
  template <typename Union> CDS_ATTR(constexpr(14)) static auto visit(Union &storage) noexcept -> void {
    using Type = GetUnionType<idx, Union>;
    GetUnionData<idx>()(storage).~Type();
  }
};

template <unsigned idx> struct UnionConstructVisitor {
  template<typename Union, typename A>
  CDS_ATTR(constexpr(14)) static auto visit(Union &storage, A &&otherStorage) -> void {
    ignore = construct(&GetUnionData<idx>()(storage), GetUnionData<idx>()(cds::forward<A>(otherStorage)));
  }
};

template <unsigned idx> struct UnionAssignVisitor {
  template <typename Union, typename A>
  CDS_ATTR(constexpr(14)) static auto visit(Union &storage, A &&otherStorage) -> void {
    GetUnionData<idx>()(storage) = GetUnionData<idx>()(cds::forward<A>(otherStorage));
  }
};

// Effectively visits all union members and gives them the promised raises.
template <unsigned idx> struct UnionRaiseVisitor {
  template <typename AccessedType, typename Union>
  CDS_ATTR(constexpr(14)) static auto visit(CDS_ATTR(unused) Union const &) -> void {
    using StoredType = GetUnionType<idx, Union>;
    CDS_ATTR(throw (UnionTypeException::of<StoredType, AccessedType>()));
  }
};

template <unsigned idx> struct UnionGenericVisitor {
  template <typename R, typename Union, typename Visitor>
  CDS_ATTR(constexpr(14)) static auto visit(Union &&storage, Visitor &&visitor) -> R {
    return functional::invoke(
        cds::forward<Visitor>(visitor),
        GetUnionData<idx>()(cds::forward<Union>(storage))
    );
  }
};

template <unsigned idx> struct UnionCompareVisitor {
  template <typename C, typename Union>
  CDS_ATTR(constexpr(14)) static auto visit(Union const& storage, Union const& otherStorage) -> bool {
    return C{}(GetUnionData<idx>{}(storage), GetUnionData<idx>{}(otherStorage));
  }
};

#if CDS_ATTR(spaceship)
template <unsigned idx> struct UnionThreeWayVisitor {
  template <typename Union> CDS_ATTR(constexpr(14)) static auto visit(Union const& storage, Union const& otherStorage)
      -> decltype(GetUnionData<idx>{}(storage) <=> GetUnionData<idx>{}(otherStorage)) {
    return GetUnionData<idx>{}(storage) <=> GetUnionData<idx>{}(otherStorage);
  }
};
#endif

template <typename I, UnionFunctionDetail d, typename... T> CDS_ATTR(constexpr(14))
auto unionDestroy(I idx, UnionStorage<d, T...> &data) noexcept -> void {
  return FunctionalVisitorTable<UnionDestroyVisitor, sizeof...(T)>::
  template Table<UnionStorage<d, T...> &>::table[idx](data);
}

template <typename I, UnionFunctionDetail d, typename... T, typename A> CDS_ATTR(constexpr(14))
auto unionConstruct(I idx, UnionStorage<d, T...> &data, A &&other) -> void {
  return FunctionalVisitorTable<UnionConstructVisitor, sizeof...(T)>::
  template Table<UnionStorage<d, T...> &, A &&>::table[idx](data, cds::forward<A>(other));
}

template <typename I, UnionFunctionDetail d, typename... T, typename A> CDS_ATTR(constexpr(14))
auto unionAssign(I idx, UnionStorage<d, T...> &data, A &&other) -> void {
  return FunctionalVisitorTable<UnionAssignVisitor, sizeof...(T)>::
  template Table<UnionStorage<d, T...> &, A &&>::table[idx](data, cds::forward<A>(other));
}

template <typename RequestedType, typename I, UnionFunctionDetail d, typename... T> CDS_ATTR(constexpr(14))
auto unionRaise(I idx, UnionStorage<d, T...> const &data) -> void {
  return FunctionalVisitorTable<UnionRaiseVisitor, sizeof...(T)>::
      template Table<RequestedType, UnionStorage<d, T...>>::table[idx](data);
}

template <typename R, typename I, UnionFunctionDetail d, typename... T, typename Visitor> CDS_ATTR(constexpr(14))
auto unionGenericVisit(I idx, UnionStorage<d, T...> &data, Visitor &&visitor) -> R {
  return FunctionalVisitorTable<UnionGenericVisitor, sizeof...(T)>::
      template Table<R, UnionStorage<d, T...> &, Visitor>::table[idx](data, cds::forward<Visitor>(visitor));
}

template <typename R, typename I, UnionFunctionDetail d, typename... T, typename Visitor> CDS_ATTR(constexpr(14))
auto unionGenericVisit(I idx, UnionStorage<d, T...> const &data, Visitor &&visitor) -> R {
  return FunctionalVisitorTable<UnionGenericVisitor, sizeof...(T)>::
      template Table<R, UnionStorage<d, T...> const &, Visitor>::table[idx](data, cds::forward<Visitor>(visitor));
}

template <typename C, typename I, UnionFunctionDetail d, typename... T> CDS_ATTR(constexpr(14))
auto unionCompare(I idx, UnionStorage<d, T...> const& data, UnionStorage<d, T...> const& otherData) -> bool {
  return FunctionalVisitorTable<UnionCompareVisitor, sizeof...(T)>::
      template Table<C, UnionStorage<d, T...> const&>::table[idx](data, otherData);
}

#if CDS_ATTR(spaceship)
template <typename I, UnionFunctionDetail d, typename... T> CDS_ATTR(constexpr(14))
decltype(auto) unionThreeWay(I idx, UnionStorage<d, T...> const& data, UnionStorage<d, T...> const& otherData) {
  return FunctionalVisitorTable<UnionThreeWayVisitor, sizeof...(T)>::
      template Table<UnionStorage<d, T...> const&>::table[idx](data, otherData);
}
#endif

template <UnionFunctionDetail, typename> struct UnionStorageBase;

template <UnionFunctionDetail detail, typename... Types> struct UnionStorageBase<detail, Pack<Types...>> {
  using Index = UnionActiveIndex<Int<sizeof...(Types)>>;
  using Data = UnionStorage<detail, Types...>;

  CDS_ATTR(2(implicit, constexpr(11))) UnionStorageBase(Valueless tag = {}) noexcept:
      _data{tag}, _index{Index::value} {}

  template <Size index, typename... A> CDS_ATTR(2(implicit, constexpr(11)))
  UnionStorageBase(InPlaceIndex<index> inPlaceIndex, A &&... args)
      CDS_ATTR(noexcept(noexcept(Data{inPlaceIndex, cds::forward<A>(args)...}))) :
      _data{inPlaceIndex, cds::forward<A>(args)...}, _index{index} {}

  template <typename A, typename M = UnionBestMatchType<IsConstructibleSingleArg, A, Types...>, EnableIf<And<
      Not<IsSameIgnoringCVRef<A, UnionStorageBase>>,
      Not<IsBaseOfIntrusiveICVR<UnionStorageBase, A>>,
      IsNotInPlaceIndex<RemoveCVRef<A>>,
      Not<IsSameIgnoringCVRef<A, Valueless>>
  >> = 0> CDS_ATTR(2(implicit, constexpr(11))) UnionStorageBase(A &&arg)
      CDS_ATTR(noexcept(IsNoexceptConstructible<M, A>::value)) :
      UnionStorageBase{
          InPlaceIndex<UnionBestMatchIndex<IsConstructibleSingleArg, A, Types...>::value>{},
          cds::forward<A>(arg)
      } {}

  template <
      typename A0, typename A1, typename... An,
      typename M = UnionBestConstructibleType<Pack<A0, A1, An...>, Types...>,
      EnableIf<IsNotInPlaceIndex<A0>> = 0
  > CDS_ATTR(constexpr(14)) UnionStorageBase(A0 &&arg0, A1 &&arg1, An &&... argn)
      CDS_ATTR(noexcept(IsNoexceptConstructible<M, A0, A1, An...>::value)) :
      UnionStorageBase{
          InPlaceIndex<UnionBestConstructibleIndex<Pack<A0, A1, An...>, Types...>::value>{},
          cds::forward<A0>(arg0), cds::forward<A1>(arg1), cds::forward<An>(argn)...
      } {}

  CDS_ATTR(2(nodiscard, constexpr(11))) auto index() const noexcept -> Size {
    return valueless() ? valuelessIndex : static_cast<Size>(_index);
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto valueless() const noexcept -> bool {
    return _index == Index::value;
  }

  Data _data;
  typename Index::Type _index;
};

template <typename PackedTypes, UnionFunctionDetail = UnionDetails<PackedTypes>::dtr> struct UnionDestructionBase;

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

  template <typename A> CDS_ATTR(constexpr(14)) auto constructFromUnion(A &&otherUnion)
      /* CDS_ATTR(noexcept(noexcept(unionConstruct(this->_index, this->_data, cds::forward<A>(otherUnion))))) */
      -> void {
    destroy();
    if (otherUnion.valueless()) {
      return;
    }

    unionConstruct(otherUnion.index(), _data, cds::forward<A>(otherUnion)._data);
    _index = otherUnion.index();
  }

  template <Size idx, typename... A> CDS_ATTR(constexpr(14)) auto emplace(A &&... args)
      CDS_ATTR(noexcept(IsNoexceptConstructible<typename GetUnionTypeImpl<idx, Types...>::Type, A...>::value))
      -> typename GetUnionTypeImpl<idx, Types...>::Type& {
    destroy();
    auto &data = *construct(&GetUnionData<idx>()(_data), cds::forward<A>(args)...);
    _index = idx;
    return data;
  }

  template <typename Type, typename... A, typename M = UnionBestMatchType<IsConstructibleSingleArg, Type, Types...>>
  CDS_ATTR(constexpr(14)) auto emplace(A &&... args) CDS_ATTR(noexcept(IsNoexceptConstructible<M, A...>::value))
      -> M& {
    return emplace<UnionBestMatchIndex<IsConstructibleSingleArg, Type, Types...>::value>(cds::forward<A>(args)...);
  }
};

template <typename> struct UnionAssignmentBase;

template <typename... Types> struct UnionAssignmentBase<Pack<Types...>> : UnionConstructionBase<Pack<Types...>> {
  using Base = UnionConstructionBase<Pack<Types...>>;
  using Base::Base;
  using Base::index;
  using Base::valueless;
  using Base::destroy;
  using Base::emplace;
  using Base::_data;
  using Base::_index;

  template <typename A> CDS_ATTR(constexpr(14)) auto assignFromUnion(A &&otherUnion) -> void {
    if (valueless() && otherUnion.valueless()) {
      return;
    }

    if (otherUnion.valueless()) {
      return;
    }

    if (index() == otherUnion.index()) {
      _index = UnionActiveIndex<Integral<Size, sizeof...(Types)>>::value;
      unionAssign(otherUnion.index(), _data, cds::forward<A>(otherUnion)._data);
      _index = otherUnion.index();
      return;
    }

    if (index() != otherUnion.index()) {
      destroy();
    }

    unionConstruct(otherUnion.index(), _data, cds::forward<A>(otherUnion)._data);
    _index = otherUnion.index();
  }

  template <typename A, typename M = UnionBestMatchType<IsConstructibleAndAssignable, A, Types...>>
  CDS_ATTR(constexpr(14)) auto assign(A &&value) CDS_ATTR(noexcept(And<
      IsNoexceptConstructible<M, A &&>, IsNoexceptAssignable<M, A>
  >::value)) -> void {
    constexpr auto bestMatchIndex = UnionBestMatchIndex<IsConstructibleAndAssignable, A, Types...>::value;
    if (bestMatchIndex == index()) {
      _index = UnionActiveIndex<Integral<Size, sizeof...(Types)>>::value;
      GetUnionData<bestMatchIndex>()(_data) = cds::forward<A>(value);
      _index = bestMatchIndex;
      return;
    }

    destroy();
    Base::template emplace<bestMatchIndex>(cds::forward<A>(value));
  }
};

template <typename PackedTypes, UnionFunctionDetail = UnionDetails<PackedTypes>::copyCtr>
struct UnionCopyConstructionBase;

template <typename PackedTypes> struct UnionCopyConstructionBase <PackedTypes, UnionFunctionDetail::Trivial> :
    UnionAssignmentBase<PackedTypes> {
  using Base = UnionAssignmentBase<PackedTypes>;
  using Base::Base;
  using Base::operator=;

  UnionCopyConstructionBase(UnionCopyConstructionBase const &) = default;
  UnionCopyConstructionBase(UnionCopyConstructionBase &&) = default;
  auto operator=(UnionCopyConstructionBase const &) -> UnionCopyConstructionBase & = default;
  auto operator=(UnionCopyConstructionBase &&) -> UnionCopyConstructionBase & = default;
  ~UnionCopyConstructionBase() = default;
};

template <typename PackedTypes> struct UnionCopyConstructionBase<PackedTypes, UnionFunctionDetail::Deleted> :
    UnionAssignmentBase<PackedTypes> {
  using Base = UnionAssignmentBase<PackedTypes>;
  using Base::Base;
  using Base::operator=;

  UnionCopyConstructionBase(UnionCopyConstructionBase const &) = delete;
  UnionCopyConstructionBase(UnionCopyConstructionBase &&) = default;
  auto operator=(UnionCopyConstructionBase const &) -> UnionCopyConstructionBase & = default;
  auto operator=(UnionCopyConstructionBase &&) -> UnionCopyConstructionBase & = default;
  ~UnionCopyConstructionBase() = default;
};

template <typename... Types> struct UnionCopyConstructionBase<Pack<Types...>, UnionFunctionDetail::NonTrivial> :
    UnionAssignmentBase<Pack<Types...>> {
  using Base = UnionAssignmentBase<Pack<Types...>>;
  using Base::Base;
  using Base::constructFromUnion;
  using Base::operator=;

  CDS_ATTR(constexpr(14)) UnionCopyConstructionBase(UnionCopyConstructionBase const &other)
  CDS_ATTR(noexcept(All<IsNoexceptCopyConstructible, Types...>::value)): Base{Valueless{}} {
    constructFromUnion(other);
  }

  UnionCopyConstructionBase(UnionCopyConstructionBase &&) = default;
  auto operator=(UnionCopyConstructionBase const &) -> UnionCopyConstructionBase & = default;
  auto operator=(UnionCopyConstructionBase &&) -> UnionCopyConstructionBase & = default;
  ~UnionCopyConstructionBase() = default;
};

template <typename PackedTypes, UnionFunctionDetail = UnionDetails<PackedTypes>::moveCtr>
struct UnionMoveConstructionBase;

template <typename PackedTypes> struct UnionMoveConstructionBase<PackedTypes, UnionFunctionDetail::Trivial> :
    UnionCopyConstructionBase<PackedTypes> {
  using Base = UnionCopyConstructionBase<PackedTypes>;
  using Base::Base;
  using Base::operator=;

  UnionMoveConstructionBase(UnionMoveConstructionBase const &) = default;
  UnionMoveConstructionBase(UnionMoveConstructionBase &&) = default;
  auto operator=(UnionMoveConstructionBase const &) -> UnionMoveConstructionBase & = default;
  auto operator=(UnionMoveConstructionBase &&) -> UnionMoveConstructionBase & = default;
  ~UnionMoveConstructionBase() = default;
};

template <typename PackedTypes> struct UnionMoveConstructionBase<PackedTypes, UnionFunctionDetail::Deleted> :
    UnionCopyConstructionBase<PackedTypes> {
  using Base = UnionCopyConstructionBase<PackedTypes>;
  using Base::Base;
  using Base::operator=;

  UnionMoveConstructionBase(UnionMoveConstructionBase const &) = default;
  UnionMoveConstructionBase(UnionMoveConstructionBase &&) = delete;
  auto operator=(UnionMoveConstructionBase const &) -> UnionMoveConstructionBase & = default;
  auto operator=(UnionMoveConstructionBase &&) -> UnionMoveConstructionBase & = default;
  ~UnionMoveConstructionBase() = default;
};

template <typename... Types> struct UnionMoveConstructionBase<Pack<Types...>, UnionFunctionDetail::NonTrivial> :
    UnionCopyConstructionBase<Pack<Types...>> {
  using Base = UnionCopyConstructionBase<Pack<Types...>>;
  using Base::Base;
  using Base::constructFromUnion;
  using Base::operator=;

  UnionMoveConstructionBase(UnionMoveConstructionBase const &) = default;

  CDS_ATTR(constexpr(14)) UnionMoveConstructionBase(UnionMoveConstructionBase &&other)
  CDS_ATTR(noexcept(All<IsNoexceptMoveConstructible, Types...>::value)): Base{Valueless{}} {
    constructFromUnion(cds::move(other));
  }

  auto operator=(UnionMoveConstructionBase const &) -> UnionMoveConstructionBase & = default;
  auto operator=(UnionMoveConstructionBase &&) -> UnionMoveConstructionBase & = default;
  ~UnionMoveConstructionBase() = default;
};

template <typename PackedTypes, UnionFunctionDetail = UnionDetails<PackedTypes>::copyAssign>
struct UnionCopyAssignmentBase;

template <typename PackedTypes> struct UnionCopyAssignmentBase<PackedTypes, UnionFunctionDetail::Trivial> :
    UnionMoveConstructionBase<PackedTypes> {
  using Base = UnionMoveConstructionBase<PackedTypes>;
  using Base::Base;
  using Base::operator=;

  UnionCopyAssignmentBase(UnionCopyAssignmentBase const &) = default;
  UnionCopyAssignmentBase(UnionCopyAssignmentBase &&) = default;
  auto operator=(UnionCopyAssignmentBase const &) -> UnionCopyAssignmentBase & = default;
  auto operator=(UnionCopyAssignmentBase &&) -> UnionCopyAssignmentBase & = default;
  ~UnionCopyAssignmentBase() = default;
};

template <typename PackedTypes> struct UnionCopyAssignmentBase<PackedTypes, UnionFunctionDetail::Deleted> :
    UnionMoveConstructionBase<PackedTypes> {
  using Base = UnionMoveConstructionBase<PackedTypes>;
  using Base::Base;
  using Base::operator=;

  UnionCopyAssignmentBase(UnionCopyAssignmentBase const &) = default;
  UnionCopyAssignmentBase(UnionCopyAssignmentBase &&) = default;
  auto operator=(UnionCopyAssignmentBase const &) -> UnionCopyAssignmentBase & = delete;
  auto operator=(UnionCopyAssignmentBase &&) -> UnionCopyAssignmentBase & = default;
  ~UnionCopyAssignmentBase() = default;
};

template <typename... Types> struct UnionCopyAssignmentBase<Pack<Types...>, UnionFunctionDetail::NonTrivial> :
    UnionMoveConstructionBase<Pack<Types...>> {
  using Base = UnionMoveConstructionBase<Pack<Types...>>;
  using Base::Base;
  using Base::assignFromUnion;
  using Base::operator=;

  UnionCopyAssignmentBase(UnionCopyAssignmentBase const &) = default;
  UnionCopyAssignmentBase(UnionCopyAssignmentBase &&) = default;

  CDS_ATTR(constexpr(14)) auto operator=(UnionCopyAssignmentBase const &other) CDS_ATTR(noexcept(And<
      All<IsNoexceptCopyConstructible, Types...>,
      All<IsNoexceptCopyAssignable, Types...>
  >::value)) -> UnionCopyAssignmentBase & {
    if (this == &other) {
      return *this;
    }

    assignFromUnion(other);
    return *this;
  }

  auto operator=(UnionCopyAssignmentBase &&) -> UnionCopyAssignmentBase & = default;
  ~UnionCopyAssignmentBase() = default;
};

template <typename PackedTypes, UnionFunctionDetail = UnionDetails<PackedTypes>::moveAssign>
struct UnionMoveAssignmentBase;

template <typename PackedTypes> struct UnionMoveAssignmentBase<PackedTypes, UnionFunctionDetail::Trivial> :
    UnionCopyAssignmentBase<PackedTypes> {
  using Base = UnionCopyAssignmentBase<PackedTypes>;
  using Base::Base;
  using Base::operator=;

  UnionMoveAssignmentBase(UnionMoveAssignmentBase const &) = default;
  UnionMoveAssignmentBase(UnionMoveAssignmentBase &&) = default;
  auto operator=(UnionMoveAssignmentBase const &) -> UnionMoveAssignmentBase & = default;
  auto operator=(UnionMoveAssignmentBase &&) -> UnionMoveAssignmentBase & = default;
  ~UnionMoveAssignmentBase() = default;
};

template <typename PackedTypes> struct UnionMoveAssignmentBase<PackedTypes, UnionFunctionDetail::Deleted> :
    UnionCopyAssignmentBase<PackedTypes> {
  using Base = UnionCopyAssignmentBase<PackedTypes>;
  using Base::Base;
  using Base::operator=;

  UnionMoveAssignmentBase(UnionMoveAssignmentBase const &) = default;
  UnionMoveAssignmentBase(UnionMoveAssignmentBase &&) = default;
  auto operator=(UnionMoveAssignmentBase const &) -> UnionMoveAssignmentBase & = default;
  auto operator=(UnionMoveAssignmentBase &&) -> UnionMoveAssignmentBase & = delete;
  ~UnionMoveAssignmentBase() = default;
};

template <typename... Types> struct UnionMoveAssignmentBase<Pack<Types...>, UnionFunctionDetail::NonTrivial> :
    UnionCopyAssignmentBase<Pack<Types...>> {
  using Base = UnionCopyAssignmentBase<Pack<Types...>>;
  using Base::Base;
  using Base::assignFromUnion;
  using Base::operator=;

  UnionMoveAssignmentBase(UnionMoveAssignmentBase const &) = default;
  UnionMoveAssignmentBase(UnionMoveAssignmentBase &&) = default;
  auto operator=(UnionMoveAssignmentBase const &) -> UnionMoveAssignmentBase & = default;

  CDS_ATTR(constexpr(14)) auto operator=(UnionMoveAssignmentBase &&other) CDS_ATTR(noexcept(And<
      All<IsNoexceptMoveConstructible, Types...>,
      All<IsNoexceptMoveAssignable, Types...>
  >::value)) -> UnionMoveAssignmentBase & {
    if (this == &other) {
      return *this;
    }

    assignFromUnion(cds::move(other));
    return *this;
  }

  ~UnionMoveAssignmentBase() = default;
};

template <typename PackedTypes> struct UnionObservableBase;

template <typename... Types> struct UnionObservableBase<Pack<Types...>> : UnionMoveAssignmentBase<Pack<Types...>> {
  using Base = UnionMoveAssignmentBase<Pack<Types...>>;
  using Base::Base;
  using Base::index;
  using Base::valueless;
  using Base::_data;
  using Base::operator=;

  template <
      typename Type, typename Match = UnionBestMatchType<IsSame, Type, Types...>,
      EnableIf<IsSame<void, Match>> = 0
  > CDS_ATTR(2(nodiscard, constexpr(11))) auto is() const noexcept -> bool {
    return false;
  }

  template <
      typename Type, typename Match = UnionBestMatchType<IsSame, Type, Types...>,
      EnableIf<Not<IsSame<void, Match>>> = 0
  > CDS_ATTR(2(nodiscard, constexpr(11))) auto is() const noexcept -> bool {
    return UnionBestMatchIndex<IsSame, Type, Types...>::value == index();
  }

  template <typename Type, typename Match = UnionBestMatchType<IsSame, Type, Types...>>
  CDS_ATTR(2(nodiscard, constexpr(14))) auto get() const CDS_ATTR(noexcept(false)) -> Match const & {
    constexpr auto matchIdx = UnionBestMatchIndex<IsSame, Type, Types...>::value;
    if (matchIdx != index()) {
      if (valueless()) {
        CDS_ATTR(throw (UnionTypeException::of<Valueless, Type>()));
      }
      unionRaise<Type>(index(), _data);
    }
    return GetUnionData<matchIdx>()(_data);
  }

  template <typename Type, typename Match = UnionBestMatchType<IsSame, Type, Types...>>
  CDS_ATTR(2(nodiscard, constexpr(14))) auto get() CDS_ATTR(noexcept(false)) -> Match & {
    constexpr auto matchIdx = UnionBestMatchIndex<IsSame, Type, Types...>::value;
    if (matchIdx != index()) {
      if (valueless()) {
        CDS_ATTR(throw (UnionTypeException::of<Valueless, Type>()));
      }
      unionRaise<Type>(index(), _data);
    }
    return GetUnionData<matchIdx>()(_data);
  }

  template <
      typename Type, typename C, typename Match = UnionBestMatchType<IsSame, Type, Types...>,
      typename R = InvokeReturnOf<C, Match const &>, EnableIf<Not<IsSame<void, R>>> = 0
  > CDS_ATTR(2(nodiscard, constexpr(14))) auto ifIs(C &&callable) const CDS_ATTR(noexcept(noexcept(
      functional::invoke(cds::forward<C>(callable), lvalue<Match const>())
  ))) -> R {
    if (is<Type>()) {
      return functional::invoke(cds::forward<C>(callable), get<Type>());
    }
    return nullopt;
  }

  template <
      typename Type, typename C, typename Match = UnionBestMatchType<IsSame, Type, Types...>,
      typename R = InvokeReturnOf<C, Match &>, EnableIf<Not<IsSame<void, R>>> = 0
  > CDS_ATTR(2(nodiscard, constexpr(14))) auto ifIs(C &&callable) CDS_ATTR(noexcept(noexcept(
      functional::invoke(cds::forward<C>(callable), lvalue<Match>())
  ))) -> R {
    if (is<Type>()) {
      return functional::invoke(cds::forward<C>(callable), get<Type>());
    }
    return nullopt;
  }

  template <
      typename Type, typename C, typename Match = UnionBestMatchType<IsSame, Type, Types...>,
      typename R = InvokeReturnOf<C, Match const &>, EnableIf<IsSame<void, R>> = 0
  > CDS_ATTR(constexpr(14)) auto ifIs(C &&callable) const CDS_ATTR(noexcept(noexcept(
      functional::invoke(cds::forward<C>(callable), lvalue<Match const>())
  ))) -> void {
    if (is<Type>()) {
      functional::invoke(cds::forward<C>(callable), get<Type>());
    }
  }

  template <
      typename Type, typename C, typename Match = UnionBestMatchType<IsSame, Type, Types...>,
      typename R = InvokeReturnOf<C, Match &>, EnableIf<IsSame<void, R>> = 0
  > CDS_ATTR(constexpr(14)) auto ifIs(C &&callable) CDS_ATTR(noexcept(noexcept(
      functional::invoke(cds::forward<C>(callable), lvalue<Match>())
  ))) -> void {
    if (is<Type>()) {
      functional::invoke(cds::forward<C>(callable), get<Type>());
    }
  }

  template <typename Comparator> CDS_ATTR(2(nodiscard, constexpr(14))) auto compare(UnionObservableBase const& other)
      const CDS_ATTR(noexcept(false)) -> bool {
    return unionCompare<Comparator>(index(), _data, other._data);
  }

#if CDS_ATTR(spaceship)
  CDS_ATTR(2(nodiscard, constexpr(14))) decltype(auto) compare(UnionObservableBase const& other)
      const CDS_ATTR(noexcept(false)) {
    return unionThreeWay(index(), *this, other);
  }
#endif
};

template <typename Visitor, typename... Types> struct VisitorDetail;

template <typename, typename = void> struct NonDecayedCommonHelper {
  using Valid = False;
  using Type = void;
};

template <typename... Types>
struct NonDecayedCommonHelper<Pack<Types...>, Void<typename NonDecayedCommon<Types...>::Type>> {
  using Valid = True;
  using Type = typename NonDecayedCommon<Types...>::Type;
};

template <typename Visitor, typename Head> struct VisitorDetail<Visitor, Head> {
  using Exhaustive = IsInvocable<Visitor, Head>;
  using Return = NonDecayedCommonHelper<Pack<InvokeReturnOf<Visitor, Head>>>;
  using Noexcept = IsNoexceptInvocable<Visitor, Head>;
};

template <typename Visitor, typename Head, typename... Tail> struct VisitorDetail<Visitor, Head, Tail...> {
  using TailDetail = VisitorDetail<Visitor, Tail...>;
  using Exhaustive = And<typename TailDetail::Exhaustive, IsInvocable<Visitor, Head>>;
  using Return = NonDecayedCommonHelper<Pack<InvokeReturnOf<Visitor, Head>, InvokeReturnOf<Visitor, Tail>...>>;
  using Noexcept = And<IsNoexceptInvocable<Visitor, Head>, typename TailDetail::Noexcept>;
};

template <typename PackedTypes> struct UnionVisitationBase;

template <typename... Types> struct UnionVisitationBase<Pack<Types...>> : UnionObservableBase<Pack<Types...>> {
  using Base = UnionObservableBase<Pack<Types...>>;
  using Base::Base;
  using Base::operator=;
  using Base::index;
  using Base::valueless;
  using Base::_data;

  template <
      typename Visitor, typename Detail = VisitorDetail<Visitor, Types...>,
      typename Exhaustive = typename Detail::Exhaustive,
      typename Compatible = typename Detail::Return::Valid,
      EnableIf<And<Exhaustive, Not<Compatible>>> = 0
  > CDS_ATTR(constexpr(14)) auto visit(CDS_ATTR(unused) Visitor&&) const noexcept -> void {
    static_assert(Compatible::value, "Visitor return types are incompatible in a common type");
  }

  template <
      typename Visitor, typename Detail = VisitorDetail<Visitor, Types...>,
      typename Exhaustive = typename Detail::Exhaustive,
      typename Compatible = typename Detail::Return::Valid,
      EnableIf<And<Exhaustive, Not<Compatible>>> = 0
  > CDS_ATTR(constexpr(14)) auto visit(CDS_ATTR(unused) Visitor&&) noexcept -> void {
    static_assert(Compatible::value, "Visitor return types are incompatible in a common type");
  }

  template <
      typename Visitor, typename Detail = VisitorDetail<Visitor, Types...>,
      typename Exhaustive = typename Detail::Exhaustive,
      typename Compatible = typename Detail::Return::Valid,
      EnableIf<And<Not<Exhaustive>, Compatible>> = 0
  > CDS_ATTR(constexpr(14)) auto visit(CDS_ATTR(unused) Visitor&&) const noexcept -> void {
    static_assert(Exhaustive::value, "Visitor is not exhaustive");
  }

  template <
      typename Visitor, typename Detail = VisitorDetail<Visitor, Types...>,
      typename Exhaustive = typename Detail::Exhaustive,
      typename Compatible = typename Detail::Return::Valid,
      EnableIf<And<Not<Exhaustive>, Compatible>> = 0
  > CDS_ATTR(constexpr(14)) auto visit(CDS_ATTR(unused) Visitor&&) noexcept -> void {
    static_assert(Exhaustive::value, "Visitor is not exhaustive");
  }

  template <
      typename Visitor, typename Detail = VisitorDetail<Visitor, Types...>,
      typename Exhaustive = typename Detail::Exhaustive,
      typename Compatible = typename Detail::Return::Valid,
      EnableIf<And<Not<Exhaustive>, Not<Compatible>>> = 0
  > CDS_ATTR(constexpr(14)) auto visit(CDS_ATTR(unused) Visitor&&) const noexcept -> void {
    static_assert(
        Or<Exhaustive, Compatible>::value,
        "Visitor is not exhaustive and the return types are incompatible in a common type"
    );
  }

  template <
      typename Visitor, typename Detail = VisitorDetail<Visitor, Types...>,
      typename Exhaustive = typename Detail::Exhaustive,
      typename Compatible = typename Detail::Return::Valid,
      EnableIf<And<Not<Exhaustive>, Not<Compatible>>> = 0
  > CDS_ATTR(constexpr(14)) auto visit(CDS_ATTR(unused) Visitor&&) noexcept -> void {
    static_assert(
        Or<Exhaustive, Compatible>::value,
        "Visitor is not exhaustive and the returned values are incompatible in a common return"
    );
  }

  template <
      typename Visitor, typename Detail = VisitorDetail<Visitor, Types...>,
      typename Exhaustive = typename Detail::Exhaustive,
      typename Compatible = typename Detail::Return::Valid,
      EnableIf<And<Exhaustive, Compatible>> = 0
  > CDS_ATTR(constexpr(14)) auto visit(Visitor&& visitor) const CDS_ATTR(noexcept(false))
      -> typename Detail::Return::Type {
    if (valueless()) {
      CDS_ATTR(throw(UnionTypeException::valuelessVisit()));
    }
    return unionGenericVisit<typename Detail::Return::Type>(index(), _data, cds::forward<Visitor>(visitor));
  }

  template <
      typename Visitor, typename Detail = VisitorDetail<Visitor, Types...>,
      typename Exhaustive = typename Detail::Exhaustive,
      typename Compatible = typename Detail::Return::Valid,
      EnableIf<And<Exhaustive, Compatible>> = 0
  > CDS_ATTR(constexpr(14)) auto visit(Visitor&& visitor) CDS_ATTR(noexcept(false))
      -> typename Detail::Return::Type {
    if (valueless()) {
      CDS_ATTR(throw(UnionTypeException::valuelessVisit()));
    }
    return unionGenericVisit<typename Detail::Return::Type>(index(), _data, cds::forward<Visitor>(visitor));
  }
};

template <typename = void> struct ValuelessTypeInfo { static char constexpr name[10u] = "valueless"; };
template <typename T> char const ValuelessTypeInfo<T>::name[10u];
} // namespace unionImpl
} // namespace impl

namespace meta {
template <> struct TypeInfo<cds::impl::unionImpl::Valueless> : cds::impl::unionImpl::ValuelessTypeInfo<> {};
} // namespace meta
} // namespace cds

CDS_ATTR(enable_warning(gcc, "-Wterminate"))
CDS_ATTR(enable_warning(msvc, 4297))

#endif // #ifndef CDS_PRIMITIVE_UNION_NODE_HPP
