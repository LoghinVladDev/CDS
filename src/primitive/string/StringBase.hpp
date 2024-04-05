//
// Created by loghin on 12/8/23.
//

#ifndef CDS_PRIMITIVE_STRING_BASE_HPP
#define CDS_PRIMITIVE_STRING_BASE_HPP
#pragma once

#include "StringBaseDecl.hpp"
#include "StringSplit.hpp"
#include "StringFind.hpp"
#include "StringUtils.hpp"
#include "StringOperator.hpp"

#include "../../bindings/BindingSelectors.hpp"
#include "../../bindings/static/ContainsOfStaticBinding.hpp"
#include "../../bindings/static/FindStaticBinding.hpp"
#include "../../bindings/static/FindOfStaticBinding.hpp"
#include "../../bindings/static/GenericLoopBinding.hpp"

#include "../../stdlib/ostream.hpp"

namespace cds {
namespace impl {
using meta::EnableIf;
using meta::Int;
using meta::IsIntegral;
using meta::IsFloating;

using sel::With;
using sel::Value;
using sel::Projector;
using sel::Immutable;
using sel::Mutable;

#if CDS_ATTR(spaceship)
using std::strong_ordering;
#endif

namespace sbo {
template <typename C> struct StringNonSboData {
  C* buf;
  Size cap;
  Size len : sizeof(Size) * 8 - 1;
  bool sbo : 1;
};

template <typename C, typename = Int<sizeof(C)>> struct StringSboData {};
template <typename C> struct StringSboData<C, Int<1>> {
  C buf[sizeof(StringNonSboData<C>) - 1u];
  U8 len : 7;
  bool sbo : 1;

  CDS_ATTR(constexpr(14)) auto initialize() noexcept -> void {
    impl::fill(buf, buf + (sizeof(StringNonSboData<C>) - 1), 0);
  }
};

template <typename C> struct StringSboData<C, Int<2>> {
  C buf[sizeof(StringNonSboData<C>) / 2u - 1u];
  U8 pad[1u];
  U8 len : 7;
  bool sbo : 1;

  CDS_ATTR(constexpr(14)) auto initialize() noexcept -> void {
    impl::fill(buf, buf + (sizeof(StringNonSboData<C>) / 2 - 1), 0);
    pad[0] = 0;
  }
};

template <typename C> struct StringSboData<C, Int<4>> {
  C buf[sizeof(StringNonSboData<C>) / 4u - 1u];
  U8 pad[3u];
  U8 len : 7;
  bool sbo : 1;

  CDS_ATTR(constexpr(14)) auto initialize() noexcept -> void {
    impl::fill(buf, buf + (sizeof(StringNonSboData<C>) / 4 - 1), 0);
    impl::fill(pad, pad + 3u, 0);
  }
};

template <typename C> struct StringData {
  union {
    StringNonSboData<C> _nrm;
    StringSboData<C> _sbo;
  };
};

#if CDS_ATTR(bitarch) == 64u
static_assert(sizeof(StringData<U8>) == 24u, "invalid string data sizes");
static_assert(sizeof(StringData<U16>) == 24u, "invalid string data sizes");
static_assert(sizeof(StringData<U32>) == 24u, "invalid string data sizes");
#elif CDS_ATTR(bitarch) == 32u
static_assert(sizeof(StringData<U8>) == 12u, "invalid string data sizes");
static_assert(sizeof(StringData<U16>) == 12u, "invalid string data sizes");
static_assert(sizeof(StringData<U32>) == 12u, "invalid string data sizes");
#endif
} // namespace sbo

using meta::IterableTraits;

template <typename C, typename U, typename A> struct FindStringTransformer {
  template <typename IB, typename IE, typename I>
  CDS_ATTR(2(nodiscard, constexpr(11))) auto operator()(IB&& b, IE&& e, I&& i) const noexcept -> Idx {
    return cds::forward<IE>(e) == cds::forward<I>(i)
        ? BaseString<C, U, A>::npos
        : (cds::forward<I>(i) - cds::forward<IB>(b));
  }
};

namespace bindingsBS {
template <typename C, typename U, typename A> using Self = BaseString<C, U, A>;
template <typename C, typename U, typename A> using Traits = IterableTraits<Self<C, U, A>>;

using ContainsOpt = With<Value, Projector>;
template <typename C, typename U, typename A> struct ContainsOf :
    ContainsOfStaticBinding<Self<C, U, A>, ContainsOpt> {};

using FindOpt = With<Value, Projector, Immutable, Mutable>;
template <typename C, typename U, typename A> struct FindTr :
    FindStringTransformer<C, U, A> {};
template <typename C, typename U, typename A> struct Find :
    FindStaticBinding<Self<C, U, A>, FindOpt, FindTr<C, U, A>, FindTr<C, U, A>> {};
template <typename C, typename U, typename A> struct FindOf :
    FindOfStaticBinding<Self<C, U, A>, FindOpt, FindTr<C, U, A>, FindTr<C, U, A>> {};

using LoopOpt = With<Immutable, Mutable>;
template <typename C, typename U, typename A> struct GenericLoop :
    GenericLoopBinding<Self<C, U, A>, LoopOpt> {};
} // namespace bindingsBS

template <typename C, typename U, typename A> class CDS_ATTR(inheritsEBOs) BaseString :
    public bindingsBS::Traits<C, U, A>,
    public bindingsBS::ContainsOf<C, U, A>,
    public bindingsBS::Find<C, U, A>,
    public bindingsBS::FindOf<C, U, A>,
    public bindingsBS::GenericLoop<C, U, A>,
    private strop::StringOperatorUser,
    private sbo::StringData<C>,
    private A {
  using sbo::StringData<C>::_sbo;
  using sbo::StringData<C>::_nrm;

public:
  using STraits = typename U::Traits;
  using ITraits = bindingsBS::Traits<C, U, A>;
  using typename ITraits::Value;
  using typename ITraits::Iterator;
  using typename ITraits::ConstIterator;
  using typename ITraits::ReverseIterator;
  using typename ITraits::ConstReverseIterator;
  using Address = C const*;
  using View = BaseStringView<C, U>;
  using Char = C;
  using OStream = typename STraits::OStream;
  using Utils = U;

  using bindingsBS::Find<C, U, A>::findFirst;

  static Idx const npos;
  static Idx const invalidIndex;

  CDS_ATTR(constexpr(20)) BaseString(Address data, Size const length, A const& alloc = A())
      CDS_ATTR(noexcept(false)) :
      A(alloc) {
    copyUninitialized(data, length);
  }

  CDS_ATTR(constexpr(14)) BaseString() {
    sboInit();
  }

  CDS_ATTR(constexpr(20)) BaseString(BaseString const& str) CDS_ATTR(noexcept(false)) :
      BaseString(str.data(), str.length()) {}

  CDS_ATTR(constexpr(20)) BaseString(BaseString&& str) noexcept : A(cds::move(str)) {
    transfer(cds::move(str));
  }

  template <
      typename Convertible, typename D = RemoveCVRef<Convertible>, EnableIf<And<
          Not<IsSame<D, BaseString>>, Not<IsIntegral<D>>, Not<IsFloating<D>>
      >> = 0
  > CDS_ATTR(2(implicit, constexpr(20)))
  BaseString(Convertible&& string, A const& alloc = A()) CDS_ATTR(noexcept(false)) :
      BaseString(
          StringAbstract<Convertible>::data(cds::forward<Convertible>(string)),
          StringAbstract<Convertible>::length(cds::forward<Convertible>(string)),
          alloc
      ) {}

  CDS_ATTR(constexpr(20)) BaseString(Size const length, Char const fill, A const& alloc = A())
      CDS_ATTR(noexcept(false)) : A(alloc) {
    init(length);
    *impl::fill(begin(), end(), fill) = STraits::nullChar;
  }

  CDS_ATTR(2(implicit, constexpr(20))) BaseString(bool value, A const& alloc = A()) noexcept :
      BaseString(value ? "true" : "false", value ? 4 : 5, alloc) {}

  CDS_ATTR(2(implicit, constexpr(20))) BaseString(Char character, A const& alloc = A()) noexcept :
      BaseString(&character, minOf(character, 1), alloc) {}

  template <typename N, EnableIf<IsIntegral<N>> = 0>
  CDS_ATTR(2(implicit, constexpr(20))) BaseString(N integral, A const& alloc = A()) noexcept : A(alloc) {
    auto const len = U::intLength(integral, 10);
    init(len);
    *U::writeInt(integral, len, data()) = STraits::nullChar;
  }

  template <typename F, EnableIf<IsFloating<F>> = 0>
  CDS_ATTR(2(implicit, constexpr(20))) BaseString(F floating, A const& alloc = A()) noexcept :
      BaseString(std::to_string(floating), alloc) {
    auto const len = U::floatingLength(floating);
    init(len);
    *U::writeFloating(floating, len, data()) = STraits::nullChar;
  }

  CDS_ATTR(constexpr(20)) ~BaseString() noexcept {
    clear();
  }

  CDS_ATTR(constexpr(20)) auto operator=(BaseString const& str) CDS_ATTR(noexcept(false)) -> BaseString& {
    if (&str == this) {
      return *this;
    }

    copy(str.data(), str.length());
    return *this;
  }

  CDS_ATTR(constexpr(20)) auto operator=(BaseString&& str) noexcept -> BaseString& {
    if (&str == this) {
      return *this;
    }

    clear();
    A::operator=(cds::move(str));
    transfer(cds::move(str));
    return *this;
  }

  template <
      typename Convertible, typename D = RemoveCVRef<Convertible>, EnableIf<And<
          Not<IsSame<D, BaseString>>, Not<IsIntegral<D>>, Not<IsFloating<D>>
      >> = 0
  > CDS_ATTR(constexpr(20)) auto operator=(Convertible&& str) CDS_ATTR(noexcept(false)) -> BaseString& {
    using Ab = StringAbstract<>;
    copy(Ab::data(cds::forward<Convertible>(str)), Ab::length(cds::forward<Convertible>(str)));
    return *this;
  }

  CDS_ATTR(constexpr(20)) auto operator=(bool value) noexcept -> BaseString& {
    copy(value ? "true" : "false", value ? 4 : 5);
    return *this;
  }

  CDS_ATTR(constexpr(20)) auto operator=(Char value) noexcept -> BaseString& {
    copy(&value, minOf(value, 1));
    return *this;
  }

  template <typename N, EnableIf<IsIntegral<N>> = 0>
  CDS_ATTR(constexpr(20)) auto operator=(N value) noexcept -> BaseString& {
    auto const len = U::intLength(value, 10);
    reinit(len);
    *U::writeInt(value, len, data()) = STraits::nullChar;
    return *this;
  }

  template <typename FP, EnableIf<IsFloating<FP>> = 0>
  CDS_ATTR(constexpr(20)) auto operator=(FP value) noexcept -> BaseString& {
    auto const len = U::floatingLength(value);
    reinit(len);
    *U::writeFloating(value, len, data()) = STraits::nullChar;
    return *this;
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto data() const noexcept -> C const* {
    return sh() ? _sbo.buf : _nrm.buf;
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto data() noexcept -> C* {
    return sh() ? _sbo.buf : _nrm.buf;
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto length() const noexcept -> Size {
    return sh() ? _sbo.len : _nrm.len;
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto size() const noexcept -> Size {
    return sh() ? _sbo.len : _nrm.len;
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto capacity() const noexcept -> Size {
    return cap() - 1;
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto empty() const noexcept -> bool {
    return size() == 0u;
  }

  CDS_ATTR(3(nodiscard, implicit, constexpr(11))) operator bool() const noexcept {
    return !empty();
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto begin() noexcept -> Iterator {
    return Iterator(data());
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto end() noexcept -> Iterator {
    return Iterator(data() + size());
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto begin() const noexcept -> ConstIterator {
    return ConstIterator(data());
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto end() const noexcept -> ConstIterator {
    return ConstIterator(data() + size());
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto cbegin() const noexcept -> ConstIterator {
    return ConstIterator(data());
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto cend() const noexcept -> ConstIterator {
    return ConstIterator(data() + length());
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto rbegin() noexcept -> ReverseIterator {
    return ReverseIterator(data() + length() - 1);
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto rend() noexcept -> ReverseIterator {
    return ReverseIterator(data() - 1);
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto rbegin() const noexcept -> ConstReverseIterator {
    return ConstReverseIterator(data() + length() - 1);
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto rend() const noexcept -> ConstReverseIterator {
    return ConstReverseIterator(data() - 1);
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto crbegin() const noexcept -> ConstReverseIterator {
    return ConstReverseIterator(data() + length() - 1);
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto crend() const noexcept -> ConstReverseIterator {
    return ConstReverseIterator(data() - 1);
  }

  template <typename N, EnableIf<IsIntegral<N>> = 0>
  CDS_ATTR(2(nodiscard, constexpr(11))) auto operator[](N idx) const noexcept -> Value {
    return *(data() + idx);
  }

  template <typename N, EnableIf<IsIntegral<N>> = 0>
  CDS_ATTR(2(nodiscard, constexpr(14))) auto operator[](N idx) noexcept -> Value& {
    return *(data() + idx);
  }

  template <typename N, EnableIf<IsIntegral<N>> = 0>
  CDS_ATTR(2(nodiscard, constexpr(11))) auto at(N idx) const noexcept -> Value {
    return *(data() + idx);
  }

  template <typename N, EnableIf<IsIntegral<N>> = 0>
  CDS_ATTR(2(nodiscard, constexpr(14))) auto at(N idx) noexcept -> Value& {
    return *(data() + idx);
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto front() const noexcept -> Value {
    return *data();
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto back() const noexcept -> Value {
    return *(data() + length() - 1u);
  }

  CDS_ATTR(2(nodiscard, constexpr(14))) auto front() noexcept -> Value& {
    return *data();
  }

  CDS_ATTR(2(nodiscard, constexpr(14))) auto back() noexcept -> Value& {
    return *(data() + length() - 1u);
  }

  template <typename N, EnableIf<IsIntegral<N>> = 0>
  CDS_ATTR(2(nodiscard, constexpr(11))) auto sub(N from) const noexcept -> View {
    return sub(from, size());
  }

  template <typename N, EnableIf<IsIntegral<N>> = 0>
  CDS_ATTR(2(nodiscard, constexpr(11))) auto operator()(N from) const noexcept -> View {
    return sub(from, size());
  }

  template <typename N1, typename N2, EnableIf<All<IsIntegral, N1, N2>> = 0>
  CDS_ATTR(2(nodiscard, constexpr(11))) auto operator()(N1 from, N2 until) const noexcept -> View {
    return sub(from, until);
  }

  template <typename N1, typename N2, EnableIf<All<IsIntegral, N1, N2>> = 0>
  CDS_ATTR(2(nodiscard, constexpr(14))) auto sub(N1 from, N2 until) const noexcept -> View {
    auto const sUntil = static_cast<Size>(until);
    auto const sFrom = static_cast<Size>(from);

    if (sFrom >= sUntil) {
      return {};
    }

    return {data() + sFrom, sUntil - sFrom};
  }

  template <typename N> CDS_ATTR(2(nodiscard, constexpr(14))) auto contains(N&& needle) const
      CDS_ATTR(noexcept(noexcept(findFirst(cds::forward<N>(needle))))) -> bool {
    return findFirst(cds::forward<N>(needle)) != npos;
  }

  template <typename N, typename S, EnableIf<Not<IsAllocatorOrAllocatorSet<S>>> = 0>
  CDS_ATTR(2(nodiscard, constexpr(14))) auto contains(
      N&& needle, S&& selector
  ) const CDS_ATTR(noexcept(noexcept(findFirst(cds::forward<N>(needle), cds::forward<S>(selector))))) -> bool {
    return findFirst(cds::forward<N>(needle), cds::forward<S>(selector)) != npos;
  }

  template <typename N, typename CA, EnableIf<IsAllocatorOrAllocatorSet<CA>> = 0>
  CDS_ATTR(2(nodiscard, constexpr(14))) auto contains(N&& needle, CA&& alloc) const
      CDS_ATTR(noexcept(noexcept(findFirst(cds::forward<N>(needle), cds::forward<CA>(alloc))))) -> bool {
    return findFirst(cds::forward<N>(needle), cds::forward<CA>(alloc)) != npos;
  }

  template <typename N, typename S, typename CA> CDS_ATTR(2(nodiscard, constexpr(14))) auto contains(
      N&& needle, S&& selector, CA&& alloc
  ) const CDS_ATTR(noexcept(noexcept(
      findFirst(cds::forward<N>(needle), cds::forward<S>(selector), cds::forward<CA>(alloc))
  ))) -> bool {
    return findFirst(cds::forward<N>(needle), cds::forward<S>(selector), cds::forward<CA>(alloc)) != npos;
  }

  template <typename N> CDS_ATTR(2(nodiscard, constexpr(14))) auto startsWith(N&& needle) const noexcept -> bool {
    return U::startsWith(data(), size(), cds::forward<N>(needle));
  }

  template <typename N> CDS_ATTR(2(nodiscard, constexpr(14))) auto endsWith(N&& needle) const noexcept -> bool {
    return U::endsWith(data(), size(), cds::forward<N>(needle));
  }

  template <typename FC, typename FU, typename FA>
  friend auto operator<<(typename BaseString<FC, FU, FA>::OStream& out, BaseString<FC, FU, FA> const& obj)
      CDS_ATTR(noexcept(noexcept(out.write(obj.data(), obj.length())))) -> typename BaseString<FC, FU, FA>::OStream&;

  template <typename S, typename T = SplitAllocationTraits<S>, EnableIf<Not<typename T::Required>> = 0>
  CDS_ATTR(2(nodiscard, constexpr(14))) auto split(S&& separator) const&
      CDS_ATTR(noexcept(noexcept(impl::split(lvalue<BaseString const>(), cds::forward<S>(separator), 0))))
      -> decltype(impl::split(lvalue<BaseString const>(), cds::forward<S>(separator), 0)) {
    return impl::split(*this, cds::forward<S>(separator), limits::sizeMax);
  }

  template <typename S, typename T = SplitAllocationTraits<S>, EnableIf<Not<typename T::Required>> = 0>
  CDS_ATTR(2(nodiscard, constexpr(14))) auto split(S&& separator) const&&
      CDS_ATTR(noexcept(noexcept(impl::split(rvalue<BaseString const>(), cds::forward<S>(separator), 0))))
      -> decltype(impl::split(rvalue<BaseString const>(), cds::forward<S>(separator), 0)) {
    return impl::split(cds::move(*this), cds::forward<S>(separator), limits::sizeMax);
  }

  template <typename S, typename T = SplitAllocationTraits<S>, EnableIf<Not<typename T::Required>> = 0>
  CDS_ATTR(2(nodiscard, constexpr(14))) auto split(S&& separator, Size limit) const& CDS_ATTR(noexcept(noexcept(
      impl::split(lvalue<BaseString const>(), cds::forward<S>(separator), limit)
  ))) -> decltype(impl::split(lvalue<BaseString const>(), cds::forward<S>(separator), limit)) {
    return impl::split(*this, cds::forward<S>(separator), limit);
  }

  template <typename S, typename T = SplitAllocationTraits<S>, EnableIf<Not<typename T::Required>> = 0>
  CDS_ATTR(2(nodiscard, constexpr(14))) auto split(S&& separator, Size limit) const&& CDS_ATTR(noexcept(noexcept(
      impl::split(rvalue<BaseString const>(), cds::forward<S>(separator), limit)
  ))) -> decltype(impl::split(rvalue<BaseString const>(), cds::forward<S>(separator), limit)) {
    return impl::split(cds::move(*this), cds::forward<S>(separator), limit);
  }

  template <
      typename S, typename T = SplitAllocationTraits<S>, typename SA = typename T::Alloc,
      EnableIf<And<typename T::Required, IsAllocatorOrAllocatorSet<RemoveCVRef<SA>>>> = 0
  > CDS_ATTR(2(nodiscard, constexpr(20))) auto split(S&& separator, SA&& alloc = SA()) const& CDS_ATTR(noexcept(
      noexcept(impl::split(lvalue<BaseString const>(), cds::forward<S>(separator), 0, cds::forward<SA>(alloc)))
  )) -> decltype(impl::split(lvalue<BaseString const>(), cds::forward<S>(separator), 0, cds::forward<SA>(alloc))) {
    return impl::split(*this, cds::forward<S>(separator), limits::sizeMax, cds::forward<SA>(alloc));
  }

  template <
      typename S, typename T = SplitAllocationTraits<S>, typename SA = typename T::Alloc,
      EnableIf<And<typename T::Required, IsAllocatorOrAllocatorSet<RemoveCVRef<SA>>>> = 0
  > CDS_ATTR(2(nodiscard, constexpr(20))) auto split(S&& separator, SA&& alloc = SA()) const&& CDS_ATTR(noexcept(
      noexcept(impl::split(rvalue<BaseString const>(), cds::forward<S>(separator), 0, cds::forward<SA>(alloc)))
  )) -> decltype(impl::split(rvalue<BaseString const>(), cds::forward<S>(separator), 0, cds::forward<SA>(alloc))) {
    return impl::split(cds::move(*this), cds::forward<S>(separator), limits::sizeMax, cds::forward<SA>(alloc));
  }

  template <
      typename S, typename T = SplitAllocationTraits<S>, typename SA = typename T::Alloc,
      EnableIf<And<typename T::Required, IsAllocatorOrAllocatorSet<RemoveCVRef<SA>>>> = 0
  > CDS_ATTR(2(nodiscard, constexpr(20))) auto split(S&& separator, Size limit, SA&& alloc = SA()) const&
      CDS_ATTR(noexcept(noexcept(
          impl::split(lvalue<BaseString const>(), cds::forward<S>(separator), limit, cds::forward<SA>(alloc))
      ))) ->
      decltype(impl::split(lvalue<BaseString const>(), cds::forward<S>(separator), limit, cds::forward<SA>(alloc))) {
    return impl::split(*this, cds::forward<S>(separator), limit, cds::forward<SA>(alloc));
  }

  template <
      typename S, typename T = SplitAllocationTraits<S>, typename SA = typename T::Alloc,
      EnableIf<And<typename T::Required, IsAllocatorOrAllocatorSet<RemoveCVRef<SA>>>> = 0
  > CDS_ATTR(2(nodiscard, constexpr(20))) auto split(S&& separator, Size limit, SA&& alloc = SA()) const&&
      CDS_ATTR(noexcept(noexcept(
          impl::split(rvalue<BaseString const>(), cds::forward<S>(separator), limit, cds::forward<SA>(alloc))
      ))) ->
      decltype(impl::split(rvalue<BaseString const>(), cds::forward<S>(separator), limit, cds::forward<SA>(alloc))) {
    return impl::split(cds::move(*this), cds::forward<S>(separator), limit, cds::forward<SA>(alloc));
  }

  CDS_ATTR(constexpr(20)) auto resize(Size size, Char character = STraits::nullChar) CDS_ATTR(noexcept(false)) -> void {
    if (capacity() == size) {
      return;
    }

    if (sh() && sh(size)) {
      if (_sbo.len < size) {
        *impl::fill(end(), begin() + size, character) = STraits::nullChar;
      }
      _sbo.len = size;
      return;
    }

    if (sh()) {
      auto const newCap = maxOf(size + 1, minCap);
      auto const newBuf = A::allocate(newCap);
      *impl::fill(impl::copy(begin(), end(), newBuf), newBuf + size, character) = STraits::nullChar;
      _nrm.sbo = false;
      _nrm.len = size;
      _nrm.cap = newCap;
      _nrm.buf = newBuf;
      return;
    }

    auto oldBuf = _nrm.buf;
    auto oldLen = _nrm.len;
    auto oldCap = _nrm.cap;

    if (sh(size)) {
      sboInit(size);
    } else {
      _nrm.cap = maxOf(size + 1, minCap);
      _nrm.len = size;
      _nrm.buf = A::allocate(_nrm.cap);
      _nrm.sbo = false;
    }

    auto cEnd = impl::copy(oldBuf, oldBuf + minOf(oldLen, size), begin());
    A::deallocate(oldBuf, oldCap);
    if (cEnd != end()) {
      cEnd = impl::fill(cEnd, end(), character);
    }
    *cEnd = STraits::nullChar;
  }

  CDS_ATTR(constexpr(20)) auto reserve(Size size) CDS_ATTR(noexcept(false)) -> void {
    if (size <= capacity()) {
      return;
    }

    auto const newCap = maxOf(minCap, size + 1);
    auto const newBuf = A::allocate(newCap);
    auto const oldLen = length();
    *impl::copy(begin(), end(), newBuf) = STraits::nullChar;
    if (!sh()) {
      A::deallocate(_nrm.buf, _nrm.cap);
    }
    _nrm.buf = newBuf;
    _nrm.cap = newCap;
    _nrm.len = oldLen;
    _nrm.sbo = false;
  }

  CDS_ATTR(constexpr(20)) auto shrink(Size size = 0u) CDS_ATTR(noexcept(false)) -> void {
    if (size >= capacity() || sh()) {
      return;
    }

    auto const buf = data();
    auto const cCap = cap();
    init(size);
    *impl::copy(buf, buf + size, begin()) = STraits::nullChar;
    A::deallocate(buf, cCap);
  }

  CDS_ATTR(constexpr(20)) auto clear() noexcept -> void {
    if (!sh()) {
      A::deallocate(_nrm.buf, _nrm.cap);
    }

    sboInit();
  }

  template <typename Str, typename D = RemoveCVRef<Str>, EnableIf<And<Not<IsIntegral<D>>, Not<IsFloating<D>>>> = 0>
  auto operator+=(Str&& string) CDS_ATTR(noexcept(false)) -> BaseString& {
    using SA = StringAbstract<>;
    return append(SA::data(cds::forward<Str>(string)), SA::length(cds::forward<Str>(string)));
  }

  CDS_ATTR(constexpr(20)) auto operator+=(Char const value) CDS_ATTR(noexcept(false)) -> BaseString& {
    return append(&value, 1);
  }

  CDS_ATTR(constexpr(20)) auto operator+=(bool value) CDS_ATTR(noexcept(false)) -> BaseString& {
    return append(value ? "true" : "false", value ? 4 : 5);
  }

  template <typename N, EnableIf<IsIntegral<N>> = 0>
  CDS_ATTR(constexpr(20)) auto operator+=(N value) CDS_ATTR(noexcept(false)) -> BaseString& {
    auto const len = U::intLength(value, 10);
    auto const reqLen = len + length();
    reserve(reqLen);
    *U::writeInt(value, len, data() + length()) = STraits::nullChar;
    if (sh()) {
      _sbo.len = reqLen;
    } else {
      _nrm.len = reqLen;
    }
    return *this;
  }

  template <typename F, EnableIf<IsFloating<F>> = 0>
  CDS_ATTR(constexpr(20)) auto operator+=(F value) CDS_ATTR(noexcept(false)) -> BaseString& {
    auto const len = U::floatingLength(value);
    auto const reqLen = len + length();
    reserve(reqLen);
    *U::writeFloating(value, len, data() + length()) = STraits::nullChar;
    if (sh()) {
      _sbo.len = reqLen;
    } else {
      _nrm.len = reqLen;
    }
    return *this;
  }

  template <
      typename FC, typename FU, typename FA, typename Str, typename D,
      EnableIf<And<Not<IsIntegral<D>>, Not<IsFloating<D>>>>
  > CDS_ATTR(constexpr(20)) friend
  auto operator+(BaseString<FC, FU, FA> const& lhs, Str&& rhs) CDS_ATTR(noexcept(false)) -> BaseString<FC, FU, FA>;

  template <
      typename FC, typename FU, typename FA, typename Str, typename D,
      EnableIf<And<Not<IsIntegral<D>>, Not<IsFloating<D>>>>
  > CDS_ATTR(constexpr(20)) friend
  auto operator+(Str&& lhs, BaseString<FC, FU, FA> const& rhs) CDS_ATTR(noexcept(false)) -> BaseString<FC, FU, FA>;

  template <typename FC, typename FU, typename FA, typename Str> CDS_ATTR(constexpr(20)) friend
  auto operator+(BaseString<FC, FU, FA>&& lhs, Str&& rhs) CDS_ATTR(noexcept(false)) -> BaseString<FC, FU, FA>;

  template <typename FC, typename FU, typename FA> CDS_ATTR(constexpr(20)) friend
  auto operator+(BaseString<FC, FU, FA> const& lhs, Char rhs) CDS_ATTR(noexcept(false)) -> BaseString<FC, FU, FA>;

  template <typename FC, typename FU, typename FA> CDS_ATTR(constexpr(20)) friend
  auto operator+(Char lhs, BaseString<FC, FU, FA> const& rhs) CDS_ATTR(noexcept(false)) -> BaseString<FC, FU, FA>;

  template <typename FC, typename FU, typename FA> CDS_ATTR(constexpr(20)) friend
  auto operator+(BaseString<FC, FU, FA>&& lhs, Char rhs) CDS_ATTR(noexcept(false)) -> BaseString<FC, FU, FA>;

  template <typename FC, typename FU, typename FA> CDS_ATTR(constexpr(20)) friend
  auto operator+(BaseString<FC, FU, FA> const& lhs, bool rhs) CDS_ATTR(noexcept(false)) -> BaseString<FC, FU, FA>;

  template <typename FC, typename FU, typename FA> CDS_ATTR(constexpr(20)) friend
  auto operator+(bool lhs, BaseString<FC, FU, FA> const& rhs) CDS_ATTR(noexcept(false)) -> BaseString<FC, FU, FA>;

  template <typename FC, typename FU, typename FA> CDS_ATTR(constexpr(20)) friend
  auto operator+(BaseString<FC, FU, FA>&& lhs, bool rhs) CDS_ATTR(noexcept(false)) -> BaseString<FC, FU, FA>;

  template <typename FC, typename FU, typename FA, typename N, EnableIf<IsIntegral<N>>> CDS_ATTR(constexpr(20)) friend
  auto operator+(BaseString<FC, FU, FA> const& lhs, N rhs) CDS_ATTR(noexcept(false)) -> BaseString<FC, FU, FA>;

  template <typename FC, typename FU, typename FA, typename N, EnableIf<IsIntegral<N>>> CDS_ATTR(constexpr(20)) friend
  auto operator+(N lhs, BaseString<FC, FU, FA> const& rhs) CDS_ATTR(noexcept(false)) -> BaseString<FC, FU, FA>;

  template <typename FC, typename FU, typename FA, typename N, EnableIf<IsIntegral<N>>> CDS_ATTR(constexpr(20)) friend
  auto operator+(BaseString<FC, FU, FA>&& lhs, N rhs) CDS_ATTR(noexcept(false)) -> BaseString<FC, FU, FA>;

  template <typename FC, typename FU, typename FA, typename F, EnableIf<IsFloating<F>>> CDS_ATTR(constexpr(20)) friend
  auto operator+(BaseString<FC, FU, FA> const& lhs, F rhs) CDS_ATTR(noexcept(false)) -> BaseString<FC, FU, FA>;

  template <typename FC, typename FU, typename FA, typename F, EnableIf<IsFloating<F>>> CDS_ATTR(constexpr(20)) friend
  auto operator+(F lhs, BaseString<FC, FU, FA> const& rhs) CDS_ATTR(noexcept(false)) -> BaseString<FC, FU, FA>;

  template <typename FC, typename FU, typename FA, typename F, EnableIf<IsFloating<F>>> CDS_ATTR(constexpr(20)) friend
  auto operator+(BaseString<FC, FU, FA>&& lhs, F rhs) CDS_ATTR(noexcept(false)) -> BaseString<FC, FU, FA>;

  CDS_ATTR(2(nodiscard, constexpr(14))) auto ltrim(Char value) const noexcept -> View;
  CDS_ATTR(2(nodiscard, constexpr(14))) auto ltrim(View const& view = STraits::whitespace) const noexcept -> View;
  template <typename I> CDS_ATTR(2(nodiscard, constexpr(14))) auto ltrim(I&& iterable) const noexcept -> View;

  CDS_ATTR(2(nodiscard, constexpr(14))) auto rtrim(Char value) const noexcept -> View;
  CDS_ATTR(2(nodiscard, constexpr(14))) auto rtrim(View const& view = STraits::whitespace) const noexcept -> View;
  template <typename I> CDS_ATTR(2(nodiscard, constexpr(14))) auto rtrim(I&& iterable) const noexcept -> View;

  CDS_ATTR(2(nodiscard, constexpr(14))) auto trim(Char value) const noexcept -> View;
  CDS_ATTR(2(nodiscard, constexpr(14))) auto trim(View const& view = STraits::whitespace) const noexcept -> View;
  template <typename I> CDS_ATTR(2(nodiscard, constexpr(14))) auto trim(I&& iterable) const noexcept -> View;

  CDS_ATTR(2(nodiscard, constexpr(20))) auto ljust(Size size, Char with = ' ') const& noexcept -> BaseString;
  CDS_ATTR(2(nodiscard, constexpr(20))) auto rjust(Size size, Char with = ' ') const& noexcept -> BaseString;
  CDS_ATTR(2(nodiscard, constexpr(20))) auto ljust(Size size, Char with = ' ')&& noexcept -> BaseString;
  CDS_ATTR(2(nodiscard, constexpr(20))) auto rjust(Size size, Char with = ' ')&& noexcept -> BaseString;
  CDS_ATTR(2(nodiscard, constexpr(20))) auto ljust(Size size, Char with = ' ') const&& noexcept -> BaseString;
  CDS_ATTR(2(nodiscard, constexpr(20))) auto rjust(Size size, Char with = ' ') const&& noexcept -> BaseString;

  template <typename N1, typename N2> CDS_ATTR(2(nodiscard, constexpr(20)))
  auto replace(N1 from, N2 to, View const& repl) const& CDS_ATTR(noexcept(false)) -> BaseString;

  template <typename N1, typename N2> CDS_ATTR(2(nodiscard, constexpr(20)))
  auto replace(N1 from, N2 to, View const& repl)&& CDS_ATTR(noexcept(false)) -> BaseString;

  template <typename N1, typename N2> CDS_ATTR(2(nodiscard, constexpr(20)))
  auto replace(N1 from, N2 to, View const& repl) const&& CDS_ATTR(noexcept(false)) -> BaseString;

  template <typename... Strings>  CDS_ATTR(2(nodiscard, constexpr(20)))
  static auto join(View const& separator, Strings&&... strings) CDS_ATTR(noexcept(false)) -> BaseString;

private:
  CDS_ATTR(constexpr(14)) auto init(Size const len) CDS_ATTR(noexcept(false)) -> void {
    if (sh(len)) {
      sboInit(len);
    } else {
      nrmInit(len);
    }
  }

  CDS_ATTR(constexpr(14)) auto sboInit(Size const len = 0) noexcept -> void {
    _sbo.sbo = true;
    _sbo.len = static_cast<U8>(len);
    _sbo.initialize();
  }

  CDS_ATTR(constexpr(14)) auto nrmInit(Size const len) CDS_ATTR(noexcept(false)) -> void {
    nrmInit(len, len + 1u);
  }

  CDS_ATTR(constexpr(14)) auto nrmInit(Size const len, Size const cap) CDS_ATTR(noexcept(false)) -> void {
    _nrm.sbo = false;
    _nrm.len = len;
    _nrm.cap = maxOf(cap, minCap);
    _nrm.buf = A::allocate(_nrm.cap);
  }

  CDS_ATTR(constexpr(14)) auto reinit(Size const len) CDS_ATTR(noexcept(false)) -> void {
    if (sh() && sh(len)) {
      sboReinit(len);
    } else {
      nrmReinit(len);
    }
  }

  CDS_ATTR(constexpr(14)) auto sboReinit(Size const len = 0) noexcept -> void {
    _sbo.len = static_cast<U8>(len);
  }

  CDS_ATTR(constexpr(14)) auto nrmReinit(Size const len) CDS_ATTR(noexcept(false)) -> void {
    nrmReinit(len, len + 1u);
  }

  CDS_ATTR(constexpr(14)) auto nrmReinit(Size const len, Size const newCap) CDS_ATTR(noexcept(false)) -> void {
    if (len >= cap()) {
      clear();
      _nrm.cap = maxOf(newCap, minCap);
      _nrm.buf = A::allocate(_nrm.cap);
    }
    _nrm.sbo = false;
    _nrm.len = len;
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto sh() const noexcept -> bool {
    return _sbo.sbo;
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) static auto sh(Size const length) noexcept -> bool {
    return length < (sizeof(sbo::StringSboData<C>::buf) / sizeof(C));
  }

  CDS_ATTR(constexpr(20)) auto copyUninitialized(Address address, Size const length) noexcept -> void {
    init(length);
    *impl::copy(address, address + length, begin()) = STraits::nullChar;
  }

  CDS_ATTR(constexpr(20)) auto copy(Address address, Size const length) noexcept -> void {
    if (sh() && sh(length)) {
      _sbo.len = static_cast<U8>(length);
    } else {
      if (length >= cap()) {
        clear();
        _nrm.cap = maxOf(minCap, length + 1u);
        _nrm.buf = A::allocate(_nrm.cap);
      }
      _nrm.len = length;
      _nrm.sbo = false;
    }
    *impl::copy(address, address + length, begin()) = STraits::nullChar;
  }

  CDS_ATTR(constexpr(20)) auto transfer(BaseString&& str) noexcept -> void {
    sbo::StringData<C>::operator=(cds::move(str));
    str._sbo.sbo = true;
    str._sbo.len = 0u;
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto cap() const noexcept -> Size {
    return sh() ? sizeof(sbo::StringSboData<C>::buf) / sizeof(C) : _nrm.cap;
  }

  auto append(Char const* const buf, Size const len) CDS_ATTR(noexcept(false)) -> BaseString& {
    auto const reqLen = len + length();
    if (reqLen > capacity()) {
      auto const newCap = maxOf(reqLen + 1, minCap, capacity() * 2);
      auto const newBuf = A::allocate(newCap);
      auto const oldLen = length();
      *impl::copy(buf, buf + len, impl::copy(begin(), end(), newBuf)) = STraits::nullChar;
      if (!sh()) {
        A::deallocate(_nrm.buf, _nrm.cap);
      }
      _nrm.len = reqLen;
      _nrm.buf = newBuf;
      _nrm.cap = newCap;
      _nrm.sbo = false;
      return *this;
    }
    *impl::copy(buf, buf + len, end()) = STraits::nullChar;
    if (sh()) {
      _sbo.len = reqLen;
    } else {
      _nrm.len = reqLen;
    }
    return *this;
  }

  static Size constexpr minCap = 32u;
};

template <typename C, typename U, typename A> Idx const BaseString<C, U, A>::npos = -1;
template <typename C, typename U, typename A> Idx const BaseString<C, U, A>::invalidIndex = npos;

template <typename FC, typename FU, typename FA>
auto operator<<(typename BaseString<FC, FU, FA>::OStream& out, BaseString<FC, FU, FA> const& obj)
    CDS_ATTR(noexcept(noexcept(out.write(obj.data(), obj.length())))) -> typename BaseString<FC, FU, FA>::OStream& {
  out.write(obj.data(), obj.length());
  return out;
}

template <
    typename FC, typename FU, typename FA, typename Str, typename D = RemoveCVRef<Str>,
    EnableIf<And<Not<IsIntegral<D>>, Not<IsFloating<D>>>> = 0
> CDS_ATTR(constexpr(20))
auto operator+(BaseString<FC, FU, FA> const& lhs, Str&& rhs) CDS_ATTR(noexcept(false)) -> BaseString<FC, FU, FA> {
  using SA = StringAbstract<>;
  BaseString<FC, FU, FA> res;
  auto const reqLen = lhs.size() + SA::length(cds::forward<Str>(rhs));
  res.reserve(reqLen);
}

//template <
//    typename FC, typename FU, typename FA, typename Str, typename D,
//    EnableIf<And<Not<IsIntegral<D>>, Not<IsFloating<D>>>>
//    > CDS_ATTR(constexpr(20)) friend
//    auto operator+(Str&& lhs, BaseString<FC, FU, FA> const& rhs) CDS_ATTR(noexcept(false)) -> BaseString<FC, FU, FA>;
//
//template <typename FC, typename FU, typename FA, typename Str> CDS_ATTR(constexpr(20)) friend
//    auto operator+(BaseString<FC, FU, FA>&& lhs, Str&& rhs) CDS_ATTR(noexcept(false)) -> BaseString<FC, FU, FA>;
//
//template <typename FC, typename FU, typename FA> CDS_ATTR(constexpr(20)) friend
//    auto operator+(BaseString<FC, FU, FA> const& lhs, Char rhs) CDS_ATTR(noexcept(false)) -> BaseString<FC, FU, FA>;
//
//template <typename FC, typename FU, typename FA> CDS_ATTR(constexpr(20)) friend
//    auto operator+(Char lhs, BaseString<FC, FU, FA> const& rhs) CDS_ATTR(noexcept(false)) -> BaseString<FC, FU, FA>;
//
//template <typename FC, typename FU, typename FA> CDS_ATTR(constexpr(20)) friend
//    auto operator+(BaseString<FC, FU, FA>&& lhs, Char rhs) CDS_ATTR(noexcept(false)) -> BaseString<FC, FU, FA>;
//
//template <typename FC, typename FU, typename FA> CDS_ATTR(constexpr(20)) friend
//    auto operator+(BaseString<FC, FU, FA> const& lhs, bool rhs) CDS_ATTR(noexcept(false)) -> BaseString<FC, FU, FA>;
//
//template <typename FC, typename FU, typename FA> CDS_ATTR(constexpr(20)) friend
//    auto operator+(bool lhs, BaseString<FC, FU, FA> const& rhs) CDS_ATTR(noexcept(false)) -> BaseString<FC, FU, FA>;
//
//template <typename FC, typename FU, typename FA> CDS_ATTR(constexpr(20)) friend
//    auto operator+(BaseString<FC, FU, FA>&& lhs, bool rhs) CDS_ATTR(noexcept(false)) -> BaseString<FC, FU, FA>;
//
//template <typename FC, typename FU, typename FA, typename N, EnableIf<IsIntegral<N>>> CDS_ATTR(constexpr(20)) friend
//    auto operator+(BaseString<FC, FU, FA> const& lhs, N rhs) CDS_ATTR(noexcept(false)) -> BaseString<FC, FU, FA>;
//
//template <typename FC, typename FU, typename FA, typename N, EnableIf<IsIntegral<N>>> CDS_ATTR(constexpr(20)) friend
//    auto operator+(N lhs, BaseString<FC, FU, FA> const& rhs) CDS_ATTR(noexcept(false)) -> BaseString<FC, FU, FA>;
//
//template <typename FC, typename FU, typename FA, typename N, EnableIf<IsIntegral<N>>> CDS_ATTR(constexpr(20)) friend
//    auto operator+(BaseString<FC, FU, FA>&& lhs, N rhs) CDS_ATTR(noexcept(false)) -> BaseString<FC, FU, FA>;
//
//template <typename FC, typename FU, typename FA, typename F, EnableIf<IsFloating<F>>> CDS_ATTR(constexpr(20)) friend
//    auto operator+(BaseString<FC, FU, FA> const& lhs, F rhs) CDS_ATTR(noexcept(false)) -> BaseString<FC, FU, FA>;
//
//template <typename FC, typename FU, typename FA, typename F, EnableIf<IsFloating<F>>> CDS_ATTR(constexpr(20)) friend
//    auto operator+(F lhs, BaseString<FC, FU, FA> const& rhs) CDS_ATTR(noexcept(false)) -> BaseString<FC, FU, FA>;
//
//template <typename FC, typename FU, typename FA, typename F, EnableIf<IsFloating<F>>> CDS_ATTR(constexpr(20)) friend
//    auto operator+(BaseString<FC, FU, FA>&& lhs, F rhs) CDS_ATTR(noexcept(false)) -> BaseString<FC, FU, FA>;
} // namespace impl

namespace literals {
CDS_ATTR(2(nodiscard, consteval(20, inline)))
auto operator ""_s(char const* string, std::size_t length) noexcept -> impl::BaseString<char> {
  return {string, length};
}

CDS_ATTR(2(nodiscard, consteval(20, inline)))
auto operator ""_s(wchar_t const* string, std::size_t length) noexcept -> impl::BaseString<wchar_t> {
  return {string, length};
}
}
} // namespace cds

#include "../../common/StringConversion.hpp"

#endif // CDS_PRIMITIVE_STRING_BASE_HPP
