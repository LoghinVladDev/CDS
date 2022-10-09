/*
 * Created by loghin on 09/10/22.
 */

#ifndef __CDS_EX_LINKED_HASH_MAP_CONSTRUCTS_HPP__
#define __CDS_EX_LINKED_HASH_MAP_CONSTRUCTS_HPP__ /* NOLINT(bugprone-reserved-identifier) */

namespace cds { /* NOLINT(modernize-concat-nested-namespaces) */
    namespace experimental {

        template <
                typename __KeyType,                                                         /* NOLINT(bugprone-reserved-identifier) */
                typename __ValueType,                                                       /* NOLINT(bugprone-reserved-identifier) */
                typename __Hasher = cds :: WrapperHasher < __KeyType, Hash < __KeyType > >  /* NOLINT(bugprone-reserved-identifier) */
        > class LinkedHashMap;

        namespace __hidden {    /* NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier) */
            namespace __impl {  /* NOLINT(bugprone-reserved-identifier) */

                template <
                        typename __KeyType,                     /* NOLINT(bugprone-reserved-identifier) */
                        typename __ValueType                    /* NOLINT(bugprone-reserved-identifier) */
                > constexpr auto __linkedHashMapKeyExtractor (  /* NOLINT(bugprone-reserved-identifier) */
                        typename Map < __KeyType, __ValueType > :: EntryType const & element
                ) noexcept -> __KeyType const & {

                    return element.key ();
                }


                template <
                        typename __KeyType,                                                     /* NOLINT(bugprone-reserved-identifier) */
                        typename __ValueType                                                    /* NOLINT(bugprone-reserved-identifier) */
                > __CDS_cpplang_ConstexprNonLiteralReturn auto __linkedHashMapCopyConstructor ( /* NOLINT(bugprone-reserved-identifier) */
                        typename Map < __KeyType, __ValueType > :: EntryType       & destinationDataNode,
                        typename Map < __KeyType, __ValueType > :: EntryType const & sourceDataNode
                ) noexcept -> void {

                    new ( & destinationDataNode ) typename Map < __KeyType, __ValueType > :: EntryType ( sourceDataNode );
                }


                template <
                        typename __KeyType,                                                 /* NOLINT(bugprone-reserved-identifier) */
                        typename __ValueType                                                /* NOLINT(bugprone-reserved-identifier) */
                > __CDS_cpplang_ConstexprNonLiteralReturn auto __linkedHashMapDestructor (  /* NOLINT(bugprone-reserved-identifier) */
                        typename Map < __KeyType, __ValueType > :: EntryType & entry
                ) noexcept -> void {

                    using EntryType = typename Map < __KeyType, __ValueType > :: EntryType;
                    entry.~EntryType();
                }


                template <
                        typename __KeyType,                 /* NOLINT(bugprone-reserved-identifier) */
                        typename __ValueType                /* NOLINT(bugprone-reserved-identifier) */
                > constexpr auto __linkedHashMapEquals (    /* NOLINT(bugprone-reserved-identifier) */
                        typename Map < __KeyType, __ValueType > :: EntryType const & leftEntry,
                        typename Map < __KeyType, __ValueType > :: EntryType const & rightEntry
                ) noexcept -> bool {

                    return
                            cds :: meta :: equals ( leftEntry.key(), rightEntry.key() ) &&
                            cds :: meta :: equals ( leftEntry.value(), rightEntry.value() );
                }


                template <
                        typename __DecoratedIteratorType,                   /* NOLINT(bugprone-reserved-identifier) */
                        typename __ValueAtType                              /* NOLINT(bugprone-reserved-identifier) */
                > constexpr auto __linkedHashMapIteratorDecoratorValueAt (  /* NOLINT(bugprone-reserved-identifier) */
                        __DecoratedIteratorType const & iterator
                ) noexcept -> __ValueAtType & {

                    return * ( * iterator );
                }


