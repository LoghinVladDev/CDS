//
// Created by loghin on 6/26/22.
//

#ifndef __CDS_SHARED_GENERIC_IMMUTABLE_STATEMENTS_COMPOSITE_CLIENT_IMPL_HPP__
#define __CDS_SHARED_GENERIC_IMMUTABLE_STATEMENTS_COMPOSITE_CLIENT_IMPL_HPP__

namespace cds {                 // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {    // NOLINT(modernize-concat-nested-namespaces)
        namespace __hidden {    // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier)
            namespace __impl {  // NOLINT(bugprone-reserved-identifier)

                template <
                        typename __IterableType,    // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType      // NOLINT(bugprone-reserved-identifier)
                > template <
                        typename __Action           // NOLINT(bugprone-reserved-identifier)
                > __CDS_OptimalInline auto __GenericImmutableStatementsCompositeClient <
                        __IterableType,
                        __ElementType
                > :: forEach (
                        __Action const & action
                ) const noexcept ( noexcept ( __forEach (
                        cds :: meta :: addressOf < __IterableType const > ()->cbegin(),
                        cds :: meta :: addressOf < __IterableType const > ()->cend(),
                        action
                ) ) ) -> void {

                    return __forEach (
                            reinterpret_cast < __IterableType const * > ( this )->cbegin(),
                            reinterpret_cast < __IterableType const * > ( this )->cend(),
                            action
                    );
                }


                template <
                        typename __IterableType,    // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType      // NOLINT(bugprone-reserved-identifier)
                > template <
                        typename __Predicate        // NOLINT(bugprone-reserved-identifier)
                > __CDS_OptimalInline auto __GenericImmutableStatementsCompositeClient <
                        __IterableType,
                        __ElementType
                > :: some (
                        Size                count,
                        __Predicate const & predicate
                ) const noexcept ( noexcept ( __some (
                        cds :: meta :: addressOf < __IterableType const > ()->cbegin(),
                        cds :: meta :: addressOf < __IterableType const > ()->cend(),
                        count,
                        predicate
                ) ) ) -> bool {

                    return __some (
                            reinterpret_cast < __IterableType const * > ( this )->cbegin(),
                            reinterpret_cast < __IterableType const * > ( this )->cend(),
                            count,
                            predicate
                    );
                }


                template <
                        typename __IterableType,    // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType      // NOLINT(bugprone-reserved-identifier)
                > template <
                        typename __Predicate        // NOLINT(bugprone-reserved-identifier)
                > __CDS_OptimalInline auto __GenericImmutableStatementsCompositeClient <
                        __IterableType,
                        __ElementType
                > :: atLeast (
                        Size                count,
                        __Predicate const & predicate
                ) const noexcept ( noexcept ( __atLeast (
                        cds :: meta :: addressOf < __IterableType const > ()->cbegin(),
                        cds :: meta :: addressOf < __IterableType const > ()->cend(),
                        count,
                        predicate
                ) ) ) -> bool {

                    return __atLeast (
                            reinterpret_cast < __IterableType const * > ( this )->cbegin(),
                            reinterpret_cast < __IterableType const * > ( this )->cend(),
                            count,
                            predicate
                    );
                }


                template <
                        typename __IterableType,    // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType      // NOLINT(bugprone-reserved-identifier)
                > template <
                        typename __Predicate        // NOLINT(bugprone-reserved-identifier)
                > __CDS_OptimalInline auto __GenericImmutableStatementsCompositeClient <
                        __IterableType,
                        __ElementType
                > :: atMost (
                        Size                count,
                        __Predicate const & predicate
                ) const noexcept ( noexcept ( __atMost (
                        cds :: meta :: addressOf < __IterableType const > ()->cbegin(),
                        cds :: meta :: addressOf < __IterableType const > ()->cend(),
                        count,
                        predicate
                ) ) ) -> bool {

                    return __atMost (
                            reinterpret_cast < __IterableType const * > ( this )->cbegin(),
                            reinterpret_cast < __IterableType const * > ( this )->cend(),
                            count,
                            predicate
                    );
                }


                template <
                        typename __IterableType,    // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType      // NOLINT(bugprone-reserved-identifier)
                > template <
                        typename __Predicate        // NOLINT(bugprone-reserved-identifier)
                > __CDS_OptimalInline auto __GenericImmutableStatementsCompositeClient <
                        __IterableType,
                        __ElementType
                > :: moreThan (
                        Size                count,
                        __Predicate const & predicate
                ) const noexcept ( noexcept ( __moreThan (
                        cds :: meta :: addressOf < __IterableType const > ()->cbegin(),
                        cds :: meta :: addressOf < __IterableType const > ()->cend(),
                        count,
                        predicate
                ) ) ) -> bool {

                    return __moreThan (
                            reinterpret_cast < __IterableType const * > ( this )->cbegin(),
                            reinterpret_cast < __IterableType const * > ( this )->cend(),
                            count,
                            predicate
                    );
                }


