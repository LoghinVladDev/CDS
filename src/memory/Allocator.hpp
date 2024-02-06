//
// Created by loghin on 12/8/23.
//

#ifndef CDS_MEMORY_ALLOCATOR_HPP
#define CDS_MEMORY_ALLOCATOR_HPP
#pragma once

namespace cds {
namespace meta {
template <typename, typename = void> struct IsAllocator : False {};
template <typename T> struct IsAllocator<T, Void<decltype(value<T>().allocate(0))>> : True {};
} // namespace meta

template <typename T> class Allocator : public std::allocator<T> {};
} // namespace cds

#endif // CDS_MEMORY_ALLOCATOR_HPP
