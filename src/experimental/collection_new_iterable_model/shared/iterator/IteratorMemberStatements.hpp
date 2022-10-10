/*
 * Created by loghin on 17/08/22.
 */

#ifndef __CDS_EX_SHARED_ITERATOR_MEMBER_STATEMENTS_HPP__
#define __CDS_EX_SHARED_ITERATOR_MEMBER_STATEMENTS_HPP__ /* NOLINT(bugprone-reserved-identifier) */

#warning No longer an experimental feature. Use the non-experimental header.
#include "../../../../shared/iterator/IteratorMemberStatements.hpp"

namespace cds {                 /* NOLINT(modernize-concat-nested-namespaces) */
    namespace experimental {    /* NOLINT(modernize-concat-nested-namespaces) */
        namespace __hidden {    /* NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier) */
            namespace __impl {  /* NOLINT(bugprone-reserved-identifier) */

                template <
                        typename __IteratorType,                        /* NOLINT(bugprone-reserved-identifier) */
                        typename __Action,                              /* NOLINT(bugprone-reserved-identifier) */
                        cds :: meta :: EnableIf <
                                cds :: meta :: isMemberFunctionPointer <
                                        __Action,
                                        cds :: meta :: Decay < decltype ( * cds :: meta :: valueOf < __IteratorType > () ) >
                                > ()
                        > = 0
                > __CDS_DeprecatedHint("No longer an experimental feature.") __CDS_cpplang_ConstexprConditioned auto __forEach (   /* NOLINT(bugprone-reserved-identifier) */
                        __IteratorType  const & begin,
                        __IteratorType  const & end,
                        __Action        const & action
                ) noexcept ( noexcept ( ( ( * begin ).* action ) () ) ) -> void {

                    cds :: __hidden :: __impl :: __forEach < __IteratorType, __Action > ( begin, end, action );
                }


                template <
                        typename __IteratorType,                                    /* NOLINT(bugprone-reserved-identifier) */
                        typename __Predicate,                                       /* NOLINT(bugprone-reserved-identifier) */
                        cds :: meta :: EnableIf <
                                cds :: meta :: isMemberFunctionPointer <
                                        __Predicate,
                                        cds :: meta :: Decay < decltype ( * cds :: meta :: valueOf < __IteratorType > () ) >
                                > ()
                        > = 0
                > __CDS_NoDiscard __CDS_DeprecatedHint("No longer an experimental feature.") __CDS_cpplang_ConstexprConditioned auto __some (  /* NOLINT(bugprone-reserved-identifier) */
                        __IteratorType const & begin,
                        __IteratorType const & end,
                        Size                   count,
                        __Predicate    const & predicate
                ) noexcept ( noexcept ( ( ( * begin ).* predicate ) () ) ) -> bool {

                    return cds :: __hidden :: __impl :: __some < __IteratorType, __Predicate > ( begin, end, count, predicate );
                }


                template <
                        typename __IteratorType,                                        /* NOLINT(bugprone-reserved-identifier) */
                        typename __Predicate,                                           /* NOLINT(bugprone-reserved-identifier) */
                        cds :: meta :: EnableIf <
                                cds :: meta :: isMemberFunctionPointer <
                                        __Predicate,
                                        cds :: meta :: Decay < decltype ( * cds :: meta :: valueOf < __IteratorType > () ) >
                                > ()
                        > = 0
                > __CDS_NoDiscard __CDS_DeprecatedHint("No longer an experimental feature.") __CDS_cpplang_ConstexprConditioned auto __atLeast (   /* NOLINT(bugprone-reserved-identifier) */
                        __IteratorType const & begin,
                        __IteratorType const & end,
                        Size                   count,
                        __Predicate    const & predicate
                ) noexcept ( noexcept ( ( ( * begin ).* predicate ) () ) ) -> bool {

                    return cds :: __hidden :: __impl :: __atLeast < __IteratorType, __Predicate > ( begin, end, count, predicate );
                }


                template <
                        typename __IteratorType,                                        /* NOLINT(bugprone-reserved-identifier) */
                        typename __Predicate,                                           /* NOLINT(bugprone-reserved-identifier) */
                        cds :: meta :: EnableIf <
                                cds :: meta :: isMemberFunctionPointer <
                                        __Predicate,
                                        cds :: meta :: Decay < decltype ( * cds :: meta :: valueOf < __IteratorType > () ) >
                                > ()
                        > = 0
                > __CDS_NoDiscard __CDS_DeprecatedHint("No longer an experimental feature.") __CDS_cpplang_ConstexprConditioned auto __atMost (    /* NOLINT(bugprone-reserved-identifier) */
                        __IteratorType const & begin,
                        __IteratorType const & end,
                        Size                   count,
                        __Predicate    const & predicate
                ) noexcept ( noexcept ( ( ( * begin ).* predicate ) () ) ) -> bool {

                    return cds :: __hidden :: __impl :: __atMost < __IteratorType, __Predicate > ( begin, end, count, predicate );
                }


                template <
                        typename __IteratorType,                                        /* NOLINT(bugprone-reserved-identifier) */
                        typename __Predicate,                                           /* NOLINT(bugprone-reserved-identifier) */
                        cds :: meta :: EnableIf <
                                cds :: meta :: isMemberFunctionPointer <
                                        __Predicate,
                                        cds :: meta :: Decay < decltype ( * cds :: meta :: valueOf < __IteratorType > () ) >
                                > ()
                        > = 0
                > __CDS_NoDiscard __CDS_DeprecatedHint("No longer an experimental feature.") __CDS_cpplang_ConstexprConditioned auto __moreThan (  /* NOLINT(bugprone-reserved-identifier) */
                        __IteratorType const & begin,
                        __IteratorType const & end,
                        Size                   count,
                        __Predicate    const & predicate
                ) noexcept ( noexcept ( ( ( * begin ).* predicate ) () ) ) -> bool {

                    return cds :: __hidden :: __impl :: __moreThan < __IteratorType, __Predicate > ( begin, end, count, predicate );
                }


