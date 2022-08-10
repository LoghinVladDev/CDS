//
// Created by loghin on 6/29/22.
//

#ifndef __CDS_SHARED_ITERATOR_DISTANCE_HPP__
#define __CDS_SHARED_ITERATOR_DISTANCE_HPP__

namespace cds {                 // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {    // NOLINT(modernize-concat-nested-namespaces)
        namespace __hidden {    // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier)
            namespace __impl {  // NOLINT(bugprone-reserved-identifier)

                template < typename __IteratorType, typename = void >       // NOLINT(bugprone-reserved-identifier)
                struct __IteratorDistance {                                 // NOLINT(bugprone-reserved-identifier)

                    static inline auto __compute (                          // NOLINT(bugprone-reserved-identifier)
                            __IteratorType const & begin,
                            __IteratorType const & end
                    ) noexcept -> Size {

                        Size distance = 0ULL;
                        for ( auto iterator = begin; iterator != end; ++ iterator ) {
                            ++ distance;
                        }

                        return distance;
                    }
                };


                template < typename __IteratorType >    // NOLINT(bugprone-reserved-identifier)
                struct __IteratorDistance <             // NOLINT(bugprone-reserved-identifier)
                        __IteratorType,
                        cds :: meta :: Void <
                                decltype ( cds :: meta :: valueOf < __IteratorType > () - cds :: meta :: valueOf < __IteratorType > () )
                        >
                > {

                    static inline auto __compute (                          // NOLINT(bugprone-reserved-identifier)
                            __IteratorType const & begin,
                            __IteratorType const & end
                    ) noexcept -> Size {

                        return end - begin;
                    }
                };

            }
        }
    }
}

#endif // __CDS_SHARED_ITERATOR_DISTANCE_HPP__
