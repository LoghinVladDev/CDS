// NOLINT(llvm-header-guard)
// Created by loghin on 7/2/22.
//

#ifndef __CDS_ARRAY_IMPL_HPP__ // NOLINT(llvm-header-guard)
#define __CDS_ARRAY_IMPL_HPP__ // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
#pragma once

namespace cds {

template <typename __ElementType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_ConstexprOverride auto Array <__ElementType>::__iicch_obtainGenericHandler (
    __hidden::__impl::__IterableInternalRequest requestType
) noexcept -> __GenericHandler {
  return __ls_handlers() [static_cast <uint32> (requestType)];
}


template <typename __ElementType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_ConstexprOverride auto Array <__ElementType>::__iicch_obtainGenericConstHandler (
    __hidden::__impl::__IterableInternalRequest requestType
) const noexcept -> __GenericConstHandler {
  return __ls_constHandlers() [static_cast <uint32> (requestType)];
}


template <typename __ElementType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline Array <__ElementType>::Array (Array const& array) noexcept(false) :
    Implementation (array) {

}


template <typename __ElementType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
constexpr Array <__ElementType>::Array (Array&& array) noexcept :
    Implementation (std::move (array)) {

}


template <typename __ElementType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <
    typename __IteratorType,    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __TElementType,    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    cds::meta::EnableIf <cds::meta::IsCopyConstructible <__TElementType>::value>
> __CDS_OptimalInline Array <__ElementType>::Array (
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
> __CDS_OptimalInline Array <__ElementType>::Array (
    std::initializer_list <__ElementType> const& initializerList
) noexcept(false) :
    Array (initializerList.begin(), initializerList.end(), initializerList.size()) {

}


template <typename __ElementType>     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <
    typename __TElementType, // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    cds::meta::EnableIf <cds::meta::IsDefaultConstructible <__TElementType>::value>
> __CDS_OptimalInline Array <__ElementType>::Array (Size size) noexcept(false) {
  __ab_resize (size);
}


template <typename __ElementType>     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <
    typename __TElementType, // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    cds::meta::EnableIf <cds::meta::IsCopyConstructible <__TElementType>::value>
> __CDS_OptimalInline Array <__ElementType>::Array (Size size,__ElementType const & defaultValue) noexcept(false) {
  __ab_resize (size, defaultValue);
}


template <typename __ElementType>     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template < typename __IterableType >    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline Array <__ElementType>::Array (__IterableType const& iterable) noexcept(false) {
  pushBackAllOf (iterable);
}


template <typename __ElementType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
Array <__ElementType>::~Array () noexcept {
  __ab_clear (true);
}


template <typename __ElementType>     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto Array <__ElementType>::operator = (Array const& array) noexcept(false) -> Array& {
  if (this == &array) {
    return *this;
  }

  __ab_copy (array);
  return *this;
}


template <typename __ElementType>     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto Array <__ElementType>::operator = (Array&& array) noexcept -> Array& {
  if (this == &array) {
    return *this;
  }

  __ab_move (std::move (array));
  return *this;
}


template <typename __ElementType>     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto Array <__ElementType>::operator = (
    std::initializer_list <__ElementType> const& initializerList
) noexcept(false) -> Array& {
  clear ();
  pushBackAllOf (initializerList);
  return *this;
}


template <typename __ElementType>     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template < typename __IterableType >    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto Array <__ElementType>::operator = (
    __IterableType const& iterable
) noexcept(false) -> Array& {
  if (this == &iterable) {
    return *this;
  }

  clear();
  pushBackAllOf (iterable);
  return * this;
}


template <typename __ElementType>     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_ConstexprConditioned auto Array <__ElementType>::operator == (
    Array const& array
) const noexcept -> bool {
  if (this == &array) {
    return true;
  }

  return __ab_equals (array);
}


template <typename __ElementType>     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_ConstexprConditioned auto Array <__ElementType>::operator != (
    Array const& array
) const noexcept -> bool {
  if (this == &array) {
    return false;
  }

  return !__ab_equals (array); /* NOLINT(clion-misra-cpp2008-5-3-1) */
}


template <typename __ElementType>     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto Array <__ElementType>::reserve (Size size) noexcept(false) -> void {
  __ab_reserve (size);
}


template <typename __ElementType>     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto Array <__ElementType>::shrink (Size size) noexcept -> void {
  __ab_shrink (size);
}


template <typename __ElementType>     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <
    typename __TElementType, // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    cds::meta::EnableIf <cds::meta::IsDefaultConstructible <__TElementType>::value>
> __CDS_OptimalInline auto Array <__ElementType>::resize (Size size) noexcept(false) -> void {
  __ab_resize (size);
}


template <typename __ElementType>     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <
    typename __TElementType, // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    cds::meta::EnableIf <cds::meta::IsCopyConstructible <__TElementType>::value>
> __CDS_OptimalInline auto Array <__ElementType>::resize (
    Size                  size,
    __ElementType const&  defaultValue
) noexcept(false) -> void {
  __ab_resize (size, defaultValue);
}


template <typename __ElementType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
auto Array <__ElementType>::clear () noexcept -> void {
  __ab_clear (false);
}


template <typename __ElementType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_ConstexprOverride auto Array <__ElementType>::size () const noexcept -> Size {
  return __ab_size ();
}


template <typename __ElementType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
auto Array <__ElementType>::popFront () noexcept -> void {
  __ab_remove (0);
}


template <typename __ElementType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
auto Array <__ElementType>::popBack () noexcept -> void {
  __ab_remove (__ab_size() - 1u);
}


template <typename __ElementType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_ConstexprOverride auto Array <__ElementType>::front () noexcept (false) -> ElementType& {
  if (empty()) {
    throw OutOfBoundsException ("Array is Empty");
  }

  return *__ab_get (0);
}


template <typename __ElementType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_ConstexprOverride auto Array <__ElementType>::front () const noexcept (false) -> ElementType const& {
  if (empty()) {
    throw OutOfBoundsException ("Array is Empty");
  }

  return *__ab_get (0);
}


template <typename __ElementType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_ConstexprOverride auto Array <__ElementType>::back () noexcept (false) -> ElementType& {
  if (empty()) {
    throw OutOfBoundsException ("Array is Empty");
  }

  return *__ab_get (__ab_size() - 1u);
}


template <typename __ElementType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_ConstexprOverride auto Array <__ElementType>::back () const noexcept (false) -> ElementType const& {
  if (empty()) {
    throw OutOfBoundsException ("Array is Empty");
  }

  return *__ab_get (__ab_size() - 1u);
}


template <typename __ElementType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_ConstexprOverride auto Array <__ElementType>::get (Index index) noexcept (false) -> ElementType& {
  if (empty()) {
    throw OutOfBoundsException (index, 0);
  }

  return *__ab_get (ListBase::circularAdjustedIndex (index));
}


template <typename __ElementType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_ConstexprOverride auto Array <__ElementType>::get (Index index) const noexcept (false) -> ElementType const& {
  if (empty()) {
    throw OutOfBoundsException (index, 0);
  }

  return *__ab_get (ListBase::circularAdjustedIndex (index));
}


template <typename __ElementType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
auto Array <__ElementType>::removeAt (Index index) noexcept -> bool {
  if (empty()) {
    return false;
  }

  __ab_remove (ListBase::circularAdjustedIndex (index));
  return true;
}


template <typename __ElementType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
constexpr auto Array <__ElementType>::data () const noexcept -> __ElementType const* {
  return __ab_data();
}


template <typename __ElementType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_NonConstConstexprMemberFunction auto Array <__ElementType>::data () noexcept -> __ElementType* {
  return __ab_data();
}


template <typename __ElementType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto Array <__ElementType>::sort (
    cds::Function < auto ( __ElementType const &, __ElementType const & ) -> bool > const & comparator
) noexcept -> void {
  return sort <decltype (comparator)> (comparator);
}


template <typename __ElementType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template < typename __Comparator >  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto Array <__ElementType>::sort (__Comparator const& comparator) noexcept -> void {
  return __ab_sort (comparator);
}

} // namespace cds

#endif // __CDS_ARRAY_IMPL_HPP__
