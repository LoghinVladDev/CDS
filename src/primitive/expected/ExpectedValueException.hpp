//
// Created by loghin on 7/28/25.
//

#ifndef CDS_PRIMITIVE_EXPECTED_VALUE_EXCEPTION_HPP
#define CDS_PRIMITIVE_EXPECTED_VALUE_EXCEPTION_HPP
#pragma once

#include "ContainingError.hpp"

#include <cds/exception/RuntimeException>

namespace cds {
namespace impl {
template <typename E> class ExpectedValueException :
    public RuntimeException,
    public ContainingError<ExpectedValueException<E>, E> {
  friend class ContainingError<ExpectedValueException<E>, E>;

public:
  ExpectedValueException(E value) noexcept :
      RuntimeException{"Attempted access into Expected without value"},
      _error{mv(value)} {}

  ~ExpectedValueException() noexcept override = default;

private:
  E _error;
};
} // namespace impl
} // namespace cds

#endif // #ifndef CDS_PRIMITIVE_EXPECTED_VALUE_EXCEPTION_HPP
