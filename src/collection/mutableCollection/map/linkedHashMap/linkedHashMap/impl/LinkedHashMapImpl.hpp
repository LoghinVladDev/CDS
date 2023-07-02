//  NOLINT(llvm-header-guard)
// Created by loghin on 09/10/22.
//

#ifndef __CDS_LINKED_HASH_MAP_IMPL_HPP__ // NOLINT(llvm-header-guard) 
#define __CDS_LINKED_HASH_MAP_IMPL_HPP__ // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
#pragma once

namespace cds {
template <typename __KeyType, typename __ValueType, typename __Hasher>       // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
__CDS_cpplang_ConstexprOverride auto LinkedHashMap <__KeyType, __ValueType, __Hasher>::__iicch_obtainGenericHandler (
    __hidden::__impl::__IterableInternalRequest requestType
) noexcept -> __GenericHandler {
  return __ms_handlers() [static_cast <uint32> (requestType)];
}


template <typename __KeyType, typename __ValueType, typename __Hasher>       // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
__CDS_cpplang_ConstexprOverride auto LinkedHashMap <__KeyType, __ValueType, __Hasher>::__iicch_obtainGenericConstHandler (
    __hidden::__impl::__IterableInternalRequest requestType
) const noexcept -> __GenericConstHandler {
  return __ms_constHandlers() [static_cast <uint32> (requestType)];
}


template <typename __KeyType, typename __ValueType, typename __Hasher>       // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
__CDS_OptimalInline auto LinkedHashMap <__KeyType, __ValueType, __Hasher>::__begin (
    LinkedHashMap* pObject
) noexcept -> __hidden::__impl ::__AbstractDelegateIterator <EntryType>* {
  return Memory::instance().create < __hidden::__impl::__DelegateIterator <EntryType, Iterator>> (
      pObject->__sll_begin()
  );
}


template <typename __KeyType, typename __ValueType, typename __Hasher>       // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
__CDS_OptimalInline auto LinkedHashMap <__KeyType, __ValueType, __Hasher>::__end (
    LinkedHashMap* pObject
) noexcept -> __hidden::__impl ::__AbstractDelegateIterator <EntryType>* {
  return Memory::instance().create < __hidden::__impl::__DelegateIterator <EntryType, Iterator>> (
      pObject->__sll_end()
  );
}


template <typename __KeyType, typename __ValueType, typename __Hasher>       // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
__CDS_cpplang_NonConstConstexprMemberFunction auto LinkedHashMap <__KeyType, __ValueType, __Hasher>::__beginLocal (
    LinkedHashMap* pObject
) noexcept -> Iterator {
  return pObject->__sll_begin();
}


template <typename __KeyType, typename __ValueType, typename __Hasher>       // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
__CDS_cpplang_NonConstConstexprMemberFunction auto LinkedHashMap <__KeyType, __ValueType, __Hasher>::__endLocal (
    LinkedHashMap* pObject
) noexcept -> Iterator {
  return pObject->__sll_end();
}


template <typename __KeyType, typename __ValueType, typename __Hasher>       // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
__CDS_OptimalInline auto LinkedHashMap <__KeyType, __ValueType, __Hasher>::__cbegin (
    LinkedHashMap const* pObject
) noexcept -> __hidden::__impl ::__AbstractDelegateIterator <EntryType const>* {
  return Memory::instance().create <__hidden::__impl::__DelegateIterator <EntryType const, ConstIterator>> (
      pObject->__sll_cbegin()
  );
}


template <typename __KeyType, typename __ValueType, typename __Hasher>       // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
__CDS_OptimalInline auto LinkedHashMap <__KeyType, __ValueType, __Hasher>::__cend (
    LinkedHashMap const* pObject
) noexcept -> __hidden::__impl ::__AbstractDelegateIterator <EntryType const>* {
  return Memory::instance().create <__hidden::__impl::__DelegateIterator <EntryType const, ConstIterator>> (
      pObject->__sll_cend()
  );
}


template <typename __KeyType, typename __ValueType, typename __Hasher>       // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
constexpr auto LinkedHashMap <__KeyType, __ValueType, __Hasher>::__cbeginLocal (
    LinkedHashMap const* pObject
) noexcept -> ConstIterator {
  return pObject->__sll_cbegin();
}


template <typename __KeyType, typename __ValueType, typename __Hasher>       // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
constexpr auto LinkedHashMap <__KeyType, __ValueType, __Hasher>::__cendLocal (
    LinkedHashMap const* pObject
) noexcept -> ConstIterator {
  return pObject->__sll_cend();
}


template <typename __KeyType, typename __ValueType, typename __Hasher>       // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
__CDS_OptimalInline auto LinkedHashMap <__KeyType, __ValueType, __Hasher>::__newAddress (
    LinkedHashMap*    pObject,
    EntryType const*  pReferenceElement,
    bool*             pNewElementCreated
) noexcept -> EntryType* {
  auto ppNewNode = pObject->__ht_get (pReferenceElement->key(), pNewElementCreated);
  if (*pNewElementCreated) {
    auto pNewElement = pObject->__sll_newBack();
    *ppNewNode = pObject->__sll_backNode();
    return pNewElement;
  }

  return &(*ppNewNode)->_data;
}


template <typename __KeyType, typename __ValueType, typename __Hasher>       // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
__CDS_OptimalInline auto LinkedHashMap <__KeyType, __ValueType, __Hasher>::__remove (
    LinkedHashMap*  pObject,
    Iterator const* pIterator
) noexcept -> bool {
  if (pIterator == nullptr || *pIterator == pObject->__sll_end()) {
    return false;
  }

  return pObject->__ht_remove((**pIterator).key()) && pObject->__sll_removeIterator(*pIterator);
}


template <typename __KeyType, typename __ValueType, typename __Hasher>       // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
__CDS_OptimalInline auto LinkedHashMap <__KeyType, __ValueType, __Hasher>::__removeConst (
    LinkedHashMap*        pObject,
    ConstIterator const*  pIterator
) noexcept -> bool {
  if (pIterator == nullptr || *pIterator == pObject->__sll_cend()) {
    return false;
  }

  return pObject->__ht_remove((**pIterator).key()) && pObject->__sll_removeConstIterator(*pIterator);
}


template <typename __KeyType, typename __ValueType, typename __Hasher>       // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
__CDS_OptimalInline auto LinkedHashMap <__KeyType, __ValueType, __Hasher>::__removeArray (
    LinkedHashMap*          pObject,
    Iterator const* const*  ppIterators,
    Size                    iteratorArraySize
) noexcept -> Size {
  for (Size index = 0u; index < iteratorArraySize; ++ index ) {
    pObject->__ht_remove ((**ppIterators[index]).key());
  }

  auto removedCount = pObject->__sll_removeIteratorArray (&ppIterators [0u], iteratorArraySize);
  return removedCount;
}


template <typename __KeyType, typename __ValueType, typename __Hasher>       // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
__CDS_OptimalInline auto LinkedHashMap <__KeyType, __ValueType, __Hasher>::__removeConstArray (
    LinkedHashMap*              pObject,
    ConstIterator const* const* ppIterators,
    Size                        iteratorArraySize
) noexcept -> Size {
  for (Size index = 0u; index < iteratorArraySize; ++ index ) {
    pObject->__ht_remove ((**ppIterators[index]).key());
  }

  auto removedCount = pObject->__sll_removeConstIteratorArray (&ppIterators [0u], iteratorArraySize);
  return removedCount;
}


template <typename __KeyType, typename __ValueType, typename __Hasher>       // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
__CDS_MaybeUnused __CDS_OptimalInline auto LinkedHashMap <__KeyType, __ValueType, __Hasher>::__find (
    LinkedHashMap*    pObject,
    __KeyType const&  element
) noexcept -> __hidden::__impl::__AbstractDelegateIterator <EntryType>* {
  using Delegate = __hidden::__impl::__DelegateIterator <EntryType, Iterator>;
  auto ppNode = pObject->__ht_at(element);
  return Memory::instance().create <Delegate> (Iterator(ppNode == nullptr ? nullptr : *ppNode));
}


template <typename __KeyType, typename __ValueType, typename __Hasher>       // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
__CDS_OptimalInline auto LinkedHashMap <__KeyType, __ValueType, __Hasher>::__findConst (
    LinkedHashMap const*  pObject,
    __KeyType const&      element
) noexcept -> __hidden::__impl::__AbstractDelegateIterator <EntryType const>* {
  using Delegate = __hidden::__impl::__DelegateIterator <EntryType const, ConstIterator>;
  auto ppNode = pObject->__ht_atConst(element);
  return Memory::instance().create <Delegate> (ConstIterator(ppNode == nullptr ? nullptr : *ppNode));
}


template <typename __KeyType, typename __ValueType, typename __Hasher>       // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
__CDS_cpplang_NonConstConstexprMemberFunction auto LinkedHashMap <__KeyType, __ValueType, __Hasher>::__findLocal (
    LinkedHashMap*    pObject,
    __KeyType const&  element
) noexcept -> Iterator {
  auto ppNode = pObject->__ht_at(element);
  return Iterator(ppNode == nullptr ? nullptr : *ppNode);
}


template <typename __KeyType, typename __ValueType, typename __Hasher>       // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
__CDS_cpplang_ConstexprConditioned auto LinkedHashMap <__KeyType, __ValueType, __Hasher>::__findConstLocal (
    LinkedHashMap const*  pObject,
    __KeyType const&      element
) noexcept -> ConstIterator {
  auto ppNode = pObject->__ht_atConst(element);
  return ConstIterator(ppNode == nullptr ? nullptr : *ppNode);
}


template <typename __KeyType, typename __ValueType, typename __Hasher>       // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
__CDS_cpplang_ConstexprOverride auto LinkedHashMap <__KeyType, __ValueType, __Hasher>::keys () const noexcept -> KeySetProxy const& {
  return _keySetProxy;
}


template <typename __KeyType, typename __ValueType, typename __Hasher>       // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
__CDS_cpplang_ConstexprOverride auto LinkedHashMap <__KeyType, __ValueType, __Hasher>::keys () noexcept -> KeySetProxy& {
  return _keySetProxy;
}


template <typename __KeyType, typename __ValueType, typename __Hasher>       // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
__CDS_cpplang_ConstexprOverride auto LinkedHashMap <__KeyType, __ValueType, __Hasher>::values () const noexcept -> ValueMutableCollectionProxy const& {
  return _valueMutableCollectionProxy;
}


template <typename __KeyType, typename __ValueType, typename __Hasher>       // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
__CDS_cpplang_ConstexprOverride auto LinkedHashMap <__KeyType, __ValueType, __Hasher>::values () noexcept -> ValueMutableCollectionProxy& {
  return _valueMutableCollectionProxy;
}


template <typename __KeyType, typename __ValueType, typename __Hasher>       // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
__CDS_cpplang_ConstexprOverride auto LinkedHashMap <__KeyType, __ValueType, __Hasher>::entries () const noexcept -> EntryMutableCollectionProxy const& {
  return _entryMutableCollectionProxy;
}


template <typename __KeyType, typename __ValueType, typename __Hasher>       // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
__CDS_cpplang_ConstexprOverride auto LinkedHashMap <__KeyType, __ValueType, __Hasher>::entries () noexcept -> EntryMutableCollectionProxy& {
  return _entryMutableCollectionProxy;
}


template <typename __KeyType, typename __ValueType, typename __Hasher>       // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
constexpr LinkedHashMap <__KeyType, __ValueType, __Hasher>::LinkedHashMap () noexcept :
    _keySetProxy (this), _valueMutableCollectionProxy (this), _entryMutableCollectionProxy (this) {

}


template <typename __KeyType, typename __ValueType, typename __Hasher>       // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
__CDS_OptimalInline LinkedHashMap <__KeyType, __ValueType, __Hasher>::LinkedHashMap (
    LinkedHashMap const& map
) noexcept(false) :
    _keySetProxy (this), _valueMutableCollectionProxy (this), _entryMutableCollectionProxy (this) {
  // Copy of each not possible, linked list references hash table elements from other map 
  for (auto iterator = map.cbegin(), end = map.cend(); iterator != end; ++iterator) {  // NOLINT(clion-misra-cpp2008-8-0-1)
    insert (*iterator);
  }
}


template <typename __KeyType, typename __ValueType, typename __Hasher>       // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
constexpr LinkedHashMap <__KeyType, __ValueType, __Hasher>::LinkedHashMap (
    LinkedHashMap&& map
) noexcept :
    _keySetProxy (this), _valueMutableCollectionProxy (this), _entryMutableCollectionProxy (this),
    HashTableImplementation (std::move (map)),
    LinkedListImplementation (std::move (map)) {

}


template <typename __KeyType, typename __ValueType, typename __Hasher>       // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
constexpr LinkedHashMap <__KeyType, __ValueType, __Hasher>::LinkedHashMap (
    __Hasher const & hasher
) noexcept :
    _keySetProxy (this), _valueMutableCollectionProxy (this), _entryMutableCollectionProxy (this),
    HashTableImplementation (hasher) {

}


template <typename __KeyType, typename __ValueType, typename __Hasher>       // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
template <
    typename __IteratorType,    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
    typename __TElementType,    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
    cds::meta::EnableIf <cds::meta::IsCopyConstructible <__TElementType>::value>
> __CDS_OptimalInline LinkedHashMap <__KeyType, __ValueType, __Hasher>::LinkedHashMap (
    __IteratorType const& begin,
    __IteratorType const& end,
    Size                  count
) noexcept(false) :
    _keySetProxy (this), _valueMutableCollectionProxy (this), _entryMutableCollectionProxy (this) {
  (void) count;
  for (auto iterator = begin; iterator != end; ++iterator) {
    (void) insert (*iterator);
  }
}


template <typename __KeyType, typename __ValueType, typename __Hasher>       // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
template <
    typename __IteratorType,    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
    typename __TElementType,    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
    cds::meta::EnableIf <cds::meta::IsCopyConstructible <__TElementType>::value>
> __CDS_OptimalInline LinkedHashMap <__KeyType, __ValueType, __Hasher>::LinkedHashMap (
    __Hasher const&       hasher,
    __IteratorType const& begin,
    __IteratorType const& end,
    Size                  count
) noexcept(false) :
    _keySetProxy (this), _valueMutableCollectionProxy (this), _entryMutableCollectionProxy (this),
    HashTableImplementation (hasher) {

  (void) count;
  for (auto iterator = begin; iterator != end; ++iterator) {
    (void) insert (*iterator);
  }
}


template <typename __KeyType, typename __ValueType, typename __Hasher>       // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
template <
    typename __TElementType,    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
    cds::meta::EnableIf <cds::meta::IsCopyConstructible <__TElementType>::value>
> __CDS_OptimalInline LinkedHashMap <__KeyType, __ValueType, __Hasher>::LinkedHashMap (
    std::initializer_list <ElementType> const& initializerList
) noexcept(false) :
    LinkedHashMap (initializerList.begin(), initializerList.end(), initializerList.size()) {

}


template <typename __KeyType, typename __ValueType, typename __Hasher>       // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
template <
    typename __TElementType,    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
    cds::meta::EnableIf <cds::meta::IsCopyConstructible <__TElementType>::value>
> __CDS_OptimalInline LinkedHashMap <__KeyType, __ValueType, __Hasher>::LinkedHashMap (
    __Hasher const&                             hasher,
    std::initializer_list <ElementType> const&  initializerList
) noexcept(false) :
    LinkedHashMap (hasher, initializerList.begin(), initializerList.end(), initializerList.size()) {

}


template <typename __KeyType, typename __ValueType, typename __Hasher>       // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
template <typename __IterableType>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline LinkedHashMap <__KeyType, __ValueType, __Hasher>::LinkedHashMap (
    __IterableType const& iterable
) noexcept(false) :
    LinkedHashMap (iterable.begin(), iterable.end()) {

}


template <typename __KeyType, typename __ValueType, typename __Hasher>       // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
template <typename __IterableType>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
__CDS_OptimalInline LinkedHashMap <__KeyType, __ValueType, __Hasher>::LinkedHashMap (
    __Hasher const&       hasher,
    __IterableType const& iterable
) noexcept(false) :
    LinkedHashMap (hasher, iterable.begin(), iterable.end()) {

}


template <typename __KeyType, typename __ValueType, typename __Hasher>       // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
LinkedHashMap <__KeyType, __ValueType, __Hasher>::~LinkedHashMap () noexcept {
  __ht_clear ();
  __sll_clear ();
}


template <typename __KeyType, typename __ValueType, typename __Hasher>       // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
__CDS_OptimalInline auto LinkedHashMap <__KeyType, __ValueType, __Hasher>::operator = (
    LinkedHashMap const& map
) noexcept(false) -> LinkedHashMap& {
  if (this == &map) {
    return *this;
  }

  __sll_clear ();
  __ht_clear ();
  // Copy of each not possible, linked list references hash table elements from other map 
  for (auto iterator = map.cbegin(), end = map.cend(); iterator != end; ++iterator) {  // NOLINT(clion-misra-cpp2008-8-0-1)
    insert (*iterator);
  }

  return *this;
}


template <typename __KeyType, typename __ValueType, typename __Hasher>       // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
__CDS_OptimalInline auto LinkedHashMap <__KeyType, __ValueType, __Hasher>::operator = (
    LinkedHashMap&& map
) noexcept -> LinkedHashMap& {
  if (this == &map) {
    return *this;
  }

  __ht_move (std::move (map));
  __sll_move (std::move (map));
  return *this;
}


template <typename __KeyType, typename __ValueType, typename __Hasher>       // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
__CDS_OptimalInline auto LinkedHashMap <__KeyType, __ValueType, __Hasher>::operator = (
    std::initializer_list <EntryType> const& initializerList
) noexcept(false) -> LinkedHashMap& {
  __ht_clear ();
  __sll_clear ();
  for (auto iterator = initializerList.begin(), end = initializerList.end(); iterator != end; ++iterator) {    // NOLINT(clion-misra-cpp2008-8-0-1)
    (void) insert (*iterator);
  }

  return *this;
}


template <typename __KeyType, typename __ValueType, typename __Hasher>       // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
template <typename __IterableType>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto LinkedHashMap <__KeyType, __ValueType, __Hasher>::operator = (
    __IterableType const& iterable
) noexcept(false) -> LinkedHashMap& {
  if (this == &iterable) {
    return *this;
  }

  __ht_clear ();
  __sll_clear ();
  for (auto iterator = iterable.begin(), end = iterable.end(); iterator != end; ++iterator) {  // NOLINT(clion-misra-cpp2008-8-0-1)
    insert (*iterator);
  }

  return *this;
}


template <typename __KeyType, typename __ValueType, typename __Hasher>       // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
__CDS_OptimalInline auto LinkedHashMap <__KeyType, __ValueType, __Hasher>::clear () noexcept -> void {
  __ht_clear();
  __sll_clear();
}


template <typename __KeyType, typename __ValueType, typename __Hasher>       // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
__CDS_cpplang_ConstexprOverride auto LinkedHashMap <__KeyType, __ValueType, __Hasher>::size () const noexcept -> Size {
  return __ht_size();
}


template <typename __KeyType, typename __ValueType, typename __Hasher>       // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
__CDS_OptimalInline auto LinkedHashMap <__KeyType, __ValueType, __Hasher>::remove (
    KeyType const& key
) noexcept -> bool {
  return __ht_remove (key) && __sll_removeIf(key, &__hidden::__impl::__linkedHashMapLinkedListRemoveIf <__KeyType, __ValueType>);
}


template <typename __KeyType, typename __ValueType, typename __Hasher>       // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
__CDS_cpplang_ConstexprConditioned auto LinkedHashMap <__KeyType, __ValueType, __Hasher>::operator == (
    LinkedHashMap const &map
) const noexcept -> bool {
  if (this == &map) {
    return true;
  }

  return __sll_equals (map);
}


template <typename __KeyType, typename __ValueType, typename __Hasher>       // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
__CDS_cpplang_ConstexprConditioned auto LinkedHashMap <__KeyType, __ValueType, __Hasher>::operator != (
    LinkedHashMap const& map
) const noexcept -> bool {
  if (this == &map) {
    return false;
  }

  return !__sll_equals (map);
}


template <typename __KeyType, typename __ValueType, typename __Hasher>       // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
__CDS_cpplang_ConstexprOverride auto LinkedHashMap <__KeyType, __ValueType, __Hasher>::containsKey (
    __KeyType const& key
) const noexcept -> bool {
  return __ht_getConst (key) != nullptr;
}


template <typename __KeyType, typename __ValueType, typename __Hasher>       // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
__CDS_cpplang_ConstexprOverride auto LinkedHashMap <__KeyType, __ValueType, __Hasher>::containsValue (
    __ValueType const& value
) const noexcept -> bool {
  for (auto iterator = __sll_cbegin (), end = __sll_cend (); iterator != end; ++iterator) {    // NOLINT(clion-misra-cpp2008-8-0-1)
    if (cds::meta::equals ((*iterator).value(), value)) {
      return true;
    }
  }

  return false;
}


template <typename __KeyType, typename __ValueType, typename __Hasher>       // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
__CDS_OptimalInline auto LinkedHashMap <__KeyType, __ValueType, __Hasher>::entryAt (
    __KeyType const&  key,
    bool*             pNewElementCreated
) noexcept -> EntryType* {
  auto ppNewNode = __ht_get (key, pNewElementCreated);
  if (*pNewElementCreated) {
    auto pNewElement = __sll_newBack();
    *ppNewNode = __sll_backNode();
    return pNewElement;
  }

  return nullptr;
}


template <typename __KeyType, typename __ValueType, typename __Hasher>       // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
__CDS_cpplang_ConstexprOverride auto LinkedHashMap <__KeyType, __ValueType, __Hasher>::entryAt (
    __KeyType const& key
) const noexcept -> EntryType const* {
  auto const* entry = __ht_getConst(key);
  return entry == nullptr ? nullptr : &(*entry)->_data;
}

} // namespace cds 

#endif // __CDS_LINKED_HASH_MAP_IMPL_HPP__ 
