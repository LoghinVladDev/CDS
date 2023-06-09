//
// Created by loghin on 6/30/22.
//

#ifndef __CDS_SHARED_INDICES_COMPOSITE_CLIENT_IMPL_HPP__ // NOLINT(llvm-header-guard) 
#define __CDS_SHARED_INDICES_COMPOSITE_CLIENT_IMPL_HPP__ // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
#pragma once

namespace cds {       // NOLINT(modernize-concat-nested-namespaces) 
namespace __hidden {  // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
namespace __impl {    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename __Receiver, typename __Element, bool __exceptCond>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename __Collection>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
auto __IndicesCompositeClient <__Receiver, __Element, __exceptCond>::indicesOf (
    Size                count,
    __Collection&       storeIn,
    ElementType const&  element
) const noexcept(false) -> __Collection& {
  Index index         = 0;
  Size  foundCount    = 0u;
  auto const* pIterable = static_cast <__Receiver const*> (this);
  for (auto iterator = pIterable->cbegin(), end = pIterable->cend(); iterator != end && foundCount < count; ++iterator, ++index) {
    if (cds::meta::equals (*iterator, element)) {
      (void) storeIn.insert (index);
      ++foundCount;
    }
  }

  return storeIn;
}


template <typename __Receiver, typename __Element, bool __exceptCond>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <template <typename...> class __Collection>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
__CDS_OptimalInline auto __IndicesCompositeClient <__Receiver, __Element, __exceptCond>::indicesOf (
    Size                count,
    ElementType const&  element
) const noexcept(false) -> __Collection <Index> {
  __Collection <Index> indices;
  return std::move (indicesOf (count, indices, element));
}


template <typename __Receiver, typename __Element, bool __exceptCond>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
auto __IndicesCompositeClient <__Receiver, __Element, __exceptCond>::firstIndexOf (
    ElementType const& element
) const noexcept(itNoexcept) -> Index {
  auto const* pIterable = static_cast <__Receiver const*> (this);
  Index index = 0;
  for (auto iterator = pIterable->cbegin(), end = pIterable->cend(); iterator != end; ++iterator, ++index) {
    if (cds::meta::equals (*iterator, element)) {
      return index;
    }
  }

  return __Receiver::invalidIndex;
}


template <typename __Receiver, typename __Element, bool __exceptCond>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
auto __IndicesCompositeClient <__Receiver, __Element, __exceptCond>::lastIndexOf (
    ElementType const& element
) const noexcept(itNoexcept) -> Index {
  auto const* pIterable = static_cast <__Receiver const*> (this);
  Index index = static_cast <Index> (pIterable->size()) - 1;
  for (auto iterator = pIterable->crbegin(), end = pIterable->crend(); iterator != end; ++iterator, --index) {
    if (cds::meta::equals (*iterator, element)) {
      return index;
    }
  }

  return __Receiver::invalidIndex;
}


template <typename __Receiver, typename __Element, bool __exceptCond>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename __Collection>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
auto __IndicesCompositeClient <__Receiver, __Element, __exceptCond>::allIndicesOf (
    __Collection&       storeIn,
    ElementType const&  element
) const noexcept(false) -> __Collection& {
  auto const* pIterable = static_cast <__Receiver const*> (this);
  Index index         = 0;
  Size  foundCount    = 0u;
  for (auto iterator = pIterable->cbegin(), end = pIterable->cend(); iterator != end; ++iterator, ++index) {
    if (cds::meta::equals (*iterator, element)) {
      (void) storeIn.insert (index);
      ++foundCount;
    }
  }

  return storeIn;
}


template <typename __Receiver, typename __Element, bool __exceptCond>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <template <typename...> class __Collection>    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto __IndicesCompositeClient <__Receiver, __Element, __exceptCond>::allIndicesOf (
    ElementType const& element
) const noexcept(false) -> __Collection <Index> {
  __Collection <Index> indices;
  return std::move (allIndicesOf (indices, element));
}
} // namespace __impl 
} // namespace __hidden 
} // namespace cds 

#endif // __CDS_SHARED_INDICES_COMPOSITE_CLIENT_IMPL_HPP__ 
