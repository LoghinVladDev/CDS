//
// Created by loghin on 6/27/22.
//

#ifndef __CDS_SHARED_ITERATOR_FIND_STATEMENTS_IMPL_HPP__ // NOLINT(llvm-header-guard) 
#define __CDS_SHARED_ITERATOR_FIND_STATEMENTS_IMPL_HPP__ // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
#pragma once

namespace cds {       // NOLINT(modernize-concat-nested-namespaces) 
namespace __hidden {  // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
namespace __impl {    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
#ifndef _MSC_VER
template <
    typename __Iterator,                            // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    template <typename...> class __Collection,   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __Predicate,                               // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    cds::meta::EnableIf <
        !cds::meta::IsMemberFunctionPointer <
            __Predicate,
            cds::meta::Decay <decltype (*cds::meta::valueOf <__Iterator>())>
        >::value
    >
> __CDS_cpplang_ConstexprConditioned auto __findThat (      // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
    __Iterator const&           begin,
    __Iterator const&           end,
    Size                        count,
    __Collection <__Iterator>&  storeIn,
    __Predicate const&          predicate
) noexcept (false) -> __Collection <__Iterator>& {
  // parse the range until the end or until the limit has been reached 
  for (auto iterator = begin; iterator != end && count != 0u; ++iterator) {
    // if the predicate validates the current element, store the iterator 
    if (predicate (*iterator)) {
      --count;
      (void) storeIn.insert (iterator);
    }
  }

  // return reference to the received storeIn collection 
  return storeIn;
}


template <
    typename __Iterator,                                            // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __Predicate,                                               // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    cds::meta::EnableIf <
        !cds::meta::IsMemberFunctionPointer <
            __Predicate,
            cds::meta::Decay <decltype (*cds::meta::valueOf <__Iterator>())>
        >::value
    >
> __CDS_cpplang_ConstexprConditioned auto __findFirstThat ( // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    __Iterator const&   begin,
    __Iterator const&   end,
    __Predicate const&  predicate
) noexcept(false) -> __Iterator {
  // parse the range until the end 
  for (auto iterator = begin; iterator != end; ++iterator) {
    // if the predicate validates the current element, return the iterator 
    if (predicate (*iterator)) {
      return iterator;
    }
  }

  // if the range parse has ended, no element found, return end of range 
  return end;
}


template <
    typename __Iterator,                                            // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __Predicate,                                               // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    cds::meta::EnableIf <
        !cds::meta::IsMemberFunctionPointer <
            __Predicate,
            cds::meta::Decay <decltype (*cds::meta::valueOf <__Iterator>())>
        >::value
    >
> __CDS_cpplang_ConstexprConditioned auto __findLastThat (  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
    __Iterator const&   begin,
    __Iterator const&   end,
    __Predicate const&  predicate
) noexcept(false) -> __Iterator {
  // create an iterator to store the last valid element iterator. Initialize with end in case of no element found 
  auto lastFound = end;
  // parse the range to the end 
  for (auto iterator = begin; iterator != end; ++iterator) {
    // if the predicate validates the current element, store the iterator 
    if (predicate (*iterator)) {
      lastFound = iterator;
    }
  }

  // return the stored iterator 
  return lastFound;
}


template <
    typename __Iterator,                            // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    template <typename...> class __Collection,   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __Predicate,                               // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    cds::meta::EnableIf <
        !cds::meta::IsMemberFunctionPointer <
            __Predicate,
            cds::meta::Decay <decltype (*cds::meta::valueOf <__Iterator>())>
        >::value
    >
> __CDS_cpplang_ConstexprConditioned auto __findAllThat (   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
    __Iterator const&           begin,
    __Iterator const&           end,
    __Collection <__Iterator>&  storeIn,
    __Predicate const&          predicate
) noexcept(false) -> __Collection <__Iterator>& {
  // parse the range to the end
  for (auto iterator = begin; iterator != end; ++iterator) {
    // if the predicate validates the current element, store the iterator 
    if (predicate (*iterator)) {
      (void) storeIn.insert (iterator);
    }
  }

  // return reference to the received storeIn collection 
  return storeIn;
}
#else
template <
    typename __Iterator,                            // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    template <typename...> class __Collection,   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __Predicate                                // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> __CDS_cpplang_ConstexprConditioned auto __findThat (      // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    __Iterator const&           begin,
    __Iterator const&           end,
    Size                        count,
    __Collection <__Iterator>&  storeIn,
    __Predicate const&          predicate
) noexcept(false) -> __Collection <__Iterator>& {
  // parse the range until the end or until the limit has been reached
  for (auto iterator = begin; iterator != end && count != 0u; ++iterator) {
    // if the predicate validates the current element, store the iterator
    if (predicate (*iterator)) {
      --count;
      (void) storeIn.insert (iterator);
    }
  }

  // return reference to the received storeIn collection
  return storeIn;
}


template <
    typename __Iterator,                            // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __Predicate                                // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> __CDS_cpplang_ConstexprConditioned auto __findFirstThat ( // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    __Iterator const&   begin,
    __Iterator const&   end,
    __Predicate const&  predicate
) noexcept(false) -> __Iterator {
  // parse the range until the end
  for (auto iterator = begin; iterator != end; ++iterator) {
    // if the predicate validates the current element, return the iterator
    if (predicate (*iterator)) {
      return iterator;
    }
  }

  // if the range parse has ended, no element found, return end of range
  return end;
}


template <
    typename __Iterator,                            // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __Predicate                                // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> __CDS_cpplang_ConstexprConditioned auto __findLastThat (  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    __Iterator const&   begin,
    __Iterator const&   end,
    __Predicate const&  predicate
) noexcept(false) -> __Iterator {
  // create an iterator to store the last valid element iterator. Initialize with end in case of no element found
  auto lastFound = end;
  // parse the range to the end
  for (auto iterator = begin; iterator != end; ++iterator) {
    // if the predicate validates the current element, store the iterator
    if (predicate (*iterator)) {
      lastFound = iterator;
    }
  }

  // return the stored iterator
  return lastFound;
}


template <
    typename __Iterator,                            // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    template <typename...> class __Collection,   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __Predicate                                // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> __CDS_cpplang_ConstexprConditioned auto __findAllThat (   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    __Iterator const&           begin,
    __Iterator const&           end,
    __Collection <__Iterator>&  storeIn,
    __Predicate const&          predicate
) noexcept(false) -> __Collection <__Iterator>& {
  // parse the range to the end
  for (auto iterator = begin; iterator != end; ++iterator) {
    // if the predicate validates the current element, store the iterator
    if (predicate (*iterator)) {
      (void) storeIn.insert (iterator);
    }
  }

  // return reference to the received storeIn collection
  return storeIn;
}
#endif
} // namespace __impl 
} // namespace __hidden 
} // namespace cds 

#endif // __CDS_SHARED_ITERATOR_FIND_STATEMENTS_IMPL_HPP__ 
