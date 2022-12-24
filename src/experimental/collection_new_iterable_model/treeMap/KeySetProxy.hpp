//
// Created by stefan on 13.10.2022.
//

#ifndef __CDS_TREE_MAP_KEY_SET_PROXY_HPP__
#define __CDS_TREE_MAP_KEY_SET_PROXY_HPP__  /* NOLINT(bugprone-reserved-identifier) */

namespace cds { /* NOLINT(modernize-concat-nested-namespaces) */
    namespace experimental {
        namespace __hidden {    /* NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier) */
            namespace __impl {  /* NOLINT(bugprone-reserved-identifier) */


                template <
                        typename __ServerType,              /* NOLINT(bugprone-reserved-identifier) */
                        typename __KeyType,                 /* NOLINT(bugprone-reserved-identifier) */
                        typename __ValueType                /* NOLINT(bugprone-reserved-identifier) */
                > using __TreeMapKeyProxyServer =         /* NOLINT(bugprone-reserved-identifier) */
                        __SetServer <
                                __ServerType,
                                const __KeyType
                        >;


                template <
                        typename __DecoratedIteratorType,                                           /* NOLINT(bugprone-reserved-identifier) */
                        typename __ValueAtType                                                      /* NOLINT(bugprone-reserved-identifier) */
                > constexpr auto __treeMapKeySetProxyIteratorDecoratorValueAt (     /* NOLINT(bugprone-reserved-identifier) */
                        __DecoratedIteratorType const & iterator
                ) noexcept -> __ValueAtType & {

                    return ( * iterator ).key ();
                }


                template <
                        typename __KeyType,                              /* NOLINT(bugprone-reserved-identifier) */
                        typename __ValueType                             /* NOLINT(bugprone-reserved-identifier) */
                > using __TreeMapKeyProxyAbstractConstIterator =       /* NOLINT(bugprone-reserved-identifier) */
                        BidirectionalIteratorGenericDecorator <
                                typename __TreeMapImplementation < __KeyType, __ValueType > :: __rbt_AbstractConstIterator,
                                __KeyType const,
                                & __treeMapKeySetProxyIteratorDecoratorValueAt <
                                        typename __TreeMapImplementation < __KeyType, __ValueType > :: __rbt_AbstractConstIterator,
                                        __KeyType const
                                >
                        >;


                template <
                        typename __KeyType,                             /* NOLINT(bugprone-reserved-identifier) */
                        typename __ValueType                            /* NOLINT(bugprone-reserved-identifier) */
                > using __TreeMapKeyProxyForwardConstIterator =       /* NOLINT(bugprone-reserved-identifier) */
                        BidirectionalIteratorGenericDecorator <
                                typename __TreeMapImplementation < __KeyType, __ValueType > :: __rbt_ConstIterator,
                                __KeyType const,
                                & __treeMapKeySetProxyIteratorDecoratorValueAt <
                                        typename __TreeMapImplementation < __KeyType, __ValueType > :: __rbt_ConstIterator,
                                        __KeyType const
                                >
                        >;


                template <
                        typename __KeyType,                              /* NOLINT(bugprone-reserved-identifier) */
                        typename __ValueType                             /* NOLINT(bugprone-reserved-identifier) */
                > using __TreeMapKeyProxyBackwardConstIterator =       /* NOLINT(bugprone-reserved-identifier) */
                        BidirectionalIteratorGenericDecorator <
                                typename __TreeMapImplementation < __KeyType, __ValueType > :: __rbt_ReverseConstIterator,
                                __KeyType const,
                                & __treeMapKeySetProxyIteratorDecoratorValueAt <
                                        typename __TreeMapImplementation < __KeyType, __ValueType > :: __rbt_ReverseConstIterator,
                                        __KeyType const
                                >
                        >;


                template <
                        typename __ServerType,                              /* NOLINT(bugprone-reserved-identifier) */
                        typename __KeyType,                                 /* NOLINT(bugprone-reserved-identifier) */
                        typename __ValueType                                /* NOLINT(bugprone-reserved-identifier) */
                > using __TreeMapKeyProxyConstIteratorRemoveClient =      /* NOLINT(bugprone-reserved-identifier) */
                        __LocalConstIteratorRemovePrimitiveClient <
                                __ServerType,
                                __KeyType,
                                __TreeMapKeyProxyAbstractConstIterator < __KeyType, __ValueType >
                        >;


