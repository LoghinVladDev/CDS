/* NOLINT(llvm-header-guard)
 * Created by loghin on 09/10/22.
 */

#ifndef __CDS_LINKED_HASH_MAP_ENTRY_MUTABLE_COLLECTION_PROXY_HPP__ /* NOLINT(llvm-header-guard) */
#define __CDS_LINKED_HASH_MAP_ENTRY_MUTABLE_COLLECTION_PROXY_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

namespace cds { /* NOLINT(modernize-concat-nested-namespaces) */

    namespace __hidden {    /* NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        namespace __impl {  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            template <
                    typename __ServerType,                          /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __KeyType,                             /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ValueType,                           /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __Hasher,                              /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __LinkedHashMap =                      /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                            cds :: LinkedHashMap <                  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                                    __KeyType,
                                    __ValueType,
                                    __Hasher
                            >
            > using __LinkedHashMapEntryProxyServer =               /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __MutableCollectionServer <
                            __ServerType,
                            typename __LinkedHashMap :: EntryType
                    >;


            template <
                    typename __ServerType,                              /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __KeyType,                                 /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ValueType,                               /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __Hasher,                                  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __LinkedHashMap =                          /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                            cds :: LinkedHashMap <
                                    __KeyType,
                                    __ValueType,
                                    __Hasher
                            >
            > using __LinkedHashMapEntryProxyRandomInsertionClient =    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __LocalRandomInsertionPrimitiveClient <
                            __ServerType,
                            typename __LinkedHashMap :: EntryType,
                            typename __LinkedHashMap :: EntryType
                    >;


            template <
                    typename __ServerType,                          /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __KeyType,                             /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ValueType,                           /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __Hasher,                              /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __LinkedHashMap =                      /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                            LinkedHashMap <
                                    __KeyType,
                                    __ValueType,
                                    __Hasher
                            >
            > using __LinkedHashMapEntryProxyIteratorRemoveClient = /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __LocalIteratorRemovePrimitiveClient <
                            __ServerType,
                            typename __LinkedHashMap :: EntryType,
                            __LinkedHashMapIterator < __KeyType, __ValueType, __Hasher >
                    >;


            template <
                    typename __ServerType,                                  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __KeyType,                                     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ValueType,                                   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __Hasher,                                      /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __LinkedHashMap =                              /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                            LinkedHashMap <
                                    __KeyType,
                                    __ValueType,
                                    __Hasher
                            >
            > using __LinkedHashMapEntryProxyConstIteratorRemoveClient =    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __LocalConstIteratorRemovePrimitiveClient <
                            __ServerType,
                            typename __LinkedHashMap :: EntryType,
                            __LinkedHashMapConstIterator < __KeyType, __ValueType, __Hasher >
                    >;


            template <
                    typename __ServerType,                              /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __KeyType,                                 /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ValueType,                               /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __Hasher,                                  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __LinkedHashMap =                          /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                            LinkedHashMap <
                                    __KeyType,
                                    __ValueType,
                                    __Hasher
                            >
            > using __LinkedHashMapEntryProxyFindOfCollectionClient =   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __LocalFindOfMutableCompositeClient <
                            __ServerType,
                            typename __LinkedHashMap :: EntryType,
                            __LinkedHashMapIterator < __KeyType, __ValueType, __Hasher >,
                            cds :: Collection < typename __LinkedHashMap :: EntryType >,
                            & __collectionContains < typename __LinkedHashMap :: EntryType >,
                            & __collectionNotContains < typename __LinkedHashMap :: EntryType >
                    >;


            template <
                    typename __ServerType,                                  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __KeyType,                                     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ValueType,                                   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __Hasher,                                      /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __LinkedHashMap =                              /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                            LinkedHashMap <
                                    __KeyType,
                                    __ValueType,
                                    __Hasher
                            >
            > using __LinkedHashMapEntryProxyFindOfConstCollectionClient =  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __LocalFindOfImmutableCompositeClient <
                            __ServerType,
                            typename __LinkedHashMap :: EntryType,
                            __LinkedHashMapConstIterator < __KeyType, __ValueType, __Hasher >,
                            cds :: Collection < typename __LinkedHashMap :: EntryType >,
                            & __collectionContains < typename __LinkedHashMap :: EntryType >,
                            & __collectionNotContains < typename __LinkedHashMap :: EntryType >
                    >;


            template <
                    typename __ServerType,                                  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __KeyType,                                     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ValueType,                                   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __Hasher,                                      /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __LinkedHashMap =                              /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                            LinkedHashMap <
                                    __KeyType,
                                    __ValueType,
                                    __Hasher
                            >
            > using __LinkedHashMapEntryProxyFindOfInitializerListClient =  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __LocalFindOfMutableCompositeClient <
                            __ServerType,
                            typename __LinkedHashMap :: EntryType,
                            __LinkedHashMapIterator < __KeyType, __ValueType, __Hasher >,
                            std :: initializer_list < typename __LinkedHashMap :: EntryType >,
                            & __initializerListContains < typename __LinkedHashMap :: EntryType, & cds :: meta :: equals < typename __LinkedHashMap :: EntryType > >,
                            & __initializerListNotContains < typename __LinkedHashMap :: EntryType, & cds :: meta :: equals < typename __LinkedHashMap :: EntryType > >
                    >;


            template <
                    typename __ServerType,                                      /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __KeyType,                                         /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ValueType,                                       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __Hasher,                                          /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __LinkedHashMap =                                  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                            LinkedHashMap <
                                    __KeyType,
                                    __ValueType,
                                    __Hasher
                            >
            > using __LinkedHashMapEntryProxyFindOfConstInitializerListClient = /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __LocalFindOfImmutableCompositeClient <
                            __ServerType,
                            typename __LinkedHashMap :: EntryType,
                            __LinkedHashMapConstIterator < __KeyType, __ValueType, __Hasher >,
                            std :: initializer_list < typename __LinkedHashMap :: EntryType >,
                            & __initializerListContains < typename __LinkedHashMap :: EntryType, & cds :: meta :: equals < typename __LinkedHashMap :: EntryType > >,
                            & __initializerListNotContains < typename __LinkedHashMap :: EntryType, & cds :: meta :: equals < typename __LinkedHashMap :: EntryType > >
                    >;


            template <
                    typename __ServerType,                  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __KeyType,                     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ValueType,                   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __Hasher,                      /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __LinkedHashMap =              /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                            LinkedHashMap <
                                    __KeyType,
                                    __ValueType,
                                    __Hasher
                            >
            > using __LinkedHashMapEntryProxyFindByClient = /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __LocalFindByMutableCompositeClient <
                            __ServerType,
                            typename __LinkedHashMap :: EntryType,
                            __LinkedHashMapIterator < __KeyType, __ValueType, __Hasher >
                    >;


            template <
                    typename __ServerType,                          /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __KeyType,                             /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ValueType,                           /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __Hasher,                              /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __LinkedHashMap =                      /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                            LinkedHashMap <
                                    __KeyType,
                                    __ValueType,
                                    __Hasher
                            >
            > using __LinkedHashMapEntryProxyConstFindByClient =    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __LocalFindByImmutableCompositeClient <
                            __ServerType,
                            typename __LinkedHashMap :: EntryType,
                            __LinkedHashMapConstIterator < __KeyType, __ValueType, __Hasher >
                    >;


            template <
                    typename __ServerType,                              /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __KeyType,                                 /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ValueType,                               /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __Hasher,                                  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __LinkedHashMap =                          /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                            LinkedHashMap <
                                    __KeyType,
                                    __ValueType,
                                    __Hasher
                            >
            > using __LinkedHashMapEntryProxyRemoveOfCollectionClient = /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __LocalRemoveOfCompositeClient <
                            __ServerType,
                            typename __LinkedHashMap :: EntryType,
                            cds :: Collection < typename __LinkedHashMap :: EntryType >,
                            & __collectionContains < typename __LinkedHashMap :: EntryType >
                    >;


            template <
                    typename __ServerType,                                      /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __KeyType,                                         /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ValueType,                                       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __Hasher,                                          /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __LinkedHashMap =                                  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                            LinkedHashMap <
                                    __KeyType,
                                    __ValueType,
                                    __Hasher
                            >
            > using __LinkedHashMapEntryProxyRemoveOfInitializerListClient =    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __LocalRemoveOfCompositeClient <
                            __ServerType,
                            typename __LinkedHashMap :: EntryType,
                            std :: initializer_list < typename __LinkedHashMap :: EntryType >,
                            & __initializerListContains < typename __LinkedHashMap :: EntryType, & cds :: meta :: equals < typename __LinkedHashMap :: EntryType > >
                    >;


            template <
                    typename __ServerType,                      /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __KeyType,                         /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ValueType,                       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __Hasher,                          /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __LinkedHashMap =                  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                            LinkedHashMap <
                                    __KeyType,
                                    __ValueType,
                                    __Hasher
                            >
            > using __LinkedHashMapEntryProxyRemoveByClient =   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __LocalRemoveByCompositeClient <
                            __ServerType,
                            typename __LinkedHashMap :: EntryType
                    >;


            template <
                    typename __ServerType,                              /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __KeyType,                                 /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ValueType,                               /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __Hasher,                                  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __LinkedHashMap =                          /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                            LinkedHashMap <
                                    __KeyType,
                                    __ValueType,
                                    __Hasher
                            >
            > using __LinkedHashMapEntryProxyGenericStatementsClient =  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __LocalGenericMutableStatementsCompositeClient <
                            __ServerType,
                            typename __LinkedHashMap :: EntryType
                    >;


            template <
                    typename __ServerType,                                  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __KeyType,                                     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ValueType,                                   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __Hasher,                                      /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __LinkedHashMap =                              /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                            LinkedHashMap <
                                    __KeyType,
                                    __ValueType,
                                    __Hasher
                            >
            > using __LinkedHashMapEntryProxyConstGenericStatementsClient = /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __LocalGenericImmutableStatementsCompositeClient <
                            __ServerType,
                            typename __LinkedHashMap :: EntryType
                    >;


            template <
                    typename __ServerType,                                  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __KeyType,                                     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ValueType,                                   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __Hasher,                                      /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __LinkedHashMap =                              /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                            LinkedHashMap <
                                    __KeyType,
                                    __ValueType,
                                    __Hasher
                            >
            > using __LinkedHashMapEntryProxyContainsOfCollectionClient =   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __LocalContainsOfCompositeClient <
                            __ServerType,
                            typename __LinkedHashMap :: EntryType,
                            cds :: Collection < typename __LinkedHashMap :: EntryType >,
                            __collectionContains < typename __LinkedHashMap :: EntryType >
                    >;


            template <
                    typename __ServerType,                                      /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __KeyType,                                         /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ValueType,                                       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __Hasher,                                          /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __LinkedHashMap =                                  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                            LinkedHashMap <
                                    __KeyType,
                                    __ValueType,
                                    __Hasher
                            >
            > using __LinkedHashMapEntryProxyContainsOfInitializerListClient =  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __LocalContainsOfCompositeClient <
                            __ServerType,
                            typename __LinkedHashMap :: EntryType,
                            std :: initializer_list < typename __LinkedHashMap :: EntryType >,
                            __initializerListContains <
                                    typename __LinkedHashMap :: EntryType,
                                    & cds :: meta :: equals < typename __LinkedHashMap :: EntryType >
                            >
                    >;


            template <
                    typename __ServerType,                                      /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __KeyType,                                         /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ValueType,                                       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __Hasher                                           /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > using __LinkedHashMapEntryProxyDelegateForwardIterableClient =    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __LocalDelegateForwardIterablePrimitiveClient <
                            __ServerType,
                            __LinkedHashMapIterator < __KeyType, __ValueType, __Hasher >
                    >;


            template <
                    typename __ServerType,                                          /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __KeyType,                                             /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ValueType,                                           /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __Hasher                                               /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > using __LinkedHashMapEntryProxyDelegateForwardConstIterableClient =   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __LocalDelegateForwardConstIterablePrimitiveClient <
                            __ServerType,
                            __LinkedHashMapConstIterator < __KeyType, __ValueType, __Hasher >
                    >;

        } /* namespace __impl */
    } /* namespace __hidden */

