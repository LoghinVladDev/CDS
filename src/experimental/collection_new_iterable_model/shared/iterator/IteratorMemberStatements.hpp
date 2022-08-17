//
// Created by loghin on 17/08/22.
//

#ifndef __CDS_SHARED_ITERATOR_MEMBER_STATEMENTS_HPP__
#define __CDS_SHARED_ITERATOR_MEMBER_STATEMENTS_HPP__ /* NOLINT(bugprone-reserved-identifier) */

namespace cds {                 /* NOLINT(modernize-concat-nested-namespaces) */
    namespace experimental {    /* NOLINT(modernize-concat-nested-namespaces) */
        namespace __hidden {    /* NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier) */
            namespace __impl {  /* NOLINT(bugprone-reserved-identifier) */

                template <
                        typename __IteratorType,
                        typename __Action,
                        cds :: meta :: EnableIf <
                                cds :: meta :: isMemberFunctionPointer <
                                        __Action,
                                        cds :: meta :: Decay < decltype ( * cds :: meta :: valueOf < __IteratorType > () ) >
                                > ()
                        > = 0
                > constexpr auto __forEach (
                        __IteratorType  const & begin,
                        __IteratorType  const & end,
                        __Action        const & action
                ) noexcept ( noexcept ( ( ( * begin ).* action ) () ) ) -> void;

                template <
                        typename __IteratorType,            /* NOLINT(bugprone-reserved-identifier) */
                        typename __Predicate,               /* NOLINT(bugprone-reserved-identifier) */
                        cds :: meta :: EnableIf <
                                cds :: meta :: isMemberFunctionPointer <
                                        __Predicate,
                                        cds :: meta :: Decay < decltype ( * cds :: meta :: valueOf < __IteratorType > () ) >
                                > ()
                        > = 0
                > __CDS_NoDiscard constexpr auto __some (   /* NOLINT(bugprone-reserved-identifier) */
                        __IteratorType const & begin,
                        __IteratorType const & end,
                        Size                   count,
                        __Predicate    const & predicate
                ) noexcept ( noexcept ( ( ( * begin ).* predicate ) () ) ) -> bool;

                template <
                        typename __IteratorType,            /* NOLINT(bugprone-reserved-identifier) */
                        typename __Predicate,               /* NOLINT(bugprone-reserved-identifier) */
                        cds :: meta :: EnableIf <
                                cds :: meta :: isMemberFunctionPointer <
                                        __Predicate,
                                        cds :: meta :: Decay < decltype ( * cds :: meta :: valueOf < __IteratorType > () ) >
                                > ()
                        > = 0
                > __CDS_NoDiscard constexpr auto __atLeast (    /* NOLINT(bugprone-reserved-identifier) */
                        __IteratorType const & begin,
                        __IteratorType const & end,
                        Size                   count,
                        __Predicate    const & predicate
                ) noexcept ( noexcept ( ( ( * begin ).* predicate ) () ) ) -> bool;

                template <
                        typename __IteratorType,            /* NOLINT(bugprone-reserved-identifier) */
                        typename __Predicate,               /* NOLINT(bugprone-reserved-identifier) */
                        cds :: meta :: EnableIf <
                                cds :: meta :: isMemberFunctionPointer <
                                        __Predicate,
                                        cds :: meta :: Decay < decltype ( * cds :: meta :: valueOf < __IteratorType > () ) >
                                > ()
                        > = 0
                > __CDS_NoDiscard constexpr auto __atMost ( /* NOLINT(bugprone-reserved-identifier) */
                        __IteratorType const & begin,
                        __IteratorType const & end,
                        Size                   count,
                        __Predicate    const & predicate
                ) noexcept ( noexcept ( ( ( * begin ).* predicate ) () ) ) -> bool;

                template <
                        typename __IteratorType,            /* NOLINT(bugprone-reserved-identifier) */
                        typename __Predicate,               /* NOLINT(bugprone-reserved-identifier) */
                        cds :: meta :: EnableIf <
                                cds :: meta :: isMemberFunctionPointer <
                                        __Predicate,
                                        cds :: meta :: Decay < decltype ( * cds :: meta :: valueOf < __IteratorType > () ) >
                                > ()
                        > = 0
                > __CDS_NoDiscard constexpr auto __moreThan (   /* NOLINT(bugprone-reserved-identifier) */
                        __IteratorType const & begin,
                        __IteratorType const & end,
                        Size                   count,
                        __Predicate    const & predicate
                ) noexcept ( noexcept ( ( ( * begin ).* predicate ) () ) ) -> bool;

