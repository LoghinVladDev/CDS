// 
// Created by loghin on 18/07/22.
//

#ifndef __CDS_SHARED_DOUBLE_LINKED_LIST_IMPL_HPP__ // NOLINT(llvm-header-guard)
#define __CDS_SHARED_DOUBLE_LINKED_LIST_IMPL_HPP__ // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
#pragma once

namespace cds {       // NOLINT(modernize-concat-nested-namespaces)
namespace __hidden {  // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
namespace __impl {    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

template <
    typename                                                                    __ElementType,  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__ElementType const&, __ElementType const&>  __equals        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> __CDS_OptimalInline auto __DoubleLinkedList <__ElementType, __equals>::__dll_allocateNode() noexcept(false) -> __NodeType* {
  using __Alloc = __allocation::__PrimitiveAlloc <__NodeType>;  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  return __Alloc::__alloc();
}


template <
    typename                                                                    __ElementType,  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__ElementType const&, __ElementType const&>  __equals        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> __CDS_OptimalInline auto __DoubleLinkedList <__ElementType, __equals> :: __dll_freeNode (
    __NodeType* pNode
) noexcept -> void {
  using __Alloc = __allocation::__PrimitiveAlloc <__NodeType>;  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  pNode->_data.~__ElementType();
  return __Alloc::__free (pNode);
}


template <
    typename                                                                    __ElementType,  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__ElementType const&, __ElementType const&>  __equals        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> constexpr __DoubleLinkedList <__ElementType, __equals>::__DoubleLinkedList () noexcept = default;


template <
    typename                                                                    __ElementType,  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__ElementType const&, __ElementType const&>  __equals        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> __CDS_OptimalInline __DoubleLinkedList <__ElementType, __equals>::__DoubleLinkedList (
        __DoubleLinkedList const& list
) noexcept(false) {
  __dll_copyCleared (list);
}


template <
    typename                                                                    __ElementType,  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__ElementType const&, __ElementType const&>  __equals        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> constexpr __DoubleLinkedList <__ElementType, __equals>::__DoubleLinkedList (
    __DoubleLinkedList&& list
) noexcept :
    _pFront (cds::exchange (list._pFront, nullptr)),
    _pBack (cds::exchange (list._pBack, nullptr)),
    _size (cds::exchange (list._size, 0u)){

}


template <
    typename                                                                    __ElementType,  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__ElementType const&, __ElementType const&>  __equals        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> auto __DoubleLinkedList <__ElementType, __equals>::__dll_clear () noexcept -> void {
  while (_pFront != nullptr) {
    auto pCopy  = _pFront;
    _pFront     = _pFront->_pNext;
    __dll_freeNode (pCopy);
  }
  _pBack  = nullptr;
  _size   = 0u;
}


template <
    typename                                                                    __ElementType,  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__ElementType const&, __ElementType const&>  __equals        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> constexpr auto __DoubleLinkedList <__ElementType, __equals>::__dll_empty () const noexcept -> bool {
  return _pFront == nullptr;
}


template <
    typename                                                                    __ElementType,  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__ElementType const&, __ElementType const&>  __equals        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> constexpr auto __DoubleLinkedList <__ElementType, __equals>::__dll_size () const noexcept -> Size {
  return _size;
}


template <
    typename                                                                    __ElementType,  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__ElementType const&, __ElementType const&>  __equals        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> constexpr auto __DoubleLinkedList <__ElementType, __equals>::__dll_front () const noexcept -> __ElementType const* {
  return _pFront == nullptr ? nullptr : &_pFront->_data;
}


template <
    typename                                                                    __ElementType,  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__ElementType const&, __ElementType const&>  __equals        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> constexpr auto __DoubleLinkedList <__ElementType, __equals>::__dll_back () const noexcept -> __ElementType const* {
  return _pBack == nullptr ? nullptr : &_pBack->_data;
}


template <
    typename                                                                    __ElementType,  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__ElementType const&, __ElementType const&>  __equals        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> __CDS_cpplang_NonConstConstexprMemberFunction auto __DoubleLinkedList <__ElementType, __equals>::__dll_front () noexcept -> __ElementType* {
  return _pFront == nullptr ? nullptr : &_pFront->_data;
}


template <
    typename                                                                    __ElementType,  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__ElementType const&, __ElementType const&>  __equals        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> __CDS_cpplang_NonConstConstexprMemberFunction auto __DoubleLinkedList <__ElementType, __equals>::__dll_back () noexcept -> __ElementType* {
  return _pBack == nullptr ? nullptr : &_pBack->_data;
}


template <
    typename                                                                    __ElementType,  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__ElementType const&, __ElementType const&>  __equals        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> auto __DoubleLinkedList <__ElementType, __equals>::__dll_removeFront () noexcept -> void {
  if (__dll_empty()) {
    return;
  }

  auto pCopy  = _pFront;
  _pFront     = _pFront->_pNext;
  __dll_freeNode (pCopy);

  if (_pFront == nullptr) {
    _pBack = nullptr;
  } else {
    _pFront->_pPrevious = nullptr;
  }
  --_size;
}


template <
    typename                                                                    __ElementType,  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__ElementType const&, __ElementType const&>  __equals        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> auto __DoubleLinkedList <__ElementType, __equals>::__dll_removeBack () noexcept -> void {
  if ( __dll_empty() ) {
    return;
  }

  auto pCopy = _pBack;
  _pBack     = _pBack->_pPrevious;
  __dll_freeNode (pCopy);

  if ( _pBack == nullptr ) {
    _pFront = nullptr;
  } else {
    _pBack->_pNext = nullptr;
  }

-- _size;
}


template <
    typename                                                                    __ElementType,  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__ElementType const&, __ElementType const&>  __equals        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> auto __DoubleLinkedList <__ElementType, __equals>::__dll_removeIterator (
    AbstractBidirectionalNodeIterator < __ElementType > const& iterator
) noexcept -> bool {

  if (iterator._pCurrentNode == nullptr) {
    return false;
  }

  if (iterator._pCurrentNode == _pFront) {
    __dll_removeFront();
    return true;
  }

  if (iterator._pCurrentNode == _pBack) {
    __dll_removeBack();
    return true;
  }

  auto pNode = iterator._pCurrentNode;
  pNode->_pPrevious->_pNext = pNode->_pNext;
  pNode->_pNext->_pPrevious = pNode->_pPrevious;
  __dll_freeNode ( pNode );
  --_size;
  return true;
}


template <
    typename                                                                    __ElementType,  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__ElementType const&, __ElementType const&>  __equals        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> auto __DoubleLinkedList <__ElementType, __equals>::__dll_removeConstIterator (
    AbstractBidirectionalNodeIterator <__ElementType const> const& iterator
) noexcept -> bool {

  if (iterator._pCurrentNode == nullptr) {
    return false;
  }

  if (iterator._pCurrentNode == _pFront) {
    __dll_removeFront();
    return true;
  }

  if (iterator._pCurrentNode == _pBack) {
    __dll_removeBack();
    return true;
  }

  auto pNode = const_cast <__NodeType*> (iterator._pCurrentNode);
  pNode->_pPrevious->_pNext = pNode->_pNext;
  pNode->_pNext->_pPrevious = pNode->_pPrevious;
  __dll_freeNode (pNode);
  --_size;
  return true;
}


template <
    typename                                                                    __ElementType,  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__ElementType const&, __ElementType const&>  __equals        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> auto __DoubleLinkedList <__ElementType, __equals>::__dll_removeIteratorArray (
    AbstractBidirectionalNodeIterator <__ElementType> const* const* ppIterators,
    Size                                                            iteratorCount
) noexcept -> Size {
  Size removedCount = 0u;
  for (Size index = 0u; index < iteratorCount; ++index) {
    if (__dll_removeIterator (*ppIterators [index])) {
      ++removedCount;
    }
  }
  return removedCount;
}


template <
    typename                                                                    __ElementType,  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__ElementType const&, __ElementType const&>  __equals        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> auto __DoubleLinkedList <__ElementType, __equals>::__dll_removeConstIteratorArray (
        AbstractBidirectionalNodeIterator <__ElementType const> const* const*  ppIterators,
        Size                                                                  iteratorCount
) noexcept -> Size {
  Size removedCount = 0u;
  for (Size index = 0u; index < iteratorCount; ++index) {
    if (__dll_removeConstIterator (*ppIterators [index])) {
      ++removedCount;
    }
  }
  return removedCount;
}


template <
    typename                                                                    __ElementType,  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__ElementType const&, __ElementType const&>  __equals        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> auto __DoubleLinkedList <__ElementType, __equals>::__dll_removeAt (Index index) noexcept -> void {
  if (__dll_empty()) {
    return;
  }

  if (index == 0) {
    return __dll_removeFront();
  }

  if (index == _size - 1u) {
      return __dll_removeBack();
  }

  Index current = 0;
  auto pHead = _pFront;
  __NodeType* pToRemove = nullptr;
  while (pHead != nullptr) {
    if (current == index) {
      pToRemove = pHead;
      break;
    }
    pHead = pHead->_pNext;
    ++current;
  }

  pToRemove->_pPrevious->_pNext = pToRemove->_pNext;
  pToRemove->_pNext->_pPrevious = pToRemove->_pPrevious;
  __dll_freeNode (pToRemove);
}


template <
    typename                                                                    __ElementType,  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__ElementType const&, __ElementType const&>  __equals        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> auto __DoubleLinkedList <__ElementType, __equals>::__dll_get (Index index) noexcept -> __ElementType* {
  if (__dll_empty()) {
      return nullptr;
  }

  Index current = 0;
  auto pHead = _pFront;
  while (pHead != nullptr) {
      if (current == index) {
          return &pHead->_data;
      }
      pHead = pHead->_pNext;
      ++current;
  }

  return nullptr;
}


template <
    typename                                                                    __ElementType,  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__ElementType const&, __ElementType const&>  __equals        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> auto __DoubleLinkedList <__ElementType, __equals>::__dll_get (Index index) const noexcept -> __ElementType const* {
  if (__dll_empty()) {
    return nullptr;
  }

  Index current = 0;
  auto pHead = _pFront;
  while (pHead != nullptr) {
    if (current == index) {
      return &pHead->_data;
    }
    pHead = pHead->_pNext;
    ++current;
  }

  return nullptr;
}


template <
    typename                                                                    __ElementType,  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__ElementType const&, __ElementType const&>  __equals        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> auto __DoubleLinkedList <__ElementType, __equals>::__dll_newFront () noexcept(false) -> __ElementType* {
  __NodeType* pNewNode  = __dll_allocateNode();
  pNewNode->_pNext      = _pFront;
  pNewNode->_pPrevious  = nullptr;

  if (_pFront != nullptr) {
    _pFront->_pPrevious = pNewNode;
  }

  _pFront = pNewNode;
  if (_pBack == nullptr) {
    _pBack = pNewNode;
  }

  ++_size;
  return &pNewNode->_data;
}


template <
    typename                                                                    __ElementType,  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__ElementType const&, __ElementType const&>  __equals        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> auto __DoubleLinkedList <__ElementType, __equals>::__dll_newBack () noexcept(false) -> __ElementType* {
  __NodeType* pNewNode  = __dll_allocateNode();
  pNewNode->_pPrevious  = _pBack;
  pNewNode->_pNext      = nullptr;

  if (_pBack != nullptr) {
    _pBack->_pNext = pNewNode;
  }

  _pBack = pNewNode;
  if (_pFront == nullptr) {
    _pFront = pNewNode;
  }
  ++_size;
  return &pNewNode->_data;
}


template <
    typename                                                                    __ElementType,  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__ElementType const&, __ElementType const&>  __equals        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> auto __DoubleLinkedList <__ElementType, __equals>::__dll_newFrontArray (
    Size            count,
    __ElementType** ppElements
) noexcept(false) -> void {
  if (count == 0u) {
    return;
  }

  __NodeType* pChainFront     = __dll_allocateNode();
  __NodeType* pChainPrevious  = pChainFront;
  __NodeType* pChainCurrent   = pChainPrevious;
  pChainPrevious->_pPrevious  = nullptr;

  for (Size index = 0u; index + 1u < count; ++index) {
    ppElements [index]        = &pChainPrevious->_data;
    pChainCurrent             = __dll_allocateNode();
    pChainPrevious->_pNext    = pChainCurrent;
    pChainCurrent->_pPrevious = pChainPrevious;
    pChainPrevious            = pChainCurrent;
  }

  ppElements [count - 1u] = &pChainCurrent->_data;
  pChainCurrent->_pNext     = _pFront;
  if (_pFront != nullptr) {
    _pFront->_pPrevious = pChainCurrent;
  }

  _pFront = pChainFront;
  if ( _pBack == nullptr ) {
    _pBack = pChainCurrent;
  }

  _size += count;
}


template <
    typename                                                                    __ElementType,  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__ElementType const&, __ElementType const&>  __equals        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> auto __DoubleLinkedList <__ElementType, __equals>::__dll_newBackArray (
    Size            count,
    __ElementType** ppElements
) noexcept(false) -> void {
  if (count == 0u) {
    return;
  }

  __NodeType* pChainFront     = __dll_allocateNode();
  __NodeType* pChainPrevious  = pChainFront;
  __NodeType* pChainCurrent   = pChainPrevious;

  for (Size index = 0u; index + 1u < count; ++index) {
    ppElements [index]        = &pChainPrevious->_data;
    pChainCurrent             = __dll_allocateNode();
    pChainPrevious->_pNext    = pChainCurrent;
    pChainCurrent->_pPrevious = pChainPrevious;
    pChainPrevious            = pChainCurrent;
  }

  ppElements [count - 1u] = &pChainCurrent->_data;
  pChainFront->_pPrevious = _pBack;
  if (_pBack != nullptr) {
    _pBack->_pNext = pChainFront;
  }

  pChainCurrent->_pNext = nullptr;
  _pBack = pChainCurrent;
  if (_pFront == nullptr) {
    _pFront = pChainFront;
  }

  _size += count;
}


template <
    typename                                                                    __ElementType,  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__ElementType const&, __ElementType const&>  __equals        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> auto __DoubleLinkedList <__ElementType, __equals>::__dll_newAddress (
    __ElementType const*  pReferenceElement,
    bool*                 pNewElementCreated
) noexcept(false) -> __ElementType* {
  (void) pReferenceElement;
  *pNewElementCreated = true;
  return __dll_newBack();
}


template <
    typename                                                                    __ElementType,  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__ElementType const&, __ElementType const&>  __equals        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> auto __DoubleLinkedList <__ElementType, __equals>::__dll_newBetweenNodes (
    __NodeType const* pPrevious,
    __NodeType const* pCurrent
) noexcept(false) -> __ElementType* {
  __NodeType* pNewNode  = __dll_allocateNode();
  pNewNode->_pNext      = const_cast <__NodeType*> (pCurrent);
  pNewNode->_pPrevious  = const_cast <__NodeType*> (pPrevious);

  if (pNewNode->_pNext != nullptr) {
    pNewNode->_pNext->_pPrevious = pNewNode;
  } else {
    _pBack = pNewNode;
  }

  if (pNewNode->_pPrevious != nullptr) {
    pNewNode->_pPrevious->_pNext = pNewNode;
  } else {
    _pFront = pNewNode;
  }

  ++_size;
  return &pNewNode->_data;
}


template <
    typename                                                                    __ElementType,  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__ElementType const&, __ElementType const&>  __equals        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> auto __DoubleLinkedList <__ElementType, __equals>::__dll_newBetweenNodesArray (
    __NodeType const* pPrevious,
    __NodeType const* pCurrent,
    Size              count,
    __ElementType**   ppElements
) noexcept(false) -> void {
  __NodeType* pChainFront     = __dll_allocateNode();
  __NodeType* pChainPrevious  = pChainFront;
  __NodeType* pChainCurrent   = pChainPrevious;

  for (Size index = 0u; index + 1u < count; ++index) {
    ppElements [index]        = &pChainPrevious->_data;
    pChainCurrent             = __dll_allocateNode();
    pChainPrevious->_pNext    = pChainCurrent;
    pChainCurrent->_pPrevious = pChainPrevious;
    pChainPrevious            = pChainCurrent;
  }

  ppElements [count - 1u] = &pChainCurrent->_data;
  pChainCurrent->_pNext   = const_cast <__NodeType*> (pCurrent);
  pChainFront->_pPrevious = const_cast <__NodeType*> (pPrevious);

  if (pChainCurrent->_pNext != nullptr) {
    pChainCurrent->_pNext->_pPrevious   = pChainCurrent;
  }

  if (pChainFront->_pPrevious != nullptr) {
    pChainFront->_pPrevious->_pNext     = pChainFront;
  }

  _size += count;
}


template <
    typename                                                                    __ElementType,  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__ElementType const&, __ElementType const&>  __equals        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> auto __DoubleLinkedList <__ElementType, __equals>::__dll_newBefore (
    AbstractBidirectionalNodeIterator <__ElementType> const& iterator
) noexcept(false) -> __ElementType* {
  auto const reversed =
      (_pFront == iterator._pPreviousNode && iterator._pCurrentNode == nullptr) ||
      (iterator._pCurrentNode != nullptr && iterator._pCurrentNode->_pNext == iterator._pPreviousNode);

  if (__dll_empty() || iterator._pCurrentNode == nullptr && iterator._pPreviousNode == nullptr) {
    return nullptr;
  }

  if (
      !reversed && iterator._pCurrentNode == _pFront && iterator._pPreviousNode == nullptr ||
      reversed && iterator._pPreviousNode == _pFront && iterator._pCurrentNode == nullptr
  ) {
    return __dll_newFront ();
  }

  if (
      !reversed && iterator._pCurrentNode == nullptr && iterator._pPreviousNode == _pBack ||
      reversed && iterator._pPreviousNode == nullptr && iterator._pCurrentNode == _pBack
  ) {
    return __dll_newBack ();
  }

  return !reversed
      ? __dll_newBetweenNodes (iterator._pPreviousNode, iterator._pCurrentNode)
      : __dll_newBetweenNodes (iterator._pCurrentNode, iterator._pPreviousNode);
}


template <
    typename                                                                    __ElementType,  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__ElementType const&, __ElementType const&>  __equals        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> auto __DoubleLinkedList <__ElementType, __equals>::__dll_newBeforeConst (
    AbstractBidirectionalNodeIterator <__ElementType const> const& iterator
) noexcept(false) -> __ElementType* {
  auto const reversed =
      (_pFront == iterator._pPreviousNode && iterator._pCurrentNode == nullptr) ||
      (iterator._pCurrentNode != nullptr && iterator._pCurrentNode->_pNext == iterator._pPreviousNode);

  if (__dll_empty() || iterator._pCurrentNode == nullptr && iterator._pPreviousNode == nullptr) {
    return nullptr;
  }

  if (
      !reversed && iterator._pCurrentNode == _pFront && iterator._pPreviousNode == nullptr ||
      reversed && iterator._pPreviousNode == _pFront && iterator._pCurrentNode == nullptr
  ) {
    return __dll_newFront ();
  }

  if (
      !reversed && iterator._pCurrentNode == nullptr && iterator._pPreviousNode == _pBack ||
      reversed && iterator._pPreviousNode == nullptr && iterator._pCurrentNode == _pBack
  ) {
    return __dll_newBack ();
  }

  return !reversed
      ? __dll_newBetweenNodes (iterator._pPreviousNode, iterator._pCurrentNode)
      : __dll_newBetweenNodes (iterator._pCurrentNode, iterator._pPreviousNode);
}


template <
    typename                                                                    __ElementType,  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__ElementType const&, __ElementType const&>  __equals        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> auto __DoubleLinkedList <__ElementType, __equals>::__dll_newAfter (
    AbstractBidirectionalNodeIterator <__ElementType> const& iterator
) noexcept(false) -> __ElementType* {
  auto const reversed =
      (_pFront == iterator._pPreviousNode && iterator._pCurrentNode == nullptr) ||
      (iterator._pCurrentNode != nullptr && iterator._pCurrentNode->_pNext == iterator._pPreviousNode);

  if (
      __dll_empty() ||
      iterator._pCurrentNode == nullptr && iterator._pPreviousNode == nullptr ||
      !reversed && iterator._pCurrentNode == nullptr ||
      reversed && iterator._pCurrentNode == nullptr
  ) {
    return nullptr;
  }

  if (reversed && iterator._pCurrentNode == _pFront) {
    return __dll_newFront();
  }

  if (!reversed && iterator._pCurrentNode == _pBack) {
    return __dll_newBack();
  }

  return reversed
      ? __dll_newBetweenNodes (iterator._pCurrentNode->_pPrevious, iterator._pCurrentNode)
      : __dll_newBetweenNodes (iterator._pCurrentNode, iterator._pCurrentNode->_pNext);
}


template <
    typename                                                                    __ElementType,  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__ElementType const&, __ElementType const&>  __equals        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> auto __DoubleLinkedList <__ElementType, __equals>::__dll_newAfterConst (
    AbstractBidirectionalNodeIterator <__ElementType const> const& iterator
) noexcept(false) -> __ElementType* {
  auto const reversed =
      (_pFront == iterator._pPreviousNode && iterator._pCurrentNode == nullptr) ||
      (iterator._pCurrentNode != nullptr && iterator._pCurrentNode->_pNext == iterator._pPreviousNode);

  if (
      __dll_empty() ||
      iterator._pCurrentNode == nullptr && iterator._pPreviousNode == nullptr ||
      !reversed && iterator._pCurrentNode == nullptr ||
      reversed && iterator._pCurrentNode == nullptr
  ) {
    return nullptr;
  }

  if (reversed && iterator._pCurrentNode == _pFront) {
    return __dll_newFront();
  }

  if (!reversed && iterator._pCurrentNode == _pBack) {
    return __dll_newBack();
  }

  return reversed
      ? __dll_newBetweenNodes (iterator._pCurrentNode->_pPrevious, iterator._pCurrentNode)
      : __dll_newBetweenNodes (iterator._pCurrentNode, iterator._pCurrentNode->_pNext);
}


template <
    typename                                                                    __ElementType,  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__ElementType const&, __ElementType const&>  __equals        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> auto __DoubleLinkedList <__ElementType, __equals>::__dll_newBeforeArray (
    AbstractBidirectionalNodeIterator <__ElementType> const&  iterator,
    Size                                                      count,
    __ElementType**                                           ppElements
) noexcept(false) -> bool {
  auto const reversed =
      (_pFront == iterator._pPreviousNode && iterator._pCurrentNode == nullptr) ||
      (iterator._pCurrentNode != nullptr && iterator._pCurrentNode->_pNext == iterator._pPreviousNode);

  if (__dll_empty() || iterator._pCurrentNode == nullptr && iterator._pPreviousNode == nullptr) {
    return false;
  }

  if (
      !reversed && iterator._pCurrentNode == _pFront && iterator._pPreviousNode == nullptr ||
      reversed && iterator._pPreviousNode == _pFront && iterator._pCurrentNode == nullptr
  ) {
    __dll_newFrontArray (count, ppElements);
  } else if (
      !reversed && iterator._pCurrentNode == nullptr && iterator._pPreviousNode == _pBack ||
      reversed && iterator._pPreviousNode == nullptr && iterator._pCurrentNode == _pBack
  ) {
    __dll_newBackArray (count, ppElements);
  } else {
    !reversed
        ? __dll_newBetweenNodesArray (iterator._pPreviousNode, iterator._pCurrentNode, count, ppElements)
        : __dll_newBetweenNodesArray (iterator._pCurrentNode, iterator._pPreviousNode, count, ppElements);
  }

  return true;
}


template <
    typename                                                                    __ElementType,  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__ElementType const&, __ElementType const&>  __equals        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> auto __DoubleLinkedList <__ElementType, __equals>::__dll_newBeforeArrayConst (
    AbstractBidirectionalNodeIterator <__ElementType const> const& iterator,
    Size                                                          count,
    __ElementType**                                               ppElements
) noexcept(false) -> bool {
  auto const reversed =
      (_pFront == iterator._pPreviousNode && iterator._pCurrentNode == nullptr) ||
      (iterator._pCurrentNode != nullptr && iterator._pCurrentNode->_pNext == iterator._pPreviousNode);

  if (__dll_empty() || iterator._pCurrentNode == nullptr && iterator._pPreviousNode == nullptr) {
    return false;
  }

  if (
      !reversed && iterator._pCurrentNode == _pFront && iterator._pPreviousNode == nullptr ||
      reversed && iterator._pPreviousNode == _pFront && iterator._pCurrentNode == nullptr
  ) {
    __dll_newFrontArray (count, ppElements);
  } else if (
      !reversed && iterator._pCurrentNode == nullptr && iterator._pPreviousNode == _pBack ||
      reversed && iterator._pPreviousNode == nullptr && iterator._pCurrentNode == _pBack
  ) {
    __dll_newBackArray (count, ppElements);
  } else {
    !reversed
        ? __dll_newBetweenNodesArray (iterator._pPreviousNode, iterator._pCurrentNode, count, ppElements)
        : __dll_newBetweenNodesArray (iterator._pCurrentNode, iterator._pPreviousNode, count, ppElements);
  }

  return true;
}


template <
    typename                                                                    __ElementType,  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__ElementType const&, __ElementType const&>  __equals        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> auto __DoubleLinkedList <__ElementType, __equals>::__dll_newAfterArray (
    AbstractBidirectionalNodeIterator <__ElementType> const&  iterator,
    Size                                                      count,
    __ElementType**                                           ppElements
) noexcept(false) -> bool {
  auto const reversed =
      (_pFront == iterator._pPreviousNode && iterator._pCurrentNode == nullptr) ||
      (iterator._pCurrentNode != nullptr && iterator._pCurrentNode->_pNext == iterator._pPreviousNode);

  if (
      __dll_empty() ||
      iterator._pCurrentNode == nullptr && iterator._pPreviousNode == nullptr ||
      !reversed && iterator._pCurrentNode == nullptr ||
      reversed && iterator._pCurrentNode == nullptr
  ) {
    return false;
  }

  if (reversed && iterator._pCurrentNode == _pFront) {
    __dll_newFrontArray (count, ppElements);
    return true;
  }

  if (!reversed && iterator._pCurrentNode == _pBack) {
    __dll_newBackArray (count, ppElements);
    return true;
  }

  reversed
      ? __dll_newBetweenNodesArray (iterator._pCurrentNode->_pPrevious, iterator._pCurrentNode, count, ppElements)
      : __dll_newBetweenNodesArray (iterator._pCurrentNode, iterator._pCurrentNode->_pNext, count, ppElements);
  return true;
}


template <
    typename                                                                    __ElementType,  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__ElementType const&, __ElementType const&>  __equals        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> auto __DoubleLinkedList <__ElementType, __equals>::__dll_newAfterArrayConst (
    AbstractBidirectionalNodeIterator <__ElementType const> const& iterator,
    Size                                                          count,
    __ElementType**                                               ppElements
) noexcept(false) -> bool {
  auto const reversed =
      (_pFront == iterator._pPreviousNode && iterator._pCurrentNode == nullptr) ||
      (iterator._pCurrentNode != nullptr && iterator._pCurrentNode->_pNext == iterator._pPreviousNode);

  if (
      __dll_empty() ||
      iterator._pCurrentNode == nullptr && iterator._pPreviousNode == nullptr ||
      !reversed && iterator._pCurrentNode == nullptr ||
      reversed && iterator._pCurrentNode == nullptr
  ) {
    return false;
  }

  if (reversed && iterator._pCurrentNode == _pFront) {
    __dll_newFrontArray (count, ppElements);
    return true;
  }

  if (!reversed && iterator._pCurrentNode == _pBack) {
    __dll_newBackArray (count, ppElements);
    return true;
  }

  reversed
      ? __dll_newBetweenNodesArray (iterator._pCurrentNode->_pPrevious, iterator._pCurrentNode, count, ppElements)
      : __dll_newBetweenNodesArray (iterator._pCurrentNode, iterator._pCurrentNode->_pNext, count, ppElements);
  return true;
}


template <
    typename                                                                    __ElementType,  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__ElementType const&, __ElementType const&>  __equals        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> __CDS_cpplang_NonConstConstexprMemberFunction auto __DoubleLinkedList <__ElementType, __equals>::__dll_begin () noexcept -> __dll_Iterator {
  return __dll_Iterator (nullptr, _pFront);
}


template <
    typename                                                                    __ElementType,  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__ElementType const&, __ElementType const&>  __equals        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> __CDS_cpplang_NonConstConstexprMemberFunction auto __DoubleLinkedList <__ElementType, __equals>::__dll_end () noexcept -> __dll_Iterator {
  return __dll_Iterator (_pBack, nullptr);
}


template <
    typename                                                                    __ElementType,  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__ElementType const&, __ElementType const&>  __equals        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> constexpr auto __DoubleLinkedList <__ElementType, __equals>::__dll_cbegin () const noexcept -> __dll_ConstIterator {
  return __dll_ConstIterator (nullptr, _pFront);
}


template <
    typename                                                                    __ElementType,  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__ElementType const&, __ElementType const&>  __equals        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> constexpr auto __DoubleLinkedList <__ElementType, __equals>::__dll_cend () const noexcept -> __dll_ConstIterator {
  return __dll_ConstIterator (_pBack, nullptr);
}


template <
    typename                                                                    __ElementType,  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__ElementType const&, __ElementType const&>  __equals        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> __CDS_cpplang_NonConstConstexprMemberFunction auto __DoubleLinkedList <__ElementType, __equals>::__dll_rbegin () noexcept -> __dll_ReverseIterator {
  return __dll_ReverseIterator (nullptr, _pBack);
}


template <
    typename                                                                    __ElementType,  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__ElementType const&, __ElementType const&>  __equals        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> __CDS_cpplang_NonConstConstexprMemberFunction auto __DoubleLinkedList <__ElementType, __equals>::__dll_rend () noexcept -> __dll_ReverseIterator {
  return __dll_ReverseIterator (_pFront, nullptr);
}


template <
    typename                                                                    __ElementType,  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__ElementType const&, __ElementType const&>  __equals        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> constexpr auto __DoubleLinkedList <__ElementType, __equals>::__dll_crbegin () const noexcept -> __dll_ConstReverseIterator {
  return __dll_ConstReverseIterator (nullptr, _pBack);
}


template <
    typename                                                                    __ElementType,  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__ElementType const&, __ElementType const&>  __equals        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> constexpr auto __DoubleLinkedList <__ElementType, __equals>::__dll_crend () const noexcept -> __dll_ConstReverseIterator {
  return __dll_ConstReverseIterator (_pFront, nullptr);
}


template <
    typename                                                                    __ElementType,  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__ElementType const&, __ElementType const&>  __equals        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> template <
    typename __TElementType,                                    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    cds::meta::EnableIf <cds::meta::IsCopyConstructible <__TElementType>::value>
> __CDS_MaybeUnused __CDS_OptimalInline auto __DoubleLinkedList <__ElementType, __equals>::__dll_copy (
    __DoubleLinkedList const& list
) noexcept(false) -> void {
  __dll_clear();
  __dll_copyCleared (list);
}


template <
    typename                                                                    __ElementType,  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__ElementType const&, __ElementType const&>  __equals        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> __CDS_MaybeUnused __CDS_OptimalInline auto __DoubleLinkedList <__ElementType, __equals>::__dll_move (
    __DoubleLinkedList&& list
) noexcept -> void {
  __dll_clear();
  __dll_moveCleared (std::move (list));
}


template <
    typename                                                                    __ElementType,  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__ElementType const&, __ElementType const&>  __equals        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> template <
    typename __TElementType,                                    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    cds::meta::EnableIf <cds::meta::IsCopyConstructible <__TElementType>::value>
> auto __DoubleLinkedList <__ElementType, __equals>::__dll_copyCleared (
    __DoubleLinkedList const &list
) noexcept(false) -> void {
  __NodeType* pOtherHead = list._pFront;
  while (pOtherHead != nullptr) {

    __NodeType* pNewNode = __dll_allocateNode();
    new (&pNewNode->_data) __ElementType (pOtherHead->_data);
    pNewNode->_pNext        = nullptr;
    pNewNode->_pPrevious    = _pBack;

    if (_pBack == nullptr) {
      _pFront = pNewNode;
    } else {
      _pBack->_pNext = pNewNode;
    }

    _pBack = pNewNode;
    pOtherHead = pOtherHead->_pNext;
  }

  _size = list._size;
}


template <
    typename                                                                    __ElementType,  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__ElementType const&, __ElementType const&>  __equals        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> __CDS_cpplang_NonConstConstexprMemberFunction auto __DoubleLinkedList <__ElementType, __equals>::__dll_moveCleared (
    __DoubleLinkedList&& list
) noexcept -> void {
  _pFront   = cds::exchange (list._pFront, nullptr);
  _pBack    = cds::exchange (list._pBack, nullptr);
  _size     = cds::exchange (list._size, 0u);
}


template <
    typename                                                                    __ElementType,  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__ElementType const&, __ElementType const&>  __equals        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> __CDS_MaybeUnused __CDS_cpplang_ConstexprConditioned auto __DoubleLinkedList <__ElementType, __equals>::__dll_equals (
    __DoubleLinkedList const& list
) const noexcept -> bool {
  if (_pFront == list._pFront) {
    return true;
  }

  if (_pFront == nullptr || list._pFront == nullptr || _size != list._size) {
    return false;
  }

  auto thisFront  = _pFront;
  auto otherFront = list._pFront;
  while (thisFront != nullptr) {
    if (!__equals ( thisFront->_data, otherFront->_data)) {
      return false;
    }

    thisFront   = thisFront->_pNext;
    otherFront  = otherFront->_pNext;
  }

  return true;
}


namespace __mergeSortHelpers {  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <
    typename __ElementType                                        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> __CDS_OptimalInline auto __bidirectionalNodeMergeSortMidNode (  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    __BidirectionalNode <__ElementType>* pHead
) noexcept -> __BidirectionalNode <__ElementType>* {
  auto pMid = pHead;
  pHead = pHead->_pNext;
  while (pHead != nullptr) {
    pHead = pHead->_pNext;
    if (pHead != nullptr) {
      pHead   = pHead->_pNext;
      pMid    = pMid->_pNext;
    }
  }

  return pMid;
}


template <
    typename __ElementType,                                               // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __Comparator                                                 // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> __CDS_OptimalInline auto __bidirectionalNodeMergeSortMergeSortedLists ( // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    __BidirectionalNode <__ElementType>*  pLeft,
    __BidirectionalNode <__ElementType>*  pRight,
    __Comparator const&                   comparator
) noexcept -> __BidirectionalNode <__ElementType>* {
  if (pLeft == nullptr) {
    return pRight;
  }

  if (pRight == nullptr) {
    return pLeft;
  }

  decltype (pLeft) pFinalFront  = nullptr;
  decltype (pLeft) pFinalBack;
  decltype (pLeft) pToAdd;
  while (pLeft != nullptr && pRight != nullptr) {
    if (comparator (pLeft->_data, pRight->_data)) {
      pToAdd  = pLeft;
      pLeft   = pLeft->_pNext;
    } else {
      pToAdd  = pRight;
      pRight  = pRight->_pNext;
    }

    if (pFinalFront == nullptr) {
      pFinalFront         = pToAdd;
      pFinalBack          = pToAdd;
      pToAdd->_pNext      = nullptr;
      pToAdd->_pPrevious  = nullptr;
    } else {
      pFinalBack->_pNext  = pToAdd;
      pToAdd->_pPrevious  = pFinalBack;
      pFinalBack          = pToAdd;
    }
  }

  while (pLeft != nullptr) {
    pToAdd              = pLeft;
    pLeft               = pLeft->_pNext;
    pFinalBack->_pNext  = pToAdd;
    pToAdd->_pPrevious  = pFinalBack;
    pFinalBack          = pToAdd;
  }

  while (pRight != nullptr) {
    pToAdd              = pRight;
    pRight              = pRight->_pNext;
    pFinalBack->_pNext  = pToAdd;
    pToAdd->_pPrevious  = pFinalBack;
    pFinalBack          = pToAdd;
  }

  pFinalBack->_pNext = nullptr;
  return pFinalFront;
}


template <
    typename __ElementType,           // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __Comparator             // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> auto __bidirectionalNodeMergeSort ( // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    __BidirectionalNode <__ElementType>*  pHead,
    __Comparator const&                   comparator
) noexcept -> __BidirectionalNode <__ElementType>* {
  if (pHead == nullptr || pHead->_pNext == nullptr) {
    return pHead;
  }

  auto pMid       = __bidirectionalNodeMergeSortMidNode (pHead);
  auto pSplit     = pMid->_pNext;
  pMid->_pNext    = nullptr;
  return __bidirectionalNodeMergeSortMergeSortedLists (
      __bidirectionalNodeMergeSort <__ElementType> (pHead, comparator),
      __bidirectionalNodeMergeSort <__ElementType> (pSplit, comparator),
      comparator
  );
}
} // namespace __mergeSortHelpers


template <
    typename                                                                    __ElementType,  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__ElementType const&, __ElementType const&>  __equals        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> template <
    typename __Comparator                                                                       // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> __CDS_OptimalInline auto __DoubleLinkedList <__ElementType, __equals>::__dll_sort (
    __Comparator const& comparator
) noexcept -> void {
  _pFront = __mergeSortHelpers::__bidirectionalNodeMergeSort (
      _pFront,
      comparator
  );

  auto pHead  = _pFront;
  _pBack      = nullptr;
  while (pHead != nullptr) {
    _pBack  = pHead;
    pHead   = pHead->_pNext;
  }
}

} /* namespace __impl */
} /* namespace __hidden */
} /* namespace cds */

#endif /* __CDS_SHARED_DOUBLE_LINKED_LIST_IMPL_HPP__ */
