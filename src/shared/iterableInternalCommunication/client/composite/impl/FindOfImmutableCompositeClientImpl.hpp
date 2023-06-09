//
// Created by loghin on 6/26/22.
//

#ifndef __CDS_SHARED_FIND_OF_IMMUTABLE_COMPOSITE_CLIENT_IMPL_HPP__ // NOLINT(llvm-header-guard) 
#define __CDS_SHARED_FIND_OF_IMMUTABLE_COMPOSITE_CLIENT_IMPL_HPP__ // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
#pragma once

namespace cds {       // NOLINT(modernize-concat-nested-namespaces)
namespace __hidden {  // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
namespace __impl {    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <
    typename                                                                __Iterable,             // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                                __Element,              // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                                __Iterator,             // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                                __FromIterable,         // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__FromIterable const&, __Element const&> __containsFunction,     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__FromIterable const&, __Element const&> __notContainsFunction,  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    bool                                                                    __exceptCond            // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> template <template <typename...> class __Collection> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto __FindOfImmutableCompositeClient <
    __Iterable, __Element, __Iterator, __FromIterable,
    __containsFunction, __notContainsFunction, __exceptCond
>::findOf (
    Size                          count,
    __Collection <ConstIterator>& storeIn,
    __FromIterable const&         from
) const noexcept(false) -> __Collection <ConstIterator>& {
  auto const* pIterable = static_cast <__Iterable const*>(this);
  // Call base, global implementation. Abstracts the 'is object const' requirement
  return __findOf <__Element, ConstIterator, __FromIterable, __Collection, __containsFunction> (
      pIterable->cbegin(), pIterable->cend(), count, storeIn, from
  );
}


template <
    typename                                                                __Iterable,             // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                                __Element,              // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                                __Iterator,             // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                                __FromIterable,         // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__FromIterable const&, __Element const&> __containsFunction,     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__FromIterable const&, __Element const&> __notContainsFunction,  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    bool                                                                    __exceptCond            // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> template <template <typename...> class __Collection> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto __FindOfImmutableCompositeClient <
    __Iterable, __Element, __Iterator, __FromIterable,
    __containsFunction, __notContainsFunction, __exceptCond
>::findOf (Size count, __FromIterable const& from) const noexcept(false) -> __Collection <ConstIterator> {
  auto const* pIterable = static_cast <__Iterable const*>(this);
  // Call base, global implementation. Abstracts the 'is object const' requirement
  __Collection <ConstIterator> foundIterators;
  return __findOf <__Element, ConstIterator, __FromIterable, __Collection, __containsFunction> (
      pIterable->cbegin(), pIterable->cend(), count, foundIterators, from
  );
}


template <
    typename                                                                __Iterable,             // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                                __Element,              // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                                __Iterator,             // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                                __FromIterable,         // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__FromIterable const&, __Element const&> __containsFunction,     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__FromIterable const&, __Element const&> __notContainsFunction,  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    bool                                                                    __exceptCond            // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> __CDS_OptimalInline auto __FindOfImmutableCompositeClient <
    __Iterable, __Element, __Iterator, __FromIterable,
    __containsFunction, __notContainsFunction, __exceptCond
>::findFirstOf (__FromIterable const& from) const noexcept(itNoexcept) -> ConstIterator {
  auto const* pIterable = static_cast <__Iterable const*>(this);
  // Call base, global implementation. Abstracts the 'is object const' requirement
  return __findFirstOf <itNoexcept, __Element, ConstIterator, __FromIterable, __containsFunction> (
      pIterable->cbegin(), pIterable->cend(), from
  );
}


template <
    typename                                                                __Iterable,             // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                                __Element,              // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                                __Iterator,             // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                                __FromIterable,         // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__FromIterable const&, __Element const&> __containsFunction,     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__FromIterable const&, __Element const&> __notContainsFunction,  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    bool                                                                    __exceptCond            // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> __CDS_OptimalInline auto __FindOfImmutableCompositeClient <
    __Iterable, __Element, __Iterator, __FromIterable,
    __containsFunction, __notContainsFunction, __exceptCond
>::findLastOf (__FromIterable const& from) const noexcept(itNoexcept) -> ConstIterator {
  auto const* pIterable = static_cast <__Iterable const*>(this);
  // Call base, global implementation. Abstracts the 'is object const' requirement
  return __findLastOf <itNoexcept, __Element, ConstIterator, __FromIterable, __containsFunction> (
      pIterable->cbegin(), pIterable->cend(), from
  );
}


template <
    typename                                                                __Iterable,             // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                                __Element,              // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                                __Iterator,             // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                                __FromIterable,         // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__FromIterable const&, __Element const&> __containsFunction,     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__FromIterable const&, __Element const&> __notContainsFunction,  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    bool                                                                    __exceptCond            // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> template <template <typename...> class __Collection> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto __FindOfImmutableCompositeClient <
    __Iterable, __Element, __Iterator, __FromIterable,
    __containsFunction, __notContainsFunction, __exceptCond
>::findAllOf (
    __Collection <ConstIterator>& storeIn,
    __FromIterable const&         from
) const noexcept(false) -> __Collection <ConstIterator>& {
  auto const* pIterable = static_cast <__Iterable const*>(this);
  // Call base, global implementation. Abstracts the 'is object const' requirement
  return __findAllOf <__Element, ConstIterator, __FromIterable, __Collection, __containsFunction> (
      pIterable->cbegin(), pIterable->cend(), storeIn, from
  );
}


template <
    typename                                                                __Iterable,             // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                                __Element,              // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                                __Iterator,             // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                                __FromIterable,         // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__FromIterable const&, __Element const&> __containsFunction,     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__FromIterable const&, __Element const&> __notContainsFunction,  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    bool                                                                    __exceptCond            // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> template <template <typename...> class __Collection> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto __FindOfImmutableCompositeClient <
    __Iterable, __Element, __Iterator, __FromIterable,
    __containsFunction, __notContainsFunction, __exceptCond
>::findAllOf (__FromIterable const& from) const noexcept(false) -> __Collection <ConstIterator> {
  auto const* pIterable = static_cast <__Iterable const*>(this);
  // Call base, global implementation. Abstracts the 'is object const' requirement
  __Collection <ConstIterator> foundIterators;
  return __findAllOf <__Element, ConstIterator, __FromIterable, __Collection, __containsFunction> (
      pIterable->cbegin(), pIterable->cend(), foundIterators, from
  );
}

template <
    typename                                                                __Iterable,             // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                                __Element,              // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                                __Iterator,             // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                                __FromIterable,         // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__FromIterable const&, __Element const&> __containsFunction,     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__FromIterable const&, __Element const&> __notContainsFunction,  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    bool                                                                    __exceptCond            // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> template <template <typename...> class __Collection> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto __FindOfImmutableCompositeClient <
    __Iterable, __Element, __Iterator, __FromIterable,
    __containsFunction, __notContainsFunction, __exceptCond
>::findNotOf (
    Size                          count,
    __Collection <ConstIterator>& storeIn,
    __FromIterable const&         from
) const noexcept(false) -> __Collection <ConstIterator>& {
  auto const* pIterable = static_cast <__Iterable const*>(this);
  // Call base, global implementation. Abstracts the 'is object const' requirement
  return __findOf <__Element, ConstIterator, __FromIterable, __Collection, __notContainsFunction> (
      pIterable->cbegin(), pIterable->cend(), count, storeIn, from
  );
}


template <
    typename                                                                __Iterable,             // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                                __Element,              // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                                __Iterator,             // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                                __FromIterable,         // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__FromIterable const&, __Element const&> __containsFunction,     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__FromIterable const&, __Element const&> __notContainsFunction,  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    bool                                                                    __exceptCond            // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> template <template <typename...> class __Collection> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto __FindOfImmutableCompositeClient <
    __Iterable, __Element, __Iterator, __FromIterable,
    __containsFunction, __notContainsFunction, __exceptCond
>::findNotOf (Size count, __FromIterable const& from) const noexcept(false) -> __Collection <ConstIterator> {
  auto const* pIterable = static_cast <__Iterable const*>(this);
  // Call base, global implementation. Abstracts the 'is object const' requirement
  __Collection <ConstIterator> foundIterators;
  return __findOf <__Element, ConstIterator, __FromIterable, __Collection, __notContainsFunction> (
      pIterable->cbegin(), pIterable->cend(), count, foundIterators, from
  );
}


template <
    typename                                                                __Iterable,             // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                                __Element,              // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                                __Iterator,             // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                                __FromIterable,         // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__FromIterable const&, __Element const&> __containsFunction,     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__FromIterable const&, __Element const&> __notContainsFunction,  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    bool                                                                    __exceptCond            // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> __CDS_OptimalInline auto __FindOfImmutableCompositeClient <
    __Iterable, __Element, __Iterator, __FromIterable,
    __containsFunction, __notContainsFunction, __exceptCond
>::findFirstNotOf (__FromIterable const& from) const noexcept(itNoexcept) -> ConstIterator {
  auto const* pIterable = static_cast <__Iterable const*>(this);
  // Call base, global implementation. Abstracts the 'is object const' requirement
  return __findFirstOf <itNoexcept, __Element, ConstIterator, __FromIterable, __notContainsFunction> (
      pIterable->cbegin(), pIterable->cend(), from
  );
}


template <
    typename                                                                __Iterable,             // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                                __Element,              // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                                __Iterator,             // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                                __FromIterable,         // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__FromIterable const&, __Element const&> __containsFunction,     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__FromIterable const&, __Element const&> __notContainsFunction,  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    bool                                                                    __exceptCond            // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> __CDS_OptimalInline auto __FindOfImmutableCompositeClient <
    __Iterable, __Element, __Iterator, __FromIterable,
    __containsFunction, __notContainsFunction, __exceptCond
>::findLastNotOf (__FromIterable const& from) const noexcept(itNoexcept) -> ConstIterator {
  auto const* pIterable = static_cast <__Iterable const*>(this);
  // Call base, global implementation. Abstracts the 'is object const' requirement
  return __findLastOf <itNoexcept, __Element, ConstIterator, __FromIterable, __notContainsFunction> (
      pIterable->cbegin(), pIterable->cend(), from
  );
}


template <
    typename                                                                __Iterable,             // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                                __Element,              // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                                __Iterator,             // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                                __FromIterable,         // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__FromIterable const&, __Element const&> __containsFunction,     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__FromIterable const&, __Element const&> __notContainsFunction,  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    bool                                                                    __exceptCond            // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> template <template <typename...> class __Collection> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto __FindOfImmutableCompositeClient <
    __Iterable, __Element, __Iterator, __FromIterable,
    __containsFunction, __notContainsFunction, __exceptCond
>::findAllNotOf (
    __Collection <ConstIterator>& storeIn,
    __FromIterable const&         from
) const noexcept(false) -> __Collection <ConstIterator>& {
  auto const* pIterable = static_cast <__Iterable const*>(this);
  // Call base, global implementation. Abstracts the 'is object const' requirement
  return __findAllOf <__Element, ConstIterator, __FromIterable, __Collection, __notContainsFunction> (
      pIterable->cbegin(), pIterable->cend(), storeIn, from
  );
}


template <
    typename                                                                __Iterable,             // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                                __Element,              // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                                __Iterator,             // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                                __FromIterable,         // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__FromIterable const&, __Element const&> __containsFunction,     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__FromIterable const&, __Element const&> __notContainsFunction,  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    bool                                                                    __exceptCond            // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> template <template <typename...> class __Collection> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto __FindOfImmutableCompositeClient <
    __Iterable, __Element, __Iterator, __FromIterable,
    __containsFunction, __notContainsFunction, __exceptCond
>::findAllNotOf (__FromIterable const& from) const noexcept(false) -> __Collection <ConstIterator> {
  auto const* pIterable = static_cast <__Iterable const*>(this);
  // Call base, global implementation. Abstracts the 'is object const' requirement 
  __Collection <ConstIterator> foundIterators;
  return __findAllOf <__Element, ConstIterator, __FromIterable, __Collection, __notContainsFunction> (
      pIterable->cbegin(), pIterable->cend(), foundIterators, from
  );
}
} // namespace __impl 
} // namespace __hidden 
} // namespace cds 

#endif // __CDS_SHARED_FIND_OF_IMMUTABLE_COMPOSITE_CLIENT_IMPL_HPP__ 
