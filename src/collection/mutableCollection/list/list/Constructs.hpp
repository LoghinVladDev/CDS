/*
 * Created by loghin on 08/07/22.
 */

#ifndef __CDS_LIST_CONSTRUCTS_HPP__
#define __CDS_LIST_CONSTRUCTS_HPP__ /* NOLINT(bugprone-reserved-identifier) */

namespace cds { /* NOLINT(modernize-concat-nested-namespaces) */

    /**
     * @brief Pre-declaration of the List class
     * @namespace cds
     */
    template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
    class List;

    namespace __hidden {    /* NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier) */
        namespace __impl {  /* NOLINT(bugprone-reserved-identifier) */

            /**
             * @typedef Alias used by List to implement the Delegate Forward Iterable Client
             * @tparam __ElementType the type of the elements enclosed in the extending Collection
             * @namespace cds :: __hidden :: __impl
             * @internal library-private
             */
            template < typename __ElementType >         /* NOLINT(bugprone-reserved-identifier) */
            using __ListDelegateForwardIterableClient = /* NOLINT(bugprone-reserved-identifier) */
                    __DelegateForwardIterablePrimitiveClient <
                            cds :: List < __ElementType >,
                            __ElementType,
                            true
                    >;


            /**
             * @typedef Alias used by List to implement the Delegate Backward Iterable Client
             * @tparam __ElementType the type of the elements enclosed in the extending Collection
             * @namespace cds :: __hidden :: __impl
             * @internal library-private
             */
            template < typename __ElementType >             /* NOLINT(bugprone-reserved-identifier) */
            using __ListDelegateBackwardIterableClient =    /* NOLINT(bugprone-reserved-identifier) */
                    __DelegateBackwardIterablePrimitiveClient <
                            cds :: List < __ElementType >,
                            __ElementType,
                            true
                    >;


            /**
             * @typedef Alias used by List to implement the Delegate Forward Const Iterable Client
             * @tparam __ElementType the type of the elements enclosed in the extending Collection
             * @namespace cds :: __hidden :: __impl
             * @internal library-private
             */
            template < typename __ElementType >                 /* NOLINT(bugprone-reserved-identifier) */
            using __ListDelegateForwardConstIterableClient =    /* NOLINT(bugprone-reserved-identifier) */
                    __DelegateForwardConstIterablePrimitiveClient <
                            cds :: List < __ElementType >,
                            __ElementType,
                            true
                    >;


            /**
             * @typedef Alias used by List to implement the Delegate Backward Const Iterable Client
             * @tparam __ElementType the type of the elements enclosed in the extending Collection
             * @namespace cds :: __hidden :: __impl
             * @internal library-private
             */
            template < typename __ElementType >                 /* NOLINT(bugprone-reserved-identifier) */
            using __ListDelegateBackwardConstIterableClient =   /* NOLINT(bugprone-reserved-identifier) */
                    __DelegateBackwardConstIterablePrimitiveClient <
                            cds :: List < __ElementType >,
                            __ElementType,
                            true
                    >;


            /**
             * @typedef Alias used by List to implement the Boundary Insertion Client
             * @tparam __ElementType the type of the elements enclosed in the extending Collection
             * @namespace cds :: __hidden :: __impl
             * @internal library-private
             */
            template < typename __ElementType >     /* NOLINT(bugprone-reserved-identifier) */
            using __ListBoundaryInsertionClient =   /* NOLINT(bugprone-reserved-identifier) */
                    __BoundaryInsertionPrimitiveClient <
                            cds :: List < __ElementType >,
                            __ElementType,
                            __ElementType
                    >;


            /**
             * @typedef Alias used by List to implement the Iterator-Relative Insertion Client
             * @tparam __ElementType the type of the elements enclosed in the extending Collection
             * @namespace cds :: __hidden :: __impl
             * @internal library-private
             */
            template < typename __ElementType >             /* NOLINT(bugprone-reserved-identifier) */
            using __ListIteratorRelativeInsertionClient =   /* NOLINT(bugprone-reserved-identifier) */
                    __AbstractIteratorRelativeInsertionPrimitiveClient <
                            cds :: List < __ElementType >,
                            __ElementType
                    >;


            /**
             * @typedef Alias used by List to implement the Const-Iterator-Relative Insertion Client
             * @tparam __ElementType the type of the elements enclosed in the extending Collection
             * @namespace cds :: __hidden :: __impl
             * @internal library-private
             */
            template < typename __ElementType >                 /* NOLINT(bugprone-reserved-identifier) */
            using __ListConstIteratorRelativeInsertionClient =  /* NOLINT(bugprone-reserved-identifier) */
                    __AbstractConstIteratorRelativeInsertionPrimitiveClient <
                            cds :: List < __ElementType >,
                            __ElementType
                    >;


