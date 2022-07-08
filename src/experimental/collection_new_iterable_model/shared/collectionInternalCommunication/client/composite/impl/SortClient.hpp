//
// Created by loghin on 6/30/2022.
//

#ifndef __CDS_SHARED_SORT_CLIENT_IMPL_HPP__
#define __CDS_SHARED_SORT_CLIENT_IMPL_HPP__

namespace cds {                 // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {    // NOLINT(modernize-concat-nested-namespaces)
        namespace __hidden {    // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier)
            namespace __impl {  // NOLINT(bugprone-reserved-identifier)

                template <
                        typename __ElementType,                         // NOLINT(bugprone-reserved-identifier)
                        cds :: meta :: EnableIf <
                                cds :: meta :: isMoveConstructible < __ElementType > () &&
                                cds :: meta :: isMoveAssignable < __ElementType > ()
                        > = 0
                > __CDS_cpplang_ConstexprNonLiteralReturn auto __swap ( // NOLINT(bugprone-reserved-identifier)
                        __ElementType & left,
                        __ElementType & right
                ) noexcept -> void {

                    auto aux    = std :: move ( left );
                    left        = std :: move ( right );
                    right       = std :: move ( aux );
                }


                template <
                        typename __ElementType,                         // NOLINT(bugprone-reserved-identifier)
                        cds :: meta :: EnableIf <
                                ! cds :: meta :: isMoveConstructible < __ElementType > () &&
                                ! cds :: meta :: isMoveAssignable < __ElementType > ()
                        > = 0
                > __CDS_cpplang_ConstexprNonLiteralReturn auto __swap ( // NOLINT(bugprone-reserved-identifier)
                        __ElementType & left,
                        __ElementType & right
                ) noexcept -> void {

                    auto aux    = left;
                    left        = right;
                    right       = aux;
                }


                template <
                        typename __IteratorType,        // NOLINT(bugprone-reserved-identifier)
                        typename __ComparatorFunction   // NOLINT(bugprone-reserved-identifier)
                > auto __quickSortPartition (                    // NOLINT(bugprone-reserved-identifier)
                        __IteratorType          const & begin,
                        Index                           beginIndex,
                        __IteratorType          const & end,
                        Index                           endIndex,
                        __ComparatorFunction    const & function,
                        Index                         * pPartitionIndex
                ) noexcept -> __IteratorType {

                    auto & pivotValue   = * begin;
                    auto   pivotIt      = begin;
                    auto   pivotIndex   = beginIndex;

                    for ( auto iterator = begin; iterator != end; ) {
                        ++ iterator;

                        if ( function ( * iterator, pivotValue ) ) {
                            ++ pivotIt;
                            ++ pivotIndex;
                        }
                    }

                    __swap ( * pivotIt, * begin );

                    auto leftIt     = begin;
                    auto rightIt    = end;
                    auto leftIndex  = beginIndex;
                    auto rightIndex = endIndex;

                    while ( leftIndex < pivotIndex && rightIndex > pivotIndex ) {
                        while ( function ( * leftIt, * pivotIt ) ) {
                            ++ leftIt;
                            ++ leftIndex;
                        }

                        while ( function ( * pivotIt, * rightIt ) ) {
                            -- rightIt;
                            -- rightIndex;
                        }

                        if ( leftIndex < pivotIndex && rightIndex > pivotIndex ) {
                            __swap ( * leftIt, * rightIt );

                            ++ leftIt;
                            ++ leftIndex;

                            -- rightIt;
                            -- rightIndex;
                        }
                    }

                    * pPartitionIndex = pivotIndex;
                    return std :: move ( pivotIt );
                }


                template <
                        typename __IteratorType,        // NOLINT(bugprone-reserved-identifier)
                        typename __ComparatorFunction   // NOLINT(bugprone-reserved-identifier)
                > auto __quickSort (                    // NOLINT(bugprone-reserved-identifier)
                        __IteratorType          const & begin,
                        Index                           beginIndex,
                        __IteratorType          const & end,
                        Index                           endIndex,
                        __ComparatorFunction    const & function
                ) noexcept -> void {

                    if ( beginIndex >= endIndex ) {
                        return;
                    }

                    Index partitionIndex = 0;
                    auto partitionIterator = __quickSortPartition (
                            begin,
                            beginIndex,
                            end,
                            endIndex,
                            function,
                            & partitionIndex
                    );

                    auto beforePartition    = partitionIterator;
                    auto afterPartition     = partitionIterator;

                    -- beforePartition;
                    ++ afterPartition;

                    __quickSort (
                            begin,
                            beginIndex,
                            beforePartition,
                            partitionIndex - 1,
                            function
                    );

                    __quickSort (
                            afterPartition,
                            partitionIndex + 1,
                            end,
                            endIndex,
                            function
                    );
                }


                template <
                        typename __ReceiverType,        // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType          // NOLINT(bugprone-reserved-identifier)
                > template <
                        typename __ComparatorFunction   // NOLINT(bugprone-reserved-identifier)
                > auto __SortClient <
                        __ReceiverType,
                        __ElementType
                > :: sort (
                        __ComparatorFunction const & comparatorFunction
                ) noexcept ( noexcept ( comparatorFunction ( cds :: meta :: valueOf < ElementType > (), cds :: meta :: valueOf < ElementType > () ) ) ) -> void {

                    if ( static_cast < __ReceiverType * > ( this )->size() < 2 ) {
                        return;
                    }

                    return __quickSort (
                            static_cast < __ReceiverType * > ( this )->begin(),
                            0,
                            -- static_cast < __ReceiverType * > ( this )->end(),
                            static_cast < Index > ( static_cast < __ReceiverType * > ( this )->size() - 1ULL ),
                            comparatorFunction
                    );
                }

            }
        }
    }
}

#endif // __CDS_SHARED_SORT_CLIENT_IMPL_HPP__
