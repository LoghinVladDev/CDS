/*
 * Created by loghin on 6/26/22.
 */

#ifndef __CDS_SHARED_ITERATOR_STATEMENTS_IMPL_HPP__
#define __CDS_SHARED_ITERATOR_STATEMENTS_IMPL_HPP__ /* NOLINT(bugprone-reserved-identifier) */

namespace cds {                 /* NOLINT(modernize-concat-nested-namespaces) */
    namespace experimental {    /* NOLINT(modernize-concat-nested-namespaces) */
        namespace __hidden {    /* NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier) */
            namespace __impl {  /* NOLINT(bugprone-reserved-identifier) */

                template <
                        typename __IteratorType,    /* NOLINT(bugprone-reserved-identifier) */
                        typename __Action,          /* NOLINT(bugprone-reserved-identifier) */
                        cds :: meta :: EnableIf <
                                ! cds :: meta :: isMemberFunctionPointer <
                                        __Action,
                                        cds :: meta :: Decay < decltype ( * cds :: meta :: valueOf < __IteratorType > () ) >
                                > ()
                        >
                > constexpr auto __forEach (        /* NOLINT(bugprone-reserved-identifier) */
                        __IteratorType const & begin,
                        __IteratorType const & end,
                        __Action       const & action
                ) noexcept ( noexcept ( action ( * begin ) ) ) -> void {

                    /* iterate through range */
                    for ( auto iterator = begin; iterator != end; ++ iterator ) {

                        /* call action for each value */
                        (void) action ( * iterator );
                    }
                }


                template <
                        typename __IteratorType,    /* NOLINT(bugprone-reserved-identifier) */
                        typename __Predicate,       /* NOLINT(bugprone-reserved-identifier) */
                        cds :: meta :: EnableIf <
                                ! cds :: meta :: isMemberFunctionPointer <
                                        __Predicate,
                                        cds :: meta :: Decay < decltype ( * cds :: meta :: valueOf < __IteratorType > () ) >
                                > ()
                        >
                > constexpr auto __some (           /* NOLINT(bugprone-reserved-identifier) */
                        __IteratorType const & begin,
                        __IteratorType const & end,
                        Size                   count,
                        __Predicate    const & predicate
                ) noexcept ( noexcept ( predicate ( * begin ) ) ) -> bool {

                    /* count values for which the predicate yielded 'true' */
                    Size trueCount = 0ULL;

                    /* parse the range */
                    for ( auto iterator = begin; iterator != end; ++ iterator ) {

                        /* for values for which the predicate yielded 'true', increment counter */
                        if ( predicate ( * iterator ) ) {
                            ++ trueCount;
                        }

                        /* if counter is greater than requested value count, there are more than requested, return false */
                        if ( trueCount > count ) {
                            return false;
                        }
                    }

                    /* otherwise, if less elements than requested, false will be yielded. Otherwise, true */
                    return trueCount == count;
                }


                template <
                        typename __IteratorType,    /* NOLINT(bugprone-reserved-identifier) */
                        typename __Predicate,       /* NOLINT(bugprone-reserved-identifier) */
                        cds :: meta :: EnableIf <
                                ! cds :: meta :: isMemberFunctionPointer <
                                        __Predicate,
                                        cds :: meta :: Decay < decltype ( * cds :: meta :: valueOf < __IteratorType > () ) >
                                > ()
                        >
                > constexpr auto __atLeast (        /* NOLINT(bugprone-reserved-identifier) */
                        __IteratorType const & begin,
                        __IteratorType const & end,
                        Size                   count,
                        __Predicate    const & predicate
                ) noexcept ( noexcept ( predicate ( * begin ) ) ) -> bool {

                    /* count values for which the predicate yielded 'true' */
                    Size trueCount = 0ULL;

                    /* parse the range */
                    for ( auto iterator = begin; iterator != end; ++ iterator ) {

                        /* for values for which the predicate yielded 'true', increment counter */
                        if ( predicate ( * iterator ) ) {
                            ++ trueCount;
                        }

                        /* if counter is greater or equal than requested value count, we have the minimum required, yield true */
                        if ( trueCount >= count ) {
                            return true;
                        }
                    }

                    /* otherwise, count not reached, yield false */
                    return false;
                }


