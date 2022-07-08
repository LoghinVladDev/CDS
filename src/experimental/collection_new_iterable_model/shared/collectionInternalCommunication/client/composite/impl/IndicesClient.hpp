//
// Created by loghin on 6/30/22.
//

#ifndef __CDS_SHARED_INDICES_CLIENT_IMPL_HPP__
#define __CDS_SHARED_INDICES_CLIENT_IMPL_HPP__

namespace cds {                 // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {    // NOLINT(modernize-concat-nested-namespaces)
        namespace __hidden {    // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier)
            namespace __impl {  // NOLINT(bugprone-reserved-identifier)

                template <
                        typename __ReceiverType,    // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType      // NOLINT(bugprone-reserved-identifier)
                > template <
                        typename __CollectionType   // NOLINT(bugprone-reserved-identifier)
                > auto __IndicesClient <
                        __ReceiverType,
                        __ElementType
                > :: indicesOf (
                        Size                        count,
                        __CollectionType          & storeIn,
                        ElementType         const & element
                ) const noexcept -> __CollectionType & {

                    Index index         = 0;
                    Size  foundCount    = 0ULL;

                    for (
                            auto
                                iterator    = static_cast < __ReceiverType const * > ( this )->cbegin (),
                                end         = static_cast < __ReceiverType const * > ( this )->cend ();

                            iterator != end && foundCount < count;
                            ++ iterator, ++ index
                    ) {
                        if ( cds :: meta :: equals ( * iterator, element ) ) {
                            (void) storeIn.insert ( index );
                            ++ foundCount;
                        }
                    }

                    return storeIn;
                }


                template <
                        typename __ReceiverType,                            // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType                              // NOLINT(bugprone-reserved-identifier)
                > template <
                        template < typename ... > class __CollectionType    // NOLINT(bugprone-reserved-identifier)
                > __CDS_OptimalInline auto __IndicesClient <
                        __ReceiverType,
                        __ElementType
                > :: indicesOf (
                        Size                count,
                        ElementType const & element
                ) const noexcept -> __CollectionType < Index > {

                    __CollectionType < Index > indices;
                    return std :: move (
                            this->indicesOf (
                                    count,
                                    indices,
                                    element
                            )
                    );
                }


                template <
                        typename __ReceiverType,                            // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType                              // NOLINT(bugprone-reserved-identifier)
                > auto __IndicesClient <
                        __ReceiverType,
                        __ElementType
                > :: firstIndexOf (
                        ElementType const & element
                ) const noexcept -> Index {

                    Index index = 0;
                    for (
                            auto
                                    iterator    = static_cast < __ReceiverType const * > ( this )->cbegin (),
                                    end         = static_cast < __ReceiverType const * > ( this )->cend ();

                            iterator != end;
                            ++ iterator, ++ index
                    ) {
                        if ( cds :: meta :: equals ( * iterator, element ) ) {
                            return index;
                        }
                    }

                    return __ReceiverType :: invalidIndex;
                }


                template <
                        typename __ReceiverType,                            // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType                              // NOLINT(bugprone-reserved-identifier)
                > auto __IndicesClient <
                        __ReceiverType,
                        __ElementType
                > :: lastIndexOf (
                        ElementType const & element
                ) const noexcept -> Index {

                    Index index = static_cast < Index > ( static_cast < __ReceiverType const * > ( this )->size() ) - 1;
                    for (
                            auto
                                    iterator    = static_cast < __ReceiverType const * > ( this )->crbegin (),
                                    end         = static_cast < __ReceiverType const * > ( this )->crend ();

                            iterator != end;
                            ++ iterator, -- index
                    ) {
                        if ( cds :: meta :: equals ( * iterator, element ) ) {
                            return index;
                        }
                    }

                    return __ReceiverType :: invalidIndex;
                }


                template <
                        typename __ReceiverType,    // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType      // NOLINT(bugprone-reserved-identifier)
                > template <
                        typename __CollectionType   // NOLINT(bugprone-reserved-identifier)
                > auto __IndicesClient <
                        __ReceiverType,
                        __ElementType
                > :: allIndicesOf (
                        __CollectionType          & storeIn,
                        ElementType         const & element
                ) const noexcept -> __CollectionType & {

                    Index index         = 0;
                    Size  foundCount    = 0ULL;

                    for (
                            auto
                                    iterator    = static_cast < __ReceiverType const * > ( this )->cbegin (),
                                    end         = static_cast < __ReceiverType const * > ( this )->cend ();

                            iterator != end;
                            ++ iterator, ++ index
                            ) {
                        if ( cds :: meta :: equals ( * iterator, element ) ) {
                            (void) storeIn.insert ( index );
                            ++ foundCount;
                        }
                    }

                    return storeIn;
                }


                template <
                        typename __ReceiverType,                            // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType                              // NOLINT(bugprone-reserved-identifier)
                > template <
                        template < typename ... > class __CollectionType    // NOLINT(bugprone-reserved-identifier)
                > __CDS_OptimalInline auto __IndicesClient <
                        __ReceiverType,
                        __ElementType
                > :: allIndicesOf (
                        ElementType const & element
                ) const noexcept -> __CollectionType < Index > {

                    __CollectionType < Index > indices;
                    return std :: move (
                            this->allIndicesOf (
                                    indices,
                                    element
                            )
                    );
                }

            }
        }
    }
}

#endif // __CDS_SHARED_INDICES_CLIENT_IMPL_HPP__
