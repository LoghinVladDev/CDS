/* NOLINT(llvm-header-guard)
 * Created by loghin on 09/10/22.
 */

#ifndef __CDS_LINKED_HASH_MAP_CONSTRUCTS_HPP__ /* NOLINT(llvm-header-guard) */
#define __CDS_LINKED_HASH_MAP_CONSTRUCTS_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

namespace cds {

    template <
            typename __KeyType,                                                         /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __ValueType,                                                       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __Hasher = cds :: WrapperHasher < __KeyType, Hash < __KeyType > >  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    > class LinkedHashMap;

    namespace __hidden {    /* NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        namespace __impl {  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            template <
                    typename __KeyType,                     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ValueType                    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > constexpr auto __linkedHashMapKeyExtractor (  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename Map < __KeyType, __ValueType > :: EntryType const & element
            ) noexcept -> __KeyType const & {

                return element.key ();
            }


            template <
                    typename __KeyType,                                                                         /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ValueType                                                                        /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > __CDS_MaybeUnused __CDS_cpplang_ConstexprNonLiteralReturn auto __linkedHashMapCopyConstructor (   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-avoid-non-const-global-variables) */
                    typename Map < __KeyType, __ValueType > :: EntryType       & destinationDataNode,
                    typename Map < __KeyType, __ValueType > :: EntryType const & sourceDataNode
            ) noexcept -> void {

                new ( & destinationDataNode ) typename Map < __KeyType, __ValueType > :: EntryType ( sourceDataNode );
            }


            template <
                    typename __KeyType,                                                 /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ValueType                                                /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > __CDS_cpplang_ConstexprNonLiteralReturn auto __linkedHashMapDestructor (  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename Map < __KeyType, __ValueType > :: EntryType & entry
            ) noexcept -> void {

                using EntryType = typename Map < __KeyType, __ValueType > :: EntryType;
                entry.~EntryType();
            }


            template <
                    typename __KeyType,                                                     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ValueType                                                    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > constexpr auto __linkedHashMapEquals (                                        /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename Map < __KeyType, __ValueType > :: EntryType const & leftEntry, /* NOLINT(bugprone-easily-swappable-parameters) */
                    typename Map < __KeyType, __ValueType > :: EntryType const & rightEntry /* NOLINT(bugprone-easily-swappable-parameters) */
            ) noexcept -> bool {

                return
                        cds :: meta :: equals ( leftEntry.key(), rightEntry.key() ) &&
                        cds :: meta :: equals ( leftEntry.value(), rightEntry.value() );
            }


            template <
                    typename __DecoratedIteratorType,                   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ValueAtType                              /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > constexpr auto __linkedHashMapIteratorDecoratorValueAt (  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __DecoratedIteratorType const & iterator
            ) noexcept -> __ValueAtType & {

                return * ( * iterator );
            }


            template <
                    typename __KeyType,                         /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ValueType,                       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __Hasher                           /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > using __LinkedHashMapHashTableImplementation =    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
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
                    typename __KeyType,                         /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ValueType,                       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __Hasher                           /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > using __LinkedHashMapLinkedListImplementation =   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __SingleLinkedList <
                            typename Map < __KeyType, __ValueType > :: EntryType *,
                            & cds :: meta :: equals < typename Map < __KeyType, __ValueType > :: EntryType * >
                    >;


            template <
                    typename __KeyType,         /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ValueType,       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __Hasher           /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > using __LinkedHashMapIterator =   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    ForwardIteratorGenericDecorator <
                            typename __LinkedHashMapLinkedListImplementation < __KeyType, __ValueType, __Hasher > :: __sll_Iterator,
                            typename Map < __KeyType, __ValueType > :: EntryType,
                            & __linkedHashMapIteratorDecoratorValueAt <
                                    typename __LinkedHashMapLinkedListImplementation < __KeyType, __ValueType, __Hasher > :: __sll_Iterator,
                                    typename Map < __KeyType, __ValueType > :: EntryType
                            >
                    >;


            template <
                    typename __KeyType,             /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ValueType,           /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __Hasher               /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > using __LinkedHashMapConstIterator =  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    ForwardIteratorGenericDecorator <
                            typename __LinkedHashMapLinkedListImplementation < __KeyType, __ValueType, __Hasher > :: __sll_ConstIterator,
                            typename Map < __KeyType, __ValueType > :: EntryType const,
                            & __linkedHashMapIteratorDecoratorValueAt <
                                    typename __LinkedHashMapLinkedListImplementation < __KeyType, __ValueType, __Hasher > :: __sll_ConstIterator,
                                    typename Map < __KeyType, __ValueType > :: EntryType const
                            >
                    >;


