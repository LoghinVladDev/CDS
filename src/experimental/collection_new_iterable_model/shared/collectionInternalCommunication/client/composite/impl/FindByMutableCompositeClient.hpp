/*
 * Created by loghin on 6/27/22.
 */

#ifndef __CDS_SHARED_FIND_BY_MUTABLE_COMPOSITE_CLIENT_IMPL_HPP__
#define __CDS_SHARED_FIND_BY_MUTABLE_COMPOSITE_CLIENT_IMPL_HPP__ /* NOLINT(bugprone-reserved-identifier) */

namespace cds {                 /* NOLINT(modernize-concat-nested-namespaces) */
    namespace experimental {    /* NOLINT(modernize-concat-nested-namespaces) */
        namespace __hidden {    /* NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier) */
            namespace __impl {  /* NOLINT(bugprone-reserved-identifier) */

                template <
                        typename                        __IterableType,     /* NOLINT(bugprone-reserved-identifier) */
                        typename                        __ElementType,      /* NOLINT(bugprone-reserved-identifier) */
                        typename                        __IteratorType      /* NOLINT(bugprone-reserved-identifier) */
                > template <
                        template < typename ... > class __CollectionType,   /* NOLINT(bugprone-reserved-identifier) */
                        typename                        __Predicate         /* NOLINT(bugprone-reserved-identifier) */
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

                    return __findThat (
                            reinterpret_cast < __IterableType * > ( this )->begin(),
                            reinterpret_cast < __IterableType * > ( this )->end(),
                            count,
                            storeIn,
                            predicate
                    );
                }


                template <
                        typename                        __IterableType,     /* NOLINT(bugprone-reserved-identifier) */
                        typename                        __ElementType,      /* NOLINT(bugprone-reserved-identifier) */
                        typename                        __IteratorType      /* NOLINT(bugprone-reserved-identifier) */
                > template <
                        template < typename ... > class __CollectionType,   /* NOLINT(bugprone-reserved-identifier) */
                        typename                        __Predicate         /* NOLINT(bugprone-reserved-identifier) */
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
                        typename                        __IterableType,     /* NOLINT(bugprone-reserved-identifier) */
                        typename                        __ElementType,      /* NOLINT(bugprone-reserved-identifier) */
                        typename                        __IteratorType      /* NOLINT(bugprone-reserved-identifier) */
                > template <
                        typename                        __Predicate         /* NOLINT(bugprone-reserved-identifier) */
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

                    return __findFirstThat (
                            reinterpret_cast < __IterableType * > ( this )->begin(),
                            reinterpret_cast < __IterableType * > ( this )->end(),
                            predicate
                    );
                }


                template <
                        typename                        __IterableType,     /* NOLINT(bugprone-reserved-identifier) */
                        typename                        __ElementType,      /* NOLINT(bugprone-reserved-identifier) */
                        typename                        __IteratorType      /* NOLINT(bugprone-reserved-identifier) */
                > template <
                        typename                        __Predicate         /* NOLINT(bugprone-reserved-identifier) */
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

                    return __findLastThat (
                            reinterpret_cast < __IterableType * > ( this )->begin(),
                            reinterpret_cast < __IterableType * > ( this )->end(),
                            predicate
                    );
                }


                template <
                        typename                        __IterableType,     /* NOLINT(bugprone-reserved-identifier) */
                        typename                        __ElementType,      /* NOLINT(bugprone-reserved-identifier) */
                        typename                        __IteratorType      /* NOLINT(bugprone-reserved-identifier) */
                > template <
                        template < typename ... > class __CollectionType,   /* NOLINT(bugprone-reserved-identifier) */
                        typename                        __Predicate         /* NOLINT(bugprone-reserved-identifier) */
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

                    return __findAllThat (
                            reinterpret_cast < __IterableType * > ( this )->begin(),
                            reinterpret_cast < __IterableType * > ( this )->end(),
                            storeIn,
                            predicate
                    );
                }


                template <
                        typename                        __IterableType,     /* NOLINT(bugprone-reserved-identifier) */
                        typename                        __ElementType,      /* NOLINT(bugprone-reserved-identifier) */
                        typename                        __IteratorType      /* NOLINT(bugprone-reserved-identifier) */
                > template <
                        template < typename ... > class __CollectionType,   /* NOLINT(bugprone-reserved-identifier) */
                        typename                        __Predicate         /* NOLINT(bugprone-reserved-identifier) */
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

                    __CollectionType < Iterator > foundIterators;
                    return __findAllThat (
                            reinterpret_cast < __IterableType * > ( this )->begin(),
                            reinterpret_cast < __IterableType * > ( this )->end(),
                            foundIterators,
                            predicate
                    );
                }

            }
        }
    }
}

#endif /* __CDS_SHARED_FIND_BY_MUTABLE_COMPOSITE_CLIENT_IMPL_HPP__ */
