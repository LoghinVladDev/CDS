/*
 * Created by loghin on 6/26/22.
 */

#ifndef __CDS_SHARED_FIND_OF_MUTABLE_COMPOSITE_CLIENT_IMPL_HPP__ /* NOLINT(llvm-header-guard) */
#define __CDS_SHARED_FIND_OF_MUTABLE_COMPOSITE_CLIENT_IMPL_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

namespace cds {             /* NOLINT(modernize-concat-nested-namespaces) */
    namespace __hidden {    /* NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        namespace __impl {  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            template <
                    typename                                                                                __IterableType,         /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                                __ElementType,          /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                                __IteratorType,         /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                                __FromIterableType,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: PredicateFunction < __FromIterableType const &, __ElementType const & >   __containsFunction,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: PredicateFunction < __FromIterableType const &, __ElementType const & >   __notContainsFunction   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > template <
                    template < typename ... > class                             __CollectionType    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > __CDS_OptimalInline auto __FindOfMutableCompositeClient <
                    __IterableType,
                    __ElementType,
                    __IteratorType,
                    __FromIterableType,
                    __containsFunction,
                    __notContainsFunction
            > :: findOf (
                    Size                                        count,
                    __CollectionType < Iterator >             & storeIn,
                    __FromIterableType                  const & from
            ) noexcept -> __CollectionType < Iterator > & {

                /* Call base, global implementation. Abstracts the 'is object const' requirement */
                return __findOf <
                        __ElementType,
                        Iterator,
                        __FromIterableType,
                        __CollectionType,
                        __containsFunction
                > (
                        reinterpret_cast < __IterableType * > ( this )->begin(),
                        reinterpret_cast < __IterableType * > ( this )->end(),
                        count,
                        storeIn,
                        from
                );
            }


            template <
                    typename                                                                                __IterableType,         /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                                __ElementType,          /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                                __IteratorType,         /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                                __FromIterableType,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: PredicateFunction < __FromIterableType const &, __ElementType const & >   __containsFunction,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: PredicateFunction < __FromIterableType const &, __ElementType const & >   __notContainsFunction   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > template <
                    template < typename ... > class                             __CollectionType    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > __CDS_OptimalInline auto __FindOfMutableCompositeClient <
                    __IterableType,
                    __ElementType,
                    __IteratorType,
                    __FromIterableType,
                    __containsFunction,
                    __notContainsFunction
            > :: findOf (
                    Size                        count,
                    __FromIterableType  const & from
            ) noexcept -> __CollectionType < Iterator > {

                /* Call base, global implementation. Abstracts the 'is object const' requirement */
                __CollectionType < Iterator > foundIterators;
                return __findOf <
                        __ElementType,
                        Iterator,
                        __FromIterableType,
                        __CollectionType,
                        __containsFunction
                > (
                        reinterpret_cast < __IterableType * > ( this )->begin(),
                        reinterpret_cast < __IterableType * > ( this )->end(),
                        count,
                        foundIterators,
                        from
                );
            }


            template <
                    typename                                                                                __IterableType,         /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                                __ElementType,          /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                                __IteratorType,         /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                                __FromIterableType,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: PredicateFunction < __FromIterableType const &, __ElementType const & >   __containsFunction,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: PredicateFunction < __FromIterableType const &, __ElementType const & >   __notContainsFunction   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > __CDS_OptimalInline auto __FindOfMutableCompositeClient <
                    __IterableType,
                    __ElementType,
                    __IteratorType,
                    __FromIterableType,
                    __containsFunction,
                    __notContainsFunction
            > :: findFirstOf (
                    __FromIterableType  const & from
            ) noexcept -> Iterator {

                /* Call base, global implementation. Abstracts the 'is object const' requirement */
                return __findFirstOf <
                        __ElementType,
                        Iterator,
                        __FromIterableType,
                        __containsFunction
                > (
                        reinterpret_cast < __IterableType * > ( this )->begin(),
                        reinterpret_cast < __IterableType * > ( this )->end(),
                        from
                );
            }


            template <
                    typename                                                                                __IterableType,         /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                                __ElementType,          /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                                __IteratorType,         /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                                __FromIterableType,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: PredicateFunction < __FromIterableType const &, __ElementType const & >   __containsFunction,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: PredicateFunction < __FromIterableType const &, __ElementType const & >   __notContainsFunction   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > __CDS_OptimalInline auto __FindOfMutableCompositeClient <
                    __IterableType,
                    __ElementType,
                    __IteratorType,
                    __FromIterableType,
                    __containsFunction,
                    __notContainsFunction
            > :: findLastOf (
                    __FromIterableType  const & from
            ) noexcept -> Iterator {

                /* Call base, global implementation. Abstracts the 'is object const' requirement */
                return __findLastOf <
                        __ElementType,
                        Iterator,
                        __FromIterableType,
                        __containsFunction
                > (
                        reinterpret_cast < __IterableType * > ( this )->begin(),
                        reinterpret_cast < __IterableType * > ( this )->end(),
                        from
                );
            }


