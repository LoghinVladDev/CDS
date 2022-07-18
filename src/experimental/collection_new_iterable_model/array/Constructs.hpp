//
// Created by loghin on 08/07/22.
//

#ifndef __CDS_ARRAY_CONSTRUCTS_HPP__
#define __CDS_ARRAY_CONSTRUCTS_HPP__

namespace cds {                 // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {    // NOLINT(modernize-concat-nested-namespaces)
        namespace __hidden {    // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier)
            namespace __impl {  // NOLINT(bugprone-reserved-identifier)

                template < typename __ElementType >         // NOLINT(bugprone-reserved-identifier)
                using __ArrayImplementation =               // NOLINT(bugprone-reserved-identifier)
                        __Array <
                                __ElementType,
                                & cds :: meta :: equals < __ElementType >
                        >;


                template < typename __ElementType >         // NOLINT(bugprone-reserved-identifier)
                using __ArrayServer =                       // NOLINT(bugprone-reserved-identifier)
                        __ListServer <
                                cds :: experimental :: Array < __ElementType >,
                                __ElementType
                        >;


                template < typename __ElementType >     // NOLINT(bugprone-reserved-identifier)
                using __ArrayRandomInsertionClient =    // NOLINT(bugprone-reserved-identifier)
                        __LocalRandomInsertionPrimitiveClient <
                                cds :: experimental :: Array < __ElementType >,
                                __ElementType,
                                __ElementType
                        >;


                template < typename __ElementType >     // NOLINT(bugprone-reserved-identifier)
                using __ArrayBoundaryInsertionClient =  // NOLINT(bugprone-reserved-identifier)
                        __LocalBoundaryInsertionPrimitiveClient <
                                cds :: experimental :: Array < __ElementType >,
                                __ElementType,
                                __ElementType
                        >;


                template < typename __ElementType >             // NOLINT(bugprone-reserved-identifier)
                using __ArrayIteratorRelativeInsertionClient =  // NOLINT(bugprone-reserved-identifier)
                        __LocalIteratorRelativeInsertionPrimitiveClient <
                                cds :: experimental :: Array < __ElementType >,
                                __ElementType,
                                AbstractAddressIterator < __ElementType >
                        >;


                template < typename __ElementType >                 // NOLINT(bugprone-reserved-identifier)
                using __ArrayConstIteratorRelativeInsertionClient = // NOLINT(bugprone-reserved-identifier)
                        __LocalConstIteratorRelativeInsertionPrimitiveClient <
                                cds :: experimental :: Array < __ElementType >,
                                __ElementType,
                                AbstractAddressIterator < __ElementType const >
                        >;


                template < typename __ElementType >     // NOLINT(bugprone-reserved-identifier)
                using __ArrayFindOfCollectionClient =   // NOLINT(bugprone-reserved-identifier)
                        __LocalFindOfMutableCompositeClient <
                                cds :: experimental :: Array < __ElementType >,
                                __ElementType,
                                AddressIterator < __ElementType >,
                                cds :: experimental :: Collection < __ElementType >,
                                & __collectionContains < __ElementType >
                        >;


                template < typename __ElementType >         // NOLINT(bugprone-reserved-identifier)
                using __ArrayFindOfInitializerListClient =  // NOLINT(bugprone-reserved-identifier)
                        __LocalFindOfMutableCompositeClient <
                                cds :: experimental :: Array < __ElementType >,
                                __ElementType,
                                AddressIterator < __ElementType >,
                                std :: initializer_list < __ElementType >,
                                & __initializerListContains < __ElementType, & cds :: meta :: equals < __ElementType > >
                        >;


                template < typename __ElementType >         // NOLINT(bugprone-reserved-identifier)
                using __ArrayFindConstOfCollectionClient =  // NOLINT(bugprone-reserved-identifier)
                        __LocalFindOfImmutableCompositeClient <
                                cds :: experimental :: Array < __ElementType >,
                                __ElementType,
                                AddressIterator < __ElementType const >,
                                cds :: experimental :: Collection < __ElementType >,
                                & __collectionContains < __ElementType >
                        >;


