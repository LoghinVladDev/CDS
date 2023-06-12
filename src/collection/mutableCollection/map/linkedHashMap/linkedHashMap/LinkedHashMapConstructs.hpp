// NOLINT(llvm-header-guard)
// Created by loghin on 09/10/22.
//

#ifndef __CDS_LINKED_HASH_MAP_CONSTRUCTS_HPP__ // NOLINT(llvm-header-guard)
#define __CDS_LINKED_HASH_MAP_CONSTRUCTS_HPP__ // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
#pragma once

namespace cds {
template <
    typename __KeyType,                                                   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __ValueType,                                                 // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __Hasher = cds::WrapperHasher <__KeyType, Hash <__KeyType>>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> class LinkedHashMap;

namespace __hidden {  // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
namespace __impl {    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

template <typename __KeyType, typename __ValueType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
constexpr auto __linkedHashMapKeyExtractor (        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    __UnidirectionalNode <MapEntry <__KeyType, __ValueType>>* const& pNode
) noexcept -> __KeyType const& {
  return pNode->_data.key();
}


template <typename __KeyType, typename __ValueType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_MaybeUnused __CDS_cpplang_ConstexprNonLiteralReturn auto __linkedHashMapCopyConstructor (   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-avoid-non-const-global-variables)
    __UnidirectionalNode <MapEntry <__KeyType, __ValueType>>*&        destination,
    __UnidirectionalNode <MapEntry <__KeyType, __ValueType>>* const&  source
) noexcept -> void {
  destination = source;
}


template <typename __KeyType, typename __ValueType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_ConstexprNonLiteralReturn auto __linkedHashMapDestructor (  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    __UnidirectionalNode <MapEntry <__KeyType, __ValueType>>*& node
) noexcept -> void {
  (void) node;
}


template <typename __KeyType, typename __ValueType>                                 // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_ConstexprNonLiteralReturn auto __linkedHashMapLinkedListRemoveIf (    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    __KeyType const& key, MapEntry <__KeyType, __ValueType> const& entry
) noexcept -> bool {
  return cds::meta::equals (key, entry.key());
}


template <typename __KeyType, typename __ValueType, typename __Hasher>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __LinkedHashMapHashTableImplementation :    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __HashTable <
        __UnidirectionalNode <MapEntry <__KeyType, __ValueType>>*, __KeyType, __Hasher,
        cds::__hidden::__impl::__PrimeRehashPolicy <uint32>, &__linkedHashMapKeyExtractor <__KeyType, __ValueType>,
        &cds::meta::equals <__KeyType>, &__linkedHashMapDestructor <__KeyType, __ValueType>
    > {};


template <typename __KeyType, typename __ValueType, typename __Hasher>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __LinkedHashMapLinkedListImplementation :   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __SingleLinkedList <
        typename Map <__KeyType, __ValueType>::EntryType,
        &cds::meta::equals <MapEntry <__KeyType, __ValueType>>
    > {};


template <typename __KeyType, typename __ValueType, typename __Hasher>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
using __LinkedHashMapIterator =   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __LinkedHashMapLinkedListImplementation <__KeyType, __ValueType, __Hasher>::__sll_Iterator;


template <typename __KeyType, typename __ValueType, typename __Hasher>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
using __LinkedHashMapConstIterator =  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __LinkedHashMapLinkedListImplementation <__KeyType, __ValueType, __Hasher>::__sll_ConstIterator;


template <typename __KeyType, typename __ValueType, typename __Hasher>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __LinkedHashMapServer :     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __MapServer <
        LinkedHashMap <__KeyType, __ValueType, __Hasher>,
        typename Map <__KeyType, __ValueType>::EntryType
    > {};


template <typename __KeyType, typename __ValueType, typename __Hasher>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __LinkedHashMapRandomInsertionClient :  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalRandomInsertionPrimitiveClient <
        LinkedHashMap <__KeyType, __ValueType, __Hasher>,
        typename Map <__KeyType, __ValueType>::EntryType,
        typename Map <__KeyType, __ValueType>::EntryType
    > {};


template <typename __KeyType, typename __ValueType, typename __Hasher>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __LinkedHashMapIteratorRemoveClient :   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalIteratorRemovePrimitiveClient <
        LinkedHashMap <__KeyType, __ValueType, __Hasher>,
        typename Map <__KeyType, __ValueType>::EntryType,
        __LinkedHashMapIterator <__KeyType, __ValueType, __Hasher>
    > {};


template <typename __KeyType, typename __ValueType, typename __Hasher>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __LinkedHashMapConstIteratorRemoveClient :  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalConstIteratorRemovePrimitiveClient <
        LinkedHashMap <__KeyType, __ValueType, __Hasher>,
        typename Map <__KeyType, __ValueType>::EntryType,
        __LinkedHashMapConstIterator <__KeyType, __ValueType, __Hasher>
    > {};


template <typename __KeyType, typename __ValueType, typename __Hasher>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __LinkedHashMapFindOfIterableClient :   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalFindOfMutableCompositeClient <
        LinkedHashMap <__KeyType, __ValueType, __Hasher>,
        typename Map <__KeyType, __ValueType>::EntryType,
        __LinkedHashMapIterator <__KeyType, __ValueType, __Hasher>,
        cds::Iterable <typename Map <__KeyType, __ValueType>::EntryType>,
        &__iterableContains <typename Map <__KeyType, __ValueType>::EntryType>,
        &__iterableNotContains <typename Map <__KeyType, __ValueType>::EntryType>
    > {};


template <typename __KeyType, typename __ValueType, typename __Hasher>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __LinkedHashMapFindOfInitializerListClient :  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalFindOfMutableCompositeClient <
        LinkedHashMap <__KeyType, __ValueType, __Hasher>,
        typename Map <__KeyType, __ValueType>::EntryType,
        __LinkedHashMapIterator <__KeyType, __ValueType, __Hasher>,
        std::initializer_list <typename Map <__KeyType, __ValueType>::EntryType>,
        &__initializerListContains <typename Map <__KeyType, __ValueType>::EntryType, &cds::meta::equals <MapEntry <__KeyType, __ValueType>>>,
        &__initializerListNotContains <typename Map <__KeyType, __ValueType>::EntryType, &cds::meta::equals <MapEntry <__KeyType, __ValueType>>>
    > {};


template <typename __KeyType, typename __ValueType, typename __Hasher>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __LinkedHashMapFindByClient :   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalFindByMutableCompositeClient <
        LinkedHashMap <__KeyType, __ValueType, __Hasher>,
        typename Map <__KeyType, __ValueType>::EntryType,
        __LinkedHashMapIterator <__KeyType, __ValueType, __Hasher>
    > {};


template <typename __KeyType, typename __ValueType, typename __Hasher>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __LinkedHashMapFindOfConstIterableClient :  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalFindOfImmutableCompositeClient <
        LinkedHashMap <__KeyType, __ValueType, __Hasher>,
        typename Map <__KeyType, __ValueType>::EntryType,
        __LinkedHashMapConstIterator <__KeyType, __ValueType, __Hasher>,
        cds::Iterable <typename Map <__KeyType, __ValueType>::EntryType>,
        &__iterableContains <typename Map <__KeyType, __ValueType>::EntryType>,
        &__iterableNotContains <typename Map <__KeyType, __ValueType>::EntryType>
    > {};


template <typename __KeyType, typename __ValueType, typename __Hasher>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __LinkedHashMapFindOfConstInitializerListClient :   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalFindOfImmutableCompositeClient <
        LinkedHashMap <__KeyType, __ValueType, __Hasher>,
        typename Map <__KeyType, __ValueType>::EntryType,
        __LinkedHashMapConstIterator <__KeyType, __ValueType, __Hasher>,
        std::initializer_list <typename Map <__KeyType, __ValueType>::EntryType>,
        &__initializerListContains <typename Map <__KeyType, __ValueType>::EntryType, &cds::meta::equals <MapEntry <__KeyType, __ValueType>>>,
        &__initializerListNotContains <typename Map <__KeyType, __ValueType>::EntryType, &cds::meta::equals <MapEntry <__KeyType, __ValueType>>>
    > {};


template <typename __KeyType, typename __ValueType, typename __Hasher>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __LinkedHashMapFindByConstClient :  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalFindByImmutableCompositeClient <
        LinkedHashMap <__KeyType, __ValueType, __Hasher>,
        typename Map <__KeyType, __ValueType>::EntryType,
        __LinkedHashMapConstIterator <__KeyType, __ValueType, __Hasher>
    > {};


template <typename __KeyType, typename __ValueType, typename __Hasher>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __LinkedHashMapFindUniqueClient :   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalFindUniqueMutablePrimitiveClient <
        LinkedHashMap <__KeyType, __ValueType, __Hasher>, __KeyType,
        __LinkedHashMapIterator <__KeyType, __ValueType, __Hasher>
    > {};


template <typename __KeyType, typename __ValueType, typename __Hasher>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __LinkedHashMapFindUniqueConstClient :  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalFindUniqueImmutablePrimitiveClient <
        LinkedHashMap <__KeyType, __ValueType, __Hasher>, __KeyType,
        __LinkedHashMapConstIterator <__KeyType, __ValueType, __Hasher>
    > {};


template <typename __KeyType, typename __ValueType, typename __Hasher>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __LinkedHashMapRemoveOfIterableClient : // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalRemoveOfCompositeClient <
        LinkedHashMap <__KeyType, __ValueType, __Hasher>,
        typename Map <__KeyType, __ValueType>::EntryType,
        cds::Iterable <typename Map <__KeyType, __ValueType>::EntryType>,
        &__iterableContains <typename Map <__KeyType, __ValueType>::EntryType>
    > {};


template <
    typename __KeyType,                             // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __ValueType,                           // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __Hasher                               // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> class __CDS_InheritsEBOs __LinkedHashMapRemoveOfInitializerListClient :  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalRemoveOfCompositeClient <
        LinkedHashMap <__KeyType, __ValueType, __Hasher>,
        typename Map <__KeyType, __ValueType>::EntryType,
        std::initializer_list <typename Map <__KeyType, __ValueType>::EntryType>,
        &__initializerListContains <typename Map <__KeyType, __ValueType>::EntryType, &cds::meta::equals <MapEntry <__KeyType, __ValueType>>>
    > {};


template <typename __KeyType, typename __ValueType, typename __Hasher>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __LinkedHashMapRemoveByClient : // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalRemoveByCompositeClient <
        LinkedHashMap <__KeyType, __ValueType, __Hasher>, typename Map <__KeyType, __ValueType>::EntryType
    > {};


template <typename __KeyType, typename __ValueType, typename __Hasher>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __LinkedHashMapGenericStatementsClient :    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalGenericMutableStatementsCompositeClient <
        LinkedHashMap <__KeyType, __ValueType, __Hasher>, typename Map <__KeyType, __ValueType>::EntryType
    > {};


template <
    typename __KeyType,                             // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __ValueType,                           // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __Hasher                               // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> class __CDS_InheritsEBOs __LinkedHashMapConstGenericStatementsClient :   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalGenericImmutableStatementsCompositeClient <
        LinkedHashMap <__KeyType, __ValueType, __Hasher>, typename Map <__KeyType, __ValueType>::EntryType
    > {};


template <typename __KeyType, typename __ValueType, typename __Hasher>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __LinkedHashMapContainsOfIterableClient :   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalContainsOfCompositeClient <
        LinkedHashMap <__KeyType, __ValueType, __Hasher>,
        typename Map <__KeyType, __ValueType>::EntryType,
        cds::Iterable <typename Map <__KeyType, __ValueType>::EntryType>,
        &__iterableContains <typename Map <__KeyType, __ValueType>::EntryType>
    > {};


template <typename __KeyType, typename __ValueType, typename __Hasher>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __LinkedHashMapContainsOfInitializerListClient :    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalContainsOfCompositeClient <
        LinkedHashMap <__KeyType, __ValueType, __Hasher>,
        typename Map <__KeyType, __ValueType>::EntryType,
        std::initializer_list <typename Map <__KeyType, __ValueType>::EntryType>,
        &__initializerListContains <typename Map <__KeyType, __ValueType>::EntryType, &cds::meta::equals <MapEntry <__KeyType, __ValueType>>>
    > {};


template <
    typename __KeyType,                             // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __ValueType,                           // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __Hasher                               // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> class __CDS_InheritsEBOs __LinkedHashMapDelegateForwardIterableClient :  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalDelegateForwardIterablePrimitiveClient <
        cds::LinkedHashMap <__KeyType, __ValueType, __Hasher>, __LinkedHashMapIterator <__KeyType, __ValueType, __Hasher>
    > {};


template <typename __KeyType, typename __ValueType, typename __Hasher>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __LinkedHashMapDelegateForwardConstIterableClient : // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalDelegateForwardConstIterablePrimitiveClient <
        cds::LinkedHashMap <__KeyType, __ValueType, __Hasher>, __LinkedHashMapConstIterator <__KeyType, __ValueType, __Hasher>
    > {};

} // namespace __impl
} // namespace __hidden
} // namespace cds

#endif // __CDS_LINKED_HASH_MAP_CONSTRUCTS_HPP__
