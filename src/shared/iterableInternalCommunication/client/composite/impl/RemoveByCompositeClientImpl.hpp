//
// Created by loghin on 6/26/22.
//

#ifndef __CDS_SHARED_REMOVE_BY_COMPOSITE_CLIENT_IMPL_HPP__ // NOLINT(llvm-header-guard)
#define __CDS_SHARED_REMOVE_BY_COMPOSITE_CLIENT_IMPL_HPP__ // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
#pragma once

namespace cds {       // NOLINT(modernize-concat-nested-namespaces)
namespace __hidden {  // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
namespace __impl {    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename __Iterable, typename __Element> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <
    typename __Predicate,           // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    cds::meta::EnableIf <!cds::meta::IsMemberFunctionPointer <__Predicate, cds::meta::Decay <__Element>>::value>
> auto __RemoveByCompositeClient <__Iterable, __Element>::removeThat (
    Size                count,
    __Predicate const&  predicate
) noexcept (false) -> Size {
  // local alias for iterable Const Iterator type
  using ConstIterator     = typename __Iterable::ConstIterator;
  using __Alloc = __hidden::__impl::__allocation::__PrimitiveAlloc <ConstIterator>; // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  // allocate space to store acquired iterators into
  auto pIteratorBuffer    = __Alloc::__alloc (count);

  // variables used to store number of iterators for matching elements, number of removed elements,
  // * and current object, reinterpreted as caller class
  Size iteratorCount      = 0u;
  Size removedCount       = 0u;
  auto const pIterable    = static_cast <__Iterable*> (this);

  try {
    // parse through elements using Const Iteration, stop if reached the given limit
    for (auto iterator = pIterable->cbegin(), end = pIterable->cend(); iterator != end && iteratorCount < count; ++iterator) {
      // if the element is validated by the predicate, initialize memory of iterator
      if (predicate (*iterator)) {
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


template <typename __Iterable, typename __Element> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <
    typename __Predicate,           // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    cds::meta::EnableIf <cds::meta::IsMemberFunctionPointer <__Predicate, cds::meta::Decay <__Element>>::value>
> auto __RemoveByCompositeClient <__Iterable, __Element>::removeThat (
    Size                count,
    __Predicate const&  predicate
) noexcept (false) -> Size {
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
      // if the element is validated by the predicate, initialize memory of iterator
      if (((*iterator).*predicate)()) {
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


template <typename __Iterable, typename __Element> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <
    typename __Predicate,           // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    cds::meta::EnableIf <!cds::meta::IsMemberFunctionPointer <__Predicate, cds::meta::Decay <__Element>>::value>
> auto __RemoveByCompositeClient <__Iterable, __Element>::removeFirstThat (
    __Predicate const& predicate
) noexcept (false) -> bool {
  // store reinterpreted object as caller class
  auto const pIterable    = static_cast <__Iterable*> (this);
  // parse through elements using Const Iteration
  for (auto iterator = pIterable->cbegin(), end = pIterable->cend(); iterator != end; ++iterator) {
    // if the element is validated by the predicate, call remove primitive and return result
    if (predicate (*iterator)) {
      return static_cast <__Iterable*> (this)->remove (iterator);
    }
  }

  // iteration ended, nothing returned, no element removed
  return false;
}


template <typename __Iterable, typename __Element> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <
    typename __Predicate,           // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    cds::meta::EnableIf <cds::meta::IsMemberFunctionPointer <__Predicate, cds::meta::Decay <__Element>>::value>
> auto __RemoveByCompositeClient <__Iterable, __Element>::removeFirstThat (
    __Predicate const& predicate
) noexcept (false) -> bool {
  // store reinterpreted object as caller class
  auto const pIterable    = static_cast <__Iterable*> (this);
  // parse through elements using Const Iteration
  for (auto iterator = pIterable->cbegin(), end = pIterable->cend(); iterator != end; ++iterator) {
    // if the element is validated by the predicate, call remove primitive and return result
    if (((*iterator).*predicate)()) {
      return static_cast <__Iterable*> (this)->remove (iterator);
    }
  }

  // iteration ended, nothing returned, no element removed
  return false;
}


template <typename __Iterable, typename __Element> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <
    typename __Predicate,           // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    cds::meta::EnableIf <!cds::meta::IsMemberFunctionPointer <__Predicate, cds::meta::Decay <__Element>>::value>
> auto __RemoveByCompositeClient <__Iterable, __Element>::removeLastThat (
    __Predicate const& predicate
) noexcept (false) -> bool {
  // using the type of ConstIterator from the Iterable Type, create an iterator to remove at the end of the loop
  using ConstIterator     = typename __Iterable::ConstIterator;
  ConstIterator toRemove;
  // store reinterpreted object as caller class
  auto const pIterable    = static_cast <__Iterable*> (this);
  // parse through elements using Const Iteration
  for (auto iterator = pIterable->cbegin(), end = pIterable->cend(); iterator != end; ++iterator) {
    // if iterator element is validated, store in local iterator
    if (predicate (*iterator)) {
      toRemove = iterator;
    }
  }

  // if iterator found ( is valid ), call primitive and return result. False otherwise
  return static_cast <bool> (toRemove) && pIterable->remove (toRemove);
}


template <typename __Iterable, typename __Element> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <
    typename __Predicate,           // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    cds::meta::EnableIf <cds::meta::IsMemberFunctionPointer <__Predicate, cds::meta::Decay <__Element>>::value>
> auto __RemoveByCompositeClient <__Iterable, __Element>::removeLastThat (
    __Predicate const& predicate
) noexcept (false) -> bool {
  // using the type of ConstIterator from the Iterable Type, create an iterator to remove at the end of the loop
  using ConstIterator     = typename __Iterable::ConstIterator;
  ConstIterator toRemove;
  // store reinterpreted object as caller class
  auto const pIterable    = static_cast <__Iterable*> (this);
  // parse through elements using Const Iteration
  for (auto iterator = pIterable->cbegin(), end = pIterable->cend(); iterator != end; ++iterator) {
    // if iterator element is validated, store in local iterator
    if (((*iterator).*predicate)()) {
      toRemove = iterator;
    }
  }

  // if iterator found ( is valid ), call primitive and return result. False otherwise
  return static_cast <bool> (toRemove) && pIterable->remove (toRemove);
}


template <typename __Iterable, typename __Element> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <
    typename __Predicate,           // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    cds::meta::EnableIf <!cds::meta::IsMemberFunctionPointer <__Predicate, cds::meta::Decay <__Element>>::value>
> auto __RemoveByCompositeClient <__Iterable, __Element>::removeAllThat (
    __Predicate const& predicate
) noexcept (false) -> Size {
  // variables used to store number of iterators for matching elements, number of removed elements,
  // and current object, reinterpreted as caller class
  Size iteratorCount      = 0u;
  Size removedCount       = 0u;
  auto const pIterable    = static_cast <__Iterable*> (this);
  // local alias for iterable Const Iterator type
  using ConstIterator     = typename __Iterable::ConstIterator;
  using __Alloc           = __hidden::__impl::__allocation::__PrimitiveAlloc <ConstIterator>; // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

  // allocate space to store acquired iterators into
  auto pIteratorBuffer    = __Alloc::__alloc (pIterable->size());

  try {
    // parse through elements using Const Iteration
    for (auto iterator = pIterable->cbegin(), end = pIterable->cend (); iterator != end; ++iterator) {
      // if the element is validated by the predicate, initialize memory of iterator
      if (predicate (*iterator)) {
        new (&pIteratorBuffer [iteratorCount++] ) ConstIterator (iterator);
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


template <typename __Iterable, typename __Element> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <
    typename __Predicate,           // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    cds::meta::EnableIf <cds::meta::IsMemberFunctionPointer <__Predicate, cds::meta::Decay <__Element>>::value>
> auto __RemoveByCompositeClient <__Iterable, __Element>::removeAllThat (
    __Predicate const& predicate
) noexcept (false) -> Size {
  // variables used to store number of iterators for matching elements, number of removed elements,
  // and current object, reinterpreted as caller class
  Size iteratorCount      = 0u;
  Size removedCount       = 0u;
  auto const pIterable    = static_cast <__Iterable*> (this);
  // local alias for iterable Const Iterator type
  using ConstIterator     = typename __Iterable::ConstIterator;
  using __Alloc           = __hidden::__impl::__allocation::__PrimitiveAlloc <ConstIterator>; // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  // allocate space to store acquired iterators into
  auto pIteratorBuffer    = __Alloc::__alloc (pIterable->size());

  try {
    // parse through elements using Const Iteration
    for (auto iterator = pIterable->cbegin(), end = pIterable->cend (); iterator != end; ++iterator) {
      // if the element is validated by the predicate, initialize memory of iterator
      if (((*iterator).*predicate)()) {
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

#endif // __CDS_SHARED_REMOVE_BY_COMPOSITE_CLIENT_IMPL_HPP__
