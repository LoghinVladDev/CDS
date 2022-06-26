//
// Created by loghin on 6/26/22.
//

#ifndef __CDS_SHARED_ITERABLE_REMOVE_OF_IMPL_HPP__
#define __CDS_SHARED_ITERABLE_REMOVE_OF_IMPL_HPP__

namespace cds {                 // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {    // NOLINT(modernize-concat-nested-namespaces)
        namespace __hidden {    // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier)
            namespace __impl {  // NOLINT(bugprone-reserved-identifier)

                template <
                        typename                                                    __IterableType,     // NOLINT(bugprone-reserved-identifier)
                        typename                                                    __ElementType,      // NOLINT(bugprone-reserved-identifier)
                        typename                                                    __FromIterableType, // NOLINT(bugprone-reserved-identifier)
                        __ContainsFunction < __FromIterableType, __ElementType >    __containsFunction  // NOLINT(bugprone-reserved-identifier)
                > template <
                        typename __TIterableType,               // NOLINT(bugprone-reserved-identifier)
                        typename __TFromIterableType,           // NOLINT(bugprone-reserved-identifier)
                        cds :: meta :: EnableIf <
                                cds :: meta :: isSame < __TIterableType, __TFromIterableType > ()
                        >
                > auto __IterableRemoveOf <
                        __IterableType,
                        __ElementType,
                        __FromIterableType,
                        __containsFunction
                > :: __iro_selfReferentialCase_removeOf (
                        Size                        count,
                        __FromIterableType  const & from
                ) noexcept -> Size {

                    auto size = static_cast < __IterableType * > ( this )->size();
                    if ( count >= size ) {
                        static_cast < __IterableType * > ( this )->clear();
                        return size;
                    }

                    auto countCopy = count;

                    while ( countCopy > 0ULL ) {
                        (void) static_cast < __IterableType * > ( this )->remove ( static_cast < __IterableType * > ( this )->cbegin() );
                        -- countCopy;
                    }

                    return count;
                }


                template <
                        typename                                                    __IterableType,     // NOLINT(bugprone-reserved-identifier)
                        typename                                                    __ElementType,      // NOLINT(bugprone-reserved-identifier)
                        typename                                                    __FromIterableType, // NOLINT(bugprone-reserved-identifier)
                        __ContainsFunction < __FromIterableType, __ElementType >    __containsFunction  // NOLINT(bugprone-reserved-identifier)
                > template <
                        typename __TIterableType,               // NOLINT(bugprone-reserved-identifier)
                        typename __TFromIterableType,           // NOLINT(bugprone-reserved-identifier)
                        cds :: meta :: EnableIf <
                                ! cds :: meta :: isSame < __TIterableType, __TFromIterableType > ()
                        >
                > auto __IterableRemoveOf <
                        __IterableType,
                        __ElementType,
                        __FromIterableType,
                        __containsFunction
                > :: __iro_selfReferentialCase_removeOf (
                        Size                        count,
                        __FromIterableType  const & from
                ) noexcept -> Size {

                    return 0ULL;
                }


                template <
                        typename                                                    __IterableType,     // NOLINT(bugprone-reserved-identifier)
                        typename                                                    __ElementType,      // NOLINT(bugprone-reserved-identifier)
                        typename                                                    __FromIterableType, // NOLINT(bugprone-reserved-identifier)
                        __ContainsFunction < __FromIterableType, __ElementType >    __containsFunction  // NOLINT(bugprone-reserved-identifier)
                > template <
                        typename __TIterableType,               // NOLINT(bugprone-reserved-identifier)
                        typename __TFromIterableType,           // NOLINT(bugprone-reserved-identifier)
                        cds :: meta :: EnableIf <
                                cds :: meta :: isSame < __TIterableType, __TFromIterableType > ()
                        >
                > auto __IterableRemoveOf <
                        __IterableType,
                        __ElementType,
                        __FromIterableType,
                        __containsFunction
                > :: __iro_selfReferentialCase_removeFirstOf (
                        __FromIterableType  const & from
                ) noexcept -> bool {

                    return static_cast < __IterableType * > ( this )->remove ( static_cast < __IterableType * > ( this )->cbegin() );
                }


