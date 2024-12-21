//
// Created by loghin on 12/8/23.
//

#ifndef CDS_PRIMITIVE_STRING_BASE_HPP
#define CDS_PRIMITIVE_STRING_BASE_HPP
#pragma once

#include <ostream>

#include <cds/meta/IterableTraits>

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

namespace cds {
namespace impl {
using meta::EnableIf;
using meta::Int;
using meta::IsIntegral;
using meta::IsFloating;
using meta::IsIterableOfThat;

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
  Size lenSbo;
};

template <typename C, typename = Int<sizeof(C)>> struct StringSboData {};
template <typename C> struct StringSboData<C, Int<1>> {
  C buf[sizeof(StringNonSboData<C>) - 1u];
  U8 lenSbo;

  using Size = Int<sizeof(StringNonSboData<C>) - 1u>;

  CDS_ATTR(constexpr(14)) auto initialize() noexcept -> void {
    impl::fill(buf, buf + (sizeof(StringNonSboData<C>) - 1), static_cast<C>(0));
  }
};

template <typename C> struct StringSboData<C, Int<2>> {
  C buf[sizeof(StringNonSboData<C>) / 2u - 1u];
  U8 pad[1u];
  U8 lenSbo;

  using Size = Int<sizeof(buf) / sizeof(buf[0])>;

  CDS_ATTR(constexpr(14)) auto initialize() noexcept -> void {
    impl::fill(buf, buf + (sizeof(StringNonSboData<C>) / 2 - 1), static_cast<C>(0));
    pad[0] = 0;
  }
};

template <typename C> struct StringSboData<C, Int<4>> {
#if CDS_ATTR(bitarch) == 64
  C buf[sizeof(StringNonSboData<C>) / 4u - 1u];
  U8 pad[3u];
  U8 lenSbo;

  using Size = Int<sizeof(buf) / sizeof(buf[0])>;

  CDS_ATTR(constexpr(14)) auto initialize() noexcept -> void {
    impl::fill(buf, buf + (sizeof(StringNonSboData<C>) / 4 - 1), static_cast<C>(0));
    impl::fill(pad, pad + 3u, static_cast<U8>(0));
  }
#elif CDS_ATTR(bitarch) == 32
  C buf[1u];
  U8 pad[7u];
  U8 lenSbo;

  using Size = Int<0>;

  CDS_ATTR(constexpr(14)) auto initialize() noexcept -> void {
    // does nothing
    // assert(false && "x86 wchar_t and char32_t is deactivated");
  }
#endif
};

template <typename C> struct StringData {
  union {
    StringNonSboData<C> _nrm;
    StringSboData<C> _sbo;
  };

  CDS_ATTR(constexpr(14)) StringData() noexcept {
    _sbo.buf[0] = StringTraits<C>::nullChar;
    _sbo.lenSbo = 1U; // 0 len, 1 sbo
  }

  CDS_ATTR(constexpr(11)) StringData(C* buf, Size c, Size l) noexcept : _nrm{buf, c, l} {}
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
        : cds::forward<I>(i) - cds::forward<IB>(b);
  }
};

namespace bindingsBS {
template <typename C, typename U, typename A> using Self = BaseString<C, U, A>;
template <typename C, typename U, typename A> using Traits = IterableTraits<Self<C, U, A>>;

using ContainsOpt = With<Value, Projector>;
template <typename C, typename U, typename A> struct CDS_ATTR(ebo) ContainsOf :
    ContainsOfStaticBinding<Self<C, U, A>, ContainsOpt> {};

using FindOpt = With<Value, Projector, Immutable, Mutable>;
template <typename C, typename U, typename A> struct CDS_ATTR(ebo) FindTr :
    FindStringTransformer<C, U, A> {};
template <typename C, typename U, typename A> struct CDS_ATTR(ebo) Find :
    FindStaticBinding<Self<C, U, A>, FindOpt, FindTr<C, U, A>, FindTr<C, U, A>> {};
template <typename C, typename U, typename A> struct CDS_ATTR(ebo) FindOf :
    FindOfStaticBinding<Self<C, U, A>, FindOpt, FindTr<C, U, A>, FindTr<C, U, A>> {};

using LoopOpt = With<Immutable, Mutable>;
template <typename C, typename U, typename A> struct CDS_ATTR(ebo) GenericLoop :
    GenericLoopBinding<Self<C, U, A>, LoopOpt> {};
} // namespace bindingsBS

template <typename C, typename U, typename A> class CDS_ATTR(ebo) BaseString :
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

  using Constants = meta::impl::StringTraitsPrivateConstants<C>;

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

#if CDS_ATTR(cpp20)
  CDS_ATTR(2(explicit, constexpr(20))) BaseString(A const& alloc = A{}) noexcept :
      A{alloc},
      sbo::StringData<C>{nullptr, 0U, 0U} {
    if (!inConstexpr()) {
      sboInit();
    }
  }
#else
  CDS_ATTR(explicit) BaseString(A const& alloc = A{}) noexcept : A{alloc}, sbo::StringData<C>{} {}
