//
// Created by loghin on 6/26/22.
//

#ifndef __CDS_SHARED_CONTAINS_OF_COMPOSITE_CLIENT_IMPL_HPP__ // NOLINT(llvm-header-guard) 
#define __CDS_SHARED_CONTAINS_OF_COMPOSITE_CLIENT_IMPL_HPP__ // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
#pragma once

namespace cds {       // NOLINT(modernize-concat-nested-namespaces)
namespace __hidden {  // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
namespace __impl {    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <
    typename                                                                __Iterable,     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                                __Element,      // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                                __FromIterable, // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__FromIterable const&, __Element const&> __contains,     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    bool                                                                    __exceptCond    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> auto __ContainsOfCompositeClient <__Iterable, __Element, __FromIterable, __contains, __exceptCond>::containsAnyOf (
    __FromIterable const& from
) const noexcept(allNoexcept) -> bool {
  auto const* pIterable = static_cast <__Iterable const*> (this);
  // parse the received iterable's elements 
  for (auto iterator = from.begin(), end = from.end(); iterator != end; ++iterator) {
    // if any is found in the caller iterable, caller contains any of the parameter's elements
    // Use caller contains as it might be optimized ( HashSet / HashMap ), as compared to
    // parameter contains, which could be linear
    if (pIterable->contains (*iterator)) {
      return true;
    }
  }

  // otherwise, no matching element found. Return false 
  return false;
}


template <
    typename                                                                __Iterable,     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                                __Element,      // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                                __FromIterable, // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__FromIterable const&, __Element const&> __contains,     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    bool                                                                    __exceptCond    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> auto __ContainsOfCompositeClient <__Iterable, __Element, __FromIterable, __contains, __exceptCond>::containsAnyNotOf (
    __FromIterable const& from
) const noexcept(allNoexcept) -> bool {
  auto const* pIterable = static_cast <__Iterable const*> (this);
  // when checking contains any not of, checking must be done from caller. Parse caller's elements
  for (auto iterator = pIterable->cbegin(), end = pIterable->cend(); iterator != end; ++iterator) {
    // If parameter iterable does not contain an element, the iterable contains elements not of the given iterable 
    if (!__contains (from, *iterator)) {
      return true;
    }
  }

  // Otherwise, no element not to be found in the given iterable was found, return false 
  return false;
}


template <
    typename                                                                __Iterable,     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                                __Element,      // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                                __FromIterable, // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__FromIterable const&, __Element const&> __contains,     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    bool                                                                    __exceptCond    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> auto __ContainsOfCompositeClient <__Iterable, __Element, __FromIterable, __contains, __exceptCond>::containsAllOf (
    __FromIterable const& from
) const noexcept(allNoexcept) -> bool {
  auto const* pIterable = static_cast <__Iterable const*> (this);
  // Parse received iterable 
  for (auto iterator = from.begin(), end = from.end(); iterator != end; ++iterator) {
    // If any element of the iterable is not found in the caller iterable, return false
    // Same reason for reverse approach as 'containsAnyOf'
    if (!pIterable->contains (*iterator)) {
      return false;
    }
  }

  // Otherwise, all elements in given iterable have a match in the caller one. Return true 
  return true;
}


template <
    typename                                                                __Iterable,     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                                __Element,      // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                                __FromIterable, // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__FromIterable const&, __Element const&> __contains,     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    bool                                                                    __exceptCond    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> auto __ContainsOfCompositeClient <__Iterable, __Element, __FromIterable, __contains, __exceptCond>::containsNoneOf (
    __FromIterable const& from
) const noexcept(allNoexcept) -> bool {
  auto const* pIterable = static_cast <__Iterable const*> (this);
  // Parse the received iterable's elements 
  for (auto iterator = from.begin(), end = from.end(); iterator != end; ++iterator) {
    // If any has a match in the caller iterable, it contains at least one element, return false
    // Reason for reverse approach same as in 'containsAnyOf'
    if (pIterable->contains (*iterator)) {
      return false;
    }
  }

  // Otherwise, no element in received iterable found in caller, caller contains none of the values in the
  // received iterable, return true
  return true;
}
} // namespace __impl 
} // namespace __hidden 
} // namespace cds 

#endif // __CDS_SHARED_CONTAINS_OF_COMPOSITE_CLIENT_IMPL_HPP__ 
