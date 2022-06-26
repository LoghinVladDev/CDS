//
// Created by loghin on 6/26/22.
//

#ifndef __CDS_SHARED_ITERABLE_IMMUTABLE_STATEMENTS_HPP__
#define __CDS_SHARED_ITERABLE_IMMUTABLE_STATEMENTS_HPP__

#include "../iterator/IteratorStatements.hpp"

namespace cds {                 // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {    // NOLINT(modernize-concat-nested-namespaces)
        namespace __hidden {    // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier)
            namespace __impl {  // NOLINT(bugprone-reserved-identifier)

                template <
                        typename __IterableType,        // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType          // NOLINT(bugprone-reserved-identifier)
                > class __IterableImmutableStatements { // NOLINT(bugprone-reserved-identifier)

                private:
                    using ElementType = __ElementType;

                protected:
                    template < typename __Action > // NOLINT(bugprone-reserved-identifier)
                    auto forEach (
                            __Action const & action
                    ) const noexcept ( noexcept ( action ( cds :: meta :: referenceOf < ElementType const > () ) ) ) -> void;

                protected:
                    template <
                            typename __Predicate = decltype ( & predicates :: alwaysTrue < ElementType > ) // NOLINT(bugprone-reserved-identifier)
                    > auto some (
                            Size                count,
                            __Predicate const & predicate
                    ) const noexcept ( noexcept ( predicate ( cds :: meta :: referenceOf < ElementType const > () ) ) ) -> bool;

                protected:
                    template <
                            typename __Predicate = decltype ( & predicates :: alwaysTrue < ElementType > ) // NOLINT(bugprone-reserved-identifier)
                    > auto atLeast (
                            Size                count,
                            __Predicate const & predicate
                    ) const noexcept ( noexcept ( predicate ( cds :: meta :: referenceOf < ElementType const > () ) ) ) -> bool;

                protected:
                    template <
                            typename __Predicate = decltype ( & predicates :: alwaysTrue < ElementType > ) // NOLINT(bugprone-reserved-identifier)
                    > auto atMost (
                            Size                count,
                            __Predicate const & predicate
                    ) const noexcept ( noexcept ( predicate ( cds :: meta :: referenceOf < ElementType const > () ) ) ) -> bool;

                protected:
                    template <
                            typename __Predicate = decltype ( & predicates :: alwaysTrue < ElementType > ) // NOLINT(bugprone-reserved-identifier)
                    > auto moreThan (
                            Size                count,
                            __Predicate const & predicate
                    ) const noexcept ( noexcept ( predicate ( cds :: meta :: referenceOf < ElementType const > () ) ) ) -> bool;

                protected:
                    template <
                            typename __Predicate = decltype ( & predicates :: alwaysTrue < ElementType > ) // NOLINT(bugprone-reserved-identifier)
                    > auto fewerThan (
                            Size                count,
                            __Predicate const & predicate
                    ) const noexcept ( noexcept ( predicate ( cds :: meta :: referenceOf < ElementType const > () ) ) ) -> bool;

                protected:
                    template <
                            typename __Predicate = decltype ( & predicates :: alwaysTrue < ElementType > ) // NOLINT(bugprone-reserved-identifier)
                    > auto count (
                            __Predicate const & predicate
                    ) const noexcept ( noexcept ( predicate ( cds :: meta :: referenceOf < ElementType const > () ) ) ) -> Size;

                protected:
                    template <
                            typename __Predicate = decltype ( & predicates :: alwaysTrue < ElementType > ) // NOLINT(bugprone-reserved-identifier)
                    > auto any (
                            __Predicate const & predicate
                    ) const noexcept ( noexcept ( predicate ( cds :: meta :: referenceOf < ElementType const > () ) ) ) -> bool;

                protected:
                    template <
                            typename __Predicate = decltype ( & predicates :: alwaysTrue < ElementType > ) // NOLINT(bugprone-reserved-identifier)
                    > auto all (
                            __Predicate const & predicate
                    ) const noexcept ( noexcept ( predicate ( cds :: meta :: referenceOf < ElementType const > () ) ) ) -> bool;

                protected:
                    template <
                            typename __Predicate = decltype ( & predicates :: alwaysTrue < ElementType > ) // NOLINT(bugprone-reserved-identifier)
                    > auto none (
                            __Predicate const & predicate
                    ) const noexcept ( noexcept ( predicate ( cds :: meta :: referenceOf < ElementType const > () ) ) ) -> bool;
                };

            }
        }
    }
}

#include "../iterator/impl/IteratorStatements.hpp"

#endif // __CDS_SHARED_ITERABLE_IMMUTABLE_STATEMENTS_HPP__