                template <
                        typename __ServerType,                                          /* NOLINT(bugprone-reserved-identifier) */
                        typename __KeyType,                                             /* NOLINT(bugprone-reserved-identifier) */
                        typename __ValueType                                            /* NOLINT(bugprone-reserved-identifier) */
                > using __TreeMapKeyProxyDelegateBackwardConstIterableClient =        /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __LocalDelegateBackwardConstIterablePrimitiveClient  <
                                __ServerType,
                                __TreeMapKeyProxyBackwardConstIterator < __KeyType, __ValueType >
                        >;


                template <
                        typename __ServerType,                                      /* NOLINT(bugprone-reserved-identifier) */
                        typename __KeyType,                                         /* NOLINT(bugprone-reserved-identifier) */
                        typename __ValueType                                        /* NOLINT(bugprone-reserved-identifier) */
                > using __TreeMapKeyProxyDelegateForwardConstIterableClient =     /* NOLINT(bugprone-reserved-identifier) */
                        __LocalDelegateForwardConstIterablePrimitiveClient  <
                                __ServerType,
                                __TreeMapKeyProxyForwardConstIterator < __KeyType, __ValueType >
                        >;


                template <
                        typename __ServerType,                          /* NOLINT(bugprone-reserved-identifier) */
                        typename __KeyType,                             /* NOLINT(bugprone-reserved-identifier) */
                        typename __ValueType                            /* NOLINT(bugprone-reserved-identifier) */
                > using __TreeMapKeyProxyRandomInsertionClient =      /* NOLINT(bugprone-reserved-identifier) */
                        __LocalRandomInsertionPrimitiveClient <
                                __ServerType,
                                __KeyType,
                                __KeyType const
                        >;


                template <
                        typename __ServerType,                              /* NOLINT(bugprone-reserved-identifier) */
                        typename __KeyType,                                 /* NOLINT(bugprone-reserved-identifier) */
                        typename __ValueType                                /* NOLINT(bugprone-reserved-identifier) */
                > using __TreeMapKeyProxyContainsOfCollectionClient =     /* NOLINT(bugprone-reserved-identifier) */
                        __LocalContainsOfCompositeClient <
                                __ServerType,
                                __KeyType,
                                cds :: Iterable < __KeyType >,
                                & cds :: __hidden :: __impl :: __iterableContains < __KeyType  >
                        >;


                template <
                        typename __ServerType,                                   /* NOLINT(bugprone-reserved-identifier) */
                        typename __KeyType,                                      /* NOLINT(bugprone-reserved-identifier) */
                        typename __ValueType                                     /* NOLINT(bugprone-reserved-identifier) */
                > using __TreeMapKeyProxyContainsOfInitializerListClient =     /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __LocalContainsOfCompositeClient <
                                __ServerType,
                                __KeyType,
                                std :: initializer_list < __KeyType >,
                                & cds :: __hidden :: __impl :: __initializerListContains <
                                        __KeyType,
                                        & cds :: meta :: equals < __KeyType >
                                >
                        >;


                template <
                        typename __ServerType,                          /* NOLINT(bugprone-reserved-identifier) */
                        typename __KeyType,                             /* NOLINT(bugprone-reserved-identifier) */
                        typename __ValueType                            /* NOLINT(bugprone-reserved-identifier) */
                > using __TreeMapKeyProxyFindByImmutableClient =      /* NOLINT(bugprone-reserved-identifier) */
                        __LocalFindByImmutableCompositeClient <
                                __ServerType,
                                __KeyType,
                                __TreeMapKeyProxyAbstractConstIterator < __KeyType, __ValueType >
                        >;


                template <
                        typename __ServerType,                                  /* NOLINT(bugprone-reserved-identifier) */
                        typename __KeyType,                                     /* NOLINT(bugprone-reserved-identifier) */
                        typename __ValueType                                    /* NOLINT(bugprone-reserved-identifier) */
                > using __TreeMapKeyProxyFindOfConstCollectionClient =        /* NOLINT(bugprone-reserved-identifier) */
                        __LocalFindOfImmutableCompositeClient <
                                __ServerType,
                                __KeyType,
                                __TreeMapKeyProxyAbstractConstIterator < __KeyType, __ValueType >,
                                cds :: Iterable < __KeyType >,
                                & cds :: __hidden :: __impl :: __iterableContains < __KeyType  >,
                                & cds :: __hidden :: __impl :: __iterableNotContains < __KeyType  >
                        >;


