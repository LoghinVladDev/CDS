//
// Created by loghin on 6/30/22.
//

#ifndef __CDS_SHARED_INDICES_BY_COMPOSITE_CLIENT_IMPL_HPP__ // NOLINT(llvm-header-guard) 
#define __CDS_SHARED_INDICES_BY_COMPOSITE_CLIENT_IMPL_HPP__ // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
#pragma once

namespace cds {       // NOLINT(modernize-concat-nested-namespaces)
namespace __hidden {  // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
namespace __impl {    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename __Receiver, typename __Element, bool __exceptCond> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename __Collection, typename __Predicate>                // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
auto __IndicesByCompositeClient <__Receiver, __Element, __exceptCond>::indicesOfThat (
    Size                count,
    __Collection&       storeIn,
    __Predicate const&  predicate
) const noexcept (false) -> __Collection& {
  Index   index       = 0;
  Size    foundCount  = 0u;
  auto const* pIterable = static_cast <__Receiver const*> (this);
  for (auto iterator = pIterable->cbegin(), end = pIterable->cend (); iterator != end && foundCount < count; ++iterator, ++index) {
    if (predicate (*iterator)) {
      (void) storeIn.insert (index);
      ++foundCount;
    }
  }

  return storeIn;
}


template <typename __Receiver, typename __Element, bool __exceptCond> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <template <typename...> class __Collection, typename __Predicate> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
__CDS_OptimalInline auto __IndicesByCompositeClient <__Receiver, __Element, __exceptCond>::indicesOfThat (
    Size                count,
    __Predicate const&  predicate
) const noexcept (false) -> __Collection <Index> {
  __Collection <Index> indices;
  return std::move (indicesOfThat (count, indices, predicate));
}


template <typename __Receiver, typename __Element, bool __exceptCond> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename __Predicate> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
auto __IndicesByCompositeClient <__Receiver, __Element, __exceptCond>::firstIndexOfThat (
    __Predicate const& predicate
) const noexcept (noexcept (predicate (cds::meta::referenceOf <ElementType const>())) && itNoexcept) -> Index {
  auto const* pIterable = static_cast <__Receiver const*> (this);
  Index index = 0;
  for (auto iterator = pIterable->cbegin(), end = pIterable->cend(); iterator != end; ++iterator, ++index) {
    if (predicate (*iterator)) {
      return index;
    }
  }

  return __Receiver::invalidIndex;
}


template <typename __Receiver, typename __Element, bool __exceptCond> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename __Predicate> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
auto __IndicesByCompositeClient <__Receiver, __Element, __exceptCond>::lastIndexOfThat (
    __Predicate const& predicate
) const noexcept (noexcept (predicate (cds::meta::referenceOf <ElementType const>())) && itNoexcept) -> Index {
  auto const* pIterable = static_cast <__Receiver const*> (this);
  Index index = static_cast <Index> (pIterable->size()) - 1;
  for (auto iterator = pIterable->crbegin(), end = pIterable->crend(); iterator != end; ++iterator, --index) {
    if (predicate (*iterator)) {
      return index;
    }
  }

  return __Receiver::invalidIndex;
}


template <typename __Receiver, typename __Element, bool __exceptCond> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename __Collection, typename __Predicate>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
auto __IndicesByCompositeClient <__Receiver, __Element, __exceptCond>::allIndicesOfThat (
    __Collection&       storeIn,
    __Predicate const&  predicate
) const noexcept (false) -> __Collection& {
  Index index = 0;
  auto const* pIterable = static_cast <__Receiver const*> (this);
  for (auto iterator = pIterable->cbegin(), end = pIterable->cend(); iterator != end; ++iterator, ++index) {
    if (predicate (*iterator)) {
      (void) storeIn.insert (index);
    }
  }

  return storeIn;
}


template <typename __Receiver, typename __Element, bool __exceptCond> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <template <typename...> class __Collection, typename __Predicate>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto __IndicesByCompositeClient <__Receiver, __Element, __exceptCond>::allIndicesOfThat (
    __Predicate const& predicate
) const noexcept (false) -> __Collection <Index> {
  __Collection <Index> indices;
  return std::move (allIndicesOfThat (indices, predicate));
}
} // namespace __impl 
} // namespace __hidden 
} // namespace cds 

#endif // __CDS_SHARED_INDICES_BY_COMPOSITE_CLIENT_IMPL_HPP__ 
