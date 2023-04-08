/*
 * Created by stefan on 10.10.2022.
 */

#ifndef __CDS_TREE_MAP_CONSTRUCTS_HPP__
#define __CDS_TREE_MAP_CONSTRUCTS_HPP__     /* NOLINT(bugprone-reserved-identifier) */

namespace cds { /* NOLINT(modernize-concat-nested-namespaces) */

    template <
            typename __KeyType,     /* NOLINT(bugprone-reserved-identifier) */
            typename __ValueType,   /* NOLINT(bugprone-reserved-identifier) */
            typename __Comparator   = functional :: DecoratedPredicate <          /* NOLINT(bugprone-reserved-identifier) */
                    cds :: functional :: PredicateFunction < __KeyType const &, __KeyType const & >,
                    & cds :: predicates :: lessThan < __KeyType >
            >
    > class TreeMap;

    namespace __hidden {    /* NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier) */
        namespace __impl {  /* NOLINT(bugprone-reserved-identifier) */

            template <
                    typename __KeyType,         /* NOLINT(bugprone-reserved-identifier) */
                    typename __ValueType        /* NOLINT(bugprone-reserved-identifier) */
            > constexpr auto __treeMapKeyExtractor (    /* NOLINT(bugprone-reserved-identifier) */
                    typename Map < __KeyType, __ValueType > :: EntryType const & value
            ) noexcept -> __KeyType const & {

                return value.key();
            }


            template <
                    typename __KeyType,         /* NOLINT(bugprone-reserved-identifier) */
                    typename __ValueType        /* NOLINT(bugprone-reserved-identifier) */
            > auto __treeMapCopyConstructor (       /* NOLINT(bugprone-reserved-identifier) */
                    typename Map < __KeyType, __ValueType > :: EntryType & destination,
                    typename Map < __KeyType, __ValueType > :: EntryType const & source
            ) noexcept -> void {

                using EntryType = typename Map < __KeyType, __ValueType > :: EntryType;
                new ( & destination ) EntryType( source );
            }


            template <
                    typename __KeyType,     /* NOLINT(bugprone-reserved-identifier) */
                    typename __ValueType    /* NOLINT(bugprone-reserved-identifier) */
            > auto __treeMapDestructor (    /* NOLINT(bugprone-reserved-identifier) */
                    typename Map < __KeyType, __ValueType > :: EntryType & element
            ) noexcept -> void {

                using EntryType = typename Map < __KeyType, __ValueType > :: EntryType;
                element.~EntryType();
            }


            template <
                    typename __KeyType,         /* NOLINT(bugprone-reserved-identifier) */
                    typename __ValueType,       /* NOLINT(bugprone-reserved-identifier) */
                    typename __Comparator       /* NOLINT(bugprone-reserved-identifier) */
            > using __TreeMapImplementation =   /* NOLINT(bugprone-reserved-identifier) */
                    __RedBlackTree <
                            typename Map < __KeyType, __ValueType > :: EntryType,
                            __KeyType,
                            __Comparator,
                            & __treeMapKeyExtractor < __KeyType, __ValueType >,
                            & cds :: meta :: equals < __KeyType >,
                            & __treeMapDestructor < __KeyType, __ValueType >
                    >;

            template <
                    typename __KeyType,         /* NOLINT(bugprone-reserved-identifier) */
                    typename __ValueType,       /* NOLINT(bugprone-reserved-identifier) */
                    typename __Comparator       /* NOLINT(bugprone-reserved-identifier) */
            > using __TreeMapDispatcher =           /* NOLINT(bugprone-reserved-identifier) */
                    typename __TreeMapImplementation <
                            __KeyType,
                            __ValueType,
                            __Comparator
                    > :: template __MapDispatcher <
                            cds :: TreeMap <
                                    __KeyType,
                                    __ValueType,
                                    __Comparator
                            >
                    >;


            template <
                    typename __KeyType,         /* NOLINT(bugprone-reserved-identifier) */
                    typename __ValueType,       /* NOLINT(bugprone-reserved-identifier) */
                    typename __Comparator       /* NOLINT(bugprone-reserved-identifier) */
            > using __TreeMapServer =           /* NOLINT(bugprone-reserved-identifier) */
                    __MapServer <
                            TreeMap <
                                    __KeyType,
                                    __ValueType,
                                    __Comparator
                            >,
                            typename Map < __KeyType, __ValueType > :: EntryType
                    >;


