/*
 * Created by loghin on 6/30/22.
 */

#ifndef __CDS_SHARED_INDICES_OF_COMPOSITE_CLIENT_IMPL_HPP__
#define __CDS_SHARED_INDICES_OF_COMPOSITE_CLIENT_IMPL_HPP__ /* NOLINT(bugprone-reserved-identifier) */

namespace cds {                 /* NOLINT(modernize-concat-nested-namespaces) */
    namespace experimental {    /* NOLINT(modernize-concat-nested-namespaces) */
        namespace __hidden {    /* NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier) */
            namespace __impl {  /* NOLINT(bugprone-reserved-identifier) */

                template <
                        typename                                                    __ReceiverType,         /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                    __ElementType,          /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                    __FromCollectionType,   /* NOLINT(bugprone-reserved-identifier) */
                        __ContainsFunction < __FromCollectionType, __ElementType >  __contains              /* NOLINT(bugprone-reserved-identifier) */
                > template <
                        typename __CollectionType                                                           /* NOLINT(bugprone-reserved-identifier) */
                > auto __IndicesOfCompositeClient <
                        __ReceiverType,
                        __ElementType,
                        __FromCollectionType,
                        __contains
                > :: indicesOfFrom (
                        Size                            count,
                        __CollectionType              & storeIn,
                        __FromCollectionType    const & from
                ) const noexcept -> __CollectionType & {

                    Size  foundCount = 0ULL;
                    Index index      = 0;

                    for (
                            auto
                                iterator    = reinterpret_cast < __ReceiverType const * > ( this )->cbegin(),
                                end         = reinterpret_cast < __ReceiverType const * > ( this )->cend();

                            iterator != end && foundCount < count;
                            ++ iterator, ++ index
                    ) {
                        if ( __contains ( from, * iterator ) ) {
                            (void) storeIn.insert ( index );
                            ++ foundCount;
                        }
                    }

                    return storeIn;
                }


                template <
                        typename                                                    __ReceiverType,         /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                    __ElementType,          /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                    __FromCollectionType,   /* NOLINT(bugprone-reserved-identifier) */
                        __ContainsFunction < __FromCollectionType, __ElementType >  __contains              /* NOLINT(bugprone-reserved-identifier) */
                > template <
                        template < typename ... > class __CollectionType                                    /* NOLINT(bugprone-reserved-identifier) */
                > __CDS_OptimalInline auto __IndicesOfCompositeClient <
                        __ReceiverType,
                        __ElementType,
                        __FromCollectionType,
                        __contains
                > :: indicesOfFrom (
                        Size                            count,
                        __FromCollectionType    const & from
                ) const noexcept -> __CollectionType < Index > {

                    __CollectionType < Index > indices;
                    return std :: move (
                            this->indicesOfFrom (
                                    count,
                                    indices,
                                    from
                            )
                    );
                }


                template <
                        typename                                                    __ReceiverType,         /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                    __ElementType,          /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                    __FromCollectionType,   /* NOLINT(bugprone-reserved-identifier) */
                        __ContainsFunction < __FromCollectionType, __ElementType >  __contains              /* NOLINT(bugprone-reserved-identifier) */
                > auto __IndicesOfCompositeClient <
                        __ReceiverType,
                        __ElementType,
                        __FromCollectionType,
                        __contains
                > :: firstIndexOfFrom (
                        __FromCollectionType const & from
                ) const noexcept -> Index {

                    Index index = 0;
                    for (
                            auto
                                    iterator    = reinterpret_cast < __ReceiverType const * > ( this )->cbegin(),
                                    end         = reinterpret_cast < __ReceiverType const * > ( this )->cend();

                            iterator != end;
                            ++ iterator, ++ index
                    ) {
                        if ( __contains ( from, * iterator ) ) {
                            return index;
                        }
                    }

                    return __ReceiverType :: invalidIndex;
                }


                template <
                        typename                                                    __ReceiverType,         /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                    __ElementType,          /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                    __FromCollectionType,   /* NOLINT(bugprone-reserved-identifier) */
                        __ContainsFunction < __FromCollectionType, __ElementType >  __contains              /* NOLINT(bugprone-reserved-identifier) */
                > auto __IndicesOfCompositeClient <
                        __ReceiverType,
                        __ElementType,
                        __FromCollectionType,
                        __contains
                > :: lastIndexOfFrom (
                        __FromCollectionType const & from
                ) const noexcept -> Index {

                    Index index = static_cast < Index > ( reinterpret_cast < __ReceiverType const * > ( this )->size() ) - 1;
                    for (
                            auto
                                    iterator    = reinterpret_cast < __ReceiverType const * > ( this )->crbegin(),
                                    end         = reinterpret_cast < __ReceiverType const * > ( this )->crend();

                            iterator != end;
                            ++ iterator, -- index
                    ) {
                        if ( __contains ( from, * iterator ) ) {
                            return index;
                        }
                    }

                    return __ReceiverType :: invalidIndex;
                }


