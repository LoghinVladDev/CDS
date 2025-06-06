//
// Created by loghin on 10/18/24.
//

#ifndef CDS_DS_ARRAY_BASE_HPP
#define CDS_DS_ARRAY_BASE_HPP

#include <cds/functional/Transformer>

#include <cds/meta/Compiler>
#include <cds/meta/FunctionTraits>
#include <cds/meta/IteratorTraits>

#include "../../algorithm/FindPreserveTransformer.hpp"
#include "../../algorithm/GenericFind.hpp"
#include "../../algorithm/RangeEqual.hpp"
#include "../../iterator/AddressIterator.hpp"
#include "../../meta/Utility.hpp"

#include "../../stdlib/ostream.hpp"

#include <cassert>

namespace cds {
namespace impl {
using iterator::BackwardAddressIterator;
using iterator::ForwardAddressIterator;

using meta::EnableIf;
using meta::IsConstructible;
using meta::IsCopyConstructible;
using meta::IsDefaultConstructible;
using meta::IsInputIterator;
using meta::IsIntegral;
using meta::IsNoexceptConstructible;
using meta::IsNoexceptCopyConstructible;

using meta::rvalue;

using functional::impl::Identity;

using impl::FindPreserveTransformer;

template <typename T, typename E, typename /* A */, typename ScalingBase>
class CDS_ATTR(ebo) ArrayBase : protected ScalingBase {
public:
  using Value = T;
  using Iterator = ForwardAddressIterator<Value>;
  using ConstIterator = ForwardAddressIterator<Value const>;
  using ReverseIterator = BackwardAddressIterator<Value>;
  using ConstReverseIterator = BackwardAddressIterator<Value const>;

private:
  using ScalingBase::head;
  using ScalingBase::makeSpaceAt;
  using ScalingBase::resizeImpl;
  using ScalingBase::tail;
  using ScalingBase::eraseRegion;

  CDS_ATTR(2(nodiscard, constexpr(14))) auto loc(Iterator const& it) noexcept -> T* {
    auto offset = it - begin();
    assert(offset <= size() && "Unexpected out-of-bounds iterator");
    return head() + offset;
  }

  CDS_ATTR(2(nodiscard, constexpr(14))) auto loc(ConstIterator const& it) noexcept -> T* {
    auto offset = it - cbegin();
    assert(offset <= size() && "Unexpected out-of-bounds iterator");
    return head() + offset;
  }

  CDS_ATTR(2(nodiscard, constexpr(14))) auto loc(ReverseIterator const& it) noexcept -> T* {
    auto offset = it - rbegin();
    assert(offset <= size() && "Unexpected out-of-bounds iterator");
    return tail() - offset;
  }

  CDS_ATTR(2(nodiscard, constexpr(14))) auto loc(ConstReverseIterator const& it) noexcept -> T* {
    auto offset = it - crbegin();
    assert(offset <= size() && "Unexpected out-of-bounds iterator");
    return tail() - offset;
  }

  template <typename N, EnableIf<IsIntegral<N>> = 0>
  CDS_ATTR(2(nodiscard, constexpr(14))) auto loc(N index) noexcept -> T* {
    assert(index <= size() && "Unexpected out-of-bounds index");
    return head() + index;
  }

public:
  using ScalingBase::ScalingBase;
  using ScalingBase::capacity;
  using ScalingBase::clear;
  using ScalingBase::data;
  using ScalingBase::forceShrinkTo;
  using ScalingBase::popBack;
  using ScalingBase::reserve;
  using ScalingBase::shrinkTo;
  using ScalingBase::size;
  using ScalingBase::takeBack;
  using ScalingBase::operator=;

  CDS_ATTR(2(nodiscard, constexpr(14))) auto begin() noexcept -> Iterator {
    return Iterator{head()};
  }

