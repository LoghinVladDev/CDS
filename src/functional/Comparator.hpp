//
// Created by loghin on 10.11.2021.
//

#ifndef CDS_COMPARATOR_HPP
#define CDS_COMPARATOR_HPP

#include <CDS/Compiler>

namespace cds {

    template < typename T >
    class Comparator {
    public:
        virtual auto operator () (T const &, T const &) const noexcept (false) -> bool = 0;
    };

}

#include "../shared/impl/generalPredicates.hpp"

namespace cds {

    namespace utility {

        template < typename __Type > // NOLINT(bugprone-reserved-identifier)
        using ComparisonFunction = decltype ( & predicates :: lessThan < __Type > );

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

#endif //CDS_COMPARATOR_HPP
