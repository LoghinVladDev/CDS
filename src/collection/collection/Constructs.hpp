/*
 * Created by loghin on 6/26/22.
 */

#ifndef __CDS_COLLECTION_CONSTRUCTS_HPP__
#define __CDS_COLLECTION_CONSTRUCTS_HPP__ /* NOLINT(bugprone-reserved-identifier) */

namespace cds {                 /* NOLINT(modernize-concat-nested-namespaces) */

    /**
     * @brief Pre-declaration of the Collection class
     * @namespace cds
     */
    template < typename > /* NOLINT(bugprone-reserved-identifier) */
    class Collection;

    namespace __hidden {    /* NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier) */
        namespace __impl {  /* NOLINT(bugprone-reserved-identifier) */

            /**
             * @brief Function passed to client to check if a given collection element contains a received value element
             * @tparam __ElementType the type of the value given and of the values enclosed in the collection
             * @param [in] collection : Collection cref = Constant Reference to a collection containing elements of required type
             * @param [in] element : __ElementType cref = Constant Reference to a value of the required type to be found in the given collection
             * @exceptsafe
             * @return bool = true if collection contains given element, false otherwise
             * @test Not Applicable
             * @namespace cds :: __hidden :: __impl
             * @internal library-private
             */
            template < typename __ElementType >             /* NOLINT(bugprone-reserved-identifier) */
            __CDS_OptimalInline auto __collectionContains ( /* NOLINT(bugprone-reserved-identifier) */
                        cds :: Collection < __ElementType > const & collection,
                        __ElementType                       const & element
            ) noexcept -> bool;

            /**
             * @brief Function passed to client to check if a given collection element does not contain a received value element
             * @tparam __ElementType the type of the value given and of the values enclosed in the collection
             * @param [in] collection : Collection cref = Constant Reference to a collection containing elements of required type
             * @param [in] element : __ElementType cref = Constant Reference to a value of the required type to be found in the given collection
             * @exceptsafe
             * @return bool = true if collection does not contain the given element, false otherwise
             * @test Not Applicable
             * @namespace cds :: __hidden :: __impl
             * @internal library-private
             */
            template < typename __ElementType >                 /* NOLINT(bugprone-reserved-identifier) */
            __CDS_OptimalInline auto __collectionNotContains (  /* NOLINT(bugprone-reserved-identifier) */
                        cds :: Collection < __ElementType > const & collection,
                        __ElementType                       const & element
            ) noexcept -> bool;


            /**
             * @brief Function passed to client to check if a given std :: initializer_list element contains a received value element
             * @tparam __ElementType the type of the value given and of the values enclosed in the initializer list
             * @tparam __function the function used to compare equality, since std :: initializer_list does not have .contains, and must be iterated and its elements compared to detect inclusion
             * @param [in] list : std :: initializer_list cref = Constant Reference to an initializer list containing elements of required type
             * @param [in] element : __ElementType cref = Constant Reference to a value of the required type to be found in the given initializer list
             * @exceptsafe
             * @return bool = true if initializer list contains given element, false otherwise
             * @test Not Applicable
             * @namespace cds :: __hidden :: __impl
             * @internal library-private
             */
            template <
                    typename __ElementType,                                     /* NOLINT(bugprone-reserved-identifier) */
                    utility :: ComparisonFunction < __ElementType > __function  /* NOLINT(bugprone-reserved-identifier) */
            > __CDS_OptimalInline auto __initializerListContains (              /* NOLINT(bugprone-reserved-identifier) */
                        std :: initializer_list < __ElementType >   const & list,
                        __ElementType                               const & element
            ) noexcept -> bool;


            /**
             * @brief Function passed to client to check if a given std :: initializer_list element does not contain a received value element
             * @tparam __ElementType the type of the value given and of the values enclosed in the initializer list
             * @tparam __function the function used to compare equality, since std :: initializer_list does not have .contains, and must be iterated and its elements compared to detect inclusion
             * @param [in] list : std :: initializer_list cref = Constant Reference to an initializer list containing elements of required type
             * @param [in] element : __ElementType cref = Constant Reference to a value of the required type to be found in the given initializer list
             * @exceptsafe
             * @return bool = true if initializer list does not contain given element, false otherwise
             * @test Not Applicable
             * @namespace cds :: __hidden :: __impl
             * @internal library-private
             */
            template <
                    typename __ElementType,                                     /* NOLINT(bugprone-reserved-identifier) */
                    utility :: ComparisonFunction < __ElementType > __function  /* NOLINT(bugprone-reserved-identifier) */
            > __CDS_OptimalInline auto __initializerListNotContains (           /* NOLINT(bugprone-reserved-identifier) */
                        std :: initializer_list < __ElementType >   const & list,
                        __ElementType                               const & element
            ) noexcept -> bool;


