/*
 * Created by loghin on 6/26/22.
 */

#ifndef __CDS_SHARED_REMOVE_BY_COMPOSITE_CLIENT_IMPL_HPP__ /* NOLINT(llvm-header-guard) */
#define __CDS_SHARED_REMOVE_BY_COMPOSITE_CLIENT_IMPL_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
 
namespace cds {             /* NOLINT(modernize-concat-nested-namespaces) */
    namespace __hidden {    /* NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        namespace __impl {  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            template <
                    typename __IterableType,        /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ElementType          /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > template <
                    typename __Predicate,           /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    cds :: meta :: EnableIf <
                            ! cds :: meta ::isMemberFunctionPointer <
                                    __Predicate,
                                    cds :: meta :: Decay < __ElementType >
                            > ()
                    >
            > auto __RemoveByCompositeClient <
                    __IterableType,
                    __ElementType
            > :: removeThat (
                    Size count,
                    __Predicate const & predicate
            ) noexcept ( noexcept ( predicate ( cds :: meta :: referenceOf < ElementType > () ) ) ) -> Size {

                /* local alias for iterable Const Iterator type */
                using ConstIterator     = typename __IterableType :: ConstIterator;

                /* allocate space to store acquired iterators into */
                auto pIteratorBuffer    = cds :: __hidden :: __impl :: __allocation :: __allocPrimitiveArray < ConstIterator > ( count );

                /* variables used to store number of iterators for matching elements, number of removed elements,
                 * and current object, reinterpreted as caller class */
                Size iteratorCount      = 0ULL;
                Size removedCount       = 0ULL;
                auto const pIterable    = reinterpret_cast < __IterableType * > ( this );

                /* parse through elements using Const Iteration, stop if reached the given limit */
                for ( auto iterator = pIterable->cbegin (), end = pIterable->cend (); iterator != end && iteratorCount < count; ++ iterator ) {

                    /* if the element is validated by the predicate, initialize memory of iterator */
                    if ( predicate ( * iterator ) ) {
                        new ( & pIteratorBuffer [ iteratorCount ++ ] ) ConstIterator ( iterator );
                    }
                }

                if ( iteratorCount >= 2ULL ) {
                    /* if more or two elements found, use removeAll */
                    removedCount = pIterable->removeAll (
                            & pIteratorBuffer [0U],
                            iteratorCount
                    );

                } else if ( iteratorCount == 1ULL ) {
                    /* if only one found, use remove */
                    removedCount = pIterable->remove (
                            pIteratorBuffer [0U]
                    ) ? 1ULL : 0ULL;
                }

                /* if none found, do nothing */

                /* destroy stored iterators */
                for ( Size index = 0ULL; index < iteratorCount; ++ index ) {
                    pIteratorBuffer [ index ].~ConstIterator ();
                }

                /* free the iterator memory and return number of removed elements */
                cds :: __hidden :: __impl :: __allocation :: __freePrimitiveArray ( pIteratorBuffer );
                return removedCount;
            }


