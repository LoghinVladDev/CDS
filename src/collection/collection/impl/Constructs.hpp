/* NOLINT(llvm-header-guard)
 * Created by loghin on 6/26/22.
 */

#ifndef __CDS_COLLECTION_CONSTRUCTS_IMPL_HPP__ /* NOLINT(llvm-header-guard) */
#define __CDS_COLLECTION_CONSTRUCTS_IMPL_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

namespace cds { /* NOLINT(modernize-concat-nested-namespaces) */

    template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    class Collection;

    namespace __hidden {    /* NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        namespace __impl {  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            inline auto __collectionContains (  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    cds :: Collection < __ElementType > const & collection,
                    __ElementType                       const & element
            ) noexcept -> bool {

                /* received type is collection, call contains */
                return collection.contains ( element );
            }


            template < typename __ElementType >     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            inline auto __collectionNotContains (   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    cds :: Collection < __ElementType > const & collection,
                    __ElementType                       const & element
            ) noexcept -> bool {

                /* received type is collection, call contains */
                return ! collection.contains ( element ); /* NOLINT(clion-misra-cpp2008-5-3-1) */
            }


            template <
                    typename                                                                            __ElementType,  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: PredicateFunction < __ElementType const &, __ElementType const & >    __function      /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > inline auto __initializerListContains (                                                                   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-avoid-non-const-global-variables) */
                    std :: initializer_list < __ElementType >   const & list,
                    __ElementType                               const & element
            ) noexcept -> bool {

                /* received type is initializer_list, iterate and compare. */
                for ( auto const & listElement : list ) {

                    /* If match found, true */
                    if ( __function ( listElement, element ) ) {
                        return true;
                    }
                }

                /* If fully parsed and no match, false */
                return false;
            }


            template <
                    typename                                                                            __ElementType,  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: PredicateFunction < __ElementType const &, __ElementType const & >    __function      /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > inline auto __initializerListNotContains (                                                                /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-avoid-non-const-global-variables) */
                    std :: initializer_list < __ElementType >   const & list,
                    __ElementType                               const & element
            ) noexcept -> bool {

                /* received type is initializer_list, iterate and compare. */
                for ( auto const & listElement : list ) {

                    /* If match found, false */
                    if ( __function ( listElement, element ) ) {
                        return false;
                    }
                }

                /* If fully parsed and no match, true */
                return true;
            }

        } /* namespace __impl */
    } /* namespace __hidden */
} /* namespace cds */

#endif /* __CDS_COLLECTION_CONSTRUCTS_IMPL_HPP__ */