    template <
            typename __KeyType,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __ValueType,   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __Hasher       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    > class __CDS_InheritsEBOs LinkedHashMap <
            __KeyType,
            __ValueType,
            __Hasher
    > :: EntryMutableCollectionProxy :
            public LinkedHashMap < __KeyType, __ValueType, __Hasher > :: AbstractEntryMutableCollectionProxy,
            protected __hidden :: __impl :: __LinkedHashMapEntryProxyServer < EntryMutableCollectionProxy, __KeyType, __ValueType, __Hasher >,
            public __hidden :: __impl :: __LinkedHashMapEntryProxyRandomInsertionClient < EntryMutableCollectionProxy, __KeyType, __ValueType, __Hasher >,
            public __hidden :: __impl :: __LinkedHashMapEntryProxyIteratorRemoveClient < EntryMutableCollectionProxy, __KeyType, __ValueType, __Hasher >,
            public __hidden :: __impl :: __LinkedHashMapEntryProxyConstIteratorRemoveClient < EntryMutableCollectionProxy, __KeyType, __ValueType, __Hasher >,
            public __hidden :: __impl :: __LinkedHashMapEntryProxyFindOfCollectionClient < EntryMutableCollectionProxy, __KeyType, __ValueType, __Hasher >,
            public __hidden :: __impl :: __LinkedHashMapEntryProxyFindOfConstCollectionClient < EntryMutableCollectionProxy, __KeyType, __ValueType, __Hasher >,
            public __hidden :: __impl :: __LinkedHashMapEntryProxyFindOfInitializerListClient < EntryMutableCollectionProxy, __KeyType, __ValueType, __Hasher >,
            public __hidden :: __impl :: __LinkedHashMapEntryProxyFindOfConstInitializerListClient < EntryMutableCollectionProxy, __KeyType, __ValueType, __Hasher >,
            public __hidden :: __impl :: __LinkedHashMapEntryProxyFindByClient < EntryMutableCollectionProxy, __KeyType, __ValueType, __Hasher >,
            public __hidden :: __impl :: __LinkedHashMapEntryProxyConstFindByClient < EntryMutableCollectionProxy, __KeyType, __ValueType, __Hasher >,
            public __hidden :: __impl :: __LinkedHashMapEntryProxyRemoveOfCollectionClient < EntryMutableCollectionProxy, __KeyType, __ValueType, __Hasher >,
            public __hidden :: __impl :: __LinkedHashMapEntryProxyRemoveOfInitializerListClient < EntryMutableCollectionProxy, __KeyType, __ValueType, __Hasher >,
            public __hidden :: __impl :: __LinkedHashMapEntryProxyRemoveByClient < EntryMutableCollectionProxy, __KeyType, __ValueType, __Hasher >,
            public __hidden :: __impl :: __LinkedHashMapEntryProxyGenericStatementsClient < EntryMutableCollectionProxy, __KeyType, __ValueType, __Hasher >,
            public __hidden :: __impl :: __LinkedHashMapEntryProxyConstGenericStatementsClient < EntryMutableCollectionProxy, __KeyType, __ValueType, __Hasher >,
            public __hidden :: __impl :: __LinkedHashMapEntryProxyContainsOfCollectionClient < EntryMutableCollectionProxy, __KeyType, __ValueType, __Hasher >,
            public __hidden :: __impl :: __LinkedHashMapEntryProxyContainsOfInitializerListClient < EntryMutableCollectionProxy, __KeyType, __ValueType, __Hasher >,
            public __hidden :: __impl :: __LinkedHashMapEntryProxyDelegateForwardIterableClient < EntryMutableCollectionProxy, __KeyType, __ValueType, __Hasher >,
            public __hidden :: __impl :: __LinkedHashMapEntryProxyDelegateForwardConstIterableClient < EntryMutableCollectionProxy, __KeyType, __ValueType, __Hasher > {

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using LinkedHashMapBase                     = LinkedHashMap < __KeyType, __ValueType, __Hasher >;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using Server                                = __hidden :: __impl :: __LinkedHashMapEntryProxyServer < EntryMutableCollectionProxy, __KeyType, __ValueType, __Hasher >;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using RandomInsertionClient                 = __hidden :: __impl :: __LinkedHashMapEntryProxyRandomInsertionClient < EntryMutableCollectionProxy, __KeyType, __ValueType, __Hasher >;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using IteratorRemoveClient                  = __hidden :: __impl :: __LinkedHashMapEntryProxyIteratorRemoveClient < EntryMutableCollectionProxy, __KeyType, __ValueType, __Hasher >;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using ConstIteratorRemoveClient             = __hidden :: __impl :: __LinkedHashMapEntryProxyConstIteratorRemoveClient < EntryMutableCollectionProxy, __KeyType, __ValueType, __Hasher >;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using FindOfCollectionClient                = __hidden :: __impl :: __LinkedHashMapEntryProxyFindOfCollectionClient < EntryMutableCollectionProxy, __KeyType, __ValueType, __Hasher >;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using ConstFindOfCollectionClient           = __hidden :: __impl :: __LinkedHashMapEntryProxyFindOfConstCollectionClient < EntryMutableCollectionProxy, __KeyType, __ValueType, __Hasher >;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using FindOfInitializerListClient           = __hidden :: __impl :: __LinkedHashMapEntryProxyFindOfInitializerListClient < EntryMutableCollectionProxy, __KeyType, __ValueType, __Hasher >;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using ConstFindOfInitializerListClient      = __hidden :: __impl :: __LinkedHashMapEntryProxyFindOfConstInitializerListClient < EntryMutableCollectionProxy, __KeyType, __ValueType, __Hasher >;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using FindByClient                          = __hidden :: __impl :: __LinkedHashMapEntryProxyFindByClient < EntryMutableCollectionProxy, __KeyType, __ValueType, __Hasher >;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using ConstFindByClient                     = __hidden :: __impl :: __LinkedHashMapEntryProxyConstFindByClient < EntryMutableCollectionProxy, __KeyType, __ValueType, __Hasher >;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using RemoveOfCollectionClient              = __hidden :: __impl :: __LinkedHashMapEntryProxyRemoveOfCollectionClient < EntryMutableCollectionProxy, __KeyType, __ValueType, __Hasher >;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using RemoveOfInitializerListClient         = __hidden :: __impl :: __LinkedHashMapEntryProxyRemoveOfInitializerListClient < EntryMutableCollectionProxy, __KeyType, __ValueType, __Hasher >;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using RemoveByClient                        = __hidden :: __impl :: __LinkedHashMapEntryProxyRemoveByClient < EntryMutableCollectionProxy, __KeyType, __ValueType, __Hasher >;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using GenericStatementsClient               = __hidden :: __impl :: __LinkedHashMapEntryProxyGenericStatementsClient < EntryMutableCollectionProxy, __KeyType, __ValueType, __Hasher >;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using ContainsOfCollectionClient            = __hidden :: __impl :: __LinkedHashMapEntryProxyContainsOfCollectionClient < EntryMutableCollectionProxy, __KeyType, __ValueType, __Hasher >;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using ContainsOfInitializerListClient       = __hidden :: __impl :: __LinkedHashMapEntryProxyContainsOfInitializerListClient < EntryMutableCollectionProxy, __KeyType, __ValueType, __Hasher >;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using ConstGenericStatementsClient          = __hidden :: __impl :: __LinkedHashMapEntryProxyConstGenericStatementsClient < EntryMutableCollectionProxy, __KeyType, __ValueType, __Hasher >;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using DelegateForwardIterableClient         = __hidden :: __impl :: __LinkedHashMapEntryProxyDelegateForwardIterableClient < EntryMutableCollectionProxy, __KeyType, __ValueType, __Hasher >;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using DelegateForwardConstIterableClient    = __hidden :: __impl :: __LinkedHashMapEntryProxyDelegateForwardConstIterableClient < EntryMutableCollectionProxy, __KeyType, __ValueType, __Hasher >;


    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using typename AbstractEntryMutableCollectionProxy :: __GenericHandler;         /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using typename AbstractEntryMutableCollectionProxy :: __GenericConstHandler;    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */


    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using EntryType     = typename cds :: Map < __KeyType, __ValueType > :: EntryType;


    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using typename DelegateForwardIterableClient :: Iterator;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using typename DelegateForwardConstIterableClient :: ConstIterator;


    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        friend Server;

    private:    /* NOLINT(readability-redundant-access-specifiers) */
        friend DelegateForwardIterableClient;

    private:    /* NOLINT(readability-redundant-access-specifiers) */
        friend DelegateForwardConstIterableClient;


    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using DelegateForwardIterableClient :: begin;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using DelegateForwardIterableClient :: end;


    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using DelegateForwardConstIterableClient :: begin;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using DelegateForwardConstIterableClient :: end;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using DelegateForwardConstIterableClient :: cbegin;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using DelegateForwardConstIterableClient :: cend;


    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using RemoveByClient :: removeThat;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using RemoveByClient :: removeFirstThat;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using RemoveByClient :: removeLastThat;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using RemoveByClient :: removeAllThat;


    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using GenericStatementsClient :: forEach;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using GenericStatementsClient :: some;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using GenericStatementsClient :: atLeast;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using GenericStatementsClient :: atMost;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using GenericStatementsClient :: moreThan;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using GenericStatementsClient :: fewerThan;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using GenericStatementsClient :: count;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using GenericStatementsClient :: any;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using GenericStatementsClient :: all;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using GenericStatementsClient :: none;


    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using ConstGenericStatementsClient :: forEach;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using ConstGenericStatementsClient :: some;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using ConstGenericStatementsClient :: atLeast;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using ConstGenericStatementsClient :: atMost;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using ConstGenericStatementsClient :: moreThan;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using ConstGenericStatementsClient :: fewerThan;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using ConstGenericStatementsClient :: count;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using ConstGenericStatementsClient :: any;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using ConstGenericStatementsClient :: all;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using ConstGenericStatementsClient :: none;


    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using RemoveOfCollectionClient :: removeOf;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using RemoveOfCollectionClient :: removeFirstOf;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using RemoveOfCollectionClient :: removeLastOf;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using RemoveOfCollectionClient :: removeAllOf;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using RemoveOfCollectionClient :: removeNotOf;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using RemoveOfCollectionClient :: removeFirstNotOf;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using RemoveOfCollectionClient :: removeLastNotOf;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using RemoveOfCollectionClient :: removeAllNotOf;


    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using RemoveOfInitializerListClient :: removeOf;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using RemoveOfInitializerListClient :: removeFirstOf;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using RemoveOfInitializerListClient :: removeLastOf;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using RemoveOfInitializerListClient :: removeAllOf;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using RemoveOfInitializerListClient :: removeNotOf;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using RemoveOfInitializerListClient :: removeFirstNotOf;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using RemoveOfInitializerListClient :: removeLastNotOf;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using RemoveOfInitializerListClient :: removeAllNotOf;


    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using ContainsOfCollectionClient :: containsAnyOf;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using ContainsOfCollectionClient :: containsAnyNotOf;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using ContainsOfCollectionClient :: containsAllOf;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using ContainsOfCollectionClient :: containsNoneOf;


    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using ContainsOfInitializerListClient :: containsAnyOf;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using ContainsOfInitializerListClient :: containsAnyNotOf;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using ContainsOfInitializerListClient :: containsAllOf;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using ContainsOfInitializerListClient :: containsNoneOf;


    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using FindByClient :: findThat;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using FindByClient :: findFirstThat;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using FindByClient :: findLastThat;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using FindByClient :: findAllThat;


    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using FindOfCollectionClient :: findOf;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using FindOfCollectionClient :: findFirstOf;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using FindOfCollectionClient :: findLastOf;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using FindOfCollectionClient :: findAllOf;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using FindOfCollectionClient :: findNotOf;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using FindOfCollectionClient :: findFirstNotOf;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using FindOfCollectionClient :: findLastNotOf;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using FindOfCollectionClient :: findAllNotOf;


    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using FindOfInitializerListClient :: findOf;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using FindOfInitializerListClient :: findFirstOf;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using FindOfInitializerListClient :: findLastOf;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using FindOfInitializerListClient :: findAllOf;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using FindOfInitializerListClient :: findNotOf;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using FindOfInitializerListClient :: findFirstNotOf;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using FindOfInitializerListClient :: findLastNotOf;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using FindOfInitializerListClient :: findAllNotOf;


    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using ConstFindByClient :: findThat;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using ConstFindByClient :: findFirstThat;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using ConstFindByClient :: findLastThat;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using ConstFindByClient :: findAllThat;


    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using ConstFindOfCollectionClient :: findOf;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using ConstFindOfCollectionClient :: findFirstOf;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using ConstFindOfCollectionClient :: findLastOf;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using ConstFindOfCollectionClient :: findAllOf;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using ConstFindOfCollectionClient :: findNotOf;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using ConstFindOfCollectionClient :: findFirstNotOf;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using ConstFindOfCollectionClient :: findLastNotOf;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using ConstFindOfCollectionClient :: findAllNotOf;


    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using ConstFindOfInitializerListClient :: findOf;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using ConstFindOfInitializerListClient :: findFirstOf;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using ConstFindOfInitializerListClient :: findLastOf;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using ConstFindOfInitializerListClient :: findAllOf;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using ConstFindOfInitializerListClient :: findNotOf;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using ConstFindOfInitializerListClient :: findFirstNotOf;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using ConstFindOfInitializerListClient :: findLastNotOf;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using ConstFindOfInitializerListClient :: findAllNotOf;


    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using RandomInsertionClient :: add;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using RandomInsertionClient :: addAll;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using RandomInsertionClient :: addAllOf;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using RandomInsertionClient :: insert;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using RandomInsertionClient :: insertAll;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using RandomInsertionClient :: insertAllOf;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using RandomInsertionClient :: emplace;


    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using IteratorRemoveClient :: remove;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using ConstIteratorRemoveClient :: remove;


    private:    /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto __cicch_obtainGenericHandler ( /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                __hidden :: __impl :: __CollectionInternalRequestType requestType
        ) noexcept -> __GenericHandler override;

    private:    /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto __cicch_obtainGenericConstHandler (    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                __hidden :: __impl :: __CollectionInternalRequestType requestType
        ) const noexcept -> __GenericConstHandler override;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_Explicit constexpr EntryMutableCollectionProxy (
                LinkedHashMap < __KeyType, __ValueType, __Hasher > * pMap
        ) noexcept;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        EntryMutableCollectionProxy (
                EntryMutableCollectionProxy const &
        ) noexcept = delete;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        EntryMutableCollectionProxy (
                EntryMutableCollectionProxy &&
        ) noexcept = delete;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_cpplang_ConstexprDestructor ~EntryMutableCollectionProxy() noexcept override;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        auto operator = (
                EntryMutableCollectionProxy const &
        ) noexcept -> EntryMutableCollectionProxy & = delete;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        auto operator = (
                EntryMutableCollectionProxy &&
        ) noexcept -> EntryMutableCollectionProxy & = delete;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto contains ( /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                EntryType const & entry
        ) const noexcept -> bool override;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        static auto __newAddress ( /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                EntryMutableCollectionProxy       * pObject,
                EntryType                   const * pReferenceElement,
                bool                              * pIsNew
        ) noexcept -> EntryType *;

    private:    /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard static auto __begin (
                EntryMutableCollectionProxy * pObject
        ) noexcept -> __hidden :: __impl :: __AbstractDelegateIterator < EntryType > *; /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

    private:    /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard static auto __end (
                EntryMutableCollectionProxy * pObject
        ) noexcept -> __hidden :: __impl :: __AbstractDelegateIterator < EntryType > *; /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

    private:    /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard static auto __cbegin (
                EntryMutableCollectionProxy const * pObject
        ) noexcept -> __hidden :: __impl :: __AbstractDelegateIterator < EntryType const > *; /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, modernize-use-nodiscard) */

