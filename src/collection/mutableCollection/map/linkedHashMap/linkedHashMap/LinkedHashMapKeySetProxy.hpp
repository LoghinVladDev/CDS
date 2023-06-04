// NOLINT(llvm-header-guard)
// Created by loghin on 09/10/22.
//

#ifndef __CDS_LINKED_HASH_MAP_KEY_SET_PROXY_HPP__ // NOLINT(llvm-header-guard)
#define __CDS_LINKED_HASH_MAP_KEY_SET_PROXY_HPP__ // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
#pragma once

namespace cds {       // NOLINT(modernize-concat-nested-namespaces)
namespace __hidden {  // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
namespace __impl {    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename __ServerType, typename __KeyType, typename __ValueType, typename __Hasher> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __LinkedHashMapKeyProxyServer :                 // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __SetServer <
        __ServerType,
        __KeyType const
    > {};


template <typename __DecoratedIteratorType, typename __ValueAtType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
constexpr auto __linkedHashMapKeySetProxyIteratorDecoratorValueAt ( // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    __DecoratedIteratorType const& iterator
) noexcept -> __ValueAtType& {
  return (*iterator).key();
}


template <typename __KeyType, typename __ValueType, typename __Hasher>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
using __LinkedHashMapKeyProxyConstIterator =  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    ForwardIteratorGenericDecorator <
        __LinkedHashMapConstIterator <__KeyType, __ValueType, __Hasher>,
        __KeyType const,
        &__linkedHashMapKeySetProxyIteratorDecoratorValueAt <
            __LinkedHashMapConstIterator <__KeyType, __ValueType, __Hasher>,
            __KeyType const
        >
    >;


template <typename __ServerType, typename __KeyType, typename __ValueType, typename __Hasher>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __LinkedHashMapKeyProxyRandomInsertionClient :  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalRandomInsertionPrimitiveClient <__ServerType, __KeyType, __KeyType const> {};


template <typename __ServerType, typename __KeyType, typename __ValueType, typename __Hasher>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __LinkedHashMapKeyProxyIteratorRemoveClient :   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalIteratorRemovePrimitiveClient <
        __ServerType, __KeyType, __LinkedHashMapKeyProxyConstIterator <__KeyType, __ValueType, __Hasher>
    > {};


template <typename __ServerType, typename __KeyType, typename __ValueType, typename __Hasher>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __LinkedHashMapKeyProxyFindOfIterableClient :   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalFindOfImmutableCompositeClient <
        __ServerType, __KeyType, __LinkedHashMapKeyProxyConstIterator <__KeyType, __ValueType, __Hasher>,
        cds::Iterable <__KeyType>, &__iterableContains <__KeyType>, &__iterableNotContains <__KeyType>
    > {};


template <typename __ServerType, typename __KeyType, typename __ValueType, typename __Hasher>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __LinkedHashMapKeyProxyFindOfInitializerListClient :    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalFindOfImmutableCompositeClient <
        __ServerType, __KeyType, __LinkedHashMapKeyProxyConstIterator <__KeyType, __ValueType, __Hasher>,
        std::initializer_list <__KeyType>, &__initializerListContains <__KeyType, &cds::meta::equals <__KeyType>>,
        &__initializerListNotContains <__KeyType, &cds::meta::equals <__KeyType>>
    > {};


template <typename __ServerType, typename __KeyType, typename __ValueType, typename __Hasher>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __LinkedHashMapKeyProxyFindByClient :   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalFindByImmutableCompositeClient <
        __ServerType, __KeyType, __LinkedHashMapKeyProxyConstIterator <__KeyType, __ValueType, __Hasher>
    > {};


template <typename __ServerType, typename __KeyType, typename __ValueType, typename __Hasher>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __LinkedHashMapKeyProxyRemoveOfIterableClient : // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalRemoveOfCompositeClient <
        __ServerType, __KeyType, cds::Iterable <__KeyType>, &__iterableContains <__KeyType>
    > {};


template <typename __ServerType, typename __KeyType, typename __ValueType, typename __Hasher>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __LinkedHashMapKeyProxyRemoveOfInitializerListClient :  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalRemoveOfCompositeClient <
        __ServerType, __KeyType, std::initializer_list <__KeyType>,
        &__initializerListContains <__KeyType, &cds::meta::equals <__KeyType>>
    > {};


template <typename __ServerType, typename __KeyType, typename __ValueType, typename __Hasher>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __LinkedHashMapKeyProxyRemoveByClient : // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalRemoveByCompositeClient <__ServerType, __KeyType> {};


template <typename __ServerType, typename __KeyType, typename __ValueType, typename __Hasher>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __LinkedHashMapKeyProxyGenericStatementsClient :    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalGenericImmutableStatementsCompositeClient <__ServerType, __KeyType> {};


template <typename __ServerType, typename __KeyType, typename __ValueType, typename __Hasher>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __LinkedHashMapKeyProxyFindUniqueClient :   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalFindUniqueImmutablePrimitiveClient <
        __ServerType, __KeyType, __LinkedHashMapKeyProxyConstIterator <__KeyType, __ValueType, __Hasher>
    > {};


template <typename __ServerType, typename __KeyType, typename __ValueType, typename __Hasher>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __LinkedHashMapKeyProxyContainsOfIterableClient :   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalContainsOfCompositeClient <
        __ServerType, __KeyType, cds::Iterable <__KeyType>, &__iterableContains <__KeyType>
    > {};


template <typename __ServerType, typename __KeyType, typename __ValueType, typename __Hasher>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __LinkedHashMapKeyProxyContainsOfInitializerListClient :    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalContainsOfCompositeClient <
        __ServerType, __KeyType, std::initializer_list <__KeyType>,
        &__initializerListContains <__KeyType, &cds::meta::equals <__KeyType>>
    > {};


template <typename __ServerType, typename __KeyType, typename __ValueType, typename __Hasher>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __LinkedHashMapKeyProxyDelegateForwardConstIterableClient : // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalDelegateForwardConstIterablePrimitiveClient <
        __ServerType, __LinkedHashMapKeyProxyConstIterator <__KeyType, __ValueType, __Hasher>
    > {};
} // namespace __impl
} // namespace __hidden

template <typename __KeyType, typename __ValueType, typename __Hasher>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs LinkedHashMap <__KeyType, __ValueType, __Hasher>::KeySetProxy :
    public LinkedHashMap <__KeyType, __ValueType, __Hasher>::AbstractKeySetProxy,
    protected __hidden::__impl::__LinkedHashMapKeyProxyServer <KeySetProxy, __KeyType, __ValueType, __Hasher>,
    public __hidden::__impl::__LinkedHashMapKeyProxyRandomInsertionClient <KeySetProxy, __KeyType, __ValueType, __Hasher>,
    public __hidden::__impl::__LinkedHashMapKeyProxyIteratorRemoveClient <KeySetProxy, __KeyType, __ValueType, __Hasher>,
    public __hidden::__impl::__LinkedHashMapKeyProxyFindOfIterableClient <KeySetProxy, __KeyType, __ValueType, __Hasher>,
    public __hidden::__impl::__LinkedHashMapKeyProxyFindOfInitializerListClient <KeySetProxy, __KeyType, __ValueType, __Hasher>,
    public __hidden::__impl::__LinkedHashMapKeyProxyFindByClient <KeySetProxy, __KeyType, __ValueType, __Hasher>,
    public __hidden::__impl::__LinkedHashMapKeyProxyRemoveOfIterableClient <KeySetProxy, __KeyType, __ValueType, __Hasher>,
    public __hidden::__impl::__LinkedHashMapKeyProxyRemoveOfInitializerListClient <KeySetProxy, __KeyType, __ValueType, __Hasher>,
    public __hidden::__impl::__LinkedHashMapKeyProxyRemoveByClient <KeySetProxy, __KeyType, __ValueType, __Hasher>,
    public __hidden::__impl::__LinkedHashMapKeyProxyGenericStatementsClient <KeySetProxy, __KeyType, __ValueType, __Hasher>,
    public __hidden::__impl::__LinkedHashMapKeyProxyFindUniqueClient <KeySetProxy, __KeyType, __ValueType, __Hasher>,
    public __hidden::__impl::__LinkedHashMapKeyProxyContainsOfIterableClient <KeySetProxy, __KeyType, __ValueType, __Hasher>,
    public __hidden::__impl::__LinkedHashMapKeyProxyContainsOfInitializerListClient <KeySetProxy, __KeyType, __ValueType, __Hasher>,
    public __hidden::__impl::__LinkedHashMapKeyProxyDelegateForwardConstIterableClient <KeySetProxy, __KeyType, __ValueType, __Hasher> {
protected:
  using LinkedHashMapBase                     = LinkedHashMap <__KeyType, __ValueType, __Hasher>;
  using Server                                = __hidden::__impl::__LinkedHashMapKeyProxyServer <KeySetProxy, __KeyType, __ValueType, __Hasher>;
  using RandomInsertionClient                 = __hidden::__impl::__LinkedHashMapKeyProxyRandomInsertionClient <KeySetProxy, __KeyType, __ValueType, __Hasher>;
  using IteratorRemoveClient                  = __hidden::__impl::__LinkedHashMapKeyProxyIteratorRemoveClient <KeySetProxy, __KeyType, __ValueType, __Hasher>;
  using FindOfIterableClient                  = __hidden::__impl::__LinkedHashMapKeyProxyFindOfIterableClient <KeySetProxy, __KeyType, __ValueType, __Hasher>;
  using FindOfInitializerListClient           = __hidden::__impl::__LinkedHashMapKeyProxyFindOfInitializerListClient <KeySetProxy, __KeyType, __ValueType, __Hasher>;
  using FindByClient                          = __hidden::__impl::__LinkedHashMapKeyProxyFindByClient <KeySetProxy, __KeyType, __ValueType, __Hasher>;
  using RemoveOfIterableClient                = __hidden::__impl::__LinkedHashMapKeyProxyRemoveOfIterableClient <KeySetProxy, __KeyType, __ValueType, __Hasher>;
  using RemoveOfInitializerListClient         = __hidden::__impl::__LinkedHashMapKeyProxyRemoveOfInitializerListClient <KeySetProxy, __KeyType, __ValueType, __Hasher>;
  using RemoveByClient                        = __hidden::__impl::__LinkedHashMapKeyProxyRemoveByClient <KeySetProxy, __KeyType, __ValueType, __Hasher>;
  using GenericStatementsClient               = __hidden::__impl::__LinkedHashMapKeyProxyGenericStatementsClient <KeySetProxy, __KeyType, __ValueType, __Hasher>;
  using ContainsOfIterableClient              = __hidden::__impl::__LinkedHashMapKeyProxyContainsOfIterableClient <KeySetProxy, __KeyType, __ValueType, __Hasher>;
  using ContainsOfInitializerListClient       = __hidden::__impl::__LinkedHashMapKeyProxyContainsOfInitializerListClient <KeySetProxy, __KeyType, __ValueType, __Hasher>;
  using FindUniqueClient                      = __hidden::__impl::__LinkedHashMapKeyProxyFindUniqueClient <KeySetProxy, __KeyType, __ValueType, __Hasher>;
  using DelegateForwardConstIterableClient    = __hidden::__impl::__LinkedHashMapKeyProxyDelegateForwardConstIterableClient <KeySetProxy, __KeyType, __ValueType, __Hasher>;

public:
  using typename DelegateForwardConstIterableClient::ConstIterator;

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

  using FindUniqueClient::find;

  __CDS_Explicit constexpr KeySetProxy (LinkedHashMap <__KeyType, __ValueType, __Hasher>* pMap) noexcept;
  KeySetProxy (KeySetProxy const&) noexcept = delete;
  KeySetProxy (KeySetProxy&&) noexcept = delete;
  __CDS_cpplang_ConstexprDestructor ~KeySetProxy() noexcept override;
  auto operator = (KeySetProxy const&) noexcept -> KeySetProxy& = delete;
  auto operator = (KeySetProxy&&) noexcept -> KeySetProxy& = delete;

  __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto contains (
      __KeyType const& key
  ) const noexcept -> bool override;

  __CDS_NoDiscard auto operator == (
      KeySetProxy const& set
  ) const noexcept -> bool;

  __CDS_NoDiscard auto operator != (
      KeySetProxy const& set
  ) const noexcept -> bool;

private:
  using typename AbstractKeySetProxy::__GenericHandler;         // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  using typename AbstractKeySetProxy::__GenericConstHandler;    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

  friend __hidden::__impl::__SetServer <KeySetProxy, __KeyType const>;
  friend __hidden::__impl::__LocalDelegateForwardConstIterablePrimitiveClient <KeySetProxy, ConstIterator>;

  using Server::__ss_handlers;       // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  using Server::__ss_constHandlers;  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

  using AbstractMapProxy::map;

  __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto __iicch_obtainGenericHandler ( // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      __hidden::__impl::__IterableInternalRequestType requestType
  ) noexcept -> __GenericHandler override;

  __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto __iicch_obtainGenericConstHandler (    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      __hidden::__impl::__IterableInternalRequestType requestType
  ) const noexcept -> __GenericConstHandler override;

  __CDS_NoDiscard static auto __cbegin (  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      KeySetProxy const* pObject
  ) noexcept -> __hidden::__impl::__AbstractDelegateIterator <__KeyType const>*;

  __CDS_NoDiscard static auto __cend (  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      KeySetProxy const* pObject
  ) noexcept -> __hidden::__impl::__AbstractDelegateIterator <__KeyType const>*;

  __CDS_NoDiscard constexpr static auto __cbeginLocal ( // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      KeySetProxy const* pObject
  ) noexcept -> ConstIterator;

  __CDS_NoDiscard constexpr static auto __cendLocal ( // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      KeySetProxy const* pObject
  ) noexcept -> ConstIterator;

  static auto __removeConst (    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      KeySetProxy*          pObject,
      ConstIterator const*  pIterator
  ) noexcept -> bool;

  static auto __removeConstArray (    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      KeySetProxy*                pObject,
      ConstIterator const* const* ppIterators,
      Size                        iteratorArraySize
  ) noexcept -> Size;

  static auto __findConst (    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      KeySetProxy const*  pObject,
      __KeyType const&    key
  ) noexcept -> __hidden::__impl::__AbstractDelegateIterator <__KeyType const>*;

  static auto __findConstLocal (    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      KeySetProxy const*  pObject,
      __KeyType const&    key
  ) noexcept -> ConstIterator;

  __CDS_NoDiscard auto __equals ( // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      KeySetProxy const& set
  ) const noexcept -> bool;
};

} // namespace cds

#endif // __CDS_LINKED_HASH_MAP_KEY_SET_PROXY_HPP__
