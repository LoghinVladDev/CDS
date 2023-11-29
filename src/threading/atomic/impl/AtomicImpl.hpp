// NOLINT(llvm-header-guard)
// Created by loghin on 23/10/22.
//

#ifndef __CDS_ATOMIC_IMPL_HPP__ // NOLINT(llvm-header-guard)
#define __CDS_ATOMIC_IMPL_HPP__ // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
#pragma once

namespace cds {
inline auto AtomicFlag::clear() noexcept -> void {
#if __CDS_atomic_flag_implementation == __CDS_atomic_flag_stl_atomic_flag_implementation
  _atomicFlag.clear();
#elif __CDS_atomic_flag_implementation == __CDS_atomic_flag_stl_atomic_implementation
  _atomicFlag.store(false);
#endif
}

inline auto AtomicFlag::clear(AtomicMemoryOrder order) noexcept -> void {
#if __CDS_atomic_flag_implementation == __CDS_atomic_flag_stl_atomic_flag_implementation
  _atomicFlag.clear(static_cast<std::memory_order>(order));
#elif __CDS_atomic_flag_implementation == __CDS_atomic_flag_stl_atomic_implementation
  _atomicFlag.store(false, static_cast<std::memory_order>(order));
#endif

}

inline auto AtomicFlag::set() noexcept -> bool {
#if __CDS_atomic_flag_implementation == __CDS_atomic_flag_stl_atomic_flag_implementation
  return _atomicFlag.test_and_set();
#elif __CDS_atomic_flag_implementation == __CDS_atomic_flag_stl_atomic_implementation
  return _atomicFlag.exchange(true);
#endif
}

inline auto AtomicFlag::set(AtomicMemoryOrder order) noexcept -> bool {
#if __CDS_atomic_flag_implementation == __CDS_atomic_flag_stl_atomic_flag_implementation
  return _atomicFlag.test_and_set(static_cast<std::memory_order>(order));
#elif __CDS_atomic_flag_implementation == __CDS_atomic_flag_stl_atomic_implementation
  return _atomicFlag.exchange(true, static_cast<std::memory_order>(order));
#endif
}

inline auto AtomicFlag::get() const noexcept -> bool {
#if __CDS_atomic_flag_implementation == __CDS_atomic_flag_stl_atomic_flag_implementation
  return _atomicFlag.test();
#elif __CDS_atomic_flag_implementation == __CDS_atomic_flag_stl_atomic_implementation
  return _atomicFlag.load();
#endif
}

inline auto AtomicFlag::get(AtomicMemoryOrder order) const noexcept -> bool {
#if __CDS_atomic_flag_implementation == __CDS_atomic_flag_stl_atomic_flag_implementation
  return _atomicFlag.test(static_cast<std::memory_order>(order));
#elif __CDS_atomic_flag_implementation == __CDS_atomic_flag_stl_atomic_implementation
  return _atomicFlag.load(static_cast<std::memory_order>(order));
#endif
}

inline AtomicFlag::operator bool() const noexcept {
  return get();
}

inline auto AtomicFlag::toString() const noexcept -> String {
  return get() ? "true" : "false";
}

inline auto AtomicFlag::hash() const noexcept -> Size {
  return reinterpret_cast<AddressValueType>(&_atomicFlag);   // NOLINT(clion-misra-cpp2008-5-2-8, *-reinterpret-cast, clion-misra-cpp2008-5-2-5, clion-misra-cpp2008-5-2-9)
}

inline auto AtomicFlag::equals(Object const& object) const noexcept -> bool {
  if (this == &object) {
    return true;
  }

  auto const* pAtomicFlag = dynamic_cast<decltype(this)>(&object);
  if (pAtomicFlag == nullptr) {
    return false;
  }

  return pAtomicFlag->get() == get();
}

inline auto AtomicFlag::toString(AtomicMemoryOrder order) const noexcept -> String {
  return get(order) ? "true" : "false";
}

inline auto AtomicFlag::equals(Object const& object, AtomicMemoryOrder order) const noexcept -> bool {
  if (this == &object) {
    return true;
  }

  auto const* pAtomicFlag = dynamic_cast<decltype(this)>(&object);
  if (pAtomicFlag == nullptr) {
    return false;
  }

  return pAtomicFlag->get(order) == get(order);
}

template <typename __Type> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_NonConstConstexprMemberFunction Atomic<__Type>::Atomic(Atomic const& atomic) noexcept {
  set(atomic.get());
}

template <typename __Type> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_NonConstConstexprMemberFunction Atomic<__Type>::Atomic(
    Atomic const&     atomic,
    AtomicMemoryOrder order
) noexcept {
  set(atomic.get(order), order);
}

template <typename __Type> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_NonConstConstexprMemberFunction Atomic<__Type>::Atomic(
    Atomic const&     atomic,
    AtomicMemoryOrder loadOrder,
    AtomicMemoryOrder storeOrder
) noexcept {
  set(atomic.get(loadOrder),storeOrder);
}

template <typename __Type> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_NonConstConstexprMemberFunction Atomic<__Type>::Atomic(__Type value) noexcept {
  set(value);
}

template <typename __Type> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_NonConstConstexprMemberFunction Atomic<__Type>::Atomic(
    __Type            value,
    AtomicMemoryOrder order
) noexcept {
  set(value, order);
}

template <typename __Type> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_NonConstConstexprMemberFunction auto Atomic<__Type>::operator=(Atomic const& atomic) noexcept -> Atomic& {
  if (this == &atomic) {
    return *this;
  }

  set(atomic.get());
  return *this;
}

template <typename __Type> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_NonConstConstexprMemberFunction auto Atomic<__Type>::operator=(__Type value) noexcept -> Atomic& {
  set(value);
  return * this;
}

template <typename __Type> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
constexpr auto Atomic<__Type>::get() const noexcept -> __Type {
  return _data.load();
}

template <typename __Type> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
constexpr auto Atomic<__Type>::get(AtomicMemoryOrder order) const noexcept -> __Type {
  return _data.load(static_cast<std::memory_order>(order));
}

template <typename __Type> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_NonConstConstexprMemberFunction auto Atomic<__Type>::set(__Type value) noexcept -> void {
  _data.store(value);
}

template <typename __Type> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_NonConstConstexprMemberFunction auto Atomic<__Type>::set(
    __Type            value,
    AtomicMemoryOrder order
) noexcept -> void {
  _data.store(value, static_cast<std::memory_order>(order));
}

template <typename __Type> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
constexpr Atomic<__Type>::operator __Type() const noexcept {
  return get();
}

template <typename __Type> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_NonConstConstexprMemberFunction auto Atomic<__Type>::exchange(__Type value) noexcept -> __Type {
  return _data.exchange(value);
}

template <typename __Type> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_NonConstConstexprMemberFunction auto Atomic<__Type>::exchange(
    __Type            value,
    AtomicMemoryOrder order
) noexcept -> __Type {
  return _data.exchange(value, static_cast<std::memory_order>(order));
}

template <typename __Type> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_NonConstConstexprMemberFunction auto Atomic<__Type>::compareExchangeWeak(
    __Type& expected,
    __Type  desired
) noexcept -> bool {
  return _data.compare_exchange_weak(expected, desired);
}

template <typename __Type> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_NonConstConstexprMemberFunction auto Atomic<__Type>::compareExchangeWeak(
    __Type&           expected,
    __Type            desired,
    AtomicMemoryOrder order
) noexcept -> bool {
  return _data.compare_exchange_weak(
      expected,
      desired,
      static_cast<std::memory_order>(order)
  );
}

template <typename __Type> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_NonConstConstexprMemberFunction auto Atomic<__Type>::compareExchangeWeak(
    __Type&           expected,
    __Type            desired,
    AtomicMemoryOrder success,
    AtomicMemoryOrder failure
) noexcept -> bool {
  return _data.compare_exchange_weak(
      expected,
      desired,
      static_cast<std::memory_order>(success),
      static_cast<std::memory_order>(failure)
  );
}

template <typename __Type> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_NonConstConstexprMemberFunction auto Atomic<__Type>::compareExchangeStrong(
    __Type& expected,
    __Type  desired
) noexcept -> bool {
  return _data.compare_exchange_strong(expected, desired);
}

template <typename __Type> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_NonConstConstexprMemberFunction auto Atomic<__Type>::compareExchangeStrong(
    __Type&           expected,
    __Type            desired,
    AtomicMemoryOrder order
) noexcept -> bool {
  return _data.compare_exchange_strong(
      expected,
      desired,
      static_cast<std::memory_order>(order)
  );
}

template <typename __Type> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_NonConstConstexprMemberFunction auto Atomic<__Type>::compareExchangeStrong(
    __Type&           expected,
    __Type            desired,
    AtomicMemoryOrder success,
    AtomicMemoryOrder failure
) noexcept -> bool {
  return _data.compare_exchange_strong(
      expected,
      desired,
      static_cast<std::memory_order>(success),
      static_cast<std::memory_order>(failure)
  );
}

template <typename __Type> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_NonConstConstexprMemberFunction auto Atomic<__Type>::getThenAdd(__Type value) noexcept -> __Type {
  return std::atomic_fetch_add(&_data, value);
}

template <typename __Type> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_NonConstConstexprMemberFunction auto Atomic<__Type>::getThenAdd(
    __Type            value,
    AtomicMemoryOrder order
) noexcept -> __Type {
  return std::atomic_fetch_add_explicit(
      &_data,
      value,
      static_cast<std::memory_order>(order)
  );
}

template <typename __Type> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_NonConstConstexprMemberFunction auto Atomic<__Type>::getThenSubtract(__Type value) noexcept -> __Type {
  return std::atomic_fetch_sub(&_data, value);
}

template <typename __Type> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_NonConstConstexprMemberFunction auto Atomic<__Type>::getThenSubtract(
    __Type            value,
    AtomicMemoryOrder order
) noexcept -> __Type {
  return std::atomic_fetch_sub_explicit(
      &_data,
      value,
      static_cast<std::memory_order>(order)
  );
}

template <typename __Type> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename T, meta::EnableIfC<meta::IsIntegral<T>>>
__CDS_cpplang_NonConstConstexprMemberFunction auto Atomic<__Type>::getThenBitwiseAnd(__Type value) noexcept -> __Type {
  return std::atomic_fetch_and(&_data, value);
}


template <typename __Type> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename T, meta::EnableIfC<meta::IsIntegral<T>>>
__CDS_cpplang_NonConstConstexprMemberFunction auto Atomic<__Type>::getThenBitwiseAnd(
    __Type            value,
    AtomicMemoryOrder order
) noexcept -> __Type {
  return std::atomic_fetch_and_explicit(
      &_data,
      value,
      static_cast<std::memory_order>(order)
  );
}

template <typename __Type> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename T, meta::EnableIfC<meta::IsIntegral<T>>>
__CDS_cpplang_NonConstConstexprMemberFunction auto Atomic<__Type>::getThenBitwiseOr(__Type value) noexcept -> __Type {
  return std::atomic_fetch_or(&_data, value);
}

template <typename __Type> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename T, meta::EnableIfC<meta::IsIntegral<T>>>
__CDS_cpplang_NonConstConstexprMemberFunction auto Atomic<__Type>::getThenBitwiseOr(
    __Type            value,
    AtomicMemoryOrder order
) noexcept -> __Type {
  return std::atomic_fetch_or_explicit(
      &_data,
      value,
      static_cast<std::memory_order>(order)
  );
}

template <typename __Type> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename T, meta::EnableIfC<meta::IsIntegral<T>>>
__CDS_cpplang_NonConstConstexprMemberFunction auto Atomic<__Type>::getThenBitwiseXor(__Type value) noexcept -> __Type {
  return std::atomic_fetch_xor(&_data, value);
}

template <typename __Type> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename T, meta::EnableIfC<meta::IsIntegral<T>>>
__CDS_cpplang_NonConstConstexprMemberFunction auto Atomic<__Type>::getThenBitwiseXor(
    __Type            value,
    AtomicMemoryOrder order
) noexcept -> __Type {
  return std::atomic_fetch_xor_explicit(
      &_data,
      value,
      static_cast<std::memory_order>(order)
  );
}

template <typename __Type> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename T, meta::EnableIfC<meta::Or<meta::IsIntegral<T>, meta::IsBasicPointer<T>>>>
__CDS_cpplang_NonConstConstexprMemberFunction auto Atomic<__Type>::operator++() noexcept -> __Type {
  return std::atomic_fetch_add(&_data, 1) + 1;
}

template <typename __Type> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename T, meta::EnableIfC<meta::Or<meta::IsIntegral<T>, meta::IsBasicPointer<T>>>>
__CDS_cpplang_NonConstConstexprMemberFunction auto Atomic<__Type>::operator++(int) noexcept -> __Type {
  return std::atomic_fetch_add(&_data, 1);
}

template <typename __Type> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename T, meta::EnableIfC<meta::Or<meta::IsIntegral<T>, meta::IsBasicPointer<T>>>>
__CDS_cpplang_NonConstConstexprMemberFunction auto Atomic<__Type>::operator--() noexcept -> __Type {
  return std::atomic_fetch_sub(&_data, 1) + 1;
}

template <typename __Type> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename T, meta::EnableIfC<meta::Or<meta::IsIntegral<T>, meta::IsBasicPointer<T>>>>
__CDS_cpplang_NonConstConstexprMemberFunction auto Atomic<__Type>::operator--(int) noexcept -> __Type {
  return std::atomic_fetch_sub(&_data, 1);
}

template <typename __Type> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_NonConstConstexprMemberFunction auto Atomic<__Type>::operator+=(__Type value) noexcept -> __Type {
  return std::atomic_fetch_add(&_data, value) + value;
}

template <typename __Type> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_NonConstConstexprMemberFunction auto Atomic<__Type>::operator-=(__Type value) noexcept -> __Type {
  return std::atomic_fetch_sub(&_data, value) - value;
}

template <typename __Type> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename T, meta::EnableIfC<meta::IsIntegral<T>>>
__CDS_cpplang_NonConstConstexprMemberFunction auto Atomic<__Type>::operator&=(__Type value) noexcept -> __Type {
  return std::atomic_fetch_and(&_data, value) & value;
}

template <typename __Type> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename T, meta::EnableIfC<meta::IsIntegral<T>>>
__CDS_cpplang_NonConstConstexprMemberFunction auto Atomic<__Type>::operator|=(__Type value) noexcept -> __Type {
  return std::atomic_fetch_or(&_data, value) | value;
}

template <typename __Type> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename T, meta::EnableIfC<meta::IsIntegral<T>>>
__CDS_cpplang_NonConstConstexprMemberFunction auto Atomic<__Type>::operator^=(__Type value) noexcept -> __Type {
  return std::atomic_fetch_xor(&_data, value) ^ value;
}

template <typename __Type> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_ConstexprOverride auto Atomic<__Type>::hash() const noexcept -> Size {
  return (AddressValueType)get();
}

template <typename __Type> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_ConstexprOverride auto Atomic<__Type>::hash(AtomicMemoryOrder order) const noexcept -> Size {
  return (AddressValueType)get(order);
}

template <typename __Type> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
inline auto Atomic<__Type>::toString() const noexcept -> String {
  return get();
}

template <typename __Type> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
inline auto Atomic<__Type>::toString(AtomicMemoryOrder order) const noexcept -> String {
  return get(order);
}

template <typename __Type> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
inline auto Atomic<__Type>::equals(Object const& object) const noexcept -> bool {
  if (this == &object) {
    return true;
  }

  auto const* pAtomic = dynamic_cast<decltype(this)>(&object); // NOLINT(clion-misra-cpp2008-5-2-8, *-reinterpret-cast, clion-misra-cpp2008-5-2-5, clion-misra-cpp2008-5-2-9)
  if (pAtomic == nullptr) {
    return false;
  }

  return get() == pAtomic->get();
}

template <typename __Type> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
inline auto Atomic<__Type>::equals(Object const& object, AtomicMemoryOrder order) const noexcept -> bool {
  if (this == &object) {
    return true;
  }

  auto const* pAtomic = dynamic_cast<decltype(this)>(&object);   // NOLINT(clion-misra-cpp2008-5-2-8, *-reinterpret-cast, clion-misra-cpp2008-5-2-5, clion-misra-cpp2008-5-2-9)
  if (pAtomic == nullptr) {
    return false;
  }

  return get(order) == pAtomic->get(order);
}

#if __CDS_atomic_ref_implementation != __CDS_atomic_ref_unavailable
template <typename __Type> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
constexpr AtomicReference<__Type>::AtomicReference(__Type& value) noexcept :
#if __CDS_atomic_ref_implementation == __CDS_atomic_ref_stl_atomic_ref_implementation
    _data(value)
#endif
{}

template <typename __Type> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
constexpr AtomicReference<__Type>::AtomicReference(AtomicReference const& atomic) noexcept :
#if __CDS_atomic_ref_implementation == __CDS_atomic_ref_stl_atomic_ref_implementation
    _data(atomic._data)
#endif
{}

template <typename __Type> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_NonConstConstexprMemberFunction auto AtomicReference<__Type>::operator=(__Type& value) noexcept -> AtomicReference& {
  _data = value;
  return* this;
}

template <typename __Type> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
constexpr auto AtomicReference<__Type>::get() const noexcept -> __Type {
  return _data.load();
}

template <typename __Type> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
constexpr auto AtomicReference<__Type>::get(AtomicMemoryOrder order) const noexcept -> __Type {
  return _data.load(static_cast<std::memory_order>(order));
}

template <typename __Type> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_NonConstConstexprMemberFunction auto AtomicReference<__Type>::set(__Type value) noexcept -> void {
  _data.store(value);
}

template <typename __Type> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_NonConstConstexprMemberFunction auto AtomicReference<__Type>::set(
    __Type            value,
    AtomicMemoryOrder order
) noexcept -> void {
  _data.store(value, static_cast<std::memory_order>(order));
}

template <typename __Type> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
constexpr AtomicReference<__Type>::operator __Type() const noexcept {
  return get();
}

template <typename __Type> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_NonConstConstexprMemberFunction auto AtomicReference<__Type>::exchange(
    __Type value
) noexcept -> __Type {
  return _data.exchange(value);
}

template <typename __Type> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_NonConstConstexprMemberFunction auto AtomicReference<__Type>::exchange(
    __Type            value,
    AtomicMemoryOrder order
) noexcept -> __Type {
  return _data.exchange(value, static_cast<std::memory_order>(order));
}

template <typename __Type> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_NonConstConstexprMemberFunction auto AtomicReference<__Type>::compareExchangeWeak(
    __Type& expected,
    __Type  desired
) noexcept -> bool {
  return _data.compare_exchange_weak(expected, desired);
}

template <typename __Type> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_NonConstConstexprMemberFunction auto AtomicReference<__Type>::compareExchangeWeak(
    __Type&           expected,
    __Type            desired,
    AtomicMemoryOrder order
) noexcept -> bool {
  return _data.compare_exchange_weak(
      expected,
      desired,
      static_cast<std::memory_order>(order)
  );
}

template <typename __Type> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_NonConstConstexprMemberFunction auto AtomicReference<__Type>::compareExchangeWeak(
    __Type&           expected,
    __Type            desired,
    AtomicMemoryOrder success,
    AtomicMemoryOrder failure
) noexcept -> bool {
  return _data.compare_exchange_weak(
      expected,
      desired,
      static_cast<std::memory_order>(success),
      static_cast<std::memory_order>(failure)
  );
}

template <typename __Type> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_NonConstConstexprMemberFunction auto AtomicReference<__Type>::compareExchangeStrong(
    __Type& expected,
    __Type  desired
) noexcept -> bool {
  return _data.compare_exchange_strong(expected, desired);
}

template <typename __Type> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_NonConstConstexprMemberFunction auto AtomicReference<__Type>::compareExchangeStrong(
    __Type&           expected,
    __Type            desired,
    AtomicMemoryOrder order
) noexcept -> bool {
  return _data.compare_exchange_strong(
      expected,
      desired,
      static_cast<std::memory_order>(order)
  );
}

template <typename __Type> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_NonConstConstexprMemberFunction auto AtomicReference<__Type>::compareExchangeStrong(
    __Type&           expected,
    __Type            desired,
    AtomicMemoryOrder success,
    AtomicMemoryOrder failure
) noexcept -> bool {
  return _data.compare_exchange_strong(
      expected,
      desired,
      static_cast<std::memory_order>(success),
      static_cast<std::memory_order>(failure)
  );
}

template <typename __Type> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_NonConstConstexprMemberFunction auto AtomicReference<__Type>::getThenAdd(__Type value) noexcept -> __Type {
  return std::atomic_fetch_add(&_data, value);
}

template <typename __Type> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_NonConstConstexprMemberFunction auto AtomicReference<__Type>::getThenAdd(
    __Type            value,
    AtomicMemoryOrder order
) noexcept -> __Type {
  return std::atomic_fetch_add_explicit(
      &_data,
      value,
      static_cast<std::memory_order>(order)
  );
}

template <typename __Type> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_NonConstConstexprMemberFunction auto AtomicReference<__Type>::getThenSubtract(__Type value) noexcept -> __Type {
  return std::atomic_fetch_sub(&_data, value);
}

template <typename __Type> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_NonConstConstexprMemberFunction auto AtomicReference<__Type>::getThenSubtract(
    __Type            value,
    AtomicMemoryOrder order
) noexcept -> __Type {
  return std::atomic_fetch_sub_explicit(
      &_data,
      value,
      static_cast<std::memory_order>(order)
  );
}

template <typename __Type> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename T, meta::EnableIfC<meta::IsIntegral<T>>>
__CDS_cpplang_NonConstConstexprMemberFunction auto AtomicReference<__Type>::getThenBitwiseAnd(__Type value) noexcept -> __Type {
  return std::atomic_fetch_and(&_data, value);
}

template <typename __Type> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename T, meta::EnableIfC<meta::IsIntegral<T>>>
__CDS_cpplang_NonConstConstexprMemberFunction auto AtomicReference<__Type>::getThenBitwiseAnd(
    __Type            value,
    AtomicMemoryOrder order
) noexcept -> __Type {
  return std::atomic_fetch_and_explicit(
      &_data,
      value,
      static_cast<std::memory_order>(order)
  );
}

template <typename __Type> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename T, meta::EnableIfC<meta::IsIntegral<T>>>
__CDS_cpplang_NonConstConstexprMemberFunction auto AtomicReference<__Type>::getThenBitwiseOr(
    __Type value
) noexcept -> __Type {
  return std::atomic_fetch_or(&_data, value);
}

template <typename __Type> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename T, meta::EnableIfC<meta::IsIntegral<T>>>
__CDS_cpplang_NonConstConstexprMemberFunction auto AtomicReference<__Type>::getThenBitwiseOr(
    __Type            value,
    AtomicMemoryOrder order
) noexcept -> __Type {
  return std::atomic_fetch_or_explicit(
      &_data,
      value,
      static_cast<std::memory_order>(order)
  );
}

template <typename __Type> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename T, meta::EnableIfC<meta::IsIntegral<T>>>
__CDS_cpplang_NonConstConstexprMemberFunction auto AtomicReference<__Type>::getThenBitwiseXor(__Type value) noexcept -> __Type {
  return std::atomic_fetch_xor(&_data, value);
}

template <typename __Type> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename T, meta::EnableIfC<meta::IsIntegral<T>>>
__CDS_cpplang_NonConstConstexprMemberFunction auto AtomicReference<__Type>::getThenBitwiseXor(
    __Type            value,
    AtomicMemoryOrder order
) noexcept -> __Type {
  return std::atomic_fetch_xor_explicit(
      &_data,
      value,
      static_cast<std::memory_order>(order)
  );
}

template <typename __Type> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename T, meta::EnableIfC<meta::Or<meta::IsIntegral<T>, meta::IsBasicPointer<T>>>>
__CDS_cpplang_NonConstConstexprMemberFunction auto AtomicReference<__Type>::operator++() noexcept -> __Type {
  return std::atomic_fetch_add(&_data, 1) + 1;
}

template <typename __Type> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename T, meta::EnableIfC<meta::Or<meta::IsIntegral<T>, meta::IsBasicPointer<T>>>>
__CDS_cpplang_NonConstConstexprMemberFunction auto AtomicReference<__Type>::operator++(int) noexcept -> __Type {
  return std::atomic_fetch_add(&_data, 1);
}

template <typename __Type> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename T, meta::EnableIfC<meta::Or<meta::IsIntegral<T>, meta::IsBasicPointer<T>>>>
__CDS_cpplang_NonConstConstexprMemberFunction auto AtomicReference<__Type>::operator--() noexcept -> __Type {
  return std::atomic_fetch_sub(&_data, 1) + 1;
}

template <typename __Type> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename T, meta::EnableIfC<meta::Or<meta::IsIntegral<T>, meta::IsBasicPointer<T>>>>
__CDS_cpplang_NonConstConstexprMemberFunction auto AtomicReference<__Type>::operator--(int) noexcept -> __Type {
  return std::atomic_fetch_sub(&_data, 1);
}

template <typename __Type> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_NonConstConstexprMemberFunction auto AtomicReference<__Type>::operator+=(__Type value) noexcept -> __Type {
  return std::atomic_fetch_add(&_data, value) + value;
}

template <typename __Type> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_NonConstConstexprMemberFunction auto AtomicReference<__Type>::operator-=(__Type value) noexcept -> __Type {
  return std::atomic_fetch_sub(&_data, value) - value;
}

template <typename __Type> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename T, meta::EnableIfC<meta::IsIntegral<T>>>
__CDS_cpplang_NonConstConstexprMemberFunction auto AtomicReference<__Type>::operator&=(__Type value) noexcept -> __Type {
  return std::atomic_fetch_and(&_data, value) & value;
}

template <typename __Type> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename T, meta::EnableIfC<meta::IsIntegral<T>>>
__CDS_cpplang_NonConstConstexprMemberFunction auto AtomicReference<__Type>::operator|=(__Type value) noexcept -> __Type {
  return std::atomic_fetch_or(&_data, value) | value;
}

template <typename __Type> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename T, meta::EnableIfC<meta::IsIntegral<T>>>
__CDS_cpplang_NonConstConstexprMemberFunction auto AtomicReference<__Type>::operator ^=(__Type value) noexcept -> __Type {
  return std::atomic_fetch_xor(&_data, value) ^ value;
}

template <typename __Type> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_ConstexprOverride auto AtomicReference<__Type>::hash() const noexcept -> Size {
  return get();
}

template <typename __Type> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_ConstexprOverride auto AtomicReference<__Type>::hash(AtomicMemoryOrder order) const noexcept -> Size {
  return get(order);
}

template <typename __Type> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
inline auto AtomicReference<__Type>::toString() const noexcept -> String {
  return get();
}

template <typename __Type> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
inline auto AtomicReference<__Type>::toString(AtomicMemoryOrder order) const noexcept -> String {
  return get(order);
}

template <typename __Type> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
inline auto AtomicReference<__Type>::equals(Object const& object) const noexcept -> bool {
  if (this == &object) {
    return true;
  }

  auto const* pAtomic = dynamic_cast<decltype(this)>(&object);   // NOLINT(clion-misra-cpp2008-5-2-8, *-reinterpret-cast, clion-misra-cpp2008-5-2-5, clion-misra-cpp2008-5-2-9)
  if (pAtomic == nullptr) {
    return false;
  }

  return get() == pAtomic->get();
}


template <typename __Type> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
inline auto AtomicReference<__Type>::equals(
    Object const&     object,
    AtomicMemoryOrder order
) const noexcept -> bool {
  if (this == &object) {
    return true;
  }

  auto const* pAtomic = dynamic_cast<decltype(this)>(&object);   // NOLINT(clion-misra-cpp2008-5-2-8, *-reinterpret-cast, clion-misra-cpp2008-5-2-5, clion-misra-cpp2008-5-2-9)
  if (pAtomic == nullptr) {
    return false;
  }

  return get(order) == pAtomic->get(order);
}
#endif
} // namespace cds

#endif // __CDS_ATOMIC_IMPL_HPP__
