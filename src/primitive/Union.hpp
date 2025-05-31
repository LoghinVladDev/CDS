//
// Created by loghin on 5/14/24.
//

#ifndef CDS_PRIMITIVE_UNION_HPP
#define CDS_PRIMITIVE_UNION_HPP
#pragma once

#include "../common/SpecialMemberFunctionHelper.hpp"

#include "union/UnionDecl.hpp"
#include "union/UnionNodeV2.hpp"

namespace cds {
namespace impl {
using functional::Equal;
using functional::NotEqual;
using functional::Less;
using functional::Greater;
using functional::LessEqual;
using functional::GreaterEqual;

using meta::All;
using meta::IsCopyAssignable;
using meta::IsMoveAssignable;
using meta::IsCopyConstructible;
using meta::IsMoveConstructible;
using meta::IsSame;
using meta::IsSameIgnoringCVRef;
using meta::Not;

using meta::impl::Pack;

using unionImpl::UnionVisitationBase;
using unionImpl::UnionBestMatchType;

template <typename T> struct IsCopyConstructibleAndAssignable : And<IsCopyConstructible<T>, IsCopyAssignable<T>> {};
template <typename T> struct IsMoveConstructibleAndAssignable : And<IsMoveConstructible<T>, IsMoveAssignable<T>> {};

template <typename... Types> class Union :
    private UnionVisitationBase<Pack<Types...>>,
    private meta::impl::SfinaeCtorBase<
        typename All<IsCopyConstructible, Types...>::Type,
        typename All<IsMoveConstructible, Types...>::Type
    >, private meta::impl::SfinaeAssignBase<
        typename All<IsCopyConstructibleAndAssignable, Types...>::Type,
        typename All<IsMoveConstructibleAndAssignable, Types...>::Type
    > {
  using Base = UnionVisitationBase<Pack<Types...>>;
  using Base::assign;
  using Base::compare;

  template <typename... Types0> CDS_ATTR(constexpr(14)) friend auto operator==(
    Union<Types0...> const& lhs, Union<Types0...> const& rhs
  ) CDS_ATTR(friend_noexcept(All<meta::IsNoexceptEqCompatible, Types0...>::value)) -> bool;

  template <typename... Types0> CDS_ATTR(constexpr(14)) friend auto operator!=(
    Union<Types0...> const& lhs, Union<Types0...> const& rhs
  ) CDS_ATTR(friend_noexcept(All<meta::IsNoexceptNeCompatible, Types0...>::value)) -> bool;

public:
  using Base::Base;
  using Base::operator=;
  Union() = default;
  Union(Union const&) = default;
  Union(Union&&) = default;
  auto operator=(Union const&) -> Union& = default;
  auto operator=(Union&&) -> Union& = default;

  using Base::emplace;

  using Base::ifIs;
  using Base::visit;

  using Base::get;
  using Base::index;
  using Base::valueless;
  using Base::is;

  template <typename A, EnableIf<Not<IsSameIgnoringCVRef<A, Union>>> = 0>
  CDS_ATTR(constexpr(14)) auto operator=(A&& arg)
      CDS_ATTR(noexcept(noexcept(assign(cds::forward<A>(arg))))) -> Union& {
    assign(cds::forward<A>(arg));
    return *this;
  }
};

template <typename T, typename... Ts> CDS_ATTR(2(nodiscard, constexpr(11))) auto get(Union<Ts...> const& u)
    CDS_ATTR(noexcept(false)) -> UnionBestMatchType<IsSame, T, Ts...> const& {
  return u.template get<T>();
}

template <typename T, typename... Ts> CDS_ATTR(2(nodiscard, constexpr(14))) auto get(Union<Ts...>& u)
    CDS_ATTR(noexcept(false)) -> UnionBestMatchType<IsSame, T, Ts...>& {
  return u.template get<T>();
}

template <typename T, typename... Ts> CDS_ATTR(2(nodiscard, constexpr(14))) auto get(Union<Ts...>&& u)
    CDS_ATTR(noexcept(false)) -> UnionBestMatchType<IsSame, T, Ts...>&& {
  return std::move(u.template get<T>());
}

template <typename...Types0> CDS_ATTR(2(nodiscard, constexpr(14))) auto operator==(
    Union<Types0...> const& lhs, Union<Types0...> const& rhs
) CDS_ATTR(friend_noexcept(All<meta::IsNoexceptEqCompatible, Types0...>::value)) -> bool {
  static_assert(All<meta::IsEqCompatible, Types0...>::value, "All union types must be equal comparable to invoke ==");
  if (lhs.index() != rhs.index()) {
    return false;
  }
  if (lhs.valueless()) {
    return true;
  }

  return lhs.template compare<Equal<>>(rhs);
}

template <typename...Types0> CDS_ATTR(2(nodiscard, constexpr(14))) auto operator!=(
    Union<Types0...> const& lhs, Union<Types0...> const& rhs
) CDS_ATTR(friend_noexcept(All<meta::IsNoexceptNeCompatible, Types0...>::value)) -> bool {
  static_assert(All<meta::IsNeCompatible, Types0...>::value,
      "All union types must be not-equal comparable to invoke ==");
  if (lhs.index() != rhs.index()) {
    return true;
  }
  if (lhs.valueless()) {
    return false;
  }

  return lhs.template compare<NotEqual<>>(rhs);
}
} // namespace impl

namespace meta {
namespace impl {
template <typename...> struct UnionVisitorComposite;
template <typename Visitor> struct UnionVisitorComposite<Visitor> : Visitor {
  using Visitor::operator();

  template <typename V> CDS_ATTR(2(explicit, constexpr(11))) UnionVisitorComposite(V&& visitor)
      CDS_ATTR(noexcept(IsNoexceptConstructible<Visitor, V>::value)) : Visitor{cds::forward<V>(visitor)} {}
};

template <typename Visitor, typename... TailVisitors> struct UnionVisitorComposite<Visitor, TailVisitors...> :
    UnionVisitorComposite<TailVisitors...>, Visitor {
  using UnionVisitorComposite<TailVisitors...>::operator();
  using Visitor::operator();

  template <typename V, typename... TailVs> CDS_ATTR(2(explicit, constexpr(11)))
  UnionVisitorComposite(V&& visitor, TailVs&&... tailVisitors)
  CDS_ATTR(noexcept(And<
      IsNoexceptConstructible<Visitor, V>,
      IsNoexceptConstructible<UnionVisitorComposite<TailVisitors...>, TailVs...>
  >::value)) :
      UnionVisitorComposite<TailVisitors...>{cds::forward<TailVs>(tailVisitors)...}, Visitor{cds::forward<V>(visitor)} {
  }
};

template <typename... Visitors> CDS_ATTR(2(nodiscard, constexpr(11))) auto visitors(
    Visitors&&... visitors
) CDS_ATTR(noexcept(noexcept(UnionVisitorComposite<Visitors...>{cds::forward<Visitors>(visitors)...})))
    -> UnionVisitorComposite<Visitors...> {
  return UnionVisitorComposite<Visitors...> {cds::forward<Visitors>(visitors)...};
}
} // namespace impl

using impl::visitors;
} // namespace meta
using impl::Union;
using impl::unionImpl::InPlaceIndex;
} // namespace cds

#endif // #ifndef CDS_PRIMITIVE_UNION_HPP
