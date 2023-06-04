// NOLINT(llvm-header-guard)
// Created by loghin on 14/08/22.
//

#ifndef __CDS_MAP_ABSTRACT_ENTRY_MUTABLE_COLLECTION_PROXY_IMPL_HPP__ // NOLINT(llvm-header-guard)
#define __CDS_MAP_ABSTRACT_ENTRY_MUTABLE_COLLECTION_PROXY_IMPL_HPP__ // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
#pragma once

namespace cds {
template <typename __KeyType, typename __ValueType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_MaybeUnused constexpr Map <__KeyType, __ValueType>::AbstractEntryMutableCollectionProxy::AbstractEntryMutableCollectionProxy (
    Map <__KeyType, __ValueType>* pMap
) noexcept : ProxyBase (pMap) {

}


template <typename __KeyType, typename __ValueType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto Map <__KeyType, __ValueType>::AbstractEntryMutableCollectionProxy::clear () noexcept -> void {
  map()->clear();
}


template <typename __KeyType, typename __ValueType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_ConstexprDestructor Map <__KeyType, __ValueType>::AbstractEntryMutableCollectionProxy::~AbstractEntryMutableCollectionProxy () noexcept = default;


template <typename __KeyType, typename __ValueType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_VirtualConstexpr auto Map <__KeyType, __ValueType>::AbstractEntryMutableCollectionProxy::size () const noexcept -> Size {
  return map()->size();
}


template <typename __KeyType, typename __ValueType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto Map <__KeyType, __ValueType>::AbstractEntryMutableCollectionProxy::toString () const noexcept -> String {
  return map()->toString();
}

} // namespace cds

#endif // __CDS_MAP_ABSTRACT_ENTRY_MUTABLE_COLLECTION_PROXY_IMPL_HPP__
