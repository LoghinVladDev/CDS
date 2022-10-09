/*
 * Created by loghin on 6/27/22.
 */

#ifndef __CDS_SHARED_ITERATOR_FIND_IMPL_HPP__
#define __CDS_SHARED_ITERATOR_FIND_IMPL_HPP__ /* NOLINT(bugprone-reserved-identifier) */

namespace cds {                 /* NOLINT(modernize-concat-nested-namespaces) */
    namespace experimental {    /* NOLINT(modernize-concat-nested-namespaces) */
        namespace __hidden {    /* NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier) */
            namespace __impl {  /* NOLINT(bugprone-reserved-identifier) */

                template <
                        typename                                                __ElementType,      /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                __IteratorType,     /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                __IterableType,     /* NOLINT(bugprone-reserved-identifier) */
                        template < typename ... > class                         __CollectionType,   /* NOLINT(bugprone-reserved-identifier) */
                        __ContainsFunction < __IterableType, __ElementType >    __containsFunction  /* NOLINT(bugprone-reserved-identifier) */
                > __CDS_cpplang_ConstexprConditioned auto __findOf (                                /* NOLINT(bugprone-reserved-identifier) */
                        __IteratorType                      const & begin,
                        __IteratorType                      const & end,
                        Size                                        count,
                        __CollectionType < __IteratorType >       & storeIn,
                        __IterableType                      const & from
                ) noexcept -> __CollectionType < __IteratorType > & {

                    /* parse the range until the end, or until the given limit is reached */
                    for ( auto iterator = begin; iterator != end && count != 0U; ++ iterator ) {

                        /* if element at iterator is also found in given 'from' iterable */
                        if ( __containsFunction ( from, * iterator ) ) {

                            /* decrease the limit and store the iterator */
                            -- count;
                            (void) storeIn.insert ( iterator );
                        }
                    }

                    /* return reference to updated collection */
                    return storeIn;
                }


                template <
                        typename                                                __ElementType,      /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                __IteratorType,     /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                __IterableType,     /* NOLINT(bugprone-reserved-identifier) */
                        __ContainsFunction < __IterableType, __ElementType >    __containsFunction  /* NOLINT(bugprone-reserved-identifier) */
                > __CDS_cpplang_ConstexprConditioned auto __findFirstOf (                           /* NOLINT(bugprone-reserved-identifier) */
                        __IteratorType                      const & begin,
                        __IteratorType                      const & end,
                        __IterableType                      const & from
                ) noexcept -> __IteratorType {

                    /* parse the range */
                    for ( auto iterator = begin; iterator != end; ++ iterator ) {

                        /* if element at iterator is also found in given 'from' iterable */
                        if ( __containsFunction ( from, * iterator ) ) {

                            /* return the iterator */
                            return iterator;
                        }
                    }

                    /* otherwise, no iterator with element located in given iterable, return 'end' */
                    return end;
                }


                template <
                        typename                                                __ElementType,      /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                __IteratorType,     /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                __IterableType,     /* NOLINT(bugprone-reserved-identifier) */
                        __ContainsFunction < __IterableType, __ElementType >    __containsFunction  /* NOLINT(bugprone-reserved-identifier) */
                > __CDS_cpplang_ConstexprConditioned auto __findLastOf (                            /* NOLINT(bugprone-reserved-identifier) */
                        __IteratorType                      const & begin,
                        __IteratorType                      const & end,
                        __IterableType                      const & from
                ) noexcept -> __IteratorType {

                    /* create a local iterator to return the last match into. Initialize with 'end' in case of none found */
                    auto lastFound = end;

                    /* parse the range */
                    for ( auto iterator = begin; iterator != end; ++ iterator ) {

                        /* if element at iterator is also found in given 'from' iterable */
                        if ( __containsFunction ( from, * iterator ) ) {

                            /* store the iterator locally */
                            lastFound = iterator;
                        }
                    }

                    /* return the last match */
                    return lastFound;
                }


                template <
                        typename                                                __ElementType,      /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                __IteratorType,     /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                __IterableType,     /* NOLINT(bugprone-reserved-identifier) */
                        template < typename ... > class                         __CollectionType,   /* NOLINT(bugprone-reserved-identifier) */
                        __ContainsFunction < __IterableType, __ElementType >    __containsFunction  /* NOLINT(bugprone-reserved-identifier) */
                > __CDS_cpplang_ConstexprConditioned auto __findAllOf (                             /* NOLINT(bugprone-reserved-identifier) */
                        __IteratorType                      const & begin,
                        __IteratorType                      const & end,
                        __CollectionType < __IteratorType >       & storeIn,
                        __IterableType                      const & from
                ) noexcept -> __CollectionType < __IteratorType > & {

                    /* parse the range */
                    for ( auto iterator = begin; iterator != end; ++ iterator ) {

                        /* if element at iterator is also found in given 'from' iterable */
                        if ( __containsFunction ( from, * iterator ) ) {

                            /* store the iterator */
                            (void) storeIn.insert ( iterator );
                        }
                    }

                    /* return reference to updated collection */
                    return storeIn;
                }

            }
        }
    }
}

#endif /* __CDS_SHARED_ITERATOR_FIND_IMPL_HPP__ */
