/*
 * Created by loghin on 15.01.2021.
 */

#ifndef __CDS_HASH_MAP_HPP__
#define __CDS_HASH_MAP_HPP__ /* NOLINT(bugprone-reserved-identifier) */

#include <CDS/Map>

#include <CDS/Comparator>
#include <CDS/Extractor>
#include <CDS/Hasher>
#include <CDS/Destructor>
#include <CDS/CopyConstructor>

#include "../../../../shared/Node.hpp"
#include "../../../../shared/rehashPolicy/rehashPolicy.hpp"

#include "../../../../shared/iterator/HashTableIterator.hpp"
#include "../../../../shared/iterator/IteratorGenericDecorator.hpp"

#include "../../../../shared/collectionInternalCommunication/server/MapServerDispatcher.hpp"

#include "../../../../shared/delegateIterator/AbstractDelegateIterator.hpp"
#include "../../../../shared/delegateIterator/DelegateIterator.hpp"

#include "../../../../shared/hashTable/HashTable.hpp"

#include "../../../../shared/collectionInternalCommunication/server/SetServer.hpp"
#include "../../../../shared/collectionInternalCommunication/server/MapServer.hpp"

#include "hashMap/Constructs.hpp"

namespace cds {

    template <
            typename __KeyType,     /* NOLINT(bugprone-reserved-identifier) */
            typename __ValueType,   /* NOLINT(bugprone-reserved-identifier) */
            typename __Hasher       /* NOLINT(bugprone-reserved-identifier) */
    > class HashMap :
            public Map < __KeyType, __ValueType >,
            protected __hidden :: __impl :: __HashMapServer < __KeyType, __ValueType, __Hasher >,
            public __hidden :: __impl :: __HashMapImplementation < __KeyType, __ValueType, __Hasher >,
            public __hidden :: __impl :: __HashMapDispatcher < __KeyType, __ValueType, __Hasher >,
            public __hidden :: __impl :: __HashMapRandomInsertionClient < __KeyType, __ValueType, __Hasher >,
            public __hidden :: __impl :: __HashMapIteratorRemoveClient < __KeyType, __ValueType, __Hasher >,
            public __hidden :: __impl :: __HashMapConstIteratorRemoveClient < __KeyType, __ValueType, __Hasher >,
            public __hidden :: __impl :: __HashMapFindOfCollectionClient < __KeyType, __ValueType, __Hasher >,
            public __hidden :: __impl :: __HashMapFindOfConstCollectionClient < __KeyType, __ValueType, __Hasher >,
            public __hidden :: __impl :: __HashMapFindOfInitializerListClient < __KeyType, __ValueType, __Hasher >,
            public __hidden :: __impl :: __HashMapFindOfConstInitializerListClient < __KeyType, __ValueType, __Hasher >,
            public __hidden :: __impl :: __HashMapFindByClient < __KeyType, __ValueType, __Hasher >,
            public __hidden :: __impl :: __HashMapFindByConstClient < __KeyType, __ValueType, __Hasher >,
            public __hidden :: __impl :: __HashMapFindUniqueClient < __KeyType, __ValueType, __Hasher >,
            public __hidden :: __impl :: __HashMapFindUniqueConstClient < __KeyType, __ValueType, __Hasher >,
            public __hidden :: __impl :: __HashMapRemoveOfCollectionClient < __KeyType, __ValueType, __Hasher >,
            public __hidden :: __impl :: __HashMapRemoveOfInitializerListClient < __KeyType, __ValueType, __Hasher >,
            public __hidden :: __impl :: __HashMapRemoveByClient < __KeyType, __ValueType, __Hasher >,
            public __hidden :: __impl :: __HashMapGenericStatementsClient < __KeyType, __ValueType, __Hasher >,
            public __hidden :: __impl :: __HashMapConstGenericStatementsClient < __KeyType, __ValueType, __Hasher >,
            public __hidden :: __impl :: __HashMapContainsOfCollectionClient < __KeyType, __ValueType, __Hasher >,
            public __hidden :: __impl :: __HashMapContainsOfInitializerListClient < __KeyType, __ValueType, __Hasher >,
            public __hidden :: __impl :: __HashMapDelegateForwardIterableClient < __KeyType, __ValueType, __Hasher >,
            public __hidden :: __impl :: __HashMapDelegateForwardConstIterableClient < __KeyType, __ValueType, __Hasher > {

    protected:  using MapBase                               = Map < __KeyType, __ValueType >;
    protected:  using Server                                = __hidden :: __impl :: __HashMapServer < __KeyType, __ValueType, __Hasher >;
    protected:  using Implementation                        = __hidden :: __impl :: __HashMapImplementation < __KeyType, __ValueType, __Hasher >;
    protected:  using Dispatcher                            = __hidden :: __impl :: __HashMapDispatcher < __KeyType, __ValueType, __Hasher >;
    protected:  using RandomInsertionClient                 = __hidden :: __impl :: __HashMapRandomInsertionClient < __KeyType, __ValueType, __Hasher >;
    protected:  using IteratorRemoveClient                  = __hidden :: __impl :: __HashMapIteratorRemoveClient < __KeyType, __ValueType, __Hasher >;
    protected:  using ConstIteratorRemoveClient             = __hidden :: __impl :: __HashMapConstIteratorRemoveClient < __KeyType, __ValueType, __Hasher >;
    protected:  using FindOfCollectionClient                = __hidden :: __impl :: __HashMapFindOfCollectionClient < __KeyType, __ValueType, __Hasher >;
    protected:  using FindOfConstCollectionClient           = __hidden :: __impl :: __HashMapFindOfConstCollectionClient < __KeyType, __ValueType, __Hasher >;
    protected:  using FindOfInitializerListClient           = __hidden :: __impl :: __HashMapFindOfInitializerListClient < __KeyType, __ValueType, __Hasher >;
    protected:  using FindOfConstInitializerListClient      = __hidden :: __impl :: __HashMapFindOfConstInitializerListClient < __KeyType, __ValueType, __Hasher >;
    protected:  using FindByClient                          = __hidden :: __impl :: __HashMapFindByClient < __KeyType, __ValueType, __Hasher >;
    protected:  using FindByConstClient                     = __hidden :: __impl :: __HashMapFindByConstClient < __KeyType, __ValueType, __Hasher >;
    protected:  using FindUniqueClient                      = __hidden :: __impl :: __HashMapFindUniqueClient < __KeyType, __ValueType, __Hasher >;
    protected:  using FindUniqueConstClient                 = __hidden :: __impl :: __HashMapFindUniqueConstClient < __KeyType, __ValueType, __Hasher >;
    protected:  using RemoveOfCollectionClient              = __hidden :: __impl :: __HashMapRemoveOfCollectionClient < __KeyType, __ValueType, __Hasher >;
    protected:  using RemoveOfInitializerListClient         = __hidden :: __impl :: __HashMapRemoveOfInitializerListClient < __KeyType, __ValueType, __Hasher >;
    protected:  using RemoveByClient                        = __hidden :: __impl :: __HashMapRemoveByClient < __KeyType, __ValueType, __Hasher >;
    protected:  using GenericStatementsClient               = __hidden :: __impl :: __HashMapGenericStatementsClient < __KeyType, __ValueType, __Hasher >;
    protected:  using ConstGenericStatementsClient          = __hidden :: __impl :: __HashMapConstGenericStatementsClient < __KeyType, __ValueType, __Hasher >;
    protected:  using ContainsOfCollectionClient            = __hidden :: __impl :: __HashMapContainsOfCollectionClient < __KeyType, __ValueType, __Hasher >;
    protected:  using ContainsOfInitializerListClient       = __hidden :: __impl :: __HashMapContainsOfInitializerListClient < __KeyType, __ValueType, __Hasher >;
    protected:  using DelegateForwardIterableClient         = __hidden :: __impl :: __HashMapDelegateForwardIterableClient < __KeyType, __ValueType, __Hasher >;
    protected:  using DelegateForwardConstIterableClient    = __hidden :: __impl :: __HashMapDelegateForwardConstIterableClient < __KeyType, __ValueType, __Hasher >;

    protected:  friend Server;
    protected:  friend RandomInsertionClient;
    protected:  friend IteratorRemoveClient;
    protected:  friend ConstIteratorRemoveClient;
    private:    friend DelegateForwardIterableClient;
    private:    friend DelegateForwardConstIterableClient;

    protected:  using typename MapBase :: __GenericHandler;         /* NOLINT(bugprone-reserved-identifier) */
    protected:  using typename MapBase :: __GenericConstHandler;    /* NOLINT(bugprone-reserved-identifier) */

    protected:  using typename MapBase :: AbstractMapProxy;
    protected:  using typename MapBase :: AbstractKeySetProxy;
    protected:  using typename MapBase :: AbstractValueMutableCollectionProxy;
    protected:  using typename MapBase :: AbstractEntryMutableCollectionProxy;

    public:     using typename DelegateForwardIterableClient :: Iterator;
    public:     using typename DelegateForwardConstIterableClient :: ConstIterator;

    protected:  class KeySetProxy;
    protected:  class ValueMutableCollectionProxy;
    protected:  class EntryMutableCollectionProxy;

    public:     using ElementType   = typename MapBase :: ElementType;
    public:     using EntryType     = typename MapBase :: EntryType;
    public:     using KeyType       = typename MapBase :: KeyType;
    public:     using ValueType     = typename MapBase :: ValueType;

    private:    KeySetProxy                 _keySetProxy;
    private:    ValueMutableCollectionProxy _valueMutableCollectionProxy;
    private:    EntryMutableCollectionProxy _entryMutableCollectionProxy;

    private:
        __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto __cicch_obtainGenericHandler ( /* NOLINT(bugprone-reserved-identifier) */
                __hidden :: __impl :: __CollectionInternalRequestType requestType
        ) noexcept -> __GenericHandler override;

    private:
        __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto __cicch_obtainGenericConstHandler (    /* NOLINT(bugprone-reserved-identifier) */
                __hidden :: __impl :: __CollectionInternalRequestType requestType
        ) const noexcept -> __GenericConstHandler override;

    public:     using DelegateForwardIterableClient :: begin;
    public:     using DelegateForwardIterableClient :: end;

    public:     using DelegateForwardConstIterableClient :: begin;
    public:     using DelegateForwardConstIterableClient :: end;
    public:     using DelegateForwardConstIterableClient :: cbegin;
    public:     using DelegateForwardConstIterableClient :: cend;

    protected:  using MapBase :: remove;

    public:     using IteratorRemoveClient :: remove;
    public:     using ConstIteratorRemoveClient :: remove;

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

    public:     using ConstGenericStatementsClient :: forEach;
    public:     using ConstGenericStatementsClient :: some;
    public:     using ConstGenericStatementsClient :: atLeast;
    public:     using ConstGenericStatementsClient :: atMost;
    public:     using ConstGenericStatementsClient :: moreThan;
    public:     using ConstGenericStatementsClient :: fewerThan;
    public:     using ConstGenericStatementsClient :: count;
    public:     using ConstGenericStatementsClient :: any;
    public:     using ConstGenericStatementsClient :: all;
    public:     using ConstGenericStatementsClient :: none;

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

    public:     using ContainsOfCollectionClient :: containsAnyOf;
    public:     using ContainsOfCollectionClient :: containsAnyNotOf;
    public:     using ContainsOfCollectionClient :: containsAllOf;
    public:     using ContainsOfCollectionClient :: containsNoneOf;

    public:     using ContainsOfInitializerListClient :: containsAnyOf;
    public:     using ContainsOfInitializerListClient :: containsAnyNotOf;
    public:     using ContainsOfInitializerListClient :: containsAllOf;
    public:     using ContainsOfInitializerListClient :: containsNoneOf;

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

    public:     using FindByConstClient :: findThat;
    public:     using FindByConstClient :: findFirstThat;
    public:     using FindByConstClient :: findLastThat;
    public:     using FindByConstClient :: findAllThat;

    public:     using FindOfConstCollectionClient :: findOf;
    public:     using FindOfConstCollectionClient :: findFirstOf;
    public:     using FindOfConstCollectionClient :: findLastOf;
    public:     using FindOfConstCollectionClient :: findAllOf;
    public:     using FindOfConstCollectionClient :: findNotOf;
    public:     using FindOfConstCollectionClient :: findFirstNotOf;
    public:     using FindOfConstCollectionClient :: findLastNotOf;
    public:     using FindOfConstCollectionClient :: findAllNotOf;

    public:     using FindOfConstInitializerListClient :: findOf;
    public:     using FindOfConstInitializerListClient :: findFirstOf;
    public:     using FindOfConstInitializerListClient :: findLastOf;
    public:     using FindOfConstInitializerListClient :: findAllOf;
    public:     using FindOfConstInitializerListClient :: findNotOf;
    public:     using FindOfConstInitializerListClient :: findFirstNotOf;
    public:     using FindOfConstInitializerListClient :: findLastNotOf;
    public:     using FindOfConstInitializerListClient :: findAllNotOf;

    public:     using RandomInsertionClient :: add;
    public:     using RandomInsertionClient :: addAll;
    public:     using RandomInsertionClient :: addAllOf;
    public:     using RandomInsertionClient :: insert;
    public:     using RandomInsertionClient :: insertAll;
    public:     using RandomInsertionClient :: insertAllOf;
    public:     using RandomInsertionClient :: emplace;

    public:     using FindUniqueClient :: find;
    public:     using FindUniqueConstClient :: find;

    protected:
        __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto keySetProxy () const noexcept -> AbstractKeySetProxy const & override;

    protected:
        __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto keySetProxy () noexcept -> AbstractKeySetProxy & override;

    protected:
        __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto valueMutableCollectionProxy () const noexcept -> AbstractValueMutableCollectionProxy const & override;

    protected:
        __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto valueMutableCollectionProxy () noexcept -> AbstractValueMutableCollectionProxy & override;

    protected:
        __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto entryMutableCollectionProxy () const noexcept -> AbstractEntryMutableCollectionProxy const & override;

    protected:
        __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto entryMutableCollectionProxy () noexcept -> AbstractEntryMutableCollectionProxy & override;

    public:
        constexpr HashMap () noexcept;

    public:
        HashMap ( /* NOLINT(google-explicit-constructor) */
                HashMap const & map
        ) noexcept;

    public:
        constexpr HashMap (
                HashMap && map
        ) noexcept;

    public:
        __CDS_Explicit constexpr HashMap (
                __Hasher const & hasher
        ) noexcept;

    public:
        template <
                typename __IteratorType,                    /* NOLINT(bugprone-reserved-identifier) */
                typename __TElementType = ElementType,      /* NOLINT(bugprone-reserved-identifier) */
                cds :: meta :: EnableIf <
                        cds :: meta :: isCopyConstructible < __TElementType > ()
                > = 0
        > HashMap (
                __IteratorType const & begin,
                __IteratorType const & end,
                Size                   count = 0ULL
        ) noexcept;

    public:
        template <
                typename __IteratorType,                    /* NOLINT(bugprone-reserved-identifier) */
                typename __TElementType = ElementType,      /* NOLINT(bugprone-reserved-identifier) */
                cds :: meta :: EnableIf <
                        cds :: meta :: isCopyConstructible < __TElementType > ()
                > = 0
        > HashMap (
                __Hasher        const & hasher,
                __IteratorType  const & begin,
                __IteratorType  const & end,
                Size                    count = 0ULL
        ) noexcept;

    public:
        template <
                typename __TElementType = ElementType,      /* NOLINT(bugprone-reserved-identifier) */
                cds :: meta :: EnableIf <
                        cds :: meta :: isCopyConstructible < __TElementType > ()
                > = 0
        > HashMap (
                std :: initializer_list < ElementType > const & initializerList
        ) noexcept;

    public:
        template <
                typename __TElementType = ElementType,    /* NOLINT(bugprone-reserved-identifier) */
                cds :: meta :: EnableIf <
                        cds :: meta :: isCopyConstructible < __TElementType > ()
                > = 0
        > HashMap (
                __Hasher                                    const & hasher,
                std :: initializer_list < ElementType >   const & initializerList
        ) noexcept;

    public:
        template < typename __IterableType > /* NOLINT(bugprone-reserved-identifier) */
        __CDS_Explicit HashMap (
                __IterableType  const & iterable
        ) noexcept;

    public:
        template < typename __IterableType > /* NOLINT(bugprone-reserved-identifier) */
        HashMap (
                __Hasher        const & hasher,
                __IterableType  const & iterable
        ) noexcept;

    public:
        ~HashMap () noexcept override;

    public:
        auto operator = (
                HashMap const & map
        ) noexcept -> HashMap &;

    public:
        auto operator = (
                HashMap && map
        ) noexcept -> HashMap &;

    public:
        auto operator = (
                std :: initializer_list < EntryType > const & initializerList
        ) noexcept -> HashMap &;

    public:
        template < typename __IterableType > /* NOLINT(bugprone-reserved-identifier) */
        auto operator = (
                __IterableType const & iterable
        ) noexcept -> HashMap &;

    public:
        __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto operator == (
                HashMap const & map
        ) const noexcept -> bool;

    public:
        __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto operator != (
                HashMap const & map
        ) const noexcept -> bool;

    public:
        auto clear () noexcept -> void override;

    public:
        __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto size () const noexcept -> Size override;

    public:
        auto remove (
                KeyType const & key
        ) noexcept -> bool override;

    public:
        __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto containsKey (
                __KeyType const & key
        ) const noexcept -> bool override;

    public:
        __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto containsValue (
                __ValueType const & value
        ) const noexcept -> bool override;

    private:
        auto entryAt (
                __KeyType const & key,
                bool            * pNewElementCreated
        ) noexcept -> EntryType * override;

    private:
        __CDS_cpplang_ConstexprOverride auto entryAt (
                __KeyType const & key
        ) const noexcept -> EntryType const * override;

    public:
        __CDS_NoDiscard auto sequence () & noexcept -> Sequence < HashMap < __KeyType, __ValueType, __Hasher > >;

    public:
        __CDS_NoDiscard auto sequence () && noexcept -> Sequence < HashMap < __KeyType, __ValueType, __Hasher > >;

    public:
        __CDS_NoDiscard auto sequence () const & noexcept -> Sequence < HashMap < __KeyType, __ValueType, __Hasher > const >;

    public:
        __CDS_NoDiscard auto sequence () const && noexcept -> Sequence < HashMap < __KeyType, __ValueType, __Hasher > const >;
    };

}

