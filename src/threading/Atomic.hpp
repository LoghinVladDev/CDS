//
// Created by vloghin on 19.12.2024.
//

#ifndef CDS_THREADING_ATOMIC_HPP
#define CDS_THREADING_ATOMIC_HPP
#pragma once

#define CDS_ATTR_atomic_impl(_variant) CDS_ATTR_atomic_impl_ ## _variant
#define CDS_ATTR_atomic_impl_c11 1u

#ifndef CDS_ATTR_atomic_impl_current
#define CDS_ATTR_atomic_impl_current CDS_ATTR(atomic_impl(c11))
#endif // #ifndef CDS_ATTR_atomic_impl_current

#if CDS_ATTR(atomic_impl(current)) == CDS_ATTR(atomic_impl(c11))
#include "atomic/AtomicC11.hpp"
#endif // #if CDS_ATTR(atomic_impl(current)) == CDS_ATTR(atomic_impl(c11))

namespace cds {
namespace impl {
template
} // namespace impl
} // namespace cds

#endif // #ifndef CDS_THREADING_ATOMIC_HPP
