//
// Created by loghin on 6/27/22.
//

#ifndef __CDS_SHARED_ITERATOR_FIND_STATEMENTS_HPP__
#define __CDS_SHARED_ITERATOR_FIND_STATEMENTS_HPP__

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
                ) noexcept ( noexcept ( predicate ( * begin ) ) ) -> __CollectionType < __IteratorType > &;

                template <
                        typename __IteratorType,                            // NOLINT(bugprone-reserved-identifier)
                        template < typename ... > class __CollectionType,   // NOLINT(bugprone-reserved-identifier)
                        typename __Predicate                                // NOLINT(bugprone-reserved-identifier)
                > constexpr auto __findThat (                               // NOLINT(bugprone-reserved-identifier)
                        __IteratorType                      const & begin,
                        __IteratorType                      const & end,
                        Size                                        count,
                        __Predicate                         const & predicate
                ) noexcept ( noexcept ( predicate ( * begin ) ) ) -> __CollectionType < __IteratorType >;

                template <
                        typename __IteratorType,    // NOLINT(bugprone-reserved-identifier)
                        typename __Predicate        // NOLINT(bugprone-reserved-identifier)
                > constexpr auto __findFirstThat (  // NOLINT(bugprone-reserved-identifier)
                        __IteratorType                      const & begin,
                        __IteratorType                      const & end,
                        __Predicate                         const & predicate
                ) noexcept ( noexcept ( predicate ( * begin ) ) ) -> __IteratorType;

                template <
                        typename __IteratorType,    // NOLINT(bugprone-reserved-identifier)
                        typename __Predicate        // NOLINT(bugprone-reserved-identifier)
                > constexpr auto __findLastThat (   // NOLINT(bugprone-reserved-identifier)
                        __IteratorType                      const & begin,
                        __IteratorType                      const & end,
                        __Predicate                         const & predicate
                ) noexcept ( noexcept ( predicate ( * begin ) ) ) -> __IteratorType;

                template <
                        typename __IteratorType,                            // NOLINT(bugprone-reserved-identifier)
                        template < typename ... > class __CollectionType,   // NOLINT(bugprone-reserved-identifier)
                        typename __Predicate                                // NOLINT(bugprone-reserved-identifier)
                > constexpr auto __findAllThat (                            // NOLINT(bugprone-reserved-identifier)
                        __IteratorType                      const & begin,
                        __IteratorType                      const & end,
                        __CollectionType < __IteratorType >       & storeIn,
                        __Predicate                         const & predicate
                ) noexcept ( noexcept ( predicate ( * begin ) ) ) -> __CollectionType < __IteratorType > &;

                template <
                        typename __IteratorType,                            // NOLINT(bugprone-reserved-identifier)
                        template < typename ... > class __CollectionType,   // NOLINT(bugprone-reserved-identifier)
                        typename __Predicate                                // NOLINT(bugprone-reserved-identifier)
                > constexpr auto __findAllThat (                            // NOLINT(bugprone-reserved-identifier)
                        __IteratorType                      const & begin,
                        __IteratorType                      const & end,
                        __Predicate                         const & predicate
                ) noexcept ( noexcept ( predicate ( * begin ) ) ) -> __CollectionType < __IteratorType >;

            }
        }
    }
}

#endif // __CDS_SHARED_ITERATOR_FIND_STATEMENTS_HPP__
