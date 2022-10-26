/*
 * Created by loghin on 27/07/22.
 */

#ifndef __CDS_LINKED_HASH_MAP_HPP__ /* NOLINT(llvm-header-guard) */
#define __CDS_LINKED_HASH_MAP_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

#include <CDS/Map>
#include <CDS/FunctionalInterface>

#include "../../../../shared/Node.hpp"
#include "../../../../shared/rehashPolicy/rehashPolicy.hpp"

#include "../../../../shared/iterator/HashTableIterator.hpp"
#include "../../../../shared/iterator/NodeIterator.hpp"                                         /* NOLINT(llvm-include-order) */
#include "../../../../shared/iterator/IteratorGenericDecorator.hpp"

#include "../../../../shared/collectionInternalCommunication/server/MapServerDispatcher.hpp"

#include "../../../../shared/delegateIterator/AbstractDelegateIterator.hpp"
#include "../../../../shared/delegateIterator/DelegateIterator.hpp"

#include "../../../../shared/hashTable/HashTable.hpp"
#include "../../../../shared/linkedList/SingleLinkedList.hpp"

#include "../../../../shared/collectionInternalCommunication/server/SetServer.hpp"              /* NOLINT(llvm-include-order) */
#include "../../../../shared/collectionInternalCommunication/server/MapServer.hpp"

#include "linkedHashMap/Constructs.hpp"

namespace cds {

    template <
            typename __KeyType,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __ValueType,   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __Hasher       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
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

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using MapBase                               = Map < __KeyType, __ValueType >;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using Server                                = __hidden :: __impl :: __LinkedHashMapServer < __KeyType, __ValueType, __Hasher >;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using HashTableImplementation               = __hidden :: __impl :: __LinkedHashMapHashTableImplementation < __KeyType, __ValueType, __Hasher >;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using LinkedListImplementation              = __hidden :: __impl :: __LinkedHashMapLinkedListImplementation < __KeyType, __ValueType, __Hasher >;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using RandomInsertionClient                 = __hidden :: __impl :: __LinkedHashMapRandomInsertionClient < __KeyType, __ValueType, __Hasher >;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using IteratorRemoveClient                  = __hidden :: __impl :: __LinkedHashMapIteratorRemoveClient < __KeyType, __ValueType, __Hasher >;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using ConstIteratorRemoveClient             = __hidden :: __impl :: __LinkedHashMapConstIteratorRemoveClient < __KeyType, __ValueType, __Hasher >;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using FindOfCollectionClient                = __hidden :: __impl :: __LinkedHashMapFindOfCollectionClient < __KeyType, __ValueType, __Hasher >;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using FindOfConstCollectionClient           = __hidden :: __impl :: __LinkedHashMapFindOfConstCollectionClient < __KeyType, __ValueType, __Hasher >;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using FindOfInitializerListClient           = __hidden :: __impl :: __LinkedHashMapFindOfInitializerListClient < __KeyType, __ValueType, __Hasher >;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using FindOfConstInitializerListClient      = __hidden :: __impl :: __LinkedHashMapFindOfConstInitializerListClient < __KeyType, __ValueType, __Hasher >;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using FindByClient                          = __hidden :: __impl :: __LinkedHashMapFindByClient < __KeyType, __ValueType, __Hasher >;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using FindByConstClient                     = __hidden :: __impl :: __LinkedHashMapFindByConstClient < __KeyType, __ValueType, __Hasher >;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using FindUniqueClient                      = __hidden :: __impl :: __LinkedHashMapFindUniqueClient < __KeyType, __ValueType, __Hasher >;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using FindUniqueConstClient                 = __hidden :: __impl :: __LinkedHashMapFindUniqueConstClient < __KeyType, __ValueType, __Hasher >;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using RemoveOfCollectionClient              = __hidden :: __impl :: __LinkedHashMapRemoveOfCollectionClient < __KeyType, __ValueType, __Hasher >;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using RemoveOfInitializerListClient         = __hidden :: __impl :: __LinkedHashMapRemoveOfInitializerListClient < __KeyType, __ValueType, __Hasher >;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using RemoveByClient                        = __hidden :: __impl :: __LinkedHashMapRemoveByClient < __KeyType, __ValueType, __Hasher >;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using GenericStatementsClient               = __hidden :: __impl :: __LinkedHashMapGenericStatementsClient < __KeyType, __ValueType, __Hasher >;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using ConstGenericStatementsClient          = __hidden :: __impl :: __LinkedHashMapConstGenericStatementsClient < __KeyType, __ValueType, __Hasher >;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using ContainsOfCollectionClient            = __hidden :: __impl :: __LinkedHashMapContainsOfCollectionClient < __KeyType, __ValueType, __Hasher >;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using ContainsOfInitializerListClient       = __hidden :: __impl :: __LinkedHashMapContainsOfInitializerListClient < __KeyType, __ValueType, __Hasher >;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using DelegateForwardIterableClient         = __hidden :: __impl :: __LinkedHashMapDelegateForwardIterableClient < __KeyType, __ValueType, __Hasher >;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using DelegateForwardConstIterableClient    = __hidden :: __impl :: __LinkedHashMapDelegateForwardConstIterableClient < __KeyType, __ValueType, __Hasher >;


    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        friend Server;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        friend RandomInsertionClient;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        friend IteratorRemoveClient;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        friend ConstIteratorRemoveClient;

