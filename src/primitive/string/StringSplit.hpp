//
// Created by loghin on 12/8/23.
//

#ifndef CDS_PRIMITIVE_STRING_SPLIT_HPP
#define CDS_PRIMITIVE_STRING_SPLIT_HPP
#pragma once

#include <cds/meta/StringTraits>
#include <cds/iterator/AddressIterator>
#include <cds/memory/Allocator>

#if CDS_ATTR(sentinel)
#include <cds/iterator/Sentinel>
#endif // CDS_ATTR(sentinel)

#include "StringPattern.hpp"

#include "../../algorithm/GenericContains.hpp"

#include "../../ds/hashTable/HashTableBase.hpp"

#include "../../stdlib/ostream.hpp"
#include "../../stdlib/string_view.hpp"

#include "../../meta/Extension.hpp"

namespace cds {
namespace impl {
using meta::EnableIf;
using meta::Not;
using meta::Decay;
using meta::All;
using meta::True;
using meta::False;
using meta::Null;
using meta::And;
using meta::Conditional;
using meta::IsSame;

using meta::value;
using meta::lvalue;
using meta::rvalue;

using meta::IsIterable;

using functional::Equal;

#if CDS_ATTR(sentinel)
using iterator::Sentinel;
#endif

namespace isStringImpl {
template <typename> struct IsString : False {};
template <typename C> struct IsString<C*> : StringTraits<C>::IsChar {};
template <typename C> struct IsString<C const*> : StringTraits<C>::IsChar {};
template <typename C, typename U> struct IsString<BaseStringView<C, U>> : True {};

#if CDS_ATTR(std_compat)
template <typename C, typename T, typename A> struct IsString<std::basic_string<C, T, A>> : True {};
#if CDS_ATTR(cpp17)
template <typename C, typename T> struct IsString<std::basic_string_view<C, T>> : True {};
#endif
#endif

template <typename T> struct CharTypeOfString {
  using Type = RemoveCVRef<decltype(*cds::begin(rvalue<T>()))>;
};

template <typename C> struct CharTypeOfString<C*> {
  using Type = C;
};
} // namespace isStringImpl

template <typename T> struct IsString : isStringImpl::IsString<Decay<T>> {};
template <typename T> struct CharTypeOfString : isStringImpl::CharTypeOfString<Decay<T>> {};

namespace splitAllocationTraits {
template <typename, typename = void> struct SplitAllocationTraits {
  using Required = False;
};

template <typename T> struct SplitAllocationTraits<T, EnableIf<IsString<T>, void>> {
  using Required = True;
  using Alloc = Allocator<Size>;
};

template <typename T>
struct SplitAllocationTraits<T, EnableIf<And<IsIterable<T>, IsString<decltype(*cds::begin(rvalue<T>()))>>, void>> {
  using S = RemoveCVRef<decltype(*cds::begin(rvalue<T>()))>;
  using C = typename CharTypeOfString<S>::Type;

  class AhoCorasickAllocatorSet;
  using AhoCorasickVertex = ahoCorasick::Vertex<C, AhoCorasickAllocatorSet>;
  class AhoCorasickAllocatorSet : public AllocatorSet<
      Allocator<FwdNode<ahoCorasick::Link<C const>>>,
      Allocator<FwdNode<ahoCorasick::Link<C const>>*>,
      Allocator<FwdNode<Size>>,
      Allocator<int>,
      Allocator<AhoCorasickVertex>
  > {};

