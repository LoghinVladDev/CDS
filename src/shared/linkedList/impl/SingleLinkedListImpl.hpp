//
// Created by loghin on 02/10/22.
//

#ifndef __CDS_SHARED_SINGLE_LINKED_LIST_IMPL_HPP__ // NOLINT(llvm-header-guard)
#define __CDS_SHARED_SINGLE_LINKED_LIST_IMPL_HPP__ // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
#pragma once

namespace cds {       // NOLINT(modernize-concat-nested-namespaces)
namespace __hidden {  // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
namespace __impl {    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

template <
    typename                                                                    __ElementType,  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__ElementType const &, __ElementType const&> __equals        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> __CDS_OptimalInline auto __SingleLinkedList <__ElementType, __equals>::__sll_allocateNode () noexcept(false) -> __NodeType* {
  using __Alloc = __allocation::__PrimitiveAlloc <__NodeType>;  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  return __Alloc::__alloc();
}


template <
    typename                                                                    __ElementType,  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__ElementType const &, __ElementType const&> __equals        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> __CDS_OptimalInline auto __SingleLinkedList <__ElementType, __equals>::__sll_freeNode (
    __NodeType* pNode
) noexcept -> void {
  using __Alloc = __allocation::__PrimitiveAlloc <__NodeType>;  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  pNode->_data.~__ElementType ();
  return __Alloc::__free (pNode);
}


template <
    typename                                                                    __ElementType,  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__ElementType const &, __ElementType const&> __equals        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> constexpr __SingleLinkedList <__ElementType, __equals>::__SingleLinkedList () noexcept = default;


template <
    typename                                                                    __ElementType,  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__ElementType const &, __ElementType const&> __equals        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> __CDS_MaybeUnused __CDS_OptimalInline __SingleLinkedList <__ElementType, __equals>::__SingleLinkedList (
    __SingleLinkedList const& list
) noexcept(false) {
  __sll_copyCleared (list);
}


template <
    typename                                                                    __ElementType,  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__ElementType const &, __ElementType const&> __equals        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> __CDS_MaybeUnused constexpr __SingleLinkedList <__ElementType, __equals>::__SingleLinkedList (
    __SingleLinkedList&& list
) noexcept :
    _pFront (cds::exchange (list._pFront, nullptr)),
    _pBack (cds::exchange (list._pBack, nullptr)) {

}


template <
    typename                                                                    __ElementType,  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__ElementType const &, __ElementType const&> __equals        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> auto __SingleLinkedList <__ElementType, __equals>::__sll_clear() noexcept -> void {
  while (_pFront != nullptr) {
    auto pCopy      = _pFront;
    _pFront   = _pFront->_pNext;
    __sll_freeNode (pCopy);
  }
  _pBack = nullptr;
}


template <
    typename                                                                    __ElementType,  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__ElementType const &, __ElementType const&> __equals        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> constexpr auto __SingleLinkedList <__ElementType, __equals>::__sll_empty() const noexcept -> bool {
  return _pFront == nullptr;
}


template <
    typename                                                                    __ElementType,  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__ElementType const &, __ElementType const&> __equals        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> __CDS_MaybeUnused constexpr auto __SingleLinkedList <__ElementType, __equals>::__sll_front () const noexcept -> __ElementType const* {
  return _pFront;
}


template <
    typename                                                                    __ElementType,  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__ElementType const &, __ElementType const&> __equals        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> __CDS_MaybeUnused __CDS_cpplang_NonConstConstexprMemberFunction auto __SingleLinkedList <__ElementType, __equals>::__sll_front () noexcept -> __ElementType* {
  return _pFront;
}


template <
    typename                                                                    __ElementType,  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__ElementType const &, __ElementType const&> __equals        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> __CDS_OptimalInline auto __SingleLinkedList <__ElementType, __equals>::__sll_removeFront () noexcept -> void {
  if (__sll_empty()) {
    return;
  }

  auto pCopy  = _pFront;
  _pFront     = _pFront->_pNext;
  __sll_freeNode (pCopy);

  if (_pFront == nullptr) {
    _pBack = nullptr;
  }
}


template <
    typename                                                                    __ElementType,  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__ElementType const &, __ElementType const&> __equals        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> __CDS_OptimalInline auto __SingleLinkedList <__ElementType, __equals>::__sll_newFront() noexcept(false) -> __ElementType* {
  auto pNewNode     = __sll_allocateNode();
  pNewNode->_pNext  = _pFront;
  _pFront           = pNewNode;
  if (_pBack == nullptr) {
    _pBack = pNewNode;
  }

  return &pNewNode->_data;
}


template <
    typename                                                                    __ElementType,  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__ElementType const &, __ElementType const&> __equals        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> __CDS_OptimalInline auto __SingleLinkedList <__ElementType, __equals>::__sll_newBack() noexcept(false) -> __ElementType* {
  if (__sll_empty()) {
    return __sll_newFront();
  }

  auto pNewNode   = __sll_allocateNode();
  _pBack->_pNext  = pNewNode;
  _pBack          = pNewNode;
  _pBack->_pNext  = nullptr;

  return &pNewNode->_data;
}


template <
    typename                                                                    __ElementType,  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__ElementType const &, __ElementType const&> __equals        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> __CDS_MaybeUnused __CDS_OptimalInline auto __SingleLinkedList <__ElementType, __equals>::__sll_new (
    __ElementType const*  pReferenceElement,
    bool*                 pNewElementCreated
) noexcept(false) -> __ElementType* {
  (void) pReferenceElement;
  *pNewElementCreated = true;
  return __sll_newBack();
}


template <
    typename                                                                    __ElementType,  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__ElementType const &, __ElementType const&> __equals        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> __CDS_MaybeUnused __CDS_cpplang_NonConstConstexprMemberFunction auto __SingleLinkedList <__ElementType, __equals>::__sll_backNode() noexcept -> __UnidirectionalNode <ElementType>* {
  return _pBack;
}


template <
    typename                                                                    __ElementType,  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__ElementType const &, __ElementType const&> __equals        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> constexpr auto __SingleLinkedList <__ElementType, __equals>::__sll_cbegin () const noexcept -> __sll_ConstIterator {
  return __sll_ConstIterator (_pFront);
}


template <
    typename                                                                    __ElementType,  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__ElementType const &, __ElementType const&> __equals        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> constexpr auto __SingleLinkedList <__ElementType, __equals>::__sll_cend () const noexcept -> __sll_ConstIterator {
  return __sll_ConstIterator (nullptr);
}


template <
    typename                                                                    __ElementType,  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__ElementType const &, __ElementType const&> __equals        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> __CDS_cpplang_NonConstConstexprMemberFunction auto __SingleLinkedList <__ElementType, __equals>::__sll_begin () noexcept -> __sll_Iterator {
  return __sll_Iterator (_pFront);
}


template <
    typename                                                                    __ElementType,  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__ElementType const &, __ElementType const&> __equals        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> __CDS_cpplang_NonConstConstexprMemberFunction auto __SingleLinkedList <__ElementType, __equals>::__sll_end () noexcept -> __sll_Iterator {
  return __sll_Iterator (nullptr);
}


template <
    typename                                                                    __ElementType,  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__ElementType const &, __ElementType const&> __equals        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> __CDS_OptimalInline auto __SingleLinkedList <__ElementType, __equals>::__sll_removeNode (
    __NodeType* pPrevious,
    __NodeType* pCurrent
) noexcept -> void {
  auto pNext = pCurrent->_pNext;
  pPrevious->_pNext = pNext;
  __sll_freeNode (pCurrent);

  if (pNext == nullptr) {
    _pBack = pPrevious;
  }
}


template <
    typename                                                                    __ElementType,  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__ElementType const &, __ElementType const&> __equals        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> __CDS_OptimalInline auto __SingleLinkedList <__ElementType, __equals>::__sll_removeNode (
    __NodeType* pCurrent
) noexcept -> void {
  if (__sll_empty()) {
    return;
  }

  if (_pFront == pCurrent) {
    __sll_removeFront();
    return;
  }

  auto pPrevious = _pFront;
  while (pPrevious->_pNext != nullptr) {
    if (pPrevious->_pNext == pCurrent) {
      __sll_removeNode (pPrevious, pPrevious->_pNext);
      return;
    }
    pPrevious = pPrevious->_pNext;
  }
}


template <
    typename                                                                    __ElementType,  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__ElementType const &, __ElementType const&> __equals        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> __CDS_MaybeUnused auto __SingleLinkedList <__ElementType, __equals>::__sll_remove (
    __ElementType const& value
) noexcept -> bool {
  if (__sll_empty()) {
    return false;
  }

  if (__equals (_pFront->_data, value)) {
    __sll_removeFront();
    return true;
  }

  auto pPrevious = _pFront;
  while (pPrevious->_pNext != nullptr) {
    if (__equals (pPrevious->_pNext->_data, value)) {
      __sll_removeNode (pPrevious, pPrevious->_pNext);
      return true;
    }
    pPrevious = pPrevious->_pNext;
  }

  return false;
}

template <
    typename                                                                    __ElementType,  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__ElementType const &, __ElementType const&> __equals        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> template <typename __Compared, typename __Comparator>                                         // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
auto __SingleLinkedList <__ElementType, __equals>::__sll_removeIf (
    __Compared const& element, __Comparator const& comparator
) noexcept -> bool {
  if (__sll_empty()) {
    return false;
  }

  if (comparator (element, _pFront->_data)) {
    __sll_removeFront();
    return true;
  }

  auto pPrevious = _pFront;
  while (pPrevious->_pNext != nullptr) {
    if (comparator (element, pPrevious->_pNext->_data)) {
      __sll_removeNode (pPrevious, pPrevious->_pNext);
      return true;
    }
    pPrevious = pPrevious->_pNext;
  }

  return false;
}

template <
    typename                                                                    __ElementType,  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__ElementType const &, __ElementType const&> __equals        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> auto __SingleLinkedList <__ElementType, __equals>::__sll_removeIterator (
    __sll_Iterator const& iterator
) noexcept -> bool {
  if (__sll_empty() || iterator == __sll_end()) {
    return false;
  }

  (__sll_begin() == iterator)
      ? __sll_removeFront()
      : __sll_removeNode (iterator._pCurrentNode);
  return true;
}


template <
    typename                                                                    __ElementType,  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__ElementType const &, __ElementType const&> __equals        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> auto __SingleLinkedList <__ElementType, __equals>::__sll_removeConstIterator (
    __sll_ConstIterator const& iterator
) noexcept -> bool {
  if (__sll_empty() || iterator == __sll_cend()) {
    return false;
  }

  (__sll_cbegin() == iterator)
      ? __sll_removeFront()
      : __sll_removeNode(const_cast <__NodeType*> (iterator._pCurrentNode));
  return true;
}


template <
    typename                                                                    __ElementType,  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__ElementType const &, __ElementType const&> __equals        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> auto __SingleLinkedList <__ElementType, __equals>::__sll_removeConstIteratorArray (
    __sll_ConstIterator const* const* ppIterators,
    Size                              iteratorCount
) noexcept -> Size {
  Size itIdx = 0u;
  while (itIdx < iteratorCount && &(*(*ppIterators [itIdx])) == &_pFront->_data) {
    __sll_removeFront();
    ++ itIdx;
  }

  auto pPrevious = _pFront;
  while (pPrevious != nullptr && pPrevious->_pNext != nullptr && itIdx < iteratorCount) {
    if (itIdx < iteratorCount && &pPrevious->_pNext->_data == &(*(*ppIterators [itIdx]))) {
      auto copy = pPrevious->_pNext;
      pPrevious->_pNext = pPrevious->_pNext->_pNext;
      __sll_freeNode(copy);
      ++ itIdx;
      if (_pBack == copy) {
        _pBack = pPrevious;
      }
    } else {
      pPrevious = pPrevious->_pNext;
    }
  }

  return itIdx;
}


template <
    typename                                                                    __ElementType,  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__ElementType const &, __ElementType const&> __equals        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> __CDS_MaybeUnused auto __SingleLinkedList <__ElementType, __equals>::__sll_removeIteratorArray (
    __sll_Iterator const* const*  ppIterators,
    Size                          iteratorCount
) noexcept -> Size {
  Size itIdx = 0u;
  while (itIdx < iteratorCount && &(*(*ppIterators [itIdx])) == &_pFront->_data) {
    __sll_removeFront();
    ++ itIdx;
  }

  auto pPrevious = _pFront;
  while (pPrevious->_pNext != nullptr && itIdx < iteratorCount) {
    if (itIdx < iteratorCount && &pPrevious->_pNext->_data == &(*(*ppIterators [itIdx]))) {
      auto copy = pPrevious->_pNext;
      pPrevious->_pNext = pPrevious->_pNext->_pNext;
      __sll_freeNode(copy);
      ++ itIdx;
      if (_pBack == copy) {
        _pBack = pPrevious;
      }
    } else {
      pPrevious = pPrevious->_pNext;
    }
  }

  return itIdx;
}


template <
    typename                                                                    __ElementType,  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__ElementType const &, __ElementType const&> __equals        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> template <
    typename __TElementType,                                                                    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    cds::meta::EnableIf <cds::meta::IsCopyConstructible <__TElementType>::value>
> __CDS_MaybeUnused __CDS_OptimalInline auto __SingleLinkedList <__ElementType, __equals>::__sll_copy (
    __SingleLinkedList const& list
) noexcept(false) -> void {
  if (this == & list) {
    return;
  }

  __sll_clear();
  __sll_copyCleared (list);
}


template <
    typename                                                                    __ElementType,  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__ElementType const &, __ElementType const&> __equals        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> template <
    typename __TElementType,                                                                    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    cds::meta::EnableIf <cds::meta::IsCopyConstructible <__TElementType>::value>
> auto __SingleLinkedList <__ElementType, __equals>::__sll_copyCleared (
    __SingleLinkedList const& list
) noexcept(false) -> void {
  auto pOtherHead = list._pFront;
  while (pOtherHead != nullptr) {

    auto pNewNode           = __sll_allocateNode();
    new (& pNewNode->_data) __ElementType (pOtherHead->_data);
    pNewNode->_pNext        = nullptr;

    if (_pBack == nullptr) {
      _pFront = pNewNode;
    } else {
      _pBack->_pNext = pNewNode;
    }

    _pBack = pNewNode;
    pOtherHead = pOtherHead->_pNext;
  }
}


template <
    typename                                                                    __ElementType,  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__ElementType const &, __ElementType const&> __equals        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> __CDS_MaybeUnused __CDS_OptimalInline auto __SingleLinkedList <__ElementType, __equals>::__sll_move (
    __SingleLinkedList&& list
) noexcept -> void {
  if (this == & list) {
    return;
  }

  __sll_clear();
  __sll_moveCleared (std::move (list));
}


template <
    typename                                                                    __ElementType,  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__ElementType const &, __ElementType const&> __equals        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> __CDS_cpplang_NonConstConstexprMemberFunction auto __SingleLinkedList <__ElementType, __equals>::__sll_moveCleared (
    __SingleLinkedList&& list
) noexcept -> void {
  _pFront   = cds::exchange (list._pFront, nullptr);
  _pBack    = cds::exchange (list._pBack, nullptr);
}


template <
    typename                                                                    __ElementType,  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__ElementType const &, __ElementType const&> __equals        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> __CDS_MaybeUnused __CDS_cpplang_ConstexprConditioned auto __SingleLinkedList <__ElementType, __equals>::__sll_equals (
    __SingleLinkedList const &list
) const noexcept -> bool {
  if (_pFront == list._pFront) {
    return true;
  }

  if (_pFront == nullptr || list._pFront == nullptr) {
    return false;
  }

  auto thisFront  = _pFront;
  auto otherFront = list._pFront;
  while (thisFront != nullptr) {
    if (!__equals (thisFront->_data, otherFront->_data)) {
      return false;
    }
    thisFront   = thisFront->_pNext;
    otherFront  = otherFront->_pNext;
  }

  return true;
}

} // namespace __impl
} // namespace __hidden
} // namespace cds

#endif // __CDS_SHARED_SINGLE_LINKED_LIST_IMPL_HPP__
