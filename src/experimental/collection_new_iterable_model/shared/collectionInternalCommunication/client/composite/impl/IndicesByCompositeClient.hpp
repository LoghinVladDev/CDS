//
// Created by loghin on 6/30/22.
//

#ifndef __CDS_SHARED_INDICES_BY_COMPOSITE_CLIENT_IMPL_HPP__
#define __CDS_SHARED_INDICES_BY_COMPOSITE_CLIENT_IMPL_HPP__

namespace cds {                 // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {    // NOLINT(modernize-concat-nested-namespaces)
        namespace __hidden {    // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier)
            namespace __impl {  // NOLINT(bugprone-reserved-identifier)

                template <
                        typename __ReceiverType,    // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType      // NOLINT(bugprone-reserved-identifier)
                > template <
                        typename __CollectionType,  // NOLINT(bugprone-reserved-identifier)
                        typename __Predicate        // NOLINT(bugprone-reserved-identifier)
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
                                iterator    = static_cast < __ReceiverType const * > ( this )->cbegin (),
                                end         = static_cast < __ReceiverType const * > ( this )->cend ();

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
                        typename __ReceiverType,                            // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType                              // NOLINT(bugprone-reserved-identifier)
                > template <
                        template < typename ... > class __CollectionType,   // NOLINT(bugprone-reserved-identifier)
                        typename __Predicate                                // NOLINT(bugprone-reserved-identifier)
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
                        typename __ReceiverType,                            // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType                              // NOLINT(bugprone-reserved-identifier)
                > template <
                        typename __Predicate                                // NOLINT(bugprone-reserved-identifier)
                > auto __IndicesByCompositeClient <
                        __ReceiverType,
                        __ElementType
                > :: firstIndexOfThat (
                        __Predicate const & predicate
                ) const noexcept ( noexcept ( predicate ( cds :: meta :: referenceOf < ElementType const > () ) ) ) -> Index {

                    Index index = 0;
                    for (
                            auto
                                iterator    = static_cast < __ReceiverType const * > ( this )->cbegin (),
                                end         = static_cast < __ReceiverType const * > ( this )->cend();

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
                        typename __ReceiverType,                            // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType                              // NOLINT(bugprone-reserved-identifier)
                > template <
                        typename __Predicate                                // NOLINT(bugprone-reserved-identifier)
                > auto __IndicesByCompositeClient <
                        __ReceiverType,
                        __ElementType
                > :: lastIndexOfThat (
                        __Predicate const & predicate
                ) const noexcept ( noexcept ( predicate ( cds :: meta :: referenceOf < ElementType const > () ) ) ) -> Index {

                    Index index = static_cast < Index > ( static_cast < __ReceiverType const * > ( this )->size () ) - 1;
                    for (
                            auto
                                iterator    = static_cast < __ReceiverType const * > ( this )->crbegin (),
                                end         = static_cast < __ReceiverType const * > ( this )->crend();

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
                        typename __ReceiverType,    // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType      // NOLINT(bugprone-reserved-identifier)
                > template <
                        typename __CollectionType,  // NOLINT(bugprone-reserved-identifier)
                        typename __Predicate        // NOLINT(bugprone-reserved-identifier)
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
                                    iterator    = static_cast < __ReceiverType const * > ( this )->cbegin (),
                                    end         = static_cast < __ReceiverType const * > ( this )->cend ();

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
                        typename __ReceiverType,                            // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType                              // NOLINT(bugprone-reserved-identifier)
                > template <
                        template < typename ... > class __CollectionType,   // NOLINT(bugprone-reserved-identifier)
                        typename __Predicate                                // NOLINT(bugprone-reserved-identifier)
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

            }
        }
    }
}

#endif // __CDS_SHARED_INDICES_BY_COMPOSITE_CLIENT_IMPL_HPP__
