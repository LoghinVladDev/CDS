/*
 * Created by loghin on 6/26/22.
 */

#ifndef __CDS_ITERABLE_CONSTRUCTS_IMPL_HPP__ /* NOLINT(llvm-header-guard) */
#define __CDS_ITERABLE_CONSTRUCTS_IMPL_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

namespace cds { /* NOLINT(modernize-concat-nested-namespaces) */

    template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    class Iterable;

    namespace __hidden {    /* NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        namespace __impl {  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            inline auto __iterableContains (    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    cds :: Iterable < __ElementType >   const & iterable,
                    __ElementType                       const & element
            ) noexcept -> bool {

                /* received type is iterable, call contains */
                return iterable.contains ( element );
            }


            template < typename __ElementType >     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            inline auto __iterableNotContains (     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    cds :: Iterable < __ElementType >   const & iterable,
                    __ElementType                       const & element
            ) noexcept -> bool {

                /* received type is iterable, call contains */
                return ! iterable.contains ( element );
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

#endif /* __CDS_ITERABLE_CONSTRUCTS_IMPL_HPP__ */
