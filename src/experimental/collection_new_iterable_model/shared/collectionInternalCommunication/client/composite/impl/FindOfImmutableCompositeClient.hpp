/*
 * Created by loghin on 6/26/22.
 */

#ifndef __CDS_SHARED_FIND_OF_IMMUTABLE_COMPOSITE_CLIENT_IMPL_HPP__
#define __CDS_SHARED_FIND_OF_IMMUTABLE_COMPOSITE_CLIENT_IMPL_HPP__ /* NOLINT(bugprone-reserved-identifier) */

namespace cds {                 /* NOLINT(modernize-concat-nested-namespaces) */
    namespace experimental {    /* NOLINT(modernize-concat-nested-namespaces) */
        namespace __hidden {    /* NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier) */
            namespace __impl {  /* NOLINT(bugprone-reserved-identifier) */

                template <
                        typename                                                    __IterableType,     /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                    __ElementType,      /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                    __IteratorType,     /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                    __FromIterableType, /* NOLINT(bugprone-reserved-identifier) */
                        __ContainsFunction < __FromIterableType, __ElementType >    __containsFunction  /* NOLINT(bugprone-reserved-identifier) */
                > template <
                        template < typename ... > class                             __CollectionType    /* NOLINT(bugprone-reserved-identifier) */
                > __CDS_OptimalInline auto __FindOfImmutableCompositeClient <
                        __IterableType,
                        __ElementType,
                        __IteratorType,
                        __FromIterableType,
                        __containsFunction
                > :: findOf (
                        Size                                        count,
                        __CollectionType < ConstIterator >        & storeIn,
                        __FromIterableType                  const & from
                ) const noexcept -> __CollectionType < ConstIterator > & {

                    return __findOf <
                            __ElementType,
                            ConstIterator,
                            __FromIterableType,
                            __CollectionType,
                            __containsFunction
                    > (
                            reinterpret_cast < __IterableType const * > ( this )->cbegin(),
                            reinterpret_cast < __IterableType const * > ( this )->cend(),
                            count,
                            storeIn,
                            from
                    );
                }


                template <
                        typename                                                    __IterableType,     /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                    __ElementType,      /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                    __IteratorType,     /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                    __FromIterableType, /* NOLINT(bugprone-reserved-identifier) */
                        __ContainsFunction < __FromIterableType, __ElementType >    __containsFunction  /* NOLINT(bugprone-reserved-identifier) */
                > template <
                        template < typename ... > class                             __CollectionType    /* NOLINT(bugprone-reserved-identifier) */
                > __CDS_OptimalInline auto __FindOfImmutableCompositeClient <
                        __IterableType,
                        __ElementType,
                        __IteratorType,
                        __FromIterableType,
                        __containsFunction
                > :: findOf (
                        Size                                        count,
                        __FromIterableType                  const & from
                ) const noexcept -> __CollectionType < ConstIterator > {

                    return __findOf <
                            __ElementType,
                            ConstIterator,
                            __FromIterableType,
                            __CollectionType,
                            __containsFunction
                    > (
                            reinterpret_cast < __IterableType const * > ( this )->cbegin(),
                            reinterpret_cast < __IterableType const * > ( this )->cend(),
                            count,
                            from
                    );
                }


                template <
                        typename                                                    __IterableType,     /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                    __ElementType,      /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                    __IteratorType,     /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                    __FromIterableType, /* NOLINT(bugprone-reserved-identifier) */
                        __ContainsFunction < __FromIterableType, __ElementType >    __containsFunction  /* NOLINT(bugprone-reserved-identifier) */
                > __CDS_OptimalInline auto __FindOfImmutableCompositeClient <
                        __IterableType,
                        __ElementType,
                        __IteratorType,
                        __FromIterableType,
                        __containsFunction
                > :: findFirstOf (
                        __FromIterableType                  const & from
                ) const noexcept -> ConstIterator {

                    return __findFirstOf <
                            __ElementType,
                            ConstIterator,
                            __FromIterableType,
                            __containsFunction
                    > (
                            reinterpret_cast < __IterableType const * > ( this )->cbegin(),
                            reinterpret_cast < __IterableType const * > ( this )->cend(),
                            from
                    );
                }


                template <
                        typename                                                    __IterableType,     /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                    __ElementType,      /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                    __IteratorType,     /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                    __FromIterableType, /* NOLINT(bugprone-reserved-identifier) */
                        __ContainsFunction < __FromIterableType, __ElementType >    __containsFunction  /* NOLINT(bugprone-reserved-identifier) */
                > __CDS_OptimalInline auto __FindOfImmutableCompositeClient <
                        __IterableType,
                        __ElementType,
                        __IteratorType,
                        __FromIterableType,
                        __containsFunction
                > :: findLastOf (
                        __FromIterableType                  const & from
                ) const noexcept -> ConstIterator {

                    return __findLastOf <
                            __ElementType,
                            ConstIterator,
                            __FromIterableType,
                            __containsFunction
                    > (
                            reinterpret_cast < __IterableType const * > ( this )->cbegin(),
                            reinterpret_cast < __IterableType const * > ( this )->cend(),
                            from
                    );
                }