#endif

  CDS_ATTR(constexpr(20)) BaseString(Address data, Size const length, A const& alloc = A())
      CDS_ATTR(noexcept(false)) :
      A(alloc) {
    copyUninitialized(data, length);
  }

  CDS_ATTR(constexpr(20)) BaseString(BaseString const& str, A const& alloc = A{}) CDS_ATTR(noexcept(false)) :
      BaseString(str.data(), str.length(), alloc) {}

  CDS_ATTR(constexpr(20)) BaseString(BaseString&& str) noexcept : A(cds::move(str)) {
    transfer(cds::move(str));
  }

  template <
      typename Convertible, typename D = RemoveCVRef<Convertible>, EnableIf<And<
          Or<IsString<Convertible>, IsSame<Null, Convertible>>,
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
    if (length == 0) {
      init();
      return;
    }
    init(length);
    construct(impl::fillInitialize(data(), data() + length, fill), STraits::nullChar);
  }

  CDS_ATTR(2(implicit, constexpr(20))) BaseString(bool value, A const& alloc = A()) noexcept :
      BaseString(value ? Constants::_true : Constants::_false, value ? 4 : 5, alloc) {}

  CDS_ATTR(2(implicit, constexpr(20))) BaseString(Char character, A const& alloc = A()) noexcept :
      BaseString(&character, minOf(character, 1), alloc) {}

  template <typename N, EnableIf<IsIntegral<N>> = 0>
  CDS_ATTR(2(implicit, constexpr(20))) BaseString(N integral, A const& alloc = A()) noexcept : A(alloc) {
    auto const len = U::intLength(integral, 10);
    init(len);
#if CDS_ATTR(cpp20)
    if (inConstexpr()) {
      impl::fillInitialize(data(), data() + len + 1, STraits::nullChar);
    }
#endif
    *U::writeInt(integral, len, data()) = STraits::nullChar;
  }

  template <typename F, EnableIf<IsFloating<F>> = 0>
  CDS_ATTR(implicit) BaseString(F floating, A const& alloc = A()) noexcept :
      A(alloc) {
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
    copy(value ? Constants::_true : Constants::_false, value ? 4 : 5);
    return *this;
  }

  CDS_ATTR(constexpr(20)) auto operator=(Char value) noexcept -> BaseString& {
    copy(&value, minOf(value, 1));
    return *this;
  }

  template <typename N, EnableIf<IsIntegral<N>> = 0>
  CDS_ATTR(constexpr(20)) auto operator=(N value) noexcept -> BaseString& {
    auto const len = U::intLength(value, 10);
#if CDS_ATTR(cpp20)
    if (inConstexpr()) {
      auto const initialized = length();
      reinit(len);
      if (initialized < len) {
        impl::fillInitialize(data() + initialized, data() + len + 1, STraits::nullChar);
      }
    } else {
      reinit(len);
    }
#else
    reinit(len);
#endif
    *U::writeInt(value, len, data()) = STraits::nullChar;
    return *this;
  }

  template <typename FP, EnableIf<IsFloating<FP>> = 0> auto operator=(FP value) noexcept -> BaseString& {
    auto const len = U::floatingLength(value);
    reinit(len);
    *U::writeFloating(value, len, data()) = STraits::nullChar;
    return *this;
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto data() const noexcept -> C const* {
    return sh() ? _sbo.buf : _nrm.buf;
  }

  CDS_ATTR(2(nodiscard, constexpr(14))) auto data() noexcept -> C* {
    return sh() ? _sbo.buf : _nrm.buf;
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto length() const noexcept -> Size {
    return static_cast<Size>((sh() ? _sbo.lenSbo : _nrm.lenSbo) >> 1u);
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto size() const noexcept -> Size {
    return static_cast<Size>((sh() ? _sbo.lenSbo : _nrm.lenSbo) >> 1u);
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto capacity() const noexcept -> Size {
    return cap() == 0 ? 0 : cap() - 1;
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto empty() const noexcept -> bool {
    return size() == 0u;
  }

  CDS_ATTR(3(nodiscard, explicit, constexpr(11))) operator bool() const noexcept {
    return !empty();
  }

  CDS_ATTR(2(nodiscard, constexpr(14))) auto begin() noexcept -> Iterator {
    return Iterator(data());
  }

  CDS_ATTR(2(nodiscard, constexpr(14))) auto end() noexcept -> Iterator {
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

  CDS_ATTR(2(nodiscard, constexpr(14))) auto rbegin() noexcept -> ReverseIterator {
    return ReverseIterator(data() + length());
  }

  CDS_ATTR(2(nodiscard, constexpr(14))) auto rend() noexcept -> ReverseIterator {
    return ReverseIterator(data());
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto rbegin() const noexcept -> ConstReverseIterator {
    return ConstReverseIterator(data() + length());
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto rend() const noexcept -> ConstReverseIterator {
    return ConstReverseIterator(data());
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto crbegin() const noexcept -> ConstReverseIterator {
    return ConstReverseIterator(data() + length());
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto crend() const noexcept -> ConstReverseIterator {
    return ConstReverseIterator(data());
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
  CDS_ATTR(2(nodiscard, constexpr(14))) auto sub(N from) const noexcept -> View {
    return sub(from, size());
  }

  template <typename N, EnableIf<IsIntegral<N>> = 0>
  CDS_ATTR(2(nodiscard, constexpr(14))) auto operator()(N from) const noexcept -> View {
    return sub(from, size());
  }

  template <typename N1, typename N2, EnableIf<All<IsIntegral, N1, N2>> = 0>
  CDS_ATTR(2(nodiscard, constexpr(14))) auto operator()(N1 from, N2 until) const noexcept -> View {
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
      if (size == 0) {
        return;
      }
#if CDS_ATTR(cpp20)
      if (inConstexpr()) {
        construct(impl::fillInitialize(data() + length(), data() + size, character), STraits::nullChar);
        _nrm.lenSbo = size << 1u;
        return;
      }
#endif
      *impl::fill(end(), begin() + size, character) = STraits::nullChar;
      if (sh()) {
        _sbo.lenSbo = static_cast<U8>(size << 1u | 1u);
      } else {
        _nrm.lenSbo = size << 1u;
      }
      return;
    }

    if (sh() && sh(size)) {
      if (/* _sbo.lenSbo */ length() < size) {
        *impl::fill(end(), begin() + size, character) = STraits::nullChar;
      }
      _sbo.lenSbo = static_cast<U8>(size << 1u | 1u);
      return;
    }

    if (sh()) {
      auto const newCap = maxOf(size + 1, minCap);
      auto const newBuf = A::allocate(newCap);
      *impl::fill(impl::copy(begin(), end(), newBuf), newBuf + size, character) = STraits::nullChar;
      _nrm.lenSbo = size << 1u;
      _nrm.cap = newCap;
      _nrm.buf = newBuf;
      return;
    }

    auto oldBuf = _nrm.buf;
    auto oldLen = _nrm.lenSbo >> 1u;
    auto oldCap = _nrm.cap;

    if (sh(size)) {
      sboInit(size);
    } else {
      _nrm.cap = maxOf(size + 1, minCap);
      _nrm.lenSbo = size << 1u;
      _nrm.buf = A::allocate(_nrm.cap);
    }

#if CDS_ATTR(cpp20)
    if constexpr(inConstexpr()) {
      construct(
        impl::fillInitialize(
          impl::copyInitialize(oldBuf, oldBuf + minOf(oldLen, size), data()),
          data() + length(),
          character
        ),
        STraits::nullChar
      );
      if (oldBuf) {
        A::deallocate(oldBuf, oldCap);
      }
      return;
    }
#endif
    auto cEnd = impl::copy(oldBuf, oldBuf + minOf(oldLen, size), begin());
    A::deallocate(oldBuf, oldCap);
    if (cEnd != end()) {
#if CDS_ATTR(cpp20)
      if (inConstexpr()) {
        auto cEndAddr = data() + (cEnd - begin());
        construct(impl::fillInitialize(cEndAddr, data() + length(), character), STraits::nullChar);
        return;
      }
#endif
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
    construct(impl::copyInitialize(begin(), end(), newBuf), STraits::nullChar);
#if CDS_ATTR(cpp20)
    if (inConstexpr()) {
      if (_nrm.buf) {
        A::deallocate(_nrm.buf, _nrm.cap);
      }
    } else
#endif
    if (!sh()) {
      A::deallocate(_nrm.buf, _nrm.cap);
    }
    _nrm.buf = newBuf;
    _nrm.cap = newCap;
    _nrm.lenSbo = oldLen << 1u;
  }

  CDS_ATTR(constexpr(20)) auto shrink(Size size = 0u) CDS_ATTR(noexcept(false)) -> void {
    if (size >= capacity()) {
      return;
    }

    if (sh()) {
      if (size < length()) {
        _sbo.lenSbo = static_cast<U8>(size << 1u | 1u);
        *(begin() + size) = STraits::nullChar;
      }
      return;
    }

    auto const buf = data();
    auto const cCap = cap();
    auto const cLen = length();
    if (sh(size)) {
      _sbo.lenSbo = static_cast<U8>(minOf(cLen, size) << 1u | 1u);
    } else {
      _nrm.lenSbo = minOf(cLen, size) << 1u;
      _nrm.cap = maxOf(size + 1, minCap);
      _nrm.buf = A::allocate(_nrm.cap);
    }
#if CDS_ATTR(cpp20)
    if (inConstexpr()) {
      construct(impl::copyInitialize(buf, buf + size, data()), STraits::nullChar);
      if (buf) {
        A::deallocate(buf, cCap);
      }

      return;
    }
#endif
    *impl::copy(buf, buf + size, begin()) = STraits::nullChar;
    A::deallocate(buf, cCap);
  }

  CDS_ATTR(constexpr(20)) auto clear() noexcept -> void {
    if (!sh()) {
#if CDS_ATTR(cpp20)
      if (inConstexpr() && !data()) {
        init();
        return;
      }
#endif
      A::deallocate(_nrm.buf, _nrm.cap);
    }

    init();
  }

  template <typename Str, typename D = RemoveCVRef<Str>, EnableIf<And<Not<IsIntegral<D>>, Not<IsFloating<D>>>> = 0>
  CDS_ATTR(constexpr(20)) auto operator+=(Str&& string) CDS_ATTR(noexcept(false)) -> BaseString& {
    using SA = StringAbstract<>;
    auto const buf = SA::data(cds::forward<Str>(string));
    auto const len = SA::length(cds::forward<Str>(string));
    return append(buf, buf + len);
  }

  CDS_ATTR(constexpr(20)) auto operator+=(Char const value) CDS_ATTR(noexcept(false)) -> BaseString& {
    return append(&value, &value + 1);
  }

  CDS_ATTR(constexpr(20)) auto operator+=(bool value) CDS_ATTR(noexcept(false)) -> BaseString& {
    auto const* buf = value ? Constants::_true : Constants::_false;
    return append(buf, buf + (value ? 4 : 5));
  }

  template <typename N, EnableIf<IsIntegral<N>> = 0>
  CDS_ATTR(constexpr(20)) auto operator+=(N value) CDS_ATTR(noexcept(false)) -> BaseString& {
    auto const len = U::intLength(value, 10);
    auto const reqLen = len + length();
    reserve(reqLen);
#if CDS_ATTR(cpp20)
    if (inConstexpr()) {
      impl::fillInitialize(data() + length(), data() + length() + len + 1, STraits::nullChar);
    }
#endif
    *U::writeInt(value, len, data() + length()) = STraits::nullChar;
    if (sh()) {
      _sbo.lenSbo = static_cast<U8>(reqLen << 1u | 1u);
    } else {
      _nrm.lenSbo = reqLen << 1u;
    }
    return *this;
  }

  template <typename F, EnableIf<IsFloating<F>> = 0>
  auto operator+=(F value) CDS_ATTR(noexcept(false)) -> BaseString& {
    auto const len = U::floatingLength(value);
    auto const reqLen = len + length();
    reserve(reqLen);
    *U::writeFloating(value, len, data() + length()) = STraits::nullChar;
    if (sh()) {
      _sbo.lenSbo = static_cast<U8>(reqLen << 1u | 1u);
    } else {
      _nrm.lenSbo = reqLen << 1u;
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
      EnableIf<And<Not<IsIntegral<D>>, Not<IsFloating<D>>, Not<IsSame<D, BaseString<FC, FU, FA>>>>>
  > CDS_ATTR(constexpr(20)) friend
  auto operator+(Str&& lhs, BaseString<FC, FU, FA> const& rhs) CDS_ATTR(noexcept(false)) -> BaseString<FC, FU, FA>;

  template <
      typename FC, typename FU, typename FA, typename Str, typename D,
      EnableIf<And<Not<IsIntegral<D>>, Not<IsFloating<D>>>>
  > CDS_ATTR(constexpr(20)) friend
  auto operator+(BaseString<FC, FU, FA>&& lhs, Str&& rhs) CDS_ATTR(noexcept(false)) -> BaseString<FC, FU, FA>;

  template <typename FC, typename FU, typename FA> CDS_ATTR(constexpr(20)) friend
  auto operator+(BaseString<FC, FU, FA> const& lhs, FC rhs) CDS_ATTR(noexcept(false)) -> BaseString<FC, FU, FA>;

  template <typename FC, typename FU, typename FA> CDS_ATTR(constexpr(20)) friend
  auto operator+(FC lhs, BaseString<FC, FU, FA> const& rhs) CDS_ATTR(noexcept(false)) -> BaseString<FC, FU, FA>;

  template <typename FC, typename FU, typename FA> CDS_ATTR(constexpr(20)) friend
  auto operator+(BaseString<FC, FU, FA>&& lhs, FC rhs) CDS_ATTR(noexcept(false)) -> BaseString<FC, FU, FA>;

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

  template <typename FC, typename FU, typename FA, typename F, EnableIf<IsFloating<F>>> friend
  auto operator+(BaseString<FC, FU, FA> const& lhs, F rhs) CDS_ATTR(noexcept(false)) -> BaseString<FC, FU, FA>;

  template <typename FC, typename FU, typename FA, typename F, EnableIf<IsFloating<F>>> friend
  auto operator+(F lhs, BaseString<FC, FU, FA> const& rhs) CDS_ATTR(noexcept(false)) -> BaseString<FC, FU, FA>;

  template <typename FC, typename FU, typename FA, typename F, EnableIf<IsFloating<F>>> friend
  auto operator+(BaseString<FC, FU, FA>&& lhs, F rhs) CDS_ATTR(noexcept(false)) -> BaseString<FC, FU, FA>;

  CDS_ATTR(2(nodiscard, constexpr(14))) auto ltrim(Char value) const& noexcept -> View {
    auto d = data();
    auto l = length();
    for (; l > 0 && *d == value; ++d, --l) {
      // nothing, just advances start pointer and length
    }
    return View{d, l};
  }

  CDS_ATTR(2(nodiscard, constexpr(14))) auto ltrim(View const& view = STraits::whitespace) const& noexcept -> View {
    auto d = data();
    auto l = length();
    for (; l > 0 && view.contains(*d); ++d, --l) {
      // nothing, just advances start pointer and length
    }
    return View{d, l};
  }

  auto ltrim(Char value)&& noexcept -> void = delete;
  auto ltrim(View const& view = STraits::whitespace)&& noexcept -> void = delete;
  auto ltrim(Char value) const&& noexcept -> void = delete;
  auto ltrim(View const& view = STraits::whitespace) const&& noexcept -> void = delete;

  CDS_ATTR(2(nodiscard, constexpr(14))) auto rtrim(Char value) const& noexcept -> View {
    auto d = data();
    auto l = length();
    for (; l > 0 && d[l - 1] == value; --l) {
      // nothing, just advances start pointer and length
    }
    return View{d, l};
  }

  CDS_ATTR(2(nodiscard, constexpr(14))) auto rtrim(View const& view = STraits::whitespace) const& noexcept -> View {
    auto d = data();
    auto l = length();
    for (; l > 0 && view.contains(d[l - 1]); --l) {
      // nothing, just advances start pointer and length
    }
    return View{d, l};
  }

  auto rtrim(Char value)&& noexcept -> void = delete;
  auto rtrim(View const& view = STraits::whitespace)&& noexcept -> void = delete;
  auto rtrim(Char value) const&& noexcept -> void = delete;
  auto rtrim(View const& view = STraits::whitespace) const&& noexcept -> void = delete;

  CDS_ATTR(2(nodiscard, constexpr(14))) auto trim(Char value) const& noexcept -> View {
    auto d = data();
    auto l = length();
    for (; l > 0 && d[l - 1] == value; --l) {
      // nothing, just advances start pointer and length
    }
    for (; l > 0 && *d == value; ++d, --l) {
      // nothing, just advances start pointer and length
    }
    return View{d, l};
  }

  CDS_ATTR(2(nodiscard, constexpr(14))) auto trim(View const& view = STraits::whitespace) const& noexcept -> View {
    auto d = data();
    auto l = length();
    for (; l > 0 && view.contains(d[l - 1]); --l) {
      // nothing, just advances start pointer and length
    }
    for (; l > 0 && view.contains(*d); ++d, --l) {
      // nothing, just advances start pointer and length
    }
    return View{d, l};
  }

  auto trim(Char value)&& noexcept -> void = delete;
  auto trim(View const& view = STraits::whitespace)&& noexcept -> void = delete;
  auto trim(Char value) const&& noexcept -> void = delete;
  auto trim(View const& view = STraits::whitespace) const&& noexcept -> void = delete;

  CDS_ATTR(2(nodiscard, constexpr(20))) auto ljust(Size size, Char with = ' ') const& noexcept -> BaseString {
    if (size <= length()) {
      return *this;
    }

    BaseString res;
    res.init(size);
    *impl::copy(begin(), end(), impl::fill(res.begin(), res.begin() + (size - length()), with)) = STraits::nullChar;
    return res;
  }

  CDS_ATTR(2(nodiscard, constexpr(20))) auto ljust(Size size, Char with = ' ')&& noexcept -> BaseString {
    auto res = cds::move(*this);
    if (size <= res.length()) {
      return res;
    }

    res.reserve(size);
    auto const diff = size - res.length();
    *(res.rbegin() - (diff + 1)) = STraits::nullChar;
    for (auto it = res.rbegin(); it != res.rend(); ++it) {
      *(it - diff) = *it;
    }

    for (auto it = res.begin(), e = res.begin() + diff; it != e; ++it) {
      *it = with;
    }

    if (res.sh()) {
      res._sbo.lenSbo = static_cast<U8>(size << 1u | 1u);
    } else {
      res._nrm.lenSbo = size << 1u;
    }

    return res;
  }

  CDS_ATTR(2(nodiscard, constexpr(20))) auto rjust(Size size, Char with = ' ') const& noexcept -> BaseString {
    if (size <= length()) {
      return *this;
    }

    auto res = *this;
    res.reserve(size);
    *impl::fill(res.end(), res.begin() + size, with) = STraits::nullChar;
    if (res.sh()) {
      res._sbo.lenSbo = static_cast<U8>(size << 1u | 1u);
    } else {
      res._nrm.lenSbo = size << 1u;
    }

    return res;
  }

  CDS_ATTR(2(nodiscard, constexpr(20))) auto rjust(Size size, Char with = ' ')&& noexcept -> BaseString {
    auto res = cds::move(*this);
    if (size <= res.length()) {
      return res;
    }

    res.reserve(size);
    *impl::fill(res.end(), res.begin() + size, with) = STraits::nullChar;
    if (res.sh()) {
      res._sbo.lenSbo = static_cast<U8>(size << 1u | 1u);
    } else {
      res._nrm.lenSbo = size << 1u;
    }

    return res;
  }

  CDS_ATTR(2(nodiscard, constexpr(14))) auto removePrefix(Char value) const& noexcept -> View {
    return ltrim(value);
  }

  CDS_ATTR(2(nodiscard, constexpr(14))) auto removePrefix(View const& view) const& noexcept -> View {
    auto d = data();
    auto l = length();
    auto dv = view.data();
    auto dl = view.length();
    for (; l > 0 && dl > 0 && *dv == *d; --l, --dl, ++d, ++dv) {
      // nothing
    }

    return dl == 0 ? View{d, l} : View{*this};
  }

  CDS_ATTR(2(nodiscard, constexpr(14))) auto removeSuffix(Char value) const& noexcept -> View {
    return rtrim(value);
  }

  CDS_ATTR(2(nodiscard, constexpr(14))) auto removeSuffix(View const& view) const& noexcept -> View {
    auto l = length();
    auto d = data() + l;
    auto dl = view.length();
    auto dv = view.data() + dl;
    for (; l > 0 && dl > 0 && *(dv - 1) == *(d - 1); --l, --dl, --d, --dv) {
      // nothing
    }

    return dl == 0 ? View{data(), l} : View{*this};
  }

  auto removePrefix(Char value)&& noexcept -> void = delete;
  auto removePrefix(View const& view)&& noexcept -> void = delete;
  auto removePrefix(Char value) const&& noexcept -> void = delete;
  auto removePrefix(View const& view) const&& noexcept -> void = delete;

  auto removeSuffix(Char value)&& noexcept -> void = delete;
  auto removeSuffix(View const& view)&& noexcept -> void = delete;
  auto removeSuffix(Char value) const&& noexcept -> void = delete;
  auto removeSuffix(View const& view) const&& noexcept -> void = delete;

  template <typename N1, typename N2> CDS_ATTR(2(nodiscard, constexpr(20)))
  auto replace(N1 from, N2 to, View const& repl) const& CDS_ATTR(noexcept(false)) -> BaseString {
    if (from > to) {
      return *this;
    }

    auto const seqLen = to - from;
    BaseString res;
    res.init(length() - seqLen + repl.length());
    auto o = impl::copy(begin(), begin() + from, res.begin());
    o = impl::copy(repl.begin(), repl.end(), o);
    *impl::copy(begin() + to, end(), o) = STraits::nullChar;
    return res;
  }

  template <typename N1, typename N2> CDS_ATTR(2(nodiscard, constexpr(20)))
  auto replace(N1 from, N2 to, View const& repl)&& CDS_ATTR(noexcept(false)) -> BaseString {
    auto res = cds::move(*this);
    if (from > to) {
      return res;
    }

    auto const seqLen = to - from;
    auto const len = res.length() - seqLen + repl.length();
    auto const oLen = res.length();
    res.reserve(len);
    if (res.sh()) {
      res._sbo.lenSbo = static_cast<U8>(len << 1u | 1u);
    } else {
      res._nrm.lenSbo = len << 1u;
    }

    if (seqLen > repl.length()) {
      auto const offset = seqLen - repl.length();
      for (auto it = res.begin() + (from + repl.length()), e = it + (oLen - to); it != e; ++it) {
        *it = *(it + offset);
      }
    } else if (seqLen < repl.length()) {
      auto const offset = repl.length() - seqLen;
      for (auto it = res.rbegin(), e = res.rbegin() + (oLen - to); it != e; ++it) {
        *it = *(it + offset);
      }
    }
    *(res.rbegin() - 1) = STraits::nullChar;

    impl::copy(repl.begin(), repl.end(), res.begin() + from);
    return res;
  }

  template <typename... Strings> CDS_ATTR(2(nodiscard, constexpr(20)))
  static auto join(View const& separator, Strings&&... strings) CDS_ATTR(noexcept(false)) -> BaseString {
    static_assert(sizeof...(Strings) > 0, "Calling join without providing strings to join");
    BaseString res;
    res.init(joinLengths(separator, cds::forward<Strings>(strings)...));
    *joinImpl(res.begin(), separator, cds::forward<Strings>(strings)...) = STraits::nullChar;
    return res;
  }

private:
  template <typename T, EnableIf<Not<IsIterableOfThat<T, IsString>>> = 0> CDS_ATTR(2(nodiscard, constexpr(11)))
  static auto eJoinLength(CDS_ATTR(unused) View const& v, T&& e) noexcept -> Size {
    return StringAbstract<>::length(e);
  }

  template <typename T, EnableIf<IsIterableOfThat<T, IsString>> = 0> CDS_ATTR(2(nodiscard, constexpr(14)))
  static auto eJoinLength(View const& v, T&& e) noexcept -> Size {
    using SA = StringAbstract<>;
    Size l = 0;
    auto ib = cds::begin(cds::forward<T>(e));
    auto const ie = cds::end(cds::forward<T>(e));
    if (ib != ie) {
      l += SA::length(*ib);
      for (++ib; ib != ie; ++ib) {
        l += SA::length(*ib) + v.length();
      }
    }

    return l;
  }

  template <typename F> CDS_ATTR(2(nodiscard, constexpr(14)))
  static auto joinLengths(CDS_ATTR(unused) View const& v, F&& f) noexcept -> Size {
    return eJoinLength(v, cds::forward<F>(f));
  }

  template <typename F, typename... R> CDS_ATTR(2(nodiscard, constexpr(14)))
  static auto joinLengths(View const& v, F&& f, R&&... r) noexcept -> Size {
    return joinLengths(v, cds::forward<R>(r)...) + eJoinLength(v, cds::forward<F>(f)) + v.length();
  }

  template <typename O, typename T, EnableIf<Not<IsIterableOfThat<T, IsString>>> = 0> CDS_ATTR(2(nodiscard, constexpr(14)))
  static auto eJoinImpl(O o, CDS_ATTR(unused) View const& v, T&& e) noexcept -> O {
    using SA = StringAbstract<>;
    auto const* buf = SA::data(cds::forward<T>(e));
    auto const len = SA::length(cds::forward<T>(e));
    return impl::copy(buf, buf + len, o);
  }

  template <typename O, typename T, EnableIf<IsIterableOfThat<T, IsString>> = 0> CDS_ATTR(2(nodiscard, constexpr(14)))
  static auto eJoinImpl(O o, View const& v, T&& e) noexcept -> O {
    using SA = StringAbstract<>;
    auto ib = cds::begin(cds::forward<T>(e));
    auto const ie = cds::end(cds::forward<T>(e));
    if (ib != ie) {
      auto const* fBuf = SA::data(*ib);
      auto const fLen = SA::length(*ib);
      o = impl::copy(fBuf, fBuf + fLen, o);
      for (++ib; ib != ie; ++ib) {
        auto const* eBuf = SA::data(*ib);
        auto const eLen = SA::length(*ib);
        o = impl::copy(eBuf, eBuf + eLen, impl::copy(v.begin(), v.end(), o));
      }
    }
    return o;
  }

  template <typename O, typename F, typename... R> CDS_ATTR(2(nodiscard, constexpr(14)))
  static auto joinImpl(O o, View const& v, F&& f, R&&... r) noexcept -> O {
    return joinImpl(impl::copy(v.begin(), v.end(), eJoinImpl(o, v, cds::forward<F>(f))), v, cds::forward<R>(r)...);
  }

  template <typename O, typename F> CDS_ATTR(2(nodiscard, constexpr(11)))
  static auto joinImpl(O o, CDS_ATTR(unused) View const& v, F&& f) noexcept -> O {
    return eJoinImpl(o, v, cds::forward<F>(f));
  }

  CDS_ATTR(constexpr(14)) auto init(Size const len) CDS_ATTR(noexcept(false)) -> void {
    if (sh(len)) {
      sboInit(len);
    } else {
      nrmInit(len);
    }
  }

  CDS_ATTR(constexpr(14)) auto init() noexcept -> void {
    _nrm.buf = nullptr;
    _nrm.lenSbo = 0u;
    _nrm.cap = 0u;
  }

  CDS_ATTR(constexpr(14)) auto sboInit(Size const len = 0) noexcept -> void {
    _sbo.lenSbo = static_cast<U8>(len << 1u | 1u);
    _sbo.initialize();
  }

  CDS_ATTR(constexpr(14)) auto nrmInit(Size const len) CDS_ATTR(noexcept(false)) -> void {
    nrmInit(len, len + 1u);
  }

  CDS_ATTR(constexpr(14)) auto nrmInit(Size const len, Size const cap) CDS_ATTR(noexcept(false)) -> void {
    _nrm.lenSbo = len << 1u;
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
    _sbo.lenSbo = static_cast<U8>(len << 1u | 1u);
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
    _nrm.lenSbo = len << 1u;
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto sh() const noexcept -> bool {
#if CDS_ATTR(cpp20)
    return !inConstexpr() && ((_sbo.lenSbo & 1) != 0u);
#else
    return ((_sbo.lenSbo & 1) != 0u);
#endif
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) static auto sh(Size const length) noexcept -> bool {
#if CDS_ATTR(cpp20)
    return !inConstexpr() && length < sbo::StringSboData<C>::Size::value;
#else
    return length < sbo::StringSboData<C>::Size::value;
#endif
  }

  CDS_ATTR(constexpr(20)) auto copyUninitialized(Address address, Size const length) noexcept -> void {
    init(length);
    if (length == 0) {
      return;
    }

    construct(impl::copyInitialize(address, address + length, data()), STraits::nullChar);
  }

  CDS_ATTR(constexpr(20)) auto copy(Address address, Size const length) noexcept -> void {
    if (sh() && sh(length)) {
      _sbo.lenSbo = static_cast<U8>(length << 1u | 1u);
    } else {
      if (length >= cap()) {
        clear();
        _nrm.cap = maxOf(minCap, length + 1u);
        _nrm.buf = A::allocate(_nrm.cap);
#if CDS_ATTR(cpp20)
        if (inConstexpr()) {
          _nrm.lenSbo = length << 1u;
          construct(impl::copyInitialize(address, address + length, data()), STraits::nullChar);
          return;
        }
#endif
      }
#if CDS_ATTR(cpp20)
      if (inConstexpr() && (_nrm.lenSbo >> 1u) < length) {
        impl::fillInitialize(_nrm.buf + (_nrm.lenSbo >> 1u), _nrm.buf + length + 1, STraits::nullChar);
      }
#endif
      _nrm.lenSbo = length << 1u;
    }
    *impl::copy(address, address + length, begin()) = STraits::nullChar;
  }

  CDS_ATTR(constexpr(20)) auto transfer(BaseString&& str) noexcept -> void {
    sbo::StringData<C>::operator=(cds::move(str));
#if CDS_ATTR(cpp20)
    if (inConstexpr()) {
      str._nrm.lenSbo = 0u;
      str._nrm.cap = 0u;
      str._nrm.buf = nullptr;
      return;
    }
#endif
    str._sbo.lenSbo = 1u;
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto cap() const noexcept -> Size {
    return sh() ? sbo::StringSboData<C>::Size::value : _nrm.cap;
  }

  template <typename I, typename S>
  CDS_ATTR(constexpr(14)) auto append(I b, S e) CDS_ATTR(noexcept(false)) -> BaseString& {
    auto const seqLen = e - b;
    auto const reqLen = seqLen + length();
    if (reqLen <= capacity()) {
      return uncheckedAppend(b, e);
    }

    auto const newCap = maxOf(reqLen + 1, minCap, capacity() * 2);
    auto const newBuf = A::allocate(newCap);
    construct(impl::copyInitialize(b, e, impl::copyInitialize(begin(), end(), newBuf)), STraits::nullChar);
    if (!sh()) {
#if CDS_ATTR(cpp20)
      if (inConstexpr()) {
        if (_nrm.buf) {
          A::deallocate(_nrm.buf, _nrm.cap);
        }
      } else {
        A::deallocate(_nrm.buf, _nrm.cap);
      }
#else
      A::deallocate(_nrm.buf, _nrm.cap);
#endif
    }
    _nrm.lenSbo = reqLen << 1u;
    _nrm.buf = newBuf;
    _nrm.cap = newCap;
    return *this;
  }

  template <typename I, typename S>
  CDS_ATTR(constexpr(14)) auto uncheckedAppend(I b, S e) CDS_ATTR(noexcept(false)) -> BaseString& {
    construct(impl::copyInitialize(b, e, data() + length()), STraits::nullChar);
    auto const newLen = length() + (e - b);
    if (sh()) {
      _sbo.lenSbo = static_cast<U8>(newLen << 1u | 1u);
    } else {
      _nrm.lenSbo = newLen << 1u;
    }
    return *this;
  }

  static Size const minCap;
};

template <typename C, typename U, typename A> Idx const BaseString<C, U, A>::npos = -1;
template <typename C, typename U, typename A> Idx const BaseString<C, U, A>::invalidIndex = npos;
template <typename C, typename U, typename A> Size const BaseString<C, U, A>::minCap = 32u;

template <typename FC, typename FU, typename FA>
auto operator<<(typename BaseString<FC, FU, FA>::OStream& out, BaseString<FC, FU, FA> const& obj)
    CDS_ATTR(noexcept(noexcept(out.write(obj.data(), obj.length())))) -> typename BaseString<FC, FU, FA>::OStream& {
  out.write(obj.data(), obj.length());
  return out;
}

template <
    typename FC, typename FU, typename FA, typename Str, typename D = RemoveCVRef<Str>,
    EnableIf<And<Not<IsIntegral<D>>, Not<IsFloating<D>>>> = 0
> CDS_ATTR(2(nodiscard, constexpr(20)))
auto operator+(BaseString<FC, FU, FA> const& lhs, Str&& rhs) CDS_ATTR(noexcept(false)) -> BaseString<FC, FU, FA> {
  using SA = StringAbstract<>;
  BaseString<FC, FU, FA> res;
  auto const buf = SA::data(cds::forward<Str>(rhs));
  auto const len = SA::length(cds::forward<Str>(rhs));
  auto const reqLen = lhs.size() + len;
  res.reserve(reqLen);
  res.uncheckedAppend(lhs.begin(), lhs.end()).uncheckedAppend(buf, buf + len);
  return res;
}

template <
    typename FC, typename FU, typename FA, typename Str, typename D = RemoveCVRef<Str>,
    EnableIf<And<Not<IsIntegral<D>>, Not<IsFloating<D>>, Not<IsSame<D, BaseString<FC, FU, FA>>>>> = 0
> CDS_ATTR(2(nodiscard, constexpr(20)))
auto operator+(Str&& lhs, BaseString<FC, FU, FA> const& rhs) CDS_ATTR(noexcept(false)) -> BaseString<FC, FU, FA> {
  using SA = StringAbstract<>;
  BaseString<FC, FU, FA> res;
  auto const buf = SA::data(cds::forward<Str>(lhs));
  auto const len = SA::length(cds::forward<Str>(lhs));
  auto const reqLen = len + rhs.size();
  res.reserve(reqLen);
  res.uncheckedAppend(buf, buf + len).uncheckedAppend(rhs.begin(), rhs.end());
  return res;
}

template <
    typename FC, typename FU, typename FA, typename Str, typename D = RemoveCVRef<Str>,
    EnableIf<And<Not<IsIntegral<D>>, Not<IsFloating<D>>>> = 0
> CDS_ATTR(2(nodiscard, constexpr(20)))
auto operator+(BaseString<FC, FU, FA>&& lhs, Str&& rhs) CDS_ATTR(noexcept(false)) -> BaseString<FC, FU, FA> {
  using SA = StringAbstract<>;
  auto res = cds::move(lhs);
  auto const buf = SA::data(cds::forward<Str>(rhs));
  auto const len = SA::length(cds::forward<Str>(rhs));
  auto const reqLen = len + res.size();
  res.reserve(reqLen);
  res.uncheckedAppend(buf, buf + len);
  return res;
}

template <typename FC, typename FU, typename FA> CDS_ATTR(2(nodiscard, constexpr(20)))
    auto operator+(BaseString<FC, FU, FA> const& lhs, FC rhs)
    CDS_ATTR(noexcept(false)) -> BaseString<FC, FU, FA> {
  BaseString<FC, FU, FA> res;
  res.reserve(lhs.size() + 1);
  res.uncheckedAppend(lhs.begin(), lhs.end()).uncheckedAppend(&rhs, &rhs + 1);
  return res;
}

template <typename FC, typename FU, typename FA> CDS_ATTR(2(nodiscard, constexpr(20)))
    auto operator+(FC lhs, BaseString<FC, FU, FA> const& rhs)
    CDS_ATTR(noexcept(false)) -> BaseString<FC, FU, FA> {
  BaseString<FC, FU, FA> res;
  res.reserve(rhs.size() + 1);
  res.uncheckedAppend(&lhs, &lhs + 1).uncheckedAppend(rhs.begin(), rhs.end());
  return res;
}

template <typename FC, typename FU, typename FA> CDS_ATTR(2(nodiscard, constexpr(20)))
    auto operator+(BaseString<FC, FU, FA>&& lhs, FC rhs)
    CDS_ATTR(noexcept(false)) -> BaseString<FC, FU, FA> {
  auto res = cds::move(lhs);
  res.reserve(res.size() + 1);
  res.uncheckedAppend(&rhs, &rhs + 1);
  return res;
}

template <typename FC, typename FU, typename FA> CDS_ATTR(2(nodiscard, constexpr(20)))
    auto operator+(BaseString<FC, FU, FA> const& lhs, bool rhs) CDS_ATTR(noexcept(false)) -> BaseString<FC, FU, FA> {
  using Constants = meta::impl::StringTraitsPrivateConstants<FC>;
  BaseString<FC, FU, FA> res;
  auto const* buf = rhs ? Constants::_true : Constants::_false;
  auto const len = rhs ? 4 : 5;
  res.reserve(lhs.size() + len);
  res.uncheckedAppend(lhs.begin(), lhs.end()).uncheckedAppend(buf, buf + len);
  return res;
}

template <typename FC, typename FU, typename FA> CDS_ATTR(2(nodiscard, constexpr(20)))
    auto operator+(bool lhs, BaseString<FC, FU, FA> const& rhs) CDS_ATTR(noexcept(false)) -> BaseString<FC, FU, FA> {
  using Constants = meta::impl::StringTraitsPrivateConstants<FC>;
  BaseString<FC, FU, FA> res;
  auto const* buf = lhs ? Constants::_true : Constants::_false;
  auto const len = lhs ? 4 : 5;
  res.reserve(rhs.size() + len);
  res.uncheckedAppend(buf, buf + len).uncheckedAppend(rhs.begin(), rhs.end());
  return res;
}

template <typename FC, typename FU, typename FA> CDS_ATTR(2(nodiscard, constexpr(20)))
    auto operator+(BaseString<FC, FU, FA>&& lhs, bool rhs) CDS_ATTR(noexcept(false)) -> BaseString<FC, FU, FA> {
  using Constants = meta::impl::StringTraitsPrivateConstants<FC>;
  auto res = cds::move(lhs);
  auto const* buf = rhs ? Constants::_true : Constants::_false;
  auto const len = rhs ? 4 : 5;
  res.reserve(res.size() + len);
  res.uncheckedAppend(buf, buf + len);
  return res;
}

template <typename FC, typename FU, typename FA, typename N, EnableIf<IsIntegral<N>> = 0> CDS_ATTR(2(nodiscard, constexpr(20)))
    auto operator+(BaseString<FC, FU, FA> const& lhs, N rhs) CDS_ATTR(noexcept(false)) -> BaseString<FC, FU, FA> {
  using Tr = typename BaseString<FC, FU, FA>::STraits;
  BaseString<FC, FU, FA> res;
  auto const len = FU::intLength(rhs, 10);
  res.reserve(lhs.size() + len);
  res.uncheckedAppend(lhs.begin(), lhs.end());
#if CDS_ATTR(cpp20)
  if (inConstexpr()) {
    impl::fillInitialize(res.data() + res.length(), res.data() + res.length() + len + 1, Tr::nullChar);
  }
#endif
  *FU::writeInt(rhs, len, res.end()) = Tr::nullChar;
  auto const newLen = res.length() + len;
  if (res.sh()) {
    res._sbo.lenSbo = static_cast<U8>(newLen << 1u | 1u);
  } else {
    res._nrm.lenSbo = newLen << 1u;
  }
  return res;
}

template <typename FC, typename FU, typename FA, typename N, EnableIf<IsIntegral<N>> = 0> CDS_ATTR(2(nodiscard, constexpr(20)))
    auto operator+(N lhs, BaseString<FC, FU, FA> const& rhs) CDS_ATTR(noexcept(false)) -> BaseString<FC, FU, FA> {
  using Tr = typename BaseString<FC, FU, FA>::STraits;
  BaseString<FC, FU, FA> res;
  auto const len = FU::intLength(lhs, 10);
  res.reserve(rhs.size() + len);
#if CDS_ATTR(cpp20)
  if (inConstexpr()) {
    impl::fillInitialize(res.data(), res.data() + len + 1, Tr::nullChar);
  }
#endif
  *FU::writeInt(lhs, len, res.end()) = Tr::nullChar;
  auto const newLen = res.length() + len;
  if (res.sh()) {
    res._sbo.lenSbo = static_cast<U8>(newLen << 1u | 1u);
  } else {
    res._nrm.lenSbo = newLen << 1u;
  }
  res.uncheckedAppend(rhs.begin(), rhs.end());
  return res;
}

template <typename FC, typename FU, typename FA, typename N, EnableIf<IsIntegral<N>> = 0> CDS_ATTR(2(nodiscard, constexpr(20)))
    auto operator+(BaseString<FC, FU, FA>&& lhs, N rhs) CDS_ATTR(noexcept(false)) -> BaseString<FC, FU, FA> {
  using Tr = typename BaseString<FC, FU, FA>::STraits;
  auto res = cds::move(lhs);
  auto const len = FU::intLength(rhs, 10);
  res.reserve(res.size() + len);
#if CDS_ATTR(cpp20)
  if (inConstexpr()) {
    impl::fillInitialize(res.data() + res.length(), res.data() + res.length() + len + 1, Tr::nullChar);
  }
#endif
  *FU::writeInt(rhs, len, res.end()) = Tr::nullChar;
  auto const newLen = res.length() + len;
  if (res.sh()) {
    res._sbo.lenSbo = static_cast<U8>(newLen << 1u | 1u);
  } else {
    res._nrm.lenSbo = newLen << 1u;
  }
  return res;
}

template <typename FC, typename FU, typename FA, typename F, EnableIf<IsFloating<F>> = 0> CDS_ATTR(nodiscard)
    auto operator+(BaseString<FC, FU, FA> const& lhs, F rhs) CDS_ATTR(noexcept(false)) -> BaseString<FC, FU, FA> {
  BaseString<FC, FU, FA> res;
  auto const len = FU::floatingLength(rhs);
  res.reserve(lhs.size() + len);
  res.uncheckedAppend(lhs.begin(), lhs.end());
  *FU::writeFloating(rhs, len, res.data() + res.length()) = BaseString<FC, FU, FA>::STraits::nullChar;
  auto const newLen = res.length() + len;
  if (res.sh()) {
    res._sbo.lenSbo = static_cast<U8>(newLen << 1u | 1u);
  } else {
    res._nrm.lenSbo = newLen << 1u;
  }
  return res;
}

template <typename FC, typename FU, typename FA, typename F, EnableIf<IsFloating<F>> = 0> CDS_ATTR(nodiscard)
    auto operator+(F lhs, BaseString<FC, FU, FA> const& rhs) CDS_ATTR(noexcept(false)) -> BaseString<FC, FU, FA> {
  BaseString<FC, FU, FA> res;
  auto const len = FU::floatingLength(lhs);
  res.reserve(rhs.size() + len);
  *FU::writeFloating(lhs, len, res.data()) = BaseString<FC, FU, FA>::STraits::nullChar;
  auto const newLen = res.length() + len;
  if (res.sh()) {
    res._sbo.lenSbo = static_cast<U8>(newLen << 1u | 1u);
  } else {
    res._nrm.lenSbo = newLen << 1u;
  }
  res.uncheckedAppend(rhs.begin(), rhs.end());
  return res;
}

template <typename FC, typename FU, typename FA, typename F, EnableIf<IsFloating<F>> = 0> CDS_ATTR(nodiscard)
    auto operator+(BaseString<FC, FU, FA>&& lhs, F rhs) CDS_ATTR(noexcept(false)) -> BaseString<FC, FU, FA> {
  auto res = cds::move(lhs);
  auto const len = FU::floatingLength(rhs);
  res.reserve(res.size() + len);
  *FU::writeFloating(rhs, len, res.data() + res.length()) = BaseString<FC, FU, FA>::STraits::nullChar;
  auto const newLen = res.length() + len;
  if (res.sh()) {
    res._sbo.lenSbo = static_cast<U8>(newLen << 1u | 1u);
  } else {
    res._nrm.lenSbo = newLen << 1u;
  }
  return res;
}
} // namespace impl

inline namespace literals {
CDS_ATTR(2(nodiscard, constexpr(20)))
auto operator ""_s(char const* string, std::size_t length) noexcept -> impl::BaseString<char> {
  return impl::BaseString<char>{string, length};
}

CDS_ATTR(2(nodiscard, constexpr(20)))
auto operator ""_s(wchar_t const* string, std::size_t length) noexcept -> impl::BaseString<wchar_t> {
  return {string, length};
}

CDS_ATTR(2(nodiscard, constexpr(20)))
auto operator ""_s(char16_t const* string, std::size_t length) noexcept -> impl::BaseString<char16_t> {
  return {string, length};
}

CDS_ATTR(2(nodiscard, constexpr(20)))
auto operator ""_s(char32_t const* string, std::size_t length) noexcept -> impl::BaseString<char32_t> {
  return {string, length};
}

#if CDS_ATTR(cpp20)
CDS_ATTR(2(nodiscard, constexpr(20)))
auto operator ""_s(char8_t const* string, std::size_t length) noexcept -> impl::BaseString<char8_t> {
  return {string, length};
}
#endif
}
} // namespace cds

#include "../../common/StringBackInserterIterator.hpp"
#include "../../common/StringConversion.hpp"
#include "../../common/TupleString.hpp"

#endif // CDS_PRIMITIVE_STRING_BASE_HPP