                template <
                        typename __IteratorType,            /* NOLINT(bugprone-reserved-identifier) */
                        typename __Predicate,               /* NOLINT(bugprone-reserved-identifier) */
                        cds :: meta :: EnableIf <
                                cds :: meta :: isMemberFunctionPointer <
                                        __Predicate,
                                        cds :: meta :: Decay < decltype ( * cds :: meta :: valueOf < __IteratorType > () ) >
                                > ()
                        > = 0
                > __CDS_NoDiscard constexpr auto __fewerThan (  /* NOLINT(bugprone-reserved-identifier) */
                        __IteratorType const & begin,
                        __IteratorType const & end,
                        Size                   count,
                        __Predicate    const & predicate
                ) noexcept ( noexcept ( ( ( * begin ).* predicate ) () ) ) -> bool;

                template <
                        typename __IteratorType,            /* NOLINT(bugprone-reserved-identifier) */
                        typename __Predicate,               /* NOLINT(bugprone-reserved-identifier) */
                        cds :: meta :: EnableIf <
                                cds :: meta :: isMemberFunctionPointer <
                                        __Predicate,
                                        cds :: meta :: Decay < decltype ( * cds :: meta :: valueOf < __IteratorType > () ) >
                                > ()
                        > = 0
                > __CDS_NoDiscard constexpr auto __count (  /* NOLINT(bugprone-reserved-identifier) */
                        __IteratorType const & begin,
                        __IteratorType const & end,
                        __Predicate    const & predicate
                ) noexcept ( noexcept ( ( ( * begin ).* predicate ) () ) ) -> Size;

                template <
                        typename __IteratorType,            /* NOLINT(bugprone-reserved-identifier) */
                        typename __Predicate,               /* NOLINT(bugprone-reserved-identifier) */
                        cds :: meta :: EnableIf <
                                cds :: meta :: isMemberFunctionPointer <
                                        __Predicate,
                                        cds :: meta :: Decay < decltype ( * cds :: meta :: valueOf < __IteratorType > () ) >
                                > ()
                        > = 0
                > __CDS_NoDiscard constexpr auto __any (    /* NOLINT(bugprone-reserved-identifier) */
                        __IteratorType const & begin,
                        __IteratorType const & end,
                        __Predicate    const & predicate
                ) noexcept ( noexcept ( ( ( * begin ).* predicate ) () ) ) -> bool;

                template <
                        typename __IteratorType,            /* NOLINT(bugprone-reserved-identifier) */
                        typename __Predicate,               /* NOLINT(bugprone-reserved-identifier) */
                        cds :: meta :: EnableIf <
                                cds :: meta :: isMemberFunctionPointer <
                                        __Predicate,
                                        cds :: meta :: Decay < decltype ( * cds :: meta :: valueOf < __IteratorType > () ) >
                                > ()
                        > = 0
                > __CDS_NoDiscard constexpr auto __all (    /* NOLINT(bugprone-reserved-identifier) */
                        __IteratorType const & begin,
                        __IteratorType const & end,
                        __Predicate    const & predicate
                ) noexcept ( noexcept ( ( ( * begin ).* predicate ) () ) ) -> bool;

                template <
                        typename __IteratorType,            /* NOLINT(bugprone-reserved-identifier) */
                        typename __Predicate,               /* NOLINT(bugprone-reserved-identifier) */
                        cds :: meta :: EnableIf <
                                cds :: meta :: isMemberFunctionPointer <
                                        __Predicate,
                                        cds :: meta :: Decay < decltype ( * cds :: meta :: valueOf < __IteratorType > () ) >
                                > ()
                        > = 0
                > __CDS_NoDiscard constexpr auto __none (   /* NOLINT(bugprone-reserved-identifier) */
                        __IteratorType const & begin,
                        __IteratorType const & end,
                        __Predicate    const & predicate
                ) noexcept ( noexcept ( ( ( * begin ).* predicate ) () ) ) -> bool;

            }
        }
    }
}

#endif /* __CDS_SHARED_ITERATOR_MEMBER_STATEMENTS_HPP__ */