                template <
                        typename                                                    __IterableType,     /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                    __ElementType,      /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                    __IteratorType,     /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                    __FromIterableType, /* NOLINT(bugprone-reserved-identifier) */
                        __ContainsFunction < __FromIterableType, __ElementType >    __containsFunction  /* NOLINT(bugprone-reserved-identifier) */
                > template <
                        template < typename ... > class                             __CollectionType    /* NOLINT(bugprone-reserved-identifier) */
                > __CDS_OptimalInline auto __FindOfImmutableCompositeClient <
                        __IterableType,
                        __ElementType,
                        __IteratorType,
                        __FromIterableType,
                        __containsFunction
                > :: findAllOf (
                        __CollectionType < ConstIterator >        & storeIn,
                        __FromIterableType                  const & from
                ) const noexcept -> __CollectionType < ConstIterator > & {

                    return __findAllOf <
                            __ElementType,
                            ConstIterator,
                            __FromIterableType,
                            __CollectionType,
                            __containsFunction
                    > (
                            reinterpret_cast < __IterableType const * > ( this )->cbegin(),
                            reinterpret_cast < __IterableType const * > ( this )->cend(),
                            storeIn,
                            from
                    );
                }


                template <
                        typename                                                    __IterableType,     /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                    __ElementType,      /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                    __IteratorType,     /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                    __FromIterableType, /* NOLINT(bugprone-reserved-identifier) */
                        __ContainsFunction < __FromIterableType, __ElementType >    __containsFunction  /* NOLINT(bugprone-reserved-identifier) */
                > template <
                        template < typename ... > class                             __CollectionType    /* NOLINT(bugprone-reserved-identifier) */
                > __CDS_OptimalInline auto __FindOfImmutableCompositeClient <
                        __IterableType,
                        __ElementType,
                        __IteratorType,
                        __FromIterableType,
                        __containsFunction
                > :: findAllOf (
                        __FromIterableType                  const & from
                ) const noexcept -> __CollectionType < ConstIterator > {

                    return __findAllOf <
                            __ElementType,
                            ConstIterator,
                            __FromIterableType,
                            __CollectionType,
                            __containsFunction
                    > (
                            reinterpret_cast < __IterableType const * > ( this )->cbegin(),
                            reinterpret_cast < __IterableType const * > ( this )->cend(),
                            from
                    );
                }

                template <
                        typename                                                    __IterableType,     /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                    __ElementType,      /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                    __IteratorType,     /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                    __FromIterableType, /* NOLINT(bugprone-reserved-identifier) */
                        __ContainsFunction < __FromIterableType, __ElementType >    __containsFunction  /* NOLINT(bugprone-reserved-identifier) */
                > template <
                        template < typename ... > class                             __CollectionType    /* NOLINT(bugprone-reserved-identifier) */
                > __CDS_OptimalInline auto __FindOfImmutableCompositeClient <
                        __IterableType,
                        __ElementType,
                        __IteratorType,
                        __FromIterableType,
                        __containsFunction
                > :: findNotOf (
                        Size                                        count,
                        __CollectionType < ConstIterator >        & storeIn,
                        __FromIterableType                  const & from
                ) const noexcept -> __CollectionType < ConstIterator > & {

                    return __findNotOf <
                            __ElementType,
                            ConstIterator,
                            __FromIterableType,
                            __CollectionType,
                            __containsFunction
                    > (
                            reinterpret_cast < __IterableType const * > ( this )->cbegin(),
                            reinterpret_cast < __IterableType const * > ( this )->cend(),
                            count,
                            storeIn,
                            from
                    );
                }


                template <
                        typename                                                    __IterableType,     /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                    __ElementType,      /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                    __IteratorType,     /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                    __FromIterableType, /* NOLINT(bugprone-reserved-identifier) */
                        __ContainsFunction < __FromIterableType, __ElementType >    __containsFunction  /* NOLINT(bugprone-reserved-identifier) */
                > template <
                        template < typename ... > class                             __CollectionType    /* NOLINT(bugprone-reserved-identifier) */
                > __CDS_OptimalInline auto __FindOfImmutableCompositeClient <
                        __IterableType,
                        __ElementType,
                        __IteratorType,
                        __FromIterableType,
                        __containsFunction
                > :: findNotOf (
                        Size                                        count,
                        __FromIterableType                  const & from
                ) const noexcept -> __CollectionType < ConstIterator > {

                    return __findNotOf <
                            __ElementType,
                            ConstIterator,
                            __FromIterableType,
                            __CollectionType,
                            __containsFunction
                    > (
                            reinterpret_cast < __IterableType const * > ( this )->cbegin(),
                            reinterpret_cast < __IterableType const * > ( this )->cend(),
                            count,
                            from
                    );
                }


