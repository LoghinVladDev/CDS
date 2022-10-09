/*
 * Created by loghin on 02/10/22.
 */

#ifndef __CDS_LINKED_HASH_SET_CONSTRUCTS_HPP__
#define __CDS_LINKED_HASH_SET_CONSTRUCTS_HPP__ /* NOLINT(bugprone-reserved-identifier) */

namespace cds { /* NOLINT(modernize-concat-nested-namespaces) */
    namespace experimental {

        template <
                typename __ElementType,                                                     /* NOLINT(bugprone-reserved-identifier) */
                typename __Hasher = WrapperHasher < __ElementType, Hash < __ElementType > > /* NOLINT(bugprone-reserved-identifier) */
        > class LinkedHashSet;

        namespace __hidden {    /* NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier) */
            namespace __impl {  /* NOLINT(bugprone-reserved-identifier) */

                template < typename __ElementType >             /* NOLINT(bugprone-reserved-identifier) */
                constexpr auto __linkedHashSetKeyExtractor (    /* NOLINT(bugprone-reserved-identifier) */
                        __ElementType const & element
                ) noexcept -> __ElementType const & {

                    return element;
                }


                template < typename __ElementType >                                             /* NOLINT(bugprone-reserved-identifier) */
                __CDS_cpplang_ConstexprNonLiteralReturn auto __linkedHashSetCopyConstructor (   /* NOLINT(bugprone-reserved-identifier) */
                        __ElementType       & destination,
                        __ElementType const & source
                ) noexcept -> void {

                    (void) new ( & destination ) __ElementType ( source );
                }


                template < typename __ElementType >                                         /* NOLINT(bugprone-reserved-identifier) */
                __CDS_cpplang_ConstexprNonLiteralReturn auto __linkedHashSetDestructor (    /* NOLINT(bugprone-reserved-identifier) */
                        __ElementType & element
                ) noexcept -> void {

                    element.~__ElementType();
                }


                template <
                        typename __DecoratedIteratorType,                   /* NOLINT(bugprone-reserved-identifier) */
                        typename __ValueAtType                              /* NOLINT(bugprone-reserved-identifier) */
                > constexpr auto __linkedHashSetIteratorDecoratorValueAt (  /* NOLINT(bugprone-reserved-identifier) */
                        __DecoratedIteratorType const & iterator
                ) noexcept -> __ValueAtType & {

                    return * ( * iterator );
                }


                template <
                        typename __ElementType,                     /* NOLINT(bugprone-reserved-identifier) */
                        typename __Hasher                           /* NOLINT(bugprone-reserved-identifier) */
                > using __LinkedHashSetHashTableImplementation =    /* NOLINT(bugprone-reserved-identifier) */
                        __HashTable <
                                __ElementType,
                                __ElementType,
                                __Hasher,
                                cds :: __hidden :: __impl :: __PrimeRehashPolicy < uint32 >,
                                & __linkedHashSetKeyExtractor < __ElementType >,
                                & cds :: meta :: equals < __ElementType >,
                                & __linkedHashSetDestructor < __ElementType >
                        >;


                template <
                        typename __ElementType,                     /* NOLINT(bugprone-reserved-identifier) */
                        typename __Hasher                           /* NOLINT(bugprone-reserved-identifier) */
                > using __LinkedHashSetLinkedListImplementation =   /* NOLINT(bugprone-reserved-identifier) */
                        __SingleLinkedList <
                                __ElementType *,
                                & cds :: meta :: equals < __ElementType * >
                        >;


                template <
                        typename __ElementType,     /* NOLINT(bugprone-reserved-identifier) */
                        typename __Hasher           /* NOLINT(bugprone-reserved-identifier) */
                > using __LinkedHashSetIterator =   /* NOLINT(bugprone-reserved-identifier) */
                        ForwardIteratorGenericDecorator <
                                typename __LinkedHashSetLinkedListImplementation < __ElementType, __Hasher > :: __sll_ConstIterator,
                                __ElementType const,
                                & __linkedHashSetIteratorDecoratorValueAt <
                                        typename __LinkedHashSetLinkedListImplementation < __ElementType, __Hasher > :: __sll_ConstIterator,
                                        __ElementType const
                                >
                        >;


