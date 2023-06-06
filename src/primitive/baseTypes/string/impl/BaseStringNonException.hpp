//
// Created by loghin on 6/9/22.
//

#ifndef __CDS_BASE_STRING_NON_EXCEPTION_HPP__   // NOLINT(llvm-header-guard) 
#define __CDS_BASE_STRING_NON_EXCEPTION_HPP__   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
#pragma once

namespace cds {       // NOLINT(modernize-concat-nested-namespaces) 
namespace __hidden {  // NOLINT(bugprone-reserved-identifier, modernize-concat-nested-namespaces, cert-dcl37-c, cert-dcl51-cpp) 
namespace __impl {    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 

template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
__CDS_cpplang_ConstexprConditioned auto __BaseString <__CharType>::operator == (
    __BaseString const & string
) const noexcept -> bool {
  return __BaseStringView <__CharType> (*this) == __BaseStringView <__CharType> (string);
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
__CDS_cpplang_ConstexprConditioned auto __BaseString <__CharType>::operator != (
    __BaseString const & string
) const noexcept -> bool {
  return __BaseStringView <__CharType> (*this) != __BaseStringView <__CharType> (string);
}

} // namespace __impl 
} // namespace __hidden 
} // namespace cds 

#endif // __CDS_BASE_STRING_NON_EXCEPTION_HPP__ 
