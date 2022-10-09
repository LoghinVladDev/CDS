/*
 * Created by loghin on 6/30/2022.
 */

#ifndef __CDS_SHARED_INDEXED_OPERATIONS_PRIMITIVE_CLIENT_IMPL_HPP__
#define __CDS_SHARED_INDEXED_OPERATIONS_PRIMITIVE_CLIENT_IMPL_HPP__ /* NOLINT(bugprone-reserved-identifier) */

namespace cds {                 /* NOLINT(modernize-concat-nested-namespaces) */
    namespace experimental {    /* NOLINT(modernize-concat-nested-namespaces) */
        namespace __hidden {    /* NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier) */
            namespace __impl {  /* NOLINT(bugprone-reserved-identifier) */

                template <
                        typename __ReceiverType,    /* NOLINT(bugprone-reserved-identifier) */
                        typename __ElementType      /* NOLINT(bugprone-reserved-identifier) */
                > template <
                        typename __CollectionType,  /* NOLINT(bugprone-reserved-identifier) */
                        typename __TElementType,    /* NOLINT(bugprone-reserved-identifier) */
                        cds :: meta :: EnableIf <
                                cds :: meta :: isCopyConstructible < __TElementType > ()
                        >
                > auto __IndexedOperationsPrimitiveClient <
                        __ReceiverType,
                        __ElementType
                > :: sub (
                        __CollectionType  & storeIn,
                        Index               from,
                        Index               to
                ) const noexcept -> __CollectionType & {

                    if ( from > to ) {
                        std :: swap ( from, to );
                    }

                    if ( from < 0 ) {
                        from = 0;
                    }

                    auto const size = reinterpret_cast < __ReceiverType const * > ( this )->size();
                    if ( to >= size ) {
                        to = size;
                    }

                    Index index __CDS_MaybeUnused = 0;

                    for (
                            auto
                                iterator    = reinterpret_cast < __ReceiverType const * > ( this )->cbegin(),
                                end         = reinterpret_cast < __ReceiverType const * > ( this )->cend();
                            iterator != end;
                            ++ iterator
                    ) {
                        if ( index >= from && index < to ) {
                            (void) storeIn.insert ( * iterator );
                        }

                        ++ index;
                    }

                    return storeIn;
                }


                template <
                        typename __ReceiverType,    /* NOLINT(bugprone-reserved-identifier) */
                        typename __ElementType      /* NOLINT(bugprone-reserved-identifier) */
                > template <
                        typename __CollectionType,  /* NOLINT(bugprone-reserved-identifier) */
                        typename __TElementType,    /* NOLINT(bugprone-reserved-identifier) */
                        cds :: meta :: EnableIf <
                                cds :: meta :: isCopyConstructible < __TElementType > ()
                        >
                > __CDS_OptimalInline auto __IndexedOperationsPrimitiveClient <
                        __ReceiverType,
                        __ElementType
                > :: sub (
                        Index               from,
                        Index               to
                ) const noexcept -> __CollectionType {

                    __CollectionType collection;
                    return std :: move (
                            this->sub (
                                    collection,
                                    from,
                                    to
                            )
                    );
                }


                template <
                        typename __ReceiverType,                            /* NOLINT(bugprone-reserved-identifier) */
                        typename __ElementType                              /* NOLINT(bugprone-reserved-identifier) */
                > template <
                        template < typename ... > class __CollectionType,   /* NOLINT(bugprone-reserved-identifier) */
                        typename __TElementType,                            /* NOLINT(bugprone-reserved-identifier) */
                        cds :: meta :: EnableIf <
                                cds :: meta :: isCopyConstructible < __TElementType > ()
                        >
                > __CDS_OptimalInline auto __IndexedOperationsPrimitiveClient <
                        __ReceiverType,
                        __ElementType
                > :: sub (
                        Index               from,
                        Index               to
                ) const noexcept -> __CollectionType < __ElementType > {

                    __CollectionType < __ElementType > collection;
                    return std :: move (
                            this->sub (
                                    collection,
                                    from,
                                    to
                            )
                    );
                }


                template <
                        typename __ReceiverType,                            /* NOLINT(bugprone-reserved-identifier) */
                        typename __ElementType                              /* NOLINT(bugprone-reserved-identifier) */
                > __CDS_OptimalInline auto __IndexedOperationsPrimitiveClient <
                        __ReceiverType,
                        __ElementType
                > :: operator [] (
                        Index index
                ) const noexcept (false) -> __ElementType const & {

                    return reinterpret_cast < __ReceiverType const * > ( this )->get ( index );
                }


                template <
                        typename __ReceiverType,                            /* NOLINT(bugprone-reserved-identifier) */
                        typename __ElementType                              /* NOLINT(bugprone-reserved-identifier) */
                > __CDS_OptimalInline auto __IndexedOperationsPrimitiveClient <
                        __ReceiverType,
                        __ElementType
                > :: operator [] (
                        Index index
                ) noexcept (false) -> __ElementType & {

                    return reinterpret_cast < __ReceiverType * > ( this )->get ( index );
                }


