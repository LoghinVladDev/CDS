//
// Created by loghin on 6/3/22.
//

#ifndef __CDS_SET_META_HPP__
#define __CDS_SET_META_HPP__

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace meta {

        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        constexpr auto isValidSetElement () noexcept -> bool {

            return cds :: meta :: equalToPossible < __ElementType, __ElementType > () || cds :: meta :: isDerivedFrom < __ElementType, Object > ();
        }

    }
}

#endif // __CDS_SET_META_HPP__
