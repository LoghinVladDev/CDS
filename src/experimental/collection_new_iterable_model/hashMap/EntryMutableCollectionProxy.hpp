/*
 * Created by loghin on 14/08/22.
 */

#ifndef __CDS_EX_HASH_MAP_ENTRY_MUTABLE_COLLECTION_PROXY_HPP__
#define __CDS_EX_HASH_MAP_ENTRY_MUTABLE_COLLECTION_PROXY_HPP__ /* NOLINT(bugprone-reserved-identifier) */

namespace cds { /* NOLINT(modernize-concat-nested-namespaces) */
    namespace experimental {

        namespace __hidden {    /* NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier) */
            namespace __impl {  /* NOLINT(bugprone-reserved-identifier) */

                template <
                        typename __ServerType,                      /* NOLINT(bugprone-reserved-identifier) */
                        typename __KeyType,                         /* NOLINT(bugprone-reserved-identifier) */
                        typename __ValueType,                       /* NOLINT(bugprone-reserved-identifier) */
                        typename __Hasher,                          /* NOLINT(bugprone-reserved-identifier) */
                        typename __HashMap =                        /* NOLINT(bugprone-reserved-identifier) */
                                cds :: experimental :: HashMap <    /* NOLINT(bugprone-reserved-identifier) */
                                        __KeyType,
                                        __ValueType,
                                        __Hasher
                                >
                > using __HashMapEntryProxyServer =                 /* NOLINT(bugprone-reserved-identifier) */
                        __MutableCollectionServer <
                                __ServerType,
                                typename __HashMap :: EntryType
                        >;


                template <
                        typename __ServerType,                      /* NOLINT(bugprone-reserved-identifier) */
                        typename __KeyType,                         /* NOLINT(bugprone-reserved-identifier) */
                        typename __ValueType,                       /* NOLINT(bugprone-reserved-identifier) */
                        typename __Hasher,                          /* NOLINT(bugprone-reserved-identifier) */
                        typename __HashMap =                        /* NOLINT(bugprone-reserved-identifier) */
                                HashMap <
                                        __KeyType,
                                        __ValueType,
                                        __Hasher
                                >
                > using __HashMapEntryProxyRandomInsertionClient =  /* NOLINT(bugprone-reserved-identifier) */
                        __LocalRandomInsertionPrimitiveClient <
                                __ServerType,
                                typename __HashMap :: EntryType,
                                typename __HashMap :: EntryType
                        >;


                template <
                        typename __ServerType,                      /* NOLINT(bugprone-reserved-identifier) */
                        typename __KeyType,                         /* NOLINT(bugprone-reserved-identifier) */
                        typename __ValueType,                       /* NOLINT(bugprone-reserved-identifier) */
                        typename __Hasher,                          /* NOLINT(bugprone-reserved-identifier) */
                        typename __HashMap =                        /* NOLINT(bugprone-reserved-identifier) */
                                HashMap <
                                        __KeyType,
                                        __ValueType,
                                        __Hasher
                                >
                > using __HashMapEntryProxyIteratorRemoveClient =   /* NOLINT(bugprone-reserved-identifier) */
                        __LocalIteratorRemovePrimitiveClient <
                                __ServerType,
                                typename __HashMap :: EntryType,
                                typename __HashMapImplementation < __KeyType, __ValueType, __Hasher > :: __ht_Iterator
                        >;


                template <
                        typename __ServerType,                      /* NOLINT(bugprone-reserved-identifier) */
                        typename __KeyType,                         /* NOLINT(bugprone-reserved-identifier) */
                        typename __ValueType,                       /* NOLINT(bugprone-reserved-identifier) */
                        typename __Hasher,                          /* NOLINT(bugprone-reserved-identifier) */
                        typename __HashMap =                        /* NOLINT(bugprone-reserved-identifier) */
                        HashMap <
                                __KeyType,
                                __ValueType,
                                __Hasher
                        >
                > using __HashMapEntryProxyConstIteratorRemoveClient =  /* NOLINT(bugprone-reserved-identifier) */
                        __LocalConstIteratorRemovePrimitiveClient <
                                __ServerType,
                                typename __HashMap :: EntryType,
                                typename __HashMapImplementation < __KeyType, __ValueType, __Hasher > :: __ht_ConstIterator
                        >;


