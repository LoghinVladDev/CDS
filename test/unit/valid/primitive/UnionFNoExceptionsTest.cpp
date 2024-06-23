// DCR-TEST
// STEPS: compile(linux:gcc;linux:clang),run(linux:gcc;linux:clang)
// STD: 11+
// FLAGS[compile]: -fno-exceptions

#include <UnitTest.hpp>
#include <cds/Union>
#include <cds/String>
#include <cds/StringView>
#include <cds/Tuple>

namespace {
using cds::String;
using cds::StringView;

using cds::Union;
}

TEST(UnionTest, constructionCheckActive) {
  Union<int, String> const a1;
  ASSERT_EQ(a1.index(), 0u);

  Union<String, int> const a2;
  ASSERT_EQ(a2.index(), 0u);

  Union<int, String> const a3 = 3;
  ASSERT_EQ(a3.index(), 0u);

  Union<int, String> const a4 = "abcd";
  ASSERT_EQ(a4.index(), 1u);

  Union<int, String> const a5 = 3.4;
  ASSERT_EQ(a5.index(), 0u);

  Union<int, String> const a6 = std::string("abc");
  ASSERT_EQ(a6.index(), 1u);
}

TEST(UnionTest, get) {
  using cds::impl::get;

  Union<int, String> const a1 = 3;
  ASSERT_EQ(a1.get<int>(), 3);

  Union<int, String> const a2 = "abc";
  ASSERT_EQ(a2.get<String>(), "abc");
}

TEST(UnionTest, getMutate) {
  using cds::impl::get;
  Union<int, String> a1;
  a1.get<int>() = 5;
  ASSERT_EQ(get<int>(a1), 5);
  get<int>(a1) = 7;
  ASSERT_EQ(get<int>(a1), 7);

  Union<int, String> a2 = "abc";
  ASSERT_EQ(get<String>(a2), "abc");
  a2.get<String>() = "abcd";
  ASSERT_EQ(get<String>(a2), "abcd");
  get<String>(a2) = "abcde";
  ASSERT_EQ(get<String>(a2), "abcde");
}

TEST(UnionTest, ensureCorrectDestruction) {
  struct X {
    explicit X(int& aliveCtr) : _alive{aliveCtr} { ++_alive; }
    X(X const& obj) : _alive{obj._alive} { ++_alive; }
    X(X&& obj) : _alive{obj._alive} { ++_alive; }
    ~X() { --_alive; }
    int& _alive;
  };

  int aliveCtr = 0;
  Union<int, X> u1;
  ASSERT_EQ(aliveCtr, 0);
  {
    Union<X, int> u2 = X{aliveCtr};
    ASSERT_EQ(aliveCtr, 1);
  }
  ASSERT_EQ(aliveCtr, 0);
}

TEST(UnionTest, is) {
  Union <int, String> const u1 = 3;
  Union <int, String> const u2 = "abc";
  ASSERT_TRUE(u1.is<int>());
  ASSERT_TRUE(u2.is<String>());
}

TEST(UnionTest, copy) {
  Union <int, String> const u1 = 3;
  Union <int, String> const u2 = "abc";
  auto const u3 {u1};
  auto const u4 {u2};
  ASSERT_TRUE(u3.is<int>());
  ASSERT_TRUE(u4.is<String>());

  struct X {
    explicit X(int& aliveCtr, int& copied) : _alive{aliveCtr}, _copied{copied} { ++_alive; }
    X(X const& obj) : _alive{obj._alive}, _copied{obj._copied} { ++_alive; ++_copied; }
    X(X&& obj) : _alive{obj._alive}, _copied{obj._copied} { ++_alive; }
    ~X() { --_alive; }
    int& _alive;
    int& _copied;
  };

  int aliveCtr = 0;
  int copiedCtr = 0;
  Union <int, X> const u5 = 4;
  ASSERT_EQ(aliveCtr, 0);
  ASSERT_EQ(copiedCtr, 0);
  {
    Union <int, X> const u6 {X{aliveCtr, copiedCtr}};
    ASSERT_EQ(aliveCtr, 1);
    ASSERT_EQ(copiedCtr, 0);
    auto const u7 {u6};
    ASSERT_EQ(aliveCtr, 2);
    ASSERT_EQ(copiedCtr, 1);
  }
  ASSERT_EQ(aliveCtr, 0);
}

TEST(UnionTest, move) {
  Union <int, String> u1 = 3;
  Union <int, String> u2 = "abc";
  auto const u3 {cds::move(u1)};
  auto const u4 {cds::move(u2)};
  ASSERT_TRUE(u3.is<int>());
  ASSERT_TRUE(u4.is<String>());

  struct X {
    explicit X(int& aliveCtr, int& moved) : _alive{aliveCtr}, _moved{moved} { ++_alive; }
    X(X const& obj) : _alive{obj._alive}, _moved{obj._moved} { ++_alive; }
    X(X&& obj) : _alive{obj._alive}, _moved{obj._moved} { ++_alive; ++_moved; }
    ~X() { --_alive; }
    int& _alive;
    int& _moved;
  };

  int aliveCtr = 0;
  int movedCtr = 0;
  Union <int, X> u5 = 4;
  ASSERT_EQ(aliveCtr, 0);
  ASSERT_EQ(movedCtr, 0);
  {
    Union <int, X> u6 {X{aliveCtr, movedCtr}};
    ASSERT_EQ(aliveCtr, 1);
    ASSERT_EQ(movedCtr, 1);
    auto const u7 {cds::move(u6)};
    ASSERT_EQ(aliveCtr, 2);
    ASSERT_EQ(movedCtr, 2);
  }
  ASSERT_EQ(aliveCtr, 0);
}

