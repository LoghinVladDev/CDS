//
// Created by loghin on 6/30/2022.
//

#ifndef __CDS_SHARED_REPLACE_COMPOSITE_CLIENT_HPP__ // NOLINT(llvm-header-guard)
#define __CDS_SHARED_REPLACE_COMPOSITE_CLIENT_HPP__ // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
#pragma once

namespace cds {       // NOLINT(modernize-concat-nested-namespaces)
namespace __hidden {  // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
namespace __impl {    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename __Receiver, typename __Element, bool __exceptCond = false> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __ReplaceCompositeClient {                                              // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
public:
  using ElementType = __Element;

protected:
  constexpr static bool const itNoexcept = __exceptCond;
  constexpr static bool const copyAsNoexcept = cds::meta::IsNoexceptCopyAssignable <__Element>::value && itNoexcept;
  constexpr static bool const moveAsNoexcept = cds::meta::IsNoexceptMoveAssignable <__Element>::value && itNoexcept;

  template <typename __TElementType = __Element, cds::meta::EnableIf <cds::meta::IsCopyAssignable <__TElementType>::value> = 0>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  auto replace (
      Size                count,
      ElementType const&  what,
      ElementType const&  with
  ) noexcept(copyAsNoexcept) -> Size;

  template <typename __TElementType = __Element, cds::meta::EnableIf <cds::meta::IsCopyAssignable <__TElementType>::value> = 0> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
  auto replaceFirst (
      ElementType const& what,
      ElementType const& with
  ) noexcept(copyAsNoexcept) -> bool;

  template <typename __TElementType = __Element, cds::meta::EnableIf <cds::meta::IsMoveAssignable <__TElementType>::value> = 0>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  auto replaceFirst (
      ElementType const&  what,
      ElementType&&       with
  ) noexcept(moveAsNoexcept) -> bool;

  template <typename __TElementType = __Element, cds::meta::EnableIf <cds::meta::IsCopyAssignable <__TElementType>::value> = 0>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  auto replaceLast (
      ElementType const& what,
      ElementType const& with
  ) noexcept(copyAsNoexcept) -> bool;

  template <typename __TElementType = __Element, cds::meta::EnableIf <cds::meta::IsMoveAssignable <__TElementType>::value> = 0>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  auto replaceLast (
      ElementType const&  what,
      ElementType&&       with
  ) noexcept(moveAsNoexcept) -> bool;

  template <typename __TElementType = __Element, cds::meta::EnableIf <cds::meta::IsCopyAssignable <__TElementType>::value> = 0>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  auto replaceAll (
      ElementType const& what,
      ElementType const& with
  ) noexcept(copyAsNoexcept) -> Size;
};


template <typename __Receiver, typename __Element>        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __LocalReplaceCompositeClient :  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __ReplaceCompositeClient <__Receiver, __Element, true> {};
} // namespace __impl
} // namespace __hidden
} // namespace cds

#endif // __CDS_SHARED_REPLACE_COMPOSITE_CLIENT_HPP__
