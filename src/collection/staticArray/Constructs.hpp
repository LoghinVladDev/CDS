/*
 * Created by loghin on 16/02/23.
 */

#ifndef __CDS_STATIC_ARRAY_CONSTRUCTS_HPP__ /* NOLINT(llvm-header-guard) */
#define __CDS_STATIC_ARRAY_CONSTRUCTS_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

namespace cds {             /* NOLINT(modernize-concat-nested-namespaces) */

    template <
            typename    __ElementType,  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            Size        __size          /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    > class StaticArray;

    namespace __hidden {    /* NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        namespace __impl {  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            template < typename __ElementType, Size __size >
            using __StaticArrayImplementation =
                    __StaticArrayBase <
                            __ElementType,
                            __size,
                            & cds :: meta :: equals < __ElementType >,
                            __StaticArrayMemoryContainer < __ElementType, __size >
                    >;


            template < typename __ElementType, Size __size >
            using __StaticArrayDispatcher =
                    typename __StaticArrayImplementation < __ElementType, __size > :: template __Dispatcher < StaticArray < __ElementType, __size > >;


            template < typename __ElementType, Size __size >
            using __StaticArrayServer =
                    __IterableServer <
                            StaticArray < __ElementType, __size >,
                            __ElementType
                    >;


            template < typename __ElementType, Size __size >    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            using __StaticArrayFindOfIterableClient =           /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __LocalFindOfMutableCompositeClient <
                            cds :: StaticArray < __ElementType, __size >,
                            __ElementType,          /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-avoid-non-const-global-variables) */
                            AddressIterator < __ElementType >,
                            cds :: Iterable < __ElementType >,
                            & __iterableContains < __ElementType >,
                            & __iterableNotContains < __ElementType >
                    >;


            template < typename __ElementType, Size __size >    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            using __StaticArrayFindOfInitializerListClient =    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __LocalFindOfMutableCompositeClient <
                            cds :: StaticArray < __ElementType, __size >,
                            __ElementType,          /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-avoid-non-const-global-variables) */
                            AddressIterator < __ElementType >,
                            std :: initializer_list < __ElementType >,
                            & __initializerListContains < __ElementType, & cds :: meta :: equals < __ElementType > >,
                            & __initializerListNotContains < __ElementType, & cds :: meta :: equals < __ElementType > >
                    >;


