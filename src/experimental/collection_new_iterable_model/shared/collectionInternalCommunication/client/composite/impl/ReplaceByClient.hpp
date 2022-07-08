//
// Created by loghin on 6/30/2022.
//

#ifndef __CDS_SHARED_REPLACE_BY_CLIENT_IMPL_HPP__
#define __CDS_SHARED_REPLACE_BY_CLIENT_IMPL_HPP__

namespace cds {                 // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {    // NOLINT(modernize-concat-nested-namespaces)
        namespace __hidden {    // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier)
            namespace __impl {  // NOLINT(bugprone-reserved-identifier)

                template <
                        typename __ElementType,     // NOLINT(bugprone-reserved-identifier)
                        typename __Supplier,        // NOLINT(bugprone-reserved-identifier)
                        cds :: meta :: EnableIf <
                                cds :: meta :: isMoveAssignable < __ElementType > ()
                        > = 0
                > __CDS_cpplang_NonConstConstexprMemberFunction auto __assignBySupplier ( // NOLINT(bugprone-reserved-identifier)
                        __ElementType         & element,
                        __Supplier      const & supplier
                ) noexcept ( noexcept ( cds :: meta :: referenceOf < __ElementType > () = std :: move ( cds :: meta :: referenceOf < __ElementType > () ) ) && noexcept ( supplier ( cds :: meta :: referenceOf < __ElementType > () ) ) ) -> void {

                    element = std :: move ( supplier ( element ) );
                }


                template <
                        typename __ElementType,     // NOLINT(bugprone-reserved-identifier)
                        typename __Supplier,        // NOLINT(bugprone-reserved-identifier)
                        cds :: meta :: EnableIf <
                                ! cds :: meta :: isMoveAssignable < __ElementType > ()
                        > = 0
                > __CDS_cpplang_NonConstConstexprMemberFunction auto __assignBySupplier ( // NOLINT(bugprone-reserved-identifier)
                        __ElementType         & element,
                        __Supplier      const & supplier
                ) noexcept ( noexcept ( cds :: meta :: referenceOf < __ElementType > () = cds :: meta :: referenceOf < __ElementType > () ) && noexcept ( supplier ( cds :: meta :: referenceOf < __ElementType > () ) ) ) -> void {

                    element = supplier ( element );
                }


