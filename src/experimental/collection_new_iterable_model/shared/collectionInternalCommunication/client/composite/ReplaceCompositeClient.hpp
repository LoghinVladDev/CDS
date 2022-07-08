//
// Created by loghin on 6/30/2022.
//

#ifndef __CDS_SHARED_REPLACE_COMPOSITE_CLIENT_HPP__
#define __CDS_SHARED_REPLACE_COMPOSITE_CLIENT_HPP__

namespace cds {                 // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {    // NOLINT(modernize-concat-nested-namespaces)
        namespace __hidden {    // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier)
            namespace __impl {  // NOLINT(bugprone-reserved-identifier)

                template <
                        typename __ReceiverType,                // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType                  // NOLINT(bugprone-reserved-identifier)
                > class __ReplaceCompositeClient {              // NOLINT(bugprone-reserved-identifier)

                private:
                    using ElementType = __ElementType;

                protected:
                    template <
                            typename __TElementType = __ElementType, // NOLINT(bugprone-reserved-identifier)
                            cds :: meta :: EnableIf <
                                    cds :: meta :: isCopyAssignable < __TElementType > ()
                            > = 0
                    > auto replace (
                            Size                count,
                            ElementType const & what,
                            ElementType const & with
                    ) noexcept -> Size;

                protected:
                    template <
                            typename __TElementType = __ElementType, // NOLINT(bugprone-reserved-identifier)
                            cds :: meta :: EnableIf <
                                    cds :: meta :: isCopyAssignable < __TElementType > ()
                            > = 0
                    > auto replaceFirst (
                            ElementType const & what,
                            ElementType const & with
                    ) noexcept -> bool;

                protected:
                    template <
                            typename __TElementType = __ElementType, // NOLINT(bugprone-reserved-identifier)
                            cds :: meta :: EnableIf <
                                    cds :: meta :: isMoveAssignable < __TElementType > ()
                            > = 0
                    > auto replaceFirst (
                            ElementType const & what,
                            ElementType      && with
                    ) noexcept -> bool;

                protected:
                    template <
                            typename __TElementType = __ElementType, // NOLINT(bugprone-reserved-identifier)
                            cds :: meta :: EnableIf <
                                    cds :: meta :: isCopyAssignable < __TElementType > ()
                            > = 0
                    > auto replaceLast (
                            ElementType const & what,
                            ElementType const & with
                    ) noexcept -> bool;

                protected:
                    template <
                            typename __TElementType = __ElementType, // NOLINT(bugprone-reserved-identifier)
                            cds :: meta :: EnableIf <
                                    cds :: meta :: isMoveAssignable < __TElementType > ()
                            > = 0
                    > auto replaceLast (
                            ElementType const & what,
                            ElementType      && with
                    ) noexcept -> bool;

                protected:
                    template <
                            typename __TElementType = __ElementType, // NOLINT(bugprone-reserved-identifier)
                            cds :: meta :: EnableIf <
                                    cds :: meta :: isCopyAssignable < __TElementType > ()
                            > = 0
                    > auto replaceAll (
                            ElementType const & what,
                            ElementType const & with
                    ) noexcept -> Size;
                };


                template <
                        typename __ReceiverType,            // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType              // NOLINT(bugprone-reserved-identifier)
                > using __LocalReplaceCompositeClient =     // NOLINT(bugprone-reserved-identifier)
                        __ReplaceCompositeClient <
                                __ReceiverType,
                                __ElementType
                        >;

            }
        }
    }
}

#endif // __CDS_SHARED_REPLACE_COMPOSITE_CLIENT_HPP__
