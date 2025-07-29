//
// Created by loghin on 7/29/25.
//

#ifndef CDS_PRIMITIVE_EXPECTED_STORAGE_BASE_HPP
#define CDS_PRIMITIVE_EXPECTED_STORAGE_BASE_HPP
#pragma once

#include <initializer_list>

#include <cds/meta/ObjectTraits>
#include <cds/meta/Tags>

#include "ExpectedSpecialMemberFunctionsDetail.hpp"

namespace cds {
namespace impl {
using meta::InPlace;
using meta::IsNoexceptConstructible;
using meta::SpecialMemberFunctionInfoType;

template <typename T, typename E, SpecialMemberFunctionInfoType = ExpectedDestructionDetail<T, E>::value>
union ExpectedStorageBase;

template <typename T, typename E> union ExpectedStorageBase<T, E, SpecialMemberFunctionInfoType::Trivial> {
  static_assert(Not<IsUnboundedArray<E>>::value, "Invalid Unexpected error type");

  ExpectedStorageBase(ExpectedStorageBase const&) = default;
  ExpectedStorageBase(ExpectedStorageBase&&) = default;
  auto operator=(ExpectedStorageBase const&) -> ExpectedStorageBase& = default;
  auto operator=(ExpectedStorageBase&&) -> ExpectedStorageBase& = default;

  ~ExpectedStorageBase() noexcept = default;

  template <typename... Args> CDS_ATTR(2(explicit, constexpr(11))) ExpectedStorageBase(InPlace, Args&&... args)
      CDS_ATTR(noexcept_v(IsNoexceptConstructible<T, Args&&...>)) : value(fwd<Args>(args)...) {}

  template <typename U, typename... Args> CDS_ATTR(2(explicit, constexpr(11)))
  ExpectedStorageBase(InPlace, std::initializer_list<U> const& list, Args&&... args)
      CDS_ATTR(noexcept_v(IsNoexceptConstructible<T, std::initializer_list<U> const&, Args&&...>)) :
      value(list, fwd<Args>(args)...) {}

  template <typename... Args> CDS_ATTR(2(explicit, constexpr(11))) ExpectedStorageBase(Unexpect, Args&&... args)
      CDS_ATTR(noexcept_v(IsNoexceptConstructible<E, Args&&...>)) : error(fwd<Args>(args)...) {}

  template <typename U, typename... Args> CDS_ATTR(constexpr(11))
  ExpectedStorageBase(Unexpect, std::initializer_list<U> const& list, Args&&... args)
      CDS_ATTR(noexcept_v(IsNoexceptConstructible<E, std::initializer_list<U> const&, Args&&...>)) :
      error(list, fwd<Args>(args)...) {}

  T value;
  E error;
};

template <typename T, typename E> union ExpectedStorageBase<T, E, SpecialMemberFunctionInfoType::NonTrivial> {
  static_assert(Not<IsUnboundedArray<E>>::value, "Invalid Unexpected error type");

  ExpectedStorageBase(ExpectedStorageBase const&) = default;
  ExpectedStorageBase(ExpectedStorageBase&&) = default;
  auto operator=(ExpectedStorageBase const&) -> ExpectedStorageBase& = default;
  auto operator=(ExpectedStorageBase&&) -> ExpectedStorageBase& = default;

  CDS_ATTR(constexpr(20)) ~ExpectedStorageBase() noexcept {}

  template <typename... Args> CDS_ATTR(2(explicit, constexpr(11))) ExpectedStorageBase(InPlace, Args&&... args)
      CDS_ATTR(noexcept_v(IsNoexceptConstructible<T, Args&&...>)) : value(fwd<Args>(args)...) {}

  template <typename U, typename... Args> CDS_ATTR(2(explicit, constexpr(11)))
  ExpectedStorageBase(InPlace, std::initializer_list<U> const& list, Args&&... args)
      CDS_ATTR(noexcept_v(IsNoexceptConstructible<T, std::initializer_list<U> const&, Args&&...>)) :
      value(list, fwd<Args>(args)...) {}

  template <typename... Args> CDS_ATTR(2(explicit, constexpr(11))) ExpectedStorageBase(Unexpect, Args&&... args)
      CDS_ATTR(noexcept_v(IsNoexceptConstructible<E, Args&&...>)) : error(fwd<Args>(args)...) {}

  template <typename U, typename... Args> CDS_ATTR(constexpr(11))
  ExpectedStorageBase(Unexpect, std::initializer_list<U> const& list, Args&&... args)
      CDS_ATTR(noexcept_v(IsNoexceptConstructible<E, std::initializer_list<U> const&, Args&&...>)) :
      error(list, fwd<Args>(args)...) {}

  T value;
  E error;
};

template <typename T, typename E> union ExpectedStorageBase<T, E, SpecialMemberFunctionInfoType::Deleted> {
  static_assert(Not<IsUnboundedArray<E>>::value, "Invalid Unexpected error type");

  ExpectedStorageBase(ExpectedStorageBase const&) = default;
  ExpectedStorageBase(ExpectedStorageBase&&) = default;
  auto operator=(ExpectedStorageBase const&) -> ExpectedStorageBase& = default;
  auto operator=(ExpectedStorageBase&&) -> ExpectedStorageBase& = default;

  ~ExpectedStorageBase() noexcept = delete;

  template <typename... Args> CDS_ATTR(2(explicit, constexpr(11))) ExpectedStorageBase(InPlace, Args&&... args)
      CDS_ATTR(noexcept_v(IsNoexceptConstructible<T, Args&&...>)) : value(fwd<Args>(args)...) {}

  template <typename U, typename... Args> CDS_ATTR(constexpr(11))
  ExpectedStorageBase(InPlace, std::initializer_list<U> const& list, Args&&... args)
      CDS_ATTR(noexcept_v(IsNoexceptConstructible<T, std::initializer_list<U> const&, Args&&...>)) :
      value(list, fwd<Args>(args)...) {}

  template <typename... Args> CDS_ATTR(2(explicit, constexpr(11))) ExpectedStorageBase(Unexpect, Args&&... args)
      CDS_ATTR(noexcept_v(IsNoexceptConstructible<E, Args&&...>)) : error(fwd<Args>(args)...) {}

  template <typename U, typename... Args> CDS_ATTR(constexpr(11))
  ExpectedStorageBase(Unexpect, std::initializer_list<U> const& list, Args&&... args)
      CDS_ATTR(noexcept_v(IsNoexceptConstructible<E, std::initializer_list<U> const&, Args&&...>)) :
      error(list, fwd<Args>(args)...) {}

  T value;
  E error;
};

template <typename E> union ExpectedStorageBase<void, E, SpecialMemberFunctionInfoType::Trivial> {
  static_assert(Not<IsUnboundedArray<E>>::value, "Invalid Unexpected error type");

  ExpectedStorageBase(ExpectedStorageBase const&) = default;
  ExpectedStorageBase(ExpectedStorageBase&&) = default;
  auto operator=(ExpectedStorageBase const&) -> ExpectedStorageBase& = default;
  auto operator=(ExpectedStorageBase&&) -> ExpectedStorageBase& = default;

  ~ExpectedStorageBase() noexcept = default;

  CDS_ATTR(2(explicit, constexpr(14))) ExpectedStorageBase(InPlace) noexcept : uninitialized{0} {}

  template <typename... Args> CDS_ATTR(2(explicit, constexpr(11))) ExpectedStorageBase(Unexpect, Args&&... args)
      CDS_ATTR(noexcept_v(IsNoexceptConstructible<E, Args&&...>)) : error(fwd<Args>(args)...) {}

  template <typename U, typename... Args> CDS_ATTR(constexpr(11))
  ExpectedStorageBase(Unexpect, std::initializer_list<U> const& list, Args&&... args)
      CDS_ATTR(noexcept_v(IsNoexceptConstructible<E, std::initializer_list<U> const&, Args&&...>)) :
      error(list, fwd<Args>(args)...) {}

  U8 uninitialized;
  E error;
};

template <typename E> union ExpectedStorageBase<void, E, SpecialMemberFunctionInfoType::NonTrivial> {
  static_assert(Not<IsUnboundedArray<E>>::value, "Invalid Unexpected error type");

  ExpectedStorageBase(ExpectedStorageBase const&) = default;
  ExpectedStorageBase(ExpectedStorageBase&&) = default;
  auto operator=(ExpectedStorageBase const&) -> ExpectedStorageBase& = default;
  auto operator=(ExpectedStorageBase&&) -> ExpectedStorageBase& = default;

  CDS_ATTR(constexpr(20)) ~ExpectedStorageBase() noexcept {}

  CDS_ATTR(2(explicit, constexpr(14))) ExpectedStorageBase(InPlace) noexcept : uninitialized{0} {}

  template <typename... Args> CDS_ATTR(2(explicit, constexpr(11))) ExpectedStorageBase(Unexpect, Args&&... args)
      CDS_ATTR(noexcept_v(IsNoexceptConstructible<E, Args&&...>)) : error(fwd<Args>(args)...) {}

  template <typename U, typename... Args> CDS_ATTR(constexpr(11))
  ExpectedStorageBase(Unexpect, std::initializer_list<U> const& list, Args&&... args)
      CDS_ATTR(noexcept_v(IsNoexceptConstructible<E, std::initializer_list<U> const&, Args&&...>)) :
      error(list, fwd<Args>(args)...) {}

  U8 uninitialized;
  E error;
};

template <typename E> union ExpectedStorageBase<void, E, SpecialMemberFunctionInfoType::Deleted> {
  static_assert(Not<IsUnboundedArray<E>>::value, "Invalid Unexpected error type");

  ExpectedStorageBase(ExpectedStorageBase const&) = default;
  ExpectedStorageBase(ExpectedStorageBase&&) = default;
  auto operator=(ExpectedStorageBase const&) -> ExpectedStorageBase& = default;
  auto operator=(ExpectedStorageBase&&) -> ExpectedStorageBase& = default;

  ~ExpectedStorageBase() noexcept = delete;

  CDS_ATTR(2(explicit, constexpr(14))) ExpectedStorageBase(InPlace) noexcept : uninitialized{0} {}

  template <typename... Args> CDS_ATTR(2(explicit, constexpr(11))) ExpectedStorageBase(Unexpect, Args&&... args)
      CDS_ATTR(noexcept_v(IsNoexceptConstructible<E, Args&&...>)) : error(fwd<Args>(args)...) {}

  template <typename U, typename... Args> CDS_ATTR(constexpr(11))
  ExpectedStorageBase(Unexpect, std::initializer_list<U> const& list, Args&&... args)
      CDS_ATTR(noexcept_v(IsNoexceptConstructible<E, std::initializer_list<U> const&, Args&&...>)) :
      error(list, fwd<Args>(args)...) {}

  U8 uninitialized;
  E error;
};
} // namespace impl
} // namespace cds

#endif // #ifndef CDS_PRIMITIVE_EXPECTED_STORAGE_BASE_HPP
