//
// Created by uic70278 on 6/30/2022.
//

#ifndef __CDS_SHARED_REPLACING_OF_CLIENT_HPP__
#define __CDS_SHARED_REPLACING_OF_CLIENT_HPP__

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {
        namespace __hidden {
            namespace __impl {

                template <
                        typename __ReceiverType,                // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType,                 // NOLINT(bugprone-reserved-identifier)
                        typename __OfCollectionType             // NOLINT(bugprone-reserved-identifier)
                > class __ReplacingOfClient {                   // NOLINT(bugprone-reserved-identifier)

                private:
                    using ElementType = __ElementType;

                private:
                    using OfCollectionType = __OfCollectionType;

                public:
                    template <
                            typename __VElementType = __ElementType, // NOLINT(bugprone-reserved-identifier)
                            cds :: meta :: EnableIf <
                                    cds :: meta :: isCopyAssignable < __VElementType > ()
                            >
                    > auto replaceOf (
                            Size                        count,
                            __OfCollectionType  const & of,
                            ElementType         const & with
                    ) noexcept -> Size;

                public:
                    template <
                            typename __VElementType = __ElementType, // NOLINT(bugprone-reserved-identifier)
                            cds :: meta :: EnableIf <
                                    cds :: meta :: isCopyAssignable < __VElementType > ()
                            >
                    > auto replaceFirstOf (
                            __OfCollectionType  const & of,
                            ElementType         const & with
                    ) noexcept -> bool;

                public:
                    template <
                            typename __VElementType = __ElementType, // NOLINT(bugprone-reserved-identifier)
                            cds :: meta :: EnableIf <
                                    cds :: meta :: isMoveAssignable < __VElementType > ()
                            >
                    > auto replaceFirstOf (
                            __OfCollectionType  const & of,
                            ElementType              && with
                    ) noexcept -> bool;

                public:
                    template <
                            typename __VElementType = __ElementType, // NOLINT(bugprone-reserved-identifier)
                            cds :: meta :: EnableIf <
                                    cds :: meta :: isCopyAssignable < __VElementType > ()
                            >
                    > auto replaceLastOf (
                            __OfCollectionType  const & of,
                            ElementType         const & with
                    ) noexcept -> bool;

                public:
                    template <
                            typename __VElementType = __ElementType, // NOLINT(bugprone-reserved-identifier)
                            cds :: meta :: EnableIf <
                                    cds :: meta :: isMoveAssignable < __VElementType > ()
                            >
                    > auto replaceLastOf (
                            __OfCollectionType  const & of,
                            ElementType              && with
                    ) noexcept -> bool;

                public:
                    template <
                            typename __VElementType = __ElementType, // NOLINT(bugprone-reserved-identifier)
                            cds :: meta :: EnableIf <
                                    cds :: meta :: isCopyAssignable < __VElementType > ()
                            >
                    > auto replaceAllOf (
                            __OfCollectionType  const & of,
                            ElementType         const & with
                    ) noexcept -> Size;

                public:
                    template <
                            typename __VElementType = __ElementType, // NOLINT(bugprone-reserved-identifier)
                            cds :: meta :: EnableIf <
                                    cds :: meta :: isCopyAssignable < __VElementType > ()
                            >
                    > auto replaceNotOf (
                            Size                        count,
                            __OfCollectionType  const & of,
                            ElementType         const & with
                    ) noexcept -> Size;

                public:
                    template <
                            typename __VElementType = __ElementType, // NOLINT(bugprone-reserved-identifier)
                            cds :: meta :: EnableIf <
                                    cds :: meta :: isCopyAssignable < __VElementType > ()
                            >
                    > auto replaceFirstNotOf (
                            __OfCollectionType  const & of,
                            ElementType         const & with
                    ) noexcept -> bool;

                public:
                    template <
                            typename __VElementType = __ElementType, // NOLINT(bugprone-reserved-identifier)
                            cds :: meta :: EnableIf <
                                    cds :: meta :: isMoveAssignable < __VElementType > ()
                            >
                    > auto replaceFirstNotOf (
                            __OfCollectionType  const & of,
                            ElementType              && with
                    ) noexcept -> bool;

                public:
                    template <
                            typename __VElementType = __ElementType, // NOLINT(bugprone-reserved-identifier)
                            cds :: meta :: EnableIf <
                                    cds :: meta :: isCopyAssignable < __VElementType > ()
                            >
                    > auto replaceLastNotOf (
                            __OfCollectionType  const & of,
                            ElementType         const & with
                    ) noexcept -> bool;

                public:
                    template <
                            typename __VElementType = __ElementType, // NOLINT(bugprone-reserved-identifier)
                            cds :: meta :: EnableIf <
                                    cds :: meta :: isMoveAssignable < __VElementType > ()
                            >
                    > auto replaceLastNotOf (
                            __OfCollectionType  const & of,
                            ElementType              && with
                    ) noexcept -> bool;

                public:
                    template <
                            typename __VElementType = __ElementType, // NOLINT(bugprone-reserved-identifier)
                            cds :: meta :: EnableIf <
                                    cds :: meta :: isCopyAssignable < __VElementType > ()
                            >
                    > auto replaceAllNotOf (
                            __OfCollectionType  const & of,
                            ElementType         const & with
                    ) noexcept -> Size;
                };

            }
        }
    }
}

#endif // __CDS_SHARED_REPLACING_OF_CLIENT_HPP__
