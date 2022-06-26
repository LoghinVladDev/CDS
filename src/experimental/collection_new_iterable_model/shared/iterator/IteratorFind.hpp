//
// Created by loghin on 6/27/22.
//

#ifndef __CDS_SHARED_ITERATOR_FIND_HPP__
#define __CDS_SHARED_ITERATOR_FIND_HPP__

namespace cds {                 // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {    // NOLINT(modernize-concat-nested-namespaces)
        namespace __hidden {    // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier)
            namespace __impl {  // NOLINT(bugprone-reserved-identifier)

                template <
                        typename                                                __ElementType,      // NOLINT(bugprone-reserved-identifier)
                        typename                                                __IteratorType,     // NOLINT(bugprone-reserved-identifier)
                        typename                                                __IterableType,     // NOLINT(bugprone-reserved-identifier)
                        template < typename ... > class                         __CollectionType,   // NOLINT(bugprone-reserved-identifier)
                        __ContainsFunction < __IterableType, __ElementType >    __containsFunction  // NOLINT(bugprone-reserved-identifier)
                > constexpr auto __findOf (                                                         // NOLINT(bugprone-reserved-identifier)
                        __IteratorType                      const & begin,
                        __IteratorType                      const & end,
                        Size                                        count,
                        __CollectionType < __IteratorType >       & storeIn,
                        __IterableType                      const & from
                ) noexcept -> __CollectionType < __IteratorType > &;

                template <
                        typename                                                __ElementType,      // NOLINT(bugprone-reserved-identifier)
                        typename                                                __IteratorType,     // NOLINT(bugprone-reserved-identifier)
                        typename                                                __IterableType,     // NOLINT(bugprone-reserved-identifier)
                        template < typename ... > class                         __CollectionType,   // NOLINT(bugprone-reserved-identifier)
                        __ContainsFunction < __IterableType, __ElementType >    __containsFunction  // NOLINT(bugprone-reserved-identifier)
                > __CDS_NoDiscard constexpr auto __findOf (                                         // NOLINT(bugprone-reserved-identifier)
                        __IteratorType                      const & begin,
                        __IteratorType                      const & end,
                        Size                                        count,
                        __IterableType                      const & from
                ) noexcept -> __CollectionType < __IteratorType >;

                template <
                        typename                                                __ElementType,      // NOLINT(bugprone-reserved-identifier)
                        typename                                                __IteratorType,     // NOLINT(bugprone-reserved-identifier)
                        typename                                                __IterableType,     // NOLINT(bugprone-reserved-identifier)
                        __ContainsFunction < __IterableType, __ElementType >    __containsFunction  // NOLINT(bugprone-reserved-identifier)
                > __CDS_NoDiscard constexpr auto __findFirstOf (                                    // NOLINT(bugprone-reserved-identifier)
                        __IteratorType                      const & begin,
                        __IteratorType                      const & end,
                        __IterableType                      const & from
                ) noexcept -> __IteratorType;

                template <
                        typename                                                __ElementType,      // NOLINT(bugprone-reserved-identifier)
                        typename                                                __IteratorType,     // NOLINT(bugprone-reserved-identifier)
                        typename                                                __IterableType,     // NOLINT(bugprone-reserved-identifier)
                        __ContainsFunction < __IterableType, __ElementType >    __containsFunction  // NOLINT(bugprone-reserved-identifier)
                > __CDS_NoDiscard constexpr auto __findLastOf (                                     // NOLINT(bugprone-reserved-identifier)
                        __IteratorType                      const & begin,
                        __IteratorType                      const & end,
                        __IterableType                      const & from
                ) noexcept -> __IteratorType;

                template <
                        typename                                                __ElementType,      // NOLINT(bugprone-reserved-identifier)
                        typename                                                __IteratorType,     // NOLINT(bugprone-reserved-identifier)
                        typename                                                __IterableType,     // NOLINT(bugprone-reserved-identifier)
                        template < typename ... > class                         __CollectionType,   // NOLINT(bugprone-reserved-identifier)
                        __ContainsFunction < __IterableType, __ElementType >    __containsFunction  // NOLINT(bugprone-reserved-identifier)
                > constexpr auto __findAllOf (                                                      // NOLINT(bugprone-reserved-identifier)
                        __IteratorType                      const & begin,
                        __IteratorType                      const & end,
                        __CollectionType < __IteratorType >       & storeIn,
                        __IterableType                      const & from
                ) noexcept -> __CollectionType < __IteratorType > &;

                template <
                        typename                                                __ElementType,      // NOLINT(bugprone-reserved-identifier)
                        typename                                                __IteratorType,     // NOLINT(bugprone-reserved-identifier)
                        typename                                                __IterableType,     // NOLINT(bugprone-reserved-identifier)
                        template < typename ... > class                         __CollectionType,   // NOLINT(bugprone-reserved-identifier)
                        __ContainsFunction < __IterableType, __ElementType >    __containsFunction  // NOLINT(bugprone-reserved-identifier)
                > __CDS_NoDiscard constexpr auto __findAllOf (                                      // NOLINT(bugprone-reserved-identifier)
                        __IteratorType                      const & begin,
                        __IteratorType                      const & end,
                        __IterableType                      const & from
                ) noexcept -> __CollectionType < __IteratorType >;

