/*
 * Created by loghin on 18/09/22.
 */

#ifndef __CDS_SHARED_ITEARTOR_SORT_IMPL_HPP__
#define __CDS_SHARED_ITEARTOR_SORT_IMPL_HPP__ /* NOLINT(bugprone-reserved-identifier) */

namespace cds {                 /* NOLINT(modernize-concat-nested-namespaces) */
    namespace experimental {    /* NOLINT(modernize-concat-nested-namespaces) */
        namespace __hidden {    /* NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier) */
            namespace __impl {  /* NOLINT(bugprone-reserved-identifier) */

                namespace __helpers { /* NOLINT(bugprone-reserved-identifier) */

                    template <
                            typename __T,
                            cds :: meta :: EnableIf <
                                    cds :: meta :: isMoveAssignable < __T > () &&
                                    cds :: meta :: isMoveConstructible < __T > ()
                            > = 0
                    > __CDS_cpplang_ConstexprNonLiteralReturn auto __swap (
                            __T & left,
                            __T & right
                    ) noexcept -> void {

                        __T auxiliary   = std :: move ( left );
                        left            = std :: move ( right );
                        right           = std :: move ( auxiliary );
                    }


                    template <
                            typename __T,
                            cds :: meta :: EnableIf <
                                    ! cds :: meta :: isMoveAssignable < __T > () ||
                                    ! cds :: meta :: isMoveConstructible < __T > ()
                            > = 0
                    > __CDS_cpplang_ConstexprNonLiteralReturn auto __swap (
                            __T & left,
                            __T & right
                    ) noexcept -> void {

                        __T auxiliary   = left;
                        left            = right;
                        right           = auxiliary;
                    }

                }

                namespace __heapSortHelpers { /* NOLINT(bugprone-reserved-identifier) */

                    template <
                            typename __RandomAccessIteratorType,    /* NOLINT(bugprone-reserved-identifier) */
                            typename __Comparator                   /* NOLINT(bugprone-reserved-identifier) */
                    > inline auto __repairHeap (                    /* NOLINT(bugprone-reserved-identifier) */
                            __RandomAccessIteratorType          root,
                            __RandomAccessIteratorType  const & begin,
                            __RandomAccessIteratorType  const & end,
                            __Comparator                const & comparator
                    ) noexcept -> void {

                        auto left = root + ( root - begin ) + 1;
                        while ( left < end ) {

                            auto pSwapWith  = & root;
                            left            = root + ( root - begin ) + 1;
                            auto right      = left + 1;

                            if ( comparator ( * ( * pSwapWith ), * left ) ) {
                                pSwapWith = & left;
                            }

                            if ( right < end && comparator ( * ( * pSwapWith ), * right ) ) {
                                pSwapWith = & right;
                            }

                            if ( pSwapWith == & root ) {
                                break;
                            }

                            __helpers :: __swap ( * root, * ( * pSwapWith ) );
                            root = * pSwapWith;
                            left = root + ( root - begin ) + 1;
                        }
                    }

                    template <
                            typename __RandomAccessIteratorType,    /* NOLINT(bugprone-reserved-identifier) */
                            typename __Comparator                   /* NOLINT(bugprone-reserved-identifier) */
                    > inline auto __heapifyInPlace (                /* NOLINT(bugprone-reserved-identifier) */
                            __RandomAccessIteratorType  const & begin,
                            __RandomAccessIteratorType  const & end,
                            __Comparator                const & comparator
                    ) {

                        auto parent = begin + ( ( end - begin - 2 ) / 2 );
                        while ( parent >= begin ) {

                            __repairHeap ( parent, begin, end, comparator );
                            -- parent;
                        }
                    }


                    template <
                            typename __RandomAccessIteratorType,    /* NOLINT(bugprone-reserved-identifier) */
                            typename __Comparator                   /* NOLINT(bugprone-reserved-identifier) */
                    > inline auto __deHeapifyInPlace (              /* NOLINT(bugprone-reserved-identifier) */
                            __RandomAccessIteratorType  const & begin,
                            __RandomAccessIteratorType          last,
                            __Comparator                const & comparator
                    ) {

                        while ( last >= begin ) {

                            __helpers :: __swap ( * last, * begin );
                            __repairHeap ( begin, begin, last, comparator );

                            -- last;
                        }
                    }

                }

                template <
                        typename __RandomAccessIteratorType,    /* NOLINT(bugprone-reserved-identifier) */
                        typename __Comparator                   /* NOLINT(bugprone-reserved-identifier) */
                > inline auto __heapSort (                      /* NOLINT(bugprone-reserved-identifier) */
                        __RandomAccessIteratorType  const & begin,
                        __RandomAccessIteratorType  const & end,
                        __Comparator                const & comparator
                ) noexcept -> void {

                    __heapSortHelpers :: __heapifyInPlace ( begin, end, comparator );
                    __heapSortHelpers :: __deHeapifyInPlace ( begin, end - 1, comparator );
                }

            }
        }


        template <
                typename __RandomAccessIteratorType,    /* NOLINT(bugprone-reserved-identifier) */
                typename __Comparator                   /* NOLINT(bugprone-reserved-identifier) */
        > inline auto heapSort (                      /* NOLINT(bugprone-reserved-identifier) */
                __RandomAccessIteratorType  const & begin,
                __RandomAccessIteratorType  const & end,
                __Comparator                const & comparator
        ) noexcept -> void {

            return __hidden :: __impl :: __heapSort < __RandomAccessIteratorType, __Comparator > (
                    begin,
                    end,
                    comparator
            );
        }
    }
}

#endif /* __CDS_SHARED_ITEARTOR_SORT_IMPL_HPP__ */
