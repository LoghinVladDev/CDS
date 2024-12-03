//
// Created by loghin on 12/22/23.
//

#ifndef CDS_FUNCTIONAL_COMPARATOR_HPP
#define CDS_FUNCTIONAL_COMPARATOR_HPP
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

template <typename L = void, typename R = L> struct NotEqual {
  CDS_ATTR(2(nodiscard, constexpr(11))) auto operator()(L const& lhs, R const& rhs) const noexcept -> bool {
    return lhs != rhs;
  }
};

template <> struct NotEqual<void> {
  template <typename L, typename R>
  CDS_ATTR(2(nodiscard, constexpr(11))) auto operator()(L&& lhs, R&& rhs) const noexcept -> bool {
    return cds::forward<L>(lhs) != cds::forward<R>(rhs);
  }
};

template <typename L = void, typename R = L> struct Less {
  CDS_ATTR(2(nodiscard, constexpr(11))) auto operator()(L const& lhs, R const& rhs) const noexcept -> bool {
    return lhs < rhs;
  }
};

template <> struct Less<void> {
  template <typename L, typename R>
  CDS_ATTR(2(nodiscard, constexpr(11))) auto operator()(L&& lhs, R&& rhs) const noexcept -> bool {
    return cds::forward<L>(lhs) < cds::forward<R>(rhs);
  }
};

template <typename L = void, typename R = L> struct Greater {
  CDS_ATTR(2(nodiscard, constexpr(11))) auto operator()(L const& lhs, R const& rhs) const noexcept -> bool {
    return lhs > rhs;
  }
};

template <> struct Greater<void> {
  template <typename L, typename R>
  CDS_ATTR(2(nodiscard, constexpr(11))) auto operator()(L&& lhs, R&& rhs) const noexcept -> bool {
    return cds::forward<L>(lhs) > cds::forward<R>(rhs);
  }
};

template <typename L = void, typename R = L> struct LessEqual {
  CDS_ATTR(2(nodiscard, constexpr(11))) auto operator()(L const& lhs, R const& rhs) const noexcept -> bool {
    return lhs <= rhs;
  }
};

template <> struct LessEqual<void> {
  template <typename L, typename R>
  CDS_ATTR(2(nodiscard, constexpr(11))) auto operator()(L&& lhs, R&& rhs) const noexcept -> bool {
    return cds::forward<L>(lhs) <= cds::forward<R>(rhs);
  }
};

template <typename L = void, typename R = L> struct GreaterEqual {
  CDS_ATTR(2(nodiscard, constexpr(11))) auto operator()(L const& lhs, R const& rhs) const noexcept -> bool {
    return lhs >= rhs;
  }
};

template <> struct GreaterEqual<void> {
  template <typename L, typename R>
  CDS_ATTR(2(nodiscard, constexpr(11))) auto operator()(L&& lhs, R&& rhs) const noexcept -> bool {
    return cds::forward<L>(lhs) >= cds::forward<R>(rhs);
  }
};

#if CDS_ATTR(spaceship)
template <typename L = void, typename R = L> struct ThreeWay {
  CDS_ATTR(2(nodiscard, constexpr(11))) auto operator()(L const& lhs, R const& rhs) const noexcept
      -> decltype(lhs <=> rhs) {
    return lhs <=> rhs;
  }
};

template <> struct ThreeWay<void> {
  template <typename L, typename R>
  CDS_ATTR(2(nodiscard, constexpr(11))) auto operator()(L&& lhs, R&& rhs) const noexcept
      -> decltype(impl::fwd<L>(lhs), impl::fwd<R>(rhs)) {
    return cds::forward<L>(lhs) <=> cds::forward<R>(rhs);
  }
};
#endif
} // namespace functional
} // namespace cds

#endif // CDS_FUNCTIONAL_COMPARATOR_HPP
