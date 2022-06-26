//
// Created by loghin on 6/26/22.
//

#ifndef __CDS_COLLECTION_CONSTRUCTS_HPP__
#define __CDS_COLLECTION_CONSTRUCTS_HPP__

namespace cds {                 // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {    // NOLINT(modernize-concat-nested-namespaces)

        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        class Collection;

        namespace __hidden {    // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier)
            namespace __impl {  // NOLINT(bugprone-reserved-identifier)

                template < typename __IterableType, typename __ElementType >                                // NOLINT(bugprone-reserved-identifier)
                using __ContainsFunction = auto ( __IterableType const &, __ElementType const & ) -> bool;  // NOLINT(bugprone-reserved-identifier)


                template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
                inline auto __collectionContains (  // NOLINT(bugprone-reserved-identifier)
                            cds :: experimental :: Collection < __ElementType > const & collection,
                            __ElementType                                       const & element
                ) noexcept -> bool;


                template <
                        typename __ElementType,                                     // NOLINT(bugprone-reserved-identifier)
                        utility :: ComparisonFunction < __ElementType > __function  // NOLINT(bugprone-reserved-identifier)
                > inline auto __initializerListContains (                           // NOLINT(bugprone-reserved-identifier)
                            std :: initializer_list < __ElementType >   const & list,
                            __ElementType                               const & element
                ) noexcept -> bool;

            }
        }
    }
}

#endif // __CDS_COLLECTION_CONSTRUCTS_HPP__
