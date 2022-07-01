//
// Created by uic70278 on 6/30/2022.
//

#ifndef __CDS_SHARED_INDEXED_OPERATIONS_CLIENT_IMPL_HPP__
#define __CDS_SHARED_INDEXED_OPERATIONS_CLIENT_IMPL_HPP__

namespace cds {                 // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {    // NOLINT(modernize-concat-nested-namespaces)
        namespace __hidden {    // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier)
            namespace __impl {  // NOLINT(bugprone-reserved-identifier)

                template <
                        typename __ReceiverType,    // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType      // NOLINT(bugprone-reserved-identifier)
                > template <
                        typename __CollectionType,  // NOLINT(bugprone-reserved-identifier)
                        typename __TElementType,    // NOLINT(bugprone-reserved-identifier)
                        cds :: meta :: EnableIf <
                                cds :: meta :: isCopyConstructible < __TElementType > ()
                        >
                > auto __IndexedOperationsClient <
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

                    if ( to >= this->size() ) {
                        to = this->size();
                    }

                    Index index __CDS_MaybeUnused = 0;

                    for (
                            auto
                                iterator    = static_cast < __ReceiverType const * > ( this )->cbegin(),
                                end         = static_cast < __ReceiverType const * > ( this )->cend();
                            iterator != end;
                            ++ iterator
                    ) {
                        if ( index >= from && index < to ) {
                            storeIn.add ( * iterator );
                        }

                        ++ index;
                    }

                    return storeIn;
                }


                template <
                        typename __ReceiverType,    // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType      // NOLINT(bugprone-reserved-identifier)
                > template <
                        typename __CollectionType,  // NOLINT(bugprone-reserved-identifier)
                        typename __TElementType,    // NOLINT(bugprone-reserved-identifier)
                        cds :: meta :: EnableIf <
                                cds :: meta :: isCopyConstructible < __TElementType > ()
                        >
                > __CDS_OptimalInline auto __IndexedOperationsClient <
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
                        typename __ReceiverType,                            // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType                              // NOLINT(bugprone-reserved-identifier)
                > template <
                        template < typename ... > class __CollectionType,   // NOLINT(bugprone-reserved-identifier)
                        typename __TElementType,                            // NOLINT(bugprone-reserved-identifier)
                        cds :: meta :: EnableIf <
                                cds :: meta :: isCopyConstructible < __TElementType > ()
                        >
                > __CDS_OptimalInline auto __IndexedOperationsClient <
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
                        typename __ReceiverType,                            // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType                              // NOLINT(bugprone-reserved-identifier)
                > __CDS_OptimalInline auto __IndexedOperationsClient <
                        __ReceiverType,
                        __ElementType
                > :: operator [] (
                        Index index
                ) const noexcept (false) -> __ElementType const & {

                    return static_cast < __ReceiverType const * > ( this )->get ( index );
                }


                template <
                        typename __ReceiverType,                            // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType                              // NOLINT(bugprone-reserved-identifier)
                > __CDS_OptimalInline auto __IndexedOperationsClient <
                        __ReceiverType,
                        __ElementType
                > :: operator [] (
                        Index index
                ) noexcept (false) -> __ElementType & {

                    return static_cast < __ReceiverType * > ( this )->get ( index );
                }


                template <
                        typename __ReceiverType,    // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType      // NOLINT(bugprone-reserved-identifier)
                > auto __IndexedOperationsClient <
                        __ReceiverType,
                        __ElementType
                > :: removeAt (
                        Collection < Index > const & indices
                ) noexcept -> Size {

                    Size removedCount = 0ULL;
                    for ( auto iterator = indices.begin(); iterator != indices.end(); ++ iterator ) {
                        if ( static_cast < __ReceiverType * > ( this )->removeAt ( * iterator ) ) {
                            ++ removedCount;
                        }
                    }

                    return removedCount;
                }


                template <
                        typename __ReceiverType,    // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType      // NOLINT(bugprone-reserved-identifier)
                > auto __IndexedOperationsClient <
                        __ReceiverType,
                        __ElementType
                > :: removeAt (
                        std :: initializer_list < Index > const & indices
                ) noexcept -> Size {

                    Size removedCount = 0ULL;
                    for ( auto const & index : indices ) {
                        if ( static_cast < __ReceiverType * > ( this )->removeAt ( index ) ) {
                            ++ removedCount;
                        }
                    }

                    return removedCount;
                }

            }
        }
    }
}

#endif // __CDS_SHARED_INDEXED_OPERATIONS_CLIENT_IMPL_HPP__