                template < typename __ElementType >             // NOLINT(bugprone-reserved-identifier)
                using __ArrayFindConstOfInitializerListClient = // NOLINT(bugprone-reserved-identifier)
                        __LocalFindOfImmutableCompositeClient <
                                cds :: experimental :: Array < __ElementType >,
                                __ElementType,
                                AddressIterator < __ElementType const >,
                                std :: initializer_list < __ElementType >,
                                & __initializerListContains < __ElementType, & cds :: meta :: equals < __ElementType > >
                        >;


                template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
                using __ArrayFindByClient =         // NOLINT(bugprone-reserved-identifier)
                        __LocalFindByMutableCompositeClient <
                                cds :: experimental :: Array < __ElementType >,
                                __ElementType,
                                AddressIterator < __ElementType >
                        >;


                template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
                using __ArrayFindConstByClient =    // NOLINT(bugprone-reserved-identifier)
                        __LocalFindByImmutableCompositeClient <
                                cds :: experimental :: Array < __ElementType >,
                                __ElementType,
                                AddressIterator < __ElementType const >
                        >;


                template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
                using __ArrayIteratorRemoveClient = // NOLINT(bugprone-reserved-identifier)
                        __LocalIteratorRemovePrimitiveClient <
                                cds :: experimental :: Array < __ElementType >,
                                __ElementType,
                                AbstractAddressIterator < __ElementType >
                        >;


                template < typename __ElementType >         // NOLINT(bugprone-reserved-identifier)
                using __ArrayConstIteratorRemoveClient =    // NOLINT(bugprone-reserved-identifier)
                        __LocalConstIteratorRemovePrimitiveClient <
                                cds :: experimental :: Array < __ElementType >,
                                __ElementType,
                                AbstractAddressIterator < __ElementType const >
                        >;


                template < typename __ElementType >     // NOLINT(bugprone-reserved-identifier)
                using __ArrayRemoveOfCollectionClient = // NOLINT(bugprone-reserved-identifier)
                        __LocalRemoveOfCompositeClient <
                                cds :: experimental :: Array < __ElementType >,
                                __ElementType,
                                cds :: experimental :: Collection < __ElementType >,
                                & __collectionContains < __ElementType >
                        >;


                template < typename __ElementType >             // NOLINT(bugprone-reserved-identifier)
                using __ArrayRemoveOfInitializerListClient =    // NOLINT(bugprone-reserved-identifier)
                        __LocalRemoveOfCompositeClient <
                                cds :: experimental :: Array < __ElementType >,
                                __ElementType,
                                std :: initializer_list < __ElementType >,
                                & __initializerListContains < __ElementType, & cds :: meta :: equals < __ElementType > >
                        >;


                template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
                using __ArrayRemoveByClient =       // NOLINT(bugprone-reserved-identifier)
                        __LocalRemoveByCompositeClient <
                                cds :: experimental :: Array < __ElementType >,
                                __ElementType
                        >;


                template < typename __ElementType >     // NOLINT(bugprone-reserved-identifier)
                using __ArrayGenericStatementsClient =  // NOLINT(bugprone-reserved-identifier)
                        __LocalGenericMutableStatementsCompositeClient <
                                cds :: experimental :: Array < __ElementType >,
                                __ElementType
                        >;


                template < typename __ElementType >         // NOLINT(bugprone-reserved-identifier)
                using __ArrayGenericConstStatementsClient = // NOLINT(bugprone-reserved-identifier)
                        __LocalGenericImmutableStatementsCompositeClient <
                                cds :: experimental :: Array < __ElementType >,
                                __ElementType
                        >;


