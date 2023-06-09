//
// Created by loghin on 6/30/22.
//

#ifndef __CDS_SHARED_INDICES_COMPOSITE_CLIENT_HPP__ // NOLINT(llvm-header-guard)
#define __CDS_SHARED_INDICES_COMPOSITE_CLIENT_HPP__ // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
#pragma once

namespace cds {       // NOLINT(modernize-concat-nested-namespaces)
namespace __hidden {  // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
namespace __impl {    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename __Receiver, typename __Element, bool __exceptCond = false> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __IndicesCompositeClient {                                              // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
public:
  using ElementType = __Element;

protected:
  constexpr static bool const itNoexcept = __exceptCond;
  
  template <typename __Collection>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  auto indicesOf (
      Size                count,
      __Collection&       storeIn,
      ElementType const&  element
  ) const noexcept(false) -> __Collection&;

  template <template <typename...> class __Collection>   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  __CDS_NoDiscard auto indicesOf (
      Size                count,
      ElementType const&  element
  ) const noexcept(false) -> __Collection <Index>;

  __CDS_NoDiscard auto firstIndexOf (ElementType const& element) const noexcept(itNoexcept) -> Index;
  __CDS_NoDiscard auto lastIndexOf (ElementType const& element) const noexcept(itNoexcept) -> Index;

  template <typename __Collection>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  auto allIndicesOf (
      __Collection&       storeIn,
      ElementType const&  element
  ) const noexcept(false) -> __Collection&;

  template <template <typename...> class __Collection>   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  __CDS_NoDiscard auto allIndicesOf (
      ElementType const& element
  ) const noexcept(false) -> __Collection <Index>;
};

template <typename __Receiver, typename __Element>        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __LocalIndicesCompositeClient :  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __IndicesCompositeClient <__Receiver, __Element, true> {};
} // namespace __impl
} // namespace __hidden
} // namespace cds

#endif // __CDS_SHARED_INDICES_COMPOSITE_CLIENT_HPP__
