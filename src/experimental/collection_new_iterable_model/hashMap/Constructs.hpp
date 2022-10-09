/*
 * Created by loghin on 13/08/22.
 */

#ifndef __CDS_HASH_MAP_CONSTRUCTS_HPP__
#define __CDS_HASH_MAP_CONSTRUCTS_HPP__ /* NOLINT(bugprone-reserved-identifier) */

namespace cds {                 /* NOLINT(modernize-concat-nested-namespaces) */
    namespace experimental {    /* NOLINT(modernize-concat-nested-namespaces) */

        template <
                typename __KeyType,                                                         /* NOLINT(bugprone-reserved-identifier) */
                typename __ValueType,                                                       /* NOLINT(bugprone-reserved-identifier) */
                typename __Hasher = cds :: WrapperHasher < __KeyType, Hash < __KeyType > >  /* NOLINT(bugprone-reserved-identifier) */
        > class HashMap;

        namespace __hidden {    /* NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier) */
            namespace __impl {  /* NOLINT(bugprone-reserved-identifier) */

                template <
                        typename __KeyType,                 /* NOLINT(bugprone-reserved-identifier) */
                        typename __ValueType                /* NOLINT(bugprone-reserved-identifier) */
                > constexpr auto __hashMapKeyExtractor (    /* NOLINT(bugprone-reserved-identifier) */
                        typename Map < __KeyType, __ValueType > :: EntryType const & element
                ) noexcept -> __KeyType const & {

                    return element.key ();
                }


                template <
                        typename __KeyType,                                                 /* NOLINT(bugprone-reserved-identifier) */
                        typename __ValueType                                                /* NOLINT(bugprone-reserved-identifier) */
                > __CDS_cpplang_ConstexprNonLiteralReturn auto __hashMapCopyConstructor (   /* NOLINT(bugprone-reserved-identifier) */
                        typename Map < __KeyType, __ValueType > :: EntryType       & destinationDataNode,
                        typename Map < __KeyType, __ValueType > :: EntryType const & sourceDataNode
                ) noexcept -> void {

                    new ( & destinationDataNode ) typename Map < __KeyType, __ValueType > :: EntryType ( sourceDataNode );
                }


                template <
                        typename __KeyType,                                             /* NOLINT(bugprone-reserved-identifier) */
                        typename __ValueType                                            /* NOLINT(bugprone-reserved-identifier) */
                > __CDS_cpplang_ConstexprNonLiteralReturn auto __hashMapDestructor (    /* NOLINT(bugprone-reserved-identifier) */
                        typename Map < __KeyType, __ValueType > :: EntryType & entry
                ) noexcept -> void {

                    using EntryType = typename Map < __KeyType, __ValueType > :: EntryType;
                    entry.~EntryType();
                }


                template <
                        typename __KeyType,             /* NOLINT(bugprone-reserved-identifier) */
                        typename __ValueType            /* NOLINT(bugprone-reserved-identifier) */
                > constexpr auto __hashMapEquals (      /* NOLINT(bugprone-reserved-identifier) */
                        typename Map < __KeyType, __ValueType > :: EntryType const & leftEntry,
                        typename Map < __KeyType, __ValueType > :: EntryType const & rightEntry
                ) noexcept -> bool {

                    return
                            cds :: meta :: equals ( leftEntry.key(), rightEntry.key() ) &&
                            cds :: meta :: equals ( leftEntry.value(), rightEntry.value() );
                }


                template <
                        typename __KeyType,         /* NOLINT(bugprone-reserved-identifier) */
                        typename __ValueType,       /* NOLINT(bugprone-reserved-identifier) */
                        typename __Hasher           /* NOLINT(bugprone-reserved-identifier) */
                > using __HashMapImplementation =   /* NOLINT(bugprone-reserved-identifier) */
                        __HashTable <
                                typename Map < __KeyType, __ValueType > :: EntryType,
                                __KeyType,
                                __Hasher,
                                cds :: __hidden :: __impl :: __PrimeRehashPolicy < uint32 >,
                                & __hashMapKeyExtractor < __KeyType, __ValueType >,
                                & cds :: meta :: equals < __KeyType >,
                                & __hashMapDestructor < __KeyType, __ValueType >
                        >;


