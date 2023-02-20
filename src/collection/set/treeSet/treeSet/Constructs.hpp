/*
 * Created by stefan on 28.08.2022.
 */

#ifndef __CDS_TREE_SET_CONSTRUCTS_HPP__
#define __CDS_TREE_SET_CONSTRUCTS_HPP__ /* NOLINT(bugprone-reserved-identifier) */

namespace cds { /* NOLINT(modernize-concat-nested-namespaces) */

    template < typename __ElementType >             /* NOLINT(bugprone-reserved-identifier) */
    class TreeSet;

    namespace __hidden {    /* NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier) */
        namespace __impl {  /* NOLINT(bugprone-reserved-identifier) */

            template < typename __ElementType >     /* NOLINT(bugprone-reserved-identifier) */
            auto __treeSetKeyExtractor (            /* NOLINT(bugprone-reserved-identifier) */
                    __ElementType const & element
            ) noexcept -> __ElementType const & {

                return element;
            }


            template < typename __ElementType >     /* NOLINT(bugprone-reserved-identifier) */
            auto __treeSetDestructor (              /* NOLINT(bugprone-reserved-identifier) */
                    __ElementType & element
            ) noexcept -> void {

                element.~__ElementType();
            }


            template < typename __ElementType >     /* NOLINT(bugprone-reserved-identifier) */
            auto __treeSetCopyConstructor (         /* NOLINT(bugprone-reserved-identifier) */
                    __ElementType       & destination,
                    __ElementType const & source
            ) noexcept -> void {

                (void) new ( & destination ) __ElementType ( source );
            }


            template < typename __ElementType >     /* NOLINT(bugprone-reserved-identifier) */
            using __TreeSetImplementation =         /* NOLINT(bugprone-reserved-identifier) */
                    __RedBlackTree <
                            __ElementType,
                            __ElementType,
                            & __treeSetKeyExtractor < __ElementType >,
                            & cds :: predicates :: lessThan < __ElementType >,
                            & cds :: meta :: equals < __ElementType >,
                            & __treeSetDestructor < __ElementType >
                    >;


            template < typename __ElementType >         /* NOLINT(bugprone-reserved-identifier) */
            using __TreeSetDispatcher =                 /* NOLINT(bugprone-reserved-identifier) */
                    typename __TreeSetImplementation <
                            __ElementType
                    > :: template __SetDispatcher <
                            cds :: TreeSet < __ElementType >
                    >;


            template < typename __ElementType >         /* NOLINT(bugprone-reserved-identifier) */
            using __TreeSetServer =                     /* NOLINT(bugprone-reserved-identifier) */
                    cds :: __hidden :: __impl :: __SetServer <
                            cds :: TreeSet < __ElementType >,
                            __ElementType
                    >;


            template < typename __ElementType >                     /* NOLINT(bugprone-reserved-identifier) */
            using __TreeSetDelegateForwardConstIterableClient =     /* NOLINT(bugprone-reserved-identifier) */
                    cds :: __hidden :: __impl :: __LocalDelegateForwardConstIterablePrimitiveClient <
                            cds :: TreeSet < __ElementType >,
                            typename __TreeSetImplementation < __ElementType > :: __rbt_ConstIterator
                    >;


            template < typename __ElementType >                     /* NOLINT(bugprone-reserved-identifier) */
            using __TreeSetDelegateBackwardConstIterableClient =    /* NOLINT(bugprone-reserved-identifier) */
                    cds :: __hidden :: __impl :: __LocalDelegateBackwardConstIterablePrimitiveClient <
                            cds :: TreeSet < __ElementType >,
                            typename __TreeSetImplementation < __ElementType > :: __rbt_ReverseConstIterator
                    >;


            template < typename __ElementType >         /* NOLINT(bugprone-reserved-identifier) */
            using __TreeSetConstIteratorRemoveClient =  /* NOLINT(bugprone-reserved-identifier) */
                    cds :: __hidden :: __impl :: __LocalConstIteratorRemovePrimitiveClient <
                            cds :: TreeSet < __ElementType >,
                            __ElementType,
                            typename __TreeSetImplementation < __ElementType > :: __rbt_AbstractConstIterator
                    >;


            template < typename __ElementType >     /* NOLINT(bugprone-reserved-identifier) */
            using __TreeSetRandomInsertionClient =  /* NOLINT(bugprone-reserved-identifier) */
                    cds :: __hidden :: __impl :: __LocalRandomInsertionPrimitiveClient <
                            cds :: TreeSet < __ElementType >,
                            __ElementType,
                            __ElementType const
                    >;

            template < typename __ElementType >     /* NOLINT(bugprone-reserved-identifier) */
            using __TreeSetFindUniqueClient =       /* NOLINT(bugprone-reserved-identifier) */
                    cds :: __hidden :: __impl :: __LocalFindUniqueImmutablePrimitiveClient <
                            cds :: TreeSet < __ElementType >,
                            __ElementType,
                            typename __TreeSetImplementation < __ElementType > :: __rbt_ConstIterator
                    >;


