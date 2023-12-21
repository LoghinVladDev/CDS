//
// Created by loghin on 22.01.2021.
//

#ifndef CDS_PRIMITIVE_OBJECT_HPP
#define CDS_PRIMITIVE_OBJECT_HPP
#pragma once

#include <cds/meta/Compiler>
#include <cds/String>

namespace cds {
class String;

CDS_ATTR(ns_poly_spec) namespace poly {
class Object {
protected:
  CDS_ATTR(constexpr(11)) Object() noexcept = default;

public:
  CDS_ATTR(constexpr(11)) Object(Object const&) noexcept = delete;
  CDS_ATTR(constexpr(11)) Object(Object&&) noexcept = delete;
  CDS_ATTR(constexpr(14)) auto operator=(Object const&) noexcept -> Object& = delete;
  CDS_ATTR(constexpr(14)) auto operator=(Object&&) noexcept -> Object& = delete;
  CDS_ATTR(constexpr(20)) virtual ~Object() noexcept = default;

  CDS_ATTR(nodiscard) virtual auto toString() const CDS_ATTR(noexcept(false)) -> String;
  CDS_ATTR(2(nodiscard, constexpr(20))) virtual auto equals(Object const&) const CDS_ATTR(noexcept(false)) -> bool;
  CDS_ATTR(2(nodiscard, constexpr(20))) virtual auto hash() const noexcept -> Size;

  template <typename OStreamType> friend auto operator<<(OStreamType&& out, Object const& object)
      CDS_ATTR(noexcept(false)) -> OStreamType&;
};
} // namespace poly
} // namespace cds

#endif // CDS_PRIMITIVE_OBJECT_HPP