                template <
                        typename __IteratorType,    /* NOLINT(bugprone-reserved-identifier) */
                        typename __Predicate,       /* NOLINT(bugprone-reserved-identifier) */
                        cds :: meta :: EnableIf <
                                ! cds :: meta :: isMemberFunctionPointer <
                                        __Predicate,
                                        cds :: meta :: Decay < decltype ( * cds :: meta :: valueOf < __IteratorType > () ) >
                                > ()
                        >
                > constexpr auto __atMost (         /* NOLINT(bugprone-reserved-identifier) */
                        __IteratorType const & begin,
                        __IteratorType const & end,
                        Size                   count,
                        __Predicate    const & predicate
                ) noexcept ( noexcept ( predicate ( * begin ) ) ) -> bool {

                    /* count values for which the predicate yielded 'true' */
                    Size trueCount = 0ULL;

                    /* parse the range */
                    for ( auto iterator = begin; iterator != end; ++ iterator ) {

                        /* for values for which the predicate yielded 'true', increment counter */
                        if ( predicate ( * iterator ) ) {
                            ++ trueCount;
                        }

                        /* if counter is greater than requested value count, we have more than required, yield false */
                        if ( trueCount > count ) {
                            return false;
                        }
                    }

                    /* otherwise, we have at most requested values, yield true */
                    return true;
                }


                template <
                        typename __IteratorType,    /* NOLINT(bugprone-reserved-identifier) */
                        typename __Predicate,       /* NOLINT(bugprone-reserved-identifier) */
                        cds :: meta :: EnableIf <
                                ! cds :: meta :: isMemberFunctionPointer <
                                        __Predicate,
                                        cds :: meta :: Decay < decltype ( * cds :: meta :: valueOf < __IteratorType > () ) >
                                > ()
                        >
                > constexpr auto __moreThan (       /* NOLINT(bugprone-reserved-identifier) */
                        __IteratorType const & begin,
                        __IteratorType const & end,
                        Size                   count,
                        __Predicate    const & predicate
                ) noexcept ( noexcept ( predicate ( * begin ) ) ) -> bool {

                    /* having more than 'x' values is the same as having at least 'x+1' values */
                    return __atLeast ( begin, end, count + 1ULL, predicate );
                }


                template <
                        typename __IteratorType,    /* NOLINT(bugprone-reserved-identifier) */
                        typename __Predicate,       /* NOLINT(bugprone-reserved-identifier) */
                        cds :: meta :: EnableIf <
                                ! cds :: meta :: isMemberFunctionPointer <
                                        __Predicate,
                                        cds :: meta :: Decay < decltype ( * cds :: meta :: valueOf < __IteratorType > () ) >
                                > ()
                        >
                > constexpr auto __fewerThan (      /* NOLINT(bugprone-reserved-identifier) */
                        __IteratorType const & begin,
                        __IteratorType const & end,
                        Size                   count,
                        __Predicate    const & predicate
                ) noexcept ( noexcept ( predicate ( * begin ) ) ) -> bool {

                    /* since we will use atMost ( count - 1 ), avoid an overflow. Fewer than 0 will always be false. */
                    if ( count == 0ULL ) {
                        return false;
                    }

                    /* having fewer than 'x' values is the same as having at most 'x-1' values */
                    return __atMost ( begin, end, count - 1ULL, predicate );
                }


