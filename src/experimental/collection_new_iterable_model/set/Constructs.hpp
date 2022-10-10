/*
 * Created by loghin on 7/23/2022.
 */

#ifndef __CDS_EX_SET_CONSTRUCTS_HPP__
#define __CDS_EX_SET_CONSTRUCTS_HPP__ /* NOLINT(bugprone-reserved-identifier) */

namespace cds {                 /* NOLINT(modernize-concat-nested-namespaces) */
    namespace experimental {    /* NOLINT(modernize-concat-nested-namespaces) */

        namespace meta {

            template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
            __CDS_DeprecatedHint("No longer an experimental feature.") constexpr auto isValidSetElement () noexcept -> bool {

                return cds :: meta :: isValidSetElement < __ElementType > ();
            }

        }

        namespace __hidden {    /* NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier) */
            namespace __impl {  /* NOLINT(bugprone-reserved-identifier) */

                template < typename __ElementType >                                                         /* NOLINT(bugprone-reserved-identifier) */
                using __SetFindUniqueClient __CDS_DeprecatedHint("No longer an experimental feature.") =    /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __SetFindUniqueClient < __ElementType >;

            }
        }
    }
}

#endif /* __CDS_EX_SET_CONSTRUCTS_HPP__ */
