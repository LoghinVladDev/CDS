//
// Created by loghin on 6/30/22.
//

#ifndef __CDS_SHARED_INDICES_OF_COMPOSITE_CLIENT_HPP__ // NOLINT(llvm-header-guard)
#define __CDS_SHARED_INDICES_OF_COMPOSITE_CLIENT_HPP__ // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
#pragma once

namespace cds {       // NOLINT(modernize-concat-nested-namespaces)
namespace __hidden {  // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
namespace __impl {    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <
    typename                                                                  __Receiver,           // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                                  __Element,            // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                                  __FromCollection,     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__FromCollection const&, __Element const&> __contains,           // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    bool                                                                      __exceptCond = false  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> class __IndicesOfCompositeClient {                                                                // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
public:
  using ElementType = __Element;

protected:
  constexpr static bool const itNoexcept = __exceptCond;
  
  template <typename __Collection>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  auto indicesOfFrom (
      Size                    count,
      __Collection&           storeIn,
      __FromCollection const& from
  ) const noexcept(false) -> __Collection&;

  template <template <typename...> class __Collection>   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  __CDS_NoDiscard auto indicesOfFrom (
      Size                    count,
      __FromCollection const& from
  ) const noexcept(false) -> __Collection <Index>;

  __CDS_NoDiscard auto firstIndexOfFrom (__FromCollection const& from) const noexcept(itNoexcept) -> Index;
  __CDS_NoDiscard auto lastIndexOfFrom (__FromCollection const& from) const noexcept(itNoexcept) -> Index;

  template <typename __Collection>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  auto allIndicesOfFrom (
      __Collection&           storeIn,
      __FromCollection const& from
  ) const noexcept(false) -> __Collection&;

  template <template <typename...> class __Collection>   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  __CDS_NoDiscard auto allIndicesOfFrom (
      __FromCollection const& from
  ) const noexcept(false) -> __Collection <Index>;

  template <typename __Collection>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  auto indicesOfNotFrom (
      Size                    count,
      __Collection&           storeIn,
      __FromCollection const& from
  ) const noexcept(false) -> __Collection&;

  template <template <typename...> class __Collection>   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  __CDS_NoDiscard auto indicesOfNotFrom (
      Size                    count,
      __FromCollection const& from
  ) const noexcept(false) -> __Collection <Index>;

  __CDS_NoDiscard auto firstIndexOfNotFrom (__FromCollection const& from) const noexcept(itNoexcept) -> Index;
  __CDS_NoDiscard auto lastIndexOfNotFrom (__FromCollection const& from) const noexcept(itNoexcept) -> Index;

  template <typename __Collection>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  auto allIndicesOfNotFrom (
      __Collection&           storeIn,
      __FromCollection const& from
  ) const noexcept(false) -> __Collection&;

  template <template <typename...> class __Collection>   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  __CDS_NoDiscard auto allIndicesOfNotFrom (
      __FromCollection const& from
  ) const noexcept(false) -> __Collection <Index>;
};


template <
    typename                                                                  __Receiver,       // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                                  __Element,        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                                  __FromCollection, // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__FromCollection const&, __Element const&> __contains        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> class __CDS_InheritsEBOs __LocalIndicesOfCompositeClient :                                    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __IndicesOfCompositeClient <__Receiver, __Element, __FromCollection, __contains, true> {};
} // namespace __impl
} // namespace __hidden
} // namespace cds

#endif // __CDS_SHARED_INDICES_OF_COMPOSITE_CLIENT_HPP__