                template <
                        typename __KeyType,                         /* NOLINT(bugprone-reserved-identifier) */
                        typename __ValueType,                       /* NOLINT(bugprone-reserved-identifier) */
                        typename __Hasher                           /* NOLINT(bugprone-reserved-identifier) */
                > using __LinkedHashMapHashTableImplementation =    /* NOLINT(bugprone-reserved-identifier) */
                        __HashTable <
                                typename Map < __KeyType, __ValueType > :: EntryType,
                                __KeyType,
                                __Hasher,
                                cds :: __hidden :: __impl :: __PrimeRehashPolicy < uint32 >,
                                & __linkedHashMapKeyExtractor < __KeyType, __ValueType >,
                                & cds :: meta :: equals < __KeyType >,
                                & __linkedHashMapDestructor < __KeyType, __ValueType >
                        >;


                template <
                        typename __KeyType,                         /* NOLINT(bugprone-reserved-identifier) */
                        typename __ValueType,                       /* NOLINT(bugprone-reserved-identifier) */
                        typename __Hasher                           /* NOLINT(bugprone-reserved-identifier) */
                > using __LinkedHashMapLinkedListImplementation =   /* NOLINT(bugprone-reserved-identifier) */
                        __SingleLinkedList <
                                typename Map < __KeyType, __ValueType > :: EntryType *,
                                & cds :: meta :: equals < typename Map < __KeyType, __ValueType > :: EntryType * >
                        >;


                template <
                        typename __KeyType,         /* NOLINT(bugprone-reserved-identifier) */
                        typename __ValueType,       /* NOLINT(bugprone-reserved-identifier) */
                        typename __Hasher           /* NOLINT(bugprone-reserved-identifier) */
                > using __LinkedHashMapIterator =   /* NOLINT(bugprone-reserved-identifier) */
                        ForwardIteratorGenericDecorator <
                                typename __LinkedHashMapLinkedListImplementation < __KeyType, __ValueType, __Hasher > :: __sll_Iterator,
                                typename Map < __KeyType, __ValueType > :: EntryType,
                                & __linkedHashSetIteratorDecoratorValueAt <
                                        typename __LinkedHashMapLinkedListImplementation < __KeyType, __ValueType, __Hasher > :: __sll_Iterator,
                                        typename Map < __KeyType, __ValueType > :: EntryType
                                >
                        >;


                template <
                        typename __KeyType,             /* NOLINT(bugprone-reserved-identifier) */
                        typename __ValueType,           /* NOLINT(bugprone-reserved-identifier) */
                        typename __Hasher               /* NOLINT(bugprone-reserved-identifier) */
                > using __LinkedHashMapConstIterator =  /* NOLINT(bugprone-reserved-identifier) */
                        ForwardIteratorGenericDecorator <
                                typename __LinkedHashMapLinkedListImplementation < __KeyType, __ValueType, __Hasher > :: __sll_ConstIterator,
                                typename Map < __KeyType, __ValueType > :: EntryType const,
                                & __linkedHashSetIteratorDecoratorValueAt <
                                        typename __LinkedHashMapLinkedListImplementation < __KeyType, __ValueType, __Hasher > :: __sll_ConstIterator,
                                        typename Map < __KeyType, __ValueType > :: EntryType const
                                >
                        >;


                template <
                        typename __KeyType,         /* NOLINT(bugprone-reserved-identifier) */
                        typename __ValueType,       /* NOLINT(bugprone-reserved-identifier) */
                        typename __Hasher           /* NOLINT(bugprone-reserved-identifier) */
                > using __LinkedHashMapServer =     /* NOLINT(bugprone-reserved-identifier) */
                        __MapServer <
                                cds :: experimental :: LinkedHashMap <
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
                > using __LinkedHashMapRandomInsertionClient =  /* NOLINT(bugprone-reserved-identifier) */
                        __LocalRandomInsertionPrimitiveClient <
                                cds :: experimental :: LinkedHashMap <
                                        __KeyType,
                                        __ValueType,
                                        __Hasher
                                >,
                                typename Map < __KeyType, __ValueType > :: EntryType,
                                typename Map < __KeyType, __ValueType > :: EntryType
                        >;


