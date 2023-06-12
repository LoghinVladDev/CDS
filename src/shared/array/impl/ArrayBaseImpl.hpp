//
// Created by loghin on 7/5/22.
//

#ifndef __CDS_SHARED_ARRAY_BASE_IMPL_HPP__ // NOLINT(llvm-header-guard)
#define __CDS_SHARED_ARRAY_BASE_IMPL_HPP__ // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
#pragma once

namespace cds {       // NOLINT(modernize-concat-nested-namespaces) 
namespace __hidden {  // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
namespace __impl {    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 

template <
    typename                                                      __Type,   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__Type const&, __Type const& > __equals  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> Size const __ArrayBase <__Type, __equals>::__ab_minCapacity;


template <
    typename                                                      __Type,   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__Type const&, __Type const&>  __equals  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> __CDS_OptimalInline __ArrayBase <__Type, __equals>::__ArrayBase (__ArrayBase const & array) noexcept(false) {
  // use internal function to copy array data, since new array is cleared
  __ab_copy (array);
}


template <
    typename                                                      __Type,   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__Type const&, __Type const&>  __equals  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> constexpr __ArrayBase <__Type, __equals>::__ArrayBase (__ArrayBase && array) noexcept :
    _pData (cds::exchange (array._pData, nullptr)) {
  // move array data directly
}


template <
    typename                                                      __Type,  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__Type const&, __Type const&>  __equals // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> auto __ArrayBase <__Type, __equals>::__ab_clear (bool destroyBuffer) noexcept -> void {
  using __Alloc = __allocation::__PrimitiveAlloc <__Type>;  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  using __AllocImpl = __allocation::__PrimitiveAlloc <__ArrayImplDataContainer>;  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

  // If no data / already clear, do nothing
  if (_pData == nullptr) {
    return;
  }

  // clear the contents of the whole array
  while (_pData->_pFront != _pData->_pBack) {
    (_pData->_pFront++)->~__Type();
  }

