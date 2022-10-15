/*
 * Created by loghin on 27/07/22.
 */

#ifndef __CDS_LINKED_HASH_MAP_HPP__
#define __CDS_LINKED_HASH_MAP_HPP__ /* NOLINT(bugprone-reserved-identifier) */

#include <CDS/Map>

#include <CDS/Comparator>
#include <CDS/Extractor>
#include <CDS/Hasher>
#include <CDS/Destructor>
#include <CDS/CopyConstructor>

#include "../../../../shared/Node.hpp"
#include "../../../../shared/rehashPolicy/rehashPolicy.hpp"

#include "../../../../shared/iterator/HashTableIterator.hpp"
#include "../../../../shared/iterator/NodeIterator.hpp"
#include "../../../../shared/iterator/IteratorGenericDecorator.hpp"

#include "../../../../shared/collectionInternalCommunication/server/MapServerDispatcher.hpp"

#include "../../../../shared/delegateIterator/AbstractDelegateIterator.hpp"
#include "../../../../shared/delegateIterator/DelegateIterator.hpp"

#include "../../../../shared/hashTable/HashTable.hpp"
#include "../../../../shared/linkedList/SingleLinkedList.hpp"

#include "../../../../shared/collectionInternalCommunication/server/SetServer.hpp"
#include "../../../../shared/collectionInternalCommunication/server/MapServer.hpp"

#include "linkedHashMap/Constructs.hpp"

namespace cds {

