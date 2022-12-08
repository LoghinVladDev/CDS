/*
 * Created by loghin on 6/27/22.
 */

#ifndef __CDS_SHARED_FIND_BY_IMMUTABLE_COMPOSITE_CLIENT_IMPL_HPP__ /* NOLINT(llvm-header-guard) */
#define __CDS_SHARED_FIND_BY_IMMUTABLE_COMPOSITE_CLIENT_IMPL_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

#if defined _MSC_VER

#include "../../../../../functional/FunctionalInterface.hpp"

#endif

namespace cds {             /* NOLINT(modernize-concat-nested-namespaces) */
    namespace __hidden {    /* NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        namespace __impl {  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

#if defined _MSC_VER

            /*
             Manual SFINAE for little non-compliant MSVC :)
            */

            template < 
                    typename                        __IteratorType,
                    template < typename ... > class __CollectionType,
                    typename                        __Predicate,
                    bool = cds :: meta :: isMemberFunctionPointer < __Predicate > ()
            > struct __MSVC_FindThatWrapper {

                constexpr static cds :: functional :: MapperFunction <
                    __CollectionType < __IteratorType > &,
                    __IteratorType const &,
                    __IteratorType const &,
                    Size,
                    __CollectionType < __IteratorType > &,
                    __Predicate const &
                > const __findThat = nullptr;
            };


            template <
                    typename                        __IteratorType,
                    template < typename ... > class __CollectionType,
                    typename                        __Predicate
            > struct __MSVC_FindThatWrapper <
                    __IteratorType,
                    __CollectionType,
                    __Predicate,
                    false
            > {

                constexpr static cds :: functional :: MapperFunction <
                    __CollectionType < __IteratorType > &,
                    __IteratorType const &,
                    __IteratorType const &,
                    Size,
                    __CollectionType < __IteratorType > &,
                    __Predicate const &
                > const __findThat = & __findThat < __IteratorType, __CollectionType, __Predicate >;
            };


            template <
                    typename                        __IteratorType,
                    template < typename ... > class __CollectionType,
                    typename                        __Predicate
            > struct __MSVC_FindThatWrapper <
                    __IteratorType,
                    __CollectionType,
                    __Predicate,
                    true
            > {

                constexpr static cds :: functional :: MapperFunction <
                    __CollectionType < __IteratorType > &,
                    __IteratorType const &,
                    __IteratorType const &,
                    Size,
                    __CollectionType < __IteratorType > &,
                    __Predicate const &
                > const __findThat = & __findThatMember < __IteratorType, __CollectionType, __Predicate >;
            };


            template <
                    typename __IteratorType,
                    typename __Predicate,
                    bool = cds :: meta :: isMemberFunctionPointer < __Predicate > ()
            > struct __MSVC_FindFirstThatWrapper {

                constexpr static cds :: functional :: MapperFunction <
                    __IteratorType,
                    __IteratorType const &,
                    __IteratorType const &,
                    __Predicate const &
                > const __findFirstThat = nullptr;
            };


            template <
                    typename __IteratorType,
                    typename __Predicate
            > struct __MSVC_FindFirstThatWrapper <
                    __IteratorType,
                    __Predicate,
                    false
            > {

                constexpr static cds :: functional :: MapperFunction <
                    __IteratorType,
                    __IteratorType const &,
                    __IteratorType const &,
                    __Predicate const &
                > const __findFirstThat = & __findFirstThat < __IteratorType, __Predicate >;
            };


            template <
                    typename __IteratorType,
                    typename __Predicate
            > struct __MSVC_FindFirstThatWrapper <
                    __IteratorType,
                    __Predicate,
                    true
            > {

                constexpr static cds :: functional :: MapperFunction <
                    __IteratorType,
                    __IteratorType const &,
                    __IteratorType const &,
                    __Predicate const &
                > const __findFirstThat = & __findFirstThatMember < __IteratorType, __Predicate >;
            };


