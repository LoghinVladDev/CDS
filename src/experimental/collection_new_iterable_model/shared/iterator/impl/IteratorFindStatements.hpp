//
// Created by loghin on 6/27/22.
//

#ifndef __CDS_SHARED_ITERATOR_FIND_STATEMENTS_IMPL_HPP__
#define __CDS_SHARED_ITERATOR_FIND_STATEMENTS_IMPL_HPP__

namespace cds {                 // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {    // NOLINT(modernize-concat-nested-namespaces)
        namespace __hidden {    // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier)
            namespace __impl {  // NOLINT(bugprone-reserved-identifier)

                template <
                        typename __IteratorType,                            // NOLINT(bugprone-reserved-identifier)
                        template < typename ... > class __CollectionType,   // NOLINT(bugprone-reserved-identifier)
                        typename __Predicate                                // NOLINT(bugprone-reserved-identifier)
                > constexpr auto __findThat (                               // NOLINT(bugprone-reserved-identifier)
                        __IteratorType                      const & begin,
                        __IteratorType                      const & end,
                        Size                                        count,
                        __CollectionType < __IteratorType >       & storeIn,
                        __Predicate                         const & predicate
                ) noexcept ( noexcept ( predicate ( * begin ) ) ) -> __CollectionType < __IteratorType > & {

                    Size found = 0ULL;
                    for ( auto iterator = begin; iterator != end && found < count; ++ iterator ) {
                        if ( predicate ( * iterator ) ) {
                            ++ found;
                            (void) storeIn.insert ( iterator );
                        }
                    }

                    return storeIn;
                }


                template <
                        typename __IteratorType,                            // NOLINT(bugprone-reserved-identifier)
                        template < typename ... > class __CollectionType,   // NOLINT(bugprone-reserved-identifier)
                        typename __Predicate                                // NOLINT(bugprone-reserved-identifier)
                > constexpr auto __findThat (                               // NOLINT(bugprone-reserved-identifier)
                        __IteratorType                      const & begin,
                        __IteratorType                      const & end,
                        Size                                        count,
                        __Predicate                         const & predicate
                ) noexcept ( noexcept ( predicate ( * begin ) ) ) -> __CollectionType < __IteratorType > {

                    __CollectionType < __IteratorType > foundIterators;
                    return __findThat (
                            begin,
                            end,
                            count,
                            foundIterators,
                            predicate
                    );
                }


                template <
                        typename __IteratorType,    // NOLINT(bugprone-reserved-identifier)
                        typename __Predicate        // NOLINT(bugprone-reserved-identifier)
                > constexpr auto __findFirstThat (  // NOLINT(bugprone-reserved-identifier)
                        __IteratorType                      const & begin,
                        __IteratorType                      const & end,
                        __Predicate                         const & predicate
                ) noexcept ( noexcept ( predicate ( * begin ) ) ) -> __IteratorType {

                    for ( auto iterator = begin; iterator != end; ++ iterator ) {
                        if ( predicate ( * iterator ) ) {
                            return iterator;
                        }
                    }

                    return end;
                }


                template <
                        typename __IteratorType,    // NOLINT(bugprone-reserved-identifier)
                        typename __Predicate        // NOLINT(bugprone-reserved-identifier)
                > constexpr auto __findLastThat (   // NOLINT(bugprone-reserved-identifier)
                        __IteratorType                      const & begin,
                        __IteratorType                      const & end,
                        __Predicate                         const & predicate
                ) noexcept ( noexcept ( predicate ( * begin ) ) ) -> __IteratorType {

                    auto lastFound = end;
                    for ( auto iterator = begin; iterator != end; ++ iterator ) {
                        if ( predicate ( * iterator ) ) {
                            lastFound = iterator;
                        }
                    }

                    return lastFound;
                }


                template <
                        typename __IteratorType,                            // NOLINT(bugprone-reserved-identifier)
                        template < typename ... > class __CollectionType,   // NOLINT(bugprone-reserved-identifier)
                        typename __Predicate                                // NOLINT(bugprone-reserved-identifier)
                > constexpr auto __findAllThat (                            // NOLINT(bugprone-reserved-identifier)
                        __IteratorType                      const & begin,
                        __IteratorType                      const & end,
                        __CollectionType < __IteratorType >       & storeIn,
                        __Predicate                         const & predicate
                ) noexcept ( noexcept ( predicate ( * begin ) ) ) -> __CollectionType < __IteratorType > & {

                    for ( auto iterator = begin; iterator != end; ++ iterator ) {
                        if ( predicate ( * iterator ) ) {
                            (void) storeIn.insert ( iterator );
                        }
                    }

                    return storeIn;
                }


                template <
                        typename __IteratorType,                            // NOLINT(bugprone-reserved-identifier)
                        template < typename ... > class __CollectionType,   // NOLINT(bugprone-reserved-identifier)
                        typename __Predicate                                // NOLINT(bugprone-reserved-identifier)
                > constexpr auto __findAllThat (                            // NOLINT(bugprone-reserved-identifier)
                        __IteratorType                      const & begin,
                        __IteratorType                      const & end,
                        __Predicate                         const & predicate
                ) noexcept ( noexcept ( predicate ( * begin ) ) ) -> __CollectionType < __IteratorType > {

                    __CollectionType < __IteratorType > foundIterators;
                    return __findAllThat (
                            begin,
                            end,
                            foundIterators
                    );
                }

            }
        }
    }
}

#endif // __CDS_SHARED_ITERATOR_FIND_STATEMENTS_IMPL_HPP__
