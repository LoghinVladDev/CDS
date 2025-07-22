//
// Created by loghin on 12/22/23.
//

#ifndef CDS_FUNCTIONAL_STREAM_PRINT_HPP
#define CDS_FUNCTIONAL_STREAM_PRINT_HPP
#pragma once

#include <cds/meta/Semantics>
#include <cds/meta/ObjectTraits>

#include "../stdlib/ostream.hpp"

namespace cds {
namespace functional {
namespace impl {
using meta::Void;
using meta::rvalue;
using meta::lvalue;

template <typename T, typename C = char, typename = void> struct StreamPrint {
  CDS_ATTR(nodiscard) auto operator()(std::basic_ostream<C>& out, T const& val) const noexcept
      -> std::basic_ostream<C>& {
    return out << "Unknown@" << &val;
  }
};

template <typename T, typename C>
struct StreamPrint<T, C, Void<decltype(lvalue<std::basic_ostream<C>>() << rvalue<T>())>> {
  CDS_ATTR(nodiscard) auto operator()(std::basic_ostream<C>& out, T const& val) const
      CDS_ATTR(noexcept(noexcept(out << val))) -> std::basic_ostream<C>& {
    return out << val;
  }
};

template <typename T, typename C> CDS_ATTR(nodiscard) auto streamPrint(std::basic_ostream<C>& out, T const& val)
    CDS_ATTR(noexcept(noexcept(StreamPrint<T, C>{}(out, val)))) -> std::basic_ostream<C>& {
  return StreamPrint<T, C>{}(out, val);
}
} // namespace impl

using impl::streamPrint;
using impl::StreamPrint;
} // namespace functional
} // namespace cds

#endif // CDS_FUNCTIONAL_STREAM_PRINT_HPP