                template <
                        typename __KeyType,                     /* NOLINT(bugprone-reserved-identifier) */
                        typename __ValueType,                   /* NOLINT(bugprone-reserved-identifier) */
                        typename __Hasher                       /* NOLINT(bugprone-reserved-identifier) */
                > using __LinkedHashMapIteratorRemoveClient =   /* NOLINT(bugprone-reserved-identifier) */
                        __LocalIteratorRemovePrimitiveClient <
                                cds :: experimental :: LinkedHashMap <
                                        __KeyType,
                                        __ValueType,
                                        __Hasher
                                >,
                                typename Map < __KeyType, __ValueType > :: EntryType,
                                __LinkedHashMapIterator < __KeyType, __ValueType, __Hasher >
                        >;


                template <
                        typename __KeyType,                         /* NOLINT(bugprone-reserved-identifier) */
                        typename __ValueType,                       /* NOLINT(bugprone-reserved-identifier) */
                        typename __Hasher                           /* NOLINT(bugprone-reserved-identifier) */
                > using __LinkedHashMapConstIteratorRemoveClient =  /* NOLINT(bugprone-reserved-identifier) */
                        __LocalIteratorRemovePrimitiveClient <
                                cds :: experimental :: LinkedHashMap <
                                        __KeyType,
                                        __ValueType,
                                        __Hasher
                                >,
                                typename Map < __KeyType, __ValueType > :: EntryType,
                                __LinkedHashMapConstIterator < __KeyType, __ValueType, __Hasher >
                        >;


                template <
                        typename __KeyType,                     /* NOLINT(bugprone-reserved-identifier) */
                        typename __ValueType,                   /* NOLINT(bugprone-reserved-identifier) */
                        typename __Hasher                       /* NOLINT(bugprone-reserved-identifier) */
                > using __LinkedHashMapFindOfCollectionClient = /* NOLINT(bugprone-reserved-identifier) */
                        __LocalFindOfMutableCompositeClient <
                                cds :: experimental :: LinkedHashMap <
                                        __KeyType,
                                        __ValueType,
                                        __Hasher
                                >,
                                typename Map < __KeyType, __ValueType > :: EntryType,
                                __LinkedHashMapIterator < __KeyType, __ValueType, __Hasher >,
                                cds :: experimental :: Collection < typename Map < __KeyType, __ValueType > :: EntryType >,
                                & __collectionContains < typename Map < __KeyType, __ValueType > :: EntryType >,
                                & __collectionNotContains < typename Map < __KeyType, __ValueType > :: EntryType >
                        >;


                template <
                        typename __KeyType,                     /* NOLINT(bugprone-reserved-identifier) */
                        typename __ValueType,                   /* NOLINT(bugprone-reserved-identifier) */
                        typename __Hasher                       /* NOLINT(bugprone-reserved-identifier) */
                > using __LinkedHashMapFindOfInitializerListClient =  /* NOLINT(bugprone-reserved-identifier) */
                        __LocalFindOfMutableCompositeClient <
                                cds :: experimental :: LinkedHashMap <
                                        __KeyType,
                                        __ValueType,
                                        __Hasher
                                >,
                                typename Map < __KeyType, __ValueType > :: EntryType,
                                __LinkedHashMapIterator < __KeyType, __ValueType, __Hasher >,
                                std :: initializer_list < typename Map < __KeyType, __ValueType > :: EntryType >,
                                & __initializerListContains < typename Map < __KeyType, __ValueType > :: EntryType, & __linkedHashMapEquals < __KeyType, __ValueType > >,
                                & __initializerListNotContains < typename Map < __KeyType, __ValueType > :: EntryType, & __linkedHashMapEquals < __KeyType, __ValueType > >
                        >;