    private:    /* NOLINT(readability-redundant-access-specifiers) */
        friend DelegateForwardIterableClient;

    private:    /* NOLINT(readability-redundant-access-specifiers) */
        friend DelegateForwardConstIterableClient;


    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using typename MapBase :: __GenericHandler;         /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using typename MapBase :: __GenericConstHandler;    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */


    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using typename MapBase :: AbstractMapProxy;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using typename MapBase :: AbstractKeySetProxy;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using typename MapBase :: AbstractValueMutableCollectionProxy;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using typename MapBase :: AbstractEntryMutableCollectionProxy;


    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using ElementType   = typename MapBase :: ElementType;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using EntryType     = typename MapBase :: EntryType;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using KeyType       = typename MapBase :: KeyType;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using ValueType     = typename MapBase :: ValueType;


    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using Iterator      = __hidden :: __impl :: __LinkedHashMapIterator < __KeyType, __ValueType, __Hasher >;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using ConstIterator = __hidden :: __impl :: __LinkedHashMapConstIterator < __KeyType, __ValueType, __Hasher >;


    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        class KeySetProxy;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        class ValueMutableCollectionProxy;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        class EntryMutableCollectionProxy;


    private:    /* NOLINT(readability-redundant-access-specifiers) */
        KeySetProxy                 _keySetProxy;

    private:    /* NOLINT(readability-redundant-access-specifiers) */
        ValueMutableCollectionProxy _valueMutableCollectionProxy;

    private:    /* NOLINT(readability-redundant-access-specifiers) */
        EntryMutableCollectionProxy _entryMutableCollectionProxy;


    private:    /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto __cicch_obtainGenericHandler ( /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                __hidden :: __impl :: __CollectionInternalRequestType requestType
        ) noexcept -> __GenericHandler override;

