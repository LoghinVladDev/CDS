//
// Created by loghin on 12/8/23.
//

#ifndef CDS_PRIMITIVE_STRING_VIEW_BASE_DECL_HPP
#define CDS_PRIMITIVE_STRING_VIEW_BASE_DECL_HPP
#pragma once

#include "StringBaseDecl.hpp"

namespace cds {
namespace meta {
template <typename> struct StringTraits;
} // namespace meta

namespace impl {
using meta::StringTraits;
template <typename, typename> struct StringUtils;

template<typename C, typename U = StringUtils<C, StringTraits<C>>> class BaseStringView;
} // namespace impl

namespace iterator {
template <typename> class ForwardAddressIterator;
template <typename> class BackwardAddressIterator;
} // namespace iterator

namespace meta {
template <typename C, typename U> struct IterableTraits<cds::impl::BaseStringView<C, U>> {
  using Value = C;
  using Iterator = iterator::ForwardAddressIterator<C const>;
  using ConstIterator = Iterator;
  using ReverseIterator = iterator::BackwardAddressIterator<C const>;
  using ConstReverseIterator = ReverseIterator;
};
} // namespace meta
} // namespace cds

#endif // CDS_PRIMITIVE_STRING_VIEW_BASE_DECL_HPP