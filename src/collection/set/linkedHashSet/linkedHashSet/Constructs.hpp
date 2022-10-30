/*
 * Created by loghin on 02/10/22.
 */

#ifndef __CDS_LINKED_HASH_SET_CONSTRUCTS_HPP__ /* NOLINT(llvm-header-guard) */
#define __CDS_LINKED_HASH_SET_CONSTRUCTS_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

namespace cds {

    template <
            typename __ElementType,                                                     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __Hasher = WrapperHasher < __ElementType, Hash < __ElementType > > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    > class LinkedHashSet;

    namespace __hidden {    /* NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        namespace __impl {  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            template < typename __ElementType >             /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            constexpr auto __linkedHashSetKeyExtractor (    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __ElementType const & element
            ) noexcept -> __ElementType const & {

                return element;
            }


            template < typename __ElementType >                                                             /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            __CDS_MaybeUnused __CDS_cpplang_ConstexprNonLiteralReturn auto __linkedHashSetCopyConstructor ( /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-avoid-non-const-global-variables) */
                    __ElementType       & destination,
                    __ElementType const & source
            ) noexcept -> void {

                (void) new ( & destination ) __ElementType ( source );
            }


            template < typename __ElementType >                                         /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            __CDS_cpplang_ConstexprNonLiteralReturn auto __linkedHashSetDestructor (    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __ElementType & element
            ) noexcept -> void {

                element.~__ElementType();
            }


            template <
                    typename __DecoratedIteratorType,                   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ValueAtType                              /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > constexpr auto __linkedHashSetIteratorDecoratorValueAt (  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __DecoratedIteratorType const & iterator
            ) noexcept -> __ValueAtType & {

                return * ( * iterator );
            }


            template <
                    typename __ElementType,                     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __Hasher                           /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > using __LinkedHashSetHashTableImplementation =    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
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
                    typename __ElementType,                     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __Hasher                           /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > using __LinkedHashSetLinkedListImplementation =   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __SingleLinkedList <
                            __ElementType *,
                            & cds :: meta :: equals < __ElementType * >
                    >;


            template <
                    typename __ElementType,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __Hasher           /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > using __LinkedHashSetIterator =   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    ForwardIteratorGenericDecorator <
                            typename __LinkedHashSetLinkedListImplementation < __ElementType, __Hasher > :: __sll_ConstIterator,
                            __ElementType const,
                            & __linkedHashSetIteratorDecoratorValueAt <
                                    typename __LinkedHashSetLinkedListImplementation < __ElementType, __Hasher > :: __sll_ConstIterator,
                                    __ElementType const
                            >
                    >;


            template <
                    typename __ElementType, /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __Hasher       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > using __LinkedHashSetServer = /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __SetServer <
                            cds :: LinkedHashSet <
                                    __ElementType,
                                    __Hasher
                            >,
                            __ElementType
                    >;


            template <
                    typename __ElementType,         /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __Hasher               /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > using __LinkedHashSetRandomInsertionClient =      /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __LocalRandomInsertionPrimitiveClient <
                            cds :: LinkedHashSet <
                                    __ElementType,
                                    __Hasher
                            >,
                            __ElementType,
                            __ElementType const
                    >;


            template <
                    typename __ElementType,         /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __Hasher               /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > using __LinkedHashSetIteratorRemoveClient = /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __LocalConstIteratorRemovePrimitiveClient <
                            cds :: LinkedHashSet <
                                    __ElementType,
                                    __Hasher
                            >,
                            __ElementType,
                            __LinkedHashSetIterator < __ElementType, __Hasher >
                    >;


            template <
                    typename __ElementType,                 /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __Hasher                       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > using __LinkedHashSetFindOfIterableClient =   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __LocalFindOfImmutableCompositeClient <
                            cds :: LinkedHashSet <
                                    __ElementType,
                                    __Hasher
                            >,
                            __ElementType,
                            __LinkedHashSetIterator < __ElementType, __Hasher >,
                            cds :: Iterable < __ElementType >,
                            & __iterableContains < __ElementType >,
                            & __iterableNotContains < __ElementType >
                    >;


