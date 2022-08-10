//
// Created by loghin on 6/26/22.
//

#ifndef __CDS_COLLECTION_CONSTRUCTS_IMPL_HPP__
#define __CDS_COLLECTION_CONSTRUCTS_IMPL_HPP__

namespace cds {                 // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {    // NOLINT(modernize-concat-nested-namespaces)

        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        class Collection;

        namespace __hidden {    // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier)
            namespace __impl {  // NOLINT(bugprone-reserved-identifier)

                template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
                inline auto __collectionContains (  // NOLINT(bugprone-reserved-identifier)
                        cds :: experimental :: Collection < __ElementType > const & collection,
                        __ElementType                                       const & element
                ) noexcept -> bool {

                    return collection.contains ( element );
                }


                template <
                        typename __ElementType,                                     // NOLINT(bugprone-reserved-identifier)
                        utility :: ComparisonFunction < __ElementType > __function  // NOLINT(bugprone-reserved-identifier)
                > inline auto __initializerListContains (                           // NOLINT(bugprone-reserved-identifier)
                        std :: initializer_list < __ElementType >   const & list,
                        __ElementType                               const & element
                ) noexcept -> bool {

                    for ( auto const & listElement : list ) {
                        if ( __function ( listElement, element ) ) {
                            return true;
                        }
                    }

                    return false;
                }

            }
        }
    }
}

#endif // __CDS_COLLECTION_CONSTRUCTS_IMPL_HPP__
