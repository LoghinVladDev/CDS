//
// Created by loghin on 6/28/22.
//

#ifndef __CDS_SHARED_RANDOM_INSERTION_PRIMITIVE_CLIENT_IMPL_HPP__ // NOLINT(llvm-header-guard)
#define __CDS_SHARED_RANDOM_INSERTION_PRIMITIVE_CLIENT_IMPL_HPP__ // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
#pragma once

namespace cds {       // NOLINT(modernize-concat-nested-namespaces)
namespace __hidden {  // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
namespace __impl {    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename __Accumulator, typename __Last>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
inline auto __expansiveInsert (__Accumulator* pAccumulator, __Last&& lastValue) noexcept(false) -> void { // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  // being the last value, call insert in the caller accumulator
  (void) pAccumulator->insert (std::forward <__Last> (lastValue));
}


template <typename __Accumulator, typename __First, typename...__Remaining> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
inline auto __expansiveInsert (__Accumulator* pAccumulator, __First&& firstValue, __Remaining&&... remainingValues) noexcept(false) -> void { // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  // call insert on the first value
  (void) pAccumulator->insert (std::forward <__First> (firstValue));
  // recursively call the same function with the remaining values
  __expansiveInsert (pAccumulator, std::forward <__Remaining> (remainingValues)...);
}


template <typename __Receiver, typename __Element, typename __Return> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename __TElement, cds::meta::EnableIf <cds::meta::IsCopyConstructible <__TElement>::value>> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
auto __RandomInsertionPrimitiveClient <__Receiver, __Element, __Return>::insert (ElementType const& element) noexcept(false) -> ElementReference {
  // decay of the element type
  using __ConstructibleElementType    = cds::meta::RemoveConst <__Element>; // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  // called handle type
  using __ReceiverNewHandlerType      = cds::functional::MapperFunction <__ConstructibleElementType*, __Receiver*, __ConstructibleElementType const*, bool*>; // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

  // receiver to call the request to
  auto        pReceiver               = static_cast <__Receiver*> (this);
  // status if new element was created and construction is possible
  bool        newElementCreated;
  // call receiver to acquire a new address from
  auto const  pElementLocation        = bitCast <__ReceiverNewHandlerType> (pReceiver->__iicch_obtainGenericHandler (__IterableInternalRequest::__iir_newAddress)) (
      pReceiver, &element, &newElementCreated
  );

  // if no new element was created, return reference to received location
  if (!newElementCreated) {
    return *pElementLocation;
  }

  // return reference to the received address element, after in-place copy construction
  return *new (pElementLocation) __Element (element);
}


template <typename __Receiver, typename __Element, typename __Return> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename __TElement, cds::meta::EnableIf <cds::meta::IsMoveConstructible <__TElement>::value>> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
auto __RandomInsertionPrimitiveClient <__Receiver, __Element, __Return>::insert (ElementType&& element) noexcept (false) -> ElementReference {
  // decay of the element type
  using __ConstructibleElementType    = cds::meta::RemoveConst <__Element>; // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  // called handle type
  using __ReceiverNewHandlerType      = cds::functional::MapperFunction <__ConstructibleElementType*, __Receiver*, __ConstructibleElementType const*, bool*>; // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

  // receiver to call the request to
  auto        pReceiver               = static_cast <__Receiver*> (this);
  // status if new element was created and construction is possible
  bool        newElementCreated;
  // call receiver to acquire a new address from
  auto const  pElementLocation        = bitCast <__ReceiverNewHandlerType> (pReceiver->__iicch_obtainGenericHandler (__IterableInternalRequest::__iir_newAddress)) (
      pReceiver, &element, &newElementCreated
  );

  // if no new element was created, return reference to received location
  if (!newElementCreated) {
    return *pElementLocation;
  }

  // return reference to the received address element, after in-place move construction
  return *new (pElementLocation) __Element (std::move (element));
}


template <typename __Receiver, typename __Element, typename __Return> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename __TElement, cds::meta::EnableIf <cds::meta::IsCopyConstructible <__TElement>::value>> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto __RandomInsertionPrimitiveClient <__Receiver, __Element, __Return>::add (ElementType const& element) noexcept(false) -> ElementReference {
  // call insert due to deprecation
  return insert (element);
}


template <typename __Receiver, typename __Element, typename __Return> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename __TElement, cds::meta::EnableIf <cds::meta::IsMoveConstructible <__TElement>::value>> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto __RandomInsertionPrimitiveClient <__Receiver, __Element, __Return>::add (ElementType&& element) noexcept(false) -> ElementReference {
  // call insert due to deprecation
  return insert (std::move (element));
}


template <typename __Receiver, typename __Element, typename __Return> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename...__Arguments> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
auto __RandomInsertionPrimitiveClient <__Receiver, __Element, __Return>::emplace (__Arguments&&... parameters) noexcept(false) -> ElementReference {
  // decay of the element type
  using __ConstructibleElementType    = cds::meta::RemoveConst <__Element>; // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  // called handle type
  using __ReceiverNewHandlerType      = cds::functional::MapperFunction <__ConstructibleElementType*, __Receiver*, __ConstructibleElementType const*, bool*>;  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

  // prepare a memory container of the newly constructed element, to avoid destruction in out-of-stack contexts, without need
  // of dynamic allocation
  cds::__hidden::__impl::__allocation::__RawContainer <__Element> referenceElementContainer;
  // emplace-construct new element
  referenceElementContainer.construct (std::forward <__Arguments> (parameters)...);

  // since resources are allocated ( constructor can allocate ) prior to a potential throw call, try
  try {
    // receiver to call the request to
    auto        pReceiver               = static_cast <__Receiver*> (this);
    // status if new element was created and construction is possible
    bool        newElementCreated;
    // call receiver to acquire a new address from
    auto const  pElementLocation        = bitCast <__ReceiverNewHandlerType> (pReceiver->__iicch_obtainGenericHandler (__IterableInternalRequest::__iir_newAddress)) (
        pReceiver, &referenceElementContainer.data(), &newElementCreated
    );

    if (!newElementCreated) {
      // if no new element was created, destruct the created element
      referenceElementContainer.destruct();
    } else {
      // otherwise, copy created data to the received memory address
      (void) std::memcpy (
          static_cast <void*> (pElementLocation),
          static_cast <void const*> (& referenceElementContainer._data[0]),
          sizeof (__Element)
      );
    }

    // either way, return reference to received address
    return *pElementLocation;
  } catch (...) {
    // in the case the call throws, destruct allocated data and throw the exception further in the stack
    referenceElementContainer.destruct();
    throw;
  }
}


template <typename __Receiver, typename __Element, typename __Return> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename...__Arguments> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto __RandomInsertionPrimitiveClient <__Receiver, __Element, __Return>::insertAll (__Arguments&&... values) noexcept(false) -> void {
  // call expansive insert with the received forwarding references on this object as the accumulator
  __expansiveInsert (this, std::forward <__Arguments> (values)...);
}


template <typename __Receiver, typename __Element, typename __Return> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename...__Arguments> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto __RandomInsertionPrimitiveClient <__Receiver, __Element, __Return>::addAll (__Arguments&&... values) noexcept(false) -> void {
  // call expansive insert with the received forwarding references on this object as the accumulator
  __expansiveInsert (this, std::forward <__Arguments> (values)...);
}


template <typename __Receiver, typename __Element, typename __Return> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename __Iterable> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto __RandomInsertionPrimitiveClient <__Receiver, __Element, __Return>::insertAllOf (__Iterable const& iterable) noexcept (false) -> void {
  // call insert all of with extracted iterators
  insertAllOf (iterable.begin(), iterable.end());
}


template <typename __Receiver, typename __Element, typename __Return> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename __TElement, cds::meta::EnableIf <cds::meta::IsCopyConstructible <__TElement>::value>>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto __RandomInsertionPrimitiveClient <__Receiver, __Element, __Return>::insertAllOf (
    std::initializer_list <__Element> const& list
) noexcept(false) -> void {
  // call insert all of with extracted iterators
  insertAllOf (list.begin(), list.end());
}


template <typename __Receiver, typename __Element, typename __Return> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename __Iterable> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto __RandomInsertionPrimitiveClient <__Receiver, __Element, __Return>::addAllOf (
    __Iterable const& iterable
) noexcept(false) -> void {
  // call insert all of with extracted iterators
  insertAllOf (iterable.begin(), iterable.end());
}


template <typename __Receiver, typename __Element, typename __Return> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename __TElement, cds::meta::EnableIf <cds::meta::IsCopyConstructible <__TElement>::value>>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto __RandomInsertionPrimitiveClient <__Receiver, __Element, __Return>::addAllOf (
    std::initializer_list <__Element> const& list
) noexcept(false) -> void {
  // call insert all of with extracted iterators
  insertAllOf (list.begin(), list.end());
}


template <typename __Receiver, typename __Element, typename __Return> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename __Iterator> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
auto __RandomInsertionPrimitiveClient <__Receiver, __Element, __Return>::insertAllOf (
    __Iterator const& begin,
    __Iterator const& end
) noexcept(false) -> void {
  // call insert with extracted iterator values
  for (auto iterator = begin; iterator != end; ++iterator) {
    (void) insert (*iterator);
  }
}


template <typename __Receiver, typename __Element, typename __Return> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename __Iterator> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto __RandomInsertionPrimitiveClient <__Receiver, __Element, __Return>::addAllOf (
    __Iterator const& begin,
    __Iterator const& end
) noexcept(false) -> void {
  // call insertAllOf with received parameters
  return insertAllOf (begin, end);
}


template <typename __Receiver, typename __Element, typename __Return> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename __TElement, cds::meta::EnableIf <cds::meta::IsCopyConstructible <__TElement>::value>> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
auto __LocalRandomInsertionPrimitiveClient <__Receiver, __Element, __Return>::insert (
    ElementType const& element
) noexcept(false) -> ElementReference {
  // status if new element was created and construction is possible
  bool newElementCreated;
  // call receiver to acquire a new address from
  auto pElementLocation = __Receiver::__newAddress (static_cast <__Receiver*> (this), &element, &newElementCreated);

  // if no new element was created, return reference to received location
  if (!newElementCreated) {
    return *pElementLocation;
  }

  // return reference to the received address element, after in-place copy construction
  return *new (pElementLocation) __Element (element);
}


template <typename __Receiver, typename __Element, typename __Return> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename __TElement, cds::meta::EnableIf <cds::meta::IsMoveConstructible <__TElement>::value>> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
auto __LocalRandomInsertionPrimitiveClient <__Receiver, __Element, __Return>::insert (
    ElementType&& element
) noexcept(false) -> ElementReference {
  // status if new element was created and construction is possible
  bool newElementCreated;
  // call receiver to acquire a new address from
  auto pElementLocation = __Receiver::__newAddress (static_cast <__Receiver*> (this), &element, &newElementCreated);

  // if no new element was created, return reference to received location
  if (!newElementCreated) {
    return *pElementLocation;
  }

  // return reference to the received address element, after in-place move construction
  return *new (pElementLocation) __Element (std::move (element));
}


template <typename __Receiver, typename __Element, typename __Return> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename __TElement, cds::meta::EnableIf <cds::meta::IsCopyConstructible <__TElement>::value>> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto __LocalRandomInsertionPrimitiveClient <__Receiver, __Element, __Return>::add (
    ElementType const& element
) noexcept(false) -> ElementReference {
  // call insert due to deprecation
  return insert (element);
}


template <typename __Receiver, typename __Element, typename __Return> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename __TElement, cds::meta::EnableIf <cds::meta::IsMoveConstructible <__TElement>::value>> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto __LocalRandomInsertionPrimitiveClient <__Receiver, __Element, __Return>::add (
    ElementType&& element
) noexcept(false) -> ElementReference {
  // call insert due to deprecation
  return insert (std::move (element));
}


template <typename __Receiver, typename __Element, typename __Return> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename...__Arguments> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
auto __LocalRandomInsertionPrimitiveClient <__Receiver, __Element, __Return>::emplace (
    __Arguments&&... parameters
) noexcept(false) -> ElementReference {
  // prepare a memory container of the newly constructed element, to avoid destruction in out-of-stack contexts, without need
  // of dynamic allocation
  cds::__hidden::__impl::__allocation::__RawContainer <__Element> referenceElementContainer;
  // emplace-construct new element
  referenceElementContainer.construct (std::forward <__Arguments> (parameters)...);

  try {
    // status if new element was created and construction is possible
    bool        newElementCreated;
    // call receiver to acquire a new address from
    auto  const pElementLocation = __Receiver::__newAddress (static_cast <__Receiver*> (this), &referenceElementContainer.data(), &newElementCreated);

    if (!newElementCreated) {
      // if no new element was created, destruct the created element
      referenceElementContainer.destruct();
    } else {
      // otherwise, copy created data to the received memory address
      (void) std::memcpy (
          static_cast <void*> (pElementLocation),
          static_cast <void const*> (&referenceElementContainer._data[0]),
          sizeof (__Element)
      );
    }

    // either way, return reference to received address
    return *pElementLocation;
  } catch (...) {
    // in the case the call throws, destruct allocated data and throw the exception further in the stack
    referenceElementContainer.destruct();
    throw;
  }
}


template <typename __Receiver, typename __Element, typename __Return> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename...__Arguments> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto __LocalRandomInsertionPrimitiveClient <__Receiver, __Element, __Return>::insertAll (
    __Arguments&& ... values
) noexcept(false) -> void {
  // call expansive insert with the received forwarding references on this object as the accumulator
  __expansiveInsert (this, std::forward <__Arguments> (values)...);
}


template <typename __Receiver, typename __Element, typename __Return> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename...__Arguments> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto __LocalRandomInsertionPrimitiveClient <__Receiver, __Element, __Return>::addAll (
    __Arguments&&... values
) noexcept(false) -> void {
  // call expansive insert with the received forwarding references on this object as the accumulator
  __expansiveInsert (this, std::forward <__Arguments> (values)...);
}


template <typename __Receiver, typename __Element, typename __Return> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename __Iterable> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto __LocalRandomInsertionPrimitiveClient <__Receiver, __Element, __Return>::insertAllOf (
    __Iterable const& iterable
) noexcept(false) -> void {
  // call insert all of with extracted iterators
  insertAllOf (iterable.begin(), iterable.end());
}


template <typename __Receiver, typename __Element, typename __Return> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename __TElement, cds::meta::EnableIf <cds::meta::IsCopyConstructible <__TElement>::value>>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto __LocalRandomInsertionPrimitiveClient <__Receiver, __Element, __Return>::insertAllOf (
    std::initializer_list <__Element> const& list
) noexcept(false) -> void {
  // call insert all of with extracted iterators
  insertAllOf (list.begin(), list.end());
}


template <typename __Receiver, typename __Element, typename __Return> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename __Iterable> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto __LocalRandomInsertionPrimitiveClient <__Receiver, __Element, __Return>::addAllOf (
    __Iterable const& iterable
) noexcept(false) -> void {
  // call insert all of with extracted iterators
  insertAllOf (iterable.begin(), iterable.end());
}


template <typename __Receiver, typename __Element, typename __Return> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename __TElement, cds::meta::EnableIf <cds::meta::IsCopyConstructible <__TElement>::value>>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto __LocalRandomInsertionPrimitiveClient <__Receiver, __Element, __Return>::addAllOf (
    std::initializer_list <__Element> const& list
) noexcept(false) -> void {
  // call insert all of with extracted iterators
  insertAllOf (list.begin(), list.end());
}


template <typename __Receiver, typename __Element, typename __Return> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename __Iterator> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
auto __LocalRandomInsertionPrimitiveClient <__Receiver, __Element, __Return>::insertAllOf (
    __Iterator const& begin,
    __Iterator const& end
) noexcept (false) -> void {
  // call insert with extracted iterator values
  for (auto iterator = begin; iterator != end; ++iterator) {
    (void) insert (*iterator);
  }
}


template <typename __Receiver, typename __Element, typename __Return> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename __Iterator> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto __LocalRandomInsertionPrimitiveClient <__Receiver, __Element, __Return>::addAllOf (
    __Iterator const& begin,
    __Iterator const& end
) noexcept(false) -> void {
  // call insertAllOf with received parameters
  return insertAllOf (begin, end);
}
} // namespace __impl
} // namespace __hidden
} // namespace cds

#endif // __CDS_SHARED_RANDOM_INSERTION_PRIMITIVE_CLIENT_IMPL_HPP__
