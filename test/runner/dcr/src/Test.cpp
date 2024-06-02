//
// Created by loghin on 12/1/23.
//

#include "Test.hpp"

#include <exception>
#include <ostream>

namespace dcr {
#ifndef DCR_NO_SUBPROCESS_LOGGING
auto Test::_execute(std::ostream& out) const noexcept -> bool {
#else
auto Test::_execute() const noexcept -> bool {
#endif
  try {
    _run();
#ifndef DCR_NO_SUBPROCESS_LOGGING
    out << "Test " << _suite << " -> " << _test << " passed\n";
#endif
    return true;
  } catch (std::exception const& assertionException) {
#ifndef DCR_NO_SUBPROCESS_LOGGING
    out << "Test " << _suite << " -> " << _test << " failed:\n" << assertionException.what() << '\n';
#endif
    return false;
  }
}

} // namespace dcr
