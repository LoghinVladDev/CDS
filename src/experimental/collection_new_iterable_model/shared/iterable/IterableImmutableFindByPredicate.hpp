//
// Created by loghin on 6/27/22.
//

#ifndef __CDS_SHARED_ITERABLE_IMMUTABLE_FIND_BY_PREDICATE_HPP__
#define __CDS_SHARED_ITERABLE_IMMUTABLE_FIND_BY_PREDICATE_HPP__

#include "../iterator/IteratorFindStatements.hpp"

namespace cds {                 // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {    // NOLINT(modernize-concat-nested-namespaces)
        namespace __hidden {    // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier)
            namespace __impl {  // NOLINT(bugprone-reserved-identifier)

                template <
                        typename __IterableType,                // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType,                 // NOLINT(bugprone-reserved-identifier)
                        typename __IteratorType                 // NOLINT(bugprone-reserved-identifier)
                > class __IterableImmutableFindByPredicate {    // NOLINT(bugprone-reserved-identifier)

                private:
                    using ConstIterator = __IteratorType;

                protected:
                    template <
                            template < typename ... > class __CollectionType,   // NOLINT(bugprone-reserved-identifier)
                            typename                        __Predicate         // NOLINT(bugprone-reserved-identifier)
                    > auto findThat (
                            Size                                        count,
                            __CollectionType < ConstIterator >        & storeIn,
                            __Predicate                         const & predicate
                    ) const noexcept ( noexcept ( predicate ( cds :: meta :: referenceOf < __ElementType const > () ) ) ) -> __CollectionType < ConstIterator > &;

                protected:
                    template <
                            template < typename ... > class __CollectionType,   // NOLINT(bugprone-reserved-identifier)
                            typename                        __Predicate         // NOLINT(bugprone-reserved-identifier)
                    > __CDS_NoDiscard auto findThat (
                            Size count,
                            __Predicate const & predicate
                    ) const noexcept ( noexcept ( predicate ( cds :: meta :: referenceOf < __ElementType const > () ) ) ) -> __CollectionType < ConstIterator >;

                protected:
                    template <
                            typename                        __Predicate         // NOLINT(bugprone-reserved-identifier)
                    > __CDS_NoDiscard auto findFirstThat (
                            __Predicate const & predicate
                    ) const noexcept ( noexcept ( predicate ( cds :: meta :: referenceOf < __ElementType const > () ) ) ) -> ConstIterator;

                protected:
                    template <
                            typename                        __Predicate         // NOLINT(bugprone-reserved-identifier)
                    > __CDS_NoDiscard auto findLastThat (
                            __Predicate const & predicate
                    ) const noexcept ( noexcept ( predicate ( cds :: meta :: referenceOf < __ElementType const > () ) ) ) -> ConstIterator;

                protected:
                    template <
                            template < typename ... > class __CollectionType,   // NOLINT(bugprone-reserved-identifier)
                            typename                        __Predicate         // NOLINT(bugprone-reserved-identifier)
                    > auto findAllThat (
                            __CollectionType < ConstIterator >        & storeIn,
                            __Predicate                         const & predicate
                    ) const noexcept ( noexcept ( predicate ( cds :: meta :: referenceOf < __ElementType const > () ) ) ) -> __CollectionType < ConstIterator > &;

                protected:
                    template <
                            template < typename ... > class __CollectionType,   // NOLINT(bugprone-reserved-identifier)
                            typename                        __Predicate         // NOLINT(bugprone-reserved-identifier)
                    > __CDS_NoDiscard auto findAllThat (
                            __Predicate const & predicate
                    ) const noexcept ( noexcept ( predicate ( cds :: meta :: referenceOf < __ElementType const > () ) ) ) -> __CollectionType < ConstIterator >;

                };

            }
        }
    }
}

#include "../iterator/impl/IteratorFindStatements.hpp"

#endif //__CDS_SHARED_ITERABLE_IMMUTABLE_FIND_BY_PREDICATE_HPP__
