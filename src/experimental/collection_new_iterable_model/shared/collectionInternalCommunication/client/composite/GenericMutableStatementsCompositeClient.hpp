//
// Created by loghin on 6/26/22.
//

#ifndef __CDS_SHARED_GENERIC_MUTABLE_STATEMENTS_COMPOSITE_CLIENT_HPP__
#define __CDS_SHARED_GENERIC_MUTABLE_STATEMENTS_COMPOSITE_CLIENT_HPP__

#include "../../../iterator/IteratorStatements.hpp"

namespace cds {                 // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {    // NOLINT(modernize-concat-nested-namespaces)
        namespace __hidden {    // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier)
            namespace __impl {  // NOLINT(bugprone-reserved-identifier)

                template <
                        typename __IterableType,                    // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType                      // NOLINT(bugprone-reserved-identifier)
                > class __GenericMutableStatementsCompositeClient { // NOLINT(bugprone-reserved-identifier)

                private:
                    using ElementType = __ElementType;

                protected:
                    template < typename __Action > // NOLINT(bugprone-reserved-identifier)
                    auto forEach (
                            __Action const & action
                    ) noexcept ( noexcept ( action ( cds :: meta :: referenceOf < ElementType > () ) ) ) -> void;

                protected:
                    template <
                            typename __Predicate = decltype ( & predicates :: alwaysTrue < ElementType > ) // NOLINT(bugprone-reserved-identifier)
                    > __CDS_NoDiscard auto some (
                            Size                count,
                            __Predicate const & predicate
                    ) noexcept ( noexcept ( predicate ( cds :: meta :: referenceOf < ElementType > () ) ) ) -> bool;

                protected:
                    template <
                            typename __Predicate = decltype ( & predicates :: alwaysTrue < ElementType > ) // NOLINT(bugprone-reserved-identifier)
                    > __CDS_NoDiscard auto atLeast (
                            Size                count,
                            __Predicate const & predicate
                    ) noexcept ( noexcept ( predicate ( cds :: meta :: referenceOf < ElementType > () ) ) ) -> bool;

                protected:
                    template <
                            typename __Predicate = decltype ( & predicates :: alwaysTrue < ElementType > ) // NOLINT(bugprone-reserved-identifier)
                    > __CDS_NoDiscard auto atMost (
                            Size                count,
                            __Predicate const & predicate
                    ) noexcept ( noexcept ( predicate ( cds :: meta :: referenceOf < ElementType > () ) ) ) -> bool;

                protected:
                    template <
                            typename __Predicate = decltype ( & predicates :: alwaysTrue < ElementType > ) // NOLINT(bugprone-reserved-identifier)
                    > __CDS_NoDiscard auto moreThan (
                            Size                count,
                            __Predicate const & predicate
                    ) noexcept ( noexcept ( predicate ( cds :: meta :: referenceOf < ElementType > () ) ) ) -> bool;

                protected:
                    template <
                            typename __Predicate = decltype ( & predicates :: alwaysTrue < ElementType > ) // NOLINT(bugprone-reserved-identifier)
                    > __CDS_NoDiscard auto fewerThan (
                            Size                count,
                            __Predicate const & predicate
                    ) noexcept ( noexcept ( predicate ( cds :: meta :: referenceOf < ElementType > () ) ) ) -> bool;

                protected:
                    template <
                            typename __Predicate = decltype ( & predicates :: alwaysTrue < ElementType > ) // NOLINT(bugprone-reserved-identifier)
                    > __CDS_NoDiscard auto count (
                            __Predicate const & predicate = & predicates :: alwaysTrue < __ElementType >
                    ) noexcept ( noexcept ( predicate ( cds :: meta :: referenceOf < ElementType > () ) ) ) -> Size;

                protected:
                    template <
                            typename __Predicate = decltype ( & predicates :: alwaysTrue < ElementType > ) // NOLINT(bugprone-reserved-identifier)
                    > __CDS_NoDiscard auto any (
                            __Predicate const & predicate
                    ) noexcept ( noexcept ( predicate ( cds :: meta :: referenceOf < ElementType > () ) ) ) -> bool;

                protected:
                    template <
                            typename __Predicate = decltype ( & predicates :: alwaysTrue < ElementType > ) // NOLINT(bugprone-reserved-identifier)
                    > __CDS_NoDiscard auto all (
                            __Predicate const & predicate
                    ) noexcept ( noexcept ( predicate ( cds :: meta :: referenceOf < ElementType > () ) ) ) -> bool;

                protected:
                    template <
                            typename __Predicate = decltype ( & predicates :: alwaysTrue < ElementType > ) // NOLINT(bugprone-reserved-identifier)
                    > __CDS_NoDiscard auto none (
                            __Predicate const & predicate
                    ) noexcept ( noexcept ( predicate ( cds :: meta :: referenceOf < ElementType > () ) ) ) -> bool;
                };


                template <
                        typename __IterableType,                            // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType                              // NOLINT(bugprone-reserved-identifier)
                > using __LocalGenericMutableStatementsCompositeClient =    // NOLINT(bugprone-reserved-identifier)
                        __GenericMutableStatementsCompositeClient <
                                __IterableType,
                                __ElementType
                        >;

            }
        }
    }
}

#include "../../../iterator/impl/IteratorStatements.hpp"

#endif // __CDS_SHARED_GENERIC_MUTABLE_STATEMENTS_COMPOSITE_CLIENT_HPP__
