//
// Created by loghin on 6/13/22.
//

#ifndef __CDS_EX_COLLECTION_FUNCTIONAL_CONSTRUCTORS_IMPL_HPP__
#define __CDS_EX_COLLECTION_FUNCTIONAL_CONSTRUCTORS_IMPL_HPP__

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {

        namespace __hidden { // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier)
            namespace __impl { // NOLINT(bugprone-reserved-identifier)


                template <
                        typename __CollectionType, // NOLINT(bugprone-reserved-identifier)
                        typename __LastArgumentType // NOLINT(bugprone-reserved-identifier)
                > inline auto __collectionOfPush ( // NOLINT(bugprone-reserved-identifier)
                        __CollectionType      & collection,
                        __LastArgumentType   && lastValue
                ) noexcept -> void {

                    collection.add ( std :: forward < __LastArgumentType > ( lastValue ) );
                }


                template <
                        typename __CollectionType, // NOLINT(bugprone-reserved-identifier)
                        typename __FirstArgumentType, // NOLINT(bugprone-reserved-identifier)
                        typename ... __RemainingArgumentTypes // NOLINT(bugprone-reserved-identifier)
                > inline auto __collectionOfPush ( // NOLINT(bugprone-reserved-identifier)
                        __CollectionType          &       collection,
                        __FirstArgumentType      &&       firstValue,
                        __RemainingArgumentTypes && ...   remainingValues
                ) noexcept -> void {

                    collection.add ( std :: forward < __FirstArgumentType > ( firstValue ) );
                    __collectionOfPush ( collection, std :: forward < __RemainingArgumentTypes > ( remainingValues ) ... );
                }

                template <
                        template < typename ... > class __CollectionType, // NOLINT(bugprone-reserved-identifier)
                        typename ... __ArgumentTypes, // NOLINT(bugprone-reserved-identifier)
                        typename __Common // NOLINT(bugprone-reserved-identifier)
                > auto __instantiateCollectionOf ( // NOLINT(bugprone-reserved-identifier)
                        __ArgumentTypes && ... values
                ) noexcept -> __CollectionType < __Common > {

                    __CollectionType < __Common > collection;
                    __hidden :: __impl :: __collectionOfPush ( collection, std :: forward < __ArgumentTypes > ( values ) ... );
                    return collection;
                }

            }
        }

    }
}