                template <
                        typename __ServerType,                                       /* NOLINT(bugprone-reserved-identifier) */
                        typename __KeyType,                                          /* NOLINT(bugprone-reserved-identifier) */
                        typename __ValueType                                         /* NOLINT(bugprone-reserved-identifier) */
                > using __TreeMapKeyProxyFindOfConstInitializerListClient =        /* NOLINT(bugprone-reserved-identifier) */
                        __LocalFindOfImmutableCompositeClient <
                                __ServerType,
                                __KeyType,
                                __TreeMapKeyProxyAbstractConstIterator < __KeyType, __ValueType >,
                                std :: initializer_list < __KeyType >,
                                & cds :: __hidden :: __impl :: __initializerListContains <
                                        __KeyType,
                                        & cds :: meta :: equals < __KeyType >
                                >,
                                & cds :: __hidden :: __impl :: __initializerListNotContains <
                                        __KeyType,
                                        & cds :: meta :: equals < __KeyType >
                                >
                        >;


                template <
                        typename __ServerType,                                  /* NOLINT(bugprone-reserved-identifier) */
                        typename __KeyType,                                     /* NOLINT(bugprone-reserved-identifier) */
                        typename __ValueType                                    /* NOLINT(bugprone-reserved-identifier) */
                > using __TreeMapKeyProxyConstGenericStatementsClient =       /* NOLINT(bugprone-reserved-identifier) */
                        __LocalGenericImmutableStatementsCompositeClient <
                                __ServerType,
                                __KeyType
                        >;


                template <
                        typename __ServerType,                             /* NOLINT(bugprone-reserved-identifier) */
                        typename __KeyType,                                /* NOLINT(bugprone-reserved-identifier) */
                        typename __ValueType                               /* NOLINT(bugprone-reserved-identifier) */
                > using __TreeMapKeyProxyGenericStatementsClient =       /* NOLINT(bugprone-reserved-identifier) */
                        __LocalGenericMutableStatementsCompositeClient <
                                __ServerType,
                                __KeyType
                        >;


                template <
                        typename __ServerType,                    /* NOLINT(bugprone-reserved-identifier) */
                        typename __KeyType,                       /* NOLINT(bugprone-reserved-identifier) */
                        typename __ValueType                      /* NOLINT(bugprone-reserved-identifier) */
                > using __TreeMapKeyProxyRemoveByClient =       /* NOLINT(bugprone-reserved-identifier) */
                        __LocalRemoveByCompositeClient <
                                __ServerType,
                                __KeyType
                        >;


                template <
                        typename __ServerType,                            /* NOLINT(bugprone-reserved-identifier) */
                        typename __KeyType,                               /* NOLINT(bugprone-reserved-identifier) */
                        typename __ValueType                              /* NOLINT(bugprone-reserved-identifier) */
                > using __TreeMapKeyProxyRemoveOfCollectionClient =     /* NOLINT(bugprone-reserved-identifier) */
                        __LocalRemoveOfCompositeClient <
                                __ServerType,
                                __KeyType,
                                cds :: Iterable < __KeyType >,
                                & cds :: __hidden :: __impl :: __iterableContains < __KeyType  >
                        >;


                template <
                        typename __ServerType,                                 /* NOLINT(bugprone-reserved-identifier) */
                        typename __KeyType,                                    /* NOLINT(bugprone-reserved-identifier) */
                        typename __ValueType                                   /* NOLINT(bugprone-reserved-identifier) */
                > using __TreeMapKeyProxyRemoveOfInitializerListClient =     /* NOLINT(bugprone-reserved-identifier) */
                        __LocalRemoveOfCompositeClient <
                                __ServerType,
                                __KeyType,
                                std :: initializer_list < __KeyType >,
                                & cds :: __hidden :: __impl :: __initializerListContains <
                                        __KeyType,
                                        & cds :: meta :: equals < __KeyType >
                                >
                        >;

            }
        }

