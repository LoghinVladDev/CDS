//
// Created by loghin on 6/30/2022.
//

#ifndef __CDS_SHARED_REPLACE_OF_COMPOSITE_CLIENT_HPP__ // NOLINT(llvm-header-guard) 
#define __CDS_SHARED_REPLACE_OF_COMPOSITE_CLIENT_HPP__ // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
#pragma once

namespace cds {       // NOLINT(modernize-concat-nested-namespaces)
namespace __hidden {  // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
namespace __impl {    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <
    typename                                                                __Receiver,           // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                                __Element,            // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                                __OfCollection,       // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__OfCollection const&, __Element const&> __contains,           // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    bool                                                                    __exceptCond = false  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> class __ReplaceOfCompositeClient {                                                              // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
public:
  using ElementType = __Element;
  using OfCollectionType = __OfCollection;

protected:
  constexpr static bool const itNoexcept = __exceptCond;
  constexpr static bool const copyAsNoexcept = cds::meta::IsNoexceptCopyAssignable <__Element>::value && itNoexcept;
  constexpr static bool const moveAsNoexcept = cds::meta::IsNoexceptMoveAssignable <__Element>::value && itNoexcept;

public:
  template <typename __TElement = __Element, cds::meta::EnableIf <cds::meta::IsCopyAssignable <__TElement>::value> = 0> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  auto replaceOf (
      Size                  count,
      __OfCollection const& of,
      ElementType const&    with
  ) noexcept(copyAsNoexcept) -> Size;

  template <typename __TElement = __Element, cds::meta::EnableIf <cds::meta::IsCopyAssignable <__TElement>::value> = 0> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  auto replaceFirstOf (
      __OfCollection const& of,
      ElementType const&    with
  ) noexcept(copyAsNoexcept) -> bool;

  template <typename __TElement = __Element, cds::meta::EnableIf <cds::meta::IsMoveAssignable <__TElement>::value> = 0> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  auto replaceFirstOf (
      __OfCollection const& of,
      ElementType&&         with
  ) noexcept(moveAsNoexcept) -> bool;

  template <typename __TElement = __Element, cds::meta::EnableIf <cds::meta::IsCopyAssignable <__TElement>::value> = 0> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  auto replaceLastOf (
      __OfCollection const& of,
      ElementType const&    with
  ) noexcept(copyAsNoexcept) -> bool;

  template <typename __TElement = __Element, cds::meta::EnableIf <cds::meta::IsMoveAssignable <__TElement>::value> = 0> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  auto replaceLastOf (
      __OfCollection const& of,
      ElementType&&         with
  ) noexcept(moveAsNoexcept) -> bool;

  template <typename __TElement = __Element, cds::meta::EnableIf <cds::meta::IsCopyAssignable <__TElement>::value> = 0> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  auto replaceAllOf (
      __OfCollection const& of,
      ElementType const&    with
  ) noexcept(copyAsNoexcept) -> Size;

  template <typename __TElement = __Element, cds::meta::EnableIf <cds::meta::IsCopyAssignable <__TElement>::value> = 0> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  auto replaceNotOf (
      Size                  count,
      __OfCollection const& of,
      ElementType const&    with
  ) noexcept(copyAsNoexcept) -> Size;

  template <typename __TElement = __Element, cds::meta::EnableIf <cds::meta::IsCopyAssignable <__TElement>::value> = 0> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  auto replaceFirstNotOf (
      __OfCollection const& of,
      ElementType const& with
  ) noexcept(copyAsNoexcept) -> bool;

  template <typename __TElement = __Element, cds::meta::EnableIf <cds::meta::IsMoveAssignable <__TElement>::value> = 0> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  auto replaceFirstNotOf (
      __OfCollection const& of,
      ElementType&&         with
  ) noexcept(moveAsNoexcept) -> bool;

  template <typename __TElement = __Element, cds::meta::EnableIf <cds::meta::IsCopyAssignable <__TElement>::value> = 0> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  auto replaceLastNotOf (
      __OfCollection const& of,
      ElementType const&    with
  ) noexcept(copyAsNoexcept) -> bool;

  template <typename __TElement = __Element, cds::meta::EnableIf <cds::meta::IsMoveAssignable <__TElement>::value> = 0> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  auto replaceLastNotOf (
      __OfCollection const& of,
      ElementType&&         with
  ) noexcept(moveAsNoexcept) -> bool;

  template <typename __TElement = __Element, cds::meta::EnableIf <cds::meta::IsCopyAssignable <__TElement>::value> = 0> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  auto replaceAllNotOf (
      __OfCollection const& of,
      ElementType const& with
  ) noexcept(copyAsNoexcept) -> Size;
};


template <
    typename                                                                __Receiver,     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                                __Element,      // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                                __OfCollection, // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__OfCollection const&, __Element const&> __contains      // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> class __CDS_InheritsEBOs __LocalReplaceOfCompositeClient :                                // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __ReplaceOfCompositeClient <__Receiver, __Element, __OfCollection, __contains, true> {};
} // namespace __impl
} // namespace __hidden
} // namespace cds

#endif // __CDS_SHARED_REPLACE_OF_COMPOSITE_CLIENT_HPP__