            template <
                    typename __KeyType,         /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ValueType,       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __Hasher           /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > using __LinkedHashMapServer =     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __MapServer <
                            cds :: LinkedHashMap <
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
            > using __LinkedHashMapRandomInsertionClient =  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __LocalRandomInsertionPrimitiveClient <
                            cds :: LinkedHashMap <
                                    __KeyType,
                                    __ValueType,
                                    __Hasher
                            >,
                            typename Map < __KeyType, __ValueType > :: EntryType,
                            typename Map < __KeyType, __ValueType > :: EntryType
                    >;


            template <
                    typename __KeyType,                     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ValueType,                   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __Hasher                       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > using __LinkedHashMapIteratorRemoveClient =   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __LocalIteratorRemovePrimitiveClient <
                            cds :: LinkedHashMap <
                                    __KeyType,
                                    __ValueType,
                                    __Hasher
                            >,
                            typename Map < __KeyType, __ValueType > :: EntryType,
                            __LinkedHashMapIterator < __KeyType, __ValueType, __Hasher >
                    >;


            template <
                    typename __KeyType,                         /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ValueType,                       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __Hasher                           /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > using __LinkedHashMapConstIteratorRemoveClient =  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __LocalIteratorRemovePrimitiveClient <
                            cds :: LinkedHashMap <
                                    __KeyType,
                                    __ValueType,
                                    __Hasher
                            >,
                            typename Map < __KeyType, __ValueType > :: EntryType,
                            __LinkedHashMapConstIterator < __KeyType, __ValueType, __Hasher >
                    >;


            template <
                    typename __KeyType,                     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ValueType,                   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __Hasher                       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > using __LinkedHashMapFindOfCollectionClient = /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __LocalFindOfMutableCompositeClient <
                            cds :: LinkedHashMap <
                                    __KeyType,
                                    __ValueType,
                                    __Hasher
                            >,
                            typename Map < __KeyType, __ValueType > :: EntryType,
                            __LinkedHashMapIterator < __KeyType, __ValueType, __Hasher >,
                            cds :: Collection < typename Map < __KeyType, __ValueType > :: EntryType >,
                            & __collectionContains < typename Map < __KeyType, __ValueType > :: EntryType >,
                            & __collectionNotContains < typename Map < __KeyType, __ValueType > :: EntryType >
                    >;


            template <
                    typename __KeyType,                     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ValueType,                   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __Hasher                       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > using __LinkedHashMapFindOfInitializerListClient =  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __LocalFindOfMutableCompositeClient <
                            cds :: LinkedHashMap <
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
                    typename __KeyType,             /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ValueType,           /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __Hasher               /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > using __LinkedHashMapFindByClient =   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __LocalFindByMutableCompositeClient <
                            cds :: LinkedHashMap <
                                    __KeyType,
                                    __ValueType,
                                    __Hasher
                            >,
                            typename Map < __KeyType, __ValueType > :: EntryType,
                            __LinkedHashMapIterator < __KeyType, __ValueType, __Hasher >
                    >;


            template <
                    typename __KeyType,                             /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ValueType,                           /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __Hasher                               /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > using __LinkedHashMapFindOfConstCollectionClient =    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __LocalFindOfImmutableCompositeClient <
                            cds :: LinkedHashMap <
                                    __KeyType,
                                    __ValueType,
                                    __Hasher
                            >,
                            typename Map < __KeyType, __ValueType > :: EntryType,
                            __LinkedHashMapConstIterator < __KeyType, __ValueType, __Hasher >,
                            cds :: Collection < typename Map < __KeyType, __ValueType > :: EntryType >,
                            & __collectionContains < typename Map < __KeyType, __ValueType > :: EntryType >,
                            & __collectionNotContains < typename Map < __KeyType, __ValueType > :: EntryType >
                    >;


            template <
                    typename __KeyType,                                 /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ValueType,                               /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __Hasher                                   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > using __LinkedHashMapFindOfConstInitializerListClient =   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __LocalFindOfImmutableCompositeClient <
                            cds :: LinkedHashMap <
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
                    typename __KeyType,                 /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ValueType,               /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __Hasher                   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > using __LinkedHashMapFindByConstClient =  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __LocalFindByImmutableCompositeClient <
                            cds :: LinkedHashMap <
                                    __KeyType,
                                    __ValueType,
                                    __Hasher
                            >,
                            typename Map < __KeyType, __ValueType > :: EntryType,
                            __LinkedHashMapConstIterator < __KeyType, __ValueType, __Hasher >
                    >;


            template <
                    typename __KeyType,                 /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ValueType,               /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __Hasher                   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > using __LinkedHashMapFindUniqueClient =   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __LocalFindUniqueMutablePrimitiveClient <
                            cds :: LinkedHashMap <
                                    __KeyType,
                                    __ValueType,
                                    __Hasher
                            >,
                            __KeyType,
                            __LinkedHashMapIterator < __KeyType, __ValueType, __Hasher >
                    >;