            template <
                    typename __IterableType,        /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ElementType          /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > template <
                    typename __Predicate,           /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    cds :: meta :: EnableIf <
                            cds :: meta ::isMemberFunctionPointer <
                                    __Predicate,
                                    cds :: meta :: Decay < __ElementType >
                            > ()
                    >
            > auto __RemoveByCompositeClient <
                    __IterableType,
                    __ElementType
            > :: removeThat (
                    Size count,
                    __Predicate const & predicate
            ) noexcept ( noexcept ( ( cds :: meta :: addressOf < ElementType > () ->* predicate ) () ) ) -> Size {

                /* local alias for iterable Const Iterator type */
                using ConstIterator     = typename __IterableType :: ConstIterator;

                /* allocate space to store acquired iterators into */
                auto pIteratorBuffer    = cds :: __hidden :: __impl :: __allocation :: __allocPrimitiveArray < ConstIterator > ( count );

                /* variables used to store number of iterators for matching elements, number of removed elements,
                 * and current object, reinterpreted as caller class */
                Size iteratorCount      = 0ULL;
                Size removedCount       = 0ULL;
                auto const pIterable    = reinterpret_cast < __IterableType * > ( this );

                /* parse through elements using Const Iteration, stop if reached the given limit */
                for ( auto iterator = pIterable->cbegin(), end = pIterable->cend(); iterator != end && iteratorCount < count; ++ iterator ) {

                    /* if the element is validated by the predicate, initialize memory of iterator */
                    if ( ( ( * iterator ).* predicate ) () ) {
                        new ( & pIteratorBuffer [ iteratorCount ++ ] ) ConstIterator ( iterator );
                    }
                }

                if ( iteratorCount >= 2ULL ) {
                    /* if more or two elements found, use removeAll */
                    removedCount = pIterable->removeAll (
                            & pIteratorBuffer [0U],
                            iteratorCount
                    );

                } else if ( iteratorCount == 1ULL ) {
                    /* if only one found, use remove */
                    removedCount = pIterable->remove (
                            pIteratorBuffer [0U]
                    ) ? 1ULL : 0ULL;
                }

                /* if none found, do nothing */

                /* destroy stored iterators */
                for ( Size index = 0ULL; index < iteratorCount; ++ index ) {
                    pIteratorBuffer [ index ].~ConstIterator ();
                }

                /* free the iterator memory and return number of removed elements */
                cds :: __hidden :: __impl :: __allocation :: __freePrimitiveArray ( pIteratorBuffer );
                return removedCount;
            }


            template <
                    typename __IterableType,        /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ElementType          /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > template <
                    typename __Predicate,           /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    cds :: meta :: EnableIf <
                            ! cds :: meta ::isMemberFunctionPointer <
                                    __Predicate,
                                    cds :: meta :: Decay < __ElementType >
                            > ()
                    >
            > auto __RemoveByCompositeClient <
                    __IterableType,
                    __ElementType
            > :: removeFirstThat (
                    __Predicate const & predicate
            ) noexcept ( noexcept ( predicate ( cds :: meta :: referenceOf < ElementType > () ) ) ) -> bool {

                /* store reinterpreted object as caller class */
                auto const pIterable    = reinterpret_cast < __IterableType * > ( this );

                /* parse through elements using Const Iteration */
                for ( auto iterator = pIterable->cbegin(), end = pIterable->cend(); iterator != end; ++ iterator ) {

                    /* if the element is validated by the predicate, call remove primitive and return result */
                    if ( predicate ( * iterator ) ) {
                        return reinterpret_cast < __IterableType * > ( this )->remove ( iterator );
                    }
                }

                /* iteration ended, nothing returned, no element removed */
                return false;
            }


            template <
                    typename __IterableType,        /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ElementType          /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > template <
                    typename __Predicate,           /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    cds :: meta :: EnableIf <
                            cds :: meta ::isMemberFunctionPointer <
                                    __Predicate,
                                    cds :: meta :: Decay < __ElementType >
                            > ()
                    >
            > auto __RemoveByCompositeClient <
                    __IterableType,
                    __ElementType
            > :: removeFirstThat (
                    __Predicate const & predicate
            ) noexcept ( noexcept ( ( cds :: meta :: addressOf < ElementType > () ->* predicate ) () ) ) -> bool {

                /* store reinterpreted object as caller class */
                auto const pIterable    = reinterpret_cast < __IterableType * > ( this );

                /* parse through elements using Const Iteration */
                for ( auto iterator = pIterable->cbegin(), end = pIterable->cend(); iterator != end; ++ iterator ) {

                    /* if the element is validated by the predicate, call remove primitive and return result */
                    if ( ( ( * iterator ).* predicate ) () ) {
                        return reinterpret_cast < __IterableType * > ( this )->remove ( iterator );
                    }
                }

                /* iteration ended, nothing returned, no element removed */
                return false;
            }


