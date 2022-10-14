/*
 * Created by loghin on 6/13/22.
 */

#ifndef __CDS_SHARED_COLLECTION_FUNCTIONAL_CONSTRUCTORS_HPP__
#define __CDS_SHARED_COLLECTION_FUNCTIONAL_CONSTRUCTORS_HPP__ /* NOLINT(bugprone-reserved-identifier) */

namespace cds {             /* NOLINT(modernize-concat-nested-namespaces) */
    namespace __hidden {    /* NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier) */
        namespace __impl {  /* NOLINT(bugprone-reserved-identifier) */
            
            template <
                    typename __CollectionType,  /* NOLINT(bugprone-reserved-identifier) */
                    typename __LastArgumentType /* NOLINT(bugprone-reserved-identifier) */
            > inline auto __collectionOfPush (  /* NOLINT(bugprone-reserved-identifier) */
                    __CollectionType      & collection,
                    __LastArgumentType   && lastValue
            ) noexcept -> void;


            template <
                    typename __CollectionType,              /* NOLINT(bugprone-reserved-identifier) */
                    typename __FirstArgumentType,           /* NOLINT(bugprone-reserved-identifier) */
                    typename ... __RemainingArgumentTypes   /* NOLINT(bugprone-reserved-identifier) */
            > inline auto __collectionOfPush (              /* NOLINT(bugprone-reserved-identifier) */
                    __CollectionType          &       collection,
                    __FirstArgumentType      &&       firstValue,
                    __RemainingArgumentTypes && ...   remainingValues
            ) noexcept -> void;


            /**
             * @brief Function used to obtain a new collection non-abstract derived type object from the given values, with the most suitable ElementType for the given values
             * @tparam __CollectionType non-abstract Collection derived type ( i.e. Array, LinkedList, HashSet, ... )
             * @tparam __ArgumentTypes pack of types, representing the types of each of the given parameters, must be convertible to a common type
             * @tparam __Common alias for the best common type the types in the __ArgumentTypes pack are convertible to
             * @param values : ArgumentTypes fref = Pack of Forwarding References to the values to be added to the newly created collection
             * @exceptsafe
             * @return __CollectionType < Common > = newly created collection-derived non-abstract object instance, containing the given elements
             * @test tested in base class test
             */
            template <
                    template < typename ... > class __CollectionType,                   /* NOLINT(bugprone-reserved-identifier) */
                    typename ... __ArgumentTypes,                                       /* NOLINT(bugprone-reserved-identifier) */
                    typename __Common = cds :: meta :: Common < __ArgumentTypes ... >   /* NOLINT(bugprone-reserved-identifier) */
            > auto __instantiateCollectionOf (                                          /* NOLINT(bugprone-reserved-identifier) */
                    __ArgumentTypes && ... values
            ) noexcept -> __CollectionType < __Common >;
            
        }
    }

}

#endif /* __CDS_SHARED_COLLECTION_FUNCTIONAL_CONSTRUCTORS_HPP__ */

namespace cds {

#if defined (__CDS_LINKED_LIST_HPP__) && ! defined ( __CDS_SHARED_LINKED_LIST_FUNCTIONAL_CONSTRUCTOR__ )
#define __CDS_SHARED_LINKED_LIST_FUNCTIONAL_CONSTRUCTOR__ /* NOLINT(bugprone-reserved-identifier) */

#if ! defined (__CDS_SHARED_ARRAY_FUNCTIONAL_CONSTRUCTOR__)
#if defined (__CDS_LIST_FUNCTIONAL_CONSTRUCTOR_TYPE)
#undef __CDS_LIST_FUNCTIONAL_CONSTRUCTOR_TYPE
#endif
#define __CDS_LIST_FUNCTIONAL_CONSTRUCTOR_TYPE LinkedList /* NOLINT(bugprone-reserved-identifier) */
#endif

