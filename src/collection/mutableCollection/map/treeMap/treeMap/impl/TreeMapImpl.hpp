//
// Created by stefan on 26.09.2022.
//

#ifndef __CDS_TREE_MAP_IMPL_HPP__
#define __CDS_TREE_MAP_IMPL_HPP__    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
#pragma once

namespace cds {
template <typename __KeyType, typename __ValueType, typename __Comparator>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_ConstexprOverride auto TreeMap <__KeyType, __ValueType, __Comparator>::__iicch_obtainGenericHandler (         // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
   cds::__hidden::__impl::__IterableInternalRequestType requestType
) noexcept -> __GenericHandler {
  return __ms_handlers() [static_cast <uint32> (requestType)];
}


template <typename __KeyType, typename __ValueType, typename __Comparator>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_ConstexprOverride auto TreeMap <__KeyType, __ValueType, __Comparator>::__iicch_obtainGenericConstHandler (         // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
   cds::__hidden::__impl::__IterableInternalRequestType requestType
) const noexcept -> __GenericConstHandler {
  return __ms_constHandlers() [static_cast <uint32> (requestType)];
}


template <typename __KeyType, typename __ValueType, typename __Comparator>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_ConstexprOverride auto TreeMap <__KeyType, __ValueType, __Comparator>::keys () const noexcept -> KeySetProxy const& {
  return _keySetProxy;
}


template <typename __KeyType, typename __ValueType, typename __Comparator>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_ConstexprOverride auto TreeMap <__KeyType, __ValueType, __Comparator>::keys () noexcept -> KeySetProxy& {
  return _keySetProxy;
}


template <typename __KeyType, typename __ValueType, typename __Comparator>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_ConstexprOverride auto TreeMap <__KeyType, __ValueType, __Comparator>::values () const noexcept -> ValueMutableCollectionProxy const& {
  return _valueMutableCollectionProxy;
}


template <typename __KeyType, typename __ValueType, typename __Comparator>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_ConstexprOverride auto TreeMap <__KeyType, __ValueType, __Comparator>::values () noexcept -> ValueMutableCollectionProxy& {
  return _valueMutableCollectionProxy;
}


template <typename __KeyType, typename __ValueType, typename __Comparator>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_ConstexprOverride auto TreeMap <__KeyType, __ValueType, __Comparator>::entries () const noexcept -> EntryMutableCollectionProxy const& {
  return _entryMutableCollectionProxy;
}


template <typename __KeyType, typename __ValueType, typename __Comparator>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_ConstexprOverride auto TreeMap <__KeyType, __ValueType, __Comparator>::entries () noexcept -> EntryMutableCollectionProxy& {
  return _entryMutableCollectionProxy;
}


template <typename __KeyType, typename __ValueType, typename __Comparator>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
constexpr TreeMap <__KeyType, __ValueType, __Comparator>::TreeMap () noexcept :
    _keySetProxy (this),
    _valueMutableCollectionProxy (this),
    _entryMutableCollectionProxy (this) {

}


template <typename __KeyType, typename __ValueType, typename __Comparator>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
TreeMap <__KeyType, __ValueType, __Comparator>::TreeMap (TreeMap const& map) noexcept(false) :
    _keySetProxy(this), _valueMutableCollectionProxy(this), _entryMutableCollectionProxy(this) {
  this->template __rbt_copyCleared <&__hidden::__impl::__treeMapCopyConstructor <__KeyType, __ValueType>> (map);
}


template <typename __KeyType, typename __ValueType, typename __Comparator>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
constexpr TreeMap <__KeyType, __ValueType, __Comparator>::TreeMap (TreeMap&& map) noexcept :
    _keySetProxy(this), _valueMutableCollectionProxy(this), _entryMutableCollectionProxy(this),
    Implementation (std::move (map)) {

}


template <typename __KeyType, typename __ValueType, typename __Comparator>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <
  typename __TElementType,        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  typename __IteratorType,        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  cds::meta::EnableIf <cds::meta::IsCopyConstructible <__TElementType>::value>
> TreeMap <__KeyType, __ValueType, __Comparator>::TreeMap (
    __IteratorType const& begin,
    __IteratorType const& end,
    Size                  count
) noexcept(false) :
    _keySetProxy(this), _valueMutableCollectionProxy(this), _entryMutableCollectionProxy(this) {
  (void) count;
  for (auto iterator = begin; iterator != end; ++iterator) {
    insert (*iterator);
  }
}


template <typename __KeyType, typename __ValueType, typename __Comparator>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <
    typename __TElementType,    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    cds::meta::EnableIf <cds::meta::IsCopyConstructible <__TElementType>::value>
> __CDS_OptimalInline TreeMap <__KeyType, __ValueType, __Comparator>::TreeMap (
    std::initializer_list <__ElementType> const& initializer_list
) noexcept(false) :
    TreeMap (initializer_list.begin(), initializer_list.end(), initializer_list.size()) {

}


template <typename __KeyType, typename __ValueType, typename __Comparator>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename __IterableType>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline TreeMap <__KeyType, __ValueType, __Comparator>::TreeMap (
    __IterableType const& iterable
) noexcept(false) :
    TreeMap (iterable.begin(), iterable.end()) {

}


template <typename __KeyType, typename __ValueType, typename __Comparator>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_ConstexprDestructor TreeMap <__KeyType, __ValueType, __Comparator>::~TreeMap () noexcept {
  __rbt_clear();
}


template <typename __KeyType, typename __ValueType, typename __Comparator>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
auto TreeMap <__KeyType, __ValueType, __Comparator>::operator = (TreeMap const& map) noexcept(false) -> TreeMap& {
  this->__rbt_copy <&__hidden::__impl ::__treeMapCopyConstructor <__KeyType, __ValueType>> (map);
  return *this;
}


template <typename __KeyType, typename __ValueType, typename __Comparator>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
auto TreeMap <__KeyType, __ValueType, __Comparator>::operator = (TreeMap&& map) noexcept -> TreeMap& {
  __rbt_move (std::move (map));
  return *this;
}


template <typename __KeyType, typename __ValueType, typename __Comparator>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_ConstexprOverride auto TreeMap <__KeyType, __ValueType, __Comparator>::size () const noexcept -> Size {
  return __rbt_size();
}


template <typename __KeyType, typename __ValueType, typename __Comparator>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
auto TreeMap <__KeyType, __ValueType, __Comparator>::clear () noexcept -> void {
  __rbt_clear();
}


template <typename __KeyType, typename __ValueType, typename __Comparator>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
auto TreeMap <__KeyType, __ValueType, __Comparator>::remove (
    __KeyType const& key
) noexcept -> bool {
  return __rbt_remove (key);
}


template <typename __KeyType, typename __ValueType, typename __Comparator>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_VirtualConstexpr auto TreeMap <__KeyType, __ValueType, __Comparator>::containsKey (
    __KeyType const& key
) const noexcept -> bool {
  return __rbt_get (key) != nullptr;
}


template <typename __KeyType, typename __ValueType, typename __Comparator>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_VirtualConstexpr auto TreeMap <__KeyType, __ValueType, __Comparator>::containsValue (
    __ValueType const & value
) const noexcept -> bool {
  for (auto it = __rbt_cbegin(); it != __rbt_cend(); ++it) {
    if (cds::meta::equals ((*it).value(), value))
      return true;
  }

  return false;
}


template <typename __KeyType, typename __ValueType, typename __Comparator>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
auto TreeMap <__KeyType, __ValueType, __Comparator>::entryAt (
    __KeyType const&  key,
    bool*             pNewElementCreated
) noexcept -> EntryType* {
  return __rbt_get (key, pNewElementCreated);
}


template <typename __KeyType, typename __ValueType, typename __Comparator>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
auto TreeMap <__KeyType, __ValueType, __Comparator>::entryAt (
    __KeyType const& key
) const noexcept -> EntryType const* {
  return __rbt_get (key);
}


template <typename __KeyType, typename __ValueType, typename __Comparator>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_ConstexprConditioned auto TreeMap <__KeyType, __ValueType, __Comparator>::operator == (
    TreeMap const& map
) const noexcept -> bool {
  if (this == &map) {
    return true;
  }

  return __rbt_equals (map);
}


template <
    typename __KeyType,             // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __ValueType,           // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __Hasher               // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> __CDS_cpplang_ConstexprConditioned auto TreeMap <
    __KeyType,
    __ValueType,
    __Hasher
>::operator != (
    TreeMap const & map
) const noexcept -> bool {

  if ( this == & map ) {
    return false;
  }

  return ! __rbt_equals (map);
}
}
#endif // __CDS_TREE_MAP_IMPL_HPP__
