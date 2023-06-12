//
// Created by loghin on 6/30/22.
//

#ifndef __CDS_SHARED_INDICES_OF_COMPOSITE_CLIENT_IMPL_HPP__ // NOLINT(llvm-header-guard) 
#define __CDS_SHARED_INDICES_OF_COMPOSITE_CLIENT_IMPL_HPP__ // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
#pragma once

namespace cds {       // NOLINT(modernize-concat-nested-namespaces)
namespace __hidden {  // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
namespace __impl {    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <
    typename                                                                  __Receiver,           // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                                  __Element,            // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                                  __FromCollection,     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__FromCollection const&, __Element const&> __contains,           // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    bool                                                                      __exceptCond          // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> template <typename __Collection> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
auto __IndicesOfCompositeClient <__Receiver, __Element, __FromCollection, __contains, __exceptCond>::indicesOfFrom (
    Size                    count,
    __Collection&           storeIn,
    __FromCollection const& from
) const noexcept(false) -> __Collection& {
  auto const* pIterable = static_cast <__Receiver const*> (this);
  Size  foundCount = 0u;
  Index index      = 0;
  for (auto iterator = pIterable->cbegin(), end = pIterable->cend(); iterator != end && foundCount < count; ++iterator, ++index) {
    if (__contains (from, *iterator)) {
      (void) storeIn.insert (index);
      ++foundCount;
    }
  }

  return storeIn;
}


template <
    typename                                                                  __Receiver,           // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                                  __Element,            // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                                  __FromCollection,     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__FromCollection const&, __Element const&> __contains,           // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    bool                                                                      __exceptCond          // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> template <template <typename...> class __Collection> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
__CDS_OptimalInline auto __IndicesOfCompositeClient <__Receiver, __Element, __FromCollection, __contains, __exceptCond>::indicesOfFrom (
    Size                    count,
    __FromCollection const& from
) const noexcept(false) -> __Collection <Index> {
  __Collection <Index> indices;
  return std::move (indicesOfFrom (count, indices, from));
}


template <
    typename                                                                  __Receiver,           // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                                  __Element,            // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                                  __FromCollection,     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__FromCollection const&, __Element const&> __contains,           // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    bool                                                                      __exceptCond          // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> auto __IndicesOfCompositeClient <__Receiver, __Element, __FromCollection, __contains, __exceptCond>::firstIndexOfFrom (
    __FromCollection const& from
) const noexcept(itNoexcept) -> Index {
  auto const* pIterable = static_cast <__Receiver const*> (this);
  Index index = 0;
  for (auto iterator = pIterable->cbegin(), end = pIterable->cend(); iterator != end; ++iterator, ++index) {
    if (__contains (from, *iterator)) {
      return index;
    }
  }

  return __Receiver::invalidIndex;
}


template <
    typename                                                                  __Receiver,           // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                                  __Element,            // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                                  __FromCollection,     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__FromCollection const&, __Element const&> __contains,           // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    bool                                                                      __exceptCond          // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> auto __IndicesOfCompositeClient <__Receiver, __Element, __FromCollection, __contains, __exceptCond>::lastIndexOfFrom (
    __FromCollection const& from
) const noexcept(itNoexcept) -> Index {
  auto const* pIterable = static_cast <__Receiver const*> (this);
  Index index = static_cast <Index> (pIterable->size()) - 1;
  for (auto iterator = pIterable->crbegin(), end = pIterable->crend(); iterator != end; ++iterator, --index) {
    if (__contains (from, *iterator)) {
      return index;
    }
  }

  return __Receiver::invalidIndex;
}


template <
    typename                                                                  __Receiver,           // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                                  __Element,            // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                                  __FromCollection,     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__FromCollection const&, __Element const&> __contains,           // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    bool                                                                      __exceptCond          // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> template <typename __Collection> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
auto __IndicesOfCompositeClient <__Receiver, __Element, __FromCollection, __contains, __exceptCond>::allIndicesOfFrom (
    __Collection&           storeIn,
    __FromCollection const& from
) const noexcept(false) -> __Collection& {
  auto const* pIterable = static_cast <__Receiver const*> (this);
  Size  foundCount = 0u;
  Index index      = 0;
  for (auto iterator = pIterable->cbegin(), end = pIterable->cend(); iterator != end; ++iterator, ++index) {
    if (__contains (from, *iterator)) {
      (void) storeIn.insert (index);
      ++foundCount;
    }
  }

  return storeIn;
}


template <
    typename                                                                  __Receiver,           // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                                  __Element,            // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                                  __FromCollection,     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__FromCollection const&, __Element const&> __contains,           // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    bool                                                                      __exceptCond          // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> template <template <typename...> class __Collection> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
__CDS_OptimalInline auto __IndicesOfCompositeClient <__Receiver, __Element, __FromCollection, __contains, __exceptCond>::allIndicesOfFrom (
    __FromCollection const& from
) const noexcept(false) -> __Collection <Index> {
  __Collection <Index> indices;
  return std::move (allIndicesOfFrom (indices, from));
}


template <
    typename                                                                  __Receiver,           // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                                  __Element,            // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                                  __FromCollection,     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__FromCollection const&, __Element const&> __contains,           // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    bool                                                                      __exceptCond          // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> template <typename __Collection> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
auto __IndicesOfCompositeClient <__Receiver, __Element, __FromCollection, __contains, __exceptCond>::indicesOfNotFrom (
    Size                    count,
    __Collection&           storeIn,
    __FromCollection const& from
) const noexcept(false) -> __Collection& {
  auto const* pIterable = static_cast <__Receiver const*> (this);
  Size  foundCount = 0u;
  Index index      = 0;
  for (auto iterator = pIterable->cbegin(), end = pIterable->cend(); iterator != end && foundCount < count; ++iterator, ++index) {
    if (!__contains (from, *iterator)) {
      (void) storeIn.insert (index);
      ++foundCount;
    }
  }

  return storeIn;
}


template <
    typename                                                                  __Receiver,           // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                                  __Element,            // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                                  __FromCollection,     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__FromCollection const&, __Element const&> __contains,           // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    bool                                                                      __exceptCond          // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> template <template <typename...> class __Collection> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
__CDS_OptimalInline auto __IndicesOfCompositeClient <__Receiver, __Element, __FromCollection, __contains, __exceptCond>::indicesOfNotFrom (
    Size                    count,
    __FromCollection const& from
) const noexcept(false) -> __Collection <Index> {
  __Collection <Index> indices;
  return std::move (indicesOfNotFrom (count, indices, from));
}


template <
    typename                                                                  __Receiver,           // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                                  __Element,            // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                                  __FromCollection,     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__FromCollection const&, __Element const&> __contains,           // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    bool                                                                      __exceptCond          // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> auto __IndicesOfCompositeClient <__Receiver, __Element, __FromCollection, __contains, __exceptCond>::firstIndexOfNotFrom (
    __FromCollection const& from
) const noexcept(itNoexcept) -> Index {
  auto const* pIterable = static_cast <__Receiver const*> (this);
  Index index = 0;
  for (auto iterator = pIterable->cbegin(), end = pIterable->cend(); iterator != end; ++iterator, ++index) {
    if (!__contains (from, *iterator)) {
      return index;
    }
  }

  return __Receiver::invalidIndex;
}


