//
// Created by loghin on 1/12/25.
//

#ifndef CDS_COMMON_SPECIAL_MEMBER_FUNCTION_HELPER_HPP
#define CDS_COMMON_SPECIAL_MEMBER_FUNCTION_HELPER_HPP
#pragma once

#include <cds/meta/Base>

namespace cds {
namespace meta {
namespace impl {
template <typename /* CanCopy */, typename /* CanMove */> struct SfinaeCtorBase {};

template <> struct SfinaeCtorBase<False::Type, False::Type> {
  SfinaeCtorBase() = default;
  SfinaeCtorBase(SfinaeCtorBase const&) = delete;
  SfinaeCtorBase(SfinaeCtorBase&&) = delete;
  auto operator=(SfinaeCtorBase const&) -> SfinaeCtorBase& = default;
  auto operator=(SfinaeCtorBase&&) -> SfinaeCtorBase& = default;
};

template <> struct SfinaeCtorBase<True::Type, False::Type> {
  SfinaeCtorBase() = default;
  SfinaeCtorBase(SfinaeCtorBase const&) = default;
  SfinaeCtorBase(SfinaeCtorBase&&) = delete;
  auto operator=(SfinaeCtorBase const&) -> SfinaeCtorBase& = default;
  auto operator=(SfinaeCtorBase&&) -> SfinaeCtorBase& = default;
};

template <> struct SfinaeCtorBase<False::Type, True::Type> {
  SfinaeCtorBase() = default;
  SfinaeCtorBase(SfinaeCtorBase const&) = delete;
  SfinaeCtorBase(SfinaeCtorBase&&) = default;
  auto operator=(SfinaeCtorBase const&) -> SfinaeCtorBase& = default;
  auto operator=(SfinaeCtorBase&&) -> SfinaeCtorBase& = default;
};

template <> struct SfinaeCtorBase<True::Type, True::Type> {
  SfinaeCtorBase() = default;
  SfinaeCtorBase(SfinaeCtorBase const&) = default;
  SfinaeCtorBase(SfinaeCtorBase&&) = default;
  auto operator=(SfinaeCtorBase const&) -> SfinaeCtorBase& = default;
  auto operator=(SfinaeCtorBase&&) -> SfinaeCtorBase& = default;
};

template <typename /* CanCopy */, typename /* CanMove */> struct SfinaeAssignBase {};

template <> struct SfinaeAssignBase<False::Type, False::Type> {
  SfinaeAssignBase() = default;
  SfinaeAssignBase(SfinaeAssignBase const&) = default;
  SfinaeAssignBase(SfinaeAssignBase&&) = default;
  auto operator=(SfinaeAssignBase const&) -> SfinaeAssignBase& = delete;
  auto operator=(SfinaeAssignBase&&) -> SfinaeAssignBase& = delete;
};

template <> struct SfinaeAssignBase<True::Type, False::Type> {
  SfinaeAssignBase() = default;
  SfinaeAssignBase(SfinaeAssignBase const&) = default;
  SfinaeAssignBase(SfinaeAssignBase&&) = default;
  auto operator=(SfinaeAssignBase const&) -> SfinaeAssignBase& = default;
  auto operator=(SfinaeAssignBase&&) -> SfinaeAssignBase& = delete;
};

template <> struct SfinaeAssignBase<False::Type, True::Type> {
  SfinaeAssignBase() = default;
  SfinaeAssignBase(SfinaeAssignBase const&) = default;
  SfinaeAssignBase(SfinaeAssignBase&&) = default;
  auto operator=(SfinaeAssignBase const&) -> SfinaeAssignBase& = delete;
  auto operator=(SfinaeAssignBase&&) -> SfinaeAssignBase& = default;
};

template <> struct SfinaeAssignBase<True::Type, True::Type> {
  SfinaeAssignBase() = default;
  SfinaeAssignBase(SfinaeAssignBase const&) = default;
  SfinaeAssignBase(SfinaeAssignBase&&) = default;
  auto operator=(SfinaeAssignBase const&) -> SfinaeAssignBase& = default;
  auto operator=(SfinaeAssignBase&&) -> SfinaeAssignBase& = default;
};
} // namespace impl
} // namespace meta
} // namespace cds

#endif // #ifndef CDS_COMMON_SPECIAL_MEMBER_FUNCTION_HELPER_HPP
