//
// Created by loghin on 6/26/22.
//

#ifndef __CDS_COLLECTION_CONSTRUCTS_HPP__
#define __CDS_COLLECTION_CONSTRUCTS_HPP__

namespace cds {                 // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {    // NOLINT(modernize-concat-nested-namespaces)

        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        class Collection;

        namespace __hidden {    // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier)
            namespace __impl {  // NOLINT(bugprone-reserved-identifier)

                template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
                inline auto __collectionContains (  // NOLINT(bugprone-reserved-identifier)
                            cds :: experimental :: Collection < __ElementType > const & collection,
                            __ElementType                                       const & element
                ) noexcept -> bool;


                template <
                        typename __ElementType,                                     // NOLINT(bugprone-reserved-identifier)
                        utility :: ComparisonFunction < __ElementType > __function  // NOLINT(bugprone-reserved-identifier)
                > inline auto __initializerListContains (                           // NOLINT(bugprone-reserved-identifier)
                            std :: initializer_list < __ElementType >   const & list,
                            __ElementType                               const & element
                ) noexcept -> bool;


                template < typename __ElementType >         // NOLINT(bugprone-reserved-identifier)
                using __CollectionCommunicationChannel =    // NOLINT(bugprone-reserved-identifier)
                        __CollectionInternalCommunicationChannel <
                                cds :: experimental :: Collection < __ElementType >,
                                __ElementType
                        >;


                template < typename __ElementType >                     // NOLINT(bugprone-reserved-identifier)
                using __CollectionDelegateForwardConstIterableClient =  // NOLINT(bugprone-reserved-identifier)
                        __DelegateForwardConstIterablePrimitiveClient <
                                cds :: experimental :: Collection < __ElementType >,
                                __ElementType,
                                false
                        >;


                template < typename __ElementType >             // NOLINT(bugprone-reserved-identifier)
                using __CollectionConstIteratorRemoveClient =   // NOLINT(bugprone-reserved-identifier)
                        __AbstractConstIteratorRemovePrimitiveClient <
                                cds :: experimental :: Collection < __ElementType >,
                                __ElementType
                        >;


                template < typename __ElementType >         // NOLINT(bugprone-reserved-identifier)
                using __CollectionRandomInsertionClient =   // NOLINT(bugprone-reserved-identifier)
                        __RandomInsertionPrimitiveClient <
                                cds :: experimental :: Collection < __ElementType >,
                                __ElementType,
                                __ElementType const
                        >;


                template < typename __ElementType >             // NOLINT(bugprone-reserved-identifier)
                using __CollectionContainsOfCollectionClient =  // NOLINT(bugprone-reserved-identifier)
                        __ContainsOfCompositeClient <
                                cds :: experimental :: Collection < __ElementType >,
                                __ElementType,
                                cds :: experimental :: Collection < __ElementType >
                        >;


                template < typename __ElementType >                 // NOLINT(bugprone-reserved-identifier)
                using __CollectionContainsOfInitializerListClient = // NOLINT(bugprone-reserved-identifier)
                        __ContainsOfCompositeClient <
                                cds :: experimental :: Collection < __ElementType >,
                                __ElementType,
                                std :: initializer_list < __ElementType >
                        >;


                template < typename __ElementType >         // NOLINT(bugprone-reserved-identifier)
                using __CollectionFindOfCollectionClient =  // NOLINT(bugprone-reserved-identifier)
                        __FindOfImmutableCompositeClient <
                                cds :: experimental :: Collection < __ElementType >,
                                __ElementType,
                                typename __CollectionDelegateForwardConstIterableClient < __ElementType > :: ConstIterator,
                                cds :: experimental :: Collection < __ElementType >,
                                & __collectionContains < __ElementType >
                        >;


                template < typename __ElementType >             // NOLINT(bugprone-reserved-identifier)
                using __CollectionFindOfInitializerListClient = // NOLINT(bugprone-reserved-identifier)
                        __FindOfImmutableCompositeClient <
                                cds :: experimental :: Collection < __ElementType >,
                                __ElementType,
                                typename __CollectionDelegateForwardConstIterableClient < __ElementType > :: ConstIterator,
                                std :: initializer_list < __ElementType >,
                                & __initializerListContains < __ElementType, & cds :: meta :: equals < __ElementType > >
                        >;


                template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
                using __CollectionFindByClient =    // NOLINT(bugprone-reserved-identifier)
                        __FindByImmutableCompositeClient <
                                cds :: experimental :: Collection < __ElementType >,
                                __ElementType,
                                typename __CollectionDelegateForwardConstIterableClient < __ElementType > :: ConstIterator
                        >;


                template < typename __ElementType >             // NOLINT(bugprone-reserved-identifier)
                using __CollectionRemoveOfCollectionClient =    // NOLINT(bugprone-reserved-identifier)
                        __RemoveOfCompositeClient <
                                cds :: experimental :: Collection < __ElementType >,
                                __ElementType,
                                cds :: experimental :: Collection < __ElementType >,
                                & __collectionContains < __ElementType >
                        >;


                template < typename __ElementType >                 // NOLINT(bugprone-reserved-identifier)
                using __CollectionRemoveOfInitializerListClient =   // NOLINT(bugprone-reserved-identifier)
                        __RemoveOfCompositeClient <
                                cds :: experimental :: Collection < __ElementType >,
                                __ElementType,
                                std :: initializer_list < __ElementType >,
                                & __initializerListContains < __ElementType, & cds :: meta :: equals < __ElementType > >
                        >;


                template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
                using __CollectionRemoveByClient =  // NOLINT(bugprone-reserved-identifier)
                        __RemoveByCompositeClient <
                                cds :: experimental :: Collection < __ElementType >,
                                __ElementType
                        >;


                template < typename __ElementType >         // NOLINT(bugprone-reserved-identifier)
                using __CollectionGenericStatementsClient = // NOLINT(bugprone-reserved-identifier)
                        __GenericImmutableStatementsCompositeClient <
                                cds :: experimental :: Collection < __ElementType >,
                                __ElementType
                        >;

            }
        }
    }
}

#endif // __CDS_COLLECTION_CONSTRUCTS_HPP__
