// NOLINT(llvm-header-guard)
// Created by loghin on 14/08/22.
//

#ifndef __CDS_MAP_ABSTRACT_MAP_PROXY_HPP__ // NOLINT(llvm-header-guard)
#define __CDS_MAP_ABSTRACT_MAP_PROXY_HPP__ // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
#pragma once

namespace cds {
template <typename __KeyType, typename __ValueType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs Map <__KeyType, __ValueType>::AbstractMapProxy {
public:
  ~AbstractMapProxy () noexcept = default;

  auto operator = (AbstractMapProxy const&) noexcept -> AbstractMapProxy& = delete;
  auto operator = (AbstractMapProxy&&) noexcept -> AbstractMapProxy& = delete;

protected:
  __CDS_MaybeUnused __CDS_Explicit constexpr AbstractMapProxy ( // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-non-private-member-variables-in-classes)
      Map <__KeyType, __ValueType>* pMap
  ) noexcept;

  constexpr AbstractMapProxy (AbstractMapProxy const &proxy) noexcept;
  constexpr AbstractMapProxy (AbstractMapProxy&& proxy) noexcept;

  template <typename __DerivedType = Map <__KeyType, __ValueType>> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  __CDS_NoDiscard auto map() noexcept -> __DerivedType*;

  template <typename __DerivedType = Map <__KeyType, __ValueType>> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  __CDS_NoDiscard auto map() const noexcept -> __DerivedType const*;

private:
  Map <__KeyType, __ValueType>* _pMap;
};
} // namespace cds

#endif // __CDS_MAP_ABSTRACT_MAP_PROXY_HPP__