                template <
                        typename                                                    __IterableType,     // NOLINT(bugprone-reserved-identifier)
                        typename                                                    __ElementType,      // NOLINT(bugprone-reserved-identifier)
                        typename                                                    __FromIterableType, // NOLINT(bugprone-reserved-identifier)
                        __ContainsFunction < __FromIterableType, __ElementType >    __containsFunction  // NOLINT(bugprone-reserved-identifier)
                > template <
                        typename __TIterableType,               // NOLINT(bugprone-reserved-identifier)
                        typename __TFromIterableType,           // NOLINT(bugprone-reserved-identifier)
                        cds :: meta :: EnableIf <
                                ! cds :: meta :: isSame < __TIterableType, __TFromIterableType > ()
                        >
                > auto __IterableRemoveOf <
                        __IterableType,
                        __ElementType,
                        __FromIterableType,
                        __containsFunction
                > :: __iro_selfReferentialCase_removeFirstOf (
                        __FromIterableType  const & from
                ) noexcept -> bool {

                    return false;
                }


                template <
                        typename                                                    __IterableType,     // NOLINT(bugprone-reserved-identifier)
                        typename                                                    __ElementType,      // NOLINT(bugprone-reserved-identifier)
                        typename                                                    __FromIterableType, // NOLINT(bugprone-reserved-identifier)
                        __ContainsFunction < __FromIterableType, __ElementType >    __containsFunction  // NOLINT(bugprone-reserved-identifier)
                > template <
                        typename __TIterableType,               // NOLINT(bugprone-reserved-identifier)
                        typename __TFromIterableType,           // NOLINT(bugprone-reserved-identifier)
                        cds :: meta :: EnableIf <
                                cds :: meta :: isSame < __TIterableType, __TFromIterableType > ()
                        >
                > auto __IterableRemoveOf <
                        __IterableType,
                        __ElementType,
                        __FromIterableType,
                        __containsFunction
                > :: __iro_selfReferentialCase_removeLastOf (
                        __FromIterableType  const & from
                ) noexcept -> bool {

                    auto iterator   = static_cast < __IterableType * > ( this )->cbegin();
                    auto end        = static_cast < __IterableType * > ( this )->end();

                    decltype ( iterator ) toRemove;

                    while ( iterator != end ) {
                        toRemove = iterator;
                        ++ iterator;
                    }

                    return toRemove.valid() && static_cast < __IterableType * > ( this )->remove ( toRemove );
                }


                template <
                        typename                                                    __IterableType,     // NOLINT(bugprone-reserved-identifier)
                        typename                                                    __ElementType,      // NOLINT(bugprone-reserved-identifier)
                        typename                                                    __FromIterableType, // NOLINT(bugprone-reserved-identifier)
                        __ContainsFunction < __FromIterableType, __ElementType >    __containsFunction  // NOLINT(bugprone-reserved-identifier)
                > template <
                        typename __TIterableType,               // NOLINT(bugprone-reserved-identifier)
                        typename __TFromIterableType,           // NOLINT(bugprone-reserved-identifier)
                        cds :: meta :: EnableIf <
                                ! cds :: meta :: isSame < __TIterableType, __TFromIterableType > ()
                        >
                > auto __IterableRemoveOf <
                        __IterableType,
                        __ElementType,
                        __FromIterableType,
                        __containsFunction
                > :: __iro_selfReferentialCase_removeLastOf (
                        __FromIterableType  const & from
                ) noexcept -> bool {

                    return false;
                }


