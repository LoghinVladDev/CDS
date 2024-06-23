// DCR-TEST
// STEPS: compile(linux:gcc;linux:clang),run(linux:gcc;linux:clang)
// STD: 11+

#include <UnitTest.hpp>
#include <cds/Optional>
#include <cds/String>
#include <cds/StringView>

namespace {
using cds::Optional;
using cds::String;
using cds::StringView;
using cds::nullopt;
} // namespace

TEST(OptionalTest, ctrFromNullopt) {
  Optional<int> const o1{};
  Optional<int> const o2{nullopt};

  ASSERT_FALSE(o1.hasValue());
  ASSERT_FALSE(o2.hasValue());
}

TEST(OptionalTest, ctrCopy) {
  String s1 = "abc";
  Optional<int> const o1 {5};
  Optional<String> const o2 {s1};

  ASSERT_TRUE(o1.hasValue());
  ASSERT_TRUE(o2.hasValue());

  ASSERT_EQ(*o1, 5);
  ASSERT_EQ(*o2, "abc");
}

TEST(OptionalTest, ctrMove) {
  String s1 = "abc";
  Optional<String> const o1 {cds::move(s1)};
  ASSERT_TRUE(o1.hasValue());
  ASSERT_EQ(*o1, "abc");
}

TEST(OptionalTest, ctrEmplace) {
  Optional<String> const o1 {4, 'a'};
  ASSERT_TRUE(o1.hasValue());
  ASSERT_EQ(*o1, "aaaa");
}

TEST(OptionalTest, ctrOptCopy) {
  Optional<int> const o1 {5};
  Optional<String> const o2 {"abc"};
  Optional<int> const o3 {};
  Optional<String> const o4 {nullopt};

  Optional<int> const o5 {o1};
  Optional<String> const o6 {o2};
  Optional<int> const o7 {o3};
  Optional<String> const o8 {o4};

  ASSERT_TRUE(o5.hasValue());
  ASSERT_TRUE(o6.hasValue());
  ASSERT_FALSE(o7.hasValue());
  ASSERT_FALSE(o8.hasValue());

  ASSERT_EQ(*o5, 5);
  ASSERT_EQ(*o6, "abc");
}

TEST(OptionalTest, ctrOptMove) {
  Optional<int> o1 {5};
  Optional<String> o2 {"abc"};
  Optional<int> o3 {};
  Optional<String> o4 {nullopt};

  Optional<int> const o5 {cds::move(o1)};
  Optional<String> const o6 {cds::move(o2)};
  Optional<int> const o7 {cds::move(o3)};
  Optional<String> const o8 {cds::move(o4)};

  ASSERT_TRUE(o5.hasValue());
  ASSERT_TRUE(o6.hasValue());
  ASSERT_FALSE(o7.hasValue());
  ASSERT_FALSE(o8.hasValue());

  ASSERT_EQ(*o5, 5);
  ASSERT_EQ(*o6, "abc");
}

TEST(OptionalTest, moveImmediate) {
  int defCtr = 0;
  int cpyCtr = 0;
  int movCtr = 0;
  int cpyAss = 0;
  int movAss = 0;
  struct X {
    X(int& d, int& c, int& m, int& ca, int& ma) : _d{d}, _c{c}, _m{m}, _ca{ca}, _ma{ma} { ++_d; }
    X(X const& o) : _d{o._d}, _c{o._c}, _m{o._m}, _ca{o._ca}, _ma{o._ma} { ++_c; }
    X(X&& o) : _d{o._d}, _c{o._c}, _m{o._m}, _ca{o._ca}, _ma{o._ma} { ++_m; }
    X& operator=(X const&) { ++_ca; return *this; }
    X& operator=(X&&) { ++_ma; return *this; }
    int& _d;
    int& _c;
    int& _m;
    int& _ca;
    int& _ma;
  };

  auto x = Optional<X>{X{defCtr, cpyCtr, movCtr, cpyAss, movAss}}.get();
  cds::ignore = x;
  ASSERT_EQ(defCtr, 1);
  ASSERT_EQ(cpyCtr, 0);
  ASSERT_EQ(movCtr, 2);
  ASSERT_EQ(cpyAss, 0);
  ASSERT_EQ(movAss, 0);
}

