/*
 * Created by loghin on 6/30/2022.
 */

#ifndef __CDS_SHARED_REPLACE_COMPOSITE_CLIENT_IMPL_HPP__ /* NOLINT(llvm-header-guard) */
#define __CDS_SHARED_REPLACE_COMPOSITE_CLIENT_IMPL_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

namespace cds {             /* NOLINT(modernize-concat-nested-namespaces) */
    namespace __hidden {    /* NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        namespace __impl {  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            template <
                    typename __ReceiverType,                /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ElementType                  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > template <
                    typename __TElementType,                /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    cds :: meta :: EnableIf <
                            cds :: meta :: isCopyAssignable < __TElementType > ()
                    >
            > auto __ReplaceCompositeClient <
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
                            iterator    = reinterpret_cast < __ReceiverType * > ( this )->begin(),
                            end         = reinterpret_cast < __ReceiverType * > ( this )->end();

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
                    typename __ReceiverType,                /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ElementType                  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > template <
                    typename __TElementType,                /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    cds :: meta :: EnableIf <
                            cds :: meta :: isCopyAssignable < __TElementType > ()
                    >
            > auto __ReplaceCompositeClient <
                    __ReceiverType,
                    __ElementType
            > :: replaceFirst (
                    ElementType const & what,
                    ElementType const & with
            ) noexcept -> bool {

                for (
                        auto
                            iterator    = reinterpret_cast < __ReceiverType * > ( this )->begin(),
                            end         = reinterpret_cast < __ReceiverType * > ( this )->end();

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
                    typename __ReceiverType,                /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ElementType                  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > template <
                    typename __TElementType,                /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    cds :: meta :: EnableIf <
                            cds :: meta :: isMoveAssignable < __TElementType > ()
                    >
            > auto __ReplaceCompositeClient <
                    __ReceiverType,
                    __ElementType
            > :: replaceFirst (
                    ElementType const & what,
                    ElementType      && with
            ) noexcept -> bool {

                for (
                        auto
                            iterator    = reinterpret_cast < __ReceiverType * > ( this )->begin(),
                            end         = reinterpret_cast < __ReceiverType * > ( this )->end();

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
                    typename __ReceiverType,                /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ElementType                  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > template <
                    typename __TElementType,                /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    cds :: meta :: EnableIf <
                            cds :: meta :: isCopyAssignable < __TElementType > ()
                    >
            > auto __ReplaceCompositeClient <
                    __ReceiverType,
                    __ElementType
            > :: replaceLast (
                    ElementType const & what,
                    ElementType const & with
            ) noexcept -> bool {

                for (
                        auto
                            iterator    = reinterpret_cast < __ReceiverType * > ( this )->rbegin(),
                            end         = reinterpret_cast < __ReceiverType * > ( this )->rend();

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
                    typename __ReceiverType,                /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ElementType                  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > template <
                    typename __TElementType,                /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    cds :: meta :: EnableIf <
                            cds :: meta :: isMoveAssignable < __TElementType > ()
                    >
            > auto __ReplaceCompositeClient <
                    __ReceiverType,
                    __ElementType
            > :: replaceLast (
                    ElementType const & what,
                    ElementType      && with
            ) noexcept -> bool {

                for (
                        auto
                            iterator    = reinterpret_cast < __ReceiverType * > ( this )->rbegin(),
                            end         = reinterpret_cast < __ReceiverType * > ( this )->rend();

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
                    typename __ReceiverType,                /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ElementType                  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > template <
                    typename __TElementType,                /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    cds :: meta :: EnableIf <
                            cds :: meta :: isCopyAssignable < __TElementType > ()
                    >
            > auto __ReplaceCompositeClient <
                    __ReceiverType,
                    __ElementType
            > :: replaceAll (
                    ElementType const & what,
                    ElementType const & with
            ) noexcept -> Size {

                Size replacedCount = 0ULL;
                for (
                        auto
                            iterator    = reinterpret_cast < __ReceiverType * > ( this )->rbegin(),
                            end         = reinterpret_cast < __ReceiverType * > ( this )->rend();

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

        } /* namespace __impl */
    } /* namespace __hidden */
} /* namespace cds */

#endif /* __CDS_SHARED_REPLACE_COMPOSITE_CLIENT_IMPL_HPP__ */
