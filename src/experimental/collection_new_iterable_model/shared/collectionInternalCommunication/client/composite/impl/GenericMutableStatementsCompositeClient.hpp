//
// Created by loghin on 6/26/22.
//

#ifndef __CDS_SHARED_GENERIC_MUTABLE_STATEMENTS_COMPOSITE_CLIENT_IMPL_HPP__
#define __CDS_SHARED_GENERIC_MUTABLE_STATEMENTS_COMPOSITE_CLIENT_IMPL_HPP__

namespace cds {                 // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {    // NOLINT(modernize-concat-nested-namespaces)
        namespace __hidden {    // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier)
            namespace __impl {  // NOLINT(bugprone-reserved-identifier)

                template <
                        typename __IterableType,    // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType      // NOLINT(bugprone-reserved-identifier)
                > template <
                        typename __Action           // NOLINT(bugprone-reserved-identifier)
                > __CDS_OptimalInline auto __GenericMutableStatementsCompositeClient <
                        __IterableType,
                        __ElementType
                > :: forEach (
                        __Action const & action
                ) noexcept ( noexcept ( action ( cds :: meta :: referenceOf < ElementType > () ) ) ) -> void {

                    return __forEach (
                            static_cast < __IterableType * > ( this )->begin(),
                            static_cast < __IterableType * > ( this )->end(),
                            action
                    );
                }


                template <
                        typename __IterableType,    // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType      // NOLINT(bugprone-reserved-identifier)
                > template <
                        typename __Predicate        // NOLINT(bugprone-reserved-identifier)
                > __CDS_OptimalInline auto __GenericMutableStatementsCompositeClient <
                        __IterableType,
                        __ElementType
                > :: some (
                        Size                count,
                        __Predicate const & predicate
                ) noexcept ( noexcept ( predicate ( cds :: meta :: referenceOf < ElementType > () ) ) ) -> bool {

                    return __some (
                            static_cast < __IterableType * > ( this )->begin(),
                            static_cast < __IterableType * > ( this )->end(),
                            count,
                            predicate
                    );
                }


                template <
                        typename __IterableType,    // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType      // NOLINT(bugprone-reserved-identifier)
                > template <
                        typename __Predicate        // NOLINT(bugprone-reserved-identifier)
                > __CDS_OptimalInline auto __GenericMutableStatementsCompositeClient <
                        __IterableType,
                        __ElementType
                > :: atLeast (
                        Size                count,
                        __Predicate const & predicate
                ) noexcept ( noexcept ( predicate ( cds :: meta :: referenceOf < ElementType > () ) ) ) -> bool {

                    return __atLeast (
                            static_cast < __IterableType * > ( this )->begin(),
                            static_cast < __IterableType * > ( this )->end(),
                            count,
                            predicate
                    );
                }


                template <
                        typename __IterableType,    // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType      // NOLINT(bugprone-reserved-identifier)
                > template <
                        typename __Predicate        // NOLINT(bugprone-reserved-identifier)
                > __CDS_OptimalInline auto __GenericMutableStatementsCompositeClient <
                        __IterableType,
                        __ElementType
                > :: atMost (
                        Size                count,
                        __Predicate const & predicate
                ) noexcept ( noexcept ( predicate ( cds :: meta :: referenceOf < ElementType > () ) ) ) -> bool {

                    return __atMost (
                            static_cast < __IterableType * > ( this )->begin(),
                            static_cast < __IterableType * > ( this )->end(),
                            count,
                            predicate
                    );
                }


                template <
                        typename __IterableType,    // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType      // NOLINT(bugprone-reserved-identifier)
                > template <
                        typename __Predicate        // NOLINT(bugprone-reserved-identifier)
                > __CDS_OptimalInline auto __GenericMutableStatementsCompositeClient <
                        __IterableType,
                        __ElementType
                > :: moreThan (
                        Size                count,
                        __Predicate const & predicate
                ) noexcept ( noexcept ( predicate ( cds :: meta :: referenceOf < ElementType > () ) ) ) -> bool {

                    return __moreThan (
                            static_cast < __IterableType * > ( this )->begin(),
                            static_cast < __IterableType * > ( this )->end(),
                            count,
                            predicate
                    );
                }