TEST(OptionalTest, monadicAndThenCL) {
  Optional<int> const o1 {5};
  Optional<String> const o2 {"abc"};
  Optional<int> const o3 {};
  Optional<String> const o4 {};

  auto const o5 = o1.andThen([](int v) { return Optional<int>{v}; });
  auto const o6 = o2.andThen([](StringView sv){ return Optional<StringView>{sv}; });
  auto const o7 = o3.andThen([](long v) { return Optional<long>{v}; });
  auto const o8 = o4.andThen([](String const& v) { return Optional<String>{v}; });

  ASSERT_TRUE(o5.hasValue());
  ASSERT_TRUE(o6.hasValue());
  ASSERT_FALSE(o7.hasValue());
  ASSERT_FALSE(o8.hasValue());

  ASSERT_EQ(*o5, 5);
  ASSERT_EQ(*o6, "abc");
}

TEST(OptionalTest, monadicAndThenL) {
  Optional<int> o1 {5};
  Optional<String> o2 {"abc"};
  Optional<int> o3 {};
  Optional<String> o4 {};

  auto const o5 = o1.andThen([](int& v) { v = 3; return Optional<int>{v}; });
  auto const o6 = o2.andThen([](String& sv){ sv = "a"; return Optional<StringView>{sv}; });
  auto const o7 = o3.andThen([](long v) { return Optional<long>{v}; });
  auto const o8 = o4.andThen([](StringView v) { return Optional<String>{v}; });

  ASSERT_TRUE(o5.hasValue());
  ASSERT_TRUE(o6.hasValue());
  ASSERT_FALSE(o7.hasValue());
  ASSERT_FALSE(o8.hasValue());

  ASSERT_EQ(*o1, 3);
  ASSERT_EQ(*o5, 3);
  ASSERT_EQ(*o2, "a");
  ASSERT_EQ(*o6, "a");
}

TEST(OptionalTest, monadicAndThenCR) {
  Optional<int> const o1 {5};
  Optional<String> const o2 {"abc"};
  Optional<int> const o3 {};
  Optional<String> const o4 {};

  auto const o5 = cds::move(o1).andThen([](int v) { return Optional<int>{v}; });
  auto const o6 = cds::move(o2).andThen([](StringView sv){ return Optional<StringView>{sv}; });
  auto const o7 = cds::move(o3).andThen([](long v) { return Optional<long>{v}; });
  auto const o8 = cds::move(o4).andThen([](String const& v) { return Optional<String>{v}; });

  ASSERT_TRUE(o5.hasValue());
  ASSERT_TRUE(o6.hasValue());
  ASSERT_FALSE(o7.hasValue());
  ASSERT_FALSE(o8.hasValue());

  ASSERT_EQ(*o5, 5);
  ASSERT_EQ(*o6, "abc");
}

TEST(OptionalTest, monadicAndThenR) {
  Optional<int> o1 {5};
  Optional<String> o2 {"abc"};
  Optional<int> o3 {};
  Optional<String> o4 {};

  auto const o5 = cds::move(o1).andThen([](int v) { return Optional<int>{v}; });
  auto const o6 = cds::move(o2).andThen([](StringView sv){ return Optional<StringView>{sv}; });
  auto const o7 = cds::move(o3).andThen([](long v) { return Optional<long>{v}; });
  auto const o8 = cds::move(o4).andThen([](String const& v) { return Optional<String>{v}; });

  ASSERT_TRUE(o5.hasValue());
  ASSERT_TRUE(o6.hasValue());
  ASSERT_FALSE(o7.hasValue());
  ASSERT_FALSE(o8.hasValue());

  ASSERT_EQ(*o5, 5);
  ASSERT_EQ(*o6, "abc");
}

