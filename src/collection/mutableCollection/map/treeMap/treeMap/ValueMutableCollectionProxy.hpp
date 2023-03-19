//
// Created by stefan on 13.10.2022.
//

#ifndef __CDS_TREE_MAP_VALUE_MUTABLE_COLLECTION_PROXY_HPP_
#define __CDS_TREE_MAP_VALUE_MUTABLE_COLLECTION_PROXY_HPP_  /* NOLINT(bugprone-reserved-identifier) */

namespace cds { /* NOLINT(modernize-concat-nested-namespaces) */
    namespace __hidden {    /* NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier) */
        namespace __impl {  /* NOLINT(bugprone-reserved-identifier) */


            template <
                    typename __ServerType,              /* NOLINT(bugprone-reserved-identifier) */
                    typename __KeyType,                 /* NOLINT(bugprone-reserved-identifier) */
                    typename __ValueType                /* NOLINT(bugprone-reserved-identifier) */
            > using __TreeMapValueProxyServer =         /* NOLINT(bugprone-reserved-identifier) */
                    __MutableCollectionServer <
                            __ServerType,
                            __ValueType
                    >;


            template <
                    typename __DecoratedIteratorType,                                           /* NOLINT(bugprone-reserved-identifier) */
                    typename __ValueAtType                                                      /* NOLINT(bugprone-reserved-identifier) */
            > constexpr auto __treeMapValueMutableCollectionProxyIteratorDecoratorValueAt (     /* NOLINT(bugprone-reserved-identifier) */
                    __DecoratedIteratorType const & iterator
            ) noexcept -> __ValueAtType & {

                return ( * iterator ).value ();
            }


            template <
                    typename __KeyType,         /* NOLINT(bugprone-reserved-identifier) */
                    typename __ValueType,       /* NOLINT(bugprone-reserved-identifier) */
                    typename __Comparator       /* NOLINT(bugprone-reserved-identifier) */
            > using __TreeMapValueProxyAbstractIterator =        /* NOLINT(bugprone-reserved-identifier) */
                    BidirectionalIteratorGenericDecorator <
                            typename __TreeMapImplementation < __KeyType, __ValueType, __Comparator > :: __rbt_AbstractIterator,
                            __ValueType,
                            & __treeMapValueMutableCollectionProxyIteratorDecoratorValueAt <
                                    typename __TreeMapImplementation < __KeyType, __ValueType, __Comparator > :: __rbt_AbstractIterator,
                                    __ValueType
                            >
                    >;


            template <
                    typename __KeyType,         /* NOLINT(bugprone-reserved-identifier) */
                    typename __ValueType,       /* NOLINT(bugprone-reserved-identifier) */
                    typename __Comparator       /* NOLINT(bugprone-reserved-identifier) */
            > using __TreeMapValueProxyAbstractConstIterator =       /* NOLINT(bugprone-reserved-identifier) */
                    BidirectionalIteratorGenericDecorator <
                            typename __TreeMapImplementation < __KeyType, __ValueType, __Comparator > :: __rbt_AbstractConstIterator,
                            __ValueType const,
                            & __treeMapValueMutableCollectionProxyIteratorDecoratorValueAt <
                                    typename __TreeMapImplementation < __KeyType, __ValueType, __Comparator > :: __rbt_AbstractConstIterator,
                                    __ValueType const
                            >
                    >;


            template <
                    typename __KeyType,         /* NOLINT(bugprone-reserved-identifier) */
                    typename __ValueType,       /* NOLINT(bugprone-reserved-identifier) */
                    typename __Comparator       /* NOLINT(bugprone-reserved-identifier) */
            > using __TreeMapValueProxyForwardIterator =        /* NOLINT(bugprone-reserved-identifier) */
                    BidirectionalIteratorGenericDecorator <
                            typename __TreeMapImplementation < __KeyType, __ValueType, __Comparator > :: __rbt_Iterator,
                            __ValueType,
                            & __treeMapValueMutableCollectionProxyIteratorDecoratorValueAt <
                                    typename __TreeMapImplementation < __KeyType, __ValueType, __Comparator > :: __rbt_Iterator,
                                    __ValueType
                            >
                    >;


