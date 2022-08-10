//
// Created by loghin on 6/30/2022.
//

#ifndef __CDS_SHARED_REPLACE_OF_COMPOSITE_CLIENT_IMPL_HPP__
#define __CDS_SHARED_REPLACE_OF_COMPOSITE_CLIENT_IMPL_HPP__

namespace cds {                 // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {    // NOLINT(modernize-concat-nested-namespaces)
        namespace __hidden {    // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier)
            namespace __impl {  // NOLINT(bugprone-reserved-identifier)

                template <
                        typename                                                    __ReceiverType,     // NOLINT(bugprone-reserved-identifier)
                        typename                                                    __ElementType,      // NOLINT(bugprone-reserved-identifier)
                        typename                                                    __OfCollectionType, // NOLINT(bugprone-reserved-identifier)
                        __ContainsFunction < __OfCollectionType, __ElementType >    __contains          // NOLINT(bugprone-reserved-identifier)
                > template <
                        typename __TElementType,                                                        // NOLINT(bugprone-reserved-identifier)
                        cds :: meta :: EnableIf <
                                cds :: meta :: isCopyAssignable < __TElementType > ()
                        >
                > auto __ReplaceOfCompositeClient <
                        __ReceiverType,
                        __ElementType,
                        __OfCollectionType,
                        __contains
                > :: replaceOf (
                        Size                        count,
                        __OfCollectionType  const & of,
                        ElementType         const & with
                ) noexcept -> Size {

                    Size replacedCount = 0ULL;
                    for (
                            auto
                                iterator    = reinterpret_cast < __ReceiverType * > ( this )->begin(),
                                end         = reinterpret_cast < __ReceiverType * > ( this )->end();

                            iterator != end && replacedCount < count;
                            ++ iterator
                    ) {
                        if ( __contains ( of, * iterator ) ) {
                            * iterator = with;
                            ++ replacedCount;
                        }
                    }

                    return replacedCount;
                }


                template <
                        typename                                                    __ReceiverType,     // NOLINT(bugprone-reserved-identifier)
                        typename                                                    __ElementType,      // NOLINT(bugprone-reserved-identifier)
                        typename                                                    __OfCollectionType, // NOLINT(bugprone-reserved-identifier)
                        __ContainsFunction < __OfCollectionType, __ElementType >    __contains          // NOLINT(bugprone-reserved-identifier)
                > template <
                        typename __TElementType,                                                        // NOLINT(bugprone-reserved-identifier)
                        cds :: meta :: EnableIf <
                                cds :: meta :: isCopyAssignable < __TElementType > ()
                        >
                > auto __ReplaceOfCompositeClient <
                        __ReceiverType,
                        __ElementType,
                        __OfCollectionType,
                        __contains
                > :: replaceFirstOf (
                        __OfCollectionType  const & of,
                        ElementType         const & with
                ) noexcept -> bool {

                    for (
                            auto
                                iterator    = reinterpret_cast < __ReceiverType * > ( this )->begin(),
                                end         = reinterpret_cast < __ReceiverType * > ( this )->end();

                            iterator != end;
                            ++ iterator
                    ) {
                        if ( __contains ( of, * iterator ) ) {
                            * iterator = with;
                            return true;
                        }
                    }

                    return false;
                }


                template <
                        typename                                                    __ReceiverType,     // NOLINT(bugprone-reserved-identifier)
                        typename                                                    __ElementType,      // NOLINT(bugprone-reserved-identifier)
                        typename                                                    __OfCollectionType, // NOLINT(bugprone-reserved-identifier)
                        __ContainsFunction < __OfCollectionType, __ElementType >    __contains          // NOLINT(bugprone-reserved-identifier)
                > template <
                        typename __TElementType,                                                        // NOLINT(bugprone-reserved-identifier)
                        cds :: meta :: EnableIf <
                                cds :: meta :: isMoveAssignable < __TElementType > ()
                        >
                > auto __ReplaceOfCompositeClient <
                        __ReceiverType,
                        __ElementType,
                        __OfCollectionType,
                        __contains
                > :: replaceFirstOf (
                        __OfCollectionType  const & of,
                        ElementType              && with
                ) noexcept -> bool {

                    for (
                            auto
                                iterator    = reinterpret_cast < __ReceiverType * > ( this )->begin(),
                                end         = reinterpret_cast < __ReceiverType * > ( this )->end();

                            iterator != end;
                            ++ iterator
                    ) {
                        if ( __contains ( of, * iterator ) ) {
                            * iterator = std :: move ( with );
                            return true;
                        }
                    }

                    return false;
                }


