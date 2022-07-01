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
                        typename                                                    __ReceiverType,     // NOLINT(bugprone-reserved-identifier)
                        typename                                                    __ElementType,      // NOLINT(bugprone-reserved-identifier)
                        typename                                                    __OfCollectionType, // NOLINT(bugprone-reserved-identifier)
                        __ContainsFunction < __OfCollectionType, __ElementType >    __contains          // NOLINT(bugprone-reserved-identifier)
                > class __ReplacingOfClient {                                                           // NOLINT(bugprone-reserved-identifier)

                private:
                    using ElementType = __ElementType;

                private:
                    using OfCollectionType = __OfCollectionType;

                public:
                    template <
                            typename __TElementType = __ElementType, // NOLINT(bugprone-reserved-identifier)
                            cds :: meta :: EnableIf <
                                    cds :: meta :: isCopyAssignable < __TElementType > ()
                            > = 0
                    > auto replaceOf (
                            Size                        count,
                            __OfCollectionType  const & of,
                            ElementType         const & with
                    ) noexcept -> Size;

                public:
                    template <
                            typename __TElementType = __ElementType, // NOLINT(bugprone-reserved-identifier)
                            cds :: meta :: EnableIf <
                                    cds :: meta :: isCopyAssignable < __TElementType > ()
                            > = 0
                    > auto replaceFirstOf (
                            __OfCollectionType  const & of,
                            ElementType         const & with
                    ) noexcept -> bool;

                public:
                    template <
                            typename __TElementType = __ElementType, // NOLINT(bugprone-reserved-identifier)
                            cds :: meta :: EnableIf <
                                    cds :: meta :: isMoveAssignable < __TElementType > ()
                            > = 0
                    > auto replaceFirstOf (
                            __OfCollectionType  const & of,
                            ElementType              && with
                    ) noexcept -> bool;

                public:
                    template <
                            typename __TElementType = __ElementType, // NOLINT(bugprone-reserved-identifier)
                            cds :: meta :: EnableIf <
                                    cds :: meta :: isCopyAssignable < __TElementType > ()
                            > = 0
                    > auto replaceLastOf (
                            __OfCollectionType  const & of,
                            ElementType         const & with
                    ) noexcept -> bool;

                public:
                    template <
                            typename __TElementType = __ElementType, // NOLINT(bugprone-reserved-identifier)
                            cds :: meta :: EnableIf <
                                    cds :: meta :: isMoveAssignable < __TElementType > ()
                            > = 0
                    > auto replaceLastOf (
                            __OfCollectionType  const & of,
                            ElementType              && with
                    ) noexcept -> bool;

                public:
                    template <
                            typename __TElementType = __ElementType, // NOLINT(bugprone-reserved-identifier)
                            cds :: meta :: EnableIf <
                                    cds :: meta :: isCopyAssignable < __TElementType > ()
                            > = 0
                    > auto replaceAllOf (
                            __OfCollectionType  const & of,
                            ElementType         const & with
                    ) noexcept -> Size;

                public:
                    template <
                            typename __TElementType = __ElementType, // NOLINT(bugprone-reserved-identifier)
                            cds :: meta :: EnableIf <
                                    cds :: meta :: isCopyAssignable < __TElementType > ()
                            > = 0
                    > auto replaceNotOf (
                            Size                        count,
                            __OfCollectionType  const & of,
                            ElementType         const & with
                    ) noexcept -> Size;

                public:
                    template <
                            typename __TElementType = __ElementType, // NOLINT(bugprone-reserved-identifier)
                            cds :: meta :: EnableIf <
                                    cds :: meta :: isCopyAssignable < __TElementType > ()
                            > = 0
                    > auto replaceFirstNotOf (
                            __OfCollectionType  const & of,
                            ElementType         const & with
                    ) noexcept -> bool;

                public:
                    template <
                            typename __TElementType = __ElementType, // NOLINT(bugprone-reserved-identifier)
                            cds :: meta :: EnableIf <
                                    cds :: meta :: isMoveAssignable < __TElementType > ()
                            > = 0
                    > auto replaceFirstNotOf (
                            __OfCollectionType  const & of,
                            ElementType              && with
                    ) noexcept -> bool;

                public:
                    template <
                            typename __TElementType = __ElementType, // NOLINT(bugprone-reserved-identifier)
                            cds :: meta :: EnableIf <
                                    cds :: meta :: isCopyAssignable < __TElementType > ()
                            > = 0
                    > auto replaceLastNotOf (
                            __OfCollectionType  const & of,
                            ElementType         const & with
                    ) noexcept -> bool;

                public:
                    template <
                            typename __TElementType = __ElementType, // NOLINT(bugprone-reserved-identifier)
                            cds :: meta :: EnableIf <
                                    cds :: meta :: isMoveAssignable < __TElementType > ()
                            > = 0
                    > auto replaceLastNotOf (
                            __OfCollectionType  const & of,
                            ElementType              && with
                    ) noexcept -> bool;

                public:
                    template <
                            typename __TElementType = __ElementType, // NOLINT(bugprone-reserved-identifier)
                            cds :: meta :: EnableIf <
                                    cds :: meta :: isCopyAssignable < __TElementType > ()
                            > = 0
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
