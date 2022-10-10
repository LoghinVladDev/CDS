/*
 * Created by loghin on 6/26/22.
 */

#ifndef __CDS_SHARED_FIND_OF_IMMUTABLE_COMPOSITE_CLIENT_IMPL_HPP__
#define __CDS_SHARED_FIND_OF_IMMUTABLE_COMPOSITE_CLIENT_IMPL_HPP__ /* NOLINT(bugprone-reserved-identifier) */

namespace cds {             /* NOLINT(modernize-concat-nested-namespaces) */
    namespace __hidden {    /* NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier) */
        namespace __impl {  /* NOLINT(bugprone-reserved-identifier) */

            template <
                    typename                                                    __IterableType,         /* NOLINT(bugprone-reserved-identifier) */
                    typename                                                    __ElementType,          /* NOLINT(bugprone-reserved-identifier) */
                    typename                                                    __IteratorType,         /* NOLINT(bugprone-reserved-identifier) */
                    typename                                                    __FromIterableType,     /* NOLINT(bugprone-reserved-identifier) */
                    __ContainsFunction < __FromIterableType, __ElementType >    __containsFunction,     /* NOLINT(bugprone-reserved-identifier) */
                    __ContainsFunction < __FromIterableType, __ElementType >    __notContainsFunction   /* NOLINT(bugprone-reserved-identifier) */
            > template <
                    template < typename ... > class                             __CollectionType    /* NOLINT(bugprone-reserved-identifier) */
            > __CDS_OptimalInline auto __FindOfImmutableCompositeClient <
                    __IterableType,
                    __ElementType,
                    __IteratorType,
                    __FromIterableType,
                    __containsFunction,
                    __notContainsFunction
            > :: findOf (
                    Size                                        count,
                    __CollectionType < ConstIterator >        & storeIn,
                    __FromIterableType                  const & from
            ) const noexcept -> __CollectionType < ConstIterator > & {

                /* Call base, global implementation. Abstracts the 'is object const' requirement */
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
                    typename                                                    __IterableType,         /* NOLINT(bugprone-reserved-identifier) */
                    typename                                                    __ElementType,          /* NOLINT(bugprone-reserved-identifier) */
                    typename                                                    __IteratorType,         /* NOLINT(bugprone-reserved-identifier) */
                    typename                                                    __FromIterableType,     /* NOLINT(bugprone-reserved-identifier) */
                    __ContainsFunction < __FromIterableType, __ElementType >    __containsFunction,     /* NOLINT(bugprone-reserved-identifier) */
                    __ContainsFunction < __FromIterableType, __ElementType >    __notContainsFunction   /* NOLINT(bugprone-reserved-identifier) */
            > template <
                    template < typename ... > class                             __CollectionType    /* NOLINT(bugprone-reserved-identifier) */
            > __CDS_OptimalInline auto __FindOfImmutableCompositeClient <
                    __IterableType,
                    __ElementType,
                    __IteratorType,
                    __FromIterableType,
                    __containsFunction,
                    __notContainsFunction
            > :: findOf (
                    Size                        count,
                    __FromIterableType  const & from
            ) const noexcept -> __CollectionType < ConstIterator > {

                /* Call base, global implementation. Abstracts the 'is object const' requirement */
                __CollectionType < ConstIterator > foundIterators;
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
                        foundIterators,
                        from
                );
            }


