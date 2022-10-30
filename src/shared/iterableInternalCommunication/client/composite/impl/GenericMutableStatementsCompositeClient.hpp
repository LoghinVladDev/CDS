/*
 * Created by loghin on 6/26/22.
 */

#ifndef __CDS_SHARED_GENERIC_MUTABLE_STATEMENTS_COMPOSITE_CLIENT_IMPL_HPP__ /* NOLINT(llvm-header-guard) */
#define __CDS_SHARED_GENERIC_MUTABLE_STATEMENTS_COMPOSITE_CLIENT_IMPL_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

namespace cds {             /* NOLINT(modernize-concat-nested-namespaces) */
    namespace __hidden {    /* NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        namespace __impl {  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            template <
                    typename __IterableType,    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ElementType      /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > template <
                    typename __Action           /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > __CDS_OptimalInline auto __GenericMutableStatementsCompositeClient <
                    __IterableType,
                    __ElementType
            > :: forEach (
                    __Action const & action
            ) noexcept ( noexcept ( __forEach (
                    cds :: meta :: addressOf < __IterableType > ()->begin(),
                    cds :: meta :: addressOf < __IterableType > ()->end(),
                    action
            ) ) ) -> void {

                /* Call base, global implementation. Abstracts the 'is object const' requirement */
                return __forEach (
                        reinterpret_cast < __IterableType * > ( this )->begin(),
                        reinterpret_cast < __IterableType * > ( this )->end(),
                        action
                );
            }


            template <
                    typename __IterableType,    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ElementType      /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > template <
                    typename __Predicate        /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > __CDS_OptimalInline auto __GenericMutableStatementsCompositeClient <
                    __IterableType,
                    __ElementType
            > :: some (
                    Size                count,
                    __Predicate const & predicate
            ) noexcept ( noexcept ( __some (
                    cds :: meta :: addressOf < __IterableType > ()->begin(),
                    cds :: meta :: addressOf < __IterableType > ()->end(),
                    count,
                    predicate
            ) ) ) -> bool {

                /* Call base, global implementation. Abstracts the 'is object const' requirement */
                return __some (
                        reinterpret_cast < __IterableType * > ( this )->begin(),
                        reinterpret_cast < __IterableType * > ( this )->end(),
                        count,
                        predicate
                );
            }


            template <
                    typename __IterableType,    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ElementType      /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > template <
                    typename __Predicate        /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > __CDS_OptimalInline auto __GenericMutableStatementsCompositeClient <
                    __IterableType,
                    __ElementType
            > :: atLeast (
                    Size                count,
                    __Predicate const & predicate
            ) noexcept ( noexcept ( __atLeast (
                    cds :: meta :: addressOf < __IterableType > ()->begin(),
                    cds :: meta :: addressOf < __IterableType > ()->end(),
                    count,
                    predicate
            ) ) ) -> bool {

                /* Call base, global implementation. Abstracts the 'is object const' requirement */
                return __atLeast (
                        reinterpret_cast < __IterableType * > ( this )->begin(),
                        reinterpret_cast < __IterableType * > ( this )->end(),
                        count,
                        predicate
                );
            }


            template <
                    typename __IterableType,    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ElementType      /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > template <
                    typename __Predicate        /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > __CDS_OptimalInline auto __GenericMutableStatementsCompositeClient <
                    __IterableType,
                    __ElementType
            > :: atMost (
                    Size                count,
                    __Predicate const & predicate
            ) noexcept ( noexcept ( __atMost (
                    cds :: meta :: addressOf < __IterableType > ()->begin(),
                    cds :: meta :: addressOf < __IterableType > ()->end(),
                    count,
                    predicate
            ) ) ) -> bool {

                /* Call base, global implementation. Abstracts the 'is object const' requirement */
                return __atMost (
                        reinterpret_cast < __IterableType * > ( this )->begin(),
                        reinterpret_cast < __IterableType * > ( this )->end(),
                        count,
                        predicate
                );
            }


            template <
                    typename __IterableType,    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ElementType      /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > template <
                    typename __Predicate        /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > __CDS_OptimalInline auto __GenericMutableStatementsCompositeClient <
                    __IterableType,
                    __ElementType
            > :: moreThan (
                    Size                count,
                    __Predicate const & predicate
            ) noexcept ( noexcept ( __moreThan (
                    cds :: meta :: addressOf < __IterableType > ()->begin(),
                    cds :: meta :: addressOf < __IterableType > ()->end(),
                    count,
                    predicate
            ) ) ) -> bool {

                /* Call base, global implementation. Abstracts the 'is object const' requirement */
                return __moreThan (
                        reinterpret_cast < __IterableType * > ( this )->begin(),
                        reinterpret_cast < __IterableType * > ( this )->end(),
                        count,
                        predicate
                );
            }