            template <
                    typename __KeyType,         /* NOLINT(bugprone-reserved-identifier) */
                    typename __ValueType,       /* NOLINT(bugprone-reserved-identifier) */
                    typename __Comparator       /* NOLINT(bugprone-reserved-identifier) */
            > using __TreeMapValueProxyForwardConstIterator =       /* NOLINT(bugprone-reserved-identifier) */
                    BidirectionalIteratorGenericDecorator <
                            typename __TreeMapImplementation < __KeyType, __ValueType, __Comparator > :: __rbt_ConstIterator,
                            __ValueType const,
                            & __treeMapValueMutableCollectionProxyIteratorDecoratorValueAt <
                                    typename __TreeMapImplementation < __KeyType, __ValueType, __Comparator > :: __rbt_ConstIterator,
                                    __ValueType const
                            >
                    >;


            template <
                    typename __KeyType,         /* NOLINT(bugprone-reserved-identifier) */
                    typename __ValueType,       /* NOLINT(bugprone-reserved-identifier) */
                    typename __Comparator       /* NOLINT(bugprone-reserved-identifier) */
            > using __TreeMapValueProxyBackwardIterator =        /* NOLINT(bugprone-reserved-identifier) */
                    BidirectionalIteratorGenericDecorator <
                            typename __TreeMapImplementation < __KeyType, __ValueType, __Comparator > :: __rbt_ReverseIterator,
                            __ValueType,
                            & __treeMapValueMutableCollectionProxyIteratorDecoratorValueAt <
                                    typename __TreeMapImplementation < __KeyType, __ValueType, __Comparator > :: __rbt_ReverseIterator,
                                    __ValueType
                            >
                    >;


            template <
                    typename __KeyType,         /* NOLINT(bugprone-reserved-identifier) */
                    typename __ValueType,       /* NOLINT(bugprone-reserved-identifier) */
                    typename __Comparator       /* NOLINT(bugprone-reserved-identifier) */
            > using __TreeMapValueProxyBackwardConstIterator =       /* NOLINT(bugprone-reserved-identifier) */
                    BidirectionalIteratorGenericDecorator <
                            typename __TreeMapImplementation < __KeyType, __ValueType, __Comparator > :: __rbt_ReverseConstIterator,
                            __ValueType const,
                            & __treeMapValueMutableCollectionProxyIteratorDecoratorValueAt <
                                    typename __TreeMapImplementation < __KeyType, __ValueType, __Comparator > :: __rbt_ReverseConstIterator,
                                    __ValueType const
                            >
                    >;


            template <
                    typename __ServerType,      /* NOLINT(bugprone-reserved-identifier) */
                    typename __KeyType,         /* NOLINT(bugprone-reserved-identifier) */
                    typename __ValueType,       /* NOLINT(bugprone-reserved-identifier) */
                    typename __Comparator       /* NOLINT(bugprone-reserved-identifier) */
            > using __TreeMapValueProxyConstIteratorRemoveClient =      /* NOLINT(bugprone-reserved-identifier) */
                    __LocalConstIteratorRemovePrimitiveClient <
                            __ServerType,
                            __ValueType,
                            __TreeMapValueProxyAbstractConstIterator < __KeyType, __ValueType, __Comparator >
                    >;


            template <
                    typename __ServerType,      /* NOLINT(bugprone-reserved-identifier) */
                    typename __KeyType,         /* NOLINT(bugprone-reserved-identifier) */
                    typename __ValueType,       /* NOLINT(bugprone-reserved-identifier) */
                    typename __Comparator       /* NOLINT(bugprone-reserved-identifier) */
            > using __TreeMapValueProxyIteratorRemoveClient =      /* NOLINT(bugprone-reserved-identifier) */
                    __LocalIteratorRemovePrimitiveClient <
                            __ServerType,
                            __ValueType,
                            __TreeMapValueProxyAbstractIterator < __KeyType, __ValueType, __Comparator >
                    >;


            template <
                    typename __ServerType,      /* NOLINT(bugprone-reserved-identifier) */
                    typename __KeyType,         /* NOLINT(bugprone-reserved-identifier) */
                    typename __ValueType,       /* NOLINT(bugprone-reserved-identifier) */
                    typename __Comparator       /* NOLINT(bugprone-reserved-identifier) */
            > using __TreeMapValueProxyDelegateBackwardConstIterableClient =        /* NOLINT(bugprone-reserved-identifier) */
                    cds :: __hidden :: __impl :: __LocalDelegateBackwardConstIterablePrimitiveClient  <
                            __ServerType,
                            __TreeMapValueProxyBackwardConstIterator < __KeyType, __ValueType, __Comparator >
                    >;


