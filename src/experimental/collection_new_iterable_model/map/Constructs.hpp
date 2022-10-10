/*
 * Created by loghin on 10/08/22.
 */

#ifndef __CDS_EX_MAP_CONSTRUCTS_HPP__
#define __CDS_EX_MAP_CONSTRUCTS_HPP__ /* NOLINT(bugprone-reserved-identifier) */

namespace cds {                 /* NOLINT(modernize-concat-nested-namespaces) */
    namespace experimental {    /* NOLINT(modernize-concat-nested-namespaces) */
        namespace __hidden {    /* NOLINT(bugprone-reserved-identifier, modernize-concat-nested-namespaces) */
            namespace __impl {  /* NOLINT(bugprone-reserved-identifier) */

                template < typename __KeyType, typename __ValueType >                                               /* NOLINT(bugprone-reserved-identifier) */
                using __MapFindUniqueImmutableClient __CDS_DeprecatedHint("No longer an experimental feature.") =   /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __MapFindUniqueImmutableClient < __KeyType, __ValueType >;


                template < typename __KeyType, typename __ValueType >                                           /* NOLINT(bugprone-reserved-identifier) */
                using __MapFindUniqueMutableClient __CDS_DeprecatedHint("No longer an experimental feature.") = /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __MapFindUniqueMutableClient < __KeyType, __ValueType >;

            }
        }

    }
}

#endif /* __CDS_EX_MAP_CONSTRUCTS_HPP__ */
