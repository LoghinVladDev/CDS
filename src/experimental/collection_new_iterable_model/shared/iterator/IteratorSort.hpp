/*
 * Created by loghin on 18/09/22.
 */

#ifndef __CDS_EX_SHARED_ITERATOR_SORT_HPP__
#define __CDS_EX_SHARED_ITERATOR_SORT_HPP__ /* NOLINT(bugprone-reserved-identifier) */

#warning No longer an experimental feature. Use the non-experimental header.
#include "../../../../shared/iterator/IteratorSort.hpp"

namespace cds {                 /* NOLINT(modernize-concat-nested-namespaces) */
    namespace experimental {    /* NOLINT(modernize-concat-nested-namespaces) */
        namespace __hidden {    /* NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier) */
            namespace __impl {  /* NOLINT(bugprone-reserved-identifier) */

                template <
                        typename __IteratorType,                                                                                                                                        /* NOLINT(bugprone-reserved-identifier) */
                        typename __Comparator                                                                                                                                           /* NOLINT(bugprone-reserved-identifier) */
                > using __SortFunction      __CDS_DeprecatedHint("No longer an experimental feature.") = cds :: __hidden :: __impl :: __SortFunction < __IteratorType, __Comparator >;  /* NOLINT(bugprone-reserved-identifier) */


                template <
                        typename __RandomAccessIteratorType,                                                                                                                                            /* NOLINT(bugprone-reserved-identifier) */
                        typename __Comparator                                                                                                                                                           /* NOLINT(bugprone-reserved-identifier) */
                > using __PartitionFunction __CDS_DeprecatedHint("No longer an experimental feature.") = cds :: __hidden :: __impl :: __PartitionFunction < __RandomAccessIteratorType, __Comparator >; /* NOLINT(bugprone-reserved-identifier) */


                template <
                        typename __BidirectionalIteratorType,                                               /* NOLINT(bugprone-reserved-identifier) */
                        typename __Comparator                                                               /* NOLINT(bugprone-reserved-identifier) */
                > __CDS_DeprecatedHint("No longer an experimental feature.") inline auto __insertionSort (  /* NOLINT(bugprone-reserved-identifier) */
                        __BidirectionalIteratorType const & begin,
                        __BidirectionalIteratorType const & end,
                        __Comparator                const & comparator
                ) noexcept -> void {

                    cds :: __hidden :: __impl :: __insertionSort < __BidirectionalIteratorType, __Comparator > ( begin, end, comparator );
                }


                template <
                        typename __RandomAccessIteratorType,                                            /* NOLINT(bugprone-reserved-identifier) */
                        typename __Comparator                                                           /* NOLINT(bugprone-reserved-identifier) */
                > __CDS_DeprecatedHint("No longer an experimental feature.") inline auto __heapSort (   /* NOLINT(bugprone-reserved-identifier) */
                        __RandomAccessIteratorType  const & begin,
                        __RandomAccessIteratorType  const & end,
                        __Comparator                const & comparator
                ) noexcept -> void {

                    cds :: __hidden :: __impl :: __heapSort < __RandomAccessIteratorType, __Comparator > ( begin, end, comparator );
                }


                template <
                        typename                                                            __RandomAccessIteratorType, /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                            __Comparator,               /* NOLINT(bugprone-reserved-identifier) */
                        Size                                                                __threshold,                /* NOLINT(bugprone-reserved-identifier) */
                        __SortFunction < __RandomAccessIteratorType, __Comparator >         __atThreshold,              /* NOLINT(bugprone-reserved-identifier) */
                        __SortFunction < __RandomAccessIteratorType, __Comparator >         __atDepth,                  /* NOLINT(bugprone-reserved-identifier) */
                        __PartitionFunction < __RandomAccessIteratorType, __Comparator >    __partition                 /* NOLINT(bugprone-reserved-identifier) */
                > __CDS_DeprecatedHint("No longer an experimental feature.") inline auto __introSort (                  /* NOLINT(bugprone-reserved-identifier) */
                        __RandomAccessIteratorType  const & begin,
                        __RandomAccessIteratorType  const & end,
                        __Comparator                const & comparator
                ) noexcept -> void {

                    cds :: __hidden :: __impl :: __introSort < __RandomAccessIteratorType, __Comparator, __threshold, __atThreshold, __atDepth, __partition > ( begin, end, comparator );
                }


                template <
                        typename __RandomAccessIteratorType,                                                /* NOLINT(bugprone-reserved-identifier) */
                        typename __Comparator                                                               /* NOLINT(bugprone-reserved-identifier) */
                > __CDS_DeprecatedHint("No longer an experimental feature.") inline auto __m3Partition (    /* NOLINT(bugprone-reserved-identifier) */
                        __RandomAccessIteratorType  const & begin,
                        __RandomAccessIteratorType  const & end,
                        __Comparator                const & comparator
                ) noexcept -> __RandomAccessIteratorType {

                    return cds :: __hidden :: __impl :: __m3Partition < __RandomAccessIteratorType, __Comparator > ( begin, end, comparator );
                }

            }
        }

        template <
                typename __RandomAccessIteratorType,
                typename __Comparator = cds :: FunctionComparator <
                        cds :: meta :: Decay < decltype ( * cds :: meta :: referenceOf < __RandomAccessIteratorType > () ) >,
                        cds :: predicates :: lessThan < cds :: meta :: Decay < decltype ( * cds :: meta :: referenceOf < __RandomAccessIteratorType > () ) > >
                >
        > __CDS_DeprecatedHint("No longer an experimental feature.") inline auto heapSort (
                __RandomAccessIteratorType  const & begin,
                __RandomAccessIteratorType  const & end,
                __Comparator                const & comparator  = __Comparator ()
        ) noexcept -> void {

            return cds :: heapSort < __RandomAccessIteratorType, __Comparator > ( begin, end, comparator );
        }


        template <
                typename __BidirectionalIteratorType,
                typename __Comparator = cds :: FunctionComparator <
                        cds :: meta :: Decay < decltype ( * cds :: meta :: referenceOf < __BidirectionalIteratorType > () ) >,
                        cds :: predicates :: lessThan < cds :: meta :: Decay < decltype ( * cds :: meta :: referenceOf < __BidirectionalIteratorType > () ) > >
                >
        > __CDS_DeprecatedHint("No longer an experimental feature.") inline auto insertionSort (
                __BidirectionalIteratorType const & begin,
                __BidirectionalIteratorType const & end,
                __Comparator                const & comparator  = __Comparator ()
        ) noexcept -> void {

            return cds :: insertionSort < __BidirectionalIteratorType, __Comparator > ( begin, end, comparator );
        }


        template <
                typename __RandomAccessIteratorType,
                typename __Comparator = cds :: FunctionComparator <
                        cds :: meta :: Decay < decltype ( * cds :: meta :: referenceOf < __RandomAccessIteratorType > () ) >,
                        cds :: predicates :: lessThan < cds :: meta :: Decay < decltype ( * cds :: meta :: referenceOf < __RandomAccessIteratorType > () ) > >
                >
        > __CDS_DeprecatedHint("No longer an experimental feature.") inline auto introSort (
                __RandomAccessIteratorType  const & begin,
                __RandomAccessIteratorType  const & end,
                __Comparator                const & comparator  = __Comparator ()
        ) noexcept -> void {

            return cds :: introSort < __RandomAccessIteratorType, __Comparator > ( begin, end, comparator );
        }

    }
}

#endif /* __CDS_EX_SHARED_ITERATOR_SORT_HPP__ */
