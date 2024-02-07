//
// Created by loghin on 22/09/2021.
//

#ifndef CDS_META_STD_LIB_HPP
#define CDS_META_STD_LIB_HPP
#pragma once

#include <cds/meta/Compiler>
#include <type_traits>

namespace cds {
namespace meta {
#ifdef __GLIBCXX__
#define CDS_ATTR_glibcxx true

CDS_ATTR(2(nodiscard, constexpr(11))) auto inConstexpr() noexcept -> bool {
  return std::__is_constant_evaluated();
}
#else // #ifdef __GLIBCXX__
#define CDS_ATTR_glibcxx false
#endif // #ifdef __GLIBCXX__ #else
} // namespace meta
} // namespace cds

#endif // CDS_META_STD_LIB_HPP
