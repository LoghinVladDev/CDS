//
// Created by loghin on 12/1/23.
//

#include "Test.hpp"

#include <exception>
#include <ostream>

namespace dcr {
auto Test::_execute(std::ostream& out) const noexcept -> bool {
  try {
    _run();
    out << "Test " << _test << " passed\n";
    return true;
  } catch (std::exception const& assertionException) {
    out << "Test " << _test << " failed:\n" << assertionException.what() << '\n';
    return false;
  }
}

} // namespace dcr
