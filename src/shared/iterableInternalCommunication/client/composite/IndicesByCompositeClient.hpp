/*
 * Created by loghin on 6/30/22.
 */

#ifndef __CDS_SHARED_INDICES_BY_COMPOSITE_CLIENT_HPP__ /* NOLINT(llvm-header-guard) */
#define __CDS_SHARED_INDICES_BY_COMPOSITE_CLIENT_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

namespace cds {             /* NOLINT(modernize-concat-nested-namespaces) */
    namespace __hidden {    /* NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        namespace __impl {  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            template <
                    typename __ReceiverType,        /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ElementType          /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > class __IndicesByCompositeClient {    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            private:    /* NOLINT(readability-redundant-access-specifiers) */
                using ElementType = __ElementType;

            public: /* NOLINT(readability-redundant-access-specifiers) */
                template <
                        typename __CollectionType,  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        typename __Predicate        /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                > auto indicesOfThat (
                        Size                        count,
                        __CollectionType          & storeIn,
                        __Predicate         const & predicate
                ) const noexcept ( noexcept ( predicate ( cds :: meta :: referenceOf < ElementType const > () ) ) ) -> __CollectionType &;

            public: /* NOLINT(readability-redundant-access-specifiers) */
                template <
                        template < typename ... > class __CollectionType,   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        typename __Predicate                                /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                > __CDS_NoDiscard auto indicesOfThat (
                        Size                count,
                        __Predicate const & predicate
                ) const noexcept ( noexcept ( predicate ( cds :: meta :: referenceOf < ElementType const > () ) ) ) -> __CollectionType < Index >;

            public: /* NOLINT(readability-redundant-access-specifiers) */
                template < typename __Predicate >   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                __CDS_NoDiscard auto firstIndexOfThat (
                        __Predicate const & predicate
                ) const noexcept ( noexcept ( predicate ( cds :: meta :: referenceOf < ElementType const > () ) ) ) -> Index;

            public: /* NOLINT(readability-redundant-access-specifiers) */
                template < typename __Predicate >   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                __CDS_NoDiscard auto lastIndexOfThat (
                        __Predicate const & predicate
                ) const noexcept ( noexcept ( predicate ( cds :: meta :: referenceOf < ElementType const > () ) ) ) -> Index;

            public: /* NOLINT(readability-redundant-access-specifiers) */
                template <
                        typename __CollectionType,  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        typename __Predicate        /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                > auto allIndicesOfThat (
                        __CollectionType          & storeIn,
                        __Predicate         const & predicate
                ) const noexcept ( noexcept ( predicate ( cds :: meta :: referenceOf < ElementType const > () ) ) ) -> __CollectionType &;

            public: /* NOLINT(readability-redundant-access-specifiers) */
                template <
                        template < typename ... > class __CollectionType,   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        typename                        __Predicate         /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                > __CDS_NoDiscard auto allIndicesOfThat (
                        __Predicate const & predicate
                ) const noexcept ( noexcept ( predicate ( cds :: meta :: referenceOf < ElementType const > () ) ) ) -> __CollectionType < Index >;
            };


            template <
                    typename __ReceiverType,            /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ElementType              /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > using __LocalIndicesByCompositeClient =   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __IndicesByCompositeClient <
                            __ReceiverType,
                            __ElementType
                    >;

        } /* namespace __impl */
    } /* namespace __hidden */
} /* namespace cds */

#endif /* __CDS_SHARED_INDICES_BY_COMPOSITE_CLIENT_HPP__ */
