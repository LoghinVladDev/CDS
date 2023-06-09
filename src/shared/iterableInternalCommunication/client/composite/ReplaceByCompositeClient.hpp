//
// Created by loghin on 6/30/2022.
//

#ifndef __CDS_SHARED_REPLACE_BY_COMPOSITE_CLIENT_HPP__ // NOLINT(llvm-header-guard)
#define __CDS_SHARED_REPLACE_BY_COMPOSITE_CLIENT_HPP__ // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
#pragma once

#include <CDS/meta/FunctionTraits>

namespace cds {       // NOLINT(modernize-concat-nested-namespaces)
namespace __hidden {  // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
namespace __impl {    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename __Receiver, typename __Element, bool __exceptCond = false> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __ReplaceByCompositeClient {                                            // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
public:
  using ElementType = __Element;

protected:
  constexpr static bool const itNoexcept = __exceptCond;
  constexpr static bool const copyAsNoexcept = cds::meta::IsNoexceptCopyAssignable <__Element>::value && itNoexcept;
  constexpr static bool const moveAsNoexcept = cds::meta::IsNoexceptMoveAssignable <__Element>::value && itNoexcept;
  
  template <typename __Supplier>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  struct IsNoexceptSuppliable : cds::meta::And <
      cds::meta::IsNoexceptAssignable <__Element, cds::meta::ReturnOf <__Supplier>>,
      cds::meta::BoolConstant <itNoexcept>
  > {};

  template <typename __Predicate, typename __TElement = __Element, cds::meta::EnableIf <cds::meta::IsCopyAssignable <__TElement>::value> = 0> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  auto replaceThat (
      Size                count,
      __Predicate const&  predicate,
      ElementType const&  with
  ) noexcept (noexcept (predicate (cds::meta::referenceOf <ElementType>())) && copyAsNoexcept) -> Size;

  template <typename __Predicate, typename __TElement = __Element, cds::meta::EnableIf <cds::meta::IsCopyAssignable <__TElement>::value> = 0> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  auto replaceFirstThat (
      __Predicate const& predicate,
      ElementType const& with
  ) noexcept (noexcept (predicate (cds::meta::referenceOf <ElementType>())) && copyAsNoexcept) -> bool;

  template <typename __Predicate, typename __TElement = __Element, cds::meta::EnableIf <cds::meta::IsMoveAssignable <__TElement>::value> = 0> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  auto replaceFirstThat (
      __Predicate const&  predicate,
      ElementType&&       with
  ) noexcept (noexcept (predicate (cds::meta::referenceOf <ElementType>())) && moveAsNoexcept) -> bool;

  template <typename __Predicate, typename __TElement = __Element, cds::meta::EnableIf <cds::meta::IsCopyAssignable <__TElement>::value> = 0> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  auto replaceLastThat (
      __Predicate const& predicate,
      ElementType const& with
  ) noexcept (noexcept (predicate (cds::meta::referenceOf <ElementType>())) && copyAsNoexcept) -> bool;

  template <typename __Predicate, typename __TElement = __Element, cds::meta::EnableIf <cds::meta::IsMoveAssignable <__TElement>::value> = 0> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  auto replaceLastThat (
      __Predicate const&  predicate,
      ElementType&&       with
  ) noexcept (noexcept (predicate (cds::meta::referenceOf <ElementType>())) && moveAsNoexcept) -> bool;

  template <typename __Predicate, typename __TElement = __Element, cds::meta::EnableIf <cds::meta::IsCopyAssignable <__TElement>::value> = 0> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  auto replaceAllThat (
      __Predicate const& predicate,
      ElementType const& with
  ) noexcept (noexcept (predicate (cds::meta::referenceOf <ElementType>())) && copyAsNoexcept) -> Size;

  template <typename __Predicate, typename __Supplier>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  auto replaceThatBy (
      Size                count,
      __Predicate const&  predicate,
      __Supplier const&   supplier
  ) noexcept (
      noexcept (predicate (cds::meta::referenceOf <ElementType>())) && 
      noexcept (supplier (cds::meta::referenceOf <ElementType>())) &&
      IsNoexceptSuppliable <__Supplier>::value
  ) -> Size;

  template <typename __Predicate, typename __Supplier>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  auto replaceFirstThatBy (
      __Predicate const&  predicate,
      __Supplier const&   supplier
  ) noexcept (
      noexcept (predicate (cds::meta::referenceOf <ElementType>())) && 
      noexcept (supplier (cds::meta::referenceOf <ElementType>())) &&
      IsNoexceptSuppliable <__Supplier>::value
  ) -> bool;

  template <typename __Predicate, typename __Supplier>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  auto replaceLastThatBy (
      __Predicate const&  predicate,
      __Supplier const&   supplier
  ) noexcept (
      noexcept (predicate (cds::meta::referenceOf <ElementType>())) && 
      noexcept (supplier (cds::meta::referenceOf <ElementType>())) &&
      IsNoexceptSuppliable <__Supplier>::value
  ) -> bool;

  template <typename __Predicate, typename __Supplier>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  auto replaceAllThatBy (
      __Predicate const&  predicate,
      __Supplier const&   supplier
  ) noexcept (
      noexcept (predicate (cds::meta::referenceOf <ElementType>())) && 
      noexcept (supplier (cds::meta::referenceOf <ElementType>())) &&
      IsNoexceptSuppliable <__Supplier>::value
  ) -> Size;
};


template <typename __Receiver, typename __Element>          // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __LocalReplaceByCompositeClient :  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __ReplaceByCompositeClient <__Receiver, __Element, true> {};
} // namespace __impl
} // namespace __hidden
} // namespace cds

#endif // __CDS_SHARED_REPLACE_BY_COMPOSITE_CLIENT_HPP__
