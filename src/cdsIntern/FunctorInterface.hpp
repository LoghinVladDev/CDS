//
// Created by loghin on 10.11.2021.
//

#ifndef CDS_FUNCTORINTERFACE_HPP
#define CDS_FUNCTORINTERFACE_HPP

namespace cds {

    template < typename T >
    class Comparator {
    public:
        virtual auto operator () (T const &, T const &) const noexcept -> bool = 0;
    };

}

#endif //CDS_FUNCTORINTERFACE_HPP
