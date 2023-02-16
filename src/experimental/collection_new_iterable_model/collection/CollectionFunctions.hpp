/*
 * Created by loghin on 6/26/22.
 */

#ifndef __CDS_EX_COLLECTION_FUNCTIONS_HPP__
#define __CDS_EX_COLLECTION_FUNCTIONS_HPP__ /* NOLINT(bugprone-reserved-identifier) */

namespace cds {                 /* NOLINT(modernize-concat-nested-namespaces) */
    namespace experimental {    /* NOLINT(modernize-concat-nested-namespaces) */
        namespace __hidden {    /* NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier) */
            namespace __impl {  /* NOLINT(bugprone-reserved-identifier) */

                template < typename __IterableType, typename __ElementType >                                /* NOLINT(bugprone-reserved-identifier) */
                using __ContainsFunction __CDS_DeprecatedHint("No longer an experimental feature.") =       /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __ContainsFunction < __IterableType, __ElementType >;

                template <
                        typename                                                __ElementType,                                          /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: ComparisonFunction < __ElementType >  __compare = & cds :: meta :: equals < __ElementType >   /* NOLINT(bugprone-reserved-identifier) */
                > using __CollectionFunctions __CDS_DeprecatedHint("No longer an experimental feature.") =                              /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __IterableFunctions < __ElementType, __compare >;

            }
        }
    }
}

#endif /* __CDS_EX_COLLECTION_FUNCTIONS_HPP__ */