                template <
                        typename __ElementType, /* NOLINT(bugprone-reserved-identifier) */
                        typename __Hasher       /* NOLINT(bugprone-reserved-identifier) */
                > using __LinkedHashSetServer = /* NOLINT(bugprone-reserved-identifier) */
                        __SetServer <
                                cds :: experimental :: LinkedHashSet <
                                        __ElementType,
                                        __Hasher
                                >,
                                __ElementType
                        >;


                template <
                        typename __ElementType,         /* NOLINT(bugprone-reserved-identifier) */
                        typename __Hasher               /* NOLINT(bugprone-reserved-identifier) */
                > using __LinkedHashSetRandomInsertionClient =      /* NOLINT(bugprone-reserved-identifier) */
                        __LocalRandomInsertionPrimitiveClient <
                                cds :: experimental :: LinkedHashSet <
                                        __ElementType,
                                        __Hasher
                                >,
                                __ElementType,
                                __ElementType const
                        >;


                template <
                        typename __ElementType,         /* NOLINT(bugprone-reserved-identifier) */
                        typename __Hasher               /* NOLINT(bugprone-reserved-identifier) */
                > using __LinkedHashSetIteratorRemoveClient = /* NOLINT(bugprone-reserved-identifier) */
                        __LocalConstIteratorRemovePrimitiveClient <
                                cds :: experimental :: LinkedHashSet <
                                        __ElementType,
                                        __Hasher
                                >,
                                __ElementType,
                                __LinkedHashSetIterator < __ElementType, __Hasher >
                        >;


                template <
                        typename __ElementType,         /* NOLINT(bugprone-reserved-identifier) */
                        typename __Hasher               /* NOLINT(bugprone-reserved-identifier) */
                > using __LinkedHashSetFindOfCollectionClient =  /* NOLINT(bugprone-reserved-identifier) */
                        __LocalFindOfImmutableCompositeClient <
                                cds :: experimental :: LinkedHashSet <
                                        __ElementType,
                                        __Hasher
                                >,
                                __ElementType,
                                __LinkedHashSetIterator < __ElementType, __Hasher >,
                                cds :: experimental :: Collection < __ElementType >,
                                & __collectionContains < __ElementType >,
                                & __collectionNotContains < __ElementType >
                        >;


                template <
                        typename __ElementType,         /* NOLINT(bugprone-reserved-identifier) */
                        typename __Hasher               /* NOLINT(bugprone-reserved-identifier) */
                > using __LinkedHashSetFindOfInitializerListClient = /* NOLINT(bugprone-reserved-identifier) */
                        __LocalFindOfImmutableCompositeClient <
                                cds :: experimental :: LinkedHashSet <
                                        __ElementType,
                                        __Hasher
                                >,
                                __ElementType,
                                __LinkedHashSetIterator < __ElementType, __Hasher >,
                                std :: initializer_list < __ElementType >,
                                & __initializerListContains < __ElementType, & cds :: meta :: equals < __ElementType > >,
                                & __initializerListNotContains < __ElementType, & cds :: meta :: equals < __ElementType > >
                        >;


                template <
                        typename __ElementType,         /* NOLINT(bugprone-reserved-identifier) */
                        typename __Hasher               /* NOLINT(bugprone-reserved-identifier) */
                > using __LinkedHashSetFindByClient =    /* NOLINT(bugprone-reserved-identifier) */
                        __LocalFindByImmutableCompositeClient <
                                cds :: experimental :: LinkedHashSet <
                                        __ElementType,
                                        __Hasher
                                >,
                                __ElementType,
                                __LinkedHashSetIterator < __ElementType, __Hasher >
                        >;


                template <
                        typename __ElementType,         /* NOLINT(bugprone-reserved-identifier) */
                        typename __Hasher               /* NOLINT(bugprone-reserved-identifier) */
                > using __LinkedHashSetRemoveOfCollectionClient = /* NOLINT(bugprone-reserved-identifier) */
                        __LocalRemoveOfCompositeClient <
                                cds :: experimental :: LinkedHashSet <
                                        __ElementType,
                                        __Hasher
                                >,
                                __ElementType,
                                cds :: experimental :: Collection < __ElementType >,
                                & __collectionContains < __ElementType >
                        >;