TEST(OptionalTest, monadicAndThenXVal) {
  int defCtr = 0;
  int cpyCtr = 0;
  int movCtr = 0;
  int cpyAss = 0;
  int movAss = 0;
  struct X {
    X(int& d, int& c, int& m, int& ca, int& ma) : _d{d}, _c{c}, _m{m}, _ca{ca}, _ma{ma} { ++_d; }
    X(X const& o) : _d{o._d}, _c{o._c}, _m{o._m}, _ca{o._ca}, _ma{o._ma} { ++_c; }
    X(X&& o) : _d{o._d}, _c{o._c}, _m{o._m}, _ca{o._ca}, _ma{o._ma} { ++_m; }
    X& operator=(X const&) { ++_ca; return *this; }
    X& operator=(X&&) { ++_ma; return *this; }
    int& _d;
    int& _c;
    int& _m;
    int& _ca;
    int& _ma;
  };

  auto x = Optional<X>{X{defCtr, cpyCtr, movCtr, cpyAss, movAss}}
      .andThen([](X&& v) { return Optional<X>{cds::move(v)}; })
      .andThen([](X&& v) { return Optional<X>{cds::move(v)}; })
      .andThen([](X&& v) { return Optional<X>{cds::move(v)}; });
  ASSERT_TRUE(x.hasValue());

  ASSERT_EQ(defCtr, 1);
  ASSERT_EQ(cpyCtr, 0);
  ASSERT_EQ(movCtr, 4);
  ASSERT_EQ(cpyAss, 0);
  ASSERT_EQ(movAss, 0);
}

TEST(OptionalTest, monadicTransformCL) {
  Optional<int> const o1 {5};
  Optional<String> const o2 {"abc"};
  Optional<int> const o3 {};
  Optional<String> const o4 {};

  auto const o5 = o1.transform([](int v) { return v + 1; });
  auto const o6 = o2.transform([](StringView sv){ return sv.length(); });
  auto const o7 = o3.transform([](long v) { return v - 1; });
  auto const o8 = o4.transform([](String const& v) { return v.length(); });

  ASSERT_TRUE(o5.hasValue());
  ASSERT_TRUE(o6.hasValue());
  ASSERT_FALSE(o7.hasValue());
  ASSERT_FALSE(o8.hasValue());

  ASSERT_EQ(*o5, 6);
  ASSERT_EQ(*o6, 3);
}

TEST(OptionalTest, monadicTransformL) {
  Optional<int> o1 {5};
  Optional<String> o2 {"abc"};
  Optional<int> o3 {};
  Optional<String> o4 {};

  auto const o5 = o1.transform([](int& v) { v = 3; return v + 1; });
  auto const o6 = o2.transform([](String& sv){ sv = "a"; return sv + "dc"; });
  auto const o7 = o3.transform([](long v) { return v; });
  auto const o8 = o4.transform([](StringView v) { return v; });

  ASSERT_TRUE(o5.hasValue());
  ASSERT_TRUE(o6.hasValue());
  ASSERT_FALSE(o7.hasValue());
  ASSERT_FALSE(o8.hasValue());

  ASSERT_EQ(*o1, 3);
  ASSERT_EQ(*o5, 4);
  ASSERT_EQ(*o2, "a");
  ASSERT_EQ(*o6, "adc");
}

TEST(OptionalTest, monadicTransformCR) {
  Optional<int> const o1 {5};
  Optional<String> const o2 {"abc"};
  Optional<int> const o3 {};
  Optional<String> const o4 {};

  auto const o5 = cds::move(o1).transform([](int v) { return v + 1; });
  auto const o6 = cds::move(o2).transform([](StringView sv){ return sv.length(); });
  auto const o7 = cds::move(o3).transform([](long v) { return v - 1; });
  auto const o8 = cds::move(o4).transform([](String const& v) { return v.length(); });

  ASSERT_TRUE(o5.hasValue());
  ASSERT_TRUE(o6.hasValue());
  ASSERT_FALSE(o7.hasValue());
  ASSERT_FALSE(o8.hasValue());

  ASSERT_EQ(*o5, 6);
  ASSERT_EQ(*o6, 3);
}

TEST(OptionalTest, monadicTransformR) {
  Optional<int> o1 {5};
  Optional<String> o2 {"abc"};
  Optional<int> o3 {};
  Optional<String> o4 {};

  auto const o5 = cds::move(o1).transform([](int v) { return v + 1; });
  auto const o6 = cds::move(o2).transform([](StringView sv){ return sv.length(); });
  auto const o7 = cds::move(o3).transform([](long v) { return v - 1; });
  auto const o8 = cds::move(o4).transform([](String const& v) { return v.length(); });

  ASSERT_TRUE(o5.hasValue());
  ASSERT_TRUE(o6.hasValue());
  ASSERT_FALSE(o7.hasValue());
  ASSERT_FALSE(o8.hasValue());

  ASSERT_EQ(*o5, 6);
  ASSERT_EQ(*o6, 3);
}