                template <
                        typename __KeyType,             /* NOLINT(bugprone-reserved-identifier) */
                        typename __ValueType,           /* NOLINT(bugprone-reserved-identifier) */
                        typename __Hasher               /* NOLINT(bugprone-reserved-identifier) */
                > using __LinkedHashMapFindByClient =   /* NOLINT(bugprone-reserved-identifier) */
                        __LocalFindByMutableCompositeClient <
                                cds :: experimental :: LinkedHashMap <
                                        __KeyType,
                                        __ValueType,
                                        __Hasher
                                >,
                                typename Map < __KeyType, __ValueType > :: EntryType,
                                __LinkedHashMapIterator < __KeyType, __ValueType, __Hasher >
                        >;


                template <
                        typename __KeyType,                             /* NOLINT(bugprone-reserved-identifier) */
                        typename __ValueType,                           /* NOLINT(bugprone-reserved-identifier) */
                        typename __Hasher                               /* NOLINT(bugprone-reserved-identifier) */
                > using __LinkedHashMapFindOfConstCollectionClient =    /* NOLINT(bugprone-reserved-identifier) */
                        __LocalFindOfImmutableCompositeClient <
                                cds :: experimental :: LinkedHashMap <
                                        __KeyType,
                                        __ValueType,
                                        __Hasher
                                >,
                                typename Map < __KeyType, __ValueType > :: EntryType,
                                __LinkedHashMapConstIterator < __KeyType, __ValueType, __Hasher >,
                                cds :: experimental :: Collection < typename Map < __KeyType, __ValueType > :: EntryType >,
                                & __collectionContains < typename Map < __KeyType, __ValueType > :: EntryType >,
                                & __collectionNotContains < typename Map < __KeyType, __ValueType > :: EntryType >
                        >;


                template <
                        typename __KeyType,                                 /* NOLINT(bugprone-reserved-identifier) */
                        typename __ValueType,                               /* NOLINT(bugprone-reserved-identifier) */
                        typename __Hasher                                   /* NOLINT(bugprone-reserved-identifier) */
                > using __LinkedHashMapFindOfConstInitializerListClient =   /* NOLINT(bugprone-reserved-identifier) */
                        __LocalFindOfImmutableCompositeClient <
                                cds :: experimental :: LinkedHashMap <
                                        __KeyType,
                                        __ValueType,
                                        __Hasher
                                >,
                                typename Map < __KeyType, __ValueType > :: EntryType,
                                __LinkedHashMapConstIterator < __KeyType, __ValueType, __Hasher >,
                                std :: initializer_list < typename Map < __KeyType, __ValueType > :: EntryType >,
                                & __initializerListContains < typename Map < __KeyType, __ValueType > :: EntryType, & __linkedHashMapEquals < __KeyType, __ValueType > >,
                                & __initializerListNotContains < typename Map < __KeyType, __ValueType > :: EntryType, & __linkedHashMapEquals < __KeyType, __ValueType > >
                        >;


                template <
                        typename __KeyType,                 /* NOLINT(bugprone-reserved-identifier) */
                        typename __ValueType,               /* NOLINT(bugprone-reserved-identifier) */
                        typename __Hasher                   /* NOLINT(bugprone-reserved-identifier) */
                > using __LinkedHashMapFindByConstClient =  /* NOLINT(bugprone-reserved-identifier) */
                        __LocalFindByImmutableCompositeClient <
                                cds :: experimental :: LinkedHashMap <
                                        __KeyType,
                                        __ValueType,
                                        __Hasher
                                >,
                                typename Map < __KeyType, __ValueType > :: EntryType,
                                __LinkedHashMapConstIterator < __KeyType, __ValueType, __Hasher >
                        >;


                template <
                        typename __KeyType,                 /* NOLINT(bugprone-reserved-identifier) */
                        typename __ValueType,               /* NOLINT(bugprone-reserved-identifier) */
                        typename __Hasher                   /* NOLINT(bugprone-reserved-identifier) */
                > using __LinkedHashMapFindUniqueClient =   /* NOLINT(bugprone-reserved-identifier) */
                        __LocalFindUniqueMutablePrimitiveClient <
                                cds :: experimental :: LinkedHashMap <
                                        __KeyType,
                                        __ValueType,
                                        __Hasher
                                >,
                                __KeyType,
                                __LinkedHashMapIterator < __KeyType, __ValueType, __Hasher >
                        >;


