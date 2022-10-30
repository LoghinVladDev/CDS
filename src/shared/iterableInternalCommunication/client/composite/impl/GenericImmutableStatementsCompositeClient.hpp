/*
 * Created by loghin on 6/26/22.
 */

#ifndef __CDS_SHARED_GENERIC_IMMUTABLE_STATEMENTS_COMPOSITE_CLIENT_IMPL_HPP__ /* NOLINT(llvm-header-guard) */
#define __CDS_SHARED_GENERIC_IMMUTABLE_STATEMENTS_COMPOSITE_CLIENT_IMPL_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

#if defined _MSC_VER

#include "../../../../../functional/FunctionalInterface.hpp"

#endif

namespace cds {             /* NOLINT(modernize-concat-nested-namespaces) */
    namespace __hidden {    /* NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        namespace __impl {  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

#ifdef _MSC_VER

            /*
             Manual SFINAE for little non-compliant MSVC :)
            */

            template <
                    typename                        __IteratorType,
                    typename                        __Consumer,
                    bool = cds :: meta :: isMemberFunctionPointer < __Consumer > ()
            > struct __MSVC_ForEachWrapper {

                constexpr static cds :: functional :: ConsumerFunction <
                        __IteratorType const &,
                        __IteratorType const &,
                        __Consumer     const &
                > __forEach = nullptr;
            };


            template <
                    typename                        __IteratorType,
                    typename                        __Consumer
            > struct __MSVC_ForEachWrapper <
                    __IteratorType,
                    __Consumer,
                    false
            > {

                constexpr static cds :: functional :: ConsumerFunction <
                        __IteratorType const &,
                        __IteratorType const &,
                        __Consumer     const &
                > __forEach = & __forEach < __IteratorType, __Consumer >;
            };


            template <
                    typename                        __IteratorType,
                    typename                        __Consumer
            > struct __MSVC_ForEachWrapper <
                    __IteratorType,
                    __Consumer,
                    true
            > {

                constexpr static cds :: functional :: ConsumerFunction <
                        __IteratorType const &,
                        __IteratorType const &,
                        __Consumer     const &
                > __forEach = & __forEachMember < __IteratorType, __Consumer >;
            };


            template <
                    typename                        __IteratorType,
                    typename                        __Predicate,
                    bool = cds :: meta :: isMemberFunctionPointer < __Predicate > ()
            > struct __MSVC_SomeWrapper {

                constexpr static cds :: functional :: PredicateFunction <
                        __IteratorType const &,
                        __IteratorType const &,
                        Size,
                        __Predicate    const &
                > __some = nullptr;
            };


            template <
                    typename                        __IteratorType,
                    typename                        __Predicate
            > struct __MSVC_SomeWrapper <
                    __IteratorType,
                    __Predicate,
                    false
            > {

                constexpr static cds :: functional :: PredicateFunction <
                        __IteratorType const &,
                        __IteratorType const &,
                        Size,
                        __Predicate    const &
                > __some = & __some < __IteratorType, __Predicate >;
            };


            template <
                    typename                        __IteratorType,
                    typename                        __Predicate
            > struct __MSVC_SomeWrapper <
                    __IteratorType,
                    __Predicate,
                    true
            > {

                constexpr static cds :: functional :: PredicateFunction <
                        __IteratorType const &,
                        __IteratorType const &,
                        Size,
                        __Predicate    const &
                > __some = & __someMember < __IteratorType, __Predicate >;
            };


            template <
                    typename                        __IteratorType,
                    typename                        __Predicate,
                    bool = cds :: meta :: isMemberFunctionPointer < __Predicate > ()
            > struct __MSVC_AtLeastWrapper {

                constexpr static cds :: functional :: PredicateFunction <
                        __IteratorType const &,
                        __IteratorType const &,
                        Size,
                        __Predicate    const &
                > __atLeast = nullptr;
            };


