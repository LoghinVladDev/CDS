//
// Created by loghin on 6/3/25.
//

#ifndef CDS_DS_ARRAY_NON_SCALING_BASE_HPP
#define CDS_DS_ARRAY_NON_SCALING_BASE_HPP
#pragma once

#include <cds/meta/Compiler>

namespace cds {
namespace impl {
template <typename /* T */, typename /* E */, typename A, typename Traits> class CDS_ATTR(ebo) ArrayNonScalingBase :
    private A, private Traits {
  // Incomplete
};
} // namespace impl
} // namespace cds

#endif // #ifndef CDS_DS_ARRAY_NON_SCALING_BASE_HPP
