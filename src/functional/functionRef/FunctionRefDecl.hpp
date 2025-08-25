//
// Created by loghin on 8/24/25.
//

#ifndef CDS_FUNCTIONAL_FUNCTION_REF_DECL_HPP
#define CDS_FUNCTIONAL_FUNCTION_REF_DECL_HPP
#pragma once

namespace cds {
namespace functional {
namespace impl {
template <typename S> class FunctionRef;
template <typename S> class NodiscardFunctionRef;
} // namespace impl

using impl::FunctionRef;
using impl::NodiscardFunctionRef;
} // namespace functional
} // namespace cds

#endif // #ifndef CDS_FUNCTIONAL_FUNCTION_REF_DECL_HPP