            template <
                    typename __ServerType,      /* NOLINT(bugprone-reserved-identifier) */
                    typename __KeyType,         /* NOLINT(bugprone-reserved-identifier) */
                    typename __ValueType,       /* NOLINT(bugprone-reserved-identifier) */
                    typename __Comparator       /* NOLINT(bugprone-reserved-identifier) */
            > using __TreeMapValueProxyDelegateBackwardIterableClient =         /* NOLINT(bugprone-reserved-identifier) */
                    cds :: __hidden :: __impl :: __LocalDelegateBackwardIterablePrimitiveClient  <
                            __ServerType,
                            __TreeMapValueProxyBackwardIterator < __KeyType, __ValueType, __Comparator >
                    >;


            template <
                    typename __ServerType,      /* NOLINT(bugprone-reserved-identifier) */
                    typename __KeyType,         /* NOLINT(bugprone-reserved-identifier) */
                    typename __ValueType,       /* NOLINT(bugprone-reserved-identifier) */
                    typename __Comparator       /* NOLINT(bugprone-reserved-identifier) */
            > using __TreeMapValueProxyDelegateForwardConstIterableClient =     /* NOLINT(bugprone-reserved-identifier) */
                    __LocalDelegateForwardConstIterablePrimitiveClient  <
                            __ServerType,
                            __TreeMapValueProxyForwardConstIterator < __KeyType, __ValueType, __Comparator >
                    >;


            template <
                    typename __ServerType,      /* NOLINT(bugprone-reserved-identifier) */
                    typename __KeyType,         /* NOLINT(bugprone-reserved-identifier) */
                    typename __ValueType,       /* NOLINT(bugprone-reserved-identifier) */
                    typename __Comparator       /* NOLINT(bugprone-reserved-identifier) */
            > using __TreeMapValueProxyDelegateForwardIterableClient =      /* NOLINT(bugprone-reserved-identifier) */
                    cds :: __hidden :: __impl :: __LocalDelegateForwardIterablePrimitiveClient  <
                            __ServerType,
                            __TreeMapValueProxyForwardIterator < __KeyType, __ValueType, __Comparator >
                    >;


            template <
                    typename __ServerType,                    /* NOLINT(bugprone-reserved-identifier) */
                    typename __KeyType,                       /* NOLINT(bugprone-reserved-identifier) */
                    typename __ValueType,                     /* NOLINT(bugprone-reserved-identifier) */
                    typename __Comparator                     /* NOLINT(bugprone-reserved-identifier) */
            > using __TreeMapValueProxyRandomInsertionClient =      /* NOLINT(bugprone-reserved-identifier) */
                    __LocalRandomInsertionPrimitiveClient <
                            __ServerType,
                            __ValueType,
                            __ValueType const
                    >;


            template <
                    typename __ServerType,      /* NOLINT(bugprone-reserved-identifier) */
                    typename __KeyType,         /* NOLINT(bugprone-reserved-identifier) */
                    typename __ValueType,       /* NOLINT(bugprone-reserved-identifier) */
                    typename __Comparator       /* NOLINT(bugprone-reserved-identifier) */
            > using __TreeMapValueProxyContainsOfCollectionClient =     /* NOLINT(bugprone-reserved-identifier) */
                    __LocalContainsOfCompositeClient <
                            __ServerType,
                            __ValueType,
                            cds :: Iterable < __ValueType >,
                            & cds :: __hidden :: __impl :: __iterableContains < __ValueType  >
                    >;


            template <
                    typename __ServerType,                    /* NOLINT(bugprone-reserved-identifier) */
                    typename __KeyType,                       /* NOLINT(bugprone-reserved-identifier) */
                    typename __ValueType,                     /* NOLINT(bugprone-reserved-identifier) */
                    typename __Comparator                     /* NOLINT(bugprone-reserved-identifier) */
            > using __TreeMapValueProxyContainsOfInitializerListClient =     /* NOLINT(bugprone-reserved-identifier) */
                    cds :: __hidden :: __impl :: __LocalContainsOfCompositeClient <
                            __ServerType,
                            __ValueType,
                            std :: initializer_list < __ValueType >,
                            & cds :: __hidden :: __impl :: __initializerListContains <
                                    __ValueType,
                                    & cds :: meta :: equals < __ValueType >
                            >
                    >;


