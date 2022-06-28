//
// Created by loghin on 6/27/22.
//

#ifndef __CDS_SHARED_ITERATOR_FIND_IMPL_HPP__
#define __CDS_SHARED_ITERATOR_FIND_IMPL_HPP__

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
                ) noexcept -> __CollectionType < __IteratorType > & {

                    Size found = 0ULL;
                    for ( auto iterator = begin; iterator != end && found < count; ++ iterator ) {
                        if ( __containsFunction ( from, * iterator ) ) {
                            ++ found;
                            (void) storeIn.insert ( iterator );
                        }
                    }

                    return storeIn;
                }


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
                        __IterableType                      const & from
                ) noexcept -> __CollectionType < __IteratorType > {

                    __CollectionType < __IteratorType > foundIterators;
                    return __findOf <
                            __ElementType,
                            __IteratorType,
                            __IterableType,
                            __CollectionType,
                            __containsFunction
                    > (
                            begin,
                            end,
                            count,
                            foundIterators,
                            from
                    );
                }


                template <
                        typename                                                __ElementType,      // NOLINT(bugprone-reserved-identifier)
                        typename                                                __IteratorType,     // NOLINT(bugprone-reserved-identifier)
                        typename                                                __IterableType,     // NOLINT(bugprone-reserved-identifier)
                        __ContainsFunction < __IterableType, __ElementType >    __containsFunction  // NOLINT(bugprone-reserved-identifier)
                > constexpr auto __findFirstOf (                                                    // NOLINT(bugprone-reserved-identifier)
                        __IteratorType                      const & begin,
                        __IteratorType                      const & end,
                        __IterableType                      const & from
                ) noexcept -> __IteratorType {

                    for ( auto iterator = begin; iterator != end; ++ iterator ) {
                        if ( __containsFunction ( from, * iterator ) ) {
                            return iterator;
                        }
                    }

                    return end;
                }


                template <
                        typename                                                __ElementType,      // NOLINT(bugprone-reserved-identifier)
                        typename                                                __IteratorType,     // NOLINT(bugprone-reserved-identifier)
                        typename                                                __IterableType,     // NOLINT(bugprone-reserved-identifier)
                        __ContainsFunction < __IterableType, __ElementType >    __containsFunction  // NOLINT(bugprone-reserved-identifier)
                > constexpr auto __findLastOf (                                                     // NOLINT(bugprone-reserved-identifier)
                        __IteratorType                      const & begin,
                        __IteratorType                      const & end,
                        __IterableType                      const & from
                ) noexcept -> __IteratorType {

                    auto lastFound = end;
                    for ( auto iterator = begin; iterator != end; ++ iterator ) {
                        if ( __containsFunction ( from, * iterator ) ) {
                            lastFound = iterator;
                        }
                    }

                    return lastFound;
                }


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
                ) noexcept -> __CollectionType < __IteratorType > & {

                    for ( auto iterator = begin; iterator != end; ++ iterator ) {
                        if ( __containsFunction ( from, * iterator ) ) {
                            (void) storeIn.insert ( iterator );
                        }
                    }

                    return storeIn;
                }


                template <
                        typename                                                __ElementType,      // NOLINT(bugprone-reserved-identifier)
                        typename                                                __IteratorType,     // NOLINT(bugprone-reserved-identifier)
                        typename                                                __IterableType,     // NOLINT(bugprone-reserved-identifier)
                        template < typename ... > class                         __CollectionType,   // NOLINT(bugprone-reserved-identifier)
                        __ContainsFunction < __IterableType, __ElementType >    __containsFunction  // NOLINT(bugprone-reserved-identifier)
                > constexpr auto __findAllOf (                                                      // NOLINT(bugprone-reserved-identifier)
                        __IteratorType                      const & begin,
                        __IteratorType                      const & end,
                        __IterableType                      const & from
                ) noexcept -> __CollectionType < __IteratorType > {

                    __CollectionType < __IteratorType > foundIterators;
                    return __findAllOf <
                            __ElementType,
                            __IteratorType,
                            __IterableType,
                            __CollectionType,
                            __containsFunction
                    > (
                            begin,
                            end,
                            foundIterators,
                            from
                    );
                }


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
                ) noexcept -> __CollectionType < __IteratorType > & {

                    Size found = 0ULL;
                    for ( auto iterator = begin; iterator != end && found < count; ++ iterator ) {
                        if ( ! __containsFunction ( from, * iterator ) ) {
                            ++ found;
                            (void) storeIn.insert ( iterator );
                        }
                    }

                    return storeIn;
                }


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
                        __IterableType                      const & from
                ) noexcept -> __CollectionType < __IteratorType > {

                    __CollectionType < __IteratorType > foundIterators;
                    return __findNotOf <
                            __ElementType,
                            __IteratorType,
                            __IterableType,
                            __CollectionType,
                            __containsFunction
                    > (
                            begin,
                            end,
                            count,
                            foundIterators,
                            from
                    );
                }


                template <
                        typename                                                __ElementType,      // NOLINT(bugprone-reserved-identifier)
                        typename                                                __IteratorType,     // NOLINT(bugprone-reserved-identifier)
                        typename                                                __IterableType,     // NOLINT(bugprone-reserved-identifier)
                        __ContainsFunction < __IterableType, __ElementType >    __containsFunction  // NOLINT(bugprone-reserved-identifier)
                > constexpr auto __findFirstNotOf (                                                 // NOLINT(bugprone-reserved-identifier)
                        __IteratorType                      const & begin,
                        __IteratorType                      const & end,
                        __IterableType                      const & from
                ) noexcept -> __IteratorType {

                    for ( auto iterator = begin; iterator != end; ++ iterator ) {
                        if ( ! __containsFunction ( from, * iterator ) ) {
                            return iterator;
                        }
                    }

                    return end;
                }


                template <
                        typename                                                __ElementType,      // NOLINT(bugprone-reserved-identifier)
                        typename                                                __IteratorType,     // NOLINT(bugprone-reserved-identifier)
                        typename                                                __IterableType,     // NOLINT(bugprone-reserved-identifier)
                        __ContainsFunction < __IterableType, __ElementType >    __containsFunction  // NOLINT(bugprone-reserved-identifier)
                > constexpr auto __findLastNotOf (                                                  // NOLINT(bugprone-reserved-identifier)
                        __IteratorType                      const & begin,
                        __IteratorType                      const & end,
                        __IterableType                      const & from
                ) noexcept -> __IteratorType {

                    auto lastFound = end;
                    for ( auto iterator = begin; iterator != end; ++ iterator ) {
                        if ( ! __containsFunction ( from, * iterator ) ) {
                            lastFound = iterator;
                        }
                    }

                    return lastFound;
                }


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
                ) noexcept -> __CollectionType < __IteratorType > & {

                    for ( auto iterator = begin; iterator != end; ++ iterator ) {
                        if ( ! __containsFunction ( from, * iterator ) ) {
                            (void) storeIn.insert ( iterator );
                        }
                    }

                    return storeIn;
                }


                template <
                        typename                                                __ElementType,      // NOLINT(bugprone-reserved-identifier)
                        typename                                                __IteratorType,     // NOLINT(bugprone-reserved-identifier)
                        typename                                                __IterableType,     // NOLINT(bugprone-reserved-identifier)
                        template < typename ... > class                         __CollectionType,   // NOLINT(bugprone-reserved-identifier)
                        __ContainsFunction < __IterableType, __ElementType >    __containsFunction  // NOLINT(bugprone-reserved-identifier)
                > constexpr auto __findAllNotOf (                                                   // NOLINT(bugprone-reserved-identifier)
                        __IteratorType                      const & begin,
                        __IteratorType                      const & end,
                        __IterableType                      const & from
                ) noexcept -> __CollectionType < __IteratorType > {

                    __CollectionType < __IteratorType > foundIterators;
                    return __findAllNotOf <
                            __ElementType,
                            __IteratorType,
                            __IterableType,
                            __CollectionType,
                            __containsFunction
                    > (
                            begin,
                            end,
                            foundIterators,
                            from
                    );
                }

            }
        }
    }
}

#endif // __CDS_SHARED_ITERATOR_FIND_IMPL_HPP__