                template <
                        typename __IterableType,    // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType      // NOLINT(bugprone-reserved-identifier)
                > template <
                        typename __Predicate        // NOLINT(bugprone-reserved-identifier)
                > __CDS_OptimalInline auto __GenericImmutableStatementsCompositeClient <
                        __IterableType,
                        __ElementType
                > :: fewerThan (
                        Size                count,
                        __Predicate const & predicate
                ) const noexcept ( noexcept ( __fewerThan (
                        cds :: meta :: addressOf < __IterableType const > ()->cbegin(),
                        cds :: meta :: addressOf < __IterableType const > ()->cend(),
                        count,
                        predicate
                ) ) ) -> bool {

                    return __fewerThan (
                            reinterpret_cast < __IterableType const * > ( this )->cbegin(),
                            reinterpret_cast < __IterableType const * > ( this )->cend(),
                            count,
                            predicate
                    );
                }


                template <
                        typename __IterableType,    // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType      // NOLINT(bugprone-reserved-identifier)
                > template <
                        typename __Predicate        // NOLINT(bugprone-reserved-identifier)
                > __CDS_OptimalInline auto __GenericImmutableStatementsCompositeClient <
                        __IterableType,
                        __ElementType
                > :: count (
                        __Predicate const & predicate
                ) const noexcept ( noexcept ( __count (
                        cds :: meta :: addressOf < __IterableType const > ()->cbegin(),
                        cds :: meta :: addressOf < __IterableType const > ()->cend(),
                        predicate
                ) ) ) -> Size {

                    return __count (
                            reinterpret_cast < __IterableType const * > ( this )->cbegin(),
                            reinterpret_cast < __IterableType const * > ( this )->cend(),
                            predicate
                    );
                }


                template <
                        typename __IterableType,    // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType      // NOLINT(bugprone-reserved-identifier)
                > template <
                        typename __Predicate        // NOLINT(bugprone-reserved-identifier)
                > __CDS_OptimalInline auto __GenericImmutableStatementsCompositeClient <
                        __IterableType,
                        __ElementType
                > :: any (
                        __Predicate const & predicate
                ) const noexcept ( noexcept ( __any (
                        cds :: meta :: addressOf < __IterableType const > ()->cbegin(),
                        cds :: meta :: addressOf < __IterableType const > ()->cend(),
                        predicate
                ) ) ) -> bool {

                    return __any (
                            reinterpret_cast < __IterableType const * > ( this )->cbegin(),
                            reinterpret_cast < __IterableType const * > ( this )->cend(),
                            predicate
                    );
                }


                template <
                        typename __IterableType,    // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType      // NOLINT(bugprone-reserved-identifier)
                > template <
                        typename __Predicate        // NOLINT(bugprone-reserved-identifier)
                > __CDS_OptimalInline auto __GenericImmutableStatementsCompositeClient <
                        __IterableType,
                        __ElementType
                > :: all (
                        __Predicate const & predicate
                ) const noexcept ( noexcept ( __all (
                        cds :: meta :: addressOf < __IterableType const > ()->cbegin(),
                        cds :: meta :: addressOf < __IterableType const > ()->cend(),
                        predicate
                ) ) ) -> bool {

                    return __all (
                            reinterpret_cast < __IterableType const * > ( this )->cbegin(),
                            reinterpret_cast < __IterableType const * > ( this )->cend(),
                            predicate
                    );
                }


                template <
                        typename __IterableType,    // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType      // NOLINT(bugprone-reserved-identifier)
                > template <
                        typename __Predicate        // NOLINT(bugprone-reserved-identifier)
                > __CDS_OptimalInline auto __GenericImmutableStatementsCompositeClient <
                        __IterableType,
                        __ElementType
                > :: none (
                        __Predicate const & predicate
                ) const noexcept ( noexcept ( __none (
                        cds :: meta :: addressOf < __IterableType const > ()->cbegin(),
                        cds :: meta :: addressOf < __IterableType const > ()->cend(),
                        predicate
                ) ) ) -> bool {

                    return __none (
                            reinterpret_cast < __IterableType const * > ( this )->cbegin(),
                            reinterpret_cast < __IterableType const * > ( this )->cend(),
                            predicate
                    );
                }

            }
        }
    }
}

#endif // __CDS_SHARED_GENERIC_IMMUTABLE_STATEMENTS_COMPOSITE_CLIENT_IMPL_HPP__