                template <
                        typename __KeyType,         /* NOLINT(bugprone-reserved-identifier) */
                        typename __ValueType,       /* NOLINT(bugprone-reserved-identifier) */
                        typename __Hasher           /* NOLINT(bugprone-reserved-identifier) */
                > using __HashMapDispatcher =       /* NOLINT(bugprone-reserved-identifier) */
                        typename __HashMapImplementation <
                                __KeyType,
                                __ValueType,
                                __Hasher
                        > :: template __MapDispatcher <
                                HashMap <
                                        __KeyType,
                                        __ValueType,
                                        __Hasher
                                >
                        >;


                template <
                        typename __KeyType,         /* NOLINT(bugprone-reserved-identifier) */
                        typename __ValueType,       /* NOLINT(bugprone-reserved-identifier) */
                        typename __Hasher           /* NOLINT(bugprone-reserved-identifier) */
                > using __HashMapServer =           /* NOLINT(bugprone-reserved-identifier) */
                        __MapServer <
                                cds :: experimental :: HashMap <
                                        __KeyType,
                                        __ValueType,
                                        __Hasher
                                >,
                                typename Map < __KeyType, __ValueType > :: EntryType
                        >;


                template <
                        typename __KeyType,                 /* NOLINT(bugprone-reserved-identifier) */
                        typename __ValueType,               /* NOLINT(bugprone-reserved-identifier) */
                        typename __Hasher                   /* NOLINT(bugprone-reserved-identifier) */
                > using __HashMapRandomInsertionClient =    /* NOLINT(bugprone-reserved-identifier) */
                        __LocalRandomInsertionPrimitiveClient <
                                cds :: experimental :: HashMap <
                                        __KeyType,
                                        __ValueType,
                                        __Hasher
                                >,
                                typename Map < __KeyType, __ValueType > :: EntryType,
                                typename Map < __KeyType, __ValueType > :: EntryType
                        >;


                template <
                        typename __KeyType,             /* NOLINT(bugprone-reserved-identifier) */
                        typename __ValueType,           /* NOLINT(bugprone-reserved-identifier) */
                        typename __Hasher               /* NOLINT(bugprone-reserved-identifier) */
                > using __HashMapIteratorRemoveClient = /* NOLINT(bugprone-reserved-identifier) */
                        __LocalIteratorRemovePrimitiveClient <
                                cds :: experimental :: HashMap <
                                        __KeyType,
                                        __ValueType,
                                        __Hasher
                                >,
                                typename Map < __KeyType, __ValueType > :: EntryType,
                                HashTableIterator < typename Map < __KeyType, __ValueType > :: EntryType >
                        >;


                template <
                        typename __KeyType,                     /* NOLINT(bugprone-reserved-identifier) */
                        typename __ValueType,                   /* NOLINT(bugprone-reserved-identifier) */
                        typename __Hasher                       /* NOLINT(bugprone-reserved-identifier) */
                > using __HashMapConstIteratorRemoveClient =    /* NOLINT(bugprone-reserved-identifier) */
                        __LocalIteratorRemovePrimitiveClient <
                                cds :: experimental :: HashMap <
                                        __KeyType,
                                        __ValueType,
                                        __Hasher
                                >,
                                typename Map < __KeyType, __ValueType > :: EntryType,
                                HashTableConstIterator < typename Map < __KeyType, __ValueType > :: EntryType >
                        >;


                template <
                        typename __KeyType,                 /* NOLINT(bugprone-reserved-identifier) */
                        typename __ValueType,               /* NOLINT(bugprone-reserved-identifier) */
                        typename __Hasher                   /* NOLINT(bugprone-reserved-identifier) */
                > using __HashMapFindOfCollectionClient =   /* NOLINT(bugprone-reserved-identifier) */
                        __LocalFindOfMutableCompositeClient <
                                cds :: experimental :: HashMap <
                                        __KeyType,
                                        __ValueType,
                                        __Hasher
                                >,
                                typename Map < __KeyType, __ValueType > :: EntryType,
                                HashTableIterator < typename Map < __KeyType, __ValueType > :: EntryType >,
                                cds :: experimental :: Collection < typename Map < __KeyType, __ValueType > :: EntryType >,
                                & __collectionContains < typename Map < __KeyType, __ValueType > :: EntryType >,
                                & __collectionNotContains < typename Map < __KeyType, __ValueType > :: EntryType >
                        >;