                template <
                        typename __IterableType,    // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType      // NOLINT(bugprone-reserved-identifier)
                > template <
                        typename __Predicate        // NOLINT(bugprone-reserved-identifier)
                > __CDS_OptimalInline auto __GenericMutableStatementsCompositeClient <
                        __IterableType,
                        __ElementType
                > :: fewerThan (
                        Size                count,
                        __Predicate const & predicate
                ) noexcept ( noexcept ( predicate ( cds :: meta :: referenceOf < ElementType > () ) ) ) -> bool {

                    return __fewerThan (
                            static_cast < __IterableType * > ( this )->begin(),
                            static_cast < __IterableType * > ( this )->end(),
                            count,
                            predicate
                    );
                }


                template <
                        typename __IterableType,    // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType      // NOLINT(bugprone-reserved-identifier)
                > template <
                        typename __Predicate        // NOLINT(bugprone-reserved-identifier)
                > __CDS_OptimalInline auto __GenericMutableStatementsCompositeClient <
                        __IterableType,
                        __ElementType
                > :: count (
                        __Predicate const & predicate
                ) noexcept ( noexcept ( predicate ( cds :: meta :: referenceOf < ElementType > () ) ) ) -> Size {

                    return __count (
                            static_cast < __IterableType * > ( this )->begin(),
                            static_cast < __IterableType * > ( this )->end(),
                            predicate
                    );
                }


                template <
                        typename __IterableType,    // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType      // NOLINT(bugprone-reserved-identifier)
                > template <
                        typename __Predicate        // NOLINT(bugprone-reserved-identifier)
                > __CDS_OptimalInline auto __GenericMutableStatementsCompositeClient <
                        __IterableType,
                        __ElementType
                > :: any (
                        __Predicate const & predicate
                ) noexcept ( noexcept ( predicate ( cds :: meta :: referenceOf < ElementType > () ) ) ) -> bool {

                    return __any (
                            static_cast < __IterableType * > ( this )->begin(),
                            static_cast < __IterableType * > ( this )->end(),
                            predicate
                    );
                }


                template <
                        typename __IterableType,    // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType      // NOLINT(bugprone-reserved-identifier)
                > template <
                        typename __Predicate        // NOLINT(bugprone-reserved-identifier)
                > __CDS_OptimalInline auto __GenericMutableStatementsCompositeClient <
                        __IterableType,
                        __ElementType
                > :: all (
                        __Predicate const & predicate
                ) noexcept ( noexcept ( predicate ( cds :: meta :: referenceOf < ElementType > () ) ) ) -> bool {

                    return __all (
                            static_cast < __IterableType * > ( this )->begin(),
                            static_cast < __IterableType * > ( this )->end(),
                            predicate
                    );
                }


                template <
                        typename __IterableType,    // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType      // NOLINT(bugprone-reserved-identifier)
                > template <
                        typename __Predicate        // NOLINT(bugprone-reserved-identifier)
                > __CDS_OptimalInline auto __GenericMutableStatementsCompositeClient <
                        __IterableType,
                        __ElementType
                > :: none (
                        __Predicate const & predicate
                ) noexcept ( noexcept ( predicate ( cds :: meta :: referenceOf < ElementType > () ) ) ) -> bool {

                    return __none (
                            static_cast < __IterableType * > ( this )->begin(),
                            static_cast < __IterableType * > ( this )->end(),
                            predicate
                    );
                }

            }
        }
    }
}

#endif // __CDS_SHARED_GENERIC_MUTABLE_STATEMENTS_COMPOSITE_CLIENT_IMPL_HPP__
