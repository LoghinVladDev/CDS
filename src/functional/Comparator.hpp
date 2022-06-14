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

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace utility {

        template <class T> __CDS_Requires( Comparable <T> )
        class __CDS_MaybeUnused DefaultSetComparator : public Comparator<T> {
        public:
            __CDS_OptimalInline auto operator () (T const & left, T const & right) const noexcept -> bool { return left < right; }
        };

    }
}

#if __CDS_cpplang_Concepts_available == true

namespace cds {

    template <class T, class C>
    concept ValidSetComparator =
        std :: is_base_of < Comparator<T>, C > :: value ||
        std :: is_invocable < C, T, T > :: type :: value;

}

#endif

#include "../shared/impl/generalPredicates.hpp"

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {

        namespace utility {

            template < typename __Type > // NOLINT(bugprone-reserved-identifier)
            using ComparisonFunction = decltype ( & predicates :: lessThan < __Type > );

        }

        template < typename __Type, utility :: ComparisonFunction < __Type > __comparisonFunction > // NOLINT(bugprone-reserved-identifier)
        class FunctionComparator : public Comparator < __Type > {
        public:
            __CDS_NoDiscard constexpr auto operator () (
                    __Type const & left,
                    __Type const & right
            ) const noexcept ( noexcept ( __comparisonFunction ( left, right ) ) ) -> bool {

                return __comparisonFunction ( left, right );
            }
        };

    }
}

#endif //CDS_COMPARATOR_HPP
