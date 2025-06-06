//
// Created by loghin on 12/17/23.
//

#ifndef CDS_BINDINGS_STATIC_FIND_OF_BINDING_STATIC_HPP
#define CDS_BINDINGS_STATIC_FIND_OF_BINDING_STATIC_HPP
#pragma once

#include "../BindingSelectors.hpp"
#include <initializer_list>
#include <cds/memory/Allocator>

#include "../../algorithm/FindPreserveTransformer.hpp"
#include "../../algorithm/FindResultTransformer.hpp"
#include "../../algorithm/GenericContains.hpp"
#include "../../algorithm/GenericFind.hpp"

namespace cds {
namespace impl {
using std::initializer_list;

using meta::rvalue;
using meta::IterableTraits;
using meta::RemoveConst;
using meta::And;

using impl::Contains;
using impl::NotContains;

using meta::IsAllocatorOrAllocatorSet;

using functional::Equal;

using impl::FindResultTransformer;
using impl::FindPreserveTransformer;

template <typename, typename, typename, typename = void> class FindOfByValueStaticBinding {};

template <typename R, typename TrAll, typename TrOne> class FindOfByValueStaticBinding<R, TrAll, TrOne> {
  CDS_ATTR(2(nodiscard, constexpr(14))) auto refl() noexcept -> R& {
    return *static_cast<R*>(this);
  }
  
protected:
  using Value = typename IterableTraits<R>::Value;
  using E = Contains<Equal<>>;
  using NE = NotContains<Equal<>>;

public:
  template <typename F = initializer_list<Value>, EnableIf<Not<FindUsesAllocation<R, RemoveCVRef<F>, E>>> = 0>
  CDS_ATTR(2(nodiscard, constexpr(14))) auto findOf(F&& from)& CDS_ATTR(noexcept(noexcept(
      impl::find(lvalue<R>(), fwd<F>(from), E{}, TrAll{})
  ))) -> decltype(impl::find(lvalue<R>(), fwd<F>(from), E{}, TrAll{})) {
    return impl::find(refl(), fwd<F>(from), E{}, TrAll{});
  }

  template <typename F = initializer_list<Value>, EnableIf<Not<FindUsesAllocation<R, RemoveCVRef<F>, NE>>> = 0>
  CDS_ATTR(2(nodiscard, constexpr(14))) auto findNotOf(F&& from)& CDS_ATTR(noexcept(noexcept(
      impl::find(lvalue<R>(), fwd<F>(from), NE{}, TrAll{})
  ))) -> decltype(impl::find(lvalue<R>(), fwd<F>(from), NE{}, TrAll{})) {
    return impl::find(refl(), fwd<F>(from), NE{}, TrAll{});
  }

  template <typename F = initializer_list<Value>, EnableIf<Not<FindUsesAllocation<R, RemoveCVRef<F>, E>>> = 0>
  CDS_ATTR(2(nodiscard, constexpr(14))) auto findOf(F&& from)&& CDS_ATTR(noexcept(noexcept(
      impl::find(rvalue<R>(), fwd<F>(from), E{}, TrAll{})
  ))) -> decltype(impl::find(rvalue<R>(), fwd<F>(from), E{}, TrAll{})) {
    return impl::find(mv(refl()), fwd<F>(from), E{}, TrAll{});
  }

  template <typename F = initializer_list<Value>, EnableIf<Not<FindUsesAllocation<R, RemoveCVRef<F>, NE>>> = 0>
  CDS_ATTR(2(nodiscard, constexpr(14))) auto findNotOf(F&& from)&& CDS_ATTR(noexcept(noexcept(
      impl::find(rvalue<R>(), fwd<F>(from), NE{}, TrAll{})
  ))) -> decltype(impl::find(rvalue<R>(), fwd<F>(from), NE{}, TrAll{})) {
    return impl::find(mv(refl()), fwd<F>(from), NE{}, TrAll{});
  }

  template <typename F = initializer_list<Value>, EnableIf<Not<FindUsesAllocation<R, RemoveCVRef<F>, E>>> = 0>
  CDS_ATTR(2(nodiscard, constexpr(14))) auto findFirstOf(F&& from) CDS_ATTR(noexcept(noexcept(
      impl::findFirst(rvalue<R>(), fwd<F>(from), E{}, TrOne{})
  ))) -> decltype(impl::findFirst(rvalue<R>(), fwd<F>(from), E{}, TrOne{})) {
    return impl::findFirst(refl(), fwd<F>(from), E{}, TrOne{});
  }

  template <typename F = initializer_list<Value>, EnableIf<Not<FindUsesAllocation<R, RemoveCVRef<F>, NE>>> = 0>
  CDS_ATTR(2(nodiscard, constexpr(14))) auto findFirstNotOf(F&& from) CDS_ATTR(noexcept(noexcept(
      impl::findFirst(rvalue<R>(), fwd<F>(from), NE{}, TrOne{})
  ))) -> decltype(impl::findFirst(rvalue<R>(), fwd<F>(from), NE{}, TrOne{})) {
    return impl::findFirst(refl(), fwd<F>(from), NE{}, TrOne{});
  }

  template <typename F = initializer_list<Value>, EnableIf<Not<FindUsesAllocation<R, RemoveCVRef<F>, E>>> = 0>
  CDS_ATTR(2(nodiscard, constexpr(14))) auto findLastOf(F&& from) CDS_ATTR(noexcept(noexcept(
      impl::findLast(rvalue<R>(), fwd<F>(from), E{}, TrOne{})
  ))) -> decltype(impl::findLast(rvalue<R>(), fwd<F>(from), E{}, TrOne{})) {
    return impl::findLast(refl(), fwd<F>(from), E{}, TrOne{});
  }

  template <typename F = initializer_list<Value>, EnableIf<Not<FindUsesAllocation<R, RemoveCVRef<F>, NE>>> = 0>
  CDS_ATTR(2(nodiscard, constexpr(14))) auto findLastNotOf(F&& from) CDS_ATTR(noexcept(noexcept(
      impl::findLast(rvalue<R>(), fwd<F>(from), NE{}, TrOne{})
  ))) -> decltype(impl::findLast(rvalue<R>(), fwd<F>(from), NE{}, TrOne{})) {
    return impl::findLast(refl(), fwd<F>(from), NE{}, TrOne{});
  }

  template <
      typename F = initializer_list<Value>, typename U = FindUsesAllocation<R, RemoveCVRef<F>, E>,
      typename A = typename U::Alloc, EnableIf<And<U, IsAllocatorOrAllocatorSet<A>>> = 0
  > CDS_ATTR(2(nodiscard, constexpr(14))) auto findOf(F&& from, A&& alloc = A())& CDS_ATTR(noexcept(noexcept(
      impl::find(lvalue<R>(), fwd<F>(from), E{}, TrAll{}, fwd<A>(alloc))
  ))) -> decltype(impl::find(lvalue<R>(), fwd<F>(from), E{}, TrAll{}, fwd<A>(alloc))) {
    return impl::find(refl(), fwd<F>(from), E{}, TrAll{}, fwd<A>(alloc));
  }

  template <
      typename F = initializer_list<Value>, typename U = FindUsesAllocation<R, RemoveCVRef<F>, NE>,
      typename A = typename U::Alloc, EnableIf<And<U, IsAllocatorOrAllocatorSet<A>>> = 0
  > CDS_ATTR(2(nodiscard, constexpr(14))) auto findNotOf(F&& from, A&& alloc = A())& CDS_ATTR(noexcept(noexcept(
      impl::find(lvalue<R>(), fwd<F>(from), NE{}, TrAll{}, fwd<A>(alloc))
  ))) -> decltype(impl::find(lvalue<R>(), fwd<F>(from), NE{}, TrAll{}, fwd<A>(alloc))) {
    return impl::find(refl(), fwd<F>(from), NE{}, TrAll{}, fwd<A>(alloc));
  }

  template <
      typename F = initializer_list<Value>, typename U = FindUsesAllocation<R, RemoveCVRef<F>, E>,
      typename A = typename U::Alloc, EnableIf<And<U, IsAllocatorOrAllocatorSet<A>>> = 0
  > CDS_ATTR(2(nodiscard, constexpr(14))) auto findOf(F&& from, A&& alloc = A())&& CDS_ATTR(noexcept(noexcept(
      impl::find(rvalue<R>(), fwd<F>(from), E{}, TrAll{}, fwd<A>(alloc))
  ))) -> decltype(impl::find(rvalue<R>(), fwd<F>(from), E{}, TrAll{}, fwd<A>(alloc))) {
    return impl::find(mv(refl()), fwd<F>(from), E{}, TrAll{}, fwd<A>(alloc));
  }

  template <
      typename F = initializer_list<Value>, typename U = FindUsesAllocation<R, RemoveCVRef<F>, NE>,
      typename A = typename U::Alloc, EnableIf<And<U, IsAllocatorOrAllocatorSet<A>>> = 0
  > CDS_ATTR(2(nodiscard, constexpr(14))) auto findNotOf(F&& from, A&& alloc = A())&& CDS_ATTR(noexcept(noexcept(
      impl::find(rvalue<R>(), fwd<F>(from), NE{}, TrAll{}, fwd<A>(alloc))
  ))) -> decltype(impl::find(rvalue<R>(), fwd<F>(from), NE{}, TrAll{}, fwd<A>(alloc))) {
    return impl::find(mv(refl()), fwd<F>(from), NE{}, TrAll{}, fwd<A>(alloc));
  }

  template <
      typename F = initializer_list<Value>, typename U = FindUsesAllocation<R, RemoveCVRef<F>, E>,
      typename A = typename U::Alloc, EnableIf<And<U, IsAllocatorOrAllocatorSet<A>>> = 0
  > CDS_ATTR(2(nodiscard, constexpr(14))) auto findFirstOf(F&& from, A&& alloc = A()) CDS_ATTR(noexcept(noexcept(
      impl::findFirst(rvalue<R>(), fwd<F>(from), E{}, TrOne{}, fwd<A>(alloc))
  ))) -> decltype(impl::findFirst(rvalue<R>(), fwd<F>(from), E{}, TrOne{}, fwd<A>(alloc))) {
    return impl::findFirst(refl(), fwd<F>(from), E{}, TrOne{}, fwd<A>(alloc));
  }

  template <
      typename F = initializer_list<Value>, typename U = FindUsesAllocation<R, RemoveCVRef<F>, NE>,
      typename A = typename U::Alloc, EnableIf<And<U, IsAllocatorOrAllocatorSet<A>>> = 0
  > CDS_ATTR(2(nodiscard, constexpr(14))) auto findFirstNotOf(F&& from, A&& alloc = A()) CDS_ATTR(noexcept(noexcept(
      impl::findFirst(rvalue<R>(), fwd<F>(from), NE{}, TrOne{}, fwd<A>(alloc))
  ))) -> decltype(impl::findFirst(rvalue<R>(), fwd<F>(from), NE{}, TrOne{}, fwd<A>(alloc))) {
    return impl::findFirst(refl(), fwd<F>(from), NE{}, TrOne{}, fwd<A>(alloc));
  }

  template <
      typename F = initializer_list<Value>, typename U = FindUsesAllocation<R, RemoveCVRef<F>, E>,
      typename A = typename U::Alloc, EnableIf<And<U, IsAllocatorOrAllocatorSet<A>>> = 0
  > CDS_ATTR(2(nodiscard, constexpr(14))) auto findLastOf(F&& from, A&& alloc = A()) CDS_ATTR(noexcept(noexcept(
      impl::findLast(rvalue<R>(), fwd<F>(from), E{}, TrOne{}, fwd<A>(alloc))
  ))) -> decltype(impl::findLast(rvalue<R>(), fwd<F>(from), E{}, TrOne{}, fwd<A>(alloc))) {
    return impl::findLast(refl(), fwd<F>(from), E{}, TrOne{}, fwd<A>(alloc));
  }

  template <
      typename F = initializer_list<Value>, typename U = FindUsesAllocation<R, RemoveCVRef<F>, NE>,
      typename A = typename U::Alloc, EnableIf<And<U, IsAllocatorOrAllocatorSet<A>>> = 0
  > CDS_ATTR(2(nodiscard, constexpr(14))) auto findLastNotOf(F&& from, A&& alloc = A()) CDS_ATTR(noexcept(noexcept(
      impl::findLast(rvalue<R>(), fwd<F>(from), NE{}, TrOne{}, fwd<A>(alloc))
  ))) -> decltype(impl::findLast(rvalue<R>(), fwd<F>(from), NE{}, TrOne{}, fwd<A>(alloc))) {
    return impl::findLast(refl(), fwd<F>(from), NE{}, TrOne{}, fwd<A>(alloc));
  }
};

template <typename R, typename TrAll, typename TrOne> class FindOfByValueStaticBinding<R const, TrAll, TrOne> {
  CDS_ATTR(2(nodiscard, constexpr(11))) auto refl() const noexcept -> R const& {
    return *static_cast<R const*>(this);
  }
  
protected:
  using Value = typename IterableTraits<R>::Value;
  using E = Contains<Equal<>>;
  using NE = NotContains<Equal<>>;
  using RNC = RemoveConst<R>;

public:
  template <typename F = initializer_list<Value>, EnableIf<Not<FindUsesAllocation<RNC, RemoveCVRef<F>, E>>> = 0>
  CDS_ATTR(2(nodiscard, constexpr(14))) auto findOf(F&& from) const& CDS_ATTR(noexcept(noexcept(
      impl::find(lvalue<R const>(), fwd<F>(from), E{}, TrAll{})
  ))) -> decltype(impl::find(lvalue<R const>(), fwd<F>(from), E{}, TrAll{})) {
    return impl::find(refl(), fwd<F>(from), E{}, TrAll{});
  }

  template <typename F = initializer_list<Value>, EnableIf<Not<FindUsesAllocation<RNC, RemoveCVRef<F>, NE>>> = 0>
  CDS_ATTR(2(nodiscard, constexpr(14))) auto findNotOf(F&& from) const& CDS_ATTR(noexcept(noexcept(
      impl::find(lvalue<R const>(), fwd<F>(from), NE{}, TrAll{})
  ))) -> decltype(impl::find(lvalue<R const>(), fwd<F>(from), NE{}, TrAll{})) {
    return impl::find(refl(), fwd<F>(from), NE{}, TrAll{});
  }

  template <typename F = initializer_list<Value>, EnableIf<Not<FindUsesAllocation<RNC, RemoveCVRef<F>, E>>> = 0>
  CDS_ATTR(2(nodiscard, constexpr(14))) auto findOf(F&& from) const&& CDS_ATTR(noexcept(noexcept(
      impl::find(rvalue<R const>(), fwd<F>(from), E{}, TrAll{})
  ))) -> decltype(impl::find(rvalue<R const>(), fwd<F>(from), E{}, TrAll{})) {
    return impl::find(mv(refl()), fwd<F>(from), E{}, TrAll{});
  }

  template <typename F = initializer_list<Value>, EnableIf<Not<FindUsesAllocation<RNC, RemoveCVRef<F>, NE>>> = 0>
  CDS_ATTR(2(nodiscard, constexpr(14))) auto findNotOf(F&& from) const&& CDS_ATTR(noexcept(noexcept(
      impl::find(rvalue<R const>(), fwd<F>(from), NE{}, TrAll{})
  ))) -> decltype(impl::find(rvalue<R const>(), fwd<F>(from), NE{}, TrAll{})) {
    return impl::find(mv(refl()), fwd<F>(from), NE{}, TrAll{});
  }

  template <typename F = initializer_list<Value>, EnableIf<Not<FindUsesAllocation<RNC, RemoveCVRef<F>, E>>> = 0>
  CDS_ATTR(2(nodiscard, constexpr(14))) auto findFirstOf(F&& from) const CDS_ATTR(noexcept(noexcept(
      impl::findFirst(rvalue<R const>(), fwd<F>(from), E{}, TrOne{})
  ))) -> decltype(impl::findFirst(rvalue<R const>(), fwd<F>(from), E{}, TrOne{})) {
    return impl::findFirst(refl(), fwd<F>(from), E{}, TrOne{});
  }

  template <typename F = initializer_list<Value>, EnableIf<Not<FindUsesAllocation<RNC, RemoveCVRef<F>, NE>>> = 0>
  CDS_ATTR(2(nodiscard, constexpr(14))) auto findFirstNotOf(F&& from) const CDS_ATTR(noexcept(noexcept(
      impl::findFirst(rvalue<R const>(), fwd<F>(from), NE{}, TrOne{})
  ))) -> decltype(impl::findFirst(rvalue<R const>(), fwd<F>(from), NE{}, TrOne{})) {
    return impl::findFirst(refl(), fwd<F>(from), NE{}, TrOne{});
  }

  template <typename F = initializer_list<Value>, EnableIf<Not<FindUsesAllocation<RNC, RemoveCVRef<F>, E>>> = 0>
  CDS_ATTR(2(nodiscard, constexpr(14))) auto findLastOf(F&& from) const CDS_ATTR(noexcept(noexcept(
      impl::findLast(rvalue<R const>(), fwd<F>(from), E{}, TrOne{})
  ))) -> decltype(impl::findLast(rvalue<R const>(), fwd<F>(from), E{}, TrOne{})) {
    return impl::findLast(refl(), fwd<F>(from), E{}, TrOne{});
  }

  template <typename F = initializer_list<Value>, EnableIf<Not<FindUsesAllocation<RNC, RemoveCVRef<F>, NE>>> = 0>
  CDS_ATTR(2(nodiscard, constexpr(14))) auto findLastNotOf(F&& from) const CDS_ATTR(noexcept(noexcept(
      impl::findLast(rvalue<R const>(), fwd<F>(from), NE{}, TrOne{})
  ))) -> decltype(impl::findLast(rvalue<R const>(), fwd<F>(from), NE{}, TrOne{})) {
    return impl::findLast(refl(), fwd<F>(from), NE{}, TrOne{});
  }

  template <
      typename F = initializer_list<Value>, typename U = FindUsesAllocation<RNC, RemoveCVRef<F>, E>,
      typename A = typename U::Alloc, EnableIf<And<U, IsAllocatorOrAllocatorSet<A>>> = 0
  > CDS_ATTR(2(nodiscard, constexpr(14))) auto findOf(F&& from, A&& alloc = A()) const& CDS_ATTR(noexcept(noexcept(
      impl::find(lvalue<R const>(), fwd<F>(from), E{}, TrAll{}, fwd<A>(alloc))
  ))) -> decltype(impl::find(lvalue<R const>(), fwd<F>(from), E{}, TrAll{}, fwd<A>(alloc))) {
    return impl::find(refl(), fwd<F>(from), E{}, TrAll{}, fwd<A>(alloc));
  }

  template <
       typename F = initializer_list<Value>, typename U = FindUsesAllocation<RNC, RemoveCVRef<F>, NE>,
      typename A = typename U::Alloc, EnableIf<And<U, IsAllocatorOrAllocatorSet<A>>> = 0
  > CDS_ATTR(2(nodiscard, constexpr(14))) auto findNotOf(F&& from, A&& alloc = A()) const& CDS_ATTR(noexcept(noexcept(
      impl::find(lvalue<R const>(), fwd<F>(from), NE{}, TrAll{}, fwd<A>(alloc))
  ))) -> decltype(impl::find(lvalue<R const>(), fwd<F>(from), NE{}, TrAll{}, fwd<A>(alloc))) {
    return impl::find(refl(), fwd<F>(from), NE{}, TrAll{}, fwd<A>(alloc));
  }

  template <
      typename F = initializer_list<Value>, typename U = FindUsesAllocation<RNC, RemoveCVRef<F>, E>,
      typename A = typename U::Alloc, EnableIf<And<U, IsAllocatorOrAllocatorSet<A>>> = 0
  > CDS_ATTR(2(nodiscard, constexpr(14))) auto findOf(F&& from, A&& alloc = A()) const&& CDS_ATTR(noexcept(noexcept(
      impl::find(rvalue<R const>(), fwd<F>(from), E{}, TrAll{}, fwd<A>(alloc))
  ))) -> decltype(impl::find(rvalue<R const>(), fwd<F>(from), E{}, TrAll{}, fwd<A>(alloc))) {
    return impl::find(mv(refl()), fwd<F>(from), E{}, TrAll{}, fwd<A>(alloc));
  }

  template <
      typename F = initializer_list<Value>, typename U = FindUsesAllocation<RNC, RemoveCVRef<F>, NE>,
      typename A = typename U::Alloc, EnableIf<And<U, IsAllocatorOrAllocatorSet<A>>> = 0
  > CDS_ATTR(2(nodiscard, constexpr(14))) auto findNotOf(F&& from, A&& alloc = A()) const&& CDS_ATTR(noexcept(noexcept(
      impl::find(rvalue<R const>(), fwd<F>(from), NE{}, TrAll{}, fwd<A>(alloc))
  ))) -> decltype(impl::find(rvalue<R const>(), fwd<F>(from), NE{}, TrAll{}, fwd<A>(alloc))) {
    return impl::find(mv(refl()), fwd<F>(from), NE{}, TrAll{}, fwd<A>(alloc));
  }

  template <
      typename F = initializer_list<Value>, typename U = FindUsesAllocation<RNC, RemoveCVRef<F>, E>,
      typename A = typename U::Alloc, EnableIf<And<U, IsAllocatorOrAllocatorSet<A>>> = 0
  > CDS_ATTR(2(nodiscard, constexpr(14))) auto findFirstOf(F&& from, A&& alloc = A()) const CDS_ATTR(noexcept(noexcept(
      impl::findFirst(rvalue<R const>(), fwd<F>(from), E{}, TrOne{}, fwd<A>(alloc))
  ))) -> decltype(impl::findFirst(rvalue<R const>(), fwd<F>(from), E{}, TrOne{}, fwd<A>(alloc))) {
    return impl::findFirst(refl(), fwd<F>(from), E{}, TrOne{}, fwd<A>(alloc));
  }

  template <
      typename F = initializer_list<Value>, typename U = FindUsesAllocation<RNC, RemoveCVRef<F>, NE>,
      typename A = typename U::Alloc, EnableIf<And<U, IsAllocatorOrAllocatorSet<A>>> = 0
  > CDS_ATTR(2(nodiscard, constexpr(14))) auto findFirstNotOf(F&& from, A&& alloc = A()) const CDS_ATTR(noexcept(
      noexcept(impl::findFirst(rvalue<R const>(), fwd<F>(from), NE{}, TrOne{}, fwd<A>(alloc)))
  )) -> decltype(impl::findFirst(rvalue<R const>(), fwd<F>(from), NE{}, TrOne{}, fwd<A>(alloc))) {
    return impl::findFirst(refl(), fwd<F>(from), NE{}, TrOne{}, fwd<A>(alloc));
  }

  template <
      typename F = initializer_list<Value>, typename U = FindUsesAllocation<RNC, RemoveCVRef<F>, E>,
      typename A = typename U::Alloc, EnableIf<And<U, IsAllocatorOrAllocatorSet<A>>> = 0
  > CDS_ATTR(2(nodiscard, constexpr(14))) auto findLastOf(F&& from, A&& alloc = A()) const CDS_ATTR(noexcept(noexcept(
      impl::findLast(rvalue<R const>(), fwd<F>(from), E{}, TrOne{}, fwd<A>(alloc))
  ))) -> decltype(impl::findLast(rvalue<R const>(), fwd<F>(from), E{}, TrOne{}, fwd<A>(alloc))) {
    return impl::findLast(refl(), fwd<F>(from), E{}, TrOne{}, fwd<A>(alloc));
  }

  template <
      typename F = initializer_list<Value>, typename U = FindUsesAllocation<RNC, RemoveCVRef<F>, NE>,
      typename A = typename U::Alloc, EnableIf<And<U, IsAllocatorOrAllocatorSet<A>>> = 0
  > CDS_ATTR(2(nodiscard, constexpr(14))) auto findLastNotOf(F&& from, A&& alloc = A()) const CDS_ATTR(noexcept(
      noexcept(impl::findLast(rvalue<R const>(), fwd<F>(from), NE{}, TrOne{}, fwd<A>(alloc)))
  )) -> decltype(impl::findLast(rvalue<R const>(), fwd<F>(from), NE{}, TrOne{}, fwd<A>(alloc))) {
    return impl::findLast(refl(), fwd<F>(from), NE{}, TrOne{}, fwd<A>(alloc));
  }
};

template <typename, typename, typename, typename = void> class FindOfByProjectorStaticBinding {};

template <typename R, typename TrAll, typename TrOne> class FindOfByProjectorStaticBinding<R, TrAll, TrOne> {
  CDS_ATTR(2(nodiscard, constexpr(14))) auto refl() noexcept -> R& {
    return *static_cast<R*>(this);
  }
  
protected:
  using Value = typename IterableTraits<R>::Value;
  using E = Contains<Equal<>>;
  using NE = NotContains<Equal<>>;

public:
  template <
      typename P, typename F = initializer_list<Value>,
        EnableIf<And<Not<FindUsesAllocation<R, RemoveCVRef<F>, E>>, Not<IsAllocatorOrAllocatorSet<P>>>> = 0
  > CDS_ATTR(2(nodiscard, constexpr(14))) auto findOf(F&& from, P&& projector)& CDS_ATTR(noexcept(noexcept(
      impl::find(lvalue<R>(), fwd<F>(from), fwd<P>(projector), E{}, TrAll{})
  ))) -> decltype(impl::find(lvalue<R>(), fwd<F>(from), fwd<P>(projector) , E{}, TrAll{})) {
    return impl::find(refl(), fwd<F>(from), fwd<P>(projector), E{}, TrAll{});
  }

  template <
      typename P, typename F = initializer_list<Value>,
      EnableIf<And<Not<FindUsesAllocation<R, RemoveCVRef<F>, NE>>, Not<IsAllocatorOrAllocatorSet<P>>>> = 0
  > CDS_ATTR(2(nodiscard, constexpr(14))) auto findNotOf(F&& from, P&& projector)& CDS_ATTR(noexcept(noexcept(
      impl::find(lvalue<R>(), fwd<F>(from), fwd<P>(projector), NE{}, TrAll{})
  ))) -> decltype(impl::find(lvalue<R>(), fwd<F>(from), fwd<P>(projector), NE{}, TrAll{})) {
    return impl::find(refl(), fwd<F>(from), fwd<P>(projector), NE{}, TrAll{});
  }

  template <
      typename P, typename F = initializer_list<Value>,
      EnableIf<And<Not<FindUsesAllocation<R, RemoveCVRef<F>, E>>, Not<IsAllocatorOrAllocatorSet<P>>>> = 0
  > CDS_ATTR(2(nodiscard, constexpr(14))) auto findOf(F&& from, P&& projector)&& CDS_ATTR(noexcept(noexcept(
      impl::find(rvalue<R>(), fwd<F>(from), fwd<P>(projector), E{}, TrAll{})
  ))) -> decltype(impl::find(rvalue<R>(), fwd<F>(from), fwd<P>(projector) , E{}, TrAll{})) {
    return impl::find(mv(refl()), fwd<F>(from), fwd<P>(projector), E{}, TrAll{});
  }

  template <
      typename P, typename F = initializer_list<Value>,
      EnableIf<And<Not<FindUsesAllocation<R, RemoveCVRef<F>, NE>>, Not<IsAllocatorOrAllocatorSet<P>>>> = 0
  > CDS_ATTR(2(nodiscard, constexpr(14))) auto findNotOf(F&& from, P&& projector)&& CDS_ATTR(noexcept(noexcept(
      impl::find(rvalue<R>(), fwd<F>(from), fwd<P>(projector), NE{}, TrAll{})
  ))) -> decltype(impl::find(rvalue<R>(), fwd<F>(from), fwd<P>(projector), NE{}, TrAll{})) {
    return impl::find(mv(refl()), fwd<F>(from), fwd<P>(projector), NE{}, TrAll{});
  }

  template <
      typename P, typename F = initializer_list<Value>,
      EnableIf<And<Not<FindUsesAllocation<R, RemoveCVRef<F>, E>>, Not<IsAllocatorOrAllocatorSet<P>>>> = 0
  > CDS_ATTR(2(nodiscard, constexpr(14))) auto findFirstOf(F&& from, P&& projector) CDS_ATTR(noexcept(noexcept(
      impl::findFirst(rvalue<R>(), fwd<F>(from), fwd<P>(projector), E{}, TrOne{})
  ))) -> decltype(impl::findFirst(rvalue<R>(), fwd<F>(from), fwd<P>(projector), E{}, TrOne{})) {
    return impl::findFirst(refl(), fwd<F>(from), fwd<P>(projector), E{}, TrOne{});
  }

  template <
      typename P, typename F = initializer_list<Value>,
      EnableIf<And<Not<FindUsesAllocation<R, RemoveCVRef<F>, NE>>, Not<IsAllocatorOrAllocatorSet<P>>>> = 0
  > CDS_ATTR(2(nodiscard, constexpr(14))) auto findFirstNotOf(F&& from, P&& projector) CDS_ATTR(noexcept(noexcept(
      impl::findFirst(rvalue<R>(), fwd<F>(from), fwd<P>(projector), NE{}, TrOne{})
  ))) -> decltype(impl::findFirst(rvalue<R>(), fwd<F>(from), fwd<P>(projector), NE{}, TrOne{})) {
    return impl::findFirst(refl(), fwd<F>(from), fwd<P>(projector), NE{}, TrOne{});
  }

  template <
      typename P, typename F = initializer_list<Value>,
      EnableIf<And<Not<FindUsesAllocation<R, RemoveCVRef<F>, E>>, Not<IsAllocatorOrAllocatorSet<P>>>> = 0
  > CDS_ATTR(2(nodiscard, constexpr(14))) auto findLastOf(F&& from, P&& projector) CDS_ATTR(noexcept(noexcept(
      impl::findLast(rvalue<R>(), fwd<F>(from), fwd<P>(projector), E{}, TrOne{})
  ))) -> decltype(impl::findLast(rvalue<R>(), fwd<F>(from), fwd<P>(projector), E{}, TrOne{})) {
    return impl::findLast(refl(), fwd<F>(from), fwd<P>(projector), E{}, TrOne{});
  }

  template <
      typename P, typename F = initializer_list<Value>,
      EnableIf<And<Not<FindUsesAllocation<R, RemoveCVRef<F>, NE>>, Not<IsAllocatorOrAllocatorSet<P>>>> = 0
  > CDS_ATTR(2(nodiscard, constexpr(14))) auto findLastNotOf(F&& from, P&& projector) CDS_ATTR(noexcept(noexcept(
      impl::findLast(rvalue<R>(), fwd<F>(from), fwd<P>(projector), NE{}, TrOne{})
  ))) -> decltype(impl::findLast(rvalue<R>(), fwd<F>(from), fwd<P>(projector), NE{}, TrOne{})) {
    return impl::findLast(refl(), fwd<F>(from), fwd<P>(projector), NE{}, TrOne{});
  }

  template <
      typename P, typename F = initializer_list<Value>, typename U = FindUsesAllocation<R, RemoveCVRef<F>, E>,
      typename A = typename U::Alloc,
      EnableIf<And<U, IsAllocatorOrAllocatorSet<A>, Not<IsAllocatorOrAllocatorSet<P>>>> = 0
  > CDS_ATTR(2(nodiscard, constexpr(14))) auto findOf(F&& from, P&& projector, A&& alloc = A())&
      CDS_ATTR(noexcept(
          noexcept(impl::find(lvalue<R>(), fwd<F>(from), fwd<P>(projector), E{}, TrAll{}, fwd<A>(alloc)))
      )) -> decltype(impl::find(lvalue<R>(), fwd<F>(from), fwd<P>(projector) , E{}, TrAll{}, fwd<A>(alloc))) {
    return impl::find(refl(), fwd<F>(from), fwd<P>(projector), E{}, TrAll{}, fwd<A>(alloc));
  }

  template <
      typename P, typename F = initializer_list<Value>, typename U = FindUsesAllocation<R, RemoveCVRef<F>, NE>,
      typename A = typename U::Alloc,
      EnableIf<And<U, IsAllocatorOrAllocatorSet<A>, Not<IsAllocatorOrAllocatorSet<P>>>> = 0
  > CDS_ATTR(2(nodiscard, constexpr(14))) auto findNotOf(F&& from, P&& projector, A&& alloc = A())&
      CDS_ATTR(noexcept(
          noexcept(impl::find(lvalue<R>(), fwd<F>(from), fwd<P>(projector), NE{}, TrAll{}, fwd<A>(alloc)))
      )) -> decltype(impl::find(lvalue<R>(), fwd<F>(from), fwd<P>(projector), NE{}, TrAll{}, fwd<A>(alloc))) {
    return impl::find(refl(), fwd<F>(from), fwd<P>(projector), NE{}, TrAll{}, fwd<A>(alloc));
  }

  template <
      typename P, typename F = initializer_list<Value>, typename U = FindUsesAllocation<R, RemoveCVRef<F>, E>,
      typename A = typename U::Alloc,
      EnableIf<And<U, IsAllocatorOrAllocatorSet<A>, Not<IsAllocatorOrAllocatorSet<P>>>> = 0
  > CDS_ATTR(2(nodiscard, constexpr(14))) auto findOf(F&& from, P&& projector, A&& alloc = A())&&
      CDS_ATTR(noexcept(
          noexcept(impl::find(rvalue<R>(), fwd<F>(from), fwd<P>(projector), E{}, TrAll{}, fwd<A>(alloc)))
      )) -> decltype(impl::find(rvalue<R>(), fwd<F>(from), fwd<P>(projector) , E{}, TrAll{}, fwd<A>(alloc))) {
    return impl::find(mv(refl()), fwd<F>(from), fwd<P>(projector), E{}, TrAll{}, fwd<A>(alloc));
  }

  template <
      typename P, typename F = initializer_list<Value>, typename U = FindUsesAllocation<R, RemoveCVRef<F>, NE>,
      typename A = typename U::Alloc,
      EnableIf<And<U, IsAllocatorOrAllocatorSet<A>, Not<IsAllocatorOrAllocatorSet<P>>>> = 0
  > CDS_ATTR(2(nodiscard, constexpr(14))) auto findNotOf(F&& from, P&& projector, A&& alloc = A())&&
      CDS_ATTR(noexcept(
          noexcept(impl::find(rvalue<R>(), fwd<F>(from), fwd<P>(projector), NE{}, TrAll{}, fwd<A>(alloc)))
      )) -> decltype(impl::find(rvalue<R>(), fwd<F>(from), fwd<P>(projector), NE{}, TrAll{}, fwd<A>(alloc))) {
    return impl::find(mv(refl()), fwd<F>(from), fwd<P>(projector), NE{}, TrAll{}, fwd<A>(alloc));
  }

  template <
      typename P, typename F = initializer_list<Value>, typename U = FindUsesAllocation<R, RemoveCVRef<F>, E>,
      typename A = typename U::Alloc,
      EnableIf<And<U, IsAllocatorOrAllocatorSet<A>, Not<IsAllocatorOrAllocatorSet<P>>>> = 0
  > CDS_ATTR(2(nodiscard, constexpr(14))) auto findFirstOf(F&& from, P&& projector, A&& alloc = A())
      CDS_ATTR(noexcept(
          noexcept(impl::findFirst(rvalue<R>(), fwd<F>(from), fwd<P>(projector), E{}, TrOne{}, fwd<A>(alloc)))
      )) -> decltype(impl::findFirst(rvalue<R>(), fwd<F>(from), fwd<P>(projector), E{}, TrOne{}, fwd<A>(alloc))) {
    return impl::findFirst(refl(), fwd<F>(from), fwd<P>(projector), E{}, TrOne{}, fwd<A>(alloc));
  }

  template <
      typename P, typename F = initializer_list<Value>, typename U = FindUsesAllocation<R, RemoveCVRef<F>, NE>,
      typename A = typename U::Alloc,
      EnableIf<And<U, IsAllocatorOrAllocatorSet<A>, Not<IsAllocatorOrAllocatorSet<P>>>> = 0
  > CDS_ATTR(2(nodiscard, constexpr(14))) auto findFirstNotOf(F&& from, P&& projector, A&& alloc = A())
      CDS_ATTR(noexcept(
          noexcept(impl::findFirst(rvalue<R>(), fwd<F>(from), fwd<P>(projector), NE{}, TrOne{}, fwd<A>(alloc)))
      )) -> decltype(impl::findFirst(rvalue<R>(), fwd<F>(from), fwd<P>(projector), NE{}, TrOne{}, fwd<A>(alloc))) {
    return impl::findFirst(refl(), fwd<F>(from), fwd<P>(projector), NE{}, TrOne{}, fwd<A>(alloc));
  }

  template <
      typename P, typename F = initializer_list<Value>, typename U = FindUsesAllocation<R, RemoveCVRef<F>, E>,
      typename A = typename U::Alloc,
      EnableIf<And<U, IsAllocatorOrAllocatorSet<A>, Not<IsAllocatorOrAllocatorSet<P>>>> = 0
  > CDS_ATTR(2(nodiscard, constexpr(14))) auto findLastOf(F&& from, P&& projector, A&& alloc = A())
      CDS_ATTR(noexcept(
          noexcept(impl::findLast(rvalue<R>(), fwd<F>(from), fwd<P>(projector), E{}, TrOne{}, fwd<A>(alloc)))
      )) -> decltype(impl::findLast(rvalue<R>(), fwd<F>(from), fwd<P>(projector), E{}, TrOne{}, fwd<A>(alloc))) {
    return impl::findLast(refl(), fwd<F>(from), fwd<P>(projector), E{}, TrOne{}, fwd<A>(alloc));
  }

  template <
      typename P, typename F = initializer_list<Value>, typename U = FindUsesAllocation<R, RemoveCVRef<F>, NE>,
      typename A = typename U::Alloc,
      EnableIf<And<U, IsAllocatorOrAllocatorSet<A>, Not<IsAllocatorOrAllocatorSet<P>>>> = 0
  > CDS_ATTR(2(nodiscard, constexpr(14))) auto findLastNotOf(F&& from, P&& projector, A&& alloc = A())
      CDS_ATTR(noexcept(
          noexcept(impl::findLast(rvalue<R>(), fwd<F>(from), fwd<P>(projector), NE{}, TrOne{}, fwd<A>(alloc)))
      )) -> decltype(impl::findLast(rvalue<R>(), fwd<F>(from), fwd<P>(projector), NE{}, TrOne{}, fwd<A>(alloc))) {
    return impl::findLast(refl(), fwd<F>(from), fwd<P>(projector), NE{}, TrOne{}, fwd<A>(alloc));
  }
};

template <typename R, typename TrAll, typename TrOne> class FindOfByProjectorStaticBinding<R const, TrAll, TrOne> {
  CDS_ATTR(2(nodiscard, constexpr(11))) auto refl() const noexcept -> R const& {
    return *static_cast<R const*>(this);
  }
  
protected:
  using Value = typename IterableTraits<R>::Value;
  using E = Contains<Equal<>>;
  using NE = NotContains<Equal<>>;
  using RNC = RemoveConst<R>;

public:
  template <
      typename P, typename F = initializer_list<Value>,
      EnableIf<And<Not<FindUsesAllocation<RNC, RemoveCVRef<F>, E>>, Not<IsAllocatorOrAllocatorSet<P>>>> = 0
  > CDS_ATTR(2(nodiscard, constexpr(14))) auto findOf(F&& from, P&& projector) const& CDS_ATTR(noexcept(noexcept(
      impl::find(lvalue<R const>(), fwd<F>(from), fwd<P>(projector), E{}, TrAll{})
  ))) -> decltype(impl::find(lvalue<R const>(), fwd<F>(from), fwd<P>(projector), E{}, TrAll{})) {
    return impl::find(refl(), fwd<F>(from), fwd<P>(projector), E{}, TrAll{});
  }

  template <
      typename P, typename F = initializer_list<Value>,
      EnableIf<And<Not<FindUsesAllocation<RNC, RemoveCVRef<F>, NE>>, Not<IsAllocatorOrAllocatorSet<P>>>> = 0
  > CDS_ATTR(2(nodiscard, constexpr(14))) auto findNotOf(F&& from, P&& projector) const& CDS_ATTR(noexcept(noexcept(
      impl::find(lvalue<R const>(), fwd<F>(from), fwd<P>(projector), NE{}, TrAll{})
  ))) -> decltype(impl::find(lvalue<R const>(), fwd<F>(from), fwd<P>(projector), NE{}, TrAll{})) {
    return impl::find(refl(), fwd<F>(from), fwd<P>(projector), NE{}, TrAll{});
  }

  template <
      typename P, typename F = initializer_list<Value>,
      EnableIf<And<Not<FindUsesAllocation<RNC, RemoveCVRef<F>, E>>, Not<IsAllocatorOrAllocatorSet<P>>>> = 0
  > CDS_ATTR(2(nodiscard, constexpr(14))) auto findOf(F&& from, P&& projector) const&& CDS_ATTR(noexcept(noexcept(
      impl::find(rvalue<R const>(), fwd<F>(from), fwd<P>(projector), E{}, TrAll{})
  ))) -> decltype(impl::find(rvalue<R const>(), fwd<F>(from), fwd<P>(projector), E{}, TrAll{})) {
    return impl::find(mv(refl()), fwd<F>(from), fwd<P>(projector), E{}, TrAll{});
  }

  template <
      typename P, typename F = initializer_list<Value>,
      EnableIf<And<Not<FindUsesAllocation<RNC, RemoveCVRef<F>, NE>>, Not<IsAllocatorOrAllocatorSet<P>>>> = 0
  > CDS_ATTR(2(nodiscard, constexpr(14))) auto findNotOf(F&& from, P&& projector) const&& CDS_ATTR(noexcept(noexcept(
      impl::find(rvalue<R const>(), fwd<F>(from), fwd<P>(projector), NE{}, TrAll{})
  ))) -> decltype(impl::find(rvalue<R const>(), fwd<F>(from), fwd<P>(projector), NE{}, TrAll{})) {
    return impl::find(mv(refl()), fwd<F>(from), fwd<P>(projector), NE{}, TrAll{});
  }

  template <
      typename P, typename F = initializer_list<Value>,
      EnableIf<And<Not<FindUsesAllocation<RNC, RemoveCVRef<F>, E>>, Not<IsAllocatorOrAllocatorSet<P>>>> = 0
  > CDS_ATTR(2(nodiscard, constexpr(14))) auto findFirstOf(F&& from, P&& projector) const CDS_ATTR(noexcept(noexcept(
      impl::findFirst(rvalue<R const>(), fwd<F>(from), fwd<P>(projector), E{}, TrOne{})
  ))) -> decltype(impl::findFirst(rvalue<R const>(), fwd<F>(from), fwd<P>(projector), E{}, TrOne{})) {
    return impl::findFirst(refl(), fwd<F>(from), fwd<P>(projector), E{}, TrOne{});
  }

  template <
      typename P, typename F = initializer_list<Value>,
      EnableIf<And<Not<FindUsesAllocation<RNC, RemoveCVRef<F>, NE>>, Not<IsAllocatorOrAllocatorSet<P>>>> = 0
  > CDS_ATTR(2(nodiscard, constexpr(14))) auto findFirstNotOf(F&& from, P&& projector) const CDS_ATTR(noexcept(noexcept(
      impl::findFirst(rvalue<R const>(), fwd<F>(from), fwd<P>(projector), NE{}, TrOne{})
  ))) -> decltype(impl::findFirst(rvalue<R const>(), fwd<F>(from), fwd<P>(projector), NE{}, TrOne{})) {
    return impl::findFirst(refl(), fwd<F>(from), fwd<P>(projector), NE{}, TrOne{});
  }

  template <
      typename P, typename F = initializer_list<Value>,
      EnableIf<And<Not<FindUsesAllocation<RNC, RemoveCVRef<F>, E>>, Not<IsAllocatorOrAllocatorSet<P>>>> = 0
  > CDS_ATTR(2(nodiscard, constexpr(14))) auto findLastOf(F&& from, P&& projector) const CDS_ATTR(noexcept(noexcept(
      impl::findLast(rvalue<R const>(), fwd<F>(from), fwd<P>(projector), E{}, TrOne{})
  ))) -> decltype(impl::findLast(rvalue<R const>(), fwd<F>(from), fwd<P>(projector), E{}, TrOne{})) {
    return impl::findLast(refl(), fwd<F>(from), fwd<P>(projector), E{}, TrOne{});
  }

  template <
      typename P, typename F = initializer_list<Value>,
      EnableIf<And<Not<FindUsesAllocation<RNC, RemoveCVRef<F>, NE>>, Not<IsAllocatorOrAllocatorSet<P>>>> = 0
  > CDS_ATTR(2(nodiscard, constexpr(14))) auto findLastNotOf(F&& from, P&& projector) const CDS_ATTR(noexcept(noexcept(
      impl::findLast(rvalue<R const>(), fwd<F>(from), fwd<P>(projector), NE{}, TrOne{})
  ))) -> decltype(impl::findLast(rvalue<R const>(), fwd<F>(from), fwd<P>(projector), NE{}, TrOne{})) {
    return impl::findLast(refl(), fwd<F>(from), fwd<P>(projector), NE{}, TrOne{});
  }

  template <
      typename P, typename F = initializer_list<Value>, typename U = FindUsesAllocation<RNC, RemoveCVRef<F>, E>,
      typename A = typename U::Alloc,
      EnableIf<And<U, IsAllocatorOrAllocatorSet<A>, Not<IsAllocatorOrAllocatorSet<P>>>> = 0
  > CDS_ATTR(2(nodiscard, constexpr(14))) auto findOf(F&& from, P&& projector, A&& alloc = A()) const&
      CDS_ATTR(noexcept(
          noexcept(impl::find(lvalue<R const>(), fwd<F>(from), fwd<P>(projector), E{}, TrAll{}, fwd<A>(alloc)))
      )) -> decltype(impl::find(lvalue<R const>(), fwd<F>(from), fwd<P>(projector), E{}, TrAll{}, fwd<A>(alloc))) {
    return impl::find(refl(), fwd<F>(from), fwd<P>(projector), E{}, TrAll{}, fwd<A>(alloc));
  }

  template <
      typename P, typename F = initializer_list<Value>, typename U = FindUsesAllocation<RNC, RemoveCVRef<F>, NE>,
      typename A = typename U::Alloc,
      EnableIf<And<U, IsAllocatorOrAllocatorSet<A>, Not<IsAllocatorOrAllocatorSet<P>>>> = 0
  > CDS_ATTR(2(nodiscard, constexpr(14))) auto findNotOf(F&& from, P&& projector, A&& alloc = A()) const&
      CDS_ATTR(noexcept(
          noexcept(impl::find(lvalue<R const>(), fwd<F>(from), fwd<P>(projector), NE{}, TrAll{}, fwd<A>(alloc)))
      )) -> decltype(impl::find(lvalue<R const>(), fwd<F>(from), fwd<P>(projector), NE{}, TrAll{}, fwd<A>(alloc))) {
    return impl::find(refl(), fwd<F>(from), fwd<P>(projector), NE{}, TrAll{}, fwd<A>(alloc));
  }

  template <
      typename P, typename F = initializer_list<Value>, typename U = FindUsesAllocation<RNC, RemoveCVRef<F>, E>,
      typename A = typename U::Alloc,
      EnableIf<And<U, IsAllocatorOrAllocatorSet<A>, Not<IsAllocatorOrAllocatorSet<P>>>> = 0
  > CDS_ATTR(2(nodiscard, constexpr(14))) auto findOf(F&& from, P&& projector, A&& alloc = A()) const&&
      CDS_ATTR(noexcept(
          noexcept(impl::find(rvalue<R const>(), fwd<F>(from), fwd<P>(projector), E{}, TrAll{}, fwd<A>(alloc)))
      )) -> decltype(impl::find(rvalue<R const>(), fwd<F>(from), fwd<P>(projector), E{}, TrAll{}, fwd<A>(alloc))) {
    return impl::find(mv(refl()), fwd<F>(from), fwd<P>(projector), E{}, TrAll{}, fwd<A>(alloc));
  }

  template <
      typename P, typename F = initializer_list<Value>, typename U = FindUsesAllocation<RNC, RemoveCVRef<F>, NE>,
      typename A = typename U::Alloc,
      EnableIf<And<U, IsAllocatorOrAllocatorSet<A>, Not<IsAllocatorOrAllocatorSet<P>>>> = 0
  > CDS_ATTR(2(nodiscard, constexpr(14))) auto findNotOf(F&& from, P&& projector, A&& alloc = A()) const&&
      CDS_ATTR(noexcept(
          noexcept(impl::find(rvalue<R const>(), fwd<F>(from), fwd<P>(projector), NE{}, TrAll{}, fwd<A>(alloc)))
      )) -> decltype(impl::find(rvalue<R const>(), fwd<F>(from), fwd<P>(projector), NE{}, TrAll{}, fwd<A>(alloc))) {
    return impl::find(mv(refl()), fwd<F>(from), fwd<P>(projector), NE{}, TrAll{}, fwd<A>(alloc));
  }

  template <
      typename P, typename F = initializer_list<Value>, typename U = FindUsesAllocation<RNC, RemoveCVRef<F>, E>,
      typename A = typename U::Alloc,
      EnableIf<And<U, IsAllocatorOrAllocatorSet<A>, Not<IsAllocatorOrAllocatorSet<P>>>> = 0
  > CDS_ATTR(2(nodiscard, constexpr(14))) auto findFirstOf(F&& from, P&& projector, A&& alloc = A()) const
      CDS_ATTR(noexcept(
          noexcept(impl::findFirst(rvalue<R const>(), fwd<F>(from), fwd<P>(projector), E{}, TrOne{}, fwd<A>(alloc)))
      )) -> decltype(impl::findFirst(rvalue<R const>(), fwd<F>(from), fwd<P>(projector), E{}, TrOne{}, fwd<A>(alloc))) {
    return impl::findFirst(refl(), fwd<F>(from), fwd<P>(projector), E{}, TrOne{}, fwd<A>(alloc));
  }

  template <
      typename P, typename F = initializer_list<Value>, typename U = FindUsesAllocation<RNC, RemoveCVRef<F>, NE>,
      typename A = typename U::Alloc,
      EnableIf<And<U, IsAllocatorOrAllocatorSet<A>, Not<IsAllocatorOrAllocatorSet<P>>>> = 0
  > CDS_ATTR(2(nodiscard, constexpr(14))) auto findFirstNotOf(F&& from, P&& projector, A&& alloc = A()) const
      CDS_ATTR(noexcept(
          noexcept(impl::findFirst(rvalue<R const>(), fwd<F>(from), fwd<P>(projector), NE{}, TrOne{}, fwd<A>(alloc)))
      ))
      -> decltype(impl::findFirst(rvalue<R const>(), fwd<F>(from), fwd<P>(projector), NE{}, TrOne{}, fwd<A>(alloc))) {
    return impl::findFirst(refl(), fwd<F>(from), fwd<P>(projector), NE{}, TrOne{}, fwd<A>(alloc));
  }

  template <
      typename P, typename F = initializer_list<Value>, typename U = FindUsesAllocation<RNC, RemoveCVRef<F>, E>,
      typename A = typename U::Alloc,
      EnableIf<And<U, IsAllocatorOrAllocatorSet<A>, Not<IsAllocatorOrAllocatorSet<P>>>> = 0
  > CDS_ATTR(2(nodiscard, constexpr(14))) auto findLastOf(F&& from, P&& projector, A&& alloc = A()) const
      CDS_ATTR(noexcept(
          noexcept(impl::findLast(rvalue<R const>(), fwd<F>(from), fwd<P>(projector), E{}, TrOne{}, fwd<A>(alloc)))
      )) -> decltype(impl::findLast(rvalue<R const>(), fwd<F>(from), fwd<P>(projector), E{}, TrOne{}, fwd<A>(alloc))) {
    return impl::findLast(refl(), fwd<F>(from), fwd<P>(projector), E{}, TrOne{}, fwd<A>(alloc));
  }

  template <
      typename P, typename F = initializer_list<Value>, typename U = FindUsesAllocation<RNC, RemoveCVRef<F>, NE>,
      typename A = typename U::Alloc,
      EnableIf<And<U, IsAllocatorOrAllocatorSet<A>, Not<IsAllocatorOrAllocatorSet<P>>>> = 0
  > CDS_ATTR(2(nodiscard, constexpr(14))) auto findLastNotOf(F&& from, P&& projector, A&& alloc = A()) const
      CDS_ATTR(noexcept(
          noexcept(impl::findLast(rvalue<R const>(), fwd<F>(from), fwd<P>(projector), NE{}, TrOne{}, fwd<A>(alloc)))
      )) -> decltype(impl::findLast(rvalue<R const>(), fwd<F>(from), fwd<P>(projector), NE{}, TrOne{}, fwd<A>(alloc))) {
    return impl::findLast(refl(), fwd<F>(from), fwd<P>(projector), NE{}, TrOne{}, fwd<A>(alloc));
  }
};

namespace findOfDeriv {
using meta::True;
using meta::False;
using meta::Any;
using meta::Bind;
using meta::Ph;

using sel::Value;
using sel::Projector;
using sel::Mutable;
using sel::Immutable;
using sel::ContainsSelector;

template <
    typename P,
    typename = typename ContainsSelector<P, Value>::Type,
    typename = typename ContainsSelector<P, Projector>::Type
> struct MethodSelector {
  static_assert(
      Any<Bind<ContainsSelector, P, Ph<0>>::template Type, Value, Projector>::value,
      "Must select Value, Projector or both"
  );
};

template <typename P> struct MethodSelector<P, True, False> {
  template <typename... A> class CDS_ATTR(ebo) Type :
    public FindOfByValueStaticBinding<A...> {};
};

template <typename P> struct MethodSelector<P, False, True> {
  template <typename... A> class CDS_ATTR(ebo) Type :
    public FindOfByProjectorStaticBinding<A...> {};
};

template <typename P> struct MethodSelector<P, True, True> {
  template <typename... A> class CDS_ATTR(ebo) Type :
      public FindOfByValueStaticBinding<A...>,
      public FindOfByProjectorStaticBinding<A...> {
  public:
    using FindOfByValueStaticBinding<A...>::findOf;
    using FindOfByValueStaticBinding<A...>::findNotOf;
    using FindOfByValueStaticBinding<A...>::findFirstOf;
    using FindOfByValueStaticBinding<A...>::findFirstNotOf;
    using FindOfByValueStaticBinding<A...>::findLastOf;
    using FindOfByValueStaticBinding<A...>::findLastNotOf;

    using FindOfByProjectorStaticBinding<A...>::findOf;
    using FindOfByProjectorStaticBinding<A...>::findNotOf;
    using FindOfByProjectorStaticBinding<A...>::findFirstOf;
    using FindOfByProjectorStaticBinding<A...>::findFirstNotOf;
    using FindOfByProjectorStaticBinding<A...>::findLastOf;
    using FindOfByProjectorStaticBinding<A...>::findLastNotOf;
  };
};

template <
    typename P,
    typename = typename ContainsSelector<P, Mutable>::Type,
    typename = typename ContainsSelector<P, Immutable>::Type
> struct MutationSelector {
  static_assert(
      Any<Bind<ContainsSelector, P, Ph<0>>::template Type, Mutable, Immutable>::value,
      "Must select Mutable, Immutable or both"
  );
};

template <typename P> struct MutationSelector<P, True, False> {
  template <typename... A> class CDS_ATTR(ebo) Type :
      public MethodSelector<P>::template Type<A...> {};
};

template <typename P> struct MutationSelector<P, False, True> {
  template <typename R, typename... A> class CDS_ATTR(ebo) Type :
      public MethodSelector<P>::template Type<R const, A...> {};
};

template <typename P> struct MutationSelector<P, True, True> {
  template <typename R, typename... A> class CDS_ATTR(ebo) Type :
      public MethodSelector<P>::template Type<R, A...>,
      public MethodSelector<P>::template Type<R const, A...> {
  public:
    using MethodSelector<P>::template Type<R, A...>::findOf;
    using MethodSelector<P>::template Type<R, A...>::findNotOf;
    using MethodSelector<P>::template Type<R const, A...>::findOf;
    using MethodSelector<P>::template Type<R const, A...>::findNotOf;

    using MethodSelector<P>::template Type<R, A...>::findFirstOf;
    using MethodSelector<P>::template Type<R, A...>::findFirstNotOf;
    using MethodSelector<P>::template Type<R const, A...>::findFirstOf;
    using MethodSelector<P>::template Type<R const, A...>::findFirstNotOf;

    using MethodSelector<P>::template Type<R, A...>::findLastOf;
    using MethodSelector<P>::template Type<R, A...>::findLastNotOf;
    using MethodSelector<P>::template Type<R const, A...>::findLastOf;
    using MethodSelector<P>::template Type<R const, A...>::findLastNotOf;
  };
};
} // namespace findOfDeriv

template <
    typename R, typename P,
    typename TrAll = FindResultTransformer<>,
    typename TrOne = FindPreserveTransformer<>
> class CDS_ATTR(ebo) FindOfStaticBinding :
    public findOfDeriv::MutationSelector<P>::template Type<R, TrAll, TrOne> {};
} // namespace impl
} // namespace cds

#endif // CDS_BINDINGS_STATIC_FIND_OF_BINDING_STATIC_HPP
