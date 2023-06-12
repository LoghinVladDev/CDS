//
// Created by loghin on 6/26/22.
//

#ifndef __CDS_SHARED_REMOVE_OF_COMPOSITE_CLIENT_IMPL_HPP__ // NOLINT(llvm-header-guard)
#define __CDS_SHARED_REMOVE_OF_COMPOSITE_CLIENT_IMPL_HPP__ // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
#pragma once

namespace cds {       // NOLINT(modernize-concat-nested-namespaces)
namespace __hidden {  // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
namespace __impl {    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <
    typename                                                                __Iterable,         // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                                __Element,          // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                                __FromIterable,     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__FromIterable const&, __Element const&> __containsFunction  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> __CDS_OptimalInline auto __RemoveOfCompositeClient <__Iterable, __Element, __FromIterable, __containsFunction>::__iro_selfReferentialCase_removeOf (
    Size                  count,
    __FromIterable const& from
) noexcept(false) -> Size {
  // ignore given collection, same as this
  (void) from;
  // store iterable, reinterpreted this and current size
  auto const pIterable    = static_cast <__Iterable*> (this);
  auto const size         = pIterable->size();
  // if count greater or equal to number of elements, only clear
  if (count >= size) {
    pIterable->clear();
    return size;
  }

  // if none requested, remove none
  if (count == 0u) {
    return 0u;
  }

  // if one requested, remove first
  if (count == 1u) {
    return pIterable->remove (pIterable->cbegin()) ? 1u : 0u;
  }

  // otherwise, prepare an array with first 'count' iterators
  using ConstIterator     = typename __Iterable::ConstIterator;
  using __Alloc           = __hidden::__impl::__allocation::__PrimitiveAlloc <ConstIterator>; // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  auto pIteratorBuffer    = __Alloc::__alloc (count);
  Size iteratorCount      = 0u;

  try {
    for (auto iterator = pIterable->cbegin(), end = pIterable->cend(); iterator != end && iteratorCount < count; ++iterator) {
      new (&pIteratorBuffer [iteratorCount++]) ConstIterator (iterator);
    }

    // remove said elements
    auto removedCount = pIterable->removeAll (&pIteratorBuffer [0], iteratorCount);

    // destroy stored iterators
    for (Size index = 0u; index < iteratorCount; ++index) {
      pIteratorBuffer [index].~ConstIterator ();
    }

    // free iterator space and return removed element count
    __Alloc::__free (pIteratorBuffer);
    return removedCount;
  } catch (...) {
    __Alloc::__free (pIteratorBuffer);
    throw;
  }
}


template <
    typename                                                                __Iterable,     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                                __Element,      // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                                __FromIterable, // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__FromIterable const&, __Element const&> __containsFunction  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> __CDS_OptimalInline auto __RemoveOfCompositeClient <__Iterable, __Element, __FromIterable, __containsFunction>::__iro_selfReferentialCase_removeFirstOf (
    __FromIterable const& from
) noexcept(false) -> bool {
  // ignore given collection, same as this
  (void) from;
  // reinterpret iterble
  auto const pIterable = static_cast <__Iterable*> (this);
  // remove first element of this iterable
  return pIterable->remove (pIterable->cbegin());
}


template <
    typename                                                                __Iterable,     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                                __Element,      // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                                __FromIterable, // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__FromIterable const&, __Element const&> __containsFunction  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> __CDS_OptimalInline auto __RemoveOfCompositeClient <__Iterable, __Element, __FromIterable, __containsFunction>::__iro_selfReferentialCase_removeLastOf (
    __FromIterable const& from
) noexcept(false) -> bool {
  // ignore given collection, same as this
  (void) from;
  // reinterpret iterable
  auto  const pIterable   = static_cast <__Iterable*> (this);
  // create iterator and store end to seek the last element
  auto        iterator    = pIterable->cbegin();
  auto        end         = pIterable->end();
  // iterator created to store last element iterator
  decltype (iterator) toRemove;

  // seek last element
  while (iterator != end) {
    // always store current iterator, as in the end, it will be the final one
    toRemove = iterator;
    ++iterator;
  }

  // if iterator found, remove iterator and return removal status
  return static_cast <bool> (toRemove) && static_cast <__Iterable*> (this)->remove (toRemove);
}


