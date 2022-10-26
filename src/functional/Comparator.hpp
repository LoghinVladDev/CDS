/*
 * Created by loghin on 10.11.2021.
 */

#ifndef __CDS_COMPARATOR_HPP__ /* NOLINT(llvm-header-guard) */
#define __CDS_COMPARATOR_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

#include <CDS/Compiler>        /* NOLINT(llvm-include-order) */
#include <CDS/FunctionalInterface>
#include "../shared/impl/generalPredicates.hpp"

namespace cds {

    template < typename T >
    class __CDS_DeprecatedHint("Deprecated use for now, to be redesigned later") Comparator {
    public:
        virtual auto operator () (T const &, T const &) const noexcept (false) -> bool = 0;
    };

} /* namespace cds */

namespace cds {

    namespace utility {

        template < typename __Type > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        using ComparisonFunction __CDS_DeprecatedHint("Use Standard Functional Interfaces instead of fixed Interface") =
                functional :: PredicateFunctionPointer < __Type const &, __Type const & >;

    } /* namespace utility */

    template < typename __Type, utility :: ComparisonFunction < __Type > __comparisonFunction > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    using  FunctionComparator __CDS_DeprecatedHint("Use Standard Functional Interface Decorator instead of fixed Interface") =
            functional :: DecoratedPredicate < utility :: ComparisonFunction < __Type >, __comparisonFunction >;

} /* namespace cds */

#endif /* __CDS_COMPARATOR_HPP__ */