            template <
                    typename __KeyType,         /* NOLINT(bugprone-reserved-identifier) */
                    typename __ValueType,       /* NOLINT(bugprone-reserved-identifier) */
                    typename __Comparator       /* NOLINT(bugprone-reserved-identifier) */
            > using __TreeMapDelegateForwardIterableClient =        /* NOLINT(bugprone-reserved-identifier) */
                    __LocalDelegateForwardIterablePrimitiveClient <
                            cds :: TreeMap <
                                    __KeyType,
                                    __ValueType,
                                    __Comparator
                            >,
                            RedBlackTreeForwardIterator < typename Map < __KeyType, __ValueType > :: EntryType >
                    >;


            template <
                    typename __KeyType,         /* NOLINT(bugprone-reserved-identifier) */
                    typename __ValueType,       /* NOLINT(bugprone-reserved-identifier) */
                    typename __Comparator       /* NOLINT(bugprone-reserved-identifier) */
            > using __TreeMapDelegateBackwardIterableClient =       /* NOLINT(bugprone-reserved-identifier) */
                    cds :: __hidden :: __impl :: __LocalDelegateBackwardIterablePrimitiveClient <
                            cds :: TreeMap <
                                    __KeyType,
                                    __ValueType,
                                    __Comparator
                            >,
                            RedBlackTreeBackwardIterator < typename Map < __KeyType, __ValueType > :: EntryType >
                    >;


            template <
                    typename __KeyType,         /* NOLINT(bugprone-reserved-identifier) */
                    typename __ValueType,       /* NOLINT(bugprone-reserved-identifier) */
                    typename __Comparator       /* NOLINT(bugprone-reserved-identifier) */
            > using __TreeMapDelegateForwardConstIterableClient =      /* NOLINT(bugprone-reserved-identifier) */
                    __LocalDelegateForwardConstIterablePrimitiveClient <
                            cds :: TreeMap <
                                    __KeyType,
                                    __ValueType,
                                    __Comparator
                            >,
                            RedBlackTreeForwardConstIterator < typename Map < __KeyType, __ValueType > :: EntryType >
                    >;


            template <
                    typename __KeyType,         /* NOLINT(bugprone-reserved-identifier) */
                    typename __ValueType,       /* NOLINT(bugprone-reserved-identifier) */
                    typename __Comparator       /* NOLINT(bugprone-reserved-identifier) */
            > using __TreeMapDelegateBackwardConstIterableClient =      /* NOLINT(bugprone-reserved-identifier) */
                    cds :: __hidden :: __impl :: __LocalDelegateBackwardConstIterablePrimitiveClient <
                            cds :: TreeMap <
                                    __KeyType,
                                    __ValueType,
                                    __Comparator
                            >,
                            RedBlackTreeBackwardConstIterator < typename Map < __KeyType, __ValueType > :: EntryType >
                    >;

            template <
                    typename __KeyType,         /* NOLINT(bugprone-reserved-identifier) */
                    typename __ValueType,       /* NOLINT(bugprone-reserved-identifier) */
                    typename __Comparator       /* NOLINT(bugprone-reserved-identifier) */
            > using __TreeMapIteratorRemoveClient =     /* NOLINT(bugprone-reserved-identifier) */
                    __LocalIteratorRemovePrimitiveClient <
                            cds :: TreeMap <
                                    __KeyType,
                                    __ValueType,
                                    __Comparator
                            >,
                            typename Map < __KeyType, __ValueType > :: EntryType,
                            AbstractRedBlackTreeIterator < typename Map < __KeyType, __ValueType > :: EntryType >
                    >;

            template <
                    typename __KeyType,         /* NOLINT(bugprone-reserved-identifier) */
                    typename __ValueType,       /* NOLINT(bugprone-reserved-identifier) */
                    typename __Comparator       /* NOLINT(bugprone-reserved-identifier) */
            > using __TreeMapConstIteratorRemoveClient =      /* NOLINT(bugprone-reserved-identifier) */
                    __LocalConstIteratorRemovePrimitiveClient <
                            cds :: TreeMap <
                                    __KeyType,
                                    __ValueType,
                                    __Comparator
                            >,
                            typename Map < __KeyType, __ValueType > :: EntryType,
                            AbstractRedBlackTreeConstIterator < typename Map < __KeyType, __ValueType > :: EntryType >
                    >;

            template <
                    typename __KeyType,         /* NOLINT(bugprone-reserved-identifier) */
                    typename __ValueType,       /* NOLINT(bugprone-reserved-identifier) */
                    typename __Comparator       /* NOLINT(bugprone-reserved-identifier) */
            > using __TreeMapFindUniqueClient =     /* NOLINT(bugprone-reserved-identifier) */
                    __LocalFindUniqueMutablePrimitiveClient <
                            cds :: TreeMap <
                                    __KeyType,
                                    __ValueType,
                                    __Comparator
                            >,
                            __KeyType,
                            AbstractRedBlackTreeIterator < typename Map < __KeyType, __ValueType > :: EntryType >
                    >;