                template <
                        typename                                                    __ReceiverType,     // NOLINT(bugprone-reserved-identifier)
                        typename                                                    __ElementType,      // NOLINT(bugprone-reserved-identifier)
                        typename                                                    __OfCollectionType, // NOLINT(bugprone-reserved-identifier)
                        __ContainsFunction < __OfCollectionType, __ElementType >    __contains          // NOLINT(bugprone-reserved-identifier)
                > template <
                        typename __TElementType,                                                        // NOLINT(bugprone-reserved-identifier)
                        cds :: meta :: EnableIf <
                                cds :: meta :: isCopyAssignable < __TElementType > ()
                        >
                > auto __ReplaceOfCompositeClient <
                        __ReceiverType,
                        __ElementType,
                        __OfCollectionType,
                        __contains
                > :: replaceLastOf (
                        __OfCollectionType  const & of,
                        ElementType         const & with
                ) noexcept -> bool {

                    for (
                            auto
                                iterator    = reinterpret_cast < __ReceiverType * > ( this )->rbegin(),
                                end         = reinterpret_cast < __ReceiverType * > ( this )->rend();

                            iterator != end;
                            ++ iterator
                    ) {
                        if ( __contains ( of, * iterator ) ) {
                            * iterator = with;
                            return true;
                        }
                    }

                    return false;
                }


                template <
                        typename                                                    __ReceiverType,     // NOLINT(bugprone-reserved-identifier)
                        typename                                                    __ElementType,      // NOLINT(bugprone-reserved-identifier)
                        typename                                                    __OfCollectionType, // NOLINT(bugprone-reserved-identifier)
                        __ContainsFunction < __OfCollectionType, __ElementType >    __contains          // NOLINT(bugprone-reserved-identifier)
                > template <
                        typename __TElementType,                                                        // NOLINT(bugprone-reserved-identifier)
                        cds :: meta :: EnableIf <
                                cds :: meta :: isMoveAssignable < __TElementType > ()
                        >
                > auto __ReplaceOfCompositeClient <
                        __ReceiverType,
                        __ElementType,
                        __OfCollectionType,
                        __contains
                > :: replaceLastOf (
                        __OfCollectionType  const & of,
                        ElementType              && with
                ) noexcept -> bool {

                    for (
                            auto
                                iterator    = reinterpret_cast < __ReceiverType * > ( this )->rbegin(),
                                end         = reinterpret_cast < __ReceiverType * > ( this )->rend();

                            iterator != end;
                            ++ iterator
                    ) {
                        if ( __contains ( of, * iterator ) ) {
                            * iterator = std :: move ( with );
                            return true;
                        }
                    }

                    return false;
                }


                template <
                        typename                                                    __ReceiverType,     // NOLINT(bugprone-reserved-identifier)
                        typename                                                    __ElementType,      // NOLINT(bugprone-reserved-identifier)
                        typename                                                    __OfCollectionType, // NOLINT(bugprone-reserved-identifier)
                        __ContainsFunction < __OfCollectionType, __ElementType >    __contains          // NOLINT(bugprone-reserved-identifier)
                > template <
                        typename __TElementType,                                                        // NOLINT(bugprone-reserved-identifier)
                        cds :: meta :: EnableIf <
                                cds :: meta :: isCopyAssignable < __TElementType > ()
                        >
                > auto __ReplaceOfCompositeClient <
                        __ReceiverType,
                        __ElementType,
                        __OfCollectionType,
                        __contains
                > :: replaceAllOf (
                        __OfCollectionType  const & of,
                        ElementType         const & with
                ) noexcept -> Size {

                    Size replacedCount = 0ULL;
                    for (
                            auto
                                iterator    = reinterpret_cast < __ReceiverType * > ( this )->rbegin(),
                                end         = reinterpret_cast < __ReceiverType * > ( this )->rend();

                            iterator != end;
                            ++ iterator
                    ) {
                        if ( __contains ( of, * iterator ) ) {
                            * iterator = std :: move ( with );
                            ++ replacedCount;
                        }
                    }

                    return replacedCount;
                }


