//
// Created by vloghin on 19.12.2024.
//

#ifndef CDS_THREADING_ATOMIC_ATOMIC_C11_HPP
#define CDS_THREADING_ATOMIC_ATOMIC_C11_HPP
#pragma once

#include <stdatomic.h>
#include <cds/meta/StdLib>

namespace cds {
namespace impl {
using meta::And;
using meta::Bool;
using meta::False;
using meta::IsCopyConstructible;
using meta::IsCopyAssignable;
using meta::IsIntegral;
using meta::IsMoveConstructible;
using meta::IsMoveAssignable;
using meta::IsNoexceptDefaultConstructible;
using meta::IsTriviallyCopyable;
using meta::IsSame;
using meta::Or;
using meta::RemoveConstVolatile;
using meta::True;
using meta::UnderlyingType;

using meta::rvalue;

enum class AtomicMemoryOrder : UnderlyingType<memory_order> {
  Relaxed = static_cast<UnderlyingType<memory_order>>(memory_order_relaxed),
  Consume = static_cast<UnderlyingType<memory_order>>(memory_order_consume),
  Acquire = static_cast<UnderlyingType<memory_order>>(memory_order_acquire),
  Release = static_cast<UnderlyingType<memory_order>>(memory_order_release),
  AcqRel = static_cast<UnderlyingType<memory_order>>(memory_order_acq_rel),
  SeqCst = static_cast<UnderlyingType<memory_order>>(memory_order_seq_cst),
  AcquireRelease = AcqRel,
  SequentiallyConsistent = SeqCst,
};

class BaseAtomicFlag {
public:
#if CDS_ATTR(libcxx)
  CDS_ATTR(inline) BaseAtomicFlag() noexcept : _flag ATOMIC_FLAG_INIT {}
#else
  CDS_ATTR(inline) BaseAtomicFlag() noexcept : _flag{ATOMIC_FLAG_INIT} {}
#endif
  ~BaseAtomicFlag() = default;

  BaseAtomicFlag(BaseAtomicFlag const&) = delete;
  BaseAtomicFlag(BaseAtomicFlag&&) = delete;
  auto operator=(BaseAtomicFlag const&) -> BaseAtomicFlag& = delete;
  auto operator=(BaseAtomicFlag&&) -> BaseAtomicFlag& = delete;

  CDS_ATTR(inline) auto clear(AtomicMemoryOrder order = AtomicMemoryOrder::SequentiallyConsistent) noexcept -> void {
    atomic_flag_clear_explicit(&_flag, static_cast<memory_order>(order));
  }

  CDS_ATTR(inline) auto clear(AtomicMemoryOrder order = AtomicMemoryOrder::SequentiallyConsistent)
      volatile noexcept -> void {
    atomic_flag_clear_explicit(&_flag, static_cast<memory_order>(order));
  }

  CDS_ATTR(2(nodiscard, inline)) auto testAndSet(AtomicMemoryOrder order = AtomicMemoryOrder::SequentiallyConsistent)
      noexcept -> bool {
    return atomic_flag_test_and_set_explicit(&_flag, static_cast<memory_order>(order));
  }

