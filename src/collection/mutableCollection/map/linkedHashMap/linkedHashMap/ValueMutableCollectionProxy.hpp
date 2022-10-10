/*
 * Created by loghin on 09/10/22.
 */

#ifndef __CDS_LINKED_HASH_MAP_VALUE_MUTABLE_COLLECTION_PROXY_HPP__
#define __CDS_LINKED_HASH_MAP_VALUE_MUTABLE_COLLECTION_PROXY_HPP__   /* NOLINT(bugprone-reserved-identifier) */

namespace cds {             /* NOLINT(bugprone-reserved-identifier) */
    namespace __hidden {    /* NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier) */
        namespace __impl {  /* NOLINT(bugprone-reserved-identifier) */

            template <
                    typename __ServerType,                          /* NOLINT(bugprone-reserved-identifier) */
                    typename __KeyType,                             /* NOLINT(bugprone-reserved-identifier) */
                    typename __ValueType,                           /* NOLINT(bugprone-reserved-identifier) */
                    typename __Hasher,                              /* NOLINT(bugprone-reserved-identifier) */
                    typename __LinkedHashMap =                      /* NOLINT(bugprone-reserved-identifier) */
                            cds :: LinkedHashMap <                  /* NOLINT(bugprone-reserved-identifier) */
                                    __KeyType,
                                    __ValueType,
                                    __Hasher
                            >
            > using __LinkedHashMapValueProxyServer =               /* NOLINT(bugprone-reserved-identifier) */
                    __MutableCollectionServer <
                            __ServerType,
                            __ValueType
                    >;


            template <
                    typename __DecoratedIteratorType,                               /* NOLINT(bugprone-reserved-identifier) */
                    typename __ValueAtType                                          /* NOLINT(bugprone-reserved-identifier) */
            > constexpr auto __linkedHashMapValueSetProxyIteratorDecoratorValueAt ( /* NOLINT(bugprone-reserved-identifier) */
                    __DecoratedIteratorType const & iterator
            ) noexcept -> __ValueAtType & {

                return ( * iterator ).value ();
            }


            template <
                    typename __KeyType,                 /* NOLINT(bugprone-reserved-identifier) */
                    typename __ValueType,               /* NOLINT(bugprone-reserved-identifier) */
                    typename __Hasher                   /* NOLINT(bugprone-reserved-identifier) */
            > using __LinkedHashMapValueProxyIterator = /* NOLINT(bugprone-reserved-identifier) */
                    ForwardIteratorGenericDecorator <
                            __LinkedHashMapIterator < __KeyType, __ValueType, __Hasher >,
                            __ValueType,
                            & __linkedHashMapValueSetProxyIteratorDecoratorValueAt <
                                    __LinkedHashMapIterator < __KeyType, __ValueType, __Hasher >,
                                    __ValueType
                            >
                    >;


            template <
                    typename __KeyType,                         /* NOLINT(bugprone-reserved-identifier) */
                    typename __ValueType,                       /* NOLINT(bugprone-reserved-identifier) */
                    typename __Hasher                           /* NOLINT(bugprone-reserved-identifier) */
            > using __LinkedHashMapValueProxyConstIterator =    /* NOLINT(bugprone-reserved-identifier) */
                    ForwardIteratorGenericDecorator <
                            __LinkedHashMapConstIterator < __KeyType, __ValueType, __Hasher >,
                            __ValueType const,
                            & __linkedHashMapValueSetProxyIteratorDecoratorValueAt <
                                    __LinkedHashMapConstIterator < __KeyType, __ValueType, __Hasher >,
                                    __ValueType const
                            >
                    >;


            template <
                    typename __ServerType,                              /* NOLINT(bugprone-reserved-identifier) */
                    typename __KeyType,                                 /* NOLINT(bugprone-reserved-identifier) */
                    typename __ValueType,                               /* NOLINT(bugprone-reserved-identifier) */
                    typename __Hasher                                   /* NOLINT(bugprone-reserved-identifier) */
            > using __LinkedHashMapValueProxyRandomInsertionClient =    /* NOLINT(bugprone-reserved-identifier) */
                    __LocalRandomInsertionPrimitiveClient <
                            __ServerType,
                            __ValueType,
                            __ValueType
                    >;


