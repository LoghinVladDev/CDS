/*
 * Created by loghin on 6/30/22.
 */

#ifndef __CDS_SHARED_INDICES_OF_COMPOSITE_CLIENT_HPP__ /* NOLINT(llvm-header-guard) */
#define __CDS_SHARED_INDICES_OF_COMPOSITE_CLIENT_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

namespace cds {             /* NOLINT(modernize-concat-nested-namespaces) */
    namespace __hidden {    /* NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        namespace __impl {  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            template <
                    typename                                                                                __ReceiverType,         /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                                __ElementType,          /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                                __FromCollectionType,   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: PredicateFunction < __FromCollectionType const &, __ElementType const & > __contains              /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > class __IndicesOfCompositeClient {                                                                                    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            private:    /* NOLINT(readability-redundant-access-specifiers) */
                using ElementType = __ElementType;

            public: /* NOLINT(readability-redundant-access-specifiers) */
                template < typename __CollectionType >  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                auto indicesOfFrom (
                        Size                            count,
                        __CollectionType              & storeIn,
                        __FromCollectionType    const & from
                ) const noexcept -> __CollectionType &;

            public: /* NOLINT(readability-redundant-access-specifiers) */
                template < template < typename ... > class __CollectionType >   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                __CDS_NoDiscard auto indicesOfFrom (
                        Size                            count,
                        __FromCollectionType    const & from
                ) const noexcept -> __CollectionType < Index >;

            public: /* NOLINT(readability-redundant-access-specifiers) */
                __CDS_NoDiscard auto firstIndexOfFrom (
                        __FromCollectionType const & from
                ) const noexcept -> Index;

            public: /* NOLINT(readability-redundant-access-specifiers) */
                __CDS_NoDiscard auto lastIndexOfFrom (
                        __FromCollectionType const & from
                ) const noexcept -> Index;

            public: /* NOLINT(readability-redundant-access-specifiers) */
                template < typename __CollectionType >  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                auto allIndicesOfFrom (
                        __CollectionType              & storeIn,
                        __FromCollectionType    const & from
                ) const noexcept -> __CollectionType &;

            public: /* NOLINT(readability-redundant-access-specifiers) */
                template < template < typename ... > class __CollectionType >   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                __CDS_NoDiscard auto allIndicesOfFrom (
                        __FromCollectionType const & from
                ) const noexcept -> __CollectionType < Index >;

            public: /* NOLINT(readability-redundant-access-specifiers) */
                template < typename __CollectionType >  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                auto indicesOfNotFrom (
                        Size                            count,
                        __CollectionType              & storeIn,
                        __FromCollectionType    const & from
                ) const noexcept -> __CollectionType &;

            public: /* NOLINT(readability-redundant-access-specifiers) */
                template < template < typename ... > class __CollectionType >   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                __CDS_NoDiscard auto indicesOfNotFrom (
                        Size                            count,
                        __FromCollectionType    const & from
                ) const noexcept -> __CollectionType < Index >;

            public: /* NOLINT(readability-redundant-access-specifiers) */
                __CDS_NoDiscard auto firstIndexOfNotFrom (
                        __FromCollectionType const & from
                ) const noexcept -> Index;

            public: /* NOLINT(readability-redundant-access-specifiers) */
                __CDS_NoDiscard auto lastIndexOfNotFrom (
                        __FromCollectionType const & from
                ) const noexcept -> Index;

            public: /* NOLINT(readability-redundant-access-specifiers) */
                template < typename __CollectionType >  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                auto allIndicesOfNotFrom (
                        __CollectionType              & storeIn,
                        __FromCollectionType    const & from
                ) const noexcept -> __CollectionType &;

            public: /* NOLINT(readability-redundant-access-specifiers) */
                template < template < typename ... > class __CollectionType >   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                __CDS_NoDiscard auto allIndicesOfNotFrom (
                        __FromCollectionType const & from
                ) const noexcept -> __CollectionType < Index >;
            };


            template <
                    typename                                                                                __ReceiverType,         /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                                __ElementType,          /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                                __FromCollectionType,   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: PredicateFunction < __FromCollectionType const &, __ElementType const & > __contains              /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > using __LocalIndicesOfCompositeClient =                                                                               /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __IndicesOfCompositeClient <
                            __ReceiverType,
                            __ElementType,
                            __FromCollectionType,
                            __contains
                    >;

        } /* namespace __impl */
    } /* namespace __hidden */
} /* namespace cds */

#endif /* __CDS_SHARED_INDICES_OF_COMPOSITE_CLIENT_HPP__ */
