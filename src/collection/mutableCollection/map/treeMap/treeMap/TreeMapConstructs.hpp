//
// Created by stefan on 10.10.2022.
//

#ifndef __CDS_TREE_MAP_CONSTRUCTS_HPP__
#define __CDS_TREE_MAP_CONSTRUCTS_HPP__     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
#pragma once

namespace cds {
template <
    typename __KeyType,     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __ValueType,   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __Comparator   = functional::DecoratedPredicate <          // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
        cds::functional::PredicateFunction <__KeyType const&, __KeyType const&>,
        &cds::predicates::lessThan <__KeyType>
    >
> class TreeMap;

namespace __hidden {  // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier)
namespace __impl {    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

template <typename __KeyType, typename __ValueType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
constexpr auto __treeMapKeyExtractor (              // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename Map <__KeyType, __ValueType>::EntryType const& value
) noexcept -> __KeyType const& {
  return value.key();
}


template <typename __KeyType, typename __ValueType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
auto __treeMapCopyConstructor (       // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename Map <__KeyType, __ValueType>::EntryType&       destination,
    typename Map <__KeyType, __ValueType>::EntryType const& source
) noexcept -> void {
  using EntryType = typename Map <__KeyType, __ValueType>::EntryType;
  new (&destination) EntryType(source);
}


template <typename __KeyType, typename __ValueType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
auto __treeMapDestructor (                          // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename Map <__KeyType, __ValueType>::EntryType& element
) noexcept -> void {
  using EntryType = typename Map <__KeyType, __ValueType>::EntryType;
  element.~EntryType();
}


template <typename __KeyType, typename __ValueType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
constexpr auto __treeMapEquals (                    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename Map <__KeyType, __ValueType>::EntryType const& leftEntry, // NOLINT(bugprone-easily-swappable-parameters)
    typename Map <__KeyType, __ValueType>::EntryType const& rightEntry // NOLINT(bugprone-easily-swappable-parameters)
) noexcept -> bool {
  return
      cds::meta::equals (leftEntry.key(), rightEntry.key()) &&
      cds::meta::equals (leftEntry.value(), rightEntry.value());
}


template <typename __KeyType, typename __ValueType, typename __Comparator>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __TreeMapImplementation :   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __RedBlackTree <
        typename Map <__KeyType, __ValueType>::EntryType, __KeyType, __Comparator,
        &__treeMapKeyExtractor <__KeyType, __ValueType>, &cds::meta::equals <__KeyType>,
        &__treeMapDestructor <__KeyType, __ValueType>
    > {};

template <typename __KeyType, typename __ValueType, typename __Comparator>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __TreeMapDispatcher :           // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __TreeMapImplementation <__KeyType, __ValueType, __Comparator>::template __MapDispatcher <
        TreeMap <__KeyType, __ValueType, __Comparator>
    > {};


template <typename __KeyType, typename __ValueType, typename __Comparator>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __TreeMapServer :           // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __MapServer <
        TreeMap <__KeyType, __ValueType, __Comparator>, typename Map <__KeyType, __ValueType>::EntryType
    > {};


template <typename __KeyType, typename __ValueType, typename __Comparator>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __TreeMapDelegateForwardIterableClient :        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalDelegateForwardIterablePrimitiveClient <
        TreeMap <__KeyType, __ValueType, __Comparator>,
        RedBlackTreeForwardIterator <typename Map <__KeyType, __ValueType>::EntryType>
    > {};


template <typename __KeyType, typename __ValueType, typename __Comparator>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __TreeMapDelegateBackwardIterableClient :       // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __hidden::__impl::__LocalDelegateBackwardIterablePrimitiveClient <
        TreeMap <__KeyType, __ValueType, __Comparator>,
        RedBlackTreeBackwardIterator <typename Map <__KeyType, __ValueType>::EntryType>
    > {};


template <typename __KeyType, typename __ValueType, typename __Comparator>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __TreeMapDelegateForwardConstIterableClient :      // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalDelegateForwardConstIterablePrimitiveClient <
        TreeMap <__KeyType, __ValueType, __Comparator>,
        RedBlackTreeForwardConstIterator <typename Map <__KeyType, __ValueType>::EntryType>
    > {};


template <typename __KeyType, typename __ValueType, typename __Comparator>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __TreeMapDelegateBackwardConstIterableClient :      // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __hidden::__impl::__LocalDelegateBackwardConstIterablePrimitiveClient <
        TreeMap <__KeyType, __ValueType, __Comparator>,
        RedBlackTreeBackwardConstIterator <typename Map <__KeyType, __ValueType>::EntryType>
    > {};

template <typename __KeyType, typename __ValueType, typename __Comparator>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __TreeMapIteratorRemoveClient :     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalIteratorRemovePrimitiveClient <
        TreeMap <__KeyType, __ValueType, __Comparator>,
        typename Map <__KeyType, __ValueType>::EntryType,
        AbstractRedBlackTreeIterator <typename Map <__KeyType, __ValueType>::EntryType>
    > {};

template <typename __KeyType, typename __ValueType, typename __Comparator>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __TreeMapConstIteratorRemoveClient :      // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalConstIteratorRemovePrimitiveClient <
        TreeMap <__KeyType, __ValueType, __Comparator>,
        typename Map <__KeyType, __ValueType>::EntryType,
        AbstractRedBlackTreeConstIterator <typename Map <__KeyType, __ValueType>::EntryType>
    > {};

template <typename __KeyType, typename __ValueType, typename __Comparator>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __TreeMapFindUniqueClient :     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalFindUniqueMutablePrimitiveClient <
        TreeMap <__KeyType, __ValueType, __Comparator>, __KeyType,
        AbstractRedBlackTreeIterator <typename Map <__KeyType, __ValueType>::EntryType>
    > {};


template <typename __KeyType, typename __ValueType, typename __Comparator>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __TreeMapFindUniqueConstClient :        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalFindUniqueImmutablePrimitiveClient <
        TreeMap <__KeyType, __ValueType, __Comparator>, __KeyType,
        AbstractRedBlackTreeConstIterator <typename Map <__KeyType, __ValueType>::EntryType>
    > {};


template <typename __KeyType, typename __ValueType, typename __Comparator>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __TreeMapRandomInsertionClient :        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalRandomInsertionPrimitiveClient <
        TreeMap <__KeyType, __ValueType, __Comparator>,
        typename Map <__KeyType, __ValueType>::EntryType,
        typename Map <__KeyType, __ValueType>::EntryType
    > {};


template <typename __KeyType, typename __ValueType, typename __Comparator>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __TreeMapContainsOfCollectionClient :       // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalContainsOfCompositeClient <
        TreeMap <__KeyType, __ValueType, __Comparator>,
        typename Map <__KeyType, __ValueType>::EntryType,
        Iterable <typename Map <__KeyType, __ValueType>::EntryType>,
        &__hidden::__impl::__iterableContains <typename Map <__KeyType, __ValueType>::EntryType>
    > {};


template <typename __KeyType, typename __ValueType, typename __Comparator>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __TreeMapContainsOfInitializerListClient :      // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalContainsOfCompositeClient <
        TreeMap <__KeyType, __ValueType, __Comparator>,
        typename Map <__KeyType, __ValueType>::EntryType,
        std::initializer_list <typename Map <__KeyType, __ValueType>::EntryType>,
        &__hidden::__impl::__initializerListContains <
            typename Map <__KeyType, __ValueType>::EntryType,
            &cds::meta::equals <typename Map <__KeyType, __ValueType>::EntryType>
        >
    > {};


template <typename __KeyType, typename __ValueType, typename __Comparator>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __TreeMapFindByClient :     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalFindByMutableCompositeClient <
        TreeMap <__KeyType, __ValueType, __Comparator>,
        typename Map <__KeyType, __ValueType>::EntryType,
        AbstractRedBlackTreeIterator <typename Map <__KeyType, __ValueType>::EntryType>
    > {};


template <typename __KeyType, typename __ValueType, typename __Comparator>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __TreeMapFindByConstClient :     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalFindByImmutableCompositeClient <
        TreeMap <__KeyType, __ValueType, __Comparator>,
        typename Map <__KeyType, __ValueType>::EntryType,
        AbstractRedBlackTreeConstIterator <typename Map <__KeyType, __ValueType>::EntryType>
    > {};


template <typename __KeyType, typename __ValueType, typename __Comparator>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __TreeMapFindOfCollectionClient :     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalFindOfMutableCompositeClient <
        TreeMap <__KeyType, __ValueType, __Comparator>,
        typename Map <__KeyType, __ValueType>::EntryType,
        AbstractRedBlackTreeIterator <typename Map <__KeyType, __ValueType>::EntryType>,
        Iterable <typename Map <__KeyType, __ValueType>::EntryType>,
        &__hidden::__impl::__iterableContains <typename Map <__KeyType, __ValueType>::EntryType>,
        &__hidden::__impl::__iterableNotContains <typename Map <__KeyType, __ValueType>::EntryType>
    > {};


template <typename __KeyType, typename __ValueType, typename __Comparator>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __TreeMapFindOfInitializerListClient :     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalFindOfMutableCompositeClient <
        TreeMap <__KeyType, __ValueType, __Comparator>,
        typename Map <__KeyType, __ValueType>::EntryType,
        AbstractRedBlackTreeIterator <typename Map <__KeyType, __ValueType>::EntryType>,
        std::initializer_list <typename Map <__KeyType, __ValueType>::EntryType>,
        &__hidden::__impl::__initializerListContains <
            typename Map <__KeyType, __ValueType>::EntryType,
            &cds::meta::equals <typename Map <__KeyType, __ValueType>::EntryType>
        >,
        &__hidden::__impl::__initializerListNotContains <
            typename Map <__KeyType, __ValueType>::EntryType,
            &cds::meta::equals <typename Map <__KeyType, __ValueType>::EntryType>
        >
    > {};


template <typename __KeyType, typename __ValueType, typename __Comparator>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __TreeMapFindOfConstCollectionClient :     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalFindOfImmutableCompositeClient <
        TreeMap <__KeyType, __ValueType, __Comparator>,
        typename Map <__KeyType, __ValueType>::EntryType,
        AbstractRedBlackTreeConstIterator <typename Map <__KeyType, __ValueType>::EntryType>,
        Iterable <typename Map <__KeyType, __ValueType>::EntryType>,
        &__hidden::__impl::__iterableContains <typename Map <__KeyType, __ValueType>::EntryType>,
        &__hidden::__impl::__iterableNotContains <typename Map <__KeyType, __ValueType>::EntryType>
    > {};


template <typename __KeyType, typename __ValueType, typename __Comparator>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __TreeMapFindOfConstInitializerListClient :     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalFindOfMutableCompositeClient <
        TreeMap <__KeyType, __ValueType, __Comparator>,
        typename Map <__KeyType, __ValueType>::EntryType,
        AbstractRedBlackTreeConstIterator <typename Map <__KeyType, __ValueType>::EntryType>,
        std::initializer_list <typename Map <__KeyType, __ValueType>::EntryType>,
        &__hidden::__impl::__initializerListContains <
            typename Map <__KeyType, __ValueType>::EntryType,
            &cds::meta::equals <typename Map <__KeyType, __ValueType>::EntryType>
        >,
        &__hidden::__impl::__initializerListNotContains <
            typename Map <__KeyType, __ValueType>::EntryType,
            &cds::meta::equals <typename Map <__KeyType, __ValueType>::EntryType>
        >
    > {};


template <typename __KeyType, typename __ValueType, typename __Comparator>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __TreeMapGenericStatementsClient :     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalGenericMutableStatementsCompositeClient <
        TreeMap <__KeyType, __ValueType, __Comparator>, typename Map <__KeyType, __ValueType>::EntryType
    > {};


template <typename __KeyType, typename __ValueType, typename __Comparator>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __TreeMapConstGenericStatementsClient :     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalGenericImmutableStatementsCompositeClient <
        TreeMap <__KeyType, __ValueType, __Comparator>, typename Map <__KeyType, __ValueType>::EntryType
    > {};


template <typename __KeyType, typename __ValueType, typename __Comparator>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __TreeMapRemoveByClient :     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalRemoveByCompositeClient <
        TreeMap <__KeyType, __ValueType, __Comparator>, typename Map <__KeyType, __ValueType>::EntryType
    > {};


template <typename __KeyType, typename __ValueType, typename __Comparator>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __TreeMapRemoveOfCollectionClient :     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalRemoveOfCompositeClient <
        TreeMap <__KeyType, __ValueType, __Comparator>,
        typename Map <__KeyType, __ValueType>::EntryType,
        Iterable <typename Map <__KeyType, __ValueType>::EntryType>,
        &__hidden::__impl::__iterableContains <typename Map <__KeyType, __ValueType>::EntryType>
    > {};


template <typename __KeyType, typename __ValueType, typename __Comparator>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __TreeMapRemoveOfInitializerListClient :     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalRemoveOfCompositeClient <
        TreeMap <__KeyType, __ValueType, __Comparator>,
        typename Map <__KeyType, __ValueType>::EntryType,
        std::initializer_list <typename Map <__KeyType, __ValueType>::EntryType>,
        &__hidden::__impl::__initializerListContains <
            typename Map <__KeyType, __ValueType>::EntryType,
            &cds::meta::equals <typename Map <__KeyType, __ValueType>::EntryType>
        >
    > {};
} // namespace __impl
} // namespace __hidden
} // namespace cds

#endif // __CDS_TREE_MAP_CONSTRUCTS_HPP__
