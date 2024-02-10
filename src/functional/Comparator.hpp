//
// Created by loghin on 12/22/23.
//

#ifndef CDS_COMPARATOR_HPP
#define CDS_COMPARATOR_HPP
#pragma once

#include <cds/meta/Semantics>

namespace cds {
namespace functional {
template <typename L = void, typename R = L> struct Equal {
  CDS_ATTR(2(nodiscard, constexpr(11))) auto operator()(L const& lhs, R const& rhs) const noexcept -> bool {
    return lhs == rhs;
  }
};

template <> struct Equal<void> {
template <typename L, typename R>
CDS_ATTR(2(nodiscard, constexpr(11))) auto operator()(L&& lhs, R&& rhs) const noexcept -> bool {
  return cds::forward<L>(lhs) == cds::forward<R>(rhs);
}
};
} // namespace functional
} // namespace cds

#endif //CDS_COMPARATOR_HPP
