/*
 * Created by loghin on 6/30/22.
 */

#ifndef __CDS_SHARED_INDICES_OF_COMPOSITE_CLIENT_HPP__
#define __CDS_SHARED_INDICES_OF_COMPOSITE_CLIENT_HPP__ /* NOLINT(bugprone-reserved-identifier) */

namespace cds {             /* NOLINT(modernize-concat-nested-namespaces) */
    namespace __hidden {    /* NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier) */
        namespace __impl {  /* NOLINT(bugprone-reserved-identifier) */

            template <
                    typename                                                    __ReceiverType,         /* NOLINT(bugprone-reserved-identifier) */
                    typename                                                    __ElementType,          /* NOLINT(bugprone-reserved-identifier) */
                    typename                                                    __FromCollectionType,   /* NOLINT(bugprone-reserved-identifier) */
                    __ContainsFunction < __FromCollectionType, __ElementType >  __contains              /* NOLINT(bugprone-reserved-identifier) */
            > class __IndicesOfCompositeClient {                                                        /* NOLINT(bugprone-reserved-identifier) */

            private:
                using ElementType = __ElementType;

            public:
                template < typename __CollectionType >  /* NOLINT(bugprone-reserved-identifier) */
                auto indicesOfFrom (
                        Size                            count,
                        __CollectionType              & storeIn,
                        __FromCollectionType    const & from
                ) const noexcept -> __CollectionType &;

            public:
                template < template < typename ... > class __CollectionType >   /* NOLINT(bugprone-reserved-identifier) */
                __CDS_NoDiscard auto indicesOfFrom (
                        Size                            count,
                        __FromCollectionType    const & from
                ) const noexcept -> __CollectionType < Index >;

            public:
                __CDS_NoDiscard auto firstIndexOfFrom (
                        __FromCollectionType const & from
                ) const noexcept -> Index;

            public:
                __CDS_NoDiscard auto lastIndexOfFrom (
                        __FromCollectionType const & from
                ) const noexcept -> Index;

            public:
                template < typename __CollectionType >  /* NOLINT(bugprone-reserved-identifier) */
                auto allIndicesOfFrom (
                        __CollectionType              & storeIn,
                        __FromCollectionType    const & from
                ) const noexcept -> __CollectionType &;

            public:
                template < template < typename ... > class __CollectionType >   /* NOLINT(bugprone-reserved-identifier) */
                __CDS_NoDiscard auto allIndicesOfFrom (
                        __FromCollectionType const & from
                ) const noexcept -> __CollectionType < Index >;

            public:
                template < typename __CollectionType >  /* NOLINT(bugprone-reserved-identifier) */
                auto indicesOfNotFrom (
                        Size                            count,
                        __CollectionType              & storeIn,
                        __FromCollectionType    const & from
                ) const noexcept -> __CollectionType &;

            public:
                template < template < typename ... > class __CollectionType >   /* NOLINT(bugprone-reserved-identifier) */
                __CDS_NoDiscard auto indicesOfNotFrom (
                        Size                            count,
                        __FromCollectionType    const & from
                ) const noexcept -> __CollectionType < Index >;

            public:
                __CDS_NoDiscard auto firstIndexOfNotFrom (
                        __FromCollectionType const & from
                ) const noexcept -> Index;

            public:
                __CDS_NoDiscard auto lastIndexOfNotFrom (
                        __FromCollectionType const & from
                ) const noexcept -> Index;

            public:
                template < typename __CollectionType >  /* NOLINT(bugprone-reserved-identifier) */
                auto allIndicesOfNotFrom (
                        __CollectionType              & storeIn,
                        __FromCollectionType    const & from
                ) const noexcept -> __CollectionType &;

            public:
                template < template < typename ... > class __CollectionType >   /* NOLINT(bugprone-reserved-identifier) */
                __CDS_NoDiscard auto allIndicesOfNotFrom (
                        __FromCollectionType const & from
                ) const noexcept -> __CollectionType < Index >;
            };


            template <
                    typename                                                    __ReceiverType,         /* NOLINT(bugprone-reserved-identifier) */
                    typename                                                    __ElementType,          /* NOLINT(bugprone-reserved-identifier) */
                    typename                                                    __FromCollectionType,   /* NOLINT(bugprone-reserved-identifier) */
                    __ContainsFunction < __FromCollectionType, __ElementType >  __contains              /* NOLINT(bugprone-reserved-identifier) */
            > using __LocalIndicesOfCompositeClient =                                                   /* NOLINT(bugprone-reserved-identifier) */
                    __IndicesOfCompositeClient <
                            __ReceiverType,
                            __ElementType,
                            __FromCollectionType,
                            __contains
                    >;

        }
    }
}

#endif /* __CDS_SHARED_INDICES_OF_COMPOSITE_CLIENT_HPP__ */