            template <
                    typename                        __IteratorType,
                    typename                        __Predicate
            > struct __MSVC_AtLeastWrapper <
                    __IteratorType,
                    __Predicate,
                    false
            > {

                constexpr static cds :: functional :: PredicateFunction <
                        __IteratorType const &,
                        __IteratorType const &,
                        Size,
                        __Predicate    const &
                > __atLeast = & __atLeast < __IteratorType, __Predicate >;
            };


            template <
                    typename                        __IteratorType,
                    typename                        __Predicate
            > struct __MSVC_AtLeastWrapper <
                    __IteratorType,
                    __Predicate,
                    true
            > {

                constexpr static cds :: functional :: PredicateFunction <
                        __IteratorType const &,
                        __IteratorType const &,
                        Size,
                        __Predicate    const &
                > __atLeast = & __atLeastMember < __IteratorType, __Predicate >;
            };


            template <
                    typename                        __IteratorType,
                    typename                        __Predicate,
                    bool = cds :: meta :: isMemberFunctionPointer < __Predicate > ()
            > struct __MSVC_AtMostWrapper {

                constexpr static cds :: functional :: PredicateFunction <
                        __IteratorType const &,
                        __IteratorType const &,
                        Size,
                        __Predicate    const &
                > __atMost = nullptr;
            };


            template <
                    typename                        __IteratorType,
                    typename                        __Predicate
            > struct __MSVC_AtMostWrapper <
                    __IteratorType,
                    __Predicate,
                    false
            > {

                constexpr static cds :: functional :: PredicateFunction <
                        __IteratorType const &,
                        __IteratorType const &,
                        Size,
                        __Predicate    const &
                > __atMost = & __atMost < __IteratorType, __Predicate >;
            };


            template <
                    typename                        __IteratorType,
                    typename                        __Predicate
            > struct __MSVC_AtMostWrapper <
                    __IteratorType,
                    __Predicate,
                    true
            > {

                constexpr static cds :: functional :: PredicateFunction <
                        __IteratorType const &,
                        __IteratorType const &,
                        Size,
                        __Predicate    const &
                > __atMost = & __atMostMember < __IteratorType, __Predicate >;
            };


            template <
                    typename                        __IteratorType,
                    typename                        __Predicate,
                    bool = cds :: meta :: isMemberFunctionPointer < __Predicate > ()
            > struct __MSVC_MoreThanWrapper {

                constexpr static cds :: functional :: PredicateFunction <
                        __IteratorType const &,
                        __IteratorType const &,
                        Size,
                        __Predicate    const &
                > __moreThan = nullptr;
            };


            template <
                    typename                        __IteratorType,
                    typename                        __Predicate
            > struct __MSVC_MoreThanWrapper <
                    __IteratorType,
                    __Predicate,
                    false
            > {

                constexpr static cds :: functional :: PredicateFunction <
                        __IteratorType const &,
                        __IteratorType const &,
                        Size,
                        __Predicate    const &
                > __moreThan = & __moreThan < __IteratorType, __Predicate >;
            };


            template <
                    typename                        __IteratorType,
                    typename                        __Predicate
            > struct __MSVC_MoreThanWrapper <
                    __IteratorType,
                    __Predicate,
                    true
            > {

                constexpr static cds :: functional :: PredicateFunction <
                        __IteratorType const &,
                        __IteratorType const &,
                        Size,
                        __Predicate    const &
                > __moreThan = & __moreThanMember < __IteratorType, __Predicate >;
            };


            template <
                    typename                        __IteratorType,
                    typename                        __Predicate,
                    bool = cds :: meta :: isMemberFunctionPointer < __Predicate > ()
            > struct __MSVC_FewerThanWrapper {

                constexpr static cds :: functional :: PredicateFunction <
                        __IteratorType const &,
                        __IteratorType const &,
                        Size,
                        __Predicate    const &
                > __fewerThan = nullptr;
            };


            template <
                    typename                        __IteratorType,
                    typename                        __Predicate
            > struct __MSVC_FewerThanWrapper <
                    __IteratorType,
                    __Predicate,
                    false
            > {

                constexpr static cds :: functional :: PredicateFunction <
                        __IteratorType const &,
                        __IteratorType const &,
                        Size,
                        __Predicate    const &
                > __fewerThan = & __fewerThan < __IteratorType, __Predicate >;
            };


