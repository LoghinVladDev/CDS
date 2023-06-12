// NOLINT(llvm-header-guard)
// Created by loghin on 14/08/22.
//

#ifndef __CDS_HASH_MAP_ENTRY_MUTABLE_COLLECTION_PROXY_IMPL_HPP__ // NOLINT(llvm-header-guard)
#define __CDS_HASH_MAP_ENTRY_MUTABLE_COLLECTION_PROXY_IMPL_HPP__ // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
#pragma once

namespace cds {
template <typename __KeyType, typename __ValueType, typename __Hasher>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_ConstexprOverride auto HashMap <__KeyType, __ValueType, __Hasher>::EntryMutableCollectionProxy::__iicch_obtainGenericHandler (
    __hidden::__impl::__IterableInternalRequest requestType
) noexcept -> __GenericHandler {
  return __mcs_handlers() [static_cast <uint32> (requestType)];
}


template <typename __KeyType, typename __ValueType, typename __Hasher>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_ConstexprOverride auto HashMap <__KeyType, __ValueType, __Hasher>::EntryMutableCollectionProxy::__iicch_obtainGenericConstHandler (
    __hidden::__impl::__IterableInternalRequest requestType
) const noexcept -> __GenericConstHandler {
  return __mcs_constHandlers() [static_cast <uint32> (requestType)];
}


template <typename __KeyType, typename __ValueType, typename __Hasher>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
constexpr HashMap <__KeyType, __ValueType, __Hasher>::EntryMutableCollectionProxy::EntryMutableCollectionProxy (
    HashMap <__KeyType, __ValueType, __Hasher>* pMap
) noexcept : AbstractEntryMutableCollectionProxy (pMap) {

}


template <typename __KeyType, typename __ValueType, typename __Hasher>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_ConstexprDestructor HashMap <__KeyType, __ValueType, __Hasher>::EntryMutableCollectionProxy::~EntryMutableCollectionProxy () noexcept = default;


template <typename __KeyType, typename __ValueType, typename __Hasher>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_ConstexprOverride auto HashMap <__KeyType, __ValueType, __Hasher>::EntryMutableCollectionProxy::contains (
    EntryType const& entry
) const noexcept -> bool {
  return map()->containsKey (entry.key());
}


template <typename __KeyType, typename __ValueType, typename __Hasher>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto HashMap <__KeyType, __ValueType, __Hasher>::EntryMutableCollectionProxy::__newAddress (
    EntryMutableCollectionProxy*  pObject,
    EntryType const*              pReferenceElement,
    bool*                         pIsNew
) noexcept -> EntryType* {
  return pObject->template map <HashMapBase> ()->__ht_new (pReferenceElement, pIsNew);
}


template <typename __KeyType, typename __ValueType, typename __Hasher>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto HashMap <__KeyType, __ValueType, __Hasher>::EntryMutableCollectionProxy::__begin (
    EntryMutableCollectionProxy* pObject
) noexcept -> __hidden::__impl::__AbstractDelegateIterator <EntryType>* {
  return HashMapBase::__begin (pObject->template map <HashMapBase>());
}


template <typename __KeyType, typename __ValueType, typename __Hasher>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto HashMap <__KeyType, __ValueType, __Hasher>::EntryMutableCollectionProxy::__end (
    EntryMutableCollectionProxy* pObject
) noexcept -> __hidden::__impl::__AbstractDelegateIterator <EntryType>* {
  return HashMapBase::__end (pObject->template map <HashMapBase>());
}


template <typename __KeyType, typename __ValueType, typename __Hasher>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto HashMap <__KeyType, __ValueType, __Hasher>::EntryMutableCollectionProxy::__cbegin (
    EntryMutableCollectionProxy const* pObject
) noexcept -> __hidden::__impl::__AbstractDelegateIterator <EntryType const>* {
  return HashMapBase::__cbegin (pObject->template map <HashMapBase>());
}


template <typename __KeyType, typename __ValueType, typename __Hasher>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto HashMap <__KeyType, __ValueType, __Hasher>::EntryMutableCollectionProxy::__cend (
    EntryMutableCollectionProxy const* pObject
) noexcept -> __hidden::__impl::__AbstractDelegateIterator <EntryType const>* {
  return HashMapBase::__cend (pObject->template map <HashMapBase>());
}


template <typename __KeyType, typename __ValueType, typename __Hasher>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_NonConstConstexprMemberFunction auto HashMap <__KeyType, __ValueType, __Hasher>::EntryMutableCollectionProxy::__beginLocal (
    EntryMutableCollectionProxy* pObject
) noexcept -> Iterator {
  return HashMapBase::__beginLocal (pObject->template map <HashMapBase>());
}


template <typename __KeyType, typename __ValueType, typename __Hasher>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_NonConstConstexprMemberFunction auto HashMap <__KeyType, __ValueType, __Hasher>::EntryMutableCollectionProxy::__endLocal (
    EntryMutableCollectionProxy* pObject
) noexcept -> Iterator {
  return HashMapBase::__endLocal (pObject->template map <HashMapBase>());
}


template <typename __KeyType, typename __ValueType, typename __Hasher>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
constexpr auto HashMap <__KeyType, __ValueType, __Hasher>::EntryMutableCollectionProxy::__cbeginLocal (
    EntryMutableCollectionProxy const* pObject
) noexcept -> ConstIterator {
  return HashMapBase::__cbeginLocal (pObject->template map <HashMapBase>());
}


template <typename __KeyType, typename __ValueType, typename __Hasher>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
constexpr auto HashMap <__KeyType, __ValueType, __Hasher>::EntryMutableCollectionProxy::__cendLocal (
    EntryMutableCollectionProxy const* pObject
) noexcept -> ConstIterator {
  return HashMapBase::__cendLocal (pObject->template map <HashMapBase>());
}


template <typename __KeyType, typename __ValueType, typename __Hasher>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto HashMap <__KeyType, __ValueType, __Hasher>::EntryMutableCollectionProxy::__remove (
    EntryMutableCollectionProxy*  pObject,
    Iterator const*               iterator
) noexcept -> bool {
  return HashMapBase::__remove (pObject->template map <HashMapBase>(), iterator);
}


template <typename __KeyType, typename __ValueType, typename __Hasher>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto HashMap <__KeyType, __ValueType, __Hasher>::EntryMutableCollectionProxy::__removeConst (
    EntryMutableCollectionProxy*  pObject,
    ConstIterator const*          iterator
) noexcept -> bool {
  return HashMapBase::__removeConst (pObject->template map <HashMapBase>(), iterator);
}


template <typename __KeyType, typename __ValueType, typename __Hasher>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto HashMap <__KeyType, __ValueType, __Hasher>::EntryMutableCollectionProxy::__removeArray (
    EntryMutableCollectionProxy*  pObject,
    Iterator const* const*        ppIterators,
    Size                          iteratorArrayCount
) noexcept -> Size {
  return HashMapBase::__removeArray (pObject->template map <HashMapBase>(), ppIterators, iteratorArrayCount);
}


template <typename __KeyType, typename __ValueType, typename __Hasher>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto HashMap <__KeyType, __ValueType, __Hasher>::EntryMutableCollectionProxy::__removeConstArray (
    EntryMutableCollectionProxy*  pObject,
    ConstIterator const* const*   ppIterators,
    Size                          iteratorArrayCount
) noexcept -> Size {
  return HashMapBase::__removeConstArray (pObject->template map <HashMapBase>(), ppIterators, iteratorArrayCount);
}


template <typename __KeyType, typename __ValueType, typename __Hasher>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto HashMap <__KeyType, __ValueType, __Hasher>::EntryMutableCollectionProxy::__equals (
    EntryMutableCollectionProxy const& set
) const noexcept -> bool {
  return this->template map <HashMapBase>()->__ht_equals (*set.template map <HashMapBase>());
}


template <typename __KeyType, typename __ValueType, typename __Hasher>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto HashMap <__KeyType, __ValueType, __Hasher>::EntryMutableCollectionProxy::operator == (
    EntryMutableCollectionProxy const& set
) const noexcept -> bool {
  return __equals (set);
}


template <typename __KeyType, typename __ValueType, typename __Hasher>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto HashMap <__KeyType, __ValueType, __Hasher>::EntryMutableCollectionProxy::operator != (
    EntryMutableCollectionProxy const& set
) const noexcept -> bool {
  return !__equals (set); // NOLINT(clion-misra-cpp2008-5-3-1)
}
} // namespace cds

#endif // __CDS_HASH_MAP_ENTRY_MUTABLE_COLLECTION_PROXY_IMPL_HPP__