                template <
                        typename __ServerType,                      /* NOLINT(bugprone-reserved-identifier) */
                        typename __KeyType,                         /* NOLINT(bugprone-reserved-identifier) */
                        typename __ValueType,                       /* NOLINT(bugprone-reserved-identifier) */
                        typename __Hasher,                          /* NOLINT(bugprone-reserved-identifier) */
                        typename __HashMap =                        /* NOLINT(bugprone-reserved-identifier) */
                        HashMap <
                                __KeyType,
                                __ValueType,
                                __Hasher
                        >
                > using __HashMapEntryProxyFindOfCollectionClient = /* NOLINT(bugprone-reserved-identifier) */
                        __LocalFindOfMutableCompositeClient <
                                __ServerType,
                                typename __HashMap :: EntryType,
                                typename __HashMapImplementation < __KeyType, __ValueType, __Hasher > :: __ht_Iterator,
                                cds :: experimental :: Collection < typename __HashMap :: EntryType >,
                                & __collectionContains < typename __HashMap :: EntryType >
                        >;


                template <
                        typename __ServerType,                      /* NOLINT(bugprone-reserved-identifier) */
                        typename __KeyType,                         /* NOLINT(bugprone-reserved-identifier) */
                        typename __ValueType,                       /* NOLINT(bugprone-reserved-identifier) */
                        typename __Hasher,                          /* NOLINT(bugprone-reserved-identifier) */
                        typename __HashMap =                        /* NOLINT(bugprone-reserved-identifier) */
                        HashMap <
                                __KeyType,
                                __ValueType,
                                __Hasher
                        >
                > using __HashMapEntryProxyFindOfConstCollectionClient =    /* NOLINT(bugprone-reserved-identifier) */
                        __LocalFindOfImmutableCompositeClient <
                                __ServerType,
                                typename __HashMap :: EntryType,
                                typename __HashMapImplementation < __KeyType, __ValueType, __Hasher > :: __ht_ConstIterator,
                                cds :: experimental :: Collection < typename __HashMap :: EntryType >,
                                & __collectionContains < typename __HashMap :: EntryType >
                        >;


                template <
                        typename __ServerType,                      /* NOLINT(bugprone-reserved-identifier) */
                        typename __KeyType,                         /* NOLINT(bugprone-reserved-identifier) */
                        typename __ValueType,                       /* NOLINT(bugprone-reserved-identifier) */
                        typename __Hasher,                          /* NOLINT(bugprone-reserved-identifier) */
                        typename __HashMap =                        /* NOLINT(bugprone-reserved-identifier) */
                        HashMap <
                                __KeyType,
                                __ValueType,
                                __Hasher
                        >
                > using __HashMapEntryProxyFindOfInitializerListClient =    /* NOLINT(bugprone-reserved-identifier) */
                        __LocalFindOfMutableCompositeClient <
                                __ServerType,
                                typename __HashMap :: EntryType,
                                typename __HashMapImplementation < __KeyType, __ValueType, __Hasher > :: __ht_Iterator,
                                std :: initializer_list < typename __HashMap :: EntryType >,
                                & __initializerListContains < typename __HashMap :: EntryType, & cds :: meta :: equals < typename __HashMap :: EntryType > >
                        >;


                template <
                        typename __ServerType,                      /* NOLINT(bugprone-reserved-identifier) */
                        typename __KeyType,                         /* NOLINT(bugprone-reserved-identifier) */
                        typename __ValueType,                       /* NOLINT(bugprone-reserved-identifier) */
                        typename __Hasher,                          /* NOLINT(bugprone-reserved-identifier) */
                        typename __HashMap =                        /* NOLINT(bugprone-reserved-identifier) */
                        HashMap <
                                __KeyType,
                                __ValueType,
                                __Hasher
                        >
                > using __HashMapEntryProxyFindOfConstInitializerListClient =   /* NOLINT(bugprone-reserved-identifier) */
                        __LocalFindOfImmutableCompositeClient <
                                __ServerType,
                                typename __HashMap :: EntryType,
                                typename __HashMapImplementation < __KeyType, __ValueType, __Hasher > :: __ht_ConstIterator,
                                std :: initializer_list < typename __HashMap :: EntryType >,
                                & __initializerListContains < typename __HashMap :: EntryType, & cds :: meta :: equals < typename __HashMap :: EntryType > >
                        >;


