/*
 * Created by loghin on 6/30/2022.
 */

#ifndef __CDS_SHARED_REPLACE_OF_COMPOSITE_CLIENT_HPP__ /* NOLINT(llvm-header-guard) */
#define __CDS_SHARED_REPLACE_OF_COMPOSITE_CLIENT_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

namespace cds {             /* NOLINT(modernize-concat-nested-namespaces) */
    namespace __hidden {    /* NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        namespace __impl {  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            template <
                    typename                                                    __ReceiverType,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                    __ElementType,      /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                    __OfCollectionType, /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __ContainsFunction < __OfCollectionType, __ElementType >    __contains          /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > class __ReplaceOfCompositeClient {                                                    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            private:    /* NOLINT(readability-redundant-access-specifiers) */
                using ElementType = __ElementType;

            private:    /* NOLINT(readability-redundant-access-specifiers) */
                using OfCollectionType = __OfCollectionType;

            public: /* NOLINT(readability-redundant-access-specifiers) */
                template <
                        typename __TElementType = __ElementType, /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        cds :: meta :: EnableIf <
                                cds :: meta :: isCopyAssignable < __TElementType > ()
                        > = 0
                > auto replaceOf (
                        Size                        count,
                        __OfCollectionType  const & of,
                        ElementType         const & with
                ) noexcept -> Size;

            public: /* NOLINT(readability-redundant-access-specifiers) */
                template <
                        typename __TElementType = __ElementType, /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        cds :: meta :: EnableIf <
                                cds :: meta :: isCopyAssignable < __TElementType > ()
                        > = 0
                > auto replaceFirstOf (
                        __OfCollectionType  const & of,
                        ElementType         const & with
                ) noexcept -> bool;

            public: /* NOLINT(readability-redundant-access-specifiers) */
                template <
                        typename __TElementType = __ElementType, /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        cds :: meta :: EnableIf <
                                cds :: meta :: isMoveAssignable < __TElementType > ()
                        > = 0
                > auto replaceFirstOf (
                        __OfCollectionType  const & of,
                        ElementType              && with
                ) noexcept -> bool;

            public: /* NOLINT(readability-redundant-access-specifiers) */
                template <
                        typename __TElementType = __ElementType, /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        cds :: meta :: EnableIf <
                                cds :: meta :: isCopyAssignable < __TElementType > ()
                        > = 0
                > auto replaceLastOf (
                        __OfCollectionType  const & of,
                        ElementType         const & with
                ) noexcept -> bool;

            public: /* NOLINT(readability-redundant-access-specifiers) */
                template <
                        typename __TElementType = __ElementType, /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        cds :: meta :: EnableIf <
                                cds :: meta :: isMoveAssignable < __TElementType > ()
                        > = 0
                > auto replaceLastOf (
                        __OfCollectionType  const & of,
                        ElementType              && with
                ) noexcept -> bool;

            public: /* NOLINT(readability-redundant-access-specifiers) */
                template <
                        typename __TElementType = __ElementType, /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        cds :: meta :: EnableIf <
                                cds :: meta :: isCopyAssignable < __TElementType > ()
                        > = 0
                > auto replaceAllOf (
                        __OfCollectionType  const & of,
                        ElementType         const & with
                ) noexcept -> Size;

            public: /* NOLINT(readability-redundant-access-specifiers) */
                template <
                        typename __TElementType = __ElementType, /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        cds :: meta :: EnableIf <
                                cds :: meta :: isCopyAssignable < __TElementType > ()
                        > = 0
                > auto replaceNotOf (
                        Size                        count,
                        __OfCollectionType  const & of,
                        ElementType         const & with
                ) noexcept -> Size;

            public: /* NOLINT(readability-redundant-access-specifiers) */
                template <
                        typename __TElementType = __ElementType, /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        cds :: meta :: EnableIf <
                                cds :: meta :: isCopyAssignable < __TElementType > ()
                        > = 0
                > auto replaceFirstNotOf (
                        __OfCollectionType  const & of,
                        ElementType         const & with
                ) noexcept -> bool;

            public: /* NOLINT(readability-redundant-access-specifiers) */
                template <
                        typename __TElementType = __ElementType, /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        cds :: meta :: EnableIf <
                                cds :: meta :: isMoveAssignable < __TElementType > ()
                        > = 0
                > auto replaceFirstNotOf (
                        __OfCollectionType  const & of,
                        ElementType              && with
                ) noexcept -> bool;

            public: /* NOLINT(readability-redundant-access-specifiers) */
                template <
                        typename __TElementType = __ElementType, /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        cds :: meta :: EnableIf <
                                cds :: meta :: isCopyAssignable < __TElementType > ()
                        > = 0
                > auto replaceLastNotOf (
                        __OfCollectionType  const & of,
                        ElementType         const & with
                ) noexcept -> bool;

            public: /* NOLINT(readability-redundant-access-specifiers) */
                template <
                        typename __TElementType = __ElementType, /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        cds :: meta :: EnableIf <
                                cds :: meta :: isMoveAssignable < __TElementType > ()
                        > = 0
                > auto replaceLastNotOf (
                        __OfCollectionType  const & of,
                        ElementType              && with
                ) noexcept -> bool;

            public: /* NOLINT(readability-redundant-access-specifiers) */
                template <
                        typename __TElementType = __ElementType, /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        cds :: meta :: EnableIf <
                                cds :: meta :: isCopyAssignable < __TElementType > ()
                        > = 0
                > auto replaceAllNotOf (
                        __OfCollectionType  const & of,
                        ElementType         const & with
                ) noexcept -> Size;
            };


            template <
                    typename                                                    __ReceiverType,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                    __ElementType,      /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                    __OfCollectionType, /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __ContainsFunction < __OfCollectionType, __ElementType >    __contains          /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > using __LocalReplaceOfCompositeClient =                                               /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __ReplaceOfCompositeClient <
                            __ReceiverType,
                            __ElementType,
                            __OfCollectionType,
                            __contains
                    >;

        } /* namespace __impl */
    } /* namespace __hidden */
} /* namespace cds */

#endif /* __CDS_SHARED_REPLACE_OF_COMPOSITE_CLIENT_HPP__ */
