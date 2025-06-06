//
// Created by loghin on 6/3/25.
//

#ifndef CDS_DS_ARRAY_ARRAY_TRAITS_HPP
#define CDS_DS_ARRAY_ARRAY_TRAITS_HPP
#pragma once

#include <cds/meta/Compiler>

namespace cds {
namespace impl {
template <typename /* T */> struct ArrayTraits {
  static constexpr Size minCapacity = 32u;
  static constexpr Size scalingMultiplier = 2u;
};

// ODR before cpp17
template <typename T> Size const ArrayTraits<T>::minCapacity;
template <typename T> Size const ArrayTraits<T>::scalingMultiplier;
} // namespace impl
} // namespace cds

#endif // #ifndef CDS_DS_ARRAY_ARRAY_TRAITS_HPP
