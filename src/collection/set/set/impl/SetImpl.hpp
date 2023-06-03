// NOLINT(llvm-header-guard)
// Created by loghin on 09/08/22.
//

#ifndef __CDS_SET_IMPL_HPP__ // NOLINT(llvm-header-guard)
#define __CDS_SET_IMPL_HPP__ // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
#pragma once

namespace cds {

template <
    typename                                                                  __ElementType,  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    cds::meta::EnableIf <cds::meta::IsValidSetElement <__ElementType>::value> __enabler       // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> constexpr Set <__ElementType, __enabler>::Set () noexcept = default;


template <
    typename                                                                  __ElementType,  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    cds::meta::EnableIf <cds::meta::IsValidSetElement <__ElementType>::value> __enabler       // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> constexpr Set <__ElementType, __enabler>::Set (Set const& set) noexcept :
    CollectionBase (set) {
  // call base copy constructor 
}


template <
    typename                                                                  __ElementType,  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    cds::meta::EnableIf <cds::meta::IsValidSetElement <__ElementType>::value> __enabler       // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> constexpr Set <__ElementType, __enabler>::Set (Set&& set) noexcept :
    CollectionBase (std::move (set)) {
  // call base move constructor 
}


template <
    typename                                                                  __ElementType,  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    cds::meta::EnableIf <cds::meta::IsValidSetElement <__ElementType>::value> __enabler       // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> __CDS_cpplang_ConstexprDestructor Set <__ElementType, __enabler>::~Set () noexcept = default;


template <
    typename                                                                  __ElementType,  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    cds::meta::EnableIf <cds::meta::IsValidSetElement <__ElementType>::value> __enabler       // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> auto Set <__ElementType, __enabler>::toString () const noexcept -> String {
  // Set toString representation is curly-brackets enclosed list 
  // if empty, return empty list 
  if (empty()) {
    return {"{}"};
  }

  // use a StringStream to output the contents for maximum compatibility. Start with open bracket 
  std::stringstream out;
  out << "{ ";
  // iterate through Set and append iterator value to Stream 
  for (auto iterator = cbegin(), end = cend(); iterator != end; ++iterator) { // NOLINT(clion-misra-cpp2008-8-0-1)
    cds::meta::print (out, *iterator) << ", ";
  }

  // transform to std string 
  auto asString = out.str();
  // replace ", " with " }" 
  asString [asString.length() - 2u] = ' ';
  asString [asString.length() - 1u] = '}';
  // return std::string to be reused as cds::String 
  return asString;
}

} // namespace cds

#endif // __CDS_SET_IMPL_HPP__
