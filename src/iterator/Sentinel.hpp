//
// Created by loghin on 12/21/23.
//

#ifndef CDS_ITERATOR_SENTINEL_HPP
#define CDS_ITERATOR_SENTINEL_HPP
#pragma once

#include <cds/meta/Compiler>

namespace cds {
namespace iterator {
class Sentinel {
  static_assert(compiler::CurrentStd::version >= compiler::StdCpp17::version, "Sentinel requires c++17 or above");
};
} // namespace iterator
} // namespace cds

#endif // CDS_ITERATOR_SENTINEL_HPP