                template <
                        typename __ServerType,                      /* NOLINT(bugprone-reserved-identifier) */
                        typename __KeyType,                         /* NOLINT(bugprone-reserved-identifier) */
                        typename __ValueType,                       /* NOLINT(bugprone-reserved-identifier) */
                        typename __Hasher,                          /* NOLINT(bugprone-reserved-identifier) */
                        typename __HashMap =                        /* NOLINT(bugprone-reserved-identifier) */
                        HashMap <
                                __KeyType,
                                __ValueType,
                                __Hasher
                        >
                > using __HashMapEntryProxyFindByClient =   /* NOLINT(bugprone-reserved-identifier) */
                        __LocalFindByMutableCompositeClient <
                                __ServerType,
                                typename __HashMap :: EntryType,
                                typename __HashMapImplementation < __KeyType, __ValueType, __Hasher > :: __ht_Iterator
                        >;


                template <
                        typename __ServerType,                      /* NOLINT(bugprone-reserved-identifier) */
                        typename __KeyType,                         /* NOLINT(bugprone-reserved-identifier) */
                        typename __ValueType,                       /* NOLINT(bugprone-reserved-identifier) */
                        typename __Hasher,                          /* NOLINT(bugprone-reserved-identifier) */
                        typename __HashMap =                        /* NOLINT(bugprone-reserved-identifier) */
                        HashMap <
                                __KeyType,
                                __ValueType,
                                __Hasher
                        >
                > using __HashMapEntryProxyConstFindByClient =  /* NOLINT(bugprone-reserved-identifier) */
                        __LocalFindByImmutableCompositeClient <
                                __ServerType,
                                typename __HashMap :: EntryType,
                                typename __HashMapImplementation < __KeyType, __ValueType, __Hasher > :: __ht_ConstIterator
                        >;


                template <
                        typename __ServerType,                      /* NOLINT(bugprone-reserved-identifier) */
                        typename __KeyType,                         /* NOLINT(bugprone-reserved-identifier) */
                        typename __ValueType,                       /* NOLINT(bugprone-reserved-identifier) */
                        typename __Hasher,                          /* NOLINT(bugprone-reserved-identifier) */
                        typename __HashMap =                        /* NOLINT(bugprone-reserved-identifier) */
                        HashMap <
                                __KeyType,
                                __ValueType,
                                __Hasher
                        >
                > using __HashMapEntryProxyRemoveOfCollectionClient =   /* NOLINT(bugprone-reserved-identifier) */
                        __LocalRemoveOfCompositeClient <
                                __ServerType,
                                typename __HashMap :: EntryType,
                                cds :: experimental :: Collection < typename __HashMap :: EntryType >,
                                & __collectionContains < typename __HashMap :: EntryType >
                        >;


                template <
                        typename __ServerType,                      /* NOLINT(bugprone-reserved-identifier) */
                        typename __KeyType,                         /* NOLINT(bugprone-reserved-identifier) */
                        typename __ValueType,                       /* NOLINT(bugprone-reserved-identifier) */
                        typename __Hasher,                          /* NOLINT(bugprone-reserved-identifier) */
                        typename __HashMap =                        /* NOLINT(bugprone-reserved-identifier) */
                        HashMap <
                                __KeyType,
                                __ValueType,
                                __Hasher
                        >
                > using __HashMapEntryProxyRemoveOfInitializerListClient =  /* NOLINT(bugprone-reserved-identifier) */
                        __LocalRemoveOfCompositeClient <
                                __ServerType,
                                typename __HashMap :: EntryType,
                                std :: initializer_list < typename __HashMap :: EntryType >,
                                & __initializerListContains < typename __HashMap :: EntryType, & cds :: meta :: equals < typename __HashMap :: EntryType > >
                        >;


                template <
                        typename __ServerType,                      /* NOLINT(bugprone-reserved-identifier) */
                        typename __KeyType,                         /* NOLINT(bugprone-reserved-identifier) */
                        typename __ValueType,                       /* NOLINT(bugprone-reserved-identifier) */
                        typename __Hasher,                          /* NOLINT(bugprone-reserved-identifier) */
                        typename __HashMap =                        /* NOLINT(bugprone-reserved-identifier) */
                        HashMap <
                                __KeyType,
                                __ValueType,
                                __Hasher
                        >
                > using __HashMapEntryProxyRemoveByClient = /* NOLINT(bugprone-reserved-identifier) */
                        __LocalRemoveByCompositeClient <
                                __ServerType,
                                typename __HashMap :: EntryType
                        >;