            template <
                    typename                        __IteratorType,
                    typename                        __Predicate
            > struct __MSVC_FewerThanWrapper <
                    __IteratorType,
                    __Predicate,
                    true
            > {

                constexpr static cds :: functional :: PredicateFunction <
                        __IteratorType const &,
                        __IteratorType const &,
                        Size,
                        __Predicate    const &
                > __fewerThan = & __fewerThanMember < __IteratorType, __Predicate >;
            };


            template <
                    typename                        __IteratorType,
                    typename                        __Predicate,
                    bool = cds :: meta :: isMemberFunctionPointer < __Predicate > ()
            > struct __MSVC_CountWrapper {

                constexpr static cds :: functional :: MapperFunction <
                        Size,
                        __IteratorType const &,
                        __IteratorType const &,
                        __Predicate    const &
                > __count = nullptr;
            };


            template <
                    typename                        __IteratorType,
                    typename                        __Predicate
            > struct __MSVC_CountWrapper <
                    __IteratorType,
                    __Predicate,
                    false
            > {

                constexpr static cds :: functional :: MapperFunction <
                        Size,
                        __IteratorType const &,
                        __IteratorType const &,
                        __Predicate    const &
                > __count = & __count < __IteratorType, __Predicate >;
            };


            template <
                    typename                        __IteratorType,
                    typename                        __Predicate
            > struct __MSVC_CountWrapper <
                    __IteratorType,
                    __Predicate,
                    true
            > {

                constexpr static cds :: functional :: MapperFunction <
                        __IteratorType const &,
                        __IteratorType const &,
                        __Predicate    const &
                > __count = & __countMember < __IteratorType, __Predicate >;
            };


            template <
                    typename                        __IteratorType,
                    typename                        __Predicate,
                    bool = cds :: meta :: isMemberFunctionPointer < __Predicate > ()
            > struct __MSVC_AnyWrapper {

                constexpr static cds :: functional :: PredicateFunction <
                        __IteratorType const &,
                        __IteratorType const &,
                        __Predicate    const &
                > __any = nullptr;
            };


            template <
                    typename                        __IteratorType,
                    typename                        __Predicate
            > struct __MSVC_AnyWrapper <
                    __IteratorType,
                    __Predicate,
                    false
            > {

                constexpr static cds :: functional :: PredicateFunction <
                        __IteratorType const &,
                        __IteratorType const &,
                        __Predicate    const &
                > __any = & __any < __IteratorType, __Predicate >;
            };


            template <
                    typename                        __IteratorType,
                    typename                        __Predicate
            > struct __MSVC_AnyWrapper <
                    __IteratorType,
                    __Predicate,
                    true
            > {

                constexpr static cds :: functional :: PredicateFunction <
                        __IteratorType const &,
                        __IteratorType const &,
                        __Predicate    const &
                > __any = & __anyMember < __IteratorType, __Predicate >;
            };


            template <
                    typename                        __IteratorType,
                    typename                        __Predicate,
                    bool = cds :: meta :: isMemberFunctionPointer < __Predicate > ()
            > struct __MSVC_AllWrapper {

                constexpr static cds :: functional :: PredicateFunction <
                        __IteratorType const &,
                        __IteratorType const &,
                        __Predicate    const &
                > __all = nullptr;
            };


            template <
                    typename                        __IteratorType,
                    typename                        __Predicate
            > struct __MSVC_AllWrapper <
                    __IteratorType,
                    __Predicate,
                    false
            > {

                constexpr static cds :: functional :: PredicateFunction <
                        __IteratorType const &,
                        __IteratorType const &,
                        __Predicate    const &
                > __all = & __all < __IteratorType, __Predicate >;
            };


            template <
                    typename                        __IteratorType,
                    typename                        __Predicate
            > struct __MSVC_AllWrapper <
                    __IteratorType,
                    __Predicate,
                    true
            > {

                constexpr static cds :: functional :: PredicateFunction <
                        __IteratorType const &,
                        __IteratorType const &,
                        __Predicate    const &
                > __all = & __allMember < __IteratorType, __Predicate >;
            };