                template <
                        typename                                                    __ReceiverType,     // NOLINT(bugprone-reserved-identifier)
                        typename                                                    __ElementType,      // NOLINT(bugprone-reserved-identifier)
                        typename                                                    __OfCollectionType, // NOLINT(bugprone-reserved-identifier)
                        __ContainsFunction < __OfCollectionType, __ElementType >    __contains          // NOLINT(bugprone-reserved-identifier)
                > template <
                        typename __TElementType,                                                        // NOLINT(bugprone-reserved-identifier)
                        cds :: meta :: EnableIf <
                                cds :: meta :: isCopyAssignable < __TElementType > ()
                        >
                > auto __ReplaceOfCompositeClient <
                        __ReceiverType,
                        __ElementType,
                        __OfCollectionType,
                        __contains
                > :: replaceNotOf (
                        Size                        count,
                        __OfCollectionType  const & of,
                        ElementType         const & with
                ) noexcept -> Size {

                    Size replacedCount = 0ULL;
                    for (
                            auto
                                iterator    = reinterpret_cast < __ReceiverType * > ( this )->begin(),
                                end         = reinterpret_cast < __ReceiverType * > ( this )->end();

                            iterator != end && replacedCount < count;
                            ++ iterator
                    ) {
                        if ( ! __contains ( of, * iterator ) ) {
                            * iterator = with;
                            ++ replacedCount;
                        }
                    }

                    return replacedCount;
                }


                template <
                        typename                                                    __ReceiverType,     // NOLINT(bugprone-reserved-identifier)
                        typename                                                    __ElementType,      // NOLINT(bugprone-reserved-identifier)
                        typename                                                    __OfCollectionType, // NOLINT(bugprone-reserved-identifier)
                        __ContainsFunction < __OfCollectionType, __ElementType >    __contains          // NOLINT(bugprone-reserved-identifier)
                > template <
                        typename __TElementType,                                                        // NOLINT(bugprone-reserved-identifier)
                        cds :: meta :: EnableIf <
                                cds :: meta :: isCopyAssignable < __TElementType > ()
                        >
                > auto __ReplaceOfCompositeClient <
                        __ReceiverType,
                        __ElementType,
                        __OfCollectionType,
                        __contains
                > :: replaceFirstNotOf (
                        __OfCollectionType  const & of,
                        ElementType         const & with
                ) noexcept -> bool {

                    for (
                            auto
                                iterator    = reinterpret_cast < __ReceiverType * > ( this )->begin(),
                                end         = reinterpret_cast < __ReceiverType * > ( this )->end();

                            iterator != end;
                            ++ iterator
                    ) {
                        if ( ! __contains ( of, * iterator ) ) {
                            * iterator = with;
                            return true;
                        }
                    }

                    return false;
                }


                template <
                        typename                                                    __ReceiverType,     // NOLINT(bugprone-reserved-identifier)
                        typename                                                    __ElementType,      // NOLINT(bugprone-reserved-identifier)
                        typename                                                    __OfCollectionType, // NOLINT(bugprone-reserved-identifier)
                        __ContainsFunction < __OfCollectionType, __ElementType >    __contains          // NOLINT(bugprone-reserved-identifier)
                > template <
                        typename __TElementType,                                                        // NOLINT(bugprone-reserved-identifier)
                        cds :: meta :: EnableIf <
                                cds :: meta :: isMoveAssignable < __TElementType > ()
                        >
                > auto __ReplaceOfCompositeClient <
                        __ReceiverType,
                        __ElementType,
                        __OfCollectionType,
                        __contains
                > :: replaceFirstNotOf (
                        __OfCollectionType  const & of,
                        ElementType              && with
                ) noexcept -> bool {

                    for (
                            auto
                                iterator    = reinterpret_cast < __ReceiverType * > ( this )->begin(),
                                end         = reinterpret_cast < __ReceiverType * > ( this )->end();

                            iterator != end;
                            ++ iterator
                    ) {
                        if ( ! __contains ( of, * iterator ) ) {
                            * iterator = std :: move ( with );
                            return true;
                        }
                    }

                    return false;
                }