            template <
                    typename __IterableType,        /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ElementType          /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > template <
                    typename __Predicate,           /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    cds :: meta :: EnableIf <
                            ! cds :: meta ::isMemberFunctionPointer <
                                    __Predicate,
                                    cds :: meta :: Decay < __ElementType >
                            > ()
                    >
            > auto __RemoveByCompositeClient <
                    __IterableType,
                    __ElementType
            > :: removeLastThat (
                    __Predicate const & predicate
            ) noexcept ( noexcept ( predicate ( cds :: meta :: referenceOf < ElementType > () ) ) ) -> bool {

                /* using the type of ConstIterator from the Iterable Type, create an iterator to remove at the end of the loop */
                using ConstIterator     = typename __IterableType :: ConstIterator;
                ConstIterator toRemove;

                /* store reinterpreted object as caller class */
                auto const pIterable    = reinterpret_cast < __IterableType * > ( this );

                /* parse through elements using Const Iteration */
                for ( auto iterator = pIterable->cbegin(), end = pIterable->cend(); iterator != end; ++ iterator ) {

                    /* if iterator element is validated, store in local iterator */
                    if ( predicate ( * iterator ) ) {
                        toRemove = iterator;
                    }
                }

                /* if iterator found ( is valid ), call primitive and return result. False otherwise */
                return toRemove.valid() && pIterable->remove ( toRemove );
            }


            template <
                    typename __IterableType,        /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ElementType          /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > template <
                    typename __Predicate,           /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    cds :: meta :: EnableIf <
                            cds :: meta ::isMemberFunctionPointer <
                                    __Predicate,
                                    cds :: meta :: Decay < __ElementType >
                            > ()
                    >
            > auto __RemoveByCompositeClient <
                    __IterableType,
                    __ElementType
            > :: removeLastThat (
                    __Predicate const & predicate
            ) noexcept ( noexcept ( ( cds :: meta :: addressOf < ElementType > () ->* predicate ) () ) ) -> bool {

                /* using the type of ConstIterator from the Iterable Type, create an iterator to remove at the end of the loop */
                using ConstIterator     = typename __IterableType :: ConstIterator;
                ConstIterator toRemove;

                /* store reinterpreted object as caller class */
                auto const pIterable    = reinterpret_cast < __IterableType * > ( this );

                /* parse through elements using Const Iteration */
                for ( auto iterator = pIterable->cbegin(), end = pIterable->cend(); iterator != end; ++ iterator ) {

                    /* if iterator element is validated, store in local iterator */
                    if ( ( ( * iterator ) .* predicate ) () ) {
                        toRemove = iterator;
                    }
                }

                /* if iterator found ( is valid ), call primitive and return result. False otherwise */
                return toRemove.valid() && pIterable->remove ( toRemove );
            }