                template <
                        typename __KeyType,                     /* NOLINT(bugprone-reserved-identifier) */
                        typename __ValueType,                   /* NOLINT(bugprone-reserved-identifier) */
                        typename __Hasher                       /* NOLINT(bugprone-reserved-identifier) */
                > using __HashMapFindOfInitializerListClient =  /* NOLINT(bugprone-reserved-identifier) */
                        __LocalFindOfMutableCompositeClient <
                                cds :: experimental :: HashMap <
                                        __KeyType,
                                        __ValueType,
                                        __Hasher
                                >,
                                typename Map < __KeyType, __ValueType > :: EntryType,
                                HashTableIterator < typename Map < __KeyType, __ValueType > :: EntryType >,
                                std :: initializer_list < typename Map < __KeyType, __ValueType > :: EntryType >,
                                & __initializerListContains < typename Map < __KeyType, __ValueType > :: EntryType, & __hashMapEquals < __KeyType, __ValueType > >,
                                & __initializerListNotContains < typename Map < __KeyType, __ValueType > :: EntryType, & __hashMapEquals < __KeyType, __ValueType > >
                        >;


                template <
                        typename __KeyType,     /* NOLINT(bugprone-reserved-identifier) */
                        typename __ValueType,   /* NOLINT(bugprone-reserved-identifier) */
                        typename __Hasher       /* NOLINT(bugprone-reserved-identifier) */
                > using __HashMapFindByClient = /* NOLINT(bugprone-reserved-identifier) */
                        __LocalFindByMutableCompositeClient <
                                cds :: experimental :: HashMap <
                                        __KeyType,
                                        __ValueType,
                                        __Hasher
                                >,
                                typename Map < __KeyType, __ValueType > :: EntryType,
                                HashTableIterator < typename Map < __KeyType, __ValueType > :: EntryType >
                        >;


                template <
                        typename __KeyType,                     /* NOLINT(bugprone-reserved-identifier) */
                        typename __ValueType,                   /* NOLINT(bugprone-reserved-identifier) */
                        typename __Hasher                       /* NOLINT(bugprone-reserved-identifier) */
                > using __HashMapFindOfConstCollectionClient =  /* NOLINT(bugprone-reserved-identifier) */
                        __LocalFindOfImmutableCompositeClient <
                                cds :: experimental :: HashMap <
                                        __KeyType,
                                        __ValueType,
                                        __Hasher
                                >,
                                typename Map < __KeyType, __ValueType > :: EntryType,
                                HashTableConstIterator < typename Map < __KeyType, __ValueType > :: EntryType >,
                                cds :: experimental :: Collection < typename Map < __KeyType, __ValueType > :: EntryType >,
                                & __collectionContains < typename Map < __KeyType, __ValueType > :: EntryType >,
                                & __collectionNotContains < typename Map < __KeyType, __ValueType > :: EntryType >
                        >;


                template <
                        typename __KeyType,                         /* NOLINT(bugprone-reserved-identifier) */
                        typename __ValueType,                       /* NOLINT(bugprone-reserved-identifier) */
                        typename __Hasher                           /* NOLINT(bugprone-reserved-identifier) */
                > using __HashMapFindOfConstInitializerListClient = /* NOLINT(bugprone-reserved-identifier) */
                        __LocalFindOfImmutableCompositeClient <
                                cds :: experimental :: HashMap <
                                        __KeyType,
                                        __ValueType,
                                        __Hasher
                                >,
                                typename Map < __KeyType, __ValueType > :: EntryType,
                                HashTableConstIterator < typename Map < __KeyType, __ValueType > :: EntryType >,
                                std :: initializer_list < typename Map < __KeyType, __ValueType > :: EntryType >,
                                & __initializerListContains < typename Map < __KeyType, __ValueType > :: EntryType, & __hashMapEquals < __KeyType, __ValueType > >,
                                & __initializerListNotContains < typename Map < __KeyType, __ValueType > :: EntryType, & __hashMapEquals < __KeyType, __ValueType > >
                        >;


