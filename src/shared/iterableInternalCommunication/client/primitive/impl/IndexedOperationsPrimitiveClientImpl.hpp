//
// Created by loghin on 6/30/2022.
//

#ifndef __CDS_SHARED_INDEXED_OPERATIONS_PRIMITIVE_CLIENT_IMPL_HPP__ // NOLINT(llvm-header-guard) 
#define __CDS_SHARED_INDEXED_OPERATIONS_PRIMITIVE_CLIENT_IMPL_HPP__ // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
#pragma once

namespace cds {       // NOLINT(modernize-concat-nested-namespaces) 
namespace __hidden {  // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
namespace __impl {    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename __Receiver, typename __Element>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
template <typename __Collection, typename __TElement, cds::meta::EnableIf <cds::meta::IsCopyConstructible <__TElement>::value>> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
auto __IndexedOperationsPrimitiveClient <__Receiver, __Element>::sub (
    __Collection& storeIn,
    Index         from,
    Index         to
) const noexcept(false) -> __Collection& {
  if (from > to) {
    std::swap (from, to);
  }

  if (from < 0) {
    from = 0;
  }

  auto const* pReceiver = static_cast <__Receiver const*> (this);
  auto const size = pReceiver->size();
  if (to >= size) {
    to = size;
  }

  Index index = 0;
  for (auto it = pReceiver->cbegin(), end = pReceiver->cend(); it != end; ++it, ++index) {
    if (index >= from && index < to) {
      (void) storeIn.insert (*it);
    }
  }

  return storeIn;
}


template <typename __Receiver, typename __Element>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
template <typename __Collection, typename __TElement, cds::meta::EnableIf <cds::meta::IsCopyConstructible <__TElement>::value>> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto __IndexedOperationsPrimitiveClient <__Receiver, __Element>::sub (Index from, Index to) const noexcept(false) -> __Collection {
  __Collection collection;
  return std::move (this->sub (collection, from, to));
}


template <typename __Receiver, typename __Element>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
template <
    template <typename ...> class __Collection,   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __TElement,                            // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
    cds::meta::EnableIf <cds::meta::IsCopyConstructible <__TElement>::value>
> __CDS_OptimalInline auto __IndexedOperationsPrimitiveClient <__Receiver, __Element>::sub (Index from, Index to) const noexcept(false) -> __Collection <__Element> {
  __Collection < __Element > collection;
  return std::move (this->sub (collection, from, to));
}


template <typename __Receiver, typename __Element>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
__CDS_OptimalInline auto __IndexedOperationsPrimitiveClient <__Receiver, __Element>::operator [] (
    Index index
) const noexcept (false) -> __Element const& {
  return static_cast <__Receiver const*> (this)->get (index);
}


template <typename __Receiver, typename __Element>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
__CDS_OptimalInline auto __IndexedOperationsPrimitiveClient <__Receiver, __Element>::operator [] (
    Index index
) noexcept (false) -> __Element& {
  return static_cast <__Receiver*> (this)->get (index);
}


template <typename __Receiver, typename __Element>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
auto __IndexedOperationsPrimitiveClient <__Receiver, __Element>::removeAt (
    Collection <Index> const& indices
) noexcept(false) -> Size {
  Size removedCount = 0u;
  auto* pReceiver = static_cast <__Receiver*> (this);
  for (auto iterator = indices.begin(); iterator != indices.end(); ++iterator) {
    if (pReceiver->removeAt (*iterator)) {
      ++removedCount;
    }
  }

  return removedCount;
}


template <typename __Receiver, typename __Element>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
auto __IndexedOperationsPrimitiveClient <__Receiver, __Element>::removeAt (
    std::initializer_list <Index> const& indices
) noexcept(false) -> Size {
  Size removedCount = 0u;
  auto* pReceiver = static_cast <__Receiver*> (this);
  for (auto const& index : indices) {
    if (pReceiver->removeAt (index)) {
      ++removedCount;
    }
  }

  return removedCount;
}


template <typename __Receiver, typename __Element>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
template <typename __Collection, typename __TElement, cds::meta::EnableIf <cds::meta::IsCopyConstructible <__TElement>::value>> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
auto __LocalIndexedOperationsPrimitiveClient <__Receiver, __Element>::sub (
    __Collection& storeIn,
    Index         from,
    Index         to
) const noexcept(false) -> __Collection& {
  if (from > to) {
    std::swap (from, to);
  }

  if (from < 0) {
    from = 0;
  }

  auto pReceiver = static_cast <__Receiver const*> (this);
  if (to >= pReceiver->size()) {
    to = pReceiver->size();
  }

  Index index = 0;
  for (auto iterator = pReceiver->cbegin(), end = pReceiver->cend(); iterator != end; ++iterator, ++index) {
    if (index >= from && index < to) {
      (void) storeIn.insert (*iterator);
    }
  }

  return storeIn;
}


template <typename __Receiver, typename __Element>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
template <typename __Collection, typename __TElement, cds::meta::EnableIf <cds::meta::IsCopyConstructible <__TElement>::value>> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto __LocalIndexedOperationsPrimitiveClient <__Receiver, __Element>::sub (Index from, Index to) const noexcept(false) -> __Collection {
  __Collection collection;
  return std::move (this->sub (collection, from, to));
}


template <typename __Receiver, typename __Element>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
template <
    template <typename...> class __Collection,   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __TElement,                            // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
    cds::meta::EnableIf <cds::meta::IsCopyConstructible <__TElement>::value>
> __CDS_OptimalInline auto __LocalIndexedOperationsPrimitiveClient <__Receiver, __Element>::sub (Index from, Index to) const noexcept(false) -> __Collection <__Element> {
  __Collection < __Element > collection;
  return std::move (this->sub (collection, from, to));
}
} // namespace __impl 
} // namespace __hidden 
} // namespace cds 

#endif // __CDS_SHARED_INDEXED_OPERATIONS_PRIMITIVE_CLIENT_IMPL_HPP__ 
