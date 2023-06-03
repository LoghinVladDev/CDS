//
// Created by loghin on 6/26/22.
//

#ifndef __CDS_ITERABLE_IMPL_HPP__ // NOLINT(llvm-header-guard)
#define __CDS_ITERABLE_IMPL_HPP__ // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
#pragma once

namespace cds {
template < typename __ElementType > // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
constexpr Iterable < __ElementType >::Iterable () noexcept = default;


template < typename __ElementType > // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
constexpr Iterable < __ElementType >::Iterable (Iterable const& iterable) noexcept = default;


template < typename __ElementType > // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
constexpr Iterable < __ElementType >::Iterable (Iterable&& iterable) noexcept = default;


template < typename __ElementType > // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_ConstexprDestructor Iterable < __ElementType >::~Iterable () noexcept = default;


template < typename __ElementType > // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto Iterable < __ElementType >::toString () const noexcept -> String {
  // Default toString implementation, store 'Iterable at 0x....'. Use a stringstream for simplicity 
  std::stringstream oss;
  oss << "Iterable at " << this;

  // converted to std::string, and to cds::String afterward 
  return oss.str();
}


template < typename __ElementType > // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto Iterable < __ElementType >::contains (
    ElementType const & element
) const noexcept -> bool {
  // Parse object via forward iteration 
  for (auto iterator = cbegin(), end = cend(); iterator != end; ++iterator) {
    // If object found, the object is contained in the iterable 
    if (Iterable::__if_equals (element, *iterator)) {
      return true;
    }
  }

  // If full parse complete and not found, object not contained in the iterable 
  return false;
}
} // namespace cds 


#endif // __CDS_ITERABLE_IMPL_HPP__ 
