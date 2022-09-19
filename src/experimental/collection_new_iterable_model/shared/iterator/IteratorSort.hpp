/*
 * Created by loghin on 18/09/22.
 */

#ifndef __CDS_SHARED_ITERATOR_SORT_HPP__
#define __CDS_SHARED_ITERATOR_SORT_HPP__ /* NOLINT(bugprone-reserved-identifier) */

namespace cds {                 /* NOLINT(modernize-concat-nested-namespaces) */
    namespace experimental {    /* NOLINT(modernize-concat-nested-namespaces) */
        namespace __hidden {    /* NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier) */
            namespace __impl {  /* NOLINT(bugprone-reserved-identifier) */

                template <
                        typename __IteratorType,                                /* NOLINT(bugprone-reserved-identifier) */
                        typename __Comparator                                   /* NOLINT(bugprone-reserved-identifier) */
                > __CDS_cpplang_ConstexprNonLiteralReturn auto __sortHelper (   /* NOLINT(bugprone-reserved-identifier) */
                        __IteratorType const &,
                        __IteratorType const &,
                        __Comparator   const &
                ) noexcept -> void {

                    /* function implementation left as dummy on purpose. clang-10, gcc-9 and gcc-10 detect this as
                     * a used function, when it is only declared for SFINAE purposes. It will still return
                     * a value acquired from an undefined function to avoid usage in compiled code. */
                }


                template <
                        typename __IteratorType,                                                        /* NOLINT(bugprone-reserved-identifier) */
                        typename __Comparator                                                           /* NOLINT(bugprone-reserved-identifier) */
                > using __SortFunction = decltype ( __sortHelper < __IteratorType, __Comparator > );    /* NOLINT(bugprone-reserved-identifier) */


                template <
                        typename __IteratorType,    /* NOLINT(bugprone-reserved-identifier) */
                        typename __Comparator       /* NOLINT(bugprone-reserved-identifier) */
                > inline auto __insertionSort (     /* NOLINT(bugprone-reserved-identifier) */
                        __IteratorType  const & begin,
                        __IteratorType  const & end,
                        __Comparator    const & comparator
                ) noexcept -> void;


                template <
                        typename __RandomAccessIteratorType,    /* NOLINT(bugprone-reserved-identifier) */
                        typename __Comparator                   /* NOLINT(bugprone-reserved-identifier) */
                > inline auto __heapSort (                      /* NOLINT(bugprone-reserved-identifier) */
                        __RandomAccessIteratorType  const & begin,
                        __RandomAccessIteratorType  const & end,
                        __Comparator                const & comparator
                ) noexcept -> void;


                template <                                                                          /* NOLINT(bugprone-reserved-identifier) */
                        typename __RandomAccessIteratorType,                                        /* NOLINT(bugprone-reserved-identifier) */
                        typename __Comparator,                                                      /* NOLINT(bugprone-reserved-identifier) */
                        Size     __threshold,                                                       /* NOLINT(bugprone-reserved-identifier) */
                        __SortFunction < __RandomAccessIteratorType, __Comparator > __atThreshold,  /* NOLINT(bugprone-reserved-identifier) */
                        __SortFunction < __RandomAccessIteratorType, __Comparator > __atDepth       /* NOLINT(bugprone-reserved-identifier) */
                > inline auto __introSort (                                                         /* NOLINT(bugprone-reserved-identifier) */
                        __RandomAccessIteratorType  const & begin,
                        __RandomAccessIteratorType  const & end,
                        __Comparator                const & comparator
                ) noexcept -> void;

            }
        }

        template <
                typename __RandomAccessIteratorType,
                typename __Comparator = cds :: FunctionComparator <
                        cds :: meta :: Decay < decltype ( * cds :: meta :: referenceOf < __RandomAccessIteratorType > () ) >,
                        cds :: predicates :: lessThan < cds :: meta :: Decay < decltype ( * cds :: meta :: referenceOf < __RandomAccessIteratorType > () ) > >
                >
        > inline auto heapSort (
                __RandomAccessIteratorType  const & begin,
                __RandomAccessIteratorType  const & end,
                __Comparator                const & comparator  = __Comparator ()
        ) noexcept -> void;

    }
}

#endif /* __CDS_SHARED_ITERATOR_SORT_HPP__ */