  CDS_ATTR(2(nodiscard, inline)) auto testAndSet(AtomicMemoryOrder order = AtomicMemoryOrder::SequentiallyConsistent)
      volatile noexcept -> bool {
    return atomic_flag_test_and_set_explicit(&_flag, static_cast<memory_order>(order));
  }

private:
  atomic_flag _flag;
};

template <typename> struct IsAtomicLockFree : False {};

template <> struct IsAtomicLockFree<char> : Bool<ATOMIC_CHAR_LOCK_FREE == 2u> {};
template <> struct IsAtomicLockFree<unsigned char> : Bool<ATOMIC_CHAR_LOCK_FREE == 2u> {};
template <> struct IsAtomicLockFree<signed char> : Bool<ATOMIC_CHAR_LOCK_FREE == 2u> {};

template <> struct IsAtomicLockFree<wchar_t> : Bool<ATOMIC_WCHAR_T_LOCK_FREE == 2u> {};
template <> struct IsAtomicLockFree<char16_t> : Bool<ATOMIC_CHAR16_T_LOCK_FREE == 2u> {};
template <> struct IsAtomicLockFree<char32_t> : Bool<ATOMIC_CHAR32_T_LOCK_FREE == 2u> {};

#if defined(ATOMIC_CHAR8_T_LOCK_FREE) && CDS_ATTR(cpp20)
template <> struct IsAtomicLockFree<char8_t> : Bool<ATOMIC_CHAR8_T_LOCK_FREE == 2u> {};
#endif

template <> struct IsAtomicLockFree<unsigned short> : Bool<ATOMIC_SHORT_LOCK_FREE == 2u> {};
template <> struct IsAtomicLockFree<signed short> : Bool<ATOMIC_SHORT_LOCK_FREE == 2u> {};

template <> struct IsAtomicLockFree<unsigned int> : Bool<ATOMIC_INT_LOCK_FREE == 2u> {};
template <> struct IsAtomicLockFree<signed int> : Bool<ATOMIC_INT_LOCK_FREE == 2u> {};

template <> struct IsAtomicLockFree<unsigned long> : Bool<ATOMIC_LONG_LOCK_FREE == 2u> {};
template <> struct IsAtomicLockFree<signed long> : Bool<ATOMIC_LONG_LOCK_FREE == 2u> {};

template <> struct IsAtomicLockFree<unsigned long long> : Bool<ATOMIC_LLONG_LOCK_FREE == 2u> {};
template <> struct IsAtomicLockFree<signed long long> : Bool<ATOMIC_LLONG_LOCK_FREE == 2u> {};

template <> struct IsAtomicLockFree<bool> : Bool<ATOMIC_BOOL_LOCK_FREE == 2u> {};

struct IsAtomicPtrLockFree : Bool<ATOMIC_POINTER_LOCK_FREE == 2u> {};

template <
    typename T,
    typename = typename Or<IsIntegral<T>, IsSame<T, bool>>::Type,
    typename = typename IsAtomicLockFree<T>::Type
> class BaseAtomic;

template <typename T> class BaseAtomic<T, False, True> {
  /* Not Integral, Lock Free */

  static_assert(And<
      IsTriviallyCopyable<T>, IsCopyConstructible<T>, IsMoveConstructible<T>,
      IsCopyAssignable<T>, IsMoveAssignable<T>, IsSame<T, RemoveConstVolatile<T>>
  >::value, "Requirements for atomic not satisfied");

public:
  using IsAlwaysLockFree = True;

  CDS_ATTR(inline) BaseAtomic() CDS_ATTR(noexcept(IsNoexceptDefaultConstructible<T>::value)) : _obj{T()} {}

  CDS_ATTR(2(implicit, inline)) BaseAtomic(T value) noexcept : _obj{value} {}

  BaseAtomic(BaseAtomic const&) = delete;
  ~BaseAtomic() = default;

  CDS_ATTR(inline) auto operator=(T value) noexcept -> T {
    atomic_store(&_obj, value);
    return value;
  }

  CDS_ATTR(inline) auto operator=(T value) volatile noexcept -> T {
    atomic_store(&_obj, value);
    return value;
  }

  auto operator=(BaseAtomic const&) -> BaseAtomic& = delete;
  auto operator=(BaseAtomic const&) volatile -> BaseAtomic& = delete;

  CDS_ATTR(2(nodiscard, inline)) auto isLockFree() const noexcept -> bool {
    return atomic_is_lock_free(&_obj);
  }

  CDS_ATTR(2(nodiscard, inline)) auto isLockFree() const volatile noexcept -> bool {
    return atomic_is_lock_free(&_obj);
  }

  CDS_ATTR(inline) auto store(T value, AtomicMemoryOrder order = AtomicMemoryOrder::SequentiallyConsistent)
      const noexcept -> void {
    return atomic_store_explicit(&_obj, value, static_cast<memory_order>(order));
  }

  CDS_ATTR(inline) auto store(T value, AtomicMemoryOrder order = AtomicMemoryOrder::SequentiallyConsistent)
      const volatile noexcept -> void {
    return atomic_store_explicit(&_obj, value, static_cast<memory_order>(order));
  }

  CDS_ATTR(2(nodiscard, inline)) auto load(AtomicMemoryOrder order = AtomicMemoryOrder::SequentiallyConsistent)
      const noexcept -> T {
    return atomic_load_explicit(&_obj, static_cast<memory_order>(order));
  }

  CDS_ATTR(2(nodiscard, inline)) auto load(AtomicMemoryOrder order = AtomicMemoryOrder::SequentiallyConsistent)
      const volatile noexcept -> T {
    return atomic_load_explicit(&_obj, static_cast<memory_order>(order));
  }

  CDS_ATTR(2(nodiscard, inline)) auto exchange(
      T value, AtomicMemoryOrder order = AtomicMemoryOrder::SequentiallyConsistent
  ) const noexcept -> T {
    return atomic_exchange_explicit(&_obj, value, static_cast<memory_order>(order));
  }

  CDS_ATTR(2(nodiscard, inline)) auto exchange(
      T value, AtomicMemoryOrder order = AtomicMemoryOrder::SequentiallyConsistent
  ) const volatile noexcept -> T {
    return atomic_exchange_explicit(&_obj, value, static_cast<memory_order>(order));
  }

  CDS_ATTR(2(nodiscard, inline)) auto compareExchangeWeak(
      T& expected, T desired, AtomicMemoryOrder order = AtomicMemoryOrder::SequentiallyConsistent
  ) const noexcept -> bool {
    return atomic_compare_exchange_weak_explicit(
        &_obj, &expected, desired,
        static_cast<memory_order>(order), static_cast<memory_order>(order)
    );
  }

  CDS_ATTR(2(nodiscard, inline)) auto compareExchangeWeak(
      T& expected, T desired, AtomicMemoryOrder order = AtomicMemoryOrder::SequentiallyConsistent
  ) const volatile noexcept -> bool {
    return atomic_compare_exchange_weak_explicit(
        &_obj, &expected, desired,
        static_cast<memory_order>(order), static_cast<memory_order>(order)
    );
  }

  CDS_ATTR(2(nodiscard, inline)) auto compareExchangeWeak(
      T& expected, T desired, AtomicMemoryOrder success, AtomicMemoryOrder failure
  ) const noexcept -> bool {
    return atomic_compare_exchange_weak_explicit(
        &_obj, &expected, desired,
        static_cast<memory_order>(success), static_cast<memory_order>(failure)
    );
  }

  CDS_ATTR(2(nodiscard, inline)) auto compareExchangeWeak(
      T& expected, T desired, AtomicMemoryOrder success, AtomicMemoryOrder failure
  ) const volatile noexcept -> bool {
    return atomic_compare_exchange_weak_explicit(
        &_obj, &expected, desired,
        static_cast<memory_order>(success), static_cast<memory_order>(failure)
    );
  }

  CDS_ATTR(2(nodiscard, inline)) auto compareExchangeStrong(
      T& expected, T desired, AtomicMemoryOrder order = AtomicMemoryOrder::SequentiallyConsistent
  ) const noexcept -> bool {
    return atomic_compare_exchange_strong_explicit(
        &_obj, &expected, desired,
        static_cast<memory_order>(order), static_cast<memory_order>(order)
    );
  }

  CDS_ATTR(2(nodiscard, inline)) auto compareExchangeStrong(
      T& expected, T desired, AtomicMemoryOrder order = AtomicMemoryOrder::SequentiallyConsistent
  ) const volatile noexcept -> bool {
    return atomic_compare_exchange_strong_explicit(
        &_obj, &expected, desired,
        static_cast<memory_order>(order), static_cast<memory_order>(order)
    );
  }

  CDS_ATTR(2(nodiscard, inline)) auto compareExchangeStrong(
      T& expected, T desired, AtomicMemoryOrder success, AtomicMemoryOrder failure
  ) const noexcept -> bool {
    return atomic_compare_exchange_strong_explicit(
        &_obj, &expected, desired,
        static_cast<memory_order>(success), static_cast<memory_order>(failure)
    );
  }

  CDS_ATTR(2(nodiscard, inline)) auto compareExchangeStrong(
      T& expected, T desired, AtomicMemoryOrder success, AtomicMemoryOrder failure
  ) const volatile noexcept -> bool {
    return atomic_compare_exchange_strong_explicit(
        &_obj, &expected, desired,
        static_cast<memory_order>(success), static_cast<memory_order>(failure)
    );
  }

protected:
  _Atomic(T) _obj;
};

template <typename T> class BaseAtomic<T, False, False> : public BaseAtomic<T, False, True> {
  /* Not Integral, Not Lock Free */
  using Base = BaseAtomic<T, False, True>;

public:
  using IsAlwaysLockFree = False;

  using Base::Base;
  using Base::operator=;

  CDS_ATTR(2(deprecated("Atomic type is not lock free, use an explicit operation instead"), inline))
  auto operator=(T value) noexcept -> T {
    return Base::operator=(value);
  }

  CDS_ATTR(2(deprecated("Atomic type is not lock free, use an explicit operation instead"), inline))
  auto operator=(T value) volatile noexcept -> T {
    return Base::operator=(value);
  }
};

template <typename T> class BaseAtomic<T, True, True> : public BaseAtomic<T, False, True> {
  /* Integral, Lock Free */
  using Base = BaseAtomic<T, False, True>;

public:
  using IsAlwaysLockFree = typename Base::IsAlwaysLockFree;
  using Base::Base;
  using Base::operator=;
  using Base::_obj;

  CDS_ATTR(inline) auto fetchAdd(T value, AtomicMemoryOrder order = AtomicMemoryOrder::SequentiallyConsistent)
      noexcept -> T {
    return atomic_fetch_add_explicit(&_obj, value, static_cast<memory_order>(order));
  }

  CDS_ATTR(inline) auto fetchAdd(T value, AtomicMemoryOrder order = AtomicMemoryOrder::SequentiallyConsistent)
      volatile noexcept -> T {
    return atomic_fetch_add_explicit(&_obj, value, static_cast<memory_order>(order));
  }

  CDS_ATTR(inline) auto fetchSub(T value, AtomicMemoryOrder order = AtomicMemoryOrder::SequentiallyConsistent)
      noexcept -> T {
    return atomic_fetch_sub_explicit(&_obj, value, static_cast<memory_order>(order));
  }

  CDS_ATTR(inline) auto fetchSub(T value, AtomicMemoryOrder order = AtomicMemoryOrder::SequentiallyConsistent)
      volatile noexcept -> T {
    return atomic_fetch_sub_explicit(&_obj, value, static_cast<memory_order>(order));
  }

  CDS_ATTR(inline) auto fetchAnd(T value, AtomicMemoryOrder order = AtomicMemoryOrder::SequentiallyConsistent)
      noexcept -> T {
    return atomic_fetch_and_explicit(&_obj, value, static_cast<memory_order>(order));
  }

  CDS_ATTR(inline) auto fetchAnd(T value, AtomicMemoryOrder order = AtomicMemoryOrder::SequentiallyConsistent)
      volatile noexcept -> T {
    return atomic_fetch_and_explicit(&_obj, value, static_cast<memory_order>(order));
  }

  CDS_ATTR(inline) auto fetchOr(T value, AtomicMemoryOrder order = AtomicMemoryOrder::SequentiallyConsistent)
      noexcept -> T {
    return atomic_fetch_or_explicit(&_obj, value, static_cast<memory_order>(order));
  }

  CDS_ATTR(inline) auto fetchOr(T value, AtomicMemoryOrder order = AtomicMemoryOrder::SequentiallyConsistent)
      volatile noexcept -> T {
    return atomic_fetch_or_explicit(&_obj, value, static_cast<memory_order>(order));
  }

  CDS_ATTR(inline) auto fetchXor(T value, AtomicMemoryOrder order = AtomicMemoryOrder::SequentiallyConsistent)
      noexcept -> T {
    return atomic_fetch_xor_explicit(&_obj, value, static_cast<memory_order>(order));
  }

  CDS_ATTR(inline) auto fetchXor(T value, AtomicMemoryOrder order = AtomicMemoryOrder::SequentiallyConsistent)
      volatile noexcept -> T {
    return atomic_fetch_xor_explicit(&_obj, value, static_cast<memory_order>(order));
  }

  CDS_ATTR(inline) auto operator++() noexcept -> T {
    return 1 + atomic_fetch_add(&_obj, 1);
  }

  CDS_ATTR(inline) auto operator++(int) noexcept -> T {
    return atomic_fetch_add(&_obj, 1);
  }

  CDS_ATTR(inline) auto operator--() noexcept -> T {
    return atomic_fetch_sub(&_obj, 1) - 1;
  }

  CDS_ATTR(inline) auto operator--(int) noexcept -> T {
    return atomic_fetch_sub(&_obj, 1);
  }

  CDS_ATTR(inline) auto operator++() volatile noexcept -> T {
    return 1 + atomic_fetch_add(&_obj, 1);
  }

  CDS_ATTR(inline) auto operator++(int) volatile noexcept -> T {
    return atomic_fetch_add(&_obj, 1);
  }

  CDS_ATTR(inline) auto operator--() volatile noexcept -> T {
    return atomic_fetch_sub(&_obj, 1) - 1;
  }

  CDS_ATTR(inline) auto operator--(int) volatile noexcept -> T {
    return atomic_fetch_sub(&_obj, 1);
  }

  CDS_ATTR(inline) auto operator+=(T value) noexcept -> T {
    return atomic_fetch_add(&_obj, value);
  }

  CDS_ATTR(inline) auto operator+=(T value) volatile noexcept -> T {
    return atomic_fetch_add(&_obj, value);
  }

  CDS_ATTR(inline) auto operator-=(T value) noexcept -> T {
    return atomic_fetch_sub(&_obj, value);
  }

  CDS_ATTR(inline) auto operator-=(T value) volatile noexcept -> T {
    return atomic_fetch_sub(&_obj, value);
  }

  CDS_ATTR(inline) auto operator&=(T value) noexcept -> T {
    return atomic_fetch_and(&_obj, value);
  }

  CDS_ATTR(inline) auto operator&=(T value) volatile noexcept -> T {
    return atomic_fetch_and(&_obj, value);
  }

  CDS_ATTR(inline) auto operator|=(T value) noexcept -> T {
    return atomic_fetch_or(&_obj, value);
  }

  CDS_ATTR(inline) auto operator|=(T value) volatile noexcept -> T {
    return atomic_fetch_or(&_obj, value);
  }

  CDS_ATTR(inline) auto operator^=(T value) noexcept -> T {
    return atomic_fetch_xor(&_obj, value);
  }

  CDS_ATTR(inline) auto operator^=(T value) volatile noexcept -> T {
    return atomic_fetch_xor(&_obj, value);
  }
};

template <typename T> class BaseAtomic<T, True, False> : public BaseAtomic<T, True, True> {
  /* Integral, Not Lock Free */
  using Base = BaseAtomic<T, False, True>;

public:
  using IsAlwaysLockFree = typename Base::IsAlwaysLockFree;
  using Base::Base;
  using Base::operator=;
  using Base::_obj;

  CDS_ATTR(2(deprecated("Atomic type is not lock free, use an explicit operation instead"), inline))
  auto operator++() noexcept -> T {
    return Base::operator++();
  }

  CDS_ATTR(2(deprecated("Atomic type is not lock free, use an explicit operation instead"), inline))
  auto operator++(int ph) noexcept -> T {
    return Base::operator++(ph);
  }

  CDS_ATTR(2(deprecated("Atomic type is not lock free, use an explicit operation instead"), inline))
  auto operator--() noexcept -> T {
    return Base::operator--();
  }

  CDS_ATTR(2(deprecated("Atomic type is not lock free, use an explicit operation instead"), inline))
  auto operator--(int ph) noexcept -> T {
    return Base::operator--(ph);
  }

  CDS_ATTR(2(deprecated("Atomic type is not lock free, use an explicit operation instead"), inline))
  auto operator++() volatile noexcept -> T {
    return Base::operator++();
  }

  CDS_ATTR(2(deprecated("Atomic type is not lock free, use an explicit operation instead"), inline))
  auto operator++(int ph) volatile noexcept -> T {
    return Base::operator++(ph);
  }

  CDS_ATTR(2(deprecated("Atomic type is not lock free, use an explicit operation instead"), inline))
  auto operator--() volatile noexcept -> T {
    return Base::operator--();
  }

  CDS_ATTR(2(deprecated("Atomic type is not lock free, use an explicit operation instead"), inline))
  auto operator--(int ph) volatile noexcept -> T {
    return Base::operator--(ph);
  }

  CDS_ATTR(2(deprecated("Atomic type is not lock free, use an explicit operation instead"), inline))
  auto operator+=(T value) noexcept -> T {
    return Base::operator+=(value);
  }

  CDS_ATTR(2(deprecated("Atomic type is not lock free, use an explicit operation instead"), inline))
  auto operator+=(T value) volatile noexcept -> T {
    return Base::operator+=(value);
  }

  CDS_ATTR(2(deprecated("Atomic type is not lock free, use an explicit operation instead"), inline))
  auto operator-=(T value) noexcept -> T {
    return Base::operator-=(value);
  }

  CDS_ATTR(2(deprecated("Atomic type is not lock free, use an explicit operation instead"), inline))
  auto operator-=(T value) volatile noexcept -> T {
    return Base::operator-=(value);
  }

  CDS_ATTR(2(deprecated("Atomic type is not lock free, use an explicit operation instead"), inline))
  auto operator&=(T value) noexcept -> T {
    return Base::operator&=(value);
  }

  CDS_ATTR(2(deprecated("Atomic type is not lock free, use an explicit operation instead"), inline))
  auto operator&=(T value) volatile noexcept -> T {
    return Base::operator&=(value);
  }

  CDS_ATTR(2(deprecated("Atomic type is not lock free, use an explicit operation instead"), inline))
  auto operator|=(T value) noexcept -> T {
    return Base::operator|=(value);
  }

  CDS_ATTR(2(deprecated("Atomic type is not lock free, use an explicit operation instead"), inline))
  auto operator|=(T value) volatile noexcept -> T {
    return Base::operator|=(value);
  }

  CDS_ATTR(2(deprecated("Atomic type is not lock free, use an explicit operation instead"), inline))
  auto operator^=(T value) noexcept -> T {
    return Base::operator^=(value);
  }

  CDS_ATTR(2(deprecated("Atomic type is not lock free, use an explicit operation instead"), inline))
  auto operator^=(T value) volatile noexcept -> T {
    return Base::operator^=(value);
  }
};

template <typename T, typename = typename IsAtomicPtrLockFree::Type> class BaseAtomicPtr;
template <typename T> class BaseAtomicPtr<T, True> {
  /* Pointer, Lock Free */
public:

  using IsAlwaysLockFree = True;
  using DiffType = decltype(rvalue<T*>() - rvalue<T*>());

  CDS_ATTR(inline) BaseAtomicPtr() noexcept : _obj{T()} {}

  CDS_ATTR(2(implicit, inline)) BaseAtomicPtr(T* value) noexcept : _obj{value} {}

  BaseAtomicPtr(BaseAtomicPtr const&) = delete;
  ~BaseAtomicPtr() = default;

  CDS_ATTR(inline) auto operator=(T* value) noexcept -> T* {
    atomic_store(&_obj, value);
    return value;
  }

  CDS_ATTR(inline) auto operator=(T* value) volatile noexcept -> T* {
    atomic_store(&_obj, value);
    return value;
  }

  auto operator=(BaseAtomicPtr const&) -> BaseAtomicPtr& = delete;
  auto operator=(BaseAtomicPtr const&) volatile -> BaseAtomicPtr& = delete;

  CDS_ATTR(2(nodiscard, inline)) auto isLockFree() const noexcept -> bool {
    return atomic_is_lock_free(&_obj);
  }

  CDS_ATTR(2(nodiscard, inline)) auto isLockFree() const volatile noexcept -> bool {
    return atomic_is_lock_free(&_obj);
  }

  CDS_ATTR(inline) auto store(T* value, AtomicMemoryOrder order = AtomicMemoryOrder::SequentiallyConsistent)
      const noexcept -> void {
    return atomic_store_explicit(&_obj, value, static_cast<memory_order>(order));
  }

  CDS_ATTR(inline) auto store(T* value, AtomicMemoryOrder order = AtomicMemoryOrder::SequentiallyConsistent)
      const volatile noexcept -> void {
    return atomic_store_explicit(&_obj, value, static_cast<memory_order>(order));
  }

  CDS_ATTR(2(nodiscard, inline)) auto load(AtomicMemoryOrder order = AtomicMemoryOrder::SequentiallyConsistent)
      const noexcept -> T* {
    return atomic_load_explicit(&_obj, static_cast<memory_order>(order));
  }

  CDS_ATTR(2(nodiscard, inline)) auto load(AtomicMemoryOrder order = AtomicMemoryOrder::SequentiallyConsistent)
      const volatile noexcept -> T* {
    return atomic_load_explicit(&_obj, static_cast<memory_order>(order));
  }

  CDS_ATTR(2(nodiscard, inline)) auto exchange(
      T* value, AtomicMemoryOrder order = AtomicMemoryOrder::SequentiallyConsistent
  ) const noexcept -> T* {
    return atomic_exchange_explicit(&_obj, value, static_cast<memory_order>(order));
  }

  CDS_ATTR(2(nodiscard, inline)) auto exchange(
      T* value, AtomicMemoryOrder order = AtomicMemoryOrder::SequentiallyConsistent
  ) const volatile noexcept -> T* {
    return atomic_exchange_explicit(&_obj, value, static_cast<memory_order>(order));
  }

  CDS_ATTR(2(nodiscard, inline)) auto compareExchangeWeak(
      T*& expected, T* desired, AtomicMemoryOrder order = AtomicMemoryOrder::SequentiallyConsistent
  ) const noexcept -> bool {
    return atomic_compare_exchange_weak_explicit(
        &_obj, &expected, desired,
        static_cast<memory_order>(order), static_cast<memory_order>(order)
    );
  }

  CDS_ATTR(2(nodiscard, inline)) auto compareExchangeWeak(
      T*& expected, T* desired, AtomicMemoryOrder order = AtomicMemoryOrder::SequentiallyConsistent
  ) const volatile noexcept -> bool {
    return atomic_compare_exchange_weak_explicit(
        &_obj, &expected, desired,
        static_cast<memory_order>(order), static_cast<memory_order>(order)
    );
  }

  CDS_ATTR(2(nodiscard, inline)) auto compareExchangeWeak(
      T*& expected, T* desired, AtomicMemoryOrder success, AtomicMemoryOrder failure
  ) const noexcept -> bool {
    return atomic_compare_exchange_weak_explicit(
        &_obj, &expected, desired,
        static_cast<memory_order>(success), static_cast<memory_order>(failure)
    );
  }

  CDS_ATTR(2(nodiscard, inline)) auto compareExchangeWeak(
      T*& expected, T* desired, AtomicMemoryOrder success, AtomicMemoryOrder failure
  ) const volatile noexcept -> bool {
    return atomic_compare_exchange_weak_explicit(
        &_obj, &expected, desired,
        static_cast<memory_order>(success), static_cast<memory_order>(failure)
    );
  }

  CDS_ATTR(2(nodiscard, inline)) auto compareExchangeStrong(
      T*& expected, T* desired, AtomicMemoryOrder order = AtomicMemoryOrder::SequentiallyConsistent
  ) const noexcept -> bool {
    return atomic_compare_exchange_strong_explicit(
        &_obj, &expected, desired,
        static_cast<memory_order>(order), static_cast<memory_order>(order)
    );
  }

  CDS_ATTR(2(nodiscard, inline)) auto compareExchangeStrong(
      T*& expected, T* desired, AtomicMemoryOrder order = AtomicMemoryOrder::SequentiallyConsistent
  ) const volatile noexcept -> bool {
    return atomic_compare_exchange_strong_explicit(
        &_obj, &expected, desired,
        static_cast<memory_order>(order), static_cast<memory_order>(order)
    );
  }

  CDS_ATTR(2(nodiscard, inline)) auto compareExchangeStrong(
      T*& expected, T* desired, AtomicMemoryOrder success, AtomicMemoryOrder failure
  ) const noexcept -> bool {
    return atomic_compare_exchange_strong_explicit(
        &_obj, &expected, desired,
        static_cast<memory_order>(success), static_cast<memory_order>(failure)
    );
  }

  CDS_ATTR(2(nodiscard, inline)) auto compareExchangeStrong(
      T*& expected, T* desired, AtomicMemoryOrder success, AtomicMemoryOrder failure
  ) const volatile noexcept -> bool {
    return atomic_compare_exchange_strong_explicit(
        &_obj, &expected, desired,
        static_cast<memory_order>(success), static_cast<memory_order>(failure)
    );
  }

  CDS_ATTR(inline) auto fetchAdd(DiffType value, AtomicMemoryOrder order = AtomicMemoryOrder::SequentiallyConsistent)
      noexcept -> T* {
    return atomic_fetch_add_explicit(&_obj, value, static_cast<memory_order>(order));
  }

  CDS_ATTR(inline) auto fetchAdd(DiffType value, AtomicMemoryOrder order = AtomicMemoryOrder::SequentiallyConsistent)
      volatile noexcept -> T* {
    return atomic_fetch_add_explicit(&_obj, value, static_cast<memory_order>(order));
  }

  CDS_ATTR(inline) auto fetchSub(DiffType value, AtomicMemoryOrder order = AtomicMemoryOrder::SequentiallyConsistent)
      noexcept -> T* {
    return atomic_fetch_sub_explicit(&_obj, value, static_cast<memory_order>(order));
  }

  CDS_ATTR(inline) auto fetchSub(DiffType value, AtomicMemoryOrder order = AtomicMemoryOrder::SequentiallyConsistent)
      volatile noexcept -> T* {
    return atomic_fetch_sub_explicit(&_obj, value, static_cast<memory_order>(order));
  }

  CDS_ATTR(inline) auto operator++() noexcept -> T* {
    return atomic_fetch_add(&_obj, 1) + 1;
  }

  CDS_ATTR(inline) auto operator++(int) noexcept -> T* {
    return atomic_fetch_add(&_obj, 1);
  }

  CDS_ATTR(inline) auto operator--() noexcept -> T* {
    return atomic_fetch_sub(&_obj, 1) - 1;
  }

  CDS_ATTR(inline) auto operator--(int) noexcept -> T* {
    return atomic_fetch_sub(&_obj, 1);
  }

  CDS_ATTR(inline) auto operator++() volatile noexcept -> T* {
    return atomic_fetch_add(&_obj, 1) + 1;
  }

  CDS_ATTR(inline) auto operator++(int) volatile noexcept -> T* {
    return atomic_fetch_add(&_obj, 1);
  }

  CDS_ATTR(inline) auto operator--() volatile noexcept -> T* {
    return atomic_fetch_sub(&_obj, 1) - 1;
  }

  CDS_ATTR(inline) auto operator--(int) volatile noexcept -> T* {
    return atomic_fetch_sub(&_obj, 1);
  }

  CDS_ATTR(inline) auto operator+=(DiffType value) noexcept -> T* {
    return atomic_fetch_add(&_obj, value);
  }

  CDS_ATTR(inline) auto operator+=(DiffType value) volatile noexcept -> T* {
    return atomic_fetch_add(&_obj, value);
  }

  CDS_ATTR(inline) auto operator-=(DiffType value) noexcept -> T* {
    return atomic_fetch_sub(&_obj, value);
  }

  CDS_ATTR(inline) auto operator-=(DiffType value) volatile noexcept -> T* {
    return atomic_fetch_sub(&_obj, value);
  }

protected:
  _Atomic(T*) _obj;
};

template <typename T> class BaseAtomicPtr<T, False> : public BaseAtomicPtr<T, True> {
  /* Pointer, Not Lock Free */
  using Base = BaseAtomicPtr<T, True>;

public:
  using IsAlwaysLockFree = typename Base::IsAlwaysLockFree;
  using DiffType = typename Base::DiffType;
  using Base::Base;
  using Base::operator=;
  using Base::_obj;

  CDS_ATTR(2(deprecated("Atomic type is not lock free, use an explicit operation instead"), inline))
  auto operator=(T* value) noexcept -> T* {
    return Base::operator=(value);
  }

  CDS_ATTR(2(deprecated("Atomic type is not lock free, use an explicit operation instead"), inline))
  auto operator=(T* value) volatile noexcept -> T* {
    return Base::operator=(value);
  }

  CDS_ATTR(2(deprecated("Atomic type is not lock free, use an explicit operation instead"), inline))
  auto operator++() noexcept -> T* {
    return Base::operator++();
  }

  CDS_ATTR(2(deprecated("Atomic type is not lock free, use an explicit operation instead"), inline))
  auto operator++(int ph) noexcept -> T* {
    return Base::operator++(ph);
  }

  CDS_ATTR(2(deprecated("Atomic type is not lock free, use an explicit operation instead"), inline))
  auto operator--() noexcept -> T* {
    return Base::operator--();
  }

  CDS_ATTR(2(deprecated("Atomic type is not lock free, use an explicit operation instead"), inline))
  auto operator--(int ph) noexcept -> T* {
    return Base::operator--(ph);
  }

  CDS_ATTR(2(deprecated("Atomic type is not lock free, use an explicit operation instead"), inline))
  auto operator++() volatile noexcept -> T* {
    return Base::operator++();
  }

  CDS_ATTR(2(deprecated("Atomic type is not lock free, use an explicit operation instead"), inline))
  auto operator++(int ph) volatile noexcept -> T* {
    return Base::operator++(ph);
  }

  CDS_ATTR(2(deprecated("Atomic type is not lock free, use an explicit operation instead"), inline))
  auto operator--() volatile noexcept -> T* {
    return Base::operator--();
  }

  CDS_ATTR(2(deprecated("Atomic type is not lock free, use an explicit operation instead"), inline))
  auto operator--(int ph) volatile noexcept -> T* {
    return Base::operator--(ph);
  }

  CDS_ATTR(2(deprecated("Atomic type is not lock free, use an explicit operation instead"), inline))
  auto operator+=(T value) noexcept -> T* {
    return Base::operator+=(value);
  }

  CDS_ATTR(2(deprecated("Atomic type is not lock free, use an explicit operation instead"), inline))
  auto operator+=(T value) volatile noexcept -> T* {
    return Base::operator+=(value);
  }

  CDS_ATTR(2(deprecated("Atomic type is not lock free, use an explicit operation instead"), inline))
  auto operator-=(T value) noexcept -> T* {
    return Base::operator-=(value);
  }

  CDS_ATTR(2(deprecated("Atomic type is not lock free, use an explicit operation instead"), inline))
  auto operator-=(T value) volatile noexcept -> T* {
    return Base::operator-=(value);
  }
};
} // namespace impl
} // namespace cds

#endif // #ifndef CDS_THREADING_ATOMIC_ATOMIC_C11_HPP