                template <
                        typename                                                    __IterableType,     /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                    __ElementType,      /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                    __IteratorType,     /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                    __FromIterableType, /* NOLINT(bugprone-reserved-identifier) */
                        __ContainsFunction < __FromIterableType, __ElementType >    __containsFunction  /* NOLINT(bugprone-reserved-identifier) */
                > __CDS_OptimalInline auto __FindOfImmutableCompositeClient <
                        __IterableType,
                        __ElementType,
                        __IteratorType,
                        __FromIterableType,
                        __containsFunction
                > :: findFirstNotOf (
                        __FromIterableType                  const & from
                ) const noexcept -> ConstIterator {

                    return __findFirstNotOf <
                            __ElementType,
                            ConstIterator,
                            __FromIterableType,
                            __containsFunction
                    > (
                            reinterpret_cast < __IterableType const * > ( this )->cbegin(),
                            reinterpret_cast < __IterableType const * > ( this )->cend(),
                            from
                    );
                }


                template <
                        typename                                                    __IterableType,     /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                    __ElementType,      /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                    __IteratorType,     /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                    __FromIterableType, /* NOLINT(bugprone-reserved-identifier) */
                        __ContainsFunction < __FromIterableType, __ElementType >    __containsFunction  /* NOLINT(bugprone-reserved-identifier) */
                > __CDS_OptimalInline auto __FindOfImmutableCompositeClient <
                        __IterableType,
                        __ElementType,
                        __IteratorType,
                        __FromIterableType,
                        __containsFunction
                > :: findLastNotOf (
                        __FromIterableType                  const & from
                ) const noexcept -> ConstIterator {

                    return __findLastNotOf <
                            __ElementType,
                            ConstIterator,
                            __FromIterableType,
                            __containsFunction
                    > (
                            reinterpret_cast < __IterableType const * > ( this )->cbegin(),
                            reinterpret_cast < __IterableType const * > ( this )->cend(),
                            from
                    );
                }


                template <
                        typename                                                    __IterableType,     /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                    __ElementType,      /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                    __IteratorType,     /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                    __FromIterableType, /* NOLINT(bugprone-reserved-identifier) */
                        __ContainsFunction < __FromIterableType, __ElementType >    __containsFunction  /* NOLINT(bugprone-reserved-identifier) */
                > template <
                        template < typename ... > class                             __CollectionType    /* NOLINT(bugprone-reserved-identifier) */
                > __CDS_OptimalInline auto __FindOfImmutableCompositeClient <
                        __IterableType,
                        __ElementType,
                        __IteratorType,
                        __FromIterableType,
                        __containsFunction
                > :: findAllNotOf (
                        __CollectionType < ConstIterator >        & storeIn,
                        __FromIterableType                  const & from
                ) const noexcept -> __CollectionType < ConstIterator > & {

                    return __findAllNotOf <
                            __ElementType,
                            ConstIterator,
                            __FromIterableType,
                            __CollectionType,
                            __containsFunction
                    > (
                            reinterpret_cast < __IterableType const * > ( this )->cbegin(),
                            reinterpret_cast < __IterableType const * > ( this )->cend(),
                            storeIn,
                            from
                    );
                }


                template <
                        typename                                                    __IterableType,     /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                    __ElementType,      /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                    __IteratorType,     /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                    __FromIterableType, /* NOLINT(bugprone-reserved-identifier) */
                        __ContainsFunction < __FromIterableType, __ElementType >    __containsFunction  /* NOLINT(bugprone-reserved-identifier) */
                > template <
                        template < typename ... > class                             __CollectionType    /* NOLINT(bugprone-reserved-identifier) */
                > __CDS_OptimalInline auto __FindOfImmutableCompositeClient <
                        __IterableType,
                        __ElementType,
                        __IteratorType,
                        __FromIterableType,
                        __containsFunction
                > :: findAllNotOf (
                        __FromIterableType                  const & from
                ) const noexcept -> __CollectionType < ConstIterator > {

                    return __findAllNotOf <
                            __ElementType,
                            ConstIterator,
                            __FromIterableType,
                            __CollectionType,
                            __containsFunction
                    > (
                            reinterpret_cast < __IterableType const * > ( this )->cbegin(),
                            reinterpret_cast < __IterableType const * > ( this )->cend(),
                            from
                    );
                }

            }
        }
    }
}

#endif /* __CDS_SHARED_FIND_OF_IMMUTABLE_COMPOSITE_CLIENT_IMPL_HPP__ */
