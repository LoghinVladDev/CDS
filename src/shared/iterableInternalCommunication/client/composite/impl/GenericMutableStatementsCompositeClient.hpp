/*
 * Created by loghin on 6/26/22.
 */

#ifndef __CDS_SHARED_GENERIC_MUTABLE_STATEMENTS_COMPOSITE_CLIENT_IMPL_HPP__ /* NOLINT(llvm-header-guard) */
#define __CDS_SHARED_GENERIC_MUTABLE_STATEMENTS_COMPOSITE_CLIENT_IMPL_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

#ifdef _MSC_VER

#include "../GenericImmutableStatementsCompositeClient.hpp"
#include "GenericImmutableStatementsCompositeClient.hpp"

#endif

namespace cds {             /* NOLINT(modernize-concat-nested-namespaces) */
    namespace __hidden {    /* NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        namespace __impl {  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            template <
                    typename __IterableType,    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ElementType      /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > template <
                    typename __Consumer         /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > __CDS_OptimalInline auto __GenericMutableStatementsCompositeClient <
                    __IterableType,
                    __ElementType
            > :: forEach (
                    __Consumer const & consumer
            ) noexcept ( __ConsumerExceptSpecTraits < __ElementType, __Consumer > :: __noexceptSpec ) -> void {

#ifdef _MSC_VER

                using IteratorType = decltype ( cds :: meta :: referenceOf < __IterableType > ().begin () );
                return __MSVC_ForEachWrapper < IteratorType, __Consumer > :: __forEach (
                        reinterpret_cast < __IterableType * > ( this )->begin(),
                        reinterpret_cast < __IterableType * > ( this )->end(),
                        consumer
                );

#else

                /* Call base, global implementation. Abstracts the 'is object const' requirement */
                return __forEach (
                        reinterpret_cast < __IterableType * > ( this )->begin(),
                        reinterpret_cast < __IterableType * > ( this )->end(),
                        consumer
                );

#endif

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
            ) noexcept ( __PredicateExceptSpecTraits < __ElementType, __Predicate > :: __noexceptSpec ) -> bool {

#ifdef _MSC_VER

                using IteratorType = decltype ( cds :: meta :: referenceOf < __IterableType > ().begin () );
                return __MSVC_SomeWrapper < IteratorType, __Predicate > :: __some (
                        reinterpret_cast < __IterableType * > ( this )->begin(),
                        reinterpret_cast < __IterableType * > ( this )->end(),
                        count,
                        predicate
                );

#else

                /* Call base, global implementation. Abstracts the 'is object const' requirement */
                return __some (
                        reinterpret_cast < __IterableType * > ( this )->begin(),
                        reinterpret_cast < __IterableType * > ( this )->end(),
                        count,
                        predicate
                );

#endif

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
            ) noexcept ( __PredicateExceptSpecTraits < __ElementType, __Predicate > :: __noexceptSpec ) -> bool {

#ifdef _MSC_VER

                using IteratorType = decltype ( cds :: meta :: referenceOf < __IterableType > ().begin () );
                return __MSVC_AtLeastWrapper < IteratorType, __Predicate > :: __atLeast (
                        reinterpret_cast < __IterableType * > ( this )->begin(),
                        reinterpret_cast < __IterableType * > ( this )->end(),
                        count,
                        predicate
                );

#else

                /* Call base, global implementation. Abstracts the 'is object const' requirement */
                return __atLeast (
                        reinterpret_cast < __IterableType * > ( this )->begin(),
                        reinterpret_cast < __IterableType * > ( this )->end(),
                        count,
                        predicate
                );

#endif

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
            ) noexcept ( __PredicateExceptSpecTraits < __ElementType, __Predicate > :: __noexceptSpec ) -> bool {

#ifdef _MSC_VER

                using IteratorType = decltype ( cds :: meta :: referenceOf < __IterableType > ().begin () );
                return __MSVC_AtMostWrapper < IteratorType, __Predicate > :: __atMost (
                        reinterpret_cast < __IterableType * > ( this )->begin(),
                        reinterpret_cast < __IterableType * > ( this )->end(),
                        count,
                        predicate
                );

#else

                /* Call base, global implementation. Abstracts the 'is object const' requirement */
                return __atMost (
                        reinterpret_cast < __IterableType * > ( this )->begin(),
                        reinterpret_cast < __IterableType * > ( this )->end(),
                        count,
                        predicate
                );

#endif

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
            ) noexcept ( __PredicateExceptSpecTraits < __ElementType, __Predicate > :: __noexceptSpec ) -> bool {

#ifdef _MSC_VER

                using IteratorType = decltype ( cds :: meta :: referenceOf < __IterableType > ().begin () );
                return __MSVC_MoreThanWrapper < IteratorType, __Predicate > :: __moreThan (
                        reinterpret_cast < __IterableType * > ( this )->begin(),
                        reinterpret_cast < __IterableType * > ( this )->end(),
                        count,
                        predicate
                );

#else

                /* Call base, global implementation. Abstracts the 'is object const' requirement */
                return __moreThan (
                        reinterpret_cast < __IterableType * > ( this )->begin(),
                        reinterpret_cast < __IterableType * > ( this )->end(),
                        count,
                        predicate
                );

#endif

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
            ) noexcept ( __PredicateExceptSpecTraits < __ElementType, __Predicate > :: __noexceptSpec ) -> bool {

#ifdef _MSC_VER

                using IteratorType = decltype ( cds :: meta :: referenceOf < __IterableType > ().begin () );
                return __MSVC_FewerThanWrapper < IteratorType, __Predicate > :: __fewerThan (
                        reinterpret_cast < __IterableType * > ( this )->begin(),
                        reinterpret_cast < __IterableType * > ( this )->end(),
                        count,
                        predicate
                );

#else

                /* Call base, global implementation. Abstracts the 'is object const' requirement */
                return __fewerThan (
                        reinterpret_cast < __IterableType * > ( this )->begin(),
                        reinterpret_cast < __IterableType * > ( this )->end(),
                        count,
                        predicate
                );

#endif

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
            ) noexcept ( __PredicateExceptSpecTraits < __ElementType, __Predicate > :: __noexceptSpec ) -> Size {

#ifdef _MSC_VER

                using IteratorType = decltype ( cds :: meta :: referenceOf < __IterableType > ().begin () );
                return __MSVC_CountWrapper < IteratorType, __Predicate > :: __count (
                        reinterpret_cast < __IterableType * > ( this )->begin(),
                        reinterpret_cast < __IterableType * > ( this )->end(),
                        predicate
                );

#else

                /* Call base, global implementation. Abstracts the 'is object const' requirement */
                return __count (
                        reinterpret_cast < __IterableType * > ( this )->begin(),
                        reinterpret_cast < __IterableType * > ( this )->end(),
                        predicate
                );

#endif

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
            ) noexcept ( __PredicateExceptSpecTraits < __ElementType, __Predicate > :: __noexceptSpec ) -> bool {

#ifdef _MSC_VER

                using IteratorType = decltype ( cds :: meta :: referenceOf < __IterableType > ().begin () );
                return __MSVC_AnyWrapper < IteratorType, __Predicate > :: __any (
                        reinterpret_cast < __IterableType * > ( this )->begin(),
                        reinterpret_cast < __IterableType * > ( this )->end(),
                        predicate
                );

#else

                /* Call base, global implementation. Abstracts the 'is object const' requirement */
                return __any (
                        reinterpret_cast < __IterableType * > ( this )->begin(),
                        reinterpret_cast < __IterableType * > ( this )->end(),
                        predicate
                );

#endif

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
            ) noexcept ( __PredicateExceptSpecTraits < __ElementType, __Predicate > :: __noexceptSpec ) -> bool {

#ifdef _MSC_VER

                using IteratorType = decltype ( cds :: meta :: referenceOf < __IterableType > ().begin () );
                return __MSVC_AllWrapper < IteratorType, __Predicate > :: __all (
                        reinterpret_cast < __IterableType * > ( this )->begin(),
                        reinterpret_cast < __IterableType * > ( this )->end(),
                        predicate
                );

#else

                /* Call base, global implementation. Abstracts the 'is object const' requirement */
                return __all (
                        reinterpret_cast < __IterableType * > ( this )->begin(),
                        reinterpret_cast < __IterableType * > ( this )->end(),
                        predicate
                );

#endif

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
            ) noexcept ( __PredicateExceptSpecTraits < __ElementType, __Predicate > :: __noexceptSpec ) -> bool {

#ifdef _MSC_VER

                using IteratorType = decltype ( cds :: meta :: referenceOf < __IterableType > ().begin () );
                return __MSVC_NoneWrapper < IteratorType, __Predicate > :: __none (
                        reinterpret_cast < __IterableType * > ( this )->begin(),
                        reinterpret_cast < __IterableType * > ( this )->end(),
                        predicate
                );

#else

                /* Call base, global implementation. Abstracts the 'is object const' requirement */
                return __none (
                        reinterpret_cast < __IterableType * > ( this )->begin(),
                        reinterpret_cast < __IterableType * > ( this )->end(),
                        predicate
                );

#endif

            }

        } /* namespace __impl */
    } /* namespace __hidden */
} /* namespace cds */

#endif /* __CDS_SHARED_GENERIC_MUTABLE_STATEMENTS_COMPOSITE_CLIENT_IMPL_HPP__ */
