//
// Created by loghin on 10.11.2021.
//

#ifndef CDS_SELECTOR_HPP
#define CDS_SELECTOR_HPP

#include <CDS/std-types>
#include <CDS/Compiler>

namespace cds {

    template < typename T >
    class Selector {
    public:
        virtual auto operator()(T const &) const noexcept -> Index = 0;
    };

}

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace utility {

        template < typename T >
        class __CDS_MaybeUnused DefaultSelector : public Selector < T > {
        public:
        auto operator () (T const & obj) const noexcept -> Index { return (Index) obj; }
    };

}
}

#endif //CDS_SELECTOR_HPP
