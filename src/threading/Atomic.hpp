// NOLINT(llvm-header-guard)
// Created by loghin on 30.03.2021.
//

#ifndef __CDS_ATOMIC_HPP__ // NOLINT(llvm-header-guard)
#define __CDS_ATOMIC_HPP__ // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
#pragma once

#include <CDS/Object>
#include <CDS/meta/TypeTraits>
#include <atomic>

#include "atomic/AtomicConfig.hpp"

namespace cds {
enum class AtomicMemoryOrder {
#if __CDS_cpplang_core_version >= __CDS_cpplang_core_version_20
  Relaxed                 = static_cast<int>(std::memory_order::relaxed),
  Consume                 = static_cast<int>(std::memory_order::consume),
  Acquire                 = static_cast<int>(std::memory_order::acquire),
  Release                 = static_cast<int>(std::memory_order::release),
  AcquireRelease          = static_cast<int>(std::memory_order::acq_rel),
  SequentiallyConsistent  = static_cast<int>(std::memory_order::seq_cst)
#else
  Relaxed                 = static_cast<int>(std::memory_order::memory_order_relaxed),
  Consume                 = static_cast<int>(std::memory_order::memory_order_consume),
  Acquire                 = static_cast<int>(std::memory_order::memory_order_acquire),
  Release                 = static_cast<int>(std::memory_order::memory_order_release),
  AcquireRelease          = static_cast<int>(std::memory_order::memory_order_acq_rel),
  SequentiallyConsistent  = static_cast<int>(std::memory_order::memory_order_seq_cst)
#endif
};

class AtomicFlag : public Object {
public:
  AtomicFlag() noexcept = default;
  AtomicFlag(AtomicFlag const&) = delete;
  AtomicFlag(AtomicFlag&&) = delete;
  __CDS_cpplang_ConstexprDestructor ~AtomicFlag() noexcept override = default;

  auto operator=(AtomicFlag const&) -> AtomicFlag& = delete;
  auto operator=(AtomicFlag&&) -> AtomicFlag& = delete;

  auto clear() noexcept -> void;
  auto clear(AtomicMemoryOrder order) noexcept -> void;

  auto set() noexcept -> bool;
  auto set(AtomicMemoryOrder order) noexcept -> bool;

  __CDS_NoDiscard auto get() const noexcept -> bool;
  __CDS_NoDiscard auto get(AtomicMemoryOrder order) const noexcept -> bool;

  __CDS_NoDiscard __CDS_Implicit operator bool() const noexcept; // NOLINT(google-explicit-constructor, hicpp-explicit-conversions)
  __CDS_NoDiscard auto toString() const noexcept -> String override;
  __CDS_NoDiscard auto hash() const noexcept -> Size override;

  __CDS_NoDiscard auto equals(Object const& object) const noexcept -> bool override;
  __CDS_NoDiscard auto toString(AtomicMemoryOrder order) const noexcept -> String;
  __CDS_NoDiscard auto equals(Object const& object, AtomicMemoryOrder order) const noexcept -> bool;
  
private:
#if __CDS_atomic_flag_implementation == __CDS_atomic_flag_stl_atomic_flag_implementation
  using BaseType = std::atomic_flag;
#endif

#if __CDS_atomic_flag_implementation == __CDS_atomic_flag_stl_atomic_implementation
  using BaseType = std::atomic<bool>;
#endif
  BaseType _atomicFlag;
};

template<typename __Type> class Atomic : public Object {      // NOLINT(*-special-member-functions, bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  static_assert(
      meta::And<
          meta::IsTriviallyCopyable<__Type>,
          meta::IsCopyConstructible<__Type>,
          meta::IsCopyAssignable<__Type>,
          meta::IsMoveConstructible<__Type>,
          meta::IsMoveAssignable<__Type>
      >::value,
      "Incompatible atomic type"
  );
  
public: // NOLINT(readability-redundant-access-specifiers)
  constexpr Atomic() noexcept(noexcept(__Type())) = default;
  __CDS_cpplang_ConstexprConstructorNonEmptyBody Atomic(Atomic const& atomic) noexcept;
  __CDS_cpplang_ConstexprConstructorNonEmptyBody Atomic(Atomic const& atomic, AtomicMemoryOrder order) noexcept;
  __CDS_cpplang_ConstexprConstructorNonEmptyBody Atomic(
      Atomic const&     atomic,
      AtomicMemoryOrder loadOrder,
      AtomicMemoryOrder storeOrder
  ) noexcept;
  