template <
    typename                                                                __Iterable,     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                                __Element,      // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                                __FromIterable, // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__FromIterable const&, __Element const&> __containsFunction  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> __CDS_OptimalInline auto __RemoveOfCompositeClient <__Iterable, __Element, __FromIterable, __containsFunction>::__iro_selfReferentialCase_removeAllOf (
    __FromIterable const& from
) noexcept(false) -> Size {
  // ignore given collection, same as this
  (void) from;
  // reinterpret iterable
  auto const pIterable    = static_cast <__Iterable*> (this);
  // acquire size before clear
  auto const size         = pIterable->size();
  // clear iterable
  pIterable->clear();
  // return size prior to clearing
  return size;
}

template <
    typename                                                                __Iterable,     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                                __Element,      // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                                __FromIterable, // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__FromIterable const&, __Element const&> __containsFunction  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> __CDS_OptimalInline auto __RemoveOfCompositeClient <__Iterable, __Element, __FromIterable, __containsFunction>::__iro_selfReferentialCase_removeNotOf (
    Size                  count,
    __FromIterable const& from
) noexcept(false) -> Size {
  // ignore given collection, same as this. Ignore count as well
  (void) count;
  (void) from;
  // this->removeNotOf (this) will do nothing.
  return 0u;
}


template <
    typename                                                                __Iterable,     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                                __Element,      // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                                __FromIterable, // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__FromIterable const&, __Element const&> __containsFunction  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> __CDS_OptimalInline auto __RemoveOfCompositeClient <__Iterable, __Element, __FromIterable, __containsFunction>::__iro_selfReferentialCase_removeFirstNotOf (
    __FromIterable const& from
) noexcept(false) -> bool {
  // ignore given collection, same as this
  (void) from;
  // this->removeFirstNotOf (this) does nothing
  return false;
}


template <
    typename                                                                __Iterable,     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                                __Element,      // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                                __FromIterable, // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__FromIterable const&, __Element const&> __containsFunction  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> __CDS_OptimalInline auto __RemoveOfCompositeClient <__Iterable, __Element, __FromIterable, __containsFunction>::__iro_selfReferentialCase_removeLastNotOf (
    __FromIterable const& from
) noexcept(false) -> bool {
  // ignore given collection, same as this
  (void) from;
  // this->removeLastNotOf (this) does nothing
  return false;
}


template <
    typename                                                                __Iterable,     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                                __Element,      // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                                __FromIterable, // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__FromIterable const&, __Element const&> __containsFunction  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> __CDS_OptimalInline auto __RemoveOfCompositeClient <__Iterable, __Element, __FromIterable, __containsFunction>::__iro_selfReferentialCase_removeAllNotOf (
    __FromIterable const& from
) noexcept(false) -> Size {
  // ignore given collection, same as this
  (void) from;
  // this->removeAllNotOf (this) does nothing
  return 0u;
}


template <
    typename                                                                __Iterable,     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                                __Element,      // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                                __FromIterable, // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__FromIterable const&, __Element const&> __containsFunction  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> auto __RemoveOfCompositeClient <__Iterable, __Element, __FromIterable, __containsFunction>::removeOf (
    Size                  count,
    __FromIterable const& from
) noexcept(false) -> Size {
  // treat the possible case when 'from' is actually 'this'
  if (static_cast <void const*> (this) == static_cast <void const*> (&from)) {
    return this->__iro_selfReferentialCase_removeOf (count, from);
  }

  // local alias for iterable Const Iterator type
  using ConstIterator     = typename __Iterable::ConstIterator;
  using __Alloc           = __hidden::__impl::__allocation::__PrimitiveAlloc <ConstIterator>; // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  // allocate space to store acquired iterators into
  auto pIteratorBuffer    = __Alloc::__alloc (count);

  // variables used to store number of iterators for matching elements, number of removed elements,
  // and current object, reinterpreted as caller class
  Size iteratorCount      = 0u;
  Size removedCount       = 0u;
  auto const pIterable    = static_cast <__Iterable*> (this);

  try {
    // parse through elements using Const Iteration, stop if reached the given limit
    for (auto iterator = pIterable->cbegin(), end = pIterable->cend(); iterator != end && iteratorCount < count; ++iterator) {
      // if the element is found in the given 'from' iterable, initialize memory of iterator
      if (__containsFunction (from, *iterator)) {
        new (&pIteratorBuffer [iteratorCount++]) ConstIterator (iterator);
      }
    }

    if (iteratorCount >= 2u) {
      // if more or two elements found, use removeAll
      removedCount = pIterable->removeAll (&pIteratorBuffer [0u], iteratorCount);
    } else if (iteratorCount == 1u) {
      // if only one found, use remove
      removedCount = pIterable->remove (pIteratorBuffer [0u]) ? 1u : 0u;
    }
    // if none found, do nothing

    // destroy stored iterators
    for (Size index = 0u; index < iteratorCount; ++index) {
      pIteratorBuffer [index].~ConstIterator ();
    }

    // free the iterator memory and return number of removed elements
    __Alloc::__free (pIteratorBuffer);
    return removedCount;
  } catch (...) {
    __Alloc::__free (pIteratorBuffer);
    throw;
  }
}