                template <
                        typename __ReceiverType,    // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType      // NOLINT(bugprone-reserved-identifier)
                > template <
                        typename __Predicate,       // NOLINT(bugprone-reserved-identifier)
                        typename __TElementType,    // NOLINT(bugprone-reserved-identifier)
                        cds :: meta :: EnableIf <
                                cds :: meta :: isCopyAssignable < __TElementType > ()
                        >
                > auto __ReplaceByClient <
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
                                iterator    = static_cast < __ReceiverType * > ( this )->begin (),
                                end         = static_cast < __ReceiverType * > ( this )->end ();

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
                        typename __ReceiverType,    // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType      // NOLINT(bugprone-reserved-identifier)
                > template <
                        typename __Predicate,       // NOLINT(bugprone-reserved-identifier)
                        typename __TElementType,    // NOLINT(bugprone-reserved-identifier)
                        cds :: meta :: EnableIf <
                                cds :: meta :: isCopyAssignable < __TElementType > ()
                        >
                > auto __ReplaceByClient <
                        __ReceiverType,
                        __ElementType
                > :: replaceFirstThat (
                        __Predicate const & predicate,
                        ElementType const & with
                ) noexcept ( noexcept ( predicate ( cds :: meta :: referenceOf < ElementType > () ) ) ) -> bool {

                    for (
                            auto
                                iterator    = static_cast < __ReceiverType * > ( this )->begin (),
                                end         = static_cast < __ReceiverType * > ( this )->end ();

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
                        typename __ReceiverType,    // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType      // NOLINT(bugprone-reserved-identifier)
                > template <
                        typename __Predicate,       // NOLINT(bugprone-reserved-identifier)
                        typename __TElementType,    // NOLINT(bugprone-reserved-identifier)
                        cds :: meta :: EnableIf <
                                cds :: meta :: isMoveAssignable < __TElementType > ()
                        >
                > auto __ReplaceByClient <
                        __ReceiverType,
                        __ElementType
                > :: replaceFirstThat (
                        __Predicate const & predicate,
                        ElementType      && with
                ) noexcept ( noexcept ( predicate ( cds :: meta :: referenceOf < ElementType > () ) ) ) -> bool {

                    for (
                            auto
                                iterator    = static_cast < __ReceiverType * > ( this )->begin (),
                                end         = static_cast < __ReceiverType * > ( this )->end ();

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
                        typename __ReceiverType,    // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType      // NOLINT(bugprone-reserved-identifier)
                > template <
                        typename __Predicate,       // NOLINT(bugprone-reserved-identifier)
                        typename __TElementType,    // NOLINT(bugprone-reserved-identifier)
                        cds :: meta :: EnableIf <
                                cds :: meta :: isCopyAssignable < __TElementType > ()
                        >
                > auto __ReplaceByClient <
                        __ReceiverType,
                        __ElementType
                > :: replaceLastThat (
                        __Predicate const & predicate,
                        ElementType const & with
                ) noexcept ( noexcept ( predicate ( cds :: meta :: referenceOf < ElementType > () ) ) ) -> bool {

                    for (
                            auto
                                iterator    = static_cast < __ReceiverType * > ( this )->rbegin (),
                                end         = static_cast < __ReceiverType * > ( this )->rend ();

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
                        typename __ReceiverType,    // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType      // NOLINT(bugprone-reserved-identifier)
                > template <
                        typename __Predicate,       // NOLINT(bugprone-reserved-identifier)
                        typename __TElementType,    // NOLINT(bugprone-reserved-identifier)
                        cds :: meta :: EnableIf <
                                cds :: meta :: isMoveAssignable < __TElementType > ()
                        >
                > auto __ReplaceByClient <
                        __ReceiverType,
                        __ElementType
                > :: replaceLastThat (
                        __Predicate const & predicate,
                        ElementType      && with
                ) noexcept ( noexcept ( predicate ( cds :: meta :: referenceOf < ElementType > () ) ) ) -> bool {

                    for (
                            auto
                                iterator    = static_cast < __ReceiverType * > ( this )->rbegin (),
                                end         = static_cast < __ReceiverType * > ( this )->rend ();

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
                        typename __ReceiverType,    // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType      // NOLINT(bugprone-reserved-identifier)
                > template <
                        typename __Predicate,       // NOLINT(bugprone-reserved-identifier)
                        typename __TElementType,    // NOLINT(bugprone-reserved-identifier)
                        cds :: meta :: EnableIf <
                                cds :: meta :: isCopyAssignable < __TElementType > ()
                        >
                > auto __ReplaceByClient <
                        __ReceiverType,
                        __ElementType
                > :: replaceAllThat (
                        __Predicate const & predicate,
                        ElementType const & with
                ) noexcept ( noexcept ( predicate ( cds :: meta :: referenceOf < ElementType > () ) ) ) -> Size {

                    Size replacedCount = 0ULL;
                    for (
                            auto
                                    iterator    = static_cast < __ReceiverType * > ( this )->begin (),
                                    end         = static_cast < __ReceiverType * > ( this )->end ();

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
                        typename __ReceiverType,    // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType      // NOLINT(bugprone-reserved-identifier)
                > template <
                        typename __Predicate,       // NOLINT(bugprone-reserved-identifier)
                        typename __Supplier         // NOLINT(bugprone-reserved-identifier)
                > auto __ReplaceByClient <
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
                                    iterator    = static_cast < __ReceiverType * > ( this )->begin (),
                                    end         = static_cast < __ReceiverType * > ( this )->end ();

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
                        typename __ReceiverType,    // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType      // NOLINT(bugprone-reserved-identifier)
                > template <
                        typename __Predicate,       // NOLINT(bugprone-reserved-identifier)
                        typename __Supplier         // NOLINT(bugprone-reserved-identifier)
                > auto __ReplaceByClient <
                        __ReceiverType,
                        __ElementType
                > :: replaceFirstThatBy (
                        __Predicate const & predicate,
                        __Supplier  const & supplier
                ) noexcept ( noexcept ( predicate ( cds :: meta :: referenceOf < ElementType > () ) ) && noexcept ( supplier ( cds :: meta :: referenceOf < ElementType > () ) ) ) -> bool {

                    for (
                            auto
                                    iterator    = static_cast < __ReceiverType * > ( this )->begin (),
                                    end         = static_cast < __ReceiverType * > ( this )->end ();

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
                        typename __ReceiverType,    // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType      // NOLINT(bugprone-reserved-identifier)
                > template <
                        typename __Predicate,       // NOLINT(bugprone-reserved-identifier)
                        typename __Supplier         // NOLINT(bugprone-reserved-identifier)
                > auto __ReplaceByClient <
                        __ReceiverType,
                        __ElementType
                > :: replaceLastThatBy (
                        __Predicate const & predicate,
                        __Supplier  const & supplier
                ) noexcept ( noexcept ( predicate ( cds :: meta :: referenceOf < ElementType > () ) ) && noexcept ( supplier ( cds :: meta :: referenceOf < ElementType > () ) ) ) -> bool {

                    for (
                            auto
                                    iterator    = static_cast < __ReceiverType * > ( this )->rbegin (),
                                    end         = static_cast < __ReceiverType * > ( this )->rend ();

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
                        typename __ReceiverType,    // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType      // NOLINT(bugprone-reserved-identifier)
                > template <
                        typename __Predicate,       // NOLINT(bugprone-reserved-identifier)
                        typename __Supplier         // NOLINT(bugprone-reserved-identifier)
                > auto __ReplaceByClient <
                        __ReceiverType,
                        __ElementType
                > :: replaceAllThatBy (
                        __Predicate const & predicate,
                        __Supplier  const & supplier
                ) noexcept ( noexcept ( predicate ( cds :: meta :: referenceOf < ElementType > () ) ) && noexcept ( supplier ( cds :: meta :: referenceOf < ElementType > () ) ) ) -> Size {

                    Size replacedCount = 0ULL;
                    for (
                            auto
                                    iterator    = static_cast < __ReceiverType * > ( this )->rbegin (),
                                    end         = static_cast < __ReceiverType * > ( this )->rend ();

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

            }
        }
    }
}

#endif // __CDS_SHARED_REPLACE_BY_CLIENT_IMPL_HPP__
