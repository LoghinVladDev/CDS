/*
 * Created by loghin on 6/26/22.
 */

#ifndef __CDS_COLLECTION_FUNCTIONS_IMPL_HPP__ /* NOLINT(llvm-header-guard) */
#define __CDS_COLLECTION_FUNCTIONS_IMPL_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

namespace cds {             /* NOLINT(modernize-concat-nested-namespaces) */
    namespace __hidden {    /* NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        namespace __impl {  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            template <
                    typename                                                __ElementType,  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    cds :: utility :: ComparisonFunction < __ElementType >  __compare       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > constexpr auto __CollectionFunctions <
                    __ElementType,
                    __compare
            > :: __cf_equals (
                    __ElementType const & left,
                    __ElementType const & right
            ) noexcept -> bool {

                return __compare ( left, right );
            }

        } /* namespace __impl */
    } /* namespace __hidden */
} /* namespace cds */

#endif /* __CDS_COLLECTION_FUNCTIONS_IMPL_HPP__ */
