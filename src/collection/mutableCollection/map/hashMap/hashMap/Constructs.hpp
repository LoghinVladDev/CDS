/* NOLINT(llvm-header-guard)
 * Created by loghin on 13/08/22.
 */

#ifndef __CDS_HASH_MAP_CONSTRUCTS_HPP__ /* NOLINT(llvm-header-guard) */
#define __CDS_HASH_MAP_CONSTRUCTS_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

namespace cds {

    template <
            typename __KeyType,                                                         /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __ValueType,                                                       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __Hasher = cds :: WrapperHasher < __KeyType, Hash < __KeyType > >  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    > class HashMap;

    namespace __hidden {    /* NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        namespace __impl {  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            template <
                    typename __KeyType,                 /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ValueType                /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > constexpr auto __hashMapKeyExtractor (    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename Map < __KeyType, __ValueType > :: EntryType const & element
            ) noexcept -> __KeyType const & {

                return element.key ();
            }


            template <
                    typename __KeyType,                                                 /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ValueType                                                /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > __CDS_cpplang_ConstexprNonLiteralReturn auto __hashMapCopyConstructor (   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename Map < __KeyType, __ValueType > :: EntryType       & destinationDataNode,
                    typename Map < __KeyType, __ValueType > :: EntryType const & sourceDataNode
            ) noexcept -> void {

                new ( & destinationDataNode ) typename Map < __KeyType, __ValueType > :: EntryType ( sourceDataNode );
            }


            template <
                    typename __KeyType,                                             /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ValueType                                            /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > __CDS_cpplang_ConstexprNonLiteralReturn auto __hashMapDestructor (    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename Map < __KeyType, __ValueType > :: EntryType & entry
            ) noexcept -> void {

                using EntryType = typename Map < __KeyType, __ValueType > :: EntryType;
                entry.~EntryType();
            }


            template <
                    typename __KeyType,                                                     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ValueType                                                    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > constexpr auto __hashMapEquals (                                              /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename Map < __KeyType, __ValueType > :: EntryType const & leftEntry, /* NOLINT(bugprone-easily-swappable-parameters) */
                    typename Map < __KeyType, __ValueType > :: EntryType const & rightEntry /* NOLINT(bugprone-easily-swappable-parameters) */
            ) noexcept -> bool {

                return
                        cds :: meta :: equals ( leftEntry.key(), rightEntry.key() ) &&
                        cds :: meta :: equals ( leftEntry.value(), rightEntry.value() );
            }


            template <
                    typename __KeyType,         /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ValueType,       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __Hasher           /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > using __HashMapImplementation =   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
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
                    typename __KeyType,         /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ValueType,       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __Hasher           /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > using __HashMapDispatcher =       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
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
                    typename __KeyType,         /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ValueType,       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __Hasher           /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > using __HashMapServer =           /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __MapServer <
                            cds :: HashMap <
                                    __KeyType,
                                    __ValueType,
                                    __Hasher
                            >,
                            typename Map < __KeyType, __ValueType > :: EntryType
                    >;


            template <
                    typename __KeyType,                 /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ValueType,               /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __Hasher                   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > using __HashMapRandomInsertionClient =    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __LocalRandomInsertionPrimitiveClient <
                            cds :: HashMap <
                                    __KeyType,
                                    __ValueType,
                                    __Hasher
                            >,
                            typename Map < __KeyType, __ValueType > :: EntryType,
                            typename Map < __KeyType, __ValueType > :: EntryType
                    >;


            template <
                    typename __KeyType,             /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ValueType,           /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __Hasher               /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > using __HashMapIteratorRemoveClient = /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __LocalIteratorRemovePrimitiveClient <
                            cds :: HashMap <
                                    __KeyType,
                                    __ValueType,
                                    __Hasher
                            >,
                            typename Map < __KeyType, __ValueType > :: EntryType,
                            HashTableIterator < typename Map < __KeyType, __ValueType > :: EntryType >
                    >;