            template <
                    typename __ElementType,         /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __Hasher               /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > using __LinkedHashSetFindOfInitializerListClient = /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __LocalFindOfImmutableCompositeClient <
                            cds :: LinkedHashSet <
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
                    typename __ElementType,         /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __Hasher               /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > using __LinkedHashSetFindByClient =    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __LocalFindByImmutableCompositeClient <
                            cds :: LinkedHashSet <
                                    __ElementType,
                                    __Hasher
                            >,
                            __ElementType,
                            __LinkedHashSetIterator < __ElementType, __Hasher >
                    >;


            template <
                    typename __ElementType,                 /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __Hasher                       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > using __LinkedHashSetRemoveOfIterableClient = /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __LocalRemoveOfCompositeClient <
                            cds :: LinkedHashSet <
                                    __ElementType,
                                    __Hasher
                            >,
                            __ElementType,
                            cds :: Iterable < __ElementType >,
                            & __iterableContains < __ElementType >
                    >;


            template <
                    typename __ElementType,         /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __Hasher               /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > using __LinkedHashSetRemoveOfInitializerListClient =    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __LocalRemoveOfCompositeClient <
                            cds :: LinkedHashSet <
                                    __ElementType,
                                    __Hasher
                            >,
                            __ElementType,
                            std :: initializer_list < __ElementType >,
                            & __initializerListContains < __ElementType, & cds :: meta :: equals < __ElementType > >
                    >;


            template <
                    typename __ElementType,         /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __Hasher               /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > using __LinkedHashSetRemoveByClient =       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __LocalRemoveByCompositeClient <
                            cds :: LinkedHashSet <
                                    __ElementType,
                                    __Hasher
                            >,
                            __ElementType
                    >;


            template <
                    typename __ElementType,         /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __Hasher               /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > using __LinkedHashSetGenericStatementsClient =  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __LocalGenericImmutableStatementsCompositeClient <
                            cds :: LinkedHashSet <
                                    __ElementType,
                                    __Hasher
                            >,
                            __ElementType
                    >;


            template <
                    typename __ElementType,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __Hasher           /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > using __LinkedHashSetFindUniqueClient = /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __LocalFindUniqueImmutablePrimitiveClient <
                            cds :: LinkedHashSet <
                                    __ElementType,
                                    __Hasher
                            >,
                            __ElementType,
                            __LinkedHashSetIterator < __ElementType, __Hasher >
                    >;


            template <
                    typename __ElementType,                     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __Hasher                           /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > using __LinkedHashSetContainsOfIterableClient =   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __LocalContainsOfCompositeClient <
                            cds :: LinkedHashSet < __ElementType, __Hasher >,
                            __ElementType,
                            cds :: Iterable < __ElementType >,
                            & __iterableContains < __ElementType >
                    >;


            template <
                    typename __ElementType,                     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __Hasher                           /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > using __LinkedHashSetContainsOfInitializerListClient =  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __LocalContainsOfCompositeClient <
                            cds :: LinkedHashSet < __ElementType, __Hasher >,
                            __ElementType,
                            std :: initializer_list < __ElementType >,
                            & __initializerListContains <
                                    __ElementType,
                                    & cds :: meta :: equals < __ElementType >
                            >
                    >;


            template <
                    typename __ElementType,                         /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __Hasher                               /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > using __LinkedHashSetDelegateForwardConstIterableClient =   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __LocalDelegateForwardConstIterablePrimitiveClient <
                            cds :: LinkedHashSet < __ElementType, __Hasher >,
                            __LinkedHashSetIterator < __ElementType, __Hasher >
                    >;

        } /* namespace __impl */
    } /* namespace __hidden */
    
} /* namespace cds */

#endif /* __CDS_LINKED_HASH_SET_CONSTRUCTS_HPP__ */
