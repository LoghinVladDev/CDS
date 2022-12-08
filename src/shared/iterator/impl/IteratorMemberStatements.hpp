/*
 * Created by loghin on 17/08/22.
 */

#ifndef __CDS_SHARED_ITERATOR_MEMBER_STATEMENTS_IMPL_HPP__ /* NOLINT(llvm-header-guard) */
#define __CDS_SHARED_ITERATOR_MEMBER_STATEMENTS_IMPL_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

namespace cds {             /* NOLINT(modernize-concat-nested-namespaces) */
    namespace __hidden {    /* NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        namespace __impl {  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

#ifndef _MSC_VER

            template <
                    typename __IteratorType,                        /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __Consumer,                            /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    cds :: meta :: EnableIf <
                            cds :: meta :: isMemberFunctionPointer <
                                    __Consumer,
                                    cds :: meta :: Decay < decltype ( * cds :: meta :: valueOf < __IteratorType > () ) >
                            > ()
                    >
            > __CDS_MaybeUnused __CDS_cpplang_ConstexprConditioned auto __forEach (   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __IteratorType  const & begin,
                    __IteratorType  const & end,
                    __Consumer      const & consumer
            ) noexcept ( noexcept ( ( ( * begin ).* consumer ) () ) ) -> void {

                /* iterate through range */
                for ( auto iterator = begin; iterator != end; ++ iterator ) {

                    /* call action for each value */
                    (void) ( ( * iterator ).* consumer ) ();
                }
            }


