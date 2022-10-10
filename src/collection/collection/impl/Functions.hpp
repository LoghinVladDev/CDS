/*
 * Created by loghin on 6/26/22.
 */

#ifndef __CDS_COLLECTION_FUNCTIONS_IMPL_HPP__
#define __CDS_COLLECTION_FUNCTIONS_IMPL_HPP__ /* NOLINT(bugprone-reserved-identifier) */

namespace cds {             /* NOLINT(modernize-concat-nested-namespaces) */
    namespace __hidden {    /* NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier) */
        namespace __impl {  /* NOLINT(bugprone-reserved-identifier) */

            template <
                    typename                                                __ElementType,  /* NOLINT(bugprone-reserved-identifier) */
                    cds :: utility :: ComparisonFunction < __ElementType >  __compare       /* NOLINT(bugprone-reserved-identifier) */
            > constexpr auto __CollectionFunctions <
                    __ElementType,
                    __compare
            > :: __cf_equals (
                    __ElementType const & left,
                    __ElementType const & right
            ) noexcept -> bool {

                return __compare ( left, right );
            }

        }
    }
}

#endif /* __CDS_COLLECTION_FUNCTIONS_IMPL_HPP__ */