                template <
                        typename __IteratorType,                                        /* NOLINT(bugprone-reserved-identifier) */
                        typename __Predicate,                                           /* NOLINT(bugprone-reserved-identifier) */
                        cds :: meta :: EnableIf <
                                cds :: meta :: isMemberFunctionPointer <
                                        __Predicate,
                                        cds :: meta :: Decay < decltype ( * cds :: meta :: valueOf < __IteratorType > () ) >
                                > ()
                        > = 0
                > __CDS_NoDiscard __CDS_DeprecatedHint("No longer an experimental feature.") __CDS_cpplang_ConstexprConditioned auto __fewerThan ( /* NOLINT(bugprone-reserved-identifier) */
                        __IteratorType const & begin,
                        __IteratorType const & end,
                        Size                   count,
                        __Predicate    const & predicate
                ) noexcept ( noexcept ( ( ( * begin ).* predicate ) () ) ) -> bool {

                    return cds :: __hidden :: __impl :: __fewerThan < __IteratorType, __Predicate > ( begin, end, count, predicate );
                }


                template <
                        typename __IteratorType,                                    /* NOLINT(bugprone-reserved-identifier) */
                        typename __Predicate,                                       /* NOLINT(bugprone-reserved-identifier) */
                        cds :: meta :: EnableIf <
                                cds :: meta :: isMemberFunctionPointer <
                                        __Predicate,
                                        cds :: meta :: Decay < decltype ( * cds :: meta :: valueOf < __IteratorType > () ) >
                                > ()
                        > = 0
                > __CDS_NoDiscard __CDS_DeprecatedHint("No longer an experimental feature.") __CDS_cpplang_ConstexprConditioned auto __count ( /* NOLINT(bugprone-reserved-identifier) */
                        __IteratorType const & begin,
                        __IteratorType const & end,
                        __Predicate    const & predicate
                ) noexcept ( noexcept ( ( ( * begin ).* predicate ) () ) ) -> Size {

                    return cds :: __hidden :: __impl :: __count < __IteratorType, __Predicate > ( begin, end, predicate );
                }


                template <
                        typename __IteratorType,                                    /* NOLINT(bugprone-reserved-identifier) */
                        typename __Predicate,                                       /* NOLINT(bugprone-reserved-identifier) */
                        cds :: meta :: EnableIf <
                                cds :: meta :: isMemberFunctionPointer <
                                        __Predicate,
                                        cds :: meta :: Decay < decltype ( * cds :: meta :: valueOf < __IteratorType > () ) >
                                > ()
                        > = 0
                > __CDS_NoDiscard __CDS_DeprecatedHint("No longer an experimental feature.") __CDS_cpplang_ConstexprConditioned auto __any (   /* NOLINT(bugprone-reserved-identifier) */
                        __IteratorType const & begin,
                        __IteratorType const & end,
                        __Predicate    const & predicate
                ) noexcept ( noexcept ( ( ( * begin ).* predicate ) () ) ) -> bool {

                    return cds :: __hidden :: __impl :: __any < __IteratorType, __Predicate > ( begin, end, predicate );
                }


                template <
                        typename __IteratorType,                                    /* NOLINT(bugprone-reserved-identifier) */
                        typename __Predicate,                                       /* NOLINT(bugprone-reserved-identifier) */
                        cds :: meta :: EnableIf <
                                cds :: meta :: isMemberFunctionPointer <
                                        __Predicate,
                                        cds :: meta :: Decay < decltype ( * cds :: meta :: valueOf < __IteratorType > () ) >
                                > ()
                        > = 0
                > __CDS_NoDiscard __CDS_DeprecatedHint("No longer an experimental feature.") __CDS_cpplang_ConstexprConditioned auto __all (   /* NOLINT(bugprone-reserved-identifier) */
                        __IteratorType const & begin,
                        __IteratorType const & end,
                        __Predicate    const & predicate
                ) noexcept ( noexcept ( ( ( * begin ).* predicate ) () ) ) -> bool {

                    return cds :: __hidden :: __impl :: __all < __IteratorType, __Predicate > ( begin, end, predicate );
                }


                template <
                        typename __IteratorType,                                    /* NOLINT(bugprone-reserved-identifier) */
                        typename __Predicate,                                       /* NOLINT(bugprone-reserved-identifier) */
                        cds :: meta :: EnableIf <
                                cds :: meta :: isMemberFunctionPointer <
                                        __Predicate,
                                        cds :: meta :: Decay < decltype ( * cds :: meta :: valueOf < __IteratorType > () ) >
                                > ()
                        > = 0
                > __CDS_NoDiscard __CDS_DeprecatedHint("No longer an experimental feature.") __CDS_cpplang_ConstexprConditioned auto __none (  /* NOLINT(bugprone-reserved-identifier) */
                        __IteratorType const & begin,
                        __IteratorType const & end,
                        __Predicate    const & predicate
                ) noexcept ( noexcept ( ( ( * begin ).* predicate ) () ) ) -> bool {

                    return cds :: __hidden :: __impl :: __none < __IteratorType, __Predicate > ( begin, end, predicate );
                }

            }
        }
    }
}

#endif /* __CDS_EX_SHARED_ITERATOR_MEMBER_STATEMENTS_HPP__ */
