//
// Created by loghin on 6/9/22.
//

#ifndef __CDS_HASH_BASE_FUNCTION_HPP__
#define __CDS_HASH_BASE_FUNCTION_HPP__

namespace cds {

    template < typename T >
    constexpr static auto hash (
            T const & object
    ) noexcept -> Size {

        return 0ULL;
    }

}


#endif // __CDS_HASH_BASE_FUNCTION_HPP__
