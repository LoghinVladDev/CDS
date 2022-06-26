//
// Created by loghin on 6/26/22.
//

#ifndef __CDS_SHARED_ITERABLE_CONTAINS_OF_IMPL_HPP__
#define __CDS_SHARED_ITERABLE_CONTAINS_OF_IMPL_HPP__

namespace cds {                 // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {    // NOLINT(modernize-concat-nested-namespaces)
        namespace __hidden {    // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier)
            namespace __impl {  // NOLINT(bugprone-reserved-identifier)

                template <
                        typename __IterableType,    // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType,     // NOLINT(bugprone-reserved-identifier)
                        typename __FromIterableType // NOLINT(bugprone-reserved-identifier)
                > auto __IterableContainsOf <
                        __IterableType,
                        __ElementType,
                        __FromIterableType
                > :: containsAnyOf (
                        __FromIterableType const & from
                ) const noexcept -> bool {

                    for ( auto iterator = from.begin(), end = from.end(); iterator != end; ++ iterator ) {
                        if ( static_cast < __IterableType const * > ( this )->contains ( * iterator ) ) {
                            return true;
                        }
                    }

                    return false;
                }

                template <
                        typename __IterableType,    // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType,     // NOLINT(bugprone-reserved-identifier)
                        typename __FromIterableType // NOLINT(bugprone-reserved-identifier)
                > auto __IterableContainsOf <
                        __IterableType,
                        __ElementType,
                        __FromIterableType
                > :: containsAnyNotOf (
                        __FromIterableType const & from
                ) const noexcept -> bool {

                    for ( auto iterator = from.begin(), end = from.end(); iterator != end; ++ iterator ) {
                        if ( ! static_cast < __IterableType const * > ( this )->contains ( * iterator ) ) {
                            return true;
                        }
                    }

                    return false;
                }

                template <
                        typename __IterableType,    // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType,     // NOLINT(bugprone-reserved-identifier)
                        typename __FromIterableType // NOLINT(bugprone-reserved-identifier)
                > auto __IterableContainsOf <
                        __IterableType,
                        __ElementType,
                        __FromIterableType
                > :: containsAllOf (
                        __FromIterableType const & from
                ) const noexcept -> bool {

                    for ( auto iterator = from.begin(), end = from.end(); iterator != end; ++ iterator ) {
                        if ( ! static_cast < __IterableType const * > ( this )->contains ( * iterator ) ) {
                            return false;
                        }
                    }

                    return true;
                }

                template <
                        typename __IterableType,    // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType,     // NOLINT(bugprone-reserved-identifier)
                        typename __FromIterableType // NOLINT(bugprone-reserved-identifier)
                > auto __IterableContainsOf <
                        __IterableType,
                        __ElementType,
                        __FromIterableType
                > :: containsAllNotOf (
                        __FromIterableType const & from
                ) const noexcept -> bool {

                    for ( auto iterator = from.begin(), end = from.end(); iterator != end; ++ iterator ) {
                        if ( static_cast < __IterableType const * > ( this )->contains ( * iterator ) ) {
                            return true;
                        }
                    }

                    return false;
                }

            }
        }
    }
}

#endif // __CDS_SHARED_ITERABLE_CONTAINS_OF_IMPL_HPP__