    private:    /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto __cicch_obtainGenericConstHandler (    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                __hidden :: __impl :: __CollectionInternalRequestType requestType
        ) const noexcept -> __GenericConstHandler override;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard auto __begin () noexcept -> __hidden :: __impl :: __AbstractDelegateIterator < EntryType > *;  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard auto __end () noexcept -> __hidden :: __impl :: __AbstractDelegateIterator < EntryType > *;    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction auto __beginLocal () noexcept -> Iterator;    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction auto __endLocal () noexcept -> Iterator;      /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard auto __cbegin () const noexcept -> __hidden :: __impl :: __AbstractDelegateIterator < EntryType const > *;  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard auto __cend () const noexcept -> __hidden :: __impl :: __AbstractDelegateIterator < EntryType const > *;    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard constexpr auto __cbeginLocal () const noexcept -> ConstIterator;    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard constexpr auto __cendLocal () const noexcept -> ConstIterator;      /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        auto __newAddress ( /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                EntryType const * pReferenceElement,
                bool            * pNewElementCreated
        ) noexcept -> EntryType *;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        auto __remove ( /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                Iterator const * pIterator
        ) noexcept -> bool;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        auto __removeConst ( /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                ConstIterator const * pIterator
        ) noexcept -> bool;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        auto __removeArray ( /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                Iterator    const * const * ppIterators,
                Size                        iteratorArraySize
        ) noexcept -> Size;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        auto __removeConstArray ( /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                ConstIterator   const * const * ppIterators,
                Size                            iteratorArraySize
        ) noexcept -> Size;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_MaybeUnused auto __find ( /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                __KeyType const & element
        ) noexcept -> __hidden :: __impl :: __AbstractDelegateIterator < EntryType > *;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        auto __findConst ( /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                __KeyType const & element
        ) const noexcept -> __hidden :: __impl :: __AbstractDelegateIterator < EntryType const > *;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_cpplang_NonConstConstexprMemberFunction auto __findLocal ( /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                __KeyType const & element
        ) noexcept -> Iterator;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_cpplang_ConstexprConditioned auto __findConstLocal ( /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                __KeyType const & element
        ) const noexcept -> ConstIterator;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using DelegateForwardIterableClient :: begin;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using DelegateForwardIterableClient :: end;


    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using DelegateForwardConstIterableClient :: begin;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using DelegateForwardConstIterableClient :: end;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using DelegateForwardConstIterableClient :: cbegin;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using DelegateForwardConstIterableClient :: cend;


    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using MapBase :: remove;


    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using IteratorRemoveClient :: remove;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using ConstIteratorRemoveClient :: remove;


    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using RemoveByClient :: removeThat;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using RemoveByClient :: removeFirstThat;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using RemoveByClient :: removeLastThat;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using RemoveByClient :: removeAllThat;


    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using GenericStatementsClient :: forEach;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using GenericStatementsClient :: some;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using GenericStatementsClient :: atLeast;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using GenericStatementsClient :: atMost;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using GenericStatementsClient :: moreThan;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using GenericStatementsClient :: fewerThan;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using GenericStatementsClient :: count;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using GenericStatementsClient :: any;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using GenericStatementsClient :: all;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using GenericStatementsClient :: none;


    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using ConstGenericStatementsClient :: forEach;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using ConstGenericStatementsClient :: some;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using ConstGenericStatementsClient :: atLeast;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using ConstGenericStatementsClient :: atMost;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using ConstGenericStatementsClient :: moreThan;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using ConstGenericStatementsClient :: fewerThan;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using ConstGenericStatementsClient :: count;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using ConstGenericStatementsClient :: any;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using ConstGenericStatementsClient :: all;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using ConstGenericStatementsClient :: none;


    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using RemoveOfCollectionClient :: removeOf;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using RemoveOfCollectionClient :: removeFirstOf;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using RemoveOfCollectionClient :: removeLastOf;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using RemoveOfCollectionClient :: removeAllOf;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using RemoveOfCollectionClient :: removeNotOf;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using RemoveOfCollectionClient :: removeFirstNotOf;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using RemoveOfCollectionClient :: removeLastNotOf;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using RemoveOfCollectionClient :: removeAllNotOf;


    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using RemoveOfInitializerListClient :: removeOf;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using RemoveOfInitializerListClient :: removeFirstOf;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using RemoveOfInitializerListClient :: removeLastOf;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using RemoveOfInitializerListClient :: removeAllOf;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using RemoveOfInitializerListClient :: removeNotOf;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using RemoveOfInitializerListClient :: removeFirstNotOf;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using RemoveOfInitializerListClient :: removeLastNotOf;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using RemoveOfInitializerListClient :: removeAllNotOf;


    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using ContainsOfCollectionClient :: containsAnyOf;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using ContainsOfCollectionClient :: containsAnyNotOf;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using ContainsOfCollectionClient :: containsAllOf;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using ContainsOfCollectionClient :: containsNoneOf;


    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using ContainsOfInitializerListClient :: containsAnyOf;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using ContainsOfInitializerListClient :: containsAnyNotOf;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using ContainsOfInitializerListClient :: containsAllOf;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using ContainsOfInitializerListClient :: containsNoneOf;


    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using FindByClient :: findThat;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using FindByClient :: findFirstThat;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using FindByClient :: findLastThat;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using FindByClient :: findAllThat;


    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using FindOfCollectionClient :: findOf;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using FindOfCollectionClient :: findFirstOf;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using FindOfCollectionClient :: findLastOf;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using FindOfCollectionClient :: findAllOf;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using FindOfCollectionClient :: findNotOf;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using FindOfCollectionClient :: findFirstNotOf;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using FindOfCollectionClient :: findLastNotOf;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using FindOfCollectionClient :: findAllNotOf;


    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using FindOfInitializerListClient :: findOf;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using FindOfInitializerListClient :: findFirstOf;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using FindOfInitializerListClient :: findLastOf;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using FindOfInitializerListClient :: findAllOf;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using FindOfInitializerListClient :: findNotOf;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using FindOfInitializerListClient :: findFirstNotOf;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using FindOfInitializerListClient :: findLastNotOf;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using FindOfInitializerListClient :: findAllNotOf;


    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using FindByConstClient :: findThat;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using FindByConstClient :: findFirstThat;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using FindByConstClient :: findLastThat;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using FindByConstClient :: findAllThat;


    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using FindOfConstCollectionClient :: findOf;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using FindOfConstCollectionClient :: findFirstOf;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using FindOfConstCollectionClient :: findLastOf;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using FindOfConstCollectionClient :: findAllOf;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using FindOfConstCollectionClient :: findNotOf;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using FindOfConstCollectionClient :: findFirstNotOf;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using FindOfConstCollectionClient :: findLastNotOf;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using FindOfConstCollectionClient :: findAllNotOf;


    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using FindOfConstInitializerListClient :: findOf;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using FindOfConstInitializerListClient :: findFirstOf;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using FindOfConstInitializerListClient :: findLastOf;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using FindOfConstInitializerListClient :: findAllOf;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using FindOfConstInitializerListClient :: findNotOf;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using FindOfConstInitializerListClient :: findFirstNotOf;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using FindOfConstInitializerListClient :: findLastNotOf;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using FindOfConstInitializerListClient :: findAllNotOf;


    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using RandomInsertionClient :: add;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using RandomInsertionClient :: addAll;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using RandomInsertionClient :: addAllOf;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using RandomInsertionClient :: insert;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using RandomInsertionClient :: insertAll;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using RandomInsertionClient :: insertAllOf;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using RandomInsertionClient :: emplace;


    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using FindUniqueClient :: find;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using FindUniqueConstClient :: find;


    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto keys () const noexcept -> KeySetProxy const & override;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto keys () noexcept -> KeySetProxy & override;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto values () const noexcept -> ValueMutableCollectionProxy const & override;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto values () noexcept -> ValueMutableCollectionProxy & override;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto entries () const noexcept -> EntryMutableCollectionProxy const & override;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto entries () noexcept -> EntryMutableCollectionProxy & override;


