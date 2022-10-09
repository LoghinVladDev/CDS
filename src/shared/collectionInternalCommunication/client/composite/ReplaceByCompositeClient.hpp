/*
 * Created by loghin on 6/30/2022.
 */

#ifndef __CDS_SHARED_REPLACE_BY_COMPOSITE_CLIENT_HPP__
#define __CDS_SHARED_REPLACE_BY_COMPOSITE_CLIENT_HPP__ /* NOLINT(bugprone-reserved-identifier) */

namespace cds {             /* NOLINT(modernize-concat-nested-namespaces) */
    namespace __hidden {    /* NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier) */
        namespace __impl {  /* NOLINT(bugprone-reserved-identifier) */

            template <
                    typename __ReceiverType,        /* NOLINT(bugprone-reserved-identifier) */
                    typename __ElementType          /* NOLINT(bugprone-reserved-identifier) */
            > class __ReplaceByCompositeClient {    /* NOLINT(bugprone-reserved-identifier) */

            private:
                using ElementType = __ElementType;

            public:
                template <
                        typename __Predicate,                       /* NOLINT(bugprone-reserved-identifier) */
                        typename __TElementType = __ElementType,    /* NOLINT(bugprone-reserved-identifier) */
                        cds :: meta :: EnableIf <
                                cds :: meta :: isCopyAssignable < __TElementType > ()
                        > = 0
                > auto replaceThat (
                        Size                count,
                        __Predicate const & predicate,
                        ElementType const & with
                ) noexcept ( noexcept ( predicate ( cds :: meta :: referenceOf < ElementType > () ) ) ) -> Size;

            public:
                template <
                        typename __Predicate,                       /* NOLINT(bugprone-reserved-identifier) */
                        typename __TElementType = __ElementType,    /* NOLINT(bugprone-reserved-identifier) */
                        cds :: meta :: EnableIf <
                                cds :: meta :: isCopyAssignable < __TElementType > ()
                        > = 0
                > auto replaceFirstThat (
                        __Predicate const & predicate,
                        ElementType const & with
                ) noexcept ( noexcept ( predicate ( cds :: meta :: referenceOf < ElementType > () ) ) ) -> bool;

            public:
                template <
                        typename __Predicate,                       /* NOLINT(bugprone-reserved-identifier) */
                        typename __TElementType = __ElementType,    /* NOLINT(bugprone-reserved-identifier) */
                        cds :: meta :: EnableIf <
                                cds :: meta :: isMoveAssignable < __TElementType > ()
                        > = 0
                > auto replaceFirstThat (
                        __Predicate const & predicate,
                        ElementType      && with
                ) noexcept ( noexcept ( predicate ( cds :: meta :: referenceOf < ElementType > () ) ) ) -> bool;

            public:
                template <
                        typename __Predicate,                       /* NOLINT(bugprone-reserved-identifier) */
                        typename __TElementType = __ElementType,    /* NOLINT(bugprone-reserved-identifier) */
                        cds :: meta :: EnableIf <
                                cds :: meta :: isCopyAssignable < __TElementType > ()
                        > = 0
                > auto replaceLastThat (
                        __Predicate const & predicate,
                        ElementType const & with
                ) noexcept ( noexcept ( predicate ( cds :: meta :: referenceOf < ElementType > () ) ) ) -> bool;

            public:
                template <
                        typename __Predicate,                       /* NOLINT(bugprone-reserved-identifier) */
                        typename __TElementType = __ElementType,    /* NOLINT(bugprone-reserved-identifier) */
                        cds :: meta :: EnableIf <
                                cds :: meta :: isMoveAssignable < __TElementType > ()
                        > = 0
                > auto replaceLastThat (
                        __Predicate const & predicate,
                        ElementType      && with
                ) noexcept ( noexcept ( predicate ( cds :: meta :: referenceOf < ElementType > () ) ) ) -> bool;

            public:
                template <
                        typename __Predicate,                       /* NOLINT(bugprone-reserved-identifier) */
                        typename __TElementType = __ElementType,    /* NOLINT(bugprone-reserved-identifier) */
                        cds :: meta :: EnableIf <
                                cds :: meta :: isCopyAssignable < __TElementType > ()
                        > = 0
                > auto replaceAllThat (
                        __Predicate const & predicate,
                        ElementType const & with
                ) noexcept ( noexcept ( predicate ( cds :: meta :: referenceOf < ElementType > () ) ) ) -> Size;

            public:
                template <
                        typename __Predicate,   /* NOLINT(bugprone-reserved-identifier) */
                        typename __Supplier     /* NOLINT(bugprone-reserved-identifier) */
                > auto replaceThatBy (
                        Size                count,
                        __Predicate const & predicate,
                        __Supplier  const & supplier
                ) noexcept ( noexcept ( predicate ( cds :: meta :: referenceOf < ElementType > () ) ) && noexcept ( supplier ( cds :: meta :: referenceOf < ElementType > () ) ) ) -> Size;

            public:
                template <
                        typename __Predicate,   /* NOLINT(bugprone-reserved-identifier) */
                        typename __Supplier     /* NOLINT(bugprone-reserved-identifier) */
                > auto replaceFirstThatBy (
                        __Predicate const & predicate,
                        __Supplier  const & supplier
                ) noexcept ( noexcept ( predicate ( cds :: meta :: referenceOf < ElementType > () ) ) && noexcept ( supplier ( cds :: meta :: referenceOf < ElementType > () ) ) ) -> bool;

            public:
                template <
                        typename __Predicate,   /* NOLINT(bugprone-reserved-identifier) */
                        typename __Supplier     /* NOLINT(bugprone-reserved-identifier) */
                > auto replaceLastThatBy (
                        __Predicate const & predicate,
                        __Supplier  const & supplier
                ) noexcept ( noexcept ( predicate ( cds :: meta :: referenceOf < ElementType > () ) ) && noexcept ( supplier ( cds :: meta :: referenceOf < ElementType > () ) ) ) -> bool;

            public:
                template <
                        typename __Predicate,   /* NOLINT(bugprone-reserved-identifier) */
                        typename __Supplier     /* NOLINT(bugprone-reserved-identifier) */
                > auto replaceAllThatBy (
                        __Predicate const & predicate,
                        __Supplier  const & supplier
                ) noexcept ( noexcept ( predicate ( cds :: meta :: referenceOf < ElementType > () ) ) && noexcept ( supplier ( cds :: meta :: referenceOf < ElementType > () ) ) ) -> Size;

            };


            template <
                    typename __ReceiverType,            /* NOLINT(bugprone-reserved-identifier) */
                    typename __ElementType              /* NOLINT(bugprone-reserved-identifier) */
            > using __LocalReplaceByCompositeClient =   /* NOLINT(bugprone-reserved-identifier) */
                    __ReplaceByCompositeClient <
                            __ReceiverType,
                            __ElementType
                    >;

        }
    }
}

#endif /* __CDS_SHARED_REPLACE_BY_COMPOSITE_CLIENT_HPP__ */
