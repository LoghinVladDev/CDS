/*
 * Created by loghin on 18/09/22.
 */

#ifndef __CDS_SHARED_ITERATOR_SORT_IMPL_HPP__ /* NOLINT(llvm-header-guard) */
#define __CDS_SHARED_ITERATOR_SORT_IMPL_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

namespace cds {             /* NOLINT(modernize-concat-nested-namespaces) */
    namespace __hidden {    /* NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        namespace __impl {  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            namespace __helpers { /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

#if defined (__CDS_compiler_gcc) || defined (__CDS_compiler_clang) || defined(__CDS_compiler_MinGW)

                constexpr auto __lg ( sint32 n ) noexcept -> uint8 {    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    return (uint8) sizeof ( sint32 ) * 8U - 1U - __builtin_clz(n);
                }

                constexpr auto __lg ( uint32 n ) noexcept -> uint8 {    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    return (uint8) sizeof ( uint32 ) * 8U - 1U - __builtin_clz(n);
                }

                constexpr auto __lg ( sint64 n ) noexcept -> uint8 {    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    return (uint8) sizeof ( sint64 ) * 8U - 1U - __builtin_clzll(n);
                }

                constexpr auto __lg ( uint64 n ) noexcept -> uint8 {    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    return (uint8) sizeof ( uint64 ) * 8U - 1U - __builtin_clzll(n);
                }

#else

                inline auto __lg ( sint32 number ) noexcept -> uint8 {   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

                    constexpr static uint32 const bases[]   = { 0x0U, 0x00000002U, 0x0000000CU, 0x000000F0U, 0x0000FF00U, 0xFFFF0000U };
                    constexpr static uint8  const counts[]  = { 0x0U, 0x01U, 0x02U, 0x04U, 0x08U, 0x10U, 0x20U };

                    uint8 result = 0U;                                          /* NOLINT(*-init-variables) */
                    for ( uint32 baseIndex = 5; baseIndex > 0; -- baseIndex ) { /* NOLINT(*-init-variables, *-infinite-loop) */
                        if ( number & bases[baseIndex] ) {
                            number >>= counts [baseIndex];
                            result |=  counts [baseIndex];
                        }
                    }

                    return result;
                }

                inline auto __lg ( uint32 number ) noexcept -> uint8 {   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

                    constexpr static uint32 const bases[]   = { 0x0U, 0x00000002U, 0x0000000CU, 0x000000F0U, 0x0000FF00U, 0xFFFF0000U };
                    constexpr static uint8  const counts[]  = { 0x0U, 0x01U, 0x02U, 0x04U, 0x08U, 0x10U };

                    uint8 result = 0U;                                          /* NOLINT(*-init-variables) */
                    for ( uint32 baseIndex = 5; baseIndex > 0; -- baseIndex ) { /* NOLINT(*-init-variables, *-infinite-loop) */
                        if ( number & bases[baseIndex] ) {
                            number >>= counts [baseIndex];
                            result |=  counts [baseIndex];
                        }
                    }

                    return result;
                }

                inline auto __lg ( sint64 number ) noexcept -> uint8 {   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

                    constexpr static uint64 const bases[]   = { 0x0U, 0x0000000000000002U, 0x000000000000000CU, 0x00000000000000F0U, 0x000000000000FF00U, 0x00000000FFFF0000U, 0xFFFFFFFF00000000 };
                    constexpr static uint8  const counts[]  = { 0x0U, 0x01U, 0x02U, 0x04U, 0x08U, 0x10U, 0x20U };

                    uint8 result = 0x0U;                                        /* NOLINT(*-init-variables) */
                    for ( uint32 baseIndex = 6; baseIndex > 0; -- baseIndex ) { /* NOLINT(*-init-variables, *-infinite-loop) */
                        if ( number & bases[baseIndex] ) {
                            number >>= counts [baseIndex];
                            result |=  counts [baseIndex];
                        }
                    }

                    return result;
                }