                template <
                        typename                                                __ElementType,      // NOLINT(bugprone-reserved-identifier)
                        typename                                                __IteratorType,     // NOLINT(bugprone-reserved-identifier)
                        typename                                                __IterableType,     // NOLINT(bugprone-reserved-identifier)
                        template < typename ... > class                         __CollectionType,   // NOLINT(bugprone-reserved-identifier)
                        __ContainsFunction < __IterableType, __ElementType >    __containsFunction  // NOLINT(bugprone-reserved-identifier)
                > constexpr auto __findNotOf (                                                      // NOLINT(bugprone-reserved-identifier)
                        __IteratorType                      const & begin,
                        __IteratorType                      const & end,
                        Size                                        count,
                        __CollectionType < __IteratorType >       & storeIn,
                        __IterableType                      const & from
                ) noexcept -> __CollectionType < __IteratorType > &;

                template <
                        typename                                                __ElementType,      // NOLINT(bugprone-reserved-identifier)
                        typename                                                __IteratorType,     // NOLINT(bugprone-reserved-identifier)
                        typename                                                __IterableType,     // NOLINT(bugprone-reserved-identifier)
                        template < typename ... > class                         __CollectionType,   // NOLINT(bugprone-reserved-identifier)
                        __ContainsFunction < __IterableType, __ElementType >    __containsFunction  // NOLINT(bugprone-reserved-identifier)
                > __CDS_NoDiscard constexpr auto __findNotOf (                                      // NOLINT(bugprone-reserved-identifier)
                        __IteratorType                      const & begin,
                        __IteratorType                      const & end,
                        Size                                        count,
                        __IterableType                      const & from
                ) noexcept -> __CollectionType < __IteratorType >;

                template <
                        typename                                                __ElementType,      // NOLINT(bugprone-reserved-identifier)
                        typename                                                __IteratorType,     // NOLINT(bugprone-reserved-identifier)
                        typename                                                __IterableType,     // NOLINT(bugprone-reserved-identifier)
                        __ContainsFunction < __IterableType, __ElementType >    __containsFunction  // NOLINT(bugprone-reserved-identifier)
                > __CDS_NoDiscard constexpr auto __findFirstNotOf (                                 // NOLINT(bugprone-reserved-identifier)
                        __IteratorType                      const & begin,
                        __IteratorType                      const & end,
                        __IterableType                      const & from
                ) noexcept -> __IteratorType;

                template <
                        typename                                                __ElementType,      // NOLINT(bugprone-reserved-identifier)
                        typename                                                __IteratorType,     // NOLINT(bugprone-reserved-identifier)
                        typename                                                __IterableType,     // NOLINT(bugprone-reserved-identifier)
                        __ContainsFunction < __IterableType, __ElementType >    __containsFunction  // NOLINT(bugprone-reserved-identifier)
                > __CDS_NoDiscard constexpr auto __findLastNotOf (                                  // NOLINT(bugprone-reserved-identifier)
                        __IteratorType                      const & begin,
                        __IteratorType                      const & end,
                        __IterableType                      const & from
                ) noexcept -> __IteratorType;

                template <
                        typename                                                __ElementType,      // NOLINT(bugprone-reserved-identifier)
                        typename                                                __IteratorType,     // NOLINT(bugprone-reserved-identifier)
                        typename                                                __IterableType,     // NOLINT(bugprone-reserved-identifier)
                        template < typename ... > class                         __CollectionType,   // NOLINT(bugprone-reserved-identifier)
                        __ContainsFunction < __IterableType, __ElementType >    __containsFunction  // NOLINT(bugprone-reserved-identifier)
                > constexpr auto __findAllNotOf (                                                   // NOLINT(bugprone-reserved-identifier)
                        __IteratorType                      const & begin,
                        __IteratorType                      const & end,
                        __CollectionType < __IteratorType >       & storeIn,
                        __IterableType                      const & from
                ) noexcept -> __CollectionType < __IteratorType > &;

                template <
                        typename                                                __ElementType,      // NOLINT(bugprone-reserved-identifier)
                        typename                                                __IteratorType,     // NOLINT(bugprone-reserved-identifier)
                        typename                                                __IterableType,     // NOLINT(bugprone-reserved-identifier)
                        template < typename ... > class                         __CollectionType,   // NOLINT(bugprone-reserved-identifier)
                        __ContainsFunction < __IterableType, __ElementType >    __containsFunction  // NOLINT(bugprone-reserved-identifier)
                > __CDS_NoDiscard constexpr auto __findAllNotOf (                                   // NOLINT(bugprone-reserved-identifier)
                        __IteratorType                      const & begin,
                        __IteratorType                      const & end,
                        __IterableType                      const & from
                ) noexcept -> __CollectionType < __IteratorType >;

            }
        }
    }
}

#endif // __CDS_SHARED_ITERATOR_FIND_HPP__
