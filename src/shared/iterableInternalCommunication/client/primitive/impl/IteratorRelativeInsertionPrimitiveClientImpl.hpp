//
// Created by loghin on 6/28/22.
//

#ifndef __CDS_SHARED_ITERATOR_RELATIVE_INSERTION_PRIMITIVE_CLIENT_IMPL_HPP__ // NOLINT(llvm-header-guard) 
#define __CDS_SHARED_ITERATOR_RELATIVE_INSERTION_PRIMITIVE_CLIENT_IMPL_HPP__ // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
#pragma once

#include "../../../../iterator/IteratorDistance.hpp"

namespace cds {       // NOLINT(modernize-concat-nested-namespaces)
namespace __hidden {  // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
namespace __impl {    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename __Receiver, typename __Element> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename __TElement, cds::meta::EnableIf <cds::meta::IsCopyConstructible <__TElement>::value>> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
__CDS_OptimalInline auto __AbstractIteratorRelativeInsertionPrimitiveClient <__Receiver, __Element>::insertBefore (
    AbstractIterator const& iterator,
    ElementType const&      element
) noexcept(false) -> bool {
  // Invoke the copy constructor via front emplacement 
  return this->emplaceBefore (iterator, element);
}


template <typename __Receiver, typename __Element> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename __TElement, cds::meta::EnableIf <cds::meta::IsMoveConstructible <__TElement>::value>> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
__CDS_OptimalInline auto __AbstractIteratorRelativeInsertionPrimitiveClient <__Receiver, __Element>::insertBefore (
    AbstractIterator const& iterator,
    ElementType&&           element
) noexcept(false) -> bool {
  // Invoke the move constructor via front emplacement 
  return this->emplaceBefore (iterator, std::move (element));
}


template <typename __Receiver, typename __Element> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename __TElement, cds::meta::EnableIf <cds::meta::IsCopyConstructible <__TElement>::value>> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
__CDS_OptimalInline auto __AbstractIteratorRelativeInsertionPrimitiveClient <__Receiver, __Element>::insertAfter (
    AbstractIterator const& iterator,
    ElementType const&      element
) noexcept(false) -> bool {
  // Invoke the copy constructor via back emplacement 
  return this->emplaceAfter (iterator, element);
}


template <typename __Receiver, typename __Element> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename __TElement, cds::meta::EnableIf <cds::meta::IsMoveConstructible <__TElement>::value>> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
__CDS_OptimalInline auto __AbstractIteratorRelativeInsertionPrimitiveClient <__Receiver, __Element>::insertAfter (
    AbstractIterator const& iterator,
    ElementType&&           element
) noexcept(false) -> bool {
  // Invoke the move constructor via back emplacement 
  return this->emplaceAfter (iterator, std::move (element)); 
}


template <typename __Receiver, typename __Element> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename...__Arguments> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
auto __AbstractIteratorRelativeInsertionPrimitiveClient <__Receiver, __Element>::emplaceBefore (
    AbstractIterator const& iterator,
    __Arguments&&...        parameters
) noexcept(false) -> bool {
  // Handle type of the new before address function 
  using __ReceiverNewBeforeHandlerType    = cds::functional::MapperFunction <__Element*, __Receiver*, cds::meta::Iterator const*>; // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  // Caller object reinterpreted as receiver of the request 
  auto pReceiver                          = static_cast <__Receiver*> (this);

  // If iterator invalid, cannot emplace before it 
  if (!iterator.of (pReceiver) || !static_cast <bool> (iterator)) {
    return false;
  }

  // Create the request for a new before address handler and call it 
  auto const pNewLocation = bitCast <__ReceiverNewBeforeHandlerType> (pReceiver->__iicch_obtainGenericHandler (__IterableInternalRequest::__iir_newBeforeAddress)) (
      pReceiver, iterator._pDelegate->iterator()
  );

  // If no address received, insertion not possible 
  if (pNewLocation == nullptr) {
    return false;
  }

  // Otherwise, use placement new for creation 
  (void) new (pNewLocation) __Element (std::forward <__Arguments> (parameters)...);

  // Successful Result 
  return true;
}


template <typename __Receiver, typename __Element> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename...__Arguments> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
auto __AbstractIteratorRelativeInsertionPrimitiveClient <__Receiver, __Element>::emplaceAfter (
    AbstractIterator const& iterator,
    __Arguments&&...        parameters
) noexcept(false) -> bool {
  // Handle type of the new after address function 
  using __ReceiverNewAfterHandlerType = cds::functional::MapperFunction <__Element*, __Receiver*, cds::meta::Iterator const*>; // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  // Caller object reinterpreted as receiver of the request 
  auto pReceiver                      = static_cast <__Receiver*> (this);

  // If iterator invalid, cannot emplace after it 
  if (!iterator.of (pReceiver) || !static_cast <bool> (iterator)) {
    return false;
  }

  // Create the request for a new after address handler and call it 
  auto const pNewLocation = bitCast <__ReceiverNewAfterHandlerType> (pReceiver->__iicch_obtainGenericHandler (__IterableInternalRequest::__iir_newAfterAddress)) (
      pReceiver, iterator._pDelegate->iterator()
  );

  // If no address received, insertion not possible 
  if (pNewLocation == nullptr) {
    return false;
  }

  // Otherwise, use placement new for creation 
  (void) new (pNewLocation) __Element (std::forward <__Arguments> (parameters)...);

  // Successful Result 
  return true;
}


template <typename __Receiver, typename __Element> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename...__Arguments> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
auto __AbstractIteratorRelativeInsertionPrimitiveClient <__Receiver, __Element>::insertAllBefore (
    AbstractIterator const& iterator,
    __Arguments&&...        values
) noexcept(false) -> bool {
  using __Alloc                               = __hidden::__impl::__allocation::__PrimitiveAlloc <__Element*>;  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  // Handle type of the new before address function 
  using __ReceiverNewBeforeArrayHandlerType   = cds::functional::PredicateFunction <__Receiver*, cds::meta::Iterator const*, Size, __Element**>; // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  // Caller object reinterpreted as receiver of the request 
  auto pReceiver                              = static_cast <__Receiver*> (this);

  // If iterator invalid, cannot emplace before it 
  if (!iterator.of (pReceiver) || !static_cast <bool> (iterator)) {
    return false;
  }

  // The number of received values is the numbers of elements to be created 
  Size  const parameterCount  = sizeof...(__Arguments);
  // Allocate the buffer to store the addresses of the newly created memory spaces for the elements 
  auto        ppElements      = __Alloc::__alloc (parameterCount);

  try {
    // Request and call handler for a new before address array with the created buffer
    auto const allocationStatus = bitCast <__ReceiverNewBeforeArrayHandlerType> (pReceiver->__iicch_obtainGenericHandler (__IterableInternalRequest::__iir_newBeforeAddressArray)) (
        pReceiver, iterator._pDelegate->iterator(), parameterCount, ppElements
    );

    // If status OK, initialize received memory with received values
    if (allocationStatus) {
      cds::__hidden::__impl::__allocation::__forwardIntoArray (ppElements, std::forward <__Arguments> (values)...);
    }

    // Free temporary buffer and return status
    __Alloc::__free (ppElements);
    return allocationStatus;
  } catch (...) {
    __Alloc::__free (ppElements);
    throw;
  }
}


template <typename __Receiver, typename __Element> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename...__Arguments> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
auto __AbstractIteratorRelativeInsertionPrimitiveClient <__Receiver, __Element>::insertAllAfter (
    AbstractIterator const& iterator,
    __Arguments&&...        values
) noexcept(false) -> bool {
  using __Alloc                               = __hidden::__impl::__allocation::__PrimitiveAlloc <__Element*>;  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  // Handle type of the new after address function 
  using __ReceiverNewAfterArrayHandlerType    = cds::functional::PredicateFunction <__Receiver*, cds::meta::Iterator const*, Size, __Element**>; // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  // Caller object reinterpreted as receiver of the request 
  auto pReceiver                              = static_cast <__Receiver*> (this);

  // If iterator invalid, cannot emplace after it 
  if (!iterator.of (pReceiver) || !static_cast <bool> (iterator)) {
    return false;
  }

  // The number of received values is the numbers of elements to be created 
  Size  const parameterCount  = sizeof...(__Arguments);
  // Allocate the buffer to store the addresses of the newly created memory spaces for the elements 
  auto        ppElements      = __Alloc::__alloc (parameterCount);

  try {
    // Request and call handler for a new after address array with the created buffer
    auto const allocationStatus = bitCast <__ReceiverNewAfterArrayHandlerType> (pReceiver->__iicch_obtainGenericHandler (__IterableInternalRequest::__iir_newAfterAddressArray)) (
        pReceiver, iterator._pDelegate->iterator(), parameterCount, ppElements
    );

    // If status OK, initialize received memory with received values
    if (allocationStatus) {
      cds::__hidden::__impl::__allocation::__forwardIntoArray (ppElements, std::forward <__Arguments> (values)...);
    }

    // Free temporary buffer and return status
    __Alloc::__free (ppElements);
    return allocationStatus;
  } catch (...) {
    __Alloc::__free (ppElements);
    throw;
  }
}


template <typename __Receiver, typename __Element> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename __Iterable, cds::meta::EnableIf <meta::__IterableSizeAvailable < __Iterable >::value>>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
__CDS_OptimalInline auto __AbstractIteratorRelativeInsertionPrimitiveClient <__Receiver, __Element>::insertAllOfBefore (
    AbstractIterator const& iterator,
    __Iterable const&       iterable
) noexcept(false) -> bool {
  // Variant with RandomAccessIterator - 'operator -'. Call insertAllOfBefore with size 
  return this->insertAllOfBefore (iterator, iterable.begin(), iterable.end(), iterable.size());
}


template <typename __Receiver, typename __Element> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename __Iterable, cds::meta::EnableIf <!meta::__IterableSizeAvailable < __Iterable >::value>> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
__CDS_OptimalInline auto __AbstractIteratorRelativeInsertionPrimitiveClient <__Receiver, __Element>::insertAllOfBefore (
    AbstractIterator const& iterator,
    __Iterable const&       iterable
) noexcept(false) -> bool {
  // Variant without RandomAccessIterator - 'operator -'. Call insertAllOfBefore without size, letting
  // the function compute the distance between start and end
  return this->insertAllOfBefore (iterator, iterable.begin(), iterable.end());
}


template <typename __Receiver, typename __Element> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename __TElement, cds::meta::EnableIf <cds::meta::IsCopyConstructible <__TElement>::value>> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
__CDS_OptimalInline auto __AbstractIteratorRelativeInsertionPrimitiveClient <__Receiver, __Element>::insertAllOfBefore (
    AbstractIterator const&                   iterator,
    std::initializer_list <__Element> const&  list
) noexcept(false) -> bool {
  // initializer_list has RandomAccessIterator - 'operator -'. Call insertAllOfBefore with size 
  return this->insertAllOfBefore (iterator, list.begin(), list.end(), list.size());
}


template <typename __Receiver, typename __Element> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename __Iterable, cds::meta::EnableIf <meta::__IterableSizeAvailable < __Iterable >::value>>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
__CDS_OptimalInline auto __AbstractIteratorRelativeInsertionPrimitiveClient <__Receiver, __Element>::insertAllOfAfter (
    AbstractIterator const& iterator,
    __Iterable const&       iterable
) noexcept(false) -> bool {
  // Variant with RandomAccessIterator - 'operator -'. Call insertAllOfAfter with size 
  return this->insertAllOfAfter (iterator, iterable.begin(), iterable.end(), iterable.size());
}


template <typename __Receiver, typename __Element> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename __Iterable, cds::meta::EnableIf <!meta::__IterableSizeAvailable < __Iterable >::value>> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
__CDS_OptimalInline auto __AbstractIteratorRelativeInsertionPrimitiveClient <__Receiver, __Element>::insertAllOfAfter (
    AbstractIterator const& iterator,
    __Iterable const&       iterable
) noexcept(false) -> bool {
  // Variant without RandomAccessIterator - 'operator -'. Call insertAllOfAfter without size, letting
  // the function compute the distance between start and end
  return this->insertAllOfAfter (iterator, iterable.begin(), iterable.end());
}


template <typename __Receiver, typename __Element> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename __TElement, cds::meta::EnableIf <cds::meta::IsCopyConstructible <__TElement>::value>> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
__CDS_OptimalInline auto __AbstractIteratorRelativeInsertionPrimitiveClient <__Receiver, __Element>::insertAllOfAfter (
    AbstractIterator const&                   iterator,
    std::initializer_list <__Element> const&  list
) noexcept(false) -> bool {
  // initializer_list has RandomAccessIterator - 'operator -'. Call insertAllOfAfter with size 
  return this->insertAllOfAfter (iterator, list.begin(), list.end(), list.size());
}


template <typename __Receiver, typename __Element> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename __Iterator> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
auto __AbstractIteratorRelativeInsertionPrimitiveClient <__Receiver, __Element>::insertAllOfBefore (
    AbstractIterator const& iterator,
    __Iterator const&       begin,
    __Iterator const&       end,
    Size                    count
) noexcept(false) -> bool {
  using __Alloc                               = __hidden::__impl::__allocation::__PrimitiveAlloc <__Element*>;  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  // Handle type of the new before address function 
  using __ReceiverNewBeforeArrayHandlerType   = cds::functional::PredicateFunction <__Receiver*, cds::meta::Iterator const*, Size, __Element**>; // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  // Caller object reinterpreted as receiver of the request 
  auto pReceiver                              = static_cast <__Receiver*> (this);

  // If iterator invalid, cannot emplace before it 
  if (!iterator.of (pReceiver) || !static_cast <bool> (iterator)) {
    return false;
  }

  // The number of received values is the numbers of elements to be created. If 0, compute 
  Size  const parameterCount  = count == 0u ? __IteratorDistance <__Iterator>::__compute (begin, end) : count;
  // Allocate the buffer to store the addresses of the newly created memory spaces for the elements 
  auto        ppElements      = __Alloc::__alloc (parameterCount);

  try {
    // Request and call handler for a new before address array with the created buffer
    auto const allocationStatus = bitCast <__ReceiverNewBeforeArrayHandlerType> (pReceiver->__iicch_obtainGenericHandler (__IterableInternalRequest::__iir_newBeforeAddressArray)) (
        pReceiver, iterator._pDelegate->iterator(), parameterCount, ppElements
    );

    // If status OK, Parse iterator range and call placement new operator at received memory with
    // each iterator's value
    if (allocationStatus) {
      Size index = 0u;
      for (auto lIterator = begin; lIterator != end; ++lIterator) {
        (void) new (ppElements [index++]) __Element (*lIterator);
      }
    }

    // Free temporary buffer and return status
    __Alloc::__free (ppElements);
    return allocationStatus;
  } catch(...) {
    __Alloc::__free (ppElements);
    throw;
  }
}


template <typename __Receiver, typename __Element> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename __Iterator> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
auto __AbstractIteratorRelativeInsertionPrimitiveClient <__Receiver, __Element>::insertAllOfAfter (
    AbstractIterator const& iterator,
    __Iterator const&       begin,
    __Iterator const&       end,
    Size                    count
) noexcept(false) -> bool {
  using __Alloc                               = __hidden::__impl::__allocation::__PrimitiveAlloc <__Element*>;  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  // Handle type of the new after address function 
  using __ReceiverNewAfterArrayHandlerType    = cds::functional::PredicateFunction <__Receiver*, cds::meta::Iterator const*, Size, __Element**>; // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  // Caller object reinterpreted as receiver of the request 
  auto pReceiver                              = static_cast <__Receiver*> (this);

  // If iterator invalid, cannot emplace before it 
  if (!iterator.of (pReceiver) || !static_cast <bool> (iterator)) {
    return false;
  }

  // The number of received values is the numbers of elements to be created. If 0, compute 
  Size  const parameterCount  = count == 0u ? __IteratorDistance <__Iterator>::__compute (begin, end) : count;
  // Allocate the buffer to store the addresses of the newly created memory spaces for the elements 
  auto        ppElements      = __Alloc::__alloc (parameterCount);

  try {
    // Request and call handler for a new after address array with the created buffer
    auto const allocationStatus = bitCast <__ReceiverNewAfterArrayHandlerType> (pReceiver->__iicch_obtainGenericHandler (__IterableInternalRequest::__iir_newAfterAddressArray)) (
        pReceiver, iterator._pDelegate->iterator(), parameterCount, ppElements
    );

    // If status OK, Parse iterator range and call placement new operator at received memory with
    // each iterator's value
    if (allocationStatus) {
      Size index = 0u;
      for (auto lIterator = begin; lIterator != end; ++lIterator) {
        (void) new (ppElements [index++]) __Element (*lIterator);
      }
    }

    // Free temporary buffer and return status
    __Alloc::__free (ppElements);
    return allocationStatus;
  } catch(...) {
    __Alloc::__free (ppElements);
    throw;
  }
}


template <typename __Receiver, typename __Element, typename __Iterator> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
template <typename __TElement, cds::meta::EnableIf <cds::meta::IsCopyConstructible <__TElement>::value>> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
__CDS_OptimalInline auto __LocalIteratorRelativeInsertionPrimitiveClient <__Receiver, __Element, __Iterator>::insertBefore (
    Iterator const&     iterator,
    ElementType const&  element
) noexcept(false) -> bool {
  // Invoke the copy constructor via front emplacement 
  return this->emplaceBefore (iterator, element);
}


template <typename __Receiver, typename __Element, typename __Iterator> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
template <typename __TElement, cds::meta::EnableIf <cds::meta::IsMoveConstructible <__TElement>::value>> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
__CDS_OptimalInline auto __LocalIteratorRelativeInsertionPrimitiveClient <__Receiver, __Element, __Iterator>::insertBefore (
    Iterator const& iterator,
    ElementType&&   element
) noexcept(false) -> bool {
  // Invoke the move constructor via front emplacement 
  return this->emplaceBefore (iterator, std::move (element));
}


template <typename __Receiver, typename __Element, typename __Iterator> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
template <typename __TElement, cds::meta::EnableIf <cds::meta::IsCopyConstructible <__TElement>::value>> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
__CDS_OptimalInline auto __LocalIteratorRelativeInsertionPrimitiveClient <__Receiver, __Element, __Iterator>::insertAfter (
    Iterator const&     iterator,
    ElementType const&  element
) noexcept(false) -> bool {
  // Invoke the copy constructor via back emplacement 
  return this->emplaceAfter (iterator, element);
}


template <typename __Receiver, typename __Element, typename __Iterator> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
template <typename __TElement, cds::meta::EnableIf <cds::meta::IsMoveConstructible <__TElement>::value>> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
__CDS_OptimalInline auto __LocalIteratorRelativeInsertionPrimitiveClient <__Receiver, __Element, __Iterator>::insertAfter (
    Iterator const& iterator,
    ElementType&&   element
) noexcept(false) -> bool {
  // Invoke the move constructor via back emplacement 
  return this->emplaceAfter (iterator, std::move (element));
}


template <typename __Receiver, typename __Element, typename __Iterator> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
template <typename...__Arguments> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
auto __LocalIteratorRelativeInsertionPrimitiveClient <__Receiver, __Element, __Iterator>::emplaceBefore (
    Iterator const&   iterator,
    __Arguments&&...  parameters
) noexcept(false) -> bool {
  // If iterator invalid, cannot emplace before it 
  if (!static_cast <bool> (iterator)) {
    return false;
  }

  // Call dispatcher local new before address handler 
  auto const pNewLocation = __Receiver::__newBefore (static_cast <__Receiver*> (this), &iterator);

  // If no address received, insertion not possible 
  if (pNewLocation == nullptr) {
    return false;
  }

  // Otherwise, use placement new for creation 
  (void) new (pNewLocation) __Element (std::forward <__Arguments> (parameters)...);

  // Successful Result 
  return true;
}


template <typename __Receiver, typename __Element, typename __Iterator> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
template <typename...__Arguments> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
auto __LocalIteratorRelativeInsertionPrimitiveClient <__Receiver, __Element, __Iterator>::emplaceAfter (
    Iterator const&   iterator,
    __Arguments&&...  parameters
) noexcept(false) -> bool {
  // If iterator invalid, cannot emplace after it 
  if (!static_cast <bool> (iterator)) {
    return false;
  }

  // Call dispatcher local new after address handler 
  auto const pNewLocation = __Receiver::__newAfter (static_cast <__Receiver*> (this), &iterator);

  // If no address received, insertion not possible 
  if (pNewLocation == nullptr) {
    return false;
  }

  // Otherwise, use placement new for creation 
  (void) new (pNewLocation) __Element (std::forward <__Arguments> (parameters)...);

  // Successful Result 
  return true;
}


template <typename __Receiver, typename __Element, typename __Iterator> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
template <typename...__Arguments> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
auto __LocalIteratorRelativeInsertionPrimitiveClient <__Receiver, __Element, __Iterator>::insertAllBefore (
    Iterator const&   iterator,
    __Arguments&&...  values
) noexcept(false) -> bool {
  using __Alloc = __hidden::__impl::__allocation::__PrimitiveAlloc <__Element*>;  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

  // If iterator invalid, cannot emplace before it 
  if (!static_cast <bool> (iterator)) {
    return false;
  }

  // The number of received values is the numbers of elements to be created 
  Size  const parameterCount  = sizeof...(__Arguments);
  // Allocate the buffer to store the addresses of the newly created memory spaces for the elements 
  auto        ppElements      = __Alloc::__alloc (parameterCount);

  try {
    // Call dispatcher local new before address array handler
    auto const allocationStatus = __Receiver::__newBeforeArray (static_cast <__Receiver*> (this), &iterator, parameterCount, ppElements);

    // If status OK, initialize received memory with received values
    if (allocationStatus) {
      cds::__hidden::__impl::__allocation::__forwardIntoArray (ppElements, std::forward <__Arguments> (values)...);
    }

    // Free temporary buffer and return status
    __Alloc::__free (ppElements);
    return allocationStatus;
  } catch (...) {
    __Alloc::__free (ppElements);
    throw;
  }
}


template <typename __Receiver, typename __Element, typename __Iterator> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
template <typename...__Arguments> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
auto __LocalIteratorRelativeInsertionPrimitiveClient <__Receiver, __Element, __Iterator>::insertAllAfter (
    Iterator const&   iterator,
    __Arguments&&...  values
) noexcept(false) -> bool {
  using __Alloc = __hidden::__impl::__allocation::__PrimitiveAlloc <__Element*>;  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

  // If iterator invalid, cannot emplace after it 
  if (!static_cast <bool> (iterator)) {
    return false;
  }

  // The number of received values is the numbers of elements to be created 
  Size  const parameterCount  = sizeof...(__Arguments);
  // Allocate the buffer to store the addresses of the newly created memory spaces for the elements 
  auto        ppElements      = __Alloc::__alloc (parameterCount);

  try {
    // Call dispatcher local new after address array handler
    auto const allocationStatus = __Receiver::__newAfterArray (static_cast <__Receiver*> (this), &iterator, parameterCount, ppElements);

    // If status OK, initialize received memory with received values
    if (allocationStatus) {
      cds::__hidden::__impl::__allocation::__forwardIntoArray (ppElements, std::forward <__Arguments> (values)...);
    }

    // Free temporary buffer and return status
    __Alloc::__free (ppElements);
    return allocationStatus;
  } catch (...) {
    __Alloc::__free (ppElements);
    throw;
  }
}


template <typename __Receiver, typename __Element, typename __Iterator> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
template <typename __Iterable, cds::meta::EnableIf <meta::__IterableSizeAvailable < __Iterable >::value>>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
__CDS_OptimalInline auto __LocalIteratorRelativeInsertionPrimitiveClient <__Receiver, __Element, __Iterator>::insertAllOfBefore (
    Iterator const&   iterator,
    __Iterable const& iterable
) noexcept(false) -> bool {
  // Variant with RandomAccessIterator - 'operator -'. Call insertAllOfBefore with size 
  return this->insertAllOfBefore (iterator, iterable.begin(), iterable.end(), iterable.size());
}


template <typename __Receiver, typename __Element, typename __Iterator> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
template <typename __Iterable, cds::meta::EnableIf <!meta::__IterableSizeAvailable < __Iterable >::value>> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
__CDS_OptimalInline auto __LocalIteratorRelativeInsertionPrimitiveClient <__Receiver, __Element, __Iterator>::insertAllOfBefore (
    Iterator const&   iterator,
    __Iterable const& iterable
) noexcept(false) -> bool {
  // Variant without RandomAccessIterator - 'operator -'. Call insertAllOfBefore without size, letting
  // the function compute the distance between start and end
  return this->insertAllOfBefore (iterator, iterable.begin(), iterable.end());
}


template <typename __Receiver, typename __Element, typename __Iterator> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
template <typename __TElement, cds::meta::EnableIf <cds::meta::IsCopyConstructible <__TElement>::value>> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
__CDS_OptimalInline auto __LocalIteratorRelativeInsertionPrimitiveClient <__Receiver, __Element, __Iterator>::insertAllOfBefore (
    Iterator const&                           iterator,
    std::initializer_list <__Element> const&  list
) noexcept(false) -> bool {
  // initializer_list has RandomAccessIterator - 'operator -'. Call insertAllOfBefore with size 
  return this->insertAllOfBefore (iterator, list.begin(), list.end(), list.size());
}


template <typename __Receiver, typename __Element, typename __Iterator> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
template <typename __Iterable, cds::meta::EnableIf <meta::__IterableSizeAvailable < __Iterable >::value>>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
__CDS_OptimalInline auto __LocalIteratorRelativeInsertionPrimitiveClient <__Receiver, __Element, __Iterator>::insertAllOfAfter (
    Iterator const&   iterator,
    __Iterable const& iterable
) noexcept(false) -> bool {
  // Variant with RandomAccessIterator - 'operator -'. Call insertAllOfAfter with size 
  return this->insertAllOfAfter (iterator, iterable.begin(), iterable.end(), iterable.size());
}


template <typename __Receiver, typename __Element, typename __Iterator> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
template <typename __Iterable, cds::meta::EnableIf <!meta::__IterableSizeAvailable < __Iterable >::value>> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
__CDS_OptimalInline auto __LocalIteratorRelativeInsertionPrimitiveClient <__Receiver, __Element, __Iterator>::insertAllOfAfter (
    Iterator const&   iterator,
    __Iterable const& iterable
) noexcept(false) -> bool {
  // Variant without RandomAccessIterator - 'operator -'. Call insertAllOfAfter without size, letting
  // the function compute the distance between start and end
  return this->insertAllOfAfter (iterator, iterable.begin(), iterable.end());
}


template <typename __Receiver, typename __Element, typename __Iterator> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
template <typename __TElement, cds::meta::EnableIf <cds::meta::IsCopyConstructible <__TElement>::value>> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
__CDS_OptimalInline auto __LocalIteratorRelativeInsertionPrimitiveClient <__Receiver, __Element, __Iterator>::insertAllOfAfter (
    Iterator const&                           iterator,
    std::initializer_list <__Element> const&  list
) noexcept(false) -> bool {
  // initializer_list has RandomAccessIterator - 'operator -'. Call insertAllOfAfter with size 
  return this->insertAllOfAfter (iterator, list.begin(), list.end(), list.size());
}


template <typename __Receiver, typename __Element, typename __LocalClientIterator>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
template <typename __Iterator> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
auto __LocalIteratorRelativeInsertionPrimitiveClient <__Receiver, __Element, __LocalClientIterator>::insertAllOfBefore (
    Iterator const&   iterator,
    __Iterator const& begin,
    __Iterator const& end,
    Size              count
) noexcept(false) -> bool {
  using __Alloc = __hidden::__impl::__allocation::__PrimitiveAlloc <__Element*>;  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  
  // If iterator invalid, cannot emplace before it 
  if (!static_cast <bool> (iterator)) {
    return false;
  }

  // The number of received values is the numbers of elements to be created. If 0, compute 
  Size  const parameterCount  = count == 0u ? __IteratorDistance <__Iterator>::__compute (begin, end) : count;
  // Allocate the buffer to store the addresses of the newly created memory spaces for the elements 
  auto        ppElements      = __Alloc::__alloc (parameterCount);

  try {
    // Call dispatcher local new before address array handler
    auto const allocationStatus = __Receiver::__newBeforeArray (static_cast <__Receiver*> (this), &iterator, parameterCount, ppElements);

    // If status OK, Parse iterator range and call placement new operator at received memory with
    // each iterator's value
    if (allocationStatus) {
      Size index = 0u;
      for (auto lIterator = begin; lIterator != end; ++lIterator) {
        (void) new (ppElements [index++]) __Element (*lIterator);
      }
    }

    // Free temporary buffer and return status
    __Alloc::__free (ppElements);
    return allocationStatus;
  } catch (...) {
    __Alloc::__free (ppElements);
    throw;
  }
}


template <typename __Receiver, typename __Element, typename __LocalClientIterator>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
template <typename __Iterator> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
auto __LocalIteratorRelativeInsertionPrimitiveClient <__Receiver, __Element, __LocalClientIterator>::insertAllOfAfter (
    Iterator const&   iterator,
    __Iterator const& begin,
    __Iterator const& end,
    Size              count
) noexcept(false) -> bool {
  using __Alloc = __hidden::__impl::__allocation::__PrimitiveAlloc <__Element*>;  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

  // If iterator invalid, cannot emplace before it 
  if (!static_cast <bool> (iterator)) {
    return false;
  }

  // The number of received values is the numbers of elements to be created. If 0, compute 
  Size  const parameterCount  = count == 0u ? __IteratorDistance <__Iterator>::__compute (begin, end) : count;
  // Allocate the buffer to store the addresses of the newly created memory spaces for the elements 
  auto        ppElements      = __Alloc::__alloc (parameterCount);

  try {
    // Call dispatcher local new after address array handler
    auto const allocationStatus = __Receiver::__newAfterArray (static_cast <__Receiver*> (this), &iterator, parameterCount, ppElements);

    // If status OK, Parse iterator range and call placement new operator at received memory with
    // each iterator's value
    if (allocationStatus) {
      Size index = 0u;
      for (auto lIterator = begin; lIterator != end; ++lIterator) {
        (void) new (ppElements [index++]) __Element (*lIterator);
      }
    }

    // Free temporary buffer and return status
    __Alloc::__free (ppElements);
    return allocationStatus;
  } catch (...) {
    __Alloc::__free (ppElements);
    throw;
  }
}
} // namespace __impl 
} // namespace __hidden 
} // namespace cds 

#endif // __CDS_SHARED_ITERATOR_RELATIVE_INSERTION_PRIMITIVE_CLIENT_IMPL_HPP__ 
