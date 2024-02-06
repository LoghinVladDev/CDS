//
// Created by loghin on 12/8/23.
//

#ifndef CDS_PRIMITIVE_STRING_VIEW_BASE_HPP
#define CDS_PRIMITIVE_STRING_VIEW_BASE_HPP
#pragma once

#include <cds/Utility>
#include <cds/meta/StringTraits>
#include <cds/iterator/AddressIterator>
#include <cds/functional/FunctionalInterface>
#include <cds/memory/Allocator>

#include "../../bindings/BindingSelectors.hpp"
#include "../../bindings/static/ContainsOfStaticBinding.hpp"
#include "../../bindings/static/FindStaticBinding.hpp"
#include "../../bindings/static/FindOfStaticBinding.hpp"

#include "StringUtils.hpp"

#include <ostream>

namespace cds {
namespace impl {
using meta::StringTraits;

template <typename C, typename = StringUtils<C, StringTraits<C>>, typename = Allocator<C>> class BaseString {};
template<typename C, typename U = StringUtils<C, StringTraits<C>>> class BaseStringView;
} // namespace impl

namespace meta {
template <typename C, typename U> struct IterableTraits<cds::impl::BaseStringView<C, U>> {
  using Value = C;
  using Iterator = iterator::ForwardAddressIterator<C const>;
  using ConstIterator = Iterator;
  using ReverseIterator = iterator::BackwardAddressIterator<C const>;
  using ConstReverseIterator = ReverseIterator;
};
} // namespace meta

namespace impl {
using sel::With;
using sel::Value;
using sel::Selector;
using sel::Immutable;

using meta::IterableTraits;
using meta::EnableIf;
using meta::Not;
using meta::IsSame;
using meta::Decay;
using meta::IsIntegral;
using meta::All;
using meta::IsConstructible;
using meta::IsBaseOf;

using meta::impl::IsIterator;
using meta::impl::IsReverseIterator;

#if CDS_ATTR(spaceship)
using std::strong_ordering;
#endif // #if CDS_ATTR(spaceship)

using meta::True;
using meta::False;
using meta::lvalue;
using meta::rvalue;
using meta::address;

namespace isStringImpl {
template <typename> struct IsString : False {};
template <typename C> struct IsString<C*> : StringTraits<C>::IsChar {};
template <typename C> struct IsString<C const*> : StringTraits<C>::IsChar {};
template <typename C, typename U> struct IsString<BaseStringView<C, U>> : True {};
} // namespace isStringImpl

template <typename T> struct IsString : isStringImpl::IsString<Decay<T>> {};

template <
    typename S, typename,
    typename = typename StringTraits<S>::IsSeparator,
    typename = typename IsIterable<S>::Type,
    typename = typename IsString<S>::Type
> class SplitPredicate {};

template <typename S, typename A> class SplitPredicate<S, A, True, False, False> {
public:
  using Allocates = False;
  using IsPatternMatching = False;

  template <typename FS>
  CDS_ATTR(2(explicit, constexpr(11))) SplitPredicate(FS&& separator, CDS_ATTR(unused) A const& _)
      CDS_ATTR(noexcept(noexcept(S(cds::forward<FS>(separator))))) : _s(cds::forward<FS>(separator)) {}

  template <typename C> CDS_ATTR(2(nodiscard, constexpr(11)))
  auto operator()(C chr) const CDS_ATTR(noexcept(noexcept(chr == _s))) -> bool {
    return chr == _s;
  }

private:
  S _s;
};

template <typename S, typename A> class SplitPredicate<S, A, False, True, False> {
public:
  using Allocates = False;
  using IsPatternMatching = False;

  template <typename FS>
  CDS_ATTR(2(explicit, constexpr(11))) SplitPredicate(FS&& separator, CDS_ATTR(unused) A const& _)
      CDS_ATTR(noexcept(noexcept(_s(cds::forward<FS>(separator))))) : _s(cds::forward<FS>(separator)) {}

  template <typename C> CDS_ATTR(2(nodiscard, constexpr(11)))
  auto operator()(C chr) const CDS_ATTR(noexcept(noexcept(impl::contains(value<S>(), chr, Equal<>())))) -> bool {
    return impl::contains(_s, chr, Equal<>());
  }

private:
  S _s;
};

template <typename> struct PatUtils {};

template <typename C, Size s> struct ArrPatUtils {
  template <typename T> CDS_ATTR(2(nodiscard, constexpr(11))) static auto length(T&&) noexcept -> Size {
    return s;
  }

  template <typename T> CDS_ATTR(2(nodiscard, constexpr(11))) static auto data(T&& data) noexcept -> C const* {
    return cds::forward<T>(data);
  }
};

template <typename C, Size s> struct PatUtils<C(&)[s]> : ArrPatUtils<C, s - 1> {};
template <typename C, Size s> struct PatUtils<C const(&)[s]> : ArrPatUtils<C, s - 1> {};

template <typename C> struct PtrPatUtils {
  using Utils = StringUtils<C, StringTraits<C>>;

  CDS_ATTR(2(nodiscard, constexpr(14))) static auto length(C const* ptr) noexcept -> Size {
    return Utils::length(ptr);
  }

  CDS_ATTR(2(nodiscard, constexpr(14))) static auto data(C const* ptr) noexcept -> C const* {
    return ptr;
  }
};

template <typename C> struct PatUtils<C*> : PtrPatUtils<C> {};
template <typename C> struct PatUtils<C*&> : PtrPatUtils<C> {};
template <typename C> struct PatUtils<C const*> : PtrPatUtils<C> {};
template <typename C> struct PatUtils<C const*&> : PtrPatUtils<C> {};

template <typename C> struct BSVPatUtils {
  template <typename T> CDS_ATTR(2(nodiscard, constexpr(11))) static auto length(T&& sv) noexcept -> Size {
    return cds::forward<T>(sv).length();
  }

  template <typename T> CDS_ATTR(2(nodiscard, constexpr(11))) static auto data(T&& sv) noexcept -> C const* {
    return cds::forward<T>(sv).data();
  }
};

template <typename C, typename U> struct PatUtils<BaseStringView<C, U>> : BSVPatUtils<C> {};
template <typename C, typename U> struct PatUtils<BaseStringView<C, U>&> : BSVPatUtils<C> {};
template <typename C, typename U> struct PatUtils<BaseStringView<C, U> const> : BSVPatUtils<C> {};
template <typename C, typename U> struct PatUtils<BaseStringView<C, U> const&> : BSVPatUtils<C> {};

template <typename S, typename A, typename I> class SplitPredicate<S, A, False, I, True> : private A {
public:
  using Allocates = True;
  using IsPatternMatching = True;
  using Utils = PatUtils<S>;

  template <typename FS, typename FA> CDS_ATTR(2(explicit, constexpr(20))) SplitPredicate(FS&& needle, FA&& alloc)
      CDS_ATTR(noexcept(noexcept(lvalue<A>().allocate(0)))) :
      A(cds::forward<FA>(alloc)),
      _pat(cds::forward<FS>(needle)),
      _lps(A::allocate(len())) {
    _lps[0] = 0;
    Size idx = 1u;
    Size parseIdx = 0;
    auto const* pattern = Utils::data(cds::forward<FS>(needle));
    while (idx < len()) {
      if (pattern[idx] == pattern[parseIdx]) {
        _lps[idx++] = ++parseIdx;
      } else if (parseIdx > 0) {
        parseIdx = _lps[parseIdx - 1];
      } else {
        _lps[idx++] = 0;
      }
    }
  }

  template <typename Ref = meta::IsRef<S>, EnableIf<Ref> = 0>
  CDS_ATTR(2(explicit, constexpr(14))) SplitPredicate(SplitPredicate&& pred) noexcept :
      A(cds::move(pred)), _pat(pred._pat), _lps(cds::exchange(pred._lps, nullptr)) {}

  template <typename Ref = meta::IsRef<S>, EnableIf<Not<Ref>> = 0>
  CDS_ATTR(2(explicit, constexpr(14))) SplitPredicate(SplitPredicate&& pred)
      CDS_ATTR(noexcept(noexcept(S(cds::move(pred._pat))))) :
      A(cds::move(pred)), _pat(cds::move(pred._pat)), _lps(cds::exchange(pred._lps, nullptr)) {}

  SplitPredicate(SplitPredicate const&) noexcept = delete;
  auto operator=(SplitPredicate const&) noexcept -> SplitPredicate& = delete;
  auto operator=(SplitPredicate&&) noexcept -> SplitPredicate& = delete;

  CDS_ATTR(constexpr(20)) ~SplitPredicate() noexcept {
    A::deallocate(_lps, len());
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto len() const
      CDS_ATTR(noexcept(noexcept(Utils::length(value<S>())))) -> Size {
    return Utils::length(_pat);
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto data() const
      CDS_ATTR(noexcept(noexcept(Utils::data(value<S>())))) -> decltype(Utils::data(value<S>())) {
    return Utils::data(_pat);
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto lps() const noexcept -> Size const* {
    return _lps;
  }

private:
  S _pat;
  Size* _lps;
};

template <typename R, typename P> class SplitIterator {
public:
  using View = typename R::View;

  CDS_ATTR(2(nodiscard, constexpr(14))) SplitIterator(R const* r, P const& p, Size limit)
      CDS_ATTR(noexcept(noexcept(nextSegment()))) : _e(!r || r->empty()), _l(limit), _r(r), _p(p) {
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
  template <typename PM = typename P::IsPatternMatching, EnableIf<Not<PM>> = 0> CDS_ATTR(constexpr(14))
  auto nextSegment() CDS_ATTR(noexcept(
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

  template <typename PM = typename P::IsPatternMatching, EnableIf<PM> = 0> CDS_ATTR(constexpr(14))
  auto nextSegment() CDS_ATTR(noexcept(noexcept(rvalue<R>().sub(0)) && noexcept(rvalue<R>().sub(0, 0)))) -> void {
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

template <typename R, typename P> class SplitRange {
public:
  using Iterable = R;
  using Predicate = P;
  using Iterator = SplitIterator<Decay<R>, Decay<P>>;

  template <typename FR, typename S, typename A, typename DA = typename P::Allocates, EnableIf<DA> = 0>
  CDS_ATTR(constexpr(20)) SplitRange(FR&& view, S&& separator, Size limit, A&& alloc) CDS_ATTR(noexcept(
        noexcept(R(cds::forward<FR>(view))) && noexcept(P(cds::forward<S>(separator), cds::forward<A>(alloc)))
  )) : _r(cds::forward<FR>(view)), _p(cds::forward<S>(separator), cds::forward<A>(alloc)), _l(limit) {}

  template <typename FR, typename S, typename A, typename DA = typename P::Allocates, EnableIf<Not<DA>> = 0>
  CDS_ATTR(constexpr(11)) SplitRange(FR&& view, S&& separator, Size limit, A&& alloc) CDS_ATTR(noexcept(
        noexcept(R(cds::forward<FR>(view))) && noexcept(P(cds::forward<S>(separator), cds::forward<A>(alloc)))
  )) : _r(cds::forward<FR>(view)), _p(cds::forward<S>(separator), cds::forward<A>(alloc)), _l(limit) {}

  CDS_ATTR(2(nodiscard, constexpr(14))) auto begin() const
      CDS_ATTR(noexcept(noexcept(Iterator(nullptr, value<P>(), 0)))) -> Iterator {
    return Iterator(&_r, _p, _l);
  }

#if CDS_ATTR(sentinel)
  CDS_ATTR(2(nodiscard, constexpr(11))) auto end() const noexcept -> Sentinel {
    return {};
  }
#else // #if CDS_ATTR(sentinel)
  CDS_ATTR(2(nodiscard, constexpr(14))) auto end() const
      CDS_ATTR(noexcept(noexcept(Iterator(nullptr, value<P>(), 0)))) -> Iterator {
    return Iterator(nullptr, _p, _l);
  }
#endif // #if CDS_ATTR(sentinel) #else

private:
  R _r;
  P _p;
  Size _l;
};

using extension::Extend;
template <
    typename I, typename S, typename R = SplitRange<Extend<I>, SplitPredicate<Extend<S>, std::nullptr_t>>,
    EnableIf<Not<IsString<RemoveCVRef<S>>>> = 0
> CDS_ATTR(2(nodiscard, constexpr(14))) auto split(I&& range, S&& sep, Size limit)
    CDS_ATTR(noexcept(noexcept(R(cds::forward<I>(range), cds::forward<S>(sep), limit, nullptr)))) -> R {
  return R(cds::forward<I>(range), cds::forward<S>(sep), limit, nullptr);
}

template <
    typename I, typename S, typename A, typename R = SplitRange<Extend<I>, SplitPredicate<Extend<S>, RemoveCVRef<A>>>,
    EnableIf<And<IsString<RemoveCVRef<S>>, meta::IsAllocator<RemoveCVRef<A>>>> = 0
> CDS_ATTR(2(nodiscard, constexpr(20))) auto split(I&& range, S&& sep, Size limit, A&& alloc)
    CDS_ATTR(noexcept(noexcept(R(cds::forward<I>(range), cds::forward<S>(sep), limit, cds::forward<A>(alloc))))) -> R {
  return R(cds::forward<I>(range), cds::forward<S>(sep), limit, cds::forward<A>(alloc));
}

template <typename C, typename U> struct FindStringTransformer {
  template <typename IB, typename IE, typename I>
  CDS_ATTR(2(nodiscard, constexpr(11))) auto operator()(IB&& b, IE&& e, I&& i) const noexcept -> Idx {
    return cds::forward<IE>(e) == cds::forward<I>(i)
        ? BaseStringView<C, U>::npos
        : (cds::forward<I>(i) - cds::forward<IB>(b));
  }
};

namespace bindingsBSV {
template <typename C, typename U> using Self = BaseStringView<C, U>;
template <typename C, typename U> using Traits = IterableTraits<Self<C, U>>;

using ContainsOpt = With<Value, Selector>;
template <typename C, typename U> struct ContainsOf :
    ContainsOfStaticBinding<Self<C, U>, ContainsOpt> {};

using FindOpt = With<Value, Selector, Immutable>;
template <typename C, typename U> struct FindTr :
    FindStringTransformer<C, U> {};
template <typename C, typename U> struct Find :
    FindStaticBinding<Self<C, U>, FindOpt, FindTr<C, U>, FindTr<C, U>> {};
template <typename C, typename U> struct FindOf :
    FindOfStaticBinding<Self<C, U>, FindOpt, FindTr<C, U>, FindTr<C, U>> {};
} // namespace bindingsBSV

template <typename C, typename U> class CDS_ATTR(inheritsEBOs) BaseStringView :
    public bindingsBSV::Traits<C, U>,
    public bindingsBSV::ContainsOf<C, U>,
    public bindingsBSV::Find<C, U>,
    public bindingsBSV::FindOf<C, U> {
public:
  using STraits = typename U::Traits;
  using ITraits = bindingsBSV::Traits<C, U>;
  using typename ITraits::Value;
  using typename ITraits::Iterator;
  using typename ITraits::ConstIterator;
  using typename ITraits::ReverseIterator;
  using typename ITraits::ConstReverseIterator;
  using Address = C const*;
  using View = BaseStringView;
  using Char = C;
  using OStream = typename STraits::OStream;
  using Utils = U;

  using bindingsBSV::Find<C, U>::findFirst;

  static Idx const npos;
  static Idx const invalidIndex;

  CDS_ATTR(constexpr(11)) BaseStringView() noexcept = default;
  CDS_ATTR(constexpr(11)) BaseStringView(BaseStringView const&) noexcept = default;
  CDS_ATTR(constexpr(11)) BaseStringView(BaseStringView &&) noexcept = default;
  CDS_ATTR(constexpr(20)) ~BaseStringView() noexcept = default;

  template <typename AddressLike, EnableIf<Not<IsSame<Decay<AddressLike>, BaseStringView>>> = 0>
  CDS_ATTR(2(implicit, constexpr(11))) BaseStringView(AddressLike&& string) noexcept;
  CDS_ATTR(constexpr(11)) BaseStringView(Address data, Size length) noexcept : _data(data), _length(length) {}

  CDS_ATTR(constexpr(14)) auto operator=(BaseStringView const&) noexcept -> BaseStringView& = default;
  CDS_ATTR(constexpr(14)) auto operator=(BaseStringView&&) noexcept -> BaseStringView& = default;

  CDS_ATTR(2(nodiscard, constexpr(11))) auto data() const noexcept -> Address {
    return _data;
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto length() const noexcept -> Size {
    return _length;
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto size() const noexcept -> Size {
    return _length;
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto empty() const noexcept -> bool {
    return _length == 0u;
  }

  CDS_ATTR(3(nodiscard, explicit, constexpr(11))) operator bool() const noexcept {
    return !empty();
  }

  CDS_ATTR(constexpr(14)) auto clear() noexcept -> void {
    _data = nullptr;
    _length = 0u;
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto begin() const noexcept -> Iterator {
    return Iterator(_data);
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto end() const noexcept -> Iterator {
    return Iterator(_data + _length);
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto cbegin() const noexcept -> ConstIterator {
    return ConstIterator(_data);
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto cend() const noexcept -> ConstIterator {
    return ConstIterator(_data + _length);
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto rbegin() const noexcept -> ReverseIterator {
    return ReverseIterator(_data + _length - 1);
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto rend() const noexcept -> ReverseIterator {
    return ReverseIterator(_data - 1);
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto crbegin() const noexcept -> ConstReverseIterator {
    return ConstReverseIterator(_data + _length - 1);
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto crend() const noexcept -> ConstReverseIterator {
    return ConstReverseIterator(_data - 1);
  }

  template <typename N, EnableIf<IsIntegral<N>> = 0>
  CDS_ATTR(2(nodiscard, constexpr(11))) auto operator[](N idx) const noexcept -> Value {
    return _data[idx];
  }

  template <typename N, EnableIf<IsIntegral<N>> = 0>
  CDS_ATTR(2(nodiscard, constexpr(11))) auto at(N idx) const noexcept -> Value {
    return _data[idx];
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto front() const noexcept -> Value {
    return _data[0u];
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto back() const noexcept -> Value {
    return _data[_length - 1u];
  }

  template <typename N, EnableIf<IsIntegral<N>> = 0>
  CDS_ATTR(2(nodiscard, constexpr(11))) auto sub(N from) const noexcept -> BaseStringView {
    return sub(from, size());
  }

  template <typename N, EnableIf<IsIntegral<N>> = 0>
  CDS_ATTR(2(nodiscard, constexpr(11))) auto operator()(N from) const noexcept -> BaseStringView {
    return sub(from, size());
  }

  template <typename N1, typename N2, EnableIf<All<IsIntegral, N1, N2>> = 0>
  CDS_ATTR(2(nodiscard, constexpr(11))) auto operator()(N1 from, N2 until) const noexcept -> BaseStringView {
    return sub(from, until);
  }

  template <typename N1, typename N2, EnableIf<All<IsIntegral, N1, N2>> = 0>
  CDS_ATTR(2(nodiscard, constexpr(14))) auto sub(N1 from, N2 until) const noexcept -> BaseStringView {
    auto const sUntil = static_cast<Size>(until);
    auto const sFrom = static_cast<Size>(from);

    if (sFrom >= sUntil) {
      return {};
    }

    return {_data + sFrom, sUntil - sFrom};
  }

  CDS_ATTR(2(nodiscard, constexpr(14))) auto contains(Value character) const noexcept -> bool {
    return findFirst(character) != npos;
  }

  template <typename S> CDS_ATTR(2(nodiscard, constexpr(14))) auto contains(
      Value character, S&& selector
  ) const noexcept -> bool {
    return findFirst(character, cds::forward<S>(selector)) != npos;
  }

  template <typename FC, typename FU> CDS_ATTR(constexpr(14)) friend auto operator==(
      BaseStringView<FC, FU> const& lhs, BaseStringView<FC, FU> const& rhs
  ) noexcept -> bool;

  template <typename FC, typename FU> CDS_ATTR(constexpr(14)) friend auto operator!=(
      BaseStringView<FC, FU> const& lhs, BaseStringView<FC, FU> const& rhs
  ) noexcept -> bool;

  template <typename FC, typename FU> CDS_ATTR(constexpr(14)) friend auto operator<(
      BaseStringView<FC, FU> const& lhs, BaseStringView<FC, FU> const& rhs
  ) noexcept -> bool;

  template <typename FC, typename FU> CDS_ATTR(constexpr(14)) friend auto operator>(
      BaseStringView<FC, FU> const& lhs, BaseStringView<FC, FU> const& rhs
  ) noexcept -> bool;

  template <typename FC, typename FU> CDS_ATTR(constexpr(14)) friend auto operator<=(
      BaseStringView<FC, FU> const& lhs, BaseStringView<FC, FU> const& rhs
  ) noexcept -> bool;

  template <typename FC, typename FU> CDS_ATTR(constexpr(14)) friend auto operator>=(
      BaseStringView<FC, FU> const& lhs, BaseStringView<FC, FU> const& rhs
  ) noexcept -> bool;

#if CDS_ATTR(spaceship)
  template <typename FC, typename FU> CDS_ATTR(constexpr(14)) friend auto operator<=>(
      BaseStringView<FC, FU> const& lhs, BaseStringView<FC, FU> const& rhs
  ) noexcept -> strong_ordering;
#endif // #if CDS_ATTR(spaceship)

  template <typename A = Allocator<C>> CDS_ATTR(2(nodiscard, constexpr(20)))
  auto str(A const& alloc = A()) const CDS_ATTR(noexcept(false)) -> BaseString<C, U, A>;

  template <typename FC, typename FU>
  friend auto operator<<(typename BaseStringView<FC, FU>::OStream& out, BaseStringView<FC, FU> const& obj)
      CDS_ATTR(noexcept(noexcept(out.write(obj._data, obj._length)))) -> typename BaseStringView<FC, FU>::OStream&;

  template <typename S, EnableIf<Not<IsString<S>>> = 0>
  CDS_ATTR(2(nodiscard, constexpr(14))) auto split(S&& separator) const&
      CDS_ATTR(noexcept(noexcept(impl::split(lvalue<BaseStringView const>(), cds::forward<S>(separator), 0))))
      -> decltype(impl::split(lvalue<BaseStringView const>(), cds::forward<S>(separator), 0)) {
    return impl::split(*this, cds::forward<S>(separator), limits::sizeMax);
  }

  template <typename S, EnableIf<Not<IsString<S>>> = 0>
  CDS_ATTR(2(nodiscard, constexpr(14))) auto split(S&& separator) const&&
      CDS_ATTR(noexcept(noexcept(impl::split(rvalue<BaseStringView const>(), cds::forward<S>(separator), 0))))
      -> decltype(impl::split(rvalue<BaseStringView const>(), cds::forward<S>(separator), 0)) {
    return impl::split(cds::move(*this), cds::forward<S>(separator), limits::sizeMax);
  }

  template <typename S, EnableIf<Not<IsString<S>>> = 0>
  CDS_ATTR(2(nodiscard, constexpr(14))) auto split(S&& separator, Size limit) const& CDS_ATTR(noexcept(noexcept(
      impl::split(lvalue<BaseStringView const>(), cds::forward<S>(separator), limit)
  ))) -> decltype(impl::split(lvalue<BaseStringView const>(), cds::forward<S>(separator), limit)) {
    return impl::split(*this, cds::forward<S>(separator), limit);
  }

  template <typename S, EnableIf<Not<IsString<S>>> = 0>
  CDS_ATTR(2(nodiscard, constexpr(14))) auto split(S&& separator, Size limit) const&& CDS_ATTR(noexcept(noexcept(
      impl::split(rvalue<BaseStringView const>(), cds::forward<S>(separator), limit)
  ))) ->
      decltype(impl::split(rvalue<BaseStringView const>(), cds::forward<S>(separator), limit)) {
    return impl::split(cds::move(*this), cds::forward<S>(separator), limit);
  }

  template <typename S, typename A = Allocator<Size>, EnableIf<IsString<S>> = 0>
  CDS_ATTR(2(nodiscard, constexpr(20))) auto split(S&& separator, A&& alloc = A()) const&
      CDS_ATTR(noexcept(noexcept(impl::split(lvalue<BaseStringView const>(), cds::forward<S>(separator), 0, cds::forward<A>(alloc)))))
      -> decltype(impl::split(lvalue<BaseStringView const>(), cds::forward<S>(separator), 0, cds::forward<A>(alloc))) {
    return impl::split(*this, cds::forward<S>(separator), limits::sizeMax, cds::forward<A>(alloc));
  }

  template <typename S, typename A = Allocator<Size>, EnableIf<IsString<S>> = 0>
  CDS_ATTR(2(nodiscard, constexpr(20))) auto split(S&& separator, A&& alloc = A()) const&&
      CDS_ATTR(noexcept(noexcept(impl::split(rvalue<BaseStringView const>(), cds::forward<S>(separator), 0, cds::forward<A>(alloc)))))
      -> decltype(impl::split(rvalue<BaseStringView const>(), cds::forward<S>(separator), 0, cds::forward<A>(alloc))) {
    return impl::split(cds::move(*this), cds::forward<S>(separator), limits::sizeMax, cds::forward<A>(alloc));
  }

  template <typename S, typename A = Allocator<Size>, EnableIf<IsString<S>> = 0>
  CDS_ATTR(2(nodiscard, constexpr(20))) auto split(S&& separator, Size limit, A&& alloc = A()) const& CDS_ATTR(noexcept(noexcept(
      impl::split(lvalue<BaseStringView const>(), cds::forward<S>(separator), limit, cds::forward<A>(alloc))
  ))) -> decltype(impl::split(lvalue<BaseStringView const>(), cds::forward<S>(separator), limit, cds::forward<A>(alloc))) {
    return impl::split(*this, cds::forward<S>(separator), limit, cds::forward<A>(alloc));
  }

  template <typename S, typename A = Allocator<Size>, EnableIf<IsString<S>> = 0>
  CDS_ATTR(2(nodiscard, constexpr(20))) auto split(S&& separator, Size limit, A&& alloc = A()) const&& CDS_ATTR(noexcept(noexcept(
      impl::split(rvalue<BaseStringView const>(), cds::forward<S>(separator), limit, cds::forward<A>(alloc))
  ))) ->
      decltype(impl::split(rvalue<BaseStringView const>(), cds::forward<S>(separator), limit, cds::forward<A>(alloc))) {
    return impl::split(cds::move(*this), cds::forward<S>(separator), limit, cds::forward<A>(alloc));
  }

private:
  Address _data {nullptr};
  Size _length {0u};
};

template <typename C, typename U> Idx const BaseStringView<C, U>::npos = -1;
template <typename C, typename U> Idx const BaseStringView<C, U>::invalidIndex = npos;

template <typename C, typename U>
template <typename AddressLike, EnableIf<Not<IsSame<Decay<AddressLike>, BaseStringView<C, U>>>>>
CDS_ATTR(constexpr(11)) BaseStringView<C, U>::BaseStringView(AddressLike &&string) noexcept :
    _data(string),
    _length(U::length(cds::forward<AddressLike>(string))) {}

template <typename C, typename U> CDS_ATTR(2(nodiscard, constexpr(14))) auto operator==(
    BaseStringView<C, U> const& lhs, BaseStringView<C, U> const& rhs
) noexcept -> bool {
  return U::compare(lhs._data, lhs._length, rhs._data, rhs._length) == U::Ordering::Equal;
}

template <typename C, typename U, typename T, EnableIf<And<
    IsConstructible<BaseStringView<C, U>, T>,
    Not<IsBaseOf<BaseStringView<C, U>, Decay<T>>>
>> = 0> CDS_ATTR(2(nodiscard, constexpr(11))) auto operator==(
    BaseStringView<C, U> const& lhs, T&& rhs
) noexcept -> bool {
  return lhs == BaseStringView<C, U>(cds::forward<T>(rhs));
}

template <typename C, typename U, typename T, EnableIf<And<
    IsConstructible<BaseStringView<C, U>, T>,
    Not<IsBaseOf<BaseStringView<C, U>, Decay<T>>>
>> = 0> CDS_ATTR(2(nodiscard, constexpr(11))) auto operator==(
    T&& lhs, BaseStringView<C, U> const& rhs
) noexcept -> bool {
  return BaseStringView<C, U>(cds::forward<T>(lhs)) == rhs;
}

template <typename C, typename U> CDS_ATTR(2(nodiscard, constexpr(14))) auto operator!=(
    BaseStringView<C, U> const& lhs, BaseStringView<C, U> const& rhs
) noexcept -> bool {
  return U::compare(lhs._data, lhs._length, rhs._data, rhs._length) != U::Ordering::Equal;
}

template <typename C, typename U, typename T, EnableIf<And<
    IsConstructible<BaseStringView<C, U>, T>,
    Not<IsBaseOf<BaseStringView<C, U>, Decay<T>>>
>> = 0> CDS_ATTR(2(nodiscard, constexpr(11))) auto operator!=(
    BaseStringView<C, U> const& lhs, T&& rhs
) noexcept -> bool {
  return lhs != BaseStringView<C, U>(cds::forward<T>(rhs));
}

template <typename C, typename U, typename T, EnableIf<And<
    IsConstructible<BaseStringView<C, U>, T>,
    Not<IsBaseOf<BaseStringView<C, U>, Decay<T>>>
>> = 0> CDS_ATTR(2(nodiscard, constexpr(11))) auto operator!=(
    T&& lhs, BaseStringView<C, U> const& rhs
) noexcept -> bool {
  return BaseStringView<C, U>(cds::forward<T>(lhs)) != rhs;
}

template <typename C, typename U> CDS_ATTR(2(nodiscard, constexpr(14))) auto operator<(
    BaseStringView<C, U> const& lhs, BaseStringView<C, U> const& rhs
) noexcept -> bool {
  return U::compare(lhs._data, lhs._length, rhs._data, rhs._length) == U::Ordering::Less;
}

template <typename C, typename U, typename T, EnableIf<And<
    IsConstructible<BaseStringView<C, U>, T>,
    Not<IsBaseOf<BaseStringView<C, U>, Decay<T>>>
>> = 0> CDS_ATTR(2(nodiscard, constexpr(11))) auto operator<(
    BaseStringView<C, U> const& lhs, T&& rhs
) noexcept -> bool {
  return lhs < BaseStringView<C, U>(cds::forward<T>(rhs));
}

template <typename C, typename U, typename T, EnableIf<And<
    IsConstructible<BaseStringView<C, U>, T>,
    Not<IsBaseOf<BaseStringView<C, U>, Decay<T>>>
>> = 0> CDS_ATTR(2(nodiscard, constexpr(11))) auto operator<(
    T&& lhs, BaseStringView<C, U> const& rhs
) noexcept -> bool {
  return BaseStringView<C, U>(cds::forward<T>(lhs)) < rhs;
}

template <typename C, typename U> CDS_ATTR(2(nodiscard, constexpr(14))) auto operator>(
    BaseStringView<C, U> const& lhs, BaseStringView<C, U> const& rhs
) noexcept -> bool {
  return U::compare(lhs._data, lhs._length, rhs._data, rhs._length) == U::Ordering::Greater;
}

template <typename C, typename U, typename T, EnableIf<And<
    IsConstructible<BaseStringView<C, U>, T>,
    Not<IsBaseOf<BaseStringView<C, U>, Decay<T>>>
>> = 0> CDS_ATTR(2(nodiscard, constexpr(11))) auto operator>(
    BaseStringView<C, U> const& lhs, T&& rhs
) noexcept -> bool {
  return lhs > BaseStringView<C, U>(cds::forward<T>(rhs));
}

template <typename C, typename U, typename T, EnableIf<And<
    IsConstructible<BaseStringView<C, U>, T>,
    Not<IsBaseOf<BaseStringView<C, U>, Decay<T>>>
>> = 0> CDS_ATTR(2(nodiscard, constexpr(11))) auto operator>(
    T&& lhs, BaseStringView<C, U> const& rhs
) noexcept -> bool {
  return BaseStringView<C, U>(cds::forward<T>(lhs)) > rhs;
}

template <typename C, typename U> CDS_ATTR(2(nodiscard, constexpr(14))) auto operator<=(
    BaseStringView<C, U> const& lhs, BaseStringView<C, U> const& rhs
) noexcept -> bool {
  return U::compare(lhs._data, lhs._length, rhs._data, rhs._length) != U::Ordering::Greater;
}

template <typename C, typename U, typename T, EnableIf<And<
    IsConstructible<BaseStringView<C, U>, T>,
    Not<IsBaseOf<BaseStringView<C, U>, Decay<T>>>
>> = 0> CDS_ATTR(2(nodiscard, constexpr(11))) auto operator<=(
    BaseStringView<C, U> const& lhs, T&& rhs
) noexcept -> bool {
  return lhs <= BaseStringView<C, U>(cds::forward<T>(rhs));
}

template <typename C, typename U, typename T, EnableIf<And<
    IsConstructible<BaseStringView<C, U>, T>,
    Not<IsBaseOf<BaseStringView<C, U>, Decay<T>>>
>> = 0> CDS_ATTR(2(nodiscard, constexpr(11))) auto operator<=(
    T&& lhs, BaseStringView<C, U> const& rhs
) noexcept -> bool {
  return BaseStringView<C, U>(cds::forward<T>(lhs)) <= rhs;
}

template <typename C, typename U> CDS_ATTR(2(nodiscard, constexpr(14))) auto operator>=(
    BaseStringView<C, U> const& lhs, BaseStringView<C, U> const& rhs
) noexcept -> bool {
  return U::compare(lhs._data, lhs._length, rhs._data, rhs._length) != U::Ordering::Less;
}

template <typename C, typename U, typename T, EnableIf<And<
    IsConstructible<BaseStringView<C, U>, T>,
    Not<IsBaseOf<BaseStringView<C, U>, Decay<T>>>
>> = 0> CDS_ATTR(2(nodiscard, constexpr(11))) auto operator>=(
    BaseStringView<C, U> const& lhs, T&& rhs
) noexcept -> bool {
return lhs >= BaseStringView<C, U>(cds::forward<T>(rhs));
}

template <typename C, typename U, typename T, EnableIf<And<
    IsConstructible<BaseStringView<C, U>, T>,
    Not<IsBaseOf<BaseStringView<C, U>, Decay<T>>>
>> = 0> CDS_ATTR(2(nodiscard, constexpr(11))) auto operator>=(
    T&& lhs, BaseStringView<C, U> const& rhs
) noexcept -> bool {
  return BaseStringView<C, U>(cds::forward<T>(lhs)) >= rhs;
}

#if CDS_ATTR(spaceship)
template <typename C, typename U> CDS_ATTR(constexpr(14)) auto operator<=>(
    BaseStringView<C, U> const& lhs, BaseStringView<C, U> const& rhs
) noexcept -> strong_ordering {
  if (lhs._data == rhs._data && lhs._length == rhs._length) {
    return strong_ordering::equivalent;
  }

  auto const compareResult = U::compare(lhs._data, lhs._length, rhs._data, rhs._length);
  if (compareResult == U::Ordering::Greater) { return strong_ordering::greater; }
  if (compareResult == U::Ordering::Less) { return strong_ordering::less; }
  return strong_ordering::equal;
}

template <typename C, typename U, typename T, EnableIf<And<
    IsConstructible<BaseStringView<C, U>, T>,
    Not<IsBaseOf<BaseStringView<C, U>, Decay<T>>>
>> = 0> CDS_ATTR(2(nodiscard, constexpr(11))) auto operator<=>(
    BaseStringView<C, U> const& lhs, T&& rhs
) noexcept -> strong_ordering {
  return lhs <=> BaseStringView<C, U>(cds::forward<T>(rhs));
}

template <typename C, typename U, typename T, EnableIf<And<
    IsConstructible<BaseStringView<C, U>, T>,
    Not<IsBaseOf<BaseStringView<C, U>, Decay<T>>>
>> = 0> CDS_ATTR(2(nodiscard, constexpr(11))) auto operator<=>(
    T&& lhs, BaseStringView<C, U> const& rhs
) noexcept -> strong_ordering {
  return BaseStringView<C, U>(cds::forward<T>(lhs)) <=> rhs;
}
#endif // #if CDS_ATTR(spaceship)

template <typename FC, typename FU>
auto operator<<(typename BaseStringView<FC, FU>::OStream& out, BaseStringView<FC, FU> const& obj)
    CDS_ATTR(noexcept(noexcept(out.write(obj._data, obj._length)))) -> typename BaseStringView<FC, FU>::OStream& {
  out.write(obj._data, obj._length);
  return out;
}
} // namespace impl
} // namespace cds

#endif // CDS_PRIMITIVE_STRING_VIEW_BASE_HPP
