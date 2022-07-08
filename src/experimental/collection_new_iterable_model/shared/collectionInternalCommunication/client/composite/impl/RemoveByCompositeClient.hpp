//
// Created by loghin on 6/26/22.
//

#ifndef __CDS_SHARED_REMOVE_BY_COMPOSITE_CLIENT_IMPL_HPP__
#define __CDS_SHARED_REMOVE_BY_COMPOSITE_CLIENT_IMPL_HPP__

namespace cds {                 // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {    // NOLINT(modernize-concat-nested-namespaces)
        namespace __hidden {    // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier)
            namespace __impl {  // NOLINT(bugprone-reserved-identifier)

                template <
                        typename __IterableType,        // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType          // NOLINT(bugprone-reserved-identifier)
                > template <
                        typename __Predicate            // NOLINT(bugprone-reserved-identifier)
                > auto __RemoveByCompositeClient <
                        __IterableType,
                        __ElementType
                > :: removeIf (
                        Size count,
                        __Predicate const & predicate
                ) noexcept ( noexcept ( predicate ( cds :: meta :: referenceOf < ElementType > () ) ) ) -> Size {

                    using ConstIterator     = typename __IterableType :: ConstIterator;
                    auto pIteratorBuffer    = cds :: __hidden :: __impl :: __allocation :: __allocPrimitiveArray < ConstIterator > ( count );
                    Size iteratorCount      = 0ULL;

                    for (
                            auto
                                iterator    = static_cast < __IterableType * > ( this )->cbegin (),
                                end         = static_cast < __IterableType * > ( this )->cend ();

                            iterator != end && iteratorCount < count;
                            ++ iterator
                    ) {

                        if ( predicate ( * iterator ) ) {
                            new ( & pIteratorBuffer [ iteratorCount ++ ] ) ConstIterator ( iterator );
                        }
                    }

                    auto removedCount = static_cast < __IterableType * > ( this )->removeAll (
                            & pIteratorBuffer [0],
                            iteratorCount
                    );

                    for ( Size index = 0ULL; index < iteratorCount; ++ index ) {
                        pIteratorBuffer [ index ].~ConstIterator ();
                    }

                    cds :: __hidden :: __impl :: __allocation :: __freePrimitiveArray ( pIteratorBuffer );
                    return removedCount;
                }


                template <
                        typename __IterableType,        // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType          // NOLINT(bugprone-reserved-identifier)
                > template <
                        typename __Predicate            // NOLINT(bugprone-reserved-identifier)
                > auto __RemoveByCompositeClient <
                        __IterableType,
                        __ElementType
                > :: removeFirstIf (
                        __Predicate const & predicate
                ) noexcept ( noexcept ( predicate ( cds :: meta :: referenceOf < ElementType > () ) ) ) -> bool {

                    for (
                            auto
                                iterator    = static_cast < __IterableType * > ( this )->cbegin (),
                                end         = static_cast < __IterableType * > ( this )->cend ();

                            iterator != end;
                            ++ iterator
                    ) {

                        if ( predicate ( * iterator ) ) {
                            return static_cast < __IterableType * > ( this )->remove ( iterator );
                        }
                    }

                    return false;
                }


                template <
                        typename __IterableType,        // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType          // NOLINT(bugprone-reserved-identifier)
                > template <
                        typename __Predicate            // NOLINT(bugprone-reserved-identifier)
                > auto __RemoveByCompositeClient <
                        __IterableType,
                        __ElementType
                > :: removeLastIf (
                        __Predicate const & predicate
                ) noexcept ( noexcept ( predicate ( cds :: meta :: referenceOf < ElementType > () ) ) ) -> bool {

                    using ConstIterator     = typename __IterableType :: ConstIterator;
                    ConstIterator toRemove;

                    for (
                            auto
                                iterator    = static_cast < __IterableType * > ( this )->cbegin (),
                                end         = static_cast < __IterableType * > ( this )->cend ();

                            iterator != end;
                            ++ iterator
                    ) {

                        if ( predicate ( * iterator ) ) {
                            toRemove = iterator;
                        }
                    }

                    return toRemove.valid() && static_cast < __IterableType * > ( this )->remove ( toRemove );
                }


                template <
                        typename __IterableType,        // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType          // NOLINT(bugprone-reserved-identifier)
                > template <
                        typename __Predicate            // NOLINT(bugprone-reserved-identifier)
                > auto __RemoveByCompositeClient <
                        __IterableType,
                        __ElementType
                > :: removeAllIf (
                        __Predicate const & predicate
                ) noexcept ( noexcept ( predicate ( cds :: meta :: referenceOf < ElementType > () ) ) ) -> Size {

                    using ConstIterator     = typename __IterableType :: ConstIterator;
                    auto pIteratorBuffer    = cds :: __hidden :: __impl :: __allocation :: __allocPrimitiveArray < ConstIterator > ( static_cast < __IterableType const * > ( this )->size() );
                    Size iteratorCount      = 0ULL;

                    for (
                            auto
                                    iterator    = static_cast < __IterableType * > ( this )->cbegin (),
                                    end         = static_cast < __IterableType * > ( this )->cend ();

                            iterator != end;
                            ++ iterator
                    ) {

                        if ( predicate ( * iterator ) ) {
                            new ( & pIteratorBuffer [ iteratorCount ++ ] ) ConstIterator ( iterator );
                        }
                    }

                    auto removedCount = static_cast < __IterableType * > ( this )->removeAll (
                            & pIteratorBuffer [0],
                            iteratorCount
                    );

                    for ( Size index = 0ULL; index < iteratorCount; ++ index ) {
                        pIteratorBuffer [ index ].~ConstIterator ();
                    }

                    cds :: __hidden :: __impl :: __allocation :: __freePrimitiveArray ( pIteratorBuffer );
                    return removedCount;
                }

            }
        }
    }
}

#endif // __CDS_SHARED_REMOVE_BY_COMPOSITE_CLIENT_IMPL_HPP__
