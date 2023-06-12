// NOLINT(llvm-header-guard)
// Created by loghin on 15.01.2021.
//

#ifndef __CDS_MAP_HPP__ // NOLINT(llvm-header-guard)
#define __CDS_MAP_HPP__ // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
#pragma once

#include <CDS/MutableCollection>
#include <CDS/Set>
#include <CDS/exception/KeyException>
#include <CDS/exception/UnsupportedOperationException>

#include "../../../shared/iterableInternalCommunication/client/primitive/FindUniqueMutablePrimitiveClient.hpp"    // NOLINT(llvm-include-order)
#include "../../../shared/iterableInternalCommunication/client/primitive/FindUniqueImmutablePrimitiveClient.hpp"
#include "../../../shared/iterableInternalCommunication/server/MutableCollectionServer.hpp"

#include "map/entry/MapEntry.hpp"

#include "map/MapConstructs.hpp"

namespace cds {
template <typename __KeyType, typename __ValueType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs Map :                      // NOLINT(*-virtual-class-destructor)
    public MutableCollection <MapEntry <__KeyType, __ValueType>>,
    public __hidden::__impl::__MapFindUniqueImmutableClient <__KeyType, __ValueType>,
    public __hidden::__impl::__MapFindUniqueMutableClient <__KeyType, __ValueType> {
protected:
  using MutableCollectionBase     = MutableCollection <MapEntry <__KeyType, __ValueType>>;
  using FindUniqueImmutableClient = __hidden::__impl::__MapFindUniqueImmutableClient <__KeyType, __ValueType>;
  using FindUniqueMutableClient   = __hidden::__impl::__MapFindUniqueMutableClient <__KeyType, __ValueType>;

  using typename MutableCollectionBase::__GenericHandler;       // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  using typename MutableCollectionBase::__GenericConstHandler;  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

public:
  using typename MutableCollectionBase::ElementType;
  
  using MutableCollectionBase::remove;

  using EntryType = ElementType;
  using KeyType   = __KeyType;
  using ValueType = __ValueType;

  __CDS_NoDiscard virtual __CDS_cpplang_ConstexprPureAbstract auto keys () const noexcept -> Set <KeyType const> const& = 0;
  __CDS_NoDiscard virtual __CDS_cpplang_ConstexprPureAbstract auto keys () noexcept -> Set <KeyType const>& = 0;
  __CDS_NoDiscard virtual __CDS_cpplang_ConstexprPureAbstract auto values () const noexcept -> MutableCollection <ValueType> const& = 0;
  __CDS_NoDiscard virtual __CDS_cpplang_ConstexprPureAbstract auto values () noexcept -> MutableCollection <ValueType>& = 0;
  __CDS_NoDiscard virtual __CDS_cpplang_ConstexprPureAbstract auto entries () const noexcept -> MutableCollection <EntryType> const& = 0;
  __CDS_NoDiscard virtual __CDS_cpplang_ConstexprPureAbstract auto entries () noexcept -> MutableCollection <EntryType>& = 0;

  constexpr Map () noexcept;
  constexpr Map (Map const& map) noexcept;
  constexpr Map (Map&& map) noexcept;
  __CDS_cpplang_ConstexprDestructor ~Map () noexcept override;

  auto operator = (Map const&) noexcept -> Map& = delete;
  auto operator = (Map&&) noexcept -> Map& = delete;

  using FindUniqueImmutableClient::find;
  using FindUniqueMutableClient::find;

  __CDS_NoDiscard auto toString () const noexcept(false) -> String override;

  auto clear () noexcept -> void override = 0;

  virtual auto remove (__KeyType const& key) noexcept -> bool = 0;

  __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto contains (
      EntryType const& entry
  ) const noexcept -> bool override;

  __CDS_NoDiscard __CDS_cpplang_VirtualConstexpr virtual auto containsKey (
      __KeyType const& key
  ) const noexcept -> bool = 0;

  __CDS_NoDiscard __CDS_MaybeUnused __CDS_cpplang_VirtualConstexpr virtual auto containsValue (
      __ValueType const& value
  ) const noexcept -> bool = 0;

  template <
      typename __TKeyType, typename __TValueType = ValueType,  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      cds::meta::EnableIf <cds::meta::IsDefaultConstructible <__TValueType>::value> = 0
  > auto get (__TKeyType&& key) noexcept -> ValueType&;

  auto at (KeyType const& key) noexcept(false) -> ValueType&;
  auto at (KeyType const& key) const noexcept(false) -> ValueType const&;

  template <
      typename __TKeyType, typename __TValueType = ValueType,  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      cds::meta::EnableIf <cds::meta::IsDefaultConstructible <__TValueType>::value> = 0
  > auto operator [] (__TKeyType&& key) noexcept -> ValueType&;

  auto operator [] (KeyType const& key) const noexcept(false) -> ValueType const&;

  using MutableCollectionBase::empty;
  using MutableCollectionBase::cbegin;
  using MutableCollectionBase::cend;

protected:
  class AbstractMapProxy;
  class AbstractKeySetProxy;
  class AbstractValueMutableCollectionProxy;
  class AbstractEntryMutableCollectionProxy;

  virtual auto entryAt (
      __KeyType const&  key,
      bool*             pNewElementCreated
  ) noexcept -> EntryType* = 0;

  virtual auto entryAt (
      __KeyType const& key
  ) const noexcept -> EntryType const* = 0;
};

} // namespace cds

#include "map/MapAbstractMapProxy.hpp"                                                                                         // NOLINT(llvm-include-order)
#include "map/MapAbstractKeySetProxy.hpp"
#include "map/MapAbstractValueMutableCollectionProxy.hpp"
#include "map/MapAbstractEntryMutableCollectionProxy.hpp"

#include "../../../shared/iterableInternalCommunication/client/primitive/impl/FindUniqueMutablePrimitiveClientImpl.hpp"       // NOLINT(llvm-include-order)
#include "../../../shared/iterableInternalCommunication/client/primitive/impl/FindUniqueImmutablePrimitiveClientImpl.hpp"
#include "../../../shared/iterableInternalCommunication/server/impl/MutableCollectionServerImpl.hpp"

#include "map/entry/impl/MapEntryImpl.hpp"

#include "map/impl/MapImpl.hpp"                                                                                                 // NOLINT(llvm-include-order)
#include "map/impl/MapAbstractMapProxyImpl.hpp"
#include "map/impl/MapAbstractKeySetProxyImpl.hpp"
#include "map/impl/MapAbstractValueMutableCollectionProxyImpl.hpp"
#include "map/impl/MapAbstractEntryMutableCollectionProxyImpl.hpp"

#endif // __CDS_MAP_HPP__
