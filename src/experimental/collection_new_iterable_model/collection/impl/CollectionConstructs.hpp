//
// Created by loghin on 6/26/22.
//

#ifndef __CDS_COLLECTION_CONSTRUCTS_IMPL_HPP__
#define __CDS_COLLECTION_CONSTRUCTS_IMPL_HPP__ /* NOLINT(bugprone-reserved-identifier) */

namespace cds {                 /* NOLINT(modernize-concat-nested-namespaces) */
    namespace experimental {    /* NOLINT(modernize-concat-nested-namespaces) */

        template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
        class Collection;

        namespace __hidden {    /* NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier) */
            namespace __impl {  /* NOLINT(bugprone-reserved-identifier) */

                template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
                inline auto __collectionContains (  /* NOLINT(bugprone-reserved-identifier) */
                        cds :: experimental :: Collection < __ElementType > const & collection,
                        __ElementType                                       const & element
                ) noexcept -> bool {

                    /* received type is collection, call contains */
                    return collection.contains ( element );
                }


                template <
                        typename __ElementType,                                     /* NOLINT(bugprone-reserved-identifier) */
                        utility :: ComparisonFunction < __ElementType > __function  /* NOLINT(bugprone-reserved-identifier) */
                > inline auto __initializerListContains (                           /* NOLINT(bugprone-reserved-identifier) */
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

            }
        }
    }
}

#endif /* __CDS_COLLECTION_CONSTRUCTS_IMPL_HPP__ */
