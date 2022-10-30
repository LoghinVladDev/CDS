/* NOLINT(llvm-header-guard)
 * Created by loghin on 09/10/22.
 */

#ifndef __CDS_LINKED_HASH_MAP_VALUE_MUTABLE_COLLECTION_PROXY_HPP__ /* NOLINT(llvm-header-guard) */
#define __CDS_LINKED_HASH_MAP_VALUE_MUTABLE_COLLECTION_PROXY_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

namespace cds {             /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    namespace __hidden {    /* NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        namespace __impl {  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            template <
                    typename __ServerType,                          /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __KeyType,                             /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ValueType,                           /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __Hasher                               /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > using __LinkedHashMapValueProxyServer =               /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __MutableCollectionServer <
                            __ServerType,
                            __ValueType
                    >;


            template <
                    typename __DecoratedIteratorType,                               /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ValueAtType                                          /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > constexpr auto __linkedHashMapValueSetProxyIteratorDecoratorValueAt ( /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __DecoratedIteratorType const & iterator
            ) noexcept -> __ValueAtType & {

                return ( * iterator ).value ();
            }


            template <
                    typename __KeyType,                 /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ValueType,               /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __Hasher                   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > using __LinkedHashMapValueProxyIterator = /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    ForwardIteratorGenericDecorator <
                            __LinkedHashMapIterator < __KeyType, __ValueType, __Hasher >,
                            __ValueType,
                            & __linkedHashMapValueSetProxyIteratorDecoratorValueAt <
                                    __LinkedHashMapIterator < __KeyType, __ValueType, __Hasher >,
                                    __ValueType
                            >
                    >;


            template <
                    typename __KeyType,                         /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ValueType,                       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __Hasher                           /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > using __LinkedHashMapValueProxyConstIterator =    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    ForwardIteratorGenericDecorator <
                            __LinkedHashMapConstIterator < __KeyType, __ValueType, __Hasher >,
                            __ValueType const,
                            & __linkedHashMapValueSetProxyIteratorDecoratorValueAt <
                                    __LinkedHashMapConstIterator < __KeyType, __ValueType, __Hasher >,
                                    __ValueType const
                            >
                    >;


            template <
                    typename __ServerType,                              /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __KeyType,                                 /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ValueType,                               /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __Hasher                                   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > using __LinkedHashMapValueProxyRandomInsertionClient =    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __LocalRandomInsertionPrimitiveClient <
                            __ServerType,
                            __ValueType,
                            __ValueType
                    >;


            template <
                    typename __ServerType,                          /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __KeyType,                             /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ValueType,                           /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __Hasher                               /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > using __LinkedHashMapValueProxyIteratorRemoveClient = /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __LocalIteratorRemovePrimitiveClient <
                            __ServerType,
                            __ValueType,
                            __LinkedHashMapValueProxyIterator < __KeyType, __ValueType, __Hasher >
                    >;


            template <
                    typename __ServerType,                                  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __KeyType,                                     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ValueType,                                   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __Hasher                                       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > using __LinkedHashMapValueProxyConstIteratorRemoveClient =    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __LocalConstIteratorRemovePrimitiveClient <
                            __ServerType,
                            __ValueType,
                            __LinkedHashMapValueProxyConstIterator < __KeyType, __ValueType, __Hasher >
                    >;


            template <
                    typename __ServerType,                              /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __KeyType,                                 /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ValueType,                               /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __Hasher                                   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > using __LinkedHashMapValueProxyFindOfIterableClient =     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __LocalFindOfMutableCompositeClient <
                            __ServerType,
                            __ValueType,
                            __LinkedHashMapValueProxyIterator < __KeyType, __ValueType, __Hasher >,
                            cds :: Iterable < __ValueType >,
                            & __iterableContains < __ValueType >,
                            & __iterableNotContains < __ValueType >
                    >;


            template <
                    typename __ServerType,                                  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __KeyType,                                     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ValueType,                                   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __Hasher                                       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > using __LinkedHashMapValueProxyFindOfConstIterableClient =    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __LocalFindOfImmutableCompositeClient <
                            __ServerType,
                            __ValueType,
                            __LinkedHashMapValueProxyConstIterator < __KeyType, __ValueType, __Hasher >,
                            cds :: Iterable < __ValueType >,
                            & __iterableContains < __ValueType >,
                            & __iterableNotContains < __ValueType >
                    >;


            template <
                    typename __ServerType,                                  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __KeyType,                                     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ValueType,                                   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __Hasher                                       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > using __LinkedHashMapValueProxyFindOfInitializerListClient =  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __LocalFindOfMutableCompositeClient <
                            __ServerType,
                            __ValueType,
                            __LinkedHashMapValueProxyIterator < __KeyType, __ValueType, __Hasher >,
                            std :: initializer_list < __ValueType >,
                            & __initializerListContains < __ValueType, & cds :: meta :: equals < __ValueType > >,
                            & __initializerListNotContains < __ValueType, & cds :: meta :: equals < __ValueType > >
                    >;


            template <
                    typename __ServerType,                                      /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __KeyType,                                         /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ValueType,                                       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __Hasher                                           /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > using __LinkedHashMapValueProxyFindOfConstInitializerListClient = /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __LocalFindOfImmutableCompositeClient <
                            __ServerType,
                            __ValueType,
                            __LinkedHashMapValueProxyConstIterator < __KeyType, __ValueType, __Hasher >,
                            std :: initializer_list < __ValueType >,
                            & __initializerListContains < __ValueType, & cds :: meta :: equals < __ValueType > >,
                            & __initializerListNotContains < __ValueType, & cds :: meta :: equals < __ValueType > >
                    >;


            template <
                    typename __ServerType,                  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __KeyType,                     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ValueType,                   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __Hasher                       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > using __LinkedHashMapValueProxyFindByClient = /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __LocalFindByMutableCompositeClient <
                            __ServerType,
                            __ValueType,
                            __LinkedHashMapValueProxyIterator < __KeyType, __ValueType, __Hasher >
                    >;


            template <
                    typename __ServerType,                          /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __KeyType,                             /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ValueType,                           /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __Hasher                               /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > using __LinkedHashMapValueProxyConstFindByClient =    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __LocalFindByImmutableCompositeClient <
                            __ServerType,
                            __ValueType,
                            __LinkedHashMapValueProxyConstIterator < __KeyType, __ValueType, __Hasher >
                    >;


            template <
                    typename __ServerType,                              /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __KeyType,                                 /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ValueType,                               /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __Hasher                                   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > using __LinkedHashMapValueProxyRemoveOfIterableClient =   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __LocalRemoveOfCompositeClient <
                            __ServerType,
                            __ValueType,
                            cds :: Iterable < __ValueType >,
                            & __iterableContains < __ValueType >
                    >;


            template <
                    typename __ServerType,                                      /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __KeyType,                                         /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ValueType,                                       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __Hasher                                           /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > using __LinkedHashMapValueProxyRemoveOfInitializerListClient =    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __LocalRemoveOfCompositeClient <
                            __ServerType,
                            __ValueType,
                            std :: initializer_list < __ValueType >,
                            & __initializerListContains < __ValueType, & cds :: meta :: equals < __ValueType > >
                    >;


            template <
                    typename __ServerType,                      /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __KeyType,                         /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ValueType,                       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __Hasher                           /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > using __LinkedHashMapValueProxyRemoveByClient =   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __LocalRemoveByCompositeClient <
                            __ServerType,
                            __ValueType
                    >;


            template <
                    typename __ServerType,                              /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __KeyType,                                 /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ValueType,                               /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __Hasher                                   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > using __LinkedHashMapValueProxyGenericStatementsClient =  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __LocalGenericMutableStatementsCompositeClient <
                            __ServerType,
                            __ValueType
                    >;


            template <
                    typename __ServerType,                                  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __KeyType,                                     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ValueType,                                   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __Hasher                                       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > using __LinkedHashMapValueProxyConstGenericStatementsClient = /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __LocalGenericImmutableStatementsCompositeClient <
                            __ServerType,
                            __ValueType
                    >;


            template <
                    typename __ServerType,                              /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __KeyType,                                 /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ValueType,                               /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __Hasher                                   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > using __LinkedHashMapValueProxyContainsOfIterableClient = /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __LocalContainsOfCompositeClient <
                            __ServerType,
                            __ValueType,
                            cds :: Iterable < __ValueType >,
                            & __iterableContains < __ValueType >
                    >;


            template <
                    typename __ServerType,                                      /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __KeyType,                                         /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ValueType,                                       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __Hasher                                           /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > using __LinkedHashMapValueProxyContainsOfInitializerListClient =  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __LocalContainsOfCompositeClient <
                            __ServerType,
                            __ValueType,
                            std :: initializer_list < __ValueType >,
                            & __initializerListContains <
                                    __ValueType,
                                    & cds :: meta :: equals < __ValueType >
                            >
                    >;


            template <
                    typename __ServerType,                                      /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __KeyType,                                         /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ValueType,                                       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __Hasher                                           /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > using __LinkedHashMapValueProxyDelegateForwardIterableClient =    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __LocalDelegateForwardIterablePrimitiveClient <
                            __ServerType,
                            __LinkedHashMapValueProxyIterator < __KeyType, __ValueType, __Hasher >
                    >;


            template <
                    typename __ServerType,                                          /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __KeyType,                                             /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ValueType,                                           /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __Hasher                                               /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > using __LinkedHashMapValueProxyDelegateForwardConstIterableClient =   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __LocalDelegateForwardConstIterablePrimitiveClient <
                            __ServerType,
                            __LinkedHashMapValueProxyConstIterator < __KeyType, __ValueType, __Hasher >
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
    > :: ValueMutableCollectionProxy :
            public LinkedHashMap < __KeyType, __ValueType, __Hasher > :: AbstractValueMutableCollectionProxy,
            protected __hidden :: __impl :: __LinkedHashMapValueProxyServer < ValueMutableCollectionProxy, __KeyType, __ValueType, __Hasher >,
            public __hidden :: __impl :: __LinkedHashMapValueProxyRandomInsertionClient < ValueMutableCollectionProxy, __KeyType, __ValueType, __Hasher >,
            public __hidden :: __impl :: __LinkedHashMapValueProxyIteratorRemoveClient < ValueMutableCollectionProxy, __KeyType, __ValueType, __Hasher >,
            public __hidden :: __impl :: __LinkedHashMapValueProxyConstIteratorRemoveClient < ValueMutableCollectionProxy, __KeyType, __ValueType, __Hasher >,
            public __hidden :: __impl :: __LinkedHashMapValueProxyFindOfIterableClient < ValueMutableCollectionProxy, __KeyType, __ValueType, __Hasher >,
            public __hidden :: __impl :: __LinkedHashMapValueProxyFindOfConstIterableClient < ValueMutableCollectionProxy, __KeyType, __ValueType, __Hasher >,
            public __hidden :: __impl :: __LinkedHashMapValueProxyFindOfInitializerListClient < ValueMutableCollectionProxy, __KeyType, __ValueType, __Hasher >,
            public __hidden :: __impl :: __LinkedHashMapValueProxyFindOfConstInitializerListClient < ValueMutableCollectionProxy, __KeyType, __ValueType, __Hasher >,
            public __hidden :: __impl :: __LinkedHashMapValueProxyFindByClient < ValueMutableCollectionProxy, __KeyType, __ValueType, __Hasher >,
            public __hidden :: __impl :: __LinkedHashMapValueProxyConstFindByClient < ValueMutableCollectionProxy, __KeyType, __ValueType, __Hasher >,
            public __hidden :: __impl :: __LinkedHashMapValueProxyRemoveOfIterableClient < ValueMutableCollectionProxy, __KeyType, __ValueType, __Hasher >,
            public __hidden :: __impl :: __LinkedHashMapValueProxyRemoveOfInitializerListClient < ValueMutableCollectionProxy, __KeyType, __ValueType, __Hasher >,
            public __hidden :: __impl :: __LinkedHashMapValueProxyRemoveByClient < ValueMutableCollectionProxy, __KeyType, __ValueType, __Hasher >,
            public __hidden :: __impl :: __LinkedHashMapValueProxyGenericStatementsClient < ValueMutableCollectionProxy, __KeyType, __ValueType, __Hasher >,
            public __hidden :: __impl :: __LinkedHashMapValueProxyConstGenericStatementsClient < ValueMutableCollectionProxy, __KeyType, __ValueType, __Hasher >,
            public __hidden :: __impl :: __LinkedHashMapValueProxyContainsOfIterableClient < ValueMutableCollectionProxy, __KeyType, __ValueType, __Hasher >,
            public __hidden :: __impl :: __LinkedHashMapValueProxyContainsOfInitializerListClient < ValueMutableCollectionProxy, __KeyType, __ValueType, __Hasher >,
            public __hidden :: __impl :: __LinkedHashMapValueProxyDelegateForwardIterableClient < ValueMutableCollectionProxy, __KeyType, __ValueType, __Hasher >,
            public __hidden :: __impl :: __LinkedHashMapValueProxyDelegateForwardConstIterableClient < ValueMutableCollectionProxy, __KeyType, __ValueType, __Hasher > {

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using LinkedHashMapBase                     = LinkedHashMap < __KeyType, __ValueType, __Hasher >;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using Server                                = __hidden :: __impl :: __LinkedHashMapValueProxyServer < ValueMutableCollectionProxy, __KeyType, __ValueType, __Hasher >;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using RandomInsertionClient                 = __hidden :: __impl :: __LinkedHashMapValueProxyRandomInsertionClient < ValueMutableCollectionProxy, __KeyType, __ValueType, __Hasher >;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using IteratorRemoveClient                  = __hidden :: __impl :: __LinkedHashMapValueProxyIteratorRemoveClient < ValueMutableCollectionProxy, __KeyType, __ValueType, __Hasher >;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using ConstIteratorRemoveClient             = __hidden :: __impl :: __LinkedHashMapValueProxyConstIteratorRemoveClient < ValueMutableCollectionProxy, __KeyType, __ValueType, __Hasher >;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using FindOfIterableClient                  = __hidden :: __impl :: __LinkedHashMapValueProxyFindOfIterableClient < ValueMutableCollectionProxy, __KeyType, __ValueType, __Hasher >;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using ConstFindOfIterableClient             = __hidden :: __impl :: __LinkedHashMapValueProxyFindOfConstIterableClient < ValueMutableCollectionProxy, __KeyType, __ValueType, __Hasher >;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using FindOfInitializerListClient           = __hidden :: __impl :: __LinkedHashMapValueProxyFindOfInitializerListClient < ValueMutableCollectionProxy, __KeyType, __ValueType, __Hasher >;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using ConstFindOfInitializerListClient      = __hidden :: __impl :: __LinkedHashMapValueProxyFindOfConstInitializerListClient < ValueMutableCollectionProxy, __KeyType, __ValueType, __Hasher >;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using FindByClient                          = __hidden :: __impl :: __LinkedHashMapValueProxyFindByClient < ValueMutableCollectionProxy, __KeyType, __ValueType, __Hasher >;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using ConstFindByClient                     = __hidden :: __impl :: __LinkedHashMapValueProxyConstFindByClient < ValueMutableCollectionProxy, __KeyType, __ValueType, __Hasher >;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using RemoveOfIterableClient                = __hidden :: __impl :: __LinkedHashMapValueProxyRemoveOfIterableClient < ValueMutableCollectionProxy, __KeyType, __ValueType, __Hasher >;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using RemoveOfInitializerListClient         = __hidden :: __impl :: __LinkedHashMapValueProxyRemoveOfInitializerListClient < ValueMutableCollectionProxy, __KeyType, __ValueType, __Hasher >;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using RemoveByClient                        = __hidden :: __impl :: __LinkedHashMapValueProxyRemoveByClient < ValueMutableCollectionProxy, __KeyType, __ValueType, __Hasher >;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using GenericStatementsClient               = __hidden :: __impl :: __LinkedHashMapValueProxyGenericStatementsClient < ValueMutableCollectionProxy, __KeyType, __ValueType, __Hasher >;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using ContainsOfIterableClient              = __hidden :: __impl :: __LinkedHashMapValueProxyContainsOfIterableClient < ValueMutableCollectionProxy, __KeyType, __ValueType, __Hasher >;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using ContainsOfInitializerListClient       = __hidden :: __impl :: __LinkedHashMapValueProxyContainsOfInitializerListClient < ValueMutableCollectionProxy, __KeyType, __ValueType, __Hasher >;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using ConstGenericStatementsClient          = __hidden :: __impl :: __LinkedHashMapValueProxyConstGenericStatementsClient < ValueMutableCollectionProxy, __KeyType, __ValueType, __Hasher >;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using DelegateForwardIterableClient         = __hidden :: __impl :: __LinkedHashMapValueProxyDelegateForwardIterableClient < ValueMutableCollectionProxy, __KeyType, __ValueType, __Hasher >;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using DelegateForwardConstIterableClient    = __hidden :: __impl :: __LinkedHashMapValueProxyDelegateForwardConstIterableClient < ValueMutableCollectionProxy, __KeyType, __ValueType, __Hasher >;


    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using typename AbstractValueMutableCollectionProxy :: __GenericHandler;         /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using typename AbstractValueMutableCollectionProxy :: __GenericConstHandler;    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */


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
        __CDS_Explicit constexpr ValueMutableCollectionProxy (
                LinkedHashMap < __KeyType, __ValueType, __Hasher > * pMap
        ) noexcept;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        ValueMutableCollectionProxy (
                ValueMutableCollectionProxy const &
        ) noexcept = delete;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        ValueMutableCollectionProxy (
                ValueMutableCollectionProxy &&
        ) noexcept = delete;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_cpplang_ConstexprDestructor ~ValueMutableCollectionProxy() noexcept override;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        auto operator = (
                ValueMutableCollectionProxy const &
        ) noexcept -> ValueMutableCollectionProxy & = delete;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        auto operator = (
                ValueMutableCollectionProxy &&
        ) noexcept -> ValueMutableCollectionProxy & = delete;

