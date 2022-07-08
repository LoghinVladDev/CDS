//
// Created by loghin on 6/30/2022.
//

#ifndef __CDS_SHARED_REPLACE_CLIENT_IMPL_HPP__
#define __CDS_SHARED_REPLACE_CLIENT_IMPL_HPP__

namespace cds {                 // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {    // NOLINT(modernize-concat-nested-namespaces)
        namespace __hidden {    // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier)
            namespace __impl {  // NOLINT(bugprone-reserved-identifier)

                template <
                        typename __ReceiverType,                // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType                  // NOLINT(bugprone-reserved-identifier)
                > template <
                        typename __TElementType,                // NOLINT(bugprone-reserved-identifier)
                        cds :: meta :: EnableIf <
                                cds :: meta :: isCopyAssignable < __TElementType > ()
                        >
                > auto __ReplaceClient <
                        __ReceiverType,
                        __ElementType
                > :: replace (
                        Size                count,
                        ElementType const & what,
                        ElementType const & with
                ) noexcept -> Size {

                    Size replacedCount = 0ULL;
                    for (
                            auto
                                iterator    = static_cast < __ReceiverType * > ( this )->begin(),
                                end         = static_cast < __ReceiverType * > ( this )->end();

                            iterator != end && replacedCount < count;
                            ++ iterator
                    ) {
                        if ( cds :: meta :: equals ( * iterator, what ) ) {
                            * iterator = with;
                            ++ replacedCount;
                        }
                    }

                    return replacedCount;
                }


                template <
                        typename __ReceiverType,                // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType                  // NOLINT(bugprone-reserved-identifier)
                > template <
                        typename __TElementType,                // NOLINT(bugprone-reserved-identifier)
                        cds :: meta :: EnableIf <
                                cds :: meta :: isCopyAssignable < __TElementType > ()
                        >
                > auto __ReplaceClient <
                        __ReceiverType,
                        __ElementType
                > :: replaceFirst (
                        ElementType const & what,
                        ElementType const & with
                ) noexcept -> bool {

                    for (
                            auto
                                iterator    = static_cast < __ReceiverType * > ( this )->begin(),
                                end         = static_cast < __ReceiverType * > ( this )->end();

                            iterator != end;
                            ++ iterator
                    ) {
                        if ( cds :: meta :: equals ( * iterator, what ) ) {
                            * iterator = with;
                            return true;
                        }
                    }

                    return false;
                }


                template <
                        typename __ReceiverType,                // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType                  // NOLINT(bugprone-reserved-identifier)
                > template <
                        typename __TElementType,                // NOLINT(bugprone-reserved-identifier)
                        cds :: meta :: EnableIf <
                                cds :: meta :: isMoveAssignable < __TElementType > ()
                        >
                > auto __ReplaceClient <
                        __ReceiverType,
                        __ElementType
                > :: replaceFirst (
                        ElementType const & what,
                        ElementType      && with
                ) noexcept -> bool {

                    for (
                            auto
                                iterator    = static_cast < __ReceiverType * > ( this )->begin(),
                                end         = static_cast < __ReceiverType * > ( this )->end();

                            iterator != end;
                            ++ iterator
                    ) {
                        if ( cds :: meta :: equals ( * iterator, what ) ) {
                            * iterator = std :: move ( with );
                            return true;
                        }
                    }

                    return false;
                }


                template <
                        typename __ReceiverType,                // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType                  // NOLINT(bugprone-reserved-identifier)
                > template <
                        typename __TElementType,                // NOLINT(bugprone-reserved-identifier)
                        cds :: meta :: EnableIf <
                                cds :: meta :: isCopyAssignable < __TElementType > ()
                        >
                > auto __ReplaceClient <
                        __ReceiverType,
                        __ElementType
                > :: replaceLast (
                        ElementType const & what,
                        ElementType const & with
                ) noexcept -> bool {

                    for (
                            auto
                                iterator    = static_cast < __ReceiverType * > ( this )->rbegin(),
                                end         = static_cast < __ReceiverType * > ( this )->rend();

                            iterator != end;
                            ++ iterator
                    ) {
                        if ( cds :: meta :: equals ( * iterator, what ) ) {
                            * iterator = with;
                            return true;
                        }
                    }

                    return false;
                }


                template <
                        typename __ReceiverType,                // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType                  // NOLINT(bugprone-reserved-identifier)
                > template <
                        typename __TElementType,                // NOLINT(bugprone-reserved-identifier)
                        cds :: meta :: EnableIf <
                                cds :: meta :: isMoveAssignable < __TElementType > ()
                        >
                > auto __ReplaceClient <
                        __ReceiverType,
                        __ElementType
                > :: replaceLast (
                        ElementType const & what,
                        ElementType      && with
                ) noexcept -> bool {

                    for (
                            auto
                                iterator    = static_cast < __ReceiverType * > ( this )->rbegin(),
                                end         = static_cast < __ReceiverType * > ( this )->rend();

                            iterator != end;
                            ++ iterator
                    ) {
                        if ( cds :: meta :: equals ( * iterator, what ) ) {
                            * iterator = std :: move ( with );
                            return true;
                        }
                    }

                    return false;
                }


                template <
                        typename __ReceiverType,                // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType                  // NOLINT(bugprone-reserved-identifier)
                > template <
                        typename __TElementType,                // NOLINT(bugprone-reserved-identifier)
                        cds :: meta :: EnableIf <
                                cds :: meta :: isCopyAssignable < __TElementType > ()
                        >
                > auto __ReplaceClient <
                        __ReceiverType,
                        __ElementType
                > :: replaceAll (
                        ElementType const & what,
                        ElementType const & with
                ) noexcept -> Size {

                    Size replacedCount = 0ULL;
                    for (
                            auto
                                iterator    = static_cast < __ReceiverType * > ( this )->rbegin(),
                                end         = static_cast < __ReceiverType * > ( this )->rend();

                            iterator != end;
                            ++ iterator
                    ) {
                        if ( cds :: meta :: equals ( * iterator, what ) ) {
                            * iterator = with;
                            ++ replacedCount;
                        }
                    }

                    return replacedCount;
                }

            }
        }
    }
}

#endif // __CDS_SHARED_REPLACE_CLIENT_IMPL_HPP__
