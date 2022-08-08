//
// Created by uic70278 on 7/23/2022.
//

#ifndef __CDS_SET_CONSTRUCTS_HPP__
#define __CDS_SET_CONSTRUCTS_HPP__

namespace cds {                 // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {    // NOLINT(modernize-concat-nested-namespaces)
        namespace meta {

            template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
            constexpr auto isValidSetElement () noexcept -> bool {

                return
                        cds :: meta :: equalToPossible < __ElementType, __ElementType > () ||
                        cds :: meta :: isDerivedFrom < __ElementType, cds :: Object > ();
            }

        }
    }
}

#endif // __CDS_SET_CONSTRUCTS_HPP__