                template <
                        typename __KeyType,             /* NOLINT(bugprone-reserved-identifier) */
                        typename __ValueType,           /* NOLINT(bugprone-reserved-identifier) */
                        typename __Hasher               /* NOLINT(bugprone-reserved-identifier) */
                > using __HashMapFindByConstClient =    /* NOLINT(bugprone-reserved-identifier) */
                        __LocalFindByImmutableCompositeClient <
                                cds :: experimental :: HashMap <
                                        __KeyType,
                                        __ValueType,
                                        __Hasher
                                >,
                                typename Map < __KeyType, __ValueType > :: EntryType,
                                HashTableConstIterator < typename Map < __KeyType, __ValueType > :: EntryType >
                        >;


                template <
                        typename __KeyType,             /* NOLINT(bugprone-reserved-identifier) */
                        typename __ValueType,           /* NOLINT(bugprone-reserved-identifier) */
                        typename __Hasher               /* NOLINT(bugprone-reserved-identifier) */
                > using __HashMapFindUniqueClient =     /* NOLINT(bugprone-reserved-identifier) */
                        __LocalFindUniqueMutablePrimitiveClient <
                                cds :: experimental :: HashMap <
                                        __KeyType,
                                        __ValueType,
                                        __Hasher
                                >,
                                __KeyType,
                                HashTableIterator < typename Map < __KeyType, __ValueType > :: EntryType >
                        >;


                template <
                        typename __KeyType,                 /* NOLINT(bugprone-reserved-identifier) */
                        typename __ValueType,               /* NOLINT(bugprone-reserved-identifier) */
                        typename __Hasher                   /* NOLINT(bugprone-reserved-identifier) */
                > using __HashMapFindUniqueConstClient =    /* NOLINT(bugprone-reserved-identifier) */
                        __LocalFindUniqueImmutablePrimitiveClient <
                                cds :: experimental :: HashMap <
                                        __KeyType,
                                        __ValueType,
                                        __Hasher
                                >,
                                __KeyType,
                                HashTableConstIterator < typename Map < __KeyType, __ValueType > :: EntryType >
                        >;


                template <
                        typename __KeyType,                 /* NOLINT(bugprone-reserved-identifier) */
                        typename __ValueType,               /* NOLINT(bugprone-reserved-identifier) */
                        typename __Hasher                   /* NOLINT(bugprone-reserved-identifier) */
                > using __HashMapRemoveOfCollectionClient = /* NOLINT(bugprone-reserved-identifier) */
                        __LocalRemoveOfCompositeClient <
                                cds :: experimental :: HashMap <
                                        __KeyType,
                                        __ValueType,
                                        __Hasher
                                >,
                                typename Map < __KeyType, __ValueType > :: EntryType,
                                cds :: experimental :: Collection < typename Map < __KeyType, __ValueType > :: EntryType >,
                                & __collectionContains < typename Map < __KeyType, __ValueType > :: EntryType >
                        >;


                template <
                        typename __KeyType,                 /* NOLINT(bugprone-reserved-identifier) */
                        typename __ValueType,               /* NOLINT(bugprone-reserved-identifier) */
                        typename __Hasher                   /* NOLINT(bugprone-reserved-identifier) */
                > using __HashMapRemoveOfInitializerListClient = /* NOLINT(bugprone-reserved-identifier) */
                        __LocalRemoveOfCompositeClient <
                                cds :: experimental :: HashMap <
                                        __KeyType,
                                        __ValueType,
                                        __Hasher
                                >,
                                typename Map < __KeyType, __ValueType > :: EntryType,
                                std :: initializer_list < typename Map < __KeyType, __ValueType > :: EntryType >,
                                & __initializerListContains < typename Map < __KeyType, __ValueType > :: EntryType, & __hashMapEquals < __KeyType, __ValueType > >
                        >;


                template <
                        typename __KeyType,         /* NOLINT(bugprone-reserved-identifier) */
                        typename __ValueType,       /* NOLINT(bugprone-reserved-identifier) */
                        typename __Hasher           /* NOLINT(bugprone-reserved-identifier) */
                > using __HashMapRemoveByClient =   /* NOLINT(bugprone-reserved-identifier) */
                        __LocalRemoveByCompositeClient <
                                cds :: experimental :: HashMap <
                                        __KeyType,
                                        __ValueType,
                                        __Hasher
                                >,
                                typename Map < __KeyType, __ValueType > :: EntryType
                        >;