template <
    typename                                                                __Iterable,     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                                __Element,      // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                                __FromIterable, // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__FromIterable const&, __Element const&> __containsFunction  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> auto __RemoveOfCompositeClient <__Iterable, __Element, __FromIterable, __containsFunction>::removeFirstOf (
    __FromIterable const& from
) noexcept(false) -> bool {
  // treat the possible case when 'from' is actually 'this'
  if (static_cast <void const*> (this) == static_cast <void const*> (&from)) {
    return this->__iro_selfReferentialCase_removeFirstOf (from);
  }

  // store reinterpreted object as caller class
  auto const pIterable = static_cast <__Iterable*> (this);
  // parse through elements using Const Iteration
  for (auto iterator = pIterable->cbegin(), end = pIterable->cend(); iterator != end; ++iterator) {
    // if the element is found in the given 'from' iterable, call remove primitive and return result
    if (__containsFunction (from, *iterator)) {
      return pIterable->remove (iterator);
    }
  }

  // iteration ended, nothing returned, no element removed
  return false;
}


template <
    typename                                                                __Iterable,     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                                __Element,      // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                                __FromIterable, // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__FromIterable const&, __Element const&> __containsFunction  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> auto __RemoveOfCompositeClient <__Iterable, __Element, __FromIterable, __containsFunction>::removeLastOf (
    __FromIterable const& from
) noexcept(false) -> bool {
  // treat the possible case when 'from' is actually 'this'
  if (static_cast <void const*> (this) == static_cast <void const*> (&from)) {
    return this->__iro_selfReferentialCase_removeLastOf (from);
  }

  // store reinterpreted object as caller class
  auto const pIterable = static_cast <__Iterable*> (this);
  // using the type of ConstIterator from the Iterable Type, create an iterator to remove at the end of the loop
  using ConstIterator = typename __Iterable::ConstIterator;
  ConstIterator toRemove;

  // parse through elements using Const Iteration
  for (auto iterator = pIterable->cbegin(), end = pIterable->cend(); iterator != end; ++iterator) {
    // if the element is found in the given 'from' iterable, store in local iterator
    if (__containsFunction (from, *iterator)) {
      toRemove = iterator;
    }
  }

  // if iterator found ( is valid ), call primitive and return result. False otherwise
  return static_cast <bool> (toRemove) && pIterable->remove (toRemove);
}