                template <
                        typename __KeyType,                     /* NOLINT(bugprone-reserved-identifier) */
                        typename __ValueType,                   /* NOLINT(bugprone-reserved-identifier) */
                        typename __Hasher                       /* NOLINT(bugprone-reserved-identifier) */
                > using __LinkedHashMapFindUniqueConstClient =  /* NOLINT(bugprone-reserved-identifier) */
                        __LocalFindUniqueImmutablePrimitiveClient <
                                cds :: experimental :: LinkedHashMap <
                                        __KeyType,
                                        __ValueType,
                                        __Hasher
                                >,
                                __KeyType,
                                __LinkedHashMapConstIterator < __KeyType, __ValueType, __Hasher >
                        >;


                template <
                        typename __KeyType,                         /* NOLINT(bugprone-reserved-identifier) */
                        typename __ValueType,                       /* NOLINT(bugprone-reserved-identifier) */
                        typename __Hasher                           /* NOLINT(bugprone-reserved-identifier) */
                > using __LinkedHashMapRemoveOfCollectionClient =   /* NOLINT(bugprone-reserved-identifier) */
                        __LocalRemoveOfCompositeClient <
                                cds :: experimental :: LinkedHashMap <
                                        __KeyType,
                                        __ValueType,
                                        __Hasher
                                >,
                                typename Map < __KeyType, __ValueType > :: EntryType,
                                cds :: experimental :: Collection < typename Map < __KeyType, __ValueType > :: EntryType >,
                                & __collectionContains < typename Map < __KeyType, __ValueType > :: EntryType >
                        >;


                template <
                        typename __KeyType,                             /* NOLINT(bugprone-reserved-identifier) */
                        typename __ValueType,                           /* NOLINT(bugprone-reserved-identifier) */
                        typename __Hasher                               /* NOLINT(bugprone-reserved-identifier) */
                > using __LinkedHashMapRemoveOfInitializerListClient =  /* NOLINT(bugprone-reserved-identifier) */
                        __LocalRemoveOfCompositeClient <
                                cds :: experimental :: LinkedHashMap <
                                        __KeyType,
                                        __ValueType,
                                        __Hasher
                                >,
                                typename Map < __KeyType, __ValueType > :: EntryType,
                                std :: initializer_list < typename Map < __KeyType, __ValueType > :: EntryType >,
                                & __initializerListContains < typename Map < __KeyType, __ValueType > :: EntryType, & __linkedHashMapEquals < __KeyType, __ValueType > >
                >;


                template <
                        typename __KeyType,             /* NOLINT(bugprone-reserved-identifier) */
                        typename __ValueType,           /* NOLINT(bugprone-reserved-identifier) */
                        typename __Hasher               /* NOLINT(bugprone-reserved-identifier) */
                > using __LinkedHashMapRemoveByClient = /* NOLINT(bugprone-reserved-identifier) */
                        __LocalRemoveByCompositeClient <
                                cds :: experimental :: LinkedHashMap <
                                        __KeyType,
                                        __ValueType,
                                        __Hasher
                                >,
                                typename Map < __KeyType, __ValueType > :: EntryType
                        >;


                template <
                        typename __KeyType,                         /* NOLINT(bugprone-reserved-identifier) */
                        typename __ValueType,                       /* NOLINT(bugprone-reserved-identifier) */
                        typename __Hasher                           /* NOLINT(bugprone-reserved-identifier) */
                > using __LinkedHashMapGenericStatementsClient =    /* NOLINT(bugprone-reserved-identifier) */
                        __LocalGenericMutableStatementsCompositeClient <
                                cds :: experimental :: LinkedHashMap <
                                        __KeyType,
                                        __ValueType,
                                        __Hasher
                                >,
                                typename Map < __KeyType, __ValueType > :: EntryType
                        >;


