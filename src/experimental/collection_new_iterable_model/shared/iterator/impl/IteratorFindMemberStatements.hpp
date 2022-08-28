/*
 * Created by loghin on 6/27/22.
 */

#ifndef __CDS_SHARED_ITERATOR_FIND_MEMBER_STATEMENTS_IMPL_HPP__
#define __CDS_SHARED_ITERATOR_FIND_MEMBER_STATEMENTS_IMPL_HPP__ /* NOLINT(bugprone-reserved-identifier) */

namespace cds {                 /* NOLINT(modernize-concat-nested-namespaces) */
    namespace experimental {    /* NOLINT(modernize-concat-nested-namespaces) */
        namespace __hidden {    /* NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier) */
            namespace __impl {  /* NOLINT(bugprone-reserved-identifier) */

                template <
                        typename __IteratorType,                            /* NOLINT(bugprone-reserved-identifier) */
                        template < typename ... > class __CollectionType,   /* NOLINT(bugprone-reserved-identifier) */
                        typename __Predicate,                               /* NOLINT(bugprone-reserved-identifier) */
                        cds :: meta :: EnableIf <
                                cds :: meta :: isMemberFunctionPointer <
                                        __Predicate,
                                        cds :: meta :: Decay < decltype ( * cds :: meta :: valueOf < __IteratorType > () ) >
                                > ()
                        >
                > constexpr auto __findThat (                               /* NOLINT(bugprone-reserved-identifier) */
                        __IteratorType                      const & begin,
                        __IteratorType                      const & end,
                        Size                                        count,
                        __CollectionType < __IteratorType >       & storeIn,
                        __Predicate                         const & predicate
                ) noexcept ( noexcept ( ( ( * begin ) .* predicate ) () ) ) -> __CollectionType < __IteratorType > & {

                    Size found = 0ULL;
                    for ( auto iterator = begin; iterator != end && found < count; ++ iterator ) {
                        if ( ( ( * iterator ) .* predicate ) () ) {
                            ++ found;
                            (void) storeIn.insert ( iterator );
                        }
                    }

                    return storeIn;
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
                > constexpr auto __findFirstThat (  /* NOLINT(bugprone-reserved-identifier) */
                        __IteratorType                      const & begin,
                        __IteratorType                      const & end,
                        __Predicate                         const & predicate
                ) noexcept ( noexcept ( ( ( * begin ) .* predicate ) () ) ) -> __IteratorType {

                    for ( auto iterator = begin; iterator != end; ++ iterator ) {
                        if ( ( ( * iterator ).* predicate ) () ) {
                            return iterator;
                        }
                    }

                    return end;
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
                > constexpr auto __findLastThat (   /* NOLINT(bugprone-reserved-identifier) */
                        __IteratorType                      const & begin,
                        __IteratorType                      const & end,
                        __Predicate                         const & predicate
                ) noexcept ( noexcept ( ( ( * begin ) .* predicate ) ()  ) ) -> __IteratorType {

                    auto lastFound = end;
                    for ( auto iterator = begin; iterator != end; ++ iterator ) {
                        if ( ( ( * iterator ) .* predicate ) () ) {
                            lastFound = iterator;
                        }
                    }

                    return lastFound;
                }


                template <
                        typename __IteratorType,                            /* NOLINT(bugprone-reserved-identifier) */
                        template < typename ... > class __CollectionType,   /* NOLINT(bugprone-reserved-identifier) */
                        typename __Predicate,                               /* NOLINT(bugprone-reserved-identifier) */
                        cds :: meta :: EnableIf <
                                cds :: meta :: isMemberFunctionPointer <
                                        __Predicate,
                                        cds :: meta :: Decay < decltype ( * cds :: meta :: valueOf < __IteratorType > () ) >
                                > ()
                        >
                > constexpr auto __findAllThat (                            /* NOLINT(bugprone-reserved-identifier) */
                        __IteratorType                      const & begin,
                        __IteratorType                      const & end,
                        __CollectionType < __IteratorType >       & storeIn,
                        __Predicate                         const & predicate
                ) noexcept ( noexcept ( ( ( * begin ) .* predicate ) () ) ) -> __CollectionType < __IteratorType > & {

                    for ( auto iterator = begin; iterator != end; ++ iterator ) {
                        if ( ( ( * iterator ) .* predicate ) () ) {
                            (void) storeIn.insert ( iterator );
                        }
                    }

                    return storeIn;
                }

            }
        }
    }
}

#endif /* __CDS_SHARED_ITERATOR_FIND_MEMBER_STATEMENTS_IMPL_HPP__ */