    template < typename ... __ArgumentTypes > /* NOLINT(bugprone-reserved-identifier) */
    inline auto linkedListOf (
            __ArgumentTypes && ... values
    ) noexcept -> LinkedList < cds :: meta :: Common < __ArgumentTypes ... > >;

#endif /* __CDS_SHARED_LINKED_LIST_FUNCTIONAL_CONSTRUCTOR__ */


#if defined (__CDS_ARRAY_HPP__) && ! defined ( __CDS_SHARED_ARRAY_FUNCTIONAL_CONSTRUCTOR__ )
#define __CDS_SHARED_ARRAY_FUNCTIONAL_CONSTRUCTOR__ /* NOLINT(bugprone-reserved-identifier) */

#if defined (__CDS_LIST_FUNCTIONAL_CONSTRUCTOR_TYPE)
#undef __CDS_LIST_FUNCTIONAL_CONSTRUCTOR_TYPE
#endif

#define __CDS_LIST_FUNCTIONAL_CONSTRUCTOR_TYPE Array /* NOLINT(bugprone-reserved-identifier) */

    template < typename ... __ArgumentTypes > /* NOLINT(bugprone-reserved-identifier) */
    inline auto arrayOf (
            __ArgumentTypes && ... values
    ) noexcept -> Array < cds :: meta :: Common < __ArgumentTypes ... > >;

#endif /* __CDS_SHARED_ARRAY_FUNCTIONAL_CONSTRUCTOR__ */



#if defined (__CDS_LINKED_HASH_SET_HPP__) && ! defined ( __CDS_SHARED_LINKED_HASH_SET_FUNCTIONAL_CONSTRUCTOR__ )
#define __CDS_SHARED_LINKED_HASH_SET_FUNCTIONAL_CONSTRUCTOR__ /* NOLINT(bugprone-reserved-identifier) */

#if ! defined (__CDS_SHARED_TREE_SET_FUNCTIONAL_CONSTRUCTOR__) && ! defined (__CDS_SHARED_HASH_SET_FUNCTIONAL_CONSTRUCTOR__)
#if defined (__CDS_SET_FUNCTIONAL_CONSTRUCTOR_TYPE)
#undef __CDS_SET_FUNCTIONAL_CONSTRUCTOR_TYPE
#endif
#define __CDS_SET_FUNCTIONAL_CONSTRUCTOR_TYPE LinkedHashSet /* NOLINT(bugprone-reserved-identifier) */
#endif

    template < typename ... __ArgumentTypes >   /* NOLINT(bugprone-reserved-identifier) */
    inline auto linkedHashSetOf (
            __ArgumentTypes && ... values
    ) noexcept -> LinkedHashSet < cds :: meta :: Common < __ArgumentTypes ... > >;

#endif /* __CDS_SHARED_LINKED_HASH_SET_FUNCTIONAL_CONSTRUCTOR__ */



#if defined (__CDS_TREE_SET_HPP__) && ! defined ( __CDS_SHARED_TREE_SET_FUNCTIONAL_CONSTRUCTOR__ ) && defined ( __CDS_TREE_SET_REMOVE_WHEN_IMPLEMENTED )
#define __CDS_SHARED_TREE_SET_FUNCTIONAL_CONSTRUCTOR__ /* NOLINT(bugprone-reserved-identifier) */

#if ! defined (__CDS_SHARED_HASH_SET_FUNCTIONAL_CONSTRUCTOR__)
#if defined (__CDS_SET_FUNCTIONAL_CONSTRUCTOR_TYPE)
#undef __CDS_SET_FUNCTIONAL_CONSTRUCTOR_TYPE
#endif
#define __CDS_SET_FUNCTIONAL_CONSTRUCTOR_TYPE TreeSet /* NOLINT(bugprone-reserved-identifier) */
#endif

    template < typename ... __ArgumentTypes >   /* NOLINT(bugprone-reserved-identifier) */
    inline auto treeSetOf (
            __ArgumentTypes && ... values
    ) noexcept -> TreeSet < cds :: meta :: Common < __ArgumentTypes ... > >;

#endif /* __CDS_SHARED_TREE_SET_FUNCTIONAL_CONSTRUCTOR__ */



#if defined (__CDS_HASH_SET_HPP__) && ! defined ( __CDS_SHARED_HASH_SET_FUNCTIONAL_CONSTRUCTOR__ )
#define __CDS_SHARED_HASH_SET_FUNCTIONAL_CONSTRUCTOR__ /* NOLINT(bugprone-reserved-identifier) */

#if defined (__CDS_SET_FUNCTIONAL_CONSTRUCTOR_TYPE)
#undef __CDS_SET_FUNCTIONAL_CONSTRUCTOR_TYPE
#endif

#define __CDS_SET_FUNCTIONAL_CONSTRUCTOR_TYPE HashSet /* NOLINT(bugprone-reserved-identifier) */

