//
// Created by vladl on 4/7/2021.
//

#ifndef CDS_TYPES_HPP
#define CDS_TYPES_HPP


#include "../std-types.h"
#include "../prepro.h"

namespace cds {
    class Object;
    class String;
}

#include <cstring>
#include <string>

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace utility {

        template < typename T >
        constexpr auto unsafeAddress () noexcept -> T * { return reinterpret_cast < T * > (0x10); }

        template < typename T >
        __CDS_MaybeUnused constexpr auto unsafeConstAddress () noexcept -> T * { return reinterpret_cast < T const * > (0x10); }

    }
}

#endif //CDS_TYPES_HPP
