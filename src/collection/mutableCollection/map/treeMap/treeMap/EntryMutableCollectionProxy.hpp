//
// Created by stefan on 13.10.2022.
//

#ifndef __CDS_TREE_MAP_ENTRY_MUTABLE_COLLECTION_PROXY_HPP_
#define __CDS_TREE_MAP_ENTRY_MUTABLE_COLLECTION_PROXY_HPP_  /* NOLINT(bugprone-reserved-identifier) */

namespace cds { /* NOLINT(modernize-concat-nested-namespaces) */
    namespace __hidden {    /* NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier) */
        namespace __impl {  /* NOLINT(bugprone-reserved-identifier) */



            template <
                    typename __ServerType,               /* NOLINT(bugprone-reserved-identifier) */
                    typename __KeyType,                  /* NOLINT(bugprone-reserved-identifier) */
                    typename __ValueType,                /* NOLINT(bugprone-reserved-identifier) */
                    typename __Comparator,               /* NOLINT(bugprone-reserved-identifier) */
                    typename __TreeMap =                 /* NOLINT(bugprone-reserved-identifier) */
                            cds :: TreeMap <
                                    __KeyType,
                                    __ValueType,
                                    __Comparator
                            >
            > using __TreeMapEntryProxyServer =          /* NOLINT(bugprone-reserved-identifier) */
                    __MutableCollectionServer <
                            __ServerType,
                            typename __TreeMap :: EntryType
                    >;


            template <
                    typename __ServerType,               /* NOLINT(bugprone-reserved-identifier) */
                    typename __KeyType,                  /* NOLINT(bugprone-reserved-identifier) */
                    typename __ValueType,                /* NOLINT(bugprone-reserved-identifier) */
                    typename __Comparator,               /* NOLINT(bugprone-reserved-identifier) */
                    typename __TreeMap =                 /* NOLINT(bugprone-reserved-identifier) */
                            cds :: TreeMap <
                                    __KeyType,
                                    __ValueType,
                                    __Comparator
                            >
            > using __TreeMapEntryProxyConstIteratorRemoveClient =      /* NOLINT(bugprone-reserved-identifier) */
                    __LocalConstIteratorRemovePrimitiveClient <
                            __ServerType,
                            typename __TreeMap :: EntryType,
                            typename __TreeMapImplementation < __KeyType, __ValueType, __Comparator > :: __rbt_AbstractConstIterator
                    >;


            template <
                    typename __ServerType,      /* NOLINT(bugprone-reserved-identifier) */
                    typename __KeyType,         /* NOLINT(bugprone-reserved-identifier) */
                    typename __ValueType,       /* NOLINT(bugprone-reserved-identifier) */
                    typename __Comparator       /* NOLINT(bugprone-reserved-identifier) */
            > using __TreeMapEntryProxyIteratorRemoveClient =      /* NOLINT(bugprone-reserved-identifier) */
                    __LocalIteratorRemovePrimitiveClient <
                            __ServerType,
                            __ValueType,
                            typename __TreeMapImplementation < __KeyType, __ValueType, __Comparator > :: __rbt_AbstractIterator
                    >;


            template <
                    typename __ServerType,                    /* NOLINT(bugprone-reserved-identifier) */
                    typename __KeyType,                       /* NOLINT(bugprone-reserved-identifier) */
                    typename __ValueType,                     /* NOLINT(bugprone-reserved-identifier) */
                    typename __Comparator                     /* NOLINT(bugprone-reserved-identifier) */
            > using __TreeMapEntryProxyDelegateBackwardConstIterableClient =        /* NOLINT(bugprone-reserved-identifier) */
                    cds :: __hidden :: __impl :: __LocalDelegateBackwardConstIterablePrimitiveClient  <
                            __ServerType,
                            typename __TreeMapImplementation < __KeyType, __ValueType, __Comparator > :: __rbt_ReverseConstIterator
                    >;


            template <
                    typename __ServerType,                    /* NOLINT(bugprone-reserved-identifier) */
                    typename __KeyType,                       /* NOLINT(bugprone-reserved-identifier) */
                    typename __ValueType,                     /* NOLINT(bugprone-reserved-identifier) */
                    typename __Comparator                     /* NOLINT(bugprone-reserved-identifier) */
            > using __TreeMapEntryProxyDelegateBackwardIterableClient =         /* NOLINT(bugprone-reserved-identifier) */
                    cds :: __hidden :: __impl :: __LocalDelegateBackwardIterablePrimitiveClient  <
                            __ServerType,
                            typename __TreeMapImplementation < __KeyType, __ValueType, __Comparator > :: __rbt_ReverseIterator
                    >;


