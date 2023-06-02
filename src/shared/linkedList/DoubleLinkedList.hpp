//
// Created by loghin on 17/07/22.
//

#ifndef __CDS_SHARED_DOUBLE_LINKED_LIST_HPP__ // NOLINT(llvm-header-guard)
#define __CDS_SHARED_DOUBLE_LINKED_LIST_HPP__ // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
#pragma once

namespace cds {       // NOLINT(modernize-concat-nested-namespaces)
namespace __hidden {  // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
namespace __impl {    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

template <
    typename                                                                    __ElementType,  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__ElementType const&, __ElementType const&>  __equals        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> class __DoubleLinkedList {                                                                    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
public:
  using __dll_Iterator              = ForwardBidirectionalNodeIterator <__ElementType>;       // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  using __dll_ConstIterator         = ForwardBidirectionalNodeConstIterator <__ElementType>;  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  using __dll_ReverseIterator       = BackwardBidirectionalNodeIterator <__ElementType>;      // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  using __dll_ConstReverseIterator  = BackwardBidirectionalNodeConstIterator <__ElementType>; // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

  template <typename __ServerType>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  class __Dispatcher;               // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

  ~__DoubleLinkedList () noexcept = default;

  auto operator = (__DoubleLinkedList const&) noexcept -> __DoubleLinkedList& = default;
  auto operator = (__DoubleLinkedList&&) noexcept -> __DoubleLinkedList& = default;

protected:
  using ElementType = __ElementType;

  constexpr __DoubleLinkedList () noexcept; // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  __DoubleLinkedList (__DoubleLinkedList const& list) noexcept(false); // NOLINT(bugprone-reserved-identifier,google-explicit-constructor)
  constexpr __DoubleLinkedList (__DoubleLinkedList&& list) noexcept; // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

  auto __dll_clear() noexcept -> void;   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  __CDS_NoDiscard constexpr auto __dll_empty() const noexcept -> bool;   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, modernize-use-nodiscard) */
  __CDS_NoDiscard constexpr auto __dll_size() const noexcept -> Size;    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, modernize-use-nodiscard) */
  __CDS_NoDiscard constexpr auto __dll_front() const noexcept -> __ElementType const*;  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, modernize-use-nodiscard) */
  __CDS_NoDiscard constexpr auto __dll_back() const noexcept -> __ElementType const*;   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, modernize-use-nodiscard) */
  __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction auto __dll_front() noexcept -> __ElementType*;  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-non-private-member-variables-in-classes) */
  __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction auto __dll_back() noexcept -> __ElementType*;   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-non-private-member-variables-in-classes) */

  auto __dll_removeFront () noexcept -> void; // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  auto __dll_removeBack () noexcept -> void;  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  auto __dll_removeAt (Index index) noexcept -> void; // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

  auto __dll_removeIterator (     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      AbstractBidirectionalNodeIterator <__ElementType> const& iterator
  ) noexcept -> bool;

  auto __dll_removeConstIterator (    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      AbstractBidirectionalNodeConstIterator <__ElementType> const& iterator
  ) noexcept -> bool;

  auto __dll_removeIteratorArray (     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      AbstractBidirectionalNodeIterator <__ElementType> const* const* ppIterators,
      Size                                                            iteratorCount
  ) noexcept -> Size;

  auto __dll_removeConstIteratorArray (    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      AbstractBidirectionalNodeConstIterator <__ElementType> const* const*  ppIterators,
      Size                                                                  iteratorCount
  ) noexcept -> Size;

  __CDS_NoDiscard auto __dll_get (Index index) noexcept -> ElementType*;  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  __CDS_NoDiscard auto __dll_get (Index index) const noexcept -> ElementType const*;  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, modernize-use-nodiscard)

  __CDS_NoDiscard auto __dll_newFront () noexcept(false) -> ElementType*;   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  __CDS_NoDiscard auto __dll_newBack () noexcept(false) -> ElementType*;    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

  auto __dll_newFrontArray (Size count, __ElementType** ppElements) noexcept(false) -> void;   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  auto __dll_newBackArray (Size count, __ElementType** ppElements) noexcept(false) -> void; // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

  auto __dll_newAddress ( // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      __ElementType const*  pReferenceElement,
      bool*                 pNewElementCreated
  ) noexcept(false) -> __ElementType*;

  __CDS_NoDiscard auto __dll_newBefore (      // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      AbstractBidirectionalNodeIterator <__ElementType> const& iterator
  ) noexcept(false) -> __ElementType*;

  __CDS_NoDiscard auto __dll_newBeforeConst ( // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      AbstractBidirectionalNodeConstIterator <__ElementType> const& iterator
  ) noexcept(false) -> __ElementType*;

  __CDS_NoDiscard auto __dll_newAfter (       // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      AbstractBidirectionalNodeIterator <__ElementType> const& iterator
  ) noexcept(false) -> __ElementType*;

  __CDS_NoDiscard auto __dll_newAfterConst (  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      AbstractBidirectionalNodeConstIterator <__ElementType> const& iterator
  ) noexcept(false) -> __ElementType*;

  auto __dll_newBeforeArray ( // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      AbstractBidirectionalNodeIterator <__ElementType> const&  iterator,
      Size                                                      count,
      __ElementType**                                           ppElements
  ) noexcept(false) -> bool;

  auto __dll_newBeforeArrayConst ( // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      AbstractBidirectionalNodeConstIterator <__ElementType> const& iterator,
      Size                                                          count,
      __ElementType**                                               ppElements
  ) noexcept(false) -> bool;

  auto __dll_newAfterArray ( // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      AbstractBidirectionalNodeIterator <__ElementType> const&  iterator,
      Size                                                      count,
      __ElementType**                                           ppElements
  ) noexcept(false) -> bool;

  auto __dll_newAfterArrayConst ( // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      AbstractBidirectionalNodeConstIterator <__ElementType> const& iterator,
      Size                                                          count,
      __ElementType**                                               ppElements
  ) noexcept(false) -> bool;

  __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction auto __dll_begin () noexcept -> __dll_Iterator;   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction auto __dll_end () noexcept -> __dll_Iterator;   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  __CDS_NoDiscard constexpr auto __dll_cbegin () const noexcept -> __dll_ConstIterator;   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, modernize-use-nodiscard) */
  __CDS_NoDiscard constexpr auto __dll_cend () const noexcept -> __dll_ConstIterator;   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, modernize-use-nodiscard) */
  __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction auto __dll_rbegin () noexcept -> __dll_ReverseIterator;   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction auto __dll_rend () noexcept -> __dll_ReverseIterator;   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  __CDS_NoDiscard constexpr auto __dll_crbegin () const noexcept -> __dll_ConstReverseIterator;   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, modernize-use-nodiscard) */
  __CDS_NoDiscard constexpr auto __dll_crend () const noexcept -> __dll_ConstReverseIterator;   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, modernize-use-nodiscard) */

  template <
      typename __TElementType = __ElementType,        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      cds::meta::EnableIf <cds::meta::IsCopyConstructible <__TElementType>::value> = 0
  > auto __dll_copy (__DoubleLinkedList const& list) noexcept(false) -> void; // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

  auto __dll_move (__DoubleLinkedList&& list) noexcept -> void; // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

  template <
      typename __TElementType = __ElementType,        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      cds::meta::EnableIf <cds::meta::IsCopyConstructible <__TElementType>::value> = 0
  > auto __dll_copyCleared (__DoubleLinkedList const& list) noexcept(false) -> void; // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

  __CDS_cpplang_NonConstConstexprMemberFunction auto __dll_moveCleared (  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      __DoubleLinkedList&& list
  ) noexcept -> void;

  __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto __dll_equals (  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-non-private-member-variables-in-classes) */
      __DoubleLinkedList const& list
  ) const noexcept -> bool;

  template <typename __Comparator = decltype (&cds::predicates::lessThan <__ElementType>)> auto __dll_sort (                                                                             // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      __Comparator const& comparator = &cds::predicates::lessThan <__ElementType>
  ) noexcept -> void;

