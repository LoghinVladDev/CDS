//
// Created by loghin on 6/27/22.
//

#ifndef __CDS_SHARED_FIND_BY_MUTABLE_COMPOSITE_CLIENT_IMPL_HPP__ // NOLINT(llvm-header-guard)
#define __CDS_SHARED_FIND_BY_MUTABLE_COMPOSITE_CLIENT_IMPL_HPP__ // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
#pragma once

#ifdef _MSC_VER
#include "../FindByImmutableCompositeClient.hpp"
#include "FindByImmutableCompositeClient.hpp"
#endif

namespace cds {       // NOLINT(modernize-concat-nested-namespaces)
namespace __hidden {  // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
namespace __impl {    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename __Iterable, typename __Element, typename __Iterator, bool __exceptCond>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <template <typename...> class __Collection, typename __Predicate>              // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto __FindByMutableCompositeClient <__Iterable, __Element, __Iterator, __exceptCond>::findThat (
    Size                      count,
    __Collection <Iterator>&  storeIn,
    __Predicate const&        predicate
) noexcept (false) -> __Collection <Iterator>& {
  auto* pIterable = static_cast <__Iterable*> (this);
  // Call base, global implementation. Abstracts the 'is object const' requirement
#ifdef _MSC_VER
  // Usable in Mutable Client, no implementation would reasonably include the mutable client before
  // or without the immutable one beforehand. (Design Based)
  return __MSVC_FindThatWrapper <__Iterator, __Collection, __Predicate>::__findThat (
      pIterable->begin(), pIterable->end(), count, storeIn, predicate
  );
#else
  return __findThat (pIterable->begin(), pIterable->end(), count, storeIn, predicate);
#endif
}


template <typename __Iterable, typename __Element, typename __Iterator, bool __exceptCond>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <template <typename...> class __Collection, typename __Predicate>              // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto __FindByMutableCompositeClient <__Iterable, __Element, __Iterator, __exceptCond>::findThat (
    Size                count,
    __Predicate const&  predicate
) noexcept(false) -> __Collection <Iterator> {
  __Collection <Iterator> foundIterators;
  auto* pIterable = static_cast <__Iterable*> (this);
  // Call base, global implementation. Abstracts the 'is object const' requirement
#ifdef _MSC_VER
  // Usable in Mutable Client, no implementation would reasonably include the mutable client before
  // or without the immutable one beforehand. (Design Based)
  return __MSVC_FindThatWrapper <__Iterator, __Collection, __Predicate>::__findThat (
      pIterable->begin(), pIterable->end(), count, foundIterators, predicate
  );
#else
  return __findThat (pIterable->begin(), pIterable->end(), count, foundIterators, predicate);
#endif
}


template <typename __Iterable, typename __Element, typename __Iterator, bool __exceptCond>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename __Predicate> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto __FindByMutableCompositeClient <__Iterable, __Element, __Iterator, __exceptCond>::findFirstThat (
    __Predicate const& predicate
) noexcept (noexcept (__PredicateExceptSpecTraits <__Element, __Predicate>::__noexceptSpec) && itNoexcept) -> Iterator {
  auto* pIterable = static_cast <__Iterable*> (this);
  // Call base, global implementation. Abstracts the 'is object const' requirement
#ifdef _MSC_VER
  // Usable in Mutable Client, no implementation would reasonably include the mutable client before
  // or without the immutable one beforehand. (Design Based)
  return __MSVC_FindFirstThatWrapper <__Iterator, __Predicate>::__findFirstThat (
      pIterable->begin(), pIterable->end(), predicate
  );
#else
  return __findFirstThat (pIterable->begin(), pIterable->end(), predicate);
#endif
}


template <typename __Iterable, typename __Element, typename __Iterator, bool __exceptCond>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename __Predicate> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto __FindByMutableCompositeClient <__Iterable, __Element, __Iterator, __exceptCond>::findLastThat (
    __Predicate const& predicate
) noexcept (noexcept (__PredicateExceptSpecTraits <__Element, __Predicate>::__noexceptSpec) && itNoexcept) -> Iterator {
  auto* pIterable = static_cast <__Iterable*> (this);
  // Call base, global implementation. Abstracts the 'is object const' requirement
#ifdef _MSC_VER
  // Usable in Mutable Client, no implementation would reasonably include the mutable client before
  // or without the immutable one beforehand. (Design Based)
  return __MSVC_FindLastThatWrapper <__Iterator, __Predicate>::__findLastThat (
      pIterable->begin(), pIterable->end(), predicate
  );
#else
  return __findLastThat (pIterable->begin(), pIterable->end(), predicate);
#endif
}


template <typename __Iterable, typename __Element, typename __Iterator, bool __exceptCond>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <template <typename...> class __Collection, typename __Predicate>              // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto __FindByMutableCompositeClient <__Iterable, __Element, __Iterator, __exceptCond>::findAllThat (
    __Collection <Iterator>&  storeIn,
    __Predicate const&        predicate
) noexcept (false) -> __Collection <Iterator>& {
  auto* pIterable = static_cast <__Iterable*> (this);
  // Call base, global implementation. Abstracts the 'is object const' requirement
#ifdef _MSC_VER
  // Usable in Mutable Client, no implementation would reasonably include the mutable client before
  // or without the immutable one beforehand. (Design Based)
  return __MSVC_FindAllThatWrapper <__Iterator, __Collection, __Predicate>::__findAllThat (
      pIterable->begin(), pIterable->end(), storeIn, predicate
  );
#else
  return __findAllThat (pIterable->begin(), pIterable->end(), storeIn, predicate);
#endif
}


template <typename __Iterable, typename __Element, typename __Iterator, bool __exceptCond>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <template <typename...> class __Collection, typename __Predicate>              // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto __FindByMutableCompositeClient <__Iterable, __Element, __Iterator, __exceptCond>::findAllThat (
    __Predicate const& predicate
) noexcept(false) -> __Collection <Iterator> {
  auto* pIterable = static_cast <__Iterable*> (this);
  // Call base, global implementation. Abstracts the 'is object const' requirement
  __Collection <Iterator> foundIterators;
#ifdef _MSC_VER
  // Usable in Mutable Client, no implementation would reasonably include the mutable client before
  // or without the immutable one beforehand. (Design Based)
  return __MSVC_FindAllThatWrapper <__Iterator, __Collection, __Predicate>::__findAllThat (
      pIterable->begin(), pIterable->end(), foundIterators, predicate
  );
#else
  // Call base, global implementation. Abstracts the 'is object const' requirement
  return __findAllThat (pIterable->begin(), pIterable->end(), foundIterators, predicate);
#endif
}
} // namespace __impl
} // namespace __hidden
} // namespace cds

#endif // __CDS_SHARED_FIND_BY_MUTABLE_COMPOSITE_CLIENT_IMPL_HPP__
