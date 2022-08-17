//
// Created by loghin on 17/08/22.
//

#ifndef __CDS_SHARED_ITERATOR_MEMBER_STATEMENTS_IMPL_HPP__
#define __CDS_SHARED_ITERATOR_MEMBER_STATEMENTS_IMPL_HPP__ /* NOLINT(bugprone-reserved-identifier) */

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
                        >
                > constexpr auto __forEach (
                        __IteratorType  const & begin,
                        __IteratorType  const & end,
                        __Action        const & action
                ) noexcept ( noexcept ( ( ( * begin ).* action ) () ) ) -> void {

                    for ( auto iterator = begin; iterator != end; ++ iterator ) {
                        (void) ( ( * iterator ).* action ) ();
                    }
                }


                template <
                        typename __IteratorType,    /* NOLINT(bugprone-reserved-identifier) */
                        typename __Predicate,       /* NOLINT(bugprone-reserved-identifier) */
                        cds :: meta :: EnableIf <
                                cds :: meta :: isMemberFunctionPointer <
                                        __Predicate,
                                        cds :: meta :: Decay < decltype ( * cds :: meta :: valueOf < __IteratorType > () ) >
                                > ()
                        >
                > constexpr auto __some (           /* NOLINT(bugprone-reserved-identifier) */
                        __IteratorType const & begin,
                        __IteratorType const & end,
                        Size                   count,
                        __Predicate    const & predicate
                ) noexcept ( noexcept ( ( ( * begin ).* predicate ) () ) ) -> bool {

                    Size trueCount = 0ULL;
                    for ( auto iterator = begin; iterator != end; ++ iterator ) {
                        if ( ( ( * iterator ).* predicate ) () ) {
                            ++ trueCount;
                        }

                        if ( trueCount > count ) {
                            return false;
                        }
                    }

                    return trueCount == count;
                }


                template <
                        typename __IteratorType,    /* NOLINT(bugprone-reserved-identifier) */
                        typename __Predicate,       /* NOLINT(bugprone-reserved-identifier) */
                        cds :: meta :: EnableIf <
                                cds :: meta :: isMemberFunctionPointer <
                                        __Predicate,
                                        cds :: meta :: Decay < decltype ( * cds :: meta :: valueOf < __IteratorType > () ) >
                                > ()
                        >
                > constexpr auto __atLeast (        /* NOLINT(bugprone-reserved-identifier) */
                        __IteratorType const & begin,
                        __IteratorType const & end,
                        Size                   count,
                        __Predicate    const & predicate
                ) noexcept ( noexcept ( ( ( * begin ).* predicate ) () ) ) -> bool {

                    Size trueCount = 0ULL;
                    for ( auto iterator = begin; iterator != end; ++ iterator ) {
                        if ( ( ( * iterator ).* predicate ) () ) {
                            ++ trueCount;
                        }

                        if ( trueCount >= count ) {
                            return true;
                        }
                    }

                    return false;
                }


                template <
                        typename __IteratorType,    /* NOLINT(bugprone-reserved-identifier) */
                        typename __Predicate,       /* NOLINT(bugprone-reserved-identifier) */
                        cds :: meta :: EnableIf <
                                cds :: meta :: isMemberFunctionPointer <
                                        __Predicate,
                                        cds :: meta :: Decay < decltype ( * cds :: meta :: valueOf < __IteratorType > () ) >
                                > ()
                        >
                > constexpr auto __atMost (         /* NOLINT(bugprone-reserved-identifier) */
                        __IteratorType const & begin,
                        __IteratorType const & end,
                        Size                   count,
                        __Predicate    const & predicate
                ) noexcept ( noexcept ( ( ( * begin ).* predicate ) () ) ) -> bool {

                    Size trueCount = 0ULL;
                    for ( auto iterator = begin; iterator != end; ++ iterator ) {
                        if ( ( ( * iterator ).* predicate ) () ) {
                            ++ trueCount;
                        }

                        if ( trueCount > count ) {
                            return false;
                        }
                    }

                    return true;
                }


                template <
                        typename __IteratorType,    /* NOLINT(bugprone-reserved-identifier) */
                        typename __Predicate,       /* NOLINT(bugprone-reserved-identifier) */
                        cds :: meta :: EnableIf <
                                cds :: meta :: isMemberFunctionPointer <
                                        __Predicate,
                                        cds :: meta :: Decay < decltype ( * cds :: meta :: valueOf < __IteratorType > () ) >
                                > ()
                        >
                > constexpr auto __moreThan (       /* NOLINT(bugprone-reserved-identifier) */
                        __IteratorType const & begin,
                        __IteratorType const & end,
                        Size                   count,
                        __Predicate    const & predicate
                ) noexcept ( noexcept ( ( ( * begin ).* predicate ) () ) ) -> bool {

                    return __atLeast ( begin, end, count + 1ULL, predicate );
                }


                template <
                        typename __IteratorType,    /* NOLINT(bugprone-reserved-identifier) */
                        typename __Predicate,       /* NOLINT(bugprone-reserved-identifier) */
                        cds :: meta :: EnableIf <
                                cds :: meta :: isMemberFunctionPointer <
                                        __Predicate,
                                        cds :: meta :: Decay < decltype ( * cds :: meta :: valueOf < __IteratorType > () ) >
                                > ()
                        >
                > constexpr auto __fewerThan (      /* NOLINT(bugprone-reserved-identifier) */
                        __IteratorType const & begin,
                        __IteratorType const & end,
                        Size                   count,
                        __Predicate    const & predicate
                ) noexcept ( noexcept ( ( ( * begin ).* predicate ) () ) ) -> bool {

                    if ( count == 0ULL ) {
                        return false;
                    }

                    return __atMost ( begin, end, count - 1ULL, predicate );
                }


                template <
                        typename __IteratorType,    /* NOLINT(bugprone-reserved-identifier) */
                        typename __Predicate,       /* NOLINT(bugprone-reserved-identifier) */
                        cds :: meta :: EnableIf <
                                cds :: meta :: isMemberFunctionPointer <
                                        __Predicate,
                                        cds :: meta :: Decay < decltype ( * cds :: meta :: valueOf < __IteratorType > () ) >
                                > ()
                        >
                > constexpr auto __count (          /* NOLINT(bugprone-reserved-identifier) */
                        __IteratorType const & begin,
                        __IteratorType const & end,
                        __Predicate    const & predicate
                ) noexcept ( noexcept ( ( ( * begin ).* predicate ) () ) ) -> Size {

                    Size trueCount = 0ULL;
                    for ( auto iterator = begin; iterator != end; ++ iterator ) {
                        if ( ( ( * iterator ).* predicate ) () ) {
                            ++ trueCount;
                        }
                    }

                    return trueCount;
                }


                template <
                        typename __IteratorType,    /* NOLINT(bugprone-reserved-identifier) */
                        typename __Predicate,       /* NOLINT(bugprone-reserved-identifier) */
                        cds :: meta :: EnableIf <
                                cds :: meta :: isMemberFunctionPointer <
                                        __Predicate,
                                        cds :: meta :: Decay < decltype ( * cds :: meta :: valueOf < __IteratorType > () ) >
                                > ()
                        >
                > constexpr auto __any (            /* NOLINT(bugprone-reserved-identifier) */
                        __IteratorType const & begin,
                        __IteratorType const & end,
                        __Predicate    const & predicate
                ) noexcept ( noexcept ( ( ( * begin ).* predicate ) () ) ) -> bool {

                    for ( auto iterator = begin; iterator != end; ++ iterator ) {
                        if ( ( ( * iterator ).* predicate ) () ) {
                            return true;
                        }
                    }

                    return false;
                }


                template <
                        typename __IteratorType,    /* NOLINT(bugprone-reserved-identifier) */
                        typename __Predicate,       /* NOLINT(bugprone-reserved-identifier) */
                        cds :: meta :: EnableIf <
                                cds :: meta :: isMemberFunctionPointer <
                                        __Predicate,
                                        cds :: meta :: Decay < decltype ( * cds :: meta :: valueOf < __IteratorType > () ) >
                                > ()
                        >
                > constexpr auto __all (            /* NOLINT(bugprone-reserved-identifier) */
                        __IteratorType const & begin,
                        __IteratorType const & end,
                        __Predicate    const & predicate
                ) noexcept ( noexcept ( ( ( * begin ).* predicate ) () ) ) -> bool {

                    for ( auto iterator = begin; iterator != end; ++ iterator ) {
                        if ( ! ( ( * iterator ).* predicate ) () ) {
                            return false;
                        }
                    }

                    return true;
                }


                template <
                        typename __IteratorType,    /* NOLINT(bugprone-reserved-identifier) */
                        typename __Predicate,       /* NOLINT(bugprone-reserved-identifier) */
                        cds :: meta :: EnableIf <
                                cds :: meta :: isMemberFunctionPointer <
                                        __Predicate,
                                        cds :: meta :: Decay < decltype ( * cds :: meta :: valueOf < __IteratorType > () ) >
                                > ()
                        >
                > constexpr auto __none (           /* NOLINT(bugprone-reserved-identifier) */
                        __IteratorType const & begin,
                        __IteratorType const & end,
                        __Predicate    const & predicate
                ) noexcept ( noexcept ( ( ( * begin ).* predicate ) () ) ) -> bool {

                    for ( auto iterator = begin; iterator != end; ++ iterator ) {
                        if ( ( ( * iterator ).* predicate ) () ) {
                            return false;
                        }
                    }

                    return true;
                }

            }
        }
    }
}

#endif /* __CDS_SHARED_ITERATOR_MEMBER_STATEMENTS_IMPL_HPP__ */
