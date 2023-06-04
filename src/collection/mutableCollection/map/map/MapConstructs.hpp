// NOLINT(llvm-header-guard)
// Created by loghin on 10/08/22.
//

#ifndef __CDS_MAP_CONSTRUCTS_HPP__ // NOLINT(llvm-header-guard)
#define __CDS_MAP_CONSTRUCTS_HPP__ // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
#pragma once

namespace cds {
template <typename __KeyType, typename __ValueType>    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class Map;

template <typename __KeyType, typename __ValueType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
constexpr auto mapEntryOf (
    __KeyType&&   key,
    __ValueType&& value
) noexcept (noexcept (MapEntry <__KeyType, __ValueType> (std::forward <__KeyType> (key), std::forward <__ValueType> (value)))) -> MapEntry <__KeyType, __ValueType> {
  return MapEntry <__KeyType, __ValueType> (std::forward <__KeyType> (key), std::forward <__ValueType> (value));
}

namespace meta {
template <typename __T>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
struct IsMapEntryCompatible                       : FalseType {};

template <typename __K, typename __V>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
struct IsMapEntryCompatible <Pair <__K, __V>>     : TrueType {};

template <typename __K, typename __V>    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
struct IsMapEntryCompatible <MapEntry <__K, __V>> : TrueType {};

template <typename __T, bool = IsMapEntryCompatible <__T>::value> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
struct MapEntryTraits {
  constexpr static bool const valid = false;
};

template <typename __K, typename __V> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
struct MapEntryTraits <MapEntry <__K, __V>, true> {
  constexpr static bool const valid = true;
  using KeyType   = RemoveConst <RemoveReference <decltype (valueOf <MapEntry <__K, __V>>().key())>>;
  using ValueType = RemoveReference <decltype (valueOf <MapEntry <__K, __V>>().value())>;
};

template <typename __K, typename __V> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
struct MapEntryTraits <Pair <__K, __V>, true> {
  constexpr static bool const valid = true;
  using KeyType   = RemoveReference <decltype (valueOf <Pair <__K, __V>>().first())>;
  using ValueType = RemoveReference <decltype (valueOf <Pair <__K, __V>>().second())>;
};
} // namespace meta

namespace __hidden {  // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
namespace __impl {    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

template <typename __KeyType, typename __ValueType>       // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __MapFindUniqueImmutableClient : // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __FindUniqueImmutablePrimitiveClient <
        cds::Map <__KeyType, __ValueType>, MapEntry <__KeyType, __ValueType>, __KeyType, false
    > {};

template <typename __KeyType, typename __ValueType>     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __MapFindUniqueMutableClient : // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __FindUniqueMutablePrimitiveClient <
        cds::Map <__KeyType, __ValueType>, MapEntry <__KeyType, __ValueType>, __KeyType, false
    > {};

} // namespace __impl
} // namespace __hidden
} // namespace cds

#endif // __CDS_MAP_CONSTRUCTS_HPP__
