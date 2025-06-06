//
// Created by loghin on 3/16/24.
//

#ifndef CDS_ALGORITHM_GENERIC_FIND_HPP
#define CDS_ALGORITHM_GENERIC_FIND_HPP
#pragma once

#include "../meta/Extension.hpp"
#include "../meta/Ignore.hpp"

#include "../iterator/Iterator.hpp"

#include <cds/functional/Invoke>

#if CDS_ATTR(sentinel)
#include <cds/iterator/Sentinel>
#endif // CDS_ATTR(sentinel)

#if CDS_ATTR(msvc)
#pragma warning(disable: 4180)
#endif

namespace cds {
namespace iterator {
namespace impl {
using meta::lvalue;
using meta::rvalue;

namespace fn = cds::functional;

#if CDS_ATTR(sentinel)
using iterator::Sentinel;
#endif // CDS_ATTR(sentinel)

template <typename I, typename V, typename E, typename T> class FindIterator {
public:
  using Iterator = I;
  using Value = V;
  using Predicate = E;
  using Transformer = T;

  template <typename RI, typename RSI> CDS_ATTR(constexpr(14)) FindIterator(RI&& b, RSI&& e, V const& v)
      CDS_ATTR(noexcept(noexcept(filter()))) :
      _i(fwd<RI>(b)), _b(fwd<RI>(b)), _e(fwd<RSI>(e)), _v(v) {
    filter();
  }

  CDS_ATTR(constexpr(14)) FindIterator(FindIterator const& it) CDS_ATTR(noexcept(noexcept(I(it._i)))) :
      _i(it._i), _b(it._b), _e(it._e), _v(it._v) {}

  CDS_ATTR(constexpr(14)) FindIterator(FindIterator&& it) noexcept :
      _i(mv(it._i)), _b(it._b), _e(it._e), _v(it._v) {}

  CDS_ATTR(constexpr(20)) ~FindIterator() noexcept = default;

  CDS_ATTR(constexpr(14)) auto operator++() CDS_ATTR(noexcept(noexcept(filter()))) -> FindIterator& {
    ignore = ++_i;
    filter();
    return *this;
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto operator*() const
      CDS_ATTR(noexcept(noexcept(fn::invoke(T{}, rvalue<I>(), rvalue<I>(), rvalue<I>()))))
      -> decltype(fn::invoke(T{}, rvalue<I>(), rvalue<I>(), rvalue<I>())) {
    return fn::invoke(T{}, _b, _e, _i);
  }

  CDS_ATTR(constexpr(14)) auto operator=(FindIterator const& iterator)
      CDS_ATTR(noexcept(noexcept(lvalue<I>() = rvalue<I>()))) -> FindIterator& {
    if (this == &iterator) {
      return *this;
    }

    _i = iterator._i;
    return *this;
  }

  CDS_ATTR(constexpr(14)) auto operator=(FindIterator && iterator) noexcept -> FindIterator& {
    if (this == &iterator) {
      return *this;
    }

    _i = mv(iterator._i);
    return *this;
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto iterator() const noexcept -> I const& {
    return _i;
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto end() const noexcept -> I const& {
    return _e;
  }

private:
  CDS_ATTR(constexpr(14)) auto filter() CDS_ATTR(noexcept(
      noexcept(++lvalue<I>())
      && noexcept(_i != _e)
      && noexcept(fn::invoke(E{}, _v, *_i))
  )) -> void {
    E const equal;
    while (_i != _e && !fn::invoke(equal, _v, *_i)) {
      ++_i;
    }
  }

  I _i;
  I const _b;
  I const _e;
  V const& _v;
};

#if CDS_ATTR(sentinel)
template <typename I, typename V, typename E, typename T>
CDS_ATTR(2(nodiscard, constexpr(11))) auto operator==(FindIterator<I, V, E, T> const& obj, Sentinel)
    CDS_ATTR(noexcept(noexcept(rvalue<I>() == rvalue<I>()))) -> bool {
  return obj.iterator() == obj.end();
}

template <typename I, typename V, typename E, typename T>
CDS_ATTR(2(nodiscard, constexpr(11))) auto operator!=(FindIterator<I, V, E, T> const& obj, Sentinel)
    CDS_ATTR(noexcept(noexcept(rvalue<I>() != rvalue<I>()))) -> bool {
  return obj.iterator() != obj.end();
}
#endif // #if CDS_ATTR(sentinel)

template <typename FI, typename FV, typename FE, typename FT> CDS_ATTR(constexpr(11))
auto operator==(FindIterator<FI, FV, FE, FT> const& lhs, FindIterator<FI, FV, FE, FT> const& rhs)
    CDS_ATTR(noexcept(noexcept(rvalue<FI>() == rvalue<FI>()))) -> bool {
  return lhs.iterator() == rhs.iterator();
}

template <typename FI, typename FV, typename FE, typename FT> CDS_ATTR(constexpr(11))
auto operator!=(FindIterator<FI, FV, FE, FT> const& lhs, FindIterator<FI, FV, FE, FT> const& rhs)
    CDS_ATTR(noexcept(noexcept(rvalue<FI>() != rvalue<FI>()))) -> bool {
  return lhs.iterator() != rhs.iterator();
}

template <typename I, typename V, typename P, typename E, typename T> class FindProjectIterator {
public:
  using Iterator = I;
  using Value = V;
  using Predicate = E;
  using Transformer = T;

  template <typename RI, typename RSI> CDS_ATTR(constexpr(14))
  FindProjectIterator(RI&& b, RSI&& e, V const& v, P const& s)
      CDS_ATTR(noexcept(noexcept(filter()))) :
      _i(fwd<RI>(b)), _b(fwd<RI>(b)), _e(fwd<RSI>(e)), _p(s), _v(v) {
    filter();
  }

  CDS_ATTR(constexpr(14)) auto operator++() CDS_ATTR(noexcept(noexcept(filter()))) -> FindProjectIterator& {
    ignore = ++_i;
    filter();
    return *this;
  }

  CDS_ATTR(constexpr(14)) FindProjectIterator(FindProjectIterator const& it) CDS_ATTR(noexcept(noexcept(I(it._i)))) :
      _i(it._i), _b(it._b), _e(it._e), _p(it._p), _v(it._v) {}

  CDS_ATTR(constexpr(14)) FindProjectIterator(FindProjectIterator&& it)
      noexcept : _i(mv(it._i)), _b(it._b), _e(it._e), _p(it._p), _v(it._v) {}

  CDS_ATTR(constexpr(20)) ~FindProjectIterator() noexcept = default;

  CDS_ATTR(2(nodiscard, constexpr(11))) auto operator*() const
      CDS_ATTR(noexcept(noexcept(fn::invoke(T{}, rvalue<I>(), rvalue<I>(), rvalue<I>()))))
      -> decltype(fn::invoke(T{}, rvalue<I>(), rvalue<I>(), rvalue<I>())) {
    return fn::invoke(T{}, _b, _e, _i);
  }

  CDS_ATTR(constexpr(14)) auto operator=(FindProjectIterator const& iterator)
      CDS_ATTR(noexcept(noexcept(lvalue<I>() = rvalue<I>()))) -> FindProjectIterator& {
    if (this == &iterator) {
      return *this;
    }

    _i = iterator._i;
    return *this;
  }

  CDS_ATTR(constexpr(14)) auto operator=(FindProjectIterator && iterator) noexcept -> FindProjectIterator& {
    if (this == &iterator) {
      return *this;
    }

    _i = mv(iterator._i);
    return *this;
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto iterator() const noexcept -> I const& {
    return _i;
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto end() const noexcept -> I const& {
    return _e;
  }

private:
  CDS_ATTR(constexpr(14)) auto filter() CDS_ATTR(noexcept(
      noexcept(++lvalue<I>())
      && noexcept(_i != _e)
      && noexcept(fn::invoke(E{}, _v, _p(*_i)))
  )) -> void {
    E const equal;
    while (_i != _e && !fn::invoke(equal, _v, _p(*_i))) {
      ++_i;
    }
  }

  I _i;
  I const _b;
  I const _e;
  P const& _p;
  V const& _v;
};

#if CDS_ATTR(sentinel)
template <typename I, typename V, typename P, typename E, typename T>
CDS_ATTR(2(nodiscard, constexpr(11))) auto operator==(FindProjectIterator<I, V, P, E, T> const& obj, Sentinel)
    CDS_ATTR(noexcept(noexcept(rvalue<I>() == rvalue<I>()))) -> bool {
  return obj.iterator() == obj.end();
}

template <typename I, typename V, typename P, typename E, typename T>
CDS_ATTR(2(nodiscard, constexpr(11))) auto operator!=(FindProjectIterator<I, V, P, E, T> const& obj, Sentinel)
    CDS_ATTR(noexcept(noexcept(rvalue<I>() != rvalue<I>()))) -> bool {
  return obj.iterator() != obj.end();
}
#endif // #if CDS_ATTR(sentinel)

template <typename I, typename V, typename P, typename E, typename T> CDS_ATTR(2(nodiscard, constexpr(11)))
auto operator==(FindProjectIterator<I, V, P, E, T> const& lhs, FindProjectIterator<I, V, P, E, T> const& rhs)
    CDS_ATTR(noexcept(noexcept(rvalue<I>() == rvalue<I>()))) -> bool {
  return lhs.iterator() == rhs.iterator();
}

template <typename I, typename V, typename P, typename E, typename T> CDS_ATTR(2(nodiscard, constexpr(11)))
auto operator!=(FindProjectIterator<I, V, P, E, T> const& lhs, FindProjectIterator<I, V, P, E, T> const& rhs)
    CDS_ATTR(noexcept(noexcept(rvalue<I>() == rvalue<I>()))) -> bool {
  return lhs.iterator() != rhs.iterator();
}
} // namespace impl
} // namespace iterator

namespace impl {
using meta::value;
using meta::lvalue;
using meta::rvalue;
using meta::EnableIf;
using meta::Not;
using meta::And;
using meta::RemoveRef;
using meta::RemoveCVRef;
using meta::False;
using meta::True;

using iterator::impl::FindIterator;
using iterator::impl::FindProjectIterator;

#if CDS_ATTR(sentinel)
using iterator::Sentinel;
#endif // #if CDS_ATTR(sentinel)
using extension::Extend;

namespace fn = cds::functional;

template <typename TAttr, typename VAttr, typename E, typename Tr> class FindIterableRange {
public:
  using Iterable = TAttr;
  using Value = VAttr;
  using Predicate = E;
  using Transformer = Tr;
  using UnderlyingIterator = decltype(cds::begin(value<TAttr>()));
  using Iterator = FindIterator<UnderlyingIterator, RemoveRef<VAttr>, E, Tr>;
  using UnderlyingConstIterator = decltype(cds::begin(value<TAttr const>()));
  using ConstIterator = FindIterator<UnderlyingConstIterator, RemoveRef<VAttr>, E, Tr>;

  template <typename T, typename V> CDS_ATTR(constexpr(11)) FindIterableRange(T&& obj, V&& v)
      CDS_ATTR(noexcept(noexcept(TAttr(fwd<T>(obj))) && noexcept(VAttr(fwd<V>(v))))) :
      _o(fwd<T>(obj)), _v(fwd<V>(v)) {}

  CDS_ATTR(2(nodiscard, constexpr(14))) auto begin()
      CDS_ATTR(noexcept(noexcept(Iterator(cds::begin(_o), cds::end(_o), _v)))) -> Iterator {
    return Iterator(cds::begin(_o), cds::end(_o), _v);
  }

  CDS_ATTR(2(nodiscard, constexpr(14))) auto begin() const
      CDS_ATTR(noexcept(noexcept(ConstIterator(cds::begin(_o), cds::end(_o), _v)))) -> ConstIterator {
    return ConstIterator(cds::begin(_o), cds::end(_o), _v);
  }

#if CDS_ATTR(sentinel)
  CDS_ATTR(2(nodiscard, constexpr(14))) auto end() const noexcept -> Sentinel {
    ignore = this;
    return {};
  }
#else // #if CDS_ATTR(sentinel)
  CDS_ATTR(2(nodiscard, constexpr(14))) auto end()
      CDS_ATTR(noexcept(noexcept(Iterator(cds::end(_o), cds::end(_o), _v)))) -> Iterator {
    return Iterator(cds::end(_o), cds::end(_o), _v);
  }

  CDS_ATTR(2(nodiscard, constexpr(14))) auto end() const
      CDS_ATTR(noexcept(noexcept(ConstIterator(cds::end(_o), cds::end(_o), _v)))) -> ConstIterator {
    return ConstIterator(cds::end(_o), cds::end(_o), _v);
  }
#endif // #if CDS_ATTR(sentinel) #else

private:
  TAttr _o;
  VAttr const _v;
};

template <typename TAttr, typename VAttr, typename PAttr, typename E, typename Tr> class FindSelectIterableRange {
public:
  using Iterable = TAttr;
  using Value = VAttr;
  using Predicate = E;
  using Transformer = Tr;
  using UnderlyingIterator = decltype(cds::begin(value<TAttr>()));
  using Iterator = FindProjectIterator<UnderlyingIterator, RemoveRef<VAttr>, RemoveRef<PAttr>, E, Tr>;
  using UnderlyingConstIterator = decltype(cds::begin(value<TAttr const>()));
  using ConstIterator = FindProjectIterator<UnderlyingConstIterator, RemoveRef<VAttr>, RemoveRef<PAttr>, E, Tr>;

  template <typename T, typename V, typename P>
  CDS_ATTR(constexpr(11)) FindSelectIterableRange(T&& obj, V&& v, P&& p) CDS_ATTR(noexcept(
      noexcept(TAttr(fwd<T>(obj)))
      && noexcept(VAttr(fwd<V>(v)))
      && noexcept(PAttr(fwd<P>(p)))
  )) : _o(fwd<T>(obj)), _v(fwd<V>(v)), _p(fwd<P>(p)) {}

  CDS_ATTR(2(nodiscard, constexpr(14))) auto begin()
      CDS_ATTR(noexcept(noexcept(Iterator(cds::begin(_o), cds::end(_o), _v, _p)))) -> Iterator {
    return Iterator(cds::begin(_o), cds::end(_o), _v, _p);
  }

  CDS_ATTR(2(nodiscard, constexpr(14))) auto begin() const
      CDS_ATTR(noexcept(noexcept(ConstIterator(cds::begin(_o), cds::end(_o), _v, _p)))) -> ConstIterator {
    return ConstIterator(cds::begin(_o), cds::end(_o), _v, _p);
  }

#if CDS_ATTR(sentinel)
  CDS_ATTR(2(nodiscard, constexpr(14))) auto end() const noexcept -> Sentinel {
    ignore = this;
    return {};
  }
#else // #if CDS_ATTR(sentinel)
  CDS_ATTR(2(nodiscard, constexpr(14))) auto end()
      CDS_ATTR(noexcept(noexcept(Iterator(cds::end(_o), cds::end(_o), _v, _p)))) -> Iterator {
    return Iterator(cds::end(_o), cds::end(_o), _v, _p);
  }

  CDS_ATTR(2(nodiscard, constexpr(14))) auto end() const
      CDS_ATTR(noexcept(noexcept(ConstIterator(cds::end(_o), cds::end(_o), _v, _p)))) -> ConstIterator {
    return ConstIterator(cds::end(_o), cds::end(_o), _v, _p);
  }
#endif // #if CDS_ATTR(sentinel) #else

private:
  TAttr _o;
  VAttr const _v;
  PAttr const _p;
};

template <typename, typename, typename> struct GenericFindEnabledFor : True {};
template <typename, typename, typename, typename = void> struct FindUsesAllocation : False {};
template <typename, typename, typename> struct GenericFindFirstUsingFind : False {};
template <typename, typename, typename> struct GenericFindLastUsingFind : False {};

template <
    typename I, typename V, typename E, typename T,
    typename R = FindIterableRange<Extend<I>, Extend<V>, E, T>,
    EnableIf<GenericFindEnabledFor<RemoveCVRef<I>, RemoveCVRef<V>, RemoveCVRef<E>>> = 0
> CDS_ATTR(2(nodiscard, constexpr(14))) auto find(
    I&& iterable, V&& value, CDS_ATTR(unused) E const& equal, CDS_ATTR(unused) T const& transform
) CDS_ATTR(noexcept(noexcept(R(fwd<I>(iterable), fwd<V>(value))))) -> R {
  return R(fwd<I>(iterable), fwd<V>(value));
}

namespace isProjector {
namespace fn = cds::functional;
using meta::IsInvocable;

template <typename T, typename P> struct IsProjector : IsInvocable<P, decltype(*cds::begin(rvalue<T>()))> {};
} // namespace isProjector

template <typename T, typename P> struct IsProjector : isProjector::IsProjector<RemoveCVRef<T>, RemoveCVRef<P>> {};

template <
    typename I, typename V, typename P, typename E, typename T,
    typename R = FindSelectIterableRange<Extend<I>, Extend<V>, Extend<P>, E, T>,
    EnableIf<And<GenericFindEnabledFor<RemoveCVRef<I>, RemoveCVRef<V>, RemoveCVRef<E>>, IsProjector<I, P>>> = 0
> CDS_ATTR(2(nodiscard, constexpr(14))) auto find(
    I&& iterable, V&& value, P&& projector, CDS_ATTR(unused) E const& equal, CDS_ATTR(unused) T const& transform
) CDS_ATTR(noexcept(noexcept(R(fwd<I>(iterable), fwd<V>(value), fwd<P>(projector))))) -> R {
  return R(fwd<I>(iterable), fwd<V>(value), fwd<P>(projector));
}

template <
    typename I, typename V, typename E, typename T,
    EnableIf<GenericFindEnabledFor<RemoveCVRef<I>, RemoveCVRef<V>, RemoveCVRef<E>>> = 0
> CDS_ATTR(2(nodiscard, constexpr(14))) auto findFirst(
    I&& iterable, V&& value, E const& equal, T const& transform
) CDS_ATTR(noexcept(
    noexcept(cds::begin(fwd<I>(iterable)) != cds::end(fwd<I>(iterable)))
    && noexcept(++lvalue<decltype(cds::begin(fwd<I>(iterable)))>())
    && noexcept(fn::invoke(equal, *cds::begin(fwd<I>(iterable)), fwd<V>(value)))
    && noexcept(fn::invoke(
        transform,
        cds::begin(fwd<I>(iterable)),
        cds::end(fwd<I>(iterable)),
        cds::begin(fwd<I>(iterable))
    ))
)) -> decltype(fn::invoke(
    transform,
    cds::begin(fwd<I>(iterable)),
    cds::end(fwd<I>(iterable)),
    cds::begin(fwd<I>(iterable))
)) {
  auto const b = cds::begin(fwd<I>(iterable));
  auto const e = cds::end(fwd<I>(iterable));
  for (auto i = b; i != e; ++i) {
    if (fn::invoke(equal, fwd<V>(value), *i)) {
      return fn::invoke(transform, b, e, i);
    }
  }
  return fn::invoke(transform, b, e, e);
}

template <
    typename I, typename V, typename E, typename T,
    EnableIf<And<
        GenericFindFirstUsingFind<RemoveCVRef<I>, RemoveCVRef<V>, RemoveCVRef<E>>,
        Not<FindUsesAllocation<RemoveCVRef<I>, RemoveCVRef<V>, RemoveCVRef<E>>>
    >> = 0
> CDS_ATTR(2(nodiscard, constexpr(14))) auto findFirst(
    I&& iterable, V&& value, E const& equal, T const& transform
) CDS_ATTR(noexcept(noexcept(*find(fwd<I>(iterable), fwd<V>(value), equal, transform).begin())))
    -> decltype(*find(fwd<I>(iterable), fwd<V>(value), equal, transform).begin()) {
  auto const r = find(fwd<I>(iterable), fwd<V>(value), equal, transform);
  auto const i = r.begin();
  if (i != r.end()) {
    return *i;
  }

  auto const e = cds::end(fwd<I>(iterable));
  return fn::invoke(transform, cds::begin(fwd<I>(iterable)), e, e);
}

template <
    typename I, typename V, typename E, typename T,
    typename U = FindUsesAllocation<RemoveCVRef<I>, RemoveCVRef<V>, RemoveCVRef<E>>,
    EnableIf<And<GenericFindFirstUsingFind<RemoveCVRef<I>, RemoveCVRef<V>, RemoveCVRef<E>>, U>> = 0,
    typename A = typename U::Alloc
> CDS_ATTR(2(nodiscard, constexpr(14))) auto findFirst(
    I&& iterable, V&& value, E const& equal, T const& transform, A&& alloc
) CDS_ATTR(noexcept(noexcept(*find(fwd<I>(iterable), fwd<V>(value), equal, transform, fwd<A>(alloc)).begin())))
    -> decltype(*find(fwd<I>(iterable), fwd<V>(value), equal, transform, fwd<A>(alloc)).begin()) {
  auto const r = find(fwd<I>(iterable), fwd<V>(value), equal, transform, fwd<A>(alloc));
  auto const i = r.begin();
  if (i != r.end()) {
    return *i;
  }

  auto const e = cds::end(fwd<I>(iterable));
  return fn::invoke(transform, cds::begin(fwd<I>(iterable)), e, e);
}

template <
    typename I, typename V, typename P, typename E, typename T,
    EnableIf<GenericFindEnabledFor<RemoveCVRef<I>, RemoveCVRef<V>, RemoveCVRef<E>>> = 0
> CDS_ATTR(2(nodiscard, constexpr(14))) auto findFirst(
    I&& iterable, V&& value, P&& projector, E const& equal, T const& transform
) CDS_ATTR(noexcept(
    noexcept(cds::begin(fwd<I>(iterable)) != cds::end(fwd<I>(iterable)))
    && noexcept(++lvalue<decltype(cds::begin(fwd<I>(iterable)))>())
    && noexcept(fn::invoke(equal, fn::invoke(fwd<P>(projector), *cds::begin(fwd<I>(iterable))), fwd<V>(value)))
    && noexcept(fn::invoke(
        transform,
        cds::begin(fwd<I>(iterable)),
        cds::end(fwd<I>(iterable)),
        cds::begin(fwd<I>(iterable))
    ))
)) -> decltype(fn::invoke(
    transform,
    cds::begin(fwd<I>(iterable)),
    cds::end(fwd<I>(iterable)),
    cds::begin(fwd<I>(iterable))
)) {
  auto const b = cds::begin(fwd<I>(iterable));
  auto const e = cds::end(fwd<I>(iterable));
  for (auto i = b; i != e; ++i) {
    if (fn::invoke(equal, fwd<V>(value), fn::invoke(fwd<P>(projector), *i))) {
      return fn::invoke(transform, b, e, i);
    }
  }
  return fn::invoke(transform, b, e, e);
}

template <
    typename I, typename V, typename P, typename E, typename T,
    EnableIf<And<
        GenericFindFirstUsingFind<RemoveCVRef<I>, RemoveCVRef<V>, RemoveCVRef<E>>,
        Not<FindUsesAllocation<RemoveCVRef<I>, RemoveCVRef<V>, RemoveCVRef<E>>>
    >> = 0
> CDS_ATTR(2(nodiscard, constexpr(14))) auto findFirst(
    I&& iterable, V&& value, P&& projector, E const& equal, T const& transform
) CDS_ATTR(noexcept(noexcept(*find(fwd<I>(iterable), fwd<V>(value), fwd<P>(projector), equal, transform).begin())))
    -> decltype(*find(fwd<I>(iterable), fwd<V>(value), fwd<P>(projector), equal, transform).begin()) {
  auto const r = find(fwd<I>(iterable), fwd<V>(value), fwd<P>(projector), equal, transform);
  auto const i = r.begin();
  if (i != r.end()) {
    return *i;
  }

  auto const e = cds::end(fwd<I>(iterable));
  return fn::invoke(transform, cds::begin(fwd<I>(iterable)), e, e);
}

template <
    typename I, typename V, typename P, typename E, typename T,
    typename U = FindUsesAllocation<RemoveCVRef<I>, RemoveCVRef<V>, RemoveCVRef<E>>,
    EnableIf<And<GenericFindFirstUsingFind<RemoveCVRef<I>, RemoveCVRef<V>, RemoveCVRef<E>>, U>> = 0,
    typename A = typename U::Alloc
> CDS_ATTR(2(nodiscard, constexpr(14))) auto findFirst(
    I&& iterable, V&& value, P&& projector, E const& equal, T const& transform, A&& alloc
) CDS_ATTR(noexcept(noexcept(
    *find(fwd<I>(iterable), fwd<V>(value), fwd<P>(projector), equal, transform, fwd<A>(alloc)).begin()
))) -> decltype(*find(fwd<I>(iterable), fwd<V>(value), fwd<P>(projector), equal, transform, fwd<A>(alloc)).begin()) {
  auto const r = find(fwd<I>(iterable), fwd<V>(value), fwd<P>(projector), equal, transform, fwd<A>(alloc));
  auto const i = r.begin();
  if (i != r.end()) {
    return *i;
  }

  auto const e = cds::end(fwd<I>(iterable));
  return fn::invoke(transform, cds::begin(fwd<I>(iterable)), e, e);
}

template <
    typename I, typename V, typename E, typename T,
    EnableIf<GenericFindEnabledFor<RemoveCVRef<I>, RemoveCVRef<V>, RemoveCVRef<E>>> = 0
> CDS_ATTR(2(nodiscard, constexpr(14))) auto findLast(
    I&& iterable, V&& value, E const& equal, T const& transform
) CDS_ATTR(noexcept(
    noexcept(cds::begin(fwd<I>(iterable)) != cds::end(fwd<I>(iterable)))
    && noexcept(++lvalue<decltype(cds::begin(fwd<I>(iterable)))>())
    && noexcept(fn::invoke(equal, *cds::begin(fwd<I>(iterable)), fwd<V>(value)))
    && noexcept(fn::invoke(
        transform,
        cds::begin(fwd<I>(iterable)),
        cds::end(fwd<I>(iterable)),
        cds::begin(fwd<I>(iterable))
    ))
)) -> decltype(fn::invoke(
    transform,
    cds::begin(fwd<I>(iterable)),
    cds::end(fwd<I>(iterable)),
    cds::begin(fwd<I>(iterable))
)) {
  auto const b = cds::begin(fwd<I>(iterable));
  auto const e = cds::end(fwd<I>(iterable));
  auto l = e;
  for (auto i = b; i != e; ++i) {
    if (fn::invoke(equal, fwd<V>(value), *i)) {
      l = i;
    }
  }
  return fn::invoke(transform, b, e, l);
}

template <
    typename I, typename V, typename E, typename T,
    EnableIf<And<
        GenericFindLastUsingFind<RemoveCVRef<I>, RemoveCVRef<V>, RemoveCVRef<E>>,
        Not<FindUsesAllocation<RemoveCVRef<I>, RemoveCVRef<V>, RemoveCVRef<E>>>
    >> = 0
> CDS_ATTR(2(nodiscard, constexpr(14))) auto findLast(
    I&& iterable, V&& value, E const& equal, T const& transform
) CDS_ATTR(noexcept(noexcept(*find(fwd<I>(iterable), fwd<V>(value), equal, transform).begin())))
    -> decltype(*find(fwd<I>(iterable), fwd<V>(value), equal, transform).begin()) {
  auto const r = find(fwd<I>(iterable), fwd<V>(value), equal, transform);
  auto i = r.begin();
  auto p = i;
  while (i != r.end()) {
    p = i;
    ++i;
  }

  if (p == r.end()) {
    auto const e = cds::end(fwd<I>(iterable));
    return fn::invoke(transform, cds::begin(fwd<I>(iterable)), e, e);
  }

  return *p;
}

template <
    typename I, typename V, typename E, typename T,
    typename U = FindUsesAllocation<RemoveCVRef<I>, RemoveCVRef<V>, RemoveCVRef<E>>,
    EnableIf<And<GenericFindLastUsingFind<RemoveCVRef<I>, RemoveCVRef<V>, RemoveCVRef<E>>, U>> = 0,
    typename A = typename U::Alloc
> CDS_ATTR(2(nodiscard, constexpr(14))) auto findLast(
    I&& iterable, V&& value, E const& equal, T const& transform, A&& alloc
) CDS_ATTR(noexcept(noexcept(*find(fwd<I>(iterable), fwd<V>(value), equal, transform, fwd<A>(alloc)).begin())))
    -> decltype(*find(fwd<I>(iterable), fwd<V>(value), equal, transform, fwd<A>(alloc)).begin()) {
  auto const r = find(fwd<I>(iterable), fwd<V>(value), equal, transform, fwd<A>(alloc));
  auto i = r.begin();
  auto p = i;
  while (i != r.end()) {
    p = i;
    ++i;
  }

  if (p == r.end()) {
    auto const e = cds::end(fwd<I>(iterable));
    return fn::invoke(transform, cds::begin(fwd<I>(iterable)), e, e);
  }

  return *p;
}

template <
    typename I, typename V, typename P, typename E, typename T,
    EnableIf<GenericFindEnabledFor<RemoveCVRef<I>, RemoveCVRef<V>, RemoveCVRef<E>>> = 0
> CDS_ATTR(2(nodiscard, constexpr(14))) auto findLast(
    I&& iterable, V&& value, P&& projector, E const& equal, T const& transform
) CDS_ATTR(noexcept(
    noexcept(cds::begin(fwd<I>(iterable)) != cds::end(fwd<I>(iterable)))
    && noexcept(++lvalue<decltype(cds::begin(fwd<I>(iterable)))>())
    && noexcept(fn::invoke(equal, fn::invoke(fwd<P>(projector), *cds::begin(fwd<I>(iterable))), fwd<V>(value)))
    && noexcept(fn::invoke(
        transform,
        cds::begin(fwd<I>(iterable)),
        cds::end(fwd<I>(iterable)),
        cds::begin(fwd<I>(iterable))
    ))
)) -> decltype(fn::invoke(
    transform,
    cds::begin(fwd<I>(iterable)),
    cds::end(fwd<I>(iterable)),
    cds::begin(fwd<I>(iterable))
)) {
  auto const b = cds::begin(fwd<I>(iterable));
  auto const e = cds::end(fwd<I>(iterable));
  auto l = e;
  for (auto i = b; i != e; ++i) {
    if (fn::invoke(equal, fwd<V>(value), fn::invoke(fwd<P>(projector), *i))) {
      l = i;
    }
  }
  return fn::invoke(transform, b, e, l);
}

template <
    typename I, typename V, typename P, typename E, typename T,
    EnableIf<And<
        GenericFindLastUsingFind<RemoveCVRef<I>, RemoveCVRef<V>, RemoveCVRef<E>>,
        Not<FindUsesAllocation<RemoveCVRef<I>, RemoveCVRef<V>, RemoveCVRef<E>>>
    >> = 0
> CDS_ATTR(2(nodiscard, constexpr(14))) auto findLast(
    I&& iterable, V&& value, P&& projector, E const& equal, T const& transform
) CDS_ATTR(noexcept(noexcept(*find(fwd<I>(iterable), fwd<V>(value), fwd<P>(projector), equal, transform).begin())))
    -> decltype(*find(fwd<I>(iterable), fwd<V>(value), fwd<P>(projector), equal, transform).begin()) {
  auto const r = find(fwd<I>(iterable), fwd<V>(value), fwd<P>(projector), equal, transform);
  auto i = r.begin();
  auto p = i;
  while (i != r.end()) {
    p = i;
    ++i;
  }

  if (p == r.end()) {
    auto const e = cds::end(fwd<I>(iterable));
    return fn::invoke(transform, cds::begin(fwd<I>(iterable)), e, e);
  }

  return *p;
}

template <
    typename I, typename V, typename P, typename E, typename T,
    typename U = FindUsesAllocation<RemoveCVRef<I>, RemoveCVRef<V>, RemoveCVRef<E>>,
    EnableIf<And<GenericFindLastUsingFind<RemoveCVRef<I>, RemoveCVRef<V>, RemoveCVRef<E>>, U>> = 0,
    typename A = typename U::Alloc
> CDS_ATTR(2(nodiscard, constexpr(14))) auto findLast(
    I&& iterable, V&& value, P&& projector, E const& equal, T const& transform, A&& alloc
) CDS_ATTR(noexcept(noexcept(
    *find(fwd<I>(iterable), fwd<V>(value), fwd<P>(projector), equal, transform, fwd<A>(alloc)).begin()
))) -> decltype(*find(fwd<I>(iterable), fwd<V>(value), fwd<P>(projector), equal, transform, fwd<A>(alloc)).begin()) {
  auto const r = find(fwd<I>(iterable), fwd<V>(value), fwd<P>(projector), equal, transform, fwd<A>(alloc));
  auto i = r.begin();
  auto p = i;
  while (i != r.end()) {
    p = i;
    ++i;
  }

  if (p == r.end()) {
    auto const e = cds::end(fwd<I>(iterable));
    return fn::invoke(transform, cds::begin(fwd<I>(iterable)), e, e);
  }

  return *p;
}
} // namespace impl
} // namespace cds

#if CDS_ATTR(msvc)
#pragma warning(default: 4180)
#endif

#endif // CDS_ALGORITHM_GENERIC_FIND_HPP
