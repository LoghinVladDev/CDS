// NOLINT(llvm-header-guard)
// Created by loghin on 6/13/22.
//

#ifndef __CDS_TREE_SET_CTAD_HPP__ // NOLINT(llvm-header-guard)
#define __CDS_TREE_SET_CTAD_HPP__ // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
#pragma once

#if __CDS_cpplang_CTAD_available

namespace cds {

template <
    typename __ElementType,                                   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __Comparator = functional::DecoratedPredicate <  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
        cds::functional::PredicateFunction <__ElementType const&, __ElementType const&>,
        &cds::predicates::lessThan <__ElementType>
    >
> TreeSet (
        std :: initializer_list <__ElementType>
) -> TreeSet <__ElementType, __Comparator>;

} // namespace cds

#endif

#endif // __CDS_TREE_SET_CTAD_HPP__
