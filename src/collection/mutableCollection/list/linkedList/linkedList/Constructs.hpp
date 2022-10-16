/*
 * Created by loghin on 08/07/22.
 */

#ifndef __CDS_LINKED_LIST_CONSTRUCTS_HPP__
#define __CDS_LINKED_LIST_CONSTRUCTS_HPP__ /* NOLINT(bugprone-reserved-identifier) */

namespace cds {             /* NOLINT(modernize-concat-nested-namespaces) */
    namespace __hidden {    /* NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier) */
        namespace __impl {  /* NOLINT(bugprone-reserved-identifier) */

            template < typename __ElementType >         /* NOLINT(bugprone-reserved-identifier) */
            using __LinkedListImplementation =          /* NOLINT(bugprone-reserved-identifier) */
                    __DoubleLinkedList <
                            __ElementType,
                            & cds :: meta :: equals < __ElementType >
                    >;


            template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
            using __LinkedListDispatcher =      /* NOLINT(bugprone-reserved-identifier) */
                    typename __LinkedListImplementation < __ElementType > :: template __Dispatcher < LinkedList < __ElementType > >;


            template < typename __ElementType >         /* NOLINT(bugprone-reserved-identifier) */
            using __LinkedListServer =                       /* NOLINT(bugprone-reserved-identifier) */
                    __ListServer <
                            cds :: LinkedList < __ElementType >,
                            __ElementType
                    >;


            template < typename __ElementType >     /* NOLINT(bugprone-reserved-identifier) */
            using __LinkedListRandomInsertionClient =    /* NOLINT(bugprone-reserved-identifier) */
                    __LocalRandomInsertionPrimitiveClient <
                            cds :: LinkedList < __ElementType >,
                            __ElementType,
                            __ElementType
                    >;


            template < typename __ElementType >     /* NOLINT(bugprone-reserved-identifier) */
            using __LinkedListBoundaryInsertionClient =  /* NOLINT(bugprone-reserved-identifier) */
                    __LocalBoundaryInsertionPrimitiveClient <
                            cds :: LinkedList < __ElementType >,
                            __ElementType,
                            __ElementType
                    >;


            template < typename __ElementType >             /* NOLINT(bugprone-reserved-identifier) */
            using __LinkedListIteratorRelativeInsertionClient =  /* NOLINT(bugprone-reserved-identifier) */
                    __LocalIteratorRelativeInsertionPrimitiveClient <
                            cds :: LinkedList < __ElementType >,
                            __ElementType,
                            AbstractBidirectionalNodeIterator < __ElementType >
                    >;


            template < typename __ElementType >                 /* NOLINT(bugprone-reserved-identifier) */
            using __LinkedListConstIteratorRelativeInsertionClient = /* NOLINT(bugprone-reserved-identifier) */
                    __LocalConstIteratorRelativeInsertionPrimitiveClient <
                            cds :: LinkedList < __ElementType >,
                            __ElementType,
                            AbstractBidirectionalNodeConstIterator < __ElementType >
                    >;


            template < typename __ElementType >     /* NOLINT(bugprone-reserved-identifier) */
            using __LinkedListFindOfCollectionClient =   /* NOLINT(bugprone-reserved-identifier) */
                    __LocalFindOfMutableCompositeClient <
                            cds :: LinkedList < __ElementType >,
                            __ElementType,
                            ForwardBidirectionalNodeIterator < __ElementType >,
                            cds :: Collection < __ElementType >,
                            & __collectionContains < __ElementType >,
                            & __collectionNotContains < __ElementType >
                    >;


            template < typename __ElementType >         /* NOLINT(bugprone-reserved-identifier) */
            using __LinkedListFindOfInitializerListClient =  /* NOLINT(bugprone-reserved-identifier) */
                    __LocalFindOfMutableCompositeClient <
                            cds :: LinkedList < __ElementType >,
                            __ElementType,
                            ForwardBidirectionalNodeIterator < __ElementType >,
                            std :: initializer_list < __ElementType >,
                            & __initializerListContains < __ElementType, & cds :: meta :: equals < __ElementType > >,
                            & __initializerListNotContains < __ElementType, & cds :: meta :: equals < __ElementType > >
                    >;


            template < typename __ElementType >         /* NOLINT(bugprone-reserved-identifier) */
            using __LinkedListFindConstOfCollectionClient =  /* NOLINT(bugprone-reserved-identifier) */
                    __LocalFindOfImmutableCompositeClient <
                            cds :: LinkedList < __ElementType >,
                            __ElementType,
                            ForwardBidirectionalNodeConstIterator < __ElementType >,
                            cds :: Collection < __ElementType >,
                            & __collectionContains < __ElementType >,
                            & __collectionNotContains < __ElementType >
                    >;


