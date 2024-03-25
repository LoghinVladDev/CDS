// DCR-TEST
// STEPS: compile(linux:gcc;linux:clang),run(linux:gcc;linux:clang)
// STD: 11+

#include <cds/String>
#include <cds/StringView>
#include <cassert>
#include <iostream>
#include <array>

#include "UnitTest.hpp"
#include "../Shared.hpp"

namespace {
using cds::String;
using cds::StringView;
}

TEST(String, construction) {
  String a = "abc";
  char const buf[] = "abc";
  String b = buf;
  String c = std::string("abc");
  String d = StringView("abc");

  String e = d;
  String f = cds::move(c);

  (void) a;
  (void) b;
  (void) e;
  (void) f;
}

TEST(String, nonSbo) {
  String a = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
  String b = a;
  String c = cds::move(b);

  (void) c;
}

#ifdef DCR_SINCECPP17
TEST(String, construction17) {
  String a = std::string_view("abc");

  (void) a;
}
#endif