#endif // __CDS_EX_COLLECTION_FUNCTIONAL_CONSTRUCTORS_IMPL_HPP__

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {

#if defined (__CDS_EX_LINKED_LIST_HPP__) && ! defined ( __CDS_EX_LINKED_LIST_FUNCTIONAL_CONSTRUCTOR_IMPL__ )
#define __CDS_EX_LINKED_LIST_FUNCTIONAL_CONSTRUCTOR_IMPL__ // NOLINT(bugprone-reserved-identifier)

        template < typename ... __ArgumentTypes > // NOLINT(bugprone-reserved-identifier)
        inline auto linkedListOf (
                __ArgumentTypes && ... values
        ) noexcept -> experimental :: LinkedList < cds :: meta :: Common < __ArgumentTypes ... > > {

            return __hidden :: __impl :: __instantiateCollectionOf < LinkedList > ( std :: forward < __ArgumentTypes > ( values ) ... );
        }

#endif // __CDS_EX_LINKED_LIST_FUNCTIONAL_CONSTRUCTOR_IMPL__


#if defined (__CDS_EX_ARRAY_HPP__) && ! defined ( __CDS_EX_ARRAY_FUNCTIONAL_CONSTRUCTOR_IMPL__ )
#define __CDS_EX_ARRAY_FUNCTIONAL_CONSTRUCTOR_IMPL__ // NOLINT(bugprone-reserved-identifier)

        template < typename ... __ArgumentTypes > // NOLINT(bugprone-reserved-identifier)
        inline auto arrayOf (
                __ArgumentTypes && ... values
        ) noexcept -> experimental :: Array < cds :: meta :: Common < __ArgumentTypes ... > > {

            return __hidden :: __impl :: __instantiateCollectionOf < Array > ( std :: forward < __ArgumentTypes > ( values ) ... );
        }

#endif // __CDS_EX_ARRAY_FUNCTIONAL_CONSTRUCTOR_IMPL__



#if defined (__CDS_EX_ORDERED_SET_HPP__) && ! defined ( __CDS_EX_ORDERED_SET_FUNCTIONAL_CONSTRUCTOR_IMPL__ )
#define __CDS_EX_ORDERED_SET_FUNCTIONAL_CONSTRUCTOR_IMPL__ // NOLINT(bugprone-reserved-identifier)

        template < typename ... __ArgumentTypes > // NOLINT(bugprone-reserved-identifier)
        inline auto orderedSetOf (
                __ArgumentTypes && ... values
        ) noexcept -> experimental :: OrderedSet < cds :: meta :: Common < __ArgumentTypes ... > > {

            return __hidden :: __impl :: __instantiateCollectionOf < OrderedSet > ( std :: forward < __ArgumentTypes > ( values ) ... );
        }

#endif // __CDS_EX_ORDERED_SET_FUNCTIONAL_CONSTRUCTOR_IMPL__



#if defined (__CDS_EX_HASH_SET_HPP__) && ! defined ( __CDS_EX_HASH_SET_FUNCTIONAL_CONSTRUCTOR_IMPL__ )
#define __CDS_EX_HASH_SET_FUNCTIONAL_CONSTRUCTOR_IMPL__ // NOLINT(bugprone-reserved-identifier)

        template < typename ... __ArgumentTypes > // NOLINT(bugprone-reserved-identifier)
        inline auto hashSetOf (
                __ArgumentTypes && ... values
        ) noexcept -> experimental :: HashSet < cds :: meta :: Common < __ArgumentTypes ... > > {

            return __hidden :: __impl :: __instantiateCollectionOf < HashSet > ( std :: forward < __ArgumentTypes > ( values ) ... );
        }

#endif // __CDS_EX_HASH_SET_FUNCTIONAL_CONSTRUCTOR_IMPL__




#if defined (__CDS_LIST_FUNCTIONAL_CONSTRUCTOR_TYPE) && ! defined ( __CDS_EX_LIST_FUNCTIONAL_CONSTRUCTOR_IMPL__ )
#define __CDS_EX_LIST_FUNCTIONAL_CONSTRUCTOR_IMPL__ // NOLINT(bugprone-reserved-identifier)

        template < typename ... __ArgumentTypes > // NOLINT(bugprone-reserved-identifier)
        inline auto listOf (
                __ArgumentTypes && ... values
        ) noexcept -> __CDS_LIST_FUNCTIONAL_CONSTRUCTOR_TYPE < cds :: meta :: Common < __ArgumentTypes ... > > {

            return __hidden :: __impl :: __instantiateCollectionOf < __CDS_LIST_FUNCTIONAL_CONSTRUCTOR_TYPE > (
                    std :: forward < __ArgumentTypes > ( values ) ...
            );
        }

#endif // __CDS_EX_LIST_FUNCTIONAL_CONSTRUCTOR_IMPL__


#if defined (__CDS_SET_FUNCTIONAL_CONSTRUCTOR_TYPE) && ! defined ( __CDS_EX_SET_FUNCTIONAL_CONSTRUCTOR_IMPL__ )
#define __CDS_EX_SET_FUNCTIONAL_CONSTRUCTOR_IMPL__ // NOLINT(bugprone-reserved-identifier)

        template < typename ... __ArgumentTypes > // NOLINT(bugprone-reserved-identifier)
        inline auto setOf (
                __ArgumentTypes && ... values
        ) noexcept -> __CDS_SET_FUNCTIONAL_CONSTRUCTOR_TYPE < cds :: meta :: Common < __ArgumentTypes ... > > {

            return __hidden :: __impl :: __instantiateCollectionOf < __CDS_SET_FUNCTIONAL_CONSTRUCTOR_TYPE > (
                    std :: forward < __ArgumentTypes > ( values ) ...
            );
        }

#endif // __CDS_EX_SET_FUNCTIONAL_CONSTRUCTOR_IMPL__

    }
}
