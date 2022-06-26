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

                template < typename __ElementType >     // NOLINT(bugprone-reserved-identifier)
                class __CollectionContainsFunction {    // NOLINT(bugprone-reserved-identifier)

                public:
                    __CDS_NoDiscard auto operator () (
                            cds :: experimental :: Collection < __ElementType > const & collection,
                            __ElementType                                       const & element
                    ) const noexcept -> bool;
                };

                template <
                        typename __ElementType,                                     // NOLINT(bugprone-reserved-identifier)
                        utility :: ComparisonFunction < __ElementType > __function  // NOLINT(bugprone-reserved-identifier)
                > class __InitializerListContainsFunction {                         // NOLINT(bugprone-reserved-identifier)

                public:
                    __CDS_NoDiscard auto operator () (
                            std :: initializer_list < __ElementType >   const & list,
                            __ElementType                               const & element
                    ) const noexcept -> bool;
                };

            }
        }
    }
}

#endif // __CDS_COLLECTION_CONSTRUCTS_HPP__