                template <
                        typename __IteratorType,    /* NOLINT(bugprone-reserved-identifier) */
                        typename __Predicate,       /* NOLINT(bugprone-reserved-identifier) */
                        cds :: meta :: EnableIf <
                                ! cds :: meta :: isMemberFunctionPointer <
                                        __Predicate,
                                        cds :: meta :: Decay < decltype ( * cds :: meta :: valueOf < __IteratorType > () ) >
                                > ()
                        >
                > constexpr auto __count (          /* NOLINT(bugprone-reserved-identifier) */
                        __IteratorType const & begin,
                        __IteratorType const & end,
                        __Predicate    const & predicate
                ) noexcept ( noexcept ( predicate ( * begin ) ) ) -> Size {

                    /* count values for which the predicate yielded 'true' */
                    Size trueCount = 0ULL;

                    /* parse the range */
                    for ( auto iterator = begin; iterator != end; ++ iterator ) {

                        /* for values for which the predicate yielded 'true', increment counter */
                        if ( predicate ( * iterator ) ) {
                            ++ trueCount;
                        }
                    }

                    /* return the number of values for which 'true' was yielded by the predicate */
                    return trueCount;
                }


                template <
                        typename __IteratorType,    /* NOLINT(bugprone-reserved-identifier) */
                        typename __Predicate,       /* NOLINT(bugprone-reserved-identifier) */
                        cds :: meta :: EnableIf <
                                ! cds :: meta :: isMemberFunctionPointer <
                                        __Predicate,
                                        cds :: meta :: Decay < decltype ( * cds :: meta :: valueOf < __IteratorType > () ) >
                                > ()
                        >
                > constexpr auto __any (            /* NOLINT(bugprone-reserved-identifier) */
                        __IteratorType const & begin,
                        __IteratorType const & end,
                        __Predicate    const & predicate
                ) noexcept ( noexcept ( predicate ( * begin ) ) ) -> bool {

                    /* parse the range */
                    for ( auto iterator = begin; iterator != end; ++ iterator ) {

                        /* if the predicate yields 'true' for any value, return true */
                        if ( predicate ( * iterator ) ) {
                            return true;
                        }
                    }

                    /* otherwise, no value was found for predicate to yield 'true' to, return false */
                    return false;
                }


                template <
                        typename __IteratorType,    /* NOLINT(bugprone-reserved-identifier) */
                        typename __Predicate,       /* NOLINT(bugprone-reserved-identifier) */
                        cds :: meta :: EnableIf <
                                ! cds :: meta :: isMemberFunctionPointer <
                                        __Predicate,
                                        cds :: meta :: Decay < decltype ( * cds :: meta :: valueOf < __IteratorType > () ) >
                                > ()
                        >
                > constexpr auto __all (            /* NOLINT(bugprone-reserved-identifier) */
                        __IteratorType const & begin,
                        __IteratorType const & end,
                        __Predicate    const & predicate
                ) noexcept ( noexcept ( predicate ( * begin ) ) ) -> bool {

                    /* parse the range */
                    for ( auto iterator = begin; iterator != end; ++ iterator ) {

                        /* if the predicate yields 'false' for any value, return false, since one 'false' = not all 'true' */
                        if ( ! predicate ( * iterator ) ) {
                            return false;
                        }
                    }

                    /* otherwise, no value was found for predicate to yield 'false' to, return true */
                    return true;
                }


                template <
                        typename __IteratorType,    /* NOLINT(bugprone-reserved-identifier) */
                        typename __Predicate,       /* NOLINT(bugprone-reserved-identifier) */
                        cds :: meta :: EnableIf <
                                ! cds :: meta :: isMemberFunctionPointer <
                                        __Predicate,
                                        cds :: meta :: Decay < decltype ( * cds :: meta :: valueOf < __IteratorType > () ) >
                                > ()
                        >
                > constexpr auto __none (           /* NOLINT(bugprone-reserved-identifier) */
                        __IteratorType const & begin,
                        __IteratorType const & end,
                        __Predicate    const & predicate
                ) noexcept ( noexcept ( predicate ( * begin ) ) ) -> bool {

                    /* parse the range */
                    for ( auto iterator = begin; iterator != end; ++ iterator ) {

                        /* if the predicate yields 'true' for any value, return false, since one 'true' = not all 'false' */
                        if ( predicate ( * iterator ) ) {
                            return false;
                        }
                    }

                    /* otherwise, no value was found for predicate to yield 'true' to, return true */
                    return true;
                }

            }
        }
    }
}

#endif /* __CDS_SHARED_ITERATOR_STATEMENTS_IMPL_HPP__ */
