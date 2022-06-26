//
// Created by loghin on 6/26/22.
//

#ifndef __CDS_SHARED_ITERABLE_IMMUTABLE_STATEMENTS_IMPL_HPP__
#define __CDS_SHARED_ITERABLE_IMMUTABLE_STATEMENTS_IMPL_HPP__

namespace cds {                 // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {    // NOLINT(modernize-concat-nested-namespaces)
        namespace __hidden {    // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier)
            namespace __impl {  // NOLINT(bugprone-reserved-identifier)

                template <
                        typename __IterableType,    // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType      // NOLINT(bugprone-reserved-identifier)
                > template <
                        typename __Action           // NOLINT(bugprone-reserved-identifier)
                > __CDS_OptimalInline auto __IterableImmutableStatements <
                        __IterableType,
                        __ElementType
                > :: forEach (
                        __Action const & action
                ) const noexcept ( noexcept ( action ( cds :: meta :: referenceOf < ElementType const > () ) ) ) -> void {

                    return __forEach (
                            static_cast < __IterableType const * > ( this )->cbegin(),
                            static_cast < __IterableType const * > ( this )->cend(),
                            action
                    );
                }


                template <
                        typename __IterableType,    // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType      // NOLINT(bugprone-reserved-identifier)
                > template <
                        typename __Predicate        // NOLINT(bugprone-reserved-identifier)
                > __CDS_OptimalInline auto __IterableImmutableStatements <
                        __IterableType,
                        __ElementType
                > :: some (
                        Size                count,
                        __Predicate const & predicate
                ) const noexcept ( noexcept ( predicate ( cds :: meta :: referenceOf < ElementType const > () ) ) ) -> bool {

                    return __some (
                            static_cast < __IterableType const * > ( this )->cbegin(),
                            static_cast < __IterableType const * > ( this )->cend(),
                            count,
                            predicate
                    );
                }


                template <
                        typename __IterableType,    // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType      // NOLINT(bugprone-reserved-identifier)
                > template <
                        typename __Predicate        // NOLINT(bugprone-reserved-identifier)
                > __CDS_OptimalInline auto __IterableImmutableStatements <
                        __IterableType,
                        __ElementType
                > :: atLeast (
                        Size                count,
                        __Predicate const & predicate
                ) const noexcept ( noexcept ( predicate ( cds :: meta :: referenceOf < ElementType const > () ) ) ) -> bool {

                    return __atLeast (
                            static_cast < __IterableType const * > ( this )->cbegin(),
                            static_cast < __IterableType const * > ( this )->cend(),
                            count,
                            predicate
                    );
                }


                template <
                        typename __IterableType,    // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType      // NOLINT(bugprone-reserved-identifier)
                > template <
                        typename __Predicate        // NOLINT(bugprone-reserved-identifier)
                > __CDS_OptimalInline auto __IterableImmutableStatements <
                        __IterableType,
                        __ElementType
                > :: atMost (
                        Size                count,
                        __Predicate const & predicate
                ) const noexcept ( noexcept ( predicate ( cds :: meta :: referenceOf < ElementType const > () ) ) ) -> bool {

                    return __atMost (
                            static_cast < __IterableType const * > ( this )->cbegin(),
                            static_cast < __IterableType const * > ( this )->cend(),
                            count,
                            predicate
                    );
                }


                template <
                        typename __IterableType,    // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType      // NOLINT(bugprone-reserved-identifier)
                > template <
                        typename __Predicate        // NOLINT(bugprone-reserved-identifier)
                > __CDS_OptimalInline auto __IterableImmutableStatements <
                        __IterableType,
                        __ElementType
                > :: moreThan (
                        Size                count,
                        __Predicate const & predicate
                ) const noexcept ( noexcept ( predicate ( cds :: meta :: referenceOf < ElementType const > () ) ) ) -> bool {

                    return __moreThan (
                            static_cast < __IterableType const * > ( this )->cbegin(),
                            static_cast < __IterableType const * > ( this )->cend(),
                            count,
                            predicate
                    );
                }


                template <
                        typename __IterableType,    // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType      // NOLINT(bugprone-reserved-identifier)
                > template <
                        typename __Predicate        // NOLINT(bugprone-reserved-identifier)
                > __CDS_OptimalInline auto __IterableImmutableStatements <
                        __IterableType,
                        __ElementType
                > :: fewerThan (
                        Size                count,
                        __Predicate const & predicate
                ) const noexcept ( noexcept ( predicate ( cds :: meta :: referenceOf < ElementType const > () ) ) ) -> bool {

                    return __fewerThan (
                            static_cast < __IterableType const * > ( this )->cbegin(),
                            static_cast < __IterableType const * > ( this )->cend(),
                            count,
                            predicate
                    );
                }


                template <
                        typename __IterableType,    // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType      // NOLINT(bugprone-reserved-identifier)
                > template <
                        typename __Predicate        // NOLINT(bugprone-reserved-identifier)
                > __CDS_OptimalInline auto __IterableImmutableStatements <
                        __IterableType,
                        __ElementType
                > :: count (
                        __Predicate const & predicate
                ) const noexcept ( noexcept ( predicate ( cds :: meta :: referenceOf < ElementType const > () ) ) ) -> Size {

                    return __count (
                            static_cast < __IterableType const * > ( this )->cbegin(),
                            static_cast < __IterableType const * > ( this )->cend(),
                            predicate
                    );
                }


                template <
                        typename __IterableType,    // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType      // NOLINT(bugprone-reserved-identifier)
                > template <
                        typename __Predicate        // NOLINT(bugprone-reserved-identifier)
                > __CDS_OptimalInline auto __IterableImmutableStatements <
                        __IterableType,
                        __ElementType
                > :: any (
                        __Predicate const & predicate
                ) const noexcept ( noexcept ( predicate ( cds :: meta :: referenceOf < ElementType const > () ) ) ) -> bool {

                    return __any (
                            static_cast < __IterableType const * > ( this )->cbegin(),
                            static_cast < __IterableType const * > ( this )->cend(),
                            predicate
                    );
                }


                template <
                        typename __IterableType,    // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType      // NOLINT(bugprone-reserved-identifier)
                > template <
                        typename __Predicate        // NOLINT(bugprone-reserved-identifier)
                > __CDS_OptimalInline auto __IterableImmutableStatements <
                        __IterableType,
                        __ElementType
                > :: all (
                        __Predicate const & predicate
                ) const noexcept ( noexcept ( predicate ( cds :: meta :: referenceOf < ElementType const > () ) ) ) -> bool {

                    return __all (
                            static_cast < __IterableType const * > ( this )->cbegin(),
                            static_cast < __IterableType const * > ( this )->cend(),
                            predicate
                    );
                }


                template <
                        typename __IterableType,    // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType      // NOLINT(bugprone-reserved-identifier)
                > template <
                        typename __Predicate        // NOLINT(bugprone-reserved-identifier)
                > __CDS_OptimalInline auto __IterableImmutableStatements <
                        __IterableType,
                        __ElementType
                > :: none (
                        __Predicate const & predicate
                ) const noexcept ( noexcept ( predicate ( cds :: meta :: referenceOf < ElementType const > () ) ) ) -> bool {

                    return __none (
                            static_cast < __IterableType const * > ( this )->cbegin(),
                            static_cast < __IterableType const * > ( this )->cend(),
                            predicate
                    );
                }

            }
        }
    }
}

#endif // __CDS_SHARED_ITERABLE_IMMUTABLE_STATEMENTS_IMPL_HPP__
