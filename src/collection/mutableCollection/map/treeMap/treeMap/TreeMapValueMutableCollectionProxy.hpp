//
// Created by stefan on 13.10.2022.
//

#ifndef __CDS_TREE_MAP_VALUE_MUTABLE_COLLECTION_PROXY_HPP__
#define __CDS_TREE_MAP_VALUE_MUTABLE_COLLECTION_PROXY_HPP__ // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
#pragma once

namespace cds {       // NOLINT(modernize-concat-nested-namespaces)
namespace __hidden {  // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier)
namespace __impl {    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename __ServerType, typename __KeyType, typename __ValueType>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __TreeMapValueProxyServer :                        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __MutableCollectionServer <__ServerType, __ValueType> {};


template <typename __DecoratedIteratorType, typename __ValueAtType>             // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
constexpr auto __treeMapValueMutableCollectionProxyIteratorDecoratorValueAt (   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    __DecoratedIteratorType const& iterator
) noexcept -> __ValueAtType& {
  return (*iterator).value ();
}


template <typename __KeyType, typename __ValueType, typename __Comparator>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
using __TreeMapValueProxyAbstractIterator =        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    BidirectionalIteratorGenericDecorator <
        typename __TreeMapImplementation <__KeyType, __ValueType, __Comparator>::__rbt_AbstractIterator,
        __ValueType,
        &__treeMapValueMutableCollectionProxyIteratorDecoratorValueAt <
            typename __TreeMapImplementation <__KeyType, __ValueType, __Comparator>::__rbt_AbstractIterator,
            __ValueType
        >
    >;


template <typename __KeyType, typename __ValueType, typename __Comparator>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
using __TreeMapValueProxyAbstractConstIterator =       // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    BidirectionalIteratorGenericDecorator <
        typename __TreeMapImplementation <__KeyType, __ValueType, __Comparator>::__rbt_AbstractConstIterator,
        __ValueType const,
        &__treeMapValueMutableCollectionProxyIteratorDecoratorValueAt <
            typename __TreeMapImplementation <__KeyType, __ValueType, __Comparator>::__rbt_AbstractConstIterator,
            __ValueType const
        >
    >;


template <typename __KeyType, typename __ValueType, typename __Comparator>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
using __TreeMapValueProxyForwardIterator =        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    BidirectionalIteratorGenericDecorator <
        typename __TreeMapImplementation <__KeyType, __ValueType, __Comparator>::__rbt_Iterator,
        __ValueType,
        &__treeMapValueMutableCollectionProxyIteratorDecoratorValueAt <
            typename __TreeMapImplementation <__KeyType, __ValueType, __Comparator>::__rbt_Iterator,
            __ValueType
        >
    >;


template <typename __KeyType, typename __ValueType, typename __Comparator>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
using __TreeMapValueProxyForwardConstIterator =       // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    BidirectionalIteratorGenericDecorator <
        typename __TreeMapImplementation <__KeyType, __ValueType, __Comparator>::__rbt_ConstIterator,
        __ValueType const,
        &__treeMapValueMutableCollectionProxyIteratorDecoratorValueAt <
            typename __TreeMapImplementation <__KeyType, __ValueType, __Comparator>::__rbt_ConstIterator,
            __ValueType const
        >
    >;


template <typename __KeyType, typename __ValueType, typename __Comparator>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
using __TreeMapValueProxyBackwardIterator =        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    BidirectionalIteratorGenericDecorator <
        typename __TreeMapImplementation <__KeyType, __ValueType, __Comparator>::__rbt_ReverseIterator,
        __ValueType,
        &__treeMapValueMutableCollectionProxyIteratorDecoratorValueAt <
            typename __TreeMapImplementation <__KeyType, __ValueType, __Comparator>::__rbt_ReverseIterator,
            __ValueType
        >
    >;


template <typename __KeyType, typename __ValueType, typename __Comparator>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
using __TreeMapValueProxyBackwardConstIterator =       // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    BidirectionalIteratorGenericDecorator <
        typename __TreeMapImplementation <__KeyType, __ValueType, __Comparator>::__rbt_ReverseConstIterator,
        __ValueType const,
        &__treeMapValueMutableCollectionProxyIteratorDecoratorValueAt <
            typename __TreeMapImplementation <__KeyType, __ValueType, __Comparator>::__rbt_ReverseConstIterator,
            __ValueType const
        >
    >;


template <typename __ServerType, typename __KeyType, typename __ValueType, typename __Comparator> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __TreeMapValueProxyConstIteratorRemoveClient :      // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalConstIteratorRemovePrimitiveClient <
        __ServerType, __ValueType, __TreeMapValueProxyAbstractConstIterator <__KeyType, __ValueType, __Comparator>
    > {};


template <typename __ServerType, typename __KeyType, typename __ValueType, typename __Comparator> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __TreeMapValueProxyIteratorRemoveClient :      // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalIteratorRemovePrimitiveClient <
        __ServerType, __ValueType, __TreeMapValueProxyAbstractIterator <__KeyType, __ValueType, __Comparator>
    > {};


template <typename __ServerType, typename __KeyType, typename __ValueType, typename __Comparator> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __TreeMapValueProxyDelegateBackwardConstIterableClient :        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalDelegateBackwardConstIterablePrimitiveClient  <
        __ServerType, __TreeMapValueProxyBackwardConstIterator <__KeyType, __ValueType, __Comparator>
    > {};


template <typename __ServerType, typename __KeyType, typename __ValueType, typename __Comparator> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __TreeMapValueProxyDelegateBackwardIterableClient :         // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalDelegateBackwardIterablePrimitiveClient  <
        __ServerType, __TreeMapValueProxyBackwardIterator <__KeyType, __ValueType, __Comparator>
    > {};


template <typename __ServerType, typename __KeyType, typename __ValueType, typename __Comparator> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __TreeMapValueProxyDelegateForwardConstIterableClient :     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalDelegateForwardConstIterablePrimitiveClient  <
        __ServerType, __TreeMapValueProxyForwardConstIterator <__KeyType, __ValueType, __Comparator>
    > {};


template <typename __ServerType, typename __KeyType, typename __ValueType, typename __Comparator> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __TreeMapValueProxyDelegateForwardIterableClient :      // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalDelegateForwardIterablePrimitiveClient  <
        __ServerType, __TreeMapValueProxyForwardIterator <__KeyType, __ValueType, __Comparator>
    > {};


template <typename __ServerType, typename __KeyType, typename __ValueType, typename __Comparator> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __TreeMapValueProxyRandomInsertionClient :      // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalRandomInsertionPrimitiveClient <__ServerType, __ValueType, __ValueType const> {};


template <typename __ServerType, typename __KeyType, typename __ValueType, typename __Comparator> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __TreeMapValueProxyContainsOfCollectionClient :     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalContainsOfCompositeClient <
        __ServerType, __ValueType, cds::Iterable <__ValueType>, &__iterableContains <__ValueType>
    > {};


template <typename __ServerType, typename __KeyType, typename __ValueType, typename __Comparator> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __TreeMapValueProxyContainsOfInitializerListClient :     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalContainsOfCompositeClient <
        __ServerType, __ValueType, std::initializer_list <__ValueType>,
    &__initializerListContains <__ValueType, &cds::meta::equals <__ValueType>>
> {};


template <typename __ServerType, typename __KeyType, typename __ValueType, typename __Comparator> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __TreeMapValueProxyFindByImmutableClient :      // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalFindByImmutableCompositeClient <
        __ServerType, __ValueType, __TreeMapValueProxyAbstractConstIterator <__KeyType, __ValueType, __Comparator>
> {};


template <typename __ServerType, typename __KeyType, typename __ValueType, typename __Comparator> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __TreeMapValueProxyFindByMutableClient :      // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalFindByMutableCompositeClient <
        __ServerType, __ValueType, __TreeMapValueProxyAbstractIterator <__KeyType, __ValueType, __Comparator>
> {};


template <typename __ServerType, typename __KeyType, typename __ValueType, typename __Comparator> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __TreeMapValueProxyFindOfConstCollectionClient :        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalFindOfImmutableCompositeClient <
        __ServerType, __ValueType,
        __TreeMapValueProxyAbstractConstIterator <__KeyType, __ValueType, __Comparator>,
    Iterable <__ValueType>, &__iterableContains <__ValueType>, &__iterableNotContains <__ValueType>
> {};


template <typename __ServerType, typename __KeyType, typename __ValueType, typename __Comparator> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __TreeMapValueProxyFindOfConstInitializerListClient :        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalFindOfImmutableCompositeClient <
        __ServerType, __ValueType,
        __TreeMapValueProxyAbstractConstIterator <__KeyType, __ValueType, __Comparator>,
    std::initializer_list <__ValueType>,
    &__initializerListContains <__ValueType, &cds::meta::equals <__ValueType>>,
    &__initializerListNotContains <__ValueType, &cds::meta::equals <__ValueType>>
> {};


template <typename __ServerType, typename __KeyType, typename __ValueType, typename __Comparator> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __TreeMapValueProxyFindOfCollectionClient :        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalFindOfImmutableCompositeClient <
        __ServerType, __ValueType,
        __TreeMapValueProxyAbstractIterator <__KeyType, __ValueType, __Comparator>,
    Iterable <__ValueType>, &__iterableContains <__ValueType>, &__iterableNotContains <__ValueType>
> {};


template <typename __ServerType, typename __KeyType, typename __ValueType, typename __Comparator> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __TreeMapValueProxyFindOfInitializerListClient :        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalFindOfImmutableCompositeClient <
        __ServerType, __ValueType,
        __TreeMapValueProxyAbstractIterator <__KeyType, __ValueType, __Comparator>,
    std::initializer_list <__ValueType>,
    &__initializerListContains <__ValueType, &cds::meta::equals <__ValueType>>,
    &__initializerListNotContains <__ValueType, &cds::meta::equals <__ValueType>>
> {};


template <typename __ServerType, typename __KeyType, typename __ValueType, typename __Comparator> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __TreeMapValueProxyConstGenericStatementsClient :       // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalGenericImmutableStatementsCompositeClient <__ServerType, __ValueType> {};


template <typename __ServerType, typename __KeyType, typename __ValueType, typename __Comparator> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __TreeMapValueProxyGenericStatementsClient :       // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalGenericMutableStatementsCompositeClient <__ServerType, __ValueType> {};


template <
    typename __ServerType,                    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __KeyType,                       // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __ValueType                      // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> class __CDS_InheritsEBOs __TreeMapValueProxyRemoveByClient :       // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalRemoveByCompositeClient <__ServerType, __ValueType> {};


template <
    typename __ServerType,                            // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __KeyType,                               // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __ValueType                              // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> class __CDS_InheritsEBOs __TreeMapValueProxyRemoveOfCollectionClient :     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalRemoveOfCompositeClient <
        __ServerType, __ValueType, cds::Iterable <__ValueType>, &__iterableContains <__ValueType>
    > {};


template <
    typename __ServerType,                                 // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __KeyType,                                    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __ValueType                                   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> class __CDS_InheritsEBOs __TreeMapValueProxyRemoveOfInitializerListClient :     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalRemoveOfCompositeClient <
        __ServerType, __ValueType, std::initializer_list <__ValueType>,
    &__initializerListContains <__ValueType, &cds::meta::equals <__ValueType>>
> {};

} // namespace __impl
} // namespace __hidden

template <typename __KeyType, typename __ValueType, typename __Comparator>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs TreeMap <__KeyType, __ValueType, __Comparator>::ValueMutableCollectionProxy :
    public TreeMap <__KeyType, __ValueType>::AbstractValueMutableCollectionProxy,
    private __hidden::__impl::__TreeMapValueProxyServer <ValueMutableCollectionProxy, __KeyType, __ValueType>,
    public __hidden::__impl::__TreeMapValueProxyConstIteratorRemoveClient <ValueMutableCollectionProxy, __KeyType, __ValueType, __Comparator>,
    public __hidden::__impl::__TreeMapValueProxyIteratorRemoveClient <ValueMutableCollectionProxy, __KeyType, __ValueType, __Comparator>,
    public __hidden::__impl::__TreeMapValueProxyDelegateBackwardConstIterableClient <ValueMutableCollectionProxy, __KeyType, __ValueType, __Comparator>,
    public __hidden::__impl::__TreeMapValueProxyDelegateBackwardIterableClient <ValueMutableCollectionProxy, __KeyType, __ValueType, __Comparator>,
    public __hidden::__impl::__TreeMapValueProxyDelegateForwardConstIterableClient <ValueMutableCollectionProxy, __KeyType, __ValueType, __Comparator>,
    public __hidden::__impl::__TreeMapValueProxyDelegateForwardIterableClient <ValueMutableCollectionProxy, __KeyType, __ValueType, __Comparator>,
    public __hidden::__impl::__TreeMapValueProxyRandomInsertionClient <ValueMutableCollectionProxy, __KeyType, __ValueType, __Comparator>,
    public __hidden::__impl::__TreeMapValueProxyContainsOfCollectionClient <ValueMutableCollectionProxy, __KeyType, __ValueType, __Comparator>,
    public __hidden::__impl::__TreeMapValueProxyContainsOfInitializerListClient <ValueMutableCollectionProxy, __KeyType, __ValueType, __Comparator>,
    public __hidden::__impl::__TreeMapValueProxyFindByImmutableClient <ValueMutableCollectionProxy, __KeyType, __ValueType, __Comparator>,
    public __hidden::__impl::__TreeMapValueProxyFindByMutableClient <ValueMutableCollectionProxy, __KeyType, __ValueType, __Comparator>,
    public __hidden::__impl::__TreeMapValueProxyFindOfConstCollectionClient <ValueMutableCollectionProxy, __KeyType, __ValueType, __Comparator>,
    public __hidden::__impl::__TreeMapValueProxyFindOfConstInitializerListClient <ValueMutableCollectionProxy, __KeyType, __ValueType, __Comparator>,
    public __hidden::__impl::__TreeMapValueProxyFindOfCollectionClient <ValueMutableCollectionProxy, __KeyType, __ValueType, __Comparator>,
    public __hidden::__impl::__TreeMapValueProxyFindOfInitializerListClient <ValueMutableCollectionProxy, __KeyType, __ValueType, __Comparator>,
    public __hidden::__impl::__TreeMapValueProxyConstGenericStatementsClient <ValueMutableCollectionProxy, __KeyType, __ValueType, __Comparator>,
    public __hidden::__impl::__TreeMapValueProxyGenericStatementsClient <ValueMutableCollectionProxy, __KeyType, __ValueType, __Comparator>,
    public __hidden::__impl::__TreeMapValueProxyRemoveByClient <ValueMutableCollectionProxy, __KeyType, __ValueType>,
    public __hidden::__impl::__TreeMapValueProxyRemoveOfCollectionClient <ValueMutableCollectionProxy, __KeyType, __ValueType>,
    public __hidden::__impl::__TreeMapValueProxyRemoveOfInitializerListClient <ValueMutableCollectionProxy, __KeyType, __ValueType> {

protected:
  using TreeMapBase                         = TreeMap <__KeyType, __ValueType, __Comparator>;
  using Server                              = __hidden::__impl::__TreeMapValueProxyServer <ValueMutableCollectionProxy, __KeyType, __ValueType>;
  using ConstIteratorRemoveClient           = __hidden::__impl::__TreeMapValueProxyConstIteratorRemoveClient <ValueMutableCollectionProxy, __KeyType, __ValueType, __Comparator>;
  using IteratorRemoveClient                = __hidden::__impl::__TreeMapValueProxyIteratorRemoveClient <ValueMutableCollectionProxy, __KeyType, __ValueType, __Comparator>;
  using DelegateBackwardConstIterableClient = __hidden::__impl::__TreeMapValueProxyDelegateBackwardConstIterableClient <ValueMutableCollectionProxy, __KeyType, __ValueType, __Comparator>;
  using DelegateBackwardIterableClient      = __hidden::__impl::__TreeMapValueProxyDelegateBackwardIterableClient <ValueMutableCollectionProxy, __KeyType, __ValueType, __Comparator>;
  using DelegateForwardConstIterableClient  = __hidden::__impl::__TreeMapValueProxyDelegateForwardConstIterableClient <ValueMutableCollectionProxy, __KeyType, __ValueType, __Comparator>;
  using DelegateForwardIterableClient       = __hidden::__impl::__TreeMapValueProxyDelegateForwardIterableClient <ValueMutableCollectionProxy, __KeyType, __ValueType, __Comparator>;
  using RandomInsertionClient               = __hidden::__impl::__TreeMapValueProxyRandomInsertionClient <ValueMutableCollectionProxy, __KeyType, __ValueType, __Comparator>;
  using ContainsOfCollectionClient          = __hidden::__impl::__TreeMapValueProxyContainsOfCollectionClient <ValueMutableCollectionProxy, __KeyType, __ValueType, __Comparator>;
  using ContainsOfInitializerListClient     = __hidden::__impl::__TreeMapValueProxyContainsOfInitializerListClient <ValueMutableCollectionProxy, __KeyType, __ValueType, __Comparator>;
  using FindByImmutableClient               = __hidden::__impl::__TreeMapValueProxyFindByImmutableClient <ValueMutableCollectionProxy, __KeyType, __ValueType, __Comparator>;
  using FindByMutableClient                 = __hidden::__impl::__TreeMapValueProxyFindByMutableClient <ValueMutableCollectionProxy, __KeyType, __ValueType, __Comparator>;
  using FindOfConstCollectionClient         = __hidden::__impl::__TreeMapValueProxyFindOfConstCollectionClient <ValueMutableCollectionProxy, __KeyType, __ValueType, __Comparator>;
  using FindOfConstInitializerListClient    = __hidden::__impl::__TreeMapValueProxyFindOfConstInitializerListClient <ValueMutableCollectionProxy, __KeyType, __ValueType, __Comparator>;
  using FindOfCollectionClient              = __hidden::__impl::__TreeMapValueProxyFindOfCollectionClient <ValueMutableCollectionProxy, __KeyType, __ValueType, __Comparator>;
  using FindOfInitializerListClient         = __hidden::__impl::__TreeMapValueProxyFindOfInitializerListClient <ValueMutableCollectionProxy, __KeyType, __ValueType, __Comparator>;
  using ConstGenericStatementsClient        = __hidden::__impl::__TreeMapValueProxyConstGenericStatementsClient <ValueMutableCollectionProxy, __KeyType, __ValueType, __Comparator>;
  using GenericStatementsClient             = __hidden::__impl::__TreeMapValueProxyGenericStatementsClient <ValueMutableCollectionProxy, __KeyType, __ValueType, __Comparator>;
  using RemoveByClient                      = __hidden::__impl::__TreeMapValueProxyRemoveByClient <ValueMutableCollectionProxy, __KeyType, __ValueType>;
  using RemoveOfCollectionClient            = __hidden::__impl::__TreeMapValueProxyRemoveOfCollectionClient <ValueMutableCollectionProxy, __KeyType, __ValueType>;
  using RemoveOfInitializerListClient       = __hidden::__impl::__TreeMapValueProxyRemoveOfInitializerListClient <ValueMutableCollectionProxy, __KeyType, __ValueType>;

  using AbstractIterator                    = typename IteratorRemoveClient::Iterator;
  using AbstractConstIterator               = typename ConstIteratorRemoveClient::ConstIterator;

public:
  using typename DelegateForwardIterableClient::Iterator;
  using typename DelegateForwardConstIterableClient::ConstIterator;
  using typename DelegateBackwardIterableClient::ReverseIterator;
  using typename DelegateBackwardConstIterableClient::ConstReverseIterator;

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

  ValueMutableCollectionProxy () noexcept = delete;
  ValueMutableCollectionProxy (ValueMutableCollectionProxy const&) noexcept = delete;
  ValueMutableCollectionProxy (ValueMutableCollectionProxy&&) noexcept = delete;

  __CDS_Explicit ValueMutableCollectionProxy (TreeMap <__KeyType, __ValueType, __Comparator>* pMap) noexcept;
  auto operator = (ValueMutableCollectionProxy const&) noexcept -> ValueMutableCollectionProxy& = delete;
  auto operator = (ValueMutableCollectionProxy&&) noexcept -> ValueMutableCollectionProxy& = delete;

private:
  friend __hidden::__impl::__MutableCollectionServer <ValueMutableCollectionProxy, __ValueType>;

  friend __hidden::__impl::__LocalDelegateForwardIterablePrimitiveClient <ValueMutableCollectionProxy, Iterator>;
  friend __hidden::__impl::__LocalDelegateForwardConstIterablePrimitiveClient <ValueMutableCollectionProxy, ConstIterator>;
  friend __hidden::__impl::__LocalDelegateBackwardIterablePrimitiveClient <ValueMutableCollectionProxy, ReverseIterator>;
  friend __hidden::__impl::__LocalDelegateBackwardConstIterablePrimitiveClient <ValueMutableCollectionProxy, ConstReverseIterator>;

  using Server::__mcs_handlers;       // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  using Server::__mcs_constHandlers;  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

  using typename AbstractValueMutableCollectionProxy::__GenericHandler;          // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  using typename AbstractValueMutableCollectionProxy::__GenericConstHandler;     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

  __CDS_NoDiscard static constexpr auto __begin ( // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      ValueMutableCollectionProxy* pObject
  ) noexcept -> cds::__hidden::__impl::__AbstractDelegateIterator <__ValueType>*;

  __CDS_NoDiscard static constexpr auto __end ( // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      ValueMutableCollectionProxy* pObject
  ) noexcept -> cds::__hidden::__impl::__AbstractDelegateIterator <__ValueType>*;

  __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction static auto __beginLocal (  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      ValueMutableCollectionProxy* pObject
  ) noexcept -> Iterator;

  __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction static auto __endLocal (  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      ValueMutableCollectionProxy* pObject
  ) noexcept -> Iterator;

  __CDS_NoDiscard constexpr static auto __cbegin (  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      ValueMutableCollectionProxy const* pObject
  ) noexcept -> cds::__hidden::__impl::__AbstractDelegateIterator <__ValueType const>*;

  __CDS_NoDiscard constexpr static auto __cend (  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      ValueMutableCollectionProxy const* pObject
  ) noexcept -> cds::__hidden::__impl::__AbstractDelegateIterator <__ValueType const>*;

  __CDS_NoDiscard constexpr static auto __cbeginLocal ( // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      ValueMutableCollectionProxy const* pObject
  ) noexcept -> ConstIterator;

  __CDS_NoDiscard constexpr static auto __cendLocal ( // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      ValueMutableCollectionProxy const* pObject
  ) noexcept -> ConstIterator;

  __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction static auto __rbeginLocal ( // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      ValueMutableCollectionProxy* pObject
  ) noexcept -> ReverseIterator;

  __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction static auto __rendLocal ( // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      ValueMutableCollectionProxy* pObject
  ) noexcept -> ReverseIterator;

  __CDS_NoDiscard constexpr static auto __crbeginLocal (  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      ValueMutableCollectionProxy const* pObject
  ) noexcept -> ConstReverseIterator;

  __CDS_NoDiscard constexpr static auto __crendLocal (  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      ValueMutableCollectionProxy const* pObject
  ) noexcept -> ConstReverseIterator;

  static auto __remove (     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      ValueMutableCollectionProxy*  pObject,
      AbstractIterator const*       iterator
  ) noexcept -> bool;

  static auto __removeConst (       // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      ValueMutableCollectionProxy* pObject,
      AbstractConstIterator const* iterator
  ) noexcept -> bool;

  static auto __removeArray (     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      ValueMutableCollectionProxy*    pObject,
      AbstractIterator const *const*  ppIterators,
      Size                            iteratorCount
  ) noexcept -> Size;

  static auto __removeConstArray (     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      ValueMutableCollectionProxy*        pObject,
      AbstractConstIterator const* const* ppIterators,
      Size                                iteratorCount
  ) noexcept -> Size;

  __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto __iicch_obtainGenericHandler (         // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      cds::__hidden::__impl::__IterableInternalRequest requestType
  ) noexcept -> __GenericHandler override;

  __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto __iicch_obtainGenericConstHandler (        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      cds::__hidden::__impl::__IterableInternalRequest requestType
  ) const noexcept -> __GenericConstHandler override;
};
} // namespace cds

#endif // __CDS_TREE_MAP_VALUE_MUTABLE_COLLECTION_PROXY_HPP__