        template <
                typename __KeyType,     /* NOLINT(bugprone-reserved-identifier) */
                typename __ValueType    /* NOLINT(bugprone-reserved-identifier) */
        > class __CDS_InheritsEBOs TreeMap <
                __KeyType,
                __ValueType
        > :: KeySetProxy :
                public TreeMap < __KeyType, __ValueType > :: AbstractKeySetProxy,
                private __hidden :: __impl :: __TreeMapKeyProxyServer < KeySetProxy, __KeyType, __ValueType >,
                public __hidden :: __impl :: __TreeMapKeyProxyConstIteratorRemoveClient < KeySetProxy, __KeyType, __ValueType >,
                public __hidden :: __impl :: __TreeMapKeyProxyDelegateBackwardConstIterableClient < KeySetProxy, __KeyType, __ValueType >,
                public __hidden :: __impl :: __TreeMapKeyProxyDelegateForwardConstIterableClient < KeySetProxy, __KeyType, __ValueType >,
                public __hidden :: __impl :: __TreeMapKeyProxyRandomInsertionClient < KeySetProxy, __KeyType, __ValueType >,
                public __hidden :: __impl :: __TreeMapKeyProxyContainsOfCollectionClient < KeySetProxy, __KeyType, __ValueType >,
                public __hidden :: __impl :: __TreeMapKeyProxyContainsOfInitializerListClient < KeySetProxy, __KeyType, __ValueType >,
                public __hidden :: __impl :: __TreeMapKeyProxyFindByImmutableClient < KeySetProxy, __KeyType, __ValueType >,
                public __hidden :: __impl :: __TreeMapKeyProxyFindOfConstCollectionClient < KeySetProxy, __KeyType, __ValueType >,
                public __hidden :: __impl :: __TreeMapKeyProxyFindOfConstInitializerListClient < KeySetProxy, __KeyType, __ValueType >,
                public __hidden :: __impl :: __TreeMapKeyProxyConstGenericStatementsClient < KeySetProxy, __KeyType, __ValueType >,
                public __hidden :: __impl :: __TreeMapKeyProxyGenericStatementsClient < KeySetProxy, __KeyType, __ValueType >,
                public __hidden :: __impl :: __TreeMapKeyProxyRemoveByClient < KeySetProxy, __KeyType, __ValueType >,
                public __hidden :: __impl :: __TreeMapKeyProxyRemoveOfCollectionClient < KeySetProxy, __KeyType, __ValueType >,
                public __hidden :: __impl :: __TreeMapKeyProxyRemoveOfInitializerListClient < KeySetProxy, __KeyType, __ValueType > {

        protected: using TreeMapBase                                = TreeMap < __KeyType, __ValueType >;
        protected: using Server                                     = __hidden::__impl::__TreeMapKeyProxyServer < KeySetProxy, __KeyType, __ValueType >;
        protected: using ConstIteratorRemoveClient                  = __hidden :: __impl :: __TreeMapKeyProxyConstIteratorRemoveClient < KeySetProxy, __KeyType, __ValueType >;
        protected: using DelegateBackwardConstIterableClient        = __hidden :: __impl :: __TreeMapKeyProxyDelegateBackwardConstIterableClient < KeySetProxy, __KeyType, __ValueType >;
        protected: using DelegateForwardConstIterableClient         = __hidden :: __impl :: __TreeMapKeyProxyDelegateForwardConstIterableClient < KeySetProxy, __KeyType, __ValueType >;
        protected: using RandomInsertionClient                      = __hidden :: __impl :: __TreeMapKeyProxyRandomInsertionClient < KeySetProxy, __KeyType, __ValueType >;
        protected: using ContainsOfCollectionClient                 = __hidden :: __impl :: __TreeMapKeyProxyContainsOfCollectionClient < KeySetProxy, __KeyType, __ValueType >;
        protected: using ContainsOfInitializerListClient            = __hidden :: __impl :: __TreeMapKeyProxyContainsOfInitializerListClient < KeySetProxy, __KeyType, __ValueType >;
        protected: using FindByImmutableClient                      = __hidden :: __impl :: __TreeMapKeyProxyFindByImmutableClient < KeySetProxy, __KeyType, __ValueType >;
        protected: using FindOfConstCollectionClient                = __hidden :: __impl :: __TreeMapKeyProxyFindOfConstCollectionClient < KeySetProxy, __KeyType, __ValueType >;
        protected: using FindOfConstInitializerListClient           = __hidden :: __impl :: __TreeMapKeyProxyFindOfConstInitializerListClient < KeySetProxy, __KeyType, __ValueType >;
        protected: using ConstGenericStatementsClient               = __hidden :: __impl :: __TreeMapKeyProxyConstGenericStatementsClient < KeySetProxy, __KeyType, __ValueType >;
        protected: using GenericStatementsClient                    = __hidden :: __impl :: __TreeMapKeyProxyGenericStatementsClient < KeySetProxy, __KeyType, __ValueType >;
        protected: using RemoveByClient                             = __hidden :: __impl :: __TreeMapKeyProxyRemoveByClient < KeySetProxy, __KeyType, __ValueType >;
        protected: using RemoveOfCollectionClient                   = __hidden :: __impl :: __TreeMapKeyProxyRemoveOfCollectionClient < KeySetProxy, __KeyType, __ValueType >;
        protected: using RemoveOfInitializerListClient              = __hidden :: __impl :: __TreeMapKeyProxyRemoveOfInitializerListClient < KeySetProxy, __KeyType, __ValueType >;

        private: friend Server;

        private: friend DelegateForwardConstIterableClient;
        private: friend DelegateBackwardConstIterableClient;

        protected: using typename AbstractKeySetProxy :: __GenericHandler;          /* NOLINT(bugprone-reserved-identifier) */
        protected: using typename AbstractKeySetProxy :: __GenericConstHandler;     /* NOLINT(bugprone-reserved-identifier) */

        public: using typename DelegateForwardConstIterableClient :: ConstIterator;
        public: using typename DelegateBackwardConstIterableClient :: ConstReverseIterator;
        public: using AbstractConstIterator = typename ConstIteratorRemoveClient :: ConstIterator;

        public:     using DelegateForwardConstIterableClient :: begin;
        public:     using DelegateForwardConstIterableClient :: end;
        public:     using DelegateForwardConstIterableClient :: cbegin;
        public:     using DelegateForwardConstIterableClient :: cend;

        public:     using DelegateBackwardConstIterableClient :: rbegin;
        public:     using DelegateBackwardConstIterableClient :: rend;
        public:     using DelegateBackwardConstIterableClient :: crbegin;
        public:     using DelegateBackwardConstIterableClient :: crend;


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
            __CDS_Explicit KeySetProxy (
                    TreeMap < __KeyType, __ValueType > * pMap
            ) noexcept;

        public:
            KeySetProxy () noexcept = delete;

        public:
            KeySetProxy (
                    KeySetProxy const &
            ) noexcept = delete;

        public:
            KeySetProxy (
                    KeySetProxy &&
            ) noexcept = delete;

        public:
            auto operator = (
                    KeySetProxy const &
            ) noexcept = delete;

        public:
            auto operator = (
                    KeySetProxy &&
            ) noexcept = delete;

        public:
            __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto contains (
                    __KeyType const & key
            ) const noexcept -> bool override;

        public:
            __CDS_NoDiscard constexpr static auto __cbegin (
                    KeySetProxy const * pObject
            ) noexcept -> cds :: __hidden :: __impl :: __AbstractDelegateIterator < __KeyType const > *;     /* NOLINT(bugprone-reserved-identifier) */

        public:
            __CDS_NoDiscard constexpr static auto __cend (
                    KeySetProxy const * pObject
            ) noexcept -> cds :: __hidden :: __impl :: __AbstractDelegateIterator < __KeyType const > *;     /* NOLINT(bugprone-reserved-identifier) */

        public:
            __CDS_NoDiscard constexpr static auto __cbeginLocal (
                    KeySetProxy const * pObject
            ) noexcept -> ConstIterator;     /* NOLINT(bugprone-reserved-identifier) */

        public:
            __CDS_NoDiscard constexpr static auto __cendLocal (
                    KeySetProxy const * pObject
            ) noexcept -> ConstIterator;     /* NOLINT(bugprone-reserved-identifier) */

        public:
            __CDS_NoDiscard constexpr static auto __crbeginLocal (
                    KeySetProxy const * pObject
            ) noexcept -> ConstReverseIterator;     /* NOLINT(bugprone-reserved-identifier) */

        public:
            __CDS_NoDiscard constexpr static auto __crendLocal (
                    KeySetProxy const * pObject
            ) noexcept -> ConstReverseIterator;     /* NOLINT(bugprone-reserved-identifier) */

        public:
            static auto __removeConst (     /* NOLINT(bugprone-reserved-identifier) */
                    KeySetProxy * pObject,
                    AbstractConstIterator const * iterator
            ) noexcept -> bool;

        public:
            static auto __removeConstArray (     /* NOLINT(bugprone-reserved-identifier) */
                    KeySetProxy * pObject,
                    AbstractConstIterator const * const * ppIterators,
                    Size                                  iteratorCount
            ) noexcept -> Size;

        public:
            static auto __findConst (      /* NOLINT(bugprone-reserved-identifier) */
                    KeySetProxy const * pObject,
                    __KeyType const & key
            ) noexcept -> cds :: __hidden :: __impl :: __AbstractDelegateIterator < __KeyType const > *;

        public:
            static auto __findConstLocal (     /* NOLINT(bugprone-reserved-identifier) */
                    KeySetProxy const * pObject,
                    __KeyType const & key
            ) noexcept -> ConstIterator;
        };

    }
}

#endif //__CDS_TREE_MAP_KEY_SET_PROXY_HPP__