                template <
                        typename __ServerType,                      /* NOLINT(bugprone-reserved-identifier) */
                        typename __KeyType,                         /* NOLINT(bugprone-reserved-identifier) */
                        typename __ValueType,                       /* NOLINT(bugprone-reserved-identifier) */
                        typename __Hasher,                          /* NOLINT(bugprone-reserved-identifier) */
                        typename __HashMap =                        /* NOLINT(bugprone-reserved-identifier) */
                        HashMap <
                                __KeyType,
                                __ValueType,
                                __Hasher
                        >
                > using __HashMapEntryProxyGenericStatementsClient =    /* NOLINT(bugprone-reserved-identifier) */
                        __LocalGenericMutableStatementsCompositeClient <
                                __ServerType,
                                typename __HashMap :: EntryType
                        >;


                template <
                        typename __ServerType,                      /* NOLINT(bugprone-reserved-identifier) */
                        typename __KeyType,                         /* NOLINT(bugprone-reserved-identifier) */
                        typename __ValueType,                       /* NOLINT(bugprone-reserved-identifier) */
                        typename __Hasher,                          /* NOLINT(bugprone-reserved-identifier) */
                        typename __HashMap =                        /* NOLINT(bugprone-reserved-identifier) */
                        HashMap <
                                __KeyType,
                                __ValueType,
                                __Hasher
                        >
                > using __HashMapEntryProxyConstGenericStatementsClient =   /* NOLINT(bugprone-reserved-identifier) */
                        __LocalGenericImmutableStatementsCompositeClient <
                                __ServerType,
                                typename __HashMap :: EntryType
                        >;


                template <
                        typename __ServerType,                          /* NOLINT(bugprone-reserved-identifier) */
                        typename __KeyType,                             /* NOLINT(bugprone-reserved-identifier) */
                        typename __ValueType,                           /* NOLINT(bugprone-reserved-identifier) */
                        typename __Hasher,                              /* NOLINT(bugprone-reserved-identifier) */
                        typename __HashMap =                            /* NOLINT(bugprone-reserved-identifier) */
                        HashMap <
                                __KeyType,
                                __ValueType,
                                __Hasher
                        >
                > using __HashMapEntryProxyContainsOfCollectionClient = /* NOLINT(bugprone-reserved-identifier) */
                        __LocalContainsOfCompositeClient <
                                __ServerType,
                                typename __HashMap :: EntryType,
                                cds :: experimental :: Collection < typename __HashMap :: EntryType >,
                                __collectionContains < typename __HashMap :: EntryType >
                        >;


                template <
                        typename __ServerType,                                  /* NOLINT(bugprone-reserved-identifier) */
                        typename __KeyType,                                     /* NOLINT(bugprone-reserved-identifier) */
                        typename __ValueType,                                   /* NOLINT(bugprone-reserved-identifier) */
                        typename __Hasher,                                      /* NOLINT(bugprone-reserved-identifier) */
                        typename __HashMap =                                    /* NOLINT(bugprone-reserved-identifier) */
                        HashMap <
                                __KeyType,
                                __ValueType,
                                __Hasher
                        >
                > using __HashMapEntryProxyContainsOfInitializerListClient =    /* NOLINT(bugprone-reserved-identifier) */
                        __LocalContainsOfCompositeClient <
                                __ServerType,
                                typename __HashMap :: EntryType,
                                std :: initializer_list < typename __HashMap :: EntryType >,
                                __initializerListContains <
                                        typename __HashMap :: EntryType,
                                        & cds :: meta :: equals < typename __HashMap :: EntryType >
                                >
                        >;


                template <
                        typename __ServerType,                              /* NOLINT(bugprone-reserved-identifier) */
                        typename __KeyType,                                 /* NOLINT(bugprone-reserved-identifier) */
                        typename __ValueType,                               /* NOLINT(bugprone-reserved-identifier) */
                        typename __Hasher,                                  /* NOLINT(bugprone-reserved-identifier) */
                        typename __HashMap =                                /* NOLINT(bugprone-reserved-identifier) */
                        HashMap <
                                __KeyType,
                                __ValueType,
                                __Hasher
                        >
                > using __HashMapEntryProxyDelegateForwardIterableClient =  /* NOLINT(bugprone-reserved-identifier) */
                        __LocalDelegateForwardIterablePrimitiveClient <
                                __ServerType,
                                typename __HashMapImplementation < __KeyType, __ValueType, __Hasher > :: __ht_Iterator
                        >;


