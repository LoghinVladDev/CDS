//
// Created by loghin on 10/18/24.
//

#ifndef CDS_DS_ARRAY_BASE
#define CDS_DS_ARRAY_BASE

#include <cds/functional/Transformer>

#include <cds/meta/Compiler>
#include <cds/meta/FunctionTraits>
#include <cds/meta/IteratorTraits>

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
using meta::IsCopyAssignable;
using meta::IsCopyConstructible;
using meta::IsDefaultConstructible;
using meta::IsInputIterator;
using meta::IsIntegral;
using meta::IsIterable;
using meta::IsMoveConstructible;
using meta::IsNoexceptConstructible;
using meta::IsNoexceptCopyConstructible;
using meta::IsNoexceptDefaultConstructible;

using meta::impl::IsBaseOfIntrusiveICVR;
using meta::impl::IsSizeInvocable;

using meta::lvalue;
using meta::rvalue;

using functional::impl::Identity;

using iterator::impl::FindPreserveTransformer;

template <typename T> struct ArrayTraits {
  static constexpr Size minCapacity = 32u;
  static constexpr Size scalingMultiplier = 2u;
};

// ODR before cpp17
template <typename T> Size const ArrayTraits<T>::minCapacity;
template <typename T> Size const ArrayTraits<T>::scalingMultiplier;

template <typename T, typename E, typename A, typename Traits> class CDS_ATTR(ebo) NonScalingBase :
    private A, private Traits {};