    template < typename ... __ArgumentTypes >   /* NOLINT(bugprone-reserved-identifier) */
    inline auto hashSetOf (
            __ArgumentTypes && ... values
    ) noexcept -> HashSet < cds :: meta :: Common < __ArgumentTypes ... > >;

#endif /* __CDS_SHARED_HASH_SET_FUNCTIONAL_CONSTRUCTOR__ */



#if defined (__CDS_LINKED_HASH_MAP_HPP__) && ! defined ( __CDS_SHARED_LINKED_HASH_MAP_FUNCTIONAL_CONSTRUCTOR__ )
#define __CDS_SHARED_LINKED_HASH_MAP_FUNCTIONAL_CONSTRUCTOR__ /* NOLINT(bugprone-reserved-identifier) */

#if ! defined (__CDS_SHARED_TREE_MAP_FUNCTIONAL_CONSTRUCTOR__) && ! defined (__CDS_SHARED_HASH_MAP_FUNCTIONAL_CONSTRUCTOR__)
#if defined (__CDS_MAP_FUNCTIONAL_CONSTRUCTOR_TYPE)
#undef __CDS_MAP_FUNCTIONAL_CONSTRUCTOR_TYPE
#endif
#define __CDS_MAP_FUNCTIONAL_CONSTRUCTOR_TYPE LinkedHashMap /* NOLINT(bugprone-reserved-identifier) */
#endif

    template <
            typename ... __ArgumentTypes,
            typename __CommonType = cds :: meta :: Common < __ArgumentTypes ... >,
            cds :: meta :: EnableIf <
                    cds :: meta :: MapEntryTraits < __CommonType > :: valid
            > = 0
    > inline auto linkedHashMapOf (
            __ArgumentTypes && ... pairs
    ) noexcept -> LinkedHashMap < typename cds :: meta :: MapEntryTraits < __CommonType > :: KeyType, typename cds :: meta :: MapEntryTraits < __CommonType > :: ValueType >;

#endif /* __CDS_SHARED_LINKED_HASH_MAP_FUNCTIONAL_CONSTRUCTOR__ */



#if defined (__CDS_TREE_MAP_HPP__) && ! defined ( __CDS_SHARED_TREE_MAP_FUNCTIONAL_CONSTRUCTOR__ ) && defined ( __CDS_TREE_MAP_REMOVE_WHEN_IMPLEMENTED )
#define __CDS_SHARED_TREE_MAP_FUNCTIONAL_CONSTRUCTOR__ /* NOLINT(bugprone-reserved-identifier) */

#if ! defined (__CDS_SHARED_HASH_MAP_FUNCTIONAL_CONSTRUCTOR__)
#if defined (__CDS_MAP_FUNCTIONAL_CONSTRUCTOR_TYPE)
#undef __CDS_MAP_FUNCTIONAL_CONSTRUCTOR_TYPE
#endif
#define __CDS_MAP_FUNCTIONAL_CONSTRUCTOR_TYPE TreeMap /* NOLINT(bugprone-reserved-identifier) */
#endif