template <
    typename                                                                __Iterable,     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                                __Element,      // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                                __FromIterable, // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__FromIterable const&, __Element const&> __containsFunction  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> auto __RemoveOfCompositeClient <__Iterable, __Element, __FromIterable, __containsFunction>::removeAllOf (
    __FromIterable const& from
) noexcept(false) -> Size {
  // treat the possible case when 'from' is actually 'this'
  if (static_cast <void const*> (this) == static_cast <void const*> (&from)) {
    return this->__iro_selfReferentialCase_removeAllOf (from);
  }

  // variables used to store number of iterators for matching elements, number of removed elements,
  // and current object, reinterpreted as caller class
  auto const pIterable    = static_cast <__Iterable*> (this);
  Size iteratorCount      = 0u;
  Size removedCount       = 0u;
  // local alias for iterable Const Iterator type
  using ConstIterator     = typename __Iterable::ConstIterator;
  using __Alloc           = __hidden::__impl::__allocation::__PrimitiveAlloc <ConstIterator>; // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  // allocate space to store acquired iterators into
  auto pIteratorBuffer    = __Alloc::__alloc (pIterable->size());

  try {
    // parse through elements using Const Iteration
    for (auto iterator = pIterable->cbegin(), end = pIterable->cend(); iterator != end; ++iterator) {
      // if the element is found in the given 'from' iterable, initialize memory of iterator
      if (__containsFunction (from, *iterator)) {
        new (&pIteratorBuffer [iteratorCount++]) ConstIterator (iterator);
      }
    }

    if (iteratorCount >= 2u) {
      // if more or two elements found, use removeAll
      removedCount = pIterable->removeAll (&pIteratorBuffer [0U], iteratorCount);
    } else if (iteratorCount == 1u) {
      // if only one found, use remove
      removedCount = pIterable->remove (pIteratorBuffer [0U]) ? 1u : 0u;
    }
    // if none found, do nothing

    // destroy stored iterators
    for (Size index = 0u; index < iteratorCount; ++index) {
      pIteratorBuffer [index].~ConstIterator();
    }

    // free the iterator memory and return number of removed elements
    __Alloc::__free (pIteratorBuffer);
    return removedCount;
  } catch (...) {
    __Alloc::__free (pIteratorBuffer);
    throw;
  }
}


template <
    typename                                                                __Iterable,     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                                __Element,      // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                                __FromIterable, // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__FromIterable const&, __Element const&> __containsFunction  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> auto __RemoveOfCompositeClient <__Iterable, __Element, __FromIterable, __containsFunction>::removeNotOf (
    Size                  count,
    __FromIterable const& from
) noexcept(false) -> Size {
  // treat the possible case when 'from' is actually 'this'
  if (static_cast <void const*> (this) == static_cast <void const*> (&from)) {
    return this->__iro_selfReferentialCase_removeNotOf (count, from);
  }

  // local alias for iterable Const Iterator type
  using ConstIterator     = typename __Iterable::ConstIterator;
  using __Alloc           = __hidden::__impl::__allocation::__PrimitiveAlloc <ConstIterator>; // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  // allocate space to store acquired iterators into
  auto pIteratorBuffer    = __Alloc::__alloc (count);
  // variables used to store number of iterators for matching elements, number of removed elements,
  // and current object, reinterpreted as caller class
  Size iteratorCount      = 0u;
  Size removedCount       = 0u;
  auto const pIterable    = static_cast <__Iterable*> (this);

  try {
    // parse through elements using Const Iteration, stop if reached the given limit
    for (auto iterator = pIterable->cbegin(), end = pIterable->cend(); iterator != end && iteratorCount < count; ++iterator) {
      // if the element is not found in the given 'from' iterable, initialize memory of iterator
      if (!__containsFunction (from, *iterator)) {
        new (&pIteratorBuffer [iteratorCount++]) ConstIterator (iterator);
      }
    }

    if (iteratorCount >= 2u) {
      // if more or two elements found, use removeAll
      removedCount = pIterable->removeAll (&pIteratorBuffer [0U], iteratorCount);
    } else if (iteratorCount == 1u) {
      // if only one found, use remove
      removedCount = pIterable->remove (pIteratorBuffer [0U]) ? 1u : 0u;
    }
    // if none found, do nothing

    // destroy stored iterators
    for (Size index = 0u; index < iteratorCount; ++index) {
      pIteratorBuffer [index].~ConstIterator();
    }

    // free the iterator memory and return number of removed elements
    __Alloc::__free (pIteratorBuffer);
    return removedCount;
  } catch (...) {
    __Alloc::__free (pIteratorBuffer);
    throw;
  }
}


template <
    typename                                                                __Iterable,     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                                __Element,      // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                                __FromIterable, // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__FromIterable const&, __Element const&> __containsFunction  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> auto __RemoveOfCompositeClient <__Iterable, __Element, __FromIterable, __containsFunction>::removeFirstNotOf (
    __FromIterable const& from
) noexcept(false) -> bool {
  // treat the possible case when 'from' is actually 'this'
  if (static_cast <void const*> (this) == static_cast <void const*> (&from)) {
    return this->__iro_selfReferentialCase_removeFirstNotOf (from);
  }

  // store reinterpreted object as caller class
  auto const pIterable = static_cast <__Iterable*> (this);
  // parse through elements using Const Iteration
  for (auto iterator = pIterable->cbegin(), end = pIterable->cend(); iterator != end; ++iterator) {
    // if the element is not found in the given 'from' iterable, call remove primitive and return result
    if (!__containsFunction (from, *iterator)) {
      return pIterable->remove (iterator);
    }
  }

  // iteration ended, nothing returned, no element removed
  return false;
}