                inline auto __lg ( uint64 number ) noexcept -> uint8 {   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

                    constexpr static uint64 const bases[]   = { 0x0U, 0x0000000000000002U, 0x000000000000000CU, 0x00000000000000F0U, 0x000000000000FF00U, 0x00000000FFFF0000U, 0xFFFFFFFF00000000 };
                    constexpr static uint8  const counts[]  = { 0x0U, 0x01U, 0x02U, 0x04U, 0x08U, 0x10U, 0x20U };

                    uint8 result = 0x0U;                                        /* NOLINT(*-init-variables) */
                    for ( uint32 baseIndex = 6; baseIndex > 0; -- baseIndex ) { /* NOLINT(*-init-variables, *-infinite-loop) */
                        if ( number & bases[baseIndex] ) {
                            number >>= counts [baseIndex];
                            result |=  counts [baseIndex];
                        }
                    }

                    return result;
                }

#endif

                template <
                        typename __T,                                   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        cds :: meta :: EnableIf <
                                cds :: meta :: isMoveAssignable < __T > () &&
                                cds :: meta :: isMoveConstructible < __T > ()
                        > = 0
                > __CDS_cpplang_ConstexprNonLiteralReturn auto __swap ( /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        __T & left,
                        __T & right
                ) noexcept -> void {

                    __T auxiliary   = std :: move ( left );
                    left            = std :: move ( right );
                    right           = std :: move ( auxiliary );
                }


                template <
                        typename __T,                                   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        cds :: meta :: EnableIf <
                                ( ! cds :: meta :: isMoveAssignable < __T > () ||
                                ! cds :: meta :: isMoveConstructible < __T > () ) &&
                                cds :: meta :: isCopyAssignable < __T > () &&
                                cds :: meta :: isCopyConstructible < __T > ()
                        > = 0
                > __CDS_cpplang_ConstexprNonLiteralReturn auto __swap ( /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        __T & left,
                        __T & right
                ) noexcept -> void {

                    __T auxiliary   = left;
                    left            = right;
                    right           = auxiliary;
                }


                template <
                        typename __T,                                   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        cds :: meta :: EnableIf <
                                ( ! cds :: meta :: isMoveAssignable < __T > () ||
                                ! cds :: meta :: isMoveConstructible < __T > () ) &&
                                ( ! cds :: meta :: isCopyAssignable < __T > () ||
                                ! cds :: meta :: isCopyConstructible < __T > () )
                        > = 0
                > __CDS_cpplang_ConstexprNonLiteralReturn auto __swap ( /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        __T & left,
                        __T & right
                ) noexcept -> void {

                    cds :: __hidden :: __impl :: __allocation :: __RawContainer < __T > auxiliary;
                    (void) std :: memcpy (
                            reinterpret_cast < void * > ( & auxiliary.data() ),
                            reinterpret_cast < void const * > ( & left ),
                            sizeof ( __T )
                    );

                    (void) std :: memcpy (
                            reinterpret_cast < void * > ( & left ),
                            reinterpret_cast < void const * > ( & right ),
                            sizeof ( __T )
                    );

                    (void) std :: memcpy (
                            reinterpret_cast < void * > ( & right ),
                            reinterpret_cast < void const * > ( & auxiliary.data() ),
                            sizeof ( __T )
                    );
                }

                template <
                        typename __T,                                       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        cds :: meta :: EnableIf <
                                cds :: meta :: isMoveAssignable < __T > ()
                        > = 0
                > __CDS_MaybeUnused __CDS_cpplang_ConstexprNonLiteralReturn auto __assign (   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        __T & left,
                        __T & right
                ) noexcept -> void {

                    left = std :: move ( right );
                }


