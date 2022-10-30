/*
 * Created by loghin on 6/26/22.
 */

#ifndef __CDS_SHARED_REMOVE_OF_COMPOSITE_CLIENT_IMPL_HPP__ /* NOLINT(llvm-header-guard) */
#define __CDS_SHARED_REMOVE_OF_COMPOSITE_CLIENT_IMPL_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

namespace cds {             /* NOLINT(modernize-concat-nested-namespaces) */
    namespace __hidden {    /* NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        namespace __impl {  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            template <
                    typename                                                                                __IterableType,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                                __ElementType,      /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                                __FromIterableType, /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: PredicateFunction < __FromIterableType const &, __ElementType const & >   __containsFunction  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > __CDS_OptimalInline auto __RemoveOfCompositeClient <
                    __IterableType,
                    __ElementType,
                    __FromIterableType,
                    __containsFunction
            > :: __iro_selfReferentialCase_removeOf (
                    Size                        count,
                    __FromIterableType  const & from
            ) noexcept -> Size {

                /* ignore given collection, same as this */
                (void) from;

                /* store iterable, reinterpreted this and current size */
                auto const pIterable    = reinterpret_cast < __IterableType * > ( this );
                auto const size         = pIterable->size();

                /* if count greater or equal to number of elements, only clear */
                if ( count >= size ) {
                    pIterable->clear();
                    return size;
                }

                /* if none requested, remove none */
                if ( count == 0ULL ) {
                    return 0ULL;
                }

                /* if one requested, remove first */
                if ( count == 1ULL ) {
                    return pIterable->remove ( pIterable->cbegin() ) ? 1ULL : 0ULL;
                }

                /* otherwise, prepare an array with first 'count' iterators */
                using ConstIterator     = typename __IterableType :: ConstIterator;
                auto pIteratorBuffer    = cds :: __hidden :: __impl :: __allocation :: __allocPrimitiveArray < ConstIterator > ( count );
                Size iteratorCount      = 0ULL;

                for ( auto iterator = pIterable->cbegin(), end = pIterable->cend(); iterator != end && iteratorCount < count; ++ iterator ) {
                    new ( & pIteratorBuffer [ iteratorCount ++ ] ) ConstIterator ( iterator );
                }

                /* remove said elements */
                auto removedCount = reinterpret_cast < __IterableType * > ( this )->removeAll (
                        & pIteratorBuffer [0],
                        iteratorCount
                );

                /* destroy stored iterators */
                for ( Size index = 0ULL; index < iteratorCount; ++ index ) {
                    pIteratorBuffer [ index ].~ConstIterator ();
                }

                /* free iterator space and return removed element count */
                cds :: __hidden :: __impl :: __allocation :: __freePrimitiveArray ( pIteratorBuffer );
                return removedCount;
            }


            template <
                    typename                                                                                __IterableType,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                                __ElementType,      /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                                __FromIterableType, /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: PredicateFunction < __FromIterableType const &, __ElementType const & >   __containsFunction  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > __CDS_OptimalInline auto __RemoveOfCompositeClient <
                    __IterableType,
                    __ElementType,
                    __FromIterableType,
                    __containsFunction
            > :: __iro_selfReferentialCase_removeFirstOf (
                    __FromIterableType  const & from
            ) noexcept -> bool {

                /* ignore given collection, same as this */
                (void) from;
                /* reinterpret iterble */
                auto const pIterable = reinterpret_cast < __IterableType * > ( this );

                /* remove first element of this iterable */
                return pIterable->remove ( pIterable->cbegin() );
            }