                template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
                using __ArraySortClient =           // NOLINT(bugprone-reserved-identifier)
                        __LocalSortCompositeClient <
                                cds :: experimental :: Array < __ElementType >,
                                __ElementType
                        >;


                template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
                using __ArrayReplaceClient =           // NOLINT(bugprone-reserved-identifier)
                        __LocalReplaceCompositeClient <
                                cds :: experimental :: Array < __ElementType >,
                                __ElementType
                        >;


                template < typename __ElementType >         // NOLINT(bugprone-reserved-identifier)
                using __ArrayReplaceOfCollectionClient =    // NOLINT(bugprone-reserved-identifier)
                        __LocalReplaceOfCompositeClient <
                                cds :: experimental :: Array < __ElementType >,
                                __ElementType,
                                cds :: experimental :: Collection < __ElementType >,
                                & __collectionContains < __ElementType >
                        >;


                template < typename __ElementType >         // NOLINT(bugprone-reserved-identifier)
                using __ArrayReplaceOfInitializerListClient =    // NOLINT(bugprone-reserved-identifier)
                        __LocalReplaceOfCompositeClient <
                                cds :: experimental :: Array < __ElementType >,
                                __ElementType,
                                std :: initializer_list < __ElementType >,
                                & __initializerListContains < __ElementType, & cds :: meta :: equals < __ElementType > >
                        >;


                template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
                using __ArrayReplaceByClient =      // NOLINT(bugprone-reserved-identifier)
                        __LocalReplaceByCompositeClient <
                                cds :: experimental :: Array < __ElementType >,
                                __ElementType
                        >;


                template < typename __ElementType >     // NOLINT(bugprone-reserved-identifier)
                using __ArrayIndexedOperationsClient =  // NOLINT(bugprone-reserved-identifier)
                        __LocalIndexedOperationsPrimitiveClient <
                                cds :: experimental :: Array < __ElementType >,
                                __ElementType
                        >;


                template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
                using __ArrayIndicesClient =        // NOLINT(bugprone-reserved-identifier)
                        __LocalIndicesCompositeClient <
                                cds :: experimental :: Array < __ElementType >,
                                __ElementType
                        >;


                template < typename __ElementType >         // NOLINT(bugprone-reserved-identifier)
                using __ArrayIndicesOfCollectionClient =    // NOLINT(bugprone-reserved-identifier)
                        __LocalIndicesOfCompositeClient <
                                cds :: experimental :: Array < __ElementType >,
                                __ElementType,
                                cds :: experimental :: Collection < __ElementType >,
                                & __collectionContains < __ElementType >
                        >;


                template < typename __ElementType >             // NOLINT(bugprone-reserved-identifier)
                using __ArrayIndicesOfInitializerListClient =   // NOLINT(bugprone-reserved-identifier)
                        __LocalIndicesOfCompositeClient <
                                cds :: experimental :: Array < __ElementType >,
                                __ElementType,
                                std :: initializer_list < __ElementType >,
                                & __initializerListContains < __ElementType, & cds :: meta :: equals < __ElementType > >
                        >;


                template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
                using __ArrayIndicesByClient =      // NOLINT(bugprone-reserved-identifier)
                        __LocalIndicesByCompositeClient <
                                cds :: experimental :: Array < __ElementType >,
                                __ElementType
                        >;


                template < typename __ElementType >     // NOLINT(bugprone-reserved-identifier)
                using __ArrayDelegateIterableServer =   // NOLINT(bugprone-reserved-identifier)
                        __DelegateIterableServer <
                                cds :: experimental :: Array < __ElementType >,
                                __ElementType,
                                true,
                                true,
                                AddressIterator < __ElementType, false >,
                                AddressIterator < __ElementType const, false >,
                                AddressIterator < __ElementType, true >,
                                AddressIterator < __ElementType const, true >
                        >;

            }
        }
    }
}

#endif // __CDS_ARRAY_CONSTRUCTS_HPP__
