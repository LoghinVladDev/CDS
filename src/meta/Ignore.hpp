//
// Created by loghin on 6/5/25.
//

#ifndef CDS_META_IGNORE_HPP
#define CDS_META_IGNORE_HPP
#pragma once

#include <cds/meta/Compiler>

namespace cds {
namespace impl {
struct Ignore {
  template <typename T> CDS_ATTR(constexpr(14)) auto operator=(T&&) const noexcept -> void {}
};

static Ignore constexpr ignore;
} // namespace impl

using impl::ignore;
} // namespace cds

#endif // #ifndef CDS_META_IGNORE_HPP