TEST(UnionTest, assignReplace) {
  using cds::impl::get;
  Union<int, String> u1;
  u1 = 3;
  ASSERT_TRUE(u1.is<int>());
  ASSERT_EQ(get<int>(u1), 3);
  u1 = 5;
  ASSERT_TRUE(u1.is<int>());
  ASSERT_EQ(get<int>(u1), 5);
  u1 = "abcd";
  ASSERT_TRUE(u1.is<String>());
  ASSERT_EQ(get<String>(u1), "abcd");
  u1 = "bcdef";
  ASSERT_TRUE(u1.is<String>());
  ASSERT_EQ(get<String>(u1), "bcdef");
  u1 = 7;
  ASSERT_TRUE(u1.is<int>());
  ASSERT_EQ(get<int>(u1), 7);

  ASSERT_TRUE(noexcept(u1 = 3));
  ASSERT_TRUE(noexcept(u1 = "abc"));
}

TEST(UnionTest, assignThrowResultsInValueless) {
  struct X {
    X() = default;
    X(int) { std::terminate(); }
    auto operator=(int) -> X& {
      std::terminate();
    }
  };

  struct Y {};

  Union<X, Y> u1;
  ASSERT_FALSE(u1.valueless());
  u1 = X{};
  ASSERT_FALSE(u1.valueless());
  u1 = Y{};
  ASSERT_FALSE(u1.valueless());
  u1 = X{};
  ASSERT_FALSE(u1.valueless());
}

TEST(UnionTest, emplace) {
  using cds::impl::get;
  Union<int, String> a;
  a.emplace<String>(10, 'a');
  ASSERT_FALSE(a.valueless());
  ASSERT_TRUE(a.is<String>());
  ASSERT_FALSE(a.valueless());
  ASSERT_EQ(get<String>(a), "aaaaaaaaaa");
  ASSERT_FALSE(a.valueless());
  ASSERT_EQ(a.emplace<String>(5, 'b'), "bbbbb");
  ASSERT_FALSE(a.valueless());
  ASSERT_EQ(a.emplace<int>(3), 3);
  ASSERT_FALSE(a.valueless());
  ASSERT_TRUE(a.is<int>());
  ASSERT_FALSE(a.valueless());
  ASSERT_EQ(a.emplace<String>(3), "3");

  ASSERT_FALSE(a.valueless());
}

TEST(UnionTest, emplaceThrowGetsValueless) {
  struct X {
    X() = default;
    X(int) { std::terminate(); }
    auto operator=(int) -> X& {
      std::terminate();
    }
  };

  struct Y {};

  Union<X, Y> u1;
  u1.emplace<X>(X{});
  ASSERT_FALSE(u1.valueless());
  u1.emplace<Y>();
  ASSERT_FALSE(u1.valueless());
  u1.emplace<X>();
  ASSERT_FALSE(u1.valueless());

}

TEST(UnionTest, copyAssign) {
  using cds::impl::get;
  Union<int, String> u1;
  Union<int, String> const u2 = 3;
  Union<int, String> const u3 = "abc";
  u1 = u2;
  ASSERT_TRUE(u1.is<int>());
  ASSERT_EQ(get<int>(u1), 3);
  u1 = u3;
  ASSERT_TRUE(u1.is<String>());
  ASSERT_EQ(get<String>(u1), "abc");
}

TEST(UnionTest, copyAssignThrowCreatesValueless) {
  struct X {
    X() = default;
    X(X const&) { std::terminate(); }
    X(X&&) = default;
    auto operator=(X const&) -> X& {
      std::terminate();
    }
    auto operator=(X&&) -> X& = default;
  };

  struct Y{};

  Union <X, Y> u1;
  ASSERT_FALSE(u1.valueless());
}

TEST(UnionTest, moveAssign) {
  using cds::impl::get;
  Union<int, String> u1;
  Union<int, String> u2 = 3;
  Union<int, String> u3 = "abc";
  u1 = cds::move(u2);
  ASSERT_TRUE(u1.is<int>());
  ASSERT_EQ(get<int>(u1), 3);
  u1 = cds::move(u3);
  ASSERT_TRUE(u1.is<String>());
  ASSERT_EQ(get<String>(u1), "abc");
}

TEST(UnionTest, moveAssignThrowCreatesValueless) {
  struct X {
    X() = default;
    X(X const&) = default;
    X(X&&) { std::terminate(); }
    auto operator=(X const&) -> X& = default;
    auto operator=(X&&) -> X& {
      std::terminate();
    }
  };

  struct Y{};

  Union <X, Y> u1;
  ASSERT_FALSE(u1.valueless());
}

TEST(UnionTest, ifIs) {
  Union<int, String> u1 = 3;
  u1.ifIs<int>([&](int v) {
    ASSERT_EQ(v, 3);
  });

  u1.ifIs<String>([&](CDS_ATTR(unused) String const&) {
    ASSERT_TRUE(false);
  });

  u1 = "abc";

  u1.ifIs<int>([&](CDS_ATTR(unused) int) {
    ASSERT_TRUE(false);
  });
  u1.ifIs<String>([&](String const& s) {
    ASSERT_EQ(s, "abc");
  });
  u1.ifIs<String>([&](StringView const s) {
    ASSERT_EQ(s, "abc");
  });

  u1.ifIs<String>([](String& s) {
    s = "bcd";
  });

  using cds::impl::get;
  ASSERT_EQ(get<String>(u1), "bcd");
  u1.ifIs<String>([&u1](CDS_ATTR(unused) StringView) {
    u1 = 5;
  });

  ASSERT_EQ(get<int>(u1), 5);
}
