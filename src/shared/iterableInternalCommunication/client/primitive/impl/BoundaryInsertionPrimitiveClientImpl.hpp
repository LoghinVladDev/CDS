//
// Created by loghin on 6/28/22.
//

#ifndef __CDS_SHARED_BOUNDARY_INSERTION_PRIMITIVE_CLIENT_IMPL_HPP__ // NOLINT(llvm-header-guard)
#define __CDS_SHARED_BOUNDARY_INSERTION_PRIMITIVE_CLIENT_IMPL_HPP__ // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
#pragma once

#include "../../../../iterator/IteratorDistance.hpp"

namespace cds {       // NOLINT(modernize-concat-nested-namespaces)
namespace __hidden {  // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
namespace __impl {    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename __Receiver, typename __Element, typename __Return> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <
    typename __TElementType,    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    cds::meta::EnableIf <cds::meta::IsCopyConstructible <__TElementType>::value>
> __CDS_OptimalInline auto __BoundaryInsertionPrimitiveClient <__Receiver, __Element, __Return>::pushFront (
    ElementType const& element
) noexcept(false) -> ElementReference {
  // Invoke the copy constructor via front emplacement 
  return emplaceFront (element);
}


template <typename __Receiver, typename __Element, typename __Return> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <
    typename __TElementType,    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    cds::meta::EnableIf <cds::meta::IsMoveConstructible <__TElementType>::value>
> __CDS_OptimalInline auto __BoundaryInsertionPrimitiveClient <__Receiver, __Element, __Return>::pushFront (
    ElementType && element
) noexcept(false) -> ElementReference {
  // Invoke the move constructor via front emplacement 
  return emplaceFront (std::move (element));
}


template <typename __Receiver, typename __Element, typename __Return> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <
    typename __TElementType,    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    cds::meta::EnableIf <cds::meta::IsCopyConstructible <__TElementType>::value>
> __CDS_OptimalInline auto __BoundaryInsertionPrimitiveClient <__Receiver, __Element, __Return>::pushBack (
    ElementType const& element
) noexcept(false) -> ElementReference {
  // Invoke the copy constructor via back emplacement 
  return emplaceBack (element);
}


template <typename __Receiver, typename __Element, typename __Return> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <
    typename __TElementType,    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    cds::meta::EnableIf <cds::meta::IsMoveConstructible <__TElementType>::value>
> __CDS_OptimalInline auto __BoundaryInsertionPrimitiveClient <__Receiver, __Element, __Return>::pushBack (
    ElementType && element
) noexcept(false) -> ElementReference {
  // Invoke the move constructor via back emplacement 
  return emplaceBack (std::move (element));
}


template <typename __Receiver, typename __Element, typename __Return> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <
    typename __TElementType,    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    cds::meta::EnableIf <cds::meta::IsCopyConstructible <__TElementType>::value>
> __CDS_OptimalInline auto __BoundaryInsertionPrimitiveClient <__Receiver, __Element, __Return>::prepend (
    ElementType const& element
) noexcept(false) -> ElementReference {
  // Call non-deprecated, equivalent function 
  return emplaceFront (element);
}


template <typename __Receiver, typename __Element, typename __Return> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <
    typename __TElementType,    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    cds::meta::EnableIf <cds::meta::IsMoveConstructible <__TElementType>::value>
> __CDS_OptimalInline auto __BoundaryInsertionPrimitiveClient <__Receiver, __Element, __Return>::prepend (
    ElementType && element
) noexcept(false) -> ElementReference {
  // Call non-deprecated, equivalent function 
  return emplaceFront (std::move (element));
}


template <typename __Receiver, typename __Element, typename __Return> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <
    typename __TElementType,    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    cds::meta::EnableIf <cds::meta::IsCopyConstructible <__TElementType>::value>
> __CDS_OptimalInline auto __BoundaryInsertionPrimitiveClient <__Receiver, __Element, __Return>::append (
    ElementType const& element
) noexcept(false) -> ElementReference {
  // Call non-deprecated, equivalent function 
  return emplaceBack (element);
}


template <typename __Receiver, typename __Element, typename __Return> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <
    typename __TElementType,    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    cds::meta::EnableIf <cds::meta::IsMoveConstructible <__TElementType>::value>
> __CDS_OptimalInline auto __BoundaryInsertionPrimitiveClient <__Receiver, __Element, __Return>::append (
    ElementType && element
) noexcept(false) -> ElementReference {
  // Call non-deprecated, equivalent function 
  return emplaceBack (std::move (element));
}


template <typename __Receiver, typename __Element, typename __Return> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename ... __Arguments> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto __BoundaryInsertionPrimitiveClient <__Receiver, __Element, __Return>::emplaceFront (
    __Arguments&&... parameters
) noexcept(false) -> ElementReference {
  // Handle type of the new front address function 
  using __ReceiverNewFrontHandlerType = cds::functional::MapperFunction <__Element*, __Receiver*>;  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  // Caller object reinterpreted as receiver of the request 
  auto pReceiver                      = static_cast <__Receiver*> (this);
  // Create the request for a new front address handler, call it and pass the received address, and
  // forward the received parameters to the emplacement new operator 
  return *new (
      bitCast <__ReceiverNewFrontHandlerType> (pReceiver->__iicch_obtainGenericHandler (__IterableInternalRequest::__iir_newFrontAddress)) (pReceiver)
  ) __Element (std::forward <__Arguments> (parameters)...);
}


template <typename __Receiver, typename __Element, typename __Return> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename...__Arguments> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
__CDS_OptimalInline auto __BoundaryInsertionPrimitiveClient <__Receiver, __Element, __Return>::emplaceBack (
    __Arguments&&... parameters
) noexcept(false) -> ElementReference {
  // Handle type of the new back address function 
  using __ReceiverNewBackHandlerType  = cds::functional::MapperFunction <__Element*, __Receiver*>; // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  // Caller object reinterpreted as receiver of the request 
  auto pReceiver                      = static_cast <__Receiver*> (this);
  // Create the request for a new back address handler, call it and pass the received address, and
  // forward the received parameters to the emplacement new operator 
  return * new (
      bitCast <__ReceiverNewBackHandlerType> (pReceiver->__iicch_obtainGenericHandler (__IterableInternalRequest::__iir_newBackAddress)) (pReceiver)
  ) __Element (std::forward <__Arguments> (parameters)...);
}


template <typename __Receiver, typename __Element, typename __Return> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename...__Arguments>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
auto __BoundaryInsertionPrimitiveClient <__Receiver, __Element, __Return>::pushFrontAll (
    __Arguments&&... values
) noexcept(false) -> void {
  // Handle type of the new front address function 
  using __ReceiverNewFrontArrayHandlerType    = cds::functional::ConsumerFunction <__Receiver*, Size, __Element**>; // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  using __Alloc                               = __hidden::__impl::__allocation::__PrimitiveAlloc <__Element*>;      // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  // Caller object reinterpreted as receiver of the request 
  auto          pReceiver                     = static_cast <__Receiver*> (this);
  // The number of received values is the numbers of elements to be created 
  Size    const parameterCount                = sizeof...(__Arguments);
  // Allocate the buffer to store the addresses of the newly created memory spaces for the elements 
  auto          ppElements                    = __Alloc::__alloc(parameterCount);

  try {
    // Request and call handler for a new front address array with the created buffer 
    bitCast <__ReceiverNewFrontArrayHandlerType> (pReceiver->__iicch_obtainGenericHandler (__IterableInternalRequest::__iir_newFrontAddressArray)) (
        pReceiver, parameterCount, ppElements
    );
  
    // Forward initialization values to construct each received address with them 
    cds::__hidden::__impl::__allocation::__forwardIntoArray (ppElements, std::forward <__Arguments> (values)...);
  } catch (...) {
    __Alloc::__free (ppElements);
    throw;
  }
  
  // Free the temporary address buffer 
  __Alloc::__free (ppElements);
}


template <typename __Receiver, typename __Element, typename __Return> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename...__Arguments>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
auto __BoundaryInsertionPrimitiveClient <__Receiver, __Element, __Return>::pushBackAll (
    __Arguments&&... values
) noexcept (false) -> void {
  // Handle type of the new back address function 
  using __ReceiverNewBackArrayHandlerType = cds::functional::ConsumerFunction <__Receiver*, Size, __Element**>; // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  using __Alloc                           = __hidden::__impl::__allocation::__PrimitiveAlloc <__Element*>;  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  // Caller object reinterpreted as receiver of the request 
  auto          pReceiver                 = static_cast <__Receiver*> (this);
  // The number of received values is the numbers of elements to be created 
  Size    const parameterCount            = sizeof...(__Arguments);
  // Allocate the buffer to store the addresses of the newly created memory spaces for the elements 
  auto          ppElements                = __Alloc::__alloc (parameterCount);

  try {
    // Request and call handler for a new back address array with the created buffer
    bitCast <__ReceiverNewBackArrayHandlerType> (pReceiver->__iicch_obtainGenericHandler (__IterableInternalRequest::__iir_newBackAddressArray)) (
        pReceiver, parameterCount, ppElements
    );

    // Forward initialization values to construct each received address with them
    cds::__hidden::__impl::__allocation::__forwardIntoArray (ppElements, std::forward <__Arguments> (values)...);
  } catch (...) {
    __Alloc::__free (ppElements);
    throw;
  }

  // Free the temporary address buffer 
  __Alloc::__free (ppElements);
}


template <typename __Receiver, typename __Element, typename __Return> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <
    typename __IterableType,            // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    cds::meta::EnableIf <meta::__IterableSizeAvailable < __IterableType >::value>
> __CDS_OptimalInline auto __BoundaryInsertionPrimitiveClient <__Receiver, __Element, __Return>::pushFrontAllOf (
    __IterableType const& iterable
) noexcept (false) -> void {
  // Variant with RandomAccessIterator - 'operator -'. Call pushFrontAllOf with size 
  pushFrontAllOf (iterable.begin(), iterable.end(), iterable.size());
}


template <typename __Receiver, typename __Element, typename __Return> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <
    typename __IterableType,            // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    cds::meta::EnableIf <!meta::__IterableSizeAvailable < __IterableType >::value>
> __CDS_OptimalInline auto __BoundaryInsertionPrimitiveClient <__Receiver, __Element, __Return>::pushFrontAllOf (
    __IterableType const& iterable
) noexcept (false) -> void {
  // Variant without RandomAccessIterator - 'operator -'. Call pushFrontAllOf without size, letting
  // the function compute the distance between start and end
  pushFrontAllOf (iterable.begin(), iterable.end());
}


template <typename __Receiver, typename __Element, typename __Return> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <
    typename __TElementType,            // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    cds::meta::EnableIf <cds::meta::IsCopyConstructible <__TElementType>::value>
> __CDS_OptimalInline auto __BoundaryInsertionPrimitiveClient <__Receiver, __Element, __Return>::pushFrontAllOf (
    std::initializer_list < __Element > const& list
) noexcept (false) -> void {
  // initializer_list has RandomAccessIterator - 'operator -'. Call pushFrontAllOf with size 
  pushFrontAllOf (list.begin(), list.end(), list.size());
}


template <typename __Receiver, typename __Element, typename __Return> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <
    typename __IterableType,            // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    cds::meta::EnableIf <meta::__IterableSizeAvailable < __IterableType >::value>
> __CDS_OptimalInline auto __BoundaryInsertionPrimitiveClient <__Receiver, __Element, __Return>::pushBackAllOf (
    __IterableType const& iterable
) noexcept(false) -> void {
  // Variant with RandomAccessIterator - 'operator -'. Call pushBackAllOf with size 
  pushBackAllOf (iterable.begin(), iterable.end(), iterable.size());
}


template <typename __Receiver, typename __Element, typename __Return> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <
    typename __IterableType,            // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    cds::meta::EnableIf <!meta::__IterableSizeAvailable < __IterableType >::value>
> __CDS_OptimalInline auto __BoundaryInsertionPrimitiveClient <__Receiver, __Element, __Return>::pushBackAllOf (
    __IterableType const& iterable
) noexcept(false) -> void {
  // Variant without RandomAccessIterator - 'operator -'. Call pushBackAllOf without size, letting
  // the function compute the distance between start and end
  pushBackAllOf (iterable.begin(), iterable.end());
}


template <typename __Receiver, typename __Element, typename __Return> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <
    typename __TElementType,            // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    cds::meta::EnableIf <cds::meta::IsCopyConstructible <__TElementType>::value>
> __CDS_OptimalInline auto __BoundaryInsertionPrimitiveClient <__Receiver, __Element, __Return>::pushBackAllOf (
    std::initializer_list < __Element > const& list
) noexcept(false) -> void {
  // initializer_list has RandomAccessIterator - 'operator -'. Call pushBackAllOf with size 
  pushBackAllOf (list.begin(), list.end(), list.size());
}


template <typename __Receiver, typename __Element, typename __Return> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename __IteratorType>             // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
auto __BoundaryInsertionPrimitiveClient <__Receiver, __Element, __Return>::pushFrontAllOf (
    __IteratorType const& begin,
    __IteratorType const& end,
    Size                   count
) noexcept(false) -> void {
  using __Alloc                               = __hidden::__impl::__allocation::__PrimitiveAlloc <__Element*>;  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  // Handle type of the new front address function 
  using __ReceiverNewFrontArrayHandlerType    = cds::functional::ConsumerFunction <__Receiver*, Size, __Element**>; // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  // Caller object reinterpreted as receiver of the request 
  auto          pReceiver                     = static_cast <__Receiver*> (this);
  // The number of received values is the numbers of elements to be created. If 0, compute 
  Size    const parameterCount                = count == 0u ? __IteratorDistance <__IteratorType>::__compute (begin, end) : count;
  // Allocate the buffer to store the addresses of the newly created memory spaces for the elements 
  auto          ppElements                    = __Alloc::__alloc (parameterCount);

  try {
    // Request and call handler for a new front address array with the created buffer
    bitCast <__ReceiverNewFrontArrayHandlerType> (pReceiver->__iicch_obtainGenericHandler (__IterableInternalRequest::__iir_newFrontAddressArray)) (
        pReceiver, parameterCount, ppElements
    );

    // Parse iterator range and call placement new operator at received memory with
    // each iterator's value
    Size index = 0u;
    for (auto iterator = begin; iterator != end; ++iterator) {
      (void) new (ppElements [index++]) __Element (*iterator);
    }
  } catch (...) {
    __Alloc::__free (ppElements);
    throw;
  }
  // Free the temporary address buffer 
  __Alloc::__free (ppElements);
}


template <typename __Receiver, typename __Element, typename __Return> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename __IteratorType>             // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
auto __BoundaryInsertionPrimitiveClient <__Receiver, __Element, __Return>::pushBackAllOf (
    __IteratorType const& begin,
    __IteratorType const& end,
    Size                  count
) noexcept (false) -> void {
  using __Alloc                           = __hidden::__impl::__allocation::__PrimitiveAlloc <__Element*>;  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  // Handle type of the new back address function 
  using __ReceiverNewBackArrayHandlerType = cds::functional::ConsumerFunction <__Receiver*, Size, __Element**>; // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  // Caller object reinterpreted as receiver of the request 
  auto          pReceiver                 = static_cast < __Receiver * > ( this );
  // The number of received values is the numbers of elements to be created. If 0, compute 
  Size    const parameterCount            = count == 0u ? __IteratorDistance <__IteratorType>::__compute (begin, end) : count;
  // Allocate the buffer to store the addresses of the newly created memory spaces for the elements 
  auto          ppElements                = __Alloc::__alloc (parameterCount);

  try {
    // Request and call handler for a new back address array with the created buffer
    bitCast <__ReceiverNewBackArrayHandlerType> (pReceiver->__iicch_obtainGenericHandler (__IterableInternalRequest::__iir_newBackAddressArray)) (
        pReceiver, parameterCount, ppElements
    );

    // Parse iterator range and call placement new operator at received memory with
    // each iterator's value
    Size index = 0u;
    for (auto iterator = begin; iterator != end; ++iterator) {
      (void) new (ppElements [index++]) __Element (*iterator);
    }
  } catch (...) {
    __Alloc::__free (ppElements);
    throw;
  }

  // Free the temporary address buffer 
  __Alloc::__free (ppElements);
}


template <typename __Receiver, typename __Element, typename __Return> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <
    typename __TElementType,    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    cds::meta::EnableIf <cds::meta::IsCopyConstructible <__TElementType>::value>
> __CDS_OptimalInline auto __LocalBoundaryInsertionPrimitiveClient <__Receiver, __Element, __Return>::pushFront (
    ElementType const& element
) noexcept(false) -> ElementReference {
  // Invoke the copy constructor via front emplacement 
  return emplaceFront (element);
}


template <typename __Receiver, typename __Element, typename __Return> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <
    typename __TElementType,    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    cds::meta::EnableIf <cds::meta::IsMoveConstructible <__TElementType>::value>
> __CDS_OptimalInline auto __LocalBoundaryInsertionPrimitiveClient <__Receiver, __Element, __Return>::pushFront (
    ElementType&& element
) noexcept(false) -> ElementReference {
  // Invoke the move constructor via front emplacement 
  return emplaceFront (std::move (element));
}


template <typename __Receiver, typename __Element, typename __Return> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <
    typename __TElementType,    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    cds::meta::EnableIf <cds::meta::IsCopyConstructible <__TElementType>::value>
> __CDS_OptimalInline auto __LocalBoundaryInsertionPrimitiveClient <__Receiver, __Element, __Return>::pushBack (
    ElementType const& element
) noexcept(false) -> ElementReference {
  // Invoke the copy constructor via back emplacement 
  return emplaceBack (element);
}


template <typename __Receiver, typename __Element, typename __Return> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <
    typename __TElementType,    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    cds::meta::EnableIf <cds::meta::IsMoveConstructible <__TElementType>::value>
> __CDS_OptimalInline auto __LocalBoundaryInsertionPrimitiveClient <__Receiver, __Element, __Return>::pushBack (
    ElementType&& element
) noexcept(false) -> ElementReference {
  // Invoke the move constructor via back emplacement 
  return emplaceBack (std::move (element));
}


template <typename __Receiver, typename __Element, typename __Return> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <
    typename __TElementType,    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    cds::meta::EnableIf <cds::meta::IsCopyConstructible <__TElementType>::value>
> __CDS_OptimalInline auto __LocalBoundaryInsertionPrimitiveClient <__Receiver, __Element, __Return>::prepend (
    ElementType const& element
) noexcept(false) -> ElementReference {
  // Call non-deprecated, equivalent function 
  return emplaceFront (element);
}


template <typename __Receiver, typename __Element, typename __Return> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <
    typename __TElementType,    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    cds::meta::EnableIf <cds::meta::IsMoveConstructible <__TElementType>::value>
> __CDS_OptimalInline auto __LocalBoundaryInsertionPrimitiveClient <__Receiver, __Element, __Return>::prepend (
    ElementType&& element
) noexcept(false) -> ElementReference {
  // Call non-deprecated, equivalent function 
  return emplaceFront (std::move (element));
}


template <typename __Receiver, typename __Element, typename __Return> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <
    typename __TElementType,    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    cds::meta::EnableIf <cds::meta::IsCopyConstructible <__TElementType>::value>
> __CDS_OptimalInline auto __LocalBoundaryInsertionPrimitiveClient <__Receiver, __Element, __Return>::append (
    ElementType const& element
) noexcept(false) -> ElementReference {
  // Call non-deprecated, equivalent function 
  return emplaceBack (element);
}


template <typename __Receiver, typename __Element, typename __Return> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <
    typename __TElementType,    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    cds::meta::EnableIf <cds::meta::IsMoveConstructible <__TElementType>::value>
> __CDS_OptimalInline auto __LocalBoundaryInsertionPrimitiveClient <__Receiver, __Element, __Return>::append (
    ElementType&& element
) noexcept(false) -> ElementReference {
  // Call non-deprecated, equivalent function 
  return emplaceBack (std::move (element));
}


template <typename __Receiver, typename __Element, typename __Return> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename ... __Arguments>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto __LocalBoundaryInsertionPrimitiveClient <__Receiver, __Element, __Return>::emplaceFront (
    __Arguments&&... parameters
) noexcept(false) -> ElementReference {
  // call local dispatcher function to acquire a new front address, then construct element
  // with received parameters
  return *new (__Receiver::__newFront (static_cast <__Receiver*> (this))) __Element (std::forward <__Arguments> (parameters)...);
}


template <typename __Receiver, typename __Element, typename __Return> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename ... __Arguments> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto __LocalBoundaryInsertionPrimitiveClient <__Receiver, __Element, __Return>::emplaceBack (
    __Arguments&&... parameters
) noexcept(false) -> ElementReference {
  // call local dispatcher function to acquire a new back address, then construct element
  // with received parameters
  return *new (__Receiver::__newBack (static_cast <__Receiver*> (this))) __Element (std::forward <__Arguments> (parameters)...);
}


template <typename __Receiver, typename __Element, typename __Return> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename...__Arguments>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
auto __LocalBoundaryInsertionPrimitiveClient <__Receiver, __Element, __Return>::pushFrontAll (
    __Arguments&&... values
) noexcept (false) -> void {
  using __Alloc                 = __hidden::__impl::__allocation::__PrimitiveAlloc <__Element*>;  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  // The number of received values is the numbers of elements to be created 
  Size    const parameterCount  = sizeof...(__Arguments);
  // Allocate the buffer to store the addresses of the newly created memory spaces for the elements 
  auto          ppElements      = __Alloc::__alloc (parameterCount);

  try {
    // Call local dispatcher handle for a new front address array with the created buffer
    __Receiver::__newFrontArray (static_cast <__Receiver*> (this), parameterCount, ppElements);
    // Forward initialization values to construct each received address with them
    cds::__hidden::__impl::__allocation::__forwardIntoArray (ppElements, std::forward <__Arguments> (values)...);
  } catch (...) {
    __Alloc::__free (ppElements);
    throw;
  }

  // Free the temporary address buffer 
  __Alloc::__free (ppElements);
}


template <typename __Receiver, typename __Element, typename __Return> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename...__Arguments>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
auto __LocalBoundaryInsertionPrimitiveClient <__Receiver, __Element, __Return>::pushBackAll (
    __Arguments&&... values
) noexcept (false) -> void {
  using __Alloc                 = __hidden::__impl::__allocation::__PrimitiveAlloc <__Element*>;  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  // The number of received values is the numbers of elements to be created 
  Size    const parameterCount  = sizeof...(__Arguments);
  // Allocate the buffer to store the addresses of the newly created memory spaces for the elements 
  auto          ppElements      = __Alloc::__alloc (parameterCount);

  try {
    // Call local dispatcher handle for a new back address array with the created buffer
    __Receiver::__newBackArray (static_cast <__Receiver*> (this), parameterCount, ppElements);
    // Forward initialization values to construct each received address with them
    cds::__hidden::__impl::__allocation::__forwardIntoArray (ppElements, std::forward <__Arguments> (values)...);
  } catch (...) {
    __Alloc::__free (ppElements);
    throw;
  }

  // Free the temporary address buffer 
  __Alloc::__free (ppElements);
}


template <typename __Receiver, typename __Element, typename __Return> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <
    typename __IterableType,            // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    cds::meta::EnableIf <meta::__IterableSizeAvailable < __IterableType >::value>
> __CDS_OptimalInline auto __LocalBoundaryInsertionPrimitiveClient <__Receiver, __Element, __Return>::pushFrontAllOf (
    __IterableType const& iterable
) noexcept (false) -> void {
  // Variant with RandomAccessIterator - 'operator -'. Call pushFrontAllOf with size 
  pushFrontAllOf (iterable.begin(), iterable.end(), iterable.size());
}


template <typename __Receiver, typename __Element, typename __Return> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <
    typename __IterableType,            // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    cds::meta::EnableIf <!meta::__IterableSizeAvailable < __IterableType >::value>
> __CDS_OptimalInline auto __LocalBoundaryInsertionPrimitiveClient <__Receiver, __Element, __Return>::pushFrontAllOf (
    __IterableType const& iterable
) noexcept (false) -> void {
  // Variant without RandomAccessIterator - 'operator -'. Call pushFrontAllOf without size, letting
  // the function compute the distance between start and end
  pushFrontAllOf (iterable.begin(), iterable.end());
}


template <typename __Receiver, typename __Element, typename __Return> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <
    typename __TElementType,            // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    cds::meta::EnableIf <cds::meta::IsCopyConstructible <__TElementType>::value>
> __CDS_OptimalInline auto __LocalBoundaryInsertionPrimitiveClient <__Receiver, __Element, __Return>::pushFrontAllOf (
    std::initializer_list < __Element > const& list
) noexcept (false) -> void {
  // initializer_list has RandomAccessIterator - 'operator -'. Call pushFrontAllOf with size 
  pushFrontAllOf (list.begin(), list.end(), list.size());
}


template <typename __Receiver, typename __Element, typename __Return> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <
    typename __IterableType,            // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    cds::meta::EnableIf <meta::__IterableSizeAvailable < __IterableType >::value>
> __CDS_OptimalInline auto __LocalBoundaryInsertionPrimitiveClient <__Receiver, __Element, __Return>::pushBackAllOf (
    __IterableType const& iterable
) noexcept (false) -> void {
  // Variant with RandomAccessIterator - 'operator -'. Call pushBackAllOf with size 
  pushBackAllOf (iterable.begin(), iterable.end(), iterable.size());
}


template <typename __Receiver, typename __Element, typename __Return> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <
    typename __IterableType,            // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    cds::meta::EnableIf <!meta::__IterableSizeAvailable < __IterableType >::value>
> __CDS_OptimalInline auto __LocalBoundaryInsertionPrimitiveClient <__Receiver, __Element, __Return>::pushBackAllOf (
    __IterableType const& iterable
) noexcept (false) -> void {
  // Variant without RandomAccessIterator - 'operator -'. Call pushBackAllOf without size, letting
  // the function compute the distance between start and end
  pushBackAllOf (iterable.begin(), iterable.end());
}


template <typename __Receiver, typename __Element, typename __Return> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <
    typename __TElementType,            // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    cds::meta::EnableIf <cds::meta::IsCopyConstructible <__TElementType>::value>
> __CDS_OptimalInline auto __LocalBoundaryInsertionPrimitiveClient <__Receiver, __Element, __Return>::pushBackAllOf (
    std::initializer_list < __Element > const& list
) noexcept (false) -> void {
  // initializer_list has RandomAccessIterator - 'operator -'. Call pushBackAllOf with size 
  pushBackAllOf (list.begin(), list.end(), list.size());
}


template <typename __Receiver, typename __Element, typename __Return> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename __IteratorType>               // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
auto __LocalBoundaryInsertionPrimitiveClient <__Receiver, __Element, __Return>::pushFrontAllOf (
    __IteratorType const& begin,
    __IteratorType const& end,
    Size                  count
) noexcept (false) -> void {
  using __Alloc                   = __hidden::__impl::__allocation::__PrimitiveAlloc <__Element*>;  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  // The number of received values is the numbers of elements to be created. If 0, compute 
  Size    const parameterCount    = count == 0u ? __IteratorDistance <__IteratorType>::__compute (begin, end) : count;
  // Allocate the buffer to store the addresses of the newly created memory spaces for the elements 
  auto          ppElements        = __Alloc::__alloc (parameterCount);

  try {
    // Call local dispatcher handle for a new front address array with the created buffer
    __Receiver::__newFrontArray (static_cast <__Receiver*> (this), parameterCount, ppElements);
    // Parse iterator range and call placement new operator at received memory with
    // each iterator's value
    Size index = 0u;
    for (auto iterator = begin; iterator != end; ++iterator) {
      (void) new (ppElements [index++]) __Element (*iterator);
    }
  } catch (...) {
    __Alloc::__free (ppElements);
    throw;
  }

  // Free the temporary address buffer 
  __Alloc::__free (ppElements);
}


template <typename __Receiver, typename __Element, typename __Return> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <
    typename __IteratorType             // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> auto __LocalBoundaryInsertionPrimitiveClient <__Receiver, __Element, __Return>::pushBackAllOf (
    __IteratorType const& begin,
    __IteratorType const& end,
    Size                   count
) noexcept (false) -> void {
  using __Alloc                   = __hidden::__impl::__allocation::__PrimitiveAlloc <__Element*>;  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  // The number of received values is the numbers of elements to be created. If 0, compute 
  Size    const parameterCount    = count == 0u ? __IteratorDistance <__IteratorType>::__compute (begin, end) : count;
  // Allocate the buffer to store the addresses of the newly created memory spaces for the elements 
  auto          ppElements        = __Alloc::__alloc (parameterCount);

  try {
    // Call local dispatcher handle for a new back address array with the created buffer
    __Receiver::__newBackArray (static_cast <__Receiver*> (this), parameterCount, ppElements);
    // Parse iterator range and call placement new operator at received memory with
    // each iterator's value
    Size index = 0u;
    for (auto iterator = begin; iterator != end; ++iterator) {
      (void) new (ppElements [index++]) __Element (*iterator);
    }
  } catch(...) {
    __Alloc::__free (ppElements);
    throw;
  }

  // Free the temporary address buffer 
  __Alloc::__free (ppElements);
}
} // namespace __impl 
} // namespace __hidden 
} // namespace cds 

#endif // __CDS_SHARED_BOUNDARY_INSERTION_PRIMITIVE_CLIENT_IMPL_HPP__ 