                template <
                        typename __KeyType,                             /* NOLINT(bugprone-reserved-identifier) */
                        typename __ValueType,                           /* NOLINT(bugprone-reserved-identifier) */
                        typename __Hasher                               /* NOLINT(bugprone-reserved-identifier) */
                > using __LinkedHashMapConstGenericStatementsClient =   /* NOLINT(bugprone-reserved-identifier) */
                        __LocalGenericImmutableStatementsCompositeClient <
                                cds :: experimental :: LinkedHashMap <
                                        __KeyType,
                                        __ValueType,
                                        __Hasher
                                >,
                                typename Map < __KeyType, __ValueType > :: EntryType
                        >;


                template <
                        typename __KeyType,                         /* NOLINT(bugprone-reserved-identifier) */
                        typename __ValueType,                       /* NOLINT(bugprone-reserved-identifier) */
                        typename __Hasher                           /* NOLINT(bugprone-reserved-identifier) */
                > using __LinkedHashMapContainsOfCollectionClient = /* NOLINT(bugprone-reserved-identifier) */
                        __LocalContainsOfCompositeClient <
                                cds :: experimental :: LinkedHashMap <
                                        __KeyType,
                                        __ValueType,
                                        __Hasher
                                >,
                                typename Map < __KeyType, __ValueType > :: EntryType,
                                cds :: experimental :: Collection < typename Map < __KeyType, __ValueType > :: EntryType >,
                                __collectionContains < typename Map < __KeyType, __ValueType > :: EntryType >
                        >;


                template <
                        typename __KeyType,                                 /* NOLINT(bugprone-reserved-identifier) */
                        typename __ValueType,                               /* NOLINT(bugprone-reserved-identifier) */
                        typename __Hasher                                   /* NOLINT(bugprone-reserved-identifier) */
                > using __LinkedHashMapContainsOfInitializerListClient =    /* NOLINT(bugprone-reserved-identifier) */
                        __LocalContainsOfCompositeClient <
                                cds :: experimental :: LinkedHashMap <
                                        __KeyType,
                                        __ValueType,
                                        __Hasher
                                >,
                                typename Map < __KeyType, __ValueType > :: EntryType,
                                std :: initializer_list < typename Map < __KeyType, __ValueType > :: EntryType >,
                                __initializerListContains <
                                        typename Map < __KeyType, __ValueType > :: EntryType,
                                        & __linkedHashMapEquals < __KeyType, __ValueType >
                                >
                        >;


                template <
                        typename __KeyType,                             /* NOLINT(bugprone-reserved-identifier) */
                        typename __ValueType,                           /* NOLINT(bugprone-reserved-identifier) */
                        typename __Hasher                               /* NOLINT(bugprone-reserved-identifier) */
                > using __LinkedHashMapDelegateForwardIterableClient =  /* NOLINT(bugprone-reserved-identifier) */
                        __LocalDelegateForwardIterablePrimitiveClient <
                                cds :: experimental :: LinkedHashMap < __KeyType, __ValueType, __Hasher >,
                                __LinkedHashMapIterator < __KeyType, __ValueType, __Hasher >
                        >;


                template <
                        typename __KeyType,                                 /* NOLINT(bugprone-reserved-identifier) */
                        typename __ValueType,                               /* NOLINT(bugprone-reserved-identifier) */
                        typename __Hasher                                   /* NOLINT(bugprone-reserved-identifier) */
                > using __LinkedHashMapDelegateForwardConstIterableClient = /* NOLINT(bugprone-reserved-identifier) */
                        __LocalDelegateForwardConstIterablePrimitiveClient <
                                cds :: experimental :: LinkedHashMap < __KeyType, __ValueType, __Hasher >,
                                __LinkedHashMapConstIterator < __KeyType, __ValueType, __Hasher >
                        >;

            }
        }

    }
}

#endif /* __CDS_EX_LINKED_HASH_MAP_CONSTRUCTS_HPP__ */