            template <
                    typename __KeyType,                     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ValueType,                   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __Hasher                       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > using __HashMapConstIteratorRemoveClient =    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __LocalIteratorRemovePrimitiveClient <
                            cds :: HashMap <
                                    __KeyType,
                                    __ValueType,
                                    __Hasher
                            >,
                            typename Map < __KeyType, __ValueType > :: EntryType,
                            HashTableConstIterator < typename Map < __KeyType, __ValueType > :: EntryType >
                    >;


            template <
                    typename __KeyType,                 /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ValueType,               /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __Hasher                   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > using __HashMapFindOfCollectionClient =   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __LocalFindOfMutableCompositeClient <
                            cds :: HashMap <
                                    __KeyType,
                                    __ValueType,
                                    __Hasher
                            >,
                            typename Map < __KeyType, __ValueType > :: EntryType,
                            HashTableIterator < typename Map < __KeyType, __ValueType > :: EntryType >,
                            cds :: Collection < typename Map < __KeyType, __ValueType > :: EntryType >,
                            & __collectionContains < typename Map < __KeyType, __ValueType > :: EntryType >,
                            & __collectionNotContains < typename Map < __KeyType, __ValueType > :: EntryType >
                    >;


            template <
                    typename __KeyType,                     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ValueType,                   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __Hasher                       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > using __HashMapFindOfInitializerListClient =  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __LocalFindOfMutableCompositeClient <
                            cds :: HashMap <
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
                    typename __KeyType,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ValueType,   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __Hasher       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > using __HashMapFindByClient = /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __LocalFindByMutableCompositeClient <
                            cds :: HashMap <
                                    __KeyType,
                                    __ValueType,
                                    __Hasher
                            >,
                            typename Map < __KeyType, __ValueType > :: EntryType,
                            HashTableIterator < typename Map < __KeyType, __ValueType > :: EntryType >
                    >;


            template <
                    typename __KeyType,                     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ValueType,                   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __Hasher                       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > using __HashMapFindOfConstCollectionClient =  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __LocalFindOfImmutableCompositeClient <
                            cds :: HashMap <
                                    __KeyType,
                                    __ValueType,
                                    __Hasher
                            >,
                            typename Map < __KeyType, __ValueType > :: EntryType,
                            HashTableConstIterator < typename Map < __KeyType, __ValueType > :: EntryType >,
                            cds :: Collection < typename Map < __KeyType, __ValueType > :: EntryType >,
                            & __collectionContains < typename Map < __KeyType, __ValueType > :: EntryType >,
                            & __collectionNotContains < typename Map < __KeyType, __ValueType > :: EntryType >
                    >;


            template <
                    typename __KeyType,                         /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ValueType,                       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __Hasher                           /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > using __HashMapFindOfConstInitializerListClient = /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __LocalFindOfImmutableCompositeClient <
                            cds :: HashMap <
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
                    typename __KeyType,             /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ValueType,           /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __Hasher               /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > using __HashMapFindByConstClient =    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __LocalFindByImmutableCompositeClient <
                            cds :: HashMap <
                                    __KeyType,
                                    __ValueType,
                                    __Hasher
                            >,
                            typename Map < __KeyType, __ValueType > :: EntryType,
                            HashTableConstIterator < typename Map < __KeyType, __ValueType > :: EntryType >
                    >;


            template <
                    typename __KeyType,             /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ValueType,           /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __Hasher               /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > using __HashMapFindUniqueClient =     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __LocalFindUniqueMutablePrimitiveClient <
                            cds :: HashMap <
                                    __KeyType,
                                    __ValueType,
                                    __Hasher
                            >,
                            __KeyType,
                            HashTableIterator < typename Map < __KeyType, __ValueType > :: EntryType >
                    >;


            template <
                    typename __KeyType,                 /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ValueType,               /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __Hasher                   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > using __HashMapFindUniqueConstClient =    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __LocalFindUniqueImmutablePrimitiveClient <
                            cds :: HashMap <
                                    __KeyType,
                                    __ValueType,
                                    __Hasher
                            >,
                            __KeyType,
                            HashTableConstIterator < typename Map < __KeyType, __ValueType > :: EntryType >
                    >;


