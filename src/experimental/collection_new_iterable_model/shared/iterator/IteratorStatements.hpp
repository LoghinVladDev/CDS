//
// Created by loghin on 6/26/22.
//

#ifndef __CDS_SHARED_ITERATOR_STATEMENTS_HPP__
#define __CDS_SHARED_ITERATOR_STATEMENTS_HPP__

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
                ) noexcept ( noexcept ( action ( * begin ) ) ) -> void;

                template <
                        typename __IteratorType,    // NOLINT(bugprone-reserved-identifier)
                        typename __Predicate        // NOLINT(bugprone-reserved-identifier)
                > constexpr auto __some (           // NOLINT(bugprone-reserved-identifier)
                        __IteratorType const & begin,
                        __IteratorType const & end,
                        Size                   count,
                        __Predicate    const & predicate
                ) noexcept ( noexcept ( predicate ( * begin ) ) ) -> bool;

                template <
                        typename __IteratorType,    // NOLINT(bugprone-reserved-identifier)
                        typename __Predicate        // NOLINT(bugprone-reserved-identifier)
                > constexpr auto __atLeast (        // NOLINT(bugprone-reserved-identifier)
                        __IteratorType const & begin,
                        __IteratorType const & end,
                        Size                   count,
                        __Predicate    const & predicate
                ) noexcept ( noexcept ( predicate ( * begin ) ) ) -> bool;

                template <
                        typename __IteratorType,    // NOLINT(bugprone-reserved-identifier)
                        typename __Predicate        // NOLINT(bugprone-reserved-identifier)
                > constexpr auto __atMost (         // NOLINT(bugprone-reserved-identifier)
                        __IteratorType const & begin,
                        __IteratorType const & end,
                        Size                   count,
                        __Predicate    const & predicate
                ) noexcept ( noexcept ( predicate ( * begin ) ) ) -> bool;

                template <
                        typename __IteratorType,    // NOLINT(bugprone-reserved-identifier)
                        typename __Predicate        // NOLINT(bugprone-reserved-identifier)
                > constexpr auto __moreThan (       // NOLINT(bugprone-reserved-identifier)
                        __IteratorType const & begin,
                        __IteratorType const & end,
                        Size                   count,
                        __Predicate    const & predicate
                ) noexcept ( noexcept ( predicate ( * begin ) ) ) -> bool;

                template <
                        typename __IteratorType,    // NOLINT(bugprone-reserved-identifier)
                        typename __Predicate        // NOLINT(bugprone-reserved-identifier)
                > constexpr auto __fewerThan (      // NOLINT(bugprone-reserved-identifier)
                        __IteratorType const & begin,
                        __IteratorType const & end,
                        Size                   count,
                        __Predicate    const & predicate
                ) noexcept ( noexcept ( predicate ( * begin ) ) ) -> bool;

                template <
                        typename __IteratorType,    // NOLINT(bugprone-reserved-identifier)
                        typename __Predicate        // NOLINT(bugprone-reserved-identifier)
                > constexpr auto __count (          // NOLINT(bugprone-reserved-identifier)
                        __IteratorType const & begin,
                        __IteratorType const & end,
                        __Predicate    const & predicate
                ) noexcept ( noexcept ( predicate ( * begin ) ) ) -> Size;

                template <
                        typename __IteratorType,    // NOLINT(bugprone-reserved-identifier)
                        typename __Predicate        // NOLINT(bugprone-reserved-identifier)
                > constexpr auto __any (            // NOLINT(bugprone-reserved-identifier)
                        __IteratorType const & begin,
                        __IteratorType const & end,
                        __Predicate    const & predicate
                ) noexcept ( noexcept ( predicate ( * begin ) ) ) -> bool;

                template <
                        typename __IteratorType,    // NOLINT(bugprone-reserved-identifier)
                        typename __Predicate        // NOLINT(bugprone-reserved-identifier)
                > constexpr auto __all (            // NOLINT(bugprone-reserved-identifier)
                        __IteratorType const & begin,
                        __IteratorType const & end,
                        __Predicate    const & predicate
                ) noexcept ( noexcept ( predicate ( * begin ) ) ) -> bool;

                template <
                        typename __IteratorType,    // NOLINT(bugprone-reserved-identifier)
                        typename __Predicate        // NOLINT(bugprone-reserved-identifier)
                > constexpr auto __none (           // NOLINT(bugprone-reserved-identifier)
                        __IteratorType const & begin,
                        __IteratorType const & end,
                        __Predicate    const & predicate
                ) noexcept ( noexcept ( predicate ( * begin ) ) ) -> bool;

            }
        }
    }
}

#endif // __CDS_SHARED_ITERATOR_STATEMENTS_HPP__
