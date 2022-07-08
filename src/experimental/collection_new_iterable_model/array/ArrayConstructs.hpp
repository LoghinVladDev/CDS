//
// Created by loghin on 08/07/22.
//

#ifndef __CDS_ARRAY_CONSTRUCTS_HPP__
#define __CDS_ARRAY_CONSTRUCTS_HPP__

namespace cds {                 // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {    // NOLINT(modernize-concat-nested-namespaces)

        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        class Array;

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