  // If destroying buffer, destroy buffer and data contents, otherwise, just reset buffer front and back
  if (destroyBuffer) {
    __Alloc::__free (_pData->_pBuffer);
    __AllocImpl::__free (_pData);
  } else {
    _pData->_pFront = _pData->_pBuffer + _pData->_frontCapacity;
    _pData->_pBack  = _pData->_pFront;
  }
}


template <
    typename                                                      __Type,   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__Type const&, __Type const&>  __equals  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> constexpr auto __ArrayBase <__Type, __equals>::__ab_size () const noexcept -> Size {
  // if data empty, size is 0. Otherwise, distance from back to front
  return _pData == nullptr
      ? 0
      : _pData->_pBack - _pData->_pFront;
}


template <
    typename                                                      __Type,   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__Type const&, __Type const&>  __equals  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> auto __ArrayBase <__Type, __equals>::__ab_remove (Index index) noexcept -> void {
  // acquire size for later use
  auto const size = __ab_size();

  // if empty, do nothing
  if (size == 0u) {
    return;
  }
  // if removal of front, delete front, advance front pointer, return
  if (static_cast <Size> (index) == 0u) {
    (_pData->_pFront++)->~__Type();
    return;
  }
  // if removal of back, delete back, reverse back pointer, return
  if (static_cast <Size> (index) == size - 1u) {
    (--_pData->_pBack)->~__Type();
    return;
  }
  // otherwise, destroy element and decide which size is easier to shift ( fewer operations )
  _pData->_pFront [index].~__Type ();
  auto shiftLeftSide = static_cast <Size> (index) < (size - 1u) / 2u;

  // find information regarding where to move, from where to move and how many elements
  ElementType*  pDestination;
  ElementType*  pSource;
  Size          count;

  // if shifting left, destination is after front. source is previous front. count is determined by given index
  // if shifting right, destination is front + index, source is one after destination, count is size - index
  if (shiftLeftSide) {
    pDestination = ++_pData->_pFront;
    pSource      = pDestination - 1u;
    count        = static_cast <Size> (index);
  } else {
    pDestination = _pData->_pFront + static_cast <Size> (index);
    pSource      = pDestination + 1u;
    count        = size - static_cast <Size> (index);
    --_pData->_pBack;
  }

  // execute the move of the elements
  (void) std::memmove (
      static_cast <void*> (pDestination),
      static_cast <void const*> (pSource),
      sizeof (__Type) * count
  );
}


template <
    typename                                                      __Type,   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
    functional::PredicateFunction <__Type const&, __Type const&>  __equals  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
> __CDS_cpplang_NonConstConstexprMemberFunction auto __ArrayBase <__Type, __equals>::__ab_get (
    Index index
) noexcept -> ElementType* {
  // element requested is offset 'index' from 'front' 
  return _pData->_pFront + index;
}


template <
    typename                                                      __Type,   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
    functional::PredicateFunction <__Type const&, __Type const&>  __equals  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
> constexpr auto __ArrayBase <__Type, __equals>::__ab_get (Index index) const noexcept -> ElementType const* {
  // element requested is offset 'index' from 'front'
  return _pData->_pFront + index;
}


template <
    typename                                                      __Type,   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
    functional::PredicateFunction <__Type const&, __Type const&>  __equals  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
> auto __ArrayBase <__Type, __equals>::__ab_init () noexcept(false) -> void {
  using __Alloc = __allocation::__PrimitiveAlloc <__ArrayImplDataContainer>;  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

  // acquire new memory for array container and clear it
  _pData = __Alloc::__calloc();

  // set future capacities
  _pData->_frontNextCapacity  = __ab_minCapacity;
  _pData->_backNextCapacity   = __ab_minCapacity;
}


template <
    typename                                                      __Type,   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
    functional::PredicateFunction <__Type const&, __Type const&>  __equals  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
> auto __ArrayBase <__Type, __equals>::__ab_newFront () noexcept(false) -> ElementType* {
  using __Alloc = __allocation::__PrimitiveAlloc <__Type>;  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

  // if empty, initialize
  if (_pData == nullptr) {
    __ab_init();
  }

  // if no space available in front, enlarge front
  if (_pData->_pFront == _pData->_pBuffer) {
    // acquire next capacity
    _pData->_frontNextCapacity  = cds::maxOf (_pData->_frontNextCapacity, __ab_minCapacity);

    // acquire new buffer
    auto pNewBuffer             = __Alloc::__alloc (_pData->_frontNextCapacity + _pData->_backCapacity);

    // store current size and compute new front in new buffer
    auto const size                     = __ab_size();
    auto const pNewFront                = pNewBuffer + _pData->_frontNextCapacity - _pData->_frontCapacity;

    // copy data from old buffer to new
    (void) std::memcpy (
            static_cast <void*> (pNewFront),
            static_cast <void const*> (_pData->_pFront),
            sizeof (__Type) * size
    );

    // set other values. back in new buffer, front and capacities
    _pData->_pBack              = pNewFront + size;
    _pData->_pFront             = pNewFront;
    _pData->_frontCapacity      = _pData->_frontNextCapacity;
    _pData->_frontNextCapacity  = _pData->_frontNextCapacity * 2u;

    // clear old buffer and store new one
    __Alloc::__free (cds::exchange (_pData->_pBuffer, pNewBuffer));
  }
  // update front to allow for one more element and return address of new space
  return --_pData->_pFront;
}


template <
    typename                                                      __Type,   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
    functional::PredicateFunction <__Type const&, __Type const&>  __equals  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
> __CDS_OptimalInline auto __ArrayBase <__Type, __equals>::__ab_newAddress (
        __Type const* pReferenceElement,
        bool*         pNewElementCreated
) noexcept(false) -> ElementType* {
  // pReferenceElement is unused
  (void) pReferenceElement;
  // element always created. return address with newBack
  *pNewElementCreated = true;
  return __ab_newBack();
}


template <
    typename                                                      __Type,   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
    functional::PredicateFunction <__Type const&, __Type const&>  __equals  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
> auto __ArrayBase <__Type, __equals>::__ab_newBack () noexcept(false) -> ElementType* {
  using __Alloc = __allocation::__PrimitiveAlloc <__Type>;  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

  // if empty, initialize
  if (_pData == nullptr) {
    __ab_init();
  }

  // if back is at end of buffer => no space
  if (_pData->_pBack == _pData->_pBuffer + _pData->_frontCapacity + _pData->_backCapacity) {

    // compute next capacity
    _pData->_backNextCapacity = cds::maxOf (_pData->_backNextCapacity, __ab_minCapacity);

    // reallocate buffer to greater size
    auto const pNewBuffer     = __Alloc::__realloc (__ab_size(), _pData->_pBuffer, _pData->_frontCapacity + _pData->_backNextCapacity);

    // reallocation could create a new buffer, so reset front and back. Also update back capacity and next capacity, and buffer
    _pData->_pFront           = pNewBuffer + (_pData->_pFront - _pData->_pBuffer);
    _pData->_pBack            = pNewBuffer + (_pData->_pBack - _pData->_pBuffer);
    _pData->_backCapacity     = _pData->_backNextCapacity;
    _pData->_backNextCapacity = _pData->_backNextCapacity * 2u;
    _pData->_pBuffer          = pNewBuffer;
  }

  // return address to back ( as it already contained uninitialized memory space ) and increase it
  return _pData->_pBack++;
}


template <
    typename                                                      __Type,   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
    functional::PredicateFunction <__Type const&, __Type const&>  __equals  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
> auto __ArrayBase <__Type, __equals>::__ab_newFrontArray (Size count, __Type** ppElements) noexcept(false) -> void {
  using __Alloc = __allocation::__PrimitiveAlloc <__Type>;  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

  // if empty, initialize 
  if (_pData == nullptr) {
    __ab_init();
  }

  // if no space available in front, enlarge front 
  if (_pData->_pBuffer + count > _pData->_pFront) {

    // acquire next capacity 
    _pData->_frontNextCapacity  = cds::maxOf (_pData->_frontNextCapacity, count + _pData->_frontCapacity);

    // acquire new buffer 
    auto pNewBuffer             = __Alloc::__alloc (_pData->_frontNextCapacity + _pData->_backCapacity);

    // store current size and compute new front in new buffer 
    auto const size             = __ab_size();
    auto const pNewFront        = pNewBuffer 
        + (_pData->_frontNextCapacity - _pData->_frontCapacity) 
        + (_pData->_pFront - _pData->_pBuffer);

    // copy data from old buffer to new 
    (void) std::memcpy (
        static_cast <void*> (pNewFront),
        static_cast <void const*> (_pData->_pFront),
        sizeof (__Type) * size
    );

    // set other values. back in new buffer, front and capacities 
    _pData->_pFront               = pNewFront;
    _pData->_pBack                = pNewFront + size;
    _pData->_frontCapacity        = _pData->_frontNextCapacity;
    _pData->_frontNextCapacity    = _pData->_frontNextCapacity * 2u;

    // clear old buffer and store new one 
    __Alloc::__free (cds::exchange (_pData->_pBuffer, pNewBuffer));
  }

  // for a given count of elements, decrease front pointer and store address value to be returned via parameter 
  for (Size index = 0u; index < count; ++index) {
    ppElements [count - index - 1u ] = --_pData->_pFront;
  }
}


template <
    typename                                                      __Type,   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
    functional::PredicateFunction <__Type const&, __Type const&>  __equals  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
> auto __ArrayBase <__Type, __equals>::__ab_newBackArray (Size count, __Type** ppElements) noexcept(false) -> void {
  using __Alloc = __allocation::__PrimitiveAlloc <__Type>;  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

  // if empty, initialize 
  if (_pData == nullptr) {
      __ab_init();
  }

  // if back + count is after end of buffer => no space 
  if (_pData->_pBack + count > _pData->_pBuffer + _pData->_frontCapacity + _pData->_backCapacity) {

    // compute next capacity 
    _pData->_backNextCapacity = cds::maxOf (_pData->_backNextCapacity, _pData->_backCapacity + count);

    // reallocate buffer to greater size 
    auto pNewBuffer           = __Alloc::__realloc (__ab_size(), _pData->_pBuffer, _pData->_frontCapacity + _pData->_backNextCapacity);

    // reallocation could create a new buffer, so reset front and back. Also update back capacity and next capacity, and buffer 
    _pData->_pFront           = pNewBuffer + (_pData->_pFront - _pData->_pBuffer);
    _pData->_pBack            = pNewBuffer + (_pData->_pBack - _pData->_pBuffer);
    _pData->_backCapacity     = _pData->_backNextCapacity;
    _pData->_backNextCapacity = _pData->_backNextCapacity * 2u;
    _pData->_pBuffer          = pNewBuffer;
  }

  // for a given count of elements, store the address of back ( as already uninitialized ) and increase it 
  for (Size index = 0u; index < count; ++index) {
    ppElements [index] = _pData->_pBack++;
  }
}


template <
    typename                                                      __Type,   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
    functional::PredicateFunction <__Type const&, __Type const&>  __equals  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
> __CDS_OptimalInline auto __ArrayBase <__Type, __equals>::__ab_newBefore (
    AbstractAddressIterator <__Type> const& iterator
) noexcept(false) -> ElementType* {
  // acquire address indicated by the iterator 
  auto pElement = iterator.absoluteBefore();

  // if array is empty or address is out of bounds, no new element created 
  if (_pData == nullptr || pElement < _pData->_pFront || pElement > _pData->_pBack) {
    return nullptr;
  }

  // if address is of the first element, return new front 
  if (pElement == _pData->_pFront) {
    return __ab_newFront();
  }

  // if address is after the last element, return new back 
  if (pElement == _pData->_pBack) {
    return __ab_newBack();
  }

  // otherwise, create a new element at the index of the address in the array 
  return __ab_newAt (pElement - _pData->_pFront);
}


template <
    typename                                                      __Type,   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
    functional::PredicateFunction <__Type const&, __Type const&>  __equals  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
> __CDS_OptimalInline auto __ArrayBase <__Type, __equals>::__ab_newBeforeConst (
    AbstractAddressIterator <__Type const> const& iterator
) noexcept(false) -> ElementType* {
  // acquire address indicated by the iterator 
  auto pElement = iterator.absoluteBefore();

  // if array is empty or address is out of bounds, no new element created 
  if (_pData == nullptr || pElement < _pData->_pFront || pElement > _pData->_pBack) {
    return nullptr;
  }

  // if address is of the first element, return new front 
  if (pElement == _pData->_pFront) {
    return __ab_newFront();
  }

  // if address is after the last element, return new back 
  if (pElement == _pData->_pBack) {
    return __ab_newBack();
  }

  // otherwise, create a new element at the index of the address in the array 
  return __ab_newAt (pElement - _pData->_pFront);
}


template <
    typename                                                      __Type,   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
    functional::PredicateFunction <__Type const&, __Type const&>  __equals  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
> __CDS_OptimalInline auto __ArrayBase <__Type, __equals>::__ab_newAfter (
    AbstractAddressIterator <__Type> const& iterator
) noexcept(false) -> ElementType* {
  // Special case : after with ReverseIterators. Check if reverse, potential to retrieve out of bounds, but valid, representing front 
  // acquire address indicated by the iterator 
  auto pElement           = iterator.absoluteAfter();
  auto const isReverse    = pElement != iterator.current();

  // If reverse, and at front, return new front 
  if (isReverse && iterator.current() == _pData->_pFront) {
    return __ab_newFront();
  }

  // if array is empty or address is out of bounds, no new element created 
  if (
      _pData == nullptr           ||
      pElement < _pData->_pFront  ||
      pElement >= _pData->_pBack  ||
      (isReverse && iterator.current() == _pData->_pBack)
  ) {
    return nullptr;
  }

  // if address is of the last element, return new back 
  if (!isReverse && pElement + 1u == _pData->_pBack) {
    return __ab_newBack();
  }

  // otherwise, create a new element at the index of the address in the array 
  return __ab_newAt (pElement - _pData->_pFront + 1u);
}


template <
    typename                                                      __Type,   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
    functional::PredicateFunction <__Type const&, __Type const&>  __equals  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
> __CDS_OptimalInline auto __ArrayBase <__Type, __equals>::__ab_newAfterConst (
        AbstractAddressIterator <__Type const> const& iterator
) noexcept(false) -> ElementType* {
  // Special case : after with ReverseIterators. Check if reverse, potential to retrieve out of bounds, but valid, representing front 
  // acquire address indicated by the iterator 
  auto pElement           = iterator.absoluteAfter();
  auto const isReverse    = pElement != iterator.current();

  // If reverse, and at front, return new front 
  if (isReverse && iterator.current() == _pData->_pFront) {
      return __ab_newFront();
  }

  // if array is empty or address is out of bounds, no new element created 
  if (
      _pData == nullptr           ||
      pElement < _pData->_pFront  ||
      pElement >= _pData->_pBack  ||
      (isReverse && iterator.current() == _pData->_pBack)
  ) {
    return nullptr;
  }

  // if address is of the last element, return new back 
  if (!isReverse && pElement + 1u == _pData->_pBack) {
    return __ab_newBack();
  }

  // otherwise, create a new element at the index of the address in the array 
  return __ab_newAt (pElement - _pData->_pFront + 1u);
}


template <
    typename                                                      __Type,   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
    functional::PredicateFunction <__Type const&, __Type const&>  __equals  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
> __CDS_OptimalInline auto __ArrayBase <__Type, __equals>::__ab_newBeforeArray (
        AbstractAddressIterator <__Type> const& iterator,
        Size                                    count,
        __Type**                                ppElements
) noexcept(false) -> bool {
  // acquire address indicated by the iterator 
  auto pElement = iterator.absoluteBefore();

  // if array is empty or address is out of bounds, no new element created 
  if (_pData == nullptr || pElement < _pData->_pFront || pElement > _pData->_pBack) {
    return false;
  }

  if (pElement == _pData->_pFront) {
    // if address is of the first element, return new front array 
    __ab_newFrontArray (count, ppElements);
  } else if ( pElement == _pData->_pBack) {
    // if address is after the last element, return new back 
    __ab_newBackArray (count, ppElements);
  } else {
    // otherwise, create a new element array of elements at the index of the address in the array 
    __ab_newArrayAt (pElement - _pData->_pFront, count, ppElements);
  }

  return true;
}


template <
    typename                                                      __Type,   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
    functional::PredicateFunction <__Type const&, __Type const&>  __equals  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
> __CDS_OptimalInline auto __ArrayBase <__Type, __equals>::__ab_newBeforeArrayConst (
        AbstractAddressIterator <__Type const> const& iterator,
        Size                                          count,
        __Type**                                      ppElements
) noexcept(false) -> bool {
  // acquire address indicated by the iterator 
  auto pElement = iterator.absoluteBefore();

  // if array is empty or address is out of bounds, no new element created 
  if (_pData == nullptr || pElement < _pData->_pFront || pElement > _pData->_pBack ) {
    return false;
  }

  if (pElement == _pData->_pFront) {
    // if address is of the first element, return new front array 
    __ab_newFrontArray (count, ppElements);
  } else if ( pElement == _pData->_pBack ) {
    // if address is after the last element, return new back 
    __ab_newBackArray (count, ppElements);
  } else {
    // otherwise, create a new element array of elements at the index of the address in the array 
    __ab_newArrayAt (pElement - _pData->_pFront, count, ppElements);
  }

  return true;
}


template <
    typename                                                      __Type,   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
    functional::PredicateFunction <__Type const&, __Type const&>  __equals  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
> __CDS_OptimalInline auto __ArrayBase <__Type, __equals>::__ab_newAfterArray (
        AbstractAddressIterator <__Type> const& iterator,
        Size                                    count,
        __Type**                                ppElements
) noexcept(false) -> bool {
  // Special case : after with ReverseIterators. Check if reverse, potential to retrieve out of bounds, but valid, representing front 
  // acquire address indicated by the iterator 
  auto pElement           = iterator.absoluteAfter();
  auto const isReverse    = pElement != iterator.current();

  // If reverse, and at front, return new front 
  if (isReverse && iterator.current() == _pData->_pFront) {
    __ab_newFrontArray (count, ppElements);
    return true;
  }

  // if array is empty or address is out of bounds, no new element created 
  if (
      _pData == nullptr           ||
      pElement < _pData->_pFront  ||
      pElement >= _pData->_pBack  ||
      (isReverse && iterator.current() == _pData->_pBack)
  ) {
    return false;
  }

  if (!isReverse && pElement + 1u == _pData->_pBack) {
    // if address is of the last element, return new back array
    __ab_newBackArray (count, ppElements);
  } else {
    // otherwise, create a new element array of elements at the index of the address in the array
    __ab_newArrayAt (pElement - _pData->_pFront + 1u, count, ppElements);
  }

  return true;
}


template <
    typename                                                      __Type,   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
    functional::PredicateFunction <__Type const&, __Type const&>  __equals  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
> __CDS_OptimalInline auto __ArrayBase <__Type, __equals>::__ab_newAfterArrayConst (
        AbstractAddressIterator <__Type const> const& iterator,
        Size                                          count,
        __Type**                                      ppElements
) noexcept(false) -> bool {

  // Special case : after with ReverseIterators. Check if reverse, potential to retrieve out of bounds, but valid, representing front
  // acquire address indicated by the iterator
  auto pElement           = iterator.absoluteAfter();
  auto const isReverse    = pElement != iterator.current();

  // If reverse, and at front, return new front
  if (isReverse && iterator.current() == _pData->_pFront) {
    __ab_newFrontArray (count, ppElements);
    return true;
  }

  // if array is empty or address is out of bounds, no new element created
  if (
      _pData == nullptr           ||
      pElement < _pData->_pFront  ||
      pElement >= _pData->_pBack  ||
      (isReverse && iterator.current() == _pData->_pBack)
  ) {
    return false;
  }

  if (!isReverse && pElement + 1u == _pData->_pBack) {
    // if address is of the last element, return new back array
    __ab_newBackArray (count, ppElements);
  } else {
    // otherwise, create a new element array of elements at the index of the address in the array
    __ab_newArrayAt (pElement - _pData->_pFront + 1u, count, ppElements);
  }

  // regardless of branch, result is positive
  return true;
}


template <
    typename                                                      __Type,   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
    functional::PredicateFunction <__Type const&, __Type const&>  __equals  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
> auto __ArrayBase <__Type, __equals>::__ab_newAt (Index index) noexcept(false) -> __Type* {
  using __Alloc = __allocation::__PrimitiveAlloc <__Type>;  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

  // if empty, cannot insert at any index other than 0
  if (_pData == nullptr && index != 0) {
    return nullptr;
  }

  // needed to decide : the shift direction of current elements ( less move operations ), current capacity, current size
  auto const fullCapacity     = _pData->_frontCapacity + _pData->_backCapacity;
  auto const size             = __ab_size();

  // decision to shift is always right, based on lower argument
  auto const shouldShiftLeft  = static_cast <Size> (index)  < size;
  auto const canShiftLeft     = _pData->_pBuffer            < _pData->_pFront;
  auto       canShiftRight    = _pData->_pBack              < _pData->_pBuffer + fullCapacity;

  // if it is not possible to shift any direction, reallocation required
  if (!canShiftLeft && !canShiftRight) {

    // choose to shift right always due to realloc being potentially faster. Reallocation in
    // front requires a full memcpy of the array data
    // investigation required as to what could be potentially faster

    // realloc will always increase back capacity
    auto const pNewBuffer     = __Alloc::__realloc (size, _pData->_pBuffer, _pData->_frontCapacity + _pData->_backNextCapacity);

    // update allocation parameters. Potential new buffer due to realloc
    _pData->_pFront           = pNewBuffer + (_pData->_pFront - _pData->_pBuffer);
    _pData->_pBack            = _pData->_pFront + size;
    _pData->_backCapacity     = _pData->_backNextCapacity;
    _pData->_backNextCapacity = _pData->_backNextCapacity * 2u;
    _pData->_pBuffer          = pNewBuffer;
  }

  // based on possibility and intention, decide shift direction
  auto const shiftLeft = canShiftLeft && shouldShiftLeft;

  __Type* pDestination;
  __Type* pSource;
  Size    count;

  if (shiftLeft) {
    // if left, destination is before front
    pDestination = --_pData->_pFront;
    pSource      = pDestination + 1u;
    count        = index;
  } else {
    // otherwise, destination is after given index
    pDestination = _pData->_pFront + index + 1u;
    pSource      = pDestination - 1u;
    count        = size - static_cast <Size> (index);
    ++_pData->_pBack;
  }

  // apply memmove due to potential realloc, same buffer, potential overlap
  (void) std::memmove (
      static_cast <void*> (pDestination),
      static_cast <void const*> (pSource),
      sizeof (__Type) * count
  );

  // the only uninitialized space will be at front + index. Return to be initialized
  return _pData->_pFront + index;
}


template <
    typename                                                      __Type,   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
    functional::PredicateFunction <__Type const&, __Type const&>  __equals  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
> auto __ArrayBase <__Type, __equals>::__ab_newArrayAt (Index index, Size count, __Type** ppElements) noexcept(false) -> void {
  using __Alloc = __allocation::__PrimitiveAlloc <__Type>;  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

  // if empty, cannot insert at any index other than 0
  if (_pData == nullptr && index != 0) {
    return;
  }

  // needed to decide : the shift direction of current elements ( less move operations ), current capacity, current size
  auto const fullCapacity     = _pData->_frontCapacity + _pData->_backCapacity;
  auto const size             = __ab_size();

  // decision to shift is always right, based on lower argument
  auto const shouldShiftLeft  = static_cast <Size> (index)  < size;
  auto const canShiftLeft     = _pData->_pBuffer + count    <= _pData->_pFront;
  auto       canShiftRight    = _pData->_pBack + count      <= _pData->_pBuffer + fullCapacity;

  // a special case exists when there is not enough space for a complete shift, but
  //  there is enough space to shift both ends to cover for the new required element count
  auto const canShiftBoth     = count + size <= fullCapacity;

  // if no shift possible, realloc
  if (!canShiftLeft && !canShiftRight && !canShiftBoth) {
    /// choose to shift right always due to realloc being potentially faster. Reallocation in
    /// front requires a full memcpy of the array data
    /// investigation required as to what could be potentially faster
    _pData->_backNextCapacity = cds::maxOf (_pData->_backNextCapacity, count + _pData->_pBuffer + fullCapacity - _pData->_pBack);

    // realloc will always increase back capacity
    auto const pNewBuffer     = __Alloc::__realloc (size, _pData->_pBuffer, _pData->_frontCapacity + _pData->_backNextCapacity);

    // update allocation parameters. Potential new buffer due to realloc
    _pData->_pFront           = pNewBuffer + (_pData->_pFront - _pData->_pBuffer);
    _pData->_pBack            = _pData->_pFront + size;
    _pData->_backCapacity     = _pData->_backNextCapacity;
    _pData->_backNextCapacity = _pData->_backNextCapacity * 2u;
    _pData->_pBuffer          = pNewBuffer;

    // since a realloc occurred, a shift can be done to the right
    canShiftRight             = true;
  }

  // will store the address of the start of the newly created element space
  __Type* pCreationSpace;

  // if complete shift can be done
  if (canShiftLeft || canShiftRight) {

    // based on possibility and intention, decide shift direction
    auto const  shiftLeft     = canShiftLeft && shouldShiftLeft;
    __Type*     pDestination;
    __Type*     pSource;
    Size        shiftCount;

    if (shiftLeft) {
      // if left, destination is before front
      pDestination    = _pData->_pFront - count,
      pSource         = _pData->_pFront;
      shiftCount      = index;

      // creation space will be at the source + index - count of the move, as those elements will be moved
      pCreationSpace  = pSource + index - count;
      _pData->_pFront -= count;
    } else {
      // otherwise, destination is 'count' positions after given index, where count is the number of newly added elements
      pDestination    = _pData->_pFront + index + count;
      pSource         = _pData->_pFront + index;
      shiftCount      = size - static_cast <Size> (index);

      // creation space will be at the source of the move, as those elements will be moved
      pCreationSpace  = _pData->_pFront + index;
      _pData->_pBack += count;
    }

    // apply memmove, as overlap is possible due to no/a potential realloc on the same buffer
    (void) std::memmove (
        static_cast <void*> (pDestination),
        static_cast <void const*> (pSource),
        sizeof (__Type) * shiftCount
    );
  } else {
    // otherwise, shifting both ways is possible. Always shift right more, as a next-right reallocation is more cost-effective due to realloc
    auto const rightShiftCount = count - (_pData->_pBuffer + fullCapacity - _pData->_pBack);
    // remaining elements are shifted left
    auto const leftShiftCount  = count - rightShiftCount;

    // apply move right
    (void) std::memmove (
        static_cast <void*> (_pData->_pFront + index + rightShiftCount),
        static_cast <void const*> (_pData->_pFront + index),
        sizeof (__Type) * rightShiftCount
    );

    // apply move left
    (void) std::memmove (
        static_cast <void*> (_pData->_pFront - leftShiftCount),
        static_cast <void const*> (_pData->_pFront),
        sizeof (__Type) * leftShiftCount
    );

    // store the creation space, at front + index
    pCreationSpace    = _pData->_pFront + index;

    // update both front and back
    _pData->_pFront  -= leftShiftCount;
    _pData->_pBack   += rightShiftCount;
  }

  // for each of the newly created space, store the addresses to be returned via the out ppElements parameter
  for (Size spaceIndex = 0u; spaceIndex < count; ++spaceIndex) {
    ppElements [spaceIndex] = pCreationSpace++;
  }
}


template <
    typename                                                      __Type,   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
    functional::PredicateFunction <__Type const&, __Type const&>  __equals  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
> __CDS_cpplang_NonConstConstexprMemberFunction auto __ArrayBase <__Type, __equals>::__ab_begin() noexcept -> __ab_Iterator {
  // forward begin iterator is at front, if applicable. nullptr otherwise
  return __ab_Iterator (_pData == nullptr ? nullptr : _pData->_pFront);
}


template <
    typename                                                      __Type,   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
    functional::PredicateFunction <__Type const&, __Type const&>  __equals  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
> __CDS_cpplang_NonConstConstexprMemberFunction auto __ArrayBase <__Type, __equals>::__ab_end() noexcept -> __ab_Iterator {
  // forward end iterator is after back, if applicable. nullptr otherwise
  return __ab_Iterator (_pData == nullptr ? nullptr : _pData->_pBack);
}


template <
    typename                                                      __Type,   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
    functional::PredicateFunction <__Type const&, __Type const&>  __equals  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
> constexpr auto __ArrayBase <__Type, __equals>::__ab_cbegin() const noexcept -> __ab_ConstIterator {
  // forward begin iterator is at front, if applicable. nullptr otherwise
  return __ab_ConstIterator (_pData == nullptr ? nullptr : _pData->_pFront);
}


template <
    typename                                                      __Type,   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
    functional::PredicateFunction <__Type const&, __Type const&>  __equals  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
> constexpr auto __ArrayBase <__Type, __equals>::__ab_cend() const noexcept -> __ab_ConstIterator {
  // forward end iterator is after back, if applicable. nullptr otherwise
  return __ab_ConstIterator (_pData == nullptr ? nullptr : _pData->_pBack);
}


template <
    typename                                                      __Type,   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
    functional::PredicateFunction <__Type const&, __Type const&>  __equals  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
> __CDS_cpplang_NonConstConstexprMemberFunction auto __ArrayBase <__Type, __equals>::__ab_rbegin() noexcept -> __ab_ReverseIterator {
  // backward begin iterator is at back, if applicable. nullptr otherwise
  return __ab_ReverseIterator (_pData == nullptr ? nullptr : _pData->_pBack - 1u);
}


template <
    typename                                                      __Type,   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
    functional::PredicateFunction <__Type const&, __Type const&>  __equals  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
> __CDS_cpplang_NonConstConstexprMemberFunction auto __ArrayBase <__Type, __equals>::__ab_rend() noexcept -> __ab_ReverseIterator {
  // backward end iterator is before front, if applicable. nullptr otherwise
  return __ab_ReverseIterator (_pData == nullptr ? nullptr : _pData->_pFront - 1u);
}


template <
    typename                                                      __Type,   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
    functional::PredicateFunction <__Type const&, __Type const&>  __equals  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
> constexpr auto __ArrayBase <__Type, __equals>::__ab_crbegin() const noexcept -> __ab_ConstReverseIterator {
  // backward begin iterator is at back, if applicable. nullptr otherwise
  return __ab_ConstReverseIterator (_pData == nullptr ? nullptr : _pData->_pBack - 1u);
}


template <
    typename                                                      __Type,   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
    functional::PredicateFunction <__Type const&, __Type const&>  __equals  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
> constexpr auto __ArrayBase <__Type, __equals>::__ab_crend() const noexcept -> __ab_ConstReverseIterator {
  // backward end iterator is before front, if applicable. nullptr otherwise
  return __ab_ConstReverseIterator (_pData == nullptr ? nullptr : _pData->_pFront - 1u);
}


template <
    typename                                                      __Type,   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
    functional::PredicateFunction <__Type const&, __Type const&>  __equals  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
> __CDS_OptimalInline auto __ArrayBase <__Type, __equals>::__ab_removeIterator (
        AbstractAddressIterator <__Type> const& iterator
) noexcept -> bool {
  // Function called to remove an iterator, will call the base remove at index function
  // acquire address of the element.
  auto const pElement = &iterator [0u];

  // if invalid or out of bounds, not possible
  if (_pData == nullptr || !(_pData->_pFront <= pElement && pElement < _pData->_pBack)) {
    return false;
  }

  // remove at index, acquired from element address - front address
  __ab_remove (static_cast <Index> (pElement - _pData->_pFront));
  // successful at this point
  return true;
}


template <
    typename                                                      __Type,   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
    functional::PredicateFunction <__Type const&, __Type const&>  __equals  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
> __CDS_OptimalInline auto __ArrayBase <__Type, __equals>::__ab_removeConstIterator (
        AbstractAddressIterator <__Type const> const& iterator
) noexcept -> bool {
  // Function called to remove an iterator, will call the base remove at index function
  // acquire address of the element.
  auto const pElement = &iterator [0u];

  // if invalid or out of bounds, not possible
  if (_pData == nullptr || !(_pData->_pFront <= pElement && pElement < _pData->_pBack)) {
    return false;
  }

  // remove at index, acquired from element address - front address
  __ab_remove (static_cast <Index> (pElement - _pData->_pFront));
  // successful at this point
  return true;
}


template <
    typename                                                      __Type,   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
    functional::PredicateFunction <__Type const&, __Type const&>  __equals  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
> __CDS_OptimalInline auto __ArrayBase <__Type, __equals>::__ab_removeIteratorArray (
        AbstractAddressIterator <__Type> const* const*  ppIterators,
        Size                                            iteratorCount
) noexcept(false) -> Size {
  using __Alloc = __allocation::__PrimitiveAlloc <__Type>;  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  /// removal of multiple iterators can go one of two ways
  /// 1. create a new buffer to move remaining elements, if capacity is twice more than remaining elements
  /// 2. move the remaining elements to the spaces previously occupied by the removed elements, keeping in mind that iterators point at in-array addresses
  /// regardless, the received iterator array will be ordered by their array order

  // first test scenario 1, compute required size
  auto const  currentSize     = __ab_size();
  auto const  requiredSize    = currentSize - iteratorCount;
  Size        iteratorIndex   = 0u;

  // if scenario 1 applicable
  if (_pData->_frontCapacity + _pData->_backCapacity > cds::maxOf (requiredSize * 2u, __ab_minCapacity)) {
    // start with a buffer with no front capacity, only back, based on max ( min size, required )
    _pData->_frontCapacity      = 0u;
    _pData->_backCapacity       = cds::maxOf (__ab_minCapacity, requiredSize);
    _pData->_frontNextCapacity  = __ab_minCapacity;
    _pData->_backNextCapacity   = _pData->_backCapacity * 2u;

    // allocate a new smaller buffer
    auto pNewBuffer             = __Alloc::__alloc (_pData->_frontCapacity + _pData->_backCapacity);

    // start with the new empty buffer
    auto pNewFront              = pNewBuffer;
    auto pNewBack               = pNewFront;

      // parse current elements
    while (_pData->_pFront != _pData->_pBack && iteratorIndex < iteratorCount) {
      if (&(*(*ppIterators [iteratorIndex])) == _pData->_pFront) {
        // if address of element at iterator is equal to current element address, destroy element and go to next iterator
        _pData->_pFront->~__Type();
        ++iteratorIndex;
      } else {
        // otherwise, move and increase the new back pointer
        (void) std::memcpy (
            static_cast <void*> (pNewBack++),
            static_cast <void const*> (_pData->_pFront),
            sizeof (__Type)
        );
      }

      // go to next element, use current front pointer as current buffer will be discarded in the end
      ++_pData->_pFront;
    }

    // if all iterators have been consumed, move remaining elements
    if (_pData->_pFront != _pData->_pBack) {
      auto const remaining = _pData->_pBack - _pData->_pFront;
      (void) std::memcpy (
          static_cast <void*> (pNewBack),
          static_cast <void const*> (_pData->_pFront),
          sizeof (__Type) * (remaining)
      );

      pNewBack += remaining;
    }

    // update complete, discard old buffer and update front, back and buffer pointer values
    _pData->_pFront   = pNewFront;
    _pData->_pBack    = pNewBack;
    __Alloc::__free (cds::exchange (_pData->_pBuffer, pNewBuffer));

    // removed elements are acquired with difference between starting size and new size
    return currentSize - requiredSize;
  }

  /// otherwise, scenario 2. Start clearing at the front, while applicable. While
  /// iterators point to elements in front, remove and move to next. Also advance front in this
  /// scenario
  while (iteratorIndex < iteratorCount && _pData->_pFront == &(*(*ppIterators [iteratorIndex]))) {
    (_pData->_pFront++)->~__Type ();
    ++ iteratorIndex;
  }

  // keep in mind the number of elements removed from the front
  auto const  frontRemoved    = iteratorIndex;
  // Use two pointers, one for current inspected element, one for the last valid move location
  // pCopyFront will always be behind or equal to pFront
  // When they are equal, no move is done, as no elements have been yet removed
  // When they are not equal, no overlap can happen as iterators will point to yet-unmoved locations
  auto        pFront          = _pData->_pFront;
  auto        pCopyFront      = _pData->_pFront;

  // while iterators exist and array has not been completely parsed
  while (pFront != _pData->_pBack && iteratorIndex < iteratorCount) {
    if (pFront == &(*(*ppIterators [ iteratorIndex ] ) ) ) {
      // if current element is to be removed, destroy it and advance to the next iterator
      (pFront)->~__Type ();
      ++iteratorIndex;
    } else if (pFront != pCopyFront) {
      // if a removal was previously done, pCopyFront will be behind, and will always indicate to
      // safe-to-copy, no overlap memory. Use memcpy. Increase pCopyFront to indicate the next
      // safe-to-copy memory space
      (void) std::memcpy (
          static_cast <void*> (pCopyFront++),
          static_cast <void const*> (pFront),
          sizeof (__Type)
      );
    } else {
      // otherwise, no removal to do, no removal previously done, only advance pCopyFront
      pCopyFront++;
    }
    // always increase lookahead pointer
    ++pFront;
  }

  // if iterators are finished, but lookahead is incomplete, and there have been elements removed
  // ( pCopyFront is different to pFront ), some elements still have to be moved
  if (pFront != _pData->_pBack && pCopyFront != pFront) {
    // remaining elements are determined with back - front
    auto const remaining = _pData->_pBack - pFront;
    // use memmove, potential overlap
    (void) std::memmove (
        static_cast <void*> (pCopyFront),
        static_cast <void const*> (pFront),
        sizeof (__Type) * remaining
    );
  }

  // removed at the back is determined by offset from copyFront and front. ( copyFront increased when no remove is done )
  auto const backRemoved = pFront - pCopyFront;
  // elements have been shifted left, so decrease back pointer
  _pData->_pBack -= backRemoved;
  // removed = frontRemoved + backRemoved
  return backRemoved + frontRemoved;
}


template <
    typename                                                      __Type,   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
    functional::PredicateFunction <__Type const&, __Type const&>  __equals  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
> __CDS_OptimalInline auto __ArrayBase <__Type, __equals>::__ab_removeConstIteratorArray (
        AbstractAddressIterator <__Type const> const* const*  ppIterators,
        Size                                                  iteratorCount
) noexcept(false) -> Size {
  using __Alloc = __allocation::__PrimitiveAlloc <__Type>;  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

  /// removal of multiple iterators can go one of two ways
  /// 1. create a new buffer to move remaining elements, if capacity is twice more than remaining elements
  /// 2. move the remaining elements to the spaces previously occupied by the removed elements, keeping in mind that iterators point at in-array addresses
  /// regardless, the received iterator array will be ordered by their array order

  // first test scenario 1, compute required size
  auto const  currentSize     = __ab_size();
  auto const  requiredSize    = currentSize - iteratorCount;
  Size        iteratorIndex   = 0ULL;

  // if scenario 1 applicable
  if (_pData->_frontCapacity + _pData->_backCapacity > cds::maxOf (requiredSize * 2u, __ab_minCapacity)) {

    // start with a buffer with no front capacity, only back, based on max ( min size, required )
    _pData->_frontCapacity        = 0u;
    _pData->_backCapacity         = cds::maxOf (__ab_minCapacity, requiredSize);
    _pData->_frontNextCapacity    = __ab_minCapacity;
    _pData->_backNextCapacity     = _pData->_backCapacity * 2u;

    // allocate a new smaller buffer
    auto pNewBuffer               = __Alloc::__alloc (_pData->_frontCapacity + _pData->_backCapacity);

    // start with the new empty buffer
    auto pNewFront              = pNewBuffer;
    auto pNewBack               = pNewFront;

    // parse current elements
    while (_pData->_pFront != _pData->_pBack && iteratorIndex < iteratorCount) {
      if (&(*(*ppIterators [iteratorIndex])) == _pData->_pFront) {
        // if address of element at iterator is equal to current element address, destroy element and go to next iterator
        _pData->_pFront->~__Type();
        ++iteratorIndex;
      } else {
        // otherwise, move and increase the new back pointer
        (void) std::memcpy (
            static_cast <void*> (pNewBack++),
            static_cast <void const*> (_pData->_pFront),
            sizeof (__Type)
        );
      }
      // go to next element, use current front pointer as current buffer will be discarded in the end
      ++_pData->_pFront;
    }

    // if all iterators have been consumed, move remaining elements
    if (_pData->_pFront != _pData->_pBack) {
      auto const remaining = _pData->_pBack - _pData->_pFront;
      (void) std::memcpy (
          static_cast <void*> (pNewBack),
          static_cast <void const*> (_pData->_pFront),
          sizeof (__Type) * ( remaining )
      );

      pNewBack += remaining;
    }

    // update complete, discard old buffer and update front, back and buffer pointer values
    _pData->_pFront   = pNewFront;
    _pData->_pBack    = pNewBack;
    __Alloc::__free (cds::exchange (_pData->_pBuffer, pNewBuffer));

    // removed elements are acquired with difference between starting size and new size
    return currentSize - requiredSize;
  }

  /// otherwise, scenario 2. Start clearing at the front, while applicable. While
  /// iterators point to elements in front, remove and move to next. Also advance front in this
  /// scenario
  while (iteratorIndex < iteratorCount && _pData->_pFront == &(*(*ppIterators [iteratorIndex]))) {
    (_pData->_pFront++)->~__Type();
    ++iteratorIndex;
  }

  // keep in mind the number of elements removed from the front
  auto const  frontRemoved    = iteratorIndex;

  // use two pointers, one for current inspected element, one for the last valid move location
  // pCopyFront will always be behind or equal to pFront
  // When they are equal, no move is done, as no elements have been yet removed
  // When they are not equal, no overlap can happen as iterators will point to yet-unmoved locations
  auto        pFront          = _pData->_pFront;
  auto        pCopyFront      = _pData->_pFront;

  // while iterators exist and array has not been completely parsed
  while (pFront != _pData->_pBack && iteratorIndex < iteratorCount) {
    if (pFront == &(*(*ppIterators [iteratorIndex]))) {
      // if current element is to be removed, destroy it and advance to the next iterator
      (pFront)->~__Type();
      ++iteratorIndex;
    } else if (pFront != pCopyFront) {
      // if a removal was previously done, pCopyFront will be behind, and will always indicate to
      // safe-to-copy, no overlap memory. Use memcpy. Increase pCopyFront to indicate the next
      // safe-to-copy memory space
      (void) std::memcpy (
          static_cast <void*> (pCopyFront++),
          static_cast <void const*> (pFront),
          sizeof (__Type)
      );
    } else {
      // otherwise, no removal to do, no removal previously done, only advance pCopyFront
      pCopyFront++;
    }
    // always increase lookahead pointer
    ++pFront;
  }

  // if iterators are finished, but lookahead is incomplete, and there have been elements removed
  // ( pCopyFront is different to pFront ), some elements still have to be moved
  if (pFront != _pData->_pBack) {
    // remaining elements are determined with back - front
    auto const remaining = _pData->_pBack - pFront;
    // use memmove, potential overlap
    (void) std::memmove (
        static_cast <void*> (pCopyFront),
        static_cast <void const*> (pFront),
        sizeof (__Type) * remaining
    );
  }

  // removed at the back is determined by offset from copyFront and front. ( copyFront increased when no remove is done )
  auto const backRemoved = pFront - pCopyFront;
  // elements have been shifted left, so decrease back pointer
  _pData->_pBack -= backRemoved;
  // removed = frontRemoved + backRemoved
  return backRemoved + frontRemoved;
}


template <
    typename                                                      __Type,   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
    functional::PredicateFunction <__Type const&, __Type const&>  __equals  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
> constexpr auto __ArrayBase <__Type, __equals>::__ab_data() const noexcept -> __Type const* {
  // when applicable, return the address to the front of the buffer. Otherwise, nullptr as there is no data
  return _pData == nullptr ? nullptr : _pData->_pFront;
}


template <
    typename                                                      __Type,   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
    functional::PredicateFunction <__Type const&, __Type const&>  __equals  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
> __CDS_cpplang_NonConstConstexprMemberFunction auto __ArrayBase <__Type, __equals>::__ab_data () noexcept -> __Type* {
  // when applicable, return the address to the front of the buffer. Otherwise, nullptr as there is no data
  return _pData == nullptr ? nullptr : _pData->_pFront;
}


template <
    typename                                                      __Type,   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
    functional::PredicateFunction <__Type const&, __Type const&>  __equals  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
> template <
    typename __TElementType,                                        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    cds::meta::EnableIf <cds::meta::IsDefaultConstructible <__TElementType>::value>
> __CDS_OptimalInline auto __ArrayBase <__Type, __equals>::__ab_resize (Size size) noexcept(false) -> void {
  using __Alloc = __allocation::__PrimitiveAlloc <__Type>;  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

  // if no data exists, initialize allocation data
  if (_pData == nullptr) {
    __ab_init();
  }

  // acquire current size
  auto const currentSize = __ab_size();
  // clear elements found after the new end, if applicable ( new size < actual size )
  for (Size index = size; index < currentSize; ++index) {
    // decrease back, destroy each
    (--_pData->_pBack)->~__Type();
  }

  // acquire pointer at the actual buffer end
  auto const pEnd = _pData->_pBuffer + _pData->_backCapacity + _pData->_frontCapacity;
  // if size does not fit between front and actual memory end, reallocation required. Do not shift, as it is time-ineffective
  if (size > pEnd - _pData->_pFront) {
    // new back capacity is max ( next, size + required )
    _pData->_backCapacity     = cds::maxOf (_pData->_backNextCapacity, _pData->_backCapacity + (size - currentSize ));
    auto const pNewBuffer     = __Alloc::__realloc (__ab_size(), _pData->_pBuffer, _pData->_backCapacity + _pData->_backCapacity);
    // update memory & allocation parameters
    _pData->_backNextCapacity = _pData->_backCapacity * 2u;
    _pData->_pFront           = pNewBuffer + (_pData->_pFront - _pData->_pBuffer);
    _pData->_pBack            = pNewBuffer + (_pData->_pBack - _pData->_pBuffer);
    _pData->_pBuffer          = pNewBuffer;
  }

  // initialize new memory space with default constructor,
  // if applicable ( new size > actual size )
  for (Size index = currentSize; index < size; ++index) {
    new (_pData->_pBack++) __Type();
  }
}


template <
    typename                                                      __Type,   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
    functional::PredicateFunction <__Type const&, __Type const&>  __equals  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
> template <
    typename __TElementType,                                        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    cds::meta::EnableIf <cds::meta::IsCopyConstructible <__TElementType>::value>
> __CDS_OptimalInline auto __ArrayBase <__Type, __equals>::__ab_resize (Size size, __Type const& defaultValue) noexcept(false) -> void {
  using __Alloc = __allocation::__PrimitiveAlloc <__Type>;  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

  // if no data exists, initialize allocation data
  if (_pData == nullptr) {
    __ab_init();
  }

  // acquire current size
  auto const currentSize = __ab_size();
  // clear elements found after the new end, if applicable ( new size < actual size )
  for (Size index = size; index < currentSize; ++index) {
    // decrease back, destroy each
    (--_pData->_pBack)->~__Type();
  }

  // acquire pointer at the actual buffer end
  auto const pEnd = _pData->_pBuffer + _pData->_backCapacity + _pData->_frontCapacity;
  // if size does not fit between front and actual memory end, reallocation required. Do not shift, as it is time-ineffective
  if (size > pEnd - _pData->_pFront) {
    // new back capacity is max ( next, size + required )
    _pData->_backCapacity     = cds::maxOf (_pData->_backNextCapacity, _pData->_backCapacity + (size - currentSize));
    auto const pNewBuffer     = __Alloc::__realloc (__ab_size(), _pData->_pBuffer, _pData->_backCapacity + _pData->_backCapacity);
    // update memory & allocation parameters
    _pData->_backNextCapacity = _pData->_backCapacity * 2u;
    _pData->_pFront           = pNewBuffer + (_pData->_pFront - _pData->_pBuffer);
    _pData->_pBack            = pNewBuffer + (_pData->_pBack - _pData->_pBuffer);
    _pData->_pBuffer          = pNewBuffer;
  }

  // initialize new memory space with copy constructor with default value,
  // if applicable ( new size > actual size )
  for (Size index = currentSize; index < size; ++index) {
    new (_pData->_pBack++) __Type (defaultValue);
  }
}


template <
    typename                                                      __Type,   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
    functional::PredicateFunction <__Type const&, __Type const&>  __equals  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
> __CDS_OptimalInline auto __ArrayBase <__Type, __equals>::__ab_shrink (Size size) noexcept -> void {
  // if no data exists, no shrink required
  if (_pData == nullptr) {
    return;
  }

  // acquire intended new back address
  auto const pEnd = _pData->_pFront + size;
  // while actual back > new back
  while (_pData->_pBack > pEnd) {
    // destroy elements at back and decrease the back pointer
    (--_pData->_pBack)->~__Type();
  }
}


template <
    typename                                                      __Type,   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
    functional::PredicateFunction <__Type const&, __Type const&>  __equals  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
> __CDS_OptimalInline auto __ArrayBase <__Type, __equals>::__ab_reserve (Size size) noexcept(false) -> void {
  using __Alloc = __allocation::__PrimitiveAlloc <__Type>;  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

  if (_pData == nullptr) {
    // if nothing exists already, initialize
    __ab_init();
  } else if (_pData->_backCapacity > size) {
    // if buffer can already contain required element count and was previously initialized ( buffer exists ), do nothing
    return;
  }

  // increase back capacity, reallocate buffer, but do not initialize elements
  _pData->_backCapacity     = cds::maxOf (_pData->_backNextCapacity, size);
  auto const pNewBuffer     = __Alloc::__realloc (__ab_size(), _pData->_pBuffer, _pData->_backCapacity + _pData->_frontCapacity);
  // update memory parameters
  _pData->_pFront           = pNewBuffer + _pData->_pFront - _pData->_pBuffer;
  _pData->_pBack            = pNewBuffer + _pData->_pBack - _pData->_pBuffer;
  _pData->_backNextCapacity = _pData->_backCapacity * 2u;
  _pData->_pBuffer          = pNewBuffer;
}


template <
    typename                                                      __Type,   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
    functional::PredicateFunction <__Type const&, __Type const&>  __equals  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
> template <
    typename __TElementType,                                                // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    cds::meta::EnableIf <cds::meta::IsCopyConstructible <__TElementType>::value>
> __CDS_OptimalInline auto __ArrayBase <__Type, __equals>::__ab_copy (__ArrayBase const& array) noexcept(false) -> void {
  // if no memory data exists, initialize. Otherwise, clear only buffer data
  if (_pData == nullptr) {
    __ab_init();
  } else {
    __ab_clear(false);
  }
  // use copy without clear requirement, since cleanup was already done above
  __ab_copyCleared (array);
}


template <
    typename                                                      __Type,   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
    functional::PredicateFunction <__Type const&, __Type const&>  __equals  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
> template <
    typename __TElementType,                                                // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    cds::meta::EnableIf <cds::meta::IsCopyConstructible <__TElementType>::value>
> auto __ArrayBase <__Type, __equals>::__ab_copyCleared (__ArrayBase const& array) noexcept(false) -> void {
  using __Alloc = __allocation::__PrimitiveAlloc <__Type>;  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

  // acquire given array size
  auto const requiredSize = array.__ab_size();
  // if elements do not fit
  if (_pData->_frontCapacity + _pData->_backCapacity < requiredSize) {
    // reallocate, as front space will not be created in copy
    _pData->_backCapacity = cds::maxOf (requiredSize, __ab_minCapacity);
    _pData->_pBuffer      = __Alloc::__realloc (0u, _pData->_pBuffer, _pData->_backCapacity);
  } else {
    // otherwise, move elements at the front, all front space becomes space at the back
    _pData->_backCapacity += _pData->_frontCapacity;
  }

  // update memory parameters
  _pData->_backNextCapacity     = _pData->_backCapacity * 2u;
  _pData->_frontCapacity        = 0u;
  _pData->_frontNextCapacity    = __ab_minCapacity;
  _pData->_pFront               = _pData->_pBuffer;
  _pData->_pBack                = _pData->_pBuffer + requiredSize;

  // copy one-by-one with copy constructor
  for (Size index = 0u; index < requiredSize; ++ index) {
    new (_pData->_pFront + index) __Type (*(array._pData->_pFront + index));
  }
}


template <
    typename                                                      __Type,   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
    functional::PredicateFunction <__Type const&, __Type const&>  __equals  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
> __CDS_MaybeUnused __CDS_OptimalInline auto __ArrayBase <__Type, __equals>::__ab_move (__ArrayBase&& array) noexcept -> void {
  // clear whole memory contents, including memory data
  __ab_clear (true);
  // use move cleared
  __ab_moveCleared (std::move (array));
}


template <
    typename                                                      __Type,   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
    functional::PredicateFunction <__Type const&, __Type const&>  __equals  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
> __CDS_cpplang_NonConstConstexprMemberFunction auto __ArrayBase <__Type, __equals>::__ab_moveCleared (
    __ArrayBase&& array
) noexcept -> void {
  // acquire memory data of given array.
  _pData = cds::exchange (array._pData, nullptr);
}


template <
    typename                                                      __Type,   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
    functional::PredicateFunction <__Type const&, __Type const&>  __equals  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
> __CDS_MaybeUnused __CDS_cpplang_ConstexprConditioned auto __ArrayBase <__Type, __equals>::__ab_equals (
    __ArrayBase const& array
) const noexcept -> bool {
  // self comparison, memory data can be used directly to check the case of null arrays
  if (_pData == array._pData) {
    return true;
  }

  // if only one is not initialized, not equal
  if (_pData == nullptr || array._pData == nullptr) {
    return false;
  }

  auto const thisSize     = __ab_size();
  auto const otherSize    = array.__ab_size();
  // different sizes => not equal
  if (thisSize != otherSize) {
    return false;
  }

  // otherwise, start parsing
  auto thisFront    = _pData->_pFront;
  auto otherFront   = array._pData->_pFront;

  // equal in size, so only use this array's end as parse limit
  while (thisFront != _pData->_pBack) {
    // if any element is not equal to the other, not equal
    if (!__equals (*thisFront, *otherFront)) {
      return false;
    }

    // otherwise, go ahead in both arrays
    ++thisFront;
    ++otherFront;
  }

  // parse ended and no return => all elements are equal
  return true;
}


template <
    typename                                                      __Type,   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
    functional::PredicateFunction <__Type const&, __Type const&>  __equals  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
> template <
    typename __Comparator                                                   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> auto __ArrayBase <__Type, __equals>::__ab_sort (__Comparator const& comparator) noexcept -> void {
  if (_pData == nullptr) {
    return;
  }
  cds::introSort (_pData->_pFront, _pData->_pBack, comparator);
}

} // namespace __impl
} // namespace __hidden
} // namespace cds

#endif // __CDS_SHARED_ARRAY_BASE_IMPL_HPP__ 