            template <
                    typename __ServerType,                    /* NOLINT(bugprone-reserved-identifier) */
                    typename __KeyType,                       /* NOLINT(bugprone-reserved-identifier) */
                    typename __ValueType,                     /* NOLINT(bugprone-reserved-identifier) */
                    typename __Comparator                     /* NOLINT(bugprone-reserved-identifier) */
            > using __TreeMapEntryProxyDelegateForwardConstIterableClient =     /* NOLINT(bugprone-reserved-identifier) */
                    __LocalDelegateForwardConstIterablePrimitiveClient  <
                            __ServerType,
                            typename __TreeMapImplementation < __KeyType, __ValueType, __Comparator > :: __rbt_ConstIterator
                    >;


            template <
                    typename __ServerType,              /* NOLINT(bugprone-reserved-identifier) */
                    typename __KeyType,                 /* NOLINT(bugprone-reserved-identifier) */
                    typename __ValueType,                /* NOLINT(bugprone-reserved-identifier) */
                    typename __Comparator                /* NOLINT(bugprone-reserved-identifier) */
            > using __TreeMapEntryProxyDelegateForwardIterableClient =      /* NOLINT(bugprone-reserved-identifier) */
                    cds :: __hidden :: __impl :: __LocalDelegateForwardIterablePrimitiveClient  <
                            __ServerType,
                            typename __TreeMapImplementation < __KeyType, __ValueType, __Comparator > :: __rbt_Iterator
                    >;


            template <
                    typename __ServerType,               /* NOLINT(bugprone-reserved-identifier) */
                    typename __KeyType,                  /* NOLINT(bugprone-reserved-identifier) */
                    typename __ValueType,                /* NOLINT(bugprone-reserved-identifier) */
                    typename __Comparator,               /* NOLINT(bugprone-reserved-identifier) */
                    typename __TreeMap =                 /* NOLINT(bugprone-reserved-identifier) */
                            cds :: TreeMap <
                                    __KeyType,
                                    __ValueType,
                                    __Comparator
                            >
            > using __TreeMapEntryProxyRandomInsertionClient =      /* NOLINT(bugprone-reserved-identifier) */
                    __LocalRandomInsertionPrimitiveClient <
                            __ServerType,
                            typename __TreeMap :: EntryType,
                            typename __TreeMap :: EntryType const
                    >;


            template <
                    typename __ServerType,               /* NOLINT(bugprone-reserved-identifier) */
                    typename __KeyType,                  /* NOLINT(bugprone-reserved-identifier) */
                    typename __ValueType,                /* NOLINT(bugprone-reserved-identifier) */
                    typename __Comparator,               /* NOLINT(bugprone-reserved-identifier) */
                    typename __TreeMap =                 /* NOLINT(bugprone-reserved-identifier) */
                            cds :: TreeMap <
                                    __KeyType,
                                    __ValueType,
                                    __Comparator
                            >
            > using __TreeMapEntryProxyContainsOfCollectionClient =     /* NOLINT(bugprone-reserved-identifier) */
                    __LocalContainsOfCompositeClient <
                            __ServerType,
                            typename __TreeMap :: EntryType,
                            cds :: Iterable < typename __TreeMap :: EntryType >,
                            & cds :: __hidden :: __impl :: __iterableContains < typename __TreeMap :: EntryType  >
                    >;


            template <
                    typename __ServerType,               /* NOLINT(bugprone-reserved-identifier) */
                    typename __KeyType,                  /* NOLINT(bugprone-reserved-identifier) */
                    typename __ValueType,                /* NOLINT(bugprone-reserved-identifier) */
                    typename __Comparator,               /* NOLINT(bugprone-reserved-identifier) */
                    typename __TreeMap =                 /* NOLINT(bugprone-reserved-identifier) */
                            cds :: TreeMap <
                                    __KeyType,
                                    __ValueType,
                                    __Comparator
                            >
            > using __TreeMapEntryProxyContainsOfInitializerListClient =     /* NOLINT(bugprone-reserved-identifier) */
                    cds :: __hidden :: __impl :: __LocalContainsOfCompositeClient <
                            __ServerType,
                            typename __TreeMap :: EntryType,
                            std :: initializer_list < typename __TreeMap :: EntryType >,
                            & cds :: __hidden :: __impl :: __initializerListContains <
                                    typename __TreeMap :: EntryType,
                                    & cds :: meta :: equals < typename __TreeMap :: EntryType >
                            >
                    >;


            template <
                    typename __ServerType,               /* NOLINT(bugprone-reserved-identifier) */
                    typename __KeyType,                  /* NOLINT(bugprone-reserved-identifier) */
                    typename __ValueType,                /* NOLINT(bugprone-reserved-identifier) */
                    typename __Comparator,               /* NOLINT(bugprone-reserved-identifier) */
                    typename __TreeMap =                 /* NOLINT(bugprone-reserved-identifier) */
                            cds :: TreeMap <
                                    __KeyType,
                                    __ValueType,
                                    __Comparator
                            >
            > using __TreeMapEntryProxyFindByImmutableClient =      /* NOLINT(bugprone-reserved-identifier) */
                    __LocalFindByImmutableCompositeClient <
                            __ServerType,
                            typename __TreeMap :: EntryType,
                            typename __TreeMapImplementation < __KeyType, __ValueType, __Comparator > :: __rbt_AbstractConstIterator
                    >;


