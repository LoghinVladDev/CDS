// NOLINT(llvm-header-guard)
// Created by loghin on 14/08/22.
//

#ifndef __CDS_HASH_MAP_VALUE_MUTABLE_COLLECTION_PROXY_HPP__ // NOLINT(llvm-header-guard)
#define __CDS_HASH_MAP_VALUE_MUTABLE_COLLECTION_PROXY_HPP__ // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
#pragma once

namespace cds {             /* NOLINT(modernize-concat-nested-namespaces) */
namespace __hidden {    /* NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
namespace __impl {  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename __ServerType, typename __KeyType, typename __ValueType, typename __Hasher> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
using __HashMapValueProxyServer = __MutableCollectionServer <__ServerType, __ValueType>;      // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)


template <typename __DecoratedIteratorType, typename __ValueAtType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
constexpr auto __hashMapValueSetProxyIteratorDecoratorValueAt (     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    __DecoratedIteratorType const& iterator
) noexcept -> __ValueAtType& {
  return (*iterator).value ();
}


template <typename __KeyType, typename __ValueType, typename __Hasher>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
using __HashMapValueProxyIterator =   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    ForwardIteratorGenericDecorator <
        typename __HashMapImplementation <__KeyType, __ValueType, __Hasher>::__ht_Iterator,
        __ValueType,
        &__hashMapValueSetProxyIteratorDecoratorValueAt <
            typename __HashMapImplementation <__KeyType, __ValueType, __Hasher>::__ht_Iterator,
            __ValueType
        >
    >;


template <typename __KeyType, typename __ValueType, typename __Hasher>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
using __HashMapValueProxyConstIterator =  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    ForwardIteratorGenericDecorator <
        typename __HashMapImplementation <__KeyType, __ValueType, __Hasher>::__ht_ConstIterator,
        __ValueType const,
        &__hashMapValueSetProxyIteratorDecoratorValueAt <
            typename __HashMapImplementation <__KeyType, __ValueType, __Hasher>::__ht_ConstIterator,
            __ValueType const
        >
    >;


template <typename __ServerType, typename __KeyType, typename __ValueType, typename __Hasher>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __HashMapValueProxyRandomInsertionClient :  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalRandomInsertionPrimitiveClient <__ServerType, __ValueType, __ValueType> {};


template <typename __ServerType, typename __KeyType, typename __ValueType, typename __Hasher>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __HashMapValueProxyIteratorRemoveClient :   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalIteratorRemovePrimitiveClient <
        __ServerType, __ValueType, __HashMapValueProxyIterator <__KeyType, __ValueType, __Hasher>
    > {};


template <typename __ServerType, typename __KeyType, typename __ValueType, typename __Hasher>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __HashMapValueProxyConstIteratorRemoveClient :  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalConstIteratorRemovePrimitiveClient <
        __ServerType, __ValueType, __HashMapValueProxyConstIterator <__KeyType, __ValueType, __Hasher>
    > {};


template <typename __ServerType, typename __KeyType, typename __ValueType, typename __Hasher>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __HashMapValueProxyFindOfIterableClient :   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalFindOfMutableCompositeClient <
        __ServerType, __ValueType,
        __HashMapValueProxyIterator <__KeyType, __ValueType, __Hasher>,
        cds::Iterable <__ValueType>,
        &__iterableContains <__ValueType>, &__iterableNotContains <__ValueType>
    > {};


template <typename __ServerType, typename __KeyType, typename __ValueType, typename __Hasher>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __HashMapValueProxyFindOfConstIterableClient :  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalFindOfImmutableCompositeClient <
        __ServerType, __ValueType,
        __HashMapValueProxyConstIterator <__KeyType, __ValueType, __Hasher>,
        cds::Iterable <__ValueType>,
        &__iterableContains <__ValueType>, &__iterableNotContains <__ValueType>
    > {};


template <typename __ServerType, typename __KeyType, typename __ValueType, typename __Hasher>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __HashMapValueProxyFindOfInitializerListClient :    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalFindOfMutableCompositeClient <
        __ServerType, __ValueType,
        __HashMapValueProxyIterator <__KeyType, __ValueType, __Hasher>,
        std::initializer_list <__ValueType>,
        &__initializerListContains <__ValueType, &cds::meta::equals <__ValueType>>,
        &__initializerListNotContains <__ValueType, &cds::meta::equals <__ValueType>>
    > {};


template <typename __ServerType, typename __KeyType, typename __ValueType, typename __Hasher>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __HashMapValueProxyFindOfConstInitializerListClient :   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalFindOfImmutableCompositeClient <
        __ServerType, __ValueType,
        __HashMapValueProxyConstIterator <__KeyType, __ValueType, __Hasher>,
        std::initializer_list <__ValueType>,
        &__initializerListContains <__ValueType, &cds::meta::equals <__ValueType>>,
        &__initializerListNotContains <__ValueType, &cds::meta::equals <__ValueType>>
    > {};


template <typename __ServerType, typename __KeyType, typename __ValueType, typename __Hasher>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __HashMapValueProxyFindByClient :   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalFindByMutableCompositeClient <
        __ServerType, __ValueType, __HashMapValueProxyIterator <__KeyType, __ValueType, __Hasher>
    > {};


template <typename __ServerType, typename __KeyType, typename __ValueType, typename __Hasher>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __HashMapValueProxyConstFindByClient :  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalFindByImmutableCompositeClient <
        __ServerType, __ValueType, __HashMapValueProxyConstIterator <__KeyType, __ValueType, __Hasher>
    > {};


template <typename __ServerType, typename __KeyType, typename __ValueType, typename __Hasher>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __HashMapValueProxyRemoveOfIterableClient : // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalRemoveOfCompositeClient <
        __ServerType, __ValueType, cds::Iterable <__ValueType>, &__iterableContains <__ValueType>
    > {};


template <typename __ServerType, typename __KeyType, typename __ValueType, typename __Hasher>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __HashMapValueProxyRemoveOfInitializerListClient :  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalRemoveOfCompositeClient <
        __ServerType, __ValueType, std::initializer_list <__ValueType>,
        &__initializerListContains <__ValueType, &cds::meta::equals <__ValueType>>
    > {};


template <typename __ServerType, typename __KeyType, typename __ValueType, typename __Hasher>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __HashMapValueProxyRemoveByClient : // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalRemoveByCompositeClient <__ServerType, __ValueType> {};


template <typename __ServerType, typename __KeyType, typename __ValueType, typename __Hasher>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __HashMapValueProxyGenericStatementsClient :    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalGenericMutableStatementsCompositeClient <__ServerType, __ValueType> {};


template <typename __ServerType, typename __KeyType, typename __ValueType, typename __Hasher>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __HashMapValueProxyConstGenericStatementsClient :   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalGenericImmutableStatementsCompositeClient <__ServerType, __ValueType> {};


template <typename __ServerType, typename __KeyType, typename __ValueType, typename __Hasher>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __HashMapValueProxyContainsOfIterableClient :   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalContainsOfCompositeClient <
        __ServerType, __ValueType, cds::Iterable <__ValueType>, &__iterableContains <__ValueType>
    > {};


template <typename __ServerType, typename __KeyType, typename __ValueType, typename __Hasher>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __HashMapValueProxyContainsOfInitializerListClient :    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalContainsOfCompositeClient <
        __ServerType, __ValueType, std::initializer_list <__ValueType>,
        &__initializerListContains <__ValueType, &cds::meta::equals <__ValueType>>
    > {};


template <typename __ServerType, typename __KeyType, typename __ValueType, typename __Hasher>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __HashMapValueProxyDelegateForwardIterableClient :  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalDelegateForwardIterablePrimitiveClient <
        __ServerType, __HashMapValueProxyIterator <__KeyType, __ValueType, __Hasher>
    > {};


template <typename __ServerType, typename __KeyType, typename __ValueType, typename __Hasher>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __HashMapValueProxyDelegateForwardConstIterableClient : // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalDelegateForwardConstIterablePrimitiveClient <
        __ServerType, __HashMapValueProxyConstIterator <__KeyType, __ValueType, __Hasher>
    > {};

} /* namespace __impl */
} /* namespace __hidden */

template <typename __KeyType, typename __ValueType,typename __Hasher> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs HashMap <__KeyType, __ValueType, __Hasher>::ValueMutableCollectionProxy :
    public HashMap <__KeyType, __ValueType, __Hasher>::AbstractValueMutableCollectionProxy,
    protected __hidden::__impl::__HashMapValueProxyServer <ValueMutableCollectionProxy, __KeyType, __ValueType, __Hasher>,
    public __hidden::__impl::__HashMapValueProxyRandomInsertionClient <ValueMutableCollectionProxy, __KeyType, __ValueType, __Hasher>,
    public __hidden::__impl::__HashMapValueProxyIteratorRemoveClient <ValueMutableCollectionProxy, __KeyType, __ValueType, __Hasher>,
    public __hidden::__impl::__HashMapValueProxyConstIteratorRemoveClient <ValueMutableCollectionProxy, __KeyType, __ValueType, __Hasher>,
    public __hidden::__impl::__HashMapValueProxyFindOfIterableClient <ValueMutableCollectionProxy, __KeyType, __ValueType, __Hasher>,
    public __hidden::__impl::__HashMapValueProxyFindOfConstIterableClient <ValueMutableCollectionProxy, __KeyType, __ValueType, __Hasher>,
    public __hidden::__impl::__HashMapValueProxyFindOfInitializerListClient <ValueMutableCollectionProxy, __KeyType, __ValueType, __Hasher>,
    public __hidden::__impl::__HashMapValueProxyFindOfConstInitializerListClient <ValueMutableCollectionProxy, __KeyType, __ValueType, __Hasher>,
    public __hidden::__impl::__HashMapValueProxyFindByClient <ValueMutableCollectionProxy, __KeyType, __ValueType, __Hasher>,
    public __hidden::__impl::__HashMapValueProxyConstFindByClient <ValueMutableCollectionProxy, __KeyType, __ValueType, __Hasher>,
    public __hidden::__impl::__HashMapValueProxyRemoveOfIterableClient <ValueMutableCollectionProxy, __KeyType, __ValueType, __Hasher>,
    public __hidden::__impl::__HashMapValueProxyRemoveOfInitializerListClient <ValueMutableCollectionProxy, __KeyType, __ValueType, __Hasher>,
    public __hidden::__impl::__HashMapValueProxyRemoveByClient <ValueMutableCollectionProxy, __KeyType, __ValueType, __Hasher>,
    public __hidden::__impl::__HashMapValueProxyGenericStatementsClient <ValueMutableCollectionProxy, __KeyType, __ValueType, __Hasher>,
    public __hidden::__impl::__HashMapValueProxyConstGenericStatementsClient <ValueMutableCollectionProxy, __KeyType, __ValueType, __Hasher>,
    public __hidden::__impl::__HashMapValueProxyContainsOfIterableClient <ValueMutableCollectionProxy, __KeyType, __ValueType, __Hasher>,
    public __hidden::__impl::__HashMapValueProxyContainsOfInitializerListClient <ValueMutableCollectionProxy, __KeyType, __ValueType, __Hasher>,
    public __hidden::__impl::__HashMapValueProxyDelegateForwardIterableClient <ValueMutableCollectionProxy, __KeyType, __ValueType, __Hasher>,
    public __hidden::__impl::__HashMapValueProxyDelegateForwardConstIterableClient <ValueMutableCollectionProxy, __KeyType, __ValueType, __Hasher> {
protected:
  using HashMapBase                           = HashMap <__KeyType, __ValueType, __Hasher>;
  using Server                                = __hidden::__impl::__HashMapValueProxyServer <ValueMutableCollectionProxy, __KeyType, __ValueType, __Hasher>;
  using RandomInsertionClient                 = __hidden::__impl::__HashMapValueProxyRandomInsertionClient <ValueMutableCollectionProxy, __KeyType, __ValueType, __Hasher>;
  using IteratorRemoveClient                  = __hidden::__impl::__HashMapValueProxyIteratorRemoveClient <ValueMutableCollectionProxy, __KeyType, __ValueType, __Hasher>;
  using ConstIteratorRemoveClient             = __hidden::__impl::__HashMapValueProxyConstIteratorRemoveClient <ValueMutableCollectionProxy, __KeyType, __ValueType, __Hasher>;
  using FindOfIterableClient                  = __hidden::__impl::__HashMapValueProxyFindOfIterableClient <ValueMutableCollectionProxy, __KeyType, __ValueType, __Hasher>;
  using ConstFindOfIterableClient             = __hidden::__impl::__HashMapValueProxyFindOfConstIterableClient <ValueMutableCollectionProxy, __KeyType, __ValueType, __Hasher>;
  using FindOfInitializerListClient           = __hidden::__impl::__HashMapValueProxyFindOfInitializerListClient <ValueMutableCollectionProxy, __KeyType, __ValueType, __Hasher>;
  using ConstFindOfInitializerListClient      = __hidden::__impl::__HashMapValueProxyFindOfConstInitializerListClient <ValueMutableCollectionProxy, __KeyType, __ValueType, __Hasher>;
  using FindByClient                          = __hidden::__impl::__HashMapValueProxyFindByClient <ValueMutableCollectionProxy, __KeyType, __ValueType, __Hasher>;
  using ConstFindByClient                     = __hidden::__impl::__HashMapValueProxyConstFindByClient <ValueMutableCollectionProxy, __KeyType, __ValueType, __Hasher>;
  using RemoveOfIterableClient                = __hidden::__impl::__HashMapValueProxyRemoveOfIterableClient <ValueMutableCollectionProxy, __KeyType, __ValueType, __Hasher>;
  using RemoveOfInitializerListClient         = __hidden::__impl::__HashMapValueProxyRemoveOfInitializerListClient <ValueMutableCollectionProxy, __KeyType, __ValueType, __Hasher>;
  using RemoveByClient                        = __hidden::__impl::__HashMapValueProxyRemoveByClient <ValueMutableCollectionProxy, __KeyType, __ValueType, __Hasher>;
  using GenericStatementsClient               = __hidden::__impl::__HashMapValueProxyGenericStatementsClient <ValueMutableCollectionProxy, __KeyType, __ValueType, __Hasher>;
  using ContainsOfIterableClient              = __hidden::__impl::__HashMapValueProxyContainsOfIterableClient <ValueMutableCollectionProxy, __KeyType, __ValueType, __Hasher>;
  using ContainsOfInitializerListClient       = __hidden::__impl::__HashMapValueProxyContainsOfInitializerListClient <ValueMutableCollectionProxy, __KeyType, __ValueType, __Hasher>;
  using ConstGenericStatementsClient          = __hidden::__impl::__HashMapValueProxyConstGenericStatementsClient <ValueMutableCollectionProxy, __KeyType, __ValueType, __Hasher>;
  using DelegateForwardIterableClient         = __hidden::__impl::__HashMapValueProxyDelegateForwardIterableClient <ValueMutableCollectionProxy, __KeyType, __ValueType, __Hasher>;
  using DelegateForwardConstIterableClient    = __hidden::__impl::__HashMapValueProxyDelegateForwardConstIterableClient <ValueMutableCollectionProxy, __KeyType, __ValueType, __Hasher>;

public:
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

  using ContainsOfIterableClient::containsAnyOf;
  using ContainsOfIterableClient::containsAnyNotOf;
  using ContainsOfIterableClient::containsAllOf;
  using ContainsOfIterableClient::containsNoneOf;

  using ContainsOfInitializerListClient::containsAnyOf;
  using ContainsOfInitializerListClient::containsAnyNotOf;
  using ContainsOfInitializerListClient::containsAllOf;
  using ContainsOfInitializerListClient::containsNoneOf;

  using RandomInsertionClient::add;
  using RandomInsertionClient::addAll;
  using RandomInsertionClient::addAllOf;
  using RandomInsertionClient::insert;
  using RandomInsertionClient::insertAll;
  using RandomInsertionClient::insertAllOf;
  using RandomInsertionClient::emplace;

  using IteratorRemoveClient::remove;
  using ConstIteratorRemoveClient::remove;

  __CDS_Explicit constexpr ValueMutableCollectionProxy (HashMap <__KeyType, __ValueType, __Hasher>* pMap) noexcept;
  ValueMutableCollectionProxy (ValueMutableCollectionProxy const&) noexcept = delete;
  ValueMutableCollectionProxy (ValueMutableCollectionProxy&&) noexcept = delete;
  __CDS_cpplang_ConstexprDestructor ~ValueMutableCollectionProxy() noexcept override;
  auto operator = (ValueMutableCollectionProxy const&) noexcept -> ValueMutableCollectionProxy& = delete;
  auto operator = (ValueMutableCollectionProxy&&) noexcept -> ValueMutableCollectionProxy& = delete;

  __CDS_NoDiscard auto operator == (ValueMutableCollectionProxy const& set) const noexcept -> bool;
  __CDS_NoDiscard auto operator != (ValueMutableCollectionProxy const& set) const noexcept -> bool;

private:
  using typename AbstractValueMutableCollectionProxy::__GenericHandler;         // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  using typename AbstractValueMutableCollectionProxy::__GenericConstHandler;    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

  friend __hidden::__impl::__MutableCollectionServer <ValueMutableCollectionProxy, __ValueType>;

  friend __hidden::__impl::__LocalDelegateForwardIterablePrimitiveClient <ValueMutableCollectionProxy, Iterator>;
  friend __hidden::__impl::__LocalDelegateForwardConstIterablePrimitiveClient <ValueMutableCollectionProxy, ConstIterator>;

  using Server::__mcs_handlers;       // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  using Server::__mcs_constHandlers;  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

  using AbstractMapProxy::map;

  __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto __iicch_obtainGenericHandler ( // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      __hidden::__impl::__IterableInternalRequest requestType
  ) noexcept -> __GenericHandler override;

  __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto __iicch_obtainGenericConstHandler (    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      __hidden::__impl::__IterableInternalRequest requestType
  ) const noexcept -> __GenericConstHandler override;

  __CDS_NoDiscard static auto __begin (  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      ValueMutableCollectionProxy* pObject
  ) noexcept -> __hidden::__impl::__AbstractDelegateIterator <__ValueType>*;

  __CDS_NoDiscard static auto __end (  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      ValueMutableCollectionProxy* pObject
  ) noexcept -> __hidden::__impl::__AbstractDelegateIterator <__ValueType>*;

  __CDS_NoDiscard static auto __cbegin (   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      ValueMutableCollectionProxy const* pObject
  ) noexcept -> __hidden::__impl::__AbstractDelegateIterator <__ValueType const>*;

  __CDS_NoDiscard static auto __cend (   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      ValueMutableCollectionProxy const* pObject
  ) noexcept -> __hidden::__impl::__AbstractDelegateIterator <__ValueType const>*;

  __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction static auto __beginLocal (   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      ValueMutableCollectionProxy* pObject
  ) noexcept -> Iterator;

  __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction static auto __endLocal (   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      ValueMutableCollectionProxy* pObject
  ) noexcept -> Iterator;

  __CDS_NoDiscard constexpr static auto __cbeginLocal ( // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      ValueMutableCollectionProxy const* pObject
  ) noexcept -> ConstIterator;

  __CDS_NoDiscard constexpr static auto __cendLocal (  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      ValueMutableCollectionProxy const* pObject
  ) noexcept -> ConstIterator;

  static auto __remove ( // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      ValueMutableCollectionProxy*  pObject,
      Iterator const*               iterator
  ) noexcept -> bool;

  static auto __removeConst (    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      ValueMutableCollectionProxy*  pObject,
      ConstIterator const*          iterator
  ) noexcept -> bool;

  static auto __removeArray ( // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      ValueMutableCollectionProxy*  pObject,
      Iterator const* const*        ppIterators,
      Size                          iteratorArrayCount
  ) noexcept -> Size;

  static auto __removeConstArray (    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      ValueMutableCollectionProxy*  pObject,
      ConstIterator const* const*   ppIterators,
      Size                          iteratorArrayCount
  ) noexcept -> Size;

  __CDS_NoDiscard auto __equals ( // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      ValueMutableCollectionProxy const& set
  ) const noexcept -> bool;
};

} // namespace cds

#endif // __CDS_HASH_MAP_VALUE_MUTABLE_COLLECTION_PROXY_HPP__