                template <
                        typename                                                    __ReceiverType,     // NOLINT(bugprone-reserved-identifier)
                        typename                                                    __ElementType,      // NOLINT(bugprone-reserved-identifier)
                        typename                                                    __OfCollectionType, // NOLINT(bugprone-reserved-identifier)
                        __ContainsFunction < __OfCollectionType, __ElementType >    __contains          // NOLINT(bugprone-reserved-identifier)
                > template <
                        typename __TElementType,                                                        // NOLINT(bugprone-reserved-identifier)
                        cds :: meta :: EnableIf <
                                cds :: meta :: isCopyAssignable < __TElementType > ()
                        >
                > auto __ReplaceOfCompositeClient <
                        __ReceiverType,
                        __ElementType,
                        __OfCollectionType,
                        __contains
                > :: replaceLastNotOf (
                        __OfCollectionType  const & of,
                        ElementType         const & with
                ) noexcept -> bool {

                    for (
                            auto
                                iterator    = reinterpret_cast < __ReceiverType * > ( this )->rbegin(),
                                end         = reinterpret_cast < __ReceiverType * > ( this )->rend();

                            iterator != end;
                            ++ iterator
                    ) {
                        if ( ! __contains ( of, * iterator ) ) {
                            * iterator = with;
                            return true;
                        }
                    }

                    return false;
                }


                template <
                        typename                                                    __ReceiverType,     // NOLINT(bugprone-reserved-identifier)
                        typename                                                    __ElementType,      // NOLINT(bugprone-reserved-identifier)
                        typename                                                    __OfCollectionType, // NOLINT(bugprone-reserved-identifier)
                        __ContainsFunction < __OfCollectionType, __ElementType >    __contains          // NOLINT(bugprone-reserved-identifier)
                > template <
                        typename __TElementType,                                                        // NOLINT(bugprone-reserved-identifier)
                        cds :: meta :: EnableIf <
                                cds :: meta :: isMoveAssignable < __TElementType > ()
                        >
                > auto __ReplaceOfCompositeClient <
                        __ReceiverType,
                        __ElementType,
                        __OfCollectionType,
                        __contains
                > :: replaceLastNotOf (
                        __OfCollectionType  const & of,
                        ElementType              && with
                ) noexcept -> bool {

                    for (
                            auto
                                iterator    = reinterpret_cast < __ReceiverType * > ( this )->rbegin(),
                                end         = reinterpret_cast < __ReceiverType * > ( this )->rend();

                            iterator != end;
                            ++ iterator
                    ) {
                        if ( ! __contains ( of, * iterator ) ) {
                            * iterator = std :: move ( with );
                            return true;
                        }
                    }

                    return false;
                }


                template <
                        typename                                                    __ReceiverType,     // NOLINT(bugprone-reserved-identifier)
                        typename                                                    __ElementType,      // NOLINT(bugprone-reserved-identifier)
                        typename                                                    __OfCollectionType, // NOLINT(bugprone-reserved-identifier)
                        __ContainsFunction < __OfCollectionType, __ElementType >    __contains          // NOLINT(bugprone-reserved-identifier)
                > template <
                        typename __TElementType,                                                        // NOLINT(bugprone-reserved-identifier)
                        cds :: meta :: EnableIf <
                                cds :: meta :: isCopyAssignable < __TElementType > ()
                        >
                > auto __ReplaceOfCompositeClient <
                        __ReceiverType,
                        __ElementType,
                        __OfCollectionType,
                        __contains
                > :: replaceAllNotOf (
                        __OfCollectionType  const & of,
                        ElementType         const & with
                ) noexcept -> Size {

                    Size replacedCount = 0ULL;
                    for (
                            auto
                                iterator    = reinterpret_cast < __ReceiverType * > ( this )->rbegin(),
                                end         = reinterpret_cast < __ReceiverType * > ( this )->rend();

                            iterator != end;
                            ++ iterator
                    ) {
                        if ( ! __contains ( of, * iterator ) ) {
                            * iterator = std :: move ( with );
                            ++ replacedCount;
                        }
                    }

                    return replacedCount;
                }

            }
        }
    }
}

#endif // __CDS_SHARED_REPLACE_OF_COMPOSITE_CLIENT_IMPL_HPP__
