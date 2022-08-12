//
// Created by loghin on 10/08/22.
//

#ifndef __CDS_HASH_SET_CONSTRUCTS_HPP__
#define __CDS_HASH_SET_CONSTRUCTS_HPP__

namespace cds {                 // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {    // NOLINT(modernize-concat-nested-namespaces)

        template <
                typename __ElementType,                                                                 // NOLINT(bugprone-reserved-identifier)
                typename __Hasher = FunctionHasher < __ElementType, & cds :: hash < __ElementType > >   // NOLINT(bugprone-reserved-identifier)
        > class HashSet;

        namespace __hidden {    // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier)
            namespace __impl {  // NOLINT(bugprone-reserved-identifier)

                template < typename __ElementType >             // NOLINT(bugprone-reserved-identifier)
                constexpr auto __hashSetKeyExtractor (  // NOLINT(bugprone-reserved-identifier)
                        __ElementType const & element
                ) noexcept -> __ElementType const & {

                    return element;
                }


                template < typename __ElementType >             // NOLINT(bugprone-reserved-identifier)
                constexpr auto __hashSetCopyConstructor (       // NOLINT(bugprone-reserved-identifier)
                        __ElementType       & destination,
                        __ElementType const & source
                ) noexcept -> void {

                    (void) new ( & destination ) __ElementType ( source );
                }


                template < typename __ElementType >             // NOLINT(bugprone-reserved-identifier)
                constexpr auto __hashSetDestructor (      // NOLINT(bugprone-reserved-identifier)
                        __ElementType & element
                ) noexcept -> void {

                    element.~__ElementType();
                }


                template <
                        typename __ElementType,     // NOLINT(bugprone-reserved-identifier)
                        typename __Hasher           // NOLINT(bugprone-reserved-identifier)
                > using __HashSetImplementation =   // NOLINT(bugprone-reserved-identifier)
                        __HashTable <
                                __ElementType,
                                __ElementType,
                                __Hasher,
                                cds :: __hidden :: __impl :: __PrimeRehashPolicy,
                                & __hashSetKeyExtractor < __ElementType >,
                                & cds :: meta :: equals < __ElementType >,
                                & __hashSetDestructor < __ElementType >
                        >;

                template <
                        typename __ElementType, // NOLINT(bugprone-reserved-identifier)
                        typename __Hasher       // NOLINT(bugprone-reserved-identifier)
                > using __HashSetDispatcher =   // NOLINT(bugprone-reserved-identifier)
                        typename __HashSetImplementation <
                                __ElementType,
                                __Hasher
                        > :: template __SetDispatcher <
                                HashSet <
                                        __ElementType,
                                        __Hasher
                                >
                        >;

                template <
                        typename __ElementType, // NOLINT(bugprone-reserved-identifier)
                        typename __Hasher       // NOLINT(bugprone-reserved-identifier)
                > using __HashSetServer =       // NOLINT(bugprone-reserved-identifier)
                        __SetServer <
                                cds :: experimental :: HashSet <
                                        __ElementType,
                                        __Hasher
                                >,
                                __ElementType
                        >;

                template <
                        typename __ElementType,             // NOLINT(bugprone-reserved-identifier)
                        typename __Hasher                   // NOLINT(bugprone-reserved-identifier)
                > using __HashSetDelegateIterableServer =   // NOLINT(bugprone-reserved-identifier)
                        __DelegateIterableServer <
                                cds :: experimental :: HashSet <
                                        __ElementType,
                                        __Hasher
                                >,
                                __ElementType,
                                false,
                                false,
                                void,
                                HashTableConstIterator < __ElementType >,
                                void,
                                void
                        >;

            }
        }
    }
}

#endif // __CDS_HASH_SET_CONSTRUCTS_HPP__
