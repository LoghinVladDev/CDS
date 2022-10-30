/*
 * Created by loghin on 6/30/2022.
 */

#ifndef __CDS_SHARED_INDEXED_OPERATIONS_PRIMITIVE_CLIENT_HPP__ /* NOLINT(llvm-header-guard) */
#define __CDS_SHARED_INDEXED_OPERATIONS_PRIMITIVE_CLIENT_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

namespace cds {             /* NOLINT(modernize-concat-nested-namespaces) */
    namespace __hidden {    /* NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        namespace __impl {  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            template <
                    typename __ReceiverType,                /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ElementType                  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > class __IndexedOperationsPrimitiveClient {    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            private:    /* NOLINT(readability-redundant-access-specifiers) */
                using ElementType = __ElementType;

            public: /* NOLINT(readability-redundant-access-specifiers) */
                template <
                        typename __CollectionType,                  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        typename __TElementType = __ElementType,    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        cds :: meta :: EnableIf <
                                cds :: meta :: isCopyConstructible < __TElementType > ()
                        > = 0
                > auto sub (
                        __CollectionType  & storeIn,
                        Index               from,
                        Index               to
                ) const noexcept -> __CollectionType &;

            public: /* NOLINT(readability-redundant-access-specifiers) */
                template <
                        typename __CollectionType,                  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        typename __TElementType = __ElementType,    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        cds :: meta :: EnableIf <
                                cds :: meta :: isCopyConstructible < __TElementType > ()
                        > = 0
                > __CDS_NoDiscard auto sub (
                        Index               from,
                        Index               to
                ) const noexcept -> __CollectionType;

            public: /* NOLINT(readability-redundant-access-specifiers) */
                template <
                        template < typename ... > class __CollectionType,   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        typename __TElementType = __ElementType,            /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        cds :: meta :: EnableIf <
                                cds :: meta :: isCopyConstructible < __TElementType > ()
                        > = 0
                > __CDS_NoDiscard auto sub (
                        Index               from,
                        Index               to
                ) const noexcept -> __CollectionType < __ElementType >;

            public: /* NOLINT(readability-redundant-access-specifiers) */
                __CDS_NoDiscard auto operator [] (
                        Index index
                ) const noexcept (false) -> ElementType const &;

            public: /* NOLINT(readability-redundant-access-specifiers) */
                __CDS_NoDiscard auto operator [] (
                        Index index
                ) noexcept (false) -> ElementType &;

            public: /* NOLINT(readability-redundant-access-specifiers) */
                auto removeAt (
                        Collection < Index > const & indices
                ) noexcept -> Size;

            public: /* NOLINT(readability-redundant-access-specifiers) */
                auto removeAt (
                        std :: initializer_list < Index > const & indices
                ) noexcept -> Size;
            };


            template <
                    typename __ReceiverType,                    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ElementType                      /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > class __LocalIndexedOperationsPrimitiveClient {   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            private:    /* NOLINT(readability-redundant-access-specifiers) */
                using ElementType = __ElementType;

            public: /* NOLINT(readability-redundant-access-specifiers) */
                template <
                        typename __CollectionType,                  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        typename __TElementType = __ElementType,    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        cds :: meta :: EnableIf <
                                cds :: meta :: isCopyConstructible < __TElementType > ()
                        > = 0
                > auto sub (
                        __CollectionType  & storeIn,
                        Index               from,
                        Index               to
                ) const noexcept -> __CollectionType &;

            public: /* NOLINT(readability-redundant-access-specifiers) */
                template <
                        typename __CollectionType = __ReceiverType, /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        typename __TElementType = __ElementType,    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        cds :: meta :: EnableIf <
                                cds :: meta :: isCopyConstructible < __TElementType > ()
                        > = 0
                > __CDS_NoDiscard auto sub (
                        Index               from,
                        Index               to
                ) const noexcept -> __CollectionType;

            public: /* NOLINT(readability-redundant-access-specifiers) */
                template <
                        template < typename ... > class __CollectionType,   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        typename __TElementType = __ElementType,            /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        cds :: meta :: EnableIf <
                                cds :: meta :: isCopyConstructible < __TElementType > ()
                        > = 0
                > __CDS_NoDiscard auto sub (
                        Index               from,
                        Index               to
                ) const noexcept -> __CollectionType < __ElementType >;
            };

        } /* namespace __impl */
    } /* namespace __hidden */
} /* namespace cds */

#endif /* __CDS_SHARED_INDEXED_OPERATIONS_PRIMITIVE_CLIENT_HPP__ */