            template <
                    typename __ServerType,                          /* NOLINT(bugprone-reserved-identifier) */
                    typename __KeyType,                             /* NOLINT(bugprone-reserved-identifier) */
                    typename __ValueType,                           /* NOLINT(bugprone-reserved-identifier) */
                    typename __Hasher                               /* NOLINT(bugprone-reserved-identifier) */
            > using __LinkedHashMapValueProxyIteratorRemoveClient = /* NOLINT(bugprone-reserved-identifier) */
                    __LocalIteratorRemovePrimitiveClient <
                            __ServerType,
                            __ValueType,
                            __LinkedHashMapValueProxyIterator < __KeyType, __ValueType, __Hasher >
                    >;


            template <
                    typename __ServerType,                                  /* NOLINT(bugprone-reserved-identifier) */
                    typename __KeyType,                                     /* NOLINT(bugprone-reserved-identifier) */
                    typename __ValueType,                                   /* NOLINT(bugprone-reserved-identifier) */
                    typename __Hasher                                       /* NOLINT(bugprone-reserved-identifier) */
            > using __LinkedHashMapValueProxyConstIteratorRemoveClient =    /* NOLINT(bugprone-reserved-identifier) */
                    __LocalConstIteratorRemovePrimitiveClient <
                            __ServerType,
                            __ValueType,
                            __LinkedHashMapValueProxyConstIterator < __KeyType, __ValueType, __Hasher >
                    >;


            template <
                    typename __ServerType,                              /* NOLINT(bugprone-reserved-identifier) */
                    typename __KeyType,                                 /* NOLINT(bugprone-reserved-identifier) */
                    typename __ValueType,                               /* NOLINT(bugprone-reserved-identifier) */
                    typename __Hasher                                   /* NOLINT(bugprone-reserved-identifier) */
            > using __LinkedHashMapValueProxyFindOfCollectionClient =   /* NOLINT(bugprone-reserved-identifier) */
                    __LocalFindOfMutableCompositeClient <
                            __ServerType,
                            __ValueType,
                            __LinkedHashMapValueProxyIterator < __KeyType, __ValueType, __Hasher >,
                            cds :: Collection < __ValueType >,
                            & __collectionContains < __ValueType >,
                            & __collectionNotContains < __ValueType >
                    >;


            template <
                    typename __ServerType,                                  /* NOLINT(bugprone-reserved-identifier) */
                    typename __KeyType,                                     /* NOLINT(bugprone-reserved-identifier) */
                    typename __ValueType,                                   /* NOLINT(bugprone-reserved-identifier) */
                    typename __Hasher                                       /* NOLINT(bugprone-reserved-identifier) */
            > using __LinkedHashMapValueProxyFindOfConstCollectionClient =  /* NOLINT(bugprone-reserved-identifier) */
                    __LocalFindOfImmutableCompositeClient <
                            __ServerType,
                            __ValueType,
                            __LinkedHashMapValueProxyConstIterator < __KeyType, __ValueType, __Hasher >,
                            cds :: Collection < __ValueType >,
                            & __collectionContains < __ValueType >,
                            & __collectionNotContains < __ValueType >
                    >;


            template <
                    typename __ServerType,                                  /* NOLINT(bugprone-reserved-identifier) */
                    typename __KeyType,                                     /* NOLINT(bugprone-reserved-identifier) */
                    typename __ValueType,                                   /* NOLINT(bugprone-reserved-identifier) */
                    typename __Hasher                                       /* NOLINT(bugprone-reserved-identifier) */
            > using __LinkedHashMapValueProxyFindOfInitializerListClient =  /* NOLINT(bugprone-reserved-identifier) */
                    __LocalFindOfMutableCompositeClient <
                            __ServerType,
                            __ValueType,
                            __LinkedHashMapValueProxyIterator < __KeyType, __ValueType, __Hasher >,
                            std :: initializer_list < __ValueType >,
                            & __initializerListContains < __ValueType, & cds :: meta :: equals < __ValueType > >,
                            & __initializerListNotContains < __ValueType, & cds :: meta :: equals < __ValueType > >
                    >;