            template <
                    typename __KeyType,                     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ValueType,                   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __Hasher                       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > using __LinkedHashMapFindUniqueConstClient =  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __LocalFindUniqueImmutablePrimitiveClient <
                            cds :: LinkedHashMap <
                                    __KeyType,
                                    __ValueType,
                                    __Hasher
                            >,
                            __KeyType,
                            __LinkedHashMapConstIterator < __KeyType, __ValueType, __Hasher >
                    >;


            template <
                    typename __KeyType,                         /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ValueType,                       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __Hasher                           /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > using __LinkedHashMapRemoveOfCollectionClient =   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __LocalRemoveOfCompositeClient <
                            cds :: LinkedHashMap <
                                    __KeyType,
                                    __ValueType,
                                    __Hasher
                            >,
                            typename Map < __KeyType, __ValueType > :: EntryType,
                            cds :: Collection < typename Map < __KeyType, __ValueType > :: EntryType >,
                            & __collectionContains < typename Map < __KeyType, __ValueType > :: EntryType >
                    >;


            template <
                    typename __KeyType,                             /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ValueType,                           /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __Hasher                               /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > using __LinkedHashMapRemoveOfInitializerListClient =  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __LocalRemoveOfCompositeClient <
                            cds :: LinkedHashMap <
                                    __KeyType,
                                    __ValueType,
                                    __Hasher
                            >,
                            typename Map < __KeyType, __ValueType > :: EntryType,
                            std :: initializer_list < typename Map < __KeyType, __ValueType > :: EntryType >,
                            & __initializerListContains < typename Map < __KeyType, __ValueType > :: EntryType, & __linkedHashMapEquals < __KeyType, __ValueType > >
            >;


            template <
                    typename __KeyType,             /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ValueType,           /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __Hasher               /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > using __LinkedHashMapRemoveByClient = /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __LocalRemoveByCompositeClient <
                            cds :: LinkedHashMap <
                                    __KeyType,
                                    __ValueType,
                                    __Hasher
                            >,
                            typename Map < __KeyType, __ValueType > :: EntryType
                    >;


            template <
                    typename __KeyType,                         /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ValueType,                       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __Hasher                           /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > using __LinkedHashMapGenericStatementsClient =    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __LocalGenericMutableStatementsCompositeClient <
                            cds :: LinkedHashMap <
                                    __KeyType,
                                    __ValueType,
                                    __Hasher
                            >,
                            typename Map < __KeyType, __ValueType > :: EntryType
                    >;


            template <
                    typename __KeyType,                             /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ValueType,                           /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __Hasher                               /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > using __LinkedHashMapConstGenericStatementsClient =   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __LocalGenericImmutableStatementsCompositeClient <
                            cds :: LinkedHashMap <
                                    __KeyType,
                                    __ValueType,
                                    __Hasher
                            >,
                            typename Map < __KeyType, __ValueType > :: EntryType
                    >;


            template <
                    typename __KeyType,                         /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ValueType,                       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __Hasher                           /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > using __LinkedHashMapContainsOfCollectionClient = /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __LocalContainsOfCompositeClient <
                            cds :: LinkedHashMap <
                                    __KeyType,
                                    __ValueType,
                                    __Hasher
                            >,
                            typename Map < __KeyType, __ValueType > :: EntryType,
                            cds :: Collection < typename Map < __KeyType, __ValueType > :: EntryType >,
                            __collectionContains < typename Map < __KeyType, __ValueType > :: EntryType >
                    >;


            template <
                    typename __KeyType,                                 /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ValueType,                               /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __Hasher                                   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > using __LinkedHashMapContainsOfInitializerListClient =    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __LocalContainsOfCompositeClient <
                            cds :: LinkedHashMap <
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
                    typename __KeyType,                             /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ValueType,                           /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __Hasher                               /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > using __LinkedHashMapDelegateForwardIterableClient =  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __LocalDelegateForwardIterablePrimitiveClient <
                            cds :: LinkedHashMap < __KeyType, __ValueType, __Hasher >,
                            __LinkedHashMapIterator < __KeyType, __ValueType, __Hasher >
                    >;


            template <
                    typename __KeyType,                                 /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ValueType,                               /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __Hasher                                   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > using __LinkedHashMapDelegateForwardConstIterableClient = /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __LocalDelegateForwardConstIterablePrimitiveClient <
                            cds :: LinkedHashMap < __KeyType, __ValueType, __Hasher >,
                            __LinkedHashMapConstIterator < __KeyType, __ValueType, __Hasher >
                    >;

        } /* namespace __impl */
    } /* namespace __hidden */
} /* namespace cds */

#endif /* __CDS_LINKED_HASH_MAP_CONSTRUCTS_HPP__ */
