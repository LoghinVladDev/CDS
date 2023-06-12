//
// Created by loghin on 17/07/22.
//

#ifndef __CDS_SHARED_SINGLE_LINKED_LIST_HPP__ // NOLINT(llvm-header-guard)
#define __CDS_SHARED_SINGLE_LINKED_LIST_HPP__ // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
#pragma once

namespace cds {       // NOLINT(modernize-concat-nested-namespaces)
namespace __hidden {  // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
namespace __impl {    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

template <
    typename                                                                    __ElementType,  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__ElementType const&, __ElementType const&>  __equals        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> class __SingleLinkedList {                                                                    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
public:
  using __sll_Iterator                = UnidirectionalNodeIterator <__ElementType>;       // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  using __sll_ConstIterator           = UnidirectionalNodeIterator <__ElementType const>;  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

  ~__SingleLinkedList () noexcept = default;
  auto operator = (__SingleLinkedList const&) noexcept -> __SingleLinkedList& = delete;
  auto operator = (__SingleLinkedList&&) noexcept -> __SingleLinkedList& = delete;

protected:
  using ElementType = __ElementType;

  constexpr __SingleLinkedList () noexcept; // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  __SingleLinkedList (__SingleLinkedList const& list) noexcept(false);       // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  constexpr __SingleLinkedList (__SingleLinkedList&& list) noexcept;  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

  auto __sll_clear() noexcept -> void;   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  __CDS_NoDiscard constexpr auto __sll_empty() const noexcept -> bool;   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  __CDS_NoDiscard __CDS_MaybeUnused constexpr auto __sll_front() const noexcept -> __ElementType const*;  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-non-private-member-variables-in-classes)
  __CDS_NoDiscard __CDS_MaybeUnused __CDS_cpplang_NonConstConstexprMemberFunction auto __sll_front() noexcept -> __ElementType*;  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction auto __sll_backNode() noexcept -> __UnidirectionalNode <__ElementType>*;

  auto __sll_removeFront() noexcept -> void; // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  auto __sll_newFront() noexcept(false) -> __ElementType*; // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  auto __sll_newBack() noexcept(false) -> __ElementType*;  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

  __CDS_MaybeUnused auto __sll_new (                                    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      __ElementType const*  pReferenceElement,
      bool*                 pNewElementCreated
  ) noexcept(false) -> __ElementType*;

  __CDS_NoDiscard constexpr auto __sll_cbegin() const noexcept -> __sll_ConstIterator;   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  __CDS_NoDiscard constexpr auto __sll_cend() const noexcept -> __sll_ConstIterator;     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction auto __sll_begin() noexcept -> __sll_Iterator;   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-non-private-member-variables-in-classes)
  __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction auto __sll_end() noexcept -> __sll_Iterator;     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

  auto __sll_remove (__ElementType const& value) noexcept -> bool;  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  auto __sll_removeIterator (__sll_Iterator const& iterator) noexcept -> bool;  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  auto __sll_removeConstIterator (__sll_ConstIterator const& iterator) noexcept -> bool;  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

  template <typename __Compared, typename __Comparator>
  auto __sll_removeIf (__Compared const& element, __Comparator const& comparator) noexcept -> bool;

  __CDS_MaybeUnused auto __sll_removeIteratorArray (    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      __sll_Iterator const* const*  ppIterators,
      Size                          iteratorCount
  ) noexcept -> Size;

  auto __sll_removeConstIteratorArray (   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      __sll_ConstIterator const* const* ppIterators,
      Size                              iteratorCount
  ) noexcept -> Size;

  template <
      typename __TElementType = __ElementType,    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      cds::meta::EnableIf <cds::meta::IsCopyConstructible <__TElementType>::value> = 0
  > __CDS_MaybeUnused auto __sll_copy (__SingleLinkedList const& list) noexcept(false) -> void; // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

  template <
      typename __TElementType = __ElementType,    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      cds::meta::EnableIf <cds::meta::IsCopyConstructible <__TElementType>::value> = 0
  > auto __sll_copyCleared (__SingleLinkedList const& list) noexcept(false) -> void;  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

  auto __sll_move (__SingleLinkedList&& list) noexcept -> void;   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  __CDS_cpplang_NonConstConstexprMemberFunction auto __sll_moveCleared (__SingleLinkedList&& list) noexcept -> void;  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

  __CDS_NoDiscard __CDS_MaybeUnused __CDS_cpplang_ConstexprConditioned auto __sll_equals (  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      __SingleLinkedList const& list
  ) const noexcept -> bool;

private:
  using __NodeType = __UnidirectionalNode <__ElementType>;  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

  __NodeType * _pFront    {nullptr};
  __NodeType * _pBack     {nullptr};

  __CDS_NoDiscard static auto __sll_allocateNode() noexcept(false) -> __NodeType*; // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  static auto __sll_freeNode (__NodeType* pNode) noexcept -> void;          // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

  auto __sll_removeNode (__NodeType* pCurrent, __NodeType* pPrevious) noexcept -> void; // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  auto __sll_removeNode (__NodeType* pCurrent) noexcept -> void; // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
};

} // namespace __impl
} // namespace __hidden
} // namespace cds

#endif // __CDS_SHARED_SINGLE_LINKED_LIST_HPP__
