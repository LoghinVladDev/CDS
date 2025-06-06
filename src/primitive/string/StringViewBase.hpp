//
// Created by loghin on 12/8/23.
//

#ifndef CDS_PRIMITIVE_STRING_VIEW_BASE_HPP
#define CDS_PRIMITIVE_STRING_VIEW_BASE_HPP
#pragma once

#include "StringViewBaseDecl.hpp"
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
using sel::With;
using sel::Value;
using sel::Projector;
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
using meta::IsAllocatorOrAllocatorSet;

using meta::lvalue;
using meta::rvalue;

#if CDS_ATTR(spaceship)
using std::strong_ordering;
#endif // #if CDS_ATTR(spaceship)

template <typename C, typename U> struct FindStringViewTransformer {
  template <typename IB, typename IE, typename I>
  CDS_ATTR(2(nodiscard, constexpr(11))) auto operator()(IB&& b, IE&& e, I&& i) const noexcept -> Idx {
    return fwd<IE>(e) == fwd<I>(i)
        ? BaseStringView<C, U>::npos
        : (fwd<I>(i) - fwd<IB>(b));
  }
};

namespace bindingsBSV {
template <typename C, typename U> using Self = BaseStringView<C, U>;
template <typename C, typename U> using Traits = IterableTraits<Self<C, U>>;

using ContainsOpt = With<Value, Projector>;
template <typename C, typename U> struct CDS_ATTR(ebo) ContainsOf :
    ContainsOfStaticBinding<Self<C, U>, ContainsOpt> {};

using FindOpt = With<Value, Projector, Immutable>;
template <typename C, typename U> struct CDS_ATTR(ebo) FindTr :
    FindStringViewTransformer<C, U> {};
template <typename C, typename U> struct CDS_ATTR(ebo) Find :
    FindStaticBinding<Self<C, U>, FindOpt, FindTr<C, U>, FindTr<C, U>> {};
template <typename C, typename U> struct CDS_ATTR(ebo) FindOf :
    FindOfStaticBinding<Self<C, U>, FindOpt, FindTr<C, U>, FindTr<C, U>> {};

using LoopOpt = With<Immutable>;
template <typename C, typename U> struct CDS_ATTR(ebo) GenericLoop :
    GenericLoopBinding<Self<C, U>, LoopOpt> {};
} // namespace bindingsBSV

