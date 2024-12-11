//
// Created by loghin on 12/11/24.
//

#ifndef CDS_ITERATOR_BACK_INSERTER_ITERATOR_HPP
#define CDS_ITERATOR_BACK_INSERTER_ITERATOR_HPP

#include <cds/meta/Semantics>
#include <cds/meta/TypeTraits>

namespace cds {
namespace iterator {
namespace impl {
using meta::EnableIf;
using meta::IsSame;
using meta::Not;
using meta::RemoveCVRef;

template <typename T> class BackInserterIterator {
public:
  CDS_ATTR(2(explicit, constexpr(11))) BackInserterIterator(T& obj) noexcept : _obj{obj} {}

  CDS_ATTR(constexpr(14)) auto operator=(BackInserterIterator const&) noexcept -> BackInserterIterator& {
    return *this;
  }

  template <typename V, EnableIf<Not<IsSame<RemoveCVRef<V>, BackInserterIterator>>> = 0>
  CDS_ATTR(constexpr(14)) auto operator=(V&& value) noexcept -> BackInserterIterator& {
    _obj.pushBack(cds::impl::fwd<V>(value));
    return *this;
  }

  CDS_ATTR(constexpr(14)) auto operator*() noexcept -> BackInserterIterator& {
    return *this;
  }

  CDS_ATTR(constexpr(14)) auto operator++() noexcept -> BackInserterIterator& {
    return *this;
  }

private:
  T& _obj;
};
} // namespace impl

using impl::BackInserterIterator;
} // namespace iterator
} // namespace cds

#include "../common/StringBackInserterIterator.hpp"

#endif // #ifndef CDS_ITERATOR_BACK_INSERTER_ITERATOR_HPP
