/*
 * Created by loghin on 6/30/22.
 */

#ifndef __CDS_SHARED_INDICES_BY_COMPOSITE_CLIENT_IMPL_HPP__ /* NOLINT(llvm-header-guard) */
#define __CDS_SHARED_INDICES_BY_COMPOSITE_CLIENT_IMPL_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

namespace cds {             /* NOLINT(modernize-concat-nested-namespaces) */
    namespace __hidden {    /* NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        namespace __impl {  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            template <
                    typename __ReceiverType,    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ElementType      /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > template <
                    typename __CollectionType,  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __Predicate        /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > auto __IndicesByCompositeClient <
                    __ReceiverType,
                    __ElementType
            > :: indicesOfThat (
                    Size                        count,
                    __CollectionType          & storeIn,
                    __Predicate         const & predicate
            ) const noexcept ( noexcept ( predicate ( cds :: meta :: referenceOf < ElementType const > () ) ) ) -> __CollectionType & {

                Index   index       = 0;
                Size    foundCount  = 0ULL;

                for (
                        auto
                            iterator    = reinterpret_cast < __ReceiverType const * > ( this )->cbegin (),
                            end         = reinterpret_cast < __ReceiverType const * > ( this )->cend ();

                        iterator != end && foundCount < count;
                        ++ iterator, ++ index
                ) {
                    if ( predicate ( * iterator ) ) {
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
                    template < typename ... > class __CollectionType,   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __Predicate                                /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > __CDS_OptimalInline auto __IndicesByCompositeClient <
                    __ReceiverType,
                    __ElementType
            > :: indicesOfThat (
                    Size                        count,
                    __Predicate         const & predicate
            ) const noexcept ( noexcept ( predicate ( cds :: meta :: referenceOf < ElementType const > () ) ) ) -> __CollectionType < Index > {

                __CollectionType < Index > indices;
                return std :: move (
                        this->indicesOfThat (
                                count,
                                indices,
                                predicate
                        )
                );
            }


            template <
                    typename __ReceiverType,                            /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ElementType                              /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > template <
                    typename __Predicate                                /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > auto __IndicesByCompositeClient <
                    __ReceiverType,
                    __ElementType
            > :: firstIndexOfThat (
                    __Predicate const & predicate
            ) const noexcept ( noexcept ( predicate ( cds :: meta :: referenceOf < ElementType const > () ) ) ) -> Index {

                Index index = 0;
                for (
                        auto
                            iterator    = reinterpret_cast < __ReceiverType const * > ( this )->cbegin (),
                            end         = reinterpret_cast < __ReceiverType const * > ( this )->cend();

                        iterator != end;
                        ++ iterator, ++ index
                ) {
                    if ( predicate ( index ) ) {
                        return index;
                    }
                }

                return __ReceiverType :: invalidIndex;
            }


            template <
                    typename __ReceiverType,                            /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ElementType                              /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > template <
                    typename __Predicate                                /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > auto __IndicesByCompositeClient <
                    __ReceiverType,
                    __ElementType
            > :: lastIndexOfThat (
                    __Predicate const & predicate
            ) const noexcept ( noexcept ( predicate ( cds :: meta :: referenceOf < ElementType const > () ) ) ) -> Index {

                Index index = static_cast < Index > ( reinterpret_cast < __ReceiverType const * > ( this )->size () ) - 1;
                for (
                        auto
                            iterator    = reinterpret_cast < __ReceiverType const * > ( this )->crbegin (),
                            end         = reinterpret_cast < __ReceiverType const * > ( this )->crend();

                        iterator != end;
                        ++ iterator, -- index
                ) {
                    if ( predicate ( index ) ) {
                        return index;
                    }
                }

                return __ReceiverType :: invalidIndex;
            }


            template <
                    typename __ReceiverType,    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ElementType      /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > template <
                    typename __CollectionType,  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __Predicate        /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > auto __IndicesByCompositeClient <
                    __ReceiverType,
                    __ElementType
            > :: allIndicesOfThat (
                    __CollectionType          & storeIn,
                    __Predicate         const & predicate
            ) const noexcept ( noexcept ( predicate ( cds :: meta :: referenceOf < ElementType const > () ) ) ) -> __CollectionType & {

                Index index = 0;
                for (
                        auto
                                iterator    = reinterpret_cast < __ReceiverType const * > ( this )->cbegin (),
                                end         = reinterpret_cast < __ReceiverType const * > ( this )->cend ();

                        iterator != end;
                        ++ iterator, ++ index
                ) {
                    if ( predicate ( * iterator ) ) {
                        (void) storeIn.insert ( index );
                    }
                }

                return storeIn;
            }


            template <
                    typename __ReceiverType,                            /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ElementType                              /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > template <
                    template < typename ... > class __CollectionType,   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __Predicate                                /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > __CDS_OptimalInline auto __IndicesByCompositeClient <
                    __ReceiverType,
                    __ElementType
            > :: allIndicesOfThat (
                    __Predicate         const & predicate
            ) const noexcept ( noexcept ( predicate ( cds :: meta :: referenceOf < ElementType const > () ) ) ) -> __CollectionType < Index > {

                __CollectionType < Index > indices;
                return std :: move (
                        this->allIndicesOfThat (
                                indices,
                                predicate
                        )
                );
            }

        } /* namespace __impl */
    } /* namespace __hidden */
} /* namespace cds */

#endif /* __CDS_SHARED_INDICES_BY_COMPOSITE_CLIENT_IMPL_HPP__ */