    template <
            typename ... __ArgumentTypes,
            typename __CommonType = cds :: meta :: Common < __ArgumentTypes ... >,
            cds :: meta :: EnableIf <
                    cds :: meta :: MapEntryTraits < __CommonType > :: valid
            > = 0
    > inline auto treeMapOf (
            __ArgumentTypes && ... pairs
    ) noexcept -> TreeMap < typename cds :: meta :: MapEntryTraits < __CommonType > :: KeyType, typename cds :: meta :: MapEntryTraits < __CommonType > :: ValueType >;

#endif /* __CDS_SHARED_TREE_MAP_FUNCTIONAL_CONSTRUCTOR__ */



#if defined (__CDS_HASH_MAP_HPP__) && ! defined ( __CDS_SHARED_HASH_MAP_FUNCTIONAL_CONSTRUCTOR__ )
#define __CDS_SHARED_HASH_MAP_FUNCTIONAL_CONSTRUCTOR__ /* NOLINT(bugprone-reserved-identifier) */

#if defined (__CDS_MAP_FUNCTIONAL_CONSTRUCTOR_TYPE)
#undef __CDS_MAP_FUNCTIONAL_CONSTRUCTOR_TYPE
#endif

#define __CDS_MAP_FUNCTIONAL_CONSTRUCTOR_TYPE HashMap /* NOLINT(bugprone-reserved-identifier) */

    template <
            typename ... __ArgumentTypes,
            typename __CommonType = cds :: meta :: Common < __ArgumentTypes ... >,
            cds :: meta :: EnableIf <
                    cds :: meta :: MapEntryTraits < __CommonType > :: valid
            > = 0
    > inline auto hashMapOf (
            __ArgumentTypes && ... pairs
    ) noexcept -> HashMap < typename cds :: meta :: MapEntryTraits < __CommonType > :: KeyType, typename cds :: meta :: MapEntryTraits < __CommonType > :: ValueType >;

#endif /* __CDS_SHARED_HASH_MAP_FUNCTIONAL_CONSTRUCTOR__ */



#if defined (__CDS_LIST_FUNCTIONAL_CONSTRUCTOR_TYPE) && ! defined ( __CDS_SHARED_LIST_FUNCTIONAL_CONSTRUCTOR__ )
#define __CDS_SHARED_LIST_FUNCTIONAL_CONSTRUCTOR__ /* NOLINT(bugprone-reserved-identifier) */

    template < typename ... __ArgumentTypes > /* NOLINT(bugprone-reserved-identifier) */
    inline auto listOf (
            __ArgumentTypes && ... values
    ) noexcept -> __CDS_LIST_FUNCTIONAL_CONSTRUCTOR_TYPE < cds :: meta :: Common < __ArgumentTypes ... > >;

#endif /* __CDS_SHARED_LIST_FUNCTIONAL_CONSTRUCTOR__ */



#if defined (__CDS_SET_FUNCTIONAL_CONSTRUCTOR_TYPE) && ! defined ( __CDS_SHARED_SET_FUNCTIONAL_CONSTRUCTOR__ )
#define __CDS_SHARED_SET_FUNCTIONAL_CONSTRUCTOR__ /* NOLINT(bugprone-reserved-identifier) */

    template < typename ... __ArgumentTypes > /* NOLINT(bugprone-reserved-identifier) */
    inline auto setOf (
            __ArgumentTypes && ... values
    ) noexcept -> __CDS_SET_FUNCTIONAL_CONSTRUCTOR_TYPE < cds :: meta :: Common < __ArgumentTypes ... > >;

#endif /* __CDS_SHARED_SET_FUNCTIONAL_CONSTRUCTOR__ */



#if defined (__CDS_MAP_FUNCTIONAL_CONSTRUCTOR_TYPE) && ! defined ( __CDS_SHARED_MAP_FUNCTIONAL_CONSTRUCTOR__ )
#define __CDS_SHARED_MAP_FUNCTIONAL_CONSTRUCTOR__ /* NOLINT(bugprone-reserved-identifier) */

    template <
            typename ... __ArgumentTypes,
            typename __CommonType = cds :: meta :: Common < __ArgumentTypes ... >,
            cds :: meta :: EnableIf <
                    cds :: meta :: MapEntryTraits < __CommonType > :: valid
            > = 0
    > inline auto mapOf (
            __ArgumentTypes && ... pairs
    ) noexcept -> __CDS_MAP_FUNCTIONAL_CONSTRUCTOR_TYPE < typename cds :: meta :: MapEntryTraits < __CommonType > :: KeyType, typename cds :: meta :: MapEntryTraits < __CommonType > :: ValueType >;

#endif /* __CDS_SHARED_SET_FUNCTIONAL_CONSTRUCTOR__ */

}
