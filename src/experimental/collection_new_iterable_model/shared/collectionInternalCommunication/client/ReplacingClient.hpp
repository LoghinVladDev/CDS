//
// Created by uic70278 on 6/30/2022.
//

#ifndef __CDS_SHARED_REPLACING_CLIENT_HPP__
#define __CDS_SHARED_REPLACING_CLIENT_HPP__

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {
        namespace __hidden {
            namespace __impl {

                template <
                        typename __ReceiverType,                // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType                  // NOLINT(bugprone-reserved-identifier)
                > class __ReplacingClient {                     // NOLINT(bugprone-reserved-identifier)

                private:
                    using ElementType = __ElementType;

                protected:
                    template <
                            typename __VElementType = __ElementType, // NOLINT(bugprone-reserved-identifier)
                            cds :: meta :: EnableIf <
                                    cds :: meta :: isCopyAssignable < __VElementType > ()
                            > = 0
                    > auto replace (
                            Size                count,
                            ElementType const & what,
                            ElementType const & with
                    ) noexcept -> Size;

                protected:
                    template <
                            typename __VElementType = __ElementType, // NOLINT(bugprone-reserved-identifier)
                            cds :: meta :: EnableIf <
                                    cds :: meta :: isCopyAssignable < __VElementType > ()
                            > = 0
                    > auto replaceFirst (
                            ElementType const & what,
                            ElementType const & with
                    ) noexcept -> bool;

                protected:
                    template <
                            typename __VElementType = __ElementType, // NOLINT(bugprone-reserved-identifier)
                            cds :: meta :: EnableIf <
                                    cds :: meta :: isMoveAssignable < __VElementType > ()
                            > = 0
                    > auto replaceFirst (
                            ElementType const & what,
                            ElementType      && with
                    ) noexcept -> bool;

                protected:
                    template <
                            typename __VElementType = __ElementType, // NOLINT(bugprone-reserved-identifier)
                            cds :: meta :: EnableIf <
                                    cds :: meta :: isCopyAssignable < __VElementType > ()
                            > = 0
                    > auto replaceLast (
                            ElementType const & what,
                            ElementType const & with
                    ) noexcept -> bool;

                protected:
                    template <
                            typename __VElementType = __ElementType, // NOLINT(bugprone-reserved-identifier)
                            cds :: meta :: EnableIf <
                                    cds :: meta :: isMoveAssignable < __VElementType > ()
                            > = 0
                    > auto replaceLast (
                            ElementType const & what,
                            ElementType      && with
                    ) noexcept -> bool;

                protected:
                    template <
                            typename __VElementType = __ElementType, // NOLINT(bugprone-reserved-identifier)
                            cds :: meta :: EnableIf <
                                    cds :: meta :: isCopyAssignable < __VElementType > ()
                            > = 0
                    > auto replaceAll (
                            ElementType const & what,
                            ElementType const & with
                    ) noexcept -> Size;
                };

            }
        }
    }
}

#endif // __CDS_SHARED_REPLACING_CLIENT_HPP__