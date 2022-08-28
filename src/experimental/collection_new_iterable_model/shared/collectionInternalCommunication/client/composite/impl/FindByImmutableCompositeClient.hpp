/*
 * Created by loghin on 6/27/22.
 */

#ifndef __CDS_SHARED_FIND_BY_IMMUTABLE_COMPOSITE_CLIENT_IMPL_HPP__
#define __CDS_SHARED_FIND_BY_IMMUTABLE_COMPOSITE_CLIENT_IMPL_HPP__ /* NOLINT(bugprone-reserved-identifier) */

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
                > __CDS_OptimalInline auto __FindByImmutableCompositeClient <
                        __IterableType,
                        __ElementType,
                        __IteratorType
                > :: findThat (
                        Size                                        count,
                        __CollectionType < ConstIterator >        & storeIn,
                        __Predicate                         const & predicate
                ) const noexcept ( noexcept ( __findThat (
                        cds :: meta :: addressOf < __IterableType const > ()->cbegin(),
                        cds :: meta :: addressOf < __IterableType const > ()->cend(),
                        count,
                        storeIn,
                        predicate
                ) ) ) -> __CollectionType < ConstIterator > & {

                    return __findThat (
                            reinterpret_cast < __IterableType const * > ( this )->cbegin(),
                            reinterpret_cast < __IterableType const * > ( this )->cend(),
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
                > __CDS_OptimalInline auto __FindByImmutableCompositeClient <
                        __IterableType,
                        __ElementType,
                        __IteratorType
                > :: findThat (
                        Size                count,
                        __Predicate const & predicate
                ) const noexcept ( noexcept ( __findThat (
                        cds :: meta :: addressOf < __IterableType const > ()->cbegin(),
                        cds :: meta :: addressOf < __IterableType const > ()->cend(),
                        count,
                        cds :: meta :: referenceOf < __CollectionType < ConstIterator > > (),
                        predicate
                ) ) ) -> __CollectionType < ConstIterator > {

                    __CollectionType < ConstIterator > foundIterators;
                    return __findThat (
                            reinterpret_cast < __IterableType const * > ( this )->cbegin(),
                            reinterpret_cast < __IterableType const * > ( this )->cend(),
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
                > __CDS_OptimalInline auto __FindByImmutableCompositeClient <
                        __IterableType,
                        __ElementType,
                        __IteratorType
                > :: findFirstThat (
                        __Predicate const & predicate
                ) const noexcept ( noexcept ( __findFirstThat (
                        cds :: meta :: addressOf < __IterableType const > ()->cbegin(),
                        cds :: meta :: addressOf < __IterableType const > ()->cend(),
                        predicate
                ) ) ) -> ConstIterator {

                    return __findFirstThat (
                            reinterpret_cast < __IterableType const * > ( this )->cbegin(),
                            reinterpret_cast < __IterableType const * > ( this )->cend(),
                            predicate
                    );
                }


                template <
                        typename                        __IterableType,     /* NOLINT(bugprone-reserved-identifier) */
                        typename                        __ElementType,      /* NOLINT(bugprone-reserved-identifier) */
                        typename                        __IteratorType      /* NOLINT(bugprone-reserved-identifier) */
                > template <
                        typename                        __Predicate         /* NOLINT(bugprone-reserved-identifier) */
                > __CDS_OptimalInline auto __FindByImmutableCompositeClient <
                        __IterableType,
                        __ElementType,
                        __IteratorType
                > :: findLastThat (
                        __Predicate const & predicate
                ) const noexcept ( noexcept ( __findLastThat (
                        cds :: meta :: addressOf < __IterableType const > ()->cbegin(),
                        cds :: meta :: addressOf < __IterableType const > ()->cend(),
                        predicate
                ) ) ) -> ConstIterator {

                    return __findLastThat (
                            reinterpret_cast < __IterableType const * > ( this )->cbegin(),
                            reinterpret_cast < __IterableType const * > ( this )->cend(),
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
                > __CDS_OptimalInline auto __FindByImmutableCompositeClient <
                        __IterableType,
                        __ElementType,
                        __IteratorType
                > :: findAllThat (
                        __CollectionType < ConstIterator >        & storeIn,
                        __Predicate                         const & predicate
                ) const noexcept ( noexcept ( __findAllThat (
                        cds :: meta :: addressOf < __IterableType const > ()->cbegin(),
                        cds :: meta :: addressOf < __IterableType const > ()->cend(),
                        storeIn,
                        predicate
                ) ) ) -> __CollectionType < ConstIterator > & {

                    return __findAllThat (
                            reinterpret_cast < __IterableType const * > ( this )->cbegin(),
                            reinterpret_cast < __IterableType const * > ( this )->cend(),
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
                > __CDS_OptimalInline auto __FindByImmutableCompositeClient <
                        __IterableType,
                        __ElementType,
                        __IteratorType
                > :: findAllThat (
                        __Predicate const & predicate
                ) const noexcept ( noexcept ( __findAllThat (
                        cds :: meta :: addressOf < __IterableType const > ()->cbegin(),
                        cds :: meta :: addressOf < __IterableType const > ()->cend(),
                        cds :: meta :: referenceOf < __CollectionType < ConstIterator > > (),
                        predicate
                ) ) ) -> __CollectionType < ConstIterator > {

                    __CollectionType < ConstIterator > foundIterators;
                    return __findAllThat (
                            reinterpret_cast < __IterableType const * > ( this )->cbegin(),
                            reinterpret_cast < __IterableType const * > ( this )->cend(),
                            foundIterators,
                            predicate
                    );
                }

            }
        }
    }
}

#endif /* __CDS_SHARED_FIND_BY_IMMUTABLE_COMPOSITE_CLIENT_IMPL_HPP__ */
