/*
 * Created by loghin on 6/27/22.
 */

#ifndef __CDS_SHARED_EX_ITERATOR_FIND_HPP__
#define __CDS_SHARED_EX_ITERATOR_FIND_HPP__ /* NOLINT(bugprone-reserved-identifier) */

#warning No longer an experimental feature. Use the non-experimental header.
#include "../../../../shared/iterator/IteratorFind.hpp"

namespace cds {                 /* NOLINT(modernize-concat-nested-namespaces) */
    namespace experimental {    /* NOLINT(modernize-concat-nested-namespaces) */
        namespace __hidden {    /* NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier) */
            namespace __impl {  /* NOLINT(bugprone-reserved-identifier) */

                template <
                        typename                                                                            __ElementType,      /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                                            __IteratorType,     /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                                            __IterableType,     /* NOLINT(bugprone-reserved-identifier) */
                        template < typename ... > class                                                     __CollectionType,   /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __ContainsFunction < __IterableType, __ElementType >   __containsFunction  /* NOLINT(bugprone-reserved-identifier) */
                > __CDS_DeprecatedHint("No longer an experimental feature.") __CDS_cpplang_ConstexprConditioned auto __findOf ( /* NOLINT(bugprone-reserved-identifier) */
                        __IteratorType                      const & begin,
                        __IteratorType                      const & end,
                        Size                                        count,
                        __CollectionType < __IteratorType >       & storeIn,
                        __IterableType                      const & from
                ) noexcept -> __CollectionType < __IteratorType > & {

                    return cds :: __hidden :: __impl :: __findOf < __ElementType, __IteratorType, __IterableType, __CollectionType, __containsFunction > ( begin, end, count, storeIn, from );
                }


                template <
                        typename                                                                            __ElementType,                              /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                                            __IteratorType,                             /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                                            __IterableType,                             /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __ContainsFunction < __IterableType, __ElementType >   __containsFunction                          /* NOLINT(bugprone-reserved-identifier) */
                > __CDS_NoDiscard __CDS_DeprecatedHint("No longer an experimental feature.") __CDS_cpplang_ConstexprConditioned auto __findFirstOf (    /* NOLINT(bugprone-reserved-identifier) */
                        __IteratorType                      const & begin,
                        __IteratorType                      const & end,
                        __IterableType                      const & from
                ) noexcept -> __IteratorType {

                    return cds :: __hidden :: __impl :: __findFirstOf < __ElementType, __IteratorType, __IterableType, __containsFunction > ( begin, end, from );
                }


                template <
                        typename                                                                                __ElementType,                      /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                                                __IteratorType,                     /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                                                __IterableType,                     /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __ContainsFunction < __IterableType, __ElementType >       __containsFunction                  /* NOLINT(bugprone-reserved-identifier) */
                > __CDS_NoDiscard __CDS_DeprecatedHint("No longer an experimental feature.") __CDS_cpplang_ConstexprConditioned auto __findLastOf ( /* NOLINT(bugprone-reserved-identifier) */
                        __IteratorType                      const & begin,
                        __IteratorType                      const & end,
                        __IterableType                      const & from
                ) noexcept -> __IteratorType {

                    return cds :: __hidden :: __impl :: __findLastOf < __ElementType, __IteratorType, __IterableType, __containsFunction > ( begin, end, from );
                }


                template <
                        typename                                                                            __ElementType,          /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                                            __IteratorType,         /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                                            __IterableType,         /* NOLINT(bugprone-reserved-identifier) */
                        template < typename ... > class                                                     __CollectionType,       /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __ContainsFunction < __IterableType, __ElementType >   __containsFunction      /* NOLINT(bugprone-reserved-identifier) */
                > __CDS_DeprecatedHint("No longer an experimental feature.") __CDS_cpplang_ConstexprConditioned auto __findAllOf (  /* NOLINT(bugprone-reserved-identifier) */
                        __IteratorType                      const & begin,
                        __IteratorType                      const & end,
                        __CollectionType < __IteratorType >       & storeIn,
                        __IterableType                      const & from
                ) noexcept -> __CollectionType < __IteratorType > & {

                    return cds :: __hidden :: __impl :: __findAllOf < __ElementType, __IteratorType, __IterableType, __CollectionType, __containsFunction > ( begin, end, storeIn, from );
                }

            }
        }
    }
}

#endif /* __CDS_EX_SHARED_ITERATOR_FIND_HPP__ */