            template <
                    typename __ServerType,               /* NOLINT(bugprone-reserved-identifier) */
                    typename __KeyType,                  /* NOLINT(bugprone-reserved-identifier) */
                    typename __ValueType,                /* NOLINT(bugprone-reserved-identifier) */
                    typename __Comparator,               /* NOLINT(bugprone-reserved-identifier) */
                    typename __TreeMap =                 /* NOLINT(bugprone-reserved-identifier) */
                            cds :: TreeMap <
                                    __KeyType,
                                    __ValueType,
                                    __Comparator
                            >
            > using __TreeMapEntryProxyFindByMutableClient =      /* NOLINT(bugprone-reserved-identifier) */
                    __LocalFindByMutableCompositeClient <
                            __ServerType,
                            typename __TreeMap :: EntryType,
                            typename __TreeMapImplementation < __KeyType, __ValueType, __Comparator > :: __rbt_AbstractIterator
                    >;


            template <
                    typename __ServerType,               /* NOLINT(bugprone-reserved-identifier) */
                    typename __KeyType,                  /* NOLINT(bugprone-reserved-identifier) */
                    typename __ValueType,                /* NOLINT(bugprone-reserved-identifier) */
                    typename __Comparator,               /* NOLINT(bugprone-reserved-identifier) */
                    typename __TreeMap =                 /* NOLINT(bugprone-reserved-identifier) */
                            cds :: TreeMap <
                                    __KeyType,
                                    __ValueType,
                                    __Comparator
                            >
            > using __TreeMapEntryProxyFindOfConstCollectionClient =        /* NOLINT(bugprone-reserved-identifier) */
                    __LocalFindOfImmutableCompositeClient <
                            __ServerType,
                            typename __TreeMap :: EntryType,
                            typename __TreeMapImplementation < __KeyType, __ValueType, __Comparator > :: __rbt_AbstractConstIterator,
                            cds :: Iterable < typename __TreeMap :: EntryType >,
                            & cds :: __hidden :: __impl :: __iterableContains < typename __TreeMap :: EntryType  >,
                            & cds :: __hidden :: __impl :: __iterableNotContains < typename __TreeMap :: EntryType  >
                    >;


            template <
                    typename __ServerType,               /* NOLINT(bugprone-reserved-identifier) */
                    typename __KeyType,                  /* NOLINT(bugprone-reserved-identifier) */
                    typename __ValueType,                /* NOLINT(bugprone-reserved-identifier) */
                    typename __Comparator,               /* NOLINT(bugprone-reserved-identifier) */
                    typename __TreeMap =                 /* NOLINT(bugprone-reserved-identifier) */
                            cds :: TreeMap <
                                    __KeyType,
                                    __ValueType,
                                    __Comparator
                            >
            > using __TreeMapEntryProxyFindOfConstInitializerListClient =        /* NOLINT(bugprone-reserved-identifier) */
                    __LocalFindOfImmutableCompositeClient <
                            __ServerType,
                            typename __TreeMap :: EntryType,
                            typename __TreeMapImplementation < __KeyType, __ValueType, __Comparator > :: __rbt_AbstractConstIterator,
                            std :: initializer_list < typename __TreeMap :: EntryType >,
                            & cds :: __hidden :: __impl :: __initializerListContains <
                                    typename __TreeMap :: EntryType,
                                    & cds :: meta :: equals < typename __TreeMap :: EntryType >
                            >,
                            & cds :: __hidden :: __impl :: __initializerListNotContains <
                                    typename __TreeMap :: EntryType,
                                    & cds :: meta :: equals < typename __TreeMap :: EntryType >
                            >
                    >;


            template <
                    typename __ServerType,               /* NOLINT(bugprone-reserved-identifier) */
                    typename __KeyType,                  /* NOLINT(bugprone-reserved-identifier) */
                    typename __ValueType,                /* NOLINT(bugprone-reserved-identifier) */
                    typename __Comparator,               /* NOLINT(bugprone-reserved-identifier) */
                    typename __TreeMap =                 /* NOLINT(bugprone-reserved-identifier) */
                            cds :: TreeMap <
                                    __KeyType,
                                    __ValueType,
                                    __Comparator
                            >
            > using __TreeMapEntryProxyFindOfCollectionClient =        /* NOLINT(bugprone-reserved-identifier) */
                    __LocalFindOfImmutableCompositeClient <
                            __ServerType,
                            typename __TreeMap :: EntryType,
                            typename __TreeMapImplementation < __KeyType, __ValueType, __Comparator > :: __rbt_AbstractIterator,
                            cds :: Iterable < typename __TreeMap :: EntryType >,
                            & cds :: __hidden :: __impl :: __iterableContains < typename __TreeMap :: EntryType  >,
                            & cds :: __hidden :: __impl :: __iterableNotContains < typename __TreeMap :: EntryType  >
                    >;


