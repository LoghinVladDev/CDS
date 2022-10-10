/*
 * Created by loghin on 6/27/22.
 */

#ifndef __CDS_EX_SHARED_ITERATOR_FIND_STATEMENTS_HPP__
#define __CDS_EX_SHARED_ITERATOR_FIND_STATEMENTS_HPP__ /* NOLINT(bugprone-reserved-identifier) */

#warning No longer an experimental feature. Use the non-experimental header.
#include "../../../../shared/iterator/IteratorFindStatements.hpp"

namespace cds {                 /* NOLINT(modernize-concat-nested-namespaces) */
    namespace experimental {    /* NOLINT(modernize-concat-nested-namespaces) */
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
                        > = 0
                > __CDS_DeprecatedHint("No longer an experimental feature.") __CDS_cpplang_ConstexprConditioned auto __findThat (      /* NOLINT(bugprone-reserved-identifier) */
                        __IteratorType                      const & begin,
                        __IteratorType                      const & end,
                        Size                                        count,
                        __CollectionType < __IteratorType >       & storeIn,
                        __Predicate                         const & predicate
                ) noexcept ( noexcept ( predicate ( * begin ) ) ) -> __CollectionType < __IteratorType > & {

                    return cds :: __hidden :: __impl :: __findThat < __IteratorType, __CollectionType, __Predicate > ( begin, end, count, storeIn, predicate );
                }


                template <
                        typename __IteratorType,                                            /* NOLINT(bugprone-reserved-identifier) */
                        typename __Predicate,                                               /* NOLINT(bugprone-reserved-identifier) */
                        cds :: meta :: EnableIf <
                                ! cds :: meta :: isMemberFunctionPointer <
                                        __Predicate,
                                        cds :: meta :: Decay < decltype ( * cds :: meta :: valueOf < __IteratorType > () ) >
                                > ()
                        > = 0
                > __CDS_NoDiscard __CDS_DeprecatedHint("No longer an experimental feature.") __CDS_cpplang_ConstexprConditioned auto __findFirstThat ( /* NOLINT(bugprone-reserved-identifier) */
                        __IteratorType                      const & begin,
                        __IteratorType                      const & end,
                        __Predicate                         const & predicate
                ) noexcept ( noexcept ( predicate ( * begin ) ) ) -> __IteratorType {

                    return cds :: __hidden :: __impl :: __findFirstThat < __IteratorType, __Predicate > ( begin, end, predicate );
                }


                template <
                        typename __IteratorType,                                            /* NOLINT(bugprone-reserved-identifier) */
                        typename __Predicate,                                               /* NOLINT(bugprone-reserved-identifier) */
                        cds :: meta :: EnableIf <
                                ! cds :: meta :: isMemberFunctionPointer <
                                        __Predicate,
                                        cds :: meta :: Decay < decltype ( * cds :: meta :: valueOf < __IteratorType > () ) >
                                > ()
                        > = 0
                > __CDS_NoDiscard __CDS_DeprecatedHint("No longer an experimental feature.") __CDS_cpplang_ConstexprConditioned auto __findLastThat (  /* NOLINT(bugprone-reserved-identifier) */
                        __IteratorType                      const & begin,
                        __IteratorType                      const & end,
                        __Predicate                         const & predicate
                ) noexcept ( noexcept ( predicate ( * begin ) ) ) -> __IteratorType {

                    return cds :: __hidden :: __impl :: __findLastThat < __IteratorType, __Predicate > ( begin, end, predicate );
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
                        > = 0
                > __CDS_DeprecatedHint("No longer an experimental feature.") __CDS_cpplang_ConstexprConditioned auto __findAllThat (   /* NOLINT(bugprone-reserved-identifier) */
                        __IteratorType                      const & begin,
                        __IteratorType                      const & end,
                        __CollectionType < __IteratorType >       & storeIn,
                        __Predicate                         const & predicate
                ) noexcept ( noexcept ( predicate ( * begin ) ) ) -> __CollectionType < __IteratorType > & {

                    return cds :: __hidden :: __impl :: __findAllThat < __IteratorType, __CollectionType, __Predicate > ( begin, end, storeIn, predicate );
                }

            }
        }
    }
}

#endif /* __CDS_EX_SHARED_ITERATOR_FIND_STATEMENTS_HPP__ */
