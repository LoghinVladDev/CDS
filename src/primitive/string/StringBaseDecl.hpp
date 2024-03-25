//
// Created by loghin on 3/19/24.
//

#ifndef CDS_PRIMITIVE_STRING_BASE_DECL_HPP
#define CDS_PRIMITIVE_STRING_BASE_DECL_HPP
#pragma once

#include <cds/meta/IteratorTraits>
#include <cds/meta/StringTraits>
#include <cds/memory/Allocator>

namespace cds {
namespace meta {
template <typename> struct StringTraits;
} // namespace meta

namespace impl {
using meta::StringTraits;
template <typename, typename> struct StringUtils;

template <typename C, typename = StringUtils<C, StringTraits<C>>, typename = Allocator<C>> class BaseString;
} // namespace impl

namespace iterator {
template <typename> class ForwardAddressIterator;
template <typename> class BackwardAddressIterator;
} // namespace iterator

namespace meta {
template <typename C, typename U, typename A> struct IterableTraits<cds::impl::BaseString<C, U, A>> {
  using Value = C;
  using Iterator = iterator::ForwardAddressIterator<C>;
  using ConstIterator = iterator::ForwardAddressIterator<C const>;
  using ReverseIterator = iterator::BackwardAddressIterator<C>;
  using ConstReverseIterator = iterator::BackwardAddressIterator<C const>;
};
} // namespace meta
} // namespace cds

#endif // CDS_PRIMITIVE_STRING_BASE_DECL_HPP
