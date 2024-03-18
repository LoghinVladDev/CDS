//
// Created by loghin on 12/8/23.
//

#ifndef CDS_PRIMITIVE_STRING_FIND_HPP
#define CDS_PRIMITIVE_STRING_FIND_HPP
#pragma once

#include "../../algorithm/GenericFind.hpp"

#include "StringViewBaseDecl.hpp"
#include "StringPattern.hpp"

#if CDS_ATTR(msvc)
#pragma warning(disable: 4180)
#endif

namespace cds {
namespace impl {
using meta::value;
using meta::rvalue;
using meta::Not;
using meta::RemoveCVRef;
using meta::False;
using meta::True;
using meta::Void;
using functional::Equal;

namespace detail {
template <typename, typename R, typename = void> struct IteratorOfOr {
  using Type = R;
};

template <typename T, typename R> struct IteratorOfOr<T, R, Void<decltype(cds::begin(rvalue<RemoveCVRef<T>>()))>> {
  using Type = decltype(cds::begin(rvalue<RemoveCVRef<T>>()));
};

template <typename T, typename R, typename = void> struct DereferenceOfOr {
  using Type = R;
};

template <typename T, typename R> struct DereferenceOfOr<T, R, Void<decltype(*rvalue<T>())>> {
  using Type = decltype(*rvalue<T>());
};
} // namespace detail

template <typename T, typename R> using IteratorOfOr = typename detail::IteratorOfOr<T, R>::Type;
template <typename T, typename R> using DereferenceOfOr = typename detail::DereferenceOfOr<T, R>::Type;

template <typename C, typename U, typename V>
struct GenericFindEnabledFor<BaseStringView<C, U>, V, Equal<>> : Not<
    IsString<RemoveCVRef<V>>> {};

template <typename C, typename U, typename V>
struct GenericFindFirstUsingFind<BaseStringView<C, U>, V, Equal<>> : IsString<RemoveCVRef<V>> {};

template <typename C, typename U, typename V>
struct GenericFindLastUsingFind<BaseStringView<C, U>, V, Equal<>> : IsString<RemoveCVRef<V>> {};

template <typename C, typename U, typename V, template <typename> class Cont>
struct GenericFindEnabledFor<BaseStringView<C, U>, V, Cont<Equal<>>> :
    Not<And<IsIterable<RemoveCVRef<V>>, IsString<DereferenceOfOr<IteratorOfOr<V, void>, void>>>> {};

template <typename C, typename U, typename V, template <typename> class Cont>
struct GenericFindFirstUsingFind<BaseStringView<C, U>, V, Cont<Equal<>>> :
    And<IsIterable<RemoveCVRef<V>>, IsString<DereferenceOfOr<IteratorOfOr<V, void>, void>>> {};

template <typename C, typename U, typename V, template <typename> class Cont>
struct GenericFindLastUsingFind<BaseStringView<C, U>, V, Cont<Equal<>>> :
    And<IsIterable<RemoveCVRef<V>>, IsString<DereferenceOfOr<IteratorOfOr<V, void>, void>>> {};

template <typename S, typename A> class StringFindKmpPredicate : public KMPBase<S, A> {
public:
  using MatchKind = matchKind::ByErrorIndex;
  using KMPBase<S, A>::KMPBase;
};

namespace stringFind {
template <typename T> struct ACTraits {
  using S = RemoveCVRef<decltype(*cds::begin(rvalue<T>()))>;
  using C = typename CharTypeOfString<S>::Type;
};
} // namepsace findString

template <typename S, typename A> class StringFindAhoCorasickPredicate :
    public ahoCorasick::AhoCorasick<typename stringFind::ACTraits<S>::C, A> {
  using AhoCorasick = ahoCorasick::AhoCorasick<typename stringFind::ACTraits<S>::C, A>;

public:
  using MatchKind = matchKind::ByState;

  template <typename FS, typename FAS> CDS_ATTR(2(explicit, constexpr(20)))
  StringFindAhoCorasickPredicate(FS&& separator, FAS&& allocatorSet) CDS_ATTR(noexcept(noexcept(
      AhoCorasick(cds::forward<FS>(separator), 16, cds::forward<FAS>(allocatorSet))
  ))) : AhoCorasick(cds::forward<FS>(separator), 16, cds::forward<FAS>(allocatorSet)) {}
};

namespace stringFind {
template <typename> struct IsBaseStringView : False {};
template <typename C, typename U> struct IsBaseStringView<BaseStringView<C, U>> : True {};

template <typename> struct IsBaseString : False {};
// template <typename C, typename U, typename A> struct IsBaseString<BaseString<C, U, A>> : True {};

template <typename T, typename V, typename E> struct UsesStringFind : And<
  Not<GenericFindEnabledFor<T, V, E>>,
  Or<IsBaseString<T>, IsBaseStringView<T>>
> {};

template <typename, typename, typename, typename = void> struct Predicate {};

template <typename S, typename A> struct Predicate<S, Equal<>, A, EnableIf<IsString<Decay<S>>, void>> {
  using Alloc = Allocator<Size>;
  using Type = StringFindKmpPredicate<S, A>;
};

template <typename T, template <typename...> class Cont, typename A>
struct Predicate<T, Cont<Equal<>>, A, EnableIf<And<
    IsIterable<T>,
    IsString<DereferenceOfOr<IteratorOfOr<T, void>, void>>
>, void>> : ACTraits<T> {
  using C = typename ACTraits<T>::C;
  using S = typename ACTraits<T>::S;
  class AhoCorasickAllocatorSet;
  using AhoCorasickVertex = ahoCorasick::Vertex<C, AhoCorasickAllocatorSet>;
  class AhoCorasickAllocatorSet : public AllocatorSet<
      Allocator<FwdNode<ahoCorasick::Link<C const>>>,
      Allocator<FwdNode<ahoCorasick::Link<C const>>*>,
      Allocator<FwdNode<Size>>,
      Allocator<int>,
      Allocator<AhoCorasickVertex>
  > {};

  using Alloc = AhoCorasickAllocatorSet;
  using Type = StringFindAhoCorasickPredicate<T, A>;
};
} // namespace stringFind

template <typename, typename V, typename, typename = typename IsString<RemoveCVRef<V>>::Type>
struct ConditionalAlloc {};

template <typename S, typename V> struct ConditionalAlloc<S, V, Equal<>, True> {
  using Alloc = typename stringFind::Predicate<V, Equal<>, Null>::Alloc;
};

template <typename S, typename V> struct ConditionalAlloc<S, V, Contains<Equal<>>, False> {
  using Alloc = typename stringFind::Predicate<V, Contains<Equal<>>, Null>::Alloc;
};

template <typename S, typename V> struct ConditionalAlloc<S, V, NotContains<Equal<>>, False> {
  using Alloc = typename stringFind::Predicate<V, NotContains<Equal<>>, Null>::Alloc;
};

template <typename C, typename U, typename V>
struct FindUsesAllocation<BaseStringView<C, U>, V, Equal<>, EnableIf<IsString<RemoveCVRef<V>>, void>> :
    True, ConditionalAlloc<BaseStringView<C, U>, V, Equal<>> {};

template <typename C, typename U, typename V, typename E>
struct FindUsesAllocation<
    BaseStringView<C, U>, V, Contains<E>,
    EnableIf<And<IsIterable<RemoveCVRef<V>>, IsString<DereferenceOfOr<IteratorOfOr<V, void>, void>>>, void>
> : True, ConditionalAlloc<BaseStringView<C, U>, V, Contains<Equal<>>> {};

template <typename C, typename U, typename V, typename E>
struct FindUsesAllocation<
    BaseStringView<C, U>, V, NotContains<E>,
    EnableIf<And<IsIterable<RemoveCVRef<V>>, IsString<DereferenceOfOr<IteratorOfOr<V, void>, void>>>, void>
> : True, ConditionalAlloc<BaseStringView<C, U>, V, NotContains<Equal<>>> {};

template <typename I, typename P, typename T> class StringFindIterator : private StateContainer<P> {
public:
  template <typename RI, typename RSI> CDS_ATTR(constexpr(14)) StringFindIterator(RI&& b, RSI&& e, P const& p)
      CDS_ATTR(noexcept(noexcept(filter()))) :
      StateContainer<P>(p), _i(cds::forward<RI>(b)), _b(cds::forward<RI>(b)), _e(cds::forward<RSI>(e)), _p(p) {
    filter();
  }

  CDS_ATTR(constexpr(14)) StringFindIterator(StringFindIterator const& it) CDS_ATTR(noexcept(noexcept(I(it._i)))) :
      StateContainer<P>(it), _i(it._i), _b(it._b), _e(it._e), _p(it._p), _m(it._m) {}

  CDS_ATTR(constexpr(14)) StringFindIterator(StringFindIterator&& it) noexcept :
      StateContainer<P>(cds::move(it)), _i(cds::move(it._i)), _b(it._b), _e(it._e),
      _p(it._p), _m(cds::exchange(it._m, 0)) {}

#if CDS_ATTR(sentinel)
  template <typename FR, typename FP, typename FT> CDS_ATTR(constexpr(11))
  friend auto operator==(StringFindIterator<FR, FP, FT> const& obj, Sentinel) noexcept -> bool;

  template <typename FR, typename FP, typename FT> CDS_ATTR(constexpr(11))
  friend auto operator!=(StringFindIterator<FR, FP, FT> const& obj, Sentinel) noexcept -> bool;
#endif // #if CDS_ATTR(sentinel)

  template <typename FR, typename FP, typename FT> CDS_ATTR(constexpr(11)) friend auto operator==(
      StringFindIterator<FR, FP, FT> const& lhs, StringFindIterator<FR, FP, FT> const& rhs
  ) noexcept -> bool;

  template <typename FR, typename FP, typename FT> CDS_ATTR(constexpr(11)) friend auto operator!=(
      StringFindIterator<FR, FP, FT> const& lhs, StringFindIterator<FR, FP, FT> const& rhs
  ) noexcept -> bool;

  CDS_ATTR(constexpr(14)) auto operator++() CDS_ATTR(noexcept(noexcept(filter()))) -> StringFindIterator& {
    _m = 0;
    filter();
    return *this;
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto operator*() const
      CDS_ATTR(noexcept(noexcept(rvalue<T>()(rvalue<I>(), rvalue<I>(), rvalue<I>()))))
      -> decltype(rvalue<T>()(rvalue<I>(), rvalue<I>(), rvalue<I>())) {
    return T()(_b, _e, _i - _m);
  }

  CDS_ATTR(constexpr(14)) auto operator=(StringFindIterator const& iterator)
      CDS_ATTR(noexcept(noexcept(lvalue<I>() = rvalue<I>()))) -> StringFindIterator& {
    if (this == &iterator) {
      return *this;
    }

    _i = iterator._i;
    _m = iterator._m;
    return *this;
  }

  CDS_ATTR(constexpr(14)) auto operator=(StringFindIterator && iterator) noexcept -> StringFindIterator& {
    if (this == &iterator) {
      return *this;
    }

    _i = cds::move(iterator._i);
    _m = cds::exchange(iterator._m, 0);
    return *this;
  }

private:
  template <typename MK = typename P::MatchKind, EnableIf<IsSame<MK, matchKind::ByErrorIndex>> = 0>
  CDS_ATTR(constexpr(20)) auto filter() noexcept -> void {
    auto i = _i;
    Size patIdx = _m;
    while (i != _e) {
      if (_p.data()[patIdx] == *i) {
        ++i;
        ++patIdx;
      }

      if (patIdx == _p.len()) {
        _m = patIdx;
        _i = i;
        return;
      }

      if (i != _e && *i != _p.data()[patIdx]) {
        if (patIdx !=0) {
          patIdx = _p.lps()[patIdx - 1];
        } else {
          ++i;
        }
      }
    }

    _i = i;
  }

  template <typename MK = typename P::MatchKind, EnableIf<IsSame<MK, matchKind::ByState>> = 0>
  CDS_ATTR(constexpr(20)) auto filter() noexcept -> void {
    auto i = _i;
    while (i != _e) {
      auto r = _p(*i, StateContainer<P>::state);
      if (r.kind == ahoCorasick::PredResultKind::PRK_accept) {
        _i = i + 1;
        _m = r.reverseLen;
        return;
      }
      StateContainer<P>::state = r.state;
      ++i;
    }

    _i = i;
  }

  I _i;
  I const _b;
  I const _e;
  P const& _p;
  Size _m {0};
};

#if CDS_ATTR(sentinel)
template <typename FR, typename FP, typename FT> CDS_ATTR(2(nodiscard, constexpr(11)))
auto operator==(StringFindIterator<FR, FP, FT> const& obj, Sentinel) noexcept -> bool {
  return obj._i == obj._e && !obj._p.isEnd(obj._m);
}

template <typename FR, typename FP, typename FT> CDS_ATTR(2(nodiscard, constexpr(11)))
auto operator!=(StringFindIterator<FR, FP, FT> const& obj, Sentinel) noexcept -> bool {
  return obj._i != obj._e || obj._p.isEnd(obj._m);
}
#endif // #if CDS_ATTR(sentinel)

template <typename FR, typename FP, typename FT> CDS_ATTR(2(nodiscard, constexpr(11))) auto operator==(
    StringFindIterator<FR, FP, FT> const& lhs, StringFindIterator<FR, FP, FT> const& rhs
) noexcept -> bool {
  return lhs._i == rhs._i && !lhs._p.isEnd(lhs._m);
}

template <typename FR, typename FP, typename FT> CDS_ATTR(2(nodiscard, constexpr(11))) auto operator!=(
    StringFindIterator<FR, FP, FT> const& lhs, StringFindIterator<FR, FP, FT> const& rhs
) noexcept -> bool {
  return lhs._i != rhs._i || lhs._p.isEnd(lhs._m);
}

template <typename I, typename P, typename Proj, typename T>
class StringProjectFindIterator : private StateContainer<P> {
public:
  template <typename RI, typename RSI, typename FP> CDS_ATTR(constexpr(14))
  StringProjectFindIterator(RI&& b, RSI&& e, P const& p, FP&& projector)
      CDS_ATTR(noexcept(noexcept(filter()))) :
      StateContainer<P>(p), _i(cds::forward<RI>(b)), _b(cds::forward<RI>(b)), _e(cds::forward<RSI>(e)),
      _p(p), _proj(cds::forward<FP>(projector)) {
    filter();
  }

  CDS_ATTR(constexpr(14)) StringProjectFindIterator(StringProjectFindIterator const& it)
      CDS_ATTR(noexcept(noexcept(I(it._i)))) :
      StateContainer<P>(it), _i(it._i), _b(it._b), _e(it._e), _p(it._p), _proj(it._proj), _m(it._m) {}

  CDS_ATTR(constexpr(14)) StringProjectFindIterator(StringProjectFindIterator&& it) noexcept :
      StateContainer<P>(cds::move(it)), _i(cds::move(it._i)), _b(it._b), _e(it._e), _p(it._p),
      _proj(it._proj), _m(cds::exchange(it._m, 0)) {}

#if CDS_ATTR(sentinel)
  template <typename FR, typename FP, typename FProj, typename FT> CDS_ATTR(constexpr(11))
  friend auto operator==(StringProjectFindIterator<FR, FP, FProj, FT> const& obj, Sentinel) noexcept -> bool;

  template <typename FR, typename FP, typename FProj, typename FT> CDS_ATTR(constexpr(11))
  friend auto operator!=(StringProjectFindIterator<FR, FP, FProj, FT> const& obj, Sentinel) noexcept -> bool;
#endif // #if CDS_ATTR(sentinel)

  template <typename FR, typename FP, typename FProj, typename FT> CDS_ATTR(constexpr(11)) friend auto operator==(
      StringProjectFindIterator<FR, FP, FProj, FT> const& lhs, StringProjectFindIterator<FR, FP, FProj, FT> const& rhs
  ) noexcept -> bool;

  template <typename FR, typename FP, typename FProj, typename FT> CDS_ATTR(constexpr(11)) friend auto operator!=(
      StringProjectFindIterator<FR, FP, FProj, FT> const& lhs, StringProjectFindIterator<FR, FP, FProj, FT> const& rhs
  ) noexcept -> bool;

  CDS_ATTR(constexpr(14)) auto operator++() CDS_ATTR(noexcept(noexcept(filter()))) -> StringProjectFindIterator& {
    _m = 0;
    filter();
    return *this;
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto operator*() const
      CDS_ATTR(noexcept(noexcept(rvalue<T>()(rvalue<I>(), rvalue<I>(), rvalue<I>()))))
      -> decltype(rvalue<T>()(rvalue<I>(), rvalue<I>(), rvalue<I>())) {
    return T()(_b, _e, _i - _m);
  }

  CDS_ATTR(constexpr(14)) auto operator=(StringProjectFindIterator const& iterator)
      CDS_ATTR(noexcept(noexcept(lvalue<I>() = rvalue<I>()))) -> StringProjectFindIterator& {
    if (this == &iterator) {
      return *this;
    }

    _i = iterator._i;
    _m = iterator._m;
    return *this;
  }

  CDS_ATTR(constexpr(14)) auto operator=(StringProjectFindIterator && iterator) noexcept -> StringProjectFindIterator& {
    if (this == &iterator) {
      return *this;
    }

    _i = cds::move(iterator._i);
    _m = cds::exchange(iterator._m, 0);
    return *this;
  }

private:
  template <typename MK = typename P::MatchKind, EnableIf<IsSame<MK, matchKind::ByErrorIndex>> = 0>
  CDS_ATTR(constexpr(20)) auto filter() noexcept -> void {
    auto i = _i;
    Size patIdx = _m;
    while (i != _e) {
      if (_p.data()[patIdx] == _proj(*i)) {
        ++i;
        ++patIdx;
      }

      if (patIdx == _p.len()) {
        _m = patIdx;
        _i = i;
        return;
      }

      if (i != _e && _proj(*i) != _p.data()[patIdx]) {
        if (patIdx !=0) {
          patIdx = _p.lps()[patIdx - 1];
        } else {
          ++i;
        }
      }
    }

    _i = i;
  }

  template <typename MK = typename P::MatchKind, EnableIf<IsSame<MK, matchKind::ByState>> = 0>
  CDS_ATTR(constexpr(20)) auto filter() noexcept -> void {
    auto i = _i;
    while (i != _e) {
      auto r = _p(_proj(*i), StateContainer<P>::state);
      if (r.kind == ahoCorasick::PredResultKind::PRK_accept) {
        _i = i + 1;
        _m = r.reverseLen;
        return;
      }
      StateContainer<P>::state = r.state;
      ++i;
    }

    _i = i;
  }

  I _i;
  I const _b;
  I const _e;
  P const& _p;
  Proj const& _proj;
  Size _m {0};
};

#if CDS_ATTR(sentinel)
template <typename FR, typename FP, typename FProj, typename FT> CDS_ATTR(2(nodiscard, constexpr(11)))
auto operator==(StringProjectFindIterator<FR, FP, FProj, FT> const& obj, Sentinel) noexcept -> bool {
  return obj._i == obj._e && !obj._p.isEnd(obj._m);
}

template <typename FR, typename FP, typename FProj, typename FT> CDS_ATTR(2(nodiscard, constexpr(11)))
auto operator!=(StringProjectFindIterator<FR, FP, FProj, FT> const& obj, Sentinel) noexcept -> bool {
  return obj._i != obj._e || obj._p.isEnd(obj._m);
}
#endif // #if CDS_ATTR(sentinel)

template <typename FR, typename FP, typename FProj, typename FT> CDS_ATTR(2(nodiscard, constexpr(11))) auto operator==(
    StringProjectFindIterator<FR, FP, FProj, FT> const& lhs, StringProjectFindIterator<FR, FP, FProj, FT> const& rhs
) noexcept -> bool {
  return lhs._i == rhs._i && !lhs._p.isEnd(lhs._m);
}

template <typename FR, typename FP, typename FProj, typename FT> CDS_ATTR(2(nodiscard, constexpr(11))) auto operator!=(
    StringProjectFindIterator<FR, FP, FProj, FT> const& lhs, StringProjectFindIterator<FR, FP, FProj, FT> const& rhs
) noexcept -> bool {
  return lhs._i != rhs._i || lhs._p.isEnd(lhs._m);
}

template <typename R, typename P, typename T> class StringFindIterableRange : private P {
public:
  using Iterable = R;
  using Predicate = P;
  using UnderlyingIterator = decltype(cds::begin(value<R>()));
  using UnderlyingConstIterator = decltype(cds::begin(value<R const>()));
  using Iterator = StringFindIterator<UnderlyingIterator, Decay<P>, T>;
  using ConstIterator = StringFindIterator<UnderlyingConstIterator, Decay<P>, T>;

  template <typename FR, typename V, typename A> CDS_ATTR(constexpr(20))
  StringFindIterableRange(FR&& view, V&& value, A&& alloc) CDS_ATTR(noexcept(
      noexcept(R(cds::forward<FR>(view))) && noexcept(P(cds::forward<V>(value), cds::forward<A>(alloc)))
  )) : P(cds::forward<V>(value), cds::forward<A>(alloc)), _r(cds::forward<FR>(view)) {}

  CDS_ATTR(2(nodiscard, constexpr(14))) auto begin()
      CDS_ATTR(noexcept(noexcept(Iterator(cds::begin(_r), cds::end(_r), value<P>())))) -> Iterator {
    return Iterator(cds::begin(_r), cds::end(_r), static_cast<P&>(*this));
  }

  CDS_ATTR(2(nodiscard, constexpr(14))) auto begin() const
      CDS_ATTR(noexcept(noexcept(ConstIterator(cds::begin(_r), cds::end(_r), value<P>())))) -> ConstIterator {
    return ConstIterator(cds::begin(_r), cds::end(_r), static_cast<P const&>(*this));
  }

#if CDS_ATTR(sentinel)
  CDS_ATTR(2(nodiscard, constexpr(11))) auto end() const noexcept -> Sentinel {
    return {};
  }
#else // #if CDS_ATTR(sentinel)
  CDS_ATTR(2(nodiscard, constexpr(14))) auto end()
      CDS_ATTR(noexcept(noexcept(Iterator(cds::end(_r), cds::end(_r), value<P>())))) -> Iterator {
    return Iterator(cds::end(_r), cds::end(_r), static_cast<P&>(*this));
  }

  CDS_ATTR(2(nodiscard, constexpr(14))) auto end() const
      CDS_ATTR(noexcept(noexcept(ConstIterator(cds::end(_r), cds::end(_r), value<P>())))) -> ConstIterator {
    return ConstIterator(cds::end(_r), cds::end(_r), static_cast<P const&>(*this));
  }
#endif // #if CDS_ATTR(sentinel) #else

private:
  R _r;
};

template <typename R, typename P, typename Proj, typename T> class StringProjectedFindIterableRange : private P {
public:
  using Iterable = R;
  using Predicate = P;
  using UnderlyingIterator = decltype(cds::begin(value<R>()));
  using UnderlyingConstIterator = decltype(cds::begin(value<R const>()));
  using Iterator = StringProjectFindIterator<UnderlyingIterator, Decay<P>, RemoveRef<Proj>, T>;
  using ConstIterator = StringProjectFindIterator<UnderlyingConstIterator, Decay<P>, RemoveRef<Proj>, T>;

  template <typename FR, typename V, typename FP, typename A> CDS_ATTR(constexpr(20))
  StringProjectedFindIterableRange(FR&& view, V&& value, FP&& projector, A&& alloc) CDS_ATTR(noexcept(
      noexcept(R(cds::forward<FR>(view))) && noexcept(P(cds::forward<V>(value), cds::forward<A>(alloc)))
      && noexcept(Proj(cds::forward<FP>(projector)))
  )) :
      P(cds::forward<V>(value), cds::forward<A>(alloc)), _r(cds::forward<FR>(view)),
      _p(cds::forward<FP>(projector)) {}

  CDS_ATTR(2(nodiscard, constexpr(14))) auto begin()
      CDS_ATTR(noexcept(noexcept(Iterator(cds::begin(_r), cds::end(_r), value<P>(), _p)))) -> Iterator {
    return Iterator(cds::begin(_r), cds::end(_r), static_cast<P&>(*this), _p);
  }

  CDS_ATTR(2(nodiscard, constexpr(14))) auto begin() const
      CDS_ATTR(noexcept(noexcept(ConstIterator(cds::begin(_r), cds::end(_r), value<P>(), _p)))) -> ConstIterator {
    return ConstIterator(cds::begin(_r), cds::end(_r), static_cast<P const&>(*this), _p);
  }

#if CDS_ATTR(sentinel)
  CDS_ATTR(2(nodiscard, constexpr(11))) auto end() const noexcept -> Sentinel {
    return {};
  }
#else // #if CDS_ATTR(sentinel)
  CDS_ATTR(2(nodiscard, constexpr(14))) auto end()
      CDS_ATTR(noexcept(noexcept(Iterator(cds::end(_r), cds::end(_r), value<P>(), _p)))) -> Iterator {
    return Iterator(cds::end(_r), cds::end(_r), static_cast<P&>(*this), _p);
  }

  CDS_ATTR(2(nodiscard, constexpr(14))) auto end() const
      CDS_ATTR(noexcept(noexcept(ConstIterator(cds::end(_r), cds::end(_r), value<P>(), _p)))) -> ConstIterator {
    return ConstIterator(cds::end(_r), cds::end(_r), static_cast<P const&>(*this), _p);
  }
#endif // #if CDS_ATTR(sentinel) #else

private:
  R _r;
  Proj _p;
};

template <
    typename I, typename V, typename E, typename T, typename A = typename stringFind::Predicate<V, E, Null>::Alloc,
    typename R = StringFindIterableRange<Extend<I>, typename stringFind::Predicate<V, E, A>::Type, T>,
    EnableIf<stringFind::UsesStringFind<RemoveCVRef<I>, RemoveCVRef<V>, RemoveCVRef<E>>> = 0
> CDS_ATTR(2(nodiscard, constexpr(20))) auto find(
    I&& view, V&& value, CDS_ATTR(unused) E const& equal, CDS_ATTR(unused) T const& transform, A&& alloc
) CDS_ATTR(noexcept(noexcept(R(cds::forward<I>(view), cds::forward<V>(value), cds::forward<A>(alloc))))) -> R {
  static_assert(Not<IsSame<E, NotContains<Equal<>>>>::value, "Usage of `findNot*` is ambiguous with multiple strings");
  return R(cds::forward<I>(view), cds::forward<V>(value), cds::forward<A>(alloc));
}

template <
    typename I, typename V, typename P, typename E, typename T,
    typename A = typename stringFind::Predicate<V, E, Null>::Alloc,
    typename R = StringProjectedFindIterableRange<
        Extend<I>,
        typename stringFind::Predicate<V, E, A>::Type,
        Extend<P>,
        T
    >,
    EnableIf<stringFind::UsesStringFind<RemoveCVRef<I>, RemoveCVRef<V>, RemoveCVRef<E>>> = 0
> CDS_ATTR(2(nodiscard, constexpr(20))) auto find(
    I&& view, V&& value, P&& projector, CDS_ATTR(unused) E const& equal, CDS_ATTR(unused) T const& transform, A&& alloc
) CDS_ATTR(noexcept(noexcept(
    R(cds::forward<I>(view), cds::forward<V>(value), cds::forward<P>(projector), cds::forward<A>(alloc))
))) -> R {
  static_assert(Not<IsSame<E, NotContains<Equal<>>>>::value, "Usage of `findNot*` is ambiguous with multiple strings");
  return R(cds::forward<I>(view), cds::forward<V>(value), cds::forward<P>(projector), cds::forward<A>(alloc));
}
} // namespace impl
} // namespace cds

#if CDS_ATTR(msvc)
#pragma warning(default: 4180)
#endif

#endif // CDS_PRIMITIVE_STRING_FIND_HPP