            template < typename __ElementType >             /* NOLINT(bugprone-reserved-identifier) */
            using __LinkedListFindConstOfInitializerListClient = /* NOLINT(bugprone-reserved-identifier) */
                    __LocalFindOfImmutableCompositeClient <
                            cds :: LinkedList < __ElementType >,
                            __ElementType,
                            ForwardBidirectionalNodeConstIterator < __ElementType >,
                            std :: initializer_list < __ElementType >,
                            & __initializerListContains < __ElementType, & cds :: meta :: equals < __ElementType > >,
                            & __initializerListNotContains < __ElementType, & cds :: meta :: equals < __ElementType > >
                    >;


            template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
            using __LinkedListFindByClient =         /* NOLINT(bugprone-reserved-identifier) */
                            __LocalFindByMutableCompositeClient <
                            cds :: LinkedList < __ElementType >,
                            __ElementType,
                            ForwardBidirectionalNodeIterator < __ElementType >
                    >;


            template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
            using __LinkedListFindConstByClient =    /* NOLINT(bugprone-reserved-identifier) */
                    __LocalFindByImmutableCompositeClient <
                            cds :: LinkedList < __ElementType >,
                            __ElementType,
                            ForwardBidirectionalNodeConstIterator < __ElementType >
                    >;


            template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
            using __LinkedListIteratorRemoveClient = /* NOLINT(bugprone-reserved-identifier) */
                    __LocalIteratorRemovePrimitiveClient <
                            cds :: LinkedList < __ElementType >,
                            __ElementType,
                            AbstractBidirectionalNodeIterator < __ElementType >
                    >;


            template < typename __ElementType >         /* NOLINT(bugprone-reserved-identifier) */
            using __LinkedListConstIteratorRemoveClient =    /* NOLINT(bugprone-reserved-identifier) */
                    __LocalConstIteratorRemovePrimitiveClient <
                            cds :: LinkedList < __ElementType >,
                            __ElementType,
                            AbstractBidirectionalNodeConstIterator < __ElementType >
                    >;


            template < typename __ElementType >     /* NOLINT(bugprone-reserved-identifier) */
            using __LinkedListRemoveOfCollectionClient = /* NOLINT(bugprone-reserved-identifier) */
                    __LocalRemoveOfCompositeClient <
                            cds :: LinkedList < __ElementType >,
                            __ElementType,
                            cds :: Collection < __ElementType >,
                            & __collectionContains < __ElementType >
                    >;


            template < typename __ElementType >             /* NOLINT(bugprone-reserved-identifier) */
            using __LinkedListRemoveOfInitializerListClient =    /* NOLINT(bugprone-reserved-identifier) */
                    __LocalRemoveOfCompositeClient <
                            cds :: LinkedList < __ElementType >,
                            __ElementType,
                            std :: initializer_list < __ElementType >,
                            & __initializerListContains < __ElementType, & cds :: meta :: equals < __ElementType > >
                    >;


            template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
            using __LinkedListRemoveByClient =       /* NOLINT(bugprone-reserved-identifier) */
                    __LocalRemoveByCompositeClient <
                            cds :: LinkedList < __ElementType >,
                            __ElementType
                    >;


            template < typename __ElementType >     /* NOLINT(bugprone-reserved-identifier) */
            using __LinkedListGenericStatementsClient =  /* NOLINT(bugprone-reserved-identifier) */
                    __LocalGenericMutableStatementsCompositeClient <
                            cds :: LinkedList < __ElementType >,
                            __ElementType
                    >;


            template < typename __ElementType >         /* NOLINT(bugprone-reserved-identifier) */
            using __LinkedListGenericConstStatementsClient = /* NOLINT(bugprone-reserved-identifier) */
                    __LocalGenericImmutableStatementsCompositeClient <
                            cds :: LinkedList < __ElementType >,
                            __ElementType
                    >;


            template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
            using __LinkedListReplaceClient =           /* NOLINT(bugprone-reserved-identifier) */
                    __LocalReplaceCompositeClient <
                            cds :: LinkedList < __ElementType >,
                            __ElementType
                    >;


            template < typename __ElementType >         /* NOLINT(bugprone-reserved-identifier) */
            using __LinkedListReplaceOfCollectionClient =    /* NOLINT(bugprone-reserved-identifier) */
                    __LocalReplaceOfCompositeClient <
                            cds :: LinkedList < __ElementType >,
                            __ElementType,
                            cds :: Collection < __ElementType >,
                            & __collectionContains < __ElementType >
                    >;


            template < typename __ElementType >         /* NOLINT(bugprone-reserved-identifier) */
            using __LinkedListReplaceOfInitializerListClient =    /* NOLINT(bugprone-reserved-identifier) */
                    __LocalReplaceOfCompositeClient <
                            cds :: LinkedList < __ElementType >,
                            __ElementType,
                            std :: initializer_list < __ElementType >,
                            & __initializerListContains < __ElementType, & cds :: meta :: equals < __ElementType > >
                    >;


