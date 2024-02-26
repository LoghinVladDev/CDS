// DCR-TEST
// STEPS: compile(linux:gcc;linux:clang)
// STD: 11-2b

#define CDS_OPTION_STD_COMPAT_MODE 0
#include <cds/StringView>

using namespace cds;

namespace {
using cds::StringView;

void compatTest1() {
  StringView sv;
}
}

#include <string>
#include <sstream>
#if CDS_ATTR(cpp17)
#include <string_view>
#endif

namespace {
void compatTest2() {
  StringView sv2;
}
}
