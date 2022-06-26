//
// Created by loghin on 6/26/22.
//

#ifndef __CDS_SHARED_ITERATOR_STATEMENTS_IMPL_HPP__
#define __CDS_SHARED_ITERATOR_STATEMENTS_IMPL_HPP__

namespace cds {                 // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {    // NOLINT(modernize-concat-nested-namespaces)
        namespace __hidden {    // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier)
            namespace __impl {  // NOLINT(bugprone-reserved-identifier)

                template <
                        typename __IteratorType,    // NOLINT(bugprone-reserved-identifier)
                        typename __Action           // NOLINT(bugprone-reserved-identifier)
                > constexpr auto __forEach (        // NOLINT(bugprone-reserved-identifier)
                        __IteratorType const & begin,
                        __IteratorType const & end,
                        __Action       const & action
                ) noexcept ( noexcept ( action ( * begin ) ) ) -> void {

                    for ( auto iterator = begin; iterator != end; ++ iterator ) {
                        action ( * iterator );
                    }
                }


                template <
                        typename __IteratorType,    // NOLINT(bugprone-reserved-identifier)
                        typename __Predicate        // NOLINT(bugprone-reserved-identifier)
                > constexpr auto __some (           // NOLINT(bugprone-reserved-identifier)
                        __IteratorType const & begin,
                        __IteratorType const & end,
                        Size                   count,
                        __Predicate    const & predicate
                ) noexcept ( noexcept ( predicate ( * begin ) ) ) -> bool {

                    Size trueCount = 0ULL;
                    for ( auto iterator = begin; iterator != end; ++ iterator ) {
                        if ( predicate ( * iterator ) ) {
                            ++ trueCount;
                        }

                        if ( trueCount > count ) {
                            return false;
                        }
                    }

                    return trueCount == count;
                }


                template <
                        typename __IteratorType,    // NOLINT(bugprone-reserved-identifier)
                        typename __Predicate        // NOLINT(bugprone-reserved-identifier)
                > constexpr auto __atLeast (        // NOLINT(bugprone-reserved-identifier)
                        __IteratorType const & begin,
                        __IteratorType const & end,
                        Size                   count,
                        __Predicate    const & predicate
                ) noexcept ( noexcept ( predicate ( * begin ) ) ) -> bool {

                    Size trueCount = 0ULL;
                    for ( auto iterator = begin; iterator != end; ++ iterator ) {
                        if ( predicate ( * iterator ) ) {
                            ++ trueCount;
                        }

                        if ( trueCount >= count ) {
                            return true;
                        }
                    }

                    return false;
                }


                template <
                        typename __IteratorType,    // NOLINT(bugprone-reserved-identifier)
                        typename __Predicate        // NOLINT(bugprone-reserved-identifier)
                > constexpr auto __atMost (         // NOLINT(bugprone-reserved-identifier)
                        __IteratorType const & begin,
                        __IteratorType const & end,
                        Size                   count,
                        __Predicate    const & predicate
                ) noexcept ( noexcept ( predicate ( * begin ) ) ) -> bool {

                    Size trueCount = 0ULL;
                    for ( auto iterator = begin; iterator != end; ++ iterator ) {
                        if ( predicate ( * iterator ) ) {
                            ++ trueCount;
                        }

                        if ( trueCount > count ) {
                            return false;
                        }
                    }

                    return true;
                }


                template <
                        typename __IteratorType,    // NOLINT(bugprone-reserved-identifier)
                        typename __Predicate        // NOLINT(bugprone-reserved-identifier)
                > constexpr auto __moreThan (       // NOLINT(bugprone-reserved-identifier)
                        __IteratorType const & begin,
                        __IteratorType const & end,
                        Size                   count,
                        __Predicate    const & predicate
                ) noexcept ( noexcept ( predicate ( * begin ) ) ) -> bool {

                    return __atLeast ( begin, end, count + 1ULL, predicate );
                }


                template <
                        typename __IteratorType,    // NOLINT(bugprone-reserved-identifier)
                        typename __Predicate        // NOLINT(bugprone-reserved-identifier)
                > constexpr auto __fewerThan (      // NOLINT(bugprone-reserved-identifier)
                        __IteratorType const & begin,
                        __IteratorType const & end,
                        Size                   count,
                        __Predicate    const & predicate
                ) noexcept ( noexcept ( predicate ( * begin ) ) ) -> bool {

                    if ( count == 0ULL ) {
                        return false;
                    }

                    return __atMost ( begin, end, count - 1ULL, predicate );
                }


                template <
                        typename __IteratorType,    // NOLINT(bugprone-reserved-identifier)
                        typename __Predicate        // NOLINT(bugprone-reserved-identifier)
                > constexpr auto __count (          // NOLINT(bugprone-reserved-identifier)
                        __IteratorType const & begin,
                        __IteratorType const & end,
                        __Predicate    const & predicate
                ) noexcept ( noexcept ( predicate ( * begin ) ) ) -> Size {

                    Size trueCount = 0ULL;
                    for ( auto iterator = begin; iterator != end; ++ iterator ) {
                        if ( predicate ( * iterator ) ) {
                            ++ trueCount;
                        }
                    }

                    return trueCount;
                }


                template <
                        typename __IteratorType,    // NOLINT(bugprone-reserved-identifier)
                        typename __Predicate        // NOLINT(bugprone-reserved-identifier)
                > constexpr auto __any (            // NOLINT(bugprone-reserved-identifier)
                        __IteratorType const & begin,
                        __IteratorType const & end,
                        __Predicate    const & predicate
                ) noexcept ( noexcept ( predicate ( * begin ) ) ) -> bool {

                    for ( auto iterator = begin; iterator != end; ++ iterator ) {
                        if ( predicate ( * iterator ) ) {
                            return true;
                        }
                    }

                    return false;
                }


                template <
                        typename __IteratorType,    // NOLINT(bugprone-reserved-identifier)
                        typename __Predicate        // NOLINT(bugprone-reserved-identifier)
                > constexpr auto __all (            // NOLINT(bugprone-reserved-identifier)
                        __IteratorType const & begin,
                        __IteratorType const & end,
                        __Predicate    const & predicate
                ) noexcept ( noexcept ( predicate ( * begin ) ) ) -> bool {

                    for ( auto iterator = begin; iterator != end; ++ iterator ) {
                        if ( ! predicate ( * iterator ) ) {
                            return false;
                        }
                    }

                    return true;
                }


                template <
                        typename __IteratorType,    // NOLINT(bugprone-reserved-identifier)
                        typename __Predicate        // NOLINT(bugprone-reserved-identifier)
                > constexpr auto __none (           // NOLINT(bugprone-reserved-identifier)
                        __IteratorType const & begin,
                        __IteratorType const & end,
                        __Predicate    const & predicate
                ) noexcept ( noexcept ( predicate ( * begin ) ) ) -> bool {

                    for ( auto iterator = begin; iterator != end; ++ iterator ) {
                        if ( predicate ( * iterator ) ) {
                            return false;
                        }
                    }

                    return true;
                }

            }
        }
    }
}

#endif // __CDS_SHARED_ITERATOR_STATEMENTS_IMPL_HPP__
