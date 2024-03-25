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

#include "../../bindings/BindingSelectors.hpp"
#include "../../bindings/static/ContainsOfStaticBinding.hpp"
#include "../../bindings/static/FindStaticBinding.hpp"
#include "../../bindings/static/FindOfStaticBinding.hpp"
#include "../../bindings/static/GenericLoopBinding.hpp"

#include "../../stdlib/ostream.hpp"

namespace cds {
namespace impl {
using meta::Int;

using sel::With;
using sel::Value;
using sel::Projector;
using sel::Immutable;
using sel::Mutable;

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
};

template <typename C> struct StringSboData<C, Int<2>> {
  C buf[sizeof(StringNonSboData<C>) / 2u - 1u];
  U8 pad[1u];
  U8 len : 7;
  bool sbo : 1;
};

template <typename C> struct StringSboData<C, Int<4>> {
  C buf[sizeof(StringNonSboData<C>) / 4u - 1u];
  U8 pad[3u];
  U8 len : 7;
  bool sbo : 1;
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

  CDS_ATTR(constexpr(20)) BaseString(Address data, Size const length) noexcept(false) {
    copy(data, length);
  }

  CDS_ATTR(constexpr(20)) BaseString() {
    _sbo.len = 0u;
    _sbo.sbo = true;
  }

  CDS_ATTR(constexpr(20)) BaseString(BaseString const& str) noexcept(false) : BaseString(str.data(), str.length()) {}

  CDS_ATTR(constexpr(20)) BaseString(BaseString && str) noexcept {
    transfer(cds::move(str));
  }

  CDS_ATTR(constexpr(20)) ~BaseString() noexcept {
    clear();
  }

  template <typename Convertible, EnableIf<Not<IsSame<RemoveCVRef<Convertible>, BaseString>>> = 0>
  CDS_ATTR(2(implicit, constexpr(20))) BaseString(Convertible&& string) noexcept(false) :
      BaseString(
          StringAbstract<Convertible>::data(cds::forward<Convertible>(string)),
          StringAbstract<Convertible>::length(cds::forward<Convertible>(string))
      ) {}

  CDS_ATTR(constexpr(20)) auto operator=(BaseString const& str) noexcept(false) -> BaseString& {
    if (&str == this) {
      return *this;
    }

    clear();
    copy(str.data(), str.length());
    return *this;
  }

  CDS_ATTR(constexpr(20)) auto operator=(BaseString&& str) noexcept -> BaseString& {
    if (&str == this) {
      return *this;
    }

    clear();
    transfer(cds::move(str));
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

  CDS_ATTR(constexpr(20)) auto clear() noexcept -> void {
    if (sh()) {
      return;
    }

    A::deallocate(_nrm.buf, _nrm.cap);
    _nrm.len = 0u;
    _nrm.cap = 0u;
  }

private:
  CDS_ATTR(2(nodiscard, constexpr(11))) auto sh() const noexcept -> bool {
    return _sbo.sbo;
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) static auto sh(Size length) noexcept -> bool {
    return length + 1u < sizeof(sbo::StringSboData<C>::buf);
  }

  CDS_ATTR(constexpr(20)) auto copy(Address address, Size const length) noexcept -> void {
    if (sh(length)) {
      _sbo.sbo = true;
      _sbo.len = static_cast<U8>(length);
      impl::copy(address, address + length, &_sbo.buf[0]);
      return;
    }

    _nrm.sbo = false;
    _nrm.cap = cds::maxOf(minCap, length + 1u);
    _nrm.len = length;
    _nrm.buf = A::allocate(_nrm.cap);
    * impl::copy(address, address + length, _nrm.buf) = '\0';
  }

  CDS_ATTR(constexpr(20)) auto transfer(BaseString&& str) noexcept -> void {
    sbo::StringData<C>::operator=(cds::move(str));
    str._sbo.sbo = true;
    str._sbo.len = 0u;
  }

  static Size constexpr minCap = 32u;
};
} // namespace impl
} // namespace cds

#endif // CDS_PRIMITIVE_STRING_BASE_HPP
