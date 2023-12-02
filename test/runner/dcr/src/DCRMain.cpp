//
// Created by loghin on 12/2/23.
//

#include <sstream>

#include "Test.hpp"

namespace dcr {
namespace internals {
std::vector<std::unique_ptr<Test const>> allTests;

auto tests() -> std::vector<std::unique_ptr<Test const>>& {
  return allTests;
}
}
}

int main(int argc, char** argv) {
  // connect to runner

  std::stringstream execBuffer;
  int totalCount = 0;
  int successfulCount = 0;
  for (auto const& test: dcr::internals::allTests) {
    ++totalCount;
    if (test->_execute(execBuffer)) {
      ++successfulCount;
    }
  }

  // write back stats
  return 0;
}
