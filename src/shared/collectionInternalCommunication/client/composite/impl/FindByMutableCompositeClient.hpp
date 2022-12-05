/*
 * Created by loghin on 6/27/22.
 */

#ifndef __CDS_SHARED_FIND_BY_MUTABLE_COMPOSITE_CLIENT_IMPL_HPP__ /* NOLINT(llvm-header-guard) */
#define __CDS_SHARED_FIND_BY_MUTABLE_COMPOSITE_CLIENT_IMPL_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

#ifdef _MSC_VER

#include "../FindByImmutableCompositeClient.hpp"
#include "FindByImmutableCompositeClient.hpp"

#endif

namespace cds {             /* NOLINT(modernize-concat-nested-namespaces) */
    namespace __hidden {    /* NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        namespace __impl {  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            template <
                    typename                        __IterableType,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                        __ElementType,      /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                        __IteratorType      /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > template <
                    template < typename ... > class __CollectionType,   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                        __Predicate         /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > __CDS_OptimalInline auto __FindByMutableCompositeClient <
                    __IterableType,
                    __ElementType,
                    __IteratorType
            > :: findThat (
                    Size                                        count,
                    __CollectionType < Iterator >             & storeIn,
                    __Predicate                         const & predicate
            ) noexcept ( noexcept ( __PredicateExceptSpecTraits < __ElementType, __Predicate > :: __noexceptSpec ) ) -> __CollectionType < Iterator > & {

#ifdef _MSC_VER

                /* Usable in Mutable Client, no implementation would reasonably include the mutable client before
                 * or without the immutable one beforehand. (Design Based) */
                /* Call base, global implementation. Abstracts the 'is object const' requirement.
                 * Also use the MSVC dedicated manual-SFINAE wrapper due to the year being (almost)
                 * 2022 and they still can't deduce whether a function is enabled or not. */
                return __MSVC_FindThatWrapper < __IteratorType, __CollectionType, __Predicate > :: __findThat (
                        reinterpret_cast < __IterableType * > ( this )->begin(),
                        reinterpret_cast < __IterableType * > ( this )->end(),
                        count,
                        storeIn,
                        predicate
                );

#else

