/*
 * Created by loghin on 6/30/22.
 */

#ifndef __CDS_SHARED_INDICES_COMPOSITE_CLIENT_IMPL_HPP__ /* NOLINT(llvm-header-guard) */
#define __CDS_SHARED_INDICES_COMPOSITE_CLIENT_IMPL_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

namespace cds {             /* NOLINT(modernize-concat-nested-namespaces) */
    namespace __hidden {    /* NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        namespace __impl {  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            template <
                    typename __ReceiverType,    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ElementType      /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > template <
                    typename __CollectionType   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > auto __IndicesCompositeClient <
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
                            iterator    = reinterpret_cast < __ReceiverType const * > ( this )->cbegin (),
                            end         = reinterpret_cast < __ReceiverType const * > ( this )->cend ();

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
                    typename __ReceiverType,                            /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ElementType                              /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > template <
                    template < typename ... > class __CollectionType    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > __CDS_OptimalInline auto __IndicesCompositeClient <
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
                    typename __ReceiverType,                            /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ElementType                              /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > auto __IndicesCompositeClient <
                    __ReceiverType,
                    __ElementType
            > :: firstIndexOf (
                    ElementType const & element
            ) const noexcept -> Index {

                Index index = 0;
                for (
                        auto
                                iterator    = reinterpret_cast < __ReceiverType const * > ( this )->cbegin (),
                                end         = reinterpret_cast < __ReceiverType const * > ( this )->cend ();

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
                    typename __ReceiverType,                            /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ElementType                              /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > auto __IndicesCompositeClient <
                    __ReceiverType,
                    __ElementType
            > :: lastIndexOf (
                    ElementType const & element
            ) const noexcept -> Index {

                Index index = static_cast < Index > ( reinterpret_cast < __ReceiverType const * > ( this )->size() ) - 1;
                for (
                        auto
                                iterator    = reinterpret_cast < __ReceiverType const * > ( this )->crbegin (),
                                end         = reinterpret_cast < __ReceiverType const * > ( this )->crend ();

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
                    typename __ReceiverType,    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ElementType      /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > template <
                    typename __CollectionType   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > auto __IndicesCompositeClient <
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
                                iterator    = reinterpret_cast < __ReceiverType const * > ( this )->cbegin (),
                                end         = reinterpret_cast < __ReceiverType const * > ( this )->cend ();

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
                    typename __ReceiverType,                            /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ElementType                              /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > template <
                    template < typename ... > class __CollectionType    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > __CDS_OptimalInline auto __IndicesCompositeClient <
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

        } /* namespace __impl */
    } /* namespace __hidden */
} /* namespace cds */

#endif /* __CDS_SHARED_INDICES_COMPOSITE_CLIENT_IMPL_HPP__ */
