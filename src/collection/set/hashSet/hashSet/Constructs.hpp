/*
 * Created by loghin on 10/08/22.
 */

#ifndef __CDS_HASH_SET_CONSTRUCTS_HPP__ /* NOLINT(llvm-header-guard) */
#define __CDS_HASH_SET_CONSTRUCTS_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

namespace cds {

    template <
            typename __ElementType,                                                     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __Hasher = WrapperHasher < __ElementType, Hash < __ElementType > > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    > class HashSet;

    namespace __hidden {    /* NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        namespace __impl {  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            template < typename __ElementType >     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            constexpr auto __hashSetKeyExtractor (  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __ElementType const & element
            ) noexcept -> __ElementType const & {

                return element;
            }


            template < typename __ElementType >                                     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            __CDS_cpplang_ConstexprNonLiteralReturn auto __hashSetCopyConstructor ( /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __ElementType       & destination,
                    __ElementType const & source
            ) noexcept -> void {

                (void) new ( & destination ) __ElementType ( source );
            }


            template < typename __ElementType >                                 /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            __CDS_cpplang_ConstexprNonLiteralReturn auto __hashSetDestructor (  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __ElementType & element
            ) noexcept -> void {

                element.~__ElementType();
            }


            template <
                    typename __ElementType,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __Hasher           /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > using __HashSetImplementation =   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __HashTable <
                            __ElementType,
                            __ElementType,
                            __Hasher,
                            cds :: __hidden :: __impl :: __PrimeRehashPolicy < uint32 >,
                            & __hashSetKeyExtractor < __ElementType >,
                            & cds :: meta :: equals < __ElementType >,
                            & __hashSetDestructor < __ElementType >
                    >;


            template <
                    typename __ElementType, /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __Hasher       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > using __HashSetDispatcher =   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __HashSetImplementation <
                            __ElementType,
                            __Hasher
                    > :: template __SetDispatcher <
                            HashSet <
                                    __ElementType,
                                    __Hasher
                            >
                    >;


            template <
                    typename __ElementType, /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __Hasher       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > using __HashSetServer =       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __SetServer <
                            cds :: HashSet <
                                    __ElementType,
                                    __Hasher
                            >,
                            __ElementType
                    >;


            template <
                    typename __ElementType,         /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __Hasher               /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > using __HashSetRandomInsertionClient =      /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __LocalRandomInsertionPrimitiveClient <
                            cds :: HashSet <
                                    __ElementType,
                                    __Hasher
                            >,
                            __ElementType,
                            __ElementType const
                    >;


            template <
                    typename __ElementType,         /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __Hasher               /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > using __HashSetIteratorRemoveClient = /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __LocalConstIteratorRemovePrimitiveClient <
                            cds :: HashSet <
                                    __ElementType,
                                    __Hasher
                            >,
                            __ElementType,
                            HashTableConstIterator < __ElementType >
                    >;


            template <
                    typename __ElementType,         /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __Hasher               /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > using __HashSetFindOfIterableClient = /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __LocalFindOfImmutableCompositeClient <
                            cds :: HashSet <
                                    __ElementType,
                                    __Hasher
                            >,
                            __ElementType,
                            HashTableConstIterator < __ElementType >,
                            cds :: Iterable < __ElementType >,
                            & __iterableContains < __ElementType >,
                            & __iterableNotContains < __ElementType >
                    >;


            template <
                    typename __ElementType,         /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __Hasher               /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > using __HashSetFindOfInitializerListClient = /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __LocalFindOfImmutableCompositeClient <
                            cds :: HashSet <
                                    __ElementType,
                                    __Hasher
                            >,
                            __ElementType,
                            HashTableConstIterator < __ElementType >,
                            std :: initializer_list < __ElementType >,
                            & __initializerListContains < __ElementType, & cds :: meta :: equals < __ElementType > >,
                            & __initializerListNotContains < __ElementType, & cds :: meta :: equals < __ElementType > >
                    >;


            template <
                    typename __ElementType,         /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __Hasher               /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > using __HashSetFindByClient =    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __LocalFindByImmutableCompositeClient <
                            cds :: HashSet <
                                    __ElementType,
                                    __Hasher
                            >,
                            __ElementType,
                            HashTableConstIterator < __ElementType >
                    >;


            template <
                    typename __ElementType,             /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __Hasher                   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > using __HashSetRemoveOfIterableClient =   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __LocalRemoveOfCompositeClient <
                            cds :: HashSet <
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
            > using __HashSetRemoveOfInitializerListClient =    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __LocalRemoveOfCompositeClient <
                            cds :: HashSet <
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
            > using __HashSetRemoveByClient =       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __LocalRemoveByCompositeClient <
                            cds :: HashSet <
                                    __ElementType,
                                    __Hasher
                            >,
                            __ElementType
                    >;


            template <
                    typename __ElementType,         /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __Hasher               /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > using __HashSetGenericStatementsClient =  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __LocalGenericImmutableStatementsCompositeClient <
                            cds :: HashSet <
                                    __ElementType,
                                    __Hasher
                            >,
                            __ElementType
                    >;


            template <
                    typename __ElementType,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __Hasher           /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > using __HashSetFindUniqueClient = /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __LocalFindUniqueImmutablePrimitiveClient <
                            cds :: HashSet <
                                    __ElementType,
                                    __Hasher
                            >,
                            __ElementType,
                            HashTableConstIterator < __ElementType >
                    >;


            template <
                    typename __ElementType,                 /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __Hasher                       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > using __HashSetContainsOfIterableClient =   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __LocalContainsOfCompositeClient <
                            cds :: HashSet < __ElementType, __Hasher >,
                            __ElementType,
                            cds :: Iterable < __ElementType >,
                            & __iterableContains < __ElementType >
                    >;


            template <
                    typename __ElementType,                     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __Hasher                           /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > using __HashSetContainsOfInitializerListClient =  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __LocalContainsOfCompositeClient <
                            cds :: HashSet < __ElementType, __Hasher >,
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
            > using __HashSetDelegateForwardConstIterableClient =   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __LocalDelegateForwardConstIterablePrimitiveClient <
                            cds :: HashSet < __ElementType, __Hasher >,
                            typename __HashSetImplementation < __ElementType, __Hasher > :: __ht_ConstIterator
                    >;

        } /* namespace __impl */
    } /* namespace __hidden */
} /* namespace cds */

#endif /* __CDS_HASH_SET_CONSTRUCTS_HPP__ */
