// NOLINT(llvm-header-guard)
// Created by loghin on 17/07/22.
//

#ifndef __CDS_LINKED_LIST_IMPL_HPP__ // NOLINT(llvm-header-guard) 
#define __CDS_LINKED_LIST_IMPL_HPP__ // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
#pragma once

namespace cds {
template <typename __ElementType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_ConstexprOverride auto LinkedList <__ElementType>::__iicch_obtainGenericHandler (
    __hidden::__impl::__IterableInternalRequest requestType
) noexcept -> __GenericHandler {
  return __ls_handlers() [static_cast <uint32> (requestType)];
}


template <typename __ElementType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_ConstexprOverride auto LinkedList <__ElementType>::__iicch_obtainGenericConstHandler (
    __hidden::__impl::__IterableInternalRequest requestType
) const noexcept -> __GenericConstHandler {
  return __ls_constHandlers() [static_cast <uint32> (requestType)];
}


template <typename __ElementType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
constexpr LinkedList <__ElementType>::LinkedList () noexcept = default;


template <typename __ElementType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline LinkedList <__ElementType>::LinkedList (LinkedList const& list) noexcept(false) :
    Implementation (list) {

}


template <typename __ElementType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
constexpr LinkedList <__ElementType>::LinkedList (LinkedList&& list) noexcept :
    Implementation (std::move (list)) {

}


template <typename __ElementType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <
    typename __IteratorType,    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __TElementType,    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    cds::meta::EnableIf <cds::meta::IsCopyConstructible <__TElementType>::value>
> __CDS_OptimalInline LinkedList <__ElementType>::LinkedList (
    __IteratorType const& begin,
    __IteratorType const& end,
    Size                  count
) noexcept(false) {
  pushBackAllOf (begin, end, count);
}


template <typename __ElementType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <
    typename __TElementType,    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    cds::meta::EnableIf <cds::meta::IsCopyConstructible <__TElementType>::value>
> __CDS_OptimalInline LinkedList <__ElementType>::LinkedList (
    std::initializer_list <__ElementType> const& initializerList
) noexcept(false) :
    LinkedList (initializerList.begin(), initializerList.end(), initializerList.size()) {

}


template <typename __ElementType>     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename __IterableType>    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline LinkedList <__ElementType>::LinkedList (__IterableType const& iterable) noexcept(false) {
  pushBackAllOf (iterable);
}


template <typename __ElementType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
LinkedList <__ElementType>::~LinkedList () noexcept {
  __dll_clear();
}


template <typename __ElementType>     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto LinkedList <__ElementType>::operator = (
    LinkedList const& list
) noexcept(false) -> LinkedList& {
  if (this == &list) {
    return *this;
  }

  __dll_copy (list);
  return *this;
}


template <typename __ElementType>     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto LinkedList <__ElementType>::operator = (LinkedList&& list) noexcept -> LinkedList& {
  if (this == &list) {
    return *this;
  }

  __dll_move (std::move (list));
  return *this;
}


template <typename __ElementType>     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto LinkedList <__ElementType>::operator = (
    std::initializer_list <__ElementType> const& initializerList
) noexcept(false) -> LinkedList& {
  clear();
  pushBackAllOf (initializerList);
  return * this;
}


template <typename __ElementType>     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename __IterableType>    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto LinkedList <__ElementType>::operator = (
    __IterableType const& iterable
) noexcept(false) -> LinkedList& {
  if (this == &iterable) {
    return *this;
  }

  clear();
  pushBackAllOf (iterable);
  return *this;
}


template <typename __ElementType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
auto LinkedList <__ElementType>::clear () noexcept -> void {
  __dll_clear ();
}


template <typename __ElementType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_ConstexprOverride auto LinkedList <__ElementType>::size () const noexcept -> Size {
  return __dll_size ();
}


template <typename __ElementType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
auto LinkedList <__ElementType>::popFront () noexcept -> void {
  __dll_removeFront ();
}


template <typename __ElementType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
auto LinkedList <__ElementType>::popBack () noexcept -> void {
  __dll_removeBack ();
}


template <typename __ElementType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_ConstexprOverride auto LinkedList <__ElementType>::front () noexcept (false) -> ElementType& {
  if (empty()) {
    throw OutOfBoundsException ("List is Empty");
  }

  return *__dll_front();
}


template <typename __ElementType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_ConstexprOverride auto LinkedList <__ElementType>::front () const noexcept (false) -> ElementType const& {
  if (empty()) {
    throw OutOfBoundsException ("List is Empty");
  }

  return *__dll_front();
}


template <typename __ElementType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_ConstexprOverride auto LinkedList <__ElementType>::back () noexcept (false) -> ElementType& {
  if (empty()) {
    throw OutOfBoundsException ("List is Empty");
  }

  return *__dll_back();
}


template <typename __ElementType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_ConstexprOverride auto LinkedList <__ElementType>::back () const noexcept (false) -> ElementType const& {
  if (empty()) {
    throw OutOfBoundsException ("List is Empty");
  }

  return *__dll_back();
}


template <typename __ElementType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_ConstexprOverride auto LinkedList <__ElementType>::get (Index index) noexcept (false) -> ElementType& {
  if (empty()) {
    throw OutOfBoundsException (index, 0);
  }

  return *__dll_get (ListBase::circularAdjustedIndex (index));
}


template <typename __ElementType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_ConstexprOverride auto LinkedList <__ElementType>::get (Index index) const noexcept (false) -> ElementType const& {
  if (empty()) {
    throw OutOfBoundsException (index, 0);
  }

  return *__dll_get (ListBase::circularAdjustedIndex (index));
}


template <typename __ElementType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
auto LinkedList <__ElementType>::removeAt (Index index) noexcept -> bool {
  if (empty()) {
    return false;
  }

  __dll_removeAt (ListBase::circularAdjustedIndex (index));
  return true;
}


template <typename __ElementType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_ConstexprConditioned auto LinkedList <__ElementType>::operator == (
    LinkedList const& list
) const noexcept -> bool {
  if (&list == this) {
    return true;
  }

  return __dll_equals (list);
}


template <typename __ElementType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_ConstexprConditioned auto LinkedList <__ElementType>::operator != (
    LinkedList const& list
) const noexcept -> bool {
  if (&list == this) {
    return false;
  }

  return !__dll_equals (list); // NOLINT(clion-misra-cpp2008-5-3-1)
}


template <typename __ElementType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto LinkedList <__ElementType>::sort (
    cds::Function <auto (__ElementType const&, __ElementType const&) -> bool > const& comparator
) noexcept -> void {
  return sort <decltype (comparator)> (comparator);
}


template <typename __ElementType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template < typename __Comparator >  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto LinkedList <__ElementType>::sort (
    __Comparator const& comparator
) noexcept -> void {
  return __dll_sort (comparator);
}
} // namespace cds

#endif // __CDS_LINKED_LIST_IMPL_HPP__
