//
// Created by loghin on 6/3/22.
//

#ifndef __CDS_EX_SET_META_HPP__
#define __CDS_EX_SET_META_HPP__

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental { // NOLINT(modernize-concat-nested-namespaces)
        namespace meta {

            template < typename T >
            constexpr auto isValidSetElement () noexcept -> bool {
                return meta :: equalToPossible < T, T > () || meta :: isDerivedFrom < T, Object > ();
            }

        }
    }
}

#endif // __CDS_EX_SET_META_HPP__