            template <
                    typename __IterableType,    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ElementType      /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > template <
                    typename __Predicate        /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > __CDS_OptimalInline auto __GenericMutableStatementsCompositeClient <
                    __IterableType,
                    __ElementType
            > :: fewerThan (
                    Size                count,
                    __Predicate const & predicate
            ) noexcept ( noexcept ( __fewerThan (
                    cds :: meta :: addressOf < __IterableType > ()->begin(),
                    cds :: meta :: addressOf < __IterableType > ()->end(),
                    count,
                    predicate
            ) ) ) -> bool {

                /* Call base, global implementation. Abstracts the 'is object const' requirement */
                return __fewerThan (
                        reinterpret_cast < __IterableType * > ( this )->begin(),
                        reinterpret_cast < __IterableType * > ( this )->end(),
                        count,
                        predicate
                );
            }


            template <
                    typename __IterableType,    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ElementType      /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > template <
                    typename __Predicate        /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > __CDS_OptimalInline auto __GenericMutableStatementsCompositeClient <
                    __IterableType,
                    __ElementType
            > :: count (
                    __Predicate const & predicate
            ) noexcept ( noexcept ( __count (
                    cds :: meta :: addressOf < __IterableType > ()->begin(),
                    cds :: meta :: addressOf < __IterableType > ()->end(),
                    predicate
            ) ) ) -> Size {

                /* Call base, global implementation. Abstracts the 'is object const' requirement */
                return __count (
                        reinterpret_cast < __IterableType * > ( this )->begin(),
                        reinterpret_cast < __IterableType * > ( this )->end(),
                        predicate
                );
            }


            template <
                    typename __IterableType,    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ElementType      /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > template <
                    typename __Predicate        /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > __CDS_OptimalInline auto __GenericMutableStatementsCompositeClient <
                    __IterableType,
                    __ElementType
            > :: any (
                    __Predicate const & predicate
            ) noexcept ( noexcept ( __any (
                    cds :: meta :: addressOf < __IterableType > ()->begin(),
                    cds :: meta :: addressOf < __IterableType > ()->end(),
                    predicate
            ) ) ) -> bool {

                /* Call base, global implementation. Abstracts the 'is object const' requirement */
                return __any (
                        reinterpret_cast < __IterableType * > ( this )->begin(),
                        reinterpret_cast < __IterableType * > ( this )->end(),
                        predicate
                );
            }


            template <
                    typename __IterableType,    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ElementType      /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > template <
                    typename __Predicate        /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > __CDS_OptimalInline auto __GenericMutableStatementsCompositeClient <
                    __IterableType,
                    __ElementType
            > :: all (
                    __Predicate const & predicate
            ) noexcept ( noexcept ( __all (
                    cds :: meta :: addressOf < __IterableType > ()->begin(),
                    cds :: meta :: addressOf < __IterableType > ()->end(),
                    predicate
            ) ) ) -> bool {

                /* Call base, global implementation. Abstracts the 'is object const' requirement */
                return __all (
                        reinterpret_cast < __IterableType * > ( this )->begin(),
                        reinterpret_cast < __IterableType * > ( this )->end(),
                        predicate
                );
            }


            template <
                    typename __IterableType,    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ElementType      /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > template <
                    typename __Predicate        /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > __CDS_OptimalInline auto __GenericMutableStatementsCompositeClient <
                    __IterableType,
                    __ElementType
            > :: none (
                    __Predicate const & predicate
            ) noexcept ( noexcept ( __none (
                    cds :: meta :: addressOf < __IterableType > ()->begin(),
                    cds :: meta :: addressOf < __IterableType > ()->end(),
                    predicate
            ) ) ) -> bool {

                /* Call base, global implementation. Abstracts the 'is object const' requirement */
                return __none (
                        reinterpret_cast < __IterableType * > ( this )->begin(),
                        reinterpret_cast < __IterableType * > ( this )->end(),
                        predicate
                );
            }

        } /* namespace __impl */
    } /* namespace __hidden */
} /* namespace cds */

#endif /* __CDS_SHARED_GENERIC_MUTABLE_STATEMENTS_COMPOSITE_CLIENT_IMPL_HPP__ */
