//
// Created by loghin on 7/29/25.
//

#ifndef CDS_PRIMITIVE_EXPECTED_EXPECTED_DECL_HPP
#define CDS_PRIMITIVE_EXPECTED_EXPECTED_DECL_HPP
#pragma once

#include <cds/meta/Base>

namespace cds {
namespace impl {
using meta::False;
using meta::True;

template <typename E> class Unexpected;
template <typename T, typename E> class Expected;

template <typename> struct IsExpected : False {};
template <typename T, typename E> struct IsExpected<Expected<T, E>> : True {};
} // namespace impl
} // namespace cds

#endif // #ifndef CDS_PRIMITIVE_EXPECTED_EXPECTED_DECL_HPP