template <typename T, typename E, typename A, typename Traits> class CDS_ATTR(ebo) DynamicBackScalingBase :
    private A, private Traits {
  using Traits::minCapacity;
  using Traits::scalingMultiplier;

  using A::allocate;
  using A::deallocate;

  template <typename R> using IsSizedRange =
      And<Not<IsBaseOfIntrusiveICVR<DynamicBackScalingBase, R>>, IsIterable<R>, IsSizeInvocable<R>>;

  template <typename R> using IsNonSizedRange =
      And<Not<IsBaseOfIntrusiveICVR<DynamicBackScalingBase, R>>, IsIterable<R>, Not<IsSizeInvocable<R>>>;

public:
  CDS_ATTR(2(explicit, constexpr(11))) DynamicBackScalingBase(A const& alloc)
      CDS_ATTR(noexcept(noexcept(A{alloc}))) : A{alloc} {}

  DynamicBackScalingBase() = default;

  CDS_ATTR(2(implicit, constexpr(20))) DynamicBackScalingBase(DynamicBackScalingBase const& base) CDS_ATTR(noexcept(
      noexcept(allocate(len(base)))
      && noexcept(copyInitialize(base._head, base._tail, _head))
  )) :
      A{base},
      _cap{base._head ? maxOf(minCapacity, len(base)) : 0u},
      _head{base._head ? allocate(_cap) : nullptr},
      _tail{copyInitialize(base._head, base._tail, _head)} {}

  CDS_ATTR(2(implicit, constexpr(11))) DynamicBackScalingBase(DynamicBackScalingBase&& base) noexcept :
      A{mv(base)},
      _cap{xch(base._cap, 0u)},
      _head{xch(base._head, nullptr)},
      _tail{xch(base._tail, nullptr)} {}

  template <typename I, EnableIf<IsInputIterator<I>> = 0>
  CDS_ATTR(constexpr(20)) DynamicBackScalingBase(I begin, Size count, A const& alloc = {}) CDS_ATTR(noexcept(
      noexcept(allocate(count)) && noexcept(copyNInitialize(begin, count, _head))
  )) :
      A{alloc},
      _cap{count == 0u ? 0u : maxOf(count, minCapacity)},
      _head{count == 0u ? nullptr : allocate(_cap)},
      _tail{copyNInitialize(begin, count, _head)} {}

  template <typename T0 = T, EnableIf<IsDefaultConstructible<T0>> = 0>
  CDS_ATTR(2(explicit, constexpr(20))) DynamicBackScalingBase(Size count, A const& alloc = {}) CDS_ATTR(noexcept(
      noexcept(allocate(count)) && noexcept(initialize(_head, _head + count))
  )) :
      A{alloc},
      _cap{count == 0u ? 0u : maxOf(count, minCapacity)},
      _head{count == 0u ? nullptr : allocate(_cap)},
      _tail{initialize(_head, _head + count)} {}

  template <typename T0 = T, EnableIf<IsCopyConstructible<T0>> = 0>
  CDS_ATTR(2(explicit, constexpr(20))) DynamicBackScalingBase(Size count, T const& value, A const& alloc = {})
      CDS_ATTR(noexcept(noexcept(allocate(count)) && noexcept(initialize(_head, _head + count, value)))) :
      A{alloc},
      _cap{count == 0u ? 0u : maxOf(count, minCapacity)},
      _head{count == 0u ? nullptr : allocate(_cap)},
      _tail{initialize(_head, _head + count, value)} {}

  template <typename I, typename S, EnableIf<IsForwardIterator<I, S>> = 0>
  CDS_ATTR(constexpr(20)) DynamicBackScalingBase(I begin, S end, A const& alloc = {}) CDS_ATTR(noexcept(
      noexcept(DynamicBackScalingBase(begin, dist(begin, end), alloc))
  )) : DynamicBackScalingBase(begin, dist(begin, end), alloc) {}

  template <typename R, EnableIf<IsSizedRange<R>> = 0>
  CDS_ATTR(2(explicit, constexpr(20))) DynamicBackScalingBase(R&& iterable, A const& alloc = {}) CDS_ATTR(noexcept(
      noexcept(DynamicBackScalingBase(begin(fwd<R>(iterable)), len(fwd<R>(iterable)), alloc))
  )) : DynamicBackScalingBase(begin(fwd<R>(iterable)), len(fwd<R>(iterable)), alloc) {}

  template <typename R, EnableIf<IsNonSizedRange<R>> = 0>
  CDS_ATTR(2(explicit, constexpr(20))) DynamicBackScalingBase(R&& iterable, A const& alloc = {}) CDS_ATTR(noexcept(
      noexcept(DynamicBackScalingBase(begin(fwd<R>(iterable)), end(fwd<R>(iterable)), alloc))
  )) : DynamicBackScalingBase(begin(fwd<R>(iterable)), end(fwd<R>(iterable)), alloc) {}

  template <typename T0 = T, EnableIf<IsCopyConstructible<T0>> = 0>
  CDS_ATTR(2(implicit, constexpr(20))) DynamicBackScalingBase(std::initializer_list<T> const& list, A const& alloc = {})
      CDS_ATTR(noexcept(noexcept(DynamicBackScalingBase(list.begin(), list.size(), alloc)))) :
      DynamicBackScalingBase(list.begin(), list.size(), alloc) {}

  template <typename A0 = A, EnableIf<IsCopyAssignable<A0>> = 0>
  CDS_ATTR(constexpr(20)) auto copyAllocator(A const& alloc) CDS_ATTR(noexcept(noexcept(A{alloc}))) -> void {
    A::operator=(alloc);
  }

  template <typename A0 = A, EnableIf<Not<IsCopyAssignable<A0>>> = 0>
  CDS_ATTR(constexpr(20)) auto copyAllocator(A const& alloc) noexcept -> void {
    ignore = alloc;
  }

  CDS_ATTR(constexpr(20)) auto operator=(DynamicBackScalingBase const& base) CDS_ATTR(noexcept(
      noexcept(allocate(base._cap)) && noexcept(copyInitialize(base._head, base._tail, _head))
  )) -> DynamicBackScalingBase& {
    if (this == &base) {
      return *this;
    }

    clear();
    auto const reqLen = len(base);
    if (_cap < reqLen) {
      if (_head) {
        deallocate(_head, _cap);
      }
      copyAllocator(base);
      _cap = maxOf(minCapacity, reqLen);
      _head = allocate(_cap);
    } else {
      copyAllocator(base);
    }
    _tail = copyInitialize(base._head, base._tail, _head);
    return *this;
  }

  CDS_ATTR(constexpr(14)) auto operator=(DynamicBackScalingBase&& base) noexcept -> DynamicBackScalingBase& {
    if (this == &base) {
      return *this;
    }

    clear();
    if (_head) {
      deallocate(_head, _cap);
    }
    A::operator=(mv(base));

    _cap = xch(base._cap, 0u);
    _head = xch(base._head, nullptr);
    _tail = xch(base._tail, nullptr);
    return *this;
  }

  template <typename R, EnableIf<IsSizedRange<R>> = 0>
  CDS_ATTR(constexpr(20)) auto operator=(R&& iterable) CDS_ATTR(noexcept(
      noexcept(allocate(len(fwd<R>(iterable))))
      && noexcept(copyNInitialize(begin(fwd<R>(iterable)), len(fwd<R>(iterable)), _head))
  )) -> DynamicBackScalingBase& {
    auto const reqSize = len(fwd<R>(iterable));
    clear();
    if (_cap < reqSize) {
      if (_head) {
        deallocate(_head, _cap);
      }
      _cap = maxOf(reqSize, minCapacity);
      _head = allocate(_cap);
    }
    _tail = copyNInitialize(begin(fwd<R>(iterable)), reqSize, _head);
    return *this;
  }

  template <typename R, EnableIf<IsNonSizedRange<R>> = 0>
  CDS_ATTR(constexpr(20)) auto operator=(R&& iterable) CDS_ATTR(noexcept(
      noexcept(allocate(rvalue<Size>()))
      && noexcept(copyInitialize(begin(fwd<R>(iterable)), end(fwd<R>(iterable)), _head))
  )) -> DynamicBackScalingBase& {
    auto const b = begin(fwd<R>(iterable));
    auto const e = end(fwd<R>(iterable));
    auto const reqSize = dist(b, e);
    clear();
    if (_cap < reqSize) {
      if (_head) {
        deallocate(_head, _cap);
      }
      _cap = maxOf(reqSize, minCapacity);
      _head = allocate(_cap);
    }
    _tail = copyInitialize(b, e, _head);
    return *this;
  }

  template <typename T0 = T, EnableIf<IsCopyConstructible<T0>> = 0>
  CDS_ATTR(constexpr(20)) auto operator=(std::initializer_list<T> const& list) CDS_ATTR(noexcept(
      noexcept(allocate(rvalue<Size>()))
      && noexcept(copyNInitialize(list.begin(), list.size(), _head))
  )) -> DynamicBackScalingBase& {
    auto const reqSize = list.size();
    clear();
    if (_cap < reqSize) {
      if (_head) {
        deallocate(_head, _cap);
      }
      _cap = maxOf(reqSize, minCapacity);
      _head = allocate(_cap);
    }
    _tail = copyNInitialize(list.begin(), reqSize, _head);
    return *this;
  }

  CDS_ATTR(constexpr(20)) ~DynamicBackScalingBase() noexcept {
    clear();
    if (_head) {
      deallocate(_head, _cap);
    }
  }

  void clear() {
    destruct(_head, _tail);
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto capacity() const noexcept -> Size {
    return _cap;
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto size() const noexcept -> Size {
    return _tail - _head;
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto data() const noexcept -> T const* {
    return _head;
  }

  CDS_ATTR(2(nodiscard, constexpr(14))) auto data() noexcept -> T* {
    return _head;
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto head() const noexcept -> T const* {
    return _head;
  }

  CDS_ATTR(2(nodiscard, constexpr(14))) auto head() noexcept -> T* {
    return _head;
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto tail() const noexcept -> T const* {
    return _tail;
  }

  CDS_ATTR(2(nodiscard, constexpr(14))) auto tail() noexcept -> T* {
    return _tail;
  }

  CDS_ATTR(constexpr(14)) auto popBack() noexcept -> void {
    assert(_head <= _tail && "Popping empty array");
    destruct(--_tail);
  }

  template <typename T0 = T, EnableIf<IsMoveConstructible<T0>> = 0>
  CDS_ATTR(constexpr(14)) auto takeBack() noexcept -> T {
    assert(_head <= _tail && "Popping empty array");
    T e{mv(*--_tail)};
    destruct(_tail);
    return e;
  }

  CDS_ATTR(constexpr(20)) auto reserve(Size amount) CDS_ATTR(noexcept(noexcept(allocate(amount)))) -> void {
    if (_cap >= amount) {
      return;
    }

    auto cap = maxOf(minCapacity, amount);
    auto head = allocate(cap);
    auto tail = moveInitialize(_head, _tail, head);
    destruct(_head, xch(_tail, tail));
    if (_head) {
      deallocate(_head, _cap);
    }
    _head = head;
    _cap = cap;
  }

  CDS_ATTR(constexpr(14)) auto shrinkTo(Size amount) noexcept -> void {
    if (!_head) {
      return;
    }

    for (auto newTail = _head + amount; newTail < _tail;) {
      destruct(--_tail);
    }
  }

  CDS_ATTR(constexpr(20)) auto forceShrinkTo(Size amount) CDS_ATTR(noexcept(noexcept(allocate(amount)))) -> void {
    shrinkTo(amount);
    if (amount >= _cap) {
      return;
    }

    auto cap = amount;
    auto head = allocate(amount);
    auto tail = moveInitialize(_head, _tail, head);
    destruct(_head, xch(_tail, tail));
    if (_head) {
      deallocate(_head, _cap);
    }
    _head = head;
    _cap = cap;
  }

  template <typename... Args> CDS_ATTR(constexpr(20)) auto resizeImpl(Size amount, Args&&... args) CDS_ATTR(noexcept(
      noexcept(allocate(amount)) && noexcept(initialize(_head, _tail, fwd<Args>(args)...))
  )) -> void {
    shrinkTo(amount);
    if (amount > _cap) {
      auto cap = amount;
      auto head = allocate(cap);
      auto tail = moveInitialize(_head, _tail, head);
      destruct(_head, xch(_tail, tail));
      if (_head) {
        deallocate(_head, _cap);
      }
      _head = head;
      _cap = cap;
    }

    for (auto newTail = _head + amount; _tail < newTail;) {
      construct(_tail++, fwd<Args>(args)...);
    }
  }

  CDS_ATTR(constexpr(20)) auto makeSpaceAt(Size amount, T* at) CDS_ATTR(noexcept(noexcept(allocate(amount)))) -> T* {
    auto const l = size();
    if (l + amount <= _cap) {
      auto src = _tail;
      auto dst = _tail + amount;

      if (src > _tail) {
        auto diff = src - _tail;
        src -= diff;
        dst -= diff;
      }

      while (src > at) {
        if (--dst < _tail) {
          destruct(dst);
        }
        construct(dst, mv(*--src));
        destruct(src);
      }
      _tail += amount;
      return at;
    }

    auto cap = maxOf(minCapacity, _cap * 2, l + amount);
    auto head = allocate(cap);
    auto returned = moveInitialize(_head, at, head);
    auto tail = moveInitialize(at, _tail, returned + amount);
    destruct(_head, xch(_tail, tail));
    if (_head) {
      deallocate(_head, _cap);
    }
    _head = head;
    _cap = cap;
    return returned;
  }

  CDS_ATTR(constexpr(20)) auto eraseRegion(T* begin, T* end) noexcept -> T* {
    assert(_head <= begin && end <= _tail && begin <= end);
    for (auto head = begin, tail = end; head != end; ++head, ++tail) {
      destruct(head);
      if (tail < end) {
        construct(head, mv(*tail));
      }
    }

    _tail -= end - begin;
    return begin;
  }

private:
  Size _cap {0u};
  T* _head {nullptr};
  T* _tail {nullptr};
};

template <typename, typename, typename A, typename Traits>
class CDS_ATTR(ebo) DynamicBidirectionalScalingBase : private A, private Traits {};

template <typename T, typename E, typename, typename ScalingBase>
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

template <typename T, typename E, typename A, typename SB>
struct GenericFindEnabledFor<ArrayBase<T, E, A, SB>, T, E> : True {};
} // namespace impl
} // namespace cds

#endif // #ifndef CDS_DS_ARRAY_BASE