    public: /* NOLINT(readability-redundant-access-specifiers) */
        constexpr LinkedHashMap () noexcept;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        LinkedHashMap ( /* NOLINT(google-explicit-constructor) */
                LinkedHashMap const & map
        ) noexcept;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        constexpr LinkedHashMap (
                LinkedHashMap && map
        ) noexcept;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_Explicit constexpr LinkedHashMap (
                __Hasher const & hasher
        ) noexcept;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        template <
                typename __IteratorType,                    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                typename __TElementType = ElementType,      /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                cds :: meta :: EnableIf <
                        cds :: meta :: isCopyConstructible < __TElementType > ()
                > = 0
        > LinkedHashMap (
                __IteratorType const & begin,
                __IteratorType const & end,
                Size                   count = 0ULL
        ) noexcept;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        template <
                typename __IteratorType,                    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                typename __TElementType = ElementType,      /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                cds :: meta :: EnableIf <
                        cds :: meta :: isCopyConstructible < __TElementType > ()
                > = 0
        > LinkedHashMap (
                __Hasher        const & hasher,
                __IteratorType  const & begin,
                __IteratorType  const & end,
                Size                    count = 0ULL
        ) noexcept;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        template <
                typename __TElementType = ElementType,      /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                cds :: meta :: EnableIf <
                        cds :: meta :: isCopyConstructible < __TElementType > ()
                > = 0
        > LinkedHashMap (
                std :: initializer_list < ElementType > const & initializerList
        ) noexcept;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        template <
                typename __TElementType = ElementType,    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                cds :: meta :: EnableIf <
                        cds :: meta :: isCopyConstructible < __TElementType > ()
                > = 0
        > LinkedHashMap (
                __Hasher                                    const & hasher,
                std :: initializer_list < ElementType >   const & initializerList
        ) noexcept;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        template < typename __IterableType > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        __CDS_Explicit LinkedHashMap (
                __IterableType  const & iterable
        ) noexcept;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        template < typename __IterableType > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        LinkedHashMap (
                __Hasher        const & hasher,
                __IterableType  const & iterable
        ) noexcept;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        ~LinkedHashMap () noexcept override;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        auto operator = (
                LinkedHashMap const & map
        ) noexcept -> LinkedHashMap &;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        auto operator = (
                LinkedHashMap && map
        ) noexcept -> LinkedHashMap &;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        auto operator = (
                std :: initializer_list < EntryType > const & initializerList
        ) noexcept -> LinkedHashMap &;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        template < typename __IterableType > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        auto operator = (
                __IterableType const & iterable
        ) noexcept -> LinkedHashMap &;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto operator == (
                LinkedHashMap const & map
        ) const noexcept -> bool;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto operator != (
                LinkedHashMap const & map
        ) const noexcept -> bool;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        auto clear () noexcept -> void override;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto size () const noexcept -> Size override;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        auto remove (
                KeyType const & key
        ) noexcept -> bool override;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto containsKey (
                __KeyType const & key
        ) const noexcept -> bool override;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto containsValue (
                __ValueType const & value
        ) const noexcept -> bool override;