                template <
                        typename __T,                                           /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        cds :: meta :: EnableIf <
                                ! cds :: meta :: isMoveAssignable < __T > ()
                        > = 0
                > __CDS_MaybeUnused __CDS_cpplang_ConstexprNonLiteralReturn auto __assign (       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        __T & left,
                        __T & right
                ) noexcept -> void {

                    left = right;
                }

            } /* namespace __helpers */

            namespace __heapSortHelpers { /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

                template <
                        typename __RandomAccessIteratorType,    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        typename __Comparator                   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                > inline auto __repairHeap (                    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
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
                        typename __RandomAccessIteratorType,    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        typename __Comparator                   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                > inline auto __heapifyInPlace (                /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        __RandomAccessIteratorType  const & begin,
                        __RandomAccessIteratorType  const & end,
                        __Comparator                const & comparator
                ) noexcept -> void {

                    auto parent = begin + ( ( end - begin - 2 ) / 2 );
                    while ( parent >= begin ) {

                        __repairHeap ( parent, begin, end, comparator );
                        -- parent;
                    }
                }


                template <
                        typename __RandomAccessIteratorType,    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        typename __Comparator                   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                > inline auto __deHeapifyInPlace (              /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        __RandomAccessIteratorType  const & begin,
                        __RandomAccessIteratorType          last,
                        __Comparator                const & comparator
                ) noexcept -> void {

                    while ( last >= begin ) {

                        __helpers :: __swap ( * last, * begin );
                        __repairHeap ( begin, begin, last, comparator );

                        -- last;
                    }
                }

            } /* namespace __heapSortHelpers */

            namespace __introSortHelpers { /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

#if !defined (__CDS_compiler_MinGW)

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
                        __Comparator                const & comparator,
                        Size                                depth
                ) noexcept -> void {

                    auto const length = end - begin;

                    if ( length < __threshold ) {
                        __atThreshold ( begin, end, comparator );
                    } else if ( depth == 0U ) {
                        __atDepth ( begin, end, comparator );
                    } else {

                        auto const pivot = __partition ( begin, end, comparator );

                        __introSort <
                                __RandomAccessIteratorType,
                                __Comparator,
                                __threshold,
                                __atThreshold,
                                __atDepth,
                                __partition
                        > ( begin, pivot, comparator, depth - 1 );

                        __introSort <
                                __RandomAccessIteratorType,
                                __Comparator,
                                __threshold,
                                __atThreshold,
                                __atDepth,
                                __partition
                        > ( pivot + 1, end, comparator, depth - 1 );
                    }
                }

#else

                template <
                        typename                                                            __RandomAccessIteratorType, /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        typename                                                            __Comparator,               /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        Size                                                                __threshold                 /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                > inline auto __introSort (                                                                             /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        __RandomAccessIteratorType  const & begin,
                        __RandomAccessIteratorType  const & end,
                        __Comparator                const & comparator,
                        Size                                depth
                ) noexcept -> void {

                    auto const length = end - begin;

                    if ( length < __threshold ) {
                        __heapSort ( begin, end, comparator );
                    } else if ( depth == 0U ) {
                        __insertionSort ( begin, end, comparator );
                    } else {

                        auto const pivot = __m3Partition ( begin, end, comparator );

                        __introSort <
                                __RandomAccessIteratorType,
                                __Comparator,
                                __threshold
                        > ( begin, pivot, comparator, depth - 1 );

                        __introSort <
                                __RandomAccessIteratorType,
                                __Comparator,
                                __threshold
                        > ( pivot + 1, end, comparator, depth - 1 );
                    }
                }

#endif

            } /* namespace __introSortHelpers */

            template <
                    typename __RandomAccessIteratorType,    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __Comparator                   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > inline auto __heapSort (                      /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __RandomAccessIteratorType  const & begin,
                    __RandomAccessIteratorType  const & end,
                    __Comparator                const & comparator
            ) noexcept -> void {

                __heapSortHelpers :: __heapifyInPlace ( begin, end, comparator );
                __heapSortHelpers :: __deHeapifyInPlace ( begin, end - 1, comparator );
            }


            template <
                    typename __BidirectionalIteratorType,   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __Comparator                   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > inline auto __insertionSort (                 /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __BidirectionalIteratorType const & begin,
                    __BidirectionalIteratorType const & end,
                    __Comparator                const & comparator
            ) noexcept -> void {

                auto start = begin;
                while ( ++ start != end ) {
                    auto previous1 = start;
                    auto previous2 = previous1;
                    -- previous2;

                    while ( previous1 > begin && comparator ( * previous1, * previous2 ) ) {
                        __helpers :: __swap ( * previous1, * previous2 );
                        previous1 = previous2;
                        -- previous2;
                    }
                }
            }

