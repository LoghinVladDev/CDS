//
// Created by stefan on 28.08.2022.
//

#ifndef __CDS_TREE_SET_IMPL_HPP__
#define __CDS_TREE_SET_IMPL_HPP__ // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
#pragma once

namespace cds {
template <typename __ElementType, typename __Comparator>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_ConstexprOverride auto TreeSet <__ElementType, __Comparator>::__iicch_obtainGenericHandler (
    cds::__hidden::__impl::__IterableInternalRequest requestType
) noexcept -> __GenericHandler {
  return __ss_handlers() [static_cast <uint32> (requestType)];
}


template <typename __ElementType, typename __Comparator>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_ConstexprOverride auto TreeSet <__ElementType, __Comparator>::__iicch_obtainGenericConstHandler (   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    cds::__hidden::__impl::__IterableInternalRequest requestType
) const noexcept -> __GenericConstHandler {
  return __ss_constHandlers() [static_cast <uint32> (requestType)];
}


template <typename __ElementType, typename __Comparator>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
constexpr TreeSet <__ElementType, __Comparator>::TreeSet () noexcept = default;


template <typename __ElementType, typename __Comparator>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline TreeSet <__ElementType, __Comparator>::TreeSet (TreeSet const& set) noexcept(false) {
  this->template __rbt_copyCleared <&__hidden::__impl::__treeSetCopyConstructor <__ElementType>> (set);
}


template <typename __ElementType, typename __Comparator>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
constexpr TreeSet <__ElementType, __Comparator>::TreeSet (TreeSet&& set) noexcept :
    Implementation (std::move (set)) {

}


template <typename __ElementType, typename __Comparator>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <
    typename __IteratorType,     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __TElementType,     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    cds::meta::EnableIf <cds::meta::IsCopyConstructible <__TElementType>::value>
> __CDS_OptimalInline TreeSet <__ElementType, __Comparator>::TreeSet (
    __IteratorType const& begin,
    __IteratorType const& end,
    Size                  count
) noexcept(false) {
  for (auto iterator = begin; iterator != end; ++ iterator) {
    insert (*iterator);
  }
}


template <typename __ElementType, typename __Comparator>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <
    typename __TElementType,     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    cds::meta::EnableIf <cds::meta::IsCopyConstructible <__TElementType>::value>
> __CDS_OptimalInline TreeSet <__ElementType, __Comparator>::TreeSet (
    std::initializer_list < __ElementType > const& initializerList
) noexcept(false) :
    TreeSet (initializerList.begin(), initializerList.end()) {

}


template <typename __ElementType, typename __Comparator>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename __IterableType>     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline TreeSet <__ElementType, __Comparator>::TreeSet (
    __IterableType const& iterable
) noexcept(false) :
    TreeSet (iterable.begin(), iterable.end()) {

}


template <typename __ElementType, typename __Comparator>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_ConstexprDestructor TreeSet <__ElementType, __Comparator>::~TreeSet () noexcept {
  __rbt_clear();
}


template <typename __ElementType, typename __Comparator>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto TreeSet <__ElementType, __Comparator>::operator = (  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    TreeSet const& set
) noexcept(false) -> TreeSet& {
  __rbt_copy <&__hidden::__impl::__treeSetCopyConstructor <__ElementType>> (set);
  return * this;
}


template <typename __ElementType, typename __Comparator>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto TreeSet <__ElementType, __Comparator>::operator = (  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    TreeSet&& set
) noexcept -> TreeSet& {
  __rbt_move (std::move (set));
  return * this;
}


template <typename __ElementType, typename __Comparator>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto TreeSet <__ElementType, __Comparator>::operator = (  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    std::initializer_list <__ElementType> const& initializerList
) noexcept(false) -> TreeSet& {
  __rbt_clear();
  for (auto const& element : initializerList) {
    insert(element);
  }
  return * this;
}


template <typename __ElementType, typename __Comparator>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename __IterableType>                        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto TreeSet <__ElementType, __Comparator>::operator = (  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    __IterableType const& iterable
) noexcept(false) -> TreeSet& {
  __rbt_clear();
  for (auto const& element : iterable) {
    insert(element);
  }
  return * this;
}


template <typename __ElementType, typename __Comparator>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_ConstexprOverride auto TreeSet <__ElementType, __Comparator>::contains (
    __ElementType const& element
) const noexcept -> bool {
  return __rbt_get (element) != nullptr;
}


template <typename __ElementType, typename __Comparator>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_ConstexprOverride auto TreeSet <__ElementType, __Comparator>::size ()  const noexcept -> Size {
  return __rbt_size();
}


template <typename __ElementType, typename __Comparator>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto TreeSet <__ElementType, __Comparator>::clear () noexcept -> void {
  __rbt_clear();
}


template <
    typename __ElementType,     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __Comparator       // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
>__CDS_OptimalInline auto TreeSet <__ElementType, __Comparator>::remove (
    __ElementType const& element
) noexcept -> bool {
  return __rbt_remove (element);
}


template <
    typename __ElementType,     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __Comparator       // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
>__CDS_cpplang_ConstexprConditioned auto TreeSet <__ElementType, __Comparator>::operator == (
    TreeSet const& set
) const noexcept -> bool {
  if (this == &set) {
    return true;
  }

  return __rbt_equals (set);
}


template <
    typename __ElementType,     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __Comparator       // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
>__CDS_cpplang_ConstexprConditioned auto TreeSet <__ElementType, __Comparator>::operator != (
    TreeSet const & set
) const noexcept -> bool {
  if (this == &set) {
    return false;
  }

  return !__rbt_equals (set);
}

}

#endif // __CDS_TREE_SET_IMPL_HPP__