  __CDS_Implicit __CDS_cpplang_ConstexprConstructorNonEmptyBody Atomic(__Type value) noexcept; // NOLINT(google-explicit-constructor, hicpp-explicit-conversions)
  __CDS_cpplang_ConstexprConstructorNonEmptyBody Atomic(__Type value, AtomicMemoryOrder order) noexcept;
  __CDS_cpplang_ConstexprDestructor ~Atomic() noexcept override = default;
  
  __CDS_cpplang_NonConstConstexprMemberFunction auto operator=(Atomic const& atomic) noexcept -> Atomic&;
  __CDS_cpplang_NonConstConstexprMemberFunction auto operator=(__Type value) noexcept -> Atomic&;
  
  __CDS_NoDiscard constexpr auto get() const noexcept -> __Type;
  __CDS_NoDiscard constexpr auto get(AtomicMemoryOrder order) const noexcept -> __Type;
  __CDS_cpplang_NonConstConstexprMemberFunction auto set(__Type value) noexcept -> void;
  __CDS_cpplang_NonConstConstexprMemberFunction auto set(__Type value, AtomicMemoryOrder order) noexcept -> void;
  __CDS_NoDiscard __CDS_Implicit constexpr operator __Type() const noexcept; // NOLINT(google-explicit-constructor, hicpp-explicit-conversions)
  
  __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction auto exchange(__Type value) noexcept -> __Type;
  __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction auto exchange(
      __Type            value,
      AtomicMemoryOrder order
  ) noexcept -> __Type;
  
  __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction auto compareExchangeWeak(
      __Type& expected,
      __Type  desired
  ) noexcept -> bool;
  
  __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction auto compareExchangeWeak(
      __Type&           expected,
      __Type            desired,
      AtomicMemoryOrder order
  ) noexcept -> bool;
  
  __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction auto compareExchangeWeak(
      __Type&           expected,
      __Type            desired,
      AtomicMemoryOrder success,
      AtomicMemoryOrder failure
  ) noexcept -> bool;
  
  __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction auto compareExchangeStrong(
      __Type& expected,
      __Type  desired
  ) noexcept -> bool;
  
  __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction auto compareExchangeStrong(
      __Type&           expected,
      __Type            desired,
      AtomicMemoryOrder order
  ) noexcept -> bool;
  
  __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction auto compareExchangeStrong(
      __Type&           expected,
      __Type            desired,
      AtomicMemoryOrder success,
      AtomicMemoryOrder failure
  ) noexcept -> bool;
  
  __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction auto getThenAdd(__Type value) noexcept -> __Type;
  __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction auto getThenAdd(
      __Type            value,
      AtomicMemoryOrder order
  ) noexcept -> __Type;
  
  __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction auto getThenSubtract(__Type value) noexcept -> __Type;
  __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction auto getThenSubtract(
      __Type            value,
      AtomicMemoryOrder order
  ) noexcept -> __Type;
  
  template <typename T = __Type, meta::EnableIfC<meta::IsIntegral<T>> = 0>
  __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction auto getThenBitwiseAnd(
      __Type value
  ) noexcept -> __Type;
  
  template <typename T = __Type, meta::EnableIfC<meta::IsIntegral<T>> = 0>
  __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction auto getThenBitwiseAnd(
      __Type            value,
      AtomicMemoryOrder order
  ) noexcept -> __Type;
  
  template <typename T = __Type, meta::EnableIfC<meta::IsIntegral<T>> = 0>
  __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction auto getThenBitwiseOr(
      __Type value
  ) noexcept -> __Type;
  
  template <typename T = __Type, meta::EnableIfC<meta::IsIntegral<T>> = 0>
  __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction auto getThenBitwiseOr(
      __Type            value,
      AtomicMemoryOrder order
  ) noexcept -> __Type;
  
  template <typename T = __Type, meta::EnableIfC<meta::IsIntegral<T>> = 0>
  __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction auto getThenBitwiseXor(
      __Type value
  ) noexcept -> __Type;
  
  template <typename T = __Type, meta::EnableIfC<meta::IsIntegral<T>> = 0>
  __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction auto getThenBitwiseXor(
      __Type            value,
      AtomicMemoryOrder order
  ) noexcept -> __Type;
  
  template <typename T = __Type, meta::EnableIfC<meta::Or<meta::IsIntegral<T>, meta::IsBasicPointer<T>>> = 0> 
  __CDS_cpplang_NonConstConstexprMemberFunction auto operator++() noexcept -> __Type;
  
  template <typename T = __Type, meta::EnableIfC<meta::Or<meta::IsIntegral<T>, meta::IsBasicPointer<T>>> = 0> 
  __CDS_cpplang_NonConstConstexprMemberFunction auto operator++(int) noexcept -> __Type;
  
