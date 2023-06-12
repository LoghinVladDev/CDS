//
// Created by loghin on 6/30/2022.
//

#ifndef __CDS_SHARED_REPLACE_COMPOSITE_CLIENT_IMPL_HPP__ // NOLINT(llvm-header-guard) 
#define __CDS_SHARED_REPLACE_COMPOSITE_CLIENT_IMPL_HPP__ // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
#pragma once

namespace cds {       // NOLINT(modernize-concat-nested-namespaces) 
namespace __hidden {  // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
namespace __impl {    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename __Receiver, typename __Element, bool __exceptCond> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
template <typename __TElement, cds::meta::EnableIf <cds::meta::IsCopyAssignable <__TElement>::value>> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
auto __ReplaceCompositeClient <__Receiver, __Element, __exceptCond>::replace (
    Size                count,
    ElementType const&  what,
    ElementType const&  with
) noexcept(copyAsNoexcept) -> Size {
  Size replacedCount = 0u;
  auto* pIterable = static_cast <__Receiver*> (this);
  for (auto iterator = pIterable->begin(), end = pIterable->end(); iterator != end && replacedCount < count; ++iterator) {
    if (cds::meta::equals (*iterator, what)) {
      *iterator = with;
      ++replacedCount;
    }
  }

  return replacedCount;
}


template <typename __Receiver, typename __Element, bool __exceptCond> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
template <typename __TElement, cds::meta::EnableIf <cds::meta::IsCopyAssignable <__TElement>::value>> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
auto __ReplaceCompositeClient <__Receiver, __Element, __exceptCond>::replaceFirst (
    ElementType const& what,
    ElementType const& with
) noexcept(copyAsNoexcept) -> bool {
  auto* pIterable = static_cast <__Receiver*> (this);
  for (auto iterator = pIterable->begin(), end = pIterable->end(); iterator != end; ++iterator) {
    if (cds::meta::equals (*iterator, what)) {
      *iterator = with;
      return true;
    }
  }

  return false;
}


template <typename __Receiver, typename __Element, bool __exceptCond> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
template <typename __TElement, cds::meta::EnableIf <cds::meta::IsMoveAssignable <__TElement>::value>> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
auto __ReplaceCompositeClient <__Receiver, __Element, __exceptCond>::replaceFirst (
    ElementType const&  what,
    ElementType&&       with
) noexcept(moveAsNoexcept) -> bool {
  auto* pIterable = static_cast <__Receiver*> (this);
  for (auto iterator = pIterable->begin(), end = pIterable->end(); iterator != end; ++iterator) {
    if (cds::meta::equals (*iterator, what)) {
      *iterator = std::move (with);
      return true;
    }
  }

  return false;
}


template <typename __Receiver, typename __Element, bool __exceptCond> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
template <typename __TElement, cds::meta::EnableIf <cds::meta::IsCopyAssignable <__TElement>::value>> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
auto __ReplaceCompositeClient <__Receiver, __Element, __exceptCond>::replaceLast (
    ElementType const& what,
    ElementType const& with
) noexcept(copyAsNoexcept) -> bool {
  auto* pIterable = static_cast <__Receiver*> (this);
  for (auto iterator = pIterable->rbegin(), end = pIterable->rend(); iterator != end; ++iterator) {
    if (cds::meta::equals (*iterator, what)) {
      * iterator = with;
      return true;
    }
  }

  return false;
}


template <typename __Receiver, typename __Element, bool __exceptCond> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
template <typename __TElement, cds::meta::EnableIf <cds::meta::IsMoveAssignable <__TElement>::value>> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
auto __ReplaceCompositeClient <__Receiver, __Element, __exceptCond>::replaceLast (
    ElementType const&  what,
    ElementType&&       with
) noexcept(moveAsNoexcept) -> bool {
  auto* pIterable = static_cast <__Receiver*> (this);
  for (auto iterator = pIterable->rbegin(), end = pIterable->rend(); iterator != end; ++iterator) {
    if (cds::meta::equals (*iterator, what)) {
      *iterator = std::move (with);
      return true;
    }
  }

  return false;
}


template <typename __Receiver, typename __Element, bool __exceptCond> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
template <typename __TElement, cds::meta::EnableIf <cds::meta::IsCopyAssignable <__TElement>::value>> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
auto __ReplaceCompositeClient <__Receiver, __Element, __exceptCond>::replaceAll (
    ElementType const& what,
    ElementType const& with
) noexcept(copyAsNoexcept) -> Size {
  auto* pIterable = static_cast <__Receiver*> (this);
  Size replacedCount = 0u;
  for (auto iterator = pIterable->rbegin(), end = pIterable->rend(); iterator != end; ++iterator) {
    if (cds::meta::equals (*iterator, what)) {
      *iterator = with;
      ++replacedCount;
    }
  }

  return replacedCount;
}
} // namespace __impl 
} // namespace __hidden 
} // namespace cds 

#endif // __CDS_SHARED_REPLACE_COMPOSITE_CLIENT_IMPL_HPP__ 
