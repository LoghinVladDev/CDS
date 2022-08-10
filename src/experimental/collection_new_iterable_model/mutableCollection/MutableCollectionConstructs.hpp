//
// Created by loghin on 08/07/22.
//

#ifndef __CDS_MUTABLE_COLLECTION_CONSTRUCTS_HPP__
#define __CDS_MUTABLE_COLLECTION_CONSTRUCTS_HPP__

namespace cds {                 // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {    // NOLINT(modernize-concat-nested-namespaces)

        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        class MutableCollection;

        namespace __hidden {    // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier)
            namespace __impl {  // NOLINT(bugprone-reserved-identifier)

                template < typename __ElementType >                         // NOLINT(bugprone-reserved-identifier)
                using __MutableCollectionDelegateForwardIterableClient =    // NOLINT(bugprone-reserved-identifier)
                        __DelegateForwardIterablePrimitiveClient <
                                cds :: experimental :: MutableCollection < __ElementType >,
                                __ElementType,
                                false
                        >;


                template < typename __ElementType >             // NOLINT(bugprone-reserved-identifier)
                using __MutableCollectionIteratorRemoveClient = // NOLINT(bugprone-reserved-identifier)
                        __AbstractIteratorRemovePrimitiveClient <
                                cds :: experimental :: MutableCollection < __ElementType >,
                                __ElementType
                        >;


                template < typename __ElementType >                 // NOLINT(bugprone-reserved-identifier)
                using __MutableCollectionRandomInsertionClient =    // NOLINT(bugprone-reserved-identifier)
                        __RandomInsertionPrimitiveClient <
                                cds :: experimental :: MutableCollection < __ElementType >,
                                __ElementType,
                                __ElementType
                        >;


                template < typename __ElementType >                 // NOLINT(bugprone-reserved-identifier)
                using __MutableCollectionFindOfCollectionClient =   // NOLINT(bugprone-reserved-identifier)
                        __FindOfMutableCompositeClient <
                                cds :: experimental :: MutableCollection < __ElementType >,
                                __ElementType,
                                typename __MutableCollectionDelegateForwardIterableClient < __ElementType > :: Iterator,
                                cds :: experimental :: Collection < __ElementType >,
                                & __collectionContains < __ElementType >
                        >;


                template < typename __ElementType >                     // NOLINT(bugprone-reserved-identifier)
                using __MutableCollectionFindOfInitializerListClient =  // NOLINT(bugprone-reserved-identifier)
                        __FindOfMutableCompositeClient <
                                cds :: experimental :: MutableCollection < __ElementType >,
                                __ElementType,
                                typename __MutableCollectionDelegateForwardIterableClient < __ElementType > :: Iterator,
                                std :: initializer_list < __ElementType >,
                                & __initializerListContains < __ElementType, & cds :: meta :: equals < __ElementType > >
                        >;


                template < typename __ElementType >     // NOLINT(bugprone-reserved-identifier)
                using __MutableCollectionFindByClient = // NOLINT(bugprone-reserved-identifier)
                        __FindByMutableCompositeClient <
                                cds :: experimental :: MutableCollection < __ElementType >,
                                __ElementType,
                                typename __MutableCollectionDelegateForwardIterableClient < __ElementType > :: Iterator
                        >;


                template < typename __ElementType >                 // NOLINT(bugprone-reserved-identifier)
                using __MutableCollectionGenericStatementsClient =  // NOLINT(bugprone-reserved-identifier)
                        __GenericMutableStatementsCompositeClient <
                                cds :: experimental :: MutableCollection < __ElementType >,
                                __ElementType
                        >;

            }
        }
    }
}

#endif // __CDS_MUTABLE_COLLECTION_CONSTRUCTS_HPP__