  template <typename T = __Type, meta::EnableIfC<meta::Or<meta::IsIntegral<T>, meta::IsBasicPointer<T>>> = 0> 
  __CDS_cpplang_NonConstConstexprMemberFunction auto operator--() noexcept -> __Type;
  
  template <typename T = __Type, meta::EnableIfC<meta::Or<meta::IsIntegral<T>, meta::IsBasicPointer<T>>> = 0> 
  __CDS_cpplang_NonConstConstexprMemberFunction auto operator--(int) noexcept -> __Type;
  
  __CDS_cpplang_NonConstConstexprMemberFunction auto operator+=(__Type value) noexcept -> __Type;
  __CDS_cpplang_NonConstConstexprMemberFunction auto operator-=(__Type value) noexcept -> __Type;
  
  template <typename T = __Type, meta::EnableIfC<meta::IsIntegral<T>> = 0>
  __CDS_cpplang_NonConstConstexprMemberFunction auto operator&=(__Type value) noexcept -> __Type;
  
  template <typename T = __Type, meta::EnableIfC<meta::IsIntegral<T>> = 0>
  __CDS_cpplang_NonConstConstexprMemberFunction auto operator|=(__Type value) noexcept -> __Type;
  
  template <typename T = __Type, meta::EnableIfC<meta::IsIntegral<T>> = 0>
  __CDS_cpplang_NonConstConstexprMemberFunction auto operator^=(__Type value) noexcept -> __Type;
  
  __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto hash() const noexcept -> Size override;
  __CDS_NoDiscard auto toString() const noexcept -> String override;
  __CDS_NoDiscard auto equals(Object const& object) const noexcept -> bool override;
  
  __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto hash(AtomicMemoryOrder order) const noexcept -> Size;
  __CDS_NoDiscard auto toString(AtomicMemoryOrder order) const noexcept -> String;
  __CDS_NoDiscard auto equals(Object const& object, AtomicMemoryOrder order) const noexcept -> bool;
  
private:
  std::atomic<__Type> _data;
};


#if __CDS_atomic_ref_implementation != __CDS_atomic_ref_unavailable

