/* NOLINT(llvm-header-guard)
 * Created by loghin on 08/07/22.
 */

#ifndef __CDS_LIST_CONSTRUCTS_HPP__ /* NOLINT(llvm-header-guard) */
#define __CDS_LIST_CONSTRUCTS_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

namespace cds { /* NOLINT(modernize-concat-nested-namespaces) */

    /**
     * @brief Pre-declaration of the List class
     * @namespace cds
     */
    template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    class List;

    namespace __hidden {    /* NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        namespace __impl {  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            /**
             * @typedef Alias used by List to implement the Delegate Forward Iterable Client
             * @tparam __ElementType the type of the elements enclosed in the extending Collection
             * @namespace cds :: __hidden :: __impl
             * @internal library-private
             */
            template < typename __ElementType >         /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            using __ListDelegateForwardIterableClient = /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
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
            template < typename __ElementType >             /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            using __ListDelegateBackwardIterableClient =    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
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
            template < typename __ElementType >                 /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            using __ListDelegateForwardConstIterableClient =    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
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
            template < typename __ElementType >                 /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            using __ListDelegateBackwardConstIterableClient =   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
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
            template < typename __ElementType >     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            using __ListBoundaryInsertionClient =   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
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
            template < typename __ElementType >             /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            using __ListIteratorRelativeInsertionClient =   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
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
            template < typename __ElementType >                 /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            using __ListConstIteratorRelativeInsertionClient =  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
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
            template < typename __ElementType >     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            using __ListIndexedOperationsClient =   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
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
            template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            using __ListReplaceClient =         /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __ReplaceCompositeClient <
                            cds :: List < __ElementType >,
                            __ElementType
                    >;


            /**
             * @typedef Alias used by List to implement the Replace of Iterable Client
             * @tparam __ElementType the type of the elements enclosed in the extending Collection
             * @namespace cds :: __hidden :: __impl
             * @internal library-private
             */
            template < typename __ElementType >     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            using __ListReplaceOfIterableClient =   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __ReplaceOfCompositeClient <
                            cds :: List < __ElementType >,
                            __ElementType,
                            cds :: Iterable < __ElementType >,
                            & __iterableContains < __ElementType >
                    >;


            /**
             * @typedef Alias used by List to implement the Replace of Initializer List Client
             * @tparam __ElementType the type of the elements enclosed in the extending Collection
             * @namespace cds :: __hidden :: __impl
             * @internal library-private
             */
            template < typename __ElementType >             /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            using __ListReplaceOfInitializerListClient =    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
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
            template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            using __ListReplaceByClient =       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
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
            template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            using __ListIndicesClient =         /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __IndicesCompositeClient <
                            cds :: List < __ElementType >,
                            __ElementType
                    >;


            /**
             * @typedef Alias used by List to implement the Indices of Iterable Client
             * @tparam __ElementType the type of the elements enclosed in the extending Collection
             * @namespace cds :: __hidden :: __impl
             * @internal library-private
             */
            template < typename __ElementType >     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            using __ListIndicesOfIterableClient =   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __IndicesOfCompositeClient <
                            cds :: List < __ElementType >,
                            __ElementType,
                            cds :: Iterable < __ElementType >,
                            & __iterableContains < __ElementType >
                    >;


            /**
             * @typedef Alias used by List to implement the Indices of Initializer List Client
             * @tparam __ElementType the type of the elements enclosed in the extending Collection
             * @namespace cds :: __hidden :: __impl
             * @internal library-private
             */
            template < typename __ElementType >             /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            using __ListIndicesOfInitializerListClient =    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
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
            template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            using __ListIndicesByClient =       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __IndicesByCompositeClient <
                            cds :: List < __ElementType >,
                            __ElementType
                    >;

        } /* namespace __impl */
    } /* namespace __hidden */
} /* namespace cds */

#endif /* __CDS_LIST_CONSTRUCTS_HPP__ */
