//
// Created by loghin on 6/26/22.
//

#ifndef __CDS_SHARED_CONTAINS_OF_COMPOSITE_CLIENT_HPP__
#define __CDS_SHARED_CONTAINS_OF_COMPOSITE_CLIENT_HPP__

namespace cds {                 // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {    // NOLINT(modernize-concat-nested-namespaces)
        namespace __hidden {    // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier)
            namespace __impl {  // NOLINT(bugprone-reserved-identifier)

                template <
                        typename __IterableType,        // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType,         // NOLINT(bugprone-reserved-identifier)
                        typename __FromIterableType     // NOLINT(bugprone-reserved-identifier)
                > class __ContainsOfCompositeClient {   // NOLINT(bugprone-reserved-identifier)

                public:
                    __CDS_NoDiscard auto containsAnyOf (
                            __FromIterableType const & from
                    ) const noexcept -> bool;

                public:
                    __CDS_NoDiscard auto containsAnyNotOf (
                            __FromIterableType const & from
                    ) const noexcept -> bool;

                public:
                    __CDS_NoDiscard auto containsAllOf (
                            __FromIterableType const & from
                    ) const noexcept -> bool;

                public:
                    __CDS_NoDiscard auto containsAllNotOf (
                            __FromIterableType const & from
                    ) const noexcept -> bool;
                };

            }
        }
    }
}

#endif // __CDS_SHARED_CONTAINS_OF_COMPOSITE_CLIENT_HPP__