            template <
                    typename                        __IteratorType,
                    typename                        __Predicate,
                    bool = cds :: meta :: isMemberFunctionPointer < __Predicate > ()
            > struct __MSVC_NoneWrapper {

                constexpr static cds :: functional :: PredicateFunction <
                        __IteratorType const &,
                        __IteratorType const &,
                        __Predicate    const &
                > __none = nullptr;
            };


            template <
                    typename                        __IteratorType,
                    typename                        __Predicate
            > struct __MSVC_NoneWrapper <
                    __IteratorType,
                    __Predicate,
                    false
            > {

                constexpr static cds :: functional :: PredicateFunction <
                        __IteratorType const &,
                        __IteratorType const &,
                        __Predicate    const &
                > __none = & __none < __IteratorType, __Predicate >;
            };


            template <
                    typename                        __IteratorType,
                    typename                        __Predicate
            > struct __MSVC_NoneWrapper <
                    __IteratorType,
                    __Predicate,
                    true
            > {

                constexpr static cds :: functional :: PredicateFunction <
                        __IteratorType const &,
                        __IteratorType const &,
                        __Predicate    const &
                > __none = & __noneMember < __IteratorType, __Predicate >;
            };

#endif

            template <
                    typename __IterableType,    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ElementType      /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > template <
                    typename __Consumer         /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > __CDS_OptimalInline auto __GenericImmutableStatementsCompositeClient <
                    __IterableType,
                    __ElementType
            > :: forEach (
                    __Consumer const & consumer
            ) const noexcept ( __ConsumerExceptSpecTraits < __ElementType const, __Consumer > :: __noexceptSpec ) -> void {

#ifdef _MSC_VER

                using IteratorType = decltype ( cds :: meta :: referenceOf < __IterableType const > ().cbegin () );
                return __MSVC_ForEachWrapper < IteratorType, __Consumer > :: __forEach (
                        reinterpret_cast < __IterableType const * > ( this )->cbegin(),
                        reinterpret_cast < __IterableType const * > ( this )->cend(),
                        consumer
                );

#else

                /* Call base, global implementation. Abstracts the 'is object const' requirement */
                return __forEach (
                        reinterpret_cast < __IterableType const * > ( this )->cbegin(),
                        reinterpret_cast < __IterableType const * > ( this )->cend(),
                        consumer
                );

#endif

            }