    private:    /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard static auto __begin (
                ValueMutableCollectionProxy * pObject
        ) noexcept -> __hidden :: __impl :: __AbstractDelegateIterator < __ValueType > *; /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

    private:    /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard static auto __end (
                ValueMutableCollectionProxy * pObject
        ) noexcept -> __hidden :: __impl :: __AbstractDelegateIterator < __ValueType > *; /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

    private:    /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard static auto __cbegin (
                ValueMutableCollectionProxy const * pObject
        ) noexcept -> __hidden :: __impl :: __AbstractDelegateIterator < __ValueType const > *; /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, modernize-use-nodiscard) */

    private:    /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard static auto __cend (
                ValueMutableCollectionProxy const * pObject
        ) noexcept -> __hidden :: __impl :: __AbstractDelegateIterator < __ValueType const > *; /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, modernize-use-nodiscard) */

    private:    /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction static auto __beginLocal (
                ValueMutableCollectionProxy * pObject
        ) noexcept -> Iterator; /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

    private:    /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction static auto __endLocal (
                ValueMutableCollectionProxy * pObject
        ) noexcept -> Iterator; /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

    private:    /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard constexpr static auto __cbeginLocal (
                ValueMutableCollectionProxy const * pObject
        ) noexcept -> ConstIterator; /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, modernize-use-nodiscard) */

    private:    /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard constexpr static auto __cendLocal (
                ValueMutableCollectionProxy const * pObject
        ) noexcept -> ConstIterator; /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, modernize-use-nodiscard) */

    private:  /* NOLINT(readability-redundant-access-specifiers) */
        static auto __remove ( /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                ValueMutableCollectionProxy       * pObject,
                Iterator                    const * iterator
        ) noexcept -> bool;

    private:  /* NOLINT(readability-redundant-access-specifiers) */
        static auto __removeConst (    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                ValueMutableCollectionProxy       * pObject,
                ConstIterator               const * iterator
        ) noexcept -> bool;

    private:  /* NOLINT(readability-redundant-access-specifiers) */
        static auto __removeArray ( /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                ValueMutableCollectionProxy               * pObject,
                Iterator                    const * const * ppIterators,
                Size                                        iteratorArrayCount
        ) noexcept -> Size;

    private:  /* NOLINT(readability-redundant-access-specifiers) */
        static auto __removeConstArray (    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                ValueMutableCollectionProxy               * pObject,
                ConstIterator               const * const * ppIterators,
                Size                                        iteratorArrayCount
        ) noexcept -> Size;

    private:    /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard auto __equals ( /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                ValueMutableCollectionProxy const & set
        ) const noexcept -> bool;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard auto operator == (
                ValueMutableCollectionProxy const & set
        ) const noexcept -> bool;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard auto operator != (
                ValueMutableCollectionProxy const & set
        ) const noexcept -> bool;
    };
    
} /* namespace cds */

#endif /* __CDS_LINKED_HASH_MAP_VALUE_MUTABLE_COLLECTION_PROXY_HPP__ */
