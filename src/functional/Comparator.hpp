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
        virtual auto operator () (T const &, T const &) const noexcept -> bool = 0;
    };

}

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace utility {

        template <class T> __CDS_Requires( Comparable <T> )
        class __CDS_MaybeUnused DefaultSetComparator : public Comparator<T> {
        public:
            __CDS_OptimalInline auto operator () (T const & a, T const & b) const noexcept -> bool { return a < b; }
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

#endif //CDS_COMPARATOR_HPP