                /* Call base, global implementation. Abstracts the 'is object const' requirement */
                return __findThat (
                        reinterpret_cast < __IterableType * > ( this )->begin(),
                        reinterpret_cast < __IterableType * > ( this )->end(),
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
            > __CDS_OptimalInline auto __FindByMutableCompositeClient <
                    __IterableType,
                    __ElementType,
                    __IteratorType
            > :: findThat (
                    Size                count,
                    __Predicate const & predicate
            ) noexcept ( noexcept ( __PredicateExceptSpecTraits < __ElementType, __Predicate > :: __noexceptSpec ) ) -> __CollectionType < Iterator > {

                __CollectionType < Iterator > foundIterators;

#ifdef _MSC_VER

                /* Usable in Mutable Client, no implementation would reasonably include the mutable client before
                 * or without the immutable one beforehand. (Design Based) */
                /* Call base, global implementation. Abstracts the 'is object const' requirement.
                 * Also use the MSVC dedicated manual-SFINAE wrapper due to the year being (almost)
                 * 2022 and they still can't deduce whether a function is enabled or not. */
                return __MSVC_FindThatWrapper < __IteratorType, __CollectionType, __Predicate > :: __findThat (
                        reinterpret_cast < __IterableType * > ( this )->begin(),
                        reinterpret_cast < __IterableType * > ( this )->end(),
                        count,
                        foundIterators,
                        predicate
                );

#else

                /* Call base, global implementation. Abstracts the 'is object const' requirement */
                return __findThat (
                        reinterpret_cast < __IterableType * > ( this )->begin(),
                        reinterpret_cast < __IterableType * > ( this )->end(),
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
            > __CDS_OptimalInline auto __FindByMutableCompositeClient <
                    __IterableType,
                    __ElementType,
                    __IteratorType
            > :: findFirstThat (
                    __Predicate const & predicate
            ) noexcept ( noexcept ( __PredicateExceptSpecTraits < __ElementType, __Predicate > :: __noexceptSpec ) ) -> Iterator {

#ifdef _MSC_VER

                /* Usable in Mutable Client, no implementation would reasonably include the mutable client before
                 * or without the immutable one beforehand. (Design Based) */
                /* Call base, global implementation. Abstracts the 'is object const' requirement.
                 * Also use the MSVC dedicated manual-SFINAE wrapper due to the year being
                 * 2022 and they still can't deduce whether a function is enabled or not. */
                return __MSVC_FindFirstThatWrapper < __IteratorType, __Predicate > :: __findFirstThat (
                        reinterpret_cast < __IterableType * > ( this )->begin(),
                        reinterpret_cast < __IterableType * > ( this )->end(),
                        predicate
                );

#else

                /* Call base, global implementation. Abstracts the 'is object const' requirement */
                return __findFirstThat (
                        reinterpret_cast < __IterableType * > ( this )->begin(),
                        reinterpret_cast < __IterableType * > ( this )->end(),
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
            > __CDS_OptimalInline auto __FindByMutableCompositeClient <
                    __IterableType,
                    __ElementType,
                    __IteratorType
            > :: findLastThat (
                    __Predicate const & predicate
            ) noexcept ( noexcept ( __PredicateExceptSpecTraits < __ElementType, __Predicate > :: __noexceptSpec ) ) -> Iterator {

#ifdef _MSC_VER

                /* Usable in Mutable Client, no implementation would reasonably include the mutable client before
                 * or without the immutable one beforehand. (Design Based) */
                /* Call base, global implementation. Abstracts the 'is object const' requirement.
                 * Also use the MSVC dedicated manual-SFINAE wrapper due to the year being
                 * 2022 and they still can't deduce whether a function is enabled or not. */
                return __MSVC_FindLastThatWrapper < __IteratorType, __Predicate > :: __findLastThat (
                        reinterpret_cast < __IterableType * > ( this )->begin(),
                        reinterpret_cast < __IterableType * > ( this )->end(),
                        predicate
                );

#else

                /* Call base, global implementation. Abstracts the 'is object const' requirement */
                return __findLastThat (
                        reinterpret_cast < __IterableType * > ( this )->begin(),
                        reinterpret_cast < __IterableType * > ( this )->end(),
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
            > __CDS_OptimalInline auto __FindByMutableCompositeClient <
                    __IterableType,
                    __ElementType,
                    __IteratorType
            > :: findAllThat (
                    __CollectionType < Iterator >             & storeIn,
                    __Predicate                         const & predicate
            ) noexcept ( noexcept ( __PredicateExceptSpecTraits < __ElementType, __Predicate > :: __noexceptSpec ) ) -> __CollectionType < Iterator > & {

#ifdef _MSC_VER

                /* Usable in Mutable Client, no implementation would reasonably include the mutable client before
                 * or without the immutable one beforehand. (Design Based) */
                /* Call base, global implementation. Abstracts the 'is object const' requirement.
                 * Also use the MSVC dedicated manual-SFINAE wrapper due to the year being
                 * 2022 and they still can't deduce whether a function is enabled or not. */
                return __MSVC_FindAllThatWrapper < __IteratorType, __Predicate > :: __findAllThat (
                        reinterpret_cast < __IterableType * > ( this )->begin(),
                        reinterpret_cast < __IterableType * > ( this )->end(),
                        storeIn,
                        predicate
                );

#else

                /* Call base, global implementation. Abstracts the 'is object const' requirement */
                return __findAllThat (
                        reinterpret_cast < __IterableType * > ( this )->begin(),
                        reinterpret_cast < __IterableType * > ( this )->end(),
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
            > __CDS_OptimalInline auto __FindByMutableCompositeClient <
                    __IterableType,
                    __ElementType,
                    __IteratorType
            > :: findAllThat (
                    __Predicate const & predicate
            ) noexcept ( noexcept ( __PredicateExceptSpecTraits < __ElementType, __Predicate > :: __noexceptSpec ) ) -> __CollectionType < Iterator > {

                __CollectionType < Iterator > foundIterators;

#ifdef _MSC_VER

                /* Usable in Mutable Client, no implementation would reasonably include the mutable client before
                 * or without the immutable one beforehand. (Design Based) */
                /* Call base, global implementation. Abstracts the 'is object const' requirement.
                 * Also use the MSVC dedicated manual-SFINAE wrapper due to the year being
                 * 2022 and they still can't deduce whether a function is enabled or not. */
                return __MSVC_FindAllThatWrapper < __IteratorType, __Predicate > :: __findAllThat (
                        reinterpret_cast < __IterableType * > ( this )->begin(),
                        reinterpret_cast < __IterableType * > ( this )->end(),
                        foundIterators,
                        predicate
                );

#else

                /* Call base, global implementation. Abstracts the 'is object const' requirement */
                return __findAllThat (
                        reinterpret_cast < __IterableType * > ( this )->begin(),
                        reinterpret_cast < __IterableType * > ( this )->end(),
                        foundIterators,
                        predicate
                );

#endif

            }

        } /* namespace __impl */
    } /* namespace __hidden */
} /* namespace cds */

#endif /* __CDS_SHARED_FIND_BY_MUTABLE_COMPOSITE_CLIENT_IMPL_HPP__ */