            template <
                    typename                                                                                __IterableType,         /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                                __ElementType,          /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                                __IteratorType,         /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                                __FromIterableType,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: PredicateFunction < __FromIterableType const &, __ElementType const & >   __containsFunction,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: PredicateFunction < __FromIterableType const &, __ElementType const & >   __notContainsFunction   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > template <
                    template < typename ... > class                             __CollectionType    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > __CDS_OptimalInline auto __FindOfMutableCompositeClient <
                    __IterableType,
                    __ElementType,
                    __IteratorType,
                    __FromIterableType,
                    __containsFunction,
                    __notContainsFunction
            > :: findAllOf (
                    __CollectionType < Iterator >         & storeIn,
                    __FromIterableType              const & from
            ) noexcept -> __CollectionType < Iterator > & {

                /* Call base, global implementation. Abstracts the 'is object const' requirement */
                return __findAllOf <
                        __ElementType,
                        Iterator,
                        __FromIterableType,
                        __CollectionType,
                        __containsFunction
                > (
                        reinterpret_cast < __IterableType * > ( this )->begin(),
                        reinterpret_cast < __IterableType * > ( this )->end(),
                        storeIn,
                        from
                );
            }


            template <
                    typename                                                                                __IterableType,         /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                                __ElementType,          /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                                __IteratorType,         /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                                __FromIterableType,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: PredicateFunction < __FromIterableType const &, __ElementType const & >   __containsFunction,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: PredicateFunction < __FromIterableType const &, __ElementType const & >   __notContainsFunction   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > template <
                    template < typename ... > class                             __CollectionType    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > __CDS_OptimalInline auto __FindOfMutableCompositeClient <
                    __IterableType,
                    __ElementType,
                    __IteratorType,
                    __FromIterableType,
                    __containsFunction,
                    __notContainsFunction
            > :: findAllOf (
                    __FromIterableType  const & from
            ) noexcept -> __CollectionType < Iterator > {

                /* Call base, global implementation. Abstracts the 'is object const' requirement */
                __CollectionType < Iterator > foundIterators;
                return __findAllOf <
                        __ElementType,
                        Iterator,
                        __FromIterableType,
                        __CollectionType,
                        __containsFunction
                > (
                        reinterpret_cast < __IterableType * > ( this )->begin(),
                        reinterpret_cast < __IterableType * > ( this )->end(),
                        foundIterators,
                        from
                );
            }

            template <
                    typename                                                                                __IterableType,         /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                                __ElementType,          /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                                __IteratorType,         /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                                __FromIterableType,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: PredicateFunction < __FromIterableType const &, __ElementType const & >   __containsFunction,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: PredicateFunction < __FromIterableType const &, __ElementType const & >   __notContainsFunction   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > template <
                    template < typename ... > class                             __CollectionType    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > __CDS_OptimalInline auto __FindOfMutableCompositeClient <
                    __IterableType,
                    __ElementType,
                    __IteratorType,
                    __FromIterableType,
                    __containsFunction,
                    __notContainsFunction
            > :: findNotOf (
                    Size                                        count,
                    __CollectionType < Iterator >             & storeIn,
                    __FromIterableType                  const & from
            ) noexcept -> __CollectionType < Iterator > & {

                /* Call base, global implementation. Abstracts the 'is object const' requirement */
                return __findOf <
                        __ElementType,
                        Iterator,
                        __FromIterableType,
                        __CollectionType,
                        __notContainsFunction
                > (
                        reinterpret_cast < __IterableType * > ( this )->begin(),
                        reinterpret_cast < __IterableType * > ( this )->end(),
                        count,
                        storeIn,
                        from
                );
            }


            template <
                    typename                                                                                __IterableType,         /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                                __ElementType,          /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                                __IteratorType,         /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                                __FromIterableType,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: PredicateFunction < __FromIterableType const &, __ElementType const & >   __containsFunction,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: PredicateFunction < __FromIterableType const &, __ElementType const & >   __notContainsFunction   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > template <
                    template < typename ... > class                             __CollectionType    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > __CDS_OptimalInline auto __FindOfMutableCompositeClient <
                    __IterableType,
                    __ElementType,
                    __IteratorType,
                    __FromIterableType,
                    __containsFunction,
                    __notContainsFunction
            > :: findNotOf (
                    Size                        count,
                    __FromIterableType  const & from
            ) noexcept -> __CollectionType < Iterator > {

                /* Call base, global implementation. Abstracts the 'is object const' requirement */
                __CollectionType < Iterator > foundIterators;
                return __findOf <
                        __ElementType,
                        Iterator,
                        __FromIterableType,
                        __CollectionType,
                        __notContainsFunction
                > (
                        reinterpret_cast < __IterableType * > ( this )->begin(),
                        reinterpret_cast < __IterableType * > ( this )->end(),
                        count,
                        foundIterators,
                        from
                );
            }