    private:    /* NOLINT(readability-redundant-access-specifiers) */
        auto entryAt (
                __KeyType const & key,
                bool            * pNewElementCreated
        ) noexcept -> EntryType * override;

    private:    /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_cpplang_ConstexprOverride auto entryAt (
                __KeyType const & key
        ) const noexcept -> EntryType const * override;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard auto sequence () & noexcept -> Sequence < LinkedHashMap < __KeyType, __ValueType, __Hasher > >;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard auto sequence () && noexcept -> Sequence < LinkedHashMap < __KeyType, __ValueType, __Hasher > >;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard auto sequence () const & noexcept -> Sequence < LinkedHashMap < __KeyType, __ValueType, __Hasher > const >;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard auto sequence () const && noexcept -> Sequence < LinkedHashMap < __KeyType, __ValueType, __Hasher > const >;
    };

} /* namespace cds */

#include "linkedHashMap/KeySetProxy.hpp"                                                            /* NOLINT(llvm-include-order) */
#include "linkedHashMap/ValueMutableCollectionProxy.hpp"
#include "linkedHashMap/EntryMutableCollectionProxy.hpp"

#include "../../../../shared/hashTable/impl/HashTable.hpp"
#include "../../../../shared/linkedList/impl/SingleLinkedList.hpp"

#include "../../../../shared/iterator/impl/HashTableIterator.hpp"
#include "../../../../shared/iterator/impl/NodeIterator.hpp"                                        /* NOLINT(llvm-include-order) */
#include "../../../../shared/iterator/impl/IteratorGenericDecorator.hpp"

#include "../../../../shared/collectionInternalCommunication/server/impl/MapServer.hpp"
#include "../../../../shared/collectionInternalCommunication/server/impl/SetServer.hpp"             /* NOLINT(llvm-include-order) */
#include "../../../../shared/collectionInternalCommunication/server/impl/MapServerDispatcher.hpp"

#include "../../../../shared/delegateIterator/impl/AbstractDelegateIterator.hpp"
#include "../../../../shared/delegateIterator/impl/DelegateIterator.hpp"

#include "../../../../shared/linkedHashMap/impl/Sequence.hpp"

#include "linkedHashMap/impl/LinkedHashMap.hpp"                                                     /* NOLINT(llvm-include-order) */
#include "linkedHashMap/impl/CTAD.hpp"
#include "linkedHashMap/impl/KeySetProxy.hpp"
#include "linkedHashMap/impl/ValueMutableCollectionProxy.hpp"
#include "linkedHashMap/impl/EntryMutableCollectionProxy.hpp"

#include "../../../../shared/collection/FunctionalConstructors.hpp"
#include "../../../../shared/collection/impl/FunctionalConstructors.hpp"

#endif /* __CDS_LINKED_HASH_MAP_HPP__ */