            template < typename __ElementType, Size __size >    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            using __StaticArrayConstFindOfIterableClient =      /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __LocalFindOfImmutableCompositeClient <
                            cds :: StaticArray < __ElementType, __size >,
                            __ElementType,          /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-avoid-non-const-global-variables) */
                            AddressIterator < __ElementType const >,
                            cds :: Iterable < __ElementType >,
                            & __iterableContains < __ElementType >,
                            & __iterableNotContains < __ElementType >
                    >;


            template < typename __ElementType, Size __size >        /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            using __StaticArrayConstFindOfInitializerListClient =   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __LocalFindOfImmutableCompositeClient <
                            cds :: StaticArray < __ElementType, __size >,
                            __ElementType,          /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-avoid-non-const-global-variables) */
                            AddressIterator < __ElementType const >,
                            std :: initializer_list < __ElementType >,
                            & __initializerListContains < __ElementType, & cds :: meta :: equals < __ElementType > >,
                            & __initializerListNotContains < __ElementType, & cds :: meta :: equals < __ElementType > >
                    >;


            template < typename __ElementType, Size __size >    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            using __StaticArrayFindByClient =                   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __LocalFindByMutableCompositeClient <
                            cds :: StaticArray < __ElementType, __size >,
                            __ElementType,      /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-avoid-non-const-global-variables) */
                            AddressIterator < __ElementType >
                    >;


            template < typename __ElementType, Size __size >    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            using __StaticArrayConstFindByClient =              /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __LocalFindByImmutableCompositeClient <
                            cds :: StaticArray < __ElementType, __size >,
                            __ElementType,      /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-avoid-non-const-global-variables) */
                            AddressIterator < __ElementType const >
                    >;


            template < typename __ElementType, Size __size >    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            using __StaticArrayGenericStatementsClient =        /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __LocalGenericMutableStatementsCompositeClient <
                            cds :: StaticArray < __ElementType, __size >,
                            __ElementType
                    >;


            template < typename __ElementType, Size __size >    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            using __StaticArrayGenericConstStatementsClient =   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __LocalGenericImmutableStatementsCompositeClient <
                            cds :: StaticArray < __ElementType, __size >,
                            __ElementType
                    >;


            template < typename __ElementType, Size __size >    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            using __StaticArrayReplaceClient =                  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __LocalReplaceCompositeClient <
                            cds :: StaticArray < __ElementType, __size >,
                            __ElementType
                    >;


            template < typename __ElementType, Size __size >     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            using __StaticArrayReplaceOfIterableClient =  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __LocalReplaceOfCompositeClient <
                            cds :: StaticArray < __ElementType, __size >,
                            __ElementType,              /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-avoid-non-const-global-variables) */
                            cds :: Iterable < __ElementType >,
                            & __iterableContains < __ElementType >
                    >;


            template < typename __ElementType, Size __size >             /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            using __StaticArrayReplaceOfInitializerListClient =   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __LocalReplaceOfCompositeClient <
                            cds :: StaticArray < __ElementType, __size >,
                            __ElementType,                  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-avoid-non-const-global-variables) */
                            std :: initializer_list < __ElementType >,
                            & __initializerListContains < __ElementType, & cds :: meta :: equals < __ElementType > >
                    >;


            template < typename __ElementType, Size __size > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            using __StaticArrayReplaceByClient =      /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __LocalReplaceByCompositeClient <
                            cds :: StaticArray < __ElementType, __size >,
                            __ElementType
                    >;


            template < typename __ElementType, Size __size >     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            using __StaticArrayIndexedOperationsClient =  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __LocalIndexedOperationsPrimitiveClient <
                            cds :: StaticArray < __ElementType, __size >,
                            __ElementType
                    >;


            template < typename __ElementType, Size __size > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            using __StaticArrayIndicesClient =        /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __LocalIndicesCompositeClient <
                            cds :: StaticArray < __ElementType, __size >,
                            __ElementType
                    >;


            template < typename __ElementType, Size __size >     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            using __StaticArrayIndicesOfIterableClient =  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __LocalIndicesOfCompositeClient <
                            cds :: StaticArray < __ElementType, __size >,
                            __ElementType,              /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-avoid-non-const-global-variables) */
                            cds :: Iterable < __ElementType >,
                            & __iterableContains < __ElementType >
                    >;


            template < typename __ElementType, Size __size >             /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            using __StaticArrayIndicesOfInitializerListClient =   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __LocalIndicesOfCompositeClient <
                            cds :: StaticArray < __ElementType, __size >,
                            __ElementType,                  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-avoid-non-const-global-variables) */
                            std :: initializer_list < __ElementType >,
                            & __initializerListContains < __ElementType, & cds :: meta :: equals < __ElementType > >
                    >;


            template < typename __ElementType, Size __size > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            using __StaticArrayIndicesByClient =      /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __LocalIndicesByCompositeClient <
                            cds :: StaticArray < __ElementType, __size >,
                            __ElementType
                    >;


            template < typename __ElementType, Size __size >     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            using __StaticArrayContainsOfIterableClient = /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __LocalContainsOfCompositeClient <
                            cds :: StaticArray < __ElementType, __size >,
                            __ElementType,              /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-avoid-non-const-global-variables) */
                            cds :: Iterable < __ElementType >,
                            & __iterableContains < __ElementType >
                    >;


            template < typename __ElementType, Size __size >             /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            using __StaticArrayContainsOfInitializerListClient =  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __LocalContainsOfCompositeClient <
                            cds :: StaticArray < __ElementType, __size >,
                            __ElementType,                  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-avoid-non-const-global-variables) */
                            std :: initializer_list < __ElementType >,
                            & __initializerListContains < __ElementType, & cds :: meta :: equals < __ElementType > >
                    >;


            template < typename __ElementType, Size __size >             /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            using __StaticArrayDelegateForwardIterableClient =    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __LocalDelegateForwardIterablePrimitiveClient <
                            cds :: StaticArray < __ElementType, __size >,
                            typename __StaticArrayImplementation < __ElementType, __size > :: __sab_Iterator
                    >;


            template < typename __ElementType, Size __size >                 /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            using __StaticArrayDelegateForwardConstIterableClient =   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __LocalDelegateForwardConstIterablePrimitiveClient <
                            cds :: StaticArray < __ElementType, __size >,
                            typename __StaticArrayImplementation < __ElementType, __size > :: __sab_ConstIterator
                    >;


            template < typename __ElementType, Size __size >             /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            using __StaticArrayDelegateBackwardIterableClient =   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __LocalDelegateBackwardIterablePrimitiveClient <
                            cds :: StaticArray < __ElementType, __size >,
                            typename __StaticArrayImplementation < __ElementType, __size > :: __sab_ReverseIterator
                    >;


            template < typename __ElementType, Size __size >                 /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            using __StaticArrayDelegateBackwardConstIterableClient =  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __LocalDelegateBackwardConstIterablePrimitiveClient <
                            cds :: StaticArray < __ElementType, __size >,
                            typename __StaticArrayImplementation < __ElementType, __size > :: __sab_ConstReverseIterator
                    >;

        } /* namespace __impl */
    } /* namespace __hidden */
} /* namespace cds */

#endif /* __CDS_STATIC_ARRAY_CONSTRUCTS_HPP__ */
