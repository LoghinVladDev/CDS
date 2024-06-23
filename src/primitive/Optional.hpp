//
// Created by loghin on 6/18/24.
//

#ifndef CDS_PRIMITIVE_OPTIONAL_HPP
#define CDS_PRIMITIVE_OPTIONAL_HPP
#pragma once

#include "optional/OptionalBase.hpp"

namespace cds {
template <typename T> class Optional : private impl::OptionalBase<T> {
  using Base = impl::OptionalBase<T>;
  using StorageBase = impl::OptionalStorageBase<T>;
  using ObservableBase = impl::OptionalObservableBase<T>;
  using MonadicBase = impl::OptionalMonadicBase<T>;

  friend MonadicBase;

public:
  using Base::Base;

  using StorageBase::reset;

  using ObservableBase::operator*;
  using ObservableBase::operator->;
  using ObservableBase::operator bool;
  using ObservableBase::hasValue;
  using ObservableBase::get;
  using ObservableBase::getOr;

  using MonadicBase::andThen;
  using MonadicBase::transform;
  using MonadicBase::orElse;

  CDS_ATTR(2(implicit, constexpr(11))) Optional(CDS_ATTR(unused) impl::Nullopt = impl::nullopt) noexcept :
      Base{} {}
};

using impl::nullopt;

#if CDS_ATTR(ctad)
template <typename T> Optional(T) -> Optional<T>;
#endif // #if CDS_ATTR(ctad)
} // namespace cds

#endif // #ifndef CDS_PRIMITIVE_OPTIONAL_HPP