            template <
                    typename                                                                                __IterableType,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                                __ElementType,      /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                                __FromIterableType, /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: PredicateFunction < __FromIterableType const &, __ElementType const & >   __containsFunction  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > __CDS_OptimalInline auto __RemoveOfCompositeClient <
                    __IterableType,
                    __ElementType,
                    __FromIterableType,
                    __containsFunction
            > :: __iro_selfReferentialCase_removeLastOf (
                    __FromIterableType  const & from
            ) noexcept -> bool {

                /* ignore given collection, same as this */
                (void) from;
                /* reinterpret iterable */
                auto  const pIterable   = reinterpret_cast < __IterableType * > ( this );
                /* create iterator and store end to seek the last element */
                auto        iterator    = pIterable->cbegin();
                auto        end         = pIterable->end();

                /* iterator created to store last element iterator */
                decltype ( iterator ) toRemove;

                /* seek last element */
                while ( iterator != end ) {
                    /* always store current iterator, as in the end, it will be the final one */
                    toRemove = iterator;
                    ++ iterator;
                }

                /* if iterator found, remove iterator and return removal status */
                return static_cast < bool > ( toRemove ) && reinterpret_cast < __IterableType * > ( this )->remove ( toRemove );
            }


            template <
                    typename                                                                                __IterableType,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                                __ElementType,      /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                                __FromIterableType, /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: PredicateFunction < __FromIterableType const &, __ElementType const & >   __containsFunction  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > __CDS_OptimalInline auto __RemoveOfCompositeClient <
                    __IterableType,
                    __ElementType,
                    __FromIterableType,
                    __containsFunction
            > :: __iro_selfReferentialCase_removeAllOf (
                    __FromIterableType  const & from
            ) noexcept -> Size {

                /* ignore given collection, same as this */
                (void) from;

                /* reinterpret iterable */
                auto const pIterable    = reinterpret_cast < __IterableType * > ( this );
                /* acquire size before clear */
                auto const size         = pIterable->size();
                /* clear iterable */
                pIterable->clear();

                /* return size prior to clearing */
                return size;
            }

            template <
                    typename                                                                                __IterableType,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                                __ElementType,      /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                                __FromIterableType, /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: PredicateFunction < __FromIterableType const &, __ElementType const & >   __containsFunction  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > __CDS_OptimalInline auto __RemoveOfCompositeClient <
                    __IterableType,
                    __ElementType,
                    __FromIterableType,
                    __containsFunction
            > :: __iro_selfReferentialCase_removeNotOf (
                    Size                        count,
                    __FromIterableType  const & from
            ) noexcept -> Size {

                /* ignore given collection, same as this. Ignore count as well */
                (void) count;
                (void) from;

                /* this->removeNotOf (this) will do nothing. */
                return 0ULL;
            }


            template <
                    typename                                                                                __IterableType,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                                __ElementType,      /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                                __FromIterableType, /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: PredicateFunction < __FromIterableType const &, __ElementType const & >   __containsFunction  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > __CDS_OptimalInline auto __RemoveOfCompositeClient <
                    __IterableType,
                    __ElementType,
                    __FromIterableType,
                    __containsFunction
            > :: __iro_selfReferentialCase_removeFirstNotOf (
                    __FromIterableType  const & from
            ) noexcept -> bool {

                /* ignore given collection, same as this */
                (void) from;

                /* this->removeFirstNotOf (this) does nothing */
                return false;
            }


            template <
                    typename                                                                                __IterableType,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                                __ElementType,      /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                                __FromIterableType, /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: PredicateFunction < __FromIterableType const &, __ElementType const & >   __containsFunction  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > __CDS_OptimalInline auto __RemoveOfCompositeClient <
                    __IterableType,
                    __ElementType,
                    __FromIterableType,
                    __containsFunction
            > :: __iro_selfReferentialCase_removeLastNotOf (
                    __FromIterableType  const & from
            ) noexcept -> bool {

                /* ignore given collection, same as this */
                (void) from;

                /* this->removeLastNotOf (this) does nothing */
                return false;
            }