            /**
             * @typedef Alias used by Collection to extend the Communication Channel object
             * @tparam __ElementType the type of the elements enclosed in the extending Collection
             * @namespace cds :: __hidden :: __impl
             * @internal library-private
             */
            template < typename __ElementType >         /* NOLINT(bugprone-reserved-identifier) */
            using __CollectionCommunicationChannel =    /* NOLINT(bugprone-reserved-identifier) */
                    __CollectionInternalCommunicationChannel <
                            cds :: Collection < __ElementType >,
                            __ElementType
                    >;


            /**
             * @typedef Alias used by Collection to implement the Delegate Forward Const Iterable Client
             * @tparam __ElementType the type of the elements enclosed in the extending Collection
             * @namespace cds :: __hidden :: __impl
             * @internal library-private
             */
            template < typename __ElementType >                     /* NOLINT(bugprone-reserved-identifier) */
            using __CollectionDelegateForwardConstIterableClient =  /* NOLINT(bugprone-reserved-identifier) */
                    __DelegateForwardConstIterablePrimitiveClient <
                            cds :: Collection < __ElementType >,
                            __ElementType,
                            false
                    >;


            /**
             * @typedef Alias used by Collection to implement the Const Iterator Remove Client
             * @tparam __ElementType the type of the elements enclosed in the extending Collection
             * @namespace cds :: __hidden :: __impl
             * @internal library-private
             */
            template < typename __ElementType >             /* NOLINT(bugprone-reserved-identifier) */
            using __CollectionConstIteratorRemoveClient =   /* NOLINT(bugprone-reserved-identifier) */
                    __AbstractConstIteratorRemovePrimitiveClient <
                            cds :: Collection < __ElementType >,
                            __ElementType
                    >;


            /**
             * @typedef Alias used by Collection to implement the Random Insertion Client
             * @tparam __ElementType the type of the elements enclosed in the extending Collection
             * @namespace cds :: __hidden :: __impl
             * @internal library-private
             */
            template < typename __ElementType >         /* NOLINT(bugprone-reserved-identifier) */
            using __CollectionRandomInsertionClient =   /* NOLINT(bugprone-reserved-identifier) */
                    __RandomInsertionPrimitiveClient <
                            cds :: Collection < __ElementType >,
                            __ElementType,
                            __ElementType const
                    >;


            /**
             * @typedef Alias used by Collection to implement the Contains Of Collection Client
             * @tparam __ElementType the type of the elements enclosed in the extending Collection
             * @namespace cds :: __hidden :: __impl
             * @internal library-private
             */
            template < typename __ElementType >             /* NOLINT(bugprone-reserved-identifier) */
            using __CollectionContainsOfCollectionClient =  /* NOLINT(bugprone-reserved-identifier) */
                    __ContainsOfCompositeClient <
                            cds :: Collection < __ElementType >,
                            __ElementType,
                            cds :: Collection < __ElementType >,
                            __collectionContains < __ElementType >
                    >;


            /**
             * @typedef Alias used by Collection to implement the Contains of Initializer List Client
             * @tparam __ElementType the type of the elements enclosed in the extending Collection
             * @namespace cds :: __hidden :: __impl
             * @internal library-private
             */
            template < typename __ElementType >                 /* NOLINT(bugprone-reserved-identifier) */
            using __CollectionContainsOfInitializerListClient = /* NOLINT(bugprone-reserved-identifier) */
                    __ContainsOfCompositeClient <
                            cds :: Collection < __ElementType >,
                            __ElementType,
                            std :: initializer_list < __ElementType >,
                            __initializerListContains < __ElementType, & cds :: meta :: equals < __ElementType > >
                    >;