            template <
                    typename                                                    __IterableType,         /* NOLINT(bugprone-reserved-identifier) */
                    typename                                                    __ElementType,          /* NOLINT(bugprone-reserved-identifier) */
                    typename                                                    __IteratorType,         /* NOLINT(bugprone-reserved-identifier) */
                    typename                                                    __FromIterableType,     /* NOLINT(bugprone-reserved-identifier) */
                    __ContainsFunction < __FromIterableType, __ElementType >    __containsFunction,     /* NOLINT(bugprone-reserved-identifier) */
                    __ContainsFunction < __FromIterableType, __ElementType >    __notContainsFunction   /* NOLINT(bugprone-reserved-identifier) */
            > __CDS_OptimalInline auto __FindOfImmutableCompositeClient <
                    __IterableType,
                    __ElementType,
                    __IteratorType,
                    __FromIterableType,
                    __containsFunction,
                    __notContainsFunction
            > :: findFirstOf (
                    __FromIterableType const & from
            ) const noexcept -> ConstIterator {

                /* Call base, global implementation. Abstracts the 'is object const' requirement */
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
                    typename                                                    __IterableType,         /* NOLINT(bugprone-reserved-identifier) */
                    typename                                                    __ElementType,          /* NOLINT(bugprone-reserved-identifier) */
                    typename                                                    __IteratorType,         /* NOLINT(bugprone-reserved-identifier) */
                    typename                                                    __FromIterableType,     /* NOLINT(bugprone-reserved-identifier) */
                    __ContainsFunction < __FromIterableType, __ElementType >    __containsFunction,     /* NOLINT(bugprone-reserved-identifier) */
                    __ContainsFunction < __FromIterableType, __ElementType >    __notContainsFunction   /* NOLINT(bugprone-reserved-identifier) */
            > __CDS_OptimalInline auto __FindOfImmutableCompositeClient <
                    __IterableType,
                    __ElementType,
                    __IteratorType,
                    __FromIterableType,
                    __containsFunction,
                    __notContainsFunction
            > :: findLastOf (
                    __FromIterableType const & from
            ) const noexcept -> ConstIterator {

                /* Call base, global implementation. Abstracts the 'is object const' requirement */
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
                    typename                                                    __IterableType,         /* NOLINT(bugprone-reserved-identifier) */
                    typename                                                    __ElementType,          /* NOLINT(bugprone-reserved-identifier) */
                    typename                                                    __IteratorType,         /* NOLINT(bugprone-reserved-identifier) */
                    typename                                                    __FromIterableType,     /* NOLINT(bugprone-reserved-identifier) */
                    __ContainsFunction < __FromIterableType, __ElementType >    __containsFunction,     /* NOLINT(bugprone-reserved-identifier) */
                    __ContainsFunction < __FromIterableType, __ElementType >    __notContainsFunction   /* NOLINT(bugprone-reserved-identifier) */
            > template <
                    template < typename ... > class                             __CollectionType    /* NOLINT(bugprone-reserved-identifier) */
            > __CDS_OptimalInline auto __FindOfImmutableCompositeClient <
                    __IterableType,
                    __ElementType,
                    __IteratorType,
                    __FromIterableType,
                    __containsFunction,
                    __notContainsFunction
            > :: findAllOf (
                    __CollectionType < ConstIterator >        & storeIn,
                    __FromIterableType                  const & from
            ) const noexcept -> __CollectionType < ConstIterator > & {

                /* Call base, global implementation. Abstracts the 'is object const' requirement */
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
                    typename                                                    __IterableType,         /* NOLINT(bugprone-reserved-identifier) */
                    typename                                                    __ElementType,          /* NOLINT(bugprone-reserved-identifier) */
                    typename                                                    __IteratorType,         /* NOLINT(bugprone-reserved-identifier) */
                    typename                                                    __FromIterableType,     /* NOLINT(bugprone-reserved-identifier) */
                    __ContainsFunction < __FromIterableType, __ElementType >    __containsFunction,     /* NOLINT(bugprone-reserved-identifier) */
                    __ContainsFunction < __FromIterableType, __ElementType >    __notContainsFunction   /* NOLINT(bugprone-reserved-identifier) */
            > template <
                    template < typename ... > class                             __CollectionType    /* NOLINT(bugprone-reserved-identifier) */
            > __CDS_OptimalInline auto __FindOfImmutableCompositeClient <
                    __IterableType,
                    __ElementType,
                    __IteratorType,
                    __FromIterableType,
                    __containsFunction,
                    __notContainsFunction
            > :: findAllOf (
                    __FromIterableType const & from
            ) const noexcept -> __CollectionType < ConstIterator > {

                /* Call base, global implementation. Abstracts the 'is object const' requirement */
                __CollectionType < ConstIterator > foundIterators;
                return __findAllOf <
                        __ElementType,
                        ConstIterator,
                        __FromIterableType,
                        __CollectionType,
                        __containsFunction
                > (
                        reinterpret_cast < __IterableType const * > ( this )->cbegin(),
                        reinterpret_cast < __IterableType const * > ( this )->cend(),
                        foundIterators,
                        from
                );
            }

            template <
                    typename                                                    __IterableType,         /* NOLINT(bugprone-reserved-identifier) */
                    typename                                                    __ElementType,          /* NOLINT(bugprone-reserved-identifier) */
                    typename                                                    __IteratorType,         /* NOLINT(bugprone-reserved-identifier) */
                    typename                                                    __FromIterableType,     /* NOLINT(bugprone-reserved-identifier) */
                    __ContainsFunction < __FromIterableType, __ElementType >    __containsFunction,     /* NOLINT(bugprone-reserved-identifier) */
                    __ContainsFunction < __FromIterableType, __ElementType >    __notContainsFunction   /* NOLINT(bugprone-reserved-identifier) */
            > template <
                    template < typename ... > class                             __CollectionType    /* NOLINT(bugprone-reserved-identifier) */
            > __CDS_OptimalInline auto __FindOfImmutableCompositeClient <
                    __IterableType,
                    __ElementType,
                    __IteratorType,
                    __FromIterableType,
                    __containsFunction,
                    __notContainsFunction
            > :: findNotOf (
                    Size                                        count,
                    __CollectionType < ConstIterator >        & storeIn,
                    __FromIterableType                  const & from
            ) const noexcept -> __CollectionType < ConstIterator > & {

                /* Call base, global implementation. Abstracts the 'is object const' requirement */
                return __findOf <
                        __ElementType,
                        ConstIterator,
                        __FromIterableType,
                        __CollectionType,
                        __notContainsFunction
                > (
                        reinterpret_cast < __IterableType const * > ( this )->cbegin(),
                        reinterpret_cast < __IterableType const * > ( this )->cend(),
                        count,
                        storeIn,
                        from
                );
            }


            template <
                    typename                                                    __IterableType,         /* NOLINT(bugprone-reserved-identifier) */
                    typename                                                    __ElementType,          /* NOLINT(bugprone-reserved-identifier) */
                    typename                                                    __IteratorType,         /* NOLINT(bugprone-reserved-identifier) */
                    typename                                                    __FromIterableType,     /* NOLINT(bugprone-reserved-identifier) */
                    __ContainsFunction < __FromIterableType, __ElementType >    __containsFunction,     /* NOLINT(bugprone-reserved-identifier) */
                    __ContainsFunction < __FromIterableType, __ElementType >    __notContainsFunction   /* NOLINT(bugprone-reserved-identifier) */
            > template <
                    template < typename ... > class                             __CollectionType    /* NOLINT(bugprone-reserved-identifier) */
            > __CDS_OptimalInline auto __FindOfImmutableCompositeClient <
                    __IterableType,
                    __ElementType,
                    __IteratorType,
                    __FromIterableType,
                    __containsFunction,
                    __notContainsFunction
            > :: findNotOf (
                    Size                        count,
                    __FromIterableType  const & from
            ) const noexcept -> __CollectionType < ConstIterator > {

                /* Call base, global implementation. Abstracts the 'is object const' requirement */
                __CollectionType < ConstIterator > foundIterators;
                return __findOf <
                        __ElementType,
                        ConstIterator,
                        __FromIterableType,
                        __CollectionType,
                        __notContainsFunction
                > (
                        reinterpret_cast < __IterableType const * > ( this )->cbegin(),
                        reinterpret_cast < __IterableType const * > ( this )->cend(),
                        count,
                        foundIterators,
                        from
                );
            }


            template <
                    typename                                                    __IterableType,         /* NOLINT(bugprone-reserved-identifier) */
                    typename                                                    __ElementType,          /* NOLINT(bugprone-reserved-identifier) */
                    typename                                                    __IteratorType,         /* NOLINT(bugprone-reserved-identifier) */
                    typename                                                    __FromIterableType,     /* NOLINT(bugprone-reserved-identifier) */
                    __ContainsFunction < __FromIterableType, __ElementType >    __containsFunction,     /* NOLINT(bugprone-reserved-identifier) */
                    __ContainsFunction < __FromIterableType, __ElementType >    __notContainsFunction   /* NOLINT(bugprone-reserved-identifier) */
            > __CDS_OptimalInline auto __FindOfImmutableCompositeClient <
                    __IterableType,
                    __ElementType,
                    __IteratorType,
                    __FromIterableType,
                    __containsFunction,
                    __notContainsFunction
            > :: findFirstNotOf (
                    __FromIterableType const & from
            ) const noexcept -> ConstIterator {

                /* Call base, global implementation. Abstracts the 'is object const' requirement */
                return __findFirstOf <
                        __ElementType,
                        ConstIterator,
                        __FromIterableType,
                        __notContainsFunction
                > (
                        reinterpret_cast < __IterableType const * > ( this )->cbegin(),
                        reinterpret_cast < __IterableType const * > ( this )->cend(),
                        from
                );
            }


            template <
                    typename                                                    __IterableType,         /* NOLINT(bugprone-reserved-identifier) */
                    typename                                                    __ElementType,          /* NOLINT(bugprone-reserved-identifier) */
                    typename                                                    __IteratorType,         /* NOLINT(bugprone-reserved-identifier) */
                    typename                                                    __FromIterableType,     /* NOLINT(bugprone-reserved-identifier) */
                    __ContainsFunction < __FromIterableType, __ElementType >    __containsFunction,     /* NOLINT(bugprone-reserved-identifier) */
                    __ContainsFunction < __FromIterableType, __ElementType >    __notContainsFunction   /* NOLINT(bugprone-reserved-identifier) */
            > __CDS_OptimalInline auto __FindOfImmutableCompositeClient <
                    __IterableType,
                    __ElementType,
                    __IteratorType,
                    __FromIterableType,
                    __containsFunction,
                    __notContainsFunction
            > :: findLastNotOf (
                    __FromIterableType const & from
            ) const noexcept -> ConstIterator {

                /* Call base, global implementation. Abstracts the 'is object const' requirement */
                return __findLastOf <
                        __ElementType,
                        ConstIterator,
                        __FromIterableType,
                        __notContainsFunction
                > (
                        reinterpret_cast < __IterableType const * > ( this )->cbegin(),
                        reinterpret_cast < __IterableType const * > ( this )->cend(),
                        from
                );
            }


            template <
                    typename                                                    __IterableType,         /* NOLINT(bugprone-reserved-identifier) */
                    typename                                                    __ElementType,          /* NOLINT(bugprone-reserved-identifier) */
                    typename                                                    __IteratorType,         /* NOLINT(bugprone-reserved-identifier) */
                    typename                                                    __FromIterableType,     /* NOLINT(bugprone-reserved-identifier) */
                    __ContainsFunction < __FromIterableType, __ElementType >    __containsFunction,     /* NOLINT(bugprone-reserved-identifier) */
                    __ContainsFunction < __FromIterableType, __ElementType >    __notContainsFunction   /* NOLINT(bugprone-reserved-identifier) */
            > template <
                    template < typename ... > class                             __CollectionType    /* NOLINT(bugprone-reserved-identifier) */
            > __CDS_OptimalInline auto __FindOfImmutableCompositeClient <
                    __IterableType,
                    __ElementType,
                    __IteratorType,
                    __FromIterableType,
                    __containsFunction,
                    __notContainsFunction
            > :: findAllNotOf (
                    __CollectionType < ConstIterator >        & storeIn,
                    __FromIterableType                  const & from
            ) const noexcept -> __CollectionType < ConstIterator > & {

                /* Call base, global implementation. Abstracts the 'is object const' requirement */
                return __findAllOf <
                        __ElementType,
                        ConstIterator,
                        __FromIterableType,
                        __CollectionType,
                        __notContainsFunction
                > (
                        reinterpret_cast < __IterableType const * > ( this )->cbegin(),
                        reinterpret_cast < __IterableType const * > ( this )->cend(),
                        storeIn,
                        from
                );
            }


            template <
                    typename                                                    __IterableType,         /* NOLINT(bugprone-reserved-identifier) */
                    typename                                                    __ElementType,          /* NOLINT(bugprone-reserved-identifier) */
                    typename                                                    __IteratorType,         /* NOLINT(bugprone-reserved-identifier) */
                    typename                                                    __FromIterableType,     /* NOLINT(bugprone-reserved-identifier) */
                    __ContainsFunction < __FromIterableType, __ElementType >    __containsFunction,     /* NOLINT(bugprone-reserved-identifier) */
                    __ContainsFunction < __FromIterableType, __ElementType >    __notContainsFunction   /* NOLINT(bugprone-reserved-identifier) */
            > template <
                    template < typename ... > class                             __CollectionType    /* NOLINT(bugprone-reserved-identifier) */
            > __CDS_OptimalInline auto __FindOfImmutableCompositeClient <
                    __IterableType,
                    __ElementType,
                    __IteratorType,
                    __FromIterableType,
                    __containsFunction,
                    __notContainsFunction
            > :: findAllNotOf (
                    __FromIterableType const & from
            ) const noexcept -> __CollectionType < ConstIterator > {

                /* Call base, global implementation. Abstracts the 'is object const' requirement */
                __CollectionType < ConstIterator > foundIterators;
                return __findAllOf <
                        __ElementType,
                        ConstIterator,
                        __FromIterableType,
                        __CollectionType,
                        __notContainsFunction
                > (
                        reinterpret_cast < __IterableType const * > ( this )->cbegin(),
                        reinterpret_cast < __IterableType const * > ( this )->cend(),
                        foundIterators,
                        from
                );
            }

        }
    }
}

#endif /* __CDS_SHARED_FIND_OF_IMMUTABLE_COMPOSITE_CLIENT_IMPL_HPP__ */