            template <
                    typename                                                                                __IterableType,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                                __ElementType,      /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                                __FromIterableType, /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: PredicateFunction < __FromIterableType const &, __ElementType const & >   __containsFunction  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > __CDS_OptimalInline auto __RemoveOfCompositeClient <
                    __IterableType,
                    __ElementType,
                    __FromIterableType,
                    __containsFunction
            > :: __iro_selfReferentialCase_removeAllNotOf (
                    __FromIterableType  const & from
            ) noexcept -> Size {

                /* ignore given collection, same as this */
                (void) from;

                /* this->removeAllNotOf (this) does nothing */
                return 0ULL;
            }


            template <
                    typename                                                                                __IterableType,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                                __ElementType,      /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                                __FromIterableType, /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: PredicateFunction < __FromIterableType const &, __ElementType const & >   __containsFunction  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > auto __RemoveOfCompositeClient <
                    __IterableType,
                    __ElementType,
                    __FromIterableType,
                    __containsFunction
            > :: removeOf (
                    Size                        count,
                    __FromIterableType  const & from
            ) noexcept -> Size {

                /* treat the possible case when 'from' is actually 'this' */
                if ( reinterpret_cast < void const * > ( this ) == reinterpret_cast < void const * > ( & from ) ) {
                    return this->__iro_selfReferentialCase_removeOf (
                            count,
                            from
                    );
                }

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
                for ( auto iterator = pIterable->cbegin(),  end = pIterable->cend(); iterator != end && iteratorCount < count; ++ iterator ) {

                    /* if the element is found in the given 'from' iterable, initialize memory of iterator */
                    if ( __containsFunction ( from, * iterator ) ) {
                        new ( & pIteratorBuffer [ iteratorCount ++ ] ) ConstIterator ( iterator );
                    }
                }

                if ( iteratorCount >= 2ULL ) {
                    /* if more or two elements found, use removeAll */
                    removedCount = pIterable->removeAll (
                            & pIteratorBuffer [0ULL],
                            iteratorCount
                    );

                } else if ( iteratorCount == 1ULL ) {
                    /* if only one found, use remove */
                    removedCount = pIterable->remove (
                            pIteratorBuffer [0ULL]
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
                    typename                                                                                __IterableType,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                                __ElementType,      /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                                __FromIterableType, /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: PredicateFunction < __FromIterableType const &, __ElementType const & >   __containsFunction  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > auto __RemoveOfCompositeClient <
                    __IterableType,
                    __ElementType,
                    __FromIterableType,
                    __containsFunction
            > :: removeFirstOf (
                    __FromIterableType  const & from
            ) noexcept -> bool {

                /* treat the possible case when 'from' is actually 'this' */
                if ( reinterpret_cast < void const * > ( this ) == reinterpret_cast < void const * > ( & from ) ) {
                    return this->__iro_selfReferentialCase_removeFirstOf ( from );
                }

                /* store reinterpreted object as caller class */
                auto const pIterable = reinterpret_cast < __IterableType * > ( this );

                /* parse through elements using Const Iteration */
                for ( auto iterator = pIterable->cbegin(), end = pIterable->cend(); iterator != end; ++ iterator ) {

                    /* if the element is found in the given 'from' iterable, call remove primitive and return result */
                    if ( __containsFunction ( from, * iterator ) ) {
                        return pIterable->remove ( iterator );
                    }
                }

                /* iteration ended, nothing returned, no element removed */
                return false;
            }


            template <
                    typename                                                                                __IterableType,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                                __ElementType,      /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                                __FromIterableType, /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: PredicateFunction < __FromIterableType const &, __ElementType const & >   __containsFunction  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > auto __RemoveOfCompositeClient <
                    __IterableType,
                    __ElementType,
                    __FromIterableType,
                    __containsFunction
            > :: removeLastOf (
                    __FromIterableType  const & from
            ) noexcept -> bool {

                /* treat the possible case when 'from' is actually 'this' */
                if ( reinterpret_cast < void const * > ( this ) == reinterpret_cast < void const * > ( & from ) ) {
                    return this->__iro_selfReferentialCase_removeLastOf ( from );
                }

                /* store reinterpreted object as caller class */
                auto const pIterable = reinterpret_cast < __IterableType * > ( this );

                /* using the type of ConstIterator from the Iterable Type, create an iterator to remove at the end of the loop */
                using ConstIterator = typename __IterableType :: ConstIterator;
                ConstIterator toRemove;

                /* parse through elements using Const Iteration */
                for ( auto iterator = pIterable->cbegin(), end = pIterable->cend(); iterator != end; ++ iterator ) {

                    /* if the element is found in the given 'from' iterable, store in local iterator */
                    if ( __containsFunction ( from, * iterator ) ) {
                        toRemove = iterator;
                    }
                }

                /* if iterator found ( is valid ), call primitive and return result. False otherwise */
                return static_cast < bool > ( toRemove ) && pIterable->remove ( toRemove );
            }


            template <
                    typename                                                                                __IterableType,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                                __ElementType,      /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                                __FromIterableType, /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: PredicateFunction < __FromIterableType const &, __ElementType const & >   __containsFunction  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > auto __RemoveOfCompositeClient <
                    __IterableType,
                    __ElementType,
                    __FromIterableType,
                    __containsFunction
            > :: removeAllOf (
                    __FromIterableType  const & from
            ) noexcept -> Size {

                /* treat the possible case when 'from' is actually 'this' */
                if ( reinterpret_cast < void const * > ( this ) == reinterpret_cast < void const * > ( & from ) ) {
                    return this->__iro_selfReferentialCase_removeAllOf ( from );
                }

                /* variables used to store number of iterators for matching elements, number of removed elements,
                 * and current object, reinterpreted as caller class */
                auto const pIterable    = reinterpret_cast < __IterableType * > ( this );
                Size iteratorCount      = 0ULL;
                Size removedCount       = 0ULL;

                /* local alias for iterable Const Iterator type */
                using ConstIterator     = typename __IterableType :: ConstIterator;

                /* allocate space to store acquired iterators into */
                auto pIteratorBuffer    = cds :: __hidden :: __impl :: __allocation :: __allocPrimitiveArray < ConstIterator > ( pIterable->size() );

                /* parse through elements using Const Iteration */
                for ( auto iterator = pIterable->cbegin(), end = pIterable->cend(); iterator != end; ++ iterator ) {

                    /* if the element is found in the given 'from' iterable, initialize memory of iterator */
                    if ( __containsFunction ( from, * iterator ) ) {
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
                    typename                                                                                __IterableType,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                                __ElementType,      /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                                __FromIterableType, /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: PredicateFunction < __FromIterableType const &, __ElementType const & >   __containsFunction  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > auto __RemoveOfCompositeClient <
                    __IterableType,
                    __ElementType,
                    __FromIterableType,
                    __containsFunction
            > :: removeNotOf (
                    Size                        count,
                    __FromIterableType  const & from
            ) noexcept -> Size {

                /* treat the possible case when 'from' is actually 'this' */
                if ( reinterpret_cast < void const * > ( this ) == reinterpret_cast < void const * > ( & from ) ) {
                    return this->__iro_selfReferentialCase_removeNotOf (
                            count,
                            from
                    );
                }

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

                    /* if the element is not found in the given 'from' iterable, initialize memory of iterator */
                    if ( ! __containsFunction ( from, * iterator ) ) {
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
                    typename                                                                                __IterableType,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                                __ElementType,      /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                                __FromIterableType, /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: PredicateFunction < __FromIterableType const &, __ElementType const & >   __containsFunction  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > auto __RemoveOfCompositeClient <
                    __IterableType,
                    __ElementType,
                    __FromIterableType,
                    __containsFunction
            > :: removeFirstNotOf (
                    __FromIterableType  const & from
            ) noexcept -> bool {

                /* treat the possible case when 'from' is actually 'this' */
                if ( reinterpret_cast < void const * > ( this ) == reinterpret_cast < void const * > ( & from ) ) {
                    return this->__iro_selfReferentialCase_removeFirstNotOf ( from );
                }

                /* store reinterpreted object as caller class */
                auto const pIterable = reinterpret_cast < __IterableType * > ( this );

                /* parse through elements using Const Iteration */
                for ( auto iterator = pIterable->cbegin(), end = pIterable->cend(); iterator != end; ++ iterator ) {

                    /* if the element is not found in the given 'from' iterable, call remove primitive and return result */
                    if ( ! __containsFunction ( from, * iterator ) ) {
                        return pIterable->remove ( iterator );
                    }
                }

                /* iteration ended, nothing returned, no element removed */
                return false;
            }


            template <
                    typename                                                                                __IterableType,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                                __ElementType,      /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                                __FromIterableType, /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: PredicateFunction < __FromIterableType const &, __ElementType const & >   __containsFunction  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > auto __RemoveOfCompositeClient <
                    __IterableType,
                    __ElementType,
                    __FromIterableType,
                    __containsFunction
            > :: removeLastNotOf (
                    __FromIterableType  const & from
            ) noexcept -> bool {

                /* treat the possible case when 'from' is actually 'this' */
                if ( reinterpret_cast < void const * > ( this ) == reinterpret_cast < void const * > ( & from ) ) {
                    return this->__iro_selfReferentialCase_removeLastNotOf ( from );
                }

                /* store reinterpreted object as caller class */
                auto const pIterable = reinterpret_cast < __IterableType * > ( this );

                /* using the type of ConstIterator from the Iterable Type, create an iterator to remove at the end of the loop */
                using ConstIterator = typename __IterableType :: ConstIterator;
                ConstIterator toRemove;

                /* parse through elements using Const Iteration */
                for ( auto iterator = pIterable->cbegin(), end = pIterable->cend(); iterator != end; ++ iterator ) {

                    /* if the element is not found in the given 'from' iterable, store in local iterator */
                    if ( ! __containsFunction ( from, * iterator ) ) {
                        toRemove = iterator;
                    }
                }

                /* if iterator found ( is valid ), call primitive and return result. False otherwise */
                return static_cast < bool > ( toRemove ) && pIterable->remove ( toRemove );
            }


            template <
                    typename                                                                                __IterableType,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                                __ElementType,      /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                                __FromIterableType, /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: PredicateFunction < __FromIterableType const &, __ElementType const & >   __containsFunction  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > auto __RemoveOfCompositeClient <
                    __IterableType,
                    __ElementType,
                    __FromIterableType,
                    __containsFunction
            > :: removeAllNotOf (
                    __FromIterableType  const & from
            ) noexcept -> Size {

                /* treat the possible case when 'from' is actually 'this' */
                if ( reinterpret_cast < void const * > ( this ) == reinterpret_cast < void const * > ( & from ) ) {
                    return this->__iro_selfReferentialCase_removeAllNotOf ( from );
                }

                /* variables used to store number of iterators for matching elements, number of removed elements,
                 * and current object, reinterpreted as caller class */
                auto const pIterable    = reinterpret_cast < __IterableType * > ( this );
                Size iteratorCount      = 0ULL;
                Size removedCount       = 0ULL;

                /* local alias for iterable Const Iterator type */
                using ConstIterator     = typename __IterableType :: ConstIterator;

                /* allocate space to store acquired iterators into */
                auto pIteratorBuffer    = cds :: __hidden :: __impl :: __allocation :: __allocPrimitiveArray < ConstIterator > ( pIterable->size() );

                /* parse through elements using Const Iteration */
                for ( auto iterator = pIterable->cbegin(), end = pIterable->cend(); iterator != end; ++ iterator ) {

                    /* if the element is not found in the given 'from' iterable, initialize memory of iterator */
                    if ( ! __containsFunction ( from, * iterator ) ) {
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

#endif /* __CDS_SHARED_REMOVE_OF_COMPOSITE_CLIENT_IMPL_HPP__ */