                template <
                        typename                                                    __IterableType,     // NOLINT(bugprone-reserved-identifier)
                        typename                                                    __ElementType,      // NOLINT(bugprone-reserved-identifier)
                        typename                                                    __FromIterableType, // NOLINT(bugprone-reserved-identifier)
                        __ContainsFunction < __FromIterableType, __ElementType >    __containsFunction  // NOLINT(bugprone-reserved-identifier)
                > template <
                        typename __TIterableType,               // NOLINT(bugprone-reserved-identifier)
                        typename __TFromIterableType,           // NOLINT(bugprone-reserved-identifier)
                        cds :: meta :: EnableIf <
                                cds :: meta :: isSame < __TIterableType, __TFromIterableType > ()
                        >
                > auto __IterableRemoveOf <
                        __IterableType,
                        __ElementType,
                        __FromIterableType,
                        __containsFunction
                > :: __iro_selfReferentialCase_removeAllOf (
                        __FromIterableType  const & from
                ) noexcept -> Size {

                    auto size = static_cast < __IterableType * > ( this )->size();
                    static_cast < __IterableType * > ( this )->clear();
                    return size;
                }


                template <
                        typename                                                    __IterableType,     // NOLINT(bugprone-reserved-identifier)
                        typename                                                    __ElementType,      // NOLINT(bugprone-reserved-identifier)
                        typename                                                    __FromIterableType, // NOLINT(bugprone-reserved-identifier)
                        __ContainsFunction < __FromIterableType, __ElementType >    __containsFunction  // NOLINT(bugprone-reserved-identifier)
                > template <
                        typename __TIterableType,               // NOLINT(bugprone-reserved-identifier)
                        typename __TFromIterableType,           // NOLINT(bugprone-reserved-identifier)
                        cds :: meta :: EnableIf <
                                ! cds :: meta :: isSame < __TIterableType, __TFromIterableType > ()
                        >
                > auto __IterableRemoveOf <
                        __IterableType,
                        __ElementType,
                        __FromIterableType,
                        __containsFunction
                > :: __iro_selfReferentialCase_removeAllOf (
                        __FromIterableType  const & from
                ) noexcept -> Size {

                    return 0ULL;
                }

                template <
                        typename                                                    __IterableType,     // NOLINT(bugprone-reserved-identifier)
                        typename                                                    __ElementType,      // NOLINT(bugprone-reserved-identifier)
                        typename                                                    __FromIterableType, // NOLINT(bugprone-reserved-identifier)
                        __ContainsFunction < __FromIterableType, __ElementType >    __containsFunction  // NOLINT(bugprone-reserved-identifier)
                > auto __IterableRemoveOf <
                        __IterableType,
                        __ElementType,
                        __FromIterableType,
                        __containsFunction
                > :: __iro_selfReferentialCase_removeNotOf (
                        Size                        count,
                        __FromIterableType  const & from
                ) noexcept -> Size {

                    return 0ULL;
                }


                template <
                        typename                                                    __IterableType,     // NOLINT(bugprone-reserved-identifier)
                        typename                                                    __ElementType,      // NOLINT(bugprone-reserved-identifier)
                        typename                                                    __FromIterableType, // NOLINT(bugprone-reserved-identifier)
                        __ContainsFunction < __FromIterableType, __ElementType >    __containsFunction  // NOLINT(bugprone-reserved-identifier)
                > auto __IterableRemoveOf <
                        __IterableType,
                        __ElementType,
                        __FromIterableType,
                        __containsFunction
                > :: __iro_selfReferentialCase_removeFirstNotOf (
                        __FromIterableType  const & from
                ) noexcept -> bool {

                    return false;
                }


                template <
                        typename                                                    __IterableType,     // NOLINT(bugprone-reserved-identifier)
                        typename                                                    __ElementType,      // NOLINT(bugprone-reserved-identifier)
                        typename                                                    __FromIterableType, // NOLINT(bugprone-reserved-identifier)
                        __ContainsFunction < __FromIterableType, __ElementType >    __containsFunction  // NOLINT(bugprone-reserved-identifier)
                > auto __IterableRemoveOf <
                        __IterableType,
                        __ElementType,
                        __FromIterableType,
                        __containsFunction
                > :: __iro_selfReferentialCase_removeLastNotOf (
                        __FromIterableType  const & from
                ) noexcept -> bool {

                    return false;
                }


