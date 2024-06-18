//
// Created by loghin on 12/2/23.
//

#include <sstream>
#ifndef DCR_NO_SUBPROCESS_LOGGING
#include <iostream>
#endif

#include "Test.hpp"

namespace dcr {
namespace internals {
auto tests() -> std::vector<std::unique_ptr<Test const>>& {
  static std::vector<std::unique_ptr<Test const>> allTests;
  return allTests;
}
}
}

#ifndef DCR_OMIT_MAIN
int main(int argc, char** argv) {
  // connect to runner

#ifndef DCR_NO_SUBPROCESS_LOGGING
  std::stringstream execBuffer;
#endif
  int totalCount = 0;
  int successfulCount = 0;
  for (auto const& test: dcr::internals::tests()) {
    ++totalCount;
    if (test->_execute(execBuffer)) {
      ++successfulCount;
    }
  }

  if (totalCount != successfulCount) {
#ifndef DCR_NO_SUBPROCESS_LOGGING
    std::cout << execBuffer.str() << '\n';
#endif
    return 1;
  }

  return 0;
}
#endif