                template <
                        typename                                                    __ReceiverType,         /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                    __ElementType,          /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                    __FromCollectionType,   /* NOLINT(bugprone-reserved-identifier) */
                        __ContainsFunction < __FromCollectionType, __ElementType >  __contains              /* NOLINT(bugprone-reserved-identifier) */
                > template <
                        typename __CollectionType                                                           /* NOLINT(bugprone-reserved-identifier) */
                > auto __IndicesOfCompositeClient <
                        __ReceiverType,
                        __ElementType,
                        __FromCollectionType,
                        __contains
                > :: allIndicesOfFrom (
                        __CollectionType              & storeIn,
                        __FromCollectionType    const & from
                ) const noexcept -> __CollectionType & {

                    Size  foundCount = 0ULL;
                    Index index      = 0;

                    for (
                            auto
                                    iterator    = reinterpret_cast < __ReceiverType const * > ( this )->cbegin(),
                                    end         = reinterpret_cast < __ReceiverType const * > ( this )->cend();

                            iterator != end;
                            ++ iterator, ++ index
                    ) {
                        if ( __contains ( from, * iterator ) ) {
                            (void) storeIn.insert ( index );
                            ++ foundCount;
                        }
                    }

                    return storeIn;
                }


                template <
                        typename                                                    __ReceiverType,         /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                    __ElementType,          /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                    __FromCollectionType,   /* NOLINT(bugprone-reserved-identifier) */
                        __ContainsFunction < __FromCollectionType, __ElementType >  __contains              /* NOLINT(bugprone-reserved-identifier) */
                > template <
                        template < typename ... > class __CollectionType                                    /* NOLINT(bugprone-reserved-identifier) */
                > __CDS_OptimalInline auto __IndicesOfCompositeClient <
                        __ReceiverType,
                        __ElementType,
                        __FromCollectionType,
                        __contains
                > :: allIndicesOfFrom (
                        __FromCollectionType    const & from
                ) const noexcept -> __CollectionType < Index > {

                    __CollectionType < Index > indices;
                    return std :: move (
                            this->allIndicesOfFrom (
                                    indices,
                                    from
                            )
                    );
                }


                template <
                        typename                                                    __ReceiverType,         /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                    __ElementType,          /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                    __FromCollectionType,   /* NOLINT(bugprone-reserved-identifier) */
                        __ContainsFunction < __FromCollectionType, __ElementType >  __contains              /* NOLINT(bugprone-reserved-identifier) */
                > template <
                        typename __CollectionType                                                           /* NOLINT(bugprone-reserved-identifier) */
                > auto __IndicesOfCompositeClient <
                        __ReceiverType,
                        __ElementType,
                        __FromCollectionType,
                        __contains
                > :: indicesOfNotFrom (
                        Size                            count,
                        __CollectionType              & storeIn,
                        __FromCollectionType    const & from
                ) const noexcept -> __CollectionType & {

                    Size  foundCount = 0ULL;
                    Index index      = 0;

                    for (
                            auto
                                iterator    = reinterpret_cast < __ReceiverType const * > ( this )->cbegin(),
                                end         = reinterpret_cast < __ReceiverType const * > ( this )->cend();

                            iterator != end && foundCount < count;
                            ++ iterator, ++ index
                    ) {
                        if ( ! __contains ( from, * iterator ) ) {
                            (void) storeIn.insert ( index );
                            ++ foundCount;
                        }
                    }

                    return storeIn;
                }


                template <
                        typename                                                    __ReceiverType,         /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                    __ElementType,          /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                    __FromCollectionType,   /* NOLINT(bugprone-reserved-identifier) */
                        __ContainsFunction < __FromCollectionType, __ElementType >  __contains              /* NOLINT(bugprone-reserved-identifier) */
                > template <
                        template < typename ... > class __CollectionType                                    /* NOLINT(bugprone-reserved-identifier) */
                > __CDS_OptimalInline auto __IndicesOfCompositeClient <
                        __ReceiverType,
                        __ElementType,
                        __FromCollectionType,
                        __contains
                > :: indicesOfNotFrom (
                        Size                            count,
                        __FromCollectionType    const & from
                ) const noexcept -> __CollectionType < Index > {

                    __CollectionType < Index > indices;
                    return std :: move (
                            this->indicesOfNotFrom (
                                    count,
                                    indices,
                                    from
                            )
                    );
                }