    private:    /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard static auto __cend (
                EntryMutableCollectionProxy const * pObject
        ) noexcept -> __hidden :: __impl :: __AbstractDelegateIterator < EntryType const > *; /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, modernize-use-nodiscard) */

    private:    /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction static auto __beginLocal (
                EntryMutableCollectionProxy * pObject
        ) noexcept -> Iterator; /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

    private:    /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction static auto __endLocal (
                EntryMutableCollectionProxy * pObject
        ) noexcept -> Iterator; /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

    private:    /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard constexpr static auto __cbeginLocal (
                EntryMutableCollectionProxy const * pObject
        ) noexcept -> ConstIterator; /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, modernize-use-nodiscard) */

    private:    /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard constexpr static auto __cendLocal (
                EntryMutableCollectionProxy const * pObject
        ) noexcept -> ConstIterator; /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, modernize-use-nodiscard) */

    private:  /* NOLINT(readability-redundant-access-specifiers) */
        static auto __remove ( /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                EntryMutableCollectionProxy       * pObject,
                Iterator                    const * iterator
        ) noexcept -> bool;

    private:  /* NOLINT(readability-redundant-access-specifiers) */
        static auto __removeConst (    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                EntryMutableCollectionProxy       * pObject,
                ConstIterator               const * iterator
        ) noexcept -> bool;

    private:  /* NOLINT(readability-redundant-access-specifiers) */
        static auto __removeArray ( /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                EntryMutableCollectionProxy               * pObject,
                Iterator                    const * const * ppIterators,
                Size                                        iteratorArrayCount
        ) noexcept -> Size;

    private:  /* NOLINT(readability-redundant-access-specifiers) */
        static auto __removeConstArray (    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                EntryMutableCollectionProxy               * pObject,
                ConstIterator               const * const * ppIterators,
                Size                                        iteratorArrayCount
        ) noexcept -> Size;

    private:    /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard auto __equals ( /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                EntryMutableCollectionProxy const & set
        ) const noexcept -> bool;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard auto operator == (
                EntryMutableCollectionProxy const & set
        ) const noexcept -> bool;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard auto operator != (
                EntryMutableCollectionProxy const & set
        ) const noexcept -> bool;
    };

} /* namespace cds */

#endif /* __CDS_LINKED_HASH_MAP_ENTRY_MUTABLE_COLLECTION_PROXY_HPP__ */
