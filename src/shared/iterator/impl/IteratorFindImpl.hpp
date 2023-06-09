//
// Created by loghin on 6/27/22.
//

#ifndef __CDS_SHARED_ITERATOR_FIND_IMPL_HPP__ // NOLINT(llvm-header-guard) 
#define __CDS_SHARED_ITERATOR_FIND_IMPL_HPP__ // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 

namespace cds {       // NOLINT(modernize-concat-nested-namespaces) 
namespace __hidden {  // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
namespace __impl {    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <
    typename                                                            __Element,          // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __Iterator,         // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __Iterable,         // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    template <typename...> class                                        __Collection,       // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__Iterable const&, __Element const&> __containsFunction  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> __CDS_cpplang_ConstexprConditioned auto __findOf (                                // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
    __Iterator const&           begin,
    __Iterator const&           end,
    Size                        count,
    __Collection <__Iterator>&  storeIn,
    __Iterable const&           from
) noexcept(false) -> __Collection <__Iterator>& {
  // parse the range until the end, or until the given limit is reached 
  for (auto iterator = begin; iterator != end && count != 0u; ++iterator) {
    // if element at iterator is also found in given 'from' iterable 
    if (__containsFunction (from, *iterator)) {
      // decrease the limit and store the iterator 
      --count;
      (void) storeIn.insert (iterator);
    }
  }

  // return reference to updated collection 
  return storeIn;
}


template <
    bool                                                                __exceptSpec,       // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __Element,          // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __Iterator,         // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __Iterable,         // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__Iterable const&, __Element const&> __containsFunction  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> __CDS_cpplang_ConstexprConditioned auto __findFirstOf (                           // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
    __Iterator const& begin,
    __Iterator const& end,
    __Iterable const& from
) noexcept(__exceptSpec) -> __Iterator {
  // parse the range 
  for (auto iterator = begin; iterator != end; ++iterator) {
    // if element at iterator is also found in given 'from' iterable 
    if (__containsFunction (from, *iterator)) {
      // return the iterator 
      return iterator;
    }
  }

  // otherwise, no iterator with element located in given iterable, return 'end' 
  return end;
}


template <
    bool                                                                __exceptSpec,       // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __Element,          // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __Iterator,         // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __Iterable,         // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__Iterable const&, __Element const&> __containsFunction  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> __CDS_cpplang_ConstexprConditioned auto __findLastOf (                                                        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
    __Iterator const& begin,
    __Iterator const& end,
    __Iterable const& from
) noexcept -> __Iterator {
  // create a local iterator to return the last match into. Initialize with 'end' in case of none found
  auto lastFound = end;
  // parse the range 
  for (auto iterator = begin; iterator != end; ++iterator) {
    // if element at iterator is also found in given 'from' iterable 
    if (__containsFunction (from, *iterator)) {
      // store the iterator locally 
      lastFound = iterator;
    }
  }

  // return the last match 
  return lastFound;
}


template <
    typename                                                            __Element,          // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __Iterator,         // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __Iterable,         // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    template <typename...> class                                        __Collection,       // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__Iterable const&, __Element const&> __containsFunction  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> __CDS_cpplang_ConstexprConditioned auto __findAllOf (                                                         // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
    __Iterator const&           begin,
    __Iterator const&           end,
    __Collection <__Iterator>&  storeIn,
    __Iterable const&           from
) noexcept(false) -> __Collection <__Iterator>& {
  // parse the range 
  for (auto iterator = begin; iterator != end; ++iterator) {
    // if element at iterator is also found in given 'from' iterable 
    if (__containsFunction (from, *iterator)) {
      // store the iterator 
      (void) storeIn.insert (iterator);
    }
  }

  // return reference to updated collection 
  return storeIn;
}
} // namespace __impl 
} // namespace __hidden 
} // namespace cds 

#endif // __CDS_SHARED_ITERATOR_FIND_IMPL_HPP__ 