            template <
                    typename __ServerType,      /* NOLINT(bugprone-reserved-identifier) */
                    typename __KeyType,         /* NOLINT(bugprone-reserved-identifier) */
                    typename __ValueType,       /* NOLINT(bugprone-reserved-identifier) */
                    typename __Comparator       /* NOLINT(bugprone-reserved-identifier) */
            > using __TreeMapValueProxyFindByImmutableClient =      /* NOLINT(bugprone-reserved-identifier) */
                    __LocalFindByImmutableCompositeClient <
                            __ServerType,
                            __ValueType,
                            __TreeMapValueProxyAbstractConstIterator < __KeyType, __ValueType, __Comparator >
                    >;


            template <
                    typename __ServerType,      /* NOLINT(bugprone-reserved-identifier) */
                    typename __KeyType,         /* NOLINT(bugprone-reserved-identifier) */
                    typename __ValueType,       /* NOLINT(bugprone-reserved-identifier) */
                    typename __Comparator       /* NOLINT(bugprone-reserved-identifier) */
            > using __TreeMapValueProxyFindByMutableClient =      /* NOLINT(bugprone-reserved-identifier) */
                    __LocalFindByMutableCompositeClient <
                            __ServerType,
                            __ValueType,
                            __TreeMapValueProxyAbstractIterator < __KeyType, __ValueType, __Comparator >
                    >;


            template <
                    typename __ServerType,      /* NOLINT(bugprone-reserved-identifier) */
                    typename __KeyType,         /* NOLINT(bugprone-reserved-identifier) */
                    typename __ValueType,       /* NOLINT(bugprone-reserved-identifier) */
                    typename __Comparator       /* NOLINT(bugprone-reserved-identifier) */
            > using __TreeMapValueProxyFindOfConstCollectionClient =        /* NOLINT(bugprone-reserved-identifier) */
                    __LocalFindOfImmutableCompositeClient <
                            __ServerType,
                            __ValueType,
                            __TreeMapValueProxyAbstractConstIterator < __KeyType, __ValueType, __Comparator >,
                            cds :: Iterable < __ValueType >,
                            & cds :: __hidden :: __impl :: __iterableContains < __ValueType >,
                            & cds :: __hidden :: __impl :: __iterableNotContains < __ValueType >
                    >;


            template <
                    typename __ServerType,      /* NOLINT(bugprone-reserved-identifier) */
                    typename __KeyType,         /* NOLINT(bugprone-reserved-identifier) */
                    typename __ValueType,       /* NOLINT(bugprone-reserved-identifier) */
                    typename __Comparator       /* NOLINT(bugprone-reserved-identifier) */
            > using __TreeMapValueProxyFindOfConstInitializerListClient =        /* NOLINT(bugprone-reserved-identifier) */
                    __LocalFindOfImmutableCompositeClient <
                            __ServerType,
                            __ValueType,
                            __TreeMapValueProxyAbstractConstIterator < __KeyType, __ValueType, __Comparator >,
                            std :: initializer_list < __ValueType >,
                            & cds :: __hidden :: __impl :: __initializerListContains <
                                    __ValueType,
                                    & cds :: meta :: equals < __ValueType >
                            >,
                            & cds :: __hidden :: __impl :: __initializerListNotContains <
                                    __ValueType,
                                    & cds :: meta :: equals < __ValueType >
                            >
                    >;


            template <
                    typename __ServerType,      /* NOLINT(bugprone-reserved-identifier) */
                    typename __KeyType,         /* NOLINT(bugprone-reserved-identifier) */
                    typename __ValueType,       /* NOLINT(bugprone-reserved-identifier) */
                    typename __Comparator       /* NOLINT(bugprone-reserved-identifier) */
            > using __TreeMapValueProxyFindOfCollectionClient =        /* NOLINT(bugprone-reserved-identifier) */
                    __LocalFindOfImmutableCompositeClient <
                            __ServerType,
                            __ValueType,
                            __TreeMapValueProxyAbstractIterator < __KeyType, __ValueType, __Comparator >,
                            cds :: Iterable < __ValueType >,
                            & cds :: __hidden :: __impl :: __iterableContains < __ValueType >,
                            & cds :: __hidden :: __impl :: __iterableNotContains < __ValueType >
                    >;


