// NOLINT(llvm-header-guard)
// Created by loghin on 14/08/22.
//

#ifndef __CDS_MAP_ABSTRACT_VALUE_MUTABLE_COLLECTION_PROXY_HPP__ // NOLINT(llvm-header-guard)
#define __CDS_MAP_ABSTRACT_VALUE_MUTABLE_COLLECTION_PROXY_HPP__ // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
#pragma once

namespace cds {
template <typename __KeyType, typename __ValueType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs Map <__KeyType, __ValueType>::AbstractValueMutableCollectionProxy :
    public cds::MutableCollection <__ValueType>,
    protected Map <__KeyType, __ValueType>::AbstractMapProxy {
protected:
  using ProxyBase             = Map <__KeyType, __ValueType>::AbstractMapProxy;
  using MutableCollectionBase = MutableCollection <__ValueType>;

public:
  AbstractValueMutableCollectionProxy (
      AbstractValueMutableCollectionProxy const& collection
  ) noexcept = delete;

  AbstractValueMutableCollectionProxy (
      AbstractValueMutableCollectionProxy&& collection
  ) noexcept = delete;

  __CDS_cpplang_ConstexprDestructor ~AbstractValueMutableCollectionProxy () noexcept override;

  auto operator = (
      AbstractValueMutableCollectionProxy const&
  ) noexcept -> AbstractValueMutableCollectionProxy& = delete;

  auto operator = (
      AbstractValueMutableCollectionProxy&&
  ) noexcept -> AbstractValueMutableCollectionProxy& = delete;

  auto clear () noexcept -> void override;

  __CDS_NoDiscard __CDS_cpplang_VirtualConstexpr auto size () const noexcept -> Size override; // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-non-private-member-variables-in-classes)

  __CDS_NoDiscard auto toString () const noexcept(false) -> String override;

  using MutableCollectionBase::empty;
  using MutableCollectionBase::cbegin;
  using MutableCollectionBase::cend;

protected:
  using typename MutableCollectionBase::__GenericHandler;         // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  using typename MutableCollectionBase::__GenericConstHandler;    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

  using AbstractMapProxy::map;

  __CDS_MaybeUnused __CDS_Explicit constexpr AbstractValueMutableCollectionProxy (    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-non-private-member-variables-in-classes)
      Map <__KeyType, __ValueType>* pMap
  ) noexcept;

  static auto __newAddress ( // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      AbstractValueMutableCollectionProxy*  pObject,
      __ValueType const*                    pReferenceKey,
      bool*                                 pIsNew
  ) noexcept(false) -> __ValueType*;
};

} // namespace cds

#endif // __CDS_MAP_ABSTRACT_VALUE_MUTABLE_COLLECTION_PROXY_HPP__
