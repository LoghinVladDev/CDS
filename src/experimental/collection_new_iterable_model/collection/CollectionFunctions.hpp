//
// Created by loghin on 6/26/22.
//

#ifndef __CDS_COLLECTION_FUNCTIONS_HPP__
#define __CDS_COLLECTION_FUNCTIONS_HPP__

namespace cds {                 // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {    // NOLINT(modernize-concat-nested-namespaces)
        namespace __hidden {    // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier)
            namespace __impl {  // NOLINT(bugprone-reserved-identifier)

                template < typename __IterableType, typename __ElementType >                                // NOLINT(bugprone-reserved-identifier)
                using __ContainsFunction = auto ( __IterableType const &, __ElementType const & ) -> bool;  // NOLINT(bugprone-reserved-identifier)


                template <
                        typename                                                __ElementType,                                          // NOLINT(bugprone-reserved-identifier)
                        cds :: utility :: ComparisonFunction < __ElementType >  __compare = & cds :: meta :: equals < __ElementType >   // NOLINT(bugprone-reserved-identifier)
                > class __CollectionFunctions {                                                                                         // NOLINT(bugprone-reserved-identifier)

                protected:
                    __CDS_NoDiscard constexpr auto __cf_equals ( // NOLINT(bugprone-reserved-identifier)
                            __ElementType const & left,
                            __ElementType const & right
                    ) const noexcept -> bool;
                };

            }
        }
    }
}

#endif // __CDS_COLLECTION_FUNCTIONS_HPP__