            template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
            using __LinkedListReplaceByClient =      /* NOLINT(bugprone-reserved-identifier) */
                    __LocalReplaceByCompositeClient <
                            cds :: LinkedList < __ElementType >,
                            __ElementType
                    >;


            template < typename __ElementType >     /* NOLINT(bugprone-reserved-identifier) */
            using __LinkedListIndexedOperationsClient =  /* NOLINT(bugprone-reserved-identifier) */
                    __LocalIndexedOperationsPrimitiveClient <
                            cds :: LinkedList < __ElementType >,
                            __ElementType
                    >;


            template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
            using __LinkedListIndicesClient =        /* NOLINT(bugprone-reserved-identifier) */
                    __LocalIndicesCompositeClient <
                            cds :: LinkedList < __ElementType >,
                            __ElementType
                    >;


            template < typename __ElementType >         /* NOLINT(bugprone-reserved-identifier) */
            using __LinkedListIndicesOfCollectionClient =    /* NOLINT(bugprone-reserved-identifier) */
                    __LocalIndicesOfCompositeClient <
                            cds :: LinkedList < __ElementType >,
                            __ElementType,
                            cds :: Collection < __ElementType >,
                            & __collectionContains < __ElementType >
                    >;


            template < typename __ElementType >             /* NOLINT(bugprone-reserved-identifier) */
            using __LinkedListIndicesOfInitializerListClient =   /* NOLINT(bugprone-reserved-identifier) */
                    __LocalIndicesOfCompositeClient <
                            cds :: LinkedList < __ElementType >,
                            __ElementType,
                            std :: initializer_list < __ElementType >,
                            & __initializerListContains < __ElementType, & cds :: meta :: equals < __ElementType > >
                    >;


            template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
            using __LinkedListIndicesByClient =      /* NOLINT(bugprone-reserved-identifier) */
                    __LocalIndicesByCompositeClient <
                            cds :: LinkedList < __ElementType >,
                            __ElementType
                    >;


            template <
                    typename __ElementType                      /* NOLINT(bugprone-reserved-identifier) */
            > using __LinkedListContainsOfCollectionClient =    /* NOLINT(bugprone-reserved-identifier) */
                    __LocalContainsOfCompositeClient <
                            cds :: LinkedList < __ElementType >,
                            __ElementType,
                            cds :: Collection < __ElementType >,
                            __collectionContains < __ElementType >
                    >;


            template <
                    typename __ElementType                          /* NOLINT(bugprone-reserved-identifier) */
            > using __LinkedListContainsOfInitializerListClient =   /* NOLINT(bugprone-reserved-identifier) */
                    __LocalContainsOfCompositeClient <
                            cds :: LinkedList < __ElementType >,
                            __ElementType,
                            std :: initializer_list < __ElementType >,
                            __initializerListContains <
                                    __ElementType,
                                    & cds :: meta :: equals < __ElementType >
                            >
                    >;


            template < typename __ElementType >                 /* NOLINT(bugprone-reserved-identifier) */
            using __LinkedListDelegateForwardIterableClient =   /* NOLINT(bugprone-reserved-identifier) */
                    __LocalDelegateForwardIterablePrimitiveClient <
                            cds :: LinkedList < __ElementType >,
                            typename __LinkedListImplementation < __ElementType > :: __dll_Iterator
                    >;


            template < typename __ElementType >                     /* NOLINT(bugprone-reserved-identifier) */
            using __LinkedListDelegateForwardConstIterableClient =  /* NOLINT(bugprone-reserved-identifier) */
                    __LocalDelegateForwardConstIterablePrimitiveClient <
                            cds :: LinkedList < __ElementType >,
                            typename __LinkedListImplementation < __ElementType > :: __dll_ConstIterator
                    >;


            template < typename __ElementType >                 /* NOLINT(bugprone-reserved-identifier) */
            using __LinkedListDelegateBackwardIterableClient =  /* NOLINT(bugprone-reserved-identifier) */
                    __LocalDelegateBackwardIterablePrimitiveClient <
                            cds :: LinkedList < __ElementType >,
                            typename __LinkedListImplementation < __ElementType > :: __dll_ReverseIterator
                    >;


            template < typename __ElementType >                     /* NOLINT(bugprone-reserved-identifier) */
            using __LinkedListDelegateBackwardConstIterableClient = /* NOLINT(bugprone-reserved-identifier) */
                    __LocalDelegateBackwardConstIterablePrimitiveClient <
                            cds :: LinkedList < __ElementType >,
                            typename __LinkedListImplementation < __ElementType > :: __dll_ConstReverseIterator
                    >;

        }
    }
}

#endif /* __CDS_LINKED_LIST_CONSTRUCTS_HPP__ */