#if ! defined(__CDS_compiler_MinGW)

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
            ) noexcept -> void {

                __introSortHelpers :: __introSort <
                        __RandomAccessIteratorType,
                        __Comparator,
                        __threshold,
                        __atThreshold,
                        __atDepth,
                        __partition
                > (
                        begin,
                        end,
                        comparator,
                        __helpers :: __lg ( (uint64) ( end - begin ) )
                );
            }

#else

            template <
                    typename                                                            __RandomAccessIteratorType, /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                            __Comparator,               /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    Size                                                                __threshold                 /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > inline auto __introSort (                                                                             /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __RandomAccessIteratorType  const & begin,
                    __RandomAccessIteratorType  const & end,
                    __Comparator                const & comparator
            ) noexcept -> void {

                __introSortHelpers :: __introSort <
                        __RandomAccessIteratorType,
                        __Comparator,
                        __threshold
                > (
                        begin,
                        end,
                        comparator,
                        __helpers :: __lg ( (uint64) ( end - begin ) )
                );
            }

#endif


            template <
                    typename                                                            __RandomAccessIteratorType, /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                            __Comparator                /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > inline auto __m3Partition (                                                                           /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __RandomAccessIteratorType  const & begin,
                    __RandomAccessIteratorType  const & end,
                    __Comparator                const & comparator
            ) noexcept -> __RandomAccessIteratorType {

                auto left   = begin;
                auto right  = end - 1;
                auto mid    = begin + ( right - begin ) / 2U;

                if ( comparator ( * mid, * left ) ) {
                    __helpers :: __swap ( * mid, * left );
                }

                if ( comparator ( * right, * left ) ) {
                    __helpers :: __swap ( * right, * left );
                }

                if ( comparator ( * right, * mid ) ) {
                    __helpers :: __swap ( * right, * mid );
                }

                __helpers :: __swap ( * mid, * ( -- right ) );
                auto piv = right;

                for ( ;; ) {
                    while ( left < right && comparator ( * ( ++ left ), * piv ) )   { /* nothing done, updated in condition */ }
                    while ( left < right && comparator ( * piv, * ( -- right ) ) )  { /* nothing done, updated in condition */ }
                    if ( left < right ) { __helpers :: __swap ( * left, * right ); }
                    else { break; }
                }

                __helpers :: __swap ( * piv, * left );
                return left;
            }

        } /* namespace __impl */
    } /* namespace __hidden */


    template <
            typename __RandomAccessIteratorType,    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __Comparator                   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    > __CDS_MaybeUnused inline auto heapSort (                        /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
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


    template <
            typename __BidirectionalIteratorType,   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __Comparator                   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    > __CDS_MaybeUnused inline auto insertionSort (                   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            __BidirectionalIteratorType const & begin,
            __BidirectionalIteratorType const & end,
            __Comparator                const & comparator
    ) noexcept -> void {

        return __hidden :: __impl :: __insertionSort < __BidirectionalIteratorType, __Comparator > (
                begin,
                end,
                comparator
        );
    }


    template <
            typename __RandomAccessIteratorType,    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __Comparator                   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    > __CDS_MaybeUnused inline auto introSort (                       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            __RandomAccessIteratorType  const & begin,
            __RandomAccessIteratorType  const & end,
            __Comparator                const & comparator
    ) noexcept -> void {

#if !defined(__CDS_compiler_MinGW)

        return __hidden :: __impl :: __introSort <
                __RandomAccessIteratorType,
                __Comparator,
                16U, /* NOLINT(*-magic-numbers) */
                & cds :: __hidden :: __impl :: __insertionSort < __RandomAccessIteratorType, __Comparator >,
                & cds :: __hidden :: __impl :: __heapSort < __RandomAccessIteratorType, __Comparator >,
                & cds :: __hidden :: __impl :: __m3Partition < __RandomAccessIteratorType, __Comparator >
        > (
                begin,
                end,
                comparator
        );

#else

        return __hidden :: __impl :: __introSort <
                __RandomAccessIteratorType,
                __Comparator,
                16U /* NOLINT(*-magic-numbers) */
        > (
                begin,
                end,
                comparator
        );

#endif

    }
} /* namespace cds */

#endif /* __CDS_SHARED_ITERATOR_SORT_IMPL_HPP__ */