            template <
                    typename __ServerType,                                      /* NOLINT(bugprone-reserved-identifier) */
                    typename __KeyType,                                         /* NOLINT(bugprone-reserved-identifier) */
                    typename __ValueType,                                       /* NOLINT(bugprone-reserved-identifier) */
                    typename __Hasher                                           /* NOLINT(bugprone-reserved-identifier) */
            > using __LinkedHashMapValueProxyFindOfConstInitializerListClient = /* NOLINT(bugprone-reserved-identifier) */
                    __LocalFindOfImmutableCompositeClient <
                            __ServerType,
                            __ValueType,
                            __LinkedHashMapValueProxyConstIterator < __KeyType, __ValueType, __Hasher >,
                            std :: initializer_list < __ValueType >,
                            & __initializerListContains < __ValueType, & cds :: meta :: equals < __ValueType > >,
                            & __initializerListNotContains < __ValueType, & cds :: meta :: equals < __ValueType > >
                    >;


            template <
                    typename __ServerType,                  /* NOLINT(bugprone-reserved-identifier) */
                    typename __KeyType,                     /* NOLINT(bugprone-reserved-identifier) */
                    typename __ValueType,                   /* NOLINT(bugprone-reserved-identifier) */
                    typename __Hasher                       /* NOLINT(bugprone-reserved-identifier) */
            > using __LinkedHashMapValueProxyFindByClient = /* NOLINT(bugprone-reserved-identifier) */
                    __LocalFindByMutableCompositeClient <
                            __ServerType,
                            __ValueType,
                            __LinkedHashMapValueProxyIterator < __KeyType, __ValueType, __Hasher >
                    >;


            template <
                    typename __ServerType,                          /* NOLINT(bugprone-reserved-identifier) */
                    typename __KeyType,                             /* NOLINT(bugprone-reserved-identifier) */
                    typename __ValueType,                           /* NOLINT(bugprone-reserved-identifier) */
                    typename __Hasher                               /* NOLINT(bugprone-reserved-identifier) */
            > using __LinkedHashMapValueProxyConstFindByClient =    /* NOLINT(bugprone-reserved-identifier) */
                    __LocalFindByImmutableCompositeClient <
                            __ServerType,
                            __ValueType,
                            __LinkedHashMapValueProxyConstIterator < __KeyType, __ValueType, __Hasher >
                    >;


            template <
                    typename __ServerType,                              /* NOLINT(bugprone-reserved-identifier) */
                    typename __KeyType,                                 /* NOLINT(bugprone-reserved-identifier) */
                    typename __ValueType,                               /* NOLINT(bugprone-reserved-identifier) */
                    typename __Hasher                                   /* NOLINT(bugprone-reserved-identifier) */
            > using __LinkedHashMapValueProxyRemoveOfCollectionClient = /* NOLINT(bugprone-reserved-identifier) */
                    __LocalRemoveOfCompositeClient <
                            __ServerType,
                            __ValueType,
                            cds :: Collection < __ValueType >,
                            & __collectionContains < __ValueType >
                    >;


            template <
                    typename __ServerType,                                      /* NOLINT(bugprone-reserved-identifier) */
                    typename __KeyType,                                         /* NOLINT(bugprone-reserved-identifier) */
                    typename __ValueType,                                       /* NOLINT(bugprone-reserved-identifier) */
                    typename __Hasher                                           /* NOLINT(bugprone-reserved-identifier) */
            > using __LinkedHashMapValueProxyRemoveOfInitializerListClient =    /* NOLINT(bugprone-reserved-identifier) */
                    __LocalRemoveOfCompositeClient <
                            __ServerType,
                            __ValueType,
                            std :: initializer_list < __ValueType >,
                            & __initializerListContains < __ValueType, & cds :: meta :: equals < __ValueType > >
                    >;


            template <
                    typename __ServerType,                      /* NOLINT(bugprone-reserved-identifier) */
                    typename __KeyType,                         /* NOLINT(bugprone-reserved-identifier) */
                    typename __ValueType,                       /* NOLINT(bugprone-reserved-identifier) */
                    typename __Hasher                           /* NOLINT(bugprone-reserved-identifier) */
            > using __LinkedHashMapValueProxyRemoveByClient =   /* NOLINT(bugprone-reserved-identifier) */
                    __LocalRemoveByCompositeClient <
                            __ServerType,
                            __ValueType
                    >;


