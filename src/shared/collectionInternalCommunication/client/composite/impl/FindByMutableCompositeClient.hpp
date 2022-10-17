/*
 * Created by loghin on 6/27/22.
 */

#ifndef __CDS_SHARED_FIND_BY_MUTABLE_COMPOSITE_CLIENT_IMPL_HPP__ /* NOLINT(llvm-header-guard) */
#define __CDS_SHARED_FIND_BY_MUTABLE_COMPOSITE_CLIENT_IMPL_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

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
            ) noexcept ( noexcept ( __findThat (
                    cds :: meta :: addressOf < __IterableType > ()->begin(),
                    cds :: meta :: addressOf < __IterableType > ()->end(),
                    count,
                    storeIn,
                    predicate
            ) ) ) -> __CollectionType < Iterator > & {

                /* Call base, global implementation. Abstracts the 'is object const' requirement */
                return __findThat (
                        reinterpret_cast < __IterableType * > ( this )->begin(),
                        reinterpret_cast < __IterableType * > ( this )->end(),
                        count,
                        storeIn,
                        predicate
                );
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
            ) noexcept ( noexcept ( __findThat (
                    cds :: meta :: addressOf < __IterableType > ()->begin(),
                    cds :: meta :: addressOf < __IterableType > ()->end(),
                    count,
                    cds :: meta :: referenceOf < __CollectionType < Iterator > > (),
                    predicate
            ) ) ) -> __CollectionType < Iterator > {

                /* Call base, global implementation. Abstracts the 'is object const' requirement */
                __CollectionType < Iterator > foundIterators;
                return __findThat (
                        reinterpret_cast < __IterableType * > ( this )->begin(),
                        reinterpret_cast < __IterableType * > ( this )->end(),
                        count,
                        foundIterators,
                        predicate
                );
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
            ) noexcept ( noexcept ( __findFirstThat (
                    cds :: meta :: addressOf < __IterableType > ()->begin(),
                    cds :: meta :: addressOf < __IterableType > ()->end(),
                    predicate
            ) ) ) -> Iterator {

                /* Call base, global implementation. Abstracts the 'is object const' requirement */
                return __findFirstThat (
                        reinterpret_cast < __IterableType * > ( this )->begin(),
                        reinterpret_cast < __IterableType * > ( this )->end(),
                        predicate
                );
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
            ) noexcept ( noexcept ( __findLastThat (
                    cds :: meta :: addressOf < __IterableType > ()->begin(),
                    cds :: meta :: addressOf < __IterableType > ()->end(),
                    predicate
            ) ) ) -> Iterator {

                /* Call base, global implementation. Abstracts the 'is object const' requirement */
                return __findLastThat (
                        reinterpret_cast < __IterableType * > ( this )->begin(),
                        reinterpret_cast < __IterableType * > ( this )->end(),
                        predicate
                );
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
            ) noexcept ( noexcept ( __findAllThat (
                    cds :: meta :: addressOf < __IterableType > ()->begin(),
                    cds :: meta :: addressOf < __IterableType > ()->end(),
                    storeIn,
                    predicate
            ) ) ) -> __CollectionType < Iterator > & {

                /* Call base, global implementation. Abstracts the 'is object const' requirement */
                return __findAllThat (
                        reinterpret_cast < __IterableType * > ( this )->begin(),
                        reinterpret_cast < __IterableType * > ( this )->end(),
                        storeIn,
                        predicate
                );
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
            ) noexcept ( noexcept ( __findAllThat (
                    cds :: meta :: addressOf < __IterableType > ()->begin(),
                    cds :: meta :: addressOf < __IterableType > ()->end(),
                    cds :: meta :: referenceOf < __CollectionType < Iterator > > (),
                    predicate
            ) ) ) -> __CollectionType < Iterator > {

                /* Call base, global implementation. Abstracts the 'is object const' requirement */
                __CollectionType < Iterator > foundIterators;
                return __findAllThat (
                        reinterpret_cast < __IterableType * > ( this )->begin(),
                        reinterpret_cast < __IterableType * > ( this )->end(),
                        foundIterators,
                        predicate
                );
            }

        } /* namespace __impl */
    } /* namespace __hidden */
} /* namespace cds */

#endif /* __CDS_SHARED_FIND_BY_MUTABLE_COMPOSITE_CLIENT_IMPL_HPP__ */
