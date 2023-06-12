//
// Created by stefan on 13.10.2022.
//

#ifndef __CDS_TREE_MAP_ENTRY_MUTABLE_COLLECTION_PROXY_HPP__
#define __CDS_TREE_MAP_ENTRY_MUTABLE_COLLECTION_PROXY_HPP__  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
#pragma once

namespace cds {       // NOLINT(modernize-concat-nested-namespaces)
namespace __hidden {  // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier)
namespace __impl {    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <
    typename __ServerType,                                              // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __KeyType,                                                 // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __ValueType,                                               // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __Comparator,                                              // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __TreeMap = TreeMap <__KeyType, __ValueType, __Comparator> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> class __CDS_InheritsEBOs __TreeMapEntryProxyServer :                  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __MutableCollectionServer <__ServerType, typename __TreeMap::EntryType> {};


template <
    typename __ServerType,                                              // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __KeyType,                                                 // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __ValueType,                                               // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __Comparator,                                              // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __TreeMap = TreeMap <__KeyType, __ValueType, __Comparator> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> class __CDS_InheritsEBOs __TreeMapEntryProxyConstIteratorRemoveClient :      // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalConstIteratorRemovePrimitiveClient <
        __ServerType, typename __TreeMap::EntryType,
        typename __TreeMapImplementation <__KeyType, __ValueType, __Comparator>::__rbt_AbstractConstIterator
    > {};


template <typename __ServerType, typename __KeyType, typename __ValueType, typename __Comparator> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __TreeMapEntryProxyIteratorRemoveClient :      // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalIteratorRemovePrimitiveClient <
        __ServerType, __ValueType,
        typename __TreeMapImplementation <__KeyType, __ValueType, __Comparator>::__rbt_AbstractIterator
    > {};


template <typename __ServerType, typename __KeyType, typename __ValueType, typename __Comparator> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __TreeMapEntryProxyDelegateBackwardConstIterableClient :        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalDelegateBackwardConstIterablePrimitiveClient <
        __ServerType,
        typename __TreeMapImplementation <__KeyType, __ValueType, __Comparator>::__rbt_ReverseConstIterator
    > {};


template <typename __ServerType, typename __KeyType, typename __ValueType, typename __Comparator> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __TreeMapEntryProxyDelegateBackwardIterableClient :         // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalDelegateBackwardIterablePrimitiveClient <
        __ServerType,
        typename __TreeMapImplementation <__KeyType, __ValueType, __Comparator>::__rbt_ReverseIterator
    > {};


template <typename __ServerType, typename __KeyType, typename __ValueType, typename __Comparator> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __TreeMapEntryProxyDelegateForwardConstIterableClient :     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalDelegateForwardConstIterablePrimitiveClient <
        __ServerType,
        typename __TreeMapImplementation <__KeyType, __ValueType, __Comparator>::__rbt_ConstIterator
    > {};


template <typename __ServerType, typename __KeyType, typename __ValueType, typename __Comparator> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __TreeMapEntryProxyDelegateForwardIterableClient :                       // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalDelegateForwardIterablePrimitiveClient <
        __ServerType,
        typename __TreeMapImplementation <__KeyType, __ValueType, __Comparator>::__rbt_Iterator
    > {};


template <
    typename __ServerType,                                              // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __KeyType,                                                 // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __ValueType,                                               // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __Comparator,                                              // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __TreeMap = TreeMap <__KeyType, __ValueType, __Comparator> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> class __CDS_InheritsEBOs __TreeMapEntryProxyRandomInsertionClient :      // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalRandomInsertionPrimitiveClient <
        __ServerType, typename __TreeMap::EntryType, typename __TreeMap::EntryType const
    > {};


template <
    typename __ServerType,                                              // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __KeyType,                                                 // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __ValueType,                                               // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __Comparator,                                              // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __TreeMap = TreeMap <__KeyType, __ValueType, __Comparator> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> class __CDS_InheritsEBOs __TreeMapEntryProxyContainsOfCollectionClient :     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalContainsOfCompositeClient <
        __ServerType, typename __TreeMap::EntryType, cds::Iterable <typename __TreeMap::EntryType>,
        &__iterableContains <typename __TreeMap::EntryType>
    > {};


template <
    typename __ServerType,                                              // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __KeyType,                                                 // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __ValueType,                                               // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __Comparator,                                              // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __TreeMap = TreeMap <__KeyType, __ValueType, __Comparator> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> class __CDS_InheritsEBOs __TreeMapEntryProxyContainsOfInitializerListClient :     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalContainsOfCompositeClient <
        __ServerType, typename __TreeMap::EntryType, std::initializer_list <typename __TreeMap::EntryType>,
        &__initializerListContains <typename __TreeMap::EntryType, &cds::meta::equals <typename __TreeMap::EntryType>>
    > {};


template <
    typename __ServerType,                                              // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __KeyType,                                                 // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __ValueType,                                               // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __Comparator,                                              // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __TreeMap = TreeMap <__KeyType, __ValueType, __Comparator> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> class __CDS_InheritsEBOs __TreeMapEntryProxyFindByImmutableClient :      // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalFindByImmutableCompositeClient <
        __ServerType, typename __TreeMap::EntryType,
        typename __TreeMapImplementation <__KeyType, __ValueType, __Comparator>::__rbt_AbstractConstIterator
    > {};


template <
    typename __ServerType,                                              // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __KeyType,                                                 // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __ValueType,                                               // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __Comparator,                                              // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __TreeMap = TreeMap <__KeyType, __ValueType, __Comparator> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> class __CDS_InheritsEBOs __TreeMapEntryProxyFindByMutableClient :      // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalFindByMutableCompositeClient <
        __ServerType, typename __TreeMap::EntryType,
        typename __TreeMapImplementation <__KeyType, __ValueType, __Comparator>::__rbt_AbstractIterator
    > {};


template <
    typename __ServerType,                                              // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __KeyType,                                                 // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __ValueType,                                               // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __Comparator,                                              // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __TreeMap = TreeMap <__KeyType, __ValueType, __Comparator> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> class __CDS_InheritsEBOs __TreeMapEntryProxyFindOfConstCollectionClient :        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalFindOfImmutableCompositeClient <
        __ServerType, typename __TreeMap::EntryType,
        typename __TreeMapImplementation <__KeyType, __ValueType, __Comparator>::__rbt_AbstractConstIterator,
        cds::Iterable <typename __TreeMap::EntryType>,
        &__iterableContains <typename __TreeMap::EntryType>, &__iterableNotContains <typename __TreeMap::EntryType>
    > {};


template <
    typename __ServerType,                                              // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __KeyType,                                                 // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __ValueType,                                               // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __Comparator,                                              // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __TreeMap = TreeMap <__KeyType, __ValueType, __Comparator> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> class __CDS_InheritsEBOs __TreeMapEntryProxyFindOfConstInitializerListClient :        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalFindOfImmutableCompositeClient <
        __ServerType, typename __TreeMap::EntryType,
        typename __TreeMapImplementation <__KeyType, __ValueType, __Comparator>::__rbt_AbstractConstIterator,
        std::initializer_list <typename __TreeMap::EntryType>,
        &__initializerListContains <typename __TreeMap::EntryType, &cds::meta::equals <typename __TreeMap::EntryType>>,
        &__initializerListNotContains <typename __TreeMap::EntryType, &cds::meta::equals <typename __TreeMap::EntryType>>
    > {};


template <
    typename __ServerType,                                              // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __KeyType,                                                 // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __ValueType,                                               // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __Comparator,                                              // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __TreeMap = TreeMap <__KeyType, __ValueType, __Comparator> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> class __CDS_InheritsEBOs __TreeMapEntryProxyFindOfCollectionClient :        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalFindOfImmutableCompositeClient <
        __ServerType, typename __TreeMap::EntryType,
        typename __TreeMapImplementation <__KeyType, __ValueType, __Comparator>::__rbt_AbstractIterator,
        cds::Iterable <typename __TreeMap::EntryType>,
        &__iterableContains <typename __TreeMap::EntryType>, &__iterableNotContains <typename __TreeMap::EntryType>
    > {};


template <
    typename __ServerType,                                              // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __KeyType,                                                 // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __ValueType,                                               // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __Comparator,                                              // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __TreeMap = TreeMap <__KeyType, __ValueType, __Comparator> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> class __CDS_InheritsEBOs __TreeMapEntryProxyFindOfInitializerListClient :        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalFindOfImmutableCompositeClient <
        __ServerType, typename __TreeMap::EntryType,
        typename __TreeMapImplementation <__KeyType, __ValueType, __Comparator>::__rbt_AbstractIterator,
        std::initializer_list <typename __TreeMap::EntryType>,
        &__initializerListContains <typename __TreeMap::EntryType, &cds::meta::equals <typename __TreeMap::EntryType>>,
        &__initializerListNotContains <typename __TreeMap::EntryType, &cds::meta::equals <typename __TreeMap::EntryType>>
    > {};


template <
    typename __ServerType,                                              // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __KeyType,                                                 // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __ValueType,                                               // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __Comparator,                                              // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __TreeMap = TreeMap <__KeyType, __ValueType, __Comparator> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> class __CDS_InheritsEBOs __TreeMapEntryProxyConstGenericStatementsClient :       // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalGenericImmutableStatementsCompositeClient <__ServerType, typename __TreeMap::EntryType> {};


template <
    typename __ServerType,                                              // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __KeyType,                                                 // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __ValueType,                                               // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __Comparator,                                              // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __TreeMap = TreeMap <__KeyType, __ValueType, __Comparator> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> class __CDS_InheritsEBOs __TreeMapEntryProxyGenericStatementsClient :       // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalGenericMutableStatementsCompositeClient <__ServerType, typename __TreeMap::EntryType> {};


template <
    typename __ServerType,                                              // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __KeyType,                                                 // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __ValueType,                                               // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __Comparator,                                              // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __TreeMap = TreeMap <__KeyType, __ValueType, __Comparator> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> class __CDS_InheritsEBOs __TreeMapEntryProxyRemoveByClient :       // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalRemoveByCompositeClient <__ServerType, typename __TreeMap::EntryType> {};


template <
    typename __ServerType,                                              // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __KeyType,                                                 // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __ValueType,                                               // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __Comparator,                                              // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __TreeMap = TreeMap <__KeyType, __ValueType, __Comparator> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> class __CDS_InheritsEBOs __TreeMapEntryProxyRemoveOfCollectionClient :     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalRemoveOfCompositeClient <
        __ServerType, typename __TreeMap::EntryType, cds::Iterable <typename __TreeMap::EntryType>,
        &__iterableContains <typename __TreeMap::EntryType>
    > {};


template <
    typename __ServerType,                                              // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __KeyType,                                                 // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __ValueType,                                               // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __Comparator,                                              // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __TreeMap = TreeMap <__KeyType, __ValueType, __Comparator> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> class __CDS_InheritsEBOs __TreeMapEntryProxyRemoveOfInitializerListClient :     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalRemoveOfCompositeClient <
        __ServerType, typename __TreeMap::EntryType, std::initializer_list <typename __TreeMap::EntryType>,
        &__initializerListContains <typename __TreeMap::EntryType, &cds::meta::equals <typename __TreeMap::EntryType>>
    > {};
} // namespace __impl
} // namespace __hidden

template <typename __KeyType, typename __ValueType, typename __Comparator>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs TreeMap <__KeyType, __ValueType, __Comparator>::EntryMutableCollectionProxy :
    public TreeMap <__KeyType, __ValueType, __Comparator>::AbstractEntryMutableCollectionProxy,
    private __hidden::__impl::__TreeMapEntryProxyServer <EntryMutableCollectionProxy, __KeyType, __ValueType, __Comparator>,
    public __hidden::__impl::__TreeMapEntryProxyConstIteratorRemoveClient <EntryMutableCollectionProxy, __KeyType, __ValueType, __Comparator>,
    public __hidden::__impl::__TreeMapEntryProxyIteratorRemoveClient <EntryMutableCollectionProxy, __KeyType, __ValueType, __Comparator>,
    public __hidden::__impl::__TreeMapEntryProxyDelegateBackwardConstIterableClient <EntryMutableCollectionProxy, __KeyType, __ValueType, __Comparator>,
    public __hidden::__impl::__TreeMapEntryProxyDelegateBackwardIterableClient <EntryMutableCollectionProxy, __KeyType, __ValueType, __Comparator>,
    public __hidden::__impl::__TreeMapEntryProxyDelegateForwardConstIterableClient <EntryMutableCollectionProxy, __KeyType, __ValueType, __Comparator>,
    public __hidden::__impl::__TreeMapEntryProxyDelegateForwardIterableClient <EntryMutableCollectionProxy, __KeyType, __ValueType, __Comparator>,
    public __hidden::__impl::__TreeMapEntryProxyRandomInsertionClient <EntryMutableCollectionProxy, __KeyType, __ValueType, __Comparator>,
    public __hidden::__impl::__TreeMapEntryProxyContainsOfCollectionClient <EntryMutableCollectionProxy, __KeyType, __ValueType, __Comparator>,
    public __hidden::__impl::__TreeMapEntryProxyContainsOfInitializerListClient <EntryMutableCollectionProxy, __KeyType, __ValueType, __Comparator>,
    public __hidden::__impl::__TreeMapEntryProxyFindByImmutableClient <EntryMutableCollectionProxy, __KeyType, __ValueType, __Comparator>,
    public __hidden::__impl::__TreeMapEntryProxyFindByMutableClient <EntryMutableCollectionProxy, __KeyType, __ValueType, __Comparator>,
    public __hidden::__impl::__TreeMapEntryProxyFindOfConstCollectionClient <EntryMutableCollectionProxy, __KeyType, __ValueType, __Comparator>,
    public __hidden::__impl::__TreeMapEntryProxyFindOfConstInitializerListClient <EntryMutableCollectionProxy, __KeyType, __ValueType, __Comparator>,
    public __hidden::__impl::__TreeMapEntryProxyFindOfCollectionClient <EntryMutableCollectionProxy, __KeyType, __ValueType, __Comparator>,
    public __hidden::__impl::__TreeMapEntryProxyFindOfInitializerListClient <EntryMutableCollectionProxy, __KeyType, __ValueType, __Comparator>,
    public __hidden::__impl::__TreeMapEntryProxyConstGenericStatementsClient <EntryMutableCollectionProxy, __KeyType, __ValueType, __Comparator>,
    public __hidden::__impl::__TreeMapEntryProxyGenericStatementsClient <EntryMutableCollectionProxy, __KeyType, __ValueType, __Comparator>,
    public __hidden::__impl::__TreeMapEntryProxyRemoveByClient <EntryMutableCollectionProxy, __KeyType, __ValueType, __Comparator>,
    public __hidden::__impl::__TreeMapEntryProxyRemoveOfCollectionClient <EntryMutableCollectionProxy, __KeyType, __ValueType, __Comparator>,
    public __hidden::__impl::__TreeMapEntryProxyRemoveOfInitializerListClient <EntryMutableCollectionProxy, __KeyType, __ValueType, __Comparator> {
protected:
  using TreeMapBase                         = TreeMap <__KeyType, __ValueType, __Comparator>;
  using Server                              = __hidden::__impl::__TreeMapEntryProxyServer <EntryMutableCollectionProxy, __KeyType, __ValueType, __Comparator>;
  using ConstIteratorRemoveClient           = __hidden::__impl::__TreeMapEntryProxyConstIteratorRemoveClient <EntryMutableCollectionProxy, __KeyType, __ValueType, __Comparator>;
  using IteratorRemoveClient                = __hidden::__impl::__TreeMapEntryProxyIteratorRemoveClient <EntryMutableCollectionProxy, __KeyType, __ValueType, __Comparator>;
  using DelegateBackwardConstIterableClient = __hidden::__impl::__TreeMapEntryProxyDelegateBackwardConstIterableClient <EntryMutableCollectionProxy, __KeyType, __ValueType, __Comparator>;
  using DelegateBackwardIterableClient      = __hidden::__impl::__TreeMapEntryProxyDelegateBackwardIterableClient <EntryMutableCollectionProxy, __KeyType, __ValueType, __Comparator>;
  using DelegateForwardConstIterableClient  = __hidden::__impl::__TreeMapEntryProxyDelegateForwardConstIterableClient <EntryMutableCollectionProxy, __KeyType, __ValueType, __Comparator>;
  using DelegateForwardIterableClient       = __hidden::__impl::__TreeMapEntryProxyDelegateForwardIterableClient <EntryMutableCollectionProxy, __KeyType, __ValueType, __Comparator>;
  using RandomInsertionClient               = __hidden::__impl::__TreeMapEntryProxyRandomInsertionClient <EntryMutableCollectionProxy, __KeyType, __ValueType, __Comparator>;
  using ContainsOfCollectionClient          = __hidden::__impl::__TreeMapEntryProxyContainsOfCollectionClient <EntryMutableCollectionProxy, __KeyType, __ValueType, __Comparator>;
  using ContainsOfInitializerListClient     = __hidden::__impl::__TreeMapEntryProxyContainsOfInitializerListClient <EntryMutableCollectionProxy, __KeyType, __ValueType, __Comparator>;
  using FindByImmutableClient               = __hidden::__impl::__TreeMapEntryProxyFindByImmutableClient <EntryMutableCollectionProxy, __KeyType, __ValueType, __Comparator>;
  using FindByMutableClient                 = __hidden::__impl::__TreeMapEntryProxyFindByMutableClient <EntryMutableCollectionProxy, __KeyType, __ValueType, __Comparator>;
  using FindOfConstCollectionClient         = __hidden::__impl::__TreeMapEntryProxyFindOfConstCollectionClient <EntryMutableCollectionProxy, __KeyType, __ValueType, __Comparator>;
  using FindOfConstInitializerListClient    = __hidden::__impl::__TreeMapEntryProxyFindOfConstInitializerListClient <EntryMutableCollectionProxy, __KeyType, __ValueType, __Comparator>;
  using FindOfCollectionClient              = __hidden::__impl::__TreeMapEntryProxyFindOfCollectionClient <EntryMutableCollectionProxy, __KeyType, __ValueType, __Comparator>;
  using FindOfInitializerListClient         = __hidden::__impl::__TreeMapEntryProxyFindOfInitializerListClient <EntryMutableCollectionProxy, __KeyType, __ValueType, __Comparator>;
  using ConstGenericStatementsClient        = __hidden::__impl::__TreeMapEntryProxyConstGenericStatementsClient <EntryMutableCollectionProxy, __KeyType, __ValueType, __Comparator>;
  using GenericStatementsClient             = __hidden::__impl::__TreeMapEntryProxyGenericStatementsClient <EntryMutableCollectionProxy, __KeyType, __ValueType, __Comparator>;
  using RemoveByClient                      = __hidden::__impl::__TreeMapEntryProxyRemoveByClient <EntryMutableCollectionProxy, __KeyType, __ValueType, __Comparator>;
  using RemoveOfCollectionClient            = __hidden::__impl::__TreeMapEntryProxyRemoveOfCollectionClient <EntryMutableCollectionProxy, __KeyType, __ValueType, __Comparator>;
  using RemoveOfInitializerListClient       = __hidden::__impl::__TreeMapEntryProxyRemoveOfInitializerListClient <EntryMutableCollectionProxy, __KeyType, __ValueType, __Comparator>;

public:
  using typename DelegateForwardIterableClient::Iterator;
  using typename DelegateForwardConstIterableClient::ConstIterator;
  using typename DelegateBackwardIterableClient::ReverseIterator;
  using typename DelegateBackwardConstIterableClient::ConstReverseIterator;
  
  using EntryType = typename MapBase::EntryType;

  using DelegateForwardIterableClient::begin;
  using DelegateForwardIterableClient::end;

  using DelegateBackwardIterableClient::rbegin;
  using DelegateBackwardIterableClient::rend;

  using DelegateForwardConstIterableClient::begin;
  using DelegateForwardConstIterableClient::end;
  using DelegateForwardConstIterableClient::cbegin;
  using DelegateForwardConstIterableClient::cend;

  using DelegateBackwardConstIterableClient::rbegin;
  using DelegateBackwardConstIterableClient::rend;
  using DelegateBackwardConstIterableClient::crbegin;
  using DelegateBackwardConstIterableClient::crend;

  using IteratorRemoveClient::remove;
  using IteratorRemoveClient::removeAll;

  using ConstIteratorRemoveClient::remove;
  using ConstIteratorRemoveClient::removeAll;

  using RandomInsertionClient::insert;
  using RandomInsertionClient::add;
  using RandomInsertionClient::emplace;
  using RandomInsertionClient::insertAll;
  using RandomInsertionClient::insertAllOf;
  using RandomInsertionClient::addAllOf;

  using ContainsOfCollectionClient::containsAnyOf;
  using ContainsOfCollectionClient::containsAnyNotOf;
  using ContainsOfCollectionClient::containsAllOf;
  using ContainsOfCollectionClient::containsNoneOf;

  using ContainsOfInitializerListClient::containsAnyOf;
  using ContainsOfInitializerListClient::containsAnyNotOf;
  using ContainsOfInitializerListClient::containsAllOf;
  using ContainsOfInitializerListClient::containsNoneOf;

  using FindOfCollectionClient::findOf;
  using FindOfCollectionClient::findFirstOf;
  using FindOfCollectionClient::findLastOf;
  using FindOfCollectionClient::findAllOf;
  using FindOfCollectionClient::findNotOf;
  using FindOfCollectionClient::findFirstNotOf;
  using FindOfCollectionClient::findLastNotOf;
  using FindOfCollectionClient::findAllNotOf;

  using FindOfInitializerListClient::findOf;
  using FindOfInitializerListClient::findFirstOf;
  using FindOfInitializerListClient::findLastOf;
  using FindOfInitializerListClient::findAllOf;
  using FindOfInitializerListClient::findNotOf;
  using FindOfInitializerListClient::findFirstNotOf;
  using FindOfInitializerListClient::findLastNotOf;
  using FindOfInitializerListClient::findAllNotOf;

  using FindOfConstCollectionClient::findOf;
  using FindOfConstCollectionClient::findFirstOf;
  using FindOfConstCollectionClient::findLastOf;
  using FindOfConstCollectionClient::findAllOf;
  using FindOfConstCollectionClient::findNotOf;
  using FindOfConstCollectionClient::findFirstNotOf;
  using FindOfConstCollectionClient::findLastNotOf;
  using FindOfConstCollectionClient::findAllNotOf;

  using FindOfConstInitializerListClient::findOf;
  using FindOfConstInitializerListClient::findFirstOf;
  using FindOfConstInitializerListClient::findLastOf;
  using FindOfConstInitializerListClient::findAllOf;
  using FindOfConstInitializerListClient::findNotOf;
  using FindOfConstInitializerListClient::findFirstNotOf;
  using FindOfConstInitializerListClient::findLastNotOf;
  using FindOfConstInitializerListClient::findAllNotOf;

  using FindByImmutableClient::findThat;
  using FindByImmutableClient::findFirstThat;
  using FindByImmutableClient::findLastThat;
  using FindByImmutableClient::findAllThat;

  using FindByMutableClient::findThat;
  using FindByMutableClient::findFirstThat;
  using FindByMutableClient::findLastThat;
  using FindByMutableClient::findAllThat;

  using RemoveOfCollectionClient::removeOf;
  using RemoveOfCollectionClient::removeFirstOf;
  using RemoveOfCollectionClient::removeLastOf;
  using RemoveOfCollectionClient::removeAllOf;
  using RemoveOfCollectionClient::removeNotOf;
  using RemoveOfCollectionClient::removeFirstNotOf;
  using RemoveOfCollectionClient::removeLastNotOf;
  using RemoveOfCollectionClient::removeAllNotOf;

  using RemoveOfInitializerListClient::removeOf;
  using RemoveOfInitializerListClient::removeFirstOf;
  using RemoveOfInitializerListClient::removeLastOf;
  using RemoveOfInitializerListClient::removeAllOf;
  using RemoveOfInitializerListClient::removeNotOf;
  using RemoveOfInitializerListClient::removeFirstNotOf;
  using RemoveOfInitializerListClient::removeLastNotOf;
  using RemoveOfInitializerListClient::removeAllNotOf;

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

  EntryMutableCollectionProxy () noexcept = delete;
  EntryMutableCollectionProxy (EntryMutableCollectionProxy const&) noexcept = delete;
  EntryMutableCollectionProxy (EntryMutableCollectionProxy&&) noexcept = delete;
  __CDS_Explicit EntryMutableCollectionProxy (TreeMap <__KeyType, __ValueType, __Comparator>* pMap) noexcept;
  auto operator = (EntryMutableCollectionProxy const&) noexcept -> EntryMutableCollectionProxy& = delete;
  auto operator = (EntryMutableCollectionProxy&&) noexcept -> EntryMutableCollectionProxy& = delete;
  
private:
  friend __hidden::__impl::__MutableCollectionServer <EntryMutableCollectionProxy, EntryType>;

  friend __hidden::__impl::__LocalDelegateForwardIterablePrimitiveClient <EntryMutableCollectionProxy, Iterator>;
  friend __hidden::__impl::__LocalDelegateForwardConstIterablePrimitiveClient <EntryMutableCollectionProxy, ConstIterator>;
  friend __hidden::__impl::__LocalDelegateBackwardIterablePrimitiveClient <EntryMutableCollectionProxy, ReverseIterator>;
  friend __hidden::__impl::__LocalDelegateBackwardConstIterablePrimitiveClient <EntryMutableCollectionProxy, ConstReverseIterator>;
  
  using typename AbstractEntryMutableCollectionProxy::__GenericHandler;          // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)  using typename AbstractEntryMutableCollectionProxy::__GenericConstHandler;     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  using typename AbstractEntryMutableCollectionProxy::__GenericConstHandler;          // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)  using typename AbstractEntryMutableCollectionProxy::__GenericConstHandler;     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  using AbstractIterator = typename IteratorRemoveClient::Iterator;
  using AbstractConstIterator = typename ConstIteratorRemoveClient::ConstIterator;

  using Server::__mcs_handlers;       // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  using Server::__mcs_constHandlers;  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

  __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto __iicch_obtainGenericHandler (         // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      cds::__hidden::__impl::__IterableInternalRequest requestType
  ) noexcept -> __GenericHandler override;

  __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto __iicch_obtainGenericConstHandler (        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      cds::__hidden::__impl::__IterableInternalRequest requestType
  ) const noexcept -> __GenericConstHandler override;
  
  static auto __newAddress ( // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      EntryMutableCollectionProxy*  pObject,
      EntryType const*              pReferenceElement,
      bool*                         pIsNew
  ) noexcept -> EntryType*;

  __CDS_NoDiscard constexpr static auto __begin ( // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      EntryMutableCollectionProxy* pObject
  ) noexcept -> cds::__hidden::__impl::__AbstractDelegateIterator <EntryType>*;

  __CDS_NoDiscard constexpr static auto __end ( // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      EntryMutableCollectionProxy * pObject
  ) noexcept -> cds::__hidden::__impl::__AbstractDelegateIterator <EntryType>*;

  __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction static auto __beginLocal (  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      EntryMutableCollectionProxy* pObject
  ) noexcept -> Iterator;

  __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction static auto __endLocal (  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      EntryMutableCollectionProxy* pObject
  ) noexcept -> Iterator;

  __CDS_NoDiscard constexpr static auto __cbegin (  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      EntryMutableCollectionProxy const* pObject
  ) noexcept -> cds::__hidden::__impl::__AbstractDelegateIterator <EntryType const>*;

  __CDS_NoDiscard constexpr static auto __cend (  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      EntryMutableCollectionProxy const* pObject
  ) noexcept -> cds::__hidden::__impl::__AbstractDelegateIterator <EntryType const>*;

  __CDS_NoDiscard constexpr static auto __cbeginLocal ( // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      EntryMutableCollectionProxy const* pObject
  ) noexcept -> ConstIterator;

  __CDS_NoDiscard constexpr static auto __cendLocal ( // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      EntryMutableCollectionProxy const* pObject
  ) noexcept -> ConstIterator;

  __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction static auto __rbeginLocal ( // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      EntryMutableCollectionProxy* pObject
  ) noexcept -> ReverseIterator;

  __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction static auto __rendLocal ( // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      EntryMutableCollectionProxy* pObject
  ) noexcept -> ReverseIterator;

  __CDS_NoDiscard constexpr static auto __crbeginLocal (  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      EntryMutableCollectionProxy const* pObject
  ) noexcept -> ConstReverseIterator;

  __CDS_NoDiscard constexpr static auto __crendLocal (  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      EntryMutableCollectionProxy const* pObject
  ) noexcept -> ConstReverseIterator;

  static auto __remove (     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      EntryMutableCollectionProxy*  pObject,
      AbstractIterator const*       iterator
  ) noexcept -> bool;

  static auto __removeConst (     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      EntryMutableCollectionProxy* pObject,
      AbstractConstIterator const* iterator
  ) noexcept -> bool;

  static auto __removeArray (     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      EntryMutableCollectionProxy*    pObject,
      AbstractIterator const* const*  ppIterators,
      Size                            iteratorCount
  ) noexcept -> Size;

  static auto __removeConstArray (     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      EntryMutableCollectionProxy*        pObject,
      AbstractConstIterator const* const* ppIterators,
      Size                                iteratorCount
  ) noexcept -> Size;
};
} // namespace cds

#endif // __CDS_TREE_MAP_ENTRY_MUTABLE_COLLECTION_PROXY_HPP__
