//
// Created by loghin on 6/26/22.
//

#ifndef __CDS_EX_ARRAY_HPP__
#define __CDS_EX_ARRAY_HPP__

#include "Collection.hpp"

namespace cds {
    namespace experimental {

        template < typename __ElementType >
        class Array : public Collection < __ElementType > {
        private:
            __ElementType v[64];
            Size s{0};

        public:
            void pushBack ( __ElementType const & e ) {
                this->v[this->s++] = e;
            }
        };

    }
}

#endif // __CDS_ARRAY_HPP__
