// NOLINT(llvm-header-guard)
// Created by loghin on 14/08/22.
//

#ifndef __CDS_HASH_MAP_ENTRY_MUTABLE_COLLECTION_PROXY_HPP__ // NOLINT(llvm-header-guard)
#define __CDS_HASH_MAP_ENTRY_MUTABLE_COLLECTION_PROXY_HPP__ // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
#pragma once

namespace cds {
namespace __hidden {    // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
namespace __impl {  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

template <
    typename __ServerType,                      // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __KeyType,                         // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __ValueType,                       // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __Hasher,                          // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __HashMap = HashMap <__KeyType, __ValueType, __Hasher> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> class __CDS_InheritsEBOs __HashMapEntryProxyServer :                 // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __MutableCollectionServer <__ServerType, typename __HashMap::EntryType> {};


template <
    typename __ServerType,                      // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __KeyType,                         // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __ValueType,                       // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __Hasher,                          // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __HashMap = HashMap <__KeyType, __ValueType, __Hasher> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> class __CDS_InheritsEBOs __HashMapEntryProxyRandomInsertionClient :  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalRandomInsertionPrimitiveClient <
        __ServerType, typename __HashMap::EntryType, typename __HashMap::EntryType
    > {};


template <
    typename __ServerType,                      // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __KeyType,                         // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __ValueType,                       // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __Hasher,                          // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __HashMap = HashMap <__KeyType, __ValueType, __Hasher> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> class __CDS_InheritsEBOs __HashMapEntryProxyIteratorRemoveClient :   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalIteratorRemovePrimitiveClient <
        __ServerType, typename __HashMap::EntryType,
        typename __HashMapImplementation <__KeyType, __ValueType, __Hasher>::__ht_Iterator
    > {};


template <
    typename __ServerType,                      // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __KeyType,                         // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __ValueType,                       // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __Hasher,                          // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __HashMap = HashMap <__KeyType, __ValueType, __Hasher> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> class __CDS_InheritsEBOs __HashMapEntryProxyConstIteratorRemoveClient :  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalConstIteratorRemovePrimitiveClient <
        __ServerType, typename __HashMap::EntryType,
        typename __HashMapImplementation <__KeyType, __ValueType, __Hasher>::__ht_ConstIterator
    > {};


template <
    typename __ServerType,                      // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __KeyType,                         // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __ValueType,                       // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __Hasher,                          // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __HashMap = HashMap <__KeyType, __ValueType, __Hasher> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> class __CDS_InheritsEBOs __HashMapEntryProxyFindOfIterableClient :   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalFindOfMutableCompositeClient <
        __ServerType, typename __HashMap::EntryType,
        typename __HashMapImplementation <__KeyType, __ValueType, __Hasher>::__ht_Iterator,
        cds::Iterable <typename __HashMap::EntryType>,
        &__iterableContains <typename __HashMap::EntryType>,
        &__iterableNotContains <typename __HashMap::EntryType>
    > {};


template <
    typename __ServerType,                      // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __KeyType,                         // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __ValueType,                       // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __Hasher,                          // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __HashMap = HashMap <__KeyType, __ValueType, __Hasher> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> class __CDS_InheritsEBOs __HashMapEntryProxyFindOfConstIterableClient :  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalFindOfImmutableCompositeClient <
        __ServerType, typename __HashMap::EntryType,
        typename __HashMapImplementation <__KeyType, __ValueType, __Hasher>::__ht_ConstIterator,
        cds::Iterable <typename __HashMap::EntryType>,
        &__iterableContains <typename __HashMap::EntryType>,
        &__iterableNotContains <typename __HashMap::EntryType>
    > {};


template <
    typename __ServerType,                      // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __KeyType,                         // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __ValueType,                       // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __Hasher,                          // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __HashMap = HashMap <__KeyType, __ValueType, __Hasher> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> class __CDS_InheritsEBOs __HashMapEntryProxyFindOfInitializerListClient :    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalFindOfMutableCompositeClient <
        __ServerType, typename __HashMap::EntryType,
        typename __HashMapImplementation <__KeyType, __ValueType, __Hasher>::__ht_Iterator,
        std::initializer_list <typename __HashMap::EntryType>,
        &__initializerListContains <typename __HashMap::EntryType, &cds::meta::equals <typename __HashMap::EntryType>>,
        &__initializerListNotContains <typename __HashMap::EntryType, &cds::meta::equals <typename __HashMap::EntryType>>
    > {};


template <
    typename __ServerType,                      // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __KeyType,                         // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __ValueType,                       // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __Hasher,                          // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __HashMap = HashMap <__KeyType, __ValueType, __Hasher> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> class __CDS_InheritsEBOs __HashMapEntryProxyFindOfConstInitializerListClient :   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalFindOfImmutableCompositeClient <
        __ServerType, typename __HashMap::EntryType,
        typename __HashMapImplementation <__KeyType, __ValueType, __Hasher>::__ht_ConstIterator,
        std::initializer_list <typename __HashMap::EntryType>,
        &__initializerListContains <typename __HashMap::EntryType, &cds::meta::equals <typename __HashMap::EntryType>>,
        &__initializerListNotContains <typename __HashMap::EntryType, &cds::meta::equals <typename __HashMap::EntryType>>
    > {};


template <
    typename __ServerType,                      // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __KeyType,                         // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __ValueType,                       // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __Hasher,                          // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __HashMap = HashMap <__KeyType, __ValueType, __Hasher> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> class __CDS_InheritsEBOs __HashMapEntryProxyFindByClient :   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalFindByMutableCompositeClient <
        __ServerType, typename __HashMap::EntryType,
        typename __HashMapImplementation <__KeyType, __ValueType, __Hasher>::__ht_Iterator
    > {};


template <
    typename __ServerType,                      // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __KeyType,                         // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __ValueType,                       // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __Hasher,                          // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __HashMap = HashMap <__KeyType, __ValueType, __Hasher> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> class __CDS_InheritsEBOs __HashMapEntryProxyConstFindByClient :  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalFindByImmutableCompositeClient <
        __ServerType, typename __HashMap::EntryType,
        typename __HashMapImplementation <__KeyType, __ValueType, __Hasher>::__ht_ConstIterator
    > {};


template <
    typename __ServerType,                      // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __KeyType,                         // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __ValueType,                       // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __Hasher,                          // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __HashMap = HashMap <__KeyType, __ValueType, __Hasher> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> class __CDS_InheritsEBOs __HashMapEntryProxyRemoveOfIterableClient : // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalRemoveOfCompositeClient <
        __ServerType, typename __HashMap::EntryType, cds::Iterable <typename __HashMap::EntryType>,
        &__iterableContains <typename __HashMap::EntryType>
    > {};


template <
    typename __ServerType,                      // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __KeyType,                         // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __ValueType,                       // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __Hasher,                          // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __HashMap = HashMap <__KeyType, __ValueType, __Hasher> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> class __CDS_InheritsEBOs __HashMapEntryProxyRemoveOfInitializerListClient :  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalRemoveOfCompositeClient <
        __ServerType, typename __HashMap::EntryType, std::initializer_list <typename __HashMap::EntryType>,
        &__initializerListContains <typename __HashMap::EntryType, &cds::meta::equals <typename __HashMap::EntryType>>
    > {};


template <
    typename __ServerType,                      // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __KeyType,                         // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __ValueType,                       // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __Hasher,                          // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __HashMap = HashMap <__KeyType, __ValueType, __Hasher> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> class __CDS_InheritsEBOs __HashMapEntryProxyRemoveByClient : // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalRemoveByCompositeClient <
        __ServerType,
        typename __HashMap::EntryType
    > {};


template <
    typename __ServerType,                      // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __KeyType,                         // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __ValueType,                       // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __Hasher,                          // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __HashMap = HashMap <__KeyType, __ValueType, __Hasher> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> class __CDS_InheritsEBOs __HashMapEntryProxyGenericStatementsClient :    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalGenericMutableStatementsCompositeClient <
        __ServerType, typename __HashMap::EntryType
    > {};


template <
    typename __ServerType,                      // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __KeyType,                         // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __ValueType,                       // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __Hasher,                          // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __HashMap = HashMap <__KeyType, __ValueType, __Hasher> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> class __CDS_InheritsEBOs __HashMapEntryProxyConstGenericStatementsClient :   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalGenericImmutableStatementsCompositeClient <
        __ServerType, typename __HashMap::EntryType
    > {};


template <
    typename __ServerType,                          // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __KeyType,                             // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __ValueType,                           // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __Hasher,                              // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __HashMap =                            // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    HashMap <
        __KeyType,
        __ValueType,
        __Hasher
    >
> class __CDS_InheritsEBOs __HashMapEntryProxyContainsOfIterableClient :   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalContainsOfCompositeClient <
        __ServerType, typename __HashMap::EntryType, 
        cds::Iterable <typename __HashMap::EntryType>,
        &__iterableContains <typename __HashMap::EntryType>
    > {};


template <
    typename __ServerType,                                  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __KeyType,                                     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __ValueType,                                   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __Hasher,                                      // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __HashMap =                                    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    HashMap <
        __KeyType,
        __ValueType,
        __Hasher
    >
> class __CDS_InheritsEBOs __HashMapEntryProxyContainsOfInitializerListClient :    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalContainsOfCompositeClient <
        __ServerType, typename __HashMap::EntryType, std::initializer_list <typename __HashMap::EntryType>,
        &__initializerListContains <typename __HashMap::EntryType, &cds::meta::equals <typename __HashMap::EntryType>>
    > {};


template <
    typename __ServerType,                              // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __KeyType,                                 // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __ValueType,                               // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __Hasher                                   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> class __CDS_InheritsEBOs __HashMapEntryProxyDelegateForwardIterableClient :  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalDelegateForwardIterablePrimitiveClient <
        __ServerType, typename __HashMapImplementation <__KeyType, __ValueType, __Hasher>::__ht_Iterator
    > {};


template <
    typename __ServerType,                                  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __KeyType,                                     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __ValueType,                                   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __Hasher                                       // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> class __CDS_InheritsEBOs __HashMapEntryProxyDelegateForwardConstIterableClient : // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalDelegateForwardConstIterablePrimitiveClient <
        __ServerType, typename __HashMapImplementation <__KeyType, __ValueType, __Hasher>::__ht_ConstIterator
    > {};

} // namespace __impl
} // namespace __hidden

template <typename __KeyType, typename __ValueType, typename __Hasher>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs HashMap <__KeyType, __ValueType, __Hasher>::EntryMutableCollectionProxy :
    public HashMap <__KeyType, __ValueType, __Hasher>::AbstractEntryMutableCollectionProxy,
    protected __hidden::__impl::__HashMapEntryProxyServer <EntryMutableCollectionProxy, __KeyType, __ValueType, __Hasher>,
    public __hidden::__impl::__HashMapEntryProxyRandomInsertionClient <EntryMutableCollectionProxy, __KeyType, __ValueType, __Hasher>,
    public __hidden::__impl::__HashMapEntryProxyIteratorRemoveClient <EntryMutableCollectionProxy, __KeyType, __ValueType, __Hasher>,
    public __hidden::__impl::__HashMapEntryProxyConstIteratorRemoveClient <EntryMutableCollectionProxy, __KeyType, __ValueType, __Hasher>,
    public __hidden::__impl::__HashMapEntryProxyFindOfIterableClient <EntryMutableCollectionProxy, __KeyType, __ValueType, __Hasher>,
    public __hidden::__impl::__HashMapEntryProxyFindOfConstIterableClient <EntryMutableCollectionProxy, __KeyType, __ValueType, __Hasher>,
    public __hidden::__impl::__HashMapEntryProxyFindOfInitializerListClient <EntryMutableCollectionProxy, __KeyType, __ValueType, __Hasher>,
    public __hidden::__impl::__HashMapEntryProxyFindOfConstInitializerListClient <EntryMutableCollectionProxy, __KeyType, __ValueType, __Hasher>,
    public __hidden::__impl::__HashMapEntryProxyFindByClient <EntryMutableCollectionProxy, __KeyType, __ValueType, __Hasher>,
    public __hidden::__impl::__HashMapEntryProxyConstFindByClient <EntryMutableCollectionProxy, __KeyType, __ValueType, __Hasher>,
    public __hidden::__impl::__HashMapEntryProxyRemoveOfIterableClient <EntryMutableCollectionProxy, __KeyType, __ValueType, __Hasher>,
    public __hidden::__impl::__HashMapEntryProxyRemoveOfInitializerListClient <EntryMutableCollectionProxy, __KeyType, __ValueType, __Hasher>,
    public __hidden::__impl::__HashMapEntryProxyRemoveByClient <EntryMutableCollectionProxy, __KeyType, __ValueType, __Hasher>,
    public __hidden::__impl::__HashMapEntryProxyGenericStatementsClient <EntryMutableCollectionProxy, __KeyType, __ValueType, __Hasher>,
    public __hidden::__impl::__HashMapEntryProxyConstGenericStatementsClient <EntryMutableCollectionProxy, __KeyType, __ValueType, __Hasher>,
    public __hidden::__impl::__HashMapEntryProxyContainsOfIterableClient <EntryMutableCollectionProxy, __KeyType, __ValueType, __Hasher>,
    public __hidden::__impl::__HashMapEntryProxyContainsOfInitializerListClient <EntryMutableCollectionProxy, __KeyType, __ValueType, __Hasher>,
    public __hidden::__impl::__HashMapEntryProxyDelegateForwardIterableClient <EntryMutableCollectionProxy, __KeyType, __ValueType, __Hasher>,
    public __hidden::__impl::__HashMapEntryProxyDelegateForwardConstIterableClient <EntryMutableCollectionProxy, __KeyType, __ValueType, __Hasher> {
protected:
  using HashMapBase                           = HashMap <__KeyType, __ValueType, __Hasher>;
  using Server                                = __hidden::__impl::__HashMapEntryProxyServer <EntryMutableCollectionProxy, __KeyType, __ValueType, __Hasher>;
  using RandomInsertionClient                 = __hidden::__impl::__HashMapEntryProxyRandomInsertionClient <EntryMutableCollectionProxy, __KeyType, __ValueType, __Hasher>;
  using IteratorRemoveClient                  = __hidden::__impl::__HashMapEntryProxyIteratorRemoveClient <EntryMutableCollectionProxy, __KeyType, __ValueType, __Hasher>;
  using ConstIteratorRemoveClient             = __hidden::__impl::__HashMapEntryProxyConstIteratorRemoveClient <EntryMutableCollectionProxy, __KeyType, __ValueType, __Hasher>;
  using FindOfIterableClient                  = __hidden::__impl::__HashMapEntryProxyFindOfIterableClient <EntryMutableCollectionProxy, __KeyType, __ValueType, __Hasher>;
  using ConstFindOfIterableClient             = __hidden::__impl::__HashMapEntryProxyFindOfConstIterableClient <EntryMutableCollectionProxy, __KeyType, __ValueType, __Hasher>;
  using FindOfInitializerListClient           = __hidden::__impl::__HashMapEntryProxyFindOfInitializerListClient <EntryMutableCollectionProxy, __KeyType, __ValueType, __Hasher>;
  using ConstFindOfInitializerListClient      = __hidden::__impl::__HashMapEntryProxyFindOfConstInitializerListClient <EntryMutableCollectionProxy, __KeyType, __ValueType, __Hasher>;
  using FindByClient                          = __hidden::__impl::__HashMapEntryProxyFindByClient <EntryMutableCollectionProxy, __KeyType, __ValueType, __Hasher>;
  using ConstFindByClient                     = __hidden::__impl::__HashMapEntryProxyConstFindByClient <EntryMutableCollectionProxy, __KeyType, __ValueType, __Hasher>;
  using RemoveOfIterableClient                = __hidden::__impl::__HashMapEntryProxyRemoveOfIterableClient <EntryMutableCollectionProxy, __KeyType, __ValueType, __Hasher>;
  using RemoveOfInitializerListClient         = __hidden::__impl::__HashMapEntryProxyRemoveOfInitializerListClient <EntryMutableCollectionProxy, __KeyType, __ValueType, __Hasher>;
  using RemoveByClient                        = __hidden::__impl::__HashMapEntryProxyRemoveByClient <EntryMutableCollectionProxy, __KeyType, __ValueType, __Hasher>;
  using GenericStatementsClient               = __hidden::__impl::__HashMapEntryProxyGenericStatementsClient <EntryMutableCollectionProxy, __KeyType, __ValueType, __Hasher>;
  using ContainsOfIterableClient              = __hidden::__impl::__HashMapEntryProxyContainsOfIterableClient <EntryMutableCollectionProxy, __KeyType, __ValueType, __Hasher>;
  using ContainsOfInitializerListClient       = __hidden::__impl::__HashMapEntryProxyContainsOfInitializerListClient <EntryMutableCollectionProxy, __KeyType, __ValueType, __Hasher>;
  using ConstGenericStatementsClient          = __hidden::__impl::__HashMapEntryProxyConstGenericStatementsClient <EntryMutableCollectionProxy, __KeyType, __ValueType, __Hasher>;
  using DelegateForwardIterableClient         = __hidden::__impl::__HashMapEntryProxyDelegateForwardIterableClient <EntryMutableCollectionProxy, __KeyType, __ValueType, __Hasher>;
  using DelegateForwardConstIterableClient    = __hidden::__impl::__HashMapEntryProxyDelegateForwardConstIterableClient <EntryMutableCollectionProxy, __KeyType, __ValueType, __Hasher>;

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

  __CDS_Explicit constexpr EntryMutableCollectionProxy (HashMap <__KeyType, __ValueType, __Hasher>* pMap) noexcept;
  EntryMutableCollectionProxy (EntryMutableCollectionProxy const&) noexcept = delete;
  EntryMutableCollectionProxy (EntryMutableCollectionProxy&&) noexcept = delete;
  __CDS_cpplang_ConstexprDestructor ~EntryMutableCollectionProxy() noexcept override;
  auto operator = (EntryMutableCollectionProxy const&) noexcept -> EntryMutableCollectionProxy& = delete;
  auto operator = (EntryMutableCollectionProxy&&) noexcept -> EntryMutableCollectionProxy& = delete;

  __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto contains (
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
      __hidden::__impl::__IterableInternalRequest requestType
  ) noexcept -> __GenericHandler override;

  __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto __iicch_obtainGenericConstHandler (    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      __hidden::__impl::__IterableInternalRequest requestType
  ) const noexcept -> __GenericConstHandler override;

  static auto __newAddress ( // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      EntryMutableCollectionProxy*  pObject,
      EntryType const*              pReferenceElement,
      bool*                         pIsNew
  ) noexcept -> EntryType*;

  __CDS_NoDiscard static auto __begin ( // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      EntryMutableCollectionProxy* pObject
  ) noexcept -> __hidden::__impl::__AbstractDelegateIterator <EntryType>*;

  __CDS_NoDiscard static auto __end ( // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      EntryMutableCollectionProxy* pObject
  ) noexcept -> __hidden::__impl::__AbstractDelegateIterator <EntryType>*;

  __CDS_NoDiscard static auto __cbegin (  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      EntryMutableCollectionProxy const* pObject
  ) noexcept -> __hidden::__impl::__AbstractDelegateIterator <EntryType const>*;

  __CDS_NoDiscard static auto __cend (  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      EntryMutableCollectionProxy const* pObject
  ) noexcept -> __hidden::__impl::__AbstractDelegateIterator <EntryType const>*;

  __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction static auto __beginLocal (  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      EntryMutableCollectionProxy* pObject
  ) noexcept -> Iterator;

  __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction static auto __endLocal (  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      EntryMutableCollectionProxy* pObject
  ) noexcept -> Iterator;

  __CDS_NoDiscard constexpr static auto __cbeginLocal ( // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      EntryMutableCollectionProxy const* pObject
  ) noexcept -> ConstIterator;

  __CDS_NoDiscard constexpr static auto __cendLocal ( // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
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

#endif // __CDS_HASH_MAP_ENTRY_MUTABLE_COLLECTION_PROXY_HPP__
