/*
 * Created by loghin on 6/26/22.
 */

#ifndef __CDS_SHARED_CONTAINS_OF_COMPOSITE_CLIENT_IMPL_HPP__ /* NOLINT(llvm-header-guard) */
#define __CDS_SHARED_CONTAINS_OF_COMPOSITE_CLIENT_IMPL_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

namespace cds {             /* NOLINT(modernize-concat-nested-namespaces) */
    namespace __hidden {    /* NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        namespace __impl {  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            template <
                    typename                                                    __IterableType,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                    __ElementType,      /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                    __FromIterableType, /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __ContainsFunction < __FromIterableType, __ElementType >    __contains          /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > auto __ContainsOfCompositeClient <
                    __IterableType,
                    __ElementType,
                    __FromIterableType,
                    __contains
            > :: containsAnyOf (
                    __FromIterableType const & from
            ) const noexcept -> bool {

                /* parse the received iterable's elements */
                for ( auto iterator = from.begin(), end = from.end(); iterator != end; ++ iterator ) {

                    /* if any is found in the caller iterable, caller contains any of the parameter's elements
                     *
                     * Use caller contains as it might be optimized ( HashSet / HashMap ), as compared to
                     * parameter contains, which could be linear */
                    if ( reinterpret_cast < __IterableType const * > ( this )->contains ( * iterator ) ) {
                        return true;
                    }
                }

                /* otherwise, no matching element found. Return false */
                return false;
            }


            template <
                    typename                                                    __IterableType,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                    __ElementType,      /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                    __FromIterableType, /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __ContainsFunction < __FromIterableType, __ElementType >    __contains          /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > auto __ContainsOfCompositeClient <
                    __IterableType,
                    __ElementType,
                    __FromIterableType,
                    __contains
            > :: containsAnyNotOf (
                    __FromIterableType const & from
            ) const noexcept -> bool {

                /* when checking contains any not of, checking must be done from caller. Parse caller's elements */
                for (
                        auto
                                iterator    = reinterpret_cast < __IterableType const * > ( this )->cbegin(),
                                end         = reinterpret_cast < __IterableType const * > ( this )->cend();
                        iterator != end;
                        ++ iterator
                ) {

                    /* If parameter iterable does not contain an element, the iterable contains elements not of the given iterable */
                    if ( ! __contains ( from, * iterator ) ) {
                        return true;
                    }
                }

                /* Otherwise, no element not to be found in the given iterable was found, return false */
                return false;
            }


            template <
                    typename                                                    __IterableType,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                    __ElementType,      /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                    __FromIterableType, /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __ContainsFunction < __FromIterableType, __ElementType >    __contains          /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > auto __ContainsOfCompositeClient <
                    __IterableType,
                    __ElementType,
                    __FromIterableType,
                    __contains
            > :: containsAllOf (
                    __FromIterableType const & from
            ) const noexcept -> bool {

                /* Parse received iterable */
                for ( auto iterator = from.begin(), end = from.end(); iterator != end; ++ iterator ) {

                    /* If any element of the iterable is not found in the caller iterable, return false
                     *
                     * Same reason for reverse approach as 'containsAnyOf' */
                    if ( ! reinterpret_cast < __IterableType const * > ( this )->contains ( * iterator ) ) {
                        return false;
                    }
                }

                /* Otherwise, all elements in given iterable have a match in the caller one. Return true */
                return true;
            }


            template <
                    typename                                                    __IterableType,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                    __ElementType,      /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                    __FromIterableType, /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __ContainsFunction < __FromIterableType, __ElementType >    __contains          /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > auto __ContainsOfCompositeClient <
                    __IterableType,
                    __ElementType,
                    __FromIterableType,
                    __contains
            > :: containsNoneOf (
                    __FromIterableType const & from
            ) const noexcept -> bool {

                /* Parse the received iterable's elements */
                for ( auto iterator = from.begin(), end = from.end(); iterator != end; ++ iterator ) {

                    /* If any has a match in the caller iterable, it contains at least one element, return false
                     *
                     * Reason for reverse approach same as in 'containsAnyOf' */
                    if ( reinterpret_cast < __IterableType const * > ( this )->contains ( * iterator ) ) {
                        return false;
                    }
                }

                /* Otherwise, no element in received iterable found in caller, caller contains none of the values in the
                 * received iterable, return true */
                return true;
            }

        } /* namespace __impl */
    } /* namespace __hidden */
} /* namespace cds */

#endif /* __CDS_SHARED_CONTAINS_OF_COMPOSITE_CLIENT_IMPL_HPP__ */