            template <
                    typename __KeyType,         /* NOLINT(bugprone-reserved-identifier) */
                    typename __ValueType,       /* NOLINT(bugprone-reserved-identifier) */
                    typename __Comparator       /* NOLINT(bugprone-reserved-identifier) */
            > using __TreeMapFindUniqueConstClient =        /* NOLINT(bugprone-reserved-identifier) */
                    __LocalFindUniqueImmutablePrimitiveClient <
                            cds :: TreeMap <
                                    __KeyType,
                                    __ValueType,
                                    __Comparator
                            >,
                            __KeyType,
                            AbstractRedBlackTreeConstIterator < typename Map < __KeyType, __ValueType > :: EntryType >
                    >;


            template <
                    typename __KeyType,         /* NOLINT(bugprone-reserved-identifier) */
                    typename __ValueType,       /* NOLINT(bugprone-reserved-identifier) */
                    typename __Comparator       /* NOLINT(bugprone-reserved-identifier) */
            > using __TreeMapRandomInsertionClient =        /* NOLINT(bugprone-reserved-identifier) */
                    __LocalRandomInsertionPrimitiveClient <
                            cds :: TreeMap <
                                    __KeyType,
                                    __ValueType,
                                    __Comparator
                            >,
                            typename Map < __KeyType, __ValueType > :: EntryType,
                            typename Map < __KeyType, __ValueType > :: EntryType const
                    >;


            template <
                    typename __KeyType,         /* NOLINT(bugprone-reserved-identifier) */
                    typename __ValueType,       /* NOLINT(bugprone-reserved-identifier) */
                    typename __Comparator       /* NOLINT(bugprone-reserved-identifier) */
            > using __TreeMapContainsOfCollectionClient =       /* NOLINT(bugprone-reserved-identifier) */
                    __LocalContainsOfCompositeClient <
                            cds :: TreeMap <
                                    __KeyType,
                                    __ValueType,
                                    __Comparator
                            >,
                            typename Map < __KeyType, __ValueType > :: EntryType,
                            cds :: Iterable < typename Map < __KeyType, __ValueType > :: EntryType >,
                            & cds :: __hidden :: __impl :: __iterableContains < typename Map < __KeyType, __ValueType > :: EntryType >
                    >;


            template <
                    typename __KeyType,         /* NOLINT(bugprone-reserved-identifier) */
                    typename __ValueType,       /* NOLINT(bugprone-reserved-identifier) */
                    typename __Comparator       /* NOLINT(bugprone-reserved-identifier) */
            > using __TreeMapContainsOfInitializerListClient =      /* NOLINT(bugprone-reserved-identifier) */
                    __LocalContainsOfCompositeClient <
                            cds :: TreeMap <
                                    __KeyType,
                                    __ValueType,
                                    __Comparator
                            >,
                            typename Map < __KeyType, __ValueType > :: EntryType,
                            std :: initializer_list < typename Map < __KeyType, __ValueType > :: EntryType >,
                            & cds :: __hidden :: __impl :: __initializerListContains <
                                    typename Map < __KeyType, __ValueType > :: EntryType,
                                    & cds :: meta :: equals < typename Map < __KeyType, __ValueType > :: EntryType >
                            >
                    >;


            template <
                    typename __KeyType,         /* NOLINT(bugprone-reserved-identifier) */
                    typename __ValueType,       /* NOLINT(bugprone-reserved-identifier) */
                    typename __Comparator       /* NOLINT(bugprone-reserved-identifier) */
            > using __TreeMapFindByClient =     /* NOLINT(bugprone-reserved-identifier) */
                    __LocalFindByMutableCompositeClient <
                            cds :: TreeMap <
                                    __KeyType,
                                    __ValueType,
                                    __Comparator
                            >,
                            typename Map < __KeyType, __ValueType > :: EntryType,
                            AbstractRedBlackTreeIterator < typename Map < __KeyType, __ValueType > :: EntryType >
                    >;


