// NOLINT(llvm-header-guard)
// Created by loghin on 14/08/22.
//

#ifndef __CDS_HASH_MAP_KEY_SET_PROXY_HPP__ // NOLINT(llvm-header-guard)
#define __CDS_HASH_MAP_KEY_SET_PROXY_HPP__ // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

namespace cds {
namespace __hidden {  // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
namespace __impl {    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename __ServerType, typename __KeyType, typename, typename>      // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __HashMapKeyProxyServer : public __SetServer <__ServerType, __KeyType const> {};  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)


template <typename __DecoratedIteratorType, typename __ValueAtType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
constexpr auto __hashMapKeySetProxyIteratorDecoratorValueAt (       // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    __DecoratedIteratorType const& iterator
) noexcept -> __ValueAtType& {
  return (*iterator).key ();
}


template <typename __KeyType, typename __ValueType, typename __Hasher>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
using __HashMapKeyProxyConstIterator =                                 // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    ForwardIteratorGenericDecorator <
        typename __HashMapImplementation <__KeyType, __ValueType, __Hasher>::__ht_ConstIterator,
        __KeyType const,
        &__hashMapKeySetProxyIteratorDecoratorValueAt <
            typename __HashMapImplementation <__KeyType, __ValueType, __Hasher>::__ht_ConstIterator,
            __KeyType const
        >
    >;


template <typename __ServerType, typename __KeyType, typename __ValueType, typename __Hasher>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __HashMapKeyProxyRandomInsertionClient :   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalRandomInsertionPrimitiveClient <
        __ServerType, __KeyType, __KeyType const
    > {};


template <typename __ServerType, typename __KeyType, typename __ValueType, typename __Hasher>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __HashMapKeyProxyIteratorRemoveClient : // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalIteratorRemovePrimitiveClient <
        __ServerType, __KeyType, __HashMapKeyProxyConstIterator <__KeyType, __ValueType, __Hasher>
    > {};


template <typename __ServerType, typename __KeyType, typename __ValueType, typename __Hasher>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __HashMapKeyProxyFindOfIterableClient : // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalFindOfImmutableCompositeClient <
        __ServerType, __KeyType, __HashMapKeyProxyConstIterator <__KeyType, __ValueType, __Hasher>,
        cds::Iterable <__KeyType>, &__iterableContains <__KeyType>, &__iterableNotContains <__KeyType>
    > {};


template <typename __ServerType, typename __KeyType, typename __ValueType, typename __Hasher>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __HashMapKeyProxyFindOfInitializerListClient : // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalFindOfImmutableCompositeClient <
        __ServerType, __KeyType,
        __HashMapKeyProxyConstIterator <__KeyType, __ValueType, __Hasher>,
        std::initializer_list <__KeyType>,
        &__initializerListContains <__KeyType, &cds::meta::equals <__KeyType>>,
        &__initializerListNotContains <__KeyType, &cds::meta::equals <__KeyType>>
    > {};


template <typename __ServerType, typename __KeyType, typename __ValueType, typename __Hasher>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __HashMapKeyProxyFindByClient : // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalFindByImmutableCompositeClient <
        __ServerType, __KeyType, __HashMapKeyProxyConstIterator <__KeyType, __ValueType, __Hasher>
    > {};


template <typename __ServerType, typename __KeyType, typename __ValueType, typename __Hasher>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __HashMapKeyProxyRemoveOfIterableClient :  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalRemoveOfCompositeClient <
        __ServerType, __KeyType, cds::Iterable <__KeyType>, &__iterableContains <__KeyType>
    > {};


template <typename __ServerType, typename __KeyType, typename __ValueType, typename __Hasher>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __HashMapKeyProxyRemoveOfInitializerListClient :   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalRemoveOfCompositeClient <
        __ServerType, __KeyType, std::initializer_list <__KeyType>,
        &__initializerListContains <__KeyType, &cds::meta::equals <__KeyType>>
    > {}; 


template <typename __ServerType, typename __KeyType, typename __ValueType, typename __Hasher>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __HashMapKeyProxyRemoveByClient :  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalRemoveByCompositeClient <__ServerType, __KeyType> {};


template <typename __ServerType, typename __KeyType, typename __ValueType, typename __Hasher>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __HashMapKeyProxyGenericStatementsClient : // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalGenericImmutableStatementsCompositeClient <__ServerType, __KeyType> {};


template <typename __ServerType, typename __KeyType, typename __ValueType, typename __Hasher>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __HashMapKeyProxyFindUniqueClient :        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalFindUniqueImmutablePrimitiveClient <
        __ServerType, __KeyType, __HashMapKeyProxyConstIterator <__KeyType, __ValueType, __Hasher>
    > {};


template <typename __ServerType, typename __KeyType, typename __ValueType, typename __Hasher>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __HashMapKeyProxyContainsOfIterableClient : // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalContainsOfCompositeClient <
        __ServerType, __KeyType, cds::Iterable <__KeyType>, &__iterableContains <__KeyType>
    > {};


template <typename __ServerType, typename __KeyType, typename __ValueType, typename __Hasher>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __HashMapKeyProxyContainsOfInitializerListClient : // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalContainsOfCompositeClient <
        __ServerType, __KeyType, std::initializer_list <__KeyType>,
        &__initializerListContains <__KeyType, &cds::meta::equals <__KeyType>>
    > {};


template <
    typename __ServerType,                                  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __KeyType,                                     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __ValueType,                                   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __Hasher                                       // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> class __CDS_InheritsEBOs __HashMapKeyProxyDelegateForwardConstIterableClient :  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalDelegateForwardConstIterablePrimitiveClient <
        __ServerType, __HashMapKeyProxyConstIterator <__KeyType, __ValueType, __Hasher>
    > {};
} // namespace __impl
} // namespace __hidden

template <typename __KeyType, typename __ValueType, typename __Hasher>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs HashMap <__KeyType, __ValueType, __Hasher>::KeySetProxy :
    public HashMap <__KeyType, __ValueType, __Hasher>::AbstractKeySetProxy,
    protected __hidden::__impl::__HashMapKeyProxyServer <KeySetProxy, __KeyType, __ValueType, __Hasher>,
    public __hidden::__impl::__HashMapKeyProxyRandomInsertionClient <KeySetProxy, __KeyType, __ValueType, __Hasher>,
    public __hidden::__impl::__HashMapKeyProxyIteratorRemoveClient <KeySetProxy, __KeyType, __ValueType, __Hasher>,
    public __hidden::__impl::__HashMapKeyProxyFindOfIterableClient <KeySetProxy, __KeyType, __ValueType, __Hasher>,
    public __hidden::__impl::__HashMapKeyProxyFindOfInitializerListClient <KeySetProxy, __KeyType, __ValueType, __Hasher>,
    public __hidden::__impl::__HashMapKeyProxyFindByClient <KeySetProxy, __KeyType, __ValueType, __Hasher>,
    public __hidden::__impl::__HashMapKeyProxyRemoveOfIterableClient <KeySetProxy, __KeyType, __ValueType, __Hasher>,
    public __hidden::__impl::__HashMapKeyProxyRemoveOfInitializerListClient <KeySetProxy, __KeyType, __ValueType, __Hasher>,
    public __hidden::__impl::__HashMapKeyProxyRemoveByClient <KeySetProxy, __KeyType, __ValueType, __Hasher>,
    public __hidden::__impl::__HashMapKeyProxyGenericStatementsClient <KeySetProxy, __KeyType, __ValueType, __Hasher>,
    public __hidden::__impl::__HashMapKeyProxyFindUniqueClient <KeySetProxy, __KeyType, __ValueType, __Hasher>,
    public __hidden::__impl::__HashMapKeyProxyContainsOfIterableClient <KeySetProxy, __KeyType, __ValueType, __Hasher>,
    public __hidden::__impl::__HashMapKeyProxyContainsOfInitializerListClient <KeySetProxy, __KeyType, __ValueType, __Hasher>,
    public __hidden::__impl::__HashMapKeyProxyDelegateForwardConstIterableClient <KeySetProxy, __KeyType, __ValueType, __Hasher> {
  
protected:
  using HashMapBase                           = HashMap <__KeyType, __ValueType, __Hasher>;
  using Server                                = __hidden::__impl::__HashMapKeyProxyServer <KeySetProxy, __KeyType, __ValueType, __Hasher>;
  using RandomInsertionClient                 = __hidden::__impl::__HashMapKeyProxyRandomInsertionClient <KeySetProxy, __KeyType, __ValueType, __Hasher>;
  using IteratorRemoveClient                  = __hidden::__impl::__HashMapKeyProxyIteratorRemoveClient <KeySetProxy, __KeyType, __ValueType, __Hasher>;
  using FindOfIterableClient                  = __hidden::__impl::__HashMapKeyProxyFindOfIterableClient <KeySetProxy, __KeyType, __ValueType, __Hasher>;
  using FindOfInitializerListClient           = __hidden::__impl::__HashMapKeyProxyFindOfInitializerListClient <KeySetProxy, __KeyType, __ValueType, __Hasher>;
  using FindByClient                          = __hidden::__impl::__HashMapKeyProxyFindByClient <KeySetProxy, __KeyType, __ValueType, __Hasher>;
  using RemoveOfIterableClient                = __hidden::__impl::__HashMapKeyProxyRemoveOfIterableClient <KeySetProxy, __KeyType, __ValueType, __Hasher>;
  using RemoveOfInitializerListClient         = __hidden::__impl::__HashMapKeyProxyRemoveOfInitializerListClient <KeySetProxy, __KeyType, __ValueType, __Hasher>;
  using RemoveByClient                        = __hidden::__impl::__HashMapKeyProxyRemoveByClient <KeySetProxy, __KeyType, __ValueType, __Hasher>;
  using GenericStatementsClient               = __hidden::__impl::__HashMapKeyProxyGenericStatementsClient <KeySetProxy, __KeyType, __ValueType, __Hasher>;
  using ContainsOfIterableClient              = __hidden::__impl::__HashMapKeyProxyContainsOfIterableClient <KeySetProxy, __KeyType, __ValueType, __Hasher>;
  using ContainsOfInitializerListClient       = __hidden::__impl::__HashMapKeyProxyContainsOfInitializerListClient <KeySetProxy, __KeyType, __ValueType, __Hasher>;
  using FindUniqueClient                      = __hidden::__impl::__HashMapKeyProxyFindUniqueClient <KeySetProxy, __KeyType, __ValueType, __Hasher>;
  using DelegateForwardConstIterableClient    = __hidden::__impl::__HashMapKeyProxyDelegateForwardConstIterableClient <KeySetProxy, __KeyType, __ValueType, __Hasher>;

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

  __CDS_Explicit constexpr KeySetProxy (HashMap <__KeyType, __ValueType, __Hasher>* pMap) noexcept;
  KeySetProxy (KeySetProxy const&) noexcept = delete;
  KeySetProxy (KeySetProxy&&) noexcept = delete;
  __CDS_cpplang_ConstexprDestructor ~KeySetProxy() noexcept override;
  auto operator = (KeySetProxy const&) noexcept -> KeySetProxy& = delete;
  auto operator = (KeySetProxy&&) noexcept -> KeySetProxy& = delete;

  __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto contains (
      __KeyType const& key
  ) const noexcept -> bool override;

  __CDS_NoDiscard auto operator == (
      KeySetProxy const & set
  ) const noexcept -> bool;

  __CDS_NoDiscard auto operator != (
      KeySetProxy const & set
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

#endif // __CDS_HASH_MAP_KEY_SET_PROXY_HPP__
