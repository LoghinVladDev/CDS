//
// Created by loghin on 7/28/25.
//

#ifndef CDS_PRIMITIVE_EXPECTED_EXPECTED_HPP
#define CDS_PRIMITIVE_EXPECTED_EXPECTED_HPP
#pragma once

#include "ContainingError.hpp"
#include "ExpectedValueException.hpp"
#include "Unexpected.hpp"

namespace cds {
namespace impl {
enum class ExpectedStorageDetail {
  Trivial, NonTrivial, Deleted
};

template <typename T, typename E> class Expected :

template <typename T, typename E> class Expected : public ContainingError<Expected<T, E>, E> {
  friend class ContainingError<Expected<T, E>, E>;

public:
  using Value = T;
  using Error = E;

  template <typename U> using Rebound = Expected<U, Error>;

  Expected() = default;
  Expected(Expected const&) = default;

private:
  bool _engaged{true};
  union {
    T _value{};
    E _error;
  };
};
} // namespace impl
} // namespace cds

#endif // #ifndef CDS_PRIMITIVE_EXPECTED_EXPECTED_HPP
