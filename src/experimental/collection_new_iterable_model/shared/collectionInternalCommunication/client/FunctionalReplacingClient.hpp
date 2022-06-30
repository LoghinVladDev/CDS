//
// Created by uic70278 on 6/30/2022.
//

#ifndef __CDS_SHARED_FUNCTIONAL_REPLACING_CLIENT_HPP__
#define __CDS_SHARED_FUNCTIONAL_REPLACING_CLIENT_HPP__

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {
        namespace __hidden {
            namespace __impl {

                template <
                        typename __ReceiverType,        // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType          // NOLINT(bugprone-reserved-identifier)
                > class __FunctionalReplacingClient {   // NOLINT(bugprone-reserved-identifier)

                private:
                    using ElementType = __ElementType;

                protected:
                    template <
                            typename __Predicate,                       // NOLINT(bugprone-reserved-identifier)
                            typename __VElementType = __ElementType,    // NOLINT(bugprone-reserved-identifier)
                            cds :: meta :: EnableIf <
                                    cds :: meta :: isCopyAssignable < __VElementType > ()
                            > = 0
                    > auto replaceThat (
                            Size                count,
                            __Predicate const & predicate,
                            ElementType const & with
                    ) noexcept ( noexcept ( predicate ( cds :: meta :: referenceOf < ElementType > () ) ) ) -> Size;

                protected:
                    template <
                            typename __Predicate,                       // NOLINT(bugprone-reserved-identifier)
                            typename __VElementType = __ElementType,    // NOLINT(bugprone-reserved-identifier)
                            cds :: meta :: EnableIf <
                                    cds :: meta :: isCopyAssignable < __VElementType > ()
                            > = 0
                    > auto replaceFirstThat (
                            __Predicate const & predicate,
                            ElementType const & with
                    ) noexcept ( noexcept ( predicate ( cds :: meta :: referenceOf < ElementType > () ) ) ) -> bool;

                protected:
                    template <
                            typename __Predicate,                       // NOLINT(bugprone-reserved-identifier)
                            typename __VElementType = __ElementType,    // NOLINT(bugprone-reserved-identifier)
                            cds :: meta :: EnableIf <
                                    cds :: meta :: isMoveAssignable < __VElementType > ()
                            > = 0
                    > auto replaceFirstThat (
                            __Predicate const & predicate,
                            ElementType      && with
                    ) noexcept ( noexcept ( predicate ( cds :: meta :: referenceOf < ElementType > () ) ) ) -> bool;

                protected:
                    template <
                            typename __Predicate,                       // NOLINT(bugprone-reserved-identifier)
                            typename __VElementType = __ElementType,    // NOLINT(bugprone-reserved-identifier)
                            cds :: meta :: EnableIf <
                                    cds :: meta :: isCopyAssignable < __VElementType > ()
                            > = 0
                    > auto replaceLastThat (
                            __Predicate const & predicate,
                            ElementType const & with
                    ) noexcept ( noexcept ( predicate ( cds :: meta :: referenceOf < ElementType > () ) ) ) -> bool;

                protected:
                    template <
                            typename __Predicate,                       // NOLINT(bugprone-reserved-identifier)
                            typename __VElementType = __ElementType,    // NOLINT(bugprone-reserved-identifier)
                            cds :: meta :: EnableIf <
                                    cds :: meta :: isMoveAssignable < __VElementType > ()
                            > = 0
                    > auto replaceLastThat (
                            __Predicate const & predicate,
                            ElementType      && with
                    ) noexcept ( noexcept ( predicate ( cds :: meta :: referenceOf < ElementType > () ) ) ) -> bool;

                protected:
                    template <
                            typename __Predicate,                       // NOLINT(bugprone-reserved-identifier)
                            typename __VElementType = __ElementType,    // NOLINT(bugprone-reserved-identifier)
                            cds :: meta :: EnableIf <
                                    cds :: meta :: isCopyAssignable < __VElementType > ()
                            > = 0
                    > auto replaceAllThat (
                            __Predicate const & predicate,
                            ElementType const & with
                    ) noexcept ( noexcept ( predicate ( cds :: meta :: referenceOf < ElementType > () ) ) ) -> Size;

                protected:
                    template <
                            typename __Predicate,   // NOLINT(bugprone-reserved-identifier)
                            typename __Supplier     // NOLINT(bugprone-reserved-identifier)
                    > auto replaceThatBy (
                            Size                count,
                            __Predicate const & predicate,
                            __Supplier  const & supplier
                    ) noexcept ( noexcept ( predicate ( cds :: meta :: referenceOf < ElementType > () ) ) && noexcept ( supplier ( cds :: meta :: referenceOf < ElementType > () ) ) ) -> Size;

                protected:
                    template <
                            typename __Predicate,   // NOLINT(bugprone-reserved-identifier)
                            typename __Supplier     // NOLINT(bugprone-reserved-identifier)
                    > auto replaceFirstThatBy (
                            __Predicate const & predicate,
                            __Supplier  const & supplier
                    ) noexcept ( noexcept ( predicate ( cds :: meta :: referenceOf < ElementType > () ) ) && noexcept ( supplier ( cds :: meta :: referenceOf < ElementType > () ) ) ) -> bool;

                protected:
                    template <
                            typename __Predicate,   // NOLINT(bugprone-reserved-identifier)
                            typename __Supplier     // NOLINT(bugprone-reserved-identifier)
                    > auto replaceLastThatBy (
                            __Predicate const & predicate,
                            __Supplier  const & supplier
                    ) noexcept ( noexcept ( predicate ( cds :: meta :: referenceOf < ElementType > () ) ) && noexcept ( supplier ( cds :: meta :: referenceOf < ElementType > () ) ) ) -> bool;

                protected:
                    template <
                            typename __Predicate,   // NOLINT(bugprone-reserved-identifier)
                            typename __Supplier     // NOLINT(bugprone-reserved-identifier)
                    > auto replaceAllThatBy (
                            __Predicate const & predicate,
                            __Supplier  const & supplier
                    ) noexcept ( noexcept ( predicate ( cds :: meta :: referenceOf < ElementType > () ) ) && noexcept ( supplier ( cds :: meta :: referenceOf < ElementType > () ) ) ) -> Size;

                };

            }
        }
    }
}

#endif // __CDS_SHARED_FUNCTIONAL_REPLACING_CLIENT_HPP__