                template <
                        typename __ServerType,                                  /* NOLINT(bugprone-reserved-identifier) */
                        typename __KeyType,                                     /* NOLINT(bugprone-reserved-identifier) */
                        typename __ValueType,                                   /* NOLINT(bugprone-reserved-identifier) */
                        typename __Hasher,                                      /* NOLINT(bugprone-reserved-identifier) */
                        typename __HashMap =                                    /* NOLINT(bugprone-reserved-identifier) */
                        HashMap <
                                __KeyType,
                                __ValueType,
                                __Hasher
                        >
                > using __HashMapEntryProxyDelegateForwardConstIterableClient = /* NOLINT(bugprone-reserved-identifier) */
                        __LocalDelegateForwardConstIterablePrimitiveClient <
                                __ServerType,
                                typename __HashMapImplementation < __KeyType, __ValueType, __Hasher > :: __ht_ConstIterator
                        >;

            }
        }

        template <
                typename __KeyType,     /* NOLINT(bugprone-reserved-identifier) */
                typename __ValueType,   /* NOLINT(bugprone-reserved-identifier) */
                typename __Hasher       /* NOLINT(bugprone-reserved-identifier) */
        > class HashMap <
                __KeyType,
                __ValueType,
                __Hasher
        > :: EntryMutableCollectionProxy :
                public AbstractEntryMutableCollectionProxy,
                protected __hidden :: __impl :: __HashMapEntryProxyServer < EntryMutableCollectionProxy, __KeyType, __ValueType, __Hasher >,
                public __hidden :: __impl :: __HashMapEntryProxyRandomInsertionClient < KeySetProxy, __KeyType, __ValueType, __Hasher >,
                public __hidden :: __impl :: __HashMapEntryProxyIteratorRemoveClient < KeySetProxy, __KeyType, __ValueType, __Hasher >,
                public __hidden :: __impl :: __HashMapEntryProxyConstIteratorRemoveClient < KeySetProxy, __KeyType, __ValueType, __Hasher >,
                public __hidden :: __impl :: __HashMapEntryProxyFindOfCollectionClient < KeySetProxy, __KeyType, __ValueType, __Hasher >,
                public __hidden :: __impl :: __HashMapEntryProxyFindOfConstCollectionClient < KeySetProxy, __KeyType, __ValueType, __Hasher >,
                public __hidden :: __impl :: __HashMapEntryProxyFindOfInitializerListClient < KeySetProxy, __KeyType, __ValueType, __Hasher >,
                public __hidden :: __impl :: __HashMapEntryProxyFindOfConstInitializerListClient < KeySetProxy, __KeyType, __ValueType, __Hasher >,
                public __hidden :: __impl :: __HashMapEntryProxyFindByClient < KeySetProxy, __KeyType, __ValueType, __Hasher >,
                public __hidden :: __impl :: __HashMapEntryProxyConstFindByClient < KeySetProxy, __KeyType, __ValueType, __Hasher >,
                public __hidden :: __impl :: __HashMapEntryProxyRemoveOfCollectionClient < KeySetProxy, __KeyType, __ValueType, __Hasher >,
                public __hidden :: __impl :: __HashMapEntryProxyRemoveOfInitializerListClient < KeySetProxy, __KeyType, __ValueType, __Hasher >,
                public __hidden :: __impl :: __HashMapEntryProxyRemoveByClient < KeySetProxy, __KeyType, __ValueType, __Hasher >,
                public __hidden :: __impl :: __HashMapEntryProxyGenericStatementsClient < KeySetProxy, __KeyType, __ValueType, __Hasher >,
                public __hidden :: __impl :: __HashMapEntryProxyConstGenericStatementsClient < KeySetProxy, __KeyType, __ValueType, __Hasher >,
                public __hidden :: __impl :: __HashMapEntryProxyContainsOfCollectionClient < KeySetProxy, __KeyType, __ValueType, __Hasher >,
                public __hidden :: __impl :: __HashMapEntryProxyContainsOfInitializerListClient < KeySetProxy, __KeyType, __ValueType, __Hasher >,
                public __hidden :: __impl :: __HashMapEntryProxyDelegateForwardIterableClient < KeySetProxy, __KeyType, __ValueType, __Hasher >,
                public __hidden :: __impl :: __HashMapEntryProxyDelegateForwardConstIterableClient < KeySetProxy, __KeyType, __ValueType, __Hasher > {

        protected:  using HashMapBase                           = HashMap < __KeyType, __ValueType, __Hasher >;
        protected:  using Server                                = __hidden :: __impl :: __HashMapEntryProxyServer < EntryMutableCollectionProxy, __KeyType, __ValueType, __Hasher >;
        protected:  using RandomInsertionClient                 = __hidden :: __impl :: __HashMapEntryProxyRandomInsertionClient < KeySetProxy, __KeyType, __ValueType, __Hasher >;
        protected:  using IteratorRemoveClient                  = __hidden :: __impl :: __HashMapEntryProxyIteratorRemoveClient < KeySetProxy, __KeyType, __ValueType, __Hasher >;
        protected:  using ConstIteratorRemoveClient             = __hidden :: __impl :: __HashMapEntryProxyConstIteratorRemoveClient < KeySetProxy, __KeyType, __ValueType, __Hasher >;
        protected:  using FindOfCollectionClient                = __hidden :: __impl :: __HashMapEntryProxyFindOfCollectionClient < KeySetProxy, __KeyType, __ValueType, __Hasher >;
        protected:  using ConstFindOfCollectionClient           = __hidden :: __impl :: __HashMapEntryProxyFindOfConstCollectionClient < KeySetProxy, __KeyType, __ValueType, __Hasher >;
        protected:  using FindOfInitializerListClient           = __hidden :: __impl :: __HashMapEntryProxyFindOfInitializerListClient < KeySetProxy, __KeyType, __ValueType, __Hasher >;
        protected:  using ConstFindOfInitializerListClient      = __hidden :: __impl :: __HashMapEntryProxyFindOfConstInitializerListClient < KeySetProxy, __KeyType, __ValueType, __Hasher >;
        protected:  using FindByClient                          = __hidden :: __impl :: __HashMapEntryProxyFindByClient < KeySetProxy, __KeyType, __ValueType, __Hasher >;
        protected:  using ConstFindByClient                     = __hidden :: __impl :: __HashMapEntryProxyConstFindByClient < KeySetProxy, __KeyType, __ValueType, __Hasher >;
        protected:  using RemoveOfCollectionClient              = __hidden :: __impl :: __HashMapEntryProxyRemoveOfCollectionClient < KeySetProxy, __KeyType, __ValueType, __Hasher >;
        protected:  using RemoveOfInitializerListClient         = __hidden :: __impl :: __HashMapEntryProxyRemoveOfInitializerListClient < KeySetProxy, __KeyType, __ValueType, __Hasher >;
        protected:  using RemoveByClient                        = __hidden :: __impl :: __HashMapEntryProxyRemoveByClient < KeySetProxy, __KeyType, __ValueType, __Hasher >;
        protected:  using GenericStatementsClient               = __hidden :: __impl :: __HashMapEntryProxyGenericStatementsClient < KeySetProxy, __KeyType, __ValueType, __Hasher >;
        protected:  using ContainsOfCollectionClient            = __hidden :: __impl :: __HashMapEntryProxyContainsOfCollectionClient < KeySetProxy, __KeyType, __ValueType, __Hasher >;
        protected:  using ContainsOfInitializerListClient       = __hidden :: __impl :: __HashMapEntryProxyContainsOfInitializerListClient < KeySetProxy, __KeyType, __ValueType, __Hasher >;
        protected:  using ConstGenericStatementsClient          = __hidden :: __impl :: __HashMapEntryProxyConstGenericStatementsClient < KeySetProxy, __KeyType, __ValueType, __Hasher >;
        protected:  using DelegateForwardIterableClient         = __hidden :: __impl :: __HashMapEntryProxyDelegateForwardIterableClient < KeySetProxy, __KeyType, __ValueType, __Hasher >;
        protected:  using DelegateForwardConstIterableClient    = __hidden :: __impl :: __HashMapEntryProxyDelegateForwardConstIterableClient < KeySetProxy, __KeyType, __ValueType, __Hasher >;

        protected:  using typename AbstractEntryMutableCollectionProxy :: __GenericHandler;         /* NOLINT(bugprone-reserved-identifier) */
        protected:  using typename AbstractEntryMutableCollectionProxy :: __GenericConstHandler;    /* NOLINT(bugprone-reserved-identifier) */

        public:     using EntryType     = typename cds :: experimental :: Map < __KeyType, __ValueType > :: EntryType;

        public:     using typename DelegateForwardIterableClient :: Iterator;
        public:     using typename DelegateForwardConstIterableClient :: ConstIterator;

        protected:  friend Server;
        private:    friend DelegateForwardIterableClient;
        private:    friend DelegateForwardConstIterableClient;

        public:     using DelegateForwardIterableClient :: begin;
        public:     using DelegateForwardIterableClient :: end;

        public:     using DelegateForwardConstIterableClient :: begin;
        public:     using DelegateForwardConstIterableClient :: end;
        public:     using DelegateForwardConstIterableClient :: cbegin;
        public:     using DelegateForwardConstIterableClient :: cend;

        public:     using RemoveByClient :: removeThat;
        public:     using RemoveByClient :: removeFirstThat;
        public:     using RemoveByClient :: removeLastThat;
        public:     using RemoveByClient :: removeAllThat;

        public:     using GenericStatementsClient :: forEach;
        public:     using GenericStatementsClient :: some;
        public:     using GenericStatementsClient :: atLeast;
        public:     using GenericStatementsClient :: atMost;
        public:     using GenericStatementsClient :: moreThan;
        public:     using GenericStatementsClient :: fewerThan;
        public:     using GenericStatementsClient :: count;
        public:     using GenericStatementsClient :: any;
        public:     using GenericStatementsClient :: all;
        public:     using GenericStatementsClient :: none;

        public:     using ConstGenericStatementsClient :: forEach;
        public:     using ConstGenericStatementsClient :: some;
        public:     using ConstGenericStatementsClient :: atLeast;
        public:     using ConstGenericStatementsClient :: atMost;
        public:     using ConstGenericStatementsClient :: moreThan;
        public:     using ConstGenericStatementsClient :: fewerThan;
        public:     using ConstGenericStatementsClient :: count;
        public:     using ConstGenericStatementsClient :: any;
        public:     using ConstGenericStatementsClient :: all;
        public:     using ConstGenericStatementsClient :: none;

        public:     using RemoveOfCollectionClient :: removeOf;
        public:     using RemoveOfCollectionClient :: removeFirstOf;
        public:     using RemoveOfCollectionClient :: removeLastOf;
        public:     using RemoveOfCollectionClient :: removeAllOf;
        public:     using RemoveOfCollectionClient :: removeNotOf;
        public:     using RemoveOfCollectionClient :: removeFirstNotOf;
        public:     using RemoveOfCollectionClient :: removeLastNotOf;
        public:     using RemoveOfCollectionClient :: removeAllNotOf;

        public:     using RemoveOfInitializerListClient :: removeOf;
        public:     using RemoveOfInitializerListClient :: removeFirstOf;
        public:     using RemoveOfInitializerListClient :: removeLastOf;
        public:     using RemoveOfInitializerListClient :: removeAllOf;
        public:     using RemoveOfInitializerListClient :: removeNotOf;
        public:     using RemoveOfInitializerListClient :: removeFirstNotOf;
        public:     using RemoveOfInitializerListClient :: removeLastNotOf;
        public:     using RemoveOfInitializerListClient :: removeAllNotOf;

        public:     using ContainsOfCollectionClient :: containsAnyOf;
        public:     using ContainsOfCollectionClient :: containsAnyNotOf;
        public:     using ContainsOfCollectionClient :: containsAllOf;
        public:     using ContainsOfCollectionClient :: containsNoneOf;

        public:     using ContainsOfInitializerListClient :: containsAnyOf;
        public:     using ContainsOfInitializerListClient :: containsAnyNotOf;
        public:     using ContainsOfInitializerListClient :: containsAllOf;
        public:     using ContainsOfInitializerListClient :: containsNoneOf;

        public:     using FindByClient :: findThat;
        public:     using FindByClient :: findFirstThat;
        public:     using FindByClient :: findLastThat;
        public:     using FindByClient :: findAllThat;

        public:     using FindOfCollectionClient :: findOf;
        public:     using FindOfCollectionClient :: findFirstOf;
        public:     using FindOfCollectionClient :: findLastOf;
        public:     using FindOfCollectionClient :: findAllOf;
        public:     using FindOfCollectionClient :: findNotOf;
        public:     using FindOfCollectionClient :: findFirstNotOf;
        public:     using FindOfCollectionClient :: findLastNotOf;
        public:     using FindOfCollectionClient :: findAllNotOf;

        public:     using FindOfInitializerListClient :: findOf;
        public:     using FindOfInitializerListClient :: findFirstOf;
        public:     using FindOfInitializerListClient :: findLastOf;
        public:     using FindOfInitializerListClient :: findAllOf;
        public:     using FindOfInitializerListClient :: findNotOf;
        public:     using FindOfInitializerListClient :: findFirstNotOf;
        public:     using FindOfInitializerListClient :: findLastNotOf;
        public:     using FindOfInitializerListClient :: findAllNotOf;

        public:     using ConstFindByClient :: findThat;
        public:     using ConstFindByClient :: findFirstThat;
        public:     using ConstFindByClient :: findLastThat;
        public:     using ConstFindByClient :: findAllThat;

        public:     using ConstFindOfCollectionClient :: findOf;
        public:     using ConstFindOfCollectionClient :: findFirstOf;
        public:     using ConstFindOfCollectionClient :: findLastOf;
        public:     using ConstFindOfCollectionClient :: findAllOf;
        public:     using ConstFindOfCollectionClient :: findNotOf;
        public:     using ConstFindOfCollectionClient :: findFirstNotOf;
        public:     using ConstFindOfCollectionClient :: findLastNotOf;
        public:     using ConstFindOfCollectionClient :: findAllNotOf;

        public:     using ConstFindOfInitializerListClient :: findOf;
        public:     using ConstFindOfInitializerListClient :: findFirstOf;
        public:     using ConstFindOfInitializerListClient :: findLastOf;
        public:     using ConstFindOfInitializerListClient :: findAllOf;
        public:     using ConstFindOfInitializerListClient :: findNotOf;
        public:     using ConstFindOfInitializerListClient :: findFirstNotOf;
        public:     using ConstFindOfInitializerListClient :: findLastNotOf;
        public:     using ConstFindOfInitializerListClient :: findAllNotOf;

        public:     using RandomInsertionClient :: add;
        public:     using RandomInsertionClient :: addAll;
        public:     using RandomInsertionClient :: addAllOf;
        public:     using RandomInsertionClient :: insert;
        public:     using RandomInsertionClient :: insertAll;
        public:     using RandomInsertionClient :: insertAllOf;
        public:     using RandomInsertionClient :: emplace;

        public:     using IteratorRemoveClient :: remove;
        public:     using ConstIteratorRemoveClient :: remove;

        private:
            __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto __cicch_obtainGenericHandler ( /* NOLINT(bugprone-reserved-identifier) */
                    __hidden :: __impl :: __CollectionInternalRequestType requestType
            ) noexcept -> __GenericHandler override;

        private:
            __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto __cicch_obtainGenericConstHandler (    /* NOLINT(bugprone-reserved-identifier) */
                    __hidden :: __impl :: __CollectionInternalRequestType requestType
            ) const noexcept -> __GenericConstHandler override;

        public:
            __CDS_Explicit constexpr EntryMutableCollectionProxy (
                    HashMap < __KeyType, __ValueType, __Hasher > * pMap
            ) noexcept;

        public:
            auto __newAddress ( /* NOLINT(bugprone-reserved-identifier) */
                    EntryType const * pReferenceElement,
                    bool            * pIsNew
            ) noexcept -> EntryType *;

        public:
            __CDS_NoDiscard auto __begin () noexcept -> __hidden :: __impl :: __AbstractDelegateIterator < EntryType > *;

        public:
            __CDS_NoDiscard auto __end () noexcept -> __hidden :: __impl :: __AbstractDelegateIterator < EntryType > *;

        public:
            __CDS_NoDiscard auto __cbegin () const noexcept -> __hidden :: __impl :: __AbstractDelegateIterator < EntryType const > *;

        public:
            __CDS_NoDiscard auto __cend () const noexcept -> __hidden :: __impl :: __AbstractDelegateIterator < EntryType const > *;

        public:
            __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction auto __beginLocal () noexcept -> Iterator;

        public:
            __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction auto __endLocal () noexcept -> Iterator;

        public:
            __CDS_NoDiscard constexpr auto __cbeginLocal () const noexcept -> ConstIterator;

        public:
            __CDS_NoDiscard constexpr auto __cendLocal () const noexcept -> ConstIterator;

        public:
            auto __remove ( /* NOLINT(bugprone-reserved-identifier) */
                    Iterator const * iterator
            ) noexcept -> bool;

        public:
            auto __removeConst (    /* NOLINT(bugprone-reserved-identifier) */
                    ConstIterator const * iterator
            ) noexcept -> bool;
        };

    }
}

#endif /* __CDS_EX_HASH_MAP_ENTRY_MUTABLE_COLLECTION_PROXY_HPP__ */