                template <
                        typename __ElementType,         /* NOLINT(bugprone-reserved-identifier) */
                        typename __Hasher               /* NOLINT(bugprone-reserved-identifier) */
                > using __LinkedHashSetRemoveOfInitializerListClient =    /* NOLINT(bugprone-reserved-identifier) */
                        __LocalRemoveOfCompositeClient <
                                cds :: experimental :: LinkedHashSet <
                                        __ElementType,
                                        __Hasher
                                >,
                                __ElementType,
                                std :: initializer_list < __ElementType >,
                                & __initializerListContains < __ElementType, & cds :: meta :: equals < __ElementType > >
                        >;


                template <
                        typename __ElementType,         /* NOLINT(bugprone-reserved-identifier) */
                        typename __Hasher               /* NOLINT(bugprone-reserved-identifier) */
                > using __LinkedHashSetRemoveByClient =       /* NOLINT(bugprone-reserved-identifier) */
                        __LocalRemoveByCompositeClient <
                                cds :: experimental :: LinkedHashSet <
                                        __ElementType,
                                        __Hasher
                                >,
                                __ElementType
                        >;


                template <
                        typename __ElementType,         /* NOLINT(bugprone-reserved-identifier) */
                        typename __Hasher               /* NOLINT(bugprone-reserved-identifier) */
                > using __LinkedHashSetGenericStatementsClient =  /* NOLINT(bugprone-reserved-identifier) */
                        __LocalGenericImmutableStatementsCompositeClient <
                                cds :: experimental :: LinkedHashSet <
                                        __ElementType,
                                        __Hasher
                                >,
                                __ElementType
                        >;


                template <
                        typename __ElementType,     /* NOLINT(bugprone-reserved-identifier) */
                        typename __Hasher           /* NOLINT(bugprone-reserved-identifier) */
                > using __LinkedHashSetFindUniqueClient = /* NOLINT(bugprone-reserved-identifier) */
                        __LocalFindUniqueImmutablePrimitiveClient <
                                cds :: experimental :: LinkedHashSet <
                                        __ElementType,
                                        __Hasher
                                >,
                                __ElementType,
                                __LinkedHashSetIterator < __ElementType, __Hasher >
                        >;


                template <
                        typename __ElementType,                 /* NOLINT(bugprone-reserved-identifier) */
                        typename __Hasher                       /* NOLINT(bugprone-reserved-identifier) */
                > using __LinkedHashSetContainsOfCollectionClient =   /* NOLINT(bugprone-reserved-identifier) */
                        __LocalContainsOfCompositeClient <
                                cds :: experimental :: LinkedHashSet < __ElementType, __Hasher >,
                                __ElementType,
                                cds :: experimental :: Collection < __ElementType >,
                                __collectionContains < __ElementType >
                        >;


                template <
                        typename __ElementType,                     /* NOLINT(bugprone-reserved-identifier) */
                        typename __Hasher                           /* NOLINT(bugprone-reserved-identifier) */
                > using __LinkedHashSetContainsOfInitializerListClient =  /* NOLINT(bugprone-reserved-identifier) */
                        __LocalContainsOfCompositeClient <
                                cds :: experimental :: LinkedHashSet < __ElementType, __Hasher >,
                                __ElementType,
                                std :: initializer_list < __ElementType >,
                                __initializerListContains <
                                        __ElementType,
                                        & cds :: meta :: equals < __ElementType >
                                >
                        >;


                template <
                        typename __ElementType,                         /* NOLINT(bugprone-reserved-identifier) */
                        typename __Hasher                               /* NOLINT(bugprone-reserved-identifier) */
                > using __LinkedHashSetDelegateForwardConstIterableClient =   /* NOLINT(bugprone-reserved-identifier) */
                        __LocalDelegateForwardConstIterablePrimitiveClient <
                                cds :: experimental :: LinkedHashSet < __ElementType, __Hasher >,
                                __LinkedHashSetIterator < __ElementType, __Hasher >
                        >;

            }
        }

    }
}

#endif /* __CDS_LINKED_HASH_SET_CONSTRUCTS_HPP__ */