template <
    typename                                                                __Iterable,     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                                __Element,      // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                                __FromIterable, // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__FromIterable const&, __Element const&> __containsFunction  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> auto __RemoveOfCompositeClient <__Iterable, __Element, __FromIterable, __containsFunction>::removeLastNotOf (
    __FromIterable const& from
) noexcept(false) -> bool {
  // treat the possible case when 'from' is actually 'this'
  if (static_cast <void const*> (this) == static_cast <void const*> (&from)) {
    return this->__iro_selfReferentialCase_removeLastNotOf (from);
  }

  // store reinterpreted object as caller class
  auto const pIterable = static_cast <__Iterable*> (this);
  // using the type of ConstIterator from the Iterable Type, create an iterator to remove at the end of the loop
  using ConstIterator = typename __Iterable::ConstIterator;
  ConstIterator toRemove;

  // parse through elements using Const Iteration
  for (auto iterator = pIterable->cbegin(), end = pIterable->cend(); iterator != end; ++iterator) {
    // if the element is not found in the given 'from' iterable, store in local iterator
    if (!__containsFunction (from, *iterator)) {
      toRemove = iterator;
    }
  }

  // if iterator found ( is valid ), call primitive and return result. False otherwise
  return static_cast <bool> (toRemove) && pIterable->remove (toRemove);
}


template <
    typename                                                                __Iterable,     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                                __Element,      // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                                __FromIterable, // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__FromIterable const&, __Element const&> __containsFunction  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> auto __RemoveOfCompositeClient <__Iterable, __Element, __FromIterable, __containsFunction>::removeAllNotOf (
    __FromIterable const& from
) noexcept(false) -> Size {
  // treat the possible case when 'from' is actually 'this'
  if (static_cast <void const*> (this) == static_cast <void const*> (&from)) {
    return this->__iro_selfReferentialCase_removeAllNotOf (from);
  }

  // variables used to store number of iterators for matching elements, number of removed elements,
  // and current object, reinterpreted as caller class
  auto const pIterable    = static_cast <__Iterable*> (this);
  Size iteratorCount      = 0u;
  Size removedCount       = 0u;
  // local alias for iterable Const Iterator type
  using ConstIterator     = typename __Iterable::ConstIterator;
  using __Alloc           = __hidden::__impl::__allocation::__PrimitiveAlloc <ConstIterator>; // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  // allocate space to store acquired iterators into
  auto pIteratorBuffer    = __Alloc::__alloc (pIterable->size());

  try {
    // parse through elements using Const Iteration
    for (auto iterator = pIterable->cbegin(), end = pIterable->cend(); iterator != end; ++iterator) {
      // if the element is not found in the given 'from' iterable, initialize memory of iterator
      if (!__containsFunction (from, *iterator)) {
        new (&pIteratorBuffer [iteratorCount++]) ConstIterator (iterator);
      }
    }

    if (iteratorCount >= 2u) {
      // if more or two elements found, use removeAll
      removedCount = pIterable->removeAll (&pIteratorBuffer [0U], iteratorCount);
    } else if (iteratorCount == 1u) {
      // if only one found, use remove
      removedCount = pIterable->remove (pIteratorBuffer [0U]) ? 1u : 0u;
    }
    // if none found, do nothing

    // destroy stored iterators
    for (Size index = 0u; index < iteratorCount; ++index) {
      pIteratorBuffer [index].~ConstIterator();
    }

    // free the iterator memory and return number of removed elements
    __Alloc::__free (pIteratorBuffer);
    return removedCount;
  } catch (...) {
    __Alloc::__free (pIteratorBuffer);
    throw;
  }
}
} // namespace __impl
} // namespace __hidden
} // namespace cds

#endif // __CDS_SHARED_REMOVE_OF_COMPOSITE_CLIENT_IMPL_HPP__
