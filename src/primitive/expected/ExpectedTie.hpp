//
// Created by loghin on 8/10/25.
//

#ifndef CDS_EXPECTED_EXPECTED_TIE_HPP
#define CDS_EXPECTED_EXPECTED_TIE_HPP
#pragma once

#include "Expected.hpp"
#include <cds/Tuple>

namespace cds {
namespace impl {
template <typename E> CDS_ATTR(constexpr(14)) auto expectedTupleGetError() noexcept -> E* {
  return nullptr;
}

template <typename E, typename F, typename... R> CDS_ATTR(constexpr(14))
auto expectedTupleGetError(F&& first, R&&... remaining) noexcept -> E* {
  if (!first) {
    return &fwd<F>(first).error();
  }
  return expectedTupleGetError<E>(fwd<R>(remaining)...);
}

template <typename... Types, typename E> CDS_ATTR(2(nodiscard, constexpr(14))) auto tie(
    Expected<Types, E>&... args
) noexcept -> Expected<Tuple<Types&...>, E> {
  auto const errPtr = expectedTupleGetError<E>(args...);
  if (errPtr) {
    return Unexpected<E>{*errPtr};
  }
  return Tuple<Types&...>(InPlace{}, *args...);
}

template <typename... Types, typename E> CDS_ATTR(2(nodiscard, constexpr(14))) auto tie(
    Expected<Types, E> const&... args
) noexcept -> Expected<Tuple<Types const&...>, E> {
  auto const errPtr = expectedTupleGetError<E>(args...);
  if (errPtr) {
    return Unexpected<E>{*errPtr};
  }
  return Tuple<Types const&...>(InPlace{}, *args...);
}

template <typename... Types, typename E> CDS_ATTR(2(nodiscard, constexpr(14))) auto tie(
    Expected<Types, E>&&... args
) noexcept -> Expected<Tuple<Types...>, E> {
  auto const errPtr = expectedTupleGetError<E>(args...);
  if (errPtr) {
    return Unexpected<E>{mv(*errPtr)};
  }
  return Tuple<Types...>(InPlace{}, *mv(args)...);
}

template <typename... Types, typename E> CDS_ATTR(2(nodiscard, constexpr(14))) auto tie(
    Expected<Types, E> const&&... args
) noexcept -> Expected<Tuple<Types...>, E> {
  auto const errPtr = expectedTupleGetError<E>(args...);
  if (errPtr) {
    return Unexpected<E>{mv(*errPtr)};
  }
  return Tuple<Types...>(InPlace{}, *mv(args)...);
}
} // namespace impl

using impl::tie;
} // namespace cds

#endif // #ifndef CDS_EXPECTED_EXPECTED_TIE_HPP
