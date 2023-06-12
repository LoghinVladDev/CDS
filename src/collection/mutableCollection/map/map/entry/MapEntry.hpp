// NOLINT(llvm-header-guard)
// Created by loghin on 6/15/22.
//

#ifndef __CDS_MAP_ENTRY_HPP__ // NOLINT(llvm-header-guard)
#define __CDS_MAP_ENTRY_HPP__ // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
#pragma once

namespace cds {
template <typename __KeyType, typename __ValueType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class MapEntry {
public:
  using KeyType   = __KeyType;
  using ValueType = __ValueType;

  constexpr MapEntry () noexcept = delete;
  constexpr MapEntry (MapEntry const& entry) noexcept (noexcept (__KeyType (entry._key)) && noexcept (__ValueType (entry._value)));

  template <
      typename __DecayedKeyType = cds::meta::Decay <__KeyType>, // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      cds::meta::EnableIf <!cds::meta::IsSame <__DecayedKeyType, __KeyType>::value> = 0
  > constexpr MapEntry (    // NOLINT(*-explicit-*)
      MapEntry <__DecayedKeyType, __ValueType> const& entry
  ) noexcept (noexcept (__KeyType (entry.key())) && noexcept (__ValueType (entry.value())));

  template <typename __TKeyType, typename __TValueType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  __CDS_Implicit constexpr MapEntry ( // NOLINT(*-explicit-*)
      cds::Pair <__TKeyType, __TValueType> const& pair
  ) noexcept (noexcept (__KeyType (pair.first())) && noexcept (__ValueType (pair.second())));

  constexpr MapEntry (MapEntry&& entry) noexcept (noexcept (__KeyType (std::move (entry._key))) && noexcept (__ValueType (std::move (entry._value))));

  template <
      typename __DecayedKeyType = cds::meta::Decay <__KeyType>, // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      cds::meta::EnableIf <!cds::meta::IsSame <__DecayedKeyType, __KeyType>::value> = 0
  > constexpr MapEntry (  // NOLINT(*-explicit-*)
      MapEntry <__DecayedKeyType, __ValueType>&& entry
  ) noexcept (noexcept (__KeyType (std::move (entry._key))) && noexcept (__ValueType (std::move (entry._value))));

  template <typename __TKeyType, typename __TValueType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  __CDS_Implicit constexpr MapEntry ( // NOLINT(*-explicit-*)
      cds::Pair <__TKeyType, __TValueType>&& pair
  ) noexcept (noexcept (__KeyType (std::move (pair._first))) && noexcept (__ValueType (std::move (pair._second))));

  ~MapEntry () noexcept = default;

  __CDS_cpplang_NonConstConstexprMemberFunction auto operator = ( // NOLINT(cppcoreguidelines-c-copy-assignment-signature, misc-unconventional-assign-operator)
      MapEntry const& entry
  ) noexcept (noexcept (cds::meta::referenceOf <__ValueType> () = entry._value)) -> MapEntry&;

  __CDS_cpplang_NonConstConstexprMemberFunction auto operator = ( // NOLINT(cppcoreguidelines-c-copy-assignment-signature, misc-unconventional-assign-operator)
      MapEntry&& entry
  ) noexcept (noexcept (cds::meta::referenceOf <__ValueType> () = std::move (entry._value))) -> MapEntry&;

  template <typename __TKeyType, typename __TValueType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  constexpr MapEntry (
      __TKeyType&&    key,
      __TValueType&&  value
  ) noexcept (noexcept (__KeyType (std::forward <__TKeyType> (key))) && noexcept (__ValueType (std::forward <__TValueType> (value))));

  __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto operator == ( // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-non-private-member-variables-in-classes)
      MapEntry const& entry
  ) const noexcept -> bool;

  __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto operator != ( // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-non-private-member-variables-in-classes)
      MapEntry const& entry
  ) const noexcept -> bool;

  __CDS_NoDiscard constexpr auto hash () const noexcept -> Size;
  __CDS_NoDiscard constexpr auto key () const noexcept -> KeyType const&;
  __CDS_NoDiscard constexpr auto value () const noexcept -> ValueType const&;
  __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction auto value () noexcept -> ValueType&;    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-non-private-member-variables-in-classes)

  __CDS_DeprecatedHint("'MapEntry::first' is deprecated. Use 'MapEntry::key' instead")
  __CDS_NoDiscard constexpr auto first () const noexcept -> KeyType const&; // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-non-private-member-variables-in-classes)

  __CDS_DeprecatedHint("'MapEntry::second' is deprecated. Use 'MapEntry::value' instead")
  __CDS_Deprecated __CDS_NoDiscard constexpr auto second () const noexcept -> ValueType const&;

  __CDS_DeprecatedHint("'MapEntry::second' is deprecated. Use 'MapEntry::value' instead")
  __CDS_Deprecated __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction auto second () noexcept -> ValueType&;

  __CDS_DeprecatedHint("'MapEntry::getFirst' is deprecated. Use 'MapEntry::key' instead")
  __CDS_Deprecated __CDS_NoDiscard constexpr auto getFirst () const noexcept -> KeyType const&;

  __CDS_DeprecatedHint("'MapEntry::getSecond' is deprecated. Use 'MapEntry::value' instead")
  __CDS_Deprecated __CDS_NoDiscard constexpr auto getSecond () const noexcept -> ValueType const&;

  __CDS_DeprecatedHint("'MapEntry::getSecond' is deprecated. Use 'MapEntry::value' instead")
  __CDS_Deprecated __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction auto getSecond () noexcept -> ValueType&;

  __CDS_NoDiscard auto toString () const noexcept(false) -> String;
  __CDS_NoDiscard __CDS_Implicit operator String () const noexcept(false);   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-non-private-member-variables-in-classes, *-explicit-*)

  template <typename __TKeyType, typename __TValueType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  friend auto operator << (
      std::ostream&                               out,
      MapEntry <__TKeyType, __TValueType> const&  object
  ) noexcept -> std::ostream&;
  
private:
  template <typename, typename> friend class cds::MapEntry;

  __KeyType   _key;
  __ValueType _value;
};

} // namespace cds

#endif // __CDS_MAP_ENTRY_HPP__
