//
// Created by loghin on 6/30/2022.
//

#ifndef __CDS_SHARED_INDEXED_OPERATIONS_PRIMITIVE_CLIENT_HPP__ // NOLINT(llvm-header-guard)
#define __CDS_SHARED_INDEXED_OPERATIONS_PRIMITIVE_CLIENT_HPP__ // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
#pragma once

namespace cds {       // NOLINT(modernize-concat-nested-namespaces)
namespace __hidden {  // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
namespace __impl {    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename __Receiver, typename __Element>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __IndexedOperationsPrimitiveClient {          // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
protected:
  using ElementType = __Element;

  template <
      typename __Collection,                  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      typename __TElementType = __Element,    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      cds::meta::EnableIf <cds::meta::IsCopyConstructible <__TElementType>::value> = 0
  > auto sub (__Collection& storeIn, Index from, Index to) const noexcept(false) -> __Collection&;

  template <
      typename __Collection,                  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      typename __TElementType = __Element,    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      cds::meta::EnableIf <cds::meta::IsCopyConstructible <__TElementType>::value> = 0
  > __CDS_NoDiscard auto sub (Index from, Index to) const noexcept(false) -> __Collection;

  template <
      template <typename...> class __Collection,   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      typename __TElementType = __Element,            // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      cds::meta::EnableIf <cds::meta::IsCopyConstructible <__TElementType>::value> = 0
  > __CDS_NoDiscard auto sub (Index from, Index to) const noexcept(false) -> __Collection <__Element>;

  __CDS_NoDiscard auto operator [] (Index index) const noexcept (false) -> ElementType const&;
  __CDS_NoDiscard auto operator [] (Index index) noexcept (false) -> ElementType&;

  auto removeAt (Collection <Index> const &indices) noexcept(false) -> Size;
  auto removeAt (std::initializer_list <Index> const &indices) noexcept(false) -> Size;
};


template <typename __Receiver, typename __Element>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __LocalIndexedOperationsPrimitiveClient {     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
protected:
  using ElementType = __Element;

  template <
      typename __Collection,                  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      typename __TElementType = __Element,    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      cds::meta::EnableIf <cds::meta::IsCopyConstructible <__TElementType>::value> = 0
  > auto sub (__Collection& storeIn, Index from, Index to) const noexcept(false) -> __Collection&;

  template <
      typename __Collection = __Receiver, // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      typename __TElementType = __Element,    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      cds::meta::EnableIf <cds::meta::IsCopyConstructible <__TElementType>::value> = 0
  > __CDS_NoDiscard auto sub (Index from, Index to) const noexcept(false) -> __Collection;

  template <
      template <typename...> class __Collection,   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      typename __TElementType = __Element,            // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      cds::meta::EnableIf <cds::meta::IsCopyConstructible <__TElementType>::value> = 0
  > __CDS_NoDiscard auto sub (Index from, Index to) const noexcept(false) -> __Collection <__Element>;
};

} // namespace __impl
} // namespace __hidden
} // namespace cds

#endif // __CDS_SHARED_INDEXED_OPERATIONS_PRIMITIVE_CLIENT_HPP__
