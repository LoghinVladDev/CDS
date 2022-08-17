//
// Created by loghin on 6/26/22.
//

#ifndef __CDS_SHARED_GENERIC_IMMUTABLE_STATEMENTS_COMPOSITE_CLIENT_HPP__
#define __CDS_SHARED_GENERIC_IMMUTABLE_STATEMENTS_COMPOSITE_CLIENT_HPP__ /* NOLINT(bugprone-reserved-identifier) */

#include "../../../iterator/IteratorStatements.hpp"
#include "../../../iterator/IteratorMemberStatements.hpp"

namespace cds {                 // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {    // NOLINT(modernize-concat-nested-namespaces)
        namespace __hidden {    // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier)
            namespace __impl {  // NOLINT(bugprone-reserved-identifier)

                template <
                        typename __IterableType,                        // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType                          // NOLINT(bugprone-reserved-identifier)
                > class __GenericImmutableStatementsCompositeClient {   // NOLINT(bugprone-reserved-identifier)

                private:
                    using ElementType = __ElementType;

                public:
                    template < typename __Action > // NOLINT(bugprone-reserved-identifier)
                    auto forEach (
                            __Action const & action
                    ) const noexcept ( noexcept ( __forEach (
                            cds :: meta :: addressOf < __IterableType const > ()->cbegin(),
                            cds :: meta :: addressOf < __IterableType const > ()->cend(),
                            action
                    ) ) ) -> void;

                public:
                    template <
                            typename __Predicate = decltype ( & predicates :: alwaysTrue < ElementType > ) // NOLINT(bugprone-reserved-identifier)
                    > __CDS_NoDiscard auto some (
                            Size                count,
                            __Predicate const & predicate
                    ) const noexcept ( noexcept ( __some (
                            cds :: meta :: addressOf < __IterableType const > ()->cbegin(),
                            cds :: meta :: addressOf < __IterableType const > ()->cend(),
                            count,
                            predicate
                    ) ) ) -> bool;

                public:
                    template <
                            typename __Predicate = decltype ( & predicates :: alwaysTrue < ElementType > ) // NOLINT(bugprone-reserved-identifier)
                    > __CDS_NoDiscard auto atLeast (
                            Size                count,
                            __Predicate const & predicate
                    ) const noexcept ( noexcept ( __atLeast (
                            cds :: meta :: addressOf < __IterableType const > ()->cbegin(),
                            cds :: meta :: addressOf < __IterableType const > ()->cend(),
                            count,
                            predicate
                    ) ) ) -> bool;

                public:
                    template <
                            typename __Predicate = decltype ( & predicates :: alwaysTrue < ElementType > ) // NOLINT(bugprone-reserved-identifier)
                    > __CDS_NoDiscard auto atMost (
                            Size                count,
                            __Predicate const & predicate
                    ) const noexcept ( noexcept ( __atMost (
                            cds :: meta :: addressOf < __IterableType const > ()->cbegin(),
                            cds :: meta :: addressOf < __IterableType const > ()->cend(),
                            count,
                            predicate
                    ) ) ) -> bool;

                public:
                    template <
                            typename __Predicate = decltype ( & predicates :: alwaysTrue < ElementType > ) // NOLINT(bugprone-reserved-identifier)
                    > __CDS_NoDiscard auto moreThan (
                            Size                count,
                            __Predicate const & predicate
                    ) const noexcept ( noexcept ( __moreThan (
                            cds :: meta :: addressOf < __IterableType const > ()->cbegin(),
                            cds :: meta :: addressOf < __IterableType const > ()->cend(),
                            count,
                            predicate
                    ) ) ) -> bool;

                public:
                    template <
                            typename __Predicate = decltype ( & predicates :: alwaysTrue < ElementType > ) // NOLINT(bugprone-reserved-identifier)
                    > __CDS_NoDiscard auto fewerThan (
                            Size                count,
                            __Predicate const & predicate
                    ) const noexcept ( noexcept ( __fewerThan (
                            cds :: meta :: addressOf < __IterableType const > ()->cbegin(),
                            cds :: meta :: addressOf < __IterableType const > ()->cend(),
                            count,
                            predicate
                    ) ) ) -> bool;

                public:
                    template <
                            typename __Predicate = decltype ( & predicates :: alwaysTrue < ElementType > ) // NOLINT(bugprone-reserved-identifier)
                    > __CDS_NoDiscard auto count (
                            __Predicate const & predicate = & predicates :: alwaysTrue < __ElementType >
                    ) const noexcept ( noexcept ( __count (
                            cds :: meta :: addressOf < __IterableType const > ()->cbegin(),
                            cds :: meta :: addressOf < __IterableType const > ()->cend(),
                            predicate
                    ) ) ) -> Size;

                public:
                    template <
                            typename __Predicate = decltype ( & predicates :: alwaysTrue < ElementType > ) // NOLINT(bugprone-reserved-identifier)
                    > __CDS_NoDiscard auto any (
                            __Predicate const & predicate
                    ) const noexcept ( noexcept ( __any (
                            cds :: meta :: addressOf < __IterableType const > ()->cbegin(),
                            cds :: meta :: addressOf < __IterableType const > ()->cend(),
                            predicate
                    ) ) ) -> bool;

                public:
                    template <
                            typename __Predicate = decltype ( & predicates :: alwaysTrue < ElementType > ) // NOLINT(bugprone-reserved-identifier)
                    > __CDS_NoDiscard auto all (
                            __Predicate const & predicate
                    ) const noexcept ( noexcept ( __all (
                            cds :: meta :: addressOf < __IterableType const > ()->cbegin(),
                            cds :: meta :: addressOf < __IterableType const > ()->cend(),
                            predicate
                    ) ) ) -> bool;

                public:
                    template <
                            typename __Predicate = decltype ( & predicates :: alwaysTrue < ElementType > ) // NOLINT(bugprone-reserved-identifier)
                    > __CDS_NoDiscard auto none (
                            __Predicate const & predicate
                    ) const noexcept ( noexcept ( __none (
                            cds :: meta :: addressOf < __IterableType const > ()->cbegin(),
                            cds :: meta :: addressOf < __IterableType const > ()->cend(),
                            predicate
                    ) ) ) -> bool;
                };


                template <
                        typename __IterableType,                            // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType                              // NOLINT(bugprone-reserved-identifier)
                > using __LocalGenericImmutableStatementsCompositeClient =  // NOLINT(bugprone-reserved-identifier)
                        __GenericImmutableStatementsCompositeClient <
                                __IterableType,
                                __ElementType
                        >;

            }
        }
    }
}

#include "../../../iterator/impl/IteratorStatements.hpp"
#include "../../../iterator/impl/IteratorMemberStatements.hpp"

#endif // __CDS_SHARED_GENERIC_IMMUTABLE_STATEMENTS_COMPOSITE_CLIENT_HPP__