    template <
            typename __KeyType,     /* NOLINT(bugprone-reserved-identifier) */
            typename __ValueType,   /* NOLINT(bugprone-reserved-identifier) */
            typename __Hasher       /* NOLINT(bugprone-reserved-identifier) */
    > class LinkedHashMap :
            public Map < __KeyType, __ValueType >,
            protected __hidden :: __impl :: __LinkedHashMapServer < __KeyType, __ValueType, __Hasher >,
            public __hidden :: __impl :: __LinkedHashMapHashTableImplementation < __KeyType, __ValueType, __Hasher >,
            public __hidden :: __impl :: __LinkedHashMapLinkedListImplementation < __KeyType, __ValueType, __Hasher >,
            public __hidden :: __impl :: __LinkedHashMapRandomInsertionClient < __KeyType, __ValueType, __Hasher >,
            public __hidden :: __impl :: __LinkedHashMapIteratorRemoveClient < __KeyType, __ValueType, __Hasher >,
            public __hidden :: __impl :: __LinkedHashMapConstIteratorRemoveClient < __KeyType, __ValueType, __Hasher >,
            public __hidden :: __impl :: __LinkedHashMapFindOfCollectionClient < __KeyType, __ValueType, __Hasher >,
            public __hidden :: __impl :: __LinkedHashMapFindOfConstCollectionClient < __KeyType, __ValueType, __Hasher >,
            public __hidden :: __impl :: __LinkedHashMapFindOfInitializerListClient < __KeyType, __ValueType, __Hasher >,
            public __hidden :: __impl :: __LinkedHashMapFindOfConstInitializerListClient < __KeyType, __ValueType, __Hasher >,
            public __hidden :: __impl :: __LinkedHashMapFindByClient < __KeyType, __ValueType, __Hasher >,
            public __hidden :: __impl :: __LinkedHashMapFindByConstClient < __KeyType, __ValueType, __Hasher >,
            public __hidden :: __impl :: __LinkedHashMapFindUniqueClient < __KeyType, __ValueType, __Hasher >,
            public __hidden :: __impl :: __LinkedHashMapFindUniqueConstClient < __KeyType, __ValueType, __Hasher >,
            public __hidden :: __impl :: __LinkedHashMapRemoveOfCollectionClient < __KeyType, __ValueType, __Hasher >,
            public __hidden :: __impl :: __LinkedHashMapRemoveOfInitializerListClient < __KeyType, __ValueType, __Hasher >,
            public __hidden :: __impl :: __LinkedHashMapRemoveByClient < __KeyType, __ValueType, __Hasher >,
            public __hidden :: __impl :: __LinkedHashMapGenericStatementsClient < __KeyType, __ValueType, __Hasher >,
            public __hidden :: __impl :: __LinkedHashMapConstGenericStatementsClient < __KeyType, __ValueType, __Hasher >,
            public __hidden :: __impl :: __LinkedHashMapContainsOfCollectionClient < __KeyType, __ValueType, __Hasher >,
            public __hidden :: __impl :: __LinkedHashMapContainsOfInitializerListClient < __KeyType, __ValueType, __Hasher >,
            public __hidden :: __impl :: __LinkedHashMapDelegateForwardIterableClient < __KeyType, __ValueType, __Hasher >,
            public __hidden :: __impl :: __LinkedHashMapDelegateForwardConstIterableClient < __KeyType, __ValueType, __Hasher > {

    protected:  using MapBase                               = Map < __KeyType, __ValueType >;
    protected:  using Server                                = __hidden :: __impl :: __LinkedHashMapServer < __KeyType, __ValueType, __Hasher >;
    protected:  using HashTableImplementation               = __hidden :: __impl :: __LinkedHashMapHashTableImplementation < __KeyType, __ValueType, __Hasher >;
    protected:  using LinkedListImplementation              = __hidden :: __impl :: __LinkedHashMapLinkedListImplementation < __KeyType, __ValueType, __Hasher >;
    protected:  using RandomInsertionClient                 = __hidden :: __impl :: __LinkedHashMapRandomInsertionClient < __KeyType, __ValueType, __Hasher >;
    protected:  using IteratorRemoveClient                  = __hidden :: __impl :: __LinkedHashMapIteratorRemoveClient < __KeyType, __ValueType, __Hasher >;
    protected:  using ConstIteratorRemoveClient             = __hidden :: __impl :: __LinkedHashMapConstIteratorRemoveClient < __KeyType, __ValueType, __Hasher >;
    protected:  using FindOfCollectionClient                = __hidden :: __impl :: __LinkedHashMapFindOfCollectionClient < __KeyType, __ValueType, __Hasher >;
    protected:  using FindOfConstCollectionClient           = __hidden :: __impl :: __LinkedHashMapFindOfConstCollectionClient < __KeyType, __ValueType, __Hasher >;
    protected:  using FindOfInitializerListClient           = __hidden :: __impl :: __LinkedHashMapFindOfInitializerListClient < __KeyType, __ValueType, __Hasher >;
    protected:  using FindOfConstInitializerListClient      = __hidden :: __impl :: __LinkedHashMapFindOfConstInitializerListClient < __KeyType, __ValueType, __Hasher >;
    protected:  using FindByClient                          = __hidden :: __impl :: __LinkedHashMapFindByClient < __KeyType, __ValueType, __Hasher >;
    protected:  using FindByConstClient                     = __hidden :: __impl :: __LinkedHashMapFindByConstClient < __KeyType, __ValueType, __Hasher >;
    protected:  using FindUniqueClient                      = __hidden :: __impl :: __LinkedHashMapFindUniqueClient < __KeyType, __ValueType, __Hasher >;
    protected:  using FindUniqueConstClient                 = __hidden :: __impl :: __LinkedHashMapFindUniqueConstClient < __KeyType, __ValueType, __Hasher >;
    protected:  using RemoveOfCollectionClient              = __hidden :: __impl :: __LinkedHashMapRemoveOfCollectionClient < __KeyType, __ValueType, __Hasher >;
    protected:  using RemoveOfInitializerListClient         = __hidden :: __impl :: __LinkedHashMapRemoveOfInitializerListClient < __KeyType, __ValueType, __Hasher >;
    protected:  using RemoveByClient                        = __hidden :: __impl :: __LinkedHashMapRemoveByClient < __KeyType, __ValueType, __Hasher >;
    protected:  using GenericStatementsClient               = __hidden :: __impl :: __LinkedHashMapGenericStatementsClient < __KeyType, __ValueType, __Hasher >;
    protected:  using ConstGenericStatementsClient          = __hidden :: __impl :: __LinkedHashMapConstGenericStatementsClient < __KeyType, __ValueType, __Hasher >;
    protected:  using ContainsOfCollectionClient            = __hidden :: __impl :: __LinkedHashMapContainsOfCollectionClient < __KeyType, __ValueType, __Hasher >;
    protected:  using ContainsOfInitializerListClient       = __hidden :: __impl :: __LinkedHashMapContainsOfInitializerListClient < __KeyType, __ValueType, __Hasher >;
    protected:  using DelegateForwardIterableClient         = __hidden :: __impl :: __LinkedHashMapDelegateForwardIterableClient < __KeyType, __ValueType, __Hasher >;
    protected:  using DelegateForwardConstIterableClient    = __hidden :: __impl :: __LinkedHashMapDelegateForwardConstIterableClient < __KeyType, __ValueType, __Hasher >;

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

    public:     using ElementType   = typename MapBase :: ElementType;
    public:     using EntryType     = typename MapBase :: EntryType;
    public:     using KeyType       = typename MapBase :: KeyType;
    public:     using ValueType     = typename MapBase :: ValueType;

    public:     using Iterator      = __hidden :: __impl :: __LinkedHashMapIterator < __KeyType, __ValueType, __Hasher >;
    public:     using ConstIterator = __hidden :: __impl :: __LinkedHashMapConstIterator < __KeyType, __ValueType, __Hasher >;

    protected:  class KeySetProxy;
    protected:  class ValueMutableCollectionProxy;
    protected:  class EntryMutableCollectionProxy;

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

    protected:
        __CDS_NoDiscard auto __begin () noexcept -> __hidden :: __impl :: __AbstractDelegateIterator < EntryType > *;  /* NOLINT(bugprone-reserved-identifier) */

    protected:
        __CDS_NoDiscard auto __end () noexcept -> __hidden :: __impl :: __AbstractDelegateIterator < EntryType > *;    /* NOLINT(bugprone-reserved-identifier) */

    protected:
        __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction auto __beginLocal () noexcept -> Iterator;    /* NOLINT(bugprone-reserved-identifier) */

    protected:
        __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction auto __endLocal () noexcept -> Iterator;      /* NOLINT(bugprone-reserved-identifier) */

    protected:
        __CDS_NoDiscard auto __cbegin () const noexcept -> __hidden :: __impl :: __AbstractDelegateIterator < EntryType const > *;  /* NOLINT(bugprone-reserved-identifier) */

    protected:
        __CDS_NoDiscard auto __cend () const noexcept -> __hidden :: __impl :: __AbstractDelegateIterator < EntryType const > *;    /* NOLINT(bugprone-reserved-identifier) */

    protected:
        __CDS_NoDiscard constexpr auto __cbeginLocal () const noexcept -> ConstIterator;    /* NOLINT(bugprone-reserved-identifier) */

    protected:
        __CDS_NoDiscard constexpr auto __cendLocal () const noexcept -> ConstIterator;      /* NOLINT(bugprone-reserved-identifier) */

    protected:
        auto __newAddress ( /* NOLINT(bugprone-reserved-identifier) */
                EntryType const * pReferenceElement,
                bool            * pNewElementCreated
        ) noexcept -> EntryType *;

    protected:
        auto __remove ( /* NOLINT(bugprone-reserved-identifier) */
                Iterator const * pIterator
        ) noexcept -> bool;

    protected:
        auto __removeConst ( /* NOLINT(bugprone-reserved-identifier) */
                ConstIterator const * pIterator
        ) noexcept -> bool;

    protected:
        auto __removeArray ( /* NOLINT(bugprone-reserved-identifier) */
                Iterator    const * const * ppIterators,
                Size                        iteratorArraySize
        ) noexcept -> Size;

    protected:
        auto __removeConstArray ( /* NOLINT(bugprone-reserved-identifier) */
                ConstIterator   const * const * ppIterators,
                Size                            iteratorArraySize
        ) noexcept -> Size;

    protected:
        auto __find ( /* NOLINT(bugprone-reserved-identifier) */
                __KeyType const & element
        ) noexcept -> __hidden :: __impl :: __AbstractDelegateIterator < EntryType > *;

    protected:
        auto __findConst ( /* NOLINT(bugprone-reserved-identifier) */
                __KeyType const & element
        ) const noexcept -> __hidden :: __impl :: __AbstractDelegateIterator < EntryType const > *;

    protected:
        __CDS_cpplang_NonConstConstexprMemberFunction auto __findLocal ( /* NOLINT(bugprone-reserved-identifier) */
                __KeyType const & element
        ) noexcept -> Iterator;

    protected:
        __CDS_cpplang_ConstexprConditioned auto __findConstLocal ( /* NOLINT(bugprone-reserved-identifier) */
                __KeyType const & element
        ) const noexcept -> ConstIterator;

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
        __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto keys () const noexcept -> KeySetProxy const & override;

    protected:
        __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto keys () noexcept -> KeySetProxy & override;

    protected:
        __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto values () const noexcept -> ValueMutableCollectionProxy const & override;

    protected:
        __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto values () noexcept -> ValueMutableCollectionProxy & override;

    protected:
        __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto entries () const noexcept -> EntryMutableCollectionProxy const & override;

    protected:
        __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto entries () noexcept -> EntryMutableCollectionProxy & override;


    public:
        constexpr LinkedHashMap () noexcept;

    public:
        LinkedHashMap ( /* NOLINT(google-explicit-constructor) */
                LinkedHashMap const & map
        ) noexcept;

    public:
        constexpr LinkedHashMap (
                LinkedHashMap && map
        ) noexcept;

    public:
        __CDS_Explicit constexpr LinkedHashMap (
                __Hasher const & hasher
        ) noexcept;

    public:
        template <
                typename __IteratorType,                    /* NOLINT(bugprone-reserved-identifier) */
                typename __TElementType = ElementType,      /* NOLINT(bugprone-reserved-identifier) */
                cds :: meta :: EnableIf <
                        cds :: meta :: isCopyConstructible < __TElementType > ()
                > = 0
        > LinkedHashMap (
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
        > LinkedHashMap (
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
        > LinkedHashMap (
                std :: initializer_list < ElementType > const & initializerList
        ) noexcept;

    public:
        template <
                typename __TElementType = ElementType,    /* NOLINT(bugprone-reserved-identifier) */
                cds :: meta :: EnableIf <
                        cds :: meta :: isCopyConstructible < __TElementType > ()
                > = 0
        > LinkedHashMap (
                __Hasher                                    const & hasher,
                std :: initializer_list < ElementType >   const & initializerList
        ) noexcept;

    public:
        template < typename __IterableType > /* NOLINT(bugprone-reserved-identifier) */
        __CDS_Explicit LinkedHashMap (
                __IterableType  const & iterable
        ) noexcept;

    public:
        template < typename __IterableType > /* NOLINT(bugprone-reserved-identifier) */
        LinkedHashMap (
                __Hasher        const & hasher,
                __IterableType  const & iterable
        ) noexcept;

    public:
        ~LinkedHashMap () noexcept override;

    public:
        auto operator = (
                LinkedHashMap const & map
        ) noexcept -> LinkedHashMap &;

    public:
        auto operator = (
                LinkedHashMap && map
        ) noexcept -> LinkedHashMap &;

    public:
        auto operator = (
                std :: initializer_list < EntryType > const & initializerList
        ) noexcept -> LinkedHashMap &;

    public:
        template < typename __IterableType > /* NOLINT(bugprone-reserved-identifier) */
        auto operator = (
                __IterableType const & iterable
        ) noexcept -> LinkedHashMap &;

    public:
        __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto operator == (
                LinkedHashMap const & map
        ) const noexcept -> bool;

    public:
        __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto operator != (
                LinkedHashMap const & map
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
        __CDS_NoDiscard auto sequence () & noexcept -> Sequence < LinkedHashMap < __KeyType, __ValueType, __Hasher > >;

    public:
        __CDS_NoDiscard auto sequence () && noexcept -> Sequence < LinkedHashMap < __KeyType, __ValueType, __Hasher > >;

    public:
        __CDS_NoDiscard auto sequence () const & noexcept -> Sequence < LinkedHashMap < __KeyType, __ValueType, __Hasher > const >;

    public:
        __CDS_NoDiscard auto sequence () const && noexcept -> Sequence < LinkedHashMap < __KeyType, __ValueType, __Hasher > const >;
    };
}

#include "linkedHashMap/KeySetProxy.hpp"
#include "linkedHashMap/ValueMutableCollectionProxy.hpp"
#include "linkedHashMap/EntryMutableCollectionProxy.hpp"

#include "../../../../shared/hashTable/impl/HashTable.hpp"
#include "../../../../shared/linkedList/impl/SingleLinkedList.hpp"

#include "../../../../shared/iterator/impl/HashTableIterator.hpp"
#include "../../../../shared/iterator/impl/NodeIterator.hpp"
#include "../../../../shared/iterator/impl/IteratorGenericDecorator.hpp"

#include "../../../../shared/collectionInternalCommunication/server/impl/MapServer.hpp"
#include "../../../../shared/collectionInternalCommunication/server/impl/SetServer.hpp"
#include "../../../../shared/collectionInternalCommunication/server/impl/MapServerDispatcher.hpp"

#include "../../../../shared/delegateIterator/impl/AbstractDelegateIterator.hpp"
#include "../../../../shared/delegateIterator/impl/DelegateIterator.hpp"

#include "../../../../shared/linkedHashMap/impl/Sequence.hpp"

#include "linkedHashMap/impl/LinkedHashMap.hpp"
#include "linkedHashMap/impl/CTAD.hpp"
#include "linkedHashMap/impl/KeySetProxy.hpp"
#include "linkedHashMap/impl/ValueMutableCollectionProxy.hpp"
#include "linkedHashMap/impl/EntryMutableCollectionProxy.hpp"

#include "../../../../shared/collection/FunctionalConstructors.hpp"
#include "../../../../shared/collection/impl/FunctionalConstructors.hpp"

#endif /* __CDS_LINKED_HASH_MAP_HPP__ */
