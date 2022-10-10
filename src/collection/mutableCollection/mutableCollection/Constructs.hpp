/*
 * Created by loghin on 08/07/22.
 */

#ifndef __CDS_MUTABLE_COLLECTION_CONSTRUCTS_HPP__
#define __CDS_MUTABLE_COLLECTION_CONSTRUCTS_HPP__ /* NOLINT(bugprone-reserved-identifier) */

namespace cds {

    /**
     * @brief Pre-declaration of the MutableCollection class
     * @namespace cds
     */
    template < typename > /* NOLINT(bugprone-reserved-identifier) */
    class MutableCollection;

    namespace __hidden {    /* NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier) */
        namespace __impl {  /* NOLINT(bugprone-reserved-identifier) */

            /**
             * @typedef Alias used by MutableCollection to implement the Delegate Forward Iterable Client
             * @tparam __ElementType the type of the elements enclosed in the extending Collection
             * @namespace cds :: __hidden :: __impl
             * @internal library-private
             */
            template < typename __ElementType >                         /* NOLINT(bugprone-reserved-identifier) */
            using __MutableCollectionDelegateForwardIterableClient =    /* NOLINT(bugprone-reserved-identifier) */
                    __DelegateForwardIterablePrimitiveClient <
                            cds :: MutableCollection < __ElementType >,
                            __ElementType,
                            false
                    >;


            /**
             * @typedef Alias used by MutableCollection to implement the Iterator Remove Client
             * @tparam __ElementType the type of the elements enclosed in the extending Collection
             * @namespace cds :: __hidden :: __impl
             * @internal library-private
             */
            template < typename __ElementType >             /* NOLINT(bugprone-reserved-identifier) */
            using __MutableCollectionIteratorRemoveClient = /* NOLINT(bugprone-reserved-identifier) */
                    __AbstractIteratorRemovePrimitiveClient <
                            cds :: MutableCollection < __ElementType >,
                            __ElementType
                    >;


            /**
             * @typedef Alias used by MutableCollection to implement the Random Insertion Client
             * @tparam __ElementType the type of the elements enclosed in the extending Collection
             * @namespace cds :: __hidden :: __impl
             * @internal library-private
             */
            template < typename __ElementType >                 /* NOLINT(bugprone-reserved-identifier) */
            using __MutableCollectionRandomInsertionClient =    /* NOLINT(bugprone-reserved-identifier) */
                    __RandomInsertionPrimitiveClient <
                            cds :: MutableCollection < __ElementType >,
                            __ElementType,
                            __ElementType
                    >;


            /**
             * @typedef Alias used by MutableCollection to implement the Find Of Mutable Collection Client
             * @tparam __ElementType the type of the elements enclosed in the extending Collection
             * @namespace cds :: __hidden :: __impl
             * @internal library-private
             */
            template < typename __ElementType >                 /* NOLINT(bugprone-reserved-identifier) */
            using __MutableCollectionFindOfCollectionClient =   /* NOLINT(bugprone-reserved-identifier) */
                    __FindOfMutableCompositeClient <
                            cds :: MutableCollection < __ElementType >,
                            __ElementType,
                            typename __MutableCollectionDelegateForwardIterableClient < __ElementType > :: Iterator,
                            cds :: Collection < __ElementType >,
                            & __collectionContains < __ElementType >,
                            & __collectionNotContains < __ElementType >
                    >;


            /**
             * @typedef Alias used by MutableCollection to implement the Find Of Immutable Initializer List Client
             * @tparam __ElementType the type of the elements enclosed in the extending Collection
             * @namespace cds :: __hidden :: __impl
             * @internal library-private
             */
            template < typename __ElementType >                     /* NOLINT(bugprone-reserved-identifier) */
            using __MutableCollectionFindOfInitializerListClient =  /* NOLINT(bugprone-reserved-identifier) */
                    __FindOfMutableCompositeClient <
                            cds :: MutableCollection < __ElementType >,
                            __ElementType,
                            typename __MutableCollectionDelegateForwardIterableClient < __ElementType > :: Iterator,
                            std :: initializer_list < __ElementType >,
                            & __initializerListContains < __ElementType, & cds :: meta :: equals < __ElementType > >,
                            & __initializerListNotContains < __ElementType, & cds :: meta :: equals < __ElementType > >
                    >;


            /**
             * @typedef Alias used by MutableCollection to implement the Find by Immutable Predicate Client
             * @tparam __ElementType the type of the elements enclosed in the extending Collection
             * @namespace cds :: __hidden :: __impl
             * @internal library-private
             */
            template < typename __ElementType >     /* NOLINT(bugprone-reserved-identifier) */
            using __MutableCollectionFindByClient = /* NOLINT(bugprone-reserved-identifier) */
                    __FindByMutableCompositeClient <
                            cds :: MutableCollection < __ElementType >,
                            __ElementType,
                            typename __MutableCollectionDelegateForwardIterableClient < __ElementType > :: Iterator
                    >;


            /**
             * @typedef Alias used by MutableCollection to implement the Generic Mutable Statements Client
             * @tparam __ElementType the type of the elements enclosed in the extending Collection
             * @namespace cds :: __hidden :: __impl
             * @internal library-private
             */
            template < typename __ElementType >                 /* NOLINT(bugprone-reserved-identifier) */
            using __MutableCollectionGenericStatementsClient =  /* NOLINT(bugprone-reserved-identifier) */
                    __GenericMutableStatementsCompositeClient <
                            cds :: MutableCollection < __ElementType >,
                            __ElementType
                    >;

        }
    }
    
}

#endif /* __CDS_MUTABLE_COLLECTION_CONSTRUCTS_HPP__ */
