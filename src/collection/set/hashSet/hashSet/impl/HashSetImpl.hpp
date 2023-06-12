// NOLINT(llvm-header-guard)
// Created by loghin on 10/08/22.
//

#ifndef __CDS_HASH_SET_IMPL_HPP__ // NOLINT(llvm-header-guard)
#define __CDS_HASH_SET_IMPL_HPP__ // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
#pragma once

namespace cds {

template <typename __ElementType, typename __Hasher>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_ConstexprOverride auto HashSet <__ElementType, __Hasher>::__iicch_obtainGenericHandler (
    __hidden::__impl::__IterableInternalRequest requestType
) noexcept -> __GenericHandler {
  return __ss_handlers() [static_cast <uint32> (requestType)];
}


template <typename __ElementType, typename __Hasher>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
 __CDS_cpplang_ConstexprOverride auto HashSet <__ElementType, __Hasher>::__iicch_obtainGenericConstHandler (
    __hidden::__impl::__IterableInternalRequest requestType
) const noexcept -> __GenericConstHandler {
  return __ss_constHandlers() [static_cast <uint32> (requestType)];
}


template <typename __ElementType, typename __Hasher>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
 constexpr HashSet <__ElementType, __Hasher>::HashSet () noexcept = default;


template <typename __ElementType, typename __Hasher>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline HashSet <__ElementType, __Hasher>::HashSet (
    HashSet const& set
) noexcept(false) {
  __ht_copyCleared (set, &cds::__hidden::__impl::__hashSetCopyConstructor <__ElementType>);
}


template <typename __ElementType, typename __Hasher>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
constexpr HashSet <__ElementType, __Hasher>::HashSet (HashSet&& set) noexcept :
    Implementation (std::move (set)) {

}


template <typename __ElementType, typename __Hasher>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
constexpr HashSet <__ElementType, __Hasher>::HashSet (__Hasher const& hasher) noexcept :
    Implementation (hasher) {

}


template <typename __ElementType, typename __Hasher>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <
    typename __IteratorType,    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __TElementType,    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    cds::meta::EnableIf <cds::meta::IsCopyConstructible <__TElementType>::value>
> __CDS_OptimalInline HashSet <__ElementType, __Hasher>::HashSet (
    __IteratorType const& begin,
    __IteratorType const& end,
    Size                  count
) noexcept(false) {
  (void) count;
  for (auto iterator = begin; iterator != end; ++iterator) {
    insert (*iterator);
  }
}


template <typename __ElementType, typename __Hasher>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <
    typename __IteratorType,    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __TElementType,    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    cds::meta::EnableIf <cds::meta::IsCopyConstructible <__TElementType>::value>
> __CDS_OptimalInline HashSet <__ElementType, __Hasher>::HashSet (
    __Hasher const&       hasher,
    __IteratorType const& begin,
    __IteratorType const& end,
    Size                  count
) noexcept(false) :
    Implementation (hasher) {
  (void) count;
  for (auto iterator = begin; iterator != end; ++iterator) {
    insert (*iterator);
  }
}


template <typename __ElementType, typename __Hasher>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <
    typename __TElementType,    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    cds::meta::EnableIf <cds::meta::IsCopyConstructible <__TElementType>::value>
> __CDS_OptimalInline HashSet <__ElementType, __Hasher>::HashSet (
    std::initializer_list < __ElementType > const& initializerList
) noexcept(false) :
    HashSet (initializerList.begin (), initializerList.end (), initializerList.size()) {

}


template <typename __ElementType, typename __Hasher>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <
    typename __TElementType,    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    cds::meta::EnableIf <cds::meta::IsCopyConstructible <__TElementType>::value>
> __CDS_OptimalInline HashSet <__ElementType, __Hasher>::HashSet (
    __Hasher const&                               hasher,
    std::initializer_list <__ElementType> const&  initializerList
) noexcept(false) :
    HashSet (hasher, initializerList.begin (), initializerList.end (), initializerList.size()) {

}


template <typename __ElementType, typename __Hasher>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
template <typename __IterableType>                    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline HashSet <__ElementType, __Hasher>::HashSet (
    __IterableType const& iterable
) noexcept(false) :
    HashSet (iterable.begin (), iterable.end ()) {

}


template <typename __ElementType, typename __Hasher>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
template <typename __IterableType>                    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline HashSet <__ElementType, __Hasher>::HashSet (
    __Hasher const&       hasher,
    __IterableType const& iterable
) noexcept(false) :
    HashSet (hasher, iterable.begin(), iterable.end()) {

}


template <typename __ElementType, typename __Hasher>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline HashSet <__ElementType, __Hasher>::~HashSet () noexcept {
  __ht_clear ();
}


template <typename __ElementType, typename __Hasher>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto HashSet <__ElementType, __Hasher>::operator = (
    HashSet const& set
) noexcept(false) -> HashSet& {
  if (this == &set) {
    return *this;
  }

  __ht_copy (set, &cds::__hidden::__impl::__hashSetCopyConstructor <__ElementType>);
  return *this;
}


template <typename __ElementType, typename __Hasher>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto HashSet <__ElementType, __Hasher>::operator = (HashSet&& set) noexcept -> HashSet& {
  if (this == &set) {
    return *this;
  }

  __ht_move (std::move (set));
  return *this;
}


template <typename __ElementType, typename __Hasher>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto HashSet <__ElementType, __Hasher>::operator = (
    std::initializer_list < __ElementType > const& initializerList
) noexcept(false) -> HashSet& {
  __ht_clear ();
  for (auto iterator = initializerList.begin(), end = initializerList.end(); iterator != end; ++iterator) { // NOLINT(clion-misra-cpp2008-8-0-1)
    (void) insert (*iterator);
  }

  return * this;
}


template <typename __ElementType, typename __Hasher>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename __IterableType>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto HashSet <__ElementType, __Hasher>::operator = (
    __IterableType const& iterable
) noexcept(false) -> HashSet& {
  if (this == &iterable) {
    return *this;
  }

  __ht_clear ();
  for (auto iterator = iterable.begin(), end = iterable.end(); iterator != end; ++iterator) { // NOLINT(clion-misra-cpp2008-8-0-1)
    insert (*iterator);
  }

  return *this;
}


template <typename __ElementType, typename __Hasher>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
 __CDS_cpplang_ConstexprOverride auto HashSet <__ElementType, __Hasher>::size () const noexcept -> Size {
  return __ht_size();
}


template <typename __ElementType, typename __Hasher>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
 __CDS_OptimalInline auto HashSet <__ElementType, __Hasher>::clear () noexcept -> void {
  return __ht_clear();
}


template <typename __ElementType, typename __Hasher>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
 __CDS_OptimalInline auto HashSet <__ElementType, __Hasher>::remove (
    __ElementType const& element
) noexcept -> bool {
  return __ht_remove (element);
}


template <typename __ElementType, typename __Hasher>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
 __CDS_cpplang_ConstexprOverride auto HashSet <__ElementType, __Hasher>::contains (
    __ElementType const& element
) const noexcept -> bool {
  return __ht_getConst (element) != nullptr;
}


template <typename __ElementType, typename __Hasher>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_ConstexprConditioned auto HashSet <__ElementType, __Hasher>::operator == (
    HashSet const& set
) const noexcept -> bool {
  if (this == &set) {
    return true;
  }

  return __ht_equals (set);
}


template <typename __ElementType, typename __Hasher>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_ConstexprConditioned auto HashSet <__ElementType, __Hasher>::operator != (
    HashSet const& set
) const noexcept -> bool {
  if (this == &set) {
    return false;
  }

  return !__ht_equals (set); // NOLINT(clion-misra-cpp2008-5-3-1)
}

} // namespace cds

#endif // __CDS_HASH_SET_IMPL_HPP__ 
