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

                template < typename __ElementType >     // NOLINT(bugprone-reserved-identifier)
                __CDS_OptimalInline auto __CollectionContainsFunction < __ElementType > :: operator () (
                        Collection < __ElementType >    const & collection,
                        __ElementType                   const & element
                ) const noexcept -> bool {

                    return collection.contains ( element );
                }


                template <
                        typename __ElementType,                                     // NOLINT(bugprone-reserved-identifier)
                        utility :: ComparisonFunction < __ElementType > __function  // NOLINT(bugprone-reserved-identifier)
                > __CDS_OptimalInline auto __InitializerListContainsFunction <
                        __ElementType,
                        __function
                > :: operator () (
                        std :: initializer_list < __ElementType >   const & list,
                        __ElementType                               const & element
                ) const noexcept -> bool {

                    for ( auto const & e : list ) {
                        if ( __function ( e, element ) ) {
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