            template <
                    typename __IteratorType,
                    typename __Predicate,
                    bool = cds :: meta :: isMemberFunctionPointer < __Predicate > ()
            > struct __MSVC_FindLastThatWrapper {

                constexpr static cds :: functional :: MapperFunction <
                    __IteratorType,
                    __IteratorType const &,
                    __IteratorType const &,
                    __Predicate const &
                > const __findLastThat = nullptr;
            };


            template <
                    typename __IteratorType,
                    typename __Predicate
            > struct __MSVC_FindLastThatWrapper <
                    __IteratorType,
                    __Predicate,
                    false
            > {

                constexpr static cds :: functional :: MapperFunction <
                    __IteratorType,
                    __IteratorType const &,
                    __IteratorType const &,
                    __Predicate const &
                > const __findLastThat = & __findLastThat < __IteratorType, __Predicate >;
            };


            template <
                    typename __IteratorType,
                    typename __Predicate
            > struct __MSVC_FindLastThatWrapper <
                    __IteratorType,
                    __Predicate,
                    true
            > {

                constexpr static cds :: functional :: MapperFunction <
                    __IteratorType,
                    __IteratorType const &,
                    __IteratorType const &,
                    __Predicate const &
                > const __findLastThat = & __findLastThatMember < __IteratorType, __Predicate >;
            };


            template <
                    typename                        __IteratorType,
                    template < typename ... > class __CollectionType,
                    typename                        __Predicate,
                    bool = cds :: meta :: isMemberFunctionPointer < __Predicate > ()
            > struct __MSVC_FindAllThatWrapper {

                constexpr static cds :: functional :: MapperFunction <
                    __CollectionType < __IteratorType > &,
                    __IteratorType const &,
                    __IteratorType const &,
                    __CollectionType < __IteratorType > &,
                    __Predicate const &
                > const __findAllThat = nullptr;
            };


            template <
                    typename                        __IteratorType,
                    template < typename ... > class __CollectionType,
                    typename                        __Predicate
            > struct __MSVC_FindAllThatWrapper <
                    __IteratorType,
                    __CollectionType,
                    __Predicate,
                    false
            > {

                constexpr static cds :: functional :: MapperFunction <
                    __CollectionType < __IteratorType > &,
                    __IteratorType const &,
                    __IteratorType const &,
                    __CollectionType < __IteratorType > &,
                    __Predicate const &
                > const __findAllThat = & __findAllThat < __IteratorType, __CollectionType, __Predicate >;
            };


            template <
                    typename                        __IteratorType,
                    template < typename ... > class __CollectionType,
                    typename                        __Predicate
            > struct __MSVC_FindAllThatWrapper <
                    __IteratorType,
                    __CollectionType,
                    __Predicate,
                    true
            > {

                constexpr static cds :: functional :: MapperFunction <
                    __CollectionType < __IteratorType > &,
                    __IteratorType const &,
                    __IteratorType const &,
                    __CollectionType < __IteratorType > &,
                    __Predicate const &
                > const __findAllThat = & __findAllThatMember < __IteratorType, __CollectionType, __Predicate >;
            };

#endif

            template <
                    typename                        __IterableType,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                        __ElementType,      /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                        __IteratorType      /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > template <
                    template < typename ... > class __CollectionType,   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                        __Predicate         /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > __CDS_OptimalInline auto __FindByImmutableCompositeClient <
                    __IterableType,
                    __ElementType,
                    __IteratorType
            > :: findThat (
                    Size                                        count,
                    __CollectionType < ConstIterator >        & storeIn,
                    __Predicate                         const & predicate
            ) const noexcept ( noexcept ( __PredicateExceptSpecTraits < __ElementType const, __Predicate > :: __noexceptSpec ) ) -> __CollectionType < ConstIterator > & {

#ifdef _MSC_VER

                /* Call base, global implementation. Abstracts the 'is object const' requirement.
                 * Also use the MSVC dedicated manual-SFINAE wrapper due to the year being (almost)
                 * 2022 and they still can't deduce whether a function is enabled or not. */
                return __MSVC_FindThatWrapper < __IteratorType, __CollectionType, __Predicate > :: __findThat (
                        reinterpret_cast < __IterableType const * > ( this )->cbegin(),
                        reinterpret_cast < __IterableType const * > ( this )->cend(),
                        count,
                        storeIn,
                        predicate
                );

#else

                /* Call base, global implementation. Abstracts the 'is object const' requirement */
                return __findThat (
                        reinterpret_cast < __IterableType const * > ( this )->cbegin(),
                        reinterpret_cast < __IterableType const * > ( this )->cend(),
                        count,
                        storeIn,
                        predicate
                );

#endif

            }