            template <
                    typename                                                                                __IterableType,         /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                                __ElementType,          /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                                __IteratorType,         /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                                __FromIterableType,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: PredicateFunction < __FromIterableType const &, __ElementType const & >   __containsFunction,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: PredicateFunction < __FromIterableType const &, __ElementType const & >   __notContainsFunction   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > __CDS_OptimalInline auto __FindOfMutableCompositeClient <
                    __IterableType,
                    __ElementType,
                    __IteratorType,
                    __FromIterableType,
                    __containsFunction,
                    __notContainsFunction
            > :: findFirstNotOf (
                    __FromIterableType  const & from
            ) noexcept -> Iterator {

                /* Call base, global implementation. Abstracts the 'is object const' requirement */
                return __findFirstOf <
                        __ElementType,
                        Iterator,
                        __FromIterableType,
                        __notContainsFunction
                > (
                        reinterpret_cast < __IterableType * > ( this )->begin(),
                        reinterpret_cast < __IterableType * > ( this )->end(),
                        from
                );
            }


            template <
                    typename                                                                                __IterableType,         /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                                __ElementType,          /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                                __IteratorType,         /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                                __FromIterableType,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: PredicateFunction < __FromIterableType const &, __ElementType const & >   __containsFunction,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: PredicateFunction < __FromIterableType const &, __ElementType const & >   __notContainsFunction   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > __CDS_OptimalInline auto __FindOfMutableCompositeClient <
                    __IterableType,
                    __ElementType,
                    __IteratorType,
                    __FromIterableType,
                    __containsFunction,
                    __notContainsFunction
            > :: findLastNotOf (
                    __FromIterableType  const & from
            ) noexcept -> Iterator {

                /* Call base, global implementation. Abstracts the 'is object const' requirement */
                return __findLastOf <
                        __ElementType,
                        Iterator,
                        __FromIterableType,
                        __notContainsFunction
                > (
                        reinterpret_cast < __IterableType * > ( this )->begin(),
                        reinterpret_cast < __IterableType * > ( this )->end(),
                        from
                );
            }


            template <
                    typename                                                                                __IterableType,         /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                                __ElementType,          /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                                __IteratorType,         /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                                __FromIterableType,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: PredicateFunction < __FromIterableType const &, __ElementType const & >   __containsFunction,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: PredicateFunction < __FromIterableType const &, __ElementType const & >   __notContainsFunction   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > template <
                    template < typename ... > class                             __CollectionType    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > __CDS_OptimalInline auto __FindOfMutableCompositeClient <
                    __IterableType,
                    __ElementType,
                    __IteratorType,
                    __FromIterableType,
                    __containsFunction,
                    __notContainsFunction
            > :: findAllNotOf (
                    __CollectionType < Iterator >         & storeIn,
                    __FromIterableType              const & from
            ) noexcept -> __CollectionType < Iterator > & {

                /* Call base, global implementation. Abstracts the 'is object const' requirement */
                return __findAllOf <
                        __ElementType,
                        Iterator,
                        __FromIterableType,
                        __CollectionType,
                        __notContainsFunction
                > (
                        reinterpret_cast < __IterableType * > ( this )->begin(),
                        reinterpret_cast < __IterableType * > ( this )->end(),
                        storeIn,
                        from
                );
            }


            template <
                    typename                                                                                __IterableType,         /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                                __ElementType,          /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                                __IteratorType,         /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                                __FromIterableType,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: PredicateFunction < __FromIterableType const &, __ElementType const & >   __containsFunction,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: PredicateFunction < __FromIterableType const &, __ElementType const & >   __notContainsFunction   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > template <
                    template < typename ... > class                             __CollectionType    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > __CDS_OptimalInline auto __FindOfMutableCompositeClient <
                    __IterableType,
                    __ElementType,
                    __IteratorType,
                    __FromIterableType,
                    __containsFunction,
                    __notContainsFunction
            > :: findAllNotOf (
                    __FromIterableType  const & from
            ) noexcept -> __CollectionType < Iterator > {

                /* Call base, global implementation. Abstracts the 'is object const' requirement */
                __CollectionType < Iterator > foundIterators;
                return __findAllOf <
                        __ElementType,
                        Iterator,
                        __FromIterableType,
                        __CollectionType,
                        __notContainsFunction
                > (
                        reinterpret_cast < __IterableType * > ( this )->begin(),
                        reinterpret_cast < __IterableType * > ( this )->end(),
                        foundIterators,
                        from
                );
            }

        } /* namespace __impl */
    } /* namespace __hidden */
} /* namespace cds */

#endif /* __CDS_SHARED_FIND_OF_MUTABLE_COMPOSITE_CLIENT_IMPL_HPP__ */
