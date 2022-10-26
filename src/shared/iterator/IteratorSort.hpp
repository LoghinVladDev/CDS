/*
 * Created by loghin on 18/09/22.
 */

#ifndef __CDS_SHARED_ITERATOR_SORT_HPP__ /* NOLINT(llvm-header-guard) */
#define __CDS_SHARED_ITERATOR_SORT_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

namespace cds {             /* NOLINT(modernize-concat-nested-namespaces) */
    namespace __hidden {    /* NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        namespace __impl {  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            template <
                    typename __IteratorType,                                /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __Comparator                                   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > __CDS_cpplang_ConstexprNonLiteralReturn auto __sortHelper (   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __IteratorType const & /* begin */,
                    __IteratorType const & /* end */,
                    __Comparator   const & /* comparator */
            ) noexcept -> void {

                /* function implementation left as dummy on purpose. clang-10, gcc-9 and gcc-10 detect this as
                 * a used function, when it is only declared for SFINAE purposes. It will still return
                 * a value acquired from an undefined function to avoid usage in compiled code. */
            }


            template <
                    typename __RandomAccessIteratorType,                        /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __Comparator                                       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > __CDS_cpplang_ConstexprNonLiteralReturn auto __partitionHelper (  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __RandomAccessIteratorType  const & /* begin */,
                    __RandomAccessIteratorType  const & /* end */,
                    __Comparator                const & /* comparator */
            ) noexcept -> __RandomAccessIteratorType {

                /* function implementation left as dummy on purpose. clang-10, gcc-9 and gcc-10 detect this as
                 * a used function, when it is only declared for SFINAE purposes. It will still return
                 * a value acquired from an undefined function to avoid usage in compiled code. */
            }


            template <
                    typename __IteratorType,                                                        /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __Comparator                                                           /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > using __SortFunction = decltype ( __sortHelper < __IteratorType, __Comparator > );    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */


            template <
                    typename __RandomAccessIteratorType,                                                                /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __Comparator                                                                               /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > using __PartitionFunction = decltype ( __partitionHelper < __RandomAccessIteratorType, __Comparator > );  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */


            template <
                    typename __BidirectionalIteratorType,   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __Comparator                   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > inline auto __insertionSort (                 /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __BidirectionalIteratorType const & begin,
                    __BidirectionalIteratorType const & end,
                    __Comparator                const & comparator
            ) noexcept -> void;


            template <
                    typename __RandomAccessIteratorType,    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __Comparator                   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > inline auto __heapSort (                      /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __RandomAccessIteratorType  const & begin,
                    __RandomAccessIteratorType  const & end,
                    __Comparator                const & comparator
            ) noexcept -> void;


            template <
                    typename                                                            __RandomAccessIteratorType, /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                            __Comparator,               /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    Size                                                                __threshold,                /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __SortFunction < __RandomAccessIteratorType, __Comparator >         __atThreshold,              /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __SortFunction < __RandomAccessIteratorType, __Comparator >         __atDepth,                  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __PartitionFunction < __RandomAccessIteratorType, __Comparator >    __partition                 /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > inline auto __introSort (                                                                             /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __RandomAccessIteratorType  const & begin,
                    __RandomAccessIteratorType  const & end,
                    __Comparator                const & comparator
            ) noexcept -> void;


            template <
                    typename __RandomAccessIteratorType,    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __Comparator                   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > inline auto __m3Partition (                   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __RandomAccessIteratorType  const & begin,
                    __RandomAccessIteratorType  const & end,
                    __Comparator                const & comparator
            ) noexcept -> __RandomAccessIteratorType;

        } /* namespace __impl */
    } /* namespace __hidden */

    template <
            typename __RandomAccessIteratorType,
            typename __Comparator = cds :: FunctionComparator <
                    cds :: meta :: Decay < decltype ( * cds :: meta :: referenceOf < __RandomAccessIteratorType > () ) >,
                    cds :: predicates :: lessThan < cds :: meta :: Decay < decltype ( * cds :: meta :: referenceOf < __RandomAccessIteratorType > () ) > >
            >
    > __CDS_MaybeUnused inline auto heapSort (
            __RandomAccessIteratorType  const & begin,
            __RandomAccessIteratorType  const & end,
            __Comparator                const & comparator  = __Comparator ()
    ) noexcept -> void;

    template <
            typename __BidirectionalIteratorType,
            typename __Comparator = cds :: FunctionComparator <
                    cds :: meta :: Decay < decltype ( * cds :: meta :: referenceOf < __BidirectionalIteratorType > () ) >,
                    cds :: predicates :: lessThan < cds :: meta :: Decay < decltype ( * cds :: meta :: referenceOf < __BidirectionalIteratorType > () ) > >
            >
    > __CDS_MaybeUnused inline auto insertionSort (
            __BidirectionalIteratorType const & begin,
            __BidirectionalIteratorType const & end,
            __Comparator                const & comparator  = __Comparator ()
    ) noexcept -> void;

    template <
            typename __RandomAccessIteratorType,
            typename __Comparator = cds :: FunctionComparator <
                    cds :: meta :: Decay < decltype ( * cds :: meta :: referenceOf < __RandomAccessIteratorType > () ) >,
                    cds :: predicates :: lessThan < cds :: meta :: Decay < decltype ( * cds :: meta :: referenceOf < __RandomAccessIteratorType > () ) > >
            >
    > inline auto introSort (
            __RandomAccessIteratorType  const & begin,
            __RandomAccessIteratorType  const & end,
            __Comparator                const & comparator  = __Comparator ()
    ) noexcept -> void;

} /* namespace cds */

#endif /* __CDS_SHARED_ITERATOR_SORT_HPP__ */
