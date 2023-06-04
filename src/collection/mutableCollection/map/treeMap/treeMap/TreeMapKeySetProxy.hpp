//
// Created by stefan on 13.10.2022.
//

#ifndef __CDS_TREE_MAP_KEY_SET_PROXY_HPP__
#define __CDS_TREE_MAP_KEY_SET_PROXY_HPP__  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
#pragma once

namespace cds {       // NOLINT(modernize-concat-nested-namespaces)
namespace __hidden {  // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier)
namespace __impl {    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename __ServerType, typename __KeyType, typename __ValueType>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __TreeMapKeyProxyServer :                          // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __SetServer <__ServerType, __KeyType const> {};


template <typename __DecoratedIteratorType, typename __ValueAtType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
constexpr auto __treeMapKeySetProxyIteratorDecoratorValueAt (       // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    __DecoratedIteratorType const& iterator
) noexcept -> __ValueAtType& {
  return (*iterator).key ();
}


template <typename __KeyType, typename __ValueType, typename __Comparator>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
using __TreeMapKeyProxyAbstractConstIterator =                              // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    BidirectionalIteratorGenericDecorator <
        typename __TreeMapImplementation <__KeyType, __ValueType, __Comparator>::__rbt_AbstractConstIterator,
        __KeyType const,
        &__treeMapKeySetProxyIteratorDecoratorValueAt <
            typename __TreeMapImplementation <__KeyType, __ValueType, __Comparator>::__rbt_AbstractConstIterator,
            __KeyType const
        >
    >;


template <typename __KeyType, typename __ValueType, typename __Comparator>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
using __TreeMapKeyProxyForwardConstIterator =                               // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    BidirectionalIteratorGenericDecorator <
        typename __TreeMapImplementation <__KeyType, __ValueType, __Comparator>::__rbt_ConstIterator,
        __KeyType const,
        &__treeMapKeySetProxyIteratorDecoratorValueAt <
            typename __TreeMapImplementation <__KeyType, __ValueType, __Comparator>::__rbt_ConstIterator,
            __KeyType const
        >
    >;


template <typename __KeyType, typename __ValueType, typename __Comparator>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
using __TreeMapKeyProxyBackwardConstIterator =                              // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    BidirectionalIteratorGenericDecorator <
        typename __TreeMapImplementation <__KeyType, __ValueType, __Comparator>::__rbt_ReverseConstIterator,
        __KeyType const,
        &__treeMapKeySetProxyIteratorDecoratorValueAt <
            typename __TreeMapImplementation <__KeyType, __ValueType, __Comparator>::__rbt_ReverseConstIterator,
            __KeyType const
        >
    >;


template <typename __ServerType, typename __KeyType, typename __ValueType, typename __Comparator> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __TreeMapKeyProxyConstIteratorRemoveClient :      // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalConstIteratorRemovePrimitiveClient <
        __ServerType, __KeyType, __TreeMapKeyProxyAbstractConstIterator <__KeyType, __ValueType, __Comparator>
    > {};


template <typename __ServerType, typename __KeyType, typename __ValueType, typename __Comparator> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __TreeMapKeyProxyDelegateBackwardConstIterableClient :        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalDelegateBackwardConstIterablePrimitiveClient  <
        __ServerType, __TreeMapKeyProxyBackwardConstIterator <__KeyType, __ValueType, __Comparator>
    > {};


template <typename __ServerType, typename __KeyType, typename __ValueType, typename __Comparator> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __TreeMapKeyProxyDelegateForwardConstIterableClient :     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalDelegateForwardConstIterablePrimitiveClient  <
        __ServerType, __TreeMapKeyProxyForwardConstIterator <__KeyType, __ValueType, __Comparator>
    > {};


template <typename __ServerType, typename __KeyType, typename __ValueType, typename __Comparator> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __TreeMapKeyProxyRandomInsertionClient :      // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalRandomInsertionPrimitiveClient <__ServerType, __KeyType, __KeyType const> {};


template <typename __ServerType, typename __KeyType, typename __ValueType, typename __Comparator> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __TreeMapKeyProxyContainsOfCollectionClient :     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalContainsOfCompositeClient <
        __ServerType, __KeyType, cds::Iterable <__KeyType>, &__iterableContains <__KeyType>
    > {};


template <typename __ServerType, typename __KeyType, typename __ValueType, typename __Comparator> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __TreeMapKeyProxyContainsOfInitializerListClient :     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalContainsOfCompositeClient <
        __ServerType, __KeyType, std::initializer_list <__KeyType>,
        &__initializerListContains <__KeyType, &cds::meta::equals <__KeyType>>
    > {};


template <typename __ServerType, typename __KeyType, typename __ValueType, typename __Comparator> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __TreeMapKeyProxyFindByImmutableClient :      // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalFindByImmutableCompositeClient <
        __ServerType, __KeyType,
        __TreeMapKeyProxyAbstractConstIterator <__KeyType, __ValueType, __Comparator>
    > {};


template <typename __ServerType, typename __KeyType, typename __ValueType, typename __Comparator> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __TreeMapKeyProxyFindOfConstCollectionClient :        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalFindOfImmutableCompositeClient <
        __ServerType, __KeyType,
        __TreeMapKeyProxyAbstractConstIterator <__KeyType, __ValueType, __Comparator>,
        cds::Iterable <__KeyType>,
        &__iterableContains <__KeyType>, &__iterableNotContains <__KeyType>
    > {};


template <typename __ServerType, typename __KeyType, typename __ValueType, typename __Comparator> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __TreeMapKeyProxyFindOfConstInitializerListClient :        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalFindOfImmutableCompositeClient <
        __ServerType, __KeyType,
        __TreeMapKeyProxyAbstractConstIterator <__KeyType, __ValueType, __Comparator>,
        std::initializer_list <__KeyType>,
        &__initializerListContains <__KeyType, &cds::meta::equals <__KeyType>>,
        &__initializerListNotContains <__KeyType, &cds::meta::equals <__KeyType>>
    > {};


template <typename __ServerType, typename __KeyType, typename __ValueType, typename __Comparator> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __TreeMapKeyProxyConstGenericStatementsClient :       // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalGenericImmutableStatementsCompositeClient <__ServerType, __KeyType> {};


template <typename __ServerType, typename __KeyType, typename __ValueType, typename __Comparator> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __TreeMapKeyProxyGenericStatementsClient :       // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalGenericMutableStatementsCompositeClient <__ServerType, __KeyType> {};


template <typename __ServerType, typename __KeyType, typename __ValueType, typename __Comparator> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __TreeMapKeyProxyRemoveByClient :       // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalRemoveByCompositeClient <__ServerType, __KeyType> {};


template <
    typename __ServerType,                            // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __KeyType,                               // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __ValueType                              // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> class __CDS_InheritsEBOs __TreeMapKeyProxyRemoveOfCollectionClient :     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalRemoveOfCompositeClient <
        __ServerType, __KeyType, cds::Iterable <__KeyType>, &__iterableContains <__KeyType>
    > {};


template <
    typename __ServerType,                                 // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __KeyType,                                    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __ValueType                                   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> class __CDS_InheritsEBOs __TreeMapKeyProxyRemoveOfInitializerListClient :     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalRemoveOfCompositeClient <
        __ServerType, __KeyType, std::initializer_list <__KeyType>,
        &__initializerListContains <__KeyType, &cds::meta::equals <__KeyType>>
    > {};

} // namespace __impl
} // namespace __hidden

template <typename __KeyType, typename __ValueType, typename __Comparator>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs TreeMap <__KeyType, __ValueType, __Comparator>::KeySetProxy :
    public TreeMap <__KeyType, __ValueType, __Comparator>::AbstractKeySetProxy,
    private __hidden::__impl::__TreeMapKeyProxyServer <KeySetProxy, __KeyType, __ValueType>,
    public __hidden::__impl::__TreeMapKeyProxyConstIteratorRemoveClient <KeySetProxy, __KeyType, __ValueType, __Comparator>,
    public __hidden::__impl::__TreeMapKeyProxyDelegateBackwardConstIterableClient <KeySetProxy, __KeyType, __ValueType, __Comparator>,
    public __hidden::__impl::__TreeMapKeyProxyDelegateForwardConstIterableClient <KeySetProxy, __KeyType, __ValueType, __Comparator>,
    public __hidden::__impl::__TreeMapKeyProxyRandomInsertionClient <KeySetProxy, __KeyType, __ValueType, __Comparator>,
    public __hidden::__impl::__TreeMapKeyProxyContainsOfCollectionClient <KeySetProxy, __KeyType, __ValueType, __Comparator>,
    public __hidden::__impl::__TreeMapKeyProxyContainsOfInitializerListClient <KeySetProxy, __KeyType, __ValueType, __Comparator>,
    public __hidden::__impl::__TreeMapKeyProxyFindByImmutableClient <KeySetProxy, __KeyType, __ValueType, __Comparator>,
    public __hidden::__impl::__TreeMapKeyProxyFindOfConstCollectionClient <KeySetProxy, __KeyType, __ValueType, __Comparator>,
    public __hidden::__impl::__TreeMapKeyProxyFindOfConstInitializerListClient <KeySetProxy, __KeyType, __ValueType, __Comparator>,
    public __hidden::__impl::__TreeMapKeyProxyConstGenericStatementsClient <KeySetProxy, __KeyType, __ValueType, __Comparator>,
    public __hidden::__impl::__TreeMapKeyProxyGenericStatementsClient <KeySetProxy, __KeyType, __ValueType, __Comparator>,
    public __hidden::__impl::__TreeMapKeyProxyRemoveByClient <KeySetProxy, __KeyType, __ValueType, __Comparator>,
    public __hidden::__impl::__TreeMapKeyProxyRemoveOfCollectionClient <KeySetProxy, __KeyType, __ValueType>,
    public __hidden::__impl::__TreeMapKeyProxyRemoveOfInitializerListClient <KeySetProxy, __KeyType, __ValueType> {

  using TreeMapBase                         = TreeMap <__KeyType, __ValueType, __Comparator>;
  using Server                              = __hidden::__impl::__TreeMapKeyProxyServer <KeySetProxy, __KeyType, __ValueType>;
  using ConstIteratorRemoveClient           = __hidden::__impl::__TreeMapKeyProxyConstIteratorRemoveClient <KeySetProxy, __KeyType, __ValueType, __Comparator>;
  using DelegateBackwardConstIterableClient = __hidden::__impl::__TreeMapKeyProxyDelegateBackwardConstIterableClient <KeySetProxy, __KeyType, __ValueType, __Comparator>;
  using DelegateForwardConstIterableClient  = __hidden::__impl::__TreeMapKeyProxyDelegateForwardConstIterableClient <KeySetProxy, __KeyType, __ValueType, __Comparator>;
  using RandomInsertionClient               = __hidden::__impl::__TreeMapKeyProxyRandomInsertionClient <KeySetProxy, __KeyType, __ValueType, __Comparator>;
  using ContainsOfCollectionClient          = __hidden::__impl::__TreeMapKeyProxyContainsOfCollectionClient <KeySetProxy, __KeyType, __ValueType, __Comparator>;
  using ContainsOfInitializerListClient     = __hidden::__impl::__TreeMapKeyProxyContainsOfInitializerListClient <KeySetProxy, __KeyType, __ValueType, __Comparator>;
  using FindByImmutableClient               = __hidden::__impl::__TreeMapKeyProxyFindByImmutableClient <KeySetProxy, __KeyType, __ValueType, __Comparator>;
  using FindOfConstCollectionClient         = __hidden::__impl::__TreeMapKeyProxyFindOfConstCollectionClient <KeySetProxy, __KeyType, __ValueType, __Comparator>;
  using FindOfConstInitializerListClient    = __hidden::__impl::__TreeMapKeyProxyFindOfConstInitializerListClient <KeySetProxy, __KeyType, __ValueType, __Comparator>;
  using ConstGenericStatementsClient        = __hidden::__impl::__TreeMapKeyProxyConstGenericStatementsClient <KeySetProxy, __KeyType, __ValueType, __Comparator>;
  using GenericStatementsClient             = __hidden::__impl::__TreeMapKeyProxyGenericStatementsClient <KeySetProxy, __KeyType, __ValueType, __Comparator>;
  using RemoveByClient                      = __hidden::__impl::__TreeMapKeyProxyRemoveByClient <KeySetProxy, __KeyType, __ValueType, __Comparator>;
  using RemoveOfCollectionClient            = __hidden::__impl::__TreeMapKeyProxyRemoveOfCollectionClient <KeySetProxy, __KeyType, __ValueType>;
  using RemoveOfInitializerListClient       = __hidden::__impl::__TreeMapKeyProxyRemoveOfInitializerListClient <KeySetProxy, __KeyType, __ValueType>;


public: 
  using typename DelegateForwardConstIterableClient::ConstIterator;
  using typename DelegateBackwardConstIterableClient::ConstReverseIterator;

  using DelegateForwardConstIterableClient::begin;
  using DelegateForwardConstIterableClient::end;
  using DelegateForwardConstIterableClient::cbegin;
  using DelegateForwardConstIterableClient::cend;

  using DelegateBackwardConstIterableClient::rbegin;
  using DelegateBackwardConstIterableClient::rend;
  using DelegateBackwardConstIterableClient::crbegin;
  using DelegateBackwardConstIterableClient::crend;


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

  KeySetProxy () noexcept = delete;
  KeySetProxy (KeySetProxy const&) noexcept = delete;
  KeySetProxy (KeySetProxy&&) noexcept = delete;

  __CDS_Explicit KeySetProxy (TreeMap <__KeyType, __ValueType, __Comparator>* pMap) noexcept;
  auto operator = (KeySetProxy const&) noexcept -> KeySetProxy& = delete;
  auto operator = (KeySetProxy&&) noexcept -> KeySetProxy& = delete;

  __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto contains (
      __KeyType const& key
  ) const noexcept -> bool override;

private:
  friend __hidden::__impl::__SetServer <KeySetProxy, __KeyType const>;

  friend __hidden::__impl::__LocalDelegateForwardConstIterablePrimitiveClient <KeySetProxy, ConstIterator>;
  friend __hidden::__impl::__LocalDelegateBackwardConstIterablePrimitiveClient <KeySetProxy, ConstReverseIterator>;

  using typename AbstractKeySetProxy::__GenericHandler;          // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  using typename AbstractKeySetProxy::__GenericConstHandler;     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

  using AbstractConstIterator = typename ConstIteratorRemoveClient::ConstIterator;

  using Server::__ss_handlers;      // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  using Server::__ss_constHandlers; // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

  using AbstractMapProxy::map;

  __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto __iicch_obtainGenericHandler (         // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      __hidden::__impl::__IterableInternalRequestType requestType
  ) noexcept -> __GenericHandler override;

  __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto __iicch_obtainGenericConstHandler (        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      __hidden::__impl::__IterableInternalRequestType requestType
  ) const noexcept -> __GenericConstHandler override;

  __CDS_NoDiscard constexpr static auto __cbegin (  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      KeySetProxy const* pObject
  ) noexcept -> __hidden::__impl::__AbstractDelegateIterator <__KeyType const>*;

  __CDS_NoDiscard constexpr static auto __cend (  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      KeySetProxy const* pObject
  ) noexcept -> __hidden::__impl::__AbstractDelegateIterator <__KeyType const>*;

  __CDS_NoDiscard constexpr static auto __cbeginLocal ( // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      KeySetProxy const* pObject
  ) noexcept -> ConstIterator;

  __CDS_NoDiscard constexpr static auto __cendLocal ( // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      KeySetProxy const* pObject
  ) noexcept -> ConstIterator;

  __CDS_NoDiscard constexpr static auto __crbeginLocal (  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      KeySetProxy const* pObject
  ) noexcept -> ConstReverseIterator;

  __CDS_NoDiscard constexpr static auto __crendLocal (  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      KeySetProxy const* pObject
  ) noexcept -> ConstReverseIterator;

  static auto __removeConst (     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      KeySetProxy*                  pObject,
      AbstractConstIterator const*  iterator
  ) noexcept -> bool;

  static auto __removeConstArray (     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      KeySetProxy*                        pObject,
      AbstractConstIterator const* const* ppIterators,
      Size                                iteratorCount
  ) noexcept -> Size;

  static auto __findConst (      // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      KeySetProxy const*  pObject,
      __KeyType const&    key
  ) noexcept -> __hidden::__impl::__AbstractDelegateIterator <__KeyType const>*;

  static auto __findConstLocal (     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      KeySetProxy const*  pObject,
      __KeyType const&    key
  ) noexcept -> ConstIterator;
};
} // namespace cds

#endif // __CDS_TREE_MAP_KEY_SET_PROXY_HPP__
