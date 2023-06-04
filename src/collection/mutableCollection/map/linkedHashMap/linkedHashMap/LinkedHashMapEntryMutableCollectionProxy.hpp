// NOLINT(llvm-header-guard)
// Created by loghin on 09/10/22.
//

#ifndef __CDS_LINKED_HASH_MAP_ENTRY_MUTABLE_COLLECTION_PROXY_HPP__ // NOLINT(llvm-header-guard)
#define __CDS_LINKED_HASH_MAP_ENTRY_MUTABLE_COLLECTION_PROXY_HPP__ // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
#pragma once

namespace cds {       // NOLINT(modernize-concat-nested-namespaces)
namespace __hidden {  // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
namespace __impl {    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

template <
    typename __ServerType,                          // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __KeyType,                             // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __ValueType,                           // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __Hasher,                              // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __LinkedHashMap = cds::LinkedHashMap <__KeyType, __ValueType, __Hasher>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> class __CDS_InheritsEBOs __LinkedHashMapEntryProxyServer :               // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __MutableCollectionServer <__ServerType, typename __LinkedHashMap::EntryType> {};


template <
    typename __ServerType,                          // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __KeyType,                             // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __ValueType,                           // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __Hasher,                              // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __LinkedHashMap = cds::LinkedHashMap <__KeyType, __ValueType, __Hasher>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> class __CDS_InheritsEBOs __LinkedHashMapEntryProxyRandomInsertionClient :    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalRandomInsertionPrimitiveClient <
        __ServerType, typename __LinkedHashMap::EntryType, typename __LinkedHashMap::EntryType
    > {};


template <
    typename __ServerType,                          // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __KeyType,                             // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __ValueType,                           // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __Hasher,                              // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __LinkedHashMap = cds::LinkedHashMap <__KeyType, __ValueType, __Hasher>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> class __CDS_InheritsEBOs __LinkedHashMapEntryProxyIteratorRemoveClient : // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalIteratorRemovePrimitiveClient <
        __ServerType, typename __LinkedHashMap::EntryType, __LinkedHashMapIterator <__KeyType, __ValueType, __Hasher>
    > {};


template <
    typename __ServerType,                          // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __KeyType,                             // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __ValueType,                           // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __Hasher,                              // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __LinkedHashMap = cds::LinkedHashMap <__KeyType, __ValueType, __Hasher>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> class __CDS_InheritsEBOs __LinkedHashMapEntryProxyConstIteratorRemoveClient :    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalConstIteratorRemovePrimitiveClient <
        __ServerType, typename __LinkedHashMap::EntryType, __LinkedHashMapConstIterator <__KeyType, __ValueType, __Hasher>
    > {};


template <
    typename __ServerType,                          // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __KeyType,                             // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __ValueType,                           // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __Hasher,                              // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __LinkedHashMap = cds::LinkedHashMap <__KeyType, __ValueType, __Hasher>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> class __CDS_InheritsEBOs __LinkedHashMapEntryProxyFindOfIterableClient :     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalFindOfMutableCompositeClient <
        __ServerType, typename __LinkedHashMap::EntryType,
        __LinkedHashMapIterator <__KeyType, __ValueType, __Hasher>,
        cds::Iterable <typename __LinkedHashMap::EntryType>,
        &__iterableContains <typename __LinkedHashMap::EntryType>,
        &__iterableNotContains <typename __LinkedHashMap::EntryType>
    > {};


template <
    typename __ServerType,                          // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __KeyType,                             // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __ValueType,                           // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __Hasher,                              // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __LinkedHashMap = cds::LinkedHashMap <__KeyType, __ValueType, __Hasher>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> class __CDS_InheritsEBOs __LinkedHashMapEntryProxyFindOfConstIterableClient :    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalFindOfImmutableCompositeClient <
        __ServerType, typename __LinkedHashMap::EntryType,
        __LinkedHashMapConstIterator <__KeyType, __ValueType, __Hasher>,
        cds::Iterable <typename __LinkedHashMap::EntryType>,
        &__iterableContains <typename __LinkedHashMap::EntryType>,
        &__iterableNotContains <typename __LinkedHashMap::EntryType>
    > {};


template <
    typename __ServerType,                          // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __KeyType,                             // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __ValueType,                           // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __Hasher,                              // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __LinkedHashMap = cds::LinkedHashMap <__KeyType, __ValueType, __Hasher>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> class __CDS_InheritsEBOs __LinkedHashMapEntryProxyFindOfInitializerListClient :  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalFindOfMutableCompositeClient <
        __ServerType, typename __LinkedHashMap::EntryType,
        __LinkedHashMapIterator <__KeyType, __ValueType, __Hasher>,
        std::initializer_list <typename __LinkedHashMap::EntryType>,
        &__initializerListContains <typename __LinkedHashMap::EntryType, &cds::meta::equals <typename __LinkedHashMap::EntryType>>,
        &__initializerListNotContains <typename __LinkedHashMap::EntryType, &cds::meta::equals <typename __LinkedHashMap::EntryType>>
    > {};


template <
    typename __ServerType,                          // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __KeyType,                             // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __ValueType,                           // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __Hasher,                              // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __LinkedHashMap = cds::LinkedHashMap <__KeyType, __ValueType, __Hasher>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> class __CDS_InheritsEBOs __LinkedHashMapEntryProxyFindOfConstInitializerListClient : // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalFindOfImmutableCompositeClient <
        __ServerType,
        typename __LinkedHashMap::EntryType,
        __LinkedHashMapConstIterator <__KeyType, __ValueType, __Hasher>,
        std::initializer_list <typename __LinkedHashMap::EntryType>,
        &__initializerListContains <typename __LinkedHashMap::EntryType, &cds::meta::equals <typename __LinkedHashMap::EntryType>>,
        &__initializerListNotContains <typename __LinkedHashMap::EntryType, &cds::meta::equals <typename __LinkedHashMap::EntryType>>
    > {};


template <
    typename __ServerType,                          // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __KeyType,                             // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __ValueType,                           // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __Hasher,                              // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __LinkedHashMap = cds::LinkedHashMap <__KeyType, __ValueType, __Hasher>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> class __CDS_InheritsEBOs __LinkedHashMapEntryProxyFindByClient : // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalFindByMutableCompositeClient <
        __ServerType, typename __LinkedHashMap::EntryType,
        __LinkedHashMapIterator <__KeyType, __ValueType, __Hasher>
    > {};


template <
    typename __ServerType,                          // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __KeyType,                             // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __ValueType,                           // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __Hasher,                              // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __LinkedHashMap = cds::LinkedHashMap <__KeyType, __ValueType, __Hasher>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> class __CDS_InheritsEBOs __LinkedHashMapEntryProxyConstFindByClient :    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalFindByImmutableCompositeClient <
        __ServerType, typename __LinkedHashMap::EntryType,
        __LinkedHashMapConstIterator <__KeyType, __ValueType, __Hasher>
    > {};


template <
    typename __ServerType,                          // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __KeyType,                             // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __ValueType,                           // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __Hasher,                              // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __LinkedHashMap = cds::LinkedHashMap <__KeyType, __ValueType, __Hasher>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
>class __CDS_InheritsEBOs __LinkedHashMapEntryProxyRemoveOfIterableClient :   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalRemoveOfCompositeClient <
        __ServerType, typename __LinkedHashMap::EntryType,
        cds::Iterable <typename __LinkedHashMap::EntryType>,
        &__iterableContains <typename __LinkedHashMap::EntryType>
    > {};


template <
    typename __ServerType,                          // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __KeyType,                             // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __ValueType,                           // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __Hasher,                              // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __LinkedHashMap = cds::LinkedHashMap <__KeyType, __ValueType, __Hasher>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> class __CDS_InheritsEBOs __LinkedHashMapEntryProxyRemoveOfInitializerListClient :    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalRemoveOfCompositeClient <
        __ServerType, typename __LinkedHashMap::EntryType, std::initializer_list <typename __LinkedHashMap::EntryType>,
        &__initializerListContains <typename __LinkedHashMap::EntryType, &cds::meta::equals <typename __LinkedHashMap::EntryType>>
    > {};


template <
    typename __ServerType,                          // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __KeyType,                             // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __ValueType,                           // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __Hasher,                              // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __LinkedHashMap = cds::LinkedHashMap <__KeyType, __ValueType, __Hasher>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> class __CDS_InheritsEBOs __LinkedHashMapEntryProxyRemoveByClient :   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalRemoveByCompositeClient <__ServerType, typename __LinkedHashMap::EntryType> {};


template <
    typename __ServerType,                          // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __KeyType,                             // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __ValueType,                           // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __Hasher,                              // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __LinkedHashMap = cds::LinkedHashMap <__KeyType, __ValueType, __Hasher>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
>class __CDS_InheritsEBOs __LinkedHashMapEntryProxyGenericStatementsClient :  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalGenericMutableStatementsCompositeClient <__ServerType, typename __LinkedHashMap::EntryType> {};


template <
    typename __ServerType,                          // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __KeyType,                             // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __ValueType,                           // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __Hasher,                              // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __LinkedHashMap = cds::LinkedHashMap <__KeyType, __ValueType, __Hasher>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> class __CDS_InheritsEBOs __LinkedHashMapEntryProxyConstGenericStatementsClient : // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalGenericImmutableStatementsCompositeClient <__ServerType, typename __LinkedHashMap::EntryType> {};


template <
    typename __ServerType,                          // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __KeyType,                             // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __ValueType,                           // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __Hasher,                              // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __LinkedHashMap = cds::LinkedHashMap <__KeyType, __ValueType, __Hasher>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
>class __CDS_InheritsEBOs __LinkedHashMapEntryProxyContainsOfIterableClient : // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalContainsOfCompositeClient <
        __ServerType, typename __LinkedHashMap::EntryType,
        cds::Iterable <typename __LinkedHashMap::EntryType>,
        &__iterableContains <typename __LinkedHashMap::EntryType>
    > {};


template <
    typename __ServerType,                          // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __KeyType,                             // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __ValueType,                           // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __Hasher,                              // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __LinkedHashMap = cds::LinkedHashMap <__KeyType, __ValueType, __Hasher>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> class __CDS_InheritsEBOs __LinkedHashMapEntryProxyContainsOfInitializerListClient :  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalContainsOfCompositeClient <
        __ServerType, typename __LinkedHashMap::EntryType, std::initializer_list <typename __LinkedHashMap::EntryType>,
        &__initializerListContains <typename __LinkedHashMap::EntryType, &cds::meta::equals <typename __LinkedHashMap::EntryType>>
    > {};


template <
    typename __ServerType,                                      // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __KeyType,                                         // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __ValueType,                                       // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __Hasher                                           // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> class __CDS_InheritsEBOs __LinkedHashMapEntryProxyDelegateForwardIterableClient :    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalDelegateForwardIterablePrimitiveClient <
        __ServerType, __LinkedHashMapIterator <__KeyType, __ValueType, __Hasher>
    > {};


template <
    typename __ServerType,                                          // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __KeyType,                                             // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __ValueType,                                           // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __Hasher                                               // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> class __CDS_InheritsEBOs __LinkedHashMapEntryProxyDelegateForwardConstIterableClient :   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalDelegateForwardConstIterablePrimitiveClient <
        __ServerType, __LinkedHashMapConstIterator <__KeyType, __ValueType, __Hasher>
    > {};
} // namespace __impl
} // namespace __hidden

template <typename __KeyType, typename __ValueType, typename __Hasher>       // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs LinkedHashMap <__KeyType, __ValueType, __Hasher>::EntryMutableCollectionProxy :
    public LinkedHashMap <__KeyType, __ValueType, __Hasher>::AbstractEntryMutableCollectionProxy,
    protected __hidden::__impl::__LinkedHashMapEntryProxyServer <EntryMutableCollectionProxy, __KeyType, __ValueType, __Hasher>,
    public __hidden::__impl::__LinkedHashMapEntryProxyRandomInsertionClient <EntryMutableCollectionProxy, __KeyType, __ValueType, __Hasher>,
    public __hidden::__impl::__LinkedHashMapEntryProxyIteratorRemoveClient <EntryMutableCollectionProxy, __KeyType, __ValueType, __Hasher>,
    public __hidden::__impl::__LinkedHashMapEntryProxyConstIteratorRemoveClient <EntryMutableCollectionProxy, __KeyType, __ValueType, __Hasher>,
    public __hidden::__impl::__LinkedHashMapEntryProxyFindOfIterableClient <EntryMutableCollectionProxy, __KeyType, __ValueType, __Hasher>,
    public __hidden::__impl::__LinkedHashMapEntryProxyFindOfConstIterableClient <EntryMutableCollectionProxy, __KeyType, __ValueType, __Hasher>,
    public __hidden::__impl::__LinkedHashMapEntryProxyFindOfInitializerListClient <EntryMutableCollectionProxy, __KeyType, __ValueType, __Hasher>,
    public __hidden::__impl::__LinkedHashMapEntryProxyFindOfConstInitializerListClient <EntryMutableCollectionProxy, __KeyType, __ValueType, __Hasher>,
    public __hidden::__impl::__LinkedHashMapEntryProxyFindByClient <EntryMutableCollectionProxy, __KeyType, __ValueType, __Hasher>,
    public __hidden::__impl::__LinkedHashMapEntryProxyConstFindByClient <EntryMutableCollectionProxy, __KeyType, __ValueType, __Hasher>,
    public __hidden::__impl::__LinkedHashMapEntryProxyRemoveOfIterableClient <EntryMutableCollectionProxy, __KeyType, __ValueType, __Hasher>,
    public __hidden::__impl::__LinkedHashMapEntryProxyRemoveOfInitializerListClient <EntryMutableCollectionProxy, __KeyType, __ValueType, __Hasher>,
    public __hidden::__impl::__LinkedHashMapEntryProxyRemoveByClient <EntryMutableCollectionProxy, __KeyType, __ValueType, __Hasher>,
    public __hidden::__impl::__LinkedHashMapEntryProxyGenericStatementsClient <EntryMutableCollectionProxy, __KeyType, __ValueType, __Hasher>,
    public __hidden::__impl::__LinkedHashMapEntryProxyConstGenericStatementsClient <EntryMutableCollectionProxy, __KeyType, __ValueType, __Hasher>,
    public __hidden::__impl::__LinkedHashMapEntryProxyContainsOfIterableClient <EntryMutableCollectionProxy, __KeyType, __ValueType, __Hasher>,
    public __hidden::__impl::__LinkedHashMapEntryProxyContainsOfInitializerListClient <EntryMutableCollectionProxy, __KeyType, __ValueType, __Hasher>,
    public __hidden::__impl::__LinkedHashMapEntryProxyDelegateForwardIterableClient <EntryMutableCollectionProxy, __KeyType, __ValueType, __Hasher>,
    public __hidden::__impl::__LinkedHashMapEntryProxyDelegateForwardConstIterableClient <EntryMutableCollectionProxy, __KeyType, __ValueType, __Hasher> {
protected:
  using LinkedHashMapBase                     = LinkedHashMap <__KeyType, __ValueType, __Hasher>;
  using Server                                = __hidden::__impl::__LinkedHashMapEntryProxyServer <EntryMutableCollectionProxy, __KeyType, __ValueType, __Hasher>;
  using RandomInsertionClient                 = __hidden::__impl::__LinkedHashMapEntryProxyRandomInsertionClient <EntryMutableCollectionProxy, __KeyType, __ValueType, __Hasher>;
  using IteratorRemoveClient                  = __hidden::__impl::__LinkedHashMapEntryProxyIteratorRemoveClient <EntryMutableCollectionProxy, __KeyType, __ValueType, __Hasher>;
  using ConstIteratorRemoveClient             = __hidden::__impl::__LinkedHashMapEntryProxyConstIteratorRemoveClient <EntryMutableCollectionProxy, __KeyType, __ValueType, __Hasher>;
  using FindOfIterableClient                  = __hidden::__impl::__LinkedHashMapEntryProxyFindOfIterableClient <EntryMutableCollectionProxy, __KeyType, __ValueType, __Hasher>;
  using ConstFindOfIterableClient             = __hidden::__impl::__LinkedHashMapEntryProxyFindOfConstIterableClient <EntryMutableCollectionProxy, __KeyType, __ValueType, __Hasher>;
  using FindOfInitializerListClient           = __hidden::__impl::__LinkedHashMapEntryProxyFindOfInitializerListClient <EntryMutableCollectionProxy, __KeyType, __ValueType, __Hasher>;
  using ConstFindOfInitializerListClient      = __hidden::__impl::__LinkedHashMapEntryProxyFindOfConstInitializerListClient <EntryMutableCollectionProxy, __KeyType, __ValueType, __Hasher>;
  using FindByClient                          = __hidden::__impl::__LinkedHashMapEntryProxyFindByClient <EntryMutableCollectionProxy, __KeyType, __ValueType, __Hasher>;
  using ConstFindByClient                     = __hidden::__impl::__LinkedHashMapEntryProxyConstFindByClient <EntryMutableCollectionProxy, __KeyType, __ValueType, __Hasher>;
  using RemoveOfIterableClient                = __hidden::__impl::__LinkedHashMapEntryProxyRemoveOfIterableClient <EntryMutableCollectionProxy, __KeyType, __ValueType, __Hasher>;
  using RemoveOfInitializerListClient         = __hidden::__impl::__LinkedHashMapEntryProxyRemoveOfInitializerListClient <EntryMutableCollectionProxy, __KeyType, __ValueType, __Hasher>;
  using RemoveByClient                        = __hidden::__impl::__LinkedHashMapEntryProxyRemoveByClient <EntryMutableCollectionProxy, __KeyType, __ValueType, __Hasher>;
  using GenericStatementsClient               = __hidden::__impl::__LinkedHashMapEntryProxyGenericStatementsClient <EntryMutableCollectionProxy, __KeyType, __ValueType, __Hasher>;
  using ContainsOfIterableClient              = __hidden::__impl::__LinkedHashMapEntryProxyContainsOfIterableClient <EntryMutableCollectionProxy, __KeyType, __ValueType, __Hasher>;
  using ContainsOfInitializerListClient       = __hidden::__impl::__LinkedHashMapEntryProxyContainsOfInitializerListClient <EntryMutableCollectionProxy, __KeyType, __ValueType, __Hasher>;
  using ConstGenericStatementsClient          = __hidden::__impl::__LinkedHashMapEntryProxyConstGenericStatementsClient <EntryMutableCollectionProxy, __KeyType, __ValueType, __Hasher>;
  using DelegateForwardIterableClient         = __hidden::__impl::__LinkedHashMapEntryProxyDelegateForwardIterableClient <EntryMutableCollectionProxy, __KeyType, __ValueType, __Hasher>;
  using DelegateForwardConstIterableClient    = __hidden::__impl::__LinkedHashMapEntryProxyDelegateForwardConstIterableClient <EntryMutableCollectionProxy, __KeyType, __ValueType, __Hasher>;

public:
  using EntryType     = typename cds::Map < __KeyType, __ValueType >::EntryType;

  using typename DelegateForwardIterableClient::Iterator;
  using typename DelegateForwardConstIterableClient::ConstIterator;

  using DelegateForwardIterableClient::begin;
  using DelegateForwardIterableClient::end;

  using DelegateForwardConstIterableClient::begin;
  using DelegateForwardConstIterableClient::end;
  using DelegateForwardConstIterableClient::cbegin;
  using DelegateForwardConstIterableClient::cend;

  using RemoveByClient::removeThat;
  using RemoveByClient::removeFirstThat;
  using RemoveByClient::removeLastThat;
  using RemoveByClient::removeAllThat;

  using GenericStatementsClient::forEach;
  using GenericStatementsClient::some;
  using GenericStatementsClient::atLeast;
  using GenericStatementsClient::atMost;
  using GenericStatementsClient::moreThan;
  using GenericStatementsClient::fewerThan;
  using GenericStatementsClient::count;
  using GenericStatementsClient::any;
  using GenericStatementsClient::all;
  using GenericStatementsClient::none;

  using ConstGenericStatementsClient::forEach;
  using ConstGenericStatementsClient::some;
  using ConstGenericStatementsClient::atLeast;
  using ConstGenericStatementsClient::atMost;
  using ConstGenericStatementsClient::moreThan;
  using ConstGenericStatementsClient::fewerThan;
  using ConstGenericStatementsClient::count;
  using ConstGenericStatementsClient::any;
  using ConstGenericStatementsClient::all;
  using ConstGenericStatementsClient::none;

  using RemoveOfIterableClient::removeOf;
  using RemoveOfIterableClient::removeFirstOf;
  using RemoveOfIterableClient::removeLastOf;
  using RemoveOfIterableClient::removeAllOf;
  using RemoveOfIterableClient::removeNotOf;
  using RemoveOfIterableClient::removeFirstNotOf;
  using RemoveOfIterableClient::removeLastNotOf;
  using RemoveOfIterableClient::removeAllNotOf;

  using RemoveOfInitializerListClient::removeOf;
  using RemoveOfInitializerListClient::removeFirstOf;
  using RemoveOfInitializerListClient::removeLastOf;
  using RemoveOfInitializerListClient::removeAllOf;
  using RemoveOfInitializerListClient::removeNotOf;
  using RemoveOfInitializerListClient::removeFirstNotOf;
  using RemoveOfInitializerListClient::removeLastNotOf;
  using RemoveOfInitializerListClient::removeAllNotOf;

  using ContainsOfIterableClient::containsAnyOf;
  using ContainsOfIterableClient::containsAnyNotOf;
  using ContainsOfIterableClient::containsAllOf;
  using ContainsOfIterableClient::containsNoneOf;

  using ContainsOfInitializerListClient::containsAnyOf;
  using ContainsOfInitializerListClient::containsAnyNotOf;
  using ContainsOfInitializerListClient::containsAllOf;
  using ContainsOfInitializerListClient::containsNoneOf;

  using FindByClient::findThat;
  using FindByClient::findFirstThat;
  using FindByClient::findLastThat;
  using FindByClient::findAllThat;

  using FindOfIterableClient::findOf;
  using FindOfIterableClient::findFirstOf;
  using FindOfIterableClient::findLastOf;
  using FindOfIterableClient::findAllOf;
  using FindOfIterableClient::findNotOf;
  using FindOfIterableClient::findFirstNotOf;
  using FindOfIterableClient::findLastNotOf;
  using FindOfIterableClient::findAllNotOf;

  using FindOfInitializerListClient::findOf;
  using FindOfInitializerListClient::findFirstOf;
  using FindOfInitializerListClient::findLastOf;
  using FindOfInitializerListClient::findAllOf;
  using FindOfInitializerListClient::findNotOf;
  using FindOfInitializerListClient::findFirstNotOf;
  using FindOfInitializerListClient::findLastNotOf;
  using FindOfInitializerListClient::findAllNotOf;

  using ConstFindByClient::findThat;
  using ConstFindByClient::findFirstThat;
  using ConstFindByClient::findLastThat;
  using ConstFindByClient::findAllThat;

  using ConstFindOfIterableClient::findOf;
  using ConstFindOfIterableClient::findFirstOf;
  using ConstFindOfIterableClient::findLastOf;
  using ConstFindOfIterableClient::findAllOf;
  using ConstFindOfIterableClient::findNotOf;
  using ConstFindOfIterableClient::findFirstNotOf;
  using ConstFindOfIterableClient::findLastNotOf;
  using ConstFindOfIterableClient::findAllNotOf;

  using ConstFindOfInitializerListClient::findOf;
  using ConstFindOfInitializerListClient::findFirstOf;
  using ConstFindOfInitializerListClient::findLastOf;
  using ConstFindOfInitializerListClient::findAllOf;
  using ConstFindOfInitializerListClient::findNotOf;
  using ConstFindOfInitializerListClient::findFirstNotOf;
  using ConstFindOfInitializerListClient::findLastNotOf;
  using ConstFindOfInitializerListClient::findAllNotOf;

  using RandomInsertionClient::add;
  using RandomInsertionClient::addAll;
  using RandomInsertionClient::addAllOf;
  using RandomInsertionClient::insert;
  using RandomInsertionClient::insertAll;
  using RandomInsertionClient::insertAllOf;
  using RandomInsertionClient::emplace;

  using IteratorRemoveClient::remove;
  using ConstIteratorRemoveClient::remove;

  __CDS_Explicit constexpr EntryMutableCollectionProxy (LinkedHashMap <__KeyType, __ValueType, __Hasher>* pMap) noexcept;
  EntryMutableCollectionProxy (EntryMutableCollectionProxy const&) noexcept = delete;
  EntryMutableCollectionProxy (EntryMutableCollectionProxy&&) noexcept = delete;
  __CDS_cpplang_ConstexprDestructor ~EntryMutableCollectionProxy() noexcept override;
  auto operator = (EntryMutableCollectionProxy const&) noexcept -> EntryMutableCollectionProxy& = delete;
  auto operator = (EntryMutableCollectionProxy&&) noexcept -> EntryMutableCollectionProxy& = delete;

  __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto contains ( // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      EntryType const& entry
  ) const noexcept -> bool override;

  __CDS_NoDiscard auto operator == (
      EntryMutableCollectionProxy const& set
  ) const noexcept -> bool;

  __CDS_NoDiscard auto operator != (
      EntryMutableCollectionProxy const& set
  ) const noexcept -> bool;

private:
  using typename AbstractEntryMutableCollectionProxy::__GenericHandler;         // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  using typename AbstractEntryMutableCollectionProxy::__GenericConstHandler;    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

  friend __hidden::__impl::__MutableCollectionServer <EntryMutableCollectionProxy, EntryType>;
  friend __hidden::__impl::__LocalDelegateForwardIterablePrimitiveClient <EntryMutableCollectionProxy, Iterator>;
  friend __hidden::__impl::__LocalDelegateForwardConstIterablePrimitiveClient <EntryMutableCollectionProxy, ConstIterator>;

  using Server::__mcs_handlers;       // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  using Server::__mcs_constHandlers;  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

  using AbstractMapProxy::map;

  __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto __iicch_obtainGenericHandler ( // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      __hidden::__impl::__IterableInternalRequestType requestType
  ) noexcept -> __GenericHandler override;

  __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto __iicch_obtainGenericConstHandler (    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      __hidden::__impl::__IterableInternalRequestType requestType
  ) const noexcept -> __GenericConstHandler override;

  static auto __newAddress ( // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      EntryMutableCollectionProxy*  pObject,
      EntryType const*              pReferenceElement,
      bool*                         pIsNew
  ) noexcept -> EntryType*;

  __CDS_NoDiscard static auto __begin (  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      EntryMutableCollectionProxy* pObject
  ) noexcept -> __hidden::__impl::__AbstractDelegateIterator <EntryType>*;

  __CDS_NoDiscard static auto __end (  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      EntryMutableCollectionProxy* pObject
  ) noexcept -> __hidden::__impl::__AbstractDelegateIterator <EntryType>*;

  __CDS_NoDiscard static auto __cbegin (   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      EntryMutableCollectionProxy const* pObject
  ) noexcept -> __hidden::__impl::__AbstractDelegateIterator <EntryType const>*;

  __CDS_NoDiscard static auto __cend (   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      EntryMutableCollectionProxy const* pObject
  ) noexcept -> __hidden::__impl::__AbstractDelegateIterator <EntryType const>*;

  __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction static auto __beginLocal (   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      EntryMutableCollectionProxy* pObject
  ) noexcept -> Iterator;

  __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction static auto __endLocal (   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      EntryMutableCollectionProxy* pObject
  ) noexcept -> Iterator;

  __CDS_NoDiscard constexpr static auto __cbeginLocal (  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      EntryMutableCollectionProxy const* pObject
  ) noexcept -> ConstIterator;

  __CDS_NoDiscard constexpr static auto __cendLocal (  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      EntryMutableCollectionProxy const* pObject
  ) noexcept -> ConstIterator;

  static auto __remove ( // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      EntryMutableCollectionProxy*  pObject,
      Iterator const*               iterator
  ) noexcept -> bool;

  static auto __removeConst (    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      EntryMutableCollectionProxy*  pObject,
      ConstIterator const*          iterator
  ) noexcept -> bool;

  static auto __removeArray ( // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      EntryMutableCollectionProxy*  pObject,
      Iterator const* const*        ppIterators,
      Size                          iteratorArrayCount
  ) noexcept -> Size;

  static auto __removeConstArray (    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      EntryMutableCollectionProxy*  pObject,
      ConstIterator const* const*   ppIterators,
      Size                          iteratorArrayCount
  ) noexcept -> Size;

  __CDS_NoDiscard auto __equals ( // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      EntryMutableCollectionProxy const& set
  ) const noexcept -> bool;
};

} // namespace cds

#endif // __CDS_LINKED_HASH_MAP_ENTRY_MUTABLE_COLLECTION_PROXY_HPP__