#include "hashMap/KeySetProxy.hpp"
#include "hashMap/ValueMutableCollectionProxy.hpp"
#include "hashMap/EntryMutableCollectionProxy.hpp"

#include "../../../../shared/iterator/impl/HashTableIterator.hpp"
#include "../../../../shared/iterator/impl/IteratorGenericDecorator.hpp"

#include "../../../../shared/delegateIterator/impl/AbstractDelegateIterator.hpp"
#include "../../../../shared/delegateIterator/impl/DelegateIterator.hpp"

#include "../../../../shared/hashTable/impl/HashTable.hpp"

#include "../../../../shared/collectionInternalCommunication/server/impl/SetServer.hpp"
#include "../../../../shared/collectionInternalCommunication/server/impl/MapServer.hpp"
#include "../../../../shared/collectionInternalCommunication/server/impl/MapServerDispatcher.hpp"

#include "hashMap/impl/HashMap.hpp"
#include "hashMap/impl/CTAD.hpp"
#include "hashMap/impl/KeySetProxy.hpp"
#include "hashMap/impl/ValueMutableCollectionProxy.hpp"
#include "hashMap/impl/EntryMutableCollectionProxy.hpp"

#include "../../../../shared/hashMap/impl/Sequence.hpp"

#include "../../../../shared/collection/FunctionalConstructors.hpp"
#include "../../../../shared/collection/impl/FunctionalConstructors.hpp"

#endif /* __CDS_HASH_MAP_HPP__ */
