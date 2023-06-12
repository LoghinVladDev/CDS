// NOLINT(llvm-header-guard)
// Created by loghin on 14/08/22.
//

#ifndef __CDS_MAP_ABSTRACT_ENTRY_MUTABLE_COLLECTION_PROXY_HPP__ // NOLINT(llvm-header-guard)
#define __CDS_MAP_ABSTRACT_ENTRY_MUTABLE_COLLECTION_PROXY_HPP__ // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
#pragma once

namespace cds {
template <typename __KeyType, typename __ValueType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs Map <__KeyType, __ValueType>::AbstractEntryMutableCollectionProxy :
    public cds::MutableCollection <EntryType>,
    protected Map <__KeyType, __ValueType>::AbstractMapProxy {
protected:
  using ProxyBase             = Map <__KeyType, __ValueType>::AbstractMapProxy;
  using MutableCollectionBase = MutableCollection <EntryType>;

public:
  AbstractEntryMutableCollectionProxy (
      AbstractEntryMutableCollectionProxy const&
  ) noexcept = delete;

  AbstractEntryMutableCollectionProxy (
      AbstractEntryMutableCollectionProxy&&
  ) noexcept = delete;

  __CDS_cpplang_ConstexprDestructor ~AbstractEntryMutableCollectionProxy () noexcept override;

  auto operator = (
      AbstractEntryMutableCollectionProxy const&
  ) noexcept -> AbstractEntryMutableCollectionProxy& = delete;

  auto operator = (
      AbstractEntryMutableCollectionProxy&&
  ) noexcept -> AbstractEntryMutableCollectionProxy& = delete;

  auto clear () noexcept -> void override;

  __CDS_NoDiscard auto toString () const noexcept(false) -> String override;

  __CDS_NoDiscard __CDS_cpplang_VirtualConstexpr auto size () const noexcept -> Size override; // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-non-private-member-variables-in-classes)

protected:
  using typename MutableCollectionBase::__GenericHandler;         // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  using typename MutableCollectionBase::__GenericConstHandler;    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

  using AbstractMapProxy::map;

  __CDS_MaybeUnused __CDS_Explicit constexpr AbstractEntryMutableCollectionProxy ( // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-non-private-member-variables-in-classes)
      Map <__KeyType, __ValueType>* pMap
  ) noexcept;
};

} // namespace cds

#endif // __CDS_MAP_ABSTRACT_ENTRY_MUTABLE_COLLECTION_PROXY_HPP__
