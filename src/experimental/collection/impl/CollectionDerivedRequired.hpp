//
// Created by loghin on 4/26/22.
//

#ifndef __CDS_COLLECTION_DERIVED_REQUIRED_HPP__
#define __CDS_COLLECTION_DERIVED_REQUIRED_HPP__

namespace cds {
    namespace experimental {

        template < typename T >
        template < typename Predicate >
        auto Collection < T > :: remove ( Predicate const & predicate, Size count ) noexcept -> Size {

        }

    }
}

#endif //__CDS_COLLECTION_DERIVED_REQUIRED_HPP__
