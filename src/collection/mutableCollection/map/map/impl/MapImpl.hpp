// NOLINT(llvm-header-guard)
// Created by loghin on 10/08/22.
//

#ifndef __CDS_MAP_IMPL_HPP__ // NOLINT(llvm-header-guard)
#define __CDS_MAP_IMPL_HPP__ // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
#pragma once

namespace cds {
template <typename __KeyType, typename __ValueType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
constexpr Map <__KeyType, __ValueType>::Map () noexcept = default;


template <typename __KeyType, typename __ValueType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
constexpr Map <__KeyType, __ValueType>::Map (Map const& map) noexcept :
    MutableCollectionBase (map) {

}


template <typename __KeyType, typename __ValueType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
constexpr Map <__KeyType, __ValueType>::Map (Map&& map) noexcept :
    MutableCollectionBase (std::move (map)) {

}


template <typename __KeyType, typename __ValueType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_ConstexprDestructor Map <__KeyType, __ValueType>::~Map () noexcept = default;


template <typename __KeyType, typename __ValueType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
auto Map <__KeyType, __ValueType>::toString () const noexcept(false) -> String {
  if (empty()) {
    return "{}";
  }

  std::stringstream oss;
  oss << "{ ";
  for (auto iterator = cbegin(), end = cend(); iterator != end; ++iterator) { // NOLINT(clion-misra-cpp2008-8-0-1)
    meta::print (meta::print (oss, (*iterator).key()) << ": ", (* iterator).value()) << ", ";
  }

  auto asString = oss.str();
  asString [asString.length() - 2u] = ' ';
  asString [asString.length() - 1u] = '}';
  return asString;
}


template <typename __KeyType, typename __ValueType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_ConstexprOverride auto Map <__KeyType, __ValueType>::contains (
    EntryType const& entry
) const noexcept -> bool {
  return containsKey (entry.key());
}


template <typename __KeyType, typename __ValueType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <
    typename __TKeyType, typename __TValueType,     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    cds::meta::EnableIf <cds::meta::IsDefaultConstructible <__TValueType>::value>
> __CDS_OptimalInline auto Map <__KeyType, __ValueType>::get (__TKeyType&& key) noexcept -> ValueType& {
  bool isNew; // NOLINT(cppcoreguidelines-init-variables)
  auto pEntry = entryAt (key, &isNew);

  if (isNew) {
    new (pEntry) EntryType (cds::forward <__TKeyType> (key), ValueType());
  }
  return pEntry->value();
}


template <typename __KeyType, typename __ValueType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto Map <__KeyType, __ValueType>::at (KeyType const& key) noexcept(false) -> ValueType& {
  auto pEntry = const_cast <EntryType*> (entryAt (key)); // NOLINT(*-const-cast)
  if (pEntry == nullptr) {
    throw KeyException (key);
  }

  return pEntry->value();
}


template <typename __KeyType, typename __ValueType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto Map <__KeyType, __ValueType>::at (KeyType const& key) const noexcept (false) -> ValueType const& {
  auto pEntry = entryAt (key);
  if (pEntry == nullptr) {
    throw KeyException (key);
  }

  return pEntry->value();
}


template <typename __KeyType, typename __ValueType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <
    typename __TKeyType, typename __TValueType,  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    cds::meta::EnableIf <cds::meta::IsDefaultConstructible <__TValueType>::value>
> __CDS_OptimalInline auto Map <__KeyType, __ValueType>::operator [] (
    __TKeyType&& key
) noexcept -> ValueType& {
  return get (key);
}


template <typename __KeyType, typename __ValueType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto Map <__KeyType, __ValueType>::operator [] (
    KeyType const& key
) const noexcept(false) -> ValueType const& {
  return at (key);
}

} // namespace cds

#endif // __CDS_MAP_IMPL_HPP__
