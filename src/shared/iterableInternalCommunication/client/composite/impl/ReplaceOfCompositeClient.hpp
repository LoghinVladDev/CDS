/*
 * Created by loghin on 6/30/2022.
 */

#ifndef __CDS_SHARED_REPLACE_OF_COMPOSITE_CLIENT_IMPL_HPP__ /* NOLINT(llvm-header-guard) */
#define __CDS_SHARED_REPLACE_OF_COMPOSITE_CLIENT_IMPL_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

namespace cds {             /* NOLINT(modernize-concat-nested-namespaces) */
    namespace __hidden {    /* NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        namespace __impl {  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            template <
                    typename                                                                                __ReceiverType,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                                __ElementType,      /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                                __OfCollectionType, /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: PredicateFunction < __OfCollectionType const &, __ElementType const & >   __contains          /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > template <
                    typename                                                                                __TElementType,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
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
                    typename                                                                                __ReceiverType,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                                __ElementType,      /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                                __OfCollectionType, /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: PredicateFunction < __OfCollectionType const &, __ElementType const & >   __contains          /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > template <
                    typename                                                                                __TElementType,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
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
                    typename                                                                                __ReceiverType,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                                __ElementType,      /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                                __OfCollectionType, /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: PredicateFunction < __OfCollectionType const &, __ElementType const & >   __contains          /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > template <
                    typename __TElementType,                                                        /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
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
                    typename                                                                                __ReceiverType,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                                __ElementType,      /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                                __OfCollectionType, /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: PredicateFunction < __OfCollectionType const &, __ElementType const & >   __contains          /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > template <
                    typename __TElementType,                                                        /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
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
                    typename                                                                                __ReceiverType,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                                __ElementType,      /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                                __OfCollectionType, /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: PredicateFunction < __OfCollectionType const &, __ElementType const & >   __contains          /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > template <
                    typename __TElementType,                                                        /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
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
                    typename                                                                                __ReceiverType,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                                __ElementType,      /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                                __OfCollectionType, /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: PredicateFunction < __OfCollectionType const &, __ElementType const & >   __contains          /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > template <
                    typename __TElementType,                                                        /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
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
                    typename                                                                                __ReceiverType,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                                __ElementType,      /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                                __OfCollectionType, /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: PredicateFunction < __OfCollectionType const &, __ElementType const & >   __contains          /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > template <
                    typename __TElementType,                                                        /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
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
                    typename                                                                                __ReceiverType,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                                __ElementType,      /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                                __OfCollectionType, /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: PredicateFunction < __OfCollectionType const &, __ElementType const & >   __contains          /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > template <
                    typename __TElementType,                                                        /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
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
                    typename                                                                                __ReceiverType,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                                __ElementType,      /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                                __OfCollectionType, /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: PredicateFunction < __OfCollectionType const &, __ElementType const & >   __contains          /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > template <
                    typename __TElementType,                                                        /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
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
                    typename                                                                                __ReceiverType,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                                __ElementType,      /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                                __OfCollectionType, /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: PredicateFunction < __OfCollectionType const &, __ElementType const & >   __contains          /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > template <
                    typename __TElementType,                                                        /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
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
                    typename                                                                                __ReceiverType,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                                __ElementType,      /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                                __OfCollectionType, /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: PredicateFunction < __OfCollectionType const &, __ElementType const & >   __contains          /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > template <
                    typename __TElementType,                                                        /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
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
                    typename                                                                                __ReceiverType,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                                __ElementType,      /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                                __OfCollectionType, /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: PredicateFunction < __OfCollectionType const &, __ElementType const & >   __contains          /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > template <
                    typename __TElementType,                                                        /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
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

        } /* namespace __impl */
    } /* namespace __hidden */
} /* namespace cds */

#endif /* __CDS_SHARED_REPLACE_OF_COMPOSITE_CLIENT_IMPL_HPP__ */
