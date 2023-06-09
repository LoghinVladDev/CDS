//
// Created by loghin on 6/30/2022.
//

#ifndef __CDS_SHARED_REPLACE_BY_COMPOSITE_CLIENT_IMPL_HPP__ // NOLINT(llvm-header-guard) 
#define __CDS_SHARED_REPLACE_BY_COMPOSITE_CLIENT_IMPL_HPP__ // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
#pragma once

namespace cds {       // NOLINT(modernize-concat-nested-namespaces) 
namespace __hidden {  // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
namespace __impl {    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename __Element, typename __Supplier, cds::meta::EnableIf <cds::meta::IsMoveAssignable <__Element>::value> = 0>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_NonConstConstexprMemberFunction auto __assignBySupplier ( // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
    __Element&        element,
    __Supplier const& supplier
) noexcept (
    noexcept (cds::meta::referenceOf <__Element>() = std::move (cds::meta::referenceOf <__Element>())) &&
    noexcept (supplier (cds::meta::referenceOf <__Element>()))
) -> void {
  element = std::move (supplier (element));
}


template <typename __Element, typename __Supplier, cds::meta::EnableIf <!cds::meta::IsMoveAssignable <__Element>::value> = 0>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_NonConstConstexprMemberFunction auto __assignBySupplier ( // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
    __Element&        element,
    __Supplier const& supplier
) noexcept (
    noexcept (cds::meta::referenceOf <__Element>() = cds::meta::referenceOf <__Element>()) &&
    noexcept (supplier (cds::meta::referenceOf <__Element>()))
) -> void {
  element = supplier (element);
}


template <typename __Receiver, typename __Element, bool __exceptCond> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
template <typename __Predicate, typename __TElement, cds::meta::EnableIf <cds::meta::IsCopyAssignable <__TElement>::value>> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
auto __ReplaceByCompositeClient <__Receiver, __Element, __exceptCond>::replaceThat (
    Size                count,
    __Predicate const&  predicate,
    ElementType const&  with
) noexcept (noexcept (predicate (cds::meta::referenceOf <ElementType>())) && copyAsNoexcept) -> Size {
  auto* pIterable = static_cast <__Receiver*> (this);
  Size replacedCount = 0u;
  for (auto iterator = pIterable->begin(), end = pIterable->end(); iterator != end && replacedCount < count; ++iterator) {
    if (predicate (*iterator)) {
      *iterator = with;
      ++replacedCount;
    }
  }

  return replacedCount;
}


template <typename __Receiver, typename __Element, bool __exceptCond> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
template <typename __Predicate, typename __TElement, cds::meta::EnableIf <cds::meta::IsCopyAssignable <__TElement>::value>> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
auto __ReplaceByCompositeClient <__Receiver, __Element, __exceptCond>::replaceFirstThat (
    __Predicate const& predicate,
    ElementType const& with
) noexcept (noexcept (predicate (cds::meta::referenceOf <ElementType>())) && copyAsNoexcept) -> bool {
  auto* pIterable = static_cast <__Receiver*> (this);
  for (auto iterator = pIterable->begin(), end = pIterable->end(); iterator != end; ++iterator) {
    if (predicate (*iterator)) {
      *iterator = with;
      return true;
    }
  }

  return false;
}


template <typename __Receiver, typename __Element, bool __exceptCond> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
template <typename __Predicate, typename __TElement, cds::meta::EnableIf <cds::meta::IsMoveAssignable <__TElement>::value>> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
auto __ReplaceByCompositeClient <__Receiver, __Element, __exceptCond>::replaceFirstThat (
    __Predicate const&  predicate,
    ElementType&&       with
) noexcept (noexcept (predicate (cds::meta::referenceOf <ElementType>())) && moveAsNoexcept) -> bool {
  auto* pIterable = static_cast <__Receiver*> (this);
  for (auto iterator = pIterable->begin(), end = pIterable->end(); iterator != end; ++iterator) {
    if (predicate (*iterator)) {
      *iterator = std::move (with);
      return true;
    }
  }

  return false;
}


template <typename __Receiver, typename __Element, bool __exceptCond> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
template <typename __Predicate, typename __TElement, cds::meta::EnableIf <cds::meta::IsCopyAssignable <__TElement>::value>> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
auto __ReplaceByCompositeClient <__Receiver, __Element, __exceptCond>::replaceLastThat (
    __Predicate const& predicate,
    ElementType const& with
) noexcept (noexcept (predicate (cds::meta::referenceOf <ElementType>())) && copyAsNoexcept) -> bool {
  auto* pIterable = static_cast <__Receiver*> (this);
  for (auto iterator = pIterable->rbegin(), end = pIterable->rend(); iterator != end; ++iterator) {
    if (predicate (*iterator)) {
      *iterator = with;
      return true;
    }
  }

  return false;
}


template <typename __Receiver, typename __Element, bool __exceptCond> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
template <typename __Predicate, typename __TElement, cds::meta::EnableIf <cds::meta::IsMoveAssignable <__TElement>::value>> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
auto __ReplaceByCompositeClient <__Receiver, __Element, __exceptCond>::replaceLastThat (
    __Predicate const&  predicate,
    ElementType&&       with
) noexcept (noexcept (predicate (cds::meta::referenceOf <ElementType>())) && moveAsNoexcept) -> bool {
  auto* pIterable = static_cast <__Receiver*> (this);
  for (auto iterator = pIterable->rbegin(), end = pIterable->rend(); iterator != end; ++iterator) {
    if (predicate (*iterator)) {
      *iterator = std::move (with);
      return true;
    }
  }

  return false;
}


template <typename __Receiver, typename __Element, bool __exceptCond> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
template <typename __Predicate, typename __TElement, cds::meta::EnableIf <cds::meta::IsCopyAssignable <__TElement>::value>> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
auto __ReplaceByCompositeClient <__Receiver, __Element, __exceptCond>::replaceAllThat (
    __Predicate const& predicate,
    ElementType const& with
) noexcept (noexcept (predicate (cds::meta::referenceOf <ElementType>())) && copyAsNoexcept) -> Size {
  auto* pIterable = static_cast <__Receiver*> (this);
  Size replacedCount = 0u;
  for (auto iterator = pIterable->begin(), end = pIterable->end(); iterator != end; ++iterator) {
    if (predicate (*iterator)) {
      *iterator = with;
      ++replacedCount;
    }
  }

  return replacedCount;
}


template <typename __Receiver, typename __Element, bool __exceptCond> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
template <typename __Predicate, typename __Supplier> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
auto __ReplaceByCompositeClient <__Receiver, __Element, __exceptCond>::replaceThatBy (
    Size                count,
    __Predicate const&  predicate,
    __Supplier  const&  supplier
) noexcept (
    noexcept (predicate (cds::meta::referenceOf <ElementType>())) &&
    noexcept (supplier (cds::meta::referenceOf <ElementType>())) &&
    IsNoexceptSuppliable <__Supplier>::value
) -> Size {
  auto* pIterable = static_cast <__Receiver*> (this);
  Size replacedCount = 0u;
  for (auto iterator = pIterable->begin(), end = pIterable->end(); iterator != end && replacedCount < count; ++iterator) {
    if (predicate (*iterator)) {
      __assignBySupplier (*iterator, supplier);
      ++replacedCount;
    }
  }

  return replacedCount;
}


template <typename __Receiver, typename __Element, bool __exceptCond> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
template <typename __Predicate, typename __Supplier> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
auto __ReplaceByCompositeClient <__Receiver, __Element, __exceptCond>::replaceFirstThatBy (
    __Predicate const&  predicate,
    __Supplier const&   supplier
) noexcept (
    noexcept (predicate (cds::meta::referenceOf <ElementType>())) &&
    noexcept (supplier (cds::meta::referenceOf <ElementType>())) &&
    IsNoexceptSuppliable <__Supplier>::value
) -> bool {
  auto* pIterable = static_cast <__Receiver*> (this);
  for (auto iterator = pIterable->begin(), end = pIterable->end(); iterator != end; ++iterator) {
    if (predicate (*iterator)) {
      __assignBySupplier (*iterator, supplier);
      return true;
    }
  }

  return false;
}


template <typename __Receiver, typename __Element, bool __exceptCond> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
template <typename __Predicate, typename __Supplier> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
auto __ReplaceByCompositeClient <__Receiver, __Element, __exceptCond>::replaceLastThatBy (
    __Predicate const&  predicate,
    __Supplier const&   supplier
) noexcept (
    noexcept (predicate (cds::meta::referenceOf <ElementType>())) &&
    noexcept (supplier (cds::meta::referenceOf <ElementType>())) &&
    IsNoexceptSuppliable <__Supplier>::value
) -> bool {
  auto* pIterable = static_cast <__Receiver*> (this);
  for (auto iterator = pIterable->rbegin(), end = pIterable->rend(); iterator != end; ++iterator) {
    if (predicate (*iterator)) {
      __assignBySupplier (*iterator, supplier);
      return true;
    }
  }

  return false;
}


template <typename __Receiver, typename __Element, bool __exceptCond> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
template <typename __Predicate, typename __Supplier> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
auto __ReplaceByCompositeClient <__Receiver, __Element, __exceptCond>::replaceAllThatBy (
    __Predicate const&  predicate,
    __Supplier const&   supplier
) noexcept (
    noexcept (predicate (cds::meta::referenceOf <ElementType>())) &&
    noexcept (supplier (cds::meta::referenceOf <ElementType>())) &&
    IsNoexceptSuppliable <__Supplier>::value
) -> Size {
  auto* pIterable = static_cast <__Receiver*> (this);
  Size replacedCount = 0u;
  for (auto iterator = pIterable->rbegin(), end = pIterable->rend(); iterator != end; ++iterator) {
    if (predicate (*iterator)) {
      __assignBySupplier (*iterator, supplier);
      ++replacedCount;
    }
  }

  return replacedCount;
}
} // namespace __impl 
} // namespace __hidden 
} // namespace cds 

#endif // __CDS_SHARED_REPLACE_BY_COMPOSITE_CLIENT_IMPL_HPP__ 