            template <
                    typename __ServerType,                              /* NOLINT(bugprone-reserved-identifier) */
                    typename __KeyType,                                 /* NOLINT(bugprone-reserved-identifier) */
                    typename __ValueType,                               /* NOLINT(bugprone-reserved-identifier) */
                    typename __Hasher                                   /* NOLINT(bugprone-reserved-identifier) */
            > using __LinkedHashMapValueProxyGenericStatementsClient =  /* NOLINT(bugprone-reserved-identifier) */
                    __LocalGenericMutableStatementsCompositeClient <
                            __ServerType,
                            __ValueType
                    >;


            template <
                    typename __ServerType,                                  /* NOLINT(bugprone-reserved-identifier) */
                    typename __KeyType,                                     /* NOLINT(bugprone-reserved-identifier) */
                    typename __ValueType,                                   /* NOLINT(bugprone-reserved-identifier) */
                    typename __Hasher                                       /* NOLINT(bugprone-reserved-identifier) */
            > using __LinkedHashMapValueProxyConstGenericStatementsClient = /* NOLINT(bugprone-reserved-identifier) */
                    __LocalGenericImmutableStatementsCompositeClient <
                            __ServerType,
                            __ValueType
                    >;


            template <
                    typename __ServerType,                                  /* NOLINT(bugprone-reserved-identifier) */
                    typename __KeyType,                                     /* NOLINT(bugprone-reserved-identifier) */
                    typename __ValueType,                                   /* NOLINT(bugprone-reserved-identifier) */
                    typename __Hasher                                       /* NOLINT(bugprone-reserved-identifier) */
            > using __LinkedHashMapValueProxyContainsOfCollectionClient =   /* NOLINT(bugprone-reserved-identifier) */
                    __LocalContainsOfCompositeClient <
                            __ServerType,
                            __ValueType,
                            cds :: Collection < __ValueType >,
                            __collectionContains < __ValueType >
                    >;


            template <
                    typename __ServerType,                                      /* NOLINT(bugprone-reserved-identifier) */
                    typename __KeyType,                                         /* NOLINT(bugprone-reserved-identifier) */
                    typename __ValueType,                                       /* NOLINT(bugprone-reserved-identifier) */
                    typename __Hasher                                           /* NOLINT(bugprone-reserved-identifier) */
            > using __LinkedHashMapValueProxyContainsOfInitializerListClient =  /* NOLINT(bugprone-reserved-identifier) */
                    __LocalContainsOfCompositeClient <
                            __ServerType,
                            __ValueType,
                            std :: initializer_list < __ValueType >,
                            __initializerListContains <
                                    __ValueType,
                                    & cds :: meta :: equals < __ValueType >
                            >
                    >;


            template <
                    typename __ServerType,                                      /* NOLINT(bugprone-reserved-identifier) */
                    typename __KeyType,                                         /* NOLINT(bugprone-reserved-identifier) */
                    typename __ValueType,                                       /* NOLINT(bugprone-reserved-identifier) */
                    typename __Hasher                                           /* NOLINT(bugprone-reserved-identifier) */
            > using __LinkedHashMapValueProxyDelegateForwardIterableClient =    /* NOLINT(bugprone-reserved-identifier) */
                    __LocalDelegateForwardIterablePrimitiveClient <
                            __ServerType,
                            __LinkedHashMapValueProxyIterator < __KeyType, __ValueType, __Hasher >
                    >;


            template <
                    typename __ServerType,                                          /* NOLINT(bugprone-reserved-identifier) */
                    typename __KeyType,                                             /* NOLINT(bugprone-reserved-identifier) */
                    typename __ValueType,                                           /* NOLINT(bugprone-reserved-identifier) */
                    typename __Hasher                                               /* NOLINT(bugprone-reserved-identifier) */
            > using __LinkedHashMapValueProxyDelegateForwardConstIterableClient =   /* NOLINT(bugprone-reserved-identifier) */
                    __LocalDelegateForwardConstIterablePrimitiveClient <
                            __ServerType,
                            __LinkedHashMapValueProxyConstIterator < __KeyType, __ValueType, __Hasher >
                    >;

        }
    }

