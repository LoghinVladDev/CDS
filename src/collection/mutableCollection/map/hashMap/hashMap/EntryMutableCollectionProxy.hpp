/* NOLINT(llvm-header-guard)
 * Created by loghin on 14/08/22.
 */

#ifndef __CDS_HASH_MAP_ENTRY_MUTABLE_COLLECTION_PROXY_HPP__ /* NOLINT(llvm-header-guard) */
#define __CDS_HASH_MAP_ENTRY_MUTABLE_COLLECTION_PROXY_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

namespace cds {             /* NOLINT(modernize-concat-nested-namespaces) */
    namespace __hidden {    /* NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        namespace __impl {  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            template <
                    typename __ServerType,                      /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __KeyType,                         /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ValueType,                       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __Hasher,                          /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __HashMap =                        /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                            cds :: HashMap <    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                                    __KeyType,
                                    __ValueType,
                                    __Hasher
                            >
            > using __HashMapEntryProxyServer =                 /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __MutableCollectionServer <
                            __ServerType,
                            typename __HashMap :: EntryType
                    >;


            template <
                    typename __ServerType,                      /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __KeyType,                         /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ValueType,                       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __Hasher,                          /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __HashMap =                        /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                            HashMap <
                                    __KeyType,
                                    __ValueType,
                                    __Hasher
                            >
            > using __HashMapEntryProxyRandomInsertionClient =  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __LocalRandomInsertionPrimitiveClient <
                            __ServerType,
                            typename __HashMap :: EntryType,
                            typename __HashMap :: EntryType
                    >;


            template <
                    typename __ServerType,                      /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __KeyType,                         /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ValueType,                       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __Hasher,                          /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __HashMap =                        /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                            HashMap <
                                    __KeyType,
                                    __ValueType,
                                    __Hasher
                            >
            > using __HashMapEntryProxyIteratorRemoveClient =   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __LocalIteratorRemovePrimitiveClient <
                            __ServerType,
                            typename __HashMap :: EntryType,
                            typename __HashMapImplementation < __KeyType, __ValueType, __Hasher > :: __ht_Iterator
                    >;


            template <
                    typename __ServerType,                      /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __KeyType,                         /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ValueType,                       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __Hasher,                          /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __HashMap =                        /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    HashMap <
                            __KeyType,
                            __ValueType,
                            __Hasher
                    >
            > using __HashMapEntryProxyConstIteratorRemoveClient =  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __LocalConstIteratorRemovePrimitiveClient <
                            __ServerType,
                            typename __HashMap :: EntryType,
                            typename __HashMapImplementation < __KeyType, __ValueType, __Hasher > :: __ht_ConstIterator
                    >;


            template <
                    typename __ServerType,                      /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __KeyType,                         /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ValueType,                       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __Hasher,                          /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __HashMap =                        /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    HashMap <
                            __KeyType,
                            __ValueType,
                            __Hasher
                    >
            > using __HashMapEntryProxyFindOfIterableClient =   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __LocalFindOfMutableCompositeClient <
                            __ServerType,
                            typename __HashMap :: EntryType,
                            typename __HashMapImplementation < __KeyType, __ValueType, __Hasher > :: __ht_Iterator,
                            cds :: Iterable < typename __HashMap :: EntryType >,
                            & __iterableContains < typename __HashMap :: EntryType >,
                            & __iterableNotContains < typename __HashMap :: EntryType >
                    >;


            template <
                    typename __ServerType,                      /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __KeyType,                         /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ValueType,                       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __Hasher,                          /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __HashMap =                        /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    HashMap <
                            __KeyType,
                            __ValueType,
                            __Hasher
                    >
            > using __HashMapEntryProxyFindOfConstIterableClient =  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __LocalFindOfImmutableCompositeClient <
                            __ServerType,
                            typename __HashMap :: EntryType,
                            typename __HashMapImplementation < __KeyType, __ValueType, __Hasher > :: __ht_ConstIterator,
                            cds :: Iterable < typename __HashMap :: EntryType >,
                            & __iterableContains < typename __HashMap :: EntryType >,
                            & __iterableNotContains < typename __HashMap :: EntryType >
                    >;


            template <
                    typename __ServerType,                      /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __KeyType,                         /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ValueType,                       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __Hasher,                          /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __HashMap =                        /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    HashMap <
                            __KeyType,
                            __ValueType,
                            __Hasher
                    >
            > using __HashMapEntryProxyFindOfInitializerListClient =    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __LocalFindOfMutableCompositeClient <
                            __ServerType,
                            typename __HashMap :: EntryType,
                            typename __HashMapImplementation < __KeyType, __ValueType, __Hasher > :: __ht_Iterator,
                            std :: initializer_list < typename __HashMap :: EntryType >,
                            & __initializerListContains < typename __HashMap :: EntryType, & cds :: meta :: equals < typename __HashMap :: EntryType > >,
                            & __initializerListNotContains < typename __HashMap :: EntryType, & cds :: meta :: equals < typename __HashMap :: EntryType > >
                    >;


            template <
                    typename __ServerType,                      /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __KeyType,                         /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ValueType,                       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __Hasher,                          /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __HashMap =                        /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    HashMap <
                            __KeyType,
                            __ValueType,
                            __Hasher
                    >
            > using __HashMapEntryProxyFindOfConstInitializerListClient =   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __LocalFindOfImmutableCompositeClient <
                            __ServerType,
                            typename __HashMap :: EntryType,
                            typename __HashMapImplementation < __KeyType, __ValueType, __Hasher > :: __ht_ConstIterator,
                            std :: initializer_list < typename __HashMap :: EntryType >,
                            & __initializerListContains < typename __HashMap :: EntryType, & cds :: meta :: equals < typename __HashMap :: EntryType > >,
                            & __initializerListNotContains < typename __HashMap :: EntryType, & cds :: meta :: equals < typename __HashMap :: EntryType > >
                    >;


            template <
                    typename __ServerType,                      /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __KeyType,                         /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ValueType,                       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __Hasher,                          /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __HashMap =                        /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    HashMap <
                            __KeyType,
                            __ValueType,
                            __Hasher
                    >
            > using __HashMapEntryProxyFindByClient =   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __LocalFindByMutableCompositeClient <
                            __ServerType,
                            typename __HashMap :: EntryType,
                            typename __HashMapImplementation < __KeyType, __ValueType, __Hasher > :: __ht_Iterator
                    >;


            template <
                    typename __ServerType,                      /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __KeyType,                         /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ValueType,                       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __Hasher,                          /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __HashMap =                        /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    HashMap <
                            __KeyType,
                            __ValueType,
                            __Hasher
                    >
            > using __HashMapEntryProxyConstFindByClient =  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __LocalFindByImmutableCompositeClient <
                            __ServerType,
                            typename __HashMap :: EntryType,
                            typename __HashMapImplementation < __KeyType, __ValueType, __Hasher > :: __ht_ConstIterator
                    >;


            template <
                    typename __ServerType,                      /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __KeyType,                         /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ValueType,                       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __Hasher,                          /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __HashMap =                        /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    HashMap <
                            __KeyType,
                            __ValueType,
                            __Hasher
                    >
            > using __HashMapEntryProxyRemoveOfIterableClient = /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __LocalRemoveOfCompositeClient <
                            __ServerType,
                            typename __HashMap :: EntryType,
                            cds :: Iterable < typename __HashMap :: EntryType >,
                            & __iterableContains < typename __HashMap :: EntryType >
                    >;


            template <
                    typename __ServerType,                      /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __KeyType,                         /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ValueType,                       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __Hasher,                          /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __HashMap =                        /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    HashMap <
                            __KeyType,
                            __ValueType,
                            __Hasher
                    >
            > using __HashMapEntryProxyRemoveOfInitializerListClient =  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __LocalRemoveOfCompositeClient <
                            __ServerType,
                            typename __HashMap :: EntryType,
                            std :: initializer_list < typename __HashMap :: EntryType >,
                            & __initializerListContains < typename __HashMap :: EntryType, & cds :: meta :: equals < typename __HashMap :: EntryType > >
                    >;


            template <
                    typename __ServerType,                      /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __KeyType,                         /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ValueType,                       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __Hasher,                          /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __HashMap =                        /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    HashMap <
                            __KeyType,
                            __ValueType,
                            __Hasher
                    >
            > using __HashMapEntryProxyRemoveByClient = /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __LocalRemoveByCompositeClient <
                            __ServerType,
                            typename __HashMap :: EntryType
                    >;


            template <
                    typename __ServerType,                      /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __KeyType,                         /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ValueType,                       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __Hasher,                          /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __HashMap =                        /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    HashMap <
                            __KeyType,
                            __ValueType,
                            __Hasher
                    >
            > using __HashMapEntryProxyGenericStatementsClient =    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __LocalGenericMutableStatementsCompositeClient <
                            __ServerType,
                            typename __HashMap :: EntryType
                    >;


            template <
                    typename __ServerType,                      /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __KeyType,                         /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ValueType,                       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __Hasher,                          /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __HashMap =                        /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    HashMap <
                            __KeyType,
                            __ValueType,
                            __Hasher
                    >
            > using __HashMapEntryProxyConstGenericStatementsClient =   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __LocalGenericImmutableStatementsCompositeClient <
                            __ServerType,
                            typename __HashMap :: EntryType
                    >;


            template <
                    typename __ServerType,                          /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __KeyType,                             /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ValueType,                           /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __Hasher,                              /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __HashMap =                            /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    HashMap <
                            __KeyType,
                            __ValueType,
                            __Hasher
                    >
            > using __HashMapEntryProxyContainsOfIterableClient =   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __LocalContainsOfCompositeClient <
                            __ServerType,
                            typename __HashMap :: EntryType,
                            cds :: Iterable < typename __HashMap :: EntryType >,
                            & __iterableContains < typename __HashMap :: EntryType >
                    >;


            template <
                    typename __ServerType,                                  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __KeyType,                                     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ValueType,                                   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __Hasher,                                      /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __HashMap =                                    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    HashMap <
                            __KeyType,
                            __ValueType,
                            __Hasher
                    >
            > using __HashMapEntryProxyContainsOfInitializerListClient =    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __LocalContainsOfCompositeClient <
                            __ServerType,
                            typename __HashMap :: EntryType,
                            std :: initializer_list < typename __HashMap :: EntryType >,
                            & __initializerListContains <
                                    typename __HashMap :: EntryType,
                                    & cds :: meta :: equals < typename __HashMap :: EntryType >
                            >
                    >;


            template <
                    typename __ServerType,                              /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __KeyType,                                 /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ValueType,                               /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __Hasher                                   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > using __HashMapEntryProxyDelegateForwardIterableClient =  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __LocalDelegateForwardIterablePrimitiveClient <
                            __ServerType,
                            typename __HashMapImplementation < __KeyType, __ValueType, __Hasher > :: __ht_Iterator
                    >;


            template <
                    typename __ServerType,                                  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __KeyType,                                     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ValueType,                                   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __Hasher                                       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > using __HashMapEntryProxyDelegateForwardConstIterableClient = /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __LocalDelegateForwardConstIterablePrimitiveClient <
                            __ServerType,
                            typename __HashMapImplementation < __KeyType, __ValueType, __Hasher > :: __ht_ConstIterator
                    >;

        } /* namespace __impl */
    } /* namespace __hidden */

