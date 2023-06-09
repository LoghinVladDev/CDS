//
// Created by loghin on 6/26/22.
//

#ifndef __CDS_SHARED_FIND_OF_MUTABLE_COMPOSITE_CLIENT_IMPL_HPP__ // NOLINT(llvm-header-guard)
#define __CDS_SHARED_FIND_OF_MUTABLE_COMPOSITE_CLIENT_IMPL_HPP__ // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
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
> template <template <typename ...> class __Collection> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto __FindOfMutableCompositeClient <
    __Iterable, __Element, __Iterator, __FromIterable,
    __containsFunction, __notContainsFunction, __exceptCond
>::findOf (
    Size                      count,
    __Collection <Iterator>&  storeIn,
    __FromIterable const&     from
) noexcept(false) -> __Collection <Iterator>& {
  // Call base, global implementation. Abstracts the 'is object const' requirement
  auto* pIterable = static_cast <__Iterable*> (this);
  return __findOf <__Element, Iterator, __FromIterable, __Collection, __containsFunction> (
      pIterable->begin(), pIterable->end(), count, storeIn, from
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
> template <template <typename ...> class __Collection> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto __FindOfMutableCompositeClient <
    __Iterable, __Element, __Iterator, __FromIterable,
    __containsFunction, __notContainsFunction, __exceptCond
>::findOf (Size count, __FromIterable const& from) noexcept(false) -> __Collection <Iterator> {
  // Call base, global implementation. Abstracts the 'is object const' requirement
  auto* pIterable = static_cast <__Iterable*> (this);
  __Collection <Iterator> foundIterators;
  return __findOf <__Element, Iterator, __FromIterable, __Collection, __containsFunction> (
      pIterable->begin(), pIterable->end(), count, foundIterators, from
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
> __CDS_OptimalInline auto __FindOfMutableCompositeClient <
    __Iterable, __Element, __Iterator, __FromIterable,
    __containsFunction, __notContainsFunction, __exceptCond
>::findFirstOf (__FromIterable const& from) noexcept(itNoexcept) -> Iterator {
  // Call base, global implementation. Abstracts the 'is object const' requirement
  auto* pIterable = static_cast <__Iterable*> (this);
  return __findFirstOf <__Element, Iterator, __FromIterable, __containsFunction> (
      pIterable->begin(), pIterable->end(), from
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
> __CDS_OptimalInline auto __FindOfMutableCompositeClient <
    __Iterable, __Element, __Iterator, __FromIterable,
    __containsFunction, __notContainsFunction, __exceptCond
>::findLastOf (__FromIterable const& from) noexcept(itNoexcept) -> Iterator {
  // Call base, global implementation. Abstracts the 'is object const' requirement
  auto* pIterable = static_cast <__Iterable*> (this);
  return __findLastOf <__Element, Iterator, __FromIterable, __containsFunction> (
      pIterable->begin(), pIterable->end(), from
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
> template <template <typename ...> class __Collection> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto __FindOfMutableCompositeClient <
    __Iterable, __Element, __Iterator, __FromIterable,
    __containsFunction, __notContainsFunction, __exceptCond
>::findAllOf (__Collection <Iterator>& storeIn, __FromIterable const& from) noexcept(false) -> __Collection <Iterator>& {
  // Call base, global implementation. Abstracts the 'is object const' requirement
  auto* pIterable = static_cast <__Iterable*> (this);
  return __findAllOf <__Element, Iterator, __FromIterable, __Collection, __containsFunction> (
      pIterable->begin(), pIterable->end(), storeIn, from
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
> template <template <typename ...> class __Collection> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto __FindOfMutableCompositeClient <
    __Iterable, __Element, __Iterator, __FromIterable,
    __containsFunction, __notContainsFunction, __exceptCond
>::findAllOf (__FromIterable const& from) noexcept(false) -> __Collection <Iterator> {
  // Call base, global implementation. Abstracts the 'is object const' requirement
  auto* pIterable = static_cast <__Iterable*> (this);
  __Collection <Iterator> foundIterators;
  return __findAllOf <__Element, Iterator, __FromIterable, __Collection, __containsFunction> (
      pIterable->begin(), pIterable->end(), foundIterators, from
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
> template <template <typename ...> class __Collection> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto __FindOfMutableCompositeClient <
    __Iterable, __Element, __Iterator, __FromIterable,
    __containsFunction, __notContainsFunction, __exceptCond
>::findNotOf (
    Size                      count,
    __Collection <Iterator>&  storeIn,
    __FromIterable const&     from
) noexcept(false) -> __Collection <Iterator>& {
  // Call base, global implementation. Abstracts the 'is object const' requirement
  auto* pIterable = static_cast <__Iterable*> (this);
  return __findOf <__Element, Iterator, __FromIterable, __Collection, __notContainsFunction> (
      pIterable->begin(), pIterable->end(), count, storeIn, from
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
> template <template <typename ...> class __Collection> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto __FindOfMutableCompositeClient <
    __Iterable, __Element, __Iterator, __FromIterable,
    __containsFunction, __notContainsFunction, __exceptCond
>::findNotOf (Size count, __FromIterable const& from) noexcept(false) -> __Collection <Iterator> {
  // Call base, global implementation. Abstracts the 'is object const' requirement
  auto* pIterable = static_cast <__Iterable*> (this);
  __Collection <Iterator> foundIterators;
  return __findOf <__Element, Iterator, __FromIterable, __Collection, __notContainsFunction> (
      pIterable->begin(), pIterable->end(), count, foundIterators, from
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
> __CDS_OptimalInline auto __FindOfMutableCompositeClient <
    __Iterable, __Element, __Iterator, __FromIterable,
    __containsFunction, __notContainsFunction, __exceptCond
>::findFirstNotOf (__FromIterable const& from) noexcept(itNoexcept) -> Iterator {
  // Call base, global implementation. Abstracts the 'is object const' requirement
  auto* pIterable = static_cast <__Iterable*> (this);
  return __findFirstOf <__Element, Iterator, __FromIterable, __notContainsFunction> (
      pIterable->begin(), pIterable->end(), from
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
> __CDS_OptimalInline auto __FindOfMutableCompositeClient <
    __Iterable, __Element, __Iterator, __FromIterable,
    __containsFunction, __notContainsFunction, __exceptCond
>::findLastNotOf (__FromIterable const& from) noexcept(itNoexcept) -> Iterator {
  // Call base, global implementation. Abstracts the 'is object const' requirement
  auto* pIterable = static_cast <__Iterable*> (this);
  return __findLastOf <__Element, Iterator, __FromIterable, __notContainsFunction> (
      pIterable->begin(), pIterable->end(), from
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
> template <template <typename ...> class __Collection> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto __FindOfMutableCompositeClient <
    __Iterable, __Element, __Iterator, __FromIterable,
    __containsFunction, __notContainsFunction, __exceptCond
>::findAllNotOf (__Collection <Iterator>& storeIn, __FromIterable const& from) noexcept(false) -> __Collection <Iterator>& {
  // Call base, global implementation. Abstracts the 'is object const' requirement
  auto* pIterable = static_cast <__Iterable*> (this);
  return __findAllOf <__Element, Iterator, __FromIterable, __Collection, __notContainsFunction> (
      pIterable->begin(), pIterable->end(), storeIn, from
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
> template <template <typename ...> class __Collection> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto __FindOfMutableCompositeClient <
    __Iterable, __Element, __Iterator, __FromIterable,
    __containsFunction, __notContainsFunction, __exceptCond
>::findAllNotOf (__FromIterable const& from) noexcept(false) -> __Collection <Iterator> {
  // Call base, global implementation. Abstracts the 'is object const' requirement
  auto* pIterable = static_cast <__Iterable*> (this);
  __Collection <Iterator> foundIterators;
  return __findAllOf <__Element, Iterator, __FromIterable, __Collection, __notContainsFunction> (
      pIterable->begin(), pIterable->end(), foundIterators, from
  );
}
} // namespace __impl
} // namespace __hidden
} // namespace cds

#endif // __CDS_SHARED_FIND_OF_MUTABLE_COMPOSITE_CLIENT_IMPL_HPP__