            template <
                    typename __KeyType,                 /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ValueType,               /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __Hasher                   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > using __HashMapRemoveOfCollectionClient = /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __LocalRemoveOfCompositeClient <
                            cds :: HashMap <
                                    __KeyType,
                                    __ValueType,
                                    __Hasher
                            >,
                            typename Map < __KeyType, __ValueType > :: EntryType,
                            cds :: Collection < typename Map < __KeyType, __ValueType > :: EntryType >,
                            & __collectionContains < typename Map < __KeyType, __ValueType > :: EntryType >
                    >;


            template <
                    typename __KeyType,                 /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ValueType,               /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __Hasher                   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > using __HashMapRemoveOfInitializerListClient = /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __LocalRemoveOfCompositeClient <
                            cds :: HashMap <
                                    __KeyType,
                                    __ValueType,
                                    __Hasher
                            >,
                            typename Map < __KeyType, __ValueType > :: EntryType,
                            std :: initializer_list < typename Map < __KeyType, __ValueType > :: EntryType >,
                            & __initializerListContains < typename Map < __KeyType, __ValueType > :: EntryType, & __hashMapEquals < __KeyType, __ValueType > >
                    >;


            template <
                    typename __KeyType,         /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ValueType,       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __Hasher           /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > using __HashMapRemoveByClient =   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __LocalRemoveByCompositeClient <
                            cds :: HashMap <
                                    __KeyType,
                                    __ValueType,
                                    __Hasher
                            >,
                            typename Map < __KeyType, __ValueType > :: EntryType
                    >;


            template <
                    typename __KeyType,                 /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ValueType,               /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __Hasher                   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > using __HashMapGenericStatementsClient =  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __LocalGenericMutableStatementsCompositeClient <
                            cds :: HashMap <
                                    __KeyType,
                                    __ValueType,
                                    __Hasher
                            >,
                            typename Map < __KeyType, __ValueType > :: EntryType
                    >;


            template <
                    typename __KeyType,                 /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ValueType,               /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __Hasher                   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > using __HashMapConstGenericStatementsClient =  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __LocalGenericImmutableStatementsCompositeClient <
                            cds :: HashMap <
                                    __KeyType,
                                    __ValueType,
                                    __Hasher
                            >,
                            typename Map < __KeyType, __ValueType > :: EntryType
                    >;


            template <
                    typename __KeyType,                     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ValueType,                   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __Hasher                       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > using __HashMapContainsOfCollectionClient =   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __LocalContainsOfCompositeClient <
                            cds :: HashMap <
                                    __KeyType,
                                    __ValueType,
                                    __Hasher
                            >,
                            typename Map < __KeyType, __ValueType > :: EntryType,
                            cds :: Collection < typename Map < __KeyType, __ValueType > :: EntryType >,
                            __collectionContains < typename Map < __KeyType, __ValueType > :: EntryType >
                    >;


            template <
                    typename __KeyType,                         /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ValueType,                       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __Hasher                           /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > using __HashMapContainsOfInitializerListClient =  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __LocalContainsOfCompositeClient <
                            cds :: HashMap <
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
                    typename __KeyType,                         /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ValueType,                       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __Hasher                           /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > using __HashMapDelegateForwardIterableClient =    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __LocalDelegateForwardIterablePrimitiveClient <
                            cds :: HashMap < __KeyType, __ValueType, __Hasher >,
                            typename __HashMapImplementation < __KeyType, __ValueType, __Hasher > :: __ht_Iterator
                    >;


            template <
                    typename __KeyType,                             /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ValueType,                           /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __Hasher                               /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > using __HashMapDelegateForwardConstIterableClient =   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __LocalDelegateForwardConstIterablePrimitiveClient <
                            cds :: HashMap < __KeyType, __ValueType, __Hasher >,
                            typename __HashMapImplementation < __KeyType, __ValueType, __Hasher > :: __ht_ConstIterator
                    >;

        } /* namespace __impl */
    } /* namespace __hidden */
} /* namespace cds */

#endif /* __CDS_HASH_MAP_CONSTRUCTS_HPP__ */