  using Required = True;
  using Alloc = AhoCorasickAllocatorSet;
};
} // namespace splitAllocationTraits

template <typename T> struct SplitAllocationTraits : splitAllocationTraits::SplitAllocationTraits<RemoveCVRef<T>> {};

namespace splitKind {
struct ByCharacter {};
struct ByCharacterSet {};
struct ByString {};
struct ByStringSet {};
} // namespace splitKind

template <typename, typename = void> struct SplitTraits {};
template <typename T> struct SplitTraits<T, EnableIf<typename StringTraits<T>::IsSeparator, void>> {
  using SplitType = splitKind::ByCharacter;
};

template <typename T> struct SplitTraits<T, EnableIf<IsString<T>, void>> {
  using SplitType = splitKind::ByString;
};

template <typename T> struct SplitTraits<T, EnableIf<And<IsIterable<T>, Not<IsString<T>>>, void>> {
  using SplitType = Conditional<
      IsString<decltype(*cds::begin(rvalue<T>()))>,
      splitKind::ByStringSet,
      splitKind::ByCharacterSet
  >;
};

template <typename S, typename, typename = typename SplitTraits<S>::SplitType> class SplitPredicate {};

template <typename S, typename A> class SplitPredicate<S, A, splitKind::ByCharacter> {
public:
  using Allocates = False;
  using IsPatternMatching = False;
  using MatchKind = matchKind::ByCharacter;

  template <typename FS>
  CDS_ATTR(2(explicit, constexpr(11))) SplitPredicate(FS&& separator, CDS_ATTR(unused) A const& alloc)
      CDS_ATTR(noexcept(noexcept(S(cds::forward<FS>(separator))))) : _s(cds::forward<FS>(separator)) {}

  template <typename C> CDS_ATTR(2(nodiscard, constexpr(11)))
  auto operator()(C chr) const CDS_ATTR(noexcept(noexcept(chr == _s))) -> bool {
    return chr == _s;
  }

private:
  S _s;
};

template <typename S, typename A> class SplitPredicate<S, A, splitKind::ByCharacterSet> {
public:
  using Allocates = False;
  using IsPatternMatching = False;
  using MatchKind = matchKind::ByCharacter;

  template <typename FS>
  CDS_ATTR(2(explicit, constexpr(11))) SplitPredicate(FS&& separator, CDS_ATTR(unused) A const& alloc)
      CDS_ATTR(noexcept(noexcept(S(cds::forward<FS>(separator))))) : _s(cds::forward<FS>(separator)) {}

  template <typename C> CDS_ATTR(2(nodiscard, constexpr(11)))
  auto operator()(C chr) const CDS_ATTR(noexcept(noexcept(impl::contains(value<S>(), chr, Equal<>())))) -> bool {
    return impl::contains(_s, chr, Equal<>());
  }

private:
  S _s;
};

template <typename S, typename A> class SplitPredicate<S, A, splitKind::ByString> : public KMPBase<S, A> {
public:
  using Allocates = True;
  using IsPatternMatching = True;
  using MatchKind = matchKind::ByErrorIndex;
  using KMPBase<S, A>::KMPBase;
};

template <typename S, typename A> class SplitPredicate<S, A, splitKind::ByStringSet> :
    public ahoCorasick::AhoCorasick<typename splitAllocationTraits::SplitAllocationTraits<S>::C, A> {
  using AhoCorasick = ahoCorasick::AhoCorasick<typename splitAllocationTraits::SplitAllocationTraits<S>::C, A>;

public:
  using Allocates = True;
  using IsPatternMatching = False;
  using MatchKind = matchKind::ByState;

  template <typename FS, typename FAS> CDS_ATTR(2(explicit, constexpr(20)))
  SplitPredicate(FS&& separator, FAS&& allocatorSet) CDS_ATTR(noexcept(noexcept(
      AhoCorasick(cds::forward<FS>(separator), 16, cds::forward<FAS>(allocatorSet))
  ))) : AhoCorasick(cds::forward<FS>(separator), 16, cds::forward<FAS>(allocatorSet)) {}
};

template <typename R, typename P> class SplitIterator : private StateContainer<P> {
public:
  using View = typename R::View;

  CDS_ATTR(2(nodiscard, constexpr(14))) SplitIterator(R const* r, P const& p, Size limit)
      CDS_ATTR(noexcept(noexcept(nextSegment()))) :
      StateContainer<P>(p), _e(!r || r->empty()), _l(limit), _r(r), _p(p) {
    if (r) {
      nextSegment();
    }
  }

#if CDS_ATTR(sentinel)
  template <typename FR, typename FP> CDS_ATTR(constexpr(11))
  friend auto operator==(SplitIterator<FR, FP> const& obj, Sentinel) noexcept -> bool;

  template <typename FR, typename FP> CDS_ATTR(constexpr(11))
  friend auto operator!=(SplitIterator<FR, FP> const& obj, Sentinel) noexcept -> bool;
#endif // #if CDS_ATTR(sentinel)

  template <typename FR, typename FP> CDS_ATTR(constexpr(11))
  friend auto operator==(SplitIterator<FR, FP> const& lhs, SplitIterator<FR, FP> const& rhs) noexcept -> bool;

  template <typename FR, typename FP> CDS_ATTR(constexpr(11))
  friend auto operator!=(SplitIterator<FR, FP> const& lhs, SplitIterator<FR, FP> const& rhs) noexcept -> bool;

  CDS_ATTR(constexpr(14)) auto operator++() CDS_ATTR(noexcept(noexcept(nextSegment()))) -> SplitIterator& {
    nextSegment();
    return *this;
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto operator*() const
      CDS_ATTR(noexcept(noexcept(View(lvalue<View>())))) -> View {
    return _segment;
  }

private:
  template <typename MK = typename P::MatchKind, EnableIf<IsSame<MK, matchKind::ByCharacter>> = 0>
  CDS_ATTR(constexpr(14)) auto nextSegment() CDS_ATTR(noexcept(
      noexcept(rvalue<P>()(rvalue<View>().data()[0])) && noexcept(rvalue<R>().sub(0)) && noexcept(rvalue<R>().sub(0, 0))
  )) -> void {
    if (_l == 0) {
      _segment = _r->sub(_f);
      _f = _r->length() + 1;
      --_l;
      return;
    }

    if (_f == _r->length() + 1) {
      _e = true;
      return;
    }

    auto endIdx = _f;
    while(endIdx < _r->length() && !_p(_r->data()[endIdx])) {
      ++endIdx;
    }

    _segment = _r->sub(_f, endIdx);
    _f = endIdx + 1;
    --_l;
  }

  template <typename MK = typename P::MatchKind, EnableIf<IsSame<MK, matchKind::ByErrorIndex>> = 0>
  CDS_ATTR(constexpr(14)) auto nextSegment()
      CDS_ATTR(noexcept(noexcept(rvalue<R>().sub(0)) && noexcept(rvalue<R>().sub(0, 0)))) -> void {
    if (_l == 0) {
      _segment = _r->sub(_f);
      _f = _r->length() + 1;
      --_l;
      return;
    }

    if (_f == _r->length() + 1) {
      _e = true;
      return;
    }

    auto srcIdx = _f;
    Size patIdx = 0;
    while (srcIdx < _r->length()) {
      if (_p.data()[patIdx] == _r->data()[srcIdx]) {
        ++srcIdx;
        ++patIdx;
      }

      if (patIdx == _p.len()) {
        --_l;
        _segment = _r->sub(_f, srcIdx - patIdx);
        _f = srcIdx;
        return;
      }

      if (srcIdx < _r->length() && _r->data()[srcIdx] != _p.data()[patIdx]) {
        if (patIdx != 0) {
          patIdx = _p.lps()[patIdx - 1];
        } else {
          ++srcIdx;
        }
      }
    }

    _segment = _r->sub(_f, _r->length());
    _f = _r->length() + 1;
  }

  template <typename MK = typename P::MatchKind, EnableIf<IsSame<MK, matchKind::ByState>> = 0>
  CDS_ATTR(constexpr(14)) auto nextSegment() CDS_ATTR(noexcept(noexcept(false))) -> void {
    if (_l == 0) {
      _segment = _r->sub(_f);
      _f = _r->length() + 1;
      --_l;
      return;
    }

    if (_f == _r->length() + 1) {
      _e = true;
      return;
    }

    auto endIdx = _f;
    while (endIdx < _r->length()) {
      auto r = _p(_r->data()[endIdx], StateContainer<P>::state);
      if (r.kind == ahoCorasick::PredResultKind::PRK_accept) {

        endIdx = endIdx + 1 - r.reverseLen;

        _segment = _r->sub(_f, endIdx);
        _f = endIdx + r.reverseLen;
        --_l;

        return;
      }
      StateContainer<P>::state = r.state;
      ++endIdx;
    }

    _segment = _r->sub(_f);
    _f = _r->length() + 1;
  }

  Size _f = 0;
  bool _e;
  Size _l;
  R const* _r;
  P const& _p;
  View _segment;
};

#if CDS_ATTR(sentinel)
template <typename FR, typename FP> CDS_ATTR(2(nodiscard, constexpr(11)))
auto operator==(SplitIterator<FR, FP> const& obj, Sentinel) noexcept -> bool {
  return obj._e;
}

template <typename FR, typename FP> CDS_ATTR(2(nodiscard, constexpr(11)))
auto operator!=(SplitIterator<FR, FP> const& obj, Sentinel) noexcept -> bool {
  return !obj._e;
}
#endif // #if CDS_ATTR(sentinel)

template <typename FR, typename FP> CDS_ATTR(constexpr(11))
auto operator==(SplitIterator<FR, FP> const& lhs, SplitIterator<FR, FP> const& rhs) noexcept -> bool {
  return lhs._e == rhs._e;
}

template <typename FR, typename FP> CDS_ATTR(constexpr(11))
auto operator!=(SplitIterator<FR, FP> const& lhs, SplitIterator<FR, FP> const& rhs) noexcept -> bool {
  return lhs._e != rhs._e;
}

template <typename R, typename P> class SplitRange : private P {
public:
  using Iterable = R;
  using Predicate = P;
  using Iterator = SplitIterator<Decay<R>, Decay<P>>;

  template <typename FR, typename S, typename A, typename DA = typename P::Allocates, EnableIf<DA> = 0>
  CDS_ATTR(constexpr(20)) SplitRange(FR&& view, S&& separator, Size limit, A&& alloc) CDS_ATTR(noexcept(
        noexcept(R(cds::forward<FR>(view))) && noexcept(P(cds::forward<S>(separator), cds::forward<A>(alloc)))
  )) : P(cds::forward<S>(separator), cds::forward<A>(alloc)), _r(cds::forward<FR>(view)), _l(limit) {}

  template <typename FR, typename S, typename A, typename DA = typename P::Allocates, EnableIf<Not<DA>> = 0>
  CDS_ATTR(constexpr(11)) SplitRange(FR&& view, S&& separator, Size limit, A&& alloc) CDS_ATTR(noexcept(
        noexcept(R(cds::forward<FR>(view))) && noexcept(P(cds::forward<S>(separator), cds::forward<A>(alloc)))
  )) : P(cds::forward<S>(separator), cds::forward<A>(alloc)), _r(cds::forward<FR>(view)), _l(limit) {}

  CDS_ATTR(2(nodiscard, constexpr(14))) auto begin() const
      CDS_ATTR(noexcept(noexcept(Iterator(nullptr, value<P>(), 0)))) -> Iterator {
    return Iterator(&_r, static_cast<P const&>(*this), _l);
  }

#if CDS_ATTR(sentinel)
  CDS_ATTR(2(nodiscard, constexpr(11))) auto end() const noexcept -> Sentinel {
    return {};
  }
#else // #if CDS_ATTR(sentinel)
  CDS_ATTR(2(nodiscard, constexpr(14))) auto end() const
      CDS_ATTR(noexcept(noexcept(Iterator(nullptr, value<P>(), 0)))) -> Iterator {
    return Iterator(nullptr, static_cast<P const&>(*this), _l);
  }
#endif // #if CDS_ATTR(sentinel) #else

private:
  R _r;
  Size _l;
};

using extension::Extend;
template <
    typename I, typename S, typename R = SplitRange<Extend<I>, SplitPredicate<Extend<S>, Null>>,
    EnableIf<Not<typename SplitAllocationTraits<S>::Required>> = 0
> CDS_ATTR(2(nodiscard, constexpr(14))) auto split(I&& range, S&& sep, Size limit)
    CDS_ATTR(noexcept(noexcept(R(cds::forward<I>(range), cds::forward<S>(sep), limit, nullptr)))) -> R {
  return R(cds::forward<I>(range), cds::forward<S>(sep), limit, nullptr);
}

template <
    typename I, typename S, typename A, typename R = SplitRange<Extend<I>, SplitPredicate<Extend<S>, RemoveCVRef<A>>>,
    EnableIf<typename SplitAllocationTraits<S>::Required> = 0
> CDS_ATTR(2(nodiscard, constexpr(20))) auto split(I&& range, S&& sep, Size limit, A&& alloc)
    CDS_ATTR(noexcept(noexcept(R(cds::forward<I>(range), cds::forward<S>(sep), limit, cds::forward<A>(alloc))))) -> R {
  return R(cds::forward<I>(range), cds::forward<S>(sep), limit, cds::forward<A>(alloc));
}
} // namespace impl
} // namespace cds

#endif // CDS_PRIMITIVE_STRING_SPLIT_HPP
