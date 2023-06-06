//
// Created by loghin on 6/3/22.
//

#ifndef __CDS_STRING_HPP__ // NOLINT(llvm-header-guard) 
#define __CDS_STRING_HPP__ // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 

#include <CDS/Object>   // NOLINT(llvm-include-order) 
#include <CDS/FunctionalInterface>
#include "../../shared/iterator/AddressIterator.hpp"

namespace cds {

namespace __hidden {    // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
namespace __impl {  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 

template <typename __CharType>    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __BaseString;                 // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 

template <typename __CharType>    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __BaseStringView;             // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 

} // namespace __impl
} // namespace __hidden

using String                                = __hidden::__impl::__BaseString <char>;
using WideString       __CDS_MaybeUnused    = __hidden::__impl::__BaseString <wchar_t>;

using StringView                            = __hidden::__impl::__BaseStringView <char>;
using WideStringView    __CDS_MaybeUnused   = __hidden::__impl::__BaseStringView <wchar_t>;
} // namespace cds

#include "string/BaseString.hpp"    // NOLINT(llvm-include-order) 
#include "../../shared/iterator/impl/AddressIterator.hpp"

#endif // __CDS_STRING_HPP__ 
