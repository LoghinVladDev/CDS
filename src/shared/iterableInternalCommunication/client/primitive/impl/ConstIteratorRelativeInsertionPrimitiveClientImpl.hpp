//
// Created by loghin on 6/28/22.
//

#ifndef __CDS_SHARED_CONST_ITERATOR_RELATIVE_INSERTION_PRIMITIVE_CLIENT_IMPL_HPP__ // NOLINT(llvm-header-guard) 
#define __CDS_SHARED_CONST_ITERATOR_RELATIVE_INSERTION_PRIMITIVE_CLIENT_IMPL_HPP__ // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
#pragma once

#include "../../../../iterator/IteratorDistance.hpp"

namespace cds {       // NOLINT(modernize-concat-nested-namespaces) 
namespace __hidden {  // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
namespace __impl {    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename __Receiver, typename __Element>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
template <
    typename __TElementType,    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
    cds::meta::EnableIf <cds::meta::IsCopyConstructible <__TElementType>::value>
> __CDS_OptimalInline auto __AbstractConstIteratorRelativeInsertionPrimitiveClient <__Receiver, __Element>::insertBefore (
    AbstractConstIterator const&  iterator,
    ElementType const&            element
) noexcept(false) -> bool {
  // Invoke the copy constructor via front emplacement 
  return emplaceBefore (iterator, element);
}


template <typename __Receiver, typename __Element>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
template <
    typename __TElementType,    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
    cds::meta::EnableIf <cds::meta::IsMoveConstructible <__TElementType>::value>
> __CDS_OptimalInline auto __AbstractConstIteratorRelativeInsertionPrimitiveClient <__Receiver, __Element>::insertBefore (
    AbstractConstIterator const&  iterator,
    ElementType&&                 element
) noexcept(false) -> bool {
  // Invoke the move constructor via front emplacement 
  return emplaceBefore (iterator, std::move (element));
}


template <typename __Receiver, typename __Element>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
template <
    typename __TElementType,    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
    cds::meta::EnableIf <cds::meta::IsCopyConstructible <__TElementType>::value>
> __CDS_OptimalInline auto __AbstractConstIteratorRelativeInsertionPrimitiveClient <__Receiver, __Element>::insertAfter (
    AbstractConstIterator const&  iterator,
    ElementType const&            element
) noexcept(false) -> bool {
  // Invoke the copy constructor via back emplacement 
  return emplaceAfter (iterator, element);
}


template <typename __Receiver, typename __Element>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
template <
    typename __TElementType,    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
    cds::meta::EnableIf <cds::meta::IsMoveConstructible <__TElementType>::value>
> __CDS_OptimalInline auto __AbstractConstIteratorRelativeInsertionPrimitiveClient <__Receiver, __Element>::insertAfter (
    AbstractConstIterator const&  iterator,
    ElementType &&                element
) noexcept(false) -> bool {
  // Invoke the move constructor via back emplacement 
  return emplaceAfter (iterator, std::move (element));
}


template <typename __Receiver, typename __Element>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
template <typename...__Arguments> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
auto __AbstractConstIteratorRelativeInsertionPrimitiveClient <__Receiver, __Element>::emplaceBefore (
    AbstractConstIterator const&  iterator,
    __Arguments&&...              parameters
) noexcept(false) -> bool {
  // Handle type of the new before address function 
  using __ReceiverNewBeforeConstHandlerType   = cds::functional::MapperFunction <__Element*, __Receiver*, cds::meta::Iterator const*>; // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  // Caller object reinterpreted as receiver of the request 
  auto pReceiver                              = static_cast <__Receiver*> (this);

  // If iterator invalid, cannot emplace before it 
  if (!iterator.of (pReceiver) || !static_cast <bool> (iterator)) {
    return false;
  }

  // Create the request for a new before address handler and call it 
  auto const pNewLocation = bitCast <__ReceiverNewBeforeConstHandlerType> (pReceiver->__iicch_obtainGenericHandler (__IterableInternalRequest::__iir_newBeforeAddressConst)) (
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


template <typename __Receiver, typename __Element>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
template <typename...__Arguments> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
auto __AbstractConstIteratorRelativeInsertionPrimitiveClient <__Receiver, __Element>::emplaceAfter (
    AbstractConstIterator const&  iterator,
    __Arguments&&...              parameters
) noexcept(false) -> bool {
  // Handle type of the new after address function 
  using __ReceiverNewAfterConstHandlerType    = cds::functional::MapperFunction <__Element*, __Receiver*, cds::meta::Iterator const*>; // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  // Caller object reinterpreted as receiver of the request 
  auto pReceiver                              = static_cast <__Receiver*> (this);

  // If iterator invalid, cannot emplace after it 
  if (!iterator.of (pReceiver) || !static_cast <bool> (iterator)) {
    return false;
  }

  // Create the request for a new after address handler and call it 
  auto const pNewLocation = bitCast <__ReceiverNewAfterConstHandlerType> (pReceiver->__iicch_obtainGenericHandler (__IterableInternalRequest::__iir_newAfterAddressConst)) (
      pReceiver, iterator._pDelegate->iterator()
  );

  // If no address received, insertion not possible 
  if (pNewLocation == nullptr) {
    return false;
  }

  // Otherwise, use placement new for creation 
  (void) new ( pNewLocation ) __Element (std::forward <__Arguments> (parameters)...);

  // Successful Result 
  return true;
}


template <typename __Receiver, typename __Element>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
template <typename...__Arguments> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
auto __AbstractConstIteratorRelativeInsertionPrimitiveClient <__Receiver, __Element>::insertAllBefore (
    AbstractConstIterator const&  iterator,
    __Arguments&&...              values
) noexcept(false) -> bool {
  using __Alloc                                   = __hidden::__impl::__allocation::__PrimitiveAlloc <__Element*>;  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  // Handle type of the new before address function 
  using __ReceiverNewBeforeConstArrayHandlerType  = cds::functional::PredicateFunction <__Receiver*, cds::meta::Iterator const*, Size, __Element**>; // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  // Caller object reinterpreted as receiver of the request 
  auto pReceiver                                  = static_cast <__Receiver*> (this);

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
    auto const allocationStatus = bitCast <__ReceiverNewBeforeConstArrayHandlerType> (pReceiver->__iicch_obtainGenericHandler (__IterableInternalRequest::__iir_newBeforeAddressArrayConst)) (
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


template <typename __Receiver, typename __Element>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
template <typename...__Arguments> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
auto __AbstractConstIteratorRelativeInsertionPrimitiveClient <__Receiver, __Element>::insertAllAfter (
    AbstractConstIterator const&  iterator,
    __Arguments&&...              values
) noexcept(false) -> bool {
  using __Alloc                                   = __hidden::__impl::__allocation::__PrimitiveAlloc <__Element*>;  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  // Handle type of the new after address function 
  using __ReceiverNewAfterConstArrayHandlerType   = cds::functional::PredicateFunction <__Receiver*, cds::meta::Iterator const*, Size, __Element**>; // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  // Caller object reinterpreted as receiver of the request 
  auto pReceiver                                  = static_cast <__Receiver*> (this);

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
    auto const allocationStatus = bitCast <__ReceiverNewAfterConstArrayHandlerType> (pReceiver->__iicch_obtainGenericHandler (__IterableInternalRequest::__iir_newAfterAddressArrayConst)) (
        pReceiver, iterator._pDelegate->iterator(), parameterCount, ppElements
    );

    // If status OK, initialize received memory with received values
    if ( allocationStatus ) {
      cds::__hidden::__impl::__allocation::__forwardIntoArray (
          ppElements,
          std::forward < __Arguments > ( values ) ...
      );
    }

    // Free temporary buffer and return status
    __Alloc::__free (ppElements);
    return allocationStatus;
  } catch (...) {
    __Alloc::__free (ppElements);
    throw;
  }
}


template <typename __Receiver, typename __Element>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
template <
    typename __Iterable, // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
    cds::meta::EnableIf <meta::__IterableSizeAvailable <__Iterable>::value>
> __CDS_OptimalInline auto __AbstractConstIteratorRelativeInsertionPrimitiveClient <__Receiver, __Element>::insertAllOfBefore (
    AbstractConstIterator const&  iterator,
    __Iterable const&             iterable
) noexcept(false) -> bool {
  // Variant with RandomAccessIterator - 'operator -'. Call insertAllOfBefore with size 
  return insertAllOfBefore (iterator, iterable.begin(), iterable.end(), iterable.size());
}


template <typename __Receiver, typename __Element>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
template <
    typename __Iterable, // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
    cds::meta::EnableIf <!meta::__IterableSizeAvailable <__Iterable>::value>
> __CDS_OptimalInline auto __AbstractConstIteratorRelativeInsertionPrimitiveClient <__Receiver, __Element>::insertAllOfBefore (
    AbstractConstIterator const&  iterator,
    __Iterable const&             iterable
) noexcept(false) -> bool {
  // Variant without RandomAccessIterator - 'operator -'. Call insertAllOfBefore without size, letting
  // the function compute the distance between start and end 
  return insertAllOfBefore (iterator, iterable.begin(), iterable.end());
}


template <typename __Receiver, typename __Element>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
template <
    typename __TElementType,            // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
    cds::meta::EnableIf <cds::meta::IsCopyConstructible <__TElementType>::value>
> __CDS_OptimalInline auto __AbstractConstIteratorRelativeInsertionPrimitiveClient <__Receiver, __Element>::insertAllOfBefore (
    AbstractConstIterator const&              iterator,
    std::initializer_list <__Element> const&  list
) noexcept(false) -> bool {
  // initializer_list has RandomAccessIterator - 'operator -'. Call insertAllOfBefore with size 
  return insertAllOfBefore (iterator, list.begin(), list.end(), list.size());
}


template <typename __Receiver, typename __Element>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
template <
    typename __Iterable, // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
    cds::meta::EnableIf <meta::__IterableSizeAvailable <__Iterable>::value>
> __CDS_OptimalInline auto __AbstractConstIteratorRelativeInsertionPrimitiveClient <__Receiver, __Element>::insertAllOfAfter (
    AbstractConstIterator const&  iterator,
    __Iterable const&             iterable
) noexcept(false) -> bool {
  // Variant with RandomAccessIterator - 'operator -'. Call insertAllOfAfter with size 
  return insertAllOfAfter (iterator, iterable.begin(), iterable.end(), iterable.size());
}


template <typename __Receiver, typename __Element>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
template <
    typename __Iterable, // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
    cds::meta::EnableIf <!meta::__IterableSizeAvailable <__Iterable>::value>
> __CDS_OptimalInline auto __AbstractConstIteratorRelativeInsertionPrimitiveClient <__Receiver, __Element>::insertAllOfAfter (
    AbstractConstIterator const&  iterator,
    __Iterable const&             iterable
) noexcept(false) -> bool {
  // Variant without RandomAccessIterator - 'operator -'. Call insertAllOfAfter without size, letting
  // the function compute the distance between start and end 
  return insertAllOfAfter (iterator, iterable.begin(), iterable.end());
}


template <typename __Receiver, typename __Element>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
template <
    typename __TElementType,            // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
    cds::meta::EnableIf <cds::meta::IsCopyConstructible <__TElementType>::value>
> __CDS_OptimalInline auto __AbstractConstIteratorRelativeInsertionPrimitiveClient <__Receiver, __Element>::insertAllOfAfter (
    AbstractConstIterator const&              iterator,
    std::initializer_list <__Element> const&  list
) noexcept(false) -> bool {
  // initializer_list has RandomAccessIterator - 'operator -'. Call insertAllOfAfter with size 
  return insertAllOfAfter (iterator, list.begin(), list.end(), list.size());
}


template <typename __Receiver, typename __Element>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
template <typename __Iterator> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
auto __AbstractConstIteratorRelativeInsertionPrimitiveClient <__Receiver, __Element>::insertAllOfBefore (
    AbstractConstIterator const&  iterator,
    __Iterator const&             begin,
    __Iterator const&             end,
    Size                          count
) noexcept(false) -> bool {
  using __Alloc                                   = __hidden::__impl::__allocation::__PrimitiveAlloc <__Element*>;  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  // Handle type of the new before address function 
  using __ReceiverNewBeforeConstArrayHandlerType  = cds::functional::PredicateFunction <__Receiver*, cds::meta::Iterator const*, Size, __Element**>; // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  // Caller object reinterpreted as receiver of the request 
  auto pReceiver                                  = static_cast <__Receiver*> (this);

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
    auto const allocationStatus =  bitCast <__ReceiverNewBeforeConstArrayHandlerType> (pReceiver->__iicch_obtainGenericHandler (__IterableInternalRequest::__iir_newBeforeAddressArrayConst)) (
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
  } catch (...) {
    __Alloc::__free (ppElements);
    throw;
  }
}


template <typename __Receiver, typename __Element>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
template <typename __Iterator> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
auto __AbstractConstIteratorRelativeInsertionPrimitiveClient <__Receiver, __Element>::insertAllOfAfter (
    AbstractConstIterator const&  iterator,
    __Iterator const&             begin,
    __Iterator const&             end,
    Size                          count
) noexcept(false) -> bool {
  using __Alloc                                   = __hidden::__impl::__allocation::__PrimitiveAlloc <__Element*>;  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  // Handle type of the new after address function 
  using __ReceiverNewAfterConstArrayHandlerType   = cds::functional::PredicateFunction <__Receiver*, cds::meta::Iterator const*, Size, __Element**>; // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  // Caller object reinterpreted as receiver of the request 
  auto pReceiver                                  = static_cast <__Receiver*> (this);

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
    auto const allocationStatus = bitCast <__ReceiverNewAfterConstArrayHandlerType> (pReceiver->__iicch_obtainGenericHandler (__IterableInternalRequest::__iir_newAfterAddressArrayConst)) (
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
  } catch (...) {
    __Alloc::__free (ppElements);
    throw;
  }
}


template <typename __Receiver, typename __Element, typename __Iterator>     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
template <
    typename __TElementType,    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
    cds::meta::EnableIf <cds::meta::IsCopyConstructible <__TElementType>::value>
> __CDS_OptimalInline auto __LocalConstIteratorRelativeInsertionPrimitiveClient <__Receiver, __Element, __Iterator>::insertBefore (
    ConstIterator const&  iterator,
    ElementType const&    element
) noexcept(false) -> bool {
  // Invoke the copy constructor via front emplacement 
  return emplaceBefore (iterator, element);
}


template <typename __Receiver, typename __Element, typename __Iterator>     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
template <
    typename __TElementType,    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
    cds::meta::EnableIf <cds::meta::IsMoveConstructible <__TElementType>::value>
> __CDS_OptimalInline auto __LocalConstIteratorRelativeInsertionPrimitiveClient <__Receiver, __Element, __Iterator>::insertBefore (
    ConstIterator const&  iterator,
    ElementType&&         element
) noexcept(false) -> bool {
  // Invoke the move constructor via front emplacement 
  return emplaceBefore (iterator, std::move (element));
}


template <typename __Receiver, typename __Element, typename __Iterator>     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
template <
    typename __TElementType,    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
    cds::meta::EnableIf <cds::meta::IsCopyConstructible <__TElementType>::value>
> __CDS_OptimalInline auto __LocalConstIteratorRelativeInsertionPrimitiveClient <__Receiver, __Element, __Iterator>::insertAfter (
    ConstIterator const&  iterator,
    ElementType const&    element
) noexcept(false) -> bool {
  // Invoke the copy constructor via back emplacement 
  return emplaceAfter (iterator, element);
}


template <typename __Receiver, typename __Element, typename __Iterator>     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
template <
    typename __TElementType,    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
    cds::meta::EnableIf <cds::meta::IsMoveConstructible <__TElementType>::value>
> __CDS_OptimalInline auto __LocalConstIteratorRelativeInsertionPrimitiveClient <__Receiver, __Element, __Iterator>::insertAfter (
    ConstIterator const&  iterator,
    ElementType&&         element
) noexcept(false) -> bool {
  // Invoke the move constructor via back emplacement 
  return emplaceAfter (iterator, std::move (element));
}


template <typename __Receiver, typename __Element, typename __Iterator>     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
template <typename...__Arguments> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
auto __LocalConstIteratorRelativeInsertionPrimitiveClient <__Receiver, __Element, __Iterator>::emplaceBefore (
    ConstIterator const&  iterator,
    __Arguments&&...      parameters
) noexcept(false) -> bool {
  // If iterator invalid, cannot emplace before it 
  if (!static_cast <bool> (iterator)) {
    return false;
  }

  // Call dispatcher local new before address handler 
  auto const pNewLocation = __Receiver::__newBeforeConst (static_cast <__Receiver*> (this), &iterator);

  // If no address received, insertion not possible 
  if (pNewLocation == nullptr) {
    return false;
  }

  // Otherwise, use placement new for creation 
  (void) new (pNewLocation) __Element (std::forward <__Arguments> (parameters)...);

  // Successful Result 
  return true;
}


template <typename __Receiver, typename __Element, typename __Iterator>     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
template <typename...__Arguments> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
auto __LocalConstIteratorRelativeInsertionPrimitiveClient <__Receiver, __Element, __Iterator>::emplaceAfter (
    ConstIterator const&  iterator,
    __Arguments&&...      parameters
) noexcept(false) -> bool {
  // If iterator invalid, cannot emplace after it 
  if (!static_cast <bool> (iterator)) {
    return false;
  }

  // Call dispatcher local new after address handler 
  auto const pNewLocation = __Receiver::__newAfterConst (static_cast <__Receiver*> (this), &iterator);

  // If no address received, insertion not possible 
  if (pNewLocation == nullptr) {
    return false;
  }

  // Otherwise, use placement new for creation 
  (void) new (pNewLocation) __Element (std::forward <__Arguments> (parameters)...);

  // Successful Result 
  return true;
}


template <typename __Receiver, typename __Element, typename __Iterator>     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
template <typename...__Arguments> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
auto __LocalConstIteratorRelativeInsertionPrimitiveClient <__Receiver, __Element, __Iterator>::insertAllBefore (
    ConstIterator const&  iterator,
    __Arguments&&...      values
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
    auto const allocationStatus = __Receiver::__newBeforeArrayConst (static_cast <__Receiver*> (this), &iterator, parameterCount, ppElements);

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


template <typename __Receiver, typename __Element, typename __Iterator>     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
template <typename...__Arguments> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
auto __LocalConstIteratorRelativeInsertionPrimitiveClient <__Receiver, __Element, __Iterator>::insertAllAfter (
    ConstIterator const&  iterator,
    __Arguments&&...      values
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
    auto const allocationStatus = __Receiver::__newAfterArrayConst (static_cast <__Receiver*> (this), &iterator, parameterCount, ppElements);

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


template <typename __Receiver, typename __Element, typename __Iterator>     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
template <
    typename __Iterable, // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
    cds::meta::EnableIf <meta::__IterableSizeAvailable <__Iterable>::value>
> __CDS_OptimalInline auto __LocalConstIteratorRelativeInsertionPrimitiveClient <__Receiver, __Element, __Iterator>::insertAllOfBefore (
    ConstIterator const&  iterator,
    __Iterable const&     iterable
) noexcept(false) -> bool {
  // Variant with RandomAccessIterator - 'operator -'. Call insertAllOfBefore with size 
  return insertAllOfBefore (iterator, iterable.begin(), iterable.end(), iterable.size());
}


template <typename __Receiver, typename __Element, typename __Iterator>     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
template <
    typename __Iterable, // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
    cds::meta::EnableIf <!meta::__IterableSizeAvailable <__Iterable>::value>
> __CDS_OptimalInline auto __LocalConstIteratorRelativeInsertionPrimitiveClient <__Receiver, __Element, __Iterator>::insertAllOfBefore (
    ConstIterator const&  iterator,
    __Iterable const&     iterable
) noexcept(false) -> bool {
  // Variant without RandomAccessIterator - 'operator -'. Call insertAllOfBefore without size, letting
  // the function compute the distance between start and end
  return insertAllOfBefore (iterator, iterable.begin(), iterable.end());
}


template <typename __Receiver, typename __Element, typename __Iterator>     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
template <
    typename __TElementType,            // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
    cds::meta::EnableIf <cds::meta::IsCopyConstructible <__TElementType>::value>
> __CDS_OptimalInline auto __LocalConstIteratorRelativeInsertionPrimitiveClient <__Receiver, __Element, __Iterator>::insertAllOfBefore (
    ConstIterator const&                      iterator,
    std::initializer_list <__Element> const&  list
) noexcept(false) -> bool {
  // initializer_list has RandomAccessIterator - 'operator -'. Call insertAllOfBefore with size 
  return insertAllOfBefore (iterator, list.begin(), list.end(), list.size());
}


template <typename __Receiver, typename __Element, typename __Iterator>     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
template <
    typename __Iterable, // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
    cds::meta::EnableIf <meta::__IterableSizeAvailable <__Iterable>::value>
> __CDS_OptimalInline auto __LocalConstIteratorRelativeInsertionPrimitiveClient <__Receiver, __Element, __Iterator>::insertAllOfAfter (
    ConstIterator const&  iterator,
    __Iterable const&     iterable
) noexcept(false) -> bool {
  // Variant with RandomAccessIterator - 'operator -'. Call insertAllOfAfter with size 
  return insertAllOfAfter (iterator, iterable.begin(), iterable.end(), iterable.size());
}


template <typename __Receiver, typename __Element, typename __Iterator>     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
template <
    typename __Iterable, // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
    cds::meta::EnableIf <!meta::__IterableSizeAvailable <__Iterable>::value>
> __CDS_OptimalInline auto __LocalConstIteratorRelativeInsertionPrimitiveClient <__Receiver, __Element, __Iterator>::insertAllOfAfter (
    ConstIterator const&  iterator,
    __Iterable const&     iterable
) noexcept(false) -> bool {
  // Variant without RandomAccessIterator - 'operator -'. Call insertAllOfAfter without size, letting
  // the function compute the distance between start and end
  return insertAllOfAfter (iterator, iterable.begin(), iterable.end());
}


template <typename __Receiver, typename __Element, typename __Iterator>     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
template <
    typename __TElementType,            // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
    cds::meta::EnableIf <cds::meta::IsCopyConstructible <__TElementType>::value>
> __CDS_OptimalInline auto __LocalConstIteratorRelativeInsertionPrimitiveClient <__Receiver, __Element, __Iterator>::insertAllOfAfter (
    ConstIterator const&                      iterator,
    std::initializer_list <__Element> const&  list
) noexcept(false) -> bool {
  // initializer_list has RandomAccessIterator - 'operator -'. Call insertAllOfAfter with size 
  return insertAllOfAfter (iterator, list.begin(), list.end(), list.size());
}


template <typename __Receiver, typename __Element, typename __LocalClientIterator>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
template <typename __Iterator> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
auto __LocalConstIteratorRelativeInsertionPrimitiveClient <__Receiver, __Element, __LocalClientIterator>::insertAllOfBefore (
    ConstIterator const&  iterator,
    __Iterator const&     begin,
    __Iterator const&     end,
    Size                  count
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
    auto const allocationStatus = __Receiver::__newBeforeArrayConst (static_cast <__Receiver*> (this), &iterator, parameterCount, ppElements);

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
auto __LocalConstIteratorRelativeInsertionPrimitiveClient <__Receiver, __Element, __LocalClientIterator>::insertAllOfAfter (
    ConstIterator const&  iterator,
    __Iterator const&     begin,
    __Iterator const&     end,
    Size                  count
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
    auto const allocationStatus = __Receiver::__newAfterArrayConst (static_cast <__Receiver*> (this), &iterator, parameterCount, ppElements);

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

#endif // __CDS_SHARED_CONST_ITERATOR_RELATIVE_INSERTION_PRIMITIVE_CLIENT_IMPL_HPP__ 