template <
    typename                                                                  __Receiver,           // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                                  __Element,            // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                                  __FromCollection,     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__FromCollection const&, __Element const&> __contains,           // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    bool                                                                      __exceptCond          // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> auto __IndicesOfCompositeClient <__Receiver, __Element, __FromCollection, __contains, __exceptCond>::lastIndexOfNotFrom (
    __FromCollection const& from
) const noexcept(itNoexcept) -> Index {
  auto const* pIterable = static_cast <__Receiver const*> (this);
  Index index = static_cast <Index> (pIterable->size()) - 1;
  for (auto iterator = pIterable->crbegin(), end = pIterable->crend(); iterator != end; ++iterator, --index) {
    if (!__contains (from, *iterator)) {
      return index;
    }
  }

  return __Receiver::invalidIndex;
}

template <
    typename                                                                  __Receiver,           // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                                  __Element,            // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                                  __FromCollection,     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__FromCollection const&, __Element const&> __contains,           // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    bool                                                                      __exceptCond          // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> template <typename __Collection> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
auto __IndicesOfCompositeClient <__Receiver, __Element, __FromCollection, __contains, __exceptCond>::allIndicesOfNotFrom (
    __Collection&           storeIn,
    __FromCollection const& from
) const noexcept(false) -> __Collection& {
  auto const* pIterable = static_cast <__Receiver const*> (this);
  Size  foundCount = 0u;
  Index index      = 0;
  for (auto iterator = pIterable->cbegin(), end = pIterable->cend(); iterator != end; ++iterator, ++index) {
    if (!__contains (from, *iterator)) {
      (void) storeIn.insert (index);
      ++foundCount;
    }
  }

  return storeIn;
}


template <
    typename                                                                  __Receiver,           // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                                  __Element,            // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                                  __FromCollection,     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__FromCollection const&, __Element const&> __contains,           // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    bool                                                                      __exceptCond          // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> template <template <typename...> class __Collection> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
__CDS_OptimalInline auto __IndicesOfCompositeClient <__Receiver, __Element, __FromCollection, __contains, __exceptCond>::allIndicesOfNotFrom (
    __FromCollection const& from
) const noexcept(false) -> __Collection <Index> {
  __Collection <Index> indices;
  return std::move (allIndicesOfNotFrom (indices, from));
}
} // namespace __impl 
} // namespace __hidden 
} // namespace cds 

#endif // __CDS_SHARED_INDICES_OF_COMPOSITE_CLIENT_IMPL_HPP__ 
