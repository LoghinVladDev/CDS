//
// Created by loghin on 6/26/22.
//

#ifndef __CDS_SHARED_ITERABLE_CONTAINS_OF_HPP__
#define __CDS_SHARED_ITERABLE_CONTAINS_OF_HPP__

namespace cds {                 // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {    // NOLINT(modernize-concat-nested-namespaces)
        namespace __hidden {    // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier)
            namespace __impl {  // NOLINT(bugprone-reserved-identifier)

                template <
                        typename __IterableType,    // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType,     // NOLINT(bugprone-reserved-identifier)
                        typename __FromIterableType // NOLINT(bugprone-reserved-identifier)
                > class __IterableContainsOf {      // NOLINT(bugprone-reserved-identifier)

                protected:
                    __CDS_NoDiscard auto containsAnyOf (
                            __FromIterableType const & from
                    ) const noexcept -> bool;

                protected:
                    __CDS_NoDiscard auto containsAnyNotOf (
                            __FromIterableType const & from
                    ) const noexcept -> bool;

                protected:
                    __CDS_NoDiscard auto containsAllOf (
                            __FromIterableType const & from
                    ) const noexcept -> bool;

                protected:
                    __CDS_NoDiscard auto containsAllNotOf (
                            __FromIterableType const & from
                    ) const noexcept -> bool;
                };

            }
        }
    }
}

#endif // __CDS_SHARED_ITERABLE_CONTAINS_OF_HPP__
