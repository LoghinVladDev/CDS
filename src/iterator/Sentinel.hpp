//
// Created by loghin on 12/21/23.
//

#ifndef CDS_SENTINEL_HPP
#define CDS_SENTINEL_HPP
#pragma once

namespace cds {
namespace iterator {
class Sentinel {
  static_assert(compiler::CurrentStd::version >= compiler::StdCpp17::version, "Sentinel requires c++17 or above");
};
} // namespace iterator
} // namespace cds

#endif //CDS_SENTINEL_HPP
