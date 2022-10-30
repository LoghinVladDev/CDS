/*
 * Created by loghin on 6/26/22.
 */

#ifndef __CDS_COLLECTION_FUNCTIONS_HPP__ /* NOLINT(llvm-header-guard) */
#define __CDS_COLLECTION_FUNCTIONS_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

namespace cds {             /* NOLINT(modernize-concat-nested-namespaces) */
    namespace __hidden {    /* NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        namespace __impl {  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            /**
             * @typedef Represents the type of function used by the Collection to check if an Iterable contains a given element
             * @tparam __IterableType is the type of the iterable to check if the element is included in it
             * @tparam __ElementType is the type of the element to be checked if it is included in the given collection
             * @namespace cds :: __hidden :: __impl
             * @internal library-private
             */
            template < typename __IterableType, typename __ElementType >                                            /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            using __ContainsFunction __CDS_DeprecatedHint("Use Functional Interface instead of fixed Interface") =  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-avoid-non-const-global-variables) */
                    functional :: PredicateFunction < __IterableType const &, __ElementType const & >;

        } /* namespace __impl */
    } /* namespace __hidden */
} /* namespace cds */

#endif /* __CDS_COLLECTION_FUNCTIONS_HPP__ */