            template <
                    typename __IterableType,        /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ElementType          /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > template <
                    typename __Predicate,           /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    cds :: meta :: EnableIf <
                            ! cds :: meta ::isMemberFunctionPointer <
                                    __Predicate,
                                    cds :: meta :: Decay < __ElementType >
                            > ()
                    >
            > auto __RemoveByCompositeClient <
                    __IterableType,
                    __ElementType
            > :: removeAllThat (
                    __Predicate const & predicate
            ) noexcept ( noexcept ( predicate ( cds :: meta :: referenceOf < ElementType > () ) ) ) -> Size {

                /* variables used to store number of iterators for matching elements, number of removed elements,
                 * and current object, reinterpreted as caller class */
                Size iteratorCount      = 0ULL;
                Size removedCount       = 0ULL;
                auto const pIterable    = reinterpret_cast < __IterableType * > ( this );

                /* local alias for iterable Const Iterator type */
                using ConstIterator     = typename __IterableType :: ConstIterator;

                /* allocate space to store acquired iterators into */
                auto pIteratorBuffer    = cds :: __hidden :: __impl :: __allocation :: __allocPrimitiveArray < ConstIterator > ( pIterable->size() );

                /* parse through elements using Const Iteration */
                for ( auto iterator = pIterable->cbegin(), end = pIterable->cend (); iterator != end; ++ iterator ) {

                    /* if the element is validated by the predicate, initialize memory of iterator */
                    if ( predicate ( * iterator ) ) {
                        new ( & pIteratorBuffer [ iteratorCount ++ ] ) ConstIterator ( iterator );
                    }
                }

                if ( iteratorCount >= 2ULL ) {
                    /* if more or two elements found, use removeAll */
                    removedCount = pIterable->removeAll (
                            & pIteratorBuffer [0U],
                            iteratorCount
                    );

                } else if ( iteratorCount == 1ULL ) {
                    /* if only one found, use remove */
                    removedCount = pIterable->remove (
                            pIteratorBuffer [0U]
                    ) ? 1ULL : 0ULL;
                }

                /* if none found, do nothing */

                /* destroy stored iterators */
                for ( Size index = 0ULL; index < iteratorCount; ++ index ) {
                    pIteratorBuffer [ index ].~ConstIterator ();
                }

                /* free the iterator memory and return number of removed elements */
                cds :: __hidden :: __impl :: __allocation :: __freePrimitiveArray ( pIteratorBuffer );
                return removedCount;
            }


            template <
                    typename __IterableType,        /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ElementType          /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > template <
                    typename __Predicate,           /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    cds :: meta :: EnableIf <
                            cds :: meta ::isMemberFunctionPointer <
                                    __Predicate,
                                    cds :: meta :: Decay < __ElementType >
                            > ()
                    >
            > auto __RemoveByCompositeClient <
                    __IterableType,
                    __ElementType
            > :: removeAllThat (
                    __Predicate const & predicate
            ) noexcept ( noexcept ( ( cds :: meta :: addressOf < ElementType > () ->* predicate ) () ) ) -> Size {

                /* variables used to store number of iterators for matching elements, number of removed elements,
                 * and current object, reinterpreted as caller class */
                Size iteratorCount      = 0ULL;
                Size removedCount       = 0ULL;
                auto const pIterable    = reinterpret_cast < __IterableType * > ( this );

                /* local alias for iterable Const Iterator type */
                using ConstIterator     = typename __IterableType :: ConstIterator;

                /* allocate space to store acquired iterators into */
                auto pIteratorBuffer    = cds :: __hidden :: __impl :: __allocation :: __allocPrimitiveArray < ConstIterator > ( pIterable->size() );

                /* parse through elements using Const Iteration */
                for ( auto iterator = pIterable->cbegin(), end = pIterable->cend (); iterator != end; ++ iterator ) {

                    /* if the element is validated by the predicate, initialize memory of iterator */
                    if ( ( ( * iterator ) .* predicate ) () ) {
                        new ( & pIteratorBuffer [ iteratorCount ++ ] ) ConstIterator ( iterator );
                    }
                }

                if ( iteratorCount >= 2ULL ) {
                    /* if more or two elements found, use removeAll */
                    removedCount = pIterable->removeAll (
                            & pIteratorBuffer [0U],
                            iteratorCount
                    );

                } else if ( iteratorCount == 1ULL ) {
                    /* if only one found, use remove */
                    removedCount = pIterable->remove (
                            pIteratorBuffer [0U]
                    ) ? 1ULL : 0ULL;
                }

                /* if none found, do nothing */

                /* destroy stored iterators */
                for ( Size index = 0ULL; index < iteratorCount; ++ index ) {
                    pIteratorBuffer [ index ].~ConstIterator ();
                }

                /* free the iterator memory and return number of removed elements */
                cds :: __hidden :: __impl :: __allocation :: __freePrimitiveArray ( pIteratorBuffer );
                return removedCount;
            }

        } /* namespace __impl */
    } /* namespace __hidden */
} /* namespace cds */

#endif /* __CDS_SHARED_REMOVE_BY_COMPOSITE_CLIENT_IMPL_HPP__ */