            template <
                    typename                        __IterableType,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                        __ElementType,      /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                        __IteratorType      /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > template <
                    template < typename ... > class __CollectionType,   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                        __Predicate         /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > __CDS_OptimalInline auto __FindByImmutableCompositeClient <
                    __IterableType,
                    __ElementType,
                    __IteratorType
            > :: findThat (
                    Size                count,
                    __Predicate const & predicate
            ) const noexcept ( noexcept ( __PredicateExceptSpecTraits < __ElementType const, __Predicate > :: __noexceptSpec ) ) -> __CollectionType < ConstIterator > {

                __CollectionType < ConstIterator > foundIterators;

#ifdef _MSC_VER

            /* Call base, global implementation. Abstracts the 'is object const' requirement.
                 * Also use the MSVC dedicated manual-SFINAE wrapper due to the year being (almost)
                 * 2022 and they still can't deduce whether a function is enabled or not. */
                return __MSVC_FindThatWrapper < __IteratorType, __CollectionType, __Predicate > :: __findThat (
                        reinterpret_cast < __IterableType const * > ( this )->cbegin(),
                        reinterpret_cast < __IterableType const * > ( this )->cend(),
                        count,
                        foundIterators,
                        predicate
                );

#else

                /* Call base, global implementation. Abstracts the 'is object const' requirement */
                return __findThat (
                        reinterpret_cast < __IterableType const * > ( this )->cbegin(),
                        reinterpret_cast < __IterableType const * > ( this )->cend(),
                        count,
                        foundIterators,
                        predicate
                );

#endif

            }


            template <
                    typename                        __IterableType,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                        __ElementType,      /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                        __IteratorType      /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > template <
                    typename                        __Predicate         /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > __CDS_OptimalInline auto __FindByImmutableCompositeClient <
                    __IterableType,
                    __ElementType,
                    __IteratorType
            > :: findFirstThat (
                    __Predicate const & predicate
            ) const noexcept ( noexcept ( __PredicateExceptSpecTraits < __ElementType const, __Predicate > :: __noexceptSpec ) ) -> ConstIterator {

#ifdef _MSC_VER

                /* Call base, global implementation. Abstracts the 'is object const' requirement.
                 * Also use the MSVC dedicated manual-SFINAE wrapper due to the year being
                 * 2022 and they still can't deduce whether a function is enabled or not. */
                return __MSVC_FindFirstThatWrapper < __IteratorType, __Predicate > :: __findFirstThat (
                        reinterpret_cast < __IterableType const * > ( this )->cbegin(),
                        reinterpret_cast < __IterableType const * > ( this )->cend(),
                        predicate
                );

#else

                /* Call base, global implementation. Abstracts the 'is object const' requirement */
                return __findFirstThat (
                        reinterpret_cast < __IterableType const * > ( this )->cbegin(),
                        reinterpret_cast < __IterableType const * > ( this )->cend(),
                        predicate
                );

#endif

            }


