/*
 * Created by loghin on 6/30/22.
 */

#ifndef __CDS_SHARED_INDICES_BY_COMPOSITE_CLIENT_HPP__
#define __CDS_SHARED_INDICES_BY_COMPOSITE_CLIENT_HPP__ /* NOLINT(bugprone-reserved-identifier) */

namespace cds {             /* NOLINT(modernize-concat-nested-namespaces) */
    namespace __hidden {    /* NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier) */
        namespace __impl {  /* NOLINT(bugprone-reserved-identifier) */

            template <
                    typename __ReceiverType,        /* NOLINT(bugprone-reserved-identifier) */
                    typename __ElementType          /* NOLINT(bugprone-reserved-identifier) */
            > class __IndicesByCompositeClient {    /* NOLINT(bugprone-reserved-identifier) */

            private:
                using ElementType = __ElementType;

            public:
                template <
                        typename __CollectionType,  /* NOLINT(bugprone-reserved-identifier) */
                        typename __Predicate        /* NOLINT(bugprone-reserved-identifier) */
                > auto indicesOfThat (
                        Size                        count,
                        __CollectionType          & storeIn,
                        __Predicate         const & predicate
                ) const noexcept ( noexcept ( predicate ( cds :: meta :: referenceOf < ElementType const > () ) ) ) -> __CollectionType &;

            public:
                template <
                        template < typename ... > class __CollectionType,   /* NOLINT(bugprone-reserved-identifier) */
                        typename __Predicate                                /* NOLINT(bugprone-reserved-identifier) */
                > __CDS_NoDiscard auto indicesOfThat (
                        Size                count,
                        __Predicate const & predicate
                ) const noexcept ( noexcept ( predicate ( cds :: meta :: referenceOf < ElementType const > () ) ) ) -> __CollectionType < Index >;

            public:
                template < typename __Predicate >   /* NOLINT(bugprone-reserved-identifier) */
                __CDS_NoDiscard auto firstIndexOfThat (
                        __Predicate const & predicate
                ) const noexcept ( noexcept ( predicate ( cds :: meta :: referenceOf < ElementType const > () ) ) ) -> Index;

            public:
                template < typename __Predicate >   /* NOLINT(bugprone-reserved-identifier) */
                __CDS_NoDiscard auto lastIndexOfThat (
                        __Predicate const & predicate
                ) const noexcept ( noexcept ( predicate ( cds :: meta :: referenceOf < ElementType const > () ) ) ) -> Index;

            public:
                template <
                        typename __CollectionType,  /* NOLINT(bugprone-reserved-identifier) */
                        typename __Predicate        /* NOLINT(bugprone-reserved-identifier) */
                > auto allIndicesOfThat (
                        __CollectionType          & storeIn,
                        __Predicate         const & predicate
                ) const noexcept ( noexcept ( predicate ( cds :: meta :: referenceOf < ElementType const > () ) ) ) -> __CollectionType &;

            public:
                template <
                        template < typename ... > class __CollectionType,   /* NOLINT(bugprone-reserved-identifier) */
                        typename                        __Predicate         /* NOLINT(bugprone-reserved-identifier) */
                > __CDS_NoDiscard auto allIndicesOfThat (
                        __Predicate const & predicate
                ) const noexcept ( noexcept ( predicate ( cds :: meta :: referenceOf < ElementType const > () ) ) ) -> __CollectionType < Index >;
            };


            template <
                    typename __ReceiverType,            /* NOLINT(bugprone-reserved-identifier) */
                    typename __ElementType              /* NOLINT(bugprone-reserved-identifier) */
            > using __LocalIndicesByCompositeClient =   /* NOLINT(bugprone-reserved-identifier) */
                    __IndicesByCompositeClient <
                            __ReceiverType,
                            __ElementType
                    >;

        }
    }
}

#endif /* __CDS_SHARED_INDICES_BY_COMPOSITE_CLIENT_HPP__ */