template <typename __Type> class AtomicReference : public Object { // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-special-member-functions)
  static_assert(
      meta::And<
          meta::IsTriviallyCopyable<__Type>,
          meta::IsCopyConstructible<__Type>,
          meta::IsCopyAssignable<__Type>,
          meta::IsMoveConstructible<__Type>,
          meta::IsMoveAssignable<__Type>
      >::value,
      "Incompatible atomic type"
  );

public:
  constexpr AtomicReference() = delete;
  __CDS_Implicit constexpr AtomicReference(__Type& value) noexcept; // NOLINT(google-explicit-constructor, hicpp-explicit-conversions)
  constexpr AtomicReference(AtomicReference const& atomic) noexcept;
  __CDS_cpplang_ConstexprDestructor ~AtomicReference() noexcept override = default;

  __CDS_cpplang_NonConstConstexprMemberFunction auto operator=(__Type& value) noexcept -> AtomicReference&;

  constexpr auto operator=(AtomicReference const& atomic) noexcept -> AtomicReference& = delete;
  __CDS_NoDiscard constexpr auto get() const noexcept -> __Type;
  __CDS_NoDiscard constexpr auto get(AtomicMemoryOrder order) const noexcept -> __Type;

  __CDS_cpplang_NonConstConstexprMemberFunction auto set(__Type value) noexcept -> void;
  __CDS_cpplang_NonConstConstexprMemberFunction auto set(
      __Type            value,
      AtomicMemoryOrder order
  ) noexcept -> void;

  __CDS_NoDiscard __CDS_Implicit constexpr operator __Type() const noexcept; // NOLINT(google-explicit-constructor, hicpp-explicit-conversions)

  __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction auto exchange(__Type value) noexcept -> __Type;
  __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction auto exchange(
      __Type            value,
      AtomicMemoryOrder order
  ) noexcept -> __Type;

  __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction auto compareExchangeWeak(
      __Type& expected,
      __Type  desired
  ) noexcept -> bool;

  __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction auto compareExchangeWeak(
      __Type&           expected,
      __Type            desired,
      AtomicMemoryOrder order
  ) noexcept -> bool;

  __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction auto compareExchangeWeak(
      __Type&           expected,
      __Type            desired,
      AtomicMemoryOrder success,
      AtomicMemoryOrder failure
  ) noexcept -> bool;

  __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction auto compareExchangeStrong(
      __Type& expected,
      __Type  desired
  ) noexcept -> bool;

  __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction auto compareExchangeStrong(
      __Type&           expected,
      __Type            desired,
      AtomicMemoryOrder order
  ) noexcept -> bool;

  __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction auto compareExchangeStrong(
      __Type&           expected,
      __Type            desired,
      AtomicMemoryOrder success,
      AtomicMemoryOrder failure
  ) noexcept -> bool;

  __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction auto getThenAdd(__Type value) noexcept -> __Type;
  __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction auto getThenAdd(
      __Type            value,
      AtomicMemoryOrder order
  ) noexcept -> __Type;
  
  __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction auto getThenSubtract(__Type value) noexcept -> __Type;
  __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction auto getThenSubtract(
      __Type            value,
      AtomicMemoryOrder order
  ) noexcept -> __Type;

  template <typename T = __Type, meta::EnableIfC<meta::IsIntegral<T>> = 0>
  __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction auto getThenBitwiseAnd(__Type value) noexcept -> __Type;

  template <typename T = __Type, meta::EnableIfC<meta::IsIntegral<T>> = 0>
  __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction auto getThenBitwiseAnd(
      __Type            value,
      AtomicMemoryOrder order
  ) noexcept -> __Type;

  template <typename T = __Type, meta::EnableIfC<meta::IsIntegral<T>> = 0>
  __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction auto getThenBitwiseOr(__Type value) noexcept -> __Type;
  
  template <typename T = __Type, meta::EnableIfC<meta::IsIntegral<T>> = 0>
  __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction auto getThenBitwiseOr(
      __Type            value,
      AtomicMemoryOrder order
  ) noexcept -> __Type;

  template <typename T = __Type, meta::EnableIfC<meta::IsIntegral<T>> = 0>
  __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction auto getThenBitwiseXor(__Type value) noexcept -> __Type;

  template <typename T = __Type, meta::EnableIfC<meta::IsIntegral<T>> = 0>
  __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction auto getThenBitwiseXor(
      __Type            value,
      AtomicMemoryOrder order
  ) noexcept -> __Type;

  template <typename T = __Type, meta::EnableIfC<meta::Or<meta::IsIntegral<T>, meta::IsBasicPointer<T>>> = 0>
  __CDS_cpplang_NonConstConstexprMemberFunction auto operator++() noexcept -> __Type;

  
  template <typename T = __Type, meta::EnableIfC<meta::Or<meta::IsIntegral<T>, meta::IsBasicPointer<T>>> = 0>
  __CDS_cpplang_NonConstConstexprMemberFunction auto operator++(int) noexcept -> __Type;

  
  template <typename T = __Type, meta::EnableIfC<meta::Or<meta::IsIntegral<T>, meta::IsBasicPointer<T>>> = 0>
  __CDS_cpplang_NonConstConstexprMemberFunction auto operator--() noexcept -> __Type;

  
  template <typename T = __Type, meta::EnableIfC<meta::Or<meta::IsIntegral<T>, meta::IsBasicPointer<T>>> = 0>
__CDS_cpplang_NonConstConstexprMemberFunction auto operator--(int) noexcept -> __Type;

  __CDS_cpplang_NonConstConstexprMemberFunction auto operator+=(__Type value) noexcept -> __Type;
  __CDS_cpplang_NonConstConstexprMemberFunction auto operator-=(__Type value) noexcept -> __Type;

  template <typename T = __Type, meta::EnableIfC<meta::IsIntegral<T>> = 0>
  __CDS_cpplang_NonConstConstexprMemberFunction auto operator&=(__Type value) noexcept -> __Type;

  template <typename T = __Type, meta::EnableIfC<meta::IsIntegral<T>> = 0>
  __CDS_cpplang_NonConstConstexprMemberFunction auto operator|=(__Type value) noexcept -> __Type;

  template <typename T = __Type, meta::EnableIfC<meta::IsIntegral<T>> = 0>
  __CDS_cpplang_NonConstConstexprMemberFunction auto operator^=(__Type value) noexcept -> __Type;

  __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto hash() const noexcept -> Size override;
  __CDS_NoDiscard auto toString() const noexcept -> String override;
  __CDS_NoDiscard auto equals(Object const& object) const noexcept -> bool override;

  __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto hash(AtomicMemoryOrder order) const noexcept -> Size;
  __CDS_NoDiscard auto toString(AtomicMemoryOrder order) const noexcept -> String;
  __CDS_NoDiscard auto equals(Object const& object, AtomicMemoryOrder order) const noexcept -> bool;

#if __CDS_atomic_ref_implementation == __CDS_atomic_ref_stl_atomic_ref_implementation
private:
  std::atomic_ref<__Type> _data;
#endif
};

#endif
} // namespace cds

#include "atomic/impl/AtomicCTAD.hpp"
#include "atomic/impl/AtomicImpl.hpp"

#endif // __CDS_ATOMIC_HPP__
