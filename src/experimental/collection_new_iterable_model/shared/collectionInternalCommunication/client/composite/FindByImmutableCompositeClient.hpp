/*
 * Created by loghin on 6/27/22.
 */

#ifndef __CDS_SHARED_FIND_BY_IMMUTABLE_COMPOSITE_CLIENT_HPP__
#define __CDS_SHARED_FIND_BY_IMMUTABLE_COMPOSITE_CLIENT_HPP__ /* NOLINT(bugprone-reserved-identifier) */

#include "../../../iterator/IteratorFindStatements.hpp"
#include "../../../iterator/IteratorFindMemberStatements.hpp"

namespace cds {                 /* NOLINT(modernize-concat-nested-namespaces) */
    namespace experimental {    /* NOLINT(modernize-concat-nested-namespaces) */
        namespace __hidden {    /* NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier) */
            namespace __impl {  /* NOLINT(bugprone-reserved-identifier) */

                template <
                        typename __IterableType,                /* NOLINT(bugprone-reserved-identifier) */
                        typename __ElementType,                 /* NOLINT(bugprone-reserved-identifier) */
                        typename __IteratorType                 /* NOLINT(bugprone-reserved-identifier) */
                > class __FindByImmutableCompositeClient {      /* NOLINT(bugprone-reserved-identifier) */

                private:
                    using ConstIterator = __IteratorType;

                public:
                    template <
                            template < typename ... > class __CollectionType,   /* NOLINT(bugprone-reserved-identifier) */
                            typename                        __Predicate         /* NOLINT(bugprone-reserved-identifier) */
                    > auto findThat (
                            Size                                        count,
                            __CollectionType < ConstIterator >        & storeIn,
                            __Predicate                         const & predicate
                    ) const noexcept ( noexcept ( __findThat (
                            cds :: meta :: addressOf < __IterableType const > ()->cbegin(),
                            cds :: meta :: addressOf < __IterableType const > ()->cend(),
                            count,
                            storeIn,
                            predicate
                    ) ) ) -> __CollectionType < ConstIterator > &;

                public:
                    template <
                            template < typename ... > class __CollectionType,   /* NOLINT(bugprone-reserved-identifier) */
                            typename                        __Predicate         /* NOLINT(bugprone-reserved-identifier) */
                    > __CDS_NoDiscard auto findThat (
                            Size count,
                            __Predicate const & predicate
                    ) const noexcept ( noexcept ( __findThat (
                            cds :: meta :: addressOf < __IterableType const > ()->cbegin(),
                            cds :: meta :: addressOf < __IterableType const > ()->cend(),
                            count,
                            cds :: meta :: referenceOf < __CollectionType < ConstIterator > > (),
                            predicate
                    ) ) ) -> __CollectionType < ConstIterator >;

                public:
                    template < typename __Predicate > /* NOLINT(bugprone-reserved-identifier) */
                    __CDS_NoDiscard auto findFirstThat (
                            __Predicate const & predicate
                    ) const noexcept ( noexcept ( __findFirstThat (
                            cds :: meta :: addressOf < __IterableType const > ()->cbegin(),
                            cds :: meta :: addressOf < __IterableType const > ()->cend(),
                            predicate
                    ) ) ) -> ConstIterator;

                public:
                    template < typename __Predicate > /* NOLINT(bugprone-reserved-identifier) */
                    __CDS_NoDiscard auto findLastThat (
                            __Predicate const & predicate
                    ) const noexcept ( noexcept ( __findLastThat (
                            cds :: meta :: addressOf < __IterableType const > ()->cbegin(),
                            cds :: meta :: addressOf < __IterableType const > ()->cend(),
                            predicate
                    ) ) ) -> ConstIterator;

                public:
                    template <
                            template < typename ... > class __CollectionType,   /* NOLINT(bugprone-reserved-identifier) */
                            typename                        __Predicate         /* NOLINT(bugprone-reserved-identifier) */
                    > auto findAllThat (
                            __CollectionType < ConstIterator >        & storeIn,
                            __Predicate                         const & predicate
                    ) const noexcept ( noexcept ( __findAllThat (
                            cds :: meta :: addressOf < __IterableType const > ()->cbegin(),
                            cds :: meta :: addressOf < __IterableType const > ()->cend(),
                            storeIn,
                            predicate
                    ) ) ) -> __CollectionType < ConstIterator > &;

                public:
                    template <
                            template < typename ... > class __CollectionType,   /* NOLINT(bugprone-reserved-identifier) */
                            typename                        __Predicate         /* NOLINT(bugprone-reserved-identifier) */
                    > __CDS_NoDiscard auto findAllThat (
                            __Predicate const & predicate
                    ) const noexcept ( noexcept ( __findAllThat (
                            cds :: meta :: addressOf < __IterableType const > ()->cbegin(),
                            cds :: meta :: addressOf < __IterableType const > ()->cend(),
                            cds :: meta :: referenceOf < __CollectionType < ConstIterator > > (),
                            predicate
                    ) ) ) -> __CollectionType < ConstIterator >;

                };


                template <
                        typename __IterableType,                /* NOLINT(bugprone-reserved-identifier) */
                        typename __ElementType,                 /* NOLINT(bugprone-reserved-identifier) */
                        typename __IteratorType                 /* NOLINT(bugprone-reserved-identifier) */
                > using __LocalFindByImmutableCompositeClient = /* NOLINT(bugprone-reserved-identifier) */
                        __FindByImmutableCompositeClient <
                                __IterableType,
                                __ElementType,
                                __IteratorType
                        >;

            }
        }
    }
}

#include "../../../iterator/impl/IteratorFindStatements.hpp"
#include "../../../iterator/impl/IteratorFindMemberStatements.hpp"

#endif /* __CDS_SHARED_FIND_BY_IMMUTABLE_COMPOSITE_CLIENT_HPP__ */