            template <
                    typename                        __IterableType,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                        __ElementType,      /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                        __IteratorType      /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > template <
                    typename                        __Predicate         /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > __CDS_OptimalInline auto __FindByImmutableCompositeClient <
                    __IterableType,
                    __ElementType,
                    __IteratorType
            > :: findLastThat (
                    __Predicate const & predicate
            ) const noexcept ( noexcept ( __PredicateExceptSpecTraits < __ElementType const, __Predicate > :: __noexceptSpec ) ) -> ConstIterator {

#ifdef _MSC_VER

                /* Call base, global implementation. Abstracts the 'is object const' requirement.
                 * Also use the MSVC dedicated manual-SFINAE wrapper due to the year being
                 * 2022 and they still can't deduce whether a function is enabled or not. */
                return __MSVC_FindLastThatWrapper < __IteratorType, __Predicate > :: __findLastThat (
                        reinterpret_cast < __IterableType const * > ( this )->cbegin(),
                        reinterpret_cast < __IterableType const * > ( this )->cend(),
                        predicate
                );

#else

                /* Call base, global implementation. Abstracts the 'is object const' requirement */
                return __findLastThat (
                        reinterpret_cast < __IterableType const * > ( this )->cbegin(),
                        reinterpret_cast < __IterableType const * > ( this )->cend(),
                        predicate
                );

#endif

            }


            template <
                    typename                        __IterableType,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                        __ElementType,      /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                        __IteratorType      /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > template <
                    template < typename ... > class __CollectionType,   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                        __Predicate         /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > __CDS_OptimalInline auto __FindByImmutableCompositeClient <
                    __IterableType,
                    __ElementType,
                    __IteratorType
            > :: findAllThat (
                    __CollectionType < ConstIterator >        & storeIn,
                    __Predicate                         const & predicate
            ) const noexcept ( noexcept ( __PredicateExceptSpecTraits < __ElementType const, __Predicate > :: __noexceptSpec ) ) -> __CollectionType < ConstIterator > & {

#ifdef _MSC_VER

                /* Call base, global implementation. Abstracts the 'is object const' requirement.
                 * Also use the MSVC dedicated manual-SFINAE wrapper due to the year being
                 * 2022 and they still can't deduce whether a function is enabled or not. */
                return __MSVC_FindAllThatWrapper < __IteratorType, __CollectionType, __Predicate > :: __findAllThat (
                        reinterpret_cast < __IterableType const * > ( this )->cbegin(),
                        reinterpret_cast < __IterableType const * > ( this )->cend(),
                        storeIn,
                        predicate
                );

#else

                /* Call base, global implementation. Abstracts the 'is object const' requirement */
                return __findAllThat (
                        reinterpret_cast < __IterableType const * > ( this )->cbegin(),
                        reinterpret_cast < __IterableType const * > ( this )->cend(),
                        storeIn,
                        predicate
                );

#endif

            }


            template <
                    typename                        __IterableType,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                        __ElementType,      /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                        __IteratorType      /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > template <
                    template < typename ... > class __CollectionType,   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                        __Predicate         /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > __CDS_OptimalInline auto __FindByImmutableCompositeClient <
                    __IterableType,
                    __ElementType,
                    __IteratorType
            > :: findAllThat (
                    __Predicate const & predicate
            ) const noexcept ( noexcept ( __PredicateExceptSpecTraits < __ElementType const, __Predicate > :: __noexceptSpec ) ) -> __CollectionType < ConstIterator > {

                __CollectionType < ConstIterator > foundIterators;

#ifdef _MSC_VER

                /* Call base, global implementation. Abstracts the 'is object const' requirement.
                 * Also use the MSVC dedicated manual-SFINAE wrapper due to the year being
                 * 2022 and they still can't deduce whether a function is enabled or not. */
                return __MSVC_FindAllThatWrapper < __IteratorType, __CollectionType, __Predicate > :: __findAllThat (
                        reinterpret_cast < __IterableType const * > ( this )->cbegin(),
                        reinterpret_cast < __IterableType const * > ( this )->cend(),
                        foundIterators,
                        predicate
                );

#else

                /* Call base, global implementation. Abstracts the 'is object const' requirement */
                return __findAllThat (
                        reinterpret_cast < __IterableType const * > ( this )->cbegin(),
                        reinterpret_cast < __IterableType const * > ( this )->cend(),
                        foundIterators,
                        predicate
                );

#endif

            }

        } /* namespace __impl */
    } /* namespace __hidden */
} /* namespace cds */

#endif /* __CDS_SHARED_FIND_BY_IMMUTABLE_COMPOSITE_CLIENT_IMPL_HPP__ */
