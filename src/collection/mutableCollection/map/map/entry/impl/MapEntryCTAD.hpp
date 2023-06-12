// NOLINT(llvm-header-guard)
// Created by loghin on 15/10/22.
//

#ifndef __CDS_MAP_ENTRY_CTAD_IMPL_HPP__ // NOLINT(llvm-header-guard)
#define __CDS_MAP_ENTRY_CTAD_IMPL_HPP__ // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
#pragma once

#if __CDS_cpplang_CTAD_available
namespace cds {
template <typename __KeyType, typename __ValueType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
MapEntry (__KeyType, __ValueType) -> MapEntry <__KeyType, __ValueType>;
} // namespace cds
#endif

#endif // __CDS_MAP_ENTRY_CTAD_IMPL_HPP__
