// NOLINT(llvm-header-guard)
// Created by loghin on 14/08/22.
//

#ifndef __CDS_TREE_MAP_CTAD_HPP__ // NOLINT(llvm-header-guard)
#define __CDS_TREE_MAP_CTAD_HPP__ // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
#pragma once

#if __CDS_cpplang_CTAD_available
namespace cds {
template <
    typename __KeyType,     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __ValueType,   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __Comparator   = functional::DecoratedPredicate <          // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
        cds::functional::PredicateFunction <__KeyType const&, __KeyType const&>,
        &cds::predicates::lessThan <__KeyType>
    >
> TreeMap (
    std::initializer_list <MapEntry <__KeyType, __ValueType>>
) -> TreeMap <__KeyType, __ValueType, __Comparator>;
} // namespace cds
#endif

#endif // __CDS_TREE_MAP_CTAD_HPP__
