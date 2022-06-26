//
// Created by loghin on 6/26/22.
//

#ifndef __CDS_COLLECTION_FUNCTIONS_IMPL_HPP__
#define __CDS_COLLECTION_FUNCTIONS_IMPL_HPP__

namespace cds {                 // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {    // NOLINT(modernize-concat-nested-namespaces)
        namespace __hidden {    // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier)
            namespace __impl {  // NOLINT(bugprone-reserved-identifier)

                template <
                        typename __ElementType,                 // NOLINT(bugprone-reserved-identifier)
                        typename __ElementTypeEqualsFunction    // NOLINT(bugprone-reserved-identifier)
                > constexpr auto __CollectionFunctions <
                        __ElementType,
                        __ElementTypeEqualsFunction
                > :: __cf_equals (
                        __ElementType const & left,
                        __ElementType const & right
                ) const noexcept -> bool {

                    return this->_equals ( left, right );
                }

            }
        }
    }
}

#endif // __CDS_COLLECTION_FUNCTIONS_IMPL_HPP__