            template <
                    typename __ServerType,      /* NOLINT(bugprone-reserved-identifier) */
                    typename __KeyType,         /* NOLINT(bugprone-reserved-identifier) */
                    typename __ValueType,       /* NOLINT(bugprone-reserved-identifier) */
                    typename __Comparator       /* NOLINT(bugprone-reserved-identifier) */
            > using __TreeMapValueProxyFindOfInitializerListClient =        /* NOLINT(bugprone-reserved-identifier) */
                    __LocalFindOfImmutableCompositeClient <
                            __ServerType,
                            __ValueType,
                            __TreeMapValueProxyAbstractIterator < __KeyType, __ValueType, __Comparator >,
                            std :: initializer_list < __ValueType >,
                            & cds :: __hidden :: __impl :: __initializerListContains <
                                    __ValueType,
                                    & cds :: meta :: equals < __ValueType >
                            >,
                            & cds :: __hidden :: __impl :: __initializerListNotContains <
                                    __ValueType,
                                    & cds :: meta :: equals < __ValueType >
                            >
                    >;


            template <
                    typename __ServerType,      /* NOLINT(bugprone-reserved-identifier) */
                    typename __KeyType,         /* NOLINT(bugprone-reserved-identifier) */
                    typename __ValueType,       /* NOLINT(bugprone-reserved-identifier) */
                    typename __Comparator       /* NOLINT(bugprone-reserved-identifier) */
            > using __TreeMapValueProxyConstGenericStatementsClient =       /* NOLINT(bugprone-reserved-identifier) */
                    __LocalGenericImmutableStatementsCompositeClient <
                            __ServerType,
                            __ValueType
                    >;


            template <
                    typename __ServerType,      /* NOLINT(bugprone-reserved-identifier) */
                    typename __KeyType,         /* NOLINT(bugprone-reserved-identifier) */
                    typename __ValueType,       /* NOLINT(bugprone-reserved-identifier) */
                    typename __Comparator       /* NOLINT(bugprone-reserved-identifier) */
            > using __TreeMapValueProxyGenericStatementsClient =       /* NOLINT(bugprone-reserved-identifier) */
                    __LocalGenericMutableStatementsCompositeClient <
                            __ServerType,
                            __ValueType
                    >;


            template <
                    typename __ServerType,                    /* NOLINT(bugprone-reserved-identifier) */
                    typename __KeyType,                       /* NOLINT(bugprone-reserved-identifier) */
                    typename __ValueType                      /* NOLINT(bugprone-reserved-identifier) */
            > using __TreeMapValueProxyRemoveByClient =       /* NOLINT(bugprone-reserved-identifier) */
                    __LocalRemoveByCompositeClient <
                            __ServerType,
                            __ValueType
                    >;


            template <
                    typename __ServerType,                            /* NOLINT(bugprone-reserved-identifier) */
                    typename __KeyType,                               /* NOLINT(bugprone-reserved-identifier) */
                    typename __ValueType                              /* NOLINT(bugprone-reserved-identifier) */
            > using __TreeMapValueProxyRemoveOfCollectionClient =     /* NOLINT(bugprone-reserved-identifier) */
                    __LocalRemoveOfCompositeClient <
                            __ServerType,
                            __ValueType,
                            cds :: Iterable < __ValueType >,
                            & cds :: __hidden :: __impl :: __iterableContains < __ValueType >
                    >;


