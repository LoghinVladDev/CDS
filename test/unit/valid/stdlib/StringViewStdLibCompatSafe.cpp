// DCR-TEST
// STEPS: compile(linux:gcc;linux:clang)
// STD: 11+

#define CDS_OPTION_STD_COMPAT_MODE 1
#include <cds/StringView>

using namespace cds;

using cds::StringView;

void svSafeCompat1() {
  StringView const sv;
  (void) sv;
}

#include <string>
#include <sstream>
#if CDS_ATTR(cpp17)
#include <string_view>
#endif

void svSafeCompat2() {
  StringView const sv2;
  (void) sv2.split(std::string{"abc"});
#if CDS_ATTR(cpp17)
  (void) sv2.split(std::string_view{"abc"});
#endif
  std::stringstream oss;
  oss << sv2;
}
