/*
 * Created by loghin on 10.11.2021.
 */

#ifndef __CDS_COMPARATOR_HPP__ /* NOLINT(llvm-header-guard) */
#define __CDS_COMPARATOR_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

#include <CDS/Compiler>
#include "../shared/impl/generalPredicates.hpp"

namespace cds {

    template < typename T >
    class Comparator {
    public:
        virtual auto operator () (T const &, T const &) const noexcept (false) -> bool = 0;
    };

}

namespace cds {

    namespace utility {

        template < typename __Type > // NOLINT(bugprone-reserved-identifier)
        using ComparisonFunction = decltype ( & cds :: meta :: equals < __Type, __Type > );

    }

    template < typename __Type, utility :: ComparisonFunction < __Type > __comparisonFunction > // NOLINT(bugprone-reserved-identifier)
    class FunctionComparator {
    public:
        __CDS_NoDiscard constexpr auto operator () (
                __Type const & left,
                __Type const & right
        ) const noexcept ( noexcept ( __comparisonFunction ( left, right ) ) ) -> bool {

            return __comparisonFunction ( left, right );
        }
    };

}

#endif /* __CDS_COMPARATOR_HPP__ */