            template <
                    typename __ServerType,                                 /* NOLINT(bugprone-reserved-identifier) */
                    typename __KeyType,                                    /* NOLINT(bugprone-reserved-identifier) */
                    typename __ValueType                                   /* NOLINT(bugprone-reserved-identifier) */
            > using __TreeMapValueProxyRemoveOfInitializerListClient =     /* NOLINT(bugprone-reserved-identifier) */
                    __LocalRemoveOfCompositeClient <
                            __ServerType,
                            __ValueType,
                            std :: initializer_list < __ValueType >,
                            & cds :: __hidden :: __impl :: __initializerListContains <
                                    __ValueType,
                                    & cds :: meta :: equals < __ValueType >
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
    > :: ValueMutableCollectionProxy :
            public AbstractValueMutableCollectionProxy,
            private __hidden :: __impl :: __TreeMapValueProxyServer < ValueMutableCollectionProxy, __KeyType, __ValueType >,
            public __hidden :: __impl :: __TreeMapValueProxyConstIteratorRemoveClient < ValueMutableCollectionProxy, __KeyType, __ValueType, __Comparator >,
            public __hidden :: __impl :: __TreeMapValueProxyIteratorRemoveClient < ValueMutableCollectionProxy, __KeyType, __ValueType, __Comparator >,
            public __hidden :: __impl :: __TreeMapValueProxyDelegateBackwardConstIterableClient < ValueMutableCollectionProxy, __KeyType, __ValueType, __Comparator >,
            public __hidden :: __impl :: __TreeMapValueProxyDelegateBackwardIterableClient < ValueMutableCollectionProxy, __KeyType, __ValueType, __Comparator >,
            public __hidden :: __impl :: __TreeMapValueProxyDelegateForwardConstIterableClient < ValueMutableCollectionProxy, __KeyType, __ValueType, __Comparator >,
            public __hidden :: __impl :: __TreeMapValueProxyDelegateForwardIterableClient < ValueMutableCollectionProxy, __KeyType, __ValueType, __Comparator >,
            public __hidden :: __impl :: __TreeMapValueProxyRandomInsertionClient < ValueMutableCollectionProxy, __KeyType, __ValueType, __Comparator >,
            public __hidden :: __impl :: __TreeMapValueProxyContainsOfCollectionClient < ValueMutableCollectionProxy, __KeyType, __ValueType, __Comparator >,
            public __hidden :: __impl :: __TreeMapValueProxyContainsOfInitializerListClient < ValueMutableCollectionProxy, __KeyType, __ValueType, __Comparator >,
            public __hidden :: __impl :: __TreeMapValueProxyFindByImmutableClient < ValueMutableCollectionProxy, __KeyType, __ValueType, __Comparator >,
            public __hidden :: __impl :: __TreeMapValueProxyFindByMutableClient < ValueMutableCollectionProxy, __KeyType, __ValueType, __Comparator >,
            public __hidden :: __impl :: __TreeMapValueProxyFindOfConstCollectionClient < ValueMutableCollectionProxy, __KeyType, __ValueType, __Comparator >,
            public __hidden :: __impl :: __TreeMapValueProxyFindOfConstInitializerListClient < ValueMutableCollectionProxy, __KeyType, __ValueType, __Comparator >,
            public __hidden :: __impl :: __TreeMapValueProxyFindOfCollectionClient < ValueMutableCollectionProxy, __KeyType, __ValueType, __Comparator >,
            public __hidden :: __impl :: __TreeMapValueProxyFindOfInitializerListClient < ValueMutableCollectionProxy, __KeyType, __ValueType, __Comparator >,
            public __hidden :: __impl :: __TreeMapValueProxyConstGenericStatementsClient < ValueMutableCollectionProxy, __KeyType, __ValueType, __Comparator >,
            public __hidden :: __impl :: __TreeMapValueProxyGenericStatementsClient < ValueMutableCollectionProxy, __KeyType, __ValueType, __Comparator >,
            public __hidden :: __impl :: __TreeMapValueProxyRemoveByClient < ValueMutableCollectionProxy, __KeyType, __ValueType >,
            public __hidden :: __impl :: __TreeMapValueProxyRemoveOfCollectionClient < ValueMutableCollectionProxy, __KeyType, __ValueType >,
            public __hidden :: __impl :: __TreeMapValueProxyRemoveOfInitializerListClient < ValueMutableCollectionProxy, __KeyType, __ValueType > {

    protected: using TreeMapBase                                = TreeMap < __KeyType, __ValueType, __Comparator >;
    protected: using Server                                     = __hidden::__impl::__TreeMapValueProxyServer < ValueMutableCollectionProxy, __KeyType, __ValueType >;
    protected: using ConstIteratorRemoveClient                  = __hidden :: __impl :: __TreeMapValueProxyConstIteratorRemoveClient < ValueMutableCollectionProxy, __KeyType, __ValueType, __Comparator >;
    protected: using IteratorRemoveClient                       = __hidden :: __impl :: __TreeMapValueProxyIteratorRemoveClient < ValueMutableCollectionProxy, __KeyType, __ValueType, __Comparator >;
    protected: using DelegateBackwardConstIterableClient        = __hidden :: __impl :: __TreeMapValueProxyDelegateBackwardConstIterableClient < ValueMutableCollectionProxy, __KeyType, __ValueType, __Comparator >;
    protected: using DelegateBackwardIterableClient             = __hidden :: __impl :: __TreeMapValueProxyDelegateBackwardIterableClient < ValueMutableCollectionProxy, __KeyType, __ValueType, __Comparator >;
    protected: using DelegateForwardConstIterableClient         = __hidden :: __impl :: __TreeMapValueProxyDelegateForwardConstIterableClient < ValueMutableCollectionProxy, __KeyType, __ValueType, __Comparator >;
    protected: using DelegateForwardIterableClient              = __hidden :: __impl :: __TreeMapValueProxyDelegateForwardIterableClient < ValueMutableCollectionProxy, __KeyType, __ValueType, __Comparator >;
    protected: using RandomInsertionClient                      = __hidden :: __impl :: __TreeMapValueProxyRandomInsertionClient < ValueMutableCollectionProxy, __KeyType, __ValueType, __Comparator >;
    protected: using ContainsOfCollectionClient                 = __hidden :: __impl :: __TreeMapValueProxyContainsOfCollectionClient < ValueMutableCollectionProxy, __KeyType, __ValueType, __Comparator >;
    protected: using ContainsOfInitializerListClient            = __hidden :: __impl :: __TreeMapValueProxyContainsOfInitializerListClient < ValueMutableCollectionProxy, __KeyType, __ValueType, __Comparator >;
    protected: using FindByImmutableClient                      = __hidden :: __impl :: __TreeMapValueProxyFindByImmutableClient < ValueMutableCollectionProxy, __KeyType, __ValueType, __Comparator >;
    protected: using FindByMutableClient                        = __hidden :: __impl :: __TreeMapValueProxyFindByMutableClient < ValueMutableCollectionProxy, __KeyType, __ValueType, __Comparator >;
    protected: using FindOfConstCollectionClient                = __hidden :: __impl :: __TreeMapValueProxyFindOfConstCollectionClient < ValueMutableCollectionProxy, __KeyType, __ValueType, __Comparator >;
    protected: using FindOfConstInitializerListClient           = __hidden :: __impl :: __TreeMapValueProxyFindOfConstInitializerListClient < ValueMutableCollectionProxy, __KeyType, __ValueType, __Comparator >;
    protected: using FindOfCollectionClient                     = __hidden :: __impl :: __TreeMapValueProxyFindOfCollectionClient < ValueMutableCollectionProxy, __KeyType, __ValueType, __Comparator >;
    protected: using FindOfInitializerListClient                = __hidden :: __impl :: __TreeMapValueProxyFindOfInitializerListClient < ValueMutableCollectionProxy, __KeyType, __ValueType, __Comparator >;
    protected: using ConstGenericStatementsClient               = __hidden :: __impl :: __TreeMapValueProxyConstGenericStatementsClient < ValueMutableCollectionProxy, __KeyType, __ValueType, __Comparator >;
    protected: using GenericStatementsClient                    = __hidden :: __impl :: __TreeMapValueProxyGenericStatementsClient < ValueMutableCollectionProxy, __KeyType, __ValueType, __Comparator >;
    protected: using RemoveByClient                             = __hidden :: __impl :: __TreeMapValueProxyRemoveByClient < ValueMutableCollectionProxy, __KeyType, __ValueType >;
    protected: using RemoveOfCollectionClient                   = __hidden :: __impl :: __TreeMapValueProxyRemoveOfCollectionClient < ValueMutableCollectionProxy, __KeyType, __ValueType >;
    protected: using RemoveOfInitializerListClient              = __hidden :: __impl :: __TreeMapValueProxyRemoveOfInitializerListClient < ValueMutableCollectionProxy, __KeyType, __ValueType >;

    private: friend Server;

    private: friend DelegateForwardIterableClient;
    private: friend DelegateBackwardIterableClient;
    private: friend DelegateForwardConstIterableClient;
    private: friend DelegateBackwardConstIterableClient;

    protected: using typename AbstractValueMutableCollectionProxy :: __GenericHandler;          /* NOLINT(bugprone-reserved-identifier) */
    protected: using typename AbstractValueMutableCollectionProxy :: __GenericConstHandler;     /* NOLINT(bugprone-reserved-identifier) */

    public: using typename DelegateForwardIterableClient :: Iterator;
    public: using typename DelegateForwardConstIterableClient :: ConstIterator;
    public: using typename DelegateBackwardIterableClient :: ReverseIterator;
    public: using typename DelegateBackwardConstIterableClient :: ConstReverseIterator;
    public: using AbstractIterator = typename IteratorRemoveClient :: Iterator;
    public: using AbstractConstIterator = typename ConstIteratorRemoveClient :: ConstIterator;


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
        __CDS_Explicit ValueMutableCollectionProxy (
                TreeMap < __KeyType, __ValueType, __Comparator > * pMap
        ) noexcept;

    public:
        ValueMutableCollectionProxy () noexcept = delete;

    public:
        ValueMutableCollectionProxy (
                ValueMutableCollectionProxy const &
        ) noexcept = delete;

    public:
        ValueMutableCollectionProxy (
                ValueMutableCollectionProxy &&
        ) noexcept = delete;

    public:
        auto operator = (
                ValueMutableCollectionProxy const &
        ) noexcept = delete;

    public:
        auto operator = (
                ValueMutableCollectionProxy &&
        ) noexcept = delete;

    public:
        __CDS_NoDiscard static constexpr auto __begin (
                ValueMutableCollectionProxy * pObject
        ) noexcept -> cds :: __hidden :: __impl :: __AbstractDelegateIterator < __ValueType > *;     /* NOLINT(bugprone-reserved-identifier) */

    public:
        __CDS_NoDiscard static constexpr auto __end (
                ValueMutableCollectionProxy * pObject
        ) noexcept -> cds :: __hidden :: __impl :: __AbstractDelegateIterator < __ValueType > *;     /* NOLINT(bugprone-reserved-identifier) */

    public:
        __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction static auto __beginLocal (
                ValueMutableCollectionProxy * pObject
        ) noexcept -> Iterator;     /* NOLINT(bugprone-reserved-identifier) */

    public:
        __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction static auto __endLocal (
                ValueMutableCollectionProxy * pObject
        ) noexcept -> Iterator;     /* NOLINT(bugprone-reserved-identifier) */

    public:
        __CDS_NoDiscard constexpr static auto __cbegin (
                ValueMutableCollectionProxy const * pObject
        ) noexcept -> cds :: __hidden :: __impl :: __AbstractDelegateIterator < __ValueType const > *;     /* NOLINT(bugprone-reserved-identifier) */

    public:
        __CDS_NoDiscard constexpr static auto __cend (
                ValueMutableCollectionProxy const * pObject
        ) noexcept -> cds :: __hidden :: __impl :: __AbstractDelegateIterator < __ValueType const > *;     /* NOLINT(bugprone-reserved-identifier) */

    public:
        __CDS_NoDiscard constexpr static auto __cbeginLocal (
                ValueMutableCollectionProxy const * pObject
        ) noexcept -> ConstIterator;     /* NOLINT(bugprone-reserved-identifier) */

    public:
        __CDS_NoDiscard constexpr static auto __cendLocal (
                ValueMutableCollectionProxy const * pObject
        ) noexcept -> ConstIterator;     /* NOLINT(bugprone-reserved-identifier) */

    public:
        __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction static auto __rbeginLocal (
                ValueMutableCollectionProxy * pObject
        ) noexcept -> ReverseIterator;     /* NOLINT(bugprone-reserved-identifier) */

    public:
        __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction static auto __rendLocal (
                ValueMutableCollectionProxy * pObject
        ) noexcept -> ReverseIterator;     /* NOLINT(bugprone-reserved-identifier) */

    public:
        __CDS_NoDiscard constexpr static auto __crbeginLocal (
                ValueMutableCollectionProxy const * pObject
        ) noexcept -> ConstReverseIterator;     /* NOLINT(bugprone-reserved-identifier) */

    public:
        __CDS_NoDiscard constexpr static auto __crendLocal (
                ValueMutableCollectionProxy const * pObject
        ) noexcept -> ConstReverseIterator;     /* NOLINT(bugprone-reserved-identifier) */

    public:
        static auto __remove (     /* NOLINT(bugprone-reserved-identifier) */
                ValueMutableCollectionProxy * pObject,
                AbstractIterator const * iterator
        ) noexcept -> bool;

    public:
        static auto __removeConst (     /* NOLINT(bugprone-reserved-identifier) */
                ValueMutableCollectionProxy * pObject,
                AbstractConstIterator const * iterator
        ) noexcept -> bool;

    public:
        static auto __removeArray (     /* NOLINT(bugprone-reserved-identifier) */
                ValueMutableCollectionProxy * pObject,
                AbstractIterator const * const * ppIterators,
                Size                             iteratorCount
        ) noexcept -> Size;

    public:
        static auto __removeConstArray (     /* NOLINT(bugprone-reserved-identifier) */
                ValueMutableCollectionProxy * pObject,
                AbstractConstIterator const * const * ppIterators,
                Size                                  iteratorCount
        ) noexcept -> Size;
    };

}

#endif //__CDS_TREE_MAP_VALUE_MUTABLE_COLLECTION_PROXY_HPP_