                template <
                        typename                                                    __IterableType,     // NOLINT(bugprone-reserved-identifier)
                        typename                                                    __ElementType,      // NOLINT(bugprone-reserved-identifier)
                        typename                                                    __FromIterableType, // NOLINT(bugprone-reserved-identifier)
                        __ContainsFunction < __FromIterableType, __ElementType >    __containsFunction  // NOLINT(bugprone-reserved-identifier)
                > auto __IterableRemoveOf <
                        __IterableType,
                        __ElementType,
                        __FromIterableType,
                        __containsFunction
                > :: __iro_selfReferentialCase_removeAllNotOf (
                        __FromIterableType  const & from
                ) noexcept -> Size {

                    return 0ULL;
                }


                template <
                        typename                                                    __IterableType,     // NOLINT(bugprone-reserved-identifier)
                        typename                                                    __ElementType,      // NOLINT(bugprone-reserved-identifier)
                        typename                                                    __FromIterableType, // NOLINT(bugprone-reserved-identifier)
                        __ContainsFunction < __FromIterableType, __ElementType >    __containsFunction  // NOLINT(bugprone-reserved-identifier)
                > auto __IterableRemoveOf <
                        __IterableType,
                        __ElementType,
                        __FromIterableType,
                        __containsFunction
                > :: removeOf (
                        Size                        count,
                        __FromIterableType  const & from
                ) noexcept -> Size {

                    if ( reinterpret_cast < void const * > ( this ) == reinterpret_cast < void const * > ( & from ) ) {
                        return this->__iro_selfReferentialCase_removeOf (
                                count,
                                from
                        );
                    }

                    using ConstIterator     = typename __IterableType :: ConstIterator;
                    auto pIteratorBuffer    = cds :: __hidden :: __impl :: __allocation :: __allocPrimitiveArray < ConstIterator > ( count );
                    Size iteratorCount      = 0ULL;

                    for (
                            auto
                                iterator = static_cast < __IterableType * > ( this )->cbegin(),
                                end      = static_cast < __IterableType * > ( this )->cend();

                            iterator != end && iteratorCount < count;
                            ++ iterator
                    ) {

                        if ( __containsFunction ( from, * iterator ) ) {
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
                        typename                                                    __IterableType,     // NOLINT(bugprone-reserved-identifier)
                        typename                                                    __ElementType,      // NOLINT(bugprone-reserved-identifier)
                        typename                                                    __FromIterableType, // NOLINT(bugprone-reserved-identifier)
                        __ContainsFunction < __FromIterableType, __ElementType >    __containsFunction  // NOLINT(bugprone-reserved-identifier)
                > auto __IterableRemoveOf <
                        __IterableType,
                        __ElementType,
                        __FromIterableType,
                        __containsFunction
                > :: removeFirstOf (
                        __FromIterableType  const & from
                ) noexcept -> bool {

                    if ( reinterpret_cast < void const * > ( this ) == reinterpret_cast < void const * > ( & from ) ) {
                        return this->__iro_selfReferentialCase_removeFirstOf ( from );
                    }

                    for (
                            auto
                                iterator = static_cast < __IterableType * > ( this )->cbegin(),
                                end      = static_cast < __IterableType * > ( this )->cend();

                            iterator != end;
                            ++ iterator
                    ) {

                        if ( __containsFunction ( from, * iterator ) ) {
                            return static_cast < __IterableType * > ( this )->remove ( iterator );
                        }
                    }

                    return false;
                }


                template <
                        typename                                                    __IterableType,     // NOLINT(bugprone-reserved-identifier)
                        typename                                                    __ElementType,      // NOLINT(bugprone-reserved-identifier)
                        typename                                                    __FromIterableType, // NOLINT(bugprone-reserved-identifier)
                        __ContainsFunction < __FromIterableType, __ElementType >    __containsFunction  // NOLINT(bugprone-reserved-identifier)
                > auto __IterableRemoveOf <
                        __IterableType,
                        __ElementType,
                        __FromIterableType,
                        __containsFunction
                > :: removeLastOf (
                        __FromIterableType  const & from
                ) noexcept -> bool {

                    if ( reinterpret_cast < void const * > ( this ) == reinterpret_cast < void const * > ( & from ) ) {
                        return this->__iro_selfReferentialCase_removeLastOf ( from );
                    }

                    using ConstIterator = typename __IterableType :: ConstIterator;
                    ConstIterator toRemove;

                    for (
                            auto
                                iterator = static_cast < __IterableType * > ( this )->cbegin(),
                                end      = static_cast < __IterableType * > ( this )->cend();

                            iterator != end;
                            ++ iterator
                    ) {

                        if ( __containsFunction ( from, * iterator ) ) {
                            toRemove = iterator;
                        }
                    }

                    return toRemove.valid() && static_cast < __IterableType * > ( this )->remove ( toRemove );
                }


                template <
                        typename                                                    __IterableType,     // NOLINT(bugprone-reserved-identifier)
                        typename                                                    __ElementType,      // NOLINT(bugprone-reserved-identifier)
                        typename                                                    __FromIterableType, // NOLINT(bugprone-reserved-identifier)
                        __ContainsFunction < __FromIterableType, __ElementType >    __containsFunction  // NOLINT(bugprone-reserved-identifier)
                > auto __IterableRemoveOf <
                        __IterableType,
                        __ElementType,
                        __FromIterableType,
                        __containsFunction
                > :: removeAllOf (
                        __FromIterableType  const & from
                ) noexcept -> Size {

                    if ( reinterpret_cast < void const * > ( this ) == reinterpret_cast < void const * > ( & from ) ) {
                        return this->__iro_selfReferentialCase_removeAllOf ( from );
                    }

                    using ConstIterator     = typename __IterableType :: ConstIterator;
                    auto pIteratorBuffer    = cds :: __hidden :: __impl :: __allocation :: __allocPrimitiveArray < ConstIterator > ( static_cast < __IterableType * > ( this )->size() );
                    Size iteratorCount      = 0ULL;

                    for (
                            auto
                                iterator = static_cast < __IterableType * > ( this )->cbegin(),
                                end      = static_cast < __IterableType * > ( this )->cend();

                            iterator != end;
                            ++ iterator
                    ) {

                        if ( __containsFunction ( from, * iterator ) ) {
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
                        typename                                                    __IterableType,     // NOLINT(bugprone-reserved-identifier)
                        typename                                                    __ElementType,      // NOLINT(bugprone-reserved-identifier)
                        typename                                                    __FromIterableType, // NOLINT(bugprone-reserved-identifier)
                        __ContainsFunction < __FromIterableType, __ElementType >    __containsFunction  // NOLINT(bugprone-reserved-identifier)
                > auto __IterableRemoveOf <
                        __IterableType,
                        __ElementType,
                        __FromIterableType,
                        __containsFunction
                > :: removeNotOf (
                        Size                        count,
                        __FromIterableType  const & from
                ) noexcept -> Size {

                    if ( reinterpret_cast < void const * > ( this ) == reinterpret_cast < void const * > ( & from ) ) {
                        return this->__iro_selfReferentialCase_removeNotOf (
                                count,
                                from
                        );
                    }

                    using ConstIterator     = typename __IterableType :: ConstIterator;
                    auto pIteratorBuffer    = cds :: __hidden :: __impl :: __allocation :: __allocPrimitiveArray < ConstIterator > ( count );
                    Size iteratorCount      = 0ULL;

                    for (
                            auto
                                iterator = static_cast < __IterableType * > ( this )->cbegin(),
                                end      = static_cast < __IterableType * > ( this )->cend();

                            iterator != end && iteratorCount < count;
                            ++ iterator
                    ) {

                        if ( ! __containsFunction ( from, * iterator ) ) {
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
                        typename                                                    __IterableType,     // NOLINT(bugprone-reserved-identifier)
                        typename                                                    __ElementType,      // NOLINT(bugprone-reserved-identifier)
                        typename                                                    __FromIterableType, // NOLINT(bugprone-reserved-identifier)
                        __ContainsFunction < __FromIterableType, __ElementType >    __containsFunction  // NOLINT(bugprone-reserved-identifier)
                > auto __IterableRemoveOf <
                        __IterableType,
                        __ElementType,
                        __FromIterableType,
                        __containsFunction
                > :: removeFirstNotOf (
                        __FromIterableType  const & from
                ) noexcept -> bool {

                    if ( reinterpret_cast < void const * > ( this ) == reinterpret_cast < void const * > ( & from ) ) {
                        return this->__iro_selfReferentialCase_removeFirstNotOf ( from );
                    }

                    for (
                            auto
                                    iterator = static_cast < __IterableType * > ( this )->cbegin(),
                                    end      = static_cast < __IterableType * > ( this )->cend();

                            iterator != end;
                            ++ iterator
                            ) {

                        if ( ! __containsFunction ( from, * iterator ) ) {
                            return static_cast < __IterableType * > ( this )->remove ( iterator );
                        }
                    }

                    return false;
                }


                template <
                        typename                                                    __IterableType,     // NOLINT(bugprone-reserved-identifier)
                        typename                                                    __ElementType,      // NOLINT(bugprone-reserved-identifier)
                        typename                                                    __FromIterableType, // NOLINT(bugprone-reserved-identifier)
                        __ContainsFunction < __FromIterableType, __ElementType >    __containsFunction  // NOLINT(bugprone-reserved-identifier)
                > auto __IterableRemoveOf <
                        __IterableType,
                        __ElementType,
                        __FromIterableType,
                        __containsFunction
                > :: removeLastNotOf (
                        __FromIterableType  const & from
                ) noexcept -> bool {

                    if ( reinterpret_cast < void const * > ( this ) == reinterpret_cast < void const * > ( & from ) ) {
                        return this->__iro_selfReferentialCase_removeLastNotOf ( from );
                    }

                    using ConstIterator = typename __IterableType :: ConstIterator;
                    ConstIterator toRemove;

                    for (
                            auto
                                    iterator = static_cast < __IterableType * > ( this )->cbegin(),
                                    end      = static_cast < __IterableType * > ( this )->cend();

                            iterator != end;
                            ++ iterator
                            ) {

                        if ( ! __containsFunction ( from, * iterator ) ) {
                            toRemove = iterator;
                        }
                    }

                    return toRemove.valid() && static_cast < __IterableType * > ( this )->remove ( toRemove );
                }


                template <
                        typename                                                    __IterableType,     // NOLINT(bugprone-reserved-identifier)
                        typename                                                    __ElementType,      // NOLINT(bugprone-reserved-identifier)
                        typename                                                    __FromIterableType, // NOLINT(bugprone-reserved-identifier)
                        __ContainsFunction < __FromIterableType, __ElementType >    __containsFunction  // NOLINT(bugprone-reserved-identifier)
                > auto __IterableRemoveOf <
                        __IterableType,
                        __ElementType,
                        __FromIterableType,
                        __containsFunction
                > :: removeAllNotOf (
                        __FromIterableType  const & from
                ) noexcept -> Size {

                    if ( reinterpret_cast < void const * > ( this ) == reinterpret_cast < void const * > ( & from ) ) {
                        return this->__iro_selfReferentialCase_removeAllNotOf ( from );
                    }

                    using ConstIterator     = typename __IterableType :: ConstIterator;
                    auto pIteratorBuffer    = cds :: __hidden :: __impl :: __allocation :: __allocPrimitiveArray < ConstIterator > ( static_cast < __IterableType * > ( this )->size() );
                    Size iteratorCount      = 0ULL;

                    for (
                            auto
                                iterator = static_cast < __IterableType * > ( this )->cbegin(),
                                end      = static_cast < __IterableType * > ( this )->cend();

                            iterator != end;
                            ++ iterator
                    ) {

                        if ( ! __containsFunction ( from, * iterator ) ) {
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

#endif // __CDS_SHARED_ITERABLE_REMOVE_OF_IMPL_HPP__