private:
  using __NodeType = cds::__hidden::__impl::__BidirectionalNode <__ElementType>;  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

  Size        _size      {0u};
  __NodeType* _pFront    {nullptr};
  __NodeType* _pBack     {nullptr};

  __CDS_NoDiscard static auto __dll_allocateNode () noexcept(false) -> __NodeType*;  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  static auto __dll_freeNode (__NodeType* pNode) noexcept -> void; // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

  __CDS_NoDiscard auto __dll_newBetweenNodes (    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      __NodeType const* pPrevious,
      __NodeType const* pCurrent
  ) noexcept(false) -> __ElementType*;

  auto __dll_newBetweenNodesArray ( // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      __NodeType const* pPrevious,
      __NodeType const* pCurrent,
      Size              count,
      __ElementType**   ppElements
  ) noexcept(false) -> void;
};


template <
    typename                                                                    __ElementType,  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__ElementType const&, __ElementType const&>  __equals        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> template <
    typename                                                                    __ServerType    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> class __DoubleLinkedList <__ElementType, __equals>::__Dispatcher :
    public __ListServerDispatcher <
        __ServerType, __DoubleLinkedList, __ElementType,
        AbstractBidirectionalNodeIterator <__ElementType>, AbstractBidirectionalNodeConstIterator <__ElementType>,
        ForwardBidirectionalNodeIterator <__ElementType>, ForwardBidirectionalNodeConstIterator <__ElementType>,
        BackwardBidirectionalNodeIterator <__ElementType>, BackwardBidirectionalNodeConstIterator <__ElementType>,
        &__DoubleLinkedList::__dll_begin, &__DoubleLinkedList::__dll_end,
        &__DoubleLinkedList::__dll_cbegin, &__DoubleLinkedList::__dll_cend,
        &__DoubleLinkedList::__dll_rbegin, &__DoubleLinkedList::__dll_rend,
        &__DoubleLinkedList::__dll_crbegin, &__DoubleLinkedList::__dll_crend,
        &__DoubleLinkedList::__dll_newAddress, &__DoubleLinkedList::__dll_newFront, &__DoubleLinkedList::__dll_newBack,
        &__DoubleLinkedList::__dll_newFrontArray, &__DoubleLinkedList::__dll_newBackArray,
        &__DoubleLinkedList::__dll_newBefore, &__DoubleLinkedList::__dll_newBeforeConst,
        &__DoubleLinkedList::__dll_newAfter, &__DoubleLinkedList::__dll_newAfterConst,
        &__DoubleLinkedList::__dll_newBeforeArray, &__DoubleLinkedList::__dll_newBeforeArrayConst,
        &__DoubleLinkedList::__dll_newAfterArray, &__DoubleLinkedList::__dll_newAfterArrayConst,
        &__DoubleLinkedList::__dll_removeIterator, &__DoubleLinkedList::__dll_removeConstIterator,
        &__DoubleLinkedList::__dll_removeIteratorArray, &__DoubleLinkedList::__dll_removeConstIteratorArray
    > {};

} // namespace __impl
} // namespace __hidden
} // namespace cds

#endif // __CDS_SHARED_DOUBLE_LINKED_LIST_HPP__
