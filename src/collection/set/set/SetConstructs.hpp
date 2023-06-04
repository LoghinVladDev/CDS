// NOLINT(llvm-header-guard)
// Created by loghin on 7/23/2022.
//

#ifndef __CDS_SET_CONSTRUCTS_HPP__ // NOLINT(llvm-header-guard)
#define __CDS_SET_CONSTRUCTS_HPP__ // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
#pragma once

namespace cds {
namespace meta {
template <typename __ElementType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
struct IsValidSetElement : Or <EqualToPossible<__ElementType>, IsDerivedFrom <__ElementType, cds::Object>> {};
} // namespace meta

/// @class Set pre-declaration
/// @tparam __ElementType is the type of the elements enclosed in the set
template <
    typename __ElementType, // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    cds::meta::EnableIf <cds::meta::IsValidSetElement <__ElementType>::value> = 0
> class Set;

namespace __hidden {  // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
namespace __impl {    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
/// @typedef Alias used by Set to implement the Find Unique Client
/// @tparam __ElementType is the type of elements contained into the Set
/// @tparam __enabler is the enabler value generated by the EnableIf < isValidSetElement >, used only by definitions
/// @namespace cds::__hidden::__impl
/// @internal library-private
template <
    typename __ElementType,                                                                 // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    cds::meta::EnableIf <cds::meta::IsValidSetElement <__ElementType>::value> __enabler = 0 // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> class __CDS_InheritsEBOs __SetFindUniqueClient :                                          // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __FindUniqueImmutablePrimitiveClient <
        cds::Set <__ElementType, __enabler>,
        __ElementType, __ElementType, false
    > {};
} // namespace __impl
} // namespace __hidden
} // namespace cds

#endif // __CDS_SET_CONSTRUCTS_HPP__