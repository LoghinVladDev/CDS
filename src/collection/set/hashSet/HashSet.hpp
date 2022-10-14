/*
 * Created by loghin on 6/13/22.
 */

#ifndef __CDS_HASH_SET_HPP__
#define __CDS_HASH_SET_HPP__ /* NOLINT(bugprone-reserved-identifier) */

#include <CDS/Set>

#include <CDS/Comparator>
#include <CDS/Extractor>
#include <CDS/Hasher>
#include <CDS/Destructor>
#include <CDS/CopyConstructor>

#include "../../../shared/Node.hpp"
#include "../../../shared/rehashPolicy/rehashPolicy.hpp"

#include "../../../shared/iterator/HashTableIterator.hpp"

#include "../../../shared/collectionInternalCommunication/server/SetServerDispatcher.hpp"

#include "../../../shared/delegateIterator/AbstractDelegateIterator.hpp"
#include "../../../shared/delegateIterator/DelegateIterator.hpp"

#include "../../../shared/hashTable/HashTable.hpp"

#include "../../../shared/collectionInternalCommunication/server/SetServer.hpp"

#include "hashSet/Constructs.hpp"

namespace cds {

    template <
            typename __ElementType, /* NOLINT(bugprone-reserved-identifier) */
            typename __Hasher       /* NOLINT(bugprone-reserved-identifier) */
    > class HashSet :
            public Set < __ElementType >,
            protected __hidden :: __impl :: __HashSetServer < __ElementType, __Hasher >,
            public __hidden :: __impl :: __HashSetImplementation < __ElementType, __Hasher >,
            public __hidden :: __impl :: __HashSetDispatcher < __ElementType, __Hasher >,
            public __hidden :: __impl :: __HashSetRandomInsertionClient < __ElementType, __Hasher >,
            public __hidden :: __impl :: __HashSetIteratorRemoveClient < __ElementType, __Hasher >,
            public __hidden :: __impl :: __HashSetFindOfCollectionClient < __ElementType, __Hasher >,
            public __hidden :: __impl :: __HashSetFindOfInitializerListClient < __ElementType, __Hasher >,
            public __hidden :: __impl :: __HashSetFindByClient < __ElementType, __Hasher >,
            public __hidden :: __impl :: __HashSetRemoveOfCollectionClient < __ElementType, __Hasher >,
            public __hidden :: __impl :: __HashSetRemoveOfInitializerListClient < __ElementType, __Hasher >,
            public __hidden :: __impl :: __HashSetRemoveByClient < __ElementType, __Hasher >,
            public __hidden :: __impl :: __HashSetGenericStatementsClient < __ElementType, __Hasher >,
            public __hidden :: __impl :: __HashSetFindUniqueClient < __ElementType, __Hasher >,
            public __hidden :: __impl :: __HashSetContainsOfCollectionClient < __ElementType, __Hasher >,
            public __hidden :: __impl :: __HashSetContainsOfInitializerListClient < __ElementType, __Hasher >,
            public __hidden :: __impl :: __HashSetDelegateForwardConstIterableClient < __ElementType, __Hasher > {

    protected:  using SetBase                               = Set < __ElementType >;
    protected:  using Server                                = __hidden :: __impl :: __HashSetServer < __ElementType, __Hasher >;
    protected:  using Implementation                        = __hidden :: __impl :: __HashSetImplementation < __ElementType, __Hasher >;
    protected:  using Dispatcher                            = __hidden :: __impl :: __HashSetDispatcher < __ElementType, __Hasher >;
    protected:  using RandomInsertionClient                 = __hidden :: __impl :: __HashSetRandomInsertionClient < __ElementType, __Hasher >;
    protected:  using IteratorRemoveClient                  = __hidden :: __impl :: __HashSetIteratorRemoveClient < __ElementType, __Hasher >;
    protected:  using FindOfCollectionClient                = __hidden :: __impl :: __HashSetFindOfCollectionClient < __ElementType, __Hasher >;
    protected:  using FindOfInitializerListClient           = __hidden :: __impl :: __HashSetFindOfInitializerListClient < __ElementType, __Hasher >;
    protected:  using FindByClient                          = __hidden :: __impl :: __HashSetFindByClient < __ElementType, __Hasher >;
    protected:  using RemoveOfCollectionClient              = __hidden :: __impl :: __HashSetRemoveOfCollectionClient < __ElementType, __Hasher >;
    protected:  using RemoveOfInitializerListClient         = __hidden :: __impl :: __HashSetRemoveOfInitializerListClient < __ElementType, __Hasher >;
    protected:  using RemoveByClient                        = __hidden :: __impl :: __HashSetRemoveByClient < __ElementType, __Hasher >;
    protected:  using GenericStatementsClient               = __hidden :: __impl :: __HashSetGenericStatementsClient < __ElementType, __Hasher >;
    protected:  using ContainsOfCollectionClient            = __hidden :: __impl :: __HashSetContainsOfCollectionClient < __ElementType, __Hasher >;
    protected:  using ContainsOfInitializerListClient       = __hidden :: __impl :: __HashSetContainsOfInitializerListClient < __ElementType, __Hasher >;
    protected:  using FindUniqueClient                      = __hidden :: __impl :: __HashSetFindUniqueClient < __ElementType, __Hasher >;
    protected:  using DelegateForwardConstIterableClient    = __hidden :: __impl :: __HashSetDelegateForwardConstIterableClient < __ElementType, __Hasher >;

    protected:  friend Server;

    protected:  using typename SetBase :: __GenericHandler;         /* NOLINT(bugprone-reserved-identifier) */
    protected:  using typename SetBase :: __GenericConstHandler;    /* NOLINT(bugprone-reserved-identifier) */

    public:     using typename DelegateForwardConstIterableClient :: ConstIterator;

    public:     using ElementType   = __ElementType;

    private:    friend RandomInsertionClient;
    private:    friend IteratorRemoveClient;
    private:    friend DelegateForwardConstIterableClient;
    private:    friend FindUniqueClient;

    private:
        __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto __cicch_obtainGenericHandler ( /* NOLINT(bugprone-reserved-identifier) */
                __hidden :: __impl :: __CollectionInternalRequestType requestType
        ) noexcept -> __GenericHandler override;

    private:
        __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto __cicch_obtainGenericConstHandler (    /* NOLINT(bugprone-reserved-identifier) */
                __hidden :: __impl :: __CollectionInternalRequestType requestType
        ) const noexcept -> __GenericConstHandler override;

    public:     using DelegateForwardConstIterableClient :: begin;
    public:     using DelegateForwardConstIterableClient :: end;
    public:     using DelegateForwardConstIterableClient :: cbegin;
    public:     using DelegateForwardConstIterableClient :: cend;

    public:     using RemoveByClient :: removeThat;
    public:     using RemoveByClient :: removeFirstThat;
    public:     using RemoveByClient :: removeLastThat;
    public:     using RemoveByClient :: removeAllThat;

    public:     using GenericStatementsClient :: forEach;
    public:     using GenericStatementsClient :: some;
    public:     using GenericStatementsClient :: atLeast;
    public:     using GenericStatementsClient :: atMost;
    public:     using GenericStatementsClient :: moreThan;
    public:     using GenericStatementsClient :: fewerThan;
    public:     using GenericStatementsClient :: count;
    public:     using GenericStatementsClient :: any;
    public:     using GenericStatementsClient :: all;
    public:     using GenericStatementsClient :: none;

    public:     using RemoveOfCollectionClient :: removeOf;
    public:     using RemoveOfCollectionClient :: removeFirstOf;
    public:     using RemoveOfCollectionClient :: removeLastOf;
    public:     using RemoveOfCollectionClient :: removeAllOf;
    public:     using RemoveOfCollectionClient :: removeNotOf;
    public:     using RemoveOfCollectionClient :: removeFirstNotOf;
    public:     using RemoveOfCollectionClient :: removeLastNotOf;
    public:     using RemoveOfCollectionClient :: removeAllNotOf;

    public:     using RemoveOfInitializerListClient :: removeOf;
    public:     using RemoveOfInitializerListClient :: removeFirstOf;
    public:     using RemoveOfInitializerListClient :: removeLastOf;
    public:     using RemoveOfInitializerListClient :: removeAllOf;
    public:     using RemoveOfInitializerListClient :: removeNotOf;
    public:     using RemoveOfInitializerListClient :: removeFirstNotOf;
    public:     using RemoveOfInitializerListClient :: removeLastNotOf;
    public:     using RemoveOfInitializerListClient :: removeAllNotOf;

    public:     using FindByClient :: findThat;
    public:     using FindByClient :: findFirstThat;
    public:     using FindByClient :: findLastThat;
    public:     using FindByClient :: findAllThat;

    public:     using FindOfCollectionClient :: findOf;
    public:     using FindOfCollectionClient :: findFirstOf;
    public:     using FindOfCollectionClient :: findLastOf;
    public:     using FindOfCollectionClient :: findAllOf;
    public:     using FindOfCollectionClient :: findNotOf;
    public:     using FindOfCollectionClient :: findFirstNotOf;
    public:     using FindOfCollectionClient :: findLastNotOf;
    public:     using FindOfCollectionClient :: findAllNotOf;

    public:     using FindOfInitializerListClient :: findOf;
    public:     using FindOfInitializerListClient :: findFirstOf;
    public:     using FindOfInitializerListClient :: findLastOf;
    public:     using FindOfInitializerListClient :: findAllOf;
    public:     using FindOfInitializerListClient :: findNotOf;
    public:     using FindOfInitializerListClient :: findFirstNotOf;
    public:     using FindOfInitializerListClient :: findLastNotOf;
    public:     using FindOfInitializerListClient :: findAllNotOf;

    public:     using ContainsOfCollectionClient :: containsAnyOf;
    public:     using ContainsOfCollectionClient :: containsAnyNotOf;
    public:     using ContainsOfCollectionClient :: containsAllOf;
    public:     using ContainsOfCollectionClient :: containsNoneOf;

    public:     using ContainsOfInitializerListClient :: containsAnyOf;
    public:     using ContainsOfInitializerListClient :: containsAnyNotOf;
    public:     using ContainsOfInitializerListClient :: containsAllOf;
    public:     using ContainsOfInitializerListClient :: containsNoneOf;

    public:     using RandomInsertionClient :: add;
    public:     using RandomInsertionClient :: addAll;
    public:     using RandomInsertionClient :: addAllOf;
    public:     using RandomInsertionClient :: insert;
    public:     using RandomInsertionClient :: insertAll;
    public:     using RandomInsertionClient :: insertAllOf;
    public:     using RandomInsertionClient :: emplace;

    public:     using IteratorRemoveClient :: remove;

    public:     using FindUniqueClient :: find;

    public:
        constexpr HashSet () noexcept;

    public:
        HashSet ( /* NOLINT(google-explicit-constructor) */
                HashSet const & set
        ) noexcept;

    public:
        constexpr HashSet (
                HashSet && set
        ) noexcept;

    public:
        template <
                typename __IteratorType,                    /* NOLINT(bugprone-reserved-identifier) */
                typename __TElementType = __ElementType,    /* NOLINT(bugprone-reserved-identifier) */
                cds :: meta :: EnableIf <
                        cds :: meta :: isCopyConstructible < __TElementType > ()
                > = 0
        > HashSet (
                __IteratorType const & begin,
                __IteratorType const & end,
                Size                   count = 0ULL
        ) noexcept;

    public:
        template <
                typename __IteratorType,                    /* NOLINT(bugprone-reserved-identifier) */
                typename __TElementType = __ElementType,    /* NOLINT(bugprone-reserved-identifier) */
                cds :: meta :: EnableIf <
                        cds :: meta :: isCopyConstructible < __TElementType > ()
                > = 0
        > HashSet (
                __Hasher        const & hasher,
                __IteratorType  const & begin,
                __IteratorType  const & end,
                Size                    count = 0ULL
        ) noexcept;

    public:
        template <
                typename __TElementType = __ElementType,    /* NOLINT(bugprone-reserved-identifier) */
                cds :: meta :: EnableIf <
                        cds :: meta :: isCopyConstructible < __TElementType > ()
                > = 0
        > HashSet (
                std :: initializer_list < __ElementType > const & initializerList
        ) noexcept;

    public:
        template <
                typename __TElementType = __ElementType,    /* NOLINT(bugprone-reserved-identifier) */
                cds :: meta :: EnableIf <
                        cds :: meta :: isCopyConstructible < __TElementType > ()
                > = 0
        > HashSet (
                __Hasher                                    const & hasher,
                std :: initializer_list < __ElementType >   const & initializerList
        ) noexcept;

    public:
        template < typename __IterableType > /* NOLINT(bugprone-reserved-identifier) */
        __CDS_Explicit HashSet (
                __IterableType  const & iterable
        ) noexcept;

    public:
        template < typename __IterableType > /* NOLINT(bugprone-reserved-identifier) */
        HashSet (
                __Hasher        const & hasher,
                __IterableType  const & iterable
        ) noexcept;

    public:
        ~HashSet () noexcept override;

    public:
        auto operator = (
                HashSet const & set
        ) noexcept -> HashSet &;

    public:
        auto operator = (
                HashSet && set
        ) noexcept -> HashSet &;

    public:
        auto operator = (
                std :: initializer_list < __ElementType > const & initializerList
        ) noexcept -> HashSet &;

    public:
        template < typename __IterableType > /* NOLINT(bugprone-reserved-identifier) */
        auto operator = (
                __IterableType const & iterable
        ) noexcept -> HashSet &;

    public:
        __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto operator == (
                HashSet const & set
        ) const noexcept -> bool;

    public:
        __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto operator != (
                HashSet const & set
        ) const noexcept -> bool;

    public:
        auto clear () noexcept -> void override;

    public:
        __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto size () const noexcept -> Size override;

    public:
        auto remove (
                __ElementType const & element
        ) noexcept -> bool override;

    public:
        __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto contains (
                __ElementType const & element
        ) const noexcept -> bool override;

    public:
        __CDS_NoDiscard auto sequence () & noexcept -> Sequence < HashSet < __ElementType, __Hasher > >;

    public:
        __CDS_NoDiscard auto sequence () && noexcept -> Sequence < HashSet < __ElementType, __Hasher > >;

    public:
        __CDS_NoDiscard auto sequence () const & noexcept -> Sequence < HashSet < __ElementType, __Hasher > const >;

    public:
        __CDS_NoDiscard auto sequence () const && noexcept -> Sequence < HashSet < __ElementType, __Hasher > const >;
    };

}

#include "../../../shared/hashTable/impl/HashTable.hpp"

#include "../../../shared/iterator/impl/HashTableIterator.hpp"

#include "../../../shared/collectionInternalCommunication/server/impl/SetServer.hpp"
#include "../../../shared/collectionInternalCommunication/server/impl/SetServerDispatcher.hpp"

#include "../../../shared/delegateIterator/impl/AbstractDelegateIterator.hpp"
#include "../../../shared/delegateIterator/impl/DelegateIterator.hpp"

#include "hashSet/impl/HashSet.hpp"
#include "hashSet/impl/CTAD.hpp"

#include "../../../shared/hashSet/impl/Sequence.hpp"

#include "../../../shared/collection/FunctionalConstructors.hpp"
#include "../../../shared/collection/impl/FunctionalConstructors.hpp"

#endif /* __CDS_HASH_SET_HPP__ */