template <typename C, typename U> class CDS_ATTR(ebo) BaseStringView :
    public bindingsBSV::Traits<C, U>,
    public bindingsBSV::ContainsOf<C, U>,
    public bindingsBSV::Find<C, U>,
    public bindingsBSV::FindOf<C, U>,
    public bindingsBSV::GenericLoop<C, U>,
    private strop::StringOperatorUser {
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

  template <typename Convertible, EnableIf<Not<IsSame<RemoveCVRef<Convertible>, BaseStringView>>> = 0>
  CDS_ATTR(2(implicit, constexpr(11))) BaseStringView(Convertible&& string) noexcept :
      _data(StringAbstract<Convertible>::data(fwd<Convertible>(string))),
      _length(StringAbstract<Convertible>::length(fwd<Convertible>(string))) {}

  CDS_ATTR(constexpr(11)) BaseStringView(Address data, Size const length) noexcept : _data(data), _length(length) {}

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
    return ReverseIterator(_data + _length);
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto rend() const noexcept -> ReverseIterator {
    return ReverseIterator(_data);
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto crbegin() const noexcept -> ConstReverseIterator {
    return ConstReverseIterator(_data + _length);
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto crend() const noexcept -> ConstReverseIterator {
    return ConstReverseIterator(_data);
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

    return {_data + sFrom, sUntil - sFrom};
  }

  template <typename N> CDS_ATTR(2(nodiscard, constexpr(14))) auto contains(N&& needle) const
      CDS_ATTR(noexcept(noexcept(findFirst(fwd<N>(needle))))) -> bool {
    return findFirst(fwd<N>(needle)) != npos;
  }

  template <typename N, typename S, EnableIf<Not<IsAllocatorOrAllocatorSet<S>>> = 0>
  CDS_ATTR(2(nodiscard, constexpr(14))) auto contains(
      N&& needle, S&& selector
  ) const CDS_ATTR(noexcept(noexcept(findFirst(fwd<N>(needle), fwd<S>(selector))))) -> bool {
    return findFirst(fwd<N>(needle), fwd<S>(selector)) != npos;
  }

  template <typename N, typename A, EnableIf<IsAllocatorOrAllocatorSet<A>> = 0>
  CDS_ATTR(2(nodiscard, constexpr(14))) auto contains(N&& needle, A&& alloc) const
      CDS_ATTR(noexcept(noexcept(findFirst(fwd<N>(needle), fwd<A>(alloc))))) -> bool {
    return findFirst(fwd<N>(needle), fwd<A>(alloc)) != npos;
  }

  template <typename N, typename S, typename A> CDS_ATTR(2(nodiscard, constexpr(14))) auto contains(
      N&& needle, S&& selector, A&& alloc
  ) const CDS_ATTR(noexcept(noexcept(
      findFirst(fwd<N>(needle), fwd<S>(selector), fwd<A>(alloc))
  ))) -> bool {
    return findFirst(fwd<N>(needle), fwd<S>(selector), fwd<A>(alloc)) != npos;
  }

  template <typename A = Allocator<C>> CDS_ATTR(2(nodiscard, constexpr(20)))
  auto str(A&& alloc = A()) const CDS_ATTR(noexcept(false)) -> BaseString<C, U, A>;

  template <typename A = Allocator<C>> CDS_ATTR(2(nodiscard, constexpr(20)))
  auto toString(A&& alloc = A()) const CDS_ATTR(noexcept(false)) -> BaseString<C, U, A> {
    return str(fwd<A>(alloc));
  }

  template <typename N> CDS_ATTR(2(nodiscard, constexpr(14))) auto startsWith(N&& needle) const noexcept -> bool {
    return U::startsWith(data(), size(), fwd<N>(needle));
  }

  template <typename N> CDS_ATTR(2(nodiscard, constexpr(14))) auto endsWith(N&& needle) const noexcept -> bool {
    return U::endsWith(data(), size(), fwd<N>(needle));
  }

  template <typename FC, typename FU>
  friend auto operator<<(typename BaseStringView<FC, FU>::OStream& out, BaseStringView<FC, FU> const& obj)
      CDS_ATTR(noexcept(noexcept(out.write(obj._data, obj._length)))) -> typename BaseStringView<FC, FU>::OStream&;

  template <typename S, typename T = SplitAllocationTraits<S>, EnableIf<Not<typename T::Required>> = 0>
  CDS_ATTR(2(nodiscard, constexpr(14))) auto split(S&& separator) const&
      CDS_ATTR(noexcept(noexcept(impl::split(lvalue<BaseStringView const>(), fwd<S>(separator), 0))))
      -> decltype(impl::split(lvalue<BaseStringView const>(), fwd<S>(separator), 0)) {
    return impl::split(*this, fwd<S>(separator), limits::sizeMax);
  }

  template <typename S, typename T = SplitAllocationTraits<S>, EnableIf<Not<typename T::Required>> = 0>
  CDS_ATTR(2(nodiscard, constexpr(14))) auto split(S&& separator) const&&
      CDS_ATTR(noexcept(noexcept(impl::split(rvalue<BaseStringView const>(), fwd<S>(separator), 0))))
      -> decltype(impl::split(rvalue<BaseStringView const>(), fwd<S>(separator), 0)) {
    return impl::split(mv(*this), fwd<S>(separator), limits::sizeMax);
  }

  template <typename S, typename T = SplitAllocationTraits<S>, EnableIf<Not<typename T::Required>> = 0>
  CDS_ATTR(2(nodiscard, constexpr(14))) auto split(S&& separator, Size limit) const& CDS_ATTR(noexcept(noexcept(
      impl::split(lvalue<BaseStringView const>(), fwd<S>(separator), limit)
  ))) -> decltype(impl::split(lvalue<BaseStringView const>(), fwd<S>(separator), limit)) {
    return impl::split(*this, fwd<S>(separator), limit);
  }

  template <typename S, typename T = SplitAllocationTraits<S>, EnableIf<Not<typename T::Required>> = 0>
  CDS_ATTR(2(nodiscard, constexpr(14))) auto split(S&& separator, Size limit) const&& CDS_ATTR(noexcept(noexcept(
      impl::split(rvalue<BaseStringView const>(), fwd<S>(separator), limit)
  ))) ->
      decltype(impl::split(rvalue<BaseStringView const>(), fwd<S>(separator), limit)) {
    return impl::split(mv(*this), fwd<S>(separator), limit);
  }

  template <
      typename S, typename T = SplitAllocationTraits<S>, typename A = typename T::Alloc,
      EnableIf<And<typename T::Required, IsAllocatorOrAllocatorSet<RemoveCVRef<A>>>> = 0
  > CDS_ATTR(2(nodiscard, constexpr(20))) auto split(S&& separator, A&& alloc = A()) const& CDS_ATTR(noexcept(noexcept(
      impl::split(lvalue<BaseStringView const>(), fwd<S>(separator), 0, fwd<A>(alloc))
  ))) -> decltype(impl::split(lvalue<BaseStringView const>(), fwd<S>(separator), 0, fwd<A>(alloc))) {
    return impl::split(*this, fwd<S>(separator), limits::sizeMax, fwd<A>(alloc));
  }

  template <
      typename S, typename T = SplitAllocationTraits<S>, typename A = typename T::Alloc,
      EnableIf<And<typename T::Required, IsAllocatorOrAllocatorSet<RemoveCVRef<A>>>> = 0
  > CDS_ATTR(2(nodiscard, constexpr(20))) auto split(S&& separator, A&& alloc = A()) const&& CDS_ATTR(noexcept(noexcept(
      impl::split(rvalue<BaseStringView const>(), fwd<S>(separator), 0, fwd<A>(alloc))
  ))) -> decltype(impl::split(rvalue<BaseStringView const>(), fwd<S>(separator), 0, fwd<A>(alloc))) {
    return impl::split(mv(*this), fwd<S>(separator), limits::sizeMax, fwd<A>(alloc));
  }

  template <
      typename S, typename T = SplitAllocationTraits<S>, typename A = typename T::Alloc,
      EnableIf<And<typename T::Required, IsAllocatorOrAllocatorSet<RemoveCVRef<A>>>> = 0
  > CDS_ATTR(2(nodiscard, constexpr(20))) auto split(S&& separator, Size limit, A&& alloc = A()) const&
      CDS_ATTR(noexcept(noexcept(
          impl::split(lvalue<BaseStringView const>(), fwd<S>(separator), limit, fwd<A>(alloc))
      ))) ->
      decltype(impl::split(lvalue<BaseStringView const>(), fwd<S>(separator), limit, fwd<A>(alloc))) {
    return impl::split(*this, fwd<S>(separator), limit, fwd<A>(alloc));
  }

  template <
      typename S, typename T = SplitAllocationTraits<S>, typename A = typename T::Alloc,
      EnableIf<And<typename T::Required, IsAllocatorOrAllocatorSet<RemoveCVRef<A>>>> = 0
  > CDS_ATTR(2(nodiscard, constexpr(20))) auto split(S&& separator, Size limit, A&& alloc = A()) const&&
      CDS_ATTR(noexcept(noexcept(
          impl::split(rvalue<BaseStringView const>(), fwd<S>(separator), limit, fwd<A>(alloc))
      ))) ->
      decltype(impl::split(rvalue<BaseStringView const>(), fwd<S>(separator), limit, fwd<A>(alloc))) {
    return impl::split(mv(*this), fwd<S>(separator), limit, fwd<A>(alloc));
  }

  CDS_ATTR(2(nodiscard, constexpr(14))) auto ltrim(Char value) const noexcept -> View {
    auto d = data();
    auto l = length();
    for (; l > 0 && *d == value; ++d, --l) {
      // nothing, just advances start pointer and length
    }
    return View{d, l};
  }

  CDS_ATTR(2(nodiscard, constexpr(14))) auto ltrim(View const& view = STraits::whitespace) const noexcept -> View {
    auto d = data();
    auto l = length();
    for (; l > 0 && view.contains(*d); ++d, --l) {
      // nothing, just advances start pointer and length
    }
    return View{d, l};
  }

  CDS_ATTR(2(nodiscard, constexpr(14))) auto rtrim(Char value) const noexcept -> View {
    auto d = data();
    auto l = length();
    for (; l > 0 && value == d[l - 1]; --l) {
      // nothing, just advances start pointer and length
    }
    return View{d, l};
  }

  CDS_ATTR(2(nodiscard, constexpr(14))) auto rtrim(View const& view = STraits::whitespace) const noexcept -> View {
    auto d = data();
    auto l = length();
    for (; l > 0 && view.contains(d[l - 1]); --l) {
      // nothing, just advances start pointer and length
    }
    return View{d, l};
  }

  CDS_ATTR(2(nodiscard, constexpr(14))) auto trim(Char value) const noexcept -> View {
    auto d = data();
    auto l = length();
    for (; l > 0 && value == d[l - 1]; --l) {
      // nothing
    }
    for (; l > 0 && value == *d; ++d, --l) {
      // nothing
    }
    return View{d, l};
  }

  CDS_ATTR(2(nodiscard, constexpr(14))) auto trim(View const& view = STraits::whitespace) const noexcept -> View {
    auto d = data();
    auto l = length();
    for (; l > 0 && view.contains(d[l - 1]); --l) {
      // nothing
    }
    for (; l > 0 && view.contains(*d); ++d, --l) {
      // nothing
    }
    return View{d, l};
  }

  CDS_ATTR(2(nodiscard, constexpr(14))) auto removePrefix(Char value) const noexcept -> View {
    return ltrim(value);
  }

  CDS_ATTR(2(nodiscard, constexpr(14))) auto removePrefix(View const& view) const noexcept -> View {
    auto d = data();
    auto l = length();
    auto dv = view.data();
    auto dl = view.length();
    for (; l > 0 && dl > 0 && *dv == *d; --l, --dl, ++d, ++dv) {
      // nothing
    }

    return dl == 0 ? View{d, l} : *this;
  }

  CDS_ATTR(2(nodiscard, constexpr(14))) auto removeSuffix(Char value) const noexcept -> View {
    return rtrim(value);
  }

  CDS_ATTR(2(nodiscard, constexpr(14))) auto removeSuffix(View const& view) const noexcept -> View {
    auto l = length();
    auto d = data() + l;
    auto dl = view.length();
    auto dv = view.data() + dl;
    for (; l > 0 && dl > 0 && *(dv - 1) == *(d - 1); --l, --dl, --d, --dv) {
      // nothing
    }

    return dl == 0 ? View{data(), l} : *this;
  }

private:
  Address _data {nullptr};
  Size _length {0u};
};

template <typename C, typename U> Idx const BaseStringView<C, U>::npos = -1;
template <typename C, typename U> Idx const BaseStringView<C, U>::invalidIndex = npos;

template <typename FC, typename FU>
auto operator<<(typename BaseStringView<FC, FU>::OStream& out, BaseStringView<FC, FU> const& obj)
    CDS_ATTR(noexcept(noexcept(out.write(obj._data, obj._length)))) -> typename BaseStringView<FC, FU>::OStream& {
  out.write(obj._data, obj._length);
  return out;
}

#if CDS_ATTR(bitarch) == 64u
static_assert(sizeof(BaseStringView<char>) == 16u, "invalid string view data sizes");
#elif CDS_ATTR(bitarch) == 32u
static_assert(sizeof(BaseStringView<char>) == 8u, "invalid string view data sizes");
#endif
} // namespace impl

inline namespace literals {
CDS_ATTR(2(nodiscard, consteval(20, constexpr(11))))
auto operator ""_sv(char const* string, std::size_t length) noexcept -> impl::BaseStringView<char> {
  return {string, length};
}

CDS_ATTR(2(nodiscard, consteval(20, constexpr(11))))
auto operator ""_sv(wchar_t const* string, std::size_t length) noexcept -> impl::BaseStringView<wchar_t> {
  return {string, length};
}

CDS_ATTR(2(nodiscard, consteval(20, constexpr(11))))
auto operator ""_sv(char16_t const* string, std::size_t length) noexcept -> impl::BaseStringView<char16_t> {
  return {string, length};
}

CDS_ATTR(2(nodiscard, consteval(20, constexpr(11))))
auto operator ""_sv(char32_t const* string, std::size_t length) noexcept -> impl::BaseStringView<char32_t> {
  return {string, length};
}

#if CDS_ATTR(cpp20)
CDS_ATTR(2(nodiscard, consteval(20, no_fallback)))
auto operator ""_sv(char8_t const* string, std::size_t length) noexcept -> impl::BaseStringView<char8_t> {
  return {string, length};
}
#endif
}
} // namespace cds

#include "../../common/StringConversion.hpp"

#endif // CDS_PRIMITIVE_STRING_VIEW_BASE_HPP
