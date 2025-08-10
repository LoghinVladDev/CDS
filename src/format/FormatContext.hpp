//
// Created by loghin on 12/11/24.
//

#ifndef CDS_FORMAT_FORMAT_CONTEXT_HPP
#define CDS_FORMAT_FORMAT_CONTEXT_HPP
#pragma once

#include <cds/String>
#include <cds/iterator/BackInserterIterator>

namespace cds {
namespace impl {
namespace fmt {
using iterator::BackInserterIterator;

template <typename C, typename U> class FormatContext {
  using S = BaseString<C, U>;
public:
  using Iterator = BackInserterIterator<S>;

  CDS_ATTR(2(explicit, constexpr(11))) FormatContext(S& str) noexcept : _out{str} {}
  ~FormatContext() noexcept = default;

  CDS_ATTR(2(nodiscard, constexpr(11))) auto out() const noexcept -> Iterator {
    return Iterator{_out};
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto from(Iterator& /* iterator */) const noexcept -> FormatContext {
    /* ignore = iterator; */
    return FormatContext{_out};
  }

private:
  S& _out;
};
} // namespace fmt
} // namespace impl
} // namespace cds

#endif // #ifndef CDS_FORMAT_FORMAT_CONTEXT_HPP
