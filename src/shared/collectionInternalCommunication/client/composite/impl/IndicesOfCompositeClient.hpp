/*
 * Created by loghin on 6/30/22.
 */

#ifndef __CDS_SHARED_INDICES_OF_COMPOSITE_CLIENT_IMPL_HPP__ /* NOLINT(llvm-header-guard) */
#define __CDS_SHARED_INDICES_OF_COMPOSITE_CLIENT_IMPL_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

namespace cds {             /* NOLINT(modernize-concat-nested-namespaces) */
    namespace __hidden {    /* NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        namespace __impl {  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            template <
                    typename                                                                                __ReceiverType,         /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                                __ElementType,          /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                                __FromCollectionType,   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: PredicateFunction < __FromCollectionType const &, __ElementType const & > __contains              /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > template <
                    typename __CollectionType                                                           /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
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
                    typename                                                                                __ReceiverType,         /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                                __ElementType,          /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                                __FromCollectionType,   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: PredicateFunction < __FromCollectionType const &, __ElementType const & > __contains              /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > template <
                    template < typename ... > class __CollectionType                                    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
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
                    typename                                                                                __ReceiverType,         /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                                __ElementType,          /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                                __FromCollectionType,   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: PredicateFunction < __FromCollectionType const &, __ElementType const & > __contains              /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
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
                    typename                                                                                __ReceiverType,         /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                                __ElementType,          /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                                __FromCollectionType,   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: PredicateFunction < __FromCollectionType const &, __ElementType const & > __contains              /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
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
                    typename                                                                                __ReceiverType,         /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                                __ElementType,          /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                                __FromCollectionType,   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: PredicateFunction < __FromCollectionType const &, __ElementType const & > __contains              /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > template <
                    typename __CollectionType                                                           /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
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
                    typename                                                                                __ReceiverType,         /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                                __ElementType,          /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                                __FromCollectionType,   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: PredicateFunction < __FromCollectionType const &, __ElementType const & > __contains              /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > template <
                    template < typename ... > class __CollectionType                                    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
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
                    typename                                                                                __ReceiverType,         /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                                __ElementType,          /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                                __FromCollectionType,   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: PredicateFunction < __FromCollectionType const &, __ElementType const & > __contains              /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > template <
                    typename __CollectionType                                                           /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
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
                    typename                                                                                __ReceiverType,         /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                                __ElementType,          /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                                __FromCollectionType,   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: PredicateFunction < __FromCollectionType const &, __ElementType const & > __contains              /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > template <
                    template < typename ... > class __CollectionType                                    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
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
                    typename                                                                                __ReceiverType,         /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                                __ElementType,          /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                                __FromCollectionType,   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: PredicateFunction < __FromCollectionType const &, __ElementType const & > __contains              /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
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
                    typename                                                                                __ReceiverType,         /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                                __ElementType,          /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                                __FromCollectionType,   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: PredicateFunction < __FromCollectionType const &, __ElementType const & > __contains              /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
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
                    typename                                                                                __ReceiverType,         /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                                __ElementType,          /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                                __FromCollectionType,   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: PredicateFunction < __FromCollectionType const &, __ElementType const & > __contains              /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > template <
                    typename __CollectionType                                                           /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
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
                    typename                                                                                __ReceiverType,         /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                                __ElementType,          /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                                __FromCollectionType,   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: PredicateFunction < __FromCollectionType const &, __ElementType const & > __contains              /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > template <
                    template < typename ... > class __CollectionType                                    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
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

        } /* namespace __impl */
    } /* namespace __hidden */
} /* namespace cds */

#endif /* __CDS_SHARED_INDICES_OF_COMPOSITE_CLIENT_IMPL_HPP__ */