  CDS_ATTR(2(nodiscard, constexpr(14))) auto end() noexcept -> Iterator {
    return Iterator{tail()};
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto begin() const noexcept -> ConstIterator {
    return ConstIterator{head()};
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto end() const noexcept -> ConstIterator {
    return ConstIterator{tail()};
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto cbegin() const noexcept -> ConstIterator {
    return ConstIterator{head()};
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto cend() const noexcept -> ConstIterator {
    return ConstIterator{tail()};
  }

  CDS_ATTR(2(nodiscard, constexpr(14))) auto rbegin() noexcept -> ReverseIterator {
    return ReverseIterator{tail()};
  }

  CDS_ATTR(2(nodiscard, constexpr(14))) auto rend() noexcept -> ReverseIterator {
    return ReverseIterator{head()};
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto rbegin() const noexcept -> ConstReverseIterator {
    return ConstReverseIterator{tail()};
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto rend() const noexcept -> ConstReverseIterator {
    return ConstReverseIterator{head()};
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto crbegin() const noexcept -> ConstReverseIterator {
    return ConstReverseIterator{tail()};
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto crend() const noexcept -> ConstReverseIterator {
    return ConstReverseIterator{head()};
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto empty() const noexcept -> bool {
    return head() == tail();
  }

  CDS_ATTR(2(nodiscard, constexpr(14))) auto front() const noexcept -> Value const& {
    assert(!empty() && "Accessing front element of empty array");
    return *head();
  }

  CDS_ATTR(2(nodiscard, constexpr(14))) auto back() const noexcept -> Value const& {
    assert(!empty() && "Accessing back element of empty array");
    return *(tail() - 1u);
  }

  CDS_ATTR(2(nodiscard, constexpr(14))) auto front() noexcept -> Value& {
    assert(!empty() && "Accessing front element of empty array");
    return *head();
  }

  CDS_ATTR(2(nodiscard, constexpr(14))) auto back() noexcept -> Value& {
    assert(!empty() && "Accessing back element of empty array");
    return *(tail() - 1u);
  }

  CDS_ATTR(2(nodiscard, constexpr(14))) auto operator[](Size index) const noexcept -> Value const& {
    assert(index < size() && "Accessing invalid index of array");
    return head()[index];
  }

  CDS_ATTR(2(nodiscard, constexpr(14))) auto operator[](Size index) noexcept -> Value& {
    assert(index < size() && "Accessing invalid index of array");
    return head()[index];
  }

  CDS_ATTR(2(nodiscard, constexpr(14))) auto at(Size index) const noexcept -> Value const& {
    assert(index < size() && "Accessing invalid index of array");
    return head()[index];
  }

  CDS_ATTR(2(nodiscard, constexpr(14))) auto at(Size index) noexcept -> Value& {
    assert(index < size() && "Accessing invalid index of array");
    return head()[index];
  }

  CDS_ATTR(constexpr(14)) auto forceShrink() noexcept -> void {
    return forceShrinkTo(size());
  }

  template <typename T0 = T, EnableIf<IsDefaultConstructible<T0>> = 0>
  CDS_ATTR(constexpr(20)) auto resize(Size amount) CDS_ATTR(noexcept(noexcept(resizeImpl(amount)))) -> void {
    resizeImpl(amount);
  }

  template <typename T0 = T, EnableIf<IsCopyConstructible<T0>> = 0>
  CDS_ATTR(constexpr(20)) auto resize(Size amount, T const& value)
  CDS_ATTR(noexcept(noexcept(resizeImpl(amount, value)))) -> void {
    resizeImpl(amount, value);
  }

  template <typename Pos, typename... Args> CDS_ATTR(constexpr(20)) auto emplace(Pos&& pos, Args&&... args)
      CDS_ATTR(noexcept(noexcept(makeSpaceAt(1u, nullptr)) && IsNoexceptConstructible<T, Args...>::value)) -> T& {
    return *construct(makeSpaceAt(1u, loc(fwd<Pos>(pos))), fwd<Args>(args)...);
  }

  template <typename Pos, typename I, EnableIf<And<IsInputIterator<I>, IsConstructible<T, decltype(*rvalue<I>())>>> = 0>
  CDS_ATTR(constexpr(20)) auto insert(Pos&& pos, I begin, Size count) CDS_ATTR(noexcept(
      noexcept(makeSpaceAt(count, nullptr)) && IsNoexceptConstructible<T, decltype(*begin)>::value
  )) -> Iterator {
    return Iterator{copyNInitialize(begin, count, makeSpaceAt(count, loc(fwd<Pos>(pos)))) - count};
  }

  template <
      typename Pos, typename I, typename S,
      EnableIf<And<IsForwardIterator<I, S>, IsConstructible<T, decltype(*rvalue<I>())>>> = 0
  > CDS_ATTR(constexpr(20)) auto insert(Pos&& pos, I begin, S end)
      CDS_ATTR(noexcept(noexcept(insert(fwd<Pos>(pos), begin, dist(begin, end))))) -> Iterator {
    return insert(fwd<Pos>(pos), begin, dist(begin, end));
  }

  template <typename Pos, typename T0 = T, EnableIf<IsCopyConstructible<T0>> = 0>
  CDS_ATTR(constexpr(20)) auto insert(Pos&& pos, Size count, T const& value) CDS_ATTR(noexcept(
      noexcept(makeSpaceAt(count, nullptr)) && IsNoexceptCopyConstructible<T>::value
  )) -> Iterator {
    return Iterator{initializeN(makeSpaceAt(count, loc(fwd<Pos>(pos))), count, value) - count};
  }

  template <typename... Args> CDS_ATTR(constexpr(20)) auto emplaceBack(Args&&... args)
      CDS_ATTR(noexcept(noexcept(emplace(end(), fwd<Args>(args)...)))) -> T& {
    return emplace(end(), fwd<Args>(args)...);
  }

  CDS_ATTR(constexpr(20)) auto pushBack(T&& object) CDS_ATTR(noexcept(noexcept(emplace(end(), mv(object))))) -> T& {
    return emplace(end(), mv(object));
  }

  CDS_ATTR(constexpr(20)) auto pushBack(T const& object) CDS_ATTR(noexcept(noexcept(emplace(end(), mv(object)))))
      -> T& {
    return emplace(end(), mv(object));
  }

  template <typename Pos> CDS_ATTR(constexpr(20)) auto remove(Pos&& pos) noexcept -> Iterator {
    return Iterator{eraseRegion(loc(fwd<Pos>(pos)), loc(fwd<Pos>(pos)) + 1)};
  }

  template <typename Pos> CDS_ATTR(constexpr(20)) auto remove(Pos&& begin, Pos&& end) noexcept -> Iterator {
    return Iterator{eraseRegion(loc(fwd<Pos>(begin)), loc(fwd<Pos>(end)))};
  }

  template <typename V, typename P = Identity<>> CDS_ATTR(2(nodiscard, constexpr(14)))
  auto contains(V const& value, P const& projector = Identity<>{}) const noexcept -> bool {
    return impl::findFirst(*this, value, projector, E{}, FindPreserveTransformer<>{}) != end();
  }

  CDS_ATTR(3(nodiscard, explicit, constexpr(11))) operator bool() const noexcept {
    return !empty();
  }
};

template <typename C, typename FT, typename FE, typename FA, typename FSB>
auto operator<<(std::basic_ostream<C>& out, ArrayBase<FT, FE, FA, FSB> const& array)
    CDS_ATTR(noexcept(noexcept(out << rvalue<FT>()))) -> std::basic_ostream<C>& {
  out << static_cast<C>('[');
  auto it = array.begin();
  auto end = array.end();
  if (it == end) {
    out << static_cast<C>(']');
    return out;
  }

  out << *it;
  for (++it; it != end; ++it) {
    out << static_cast<C>(',');
    out << static_cast<C>(' ');
    out << *it;
  }
  out << static_cast<C>(']');
  return out;
}

template <typename T, typename E, typename A0, typename A1, typename S0, typename S1>
CDS_ATTR(2(nodiscard, constexpr(14))) auto operator==(
    ArrayBase<T, E, A0, S0> const& lhs,
    ArrayBase<T, E, A1, S1> const& rhs
) noexcept -> bool {
  if (&lhs == &rhs) {
    return true;
  }

  if (lhs.size() != rhs.size()) {
    return false;
  }

  return equal(lhs.begin(), lhs.end(), rhs.begin(), rhs.end(), E{});
}

template <typename T, typename E, typename A0, typename A1, typename S0, typename S1>
CDS_ATTR(2(nodiscard, constexpr(14))) auto operator!=(
    ArrayBase<T, E, A0, S0> const& lhs,
    ArrayBase<T, E, A1, S1> const& rhs
) noexcept -> bool {
  if (&lhs == &rhs) {
    return false;
  }

  if (lhs.size() != rhs.size()) {
    return true;
  }

  return !equal(lhs.begin(), lhs.end(), rhs.begin(), rhs.end(), E{});
}

template <typename T, typename E, typename A, typename SB>
struct GenericFindEnabledFor<ArrayBase<T, E, A, SB>, T, E> : True {};
} // namespace impl
} // namespace cds

#endif // #ifndef CDS_DS_ARRAY_BASE_HPP
