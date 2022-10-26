/*
 * Created by loghin on 6/30/2022.
 */

#ifndef __CDS_SHARED_REPLACE_COMPOSITE_CLIENT_HPP__ /* NOLINT(llvm-header-guard) */
#define __CDS_SHARED_REPLACE_COMPOSITE_CLIENT_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

namespace cds {             /* NOLINT(modernize-concat-nested-namespaces) */
    namespace __hidden {    /* NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        namespace __impl {  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            template <
                    typename __ReceiverType,                /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ElementType                  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > class __ReplaceCompositeClient {              /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            private:    /* NOLINT(readability-redundant-access-specifiers) */
                using ElementType = __ElementType;

            public: /* NOLINT(readability-redundant-access-specifiers) */
                template <
                        typename __TElementType = __ElementType, /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        cds :: meta :: EnableIf <
                                cds :: meta :: isCopyAssignable < __TElementType > ()
                        > = 0
                > auto replace (
                        Size                count,
                        ElementType const & what,
                        ElementType const & with
                ) noexcept -> Size;

            public: /* NOLINT(readability-redundant-access-specifiers) */
                template <
                        typename __TElementType = __ElementType, /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        cds :: meta :: EnableIf <
                                cds :: meta :: isCopyAssignable < __TElementType > ()
                        > = 0
                > auto replaceFirst (
                        ElementType const & what,
                        ElementType const & with
                ) noexcept -> bool;

            public: /* NOLINT(readability-redundant-access-specifiers) */
                template <
                        typename __TElementType = __ElementType, /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        cds :: meta :: EnableIf <
                                cds :: meta :: isMoveAssignable < __TElementType > ()
                        > = 0
                > auto replaceFirst (
                        ElementType const & what,
                        ElementType      && with
                ) noexcept -> bool;

            public: /* NOLINT(readability-redundant-access-specifiers) */
                template <
                        typename __TElementType = __ElementType, /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        cds :: meta :: EnableIf <
                                cds :: meta :: isCopyAssignable < __TElementType > ()
                        > = 0
                > auto replaceLast (
                        ElementType const & what,
                        ElementType const & with
                ) noexcept -> bool;

            public: /* NOLINT(readability-redundant-access-specifiers) */
                template <
                        typename __TElementType = __ElementType, /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        cds :: meta :: EnableIf <
                                cds :: meta :: isMoveAssignable < __TElementType > ()
                        > = 0
                > auto replaceLast (
                        ElementType const & what,
                        ElementType      && with
                ) noexcept -> bool;

            public: /* NOLINT(readability-redundant-access-specifiers) */
                template <
                        typename __TElementType = __ElementType, /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        cds :: meta :: EnableIf <
                                cds :: meta :: isCopyAssignable < __TElementType > ()
                        > = 0
                > auto replaceAll (
                        ElementType const & what,
                        ElementType const & with
                ) noexcept -> Size;
            };


            template <
                    typename __ReceiverType,            /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ElementType              /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > using __LocalReplaceCompositeClient =     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __ReplaceCompositeClient <
                            __ReceiverType,
                            __ElementType
                    >;

        } /* namespace __impl */
    } /* namespace __hidden */
} /* namespace cds */

#endif /* __CDS_SHARED_REPLACE_COMPOSITE_CLIENT_HPP__ */
