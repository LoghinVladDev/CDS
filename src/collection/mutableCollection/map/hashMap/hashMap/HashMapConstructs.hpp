// NOLINT(llvm-header-guard)
// Created by loghin on 13/08/22.
//

#ifndef __CDS_HASH_MAP_CONSTRUCTS_HPP__ // NOLINT(llvm-header-guard)
#define __CDS_HASH_MAP_CONSTRUCTS_HPP__ // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
#pragma once

namespace cds {
template <
    typename __KeyType,                                                   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __ValueType,                                                 // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __Hasher = cds::WrapperHasher <__KeyType, Hash <__KeyType>>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> class HashMap;

namespace __hidden {  // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
namespace __impl {    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

template <typename __KeyType, typename __ValueType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
constexpr auto __hashMapKeyExtractor (              // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename Map <__KeyType, __ValueType>::EntryType const& element
) noexcept -> __KeyType const& {
  return element.key ();
}


template <typename __KeyType, typename __ValueType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_ConstexprNonLiteralReturn auto __hashMapCopyConstructor (   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename Map <__KeyType, __ValueType>::EntryType&       destinationDataNode,
    typename Map <__KeyType, __ValueType>::EntryType const& sourceDataNode
) noexcept -> void {
  new (&destinationDataNode) typename Map <__KeyType, __ValueType>::EntryType (sourceDataNode);
}


template <typename __KeyType, typename __ValueType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_ConstexprNonLiteralReturn auto __hashMapDestructor (    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename Map <__KeyType, __ValueType>::EntryType& entry
) noexcept -> void {
  using EntryType = typename Map <__KeyType, __ValueType>::EntryType;
  entry.~EntryType();
}


template <typename __KeyType, typename __ValueType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
constexpr auto __hashMapEquals (                                              // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename Map <__KeyType, __ValueType>::EntryType const& leftEntry, // NOLINT(bugprone-easily-swappable-parameters)
    typename Map <__KeyType, __ValueType>::EntryType const& rightEntry // NOLINT(bugprone-easily-swappable-parameters)
) noexcept -> bool {
  return
      cds::meta::equals (leftEntry.key(), rightEntry.key()) &&
      cds::meta::equals (leftEntry.value(), rightEntry.value());
}


template <typename __KeyType, typename __ValueType, typename __Hasher>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __HashMapImplementation :   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __HashTable <
        typename Map <__KeyType, __ValueType>::EntryType, __KeyType, __Hasher,
        cds::__hidden::__impl::__PrimeRehashPolicy <uint32>, &__hashMapKeyExtractor <__KeyType, __ValueType>,
        &cds::meta::equals < __KeyType >, &__hashMapDestructor <__KeyType, __ValueType>
    > {
    public:
      using __HashTable<
          typename Map <__KeyType, __ValueType>::EntryType, __KeyType, __Hasher,
          cds::__hidden::__impl::__PrimeRehashPolicy <uint32>, &__hashMapKeyExtractor <__KeyType, __ValueType>,
          &cds::meta::equals < __KeyType >, &__hashMapDestructor <__KeyType, __ValueType>
      >::__HashTable;
    };


template <typename __KeyType, typename __ValueType, typename __Hasher>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __HashMapDispatcher :       // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __HashMapImplementation <__KeyType, __ValueType, __Hasher>::template __MapDispatcher <
        HashMap <__KeyType, __ValueType, __Hasher>
    > {};


template <typename __KeyType, typename __ValueType, typename __Hasher>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __HashMapServer :           // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __MapServer <
        HashMap <__KeyType, __ValueType, __Hasher>, typename Map <__KeyType, __ValueType>::EntryType
    > {};


template <typename __KeyType, typename __ValueType, typename __Hasher>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __HashMapRandomInsertionClient :    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalRandomInsertionPrimitiveClient <
        HashMap <__KeyType, __ValueType, __Hasher>,
        typename Map <__KeyType, __ValueType>::EntryType,
        typename Map <__KeyType, __ValueType>::EntryType
    > {};


template <typename __KeyType, typename __ValueType, typename __Hasher>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __HashMapIteratorRemoveClient : // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalIteratorRemovePrimitiveClient <
        HashMap <__KeyType, __ValueType, __Hasher>, typename Map <__KeyType, __ValueType>::EntryType,
        HashTableIterator <typename Map <__KeyType, __ValueType>::EntryType>
    > {};


template <typename __KeyType, typename __ValueType, typename __Hasher>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __HashMapConstIteratorRemoveClient :    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalConstIteratorRemovePrimitiveClient <
        HashMap <__KeyType, __ValueType, __Hasher>, typename Map <__KeyType, __ValueType>::EntryType,
        HashTableConstIterator <typename Map <__KeyType, __ValueType>::EntryType>
    > {};


template <typename __KeyType, typename __ValueType, typename __Hasher>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __HashMapFindOfIterableClient : // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalFindOfMutableCompositeClient <
        HashMap <__KeyType, __ValueType, __Hasher>, typename Map <__KeyType, __ValueType>::EntryType,
        HashTableIterator <typename Map <__KeyType, __ValueType>::EntryType>,
        cds::Iterable <typename Map <__KeyType, __ValueType>::EntryType>,
        &__iterableContains <typename Map <__KeyType, __ValueType>::EntryType>,
        &__iterableNotContains <typename Map <__KeyType, __ValueType>::EntryType>
    > {};


template <typename __KeyType, typename __ValueType, typename __Hasher>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __HashMapFindOfInitializerListClient :  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalFindOfMutableCompositeClient <
        HashMap <__KeyType, __ValueType, __Hasher>, typename Map <__KeyType, __ValueType>::EntryType,
        HashTableIterator <typename Map <__KeyType, __ValueType>::EntryType>,
        std::initializer_list <typename Map <__KeyType, __ValueType>::EntryType>,
        &__initializerListContains <typename Map <__KeyType, __ValueType>::EntryType, &__hashMapEquals <__KeyType, __ValueType>>,
        &__initializerListNotContains <typename Map <__KeyType, __ValueType>::EntryType, &__hashMapEquals <__KeyType, __ValueType>>
    > {};


template <typename __KeyType, typename __ValueType, typename __Hasher>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __HashMapFindByClient : // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalFindByMutableCompositeClient <
        HashMap <__KeyType, __ValueType, __Hasher>, typename Map <__KeyType, __ValueType>::EntryType,
        HashTableIterator <typename Map <__KeyType, __ValueType>::EntryType>
    > {};


template <typename __KeyType, typename __ValueType, typename __Hasher>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __HashMapFindOfConstIterableClient :    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalFindOfImmutableCompositeClient <
        HashMap <__KeyType, __ValueType, __Hasher>, typename Map <__KeyType, __ValueType>::EntryType,
        HashTableConstIterator <typename Map <__KeyType, __ValueType>::EntryType>,
        cds::Iterable <typename Map <__KeyType, __ValueType>::EntryType>,
        &__iterableContains <typename Map <__KeyType, __ValueType>::EntryType>,
        &__iterableNotContains <typename Map <__KeyType, __ValueType>::EntryType>
    > {};


template <typename __KeyType, typename __ValueType, typename __Hasher>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __HashMapFindOfConstInitializerListClient : // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalFindOfImmutableCompositeClient <
        HashMap <__KeyType, __ValueType, __Hasher>, typename Map <__KeyType, __ValueType>::EntryType,
        HashTableConstIterator <typename Map <__KeyType, __ValueType>::EntryType>,
        std::initializer_list <typename Map <__KeyType, __ValueType>::EntryType>,
        &__initializerListContains <typename Map <__KeyType, __ValueType>::EntryType, &__hashMapEquals <__KeyType, __ValueType>>,
        &__initializerListNotContains <typename Map <__KeyType, __ValueType>::EntryType, &__hashMapEquals <__KeyType, __ValueType>>
    > {};


template <typename __KeyType, typename __ValueType, typename __Hasher>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __HashMapFindByConstClient :    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalFindByImmutableCompositeClient <
        HashMap <__KeyType, __ValueType, __Hasher>, typename Map <__KeyType, __ValueType>::EntryType,
        HashTableConstIterator <typename Map <__KeyType, __ValueType>::EntryType>
    > {};


template <typename __KeyType, typename __ValueType, typename __Hasher>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __HashMapFindUniqueClient :     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalFindUniqueMutablePrimitiveClient <
        HashMap <__KeyType, __ValueType, __Hasher>, __KeyType,
        HashTableIterator <typename Map <__KeyType, __ValueType>::EntryType>
    > {};


template <typename __KeyType, typename __ValueType, typename __Hasher>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __HashMapFindUniqueConstClient :    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalFindUniqueImmutablePrimitiveClient <
        HashMap <__KeyType, __ValueType, __Hasher>, __KeyType,
        HashTableConstIterator <typename Map <__KeyType, __ValueType>::EntryType>
    > {};


template <typename __KeyType, typename __ValueType, typename __Hasher>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __HashMapRemoveOfIterableClient :   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalRemoveOfCompositeClient <
        HashMap <__KeyType, __ValueType, __Hasher>, typename Map <__KeyType, __ValueType>::EntryType,
        cds::Iterable <typename Map <__KeyType, __ValueType>::EntryType>,
        &__iterableContains <typename Map <__KeyType, __ValueType>::EntryType>
    > {};


template <typename __KeyType, typename __ValueType, typename __Hasher>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __HashMapRemoveOfInitializerListClient : // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalRemoveOfCompositeClient <
        HashMap <__KeyType, __ValueType, __Hasher>, typename Map <__KeyType, __ValueType>::EntryType,
        std::initializer_list <typename Map <__KeyType, __ValueType>::EntryType>,
        &__initializerListContains <typename Map <__KeyType, __ValueType>::EntryType, &__hashMapEquals <__KeyType, __ValueType>>
    > {};


template <typename __KeyType, typename __ValueType, typename __Hasher>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __HashMapRemoveByClient :   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalRemoveByCompositeClient <
        HashMap <__KeyType, __ValueType, __Hasher>, typename Map <__KeyType, __ValueType>::EntryType
    > {};


template <typename __KeyType, typename __ValueType, typename __Hasher>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __HashMapGenericStatementsClient :  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalGenericMutableStatementsCompositeClient <
        HashMap <__KeyType, __ValueType, __Hasher>, typename Map <__KeyType, __ValueType>::EntryType
    > {};


template <typename __KeyType, typename __ValueType, typename __Hasher>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __HashMapConstGenericStatementsClient :  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalGenericImmutableStatementsCompositeClient <
        HashMap <__KeyType, __ValueType, __Hasher>, typename Map <__KeyType, __ValueType>::EntryType
    > {};


template <typename __KeyType, typename __ValueType, typename __Hasher>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __HashMapContainsOfIterableClient : // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalContainsOfCompositeClient <
        HashMap <__KeyType, __ValueType, __Hasher>, typename Map <__KeyType, __ValueType>::EntryType,
        cds::Iterable <typename Map <__KeyType, __ValueType>::EntryType>,
        &__iterableContains <typename Map <__KeyType, __ValueType>::EntryType>
    > {};


template <typename __KeyType, typename __ValueType, typename __Hasher>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __HashMapContainsOfInitializerListClient :  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalContainsOfCompositeClient <
        HashMap <__KeyType, __ValueType, __Hasher>, typename Map <__KeyType, __ValueType>::EntryType,
        std::initializer_list <typename Map <__KeyType, __ValueType>::EntryType>,
        &__initializerListContains <typename Map <__KeyType, __ValueType>::EntryType, &__hashMapEquals <__KeyType, __ValueType>>
    > {};


template <typename __KeyType, typename __ValueType, typename __Hasher>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __HashMapDelegateForwardIterableClient :    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalDelegateForwardIterablePrimitiveClient <
        HashMap <__KeyType, __ValueType, __Hasher>,
        typename __HashMapImplementation < __KeyType, __ValueType, __Hasher >::__ht_Iterator
    > {};


template <typename __KeyType, typename __ValueType, typename __Hasher>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __HashMapDelegateForwardConstIterableClient :   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalDelegateForwardConstIterablePrimitiveClient <
        HashMap <__KeyType, __ValueType, __Hasher>,
        typename __HashMapImplementation < __KeyType, __ValueType, __Hasher >::__ht_ConstIterator
    > {};

} // namespace __impl
} // namespace __hidden
} // namespace cds

#endif // __CDS_HASH_MAP_CONSTRUCTS_HPP__
