//
// Created by loghin on 4/26/22.
//

#ifndef __CDS_ARRAY_IMPL_HPP__
#define __CDS_ARRAY_IMPL_HPP__

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {

        template < typename T >
        Array < T > :: ~Array () noexcept {
            for ( Index i = 0U; i < this->_capacity; ++ i ) {
                Memory :: instance().destroy ( this->_pData[i] );
            }

            Memory :: instance().destroyArray ( this->_pData );
        }

    }
}

#endif // __CDS_ARRAY_IMPL_HPP__