            template <
                    typename __IteratorType,                    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __Predicate,                       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    cds :: meta :: EnableIf <
                            cds :: meta :: isMemberFunctionPointer <
                                    __Predicate,
                                    cds :: meta :: Decay < decltype ( * cds :: meta :: valueOf < __IteratorType > () ) >
                            > ()
                    >
            > __CDS_MaybeUnused __CDS_cpplang_ConstexprConditioned auto __some (  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __IteratorType const & begin,
                    __IteratorType const & end,
                    Size                   count,
                    __Predicate    const & predicate
            ) noexcept ( noexcept ( ( ( * begin ).* predicate ) () ) ) -> bool {

                /* count values for which the predicate yielded 'true' */
                Size trueCount = 0ULL;

                /* parse the range */
                for ( auto iterator = begin; iterator != end; ++ iterator ) {

                    /* for values for which the predicate yielded 'true', increment counter */
                    if ( ( ( * iterator ).* predicate ) () ) {
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
                    typename __IteratorType,                        /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __Predicate,                           /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    cds :: meta :: EnableIf <
                            cds :: meta :: isMemberFunctionPointer <
                                    __Predicate,
                                    cds :: meta :: Decay < decltype ( * cds :: meta :: valueOf < __IteratorType > () ) >
                            > ()
                    >
            > __CDS_cpplang_ConstexprConditioned auto __atLeast (   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __IteratorType const & begin,
                    __IteratorType const & end,
                    Size                   count,
                    __Predicate    const & predicate
            ) noexcept ( noexcept ( ( ( * begin ).* predicate ) () ) ) -> bool {

                /* count values for which the predicate yielded 'true' */
                Size trueCount = 0ULL;

                /* parse the range */
                for ( auto iterator = begin; iterator != end; ++ iterator ) {

                    /* for values for which the predicate yielded 'true', increment counter */
                    if ( ( ( * iterator ).* predicate ) () ) {
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
                    typename __IteratorType,                        /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __Predicate,                           /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    cds :: meta :: EnableIf <
                            cds :: meta :: isMemberFunctionPointer <
                                    __Predicate,
                                    cds :: meta :: Decay < decltype ( * cds :: meta :: valueOf < __IteratorType > () ) >
                            > ()
                    >
            > __CDS_cpplang_ConstexprConditioned auto __atMost (    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __IteratorType const & begin,
                    __IteratorType const & end,
                    Size                   count,
                    __Predicate    const & predicate
            ) noexcept ( noexcept ( ( ( * begin ).* predicate ) () ) ) -> bool {

                /* count values for which the predicate yielded 'true' */
                Size trueCount = 0ULL;

                /* parse the range */
                for ( auto iterator = begin; iterator != end; ++ iterator ) {

                    /* for values for which the predicate yielded 'true', increment counter */
                    if ( ( ( * iterator ).* predicate ) () ) {
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
                    typename __IteratorType,                        /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __Predicate,                           /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    cds :: meta :: EnableIf <
                            cds :: meta :: isMemberFunctionPointer <
                                    __Predicate,
                                    cds :: meta :: Decay < decltype ( * cds :: meta :: valueOf < __IteratorType > () ) >
                            > ()
                    >
            > __CDS_MaybeUnused __CDS_cpplang_ConstexprConditioned auto __moreThan (  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __IteratorType const & begin,
                    __IteratorType const & end,
                    Size                   count,
                    __Predicate    const & predicate
            ) noexcept ( noexcept ( ( ( * begin ).* predicate ) () ) ) -> bool {

                /* having more than 'x' values is the same as having at least 'x+1' values */
                return __atLeast ( begin, end, count + 1ULL, predicate );
            }


            template <
                    typename __IteratorType,                        /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __Predicate,                           /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    cds :: meta :: EnableIf <
                            cds :: meta :: isMemberFunctionPointer <
                                    __Predicate,
                                    cds :: meta :: Decay < decltype ( * cds :: meta :: valueOf < __IteratorType > () ) >
                            > ()
                    >
            > __CDS_MaybeUnused __CDS_cpplang_ConstexprConditioned auto __fewerThan ( /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __IteratorType const & begin,
                    __IteratorType const & end,
                    Size                   count,
                    __Predicate    const & predicate
            ) noexcept ( noexcept ( ( ( * begin ).* predicate ) () ) ) -> bool {

                /* since we will use atMost ( count - 1 ), avoid an overflow. Fewer than 0 will always be false. */
                if ( count == 0ULL ) {
                    return false;
                }

                /* having fewer than 'x' values is the same as having at most 'x-1' values */
                return __atMost ( begin, end, count - 1ULL, predicate );
            }


            template <
                    typename __IteratorType,                    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __Predicate,                       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    cds :: meta :: EnableIf <
                            cds :: meta :: isMemberFunctionPointer <
                                    __Predicate,
                                    cds :: meta :: Decay < decltype ( * cds :: meta :: valueOf < __IteratorType > () ) >
                            > ()
                    >
            > __CDS_MaybeUnused __CDS_cpplang_ConstexprConditioned auto __count ( /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __IteratorType const & begin,
                    __IteratorType const & end,
                    __Predicate    const & predicate
            ) noexcept ( noexcept ( ( ( * begin ).* predicate ) () ) ) -> Size {

                /* count values for which the predicate yielded 'true' */
                Size trueCount = 0ULL;

                /* parse the range */
                for ( auto iterator = begin; iterator != end; ++ iterator ) {

                    /* for values for which the predicate yielded 'true', increment counter */
                    if ( ( ( * iterator ).* predicate ) () ) {
                        ++ trueCount;
                    }
                }

                /* return the number of values for which 'true' was yielded by the predicate */
                return trueCount;
            }


            template <
                    typename __IteratorType,                    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __Predicate,                       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    cds :: meta :: EnableIf <
                            cds :: meta :: isMemberFunctionPointer <
                                    __Predicate,
                                    cds :: meta :: Decay < decltype ( * cds :: meta :: valueOf < __IteratorType > () ) >
                            > ()
                    >
            > __CDS_MaybeUnused __CDS_cpplang_ConstexprConditioned auto __any (   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __IteratorType const & begin,
                    __IteratorType const & end,
                    __Predicate    const & predicate
            ) noexcept ( noexcept ( ( ( * begin ).* predicate ) () ) ) -> bool {

                /* parse the range */
                for ( auto iterator = begin; iterator != end; ++ iterator ) {

                    /* if the predicate yields 'true' for any value, return true */
                    if ( ( ( * iterator ).* predicate ) () ) {
                        return true;
                    }
                }

                /* otherwise, no value was found for predicate to yield 'true' to, return false */
                return false;
            }


            template <
                    typename __IteratorType,                    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __Predicate,                       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    cds :: meta :: EnableIf <
                            cds :: meta :: isMemberFunctionPointer <
                                    __Predicate,
                                    cds :: meta :: Decay < decltype ( * cds :: meta :: valueOf < __IteratorType > () ) >
                            > ()
                    >
            > __CDS_MaybeUnused __CDS_cpplang_ConstexprConditioned auto __all (   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __IteratorType const & begin,
                    __IteratorType const & end,
                    __Predicate    const & predicate
            ) noexcept ( noexcept ( ( ( * begin ).* predicate ) () ) ) -> bool {

                /* parse the range */
                for ( auto iterator = begin; iterator != end; ++ iterator ) {

                    /* if the predicate yields 'false' for any value, return false, since one 'false' = not all 'true' */
                    if ( ! ( ( * iterator ).* predicate ) () ) {
                        return false;
                    }
                }

                /* otherwise, no value was found for predicate to yield 'false' to, return true */
                return true;
            }


            template <
                    typename __IteratorType,                    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __Predicate,                       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    cds :: meta :: EnableIf <
                            cds :: meta :: isMemberFunctionPointer <
                                    __Predicate,
                                    cds :: meta :: Decay < decltype ( * cds :: meta :: valueOf < __IteratorType > () ) >
                            > ()
                    >
            > __CDS_MaybeUnused __CDS_cpplang_ConstexprConditioned auto __none (  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __IteratorType const & begin,
                    __IteratorType const & end,
                    __Predicate    const & predicate
            ) noexcept ( noexcept ( ( ( * begin ).* predicate ) () ) ) -> bool {

                /* parse the range */
                for ( auto iterator = begin; iterator != end; ++ iterator ) {

                    /* if the predicate yields 'true' for any value, return false, since one 'true' = not all 'false' */
                    if ( ( ( * iterator ).* predicate ) () ) {
                        return false;
                    }
                }

                /* otherwise, no value was found for predicate to yield 'true' to, return true */
                return true;
            }

#else

            template <
                    typename __IteratorType,                                                /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __Consumer                                                     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > __CDS_MaybeUnused __CDS_cpplang_ConstexprConditioned auto __forEachMember (   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __IteratorType  const & begin,
                    __IteratorType  const & end,
                    __Consumer      const & consumer
            ) noexcept ( noexcept ( ( ( * begin ).* consumer ) () ) ) -> void {

                /* iterate through range */
                for ( auto iterator = begin; iterator != end; ++ iterator ) {

                    /* call action for each value */
                    (void) ( ( * iterator ).* consumer ) ();
                }
            }


            template <
                    typename __IteratorType,                                            /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __Predicate                                                /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > __CDS_MaybeUnused __CDS_cpplang_ConstexprConditioned auto __someMember (  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __IteratorType const & begin,
                    __IteratorType const & end,
                    Size                   count,
                    __Predicate    const & predicate
            ) noexcept ( noexcept ( ( ( * begin ).* predicate ) () ) ) -> bool {

                /* count values for which the predicate yielded 'true' */
                Size trueCount = 0ULL;

                /* parse the range */
                for ( auto iterator = begin; iterator != end; ++ iterator ) {

                    /* for values for which the predicate yielded 'true', increment counter */
                    if ( ( ( * iterator ).* predicate ) () ) {
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
                    typename __IteratorType,                            /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __Predicate                                /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > __CDS_cpplang_ConstexprConditioned auto __atLeastMeber (  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __IteratorType const & begin,
                    __IteratorType const & end,
                    Size                   count,
                    __Predicate    const & predicate
            ) noexcept ( noexcept ( ( ( * begin ).* predicate ) () ) ) -> bool {

                /* count values for which the predicate yielded 'true' */
                Size trueCount = 0ULL;

                /* parse the range */
                for ( auto iterator = begin; iterator != end; ++ iterator ) {

                    /* for values for which the predicate yielded 'true', increment counter */
                    if ( ( ( * iterator ).* predicate ) () ) {
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
                    typename __IteratorType,                            /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __Predicate                                /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > __CDS_cpplang_ConstexprConditioned auto __atMostMember (  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __IteratorType const & begin,
                    __IteratorType const & end,
                    Size                   count,
                    __Predicate    const & predicate
            ) noexcept ( noexcept ( ( ( * begin ).* predicate ) () ) ) -> bool {

                /* count values for which the predicate yielded 'true' */
                Size trueCount = 0ULL;

                /* parse the range */
                for ( auto iterator = begin; iterator != end; ++ iterator ) {

                    /* for values for which the predicate yielded 'true', increment counter */
                    if ( ( ( * iterator ).* predicate ) () ) {
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
                    typename __IteratorType,                                                /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __Predicate                                                    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > __CDS_MaybeUnused __CDS_cpplang_ConstexprConditioned auto __moreThanMember (  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __IteratorType const & begin,
                    __IteratorType const & end,
                    Size                   count,
                    __Predicate    const & predicate
            ) noexcept ( noexcept ( ( ( * begin ).* predicate ) () ) ) -> bool {

                /* having more than 'x' values is the same as having at least 'x+1' values */
                return __atLeast ( begin, end, count + 1ULL, predicate );
            }


            template <
                    typename __IteratorType,                                                /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __Predicate                                                    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > __CDS_MaybeUnused __CDS_cpplang_ConstexprConditioned auto __fewerThanMember ( /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __IteratorType const & begin,
                    __IteratorType const & end,
                    Size                   count,
                    __Predicate    const & predicate
            ) noexcept ( noexcept ( ( ( * begin ).* predicate ) () ) ) -> bool {

                /* since we will use atMost ( count - 1 ), avoid an overflow. Fewer than 0 will always be false. */
                if ( count == 0ULL ) {
                    return false;
                }

                /* having fewer than 'x' values is the same as having at most 'x-1' values */
                return __atMost ( begin, end, count - 1ULL, predicate );
            }


            template <
                    typename __IteratorType,                                            /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __Predicate                                                /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > __CDS_MaybeUnused __CDS_cpplang_ConstexprConditioned auto __countMember ( /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __IteratorType const & begin,
                    __IteratorType const & end,
                    __Predicate    const & predicate
            ) noexcept ( noexcept ( ( ( * begin ).* predicate ) () ) ) -> Size {

                /* count values for which the predicate yielded 'true' */
                Size trueCount = 0ULL;

                /* parse the range */
                for ( auto iterator = begin; iterator != end; ++ iterator ) {

                    /* for values for which the predicate yielded 'true', increment counter */
                    if ( ( ( * iterator ).* predicate ) () ) {
                        ++ trueCount;
                    }
                }

                /* return the number of values for which 'true' was yielded by the predicate */
                return trueCount;
            }


            template <
                    typename __IteratorType,                                            /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __Predicate                                                /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > __CDS_MaybeUnused __CDS_cpplang_ConstexprConditioned auto __anyMember (   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __IteratorType const & begin,
                    __IteratorType const & end,
                    __Predicate    const & predicate
            ) noexcept ( noexcept ( ( ( * begin ).* predicate ) () ) ) -> bool {

                /* parse the range */
                for ( auto iterator = begin; iterator != end; ++ iterator ) {

                    /* if the predicate yields 'true' for any value, return true */
                    if ( ( ( * iterator ).* predicate ) () ) {
                        return true;
                    }
                }

                /* otherwise, no value was found for predicate to yield 'true' to, return false */
                return false;
            }


            template <
                    typename __IteratorType,                                            /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __Predicate                                                /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > __CDS_MaybeUnused __CDS_cpplang_ConstexprConditioned auto __allMember (   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __IteratorType const & begin,
                    __IteratorType const & end,
                    __Predicate    const & predicate
            ) noexcept ( noexcept ( ( ( * begin ).* predicate ) () ) ) -> bool {

                /* parse the range */
                for ( auto iterator = begin; iterator != end; ++ iterator ) {

                    /* if the predicate yields 'false' for any value, return false, since one 'false' = not all 'true' */
                    if ( ! ( ( * iterator ).* predicate ) () ) {
                        return false;
                    }
                }

                /* otherwise, no value was found for predicate to yield 'false' to, return true */
                return true;
            }


            template <
                    typename __IteratorType,                                            /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __Predicate                                                /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > __CDS_MaybeUnused __CDS_cpplang_ConstexprConditioned auto __noneMember (  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __IteratorType const & begin,
                    __IteratorType const & end,
                    __Predicate    const & predicate
            ) noexcept ( noexcept ( ( ( * begin ).* predicate ) () ) ) -> bool {

                /* parse the range */
                for ( auto iterator = begin; iterator != end; ++ iterator ) {

                    /* if the predicate yields 'true' for any value, return false, since one 'true' = not all 'false' */
                    if ( ( ( * iterator ).* predicate ) () ) {
                        return false;
                    }
                }

                /* otherwise, no value was found for predicate to yield 'true' to, return true */
                return true;
            }

#endif

        } /* namespace __impl */
    } /* namespace __hidden */
} /* namespace cds */

#endif /* __CDS_SHARED_ITERATOR_MEMBER_STATEMENTS_IMPL_HPP__ */
