/*
 * Created by loghin on 6/27/22.
 */

#ifndef __CDS_SHARED_ITERATOR_FIND_STATEMENTS_IMPL_HPP__
#define __CDS_SHARED_ITERATOR_FIND_STATEMENTS_IMPL_HPP__ /* NOLINT(bugprone-reserved-identifier) */

namespace cds {             /* NOLINT(modernize-concat-nested-namespaces) */
    namespace __hidden {    /* NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier) */
        namespace __impl {  /* NOLINT(bugprone-reserved-identifier) */

            template <
                    typename __IteratorType,                            /* NOLINT(bugprone-reserved-identifier) */
                    template < typename ... > class __CollectionType,   /* NOLINT(bugprone-reserved-identifier) */
                    typename __Predicate,                               /* NOLINT(bugprone-reserved-identifier) */
                    cds :: meta :: EnableIf <
                            ! cds :: meta :: isMemberFunctionPointer <
                                    __Predicate,
                                    cds :: meta :: Decay < decltype ( * cds :: meta :: valueOf < __IteratorType > () ) >
                            > ()
                    >
            > __CDS_cpplang_ConstexprConditioned auto __findThat (      /* NOLINT(bugprone-reserved-identifier) */
                    __IteratorType                      const & begin,
                    __IteratorType                      const & end,
                    Size                                        count,
                    __CollectionType < __IteratorType >       & storeIn,
                    __Predicate                         const & predicate
            ) noexcept ( noexcept ( predicate ( * begin ) ) ) -> __CollectionType < __IteratorType > & {

                /* parse the range until the end or until the limit has been reached */
                for ( auto iterator = begin; iterator != end && count != 0ULL; ++ iterator ) {

                    /* if the predicate validates the current element, store the iterator */
                    if ( predicate ( * iterator ) ) {
                        -- count;
                        (void) storeIn.insert ( iterator );
                    }
                }

                /* return reference to the received storeIn collection */
                return storeIn;
            }


            template <
                    typename __IteratorType,                            /* NOLINT(bugprone-reserved-identifier) */
                    typename __Predicate,                               /* NOLINT(bugprone-reserved-identifier) */
                    cds :: meta :: EnableIf <
                            ! cds :: meta :: isMemberFunctionPointer <
                                    __Predicate,
                                    cds :: meta :: Decay < decltype ( * cds :: meta :: valueOf < __IteratorType > () ) >
                            > ()
                    >
            > __CDS_cpplang_ConstexprConditioned auto __findFirstThat ( /* NOLINT(bugprone-reserved-identifier) */
                    __IteratorType                      const & begin,
                    __IteratorType                      const & end,
                    __Predicate                         const & predicate
            ) noexcept ( noexcept ( predicate ( * begin ) ) ) -> __IteratorType {

                /* parse the range until the end */
                for ( auto iterator = begin; iterator != end; ++ iterator ) {

                    /* if the predicate validates the current element, return the iterator */
                    if ( predicate ( * iterator ) ) {
                        return iterator;
                    }
                }

                /* if the range parse has ended, no element found, return end of range */
                return end;
            }


            template <
                    typename __IteratorType,                            /* NOLINT(bugprone-reserved-identifier) */
                    typename __Predicate,                               /* NOLINT(bugprone-reserved-identifier) */
                    cds :: meta :: EnableIf <
                            ! cds :: meta :: isMemberFunctionPointer <
                                    __Predicate,
                                    cds :: meta :: Decay < decltype ( * cds :: meta :: valueOf < __IteratorType > () ) >
                            > ()
                    >
            > __CDS_cpplang_ConstexprConditioned auto __findLastThat (  /* NOLINT(bugprone-reserved-identifier) */
                    __IteratorType                      const & begin,
                    __IteratorType                      const & end,
                    __Predicate                         const & predicate
            ) noexcept ( noexcept ( predicate ( * begin ) ) ) -> __IteratorType {

                /* create an iterator to store the last valid element iterator. Initialize with end in case of no element found */
                auto lastFound = end;

                /* parse the range to the end */
                for ( auto iterator = begin; iterator != end; ++ iterator ) {

                    /* if the predicate validates the current element, store the iterator */
                    if ( predicate ( * iterator ) ) {
                        lastFound = iterator;
                    }
                }

                /* return the stored iterator */
                return lastFound;
            }


            template <
                    typename __IteratorType,                            /* NOLINT(bugprone-reserved-identifier) */
                    template < typename ... > class __CollectionType,   /* NOLINT(bugprone-reserved-identifier) */
                    typename __Predicate,                               /* NOLINT(bugprone-reserved-identifier) */
                    cds :: meta :: EnableIf <
                            ! cds :: meta :: isMemberFunctionPointer <
                                    __Predicate,
                                    cds :: meta :: Decay < decltype ( * cds :: meta :: valueOf < __IteratorType > () ) >
                            > ()
                    >
            > __CDS_cpplang_ConstexprConditioned auto __findAllThat (   /* NOLINT(bugprone-reserved-identifier) */
                    __IteratorType                      const & begin,
                    __IteratorType                      const & end,
                    __CollectionType < __IteratorType >       & storeIn,
                    __Predicate                         const & predicate
            ) noexcept ( noexcept ( predicate ( * begin ) ) ) -> __CollectionType < __IteratorType > & {

                /* parse the range to the end */
                for ( auto iterator = begin; iterator != end; ++ iterator ) {

                    /* if the predicate validates the current element, store the iterator */
                    if ( predicate ( * iterator ) ) {
                        (void) storeIn.insert ( iterator );
                    }
                }

                /* return reference to the received storeIn collection */
                return storeIn;
            }

        }
    }
}

#endif /* __CDS_SHARED_ITERATOR_FIND_STATEMENTS_IMPL_HPP__ */
