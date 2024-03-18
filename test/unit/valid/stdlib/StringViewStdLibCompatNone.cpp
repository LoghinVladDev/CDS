// DCR-TEST
// STEPS: compile(linux:gcc;linux:clang)
// STD: 11+

#define CDS_OPTION_STD_COMPAT_MODE 0
#include <cds/StringView>

using namespace cds;

using cds::StringView;

void svNoneCompat1() {
  StringView const sv;
  (void) sv;
}

#include <string>
#include <sstream>
#if CDS_ATTR(cpp17)
#include <string_view>
#endif

void svNoneCompat2() {
  StringView const sv2;
  (void) sv2;
}