    template <
            typename __KeyType,     /* NOLINT(bugprone-reserved-identifier) */
            typename __ValueType,   /* NOLINT(bugprone-reserved-identifier) */
            typename __Hasher       /* NOLINT(bugprone-reserved-identifier) */
    > class LinkedHashMap <
            __KeyType,
            __ValueType,
            __Hasher
    > :: ValueMutableCollectionProxy :
            public AbstractValueMutableCollectionProxy,
            protected __hidden :: __impl :: __LinkedHashMapValueProxyServer < ValueMutableCollectionProxy, __KeyType, __ValueType, __Hasher >,
            public __hidden :: __impl :: __LinkedHashMapValueProxyRandomInsertionClient < KeySetProxy, __KeyType, __ValueType, __Hasher >,
            public __hidden :: __impl :: __LinkedHashMapValueProxyIteratorRemoveClient < KeySetProxy, __KeyType, __ValueType, __Hasher >,
            public __hidden :: __impl :: __LinkedHashMapValueProxyConstIteratorRemoveClient < KeySetProxy, __KeyType, __ValueType, __Hasher >,
            public __hidden :: __impl :: __LinkedHashMapValueProxyFindOfCollectionClient < KeySetProxy, __KeyType, __ValueType, __Hasher >,
            public __hidden :: __impl :: __LinkedHashMapValueProxyFindOfConstCollectionClient < KeySetProxy, __KeyType, __ValueType, __Hasher >,
            public __hidden :: __impl :: __LinkedHashMapValueProxyFindOfInitializerListClient < KeySetProxy, __KeyType, __ValueType, __Hasher >,
            public __hidden :: __impl :: __LinkedHashMapValueProxyFindOfConstInitializerListClient < KeySetProxy, __KeyType, __ValueType, __Hasher >,
            public __hidden :: __impl :: __LinkedHashMapValueProxyFindByClient < KeySetProxy, __KeyType, __ValueType, __Hasher >,
            public __hidden :: __impl :: __LinkedHashMapValueProxyConstFindByClient < KeySetProxy, __KeyType, __ValueType, __Hasher >,
            public __hidden :: __impl :: __LinkedHashMapValueProxyRemoveOfCollectionClient < KeySetProxy, __KeyType, __ValueType, __Hasher >,
            public __hidden :: __impl :: __LinkedHashMapValueProxyRemoveOfInitializerListClient < KeySetProxy, __KeyType, __ValueType, __Hasher >,
            public __hidden :: __impl :: __LinkedHashMapValueProxyRemoveByClient < KeySetProxy, __KeyType, __ValueType, __Hasher >,
            public __hidden :: __impl :: __LinkedHashMapValueProxyGenericStatementsClient < KeySetProxy, __KeyType, __ValueType, __Hasher >,
            public __hidden :: __impl :: __LinkedHashMapValueProxyConstGenericStatementsClient < KeySetProxy, __KeyType, __ValueType, __Hasher >,
            public __hidden :: __impl :: __LinkedHashMapValueProxyContainsOfCollectionClient < KeySetProxy, __KeyType, __ValueType, __Hasher >,
            public __hidden :: __impl :: __LinkedHashMapValueProxyContainsOfInitializerListClient < KeySetProxy, __KeyType, __ValueType, __Hasher >,
            public __hidden :: __impl :: __LinkedHashMapValueProxyDelegateForwardIterableClient < KeySetProxy, __KeyType, __ValueType, __Hasher >,
            public __hidden :: __impl :: __LinkedHashMapValueProxyDelegateForwardConstIterableClient < KeySetProxy, __KeyType, __ValueType, __Hasher > {

    protected:  using LinkedHashMapBase                     = LinkedHashMap < __KeyType, __ValueType, __Hasher >;
    protected:  using Server                                = __hidden :: __impl :: __LinkedHashMapValueProxyServer < ValueMutableCollectionProxy, __KeyType, __ValueType, __Hasher >;
    protected:  using RandomInsertionClient                 = __hidden :: __impl :: __LinkedHashMapValueProxyRandomInsertionClient < KeySetProxy, __KeyType, __ValueType, __Hasher >;
    protected:  using IteratorRemoveClient                  = __hidden :: __impl :: __LinkedHashMapValueProxyIteratorRemoveClient < KeySetProxy, __KeyType, __ValueType, __Hasher >;
    protected:  using ConstIteratorRemoveClient             = __hidden :: __impl :: __LinkedHashMapValueProxyConstIteratorRemoveClient < KeySetProxy, __KeyType, __ValueType, __Hasher >;
    protected:  using FindOfCollectionClient                = __hidden :: __impl :: __LinkedHashMapValueProxyFindOfCollectionClient < KeySetProxy, __KeyType, __ValueType, __Hasher >;
    protected:  using ConstFindOfCollectionClient           = __hidden :: __impl :: __LinkedHashMapValueProxyFindOfConstCollectionClient < KeySetProxy, __KeyType, __ValueType, __Hasher >;
    protected:  using FindOfInitializerListClient           = __hidden :: __impl :: __LinkedHashMapValueProxyFindOfInitializerListClient < KeySetProxy, __KeyType, __ValueType, __Hasher >;
    protected:  using ConstFindOfInitializerListClient      = __hidden :: __impl :: __LinkedHashMapValueProxyFindOfConstInitializerListClient < KeySetProxy, __KeyType, __ValueType, __Hasher >;
    protected:  using FindByClient                          = __hidden :: __impl :: __LinkedHashMapValueProxyFindByClient < KeySetProxy, __KeyType, __ValueType, __Hasher >;
    protected:  using ConstFindByClient                     = __hidden :: __impl :: __LinkedHashMapValueProxyConstFindByClient < KeySetProxy, __KeyType, __ValueType, __Hasher >;
    protected:  using RemoveOfCollectionClient              = __hidden :: __impl :: __LinkedHashMapValueProxyRemoveOfCollectionClient < KeySetProxy, __KeyType, __ValueType, __Hasher >;
    protected:  using RemoveOfInitializerListClient         = __hidden :: __impl :: __LinkedHashMapValueProxyRemoveOfInitializerListClient < KeySetProxy, __KeyType, __ValueType, __Hasher >;
    protected:  using RemoveByClient                        = __hidden :: __impl :: __LinkedHashMapValueProxyRemoveByClient < KeySetProxy, __KeyType, __ValueType, __Hasher >;
    protected:  using GenericStatementsClient               = __hidden :: __impl :: __LinkedHashMapValueProxyGenericStatementsClient < KeySetProxy, __KeyType, __ValueType, __Hasher >;
    protected:  using ContainsOfCollectionClient            = __hidden :: __impl :: __LinkedHashMapValueProxyContainsOfCollectionClient < KeySetProxy, __KeyType, __ValueType, __Hasher >;
    protected:  using ContainsOfInitializerListClient       = __hidden :: __impl :: __LinkedHashMapValueProxyContainsOfInitializerListClient < KeySetProxy, __KeyType, __ValueType, __Hasher >;
    protected:  using ConstGenericStatementsClient          = __hidden :: __impl :: __LinkedHashMapValueProxyConstGenericStatementsClient < KeySetProxy, __KeyType, __ValueType, __Hasher >;
    protected:  using DelegateForwardIterableClient         = __hidden :: __impl :: __LinkedHashMapValueProxyDelegateForwardIterableClient < KeySetProxy, __KeyType, __ValueType, __Hasher >;
    protected:  using DelegateForwardConstIterableClient    = __hidden :: __impl :: __LinkedHashMapValueProxyDelegateForwardConstIterableClient < KeySetProxy, __KeyType, __ValueType, __Hasher >;

    protected:  using typename AbstractValueMutableCollectionProxy :: __GenericHandler;         /* NOLINT(bugprone-reserved-identifier) */
    protected:  using typename AbstractValueMutableCollectionProxy :: __GenericConstHandler;    /* NOLINT(bugprone-reserved-identifier) */

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

    public:     using ContainsOfCollectionClient :: containsAnyOf;
    public:     using ContainsOfCollectionClient :: containsAnyNotOf;
    public:     using ContainsOfCollectionClient :: containsAllOf;
    public:     using ContainsOfCollectionClient :: containsNoneOf;

    public:     using ContainsOfInitializerListClient :: containsAnyOf;
    public:     using ContainsOfInitializerListClient :: containsAnyNotOf;
    public:     using ContainsOfInitializerListClient :: containsAllOf;
    public:     using ContainsOfInitializerListClient :: containsNoneOf;

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
        __CDS_Explicit constexpr ValueMutableCollectionProxy (
                LinkedHashMap < __KeyType, __ValueType, __Hasher > * pMap
        ) noexcept;

    public:
        ValueMutableCollectionProxy (
                ValueMutableCollectionProxy const &
        ) noexcept = delete;

    public:
        ValueMutableCollectionProxy (
                ValueMutableCollectionProxy &&
        ) noexcept = delete;

    public:
        __CDS_cpplang_ConstexprDestructor ~ValueMutableCollectionProxy() noexcept override;

    public:
        auto operator = (
                ValueMutableCollectionProxy const &
        ) noexcept -> ValueMutableCollectionProxy & = delete;

    public:
        auto operator = (
                ValueMutableCollectionProxy &&
        ) noexcept -> ValueMutableCollectionProxy & = delete;

    private:
        __CDS_NoDiscard auto __begin () noexcept -> __hidden :: __impl :: __AbstractDelegateIterator < __ValueType > *; /* NOLINT(bugprone-reserved-identifier) */

    private:
        __CDS_NoDiscard auto __end () noexcept -> __hidden :: __impl :: __AbstractDelegateIterator < __ValueType > *; /* NOLINT(bugprone-reserved-identifier) */

    private:
        __CDS_NoDiscard auto __cbegin () const noexcept -> __hidden :: __impl :: __AbstractDelegateIterator < __ValueType const > *; /* NOLINT(bugprone-reserved-identifier) */

    private:
        __CDS_NoDiscard auto __cend () const noexcept -> __hidden :: __impl :: __AbstractDelegateIterator < __ValueType const > *; /* NOLINT(bugprone-reserved-identifier) */

    private:
        __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction auto __beginLocal () noexcept -> Iterator; /* NOLINT(bugprone-reserved-identifier) */

    private:
        __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction auto __endLocal () noexcept -> Iterator; /* NOLINT(bugprone-reserved-identifier) */

    private:
        __CDS_NoDiscard constexpr auto __cbeginLocal () const noexcept -> ConstIterator; /* NOLINT(bugprone-reserved-identifier) */

    private:
        __CDS_NoDiscard constexpr auto __cendLocal () const noexcept -> ConstIterator; /* NOLINT(bugprone-reserved-identifier) */

    protected:
        auto __remove ( /* NOLINT(bugprone-reserved-identifier) */
                Iterator const * iterator
        ) noexcept -> bool;

    protected:
        auto __removeConst (    /* NOLINT(bugprone-reserved-identifier) */
                ConstIterator const * iterator
        ) noexcept -> bool;

    protected:
        auto __removeArray ( /* NOLINT(bugprone-reserved-identifier) */
                Iterator    const * const * ppIterators,
                Size                        iteratorArrayCount
        ) noexcept -> Size;

    protected:
        auto __removeConstArray (    /* NOLINT(bugprone-reserved-identifier) */
                ConstIterator   const * const * ppIterators,
                Size                            iteratorArrayCount
        ) noexcept -> Size;

    private:
        __CDS_NoDiscard auto __equals ( /* NOLINT(bugprone-reserved-identifier) */
                ValueMutableCollectionProxy const & set
        ) const noexcept -> bool;

    public:
        __CDS_NoDiscard auto operator == (
                ValueMutableCollectionProxy const & set
        ) const noexcept -> bool;

    public:
        __CDS_NoDiscard auto operator != (
                ValueMutableCollectionProxy const & set
        ) const noexcept -> bool;
    };
    
}

#endif /* __CDS_LINKED_HASH_MAP_VALUE_MUTABLE_COLLECTION_PROXY_HPP__ */