            template <
                    typename __IterableType,    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ElementType      /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > template <
                    typename __Predicate        /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > __CDS_OptimalInline auto __GenericImmutableStatementsCompositeClient <
                    __IterableType,
                    __ElementType
            > :: some (
                    Size                count,
                    __Predicate const & predicate
            ) const noexcept ( __PredicateExceptSpecTraits < __ElementType const, __Predicate > :: __noexceptSpec ) -> bool {

#ifdef _MSC_VER

                using IteratorType = decltype ( cds :: meta :: referenceOf < __IterableType const > ().cbegin () );
                return __MSVC_SomeWrapper < IteratorType, __Predicate > :: __some (
                        reinterpret_cast < __IterableType const * > ( this )->cbegin(),
                        reinterpret_cast < __IterableType const * > ( this )->cend(),
                        count,
                        predicate
                );

#else

                /* Call base, global implementation. Abstracts the 'is object const' requirement */
                return __some (
                        reinterpret_cast < __IterableType const * > ( this )->cbegin(),
                        reinterpret_cast < __IterableType const * > ( this )->cend(),
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
            > __CDS_OptimalInline auto __GenericImmutableStatementsCompositeClient <
                    __IterableType,
                    __ElementType
            > :: atLeast (
                    Size                count,
                    __Predicate const & predicate
            ) const noexcept ( __PredicateExceptSpecTraits < __ElementType const, __Predicate > :: __noexceptSpec ) -> bool {

#ifdef _MSC_VER

                using IteratorType = decltype ( cds :: meta :: referenceOf < __IterableType const > ().cbegin () );
                return __MSVC_AtLeastWrapper < IteratorType, __Predicate > :: __atLeast (
                        reinterpret_cast < __IterableType const * > ( this )->cbegin(),
                        reinterpret_cast < __IterableType const * > ( this )->cend(),
                        count,
                        predicate
                );

#else

                /* Call base, global implementation. Abstracts the 'is object const' requirement */
                return __atLeast (
                        reinterpret_cast < __IterableType const * > ( this )->cbegin(),
                        reinterpret_cast < __IterableType const * > ( this )->cend(),
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
            > __CDS_OptimalInline auto __GenericImmutableStatementsCompositeClient <
                    __IterableType,
                    __ElementType
            > :: atMost (
                    Size                count,
                    __Predicate const & predicate
            ) const noexcept ( __PredicateExceptSpecTraits < __ElementType const, __Predicate > :: __noexceptSpec ) -> bool {

#ifdef _MSC_VER

                using IteratorType = decltype ( cds :: meta :: referenceOf < __IterableType const > ().cbegin () );
                return __MSVC_AtMostWrapper < IteratorType, __Predicate > :: __atMost (
                        reinterpret_cast < __IterableType const * > ( this )->cbegin(),
                        reinterpret_cast < __IterableType const * > ( this )->cend(),
                        count,
                        predicate
                );

#else

                /* Call base, global implementation. Abstracts the 'is object const' requirement */
                return __atMost (
                        reinterpret_cast < __IterableType const * > ( this )->cbegin(),
                        reinterpret_cast < __IterableType const * > ( this )->cend(),
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
            > __CDS_OptimalInline auto __GenericImmutableStatementsCompositeClient <
                    __IterableType,
                    __ElementType
            > :: moreThan (
                    Size                count,
                    __Predicate const & predicate
            ) const noexcept ( __PredicateExceptSpecTraits < __ElementType const, __Predicate > :: __noexceptSpec ) -> bool {

#ifdef _MSC_VER

                using IteratorType = decltype ( cds :: meta :: referenceOf < __IterableType const > ().cbegin () );
                return __MSVC_MoreThanWrapper < IteratorType, __Predicate > :: __moreThan (
                        reinterpret_cast < __IterableType const * > ( this )->cbegin(),
                        reinterpret_cast < __IterableType const * > ( this )->cend(),
                        count,
                        predicate
                );

#else

                /* Call base, global implementation. Abstracts the 'is object const' requirement */
                return __moreThan (
                        reinterpret_cast < __IterableType const * > ( this )->cbegin(),
                        reinterpret_cast < __IterableType const * > ( this )->cend(),
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
            > __CDS_OptimalInline auto __GenericImmutableStatementsCompositeClient <
                    __IterableType,
                    __ElementType
            > :: fewerThan (
                    Size                count,
                    __Predicate const & predicate
            ) const noexcept ( __PredicateExceptSpecTraits < __ElementType const, __Predicate > :: __noexceptSpec ) -> bool {

#ifdef _MSC_VER

                using IteratorType = decltype ( cds :: meta :: referenceOf < __IterableType const > ().cbegin () );
                return __MSVC_FewerThanWrapper < IteratorType, __Predicate > :: __fewerThan (
                        reinterpret_cast < __IterableType const * > ( this )->cbegin(),
                        reinterpret_cast < __IterableType const * > ( this )->cend(),
                        count,
                        predicate
                );

#else

                /* Call base, global implementation. Abstracts the 'is object const' requirement */
                return __fewerThan (
                        reinterpret_cast < __IterableType const * > ( this )->cbegin(),
                        reinterpret_cast < __IterableType const * > ( this )->cend(),
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
            > __CDS_OptimalInline auto __GenericImmutableStatementsCompositeClient <
                    __IterableType,
                    __ElementType
            > :: count (
                    __Predicate const & predicate
            ) const noexcept ( __PredicateExceptSpecTraits < __ElementType const, __Predicate > :: __noexceptSpec ) -> Size {

#ifdef _MSC_VER

                using IteratorType = decltype ( cds :: meta :: referenceOf < __IterableType const > ().cbegin () );
                return __MSVC_CountWrapper < IteratorType, __Predicate > :: __count (
                        reinterpret_cast < __IterableType const * > ( this )->cbegin(),
                        reinterpret_cast < __IterableType const * > ( this )->cend(),
                        predicate
                );

#else

                /* Call base, global implementation. Abstracts the 'is object const' requirement */
                return __count (
                        reinterpret_cast < __IterableType const * > ( this )->cbegin(),
                        reinterpret_cast < __IterableType const * > ( this )->cend(),
                        predicate
                );

#endif

            }


            template <
                    typename __IterableType,    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ElementType      /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > template <
                    typename __Predicate        /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > __CDS_OptimalInline auto __GenericImmutableStatementsCompositeClient <
                    __IterableType,
                    __ElementType
            > :: any (
                    __Predicate const & predicate
            ) const noexcept ( __PredicateExceptSpecTraits < __ElementType const, __Predicate > :: __noexceptSpec ) -> bool {

#ifdef _MSC_VER

                using IteratorType = decltype ( cds :: meta :: referenceOf < __IterableType const > ().cbegin () );
                return __MSVC_AnyWrapper < IteratorType, __Predicate > :: __any (
                        reinterpret_cast < __IterableType const * > ( this )->cbegin(),
                        reinterpret_cast < __IterableType const * > ( this )->cend(),
                        predicate
                );

#else

                /* Call base, global implementation. Abstracts the 'is object const' requirement */
                return __any (
                        reinterpret_cast < __IterableType const * > ( this )->cbegin(),
                        reinterpret_cast < __IterableType const * > ( this )->cend(),
                        predicate
                );

#endif

            }


            template <
                    typename __IterableType,    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ElementType      /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > template <
                    typename __Predicate        /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > __CDS_OptimalInline auto __GenericImmutableStatementsCompositeClient <
                    __IterableType,
                    __ElementType
            > :: all (
                    __Predicate const & predicate
            ) const noexcept ( __PredicateExceptSpecTraits < __ElementType const, __Predicate > :: __noexceptSpec ) -> bool {

#ifdef _MSC_VER

                using IteratorType = decltype ( cds :: meta :: referenceOf < __IterableType const > ().cbegin () );
                return __MSVC_AllWrapper < IteratorType, __Predicate > :: __all (
                        reinterpret_cast < __IterableType const * > ( this )->cbegin(),
                        reinterpret_cast < __IterableType const * > ( this )->cend(),
                        predicate
                );

#else

                /* Call base, global implementation. Abstracts the 'is object const' requirement */
                return __all (
                        reinterpret_cast < __IterableType const * > ( this )->cbegin(),
                        reinterpret_cast < __IterableType const * > ( this )->cend(),
                        predicate
                );

#endif

            }


            template <
                    typename __IterableType,    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ElementType      /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > template <
                    typename __Predicate        /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > __CDS_OptimalInline auto __GenericImmutableStatementsCompositeClient <
                    __IterableType,
                    __ElementType
            > :: none (
                    __Predicate const & predicate
            ) const noexcept ( __PredicateExceptSpecTraits < __ElementType const, __Predicate > :: __noexceptSpec ) -> bool {

#ifdef _MSC_VER

                using IteratorType = decltype ( cds :: meta :: referenceOf < __IterableType const > ().cbegin () );
                return __MSVC_NoneWrapper < IteratorType, __Predicate > :: __none (
                        reinterpret_cast < __IterableType const * > ( this )->cbegin(),
                        reinterpret_cast < __IterableType const * > ( this )->cend(),
                        predicate
                );

#else

                /* Call base, global implementation. Abstracts the 'is object const' requirement */
                return __none (
                        reinterpret_cast < __IterableType const * > ( this )->cbegin(),
                        reinterpret_cast < __IterableType const * > ( this )->cend(),
                        predicate
                );

#endif

            }

        } /* namespace __impl */
    } /* namespace __hidden */
} /* namespace cds */

#endif /* __CDS_SHARED_GENERIC_IMMUTABLE_STATEMENTS_COMPOSITE_CLIENT_IMPL_HPP__ */