                template <
                        typename                                                    __ReceiverType,         /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                    __ElementType,          /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                    __FromCollectionType,   /* NOLINT(bugprone-reserved-identifier) */
                        __ContainsFunction < __FromCollectionType, __ElementType >  __contains              /* NOLINT(bugprone-reserved-identifier) */
                > auto __IndicesOfCompositeClient <
                        __ReceiverType,
                        __ElementType,
                        __FromCollectionType,
                        __contains
                > :: firstIndexOfNotFrom (
                        __FromCollectionType const & from
                ) const noexcept -> Index {

                    Index index = 0;
                    for (
                            auto
                                    iterator    = reinterpret_cast < __ReceiverType const * > ( this )->cbegin(),
                                    end         = reinterpret_cast < __ReceiverType const * > ( this )->cend();

                            iterator != end;
                            ++ iterator, ++ index
                    ) {
                        if ( ! __contains ( from, * iterator ) ) {
                            return index;
                        }
                    }

                    return __ReceiverType :: invalidIndex;
                }


                template <
                        typename                                                    __ReceiverType,         /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                    __ElementType,          /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                    __FromCollectionType,   /* NOLINT(bugprone-reserved-identifier) */
                        __ContainsFunction < __FromCollectionType, __ElementType >  __contains              /* NOLINT(bugprone-reserved-identifier) */
                > auto __IndicesOfCompositeClient <
                        __ReceiverType,
                        __ElementType,
                        __FromCollectionType,
                        __contains
                > :: lastIndexOfNotFrom (
                        __FromCollectionType const & from
                ) const noexcept -> Index {

                    Index index = static_cast < Index > ( reinterpret_cast < __ReceiverType const * > ( this )->size() ) - 1;
                    for (
                            auto
                                    iterator    = reinterpret_cast < __ReceiverType const * > ( this )->crbegin(),
                                    end         = reinterpret_cast < __ReceiverType const * > ( this )->crend();

                            iterator != end;
                            ++ iterator, -- index
                    ) {
                        if ( ! __contains ( from, * iterator ) ) {
                            return index;
                        }
                    }

                    return __ReceiverType :: invalidIndex;
                }

                template <
                        typename                                                    __ReceiverType,         /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                    __ElementType,          /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                    __FromCollectionType,   /* NOLINT(bugprone-reserved-identifier) */
                        __ContainsFunction < __FromCollectionType, __ElementType >  __contains              /* NOLINT(bugprone-reserved-identifier) */
                > template <
                        typename __CollectionType                                                           /* NOLINT(bugprone-reserved-identifier) */
                > auto __IndicesOfCompositeClient <
                        __ReceiverType,
                        __ElementType,
                        __FromCollectionType,
                        __contains
                > :: allIndicesOfNotFrom (
                        __CollectionType              & storeIn,
                        __FromCollectionType    const & from
                ) const noexcept -> __CollectionType & {

                    Size  foundCount = 0ULL;
                    Index index      = 0;

                    for (
                            auto
                                    iterator    = reinterpret_cast < __ReceiverType const * > ( this )->cbegin(),
                                    end         = reinterpret_cast < __ReceiverType const * > ( this )->cend();

                            iterator != end;
                            ++ iterator, ++ index
                    ) {
                        if ( ! __contains ( from, * iterator ) ) {
                            (void) storeIn.insert ( index );
                            ++ foundCount;
                        }
                    }

                    return storeIn;
                }


                template <
                        typename                                                    __ReceiverType,         /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                    __ElementType,          /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                    __FromCollectionType,   /* NOLINT(bugprone-reserved-identifier) */
                        __ContainsFunction < __FromCollectionType, __ElementType >  __contains              /* NOLINT(bugprone-reserved-identifier) */
                > template <
                        template < typename ... > class __CollectionType                                    /* NOLINT(bugprone-reserved-identifier) */
                > __CDS_OptimalInline auto __IndicesOfCompositeClient <
                        __ReceiverType,
                        __ElementType,
                        __FromCollectionType,
                        __contains
                > :: allIndicesOfNotFrom (
                        __FromCollectionType    const & from
                ) const noexcept -> __CollectionType < Index > {

                    __CollectionType < Index > indices;
                    return std :: move (
                            this->allIndicesOfNotFrom (
                                    indices,
                                    from
                            )
                    );
                }

            }
        }
    }
}

#endif /* __CDS_SHARED_INDICES_OF_COMPOSITE_CLIENT_IMPL_HPP__ */