            template <
                    typename __KeyType,         /* NOLINT(bugprone-reserved-identifier) */
                    typename __ValueType,       /* NOLINT(bugprone-reserved-identifier) */
                    typename __Comparator       /* NOLINT(bugprone-reserved-identifier) */
            > using __TreeMapFindByConstClient =     /* NOLINT(bugprone-reserved-identifier) */
                    __LocalFindByImmutableCompositeClient <
                            cds :: TreeMap <
                                    __KeyType,
                                    __ValueType,
                                    __Comparator
                            >,
                            typename Map < __KeyType, __ValueType > :: EntryType,
                            AbstractRedBlackTreeConstIterator < typename Map < __KeyType, __ValueType > :: EntryType >
                    >;


            template <
                    typename __KeyType,         /* NOLINT(bugprone-reserved-identifier) */
                    typename __ValueType,       /* NOLINT(bugprone-reserved-identifier) */
                    typename __Comparator       /* NOLINT(bugprone-reserved-identifier) */
            > using __TreeMapFindOfCollectionClient =     /* NOLINT(bugprone-reserved-identifier) */
                    __LocalFindOfMutableCompositeClient <
                            cds :: TreeMap <
                                    __KeyType,
                                    __ValueType,
                                    __Comparator
                            >,
                            typename Map < __KeyType, __ValueType > :: EntryType,
                            AbstractRedBlackTreeIterator < typename Map < __KeyType, __ValueType > :: EntryType >,
                            cds :: Iterable < typename Map < __KeyType, __ValueType > :: EntryType >,
                            & cds :: __hidden :: __impl :: __iterableContains < typename Map < __KeyType, __ValueType > :: EntryType >,
                            & cds :: __hidden :: __impl :: __iterableNotContains < typename Map < __KeyType, __ValueType > :: EntryType >
                    >;


            template <
                    typename __KeyType,         /* NOLINT(bugprone-reserved-identifier) */
                    typename __ValueType,       /* NOLINT(bugprone-reserved-identifier) */
                    typename __Comparator       /* NOLINT(bugprone-reserved-identifier) */
            > using __TreeMapFindOfInitializerListClient =     /* NOLINT(bugprone-reserved-identifier) */
                    __LocalFindOfMutableCompositeClient <
                            cds :: TreeMap <
                                    __KeyType,
                                    __ValueType,
                                    __Comparator
                            >,
                            typename Map < __KeyType, __ValueType > :: EntryType,
                            AbstractRedBlackTreeIterator < typename Map < __KeyType, __ValueType > :: EntryType >,
                            std :: initializer_list < typename Map < __KeyType, __ValueType > :: EntryType >,
                            & cds :: __hidden :: __impl :: __initializerListContains <
                                    typename Map < __KeyType, __ValueType > :: EntryType,
                                    & cds :: meta :: equals < typename Map < __KeyType, __ValueType > :: EntryType >
                            >,
                            & cds :: __hidden :: __impl :: __initializerListNotContains <
                                    typename Map < __KeyType, __ValueType > :: EntryType,
                                    & cds :: meta :: equals < typename Map < __KeyType, __ValueType > :: EntryType >
                            >
                    >;


            template <
                    typename __KeyType,         /* NOLINT(bugprone-reserved-identifier) */
                    typename __ValueType,       /* NOLINT(bugprone-reserved-identifier) */
                    typename __Comparator       /* NOLINT(bugprone-reserved-identifier) */
            > using __TreeMapFindOfConstCollectionClient =     /* NOLINT(bugprone-reserved-identifier) */
                    __LocalFindOfImmutableCompositeClient <
                            cds :: TreeMap <
                                    __KeyType,
                                    __ValueType,
                                    __Comparator
                            >,
                            typename Map < __KeyType, __ValueType > :: EntryType,
                            AbstractRedBlackTreeConstIterator < typename Map < __KeyType, __ValueType > :: EntryType >,
                            cds :: Iterable < typename Map < __KeyType, __ValueType > :: EntryType >,
                            & cds :: __hidden :: __impl :: __iterableContains < typename Map < __KeyType, __ValueType > :: EntryType >,
                            & cds :: __hidden :: __impl :: __iterableNotContains < typename Map < __KeyType, __ValueType > :: EntryType >
                    >;


