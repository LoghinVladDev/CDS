/*
 * Created by loghin on 6/27/22.
 */

#ifndef __CDS_SHARED_FIND_BY_MUTABLE_COMPOSITE_CLIENT_HPP__
#define __CDS_SHARED_FIND_BY_MUTABLE_COMPOSITE_CLIENT_HPP__ /* NOLINT(bugprone-reserved-identifier) */

#include "../../../iterator/IteratorFindStatements.hpp"

namespace cds {                 /* NOLINT(modernize-concat-nested-namespaces) */
    namespace experimental {    /* NOLINT(modernize-concat-nested-namespaces) */
        namespace __hidden {    /* NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier) */
            namespace __impl {  /* NOLINT(bugprone-reserved-identifier) */

                template <
                        typename __IterableType,                /* NOLINT(bugprone-reserved-identifier) */
                        typename __ElementType,                 /* NOLINT(bugprone-reserved-identifier) */
                        typename __IteratorType                 /* NOLINT(bugprone-reserved-identifier) */
                > class __FindByMutableCompositeClient {        /* NOLINT(bugprone-reserved-identifier) */

                private:
                    using Iterator = __IteratorType;

                public:
                    template <
                            template < typename ... > class __CollectionType,   /* NOLINT(bugprone-reserved-identifier) */
                            typename                        __Predicate         /* NOLINT(bugprone-reserved-identifier) */
                    > auto findThat (
                            Size                                        count,
                            __CollectionType < Iterator >             & storeIn,
                            __Predicate                         const & predicate
                    ) noexcept ( noexcept ( __findThat (
                            cds :: meta :: addressOf < __IterableType > ()->begin(),
                            cds :: meta :: addressOf < __IterableType > ()->end(),
                            count,
                            storeIn,
                            predicate
                    ) ) ) -> __CollectionType < Iterator > &;

                public:
                    template <
                            template < typename ... > class __CollectionType,   /* NOLINT(bugprone-reserved-identifier) */
                            typename                        __Predicate         /* NOLINT(bugprone-reserved-identifier) */
                    > __CDS_NoDiscard auto findThat (
                            Size count,
                            __Predicate const & predicate
                    ) noexcept ( noexcept ( __findThat (
                            cds :: meta :: addressOf < __IterableType > ()->begin(),
                            cds :: meta :: addressOf < __IterableType > ()->end(),
                            count,
                            cds :: meta :: referenceOf < __CollectionType < Iterator > > (),
                            predicate
                    ) ) ) -> __CollectionType < Iterator >;

                public:
                    template < typename __Predicate > /* NOLINT(bugprone-reserved-identifier) */
                    __CDS_NoDiscard auto findFirstThat (
                            __Predicate const & predicate
                    ) noexcept ( noexcept ( __findFirstThat (
                            cds :: meta :: addressOf < __IterableType > ()->begin(),
                            cds :: meta :: addressOf < __IterableType > ()->end(),
                            predicate
                    ) ) ) -> Iterator;

                public:
                    template < typename __Predicate > /* NOLINT(bugprone-reserved-identifier) */
                    __CDS_NoDiscard auto findLastThat (
                            __Predicate const & predicate
                    ) noexcept ( noexcept ( __findLastThat (
                            cds :: meta :: addressOf < __IterableType > ()->begin(),
                            cds :: meta :: addressOf < __IterableType > ()->end(),
                            predicate
                    ) ) ) -> Iterator;

                public:
                    template <
                            template < typename ... > class __CollectionType,   /* NOLINT(bugprone-reserved-identifier) */
                            typename                        __Predicate         /* NOLINT(bugprone-reserved-identifier) */
                    > auto findAllThat (
                            __CollectionType < Iterator >             & storeIn,
                            __Predicate                         const & predicate
                    ) noexcept ( noexcept ( __findAllThat (
                            cds :: meta :: addressOf < __IterableType > ()->begin(),
                            cds :: meta :: addressOf < __IterableType > ()->end(),
                            storeIn,
                            predicate
                    ) ) ) -> __CollectionType < Iterator > &;

                public:
                    template <
                            template < typename ... > class __CollectionType,   /* NOLINT(bugprone-reserved-identifier) */
                            typename                        __Predicate         /* NOLINT(bugprone-reserved-identifier) */
                    > __CDS_NoDiscard auto findAllThat (
                            __Predicate const & predicate
                    ) noexcept ( noexcept ( __findAllThat (
                            cds :: meta :: addressOf < __IterableType > ()->begin(),
                            cds :: meta :: addressOf < __IterableType > ()->end(),
                            cds :: meta :: referenceOf < __CollectionType < Iterator > > (),
                            predicate
                    ) ) ) -> __CollectionType < Iterator >;

                };


                template <
                        typename __IterableType,                /* NOLINT(bugprone-reserved-identifier) */
                        typename __ElementType,                 /* NOLINT(bugprone-reserved-identifier) */
                        typename __IteratorType                 /* NOLINT(bugprone-reserved-identifier) */
                > using __LocalFindByMutableCompositeClient =   /* NOLINT(bugprone-reserved-identifier) */
                        __FindByMutableCompositeClient <
                                __IterableType,
                                __ElementType,
                                __IteratorType
                        >;

            }
        }
    }
}

#include "../../../iterator/impl/IteratorFindStatements.hpp"

#endif /* __CDS_SHARED_FIND_BY_MUTABLE_COMPOSITE_CLIENT_HPP__ */