    template <
            typename __KeyType,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __ValueType,   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __Hasher       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    > class __CDS_InheritsEBOs HashMap <
            __KeyType,
            __ValueType,
            __Hasher
    > :: EntryMutableCollectionProxy :
            public HashMap < __KeyType, __ValueType, __Hasher > :: AbstractEntryMutableCollectionProxy,
            protected __hidden :: __impl :: __HashMapEntryProxyServer < EntryMutableCollectionProxy, __KeyType, __ValueType, __Hasher >,
            public __hidden :: __impl :: __HashMapEntryProxyRandomInsertionClient < EntryMutableCollectionProxy, __KeyType, __ValueType, __Hasher >,
            public __hidden :: __impl :: __HashMapEntryProxyIteratorRemoveClient < EntryMutableCollectionProxy, __KeyType, __ValueType, __Hasher >,
            public __hidden :: __impl :: __HashMapEntryProxyConstIteratorRemoveClient < EntryMutableCollectionProxy, __KeyType, __ValueType, __Hasher >,
            public __hidden :: __impl :: __HashMapEntryProxyFindOfIterableClient < EntryMutableCollectionProxy, __KeyType, __ValueType, __Hasher >,
            public __hidden :: __impl :: __HashMapEntryProxyFindOfConstIterableClient < EntryMutableCollectionProxy, __KeyType, __ValueType, __Hasher >,
            public __hidden :: __impl :: __HashMapEntryProxyFindOfInitializerListClient < EntryMutableCollectionProxy, __KeyType, __ValueType, __Hasher >,
            public __hidden :: __impl :: __HashMapEntryProxyFindOfConstInitializerListClient < EntryMutableCollectionProxy, __KeyType, __ValueType, __Hasher >,
            public __hidden :: __impl :: __HashMapEntryProxyFindByClient < EntryMutableCollectionProxy, __KeyType, __ValueType, __Hasher >,
            public __hidden :: __impl :: __HashMapEntryProxyConstFindByClient < EntryMutableCollectionProxy, __KeyType, __ValueType, __Hasher >,
            public __hidden :: __impl :: __HashMapEntryProxyRemoveOfIterableClient < EntryMutableCollectionProxy, __KeyType, __ValueType, __Hasher >,
            public __hidden :: __impl :: __HashMapEntryProxyRemoveOfInitializerListClient < EntryMutableCollectionProxy, __KeyType, __ValueType, __Hasher >,
            public __hidden :: __impl :: __HashMapEntryProxyRemoveByClient < EntryMutableCollectionProxy, __KeyType, __ValueType, __Hasher >,
            public __hidden :: __impl :: __HashMapEntryProxyGenericStatementsClient < EntryMutableCollectionProxy, __KeyType, __ValueType, __Hasher >,
            public __hidden :: __impl :: __HashMapEntryProxyConstGenericStatementsClient < EntryMutableCollectionProxy, __KeyType, __ValueType, __Hasher >,
            public __hidden :: __impl :: __HashMapEntryProxyContainsOfIterableClient < EntryMutableCollectionProxy, __KeyType, __ValueType, __Hasher >,
            public __hidden :: __impl :: __HashMapEntryProxyContainsOfInitializerListClient < EntryMutableCollectionProxy, __KeyType, __ValueType, __Hasher >,
            public __hidden :: __impl :: __HashMapEntryProxyDelegateForwardIterableClient < EntryMutableCollectionProxy, __KeyType, __ValueType, __Hasher >,
            public __hidden :: __impl :: __HashMapEntryProxyDelegateForwardConstIterableClient < EntryMutableCollectionProxy, __KeyType, __ValueType, __Hasher > {

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using HashMapBase                           = HashMap < __KeyType, __ValueType, __Hasher >;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using Server                                = __hidden :: __impl :: __HashMapEntryProxyServer < EntryMutableCollectionProxy, __KeyType, __ValueType, __Hasher >;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using RandomInsertionClient                 = __hidden :: __impl :: __HashMapEntryProxyRandomInsertionClient < EntryMutableCollectionProxy, __KeyType, __ValueType, __Hasher >;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using IteratorRemoveClient                  = __hidden :: __impl :: __HashMapEntryProxyIteratorRemoveClient < EntryMutableCollectionProxy, __KeyType, __ValueType, __Hasher >;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using ConstIteratorRemoveClient             = __hidden :: __impl :: __HashMapEntryProxyConstIteratorRemoveClient < EntryMutableCollectionProxy, __KeyType, __ValueType, __Hasher >;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using FindOfIterableClient                  = __hidden :: __impl :: __HashMapEntryProxyFindOfIterableClient < EntryMutableCollectionProxy, __KeyType, __ValueType, __Hasher >;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using ConstFindOfIterableClient             = __hidden :: __impl :: __HashMapEntryProxyFindOfConstIterableClient < EntryMutableCollectionProxy, __KeyType, __ValueType, __Hasher >;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using FindOfInitializerListClient           = __hidden :: __impl :: __HashMapEntryProxyFindOfInitializerListClient < EntryMutableCollectionProxy, __KeyType, __ValueType, __Hasher >;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using ConstFindOfInitializerListClient      = __hidden :: __impl :: __HashMapEntryProxyFindOfConstInitializerListClient < EntryMutableCollectionProxy, __KeyType, __ValueType, __Hasher >;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using FindByClient                          = __hidden :: __impl :: __HashMapEntryProxyFindByClient < EntryMutableCollectionProxy, __KeyType, __ValueType, __Hasher >;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using ConstFindByClient                     = __hidden :: __impl :: __HashMapEntryProxyConstFindByClient < EntryMutableCollectionProxy, __KeyType, __ValueType, __Hasher >;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using RemoveOfIterableClient                = __hidden :: __impl :: __HashMapEntryProxyRemoveOfIterableClient < EntryMutableCollectionProxy, __KeyType, __ValueType, __Hasher >;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using RemoveOfInitializerListClient         = __hidden :: __impl :: __HashMapEntryProxyRemoveOfInitializerListClient < EntryMutableCollectionProxy, __KeyType, __ValueType, __Hasher >;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using RemoveByClient                        = __hidden :: __impl :: __HashMapEntryProxyRemoveByClient < EntryMutableCollectionProxy, __KeyType, __ValueType, __Hasher >;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using GenericStatementsClient               = __hidden :: __impl :: __HashMapEntryProxyGenericStatementsClient < EntryMutableCollectionProxy, __KeyType, __ValueType, __Hasher >;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using ContainsOfIterableClient              = __hidden :: __impl :: __HashMapEntryProxyContainsOfIterableClient < EntryMutableCollectionProxy, __KeyType, __ValueType, __Hasher >;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using ContainsOfInitializerListClient       = __hidden :: __impl :: __HashMapEntryProxyContainsOfInitializerListClient < EntryMutableCollectionProxy, __KeyType, __ValueType, __Hasher >;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using ConstGenericStatementsClient          = __hidden :: __impl :: __HashMapEntryProxyConstGenericStatementsClient < EntryMutableCollectionProxy, __KeyType, __ValueType, __Hasher >;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using DelegateForwardIterableClient         = __hidden :: __impl :: __HashMapEntryProxyDelegateForwardIterableClient < EntryMutableCollectionProxy, __KeyType, __ValueType, __Hasher >;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using DelegateForwardConstIterableClient    = __hidden :: __impl :: __HashMapEntryProxyDelegateForwardConstIterableClient < EntryMutableCollectionProxy, __KeyType, __ValueType, __Hasher >;


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
        using RemoveOfIterableClient :: removeOf;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using RemoveOfIterableClient :: removeFirstOf;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using RemoveOfIterableClient :: removeLastOf;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using RemoveOfIterableClient :: removeAllOf;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using RemoveOfIterableClient :: removeNotOf;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using RemoveOfIterableClient :: removeFirstNotOf;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using RemoveOfIterableClient :: removeLastNotOf;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using RemoveOfIterableClient :: removeAllNotOf;


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
        using ContainsOfIterableClient :: containsAnyOf;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using ContainsOfIterableClient :: containsAnyNotOf;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using ContainsOfIterableClient :: containsAllOf;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using ContainsOfIterableClient :: containsNoneOf;


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
        using FindOfIterableClient :: findOf;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using FindOfIterableClient :: findFirstOf;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using FindOfIterableClient :: findLastOf;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using FindOfIterableClient :: findAllOf;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using FindOfIterableClient :: findNotOf;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using FindOfIterableClient :: findFirstNotOf;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using FindOfIterableClient :: findLastNotOf;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using FindOfIterableClient :: findAllNotOf;


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
        using ConstFindOfIterableClient :: findOf;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using ConstFindOfIterableClient :: findFirstOf;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using ConstFindOfIterableClient :: findLastOf;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using ConstFindOfIterableClient :: findAllOf;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using ConstFindOfIterableClient :: findNotOf;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using ConstFindOfIterableClient :: findFirstNotOf;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using ConstFindOfIterableClient :: findLastNotOf;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using ConstFindOfIterableClient :: findAllNotOf;


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
        __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto __iicch_obtainGenericHandler ( /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                __hidden :: __impl :: __IterableInternalRequestType requestType
        ) noexcept -> __GenericHandler override;

    private:    /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto __iicch_obtainGenericConstHandler (    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                __hidden :: __impl :: __IterableInternalRequestType requestType
        ) const noexcept -> __GenericConstHandler override;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_Explicit constexpr EntryMutableCollectionProxy (
                HashMap < __KeyType, __ValueType, __Hasher > * pMap
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

#endif /* __CDS_HASH_MAP_ENTRY_MUTABLE_COLLECTION_PROXY_HPP__ */
