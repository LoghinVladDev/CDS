//
// Created by loghin on 6/3/25.
//

#ifndef CDS_DS_ARRAY_DYNAMIC_BIDIRECTIONAL_SCALING_BASE_HPP
#define CDS_DS_ARRAY_DYNAMIC_BIDIRECTIONAL_SCALING_BASE_HPP
#pragma once

#include <cds/meta/Compiler>

namespace cds {
namespace impl {
template <typename, typename, typename A, typename Traits>
class CDS_ATTR(ebo) ArrayDynamicBidirectionalScalingBase : private A, private Traits {};
} // namespace impl
} // namespace cds

#endif // #ifndef CDS_DS_ARRAY_DYNAMIC_BIDIRECTIONAL_SCALING_BASE_HPP