TEST(OptionalTest, monadicTransformXVal) {
  int defCtr = 0;
  int cpyCtr = 0;
  int movCtr = 0;
  int cpyAss = 0;
  int movAss = 0;
  struct X {
    X(int& d, int& c, int& m, int& ca, int& ma) : _d{d}, _c{c}, _m{m}, _ca{ca}, _ma{ma} { ++_d; }
    X(X const& o) : _d{o._d}, _c{o._c}, _m{o._m}, _ca{o._ca}, _ma{o._ma} { ++_c; }
    X(X&& o) : _d{o._d}, _c{o._c}, _m{o._m}, _ca{o._ca}, _ma{o._ma} { ++_m; }
    X& operator=(X const&) { ++_ca; return *this; }
    X& operator=(X&&) { ++_ma; return *this; }
    int& _d;
    int& _c;
    int& _m;
    int& _ca;
    int& _ma;
  };

  auto x = Optional<X>{X{defCtr, cpyCtr, movCtr, cpyAss, movAss}}
      .transform([](X&& v) { return cds::move(v); })
      .transform([](X&& v) { return cds::move(v); })
      .transform([](X&& v) { return cds::move(v); });
  ASSERT_TRUE(x.hasValue());

  ASSERT_EQ(defCtr, 1);
  ASSERT_EQ(cpyCtr, 0);
  ASSERT_EQ(movCtr, 7);
  ASSERT_EQ(cpyAss, 0);
  ASSERT_EQ(movAss, 0);
}

TEST(OptionalTest, monadicOrElseL) {
  Optional<int> const o1 {1};
  Optional<String> const o2 {"abc"};
  Optional<int> const o3 {};
  Optional<String> const o4 {};

  auto const o5 = o1.orElse([](){ return Optional<int>{2}; });
  auto const o6 = o2.orElse([]() { return Optional<String> {"bcd"}; });
  auto const o7 = o3.orElse([](){ return Optional<int>{2}; });
  auto const o8 = o4.orElse([]() { return Optional<String> {"bcd"}; });

  ASSERT_TRUE(o5.hasValue());
  ASSERT_TRUE(o6.hasValue());
  ASSERT_TRUE(o7.hasValue());
  ASSERT_TRUE(o8.hasValue());

  ASSERT_EQ(*o5, 1);
  ASSERT_EQ(*o6, "abc");
  ASSERT_EQ(*o7, 2);
  ASSERT_EQ(*o8, "bcd");

  auto const o9 = o1.orElse([]() { return nullopt; });
  auto const o10 = o2.orElse([]() { return nullopt; });
  auto const o11 = o3.orElse([]() { return nullopt; });
  auto const o12 = o4.orElse([]() { return nullopt; });

  ASSERT_TRUE(o9.hasValue());
  ASSERT_TRUE(o10.hasValue());
  ASSERT_FALSE(o11.hasValue());
  ASSERT_FALSE(o12.hasValue());

  ASSERT_EQ(*o9, 1);
  ASSERT_EQ(*o10, "abc");
}

TEST(OptionalTest, monadicOrElseR) {
  Optional<int> o1 {1};
  Optional<String> o2 {"abc"};
  Optional<int> o3 {};
  Optional<String> o4 {};

  auto const o5 = cds::move(o1).orElse([](){ return Optional<int>{2}; });
  auto const o6 = cds::move(o2).orElse([]() { return Optional<String> {"bcd"}; });
  auto const o7 = cds::move(o3).orElse([](){ return Optional<int>{2}; });
  auto const o8 = cds::move(o4).orElse([]() { return Optional<String> {"bcd"}; });

  ASSERT_TRUE(o5.hasValue());
  ASSERT_TRUE(o6.hasValue());
  ASSERT_TRUE(o7.hasValue());
  ASSERT_TRUE(o8.hasValue());

  ASSERT_EQ(*o5, 1);
  ASSERT_EQ(*o6, "abc");
  ASSERT_EQ(*o7, 2);
  ASSERT_EQ(*o8, "bcd");
}