            /**
             * @typedef Alias used by List to implement the Indexed Operations Client
             * @tparam __ElementType the type of the elements enclosed in the extending Collection
             * @namespace cds :: __hidden :: __impl
             * @internal library-private
             */
            template < typename __ElementType >     /* NOLINT(bugprone-reserved-identifier) */
            using __ListIndexedOperationsClient =   /* NOLINT(bugprone-reserved-identifier) */
                    __IndexedOperationsPrimitiveClient <
                            cds :: List < __ElementType >,
                            __ElementType
                    >;


            /**
             * @typedef Alias used by List to implement the Replace Client
             * @tparam __ElementType the type of the elements enclosed in the extending Collection
             * @namespace cds :: __hidden :: __impl
             * @internal library-private
             */
            template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
            using __ListReplaceClient =         /* NOLINT(bugprone-reserved-identifier) */
                    __ReplaceCompositeClient <
                            cds :: List < __ElementType >,
                            __ElementType
                    >;


            /**
             * @typedef Alias used by List to implement the Replace of Collection Client
             * @tparam __ElementType the type of the elements enclosed in the extending Collection
             * @namespace cds :: __hidden :: __impl
             * @internal library-private
             */
            template < typename __ElementType >     /* NOLINT(bugprone-reserved-identifier) */
            using __ListReplaceOfCollectionClient = /* NOLINT(bugprone-reserved-identifier) */
                    __ReplaceOfCompositeClient <
                            cds :: List < __ElementType >,
                            __ElementType,
                            cds :: Collection < __ElementType >,
                            & __collectionContains < __ElementType >
                    >;


            /**
             * @typedef Alias used by List to implement the Replace of Initializer List Client
             * @tparam __ElementType the type of the elements enclosed in the extending Collection
             * @namespace cds :: __hidden :: __impl
             * @internal library-private
             */
            template < typename __ElementType >             /* NOLINT(bugprone-reserved-identifier) */
            using __ListReplaceOfInitializerListClient =    /* NOLINT(bugprone-reserved-identifier) */
                    __ReplaceOfCompositeClient <
                            cds :: List < __ElementType >,
                            __ElementType,
                            std :: initializer_list < __ElementType >,
                            & __initializerListContains < __ElementType, & cds :: meta :: equals < __ElementType > >
                    >;


            /**
             * @typedef Alias used by List to implement the Replace by Client
             * @tparam __ElementType the type of the elements enclosed in the extending Collection
             * @namespace cds :: __hidden :: __impl
             * @internal library-private
             */
            template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
            using __ListReplaceByClient =       /* NOLINT(bugprone-reserved-identifier) */
                    __ReplaceByCompositeClient <
                            cds :: List < __ElementType >,
                            __ElementType
                    >;


            /**
             * @typedef Alias used by List to implement the Indices Client
             * @tparam __ElementType the type of the elements enclosed in the extending Collection
             * @namespace cds :: __hidden :: __impl
             * @internal library-private
             */
            template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
            using __ListIndicesClient =         /* NOLINT(bugprone-reserved-identifier) */
                    __IndicesCompositeClient <
                            cds :: List < __ElementType >,
                            __ElementType
                    >;


            /**
             * @typedef Alias used by List to implement the Indices of Collection Client
             * @tparam __ElementType the type of the elements enclosed in the extending Collection
             * @namespace cds :: __hidden :: __impl
             * @internal library-private
             */
            template < typename __ElementType >     /* NOLINT(bugprone-reserved-identifier) */
            using __ListIndicesOfCollectionClient = /* NOLINT(bugprone-reserved-identifier) */
                    __IndicesOfCompositeClient <
                            cds :: List < __ElementType >,
                            __ElementType,
                            cds :: Collection < __ElementType >,
                            & __collectionContains < __ElementType >
                    >;


            /**
             * @typedef Alias used by List to implement the Indices of Initializer List Client
             * @tparam __ElementType the type of the elements enclosed in the extending Collection
             * @namespace cds :: __hidden :: __impl
             * @internal library-private
             */
            template < typename __ElementType >             /* NOLINT(bugprone-reserved-identifier) */
            using __ListIndicesOfInitializerListClient =    /* NOLINT(bugprone-reserved-identifier) */
                    __IndicesOfCompositeClient <
                            cds :: List < __ElementType >,
                            __ElementType,
                            std :: initializer_list < __ElementType >,
                            & __initializerListContains < __ElementType, & cds :: meta :: equals < __ElementType > >
                    >;


            /**
             * @typedef Alias used by List to implement the Indices by Client
             * @tparam __ElementType the type of the elements enclosed in the extending Collection
             * @namespace cds :: __hidden :: __impl
             * @internal library-private
             */
            template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
            using __ListIndicesByClient =       /* NOLINT(bugprone-reserved-identifier) */
                    __IndicesByCompositeClient <
                            cds :: List < __ElementType >,
                            __ElementType
                    >;

        }
    }
}

#endif /* __CDS_LIST_CONSTRUCTS_HPP__ */