            template <
                    typename __ServerType,               /* NOLINT(bugprone-reserved-identifier) */
                    typename __KeyType,                  /* NOLINT(bugprone-reserved-identifier) */
                    typename __ValueType,                /* NOLINT(bugprone-reserved-identifier) */
                    typename __Comparator,               /* NOLINT(bugprone-reserved-identifier) */
                    typename __TreeMap =                 /* NOLINT(bugprone-reserved-identifier) */
                            cds :: TreeMap <
                                    __KeyType,
                                    __ValueType,
                                    __Comparator
                            >
            > using __TreeMapEntryProxyFindOfInitializerListClient =        /* NOLINT(bugprone-reserved-identifier) */
                    __LocalFindOfImmutableCompositeClient <
                            __ServerType,
                            typename __TreeMap :: EntryType,
                            typename __TreeMapImplementation < __KeyType, __ValueType, __Comparator > :: __rbt_AbstractIterator,
                            std :: initializer_list < typename __TreeMap :: EntryType >,
                            & cds :: __hidden :: __impl :: __initializerListContains <
                                    typename __TreeMap :: EntryType,
                                    & cds :: meta :: equals < typename __TreeMap :: EntryType >
                            >,
                            & cds :: __hidden :: __impl :: __initializerListNotContains <
                                    typename __TreeMap :: EntryType,
                                    & cds :: meta :: equals < typename __TreeMap :: EntryType >
                            >
                    >;


            template <
                    typename __ServerType,               /* NOLINT(bugprone-reserved-identifier) */
                    typename __KeyType,                  /* NOLINT(bugprone-reserved-identifier) */
                    typename __ValueType,                /* NOLINT(bugprone-reserved-identifier) */
                    typename __Comparator,               /* NOLINT(bugprone-reserved-identifier) */
                    typename __TreeMap =                 /* NOLINT(bugprone-reserved-identifier) */
                            cds :: TreeMap <
                                    __KeyType,
                                    __ValueType,
                                    __Comparator
                            >
            > using __TreeMapEntryProxyConstGenericStatementsClient =       /* NOLINT(bugprone-reserved-identifier) */
                    __LocalGenericImmutableStatementsCompositeClient <
                            __ServerType,
                            typename __TreeMap :: EntryType
                    >;


            template <
                    typename __ServerType,               /* NOLINT(bugprone-reserved-identifier) */
                    typename __KeyType,                  /* NOLINT(bugprone-reserved-identifier) */
                    typename __ValueType,                /* NOLINT(bugprone-reserved-identifier) */
                    typename __Comparator,               /* NOLINT(bugprone-reserved-identifier) */
                    typename __TreeMap =                 /* NOLINT(bugprone-reserved-identifier) */
                            cds :: TreeMap <
                                    __KeyType,
                                    __ValueType,
                                    __Comparator
                            >
            > using __TreeMapEntryProxyGenericStatementsClient =       /* NOLINT(bugprone-reserved-identifier) */
                    __LocalGenericMutableStatementsCompositeClient <
                            __ServerType,
                            typename __TreeMap :: EntryType
                    >;


            template <
                    typename __ServerType,               /* NOLINT(bugprone-reserved-identifier) */
                    typename __KeyType,                  /* NOLINT(bugprone-reserved-identifier) */
                    typename __ValueType,                /* NOLINT(bugprone-reserved-identifier) */
                    typename __Comparator,               /* NOLINT(bugprone-reserved-identifier) */
                    typename __TreeMap =                 /* NOLINT(bugprone-reserved-identifier) */
                            cds :: TreeMap <
                                    __KeyType,
                                    __ValueType,
                                    __Comparator
                            >
            > using __TreeMapEntryProxyRemoveByClient =       /* NOLINT(bugprone-reserved-identifier) */
                    __LocalRemoveByCompositeClient <
                            __ServerType,
                            typename __TreeMap :: EntryType
                    >;


            template <
                    typename __ServerType,               /* NOLINT(bugprone-reserved-identifier) */
                    typename __KeyType,                  /* NOLINT(bugprone-reserved-identifier) */
                    typename __ValueType,                /* NOLINT(bugprone-reserved-identifier) */
                    typename __Comparator,               /* NOLINT(bugprone-reserved-identifier) */
                    typename __TreeMap =                 /* NOLINT(bugprone-reserved-identifier) */
                            cds :: TreeMap <
                                    __KeyType,
                                    __ValueType,
                                    __Comparator
                            >
            > using __TreeMapEntryProxyRemoveOfCollectionClient =     /* NOLINT(bugprone-reserved-identifier) */
                    __LocalRemoveOfCompositeClient <
                            __ServerType,
                            typename __TreeMap :: EntryType,
                            cds :: Iterable < typename __TreeMap :: EntryType >,
                            & cds :: __hidden :: __impl :: __iterableContains < typename __TreeMap :: EntryType  >
                    >;


