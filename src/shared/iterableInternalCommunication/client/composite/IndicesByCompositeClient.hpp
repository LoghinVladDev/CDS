//
// Created by loghin on 6/30/22.
//

#ifndef __CDS_SHARED_INDICES_BY_COMPOSITE_CLIENT_HPP__ // NOLINT(llvm-header-guard)
#define __CDS_SHARED_INDICES_BY_COMPOSITE_CLIENT_HPP__ // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
#pragma once

namespace cds {       // NOLINT(modernize-concat-nested-namespaces)
namespace __hidden {  // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
namespace __impl {    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename __Receiver, typename __Element, bool __exceptCond = false> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __IndicesByCompositeClient {                                            // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
public:
  using ElementType = __Element;

protected:
  constexpr static bool const itNoexcept = __exceptCond;

public:
  template <typename __Collection, typename __Predicate>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  auto indicesOfThat (
      Size                count,
      __Collection&       storeIn,
      __Predicate const&  predicate
  ) const noexcept(false) -> __Collection&;

  template <template <typename...> class __Collection, typename __Predicate>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  __CDS_NoDiscard auto indicesOfThat (
      Size                count,
      __Predicate const&  predicate
  ) const noexcept(false) -> __Collection <Index>;

public: /* NOLINT(readability-redundant-access-specifiers) */
  template <typename __Predicate>   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  __CDS_NoDiscard auto firstIndexOfThat (
      __Predicate const& predicate
  ) const noexcept (noexcept (predicate (cds::meta::referenceOf <ElementType const>())) && itNoexcept) -> Index;

  template <typename __Predicate>   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  __CDS_NoDiscard auto lastIndexOfThat (
      __Predicate const& predicate
  ) const noexcept (noexcept (predicate (cds::meta::referenceOf <ElementType const>())) && itNoexcept) -> Index;

  template <typename __Collection, typename __Predicate>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  auto allIndicesOfThat (
      __Collection&       storeIn,
      __Predicate const&  predicate
  ) const noexcept(false) -> __Collection&;

  template <template <typename...> class __Collection, typename __Predicate>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  __CDS_NoDiscard auto allIndicesOfThat (
      __Predicate const& predicate
  ) const noexcept(false) -> __Collection <Index>;
};


template <typename __Receiver, typename __Element>          // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __LocalIndicesByCompositeClient :  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __IndicesByCompositeClient <__Receiver, __Element, true> {};
} // namespace __impl
} // namespace __hidden
} // namespace cds

#endif // __CDS_SHARED_INDICES_BY_COMPOSITE_CLIENT_HPP__
