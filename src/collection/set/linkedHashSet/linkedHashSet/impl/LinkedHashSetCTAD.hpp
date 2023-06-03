// NOLINT(llvm-header-guard)
// Created by loghin on 6/13/22.
//

#ifndef __CDS_LINKED_HASH_SET_CTAD_HPP__ // NOLINT(llvm-header-guard)
#define __CDS_LINKED_HASH_SET_CTAD_HPP__ // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
#pragma once

#if __CDS_cpplang_CTAD_available

namespace cds {

template <
    typename __ElementType,                                                       // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __Hasher = cds::WrapperHasher <__ElementType, Hash <__ElementType>>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> LinkedHashSet (std::initializer_list <__ElementType>) -> LinkedHashSet <__ElementType, __Hasher>;

template <
    typename __ElementType,                                                       // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __Hasher = cds::WrapperHasher <__ElementType, Hash <__ElementType>>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> LinkedHashSet (__Hasher, std::initializer_list <__ElementType>) -> LinkedHashSet <__ElementType, __Hasher>;

} // namespace cds

#endif

#endif // __CDS_LINKED_HASH_SET_CTAD_HPP__
