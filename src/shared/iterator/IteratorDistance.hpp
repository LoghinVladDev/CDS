//
// Created by loghin on 6/29/22.
//

#ifndef __CDS_SHARED_ITERATOR_DISTANCE_HPP__ // NOLINT(llvm-header-guard)
#define __CDS_SHARED_ITERATOR_DISTANCE_HPP__ // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
#pragma once

namespace cds {       // NOLINT(modernize-concat-nested-namespaces)
namespace __hidden {  // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
namespace __impl {    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
/// \struct Auxiliary structure used to compute the distance between two iterators, when the iterator type does not allow for distance computation
/// \tparam __Iterator is the type of iterator
///
/// \test: Not Applicable.
/// \namespace cds::__hidden::__impl
/// \internal library-private
template <typename __Iterator, typename = void> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
struct __IteratorDistance {                     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  /// \brief Function used to compute the distance between two iterators
  /// \param [in] begin : __Iterator cref = Constant Reference to the iterator at the start of the range
  /// \param [in] end : __Iterator cref = Constant Reference to the iterator at the end of the range
  /// \exceptsafe
  /// \return Size = distance between the iterators
  ///
  /// \test: Not Applicable.
  /// \public
  static inline auto __compute (__Iterator const& begin, __Iterator const& end) noexcept -> Size {  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    // compute the distance via iteration
    Size distance = 0u;
    for (auto iterator = begin; iterator != end; ++iterator) {
      ++distance;
    }
    // return the distance
    return distance;
  }
};


/// \struct Auxiliary structure used to compute the distance between two iterators, when the iterator type allows distance computation
/// \tparam __Iterator is the type of iterator
///
/// \test: Not Applicable.
///
/// \namespace cds::__hidden::__impl
/// \internal library-private
template <typename __Iterator>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
struct __IteratorDistance <     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    __Iterator,
    cds::meta::Void <decltype (cds::meta::valueOf <__Iterator>() - cds::meta::valueOf <__Iterator>())>
> {
  /// \brief Function used to compute the distance between two iterators
  /// \param [in] begin : __Iterator cref = Constant Reference to the iterator at the start of the range
  /// \param [in] end : __Iterator cref = Constant Reference to the iterator at the end of the range
  /// \exceptsafe
  /// \return Size = distance between the iterators
  ///
  /// \test: Not Applicable.
  /// \public
  static inline auto __compute (__Iterator const& begin, __Iterator const& end) noexcept -> Size {  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    // use 'operator -' to compute the distance
    return end - begin;
  }
};
} // namespace __impl
} // namespace __hidden
} // namespace cds

#endif // __CDS_SHARED_ITERATOR_DISTANCE_HPP__
