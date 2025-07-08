//
// Created by loghin on 6/3/25.
//

#ifndef CDS_DS_ARRAY_DYNAMIC_BACK_SCALING_BASE_HPP
#define CDS_DS_ARRAY_DYNAMIC_BACK_SCALING_BASE_HPP
#pragma once

#include <cds/Utility>
#include <cds/meta/IterableTraits>

#include <cassert>
#include <initializer_list>

namespace cds {
namespace impl {
using meta::And;
using meta::IsCopyAssignable;
using meta::IsCopyConstructible;
using meta::IsDefaultConstructible;
using meta::IsInputIterator;
using meta::IsIterable;
using meta::IsMoveConstructible;
using meta::Not;
using meta::rvalue;

using meta::impl::IsBaseOfIntrusiveICVR;
using meta::impl::IsSizeInvocable;

template <typename T, typename /* E */, typename A, typename Traits> class CDS_ATTR(ebo) ArrayDynamicBackScalingBase :
    private A, private Traits {
  using Traits::minCapacity;
  using Traits::scalingMultiplier;

  using A::allocate;
  using A::deallocate;

  template <typename R> using IsSizedRange =
      And<Not<IsBaseOfIntrusiveICVR<ArrayDynamicBackScalingBase, R>>, IsIterable<R>, IsSizeInvocable<R>>;

  template <typename R> using IsNonSizedRange =
      And<Not<IsBaseOfIntrusiveICVR<ArrayDynamicBackScalingBase, R>>, IsIterable<R>, Not<IsSizeInvocable<R>>>;

public:
  CDS_ATTR(2(explicit, constexpr(11))) ArrayDynamicBackScalingBase(A const& alloc)
      CDS_ATTR(noexcept(noexcept(A{alloc}))) : A{alloc} {}

  ArrayDynamicBackScalingBase() = default;

  CDS_ATTR(2(implicit, constexpr(20)))
  ArrayDynamicBackScalingBase(ArrayDynamicBackScalingBase const& base) CDS_ATTR(noexcept(
      noexcept(allocate(len(base)))
      && noexcept(copyInitialize(base._head, base._tail, _head))
  )) :
      A{base},
      _cap{base._head ? maxOf(minCapacity, len(base)) : 0u},
      _head{base._head ? allocate(_cap) : nullptr},
      _tail{copyInitialize(base._head, base._tail, _head)} {}

  CDS_ATTR(2(implicit, constexpr(11))) ArrayDynamicBackScalingBase(ArrayDynamicBackScalingBase&& base) noexcept :
      A{mv(base)},
      _cap{xch(base._cap, 0u)},
      _head{xch(base._head, nullptr)},
      _tail{xch(base._tail, nullptr)} {}

  template <typename I, EnableIf<IsInputIterator<I>> = 0>
  CDS_ATTR(constexpr(20)) ArrayDynamicBackScalingBase(I begin, Size count, A const& alloc = {}) CDS_ATTR(noexcept(
      noexcept(allocate(count)) && noexcept(copyNInitialize(begin, count, _head))
  )) :
      A{alloc},
      _cap{count == 0u ? 0u : maxOf(count, minCapacity)},
      _head{count == 0u ? nullptr : allocate(_cap)},
      _tail{copyNInitialize(begin, count, _head)} {}

  template <typename T0 = T, EnableIf<IsDefaultConstructible<T0>> = 0>
  CDS_ATTR(2(explicit, constexpr(20))) ArrayDynamicBackScalingBase(Size count, A const& alloc = {}) CDS_ATTR(noexcept(
      noexcept(allocate(count)) && noexcept(initialize(_head, _head + count))
  )) :
      A{alloc},
      _cap{count == 0u ? 0u : maxOf(count, minCapacity)},
      _head{count == 0u ? nullptr : allocate(_cap)},
      _tail{initialize(_head, _head + count)} {}

  template <typename T0 = T, EnableIf<IsCopyConstructible<T0>> = 0>
  CDS_ATTR(2(explicit, constexpr(20))) ArrayDynamicBackScalingBase(Size count, T const& value, A const& alloc = {})
      CDS_ATTR(noexcept(noexcept(allocate(count)) && noexcept(initialize(_head, _head + count, value)))) :
      A{alloc},
      _cap{count == 0u ? 0u : maxOf(count, minCapacity)},
      _head{count == 0u ? nullptr : allocate(_cap)},
      _tail{initialize(_head, _head + count, value)} {}

  template <typename I, typename S, EnableIf<IsForwardIterator<I, S>> = 0>
  CDS_ATTR(constexpr(20)) ArrayDynamicBackScalingBase(I begin, S end, A const& alloc = {}) CDS_ATTR(noexcept(
      noexcept(ArrayDynamicBackScalingBase(begin, dist(begin, end), alloc))
  )) : ArrayDynamicBackScalingBase(begin, dist(begin, end), alloc) {}

  template <typename R, EnableIf<IsSizedRange<R>> = 0>
  CDS_ATTR(2(explicit, constexpr(20))) ArrayDynamicBackScalingBase(R&& iterable, A const& alloc = {}) CDS_ATTR(noexcept(
      noexcept(ArrayDynamicBackScalingBase(begin(fwd<R>(iterable)), len(fwd<R>(iterable)), alloc))
  )) : ArrayDynamicBackScalingBase(begin(fwd<R>(iterable)), len(fwd<R>(iterable)), alloc) {}

  template <typename R, EnableIf<IsNonSizedRange<R>> = 0>
  CDS_ATTR(2(explicit, constexpr(20))) ArrayDynamicBackScalingBase(R&& iterable, A const& alloc = {}) CDS_ATTR(noexcept(
      noexcept(ArrayDynamicBackScalingBase(begin(fwd<R>(iterable)), end(fwd<R>(iterable)), alloc))
  )) : ArrayDynamicBackScalingBase(begin(fwd<R>(iterable)), end(fwd<R>(iterable)), alloc) {}

  template <typename T0 = T, EnableIf<IsCopyConstructible<T0>> = 0>
  CDS_ATTR(2(implicit, constexpr(20))) ArrayDynamicBackScalingBase(std::initializer_list<T> const& list, A const& alloc = {})
      CDS_ATTR(noexcept(noexcept(ArrayDynamicBackScalingBase(list.begin(), list.size(), alloc)))) :
      ArrayDynamicBackScalingBase(list.begin(), list.size(), alloc) {}

  template <typename A0 = A, EnableIf<IsCopyAssignable<A0>> = 0>
  CDS_ATTR(constexpr(20)) auto copyAllocator(A const& alloc) CDS_ATTR(noexcept(noexcept(A{alloc}))) -> void {
    A::operator=(alloc);
  }

  template <typename A0 = A, EnableIf<Not<IsCopyAssignable<A0>>> = 0>
  CDS_ATTR(constexpr(20)) static auto copyAllocator(A const& alloc) noexcept -> void {
    ignore = alloc;
  }

  CDS_ATTR(constexpr(20)) auto operator=(ArrayDynamicBackScalingBase const& base) CDS_ATTR(noexcept(
      noexcept(allocate(base._cap)) && noexcept(copyInitialize(base._head, base._tail, _head))
  )) -> ArrayDynamicBackScalingBase& {
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

  CDS_ATTR(constexpr(14)) auto operator=(ArrayDynamicBackScalingBase&& base) noexcept -> ArrayDynamicBackScalingBase& {
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
  )) -> ArrayDynamicBackScalingBase& {
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
  )) -> ArrayDynamicBackScalingBase& {
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
  )) -> ArrayDynamicBackScalingBase& {
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

  CDS_ATTR(constexpr(20)) ~ArrayDynamicBackScalingBase() noexcept {
    clear();
    if (_head) {
      deallocate(_head, _cap);
    }
  }

  CDS_ATTR(constexpr(20)) void clear() {
    destruct(_head, xch(_tail, _head));
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto capacity() const noexcept -> Size {
    return _cap;
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto size() const noexcept -> Size {
    return static_cast<Size>(_tail - _head);
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

    auto const cap = amount;
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
    for (auto head = begin, tail = end; head != _tail; ++head, ++tail) {
      if (head < end) {
        destruct(head);
      }
      if (tail < _tail) {
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
} // namespace impl
} // namespace cds

#endif // #ifndef CDS_DS_ARRAY_DYNAMIC_BACK_SCALING_BASE_HPP
