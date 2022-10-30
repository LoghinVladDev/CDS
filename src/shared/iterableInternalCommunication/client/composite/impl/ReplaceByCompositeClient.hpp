/*
 * Created by loghin on 6/30/2022.
 */

#ifndef __CDS_SHARED_REPLACE_BY_COMPOSITE_CLIENT_IMPL_HPP__ /* NOLINT(llvm-header-guard) */
#define __CDS_SHARED_REPLACE_BY_COMPOSITE_CLIENT_IMPL_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

namespace cds {             /* NOLINT(modernize-concat-nested-namespaces) */
    namespace __hidden {    /* NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        namespace __impl {  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            template <
                    typename __ElementType,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __Supplier,        /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    cds :: meta :: EnableIf <
                            cds :: meta :: isMoveAssignable < __ElementType > ()
                    > = 0
            > __CDS_cpplang_NonConstConstexprMemberFunction auto __assignBySupplier ( /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __ElementType         & element,
                    __Supplier      const & supplier
            ) noexcept ( noexcept ( cds :: meta :: referenceOf < __ElementType > () = std :: move ( cds :: meta :: referenceOf < __ElementType > () ) ) && noexcept ( supplier ( cds :: meta :: referenceOf < __ElementType > () ) ) ) -> void {

                element = std :: move ( supplier ( element ) );
            }


            template <
                    typename __ElementType,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __Supplier,        /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    cds :: meta :: EnableIf <
                            ! cds :: meta :: isMoveAssignable < __ElementType > ()
                    > = 0
            > __CDS_cpplang_NonConstConstexprMemberFunction auto __assignBySupplier ( /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __ElementType         & element,
                    __Supplier      const & supplier
            ) noexcept ( noexcept ( cds :: meta :: referenceOf < __ElementType > () = cds :: meta :: referenceOf < __ElementType > () ) && noexcept ( supplier ( cds :: meta :: referenceOf < __ElementType > () ) ) ) -> void {

                element = supplier ( element );
            }


            template <
                    typename __ReceiverType,    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ElementType      /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > template <
                    typename __Predicate,       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __TElementType,    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    cds :: meta :: EnableIf <
                            cds :: meta :: isCopyAssignable < __TElementType > ()
                    >
            > auto __ReplaceByCompositeClient <
                    __ReceiverType,
                    __ElementType
            > :: replaceThat (
                    Size                count,
                    __Predicate const & predicate,
                    ElementType const & with
            ) noexcept ( noexcept ( predicate ( cds :: meta :: referenceOf < ElementType > () ) ) ) -> Size {

                Size replacedCount = 0ULL;
                for (
                        auto
                            iterator    = reinterpret_cast < __ReceiverType * > ( this )->begin (),
                            end         = reinterpret_cast < __ReceiverType * > ( this )->end ();

                        iterator != end && replacedCount < count;
                        ++ iterator
                ) {
                    if ( predicate ( * iterator ) ) {
                        * iterator = with;
                        ++ replacedCount;
                    }
                }

                return replacedCount;
            }


            template <
                    typename __ReceiverType,    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ElementType      /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > template <
                    typename __Predicate,       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __TElementType,    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    cds :: meta :: EnableIf <
                            cds :: meta :: isCopyAssignable < __TElementType > ()
                    >
            > auto __ReplaceByCompositeClient <
                    __ReceiverType,
                    __ElementType
            > :: replaceFirstThat (
                    __Predicate const & predicate,
                    ElementType const & with
            ) noexcept ( noexcept ( predicate ( cds :: meta :: referenceOf < ElementType > () ) ) ) -> bool {

                for (
                        auto
                            iterator    = reinterpret_cast < __ReceiverType * > ( this )->begin (),
                            end         = reinterpret_cast < __ReceiverType * > ( this )->end ();

                        iterator != end;
                        ++ iterator
                ) {
                    if ( predicate ( * iterator ) ) {
                        * iterator = with;
                        return true;
                    }
                }

                return false;
            }


            template <
                    typename __ReceiverType,    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ElementType      /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > template <
                    typename __Predicate,       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __TElementType,    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    cds :: meta :: EnableIf <
                            cds :: meta :: isMoveAssignable < __TElementType > ()
                    >
            > auto __ReplaceByCompositeClient <
                    __ReceiverType,
                    __ElementType
            > :: replaceFirstThat (
                    __Predicate const & predicate,
                    ElementType      && with
            ) noexcept ( noexcept ( predicate ( cds :: meta :: referenceOf < ElementType > () ) ) ) -> bool {

                for (
                        auto
                            iterator    = reinterpret_cast < __ReceiverType * > ( this )->begin (),
                            end         = reinterpret_cast < __ReceiverType * > ( this )->end ();

                        iterator != end;
                        ++ iterator
                ) {
                    if ( predicate ( * iterator ) ) {
                        * iterator = std :: move ( with );
                        return true;
                    }
                }

                return false;
            }


            template <
                    typename __ReceiverType,    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ElementType      /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > template <
                    typename __Predicate,       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __TElementType,    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    cds :: meta :: EnableIf <
                            cds :: meta :: isCopyAssignable < __TElementType > ()
                    >
            > auto __ReplaceByCompositeClient <
                    __ReceiverType,
                    __ElementType
            > :: replaceLastThat (
                    __Predicate const & predicate,
                    ElementType const & with
            ) noexcept ( noexcept ( predicate ( cds :: meta :: referenceOf < ElementType > () ) ) ) -> bool {

                for (
                        auto
                            iterator    = reinterpret_cast < __ReceiverType * > ( this )->rbegin (),
                            end         = reinterpret_cast < __ReceiverType * > ( this )->rend ();

                        iterator != end;
                        ++ iterator
                ) {
                    if ( predicate ( * iterator ) ) {
                        * iterator = with;
                        return true;
                    }
                }

                return false;
            }


            template <
                    typename __ReceiverType,    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ElementType      /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > template <
                    typename __Predicate,       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __TElementType,    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    cds :: meta :: EnableIf <
                            cds :: meta :: isMoveAssignable < __TElementType > ()
                    >
            > auto __ReplaceByCompositeClient <
                    __ReceiverType,
                    __ElementType
            > :: replaceLastThat (
                    __Predicate const & predicate,
                    ElementType      && with
            ) noexcept ( noexcept ( predicate ( cds :: meta :: referenceOf < ElementType > () ) ) ) -> bool {

                for (
                        auto
                            iterator    = reinterpret_cast < __ReceiverType * > ( this )->rbegin (),
                            end         = reinterpret_cast < __ReceiverType * > ( this )->rend ();

                        iterator != end;
                        ++ iterator
                ) {
                    if ( predicate ( * iterator ) ) {
                        * iterator = std :: move ( with );
                        return true;
                    }
                }

                return false;
            }


            template <
                    typename __ReceiverType,    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ElementType      /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > template <
                    typename __Predicate,       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __TElementType,    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    cds :: meta :: EnableIf <
                            cds :: meta :: isCopyAssignable < __TElementType > ()
                    >
            > auto __ReplaceByCompositeClient <
                    __ReceiverType,
                    __ElementType
            > :: replaceAllThat (
                    __Predicate const & predicate,
                    ElementType const & with
            ) noexcept ( noexcept ( predicate ( cds :: meta :: referenceOf < ElementType > () ) ) ) -> Size {

                Size replacedCount = 0ULL;
                for (
                        auto
                                iterator    = reinterpret_cast < __ReceiverType * > ( this )->begin (),
                                end         = reinterpret_cast < __ReceiverType * > ( this )->end ();

                        iterator != end;
                        ++ iterator
                ) {
                    if ( predicate ( * iterator ) ) {
                        * iterator = with;
                        ++ replacedCount;
                    }
                }

                return replacedCount;
            }


            template <
                    typename __ReceiverType,    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ElementType      /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > template <
                    typename __Predicate,       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __Supplier         /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > auto __ReplaceByCompositeClient <
                    __ReceiverType,
                    __ElementType
            > :: replaceThatBy (
                    Size                count,
                    __Predicate const & predicate,
                    __Supplier  const & supplier
            ) noexcept ( noexcept ( predicate ( cds :: meta :: referenceOf < ElementType > () ) ) && noexcept ( supplier ( cds :: meta :: referenceOf < ElementType > () ) ) ) -> Size {

                Size replacedCount = 0ULL;
                for (
                        auto
                                iterator    = reinterpret_cast < __ReceiverType * > ( this )->begin (),
                                end         = reinterpret_cast < __ReceiverType * > ( this )->end ();

                        iterator != end && replacedCount < count;
                        ++ iterator
                ) {
                    if ( predicate ( * iterator ) ) {
                        __assignBySupplier (
                                * iterator,
                                supplier
                        );

                        ++ replacedCount;
                    }
                }

                return replacedCount;
            }


            template <
                    typename __ReceiverType,    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ElementType      /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > template <
                    typename __Predicate,       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __Supplier         /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > auto __ReplaceByCompositeClient <
                    __ReceiverType,
                    __ElementType
            > :: replaceFirstThatBy (
                    __Predicate const & predicate,
                    __Supplier  const & supplier
            ) noexcept ( noexcept ( predicate ( cds :: meta :: referenceOf < ElementType > () ) ) && noexcept ( supplier ( cds :: meta :: referenceOf < ElementType > () ) ) ) -> bool {

                for (
                        auto
                                iterator    = reinterpret_cast < __ReceiverType * > ( this )->begin (),
                                end         = reinterpret_cast < __ReceiverType * > ( this )->end ();

                        iterator != end;
                        ++ iterator
                ) {
                    if ( predicate ( * iterator ) ) {
                        __assignBySupplier (
                                * iterator,
                                supplier
                        );

                        return true;
                    }
                }

                return false;
            }


            template <
                    typename __ReceiverType,    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ElementType      /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > template <
                    typename __Predicate,       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __Supplier         /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > auto __ReplaceByCompositeClient <
                    __ReceiverType,
                    __ElementType
            > :: replaceLastThatBy (
                    __Predicate const & predicate,
                    __Supplier  const & supplier
            ) noexcept ( noexcept ( predicate ( cds :: meta :: referenceOf < ElementType > () ) ) && noexcept ( supplier ( cds :: meta :: referenceOf < ElementType > () ) ) ) -> bool {

                for (
                        auto
                                iterator    = reinterpret_cast < __ReceiverType * > ( this )->rbegin (),
                                end         = reinterpret_cast < __ReceiverType * > ( this )->rend ();

                        iterator != end;
                        ++ iterator
                ) {
                    if ( predicate ( * iterator ) ) {
                        __assignBySupplier (
                                * iterator,
                                supplier
                        );

                        return true;
                    }
                }

                return false;
            }


            template <
                    typename __ReceiverType,    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ElementType      /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > template <
                    typename __Predicate,       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __Supplier         /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > auto __ReplaceByCompositeClient <
                    __ReceiverType,
                    __ElementType
            > :: replaceAllThatBy (
                    __Predicate const & predicate,
                    __Supplier  const & supplier
            ) noexcept ( noexcept ( predicate ( cds :: meta :: referenceOf < ElementType > () ) ) && noexcept ( supplier ( cds :: meta :: referenceOf < ElementType > () ) ) ) -> Size {

                Size replacedCount = 0ULL;
                for (
                        auto
                                iterator    = reinterpret_cast < __ReceiverType * > ( this )->rbegin (),
                                end         = reinterpret_cast < __ReceiverType * > ( this )->rend ();

                        iterator != end;
                        ++ iterator
                ) {
                    if ( predicate ( * iterator ) ) {
                        __assignBySupplier (
                                * iterator,
                                supplier
                        );

                        ++ replacedCount;
                    }
                }

                return replacedCount;
            }

        } /* namespace __impl */
    } /* namespace __hidden */
} /* namespace cds */

#endif /* __CDS_SHARED_REPLACE_BY_COMPOSITE_CLIENT_IMPL_HPP__ */
