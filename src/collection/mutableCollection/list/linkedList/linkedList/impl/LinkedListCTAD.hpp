// NOLINT(llvm-header-guard)
// Created by loghin on 17/07/22.
//

#ifndef __CDS_LINKED_LIST_CTAD_HPP__ // NOLINT(llvm-header-guard)
#define __CDS_LINKED_LIST_CTAD_HPP__ // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
#pragma once

#if __CDS_cpplang_CTAD_available
namespace cds {

template <typename __ElementType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
LinkedList (
    std::initializer_list <__ElementType>
) -> LinkedList <__ElementType>;

} // namespace cds
#endif

#endif // __CDS_LINKED_LIST_CTAD_HPP__
