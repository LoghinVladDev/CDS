//
// Created by loghin on 6/26/22.
//

#ifndef __CDS_COLLECTION_FUNCTIONS_HPP__
#define __CDS_COLLECTION_FUNCTIONS_HPP__

namespace cds {                 // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {    // NOLINT(modernize-concat-nested-namespaces)
        namespace __hidden {    // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier)
            namespace __impl {  // NOLINT(bugprone-reserved-identifier)

                template <
                        typename __ElementType,                 // NOLINT(bugprone-reserved-identifier)
                        typename __ElementTypeEqualsFunction    // NOLINT(bugprone-reserved-identifier)
                > class __CollectionFunctions {                 // NOLINT(bugprone-reserved-identifier)

                private:
                    __CDS_NoUniqueAddress __ElementTypeEqualsFunction _equals;

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
