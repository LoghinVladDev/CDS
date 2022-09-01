/*
 * Created by loghin on 6/29/22.
 */

#ifndef __CDS_SHARED_ITERATOR_DISTANCE_HPP__
#define __CDS_SHARED_ITERATOR_DISTANCE_HPP__ /* NOLINT(bugprone-reserved-identifier) */

namespace cds {                 /* NOLINT(modernize-concat-nested-namespaces) */
    namespace experimental {    /* NOLINT(modernize-concat-nested-namespaces) */
        namespace __hidden {    /* NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier) */
            namespace __impl {  /* NOLINT(bugprone-reserved-identifier) */

                /**
                 * @struct Auxiliary structure used to compute the distance between two iterators, when the iterator type does not allow for distance computation
                 * @tparam __IteratorType is the type of iterator
                 *
                 * @test: Not Applicable.
                 *
                 * @namespace cds :: experimental :: __hidden :: __impl
                 * @internal library-private
                 */
                template < typename __IteratorType, typename = void >       /* NOLINT(bugprone-reserved-identifier) */
                struct __IteratorDistance {                                 /* NOLINT(bugprone-reserved-identifier) */

                    /**
                     * @brief Function used to compute the distance between two iterators
                     * @param [in] begin : __IteratorType cref = Constant Reference to the iterator at the start of the range
                     * @param [in] end : __IteratorType cref = Constant Reference to the iterator at the end of the range
                     * @exceptsafe
                     * @return Size = distance between the iterators
                     *
                     * @public
                     */
                    static inline auto __compute (                          /* NOLINT(bugprone-reserved-identifier) */
                            __IteratorType const & begin,
                            __IteratorType const & end
                    ) noexcept -> Size {

                        /* compute the distance via iteration */
                        Size distance = 0ULL;
                        for ( auto iterator = begin; iterator != end; ++ iterator ) {
                            ++ distance;
                        }

                        /* return the distance */
                        return distance;
                    }
                };


                /**
                 * @struct Auxiliary structure used to compute the distance between two iterators, when the iterator type allows distance computation
                 * @tparam __IteratorType is the type of iterator
                 *
                 * @test: Not Applicable.
                 *
                 * @namespace cds :: experimental :: __hidden :: __impl
                 * @internal library-private
                 */
                template < typename __IteratorType >    /* NOLINT(bugprone-reserved-identifier) */
                struct __IteratorDistance <             /* NOLINT(bugprone-reserved-identifier) */
                        __IteratorType,
                        cds :: meta :: Void <
                                decltype ( cds :: meta :: valueOf < __IteratorType > () - cds :: meta :: valueOf < __IteratorType > () )
                        >
                > {

                    /**
                     * @brief Function used to compute the distance between two iterators
                     * @param [in] begin : __IteratorType cref = Constant Reference to the iterator at the start of the range
                     * @param [in] end : __IteratorType cref = Constant Reference to the iterator at the end of the range
                     * @exceptsafe
                     * @return Size = distance between the iterators
                     *
                     * @public
                     */
                    static inline auto __compute (                          /* NOLINT(bugprone-reserved-identifier) */
                            __IteratorType const & begin,
                            __IteratorType const & end
                    ) noexcept -> Size {

                        /* use 'operator -' to compute the distance */
                        return end - begin;
                    }
                };

            }
        }
    }
}

#endif /* __CDS_SHARED_ITERATOR_DISTANCE_HPP__ */
