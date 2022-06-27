//
// Created by loghin on 6/27/22.
//

#ifndef __CDS_SHARED_ITERABLE_MUTABLE_FIND_BY_PREDICATE_IMPL_HPP__
#define __CDS_SHARED_ITERABLE_MUTABLE_FIND_BY_PREDICATE_IMPL_HPP__

namespace cds {                 // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {    // NOLINT(modernize-concat-nested-namespaces)
        namespace __hidden {    // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier)
            namespace __impl {  // NOLINT(bugprone-reserved-identifier)

                template <
                        typename                        __IterableType,     // NOLINT(bugprone-reserved-identifier)
                        typename                        __ElementType,      // NOLINT(bugprone-reserved-identifier)
                        typename                        __IteratorType      // NOLINT(bugprone-reserved-identifier)
                > template <
                        template < typename ... > class __CollectionType,   // NOLINT(bugprone-reserved-identifier)
                        typename                        __Predicate         // NOLINT(bugprone-reserved-identifier)
                > __CDS_OptimalInline auto __IterableMutableFindByPredicate <
                        __IterableType,
                        __ElementType,
                        __IteratorType
                > :: findThat (
                        Size                                        count,
                        __CollectionType < Iterator >             & storeIn,
                        __Predicate                         const & predicate
                ) noexcept ( noexcept ( predicate ( cds :: meta :: referenceOf < __ElementType > () ) ) ) -> __CollectionType < Iterator > & {

                    return __findThat (
                            static_cast < __IterableType * > ( this )->begin(),
                            static_cast < __IterableType * > ( this )->end(),
                            count,
                            storeIn,
                            predicate
                    );
                }


                template <
                        typename                        __IterableType,     // NOLINT(bugprone-reserved-identifier)
                        typename                        __ElementType,      // NOLINT(bugprone-reserved-identifier)
                        typename                        __IteratorType      // NOLINT(bugprone-reserved-identifier)
                > template <
                        template < typename ... > class __CollectionType,   // NOLINT(bugprone-reserved-identifier)
                        typename                        __Predicate         // NOLINT(bugprone-reserved-identifier)
                > __CDS_OptimalInline auto __IterableMutableFindByPredicate <
                        __IterableType,
                        __ElementType,
                        __IteratorType
                > :: findThat (
                        Size                count,
                        __Predicate const & predicate
                ) noexcept ( noexcept ( predicate ( cds :: meta :: referenceOf < __ElementType > () ) ) ) -> __CollectionType < Iterator > {

                    return __findThat (
                            static_cast < __IterableType * > ( this )->begin(),
                            static_cast < __IterableType * > ( this )->end(),
                            count,
                            predicate
                    );
                }


                template <
                        typename                        __IterableType,     // NOLINT(bugprone-reserved-identifier)
                        typename                        __ElementType,      // NOLINT(bugprone-reserved-identifier)
                        typename                        __IteratorType      // NOLINT(bugprone-reserved-identifier)
                > template <
                        typename                        __Predicate         // NOLINT(bugprone-reserved-identifier)
                > __CDS_OptimalInline auto __IterableMutableFindByPredicate <
                        __IterableType,
                        __ElementType,
                        __IteratorType
                > :: findFirstThat (
                        __Predicate const & predicate
                ) noexcept ( noexcept ( predicate ( cds :: meta :: referenceOf < __ElementType > () ) ) ) -> Iterator {

                    return __findFirstThat (
                            static_cast < __IterableType * > ( this )->begin(),
                            static_cast < __IterableType * > ( this )->end(),
                            predicate
                    );
                }


                template <
                        typename                        __IterableType,     // NOLINT(bugprone-reserved-identifier)
                        typename                        __ElementType,      // NOLINT(bugprone-reserved-identifier)
                        typename                        __IteratorType      // NOLINT(bugprone-reserved-identifier)
                > template <
                        typename                        __Predicate         // NOLINT(bugprone-reserved-identifier)
                > __CDS_OptimalInline auto __IterableMutableFindByPredicate <
                        __IterableType,
                        __ElementType,
                        __IteratorType
                > :: findLastThat (
                        __Predicate const & predicate
                ) noexcept ( noexcept ( predicate ( cds :: meta :: referenceOf < __ElementType > () ) ) ) -> Iterator {

                    return __findLastThat (
                            static_cast < __IterableType * > ( this )->begin(),
                            static_cast < __IterableType * > ( this )->end(),
                            predicate
                    );
                }


                template <
                        typename                        __IterableType,     // NOLINT(bugprone-reserved-identifier)
                        typename                        __ElementType,      // NOLINT(bugprone-reserved-identifier)
                        typename                        __IteratorType      // NOLINT(bugprone-reserved-identifier)
                > template <
                        template < typename ... > class __CollectionType,   // NOLINT(bugprone-reserved-identifier)
                        typename                        __Predicate         // NOLINT(bugprone-reserved-identifier)
                > __CDS_OptimalInline auto __IterableMutableFindByPredicate <
                        __IterableType,
                        __ElementType,
                        __IteratorType
                > :: findAllThat (
                        __CollectionType < Iterator >             & storeIn,
                        __Predicate                         const & predicate
                ) noexcept ( noexcept ( predicate ( cds :: meta :: referenceOf < __ElementType > () ) ) ) -> __CollectionType < Iterator > & {

                    return __findAllThat (
                            static_cast < __IterableType * > ( this )->begin(),
                            static_cast < __IterableType * > ( this )->end(),
                            storeIn,
                            predicate
                    );
                }


                template <
                        typename                        __IterableType,     // NOLINT(bugprone-reserved-identifier)
                        typename                        __ElementType,      // NOLINT(bugprone-reserved-identifier)
                        typename                        __IteratorType      // NOLINT(bugprone-reserved-identifier)
                > template <
                        template < typename ... > class __CollectionType,   // NOLINT(bugprone-reserved-identifier)
                        typename                        __Predicate         // NOLINT(bugprone-reserved-identifier)
                > __CDS_OptimalInline auto __IterableMutableFindByPredicate <
                        __IterableType,
                        __ElementType,
                        __IteratorType
                > :: findAllThat (
                        __Predicate const & predicate
                ) noexcept ( noexcept ( predicate ( cds :: meta :: referenceOf < __ElementType > () ) ) ) -> __CollectionType < Iterator > {

                    return __findAllThat (
                            static_cast < __IterableType * > ( this )->begin(),
                            static_cast < __IterableType * > ( this )->end(),
                            predicate
                    );
                }

            }
        }
    }
}

#endif // __CDS_SHARED_ITERABLE_MUTABLE_FIND_BY_PREDICATE_IMPL_HPP__