            template <
                    typename __KeyType,         /* NOLINT(bugprone-reserved-identifier) */
                    typename __ValueType,       /* NOLINT(bugprone-reserved-identifier) */
                    typename __Comparator       /* NOLINT(bugprone-reserved-identifier) */
            > using __TreeMapFindOfConstInitializerListClient =     /* NOLINT(bugprone-reserved-identifier) */
                    __LocalFindOfMutableCompositeClient <
                            cds :: TreeMap <
                                    __KeyType,
                                    __ValueType,
                                    __Comparator
                            >,
                            typename Map < __KeyType, __ValueType > :: EntryType,
                            AbstractRedBlackTreeConstIterator < typename Map < __KeyType, __ValueType > :: EntryType >,
                            std :: initializer_list < typename Map < __KeyType, __ValueType > :: EntryType >,
                            & cds :: __hidden :: __impl :: __initializerListContains <
                                    typename Map < __KeyType, __ValueType > :: EntryType,
                                    & cds :: meta :: equals < typename Map < __KeyType, __ValueType > :: EntryType >
                            >,
                            & cds :: __hidden :: __impl :: __initializerListNotContains <
                                    typename Map < __KeyType, __ValueType > :: EntryType,
                                    & cds :: meta :: equals < typename Map < __KeyType, __ValueType > :: EntryType >
                            >
                    >;


            template <
                    typename __KeyType,         /* NOLINT(bugprone-reserved-identifier) */
                    typename __ValueType,       /* NOLINT(bugprone-reserved-identifier) */
                    typename __Comparator       /* NOLINT(bugprone-reserved-identifier) */
            > using __TreeMapGenericStatementsClient =     /* NOLINT(bugprone-reserved-identifier) */
                    __LocalGenericMutableStatementsCompositeClient <
                            cds :: TreeMap <
                                    __KeyType,
                                    __ValueType,
                                    __Comparator
                            >,
                            typename Map < __KeyType, __ValueType > :: EntryType
                    >;


            template <
                    typename __KeyType,         /* NOLINT(bugprone-reserved-identifier) */
                    typename __ValueType,       /* NOLINT(bugprone-reserved-identifier) */
                    typename __Comparator       /* NOLINT(bugprone-reserved-identifier) */
            > using __TreeMapConstGenericStatementsClient =     /* NOLINT(bugprone-reserved-identifier) */
                    __LocalGenericImmutableStatementsCompositeClient <
                            cds :: TreeMap <
                                    __KeyType,
                                    __ValueType,
                                    __Comparator
                            >,
                            typename Map < __KeyType, __ValueType > :: EntryType
                    >;


            template <
                    typename __KeyType,         /* NOLINT(bugprone-reserved-identifier) */
                    typename __ValueType,       /* NOLINT(bugprone-reserved-identifier) */
                    typename __Comparator       /* NOLINT(bugprone-reserved-identifier) */
            > using __TreeMapRemoveByClient =     /* NOLINT(bugprone-reserved-identifier) */
                    __LocalRemoveByCompositeClient <
                            cds :: TreeMap <
                                    __KeyType,
                                    __ValueType,
                                    __Comparator
                            >,
                            typename Map < __KeyType, __ValueType > :: EntryType
                    >;


            template <
                    typename __KeyType,         /* NOLINT(bugprone-reserved-identifier) */
                    typename __ValueType,       /* NOLINT(bugprone-reserved-identifier) */
                    typename __Comparator       /* NOLINT(bugprone-reserved-identifier) */
            > using __TreeMapRemoveOfCollectionClient =     /* NOLINT(bugprone-reserved-identifier) */
                    __LocalRemoveOfCompositeClient <
                            cds :: TreeMap <
                                    __KeyType,
                                    __ValueType,
                                    __Comparator
                            >,
                            typename Map < __KeyType, __ValueType > :: EntryType,
                            cds :: Iterable < typename Map < __KeyType, __ValueType > :: EntryType >,
                            & cds :: __hidden :: __impl :: __iterableContains < typename Map < __KeyType, __ValueType > :: EntryType >
                    >;


            template <
                    typename __KeyType,         /* NOLINT(bugprone-reserved-identifier) */
                    typename __ValueType,       /* NOLINT(bugprone-reserved-identifier) */
                    typename __Comparator       /* NOLINT(bugprone-reserved-identifier) */
            > using __TreeMapRemoveOfInitializerListClient =     /* NOLINT(bugprone-reserved-identifier) */
                    __LocalRemoveOfCompositeClient <
                            cds :: TreeMap <
                                    __KeyType,
                                    __ValueType,
                                    __Comparator
                            >,
                            typename Map < __KeyType, __ValueType > :: EntryType,
                            std :: initializer_list < typename Map < __KeyType, __ValueType > :: EntryType >,
                            & cds :: __hidden :: __impl :: __initializerListContains <
                                    typename Map < __KeyType, __ValueType > :: EntryType,
                                    & cds :: meta :: equals < typename Map < __KeyType, __ValueType > :: EntryType >
                            >
                    >;
        }
    }
}

#endif /* __CDS_TREE_MAP_CONSTRUCTS_HPP__ */