                template <
                        typename __ReceiverType,    /* NOLINT(bugprone-reserved-identifier) */
                        typename __ElementType      /* NOLINT(bugprone-reserved-identifier) */
                > auto __IndexedOperationsPrimitiveClient <
                        __ReceiverType,
                        __ElementType
                > :: removeAt (
                        Collection < Index > const & indices
                ) noexcept -> Size {

                    Size removedCount = 0ULL;
                    for ( auto iterator = indices.begin(); iterator != indices.end(); ++ iterator ) {
                        if ( reinterpret_cast < __ReceiverType * > ( this )->removeAt ( * iterator ) ) {
                            ++ removedCount;
                        }
                    }

                    return removedCount;
                }


                template <
                        typename __ReceiverType,    /* NOLINT(bugprone-reserved-identifier) */
                        typename __ElementType      /* NOLINT(bugprone-reserved-identifier) */
                > auto __IndexedOperationsPrimitiveClient <
                        __ReceiverType,
                        __ElementType
                > :: removeAt (
                        std :: initializer_list < Index > const & indices
                ) noexcept -> Size {

                    Size removedCount = 0ULL;
                    for ( auto const & index : indices ) {
                        if ( reinterpret_cast < __ReceiverType * > ( this )->removeAt ( index ) ) {
                            ++ removedCount;
                        }
                    }

                    return removedCount;
                }


                template <
                        typename __ReceiverType,    /* NOLINT(bugprone-reserved-identifier) */
                        typename __ElementType      /* NOLINT(bugprone-reserved-identifier) */
                > template <
                        typename __CollectionType,  /* NOLINT(bugprone-reserved-identifier) */
                        typename __TElementType,    /* NOLINT(bugprone-reserved-identifier) */
                        cds :: meta :: EnableIf <
                                cds :: meta :: isCopyConstructible < __TElementType > ()
                        >
                > auto __LocalIndexedOperationsPrimitiveClient <
                        __ReceiverType,
                        __ElementType
                > :: sub (
                        __CollectionType  & storeIn,
                        Index               from,
                        Index               to
                ) const noexcept -> __CollectionType & {

                    if ( from > to ) {
                        std :: swap ( from, to );
                    }

                    if ( from < 0 ) {
                        from = 0;
                    }

                    if ( to >= reinterpret_cast < __ReceiverType const * > ( this )->size() ) {
                        to = reinterpret_cast < __ReceiverType const * > ( this )->size();
                    }

                    Index index __CDS_MaybeUnused = 0;

                    for (
                            auto
                                    iterator    = reinterpret_cast < __ReceiverType const * > ( this )->cbegin(),
                                    end         = reinterpret_cast < __ReceiverType const * > ( this )->cend();
                            iterator != end;
                            ++ iterator
                    ) {
                        if ( index >= from && index < to ) {
                            (void) storeIn.insert ( * iterator );
                        }

                        ++ index;
                    }

                    return storeIn;
                }


                template <
                        typename __ReceiverType,    /* NOLINT(bugprone-reserved-identifier) */
                        typename __ElementType      /* NOLINT(bugprone-reserved-identifier) */
                > template <
                        typename __CollectionType,  /* NOLINT(bugprone-reserved-identifier) */
                        typename __TElementType,    /* NOLINT(bugprone-reserved-identifier) */
                        cds :: meta :: EnableIf <
                                cds :: meta :: isCopyConstructible < __TElementType > ()
                        >
                > __CDS_OptimalInline auto __LocalIndexedOperationsPrimitiveClient <
                        __ReceiverType,
                        __ElementType
                > :: sub (
                        Index               from,
                        Index               to
                ) const noexcept -> __CollectionType {

                    __CollectionType collection;
                    return std :: move (
                            this->sub (
                                    collection,
                                    from,
                                    to
                            )
                    );
                }


                template <
                        typename __ReceiverType,                            /* NOLINT(bugprone-reserved-identifier) */
                        typename __ElementType                              /* NOLINT(bugprone-reserved-identifier) */
                > template <
                        template < typename ... > class __CollectionType,   /* NOLINT(bugprone-reserved-identifier) */
                        typename __TElementType,                            /* NOLINT(bugprone-reserved-identifier) */
                        cds :: meta :: EnableIf <
                                cds :: meta :: isCopyConstructible < __TElementType > ()
                        >
                > __CDS_OptimalInline auto __LocalIndexedOperationsPrimitiveClient <
                        __ReceiverType,
                        __ElementType
                > :: sub (
                        Index               from,
                        Index               to
                ) const noexcept -> __CollectionType < __ElementType > {

                    __CollectionType < __ElementType > collection;
                    return std :: move (
                            this->sub (
                                    collection,
                                    from,
                                    to
                            )
                    );
                }

            }
        }
    }
}

#endif /* __CDS_SHARED_INDEXED_OPERATIONS_PRIMITIVE_CLIENT_IMPL_HPP__ */
