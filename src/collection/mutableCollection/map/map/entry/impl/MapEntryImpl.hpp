// NOLINT(llvm-header-guard)
// Created by loghin on 6/16/22.
//

#ifndef __CDS_MAP_ENTRY_IMPL_HPP__ // NOLINT(llvm-header-guard)
#define __CDS_MAP_ENTRY_IMPL_HPP__ // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
#pragma once

namespace cds {
template <typename __KeyType, typename __ValueType>   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_ConstexprConditioned auto MapEntry <__KeyType, __ValueType>::operator == (
    MapEntry const& entry
) const noexcept -> bool {
  if (this == &entry) {
    return true;
  }

  return cds::meta::equals (this->_key, entry._key) && cds::meta::equals (this->_value, entry._value);
}

template <typename __KeyType, typename __ValueType>   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_ConstexprConditioned auto MapEntry <__KeyType, __ValueType>::operator != (
    MapEntry const &entry
) const noexcept -> bool {
  if (this == & entry) {
    return false;
  }

  return !cds::meta::equals (this->_key, entry._key) || !cds::meta::equals (this->_value, entry._value);
}


template <typename __KeyType, typename __ValueType>   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
constexpr auto MapEntry <__KeyType, __ValueType>::hash () const noexcept -> Size {
  return cds::hash (this->_key) ^ cds::hash (this->_value);
}


template <typename __KeyType, typename __ValueType>   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto MapEntry <__KeyType, __ValueType>::toString () const noexcept(false) -> String {
  std::stringstream oss;
  cds::meta::print (cds::meta::print (oss << "( ", this->_key) << ", ", this->_value) << " )";
  return oss.str();
}


template <typename __KeyType, typename __ValueType>   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline MapEntry <__KeyType, __ValueType>::operator String () const noexcept(false) {
  return this->toString();
}


template <typename __KeyType, typename __ValueType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
constexpr MapEntry <__KeyType, __ValueType>::MapEntry (
    MapEntry const& entry
) noexcept (noexcept (__KeyType (entry._key)) && noexcept (__ValueType (entry._value))) :
    _key (entry._key),
    _value (entry._value) {

}


template <typename __KeyType, typename __ValueType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <
    typename __DecayedKeyType,                      // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    cds::meta::EnableIf <!cds::meta::IsSame <__DecayedKeyType, __KeyType>::value>
> constexpr MapEntry <__KeyType, __ValueType>::MapEntry (
    MapEntry <__DecayedKeyType, __ValueType> const& entry
) noexcept (noexcept (__KeyType (entry.key())) && noexcept (__ValueType (entry.value()))) :
    _key (entry.key()),
    _value (entry.value()) {

}


template <typename __KeyType, typename __ValueType>   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename __TKeyType, typename __TValueType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
constexpr MapEntry <__KeyType, __ValueType>::MapEntry (
    cds::Pair <__TKeyType, __TValueType> const& pair
) noexcept (noexcept (__KeyType (pair.first())) && noexcept (__ValueType (pair.second()))) :
    _key (pair.first()),
    _value (pair.second()) {

}


template <typename __KeyType, typename __ValueType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
constexpr MapEntry <__KeyType, __ValueType>::MapEntry (
    MapEntry&& entry
) noexcept (noexcept (__KeyType (std::move (entry._key))) && noexcept (__ValueType (std::move (entry._value)))) :
    _key (std::move (entry._key)),
    _value (std::move (entry._value)) {

}


template <typename __KeyType, typename __ValueType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <
    typename __DecayedKeyType,                      // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    cds::meta::EnableIf <!cds::meta::IsSame <__DecayedKeyType, __KeyType>::value>
> constexpr MapEntry <__KeyType, __ValueType>::MapEntry (
    MapEntry <__DecayedKeyType, __ValueType>&& entry
) noexcept (noexcept (__KeyType (std::move (entry._key))) && noexcept (__ValueType (std::move (entry._value)))) :
    _key (std::move (entry._key)),
    _value (std::move (entry._value)) {

}


template <typename __KeyType, typename __ValueType>   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename __TKeyType, typename __TValueType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
constexpr MapEntry <__KeyType, __ValueType>::MapEntry (
    cds::Pair <__TKeyType, __TValueType>&& pair
) noexcept (noexcept (__KeyType (std::move (pair._first))) && noexcept (__ValueType (std::move (pair._second)))) :
    _key (std::move (pair._first)),
    _value (std::move (pair._second)) {

}


template <typename __KeyType, typename __ValueType>   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_NonConstConstexprMemberFunction auto MapEntry <__KeyType, __ValueType>::operator = (
    MapEntry const& entry
) noexcept (noexcept (cds::meta::referenceOf <__ValueType> () = entry._value)) -> MapEntry& {
  if (this == &entry) {
    return *this;
  }

  this->_value = entry._value;
  return *this;
}


template <typename __KeyType, typename __ValueType>   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_NonConstConstexprMemberFunction auto MapEntry <__KeyType, __ValueType>::operator = (
    MapEntry&& entry
) noexcept (noexcept ( cds::meta::referenceOf <__ValueType> () = std::move (entry._value))) -> MapEntry & {
  if (this == &entry) {
    return *this;
  }

  this->_value = std::move (entry._value);
  return *this;
}


template <typename __KeyType, typename __ValueType>   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename __TKeyType, typename __TValueType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
constexpr MapEntry <__KeyType, __ValueType>::MapEntry (
    __TKeyType&&    key,
    __TValueType&&  value
) noexcept (noexcept (__KeyType (std::forward <__TKeyType> (key))) && noexcept (__ValueType (std::forward <__TValueType> (value)))) :
    _key (std::forward <__TKeyType> (key)),
    _value (std::forward <__TValueType> (value)) {

}


template <typename __KeyType, typename __ValueType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
constexpr auto MapEntry <__KeyType, __ValueType>::key () const noexcept -> KeyType const& {
  return this->_key;
}


template <typename __KeyType, typename __ValueType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
constexpr auto MapEntry <__KeyType, __ValueType>::value () const noexcept -> ValueType const& {
  return this->_value;
}


template <typename __KeyType, typename __ValueType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_NonConstConstexprMemberFunction auto MapEntry <__KeyType, __ValueType>::value () noexcept -> ValueType& {
  return this->_value;
}


template <typename __KeyType, typename __ValueType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
constexpr auto MapEntry <__KeyType, __ValueType>::first () const noexcept -> KeyType const& {
  return this->key();
}


template <typename __KeyType, typename __ValueType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
constexpr auto MapEntry <__KeyType, __ValueType>::second () const noexcept -> ValueType const& {
  return this->value();
}


template <typename __KeyType, typename __ValueType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_NonConstConstexprMemberFunction auto MapEntry <__KeyType, __ValueType>::second () noexcept -> ValueType& {
  return this->value();
}


template <typename __KeyType, typename __ValueType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
constexpr auto MapEntry <__KeyType, __ValueType>::getFirst () const noexcept -> KeyType const& {
  return this->key();
}


template <typename __KeyType, typename __ValueType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
constexpr auto MapEntry <__KeyType, __ValueType>::getSecond () const noexcept -> ValueType const& {
  return this->value();
}


template <typename __KeyType, typename __ValueType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_NonConstConstexprMemberFunction auto MapEntry <__KeyType, __ValueType>::getSecond () noexcept -> ValueType& {
  return this->value();
}


template <typename __TKeyType, typename __TValueType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto operator << (
    std::ostream&                               out,
    MapEntry <__TKeyType, __TValueType> const&  object
) noexcept -> std::ostream& {
  return cds::meta::print (cds::meta::print (out << "( ", object.key()) << ", ", object.value()) << " )";
}

template <typename __KeyType,typename __ValueType>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
struct Hash <MapEntry <__KeyType, __ValueType>> {
  __CDS_NoDiscard constexpr static auto hash (MapEntry <__KeyType, __ValueType> const& entry) noexcept -> Size {
    return entry.hash();
  }
};

} // namespace cds

#include "MapEntryCTAD.hpp"

#endif // __CDS_MAP_ENTRY_IMPL_HPP__