            template <
                    typename __ServerType,               /* NOLINT(bugprone-reserved-identifier) */
                    typename __KeyType,                  /* NOLINT(bugprone-reserved-identifier) */
                    typename __ValueType,                /* NOLINT(bugprone-reserved-identifier) */
                    typename __Comparator,               /* NOLINT(bugprone-reserved-identifier) */
                    typename __TreeMap =                 /* NOLINT(bugprone-reserved-identifier) */
                            cds :: TreeMap <
                                    __KeyType,
                                    __ValueType,
                                    __Comparator
                            >
            > using __TreeMapEntryProxyRemoveOfInitializerListClient =     /* NOLINT(bugprone-reserved-identifier) */
                    __LocalRemoveOfCompositeClient <
                            __ServerType,
                            typename __TreeMap :: EntryType,
                            std :: initializer_list < typename __TreeMap :: EntryType >,
                            & cds :: __hidden :: __impl :: __initializerListContains <
                                    typename __TreeMap :: EntryType,
                                    & cds :: meta :: equals < typename __TreeMap :: EntryType >
                            >
                    >;

        }
    }

    template <
            typename __KeyType,     /* NOLINT(bugprone-reserved-identifier) */
            typename __ValueType,   /* NOLINT(bugprone-reserved-identifier) */
            typename __Comparator   /* NOLINT(bugprone-reserved-identifier) */
    > class __CDS_InheritsEBOs TreeMap <
            __KeyType,
            __ValueType,
            __Comparator
    > :: EntryMutableCollectionProxy :
            public TreeMap < __KeyType, __ValueType, __Comparator > :: AbstractEntryMutableCollectionProxy,
            private __hidden :: __impl :: __TreeMapEntryProxyServer < EntryMutableCollectionProxy, __KeyType, __ValueType, __Comparator >,
            public __hidden :: __impl :: __TreeMapEntryProxyConstIteratorRemoveClient < EntryMutableCollectionProxy, __KeyType, __ValueType, __Comparator >,
            public __hidden :: __impl :: __TreeMapEntryProxyIteratorRemoveClient < EntryMutableCollectionProxy, __KeyType, __ValueType, __Comparator >,
            public __hidden :: __impl :: __TreeMapEntryProxyDelegateBackwardConstIterableClient < EntryMutableCollectionProxy, __KeyType, __ValueType, __Comparator >,
            public __hidden :: __impl :: __TreeMapEntryProxyDelegateBackwardIterableClient < EntryMutableCollectionProxy, __KeyType, __ValueType, __Comparator >,
            public __hidden :: __impl :: __TreeMapEntryProxyDelegateForwardConstIterableClient < EntryMutableCollectionProxy, __KeyType, __ValueType, __Comparator >,
            public __hidden :: __impl :: __TreeMapEntryProxyDelegateForwardIterableClient < EntryMutableCollectionProxy, __KeyType, __ValueType, __Comparator >,
            public __hidden :: __impl :: __TreeMapEntryProxyRandomInsertionClient < EntryMutableCollectionProxy, __KeyType, __ValueType, __Comparator >,
            public __hidden :: __impl :: __TreeMapEntryProxyContainsOfCollectionClient < EntryMutableCollectionProxy, __KeyType, __ValueType, __Comparator >,
            public __hidden :: __impl :: __TreeMapEntryProxyContainsOfInitializerListClient < EntryMutableCollectionProxy, __KeyType, __ValueType, __Comparator >,
            public __hidden :: __impl :: __TreeMapEntryProxyFindByImmutableClient < EntryMutableCollectionProxy, __KeyType, __ValueType, __Comparator >,
            public __hidden :: __impl :: __TreeMapEntryProxyFindByMutableClient < EntryMutableCollectionProxy, __KeyType, __ValueType, __Comparator >,
            public __hidden :: __impl :: __TreeMapEntryProxyFindOfConstCollectionClient < EntryMutableCollectionProxy, __KeyType, __ValueType, __Comparator >,
            public __hidden :: __impl :: __TreeMapEntryProxyFindOfConstInitializerListClient < EntryMutableCollectionProxy, __KeyType, __ValueType, __Comparator >,
            public __hidden :: __impl :: __TreeMapEntryProxyFindOfCollectionClient < EntryMutableCollectionProxy, __KeyType, __ValueType, __Comparator >,
            public __hidden :: __impl :: __TreeMapEntryProxyFindOfInitializerListClient < EntryMutableCollectionProxy, __KeyType, __ValueType, __Comparator >,
            public __hidden :: __impl :: __TreeMapEntryProxyConstGenericStatementsClient < EntryMutableCollectionProxy, __KeyType, __ValueType, __Comparator >,
            public __hidden :: __impl :: __TreeMapEntryProxyGenericStatementsClient < EntryMutableCollectionProxy, __KeyType, __ValueType, __Comparator >,
            public __hidden :: __impl :: __TreeMapEntryProxyRemoveByClient < EntryMutableCollectionProxy, __KeyType, __ValueType, __Comparator >,
            public __hidden :: __impl :: __TreeMapEntryProxyRemoveOfCollectionClient < EntryMutableCollectionProxy, __KeyType, __ValueType, __Comparator >,
            public __hidden :: __impl :: __TreeMapEntryProxyRemoveOfInitializerListClient < EntryMutableCollectionProxy, __KeyType, __ValueType, __Comparator > {

    protected: using TreeMapBase                                = TreeMap < __KeyType, __ValueType, __Comparator >;
    protected: using Server                                     = __hidden::__impl::__TreeMapEntryProxyServer < EntryMutableCollectionProxy, __KeyType, __ValueType, __Comparator >;
    protected: using ConstIteratorRemoveClient                  = __hidden :: __impl :: __TreeMapEntryProxyConstIteratorRemoveClient < EntryMutableCollectionProxy, __KeyType, __ValueType, __Comparator >;
    protected: using IteratorRemoveClient                       = __hidden :: __impl :: __TreeMapEntryProxyIteratorRemoveClient < EntryMutableCollectionProxy, __KeyType, __ValueType, __Comparator >;
    protected: using DelegateBackwardConstIterableClient        = __hidden :: __impl :: __TreeMapEntryProxyDelegateBackwardConstIterableClient < EntryMutableCollectionProxy, __KeyType, __ValueType, __Comparator >;
    protected: using DelegateBackwardIterableClient             = __hidden :: __impl :: __TreeMapEntryProxyDelegateBackwardIterableClient < EntryMutableCollectionProxy, __KeyType, __ValueType, __Comparator >;
    protected: using DelegateForwardConstIterableClient         = __hidden :: __impl :: __TreeMapEntryProxyDelegateForwardConstIterableClient < EntryMutableCollectionProxy, __KeyType, __ValueType, __Comparator >;
    protected: using DelegateForwardIterableClient              = __hidden :: __impl :: __TreeMapEntryProxyDelegateForwardIterableClient < EntryMutableCollectionProxy, __KeyType, __ValueType, __Comparator >;
    protected: using RandomInsertionClient                      = __hidden :: __impl :: __TreeMapEntryProxyRandomInsertionClient < EntryMutableCollectionProxy, __KeyType, __ValueType, __Comparator >;
    protected: using ContainsOfCollectionClient                 = __hidden :: __impl :: __TreeMapEntryProxyContainsOfCollectionClient < EntryMutableCollectionProxy, __KeyType, __ValueType, __Comparator >;
    protected: using ContainsOfInitializerListClient            = __hidden :: __impl :: __TreeMapEntryProxyContainsOfInitializerListClient < EntryMutableCollectionProxy, __KeyType, __ValueType, __Comparator >;
    protected: using FindByImmutableClient                      = __hidden :: __impl :: __TreeMapEntryProxyFindByImmutableClient < EntryMutableCollectionProxy, __KeyType, __ValueType, __Comparator >;
    protected: using FindByMutableClient                        = __hidden :: __impl :: __TreeMapEntryProxyFindByMutableClient < EntryMutableCollectionProxy, __KeyType, __ValueType, __Comparator >;
    protected: using FindOfConstCollectionClient                = __hidden :: __impl :: __TreeMapEntryProxyFindOfConstCollectionClient < EntryMutableCollectionProxy, __KeyType, __ValueType, __Comparator >;
    protected: using FindOfConstInitializerListClient           = __hidden :: __impl :: __TreeMapEntryProxyFindOfConstInitializerListClient < EntryMutableCollectionProxy, __KeyType, __ValueType, __Comparator >;
    protected: using FindOfCollectionClient                     = __hidden :: __impl :: __TreeMapEntryProxyFindOfCollectionClient < EntryMutableCollectionProxy, __KeyType, __ValueType, __Comparator >;
    protected: using FindOfInitializerListClient                = __hidden :: __impl :: __TreeMapEntryProxyFindOfInitializerListClient < EntryMutableCollectionProxy, __KeyType, __ValueType, __Comparator >;
    protected: using ConstGenericStatementsClient               = __hidden :: __impl :: __TreeMapEntryProxyConstGenericStatementsClient < EntryMutableCollectionProxy, __KeyType, __ValueType, __Comparator >;
    protected: using GenericStatementsClient                    = __hidden :: __impl :: __TreeMapEntryProxyGenericStatementsClient < EntryMutableCollectionProxy, __KeyType, __ValueType, __Comparator >;
    protected: using RemoveByClient                             = __hidden :: __impl :: __TreeMapEntryProxyRemoveByClient < EntryMutableCollectionProxy, __KeyType, __ValueType, __Comparator >;
    protected: using RemoveOfCollectionClient                   = __hidden :: __impl :: __TreeMapEntryProxyRemoveOfCollectionClient < EntryMutableCollectionProxy, __KeyType, __ValueType, __Comparator >;
    protected: using RemoveOfInitializerListClient              = __hidden :: __impl :: __TreeMapEntryProxyRemoveOfInitializerListClient < EntryMutableCollectionProxy, __KeyType, __ValueType, __Comparator >;

    private: friend Server;

    private: friend DelegateForwardIterableClient;
    private: friend DelegateBackwardIterableClient;
    private: friend DelegateForwardConstIterableClient;
    private: friend DelegateBackwardConstIterableClient;

    protected: using typename AbstractEntryMutableCollectionProxy :: __GenericHandler;          /* NOLINT(bugprone-reserved-identifier) */
    protected: using typename AbstractEntryMutableCollectionProxy :: __GenericConstHandler;     /* NOLINT(bugprone-reserved-identifier) */

    public: using typename DelegateForwardIterableClient :: Iterator;
    public: using typename DelegateForwardConstIterableClient :: ConstIterator;
    public: using typename DelegateBackwardIterableClient :: ReverseIterator;
    public: using typename DelegateBackwardConstIterableClient :: ConstReverseIterator;
    public: using AbstractIterator = typename IteratorRemoveClient :: Iterator;
    public: using AbstractConstIterator = typename ConstIteratorRemoveClient :: ConstIterator;

    public: using EntryType = typename MapBase :: EntryType;

    public:     using DelegateForwardIterableClient :: begin;
    public:     using DelegateForwardIterableClient :: end;

    public:     using DelegateBackwardIterableClient :: rbegin;
    public:     using DelegateBackwardIterableClient :: rend;

    public:     using DelegateForwardConstIterableClient :: begin;
    public:     using DelegateForwardConstIterableClient :: end;
    public:     using DelegateForwardConstIterableClient :: cbegin;
    public:     using DelegateForwardConstIterableClient :: cend;

    public:     using DelegateBackwardConstIterableClient :: rbegin;
    public:     using DelegateBackwardConstIterableClient :: rend;
    public:     using DelegateBackwardConstIterableClient :: crbegin;
    public:     using DelegateBackwardConstIterableClient :: crend;

    public:     using IteratorRemoveClient :: remove;
    public:     using IteratorRemoveClient :: removeAll;

    public:     using ConstIteratorRemoveClient :: remove;
    public:     using ConstIteratorRemoveClient :: removeAll;

    public:     using RandomInsertionClient :: insert;
    public:     using RandomInsertionClient :: add;
    public:     using RandomInsertionClient :: emplace;
    public:     using RandomInsertionClient :: insertAll;
    public:     using RandomInsertionClient :: insertAllOf;
    public:     using RandomInsertionClient :: addAllOf;

    public:     using ContainsOfCollectionClient :: containsAnyOf;
    public:     using ContainsOfCollectionClient :: containsAnyNotOf;
    public:     using ContainsOfCollectionClient :: containsAllOf;
    public:     using ContainsOfCollectionClient :: containsNoneOf;

    public:     using ContainsOfInitializerListClient :: containsAnyOf;
    public:     using ContainsOfInitializerListClient :: containsAnyNotOf;
    public:     using ContainsOfInitializerListClient :: containsAllOf;
    public:     using ContainsOfInitializerListClient :: containsNoneOf;

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

    public:     using FindOfConstCollectionClient :: findOf;
    public:     using FindOfConstCollectionClient :: findFirstOf;
    public:     using FindOfConstCollectionClient :: findLastOf;
    public:     using FindOfConstCollectionClient :: findAllOf;
    public:     using FindOfConstCollectionClient :: findNotOf;
    public:     using FindOfConstCollectionClient :: findFirstNotOf;
    public:     using FindOfConstCollectionClient :: findLastNotOf;
    public:     using FindOfConstCollectionClient :: findAllNotOf;

    public:     using FindOfConstInitializerListClient :: findOf;
    public:     using FindOfConstInitializerListClient :: findFirstOf;
    public:     using FindOfConstInitializerListClient :: findLastOf;
    public:     using FindOfConstInitializerListClient :: findAllOf;
    public:     using FindOfConstInitializerListClient :: findNotOf;
    public:     using FindOfConstInitializerListClient :: findFirstNotOf;
    public:     using FindOfConstInitializerListClient :: findLastNotOf;
    public:     using FindOfConstInitializerListClient :: findAllNotOf;

    public:     using FindByImmutableClient :: findThat;
    public:     using FindByImmutableClient :: findFirstThat;
    public:     using FindByImmutableClient :: findLastThat;
    public:     using FindByImmutableClient :: findAllThat;

    public:     using FindByMutableClient :: findThat;
    public:     using FindByMutableClient :: findFirstThat;
    public:     using FindByMutableClient :: findLastThat;
    public:     using FindByMutableClient :: findAllThat;

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

    private:
        __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto __iicch_obtainGenericHandler (         /* NOLINT(bugprone-reserved-identifier) */
                cds :: __hidden :: __impl :: __IterableInternalRequestType requestType
        ) noexcept -> __GenericHandler override;

    private:
        __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto __iicch_obtainGenericConstHandler (        /* NOLINT(bugprone-reserved-identifier) */
                cds :: __hidden :: __impl :: __IterableInternalRequestType requestType
        ) const noexcept -> __GenericConstHandler override;

    public:
        __CDS_Explicit EntryMutableCollectionProxy (
                TreeMap < __KeyType, __ValueType, __Comparator > * pMap
        ) noexcept;

    public:
        EntryMutableCollectionProxy () noexcept = delete;

    public:
        EntryMutableCollectionProxy (
                EntryMutableCollectionProxy const &
        ) noexcept = delete;

    public:
        EntryMutableCollectionProxy (
                EntryMutableCollectionProxy &&
        ) noexcept = delete;

    public:
        auto operator = (
                EntryMutableCollectionProxy const &
        ) noexcept = delete;

    public:
        auto operator = (
                EntryMutableCollectionProxy &&
        ) noexcept = delete;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        static auto __newAddress ( /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                EntryMutableCollectionProxy * pObject,
                EntryType const * pReferenceElement,
                bool            * pIsNew
        ) noexcept -> EntryType *;

    public:
        __CDS_NoDiscard constexpr static auto __begin (
                EntryMutableCollectionProxy * pObject
        ) noexcept -> cds :: __hidden :: __impl :: __AbstractDelegateIterator < EntryType > *;     /* NOLINT(bugprone-reserved-identifier) */

    public:
        __CDS_NoDiscard constexpr static auto __end (
                EntryMutableCollectionProxy * pObject
        ) noexcept -> cds :: __hidden :: __impl :: __AbstractDelegateIterator < EntryType > *;     /* NOLINT(bugprone-reserved-identifier) */

    public:
        __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction static auto __beginLocal (
                EntryMutableCollectionProxy * pObject
        ) noexcept -> Iterator;     /* NOLINT(bugprone-reserved-identifier) */

    public:
        __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction static auto __endLocal (
                EntryMutableCollectionProxy * pObject
        ) noexcept -> Iterator;     /* NOLINT(bugprone-reserved-identifier) */

    public:
        __CDS_NoDiscard constexpr static auto __cbegin (
                EntryMutableCollectionProxy const * pObject
        ) noexcept -> cds :: __hidden :: __impl :: __AbstractDelegateIterator < EntryType const > *;     /* NOLINT(bugprone-reserved-identifier) */

    public:
        __CDS_NoDiscard constexpr static auto __cend (
                EntryMutableCollectionProxy const * pObject
        ) noexcept -> cds :: __hidden :: __impl :: __AbstractDelegateIterator < EntryType const > *;     /* NOLINT(bugprone-reserved-identifier) */

    public:
        __CDS_NoDiscard constexpr static auto __cbeginLocal (
                EntryMutableCollectionProxy const * pObject
        ) noexcept -> ConstIterator;     /* NOLINT(bugprone-reserved-identifier) */

    public:
        __CDS_NoDiscard constexpr static auto __cendLocal (
                EntryMutableCollectionProxy const * pObject
        ) noexcept -> ConstIterator;     /* NOLINT(bugprone-reserved-identifier) */

    public:
        __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction static auto __rbeginLocal (
                EntryMutableCollectionProxy * pObject
        ) noexcept -> ReverseIterator;     /* NOLINT(bugprone-reserved-identifier) */

    public:
        __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction static auto __rendLocal (
                EntryMutableCollectionProxy * pObject
        ) noexcept -> ReverseIterator;     /* NOLINT(bugprone-reserved-identifier) */

    public:
        __CDS_NoDiscard constexpr static auto __crbeginLocal (
                EntryMutableCollectionProxy const * pObject
        ) noexcept -> ConstReverseIterator;     /* NOLINT(bugprone-reserved-identifier) */

    public:
        __CDS_NoDiscard constexpr static auto __crendLocal (
                EntryMutableCollectionProxy const * pObject
        ) noexcept -> ConstReverseIterator;     /* NOLINT(bugprone-reserved-identifier) */

    public:
        static auto __remove (     /* NOLINT(bugprone-reserved-identifier) */
                EntryMutableCollectionProxy * pObject,
                AbstractIterator const * iterator
        ) noexcept -> bool;

    public:
        static auto __removeConst (     /* NOLINT(bugprone-reserved-identifier) */
                EntryMutableCollectionProxy * pObject,
                AbstractConstIterator const * iterator
        ) noexcept -> bool;

    public:
        static auto __removeArray (     /* NOLINT(bugprone-reserved-identifier) */
                EntryMutableCollectionProxy * pObject,
                AbstractIterator const * const * ppIterators,
                Size                             iteratorCount
        ) noexcept -> Size;

    public:
        static auto __removeConstArray (     /* NOLINT(bugprone-reserved-identifier) */
                EntryMutableCollectionProxy * pObject,
                AbstractConstIterator const * const * ppIterators,
                Size                                  iteratorCount
        ) noexcept -> Size;
    };

}

#endif //__CDS_TREE_MAP_ENTRY_MUTABLE_COLLECTION_PROXY_HPP_