            /**
             * @typedef Alias used by Collection to implement the Find Of Immutable Collection Client
             * @tparam __ElementType the type of the elements enclosed in the extending Collection
             * @namespace cds :: __hidden :: __impl
             * @internal library-private
             */
            template < typename __ElementType >         /* NOLINT(bugprone-reserved-identifier) */
            using __CollectionFindOfCollectionClient =  /* NOLINT(bugprone-reserved-identifier) */
                    __FindOfImmutableCompositeClient <
                            cds :: Collection < __ElementType >,
                            __ElementType,
                            typename __CollectionDelegateForwardConstIterableClient < __ElementType > :: ConstIterator,
                            cds :: Collection < __ElementType >,
                            & __collectionContains < __ElementType >,
                            & __collectionNotContains < __ElementType >
                    >;


            /**
             * @typedef Alias used by Collection to implement the Find Of Immutable Initializer List Client
             * @tparam __ElementType the type of the elements enclosed in the extending Collection
             * @namespace cds :: __hidden :: __impl
             * @internal library-private
             */
            template < typename __ElementType >             /* NOLINT(bugprone-reserved-identifier) */
            using __CollectionFindOfInitializerListClient = /* NOLINT(bugprone-reserved-identifier) */
                    __FindOfImmutableCompositeClient <
                            cds :: Collection < __ElementType >,
                            __ElementType,
                            typename __CollectionDelegateForwardConstIterableClient < __ElementType > :: ConstIterator,
                            std :: initializer_list < __ElementType >,
                            & __initializerListContains < __ElementType, & cds :: meta :: equals < __ElementType > >,
                            & __initializerListNotContains < __ElementType, & cds :: meta :: equals < __ElementType > >
                    >;


            /**
             * @typedef Alias used by Collection to implement the Find by Immutable Predicate Client
             * @tparam __ElementType the type of the elements enclosed in the extending Collection
             * @namespace cds :: __hidden :: __impl
             * @internal library-private
             */
            template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
            using __CollectionFindByClient =    /* NOLINT(bugprone-reserved-identifier) */
                    __FindByImmutableCompositeClient <
                            cds :: Collection < __ElementType >,
                            __ElementType,
                            typename __CollectionDelegateForwardConstIterableClient < __ElementType > :: ConstIterator
                    >;


            /**
             * @typedef Alias used by Collection to implement the Remove of Collection Client
             * @tparam __ElementType the type of the elements enclosed in the extending Collection
             * @namespace cds :: __hidden :: __impl
             * @internal library-private
             */
            template < typename __ElementType >             /* NOLINT(bugprone-reserved-identifier) */
            using __CollectionRemoveOfCollectionClient =    /* NOLINT(bugprone-reserved-identifier) */
                    __RemoveOfCompositeClient <
                            cds :: Collection < __ElementType >,
                            __ElementType,
                            cds :: Collection < __ElementType >,
                            & __collectionContains < __ElementType >
                    >;


            /**
             * @typedef Alias used by Collection to implement the Remove of Initializer List Client
             * @tparam __ElementType the type of the elements enclosed in the extending Collection
             * @namespace cds :: __hidden :: __impl
             * @internal library-private
             */
            template < typename __ElementType >                 /* NOLINT(bugprone-reserved-identifier) */
            using __CollectionRemoveOfInitializerListClient =   /* NOLINT(bugprone-reserved-identifier) */
                    __RemoveOfCompositeClient <
                            cds :: Collection < __ElementType >,
                            __ElementType,
                            std :: initializer_list < __ElementType >,
                            & __initializerListContains < __ElementType, & cds :: meta :: equals < __ElementType > >
                    >;


            /**
             * @typedef Alias used by Collection to implement the Remove by Predicate Client
             * @tparam __ElementType the type of the elements enclosed in the extending Collection
             * @namespace cds :: __hidden :: __impl
             * @internal library-private
             */
            template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
            using __CollectionRemoveByClient =  /* NOLINT(bugprone-reserved-identifier) */
                    __RemoveByCompositeClient <
                            cds :: Collection < __ElementType >,
                            __ElementType
                    >;


            /**
             * @typedef Alias used by Collection to implement the Generic Immutable Statements Client
             * @tparam __ElementType the type of the elements enclosed in the extending Collection
             * @namespace cds :: __hidden :: __impl
             * @internal library-private
             */
            template < typename __ElementType >         /* NOLINT(bugprone-reserved-identifier) */
            using __CollectionGenericStatementsClient = /* NOLINT(bugprone-reserved-identifier) */
                    __GenericImmutableStatementsCompositeClient <
                            cds :: Collection < __ElementType >,
                            __ElementType
                    >;

        }
    }
}

#endif /* __CDS_COLLECTION_CONSTRUCTS_HPP__ */
