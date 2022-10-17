/*
 * Created by loghin on 6/30/22.
 */

#ifndef __CDS_SHARED_INDICES_COMPOSITE_CLIENT_HPP__ /* NOLINT(llvm-header-guard) */
#define __CDS_SHARED_INDICES_COMPOSITE_CLIENT_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

namespace cds {             /* NOLINT(modernize-concat-nested-namespaces) */
    namespace __hidden {    /* NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        namespace __impl {  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            template <
                    typename __ReceiverType,    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ElementType      /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > class __IndicesCompositeClient {  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            private:    /* NOLINT(readability-redundant-access-specifiers) */
                using ElementType = __ElementType;

            public: /* NOLINT(readability-redundant-access-specifiers) */
                template < typename __CollectionType >  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                auto indicesOf (
                        Size                        count,
                        __CollectionType          & storeIn,
                        ElementType         const & element
                ) const noexcept -> __CollectionType &;

            public: /* NOLINT(readability-redundant-access-specifiers) */
                template < template < typename ... > class __CollectionType >   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                __CDS_NoDiscard auto indicesOf (
                        Size                count,
                        ElementType const & element
                ) const noexcept -> __CollectionType < Index >;

            public: /* NOLINT(readability-redundant-access-specifiers) */
                __CDS_NoDiscard auto firstIndexOf (
                        ElementType const & element
                ) const noexcept -> Index;

            public: /* NOLINT(readability-redundant-access-specifiers) */
                __CDS_NoDiscard auto lastIndexOf (
                        ElementType const & element
                ) const noexcept -> Index;

            public: /* NOLINT(readability-redundant-access-specifiers) */
                template < typename __CollectionType >  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                auto allIndicesOf (
                        __CollectionType          & storeIn,
                        ElementType         const & element
                ) const noexcept -> __CollectionType &;

            public: /* NOLINT(readability-redundant-access-specifiers) */
                template < template < typename ... > class __CollectionType >   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                __CDS_NoDiscard auto allIndicesOf (
                        ElementType const & element
                ) const noexcept -> __CollectionType < Index >;
            };

            template <
                    typename __ReceiverType,        /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ElementType          /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > using __LocalIndicesCompositeClient = /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __IndicesCompositeClient <
                            __ReceiverType,
                            __ElementType
                    >;

        } /* namespace __impl */
    } /* namespace __hidden */
} /* namespace cds */

#endif /* __CDS_SHARED_INDICES_COMPOSITE_CLIENT_HPP__ */