            template < typename __ElementType >             /* NOLINT(bugprone-reserved-identifier) */
            using __TreeSetContainsOfCollectionClient =     /* NOLINT(bugprone-reserved-identifier) */
                    cds :: __hidden :: __impl :: __LocalContainsOfCompositeClient <
                            cds :: TreeSet < __ElementType >,
                            __ElementType,
                            cds :: Iterable < __ElementType >,
                            & cds :: __hidden :: __impl :: __iterableContains < __ElementType >
                    >;


            template < typename __ElementType >                  /* NOLINT(bugprone-reserved-identifier) */
            using __TreeSetContainsOfInitializerListClient =     /* NOLINT(bugprone-reserved-identifier) */
                    cds :: __hidden :: __impl :: __LocalContainsOfCompositeClient <
                            cds :: TreeSet < __ElementType >,
                            __ElementType,
                            std :: initializer_list < __ElementType >,
                            & cds :: __hidden :: __impl :: __initializerListContains  <
                                    __ElementType,
                                    & cds :: meta :: equals < __ElementType >
                            >
                    >;


            template < typename __ElementType >         /* NOLINT(bugprone-reserved-identifier) */
            using __TreeSetFindOfCollectionClient =     /* NOLINT(bugprone-reserved-identifier) */
                    cds :: __hidden :: __impl :: __LocalFindOfImmutableCompositeClient <
                            cds :: TreeSet < __ElementType >,
                            __ElementType,
                            AbstractRedBlackTreeConstIterator < __ElementType >,
                            cds :: Iterable < __ElementType >,
                            & cds :: __hidden :: __impl :: __iterableContains < __ElementType >,
                            & cds :: __hidden :: __impl :: __iterableNotContains < __ElementType >
                    >;


            template < typename __ElementType >              /* NOLINT(bugprone-reserved-identifier) */
            using __TreeSetFindOfInitializerListClient =     /* NOLINT(bugprone-reserved-identifier) */
                    cds :: __hidden :: __impl :: __LocalFindOfImmutableCompositeClient <
                            cds :: TreeSet < __ElementType >,
                            __ElementType,
                            AbstractRedBlackTreeConstIterator < __ElementType >,
                            std :: initializer_list < __ElementType >,
                            & cds :: __hidden :: __impl :: __initializerListContains < __ElementType, & cds :: meta :: equals < __ElementType > >,
                            & cds :: __hidden :: __impl :: __initializerListNotContains < __ElementType, & cds :: meta :: equals < __ElementType > >
                    >;


            template < typename __ElementType >     /* NOLINT(bugprone-reserved-identifier) */
            using __TreeSetFindByClient =           /* NOLINT(bugprone-reserved-identifier) */
                    cds :: __hidden :: __impl :: __LocalFindByImmutableCompositeClient <
                            cds :: TreeSet < __ElementType >,
                            __ElementType,
                            AbstractRedBlackTreeConstIterator < __ElementType >
                    >;


            template < typename __ElementType >             /* NOLINT(bugprone-reserved-identifier) */
            using __TreeSetRemoveOfCollectionClient =       /* NOLINT(bugprone-reserved-identifier) */
                    cds :: __hidden :: __impl :: __LocalRemoveOfCompositeClient <
                            cds :: TreeSet < __ElementType >,
                            __ElementType,
                            cds :: Iterable < __ElementType >,
                            & cds :: __hidden :: __impl :: __iterableContains < __ElementType >
                    >;


            template < typename __ElementType >             /* NOLINT(bugprone-reserved-identifier) */
            using __TreeSetRemoveOfInitializerListClient =  /* NOLINT(bugprone-reserved-identifier) */
                    cds :: __hidden :: __impl :: __LocalRemoveOfCompositeClient <
                            cds :: TreeSet < __ElementType >,
                            __ElementType,
                            std :: initializer_list< __ElementType >,
                            & cds :: __hidden :: __impl :: __initializerListContains < __ElementType, & cds :: meta :: equals < __ElementType > >
                    >;


            template < typename __ElementType >             /* NOLINT(bugprone-reserved-identifier) */
            using __TreeSetRemoveByClient =                 /* NOLINT(bugprone-reserved-identifier) */
                    cds :: __hidden :: __impl :: __LocalRemoveByCompositeClient <
                            cds :: TreeSet < __ElementType >,
                            __ElementType
                    >;


            template < typename __ElementType >             /* NOLINT(bugprone-reserved-identifier) */
            using __TreeSetGenericStatementsClient =        /* NOLINT(bugprone-reserved-identifier) */
                    cds :: __hidden :: __impl :: __GenericImmutableStatementsCompositeClient <
                            cds :: TreeSet < __ElementType >,
                            __ElementType
                    >;
        }
    }
}

#endif /* __CDS_TREE_SET_CONSTRUCTS_HPP__ */