                template <
                        typename __KeyType,                 /* NOLINT(bugprone-reserved-identifier) */
                        typename __ValueType,               /* NOLINT(bugprone-reserved-identifier) */
                        typename __Hasher                   /* NOLINT(bugprone-reserved-identifier) */
                > using __HashMapGenericStatementsClient =  /* NOLINT(bugprone-reserved-identifier) */
                        __LocalGenericMutableStatementsCompositeClient <
                                cds :: experimental :: HashMap <
                                        __KeyType,
                                        __ValueType,
                                        __Hasher
                                >,
                                typename Map < __KeyType, __ValueType > :: EntryType
                        >;


                template <
                        typename __KeyType,                 /* NOLINT(bugprone-reserved-identifier) */
                        typename __ValueType,               /* NOLINT(bugprone-reserved-identifier) */
                        typename __Hasher                   /* NOLINT(bugprone-reserved-identifier) */
                > using __HashMapConstGenericStatementsClient =  /* NOLINT(bugprone-reserved-identifier) */
                        __LocalGenericImmutableStatementsCompositeClient <
                                cds :: experimental :: HashMap <
                                        __KeyType,
                                        __ValueType,
                                        __Hasher
                                >,
                                typename Map < __KeyType, __ValueType > :: EntryType
                        >;


                template <
                        typename __KeyType,                     /* NOLINT(bugprone-reserved-identifier) */
                        typename __ValueType,                   /* NOLINT(bugprone-reserved-identifier) */
                        typename __Hasher                       /* NOLINT(bugprone-reserved-identifier) */
                > using __HashMapContainsOfCollectionClient =   /* NOLINT(bugprone-reserved-identifier) */
                        __LocalContainsOfCompositeClient <
                                cds :: experimental :: HashMap <
                                        __KeyType,
                                        __ValueType,
                                        __Hasher
                                >,
                                typename Map < __KeyType, __ValueType > :: EntryType,
                                cds :: experimental :: Collection < typename Map < __KeyType, __ValueType > :: EntryType >,
                                __collectionContains < typename Map < __KeyType, __ValueType > :: EntryType >
                        >;


                template <
                        typename __KeyType,                         /* NOLINT(bugprone-reserved-identifier) */
                        typename __ValueType,                       /* NOLINT(bugprone-reserved-identifier) */
                        typename __Hasher                           /* NOLINT(bugprone-reserved-identifier) */
                > using __HashMapContainsOfInitializerListClient =  /* NOLINT(bugprone-reserved-identifier) */
                        __LocalContainsOfCompositeClient <
                                cds :: experimental :: HashMap <
                                        __KeyType,
                                        __ValueType,
                                        __Hasher
                                >,
                                typename Map < __KeyType, __ValueType > :: EntryType,
                                std :: initializer_list < typename Map < __KeyType, __ValueType > :: EntryType >,
                                __initializerListContains <
                                        typename Map < __KeyType, __ValueType > :: EntryType,
                                        & __hashMapEquals < __KeyType, __ValueType >
                                >
                        >;


                template <
                        typename __KeyType,                         /* NOLINT(bugprone-reserved-identifier) */
                        typename __ValueType,                       /* NOLINT(bugprone-reserved-identifier) */
                        typename __Hasher                           /* NOLINT(bugprone-reserved-identifier) */
                > using __HashMapDelegateForwardIterableClient =    /* NOLINT(bugprone-reserved-identifier) */
                        __LocalDelegateForwardIterablePrimitiveClient <
                                cds :: experimental :: HashMap < __KeyType, __ValueType, __Hasher >,
                                typename __HashMapImplementation < __KeyType, __ValueType, __Hasher > :: __ht_Iterator
                        >;


                template <
                        typename __KeyType,                             /* NOLINT(bugprone-reserved-identifier) */
                        typename __ValueType,                           /* NOLINT(bugprone-reserved-identifier) */
                        typename __Hasher                               /* NOLINT(bugprone-reserved-identifier) */
                > using __HashMapDelegateForwardConstIterableClient =   /* NOLINT(bugprone-reserved-identifier) */
                        __LocalDelegateForwardConstIterablePrimitiveClient <
                                cds :: experimental :: HashMap < __KeyType, __ValueType, __Hasher >,
                                typename __HashMapImplementation < __KeyType, __ValueType, __Hasher > :: __ht_ConstIterator
                        >;

            }
        }

    }
}

#endif /* __CDS_HASH_MAP_CONSTRUCTS_HPP__ */
