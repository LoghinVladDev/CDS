// NOLINT(llvm-header-guard)
// Created by loghin on 14/08/22.
//

#ifndef __CDS_MAP_ABSTRACT_KEY_SET_PROXY_HPP__ // NOLINT(llvm-header-guard)
#define __CDS_MAP_ABSTRACT_KEY_SET_PROXY_HPP__ // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
#pragma once

namespace cds {

template <typename __KeyType, typename __ValueType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs Map <__KeyType, __ValueType>::AbstractKeySetProxy :
    public cds::Set <__KeyType const>,
    protected Map <__KeyType, __ValueType>::AbstractMapProxy {
protected:
  using ProxyBase = Map <__KeyType, __ValueType>::AbstractMapProxy;
  using SetBase   = Set <__KeyType const>;

public:
  AbstractKeySetProxy (AbstractKeySetProxy const&) noexcept = delete;
  AbstractKeySetProxy (AbstractKeySetProxy&&) noexcept = delete;

  __CDS_cpplang_ConstexprDestructor ~AbstractKeySetProxy () noexcept override;

  auto operator = (AbstractKeySetProxy const&) noexcept -> AbstractKeySetProxy& = delete;
  auto operator = (AbstractKeySetProxy&&) noexcept -> AbstractKeySetProxy& = delete;

  auto clear () noexcept -> void override;
  auto remove (KeyType const& key) noexcept -> bool override;

  __CDS_NoDiscard __CDS_cpplang_VirtualConstexpr auto size () const noexcept -> Size override; // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-non-private-member-variables-in-classes)

protected:
  using typename SetBase::__GenericHandler;         // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  using typename SetBase::__GenericConstHandler;    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

  __CDS_MaybeUnused __CDS_Explicit constexpr AbstractKeySetProxy (    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-non-private-member-variables-in-classes)
      Map <__KeyType, __ValueType>* pMap
  ) noexcept;

  static auto __newAddress ( // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      AbstractKeySetProxy*  pObject,
      __KeyType const*      pReferenceKey,
      bool*                 pIsNew
  ) noexcept(false) -> __KeyType*;

  using AbstractMapProxy::map;
};

} // namespace cds

#endif // __CDS_MAP_ABSTRACT_KEY_SET_PROXY_HPP__
