// DCR-TEST
// STEPS: compile(linux:gcc;linux:clang),run(linux:gcc;linux:clang)
// STD: 11+

#include <UnitTest.hpp>
#include <cds/Union>
#include <cds/String>
#include <cds/StringView>
#include <cds/Tuple>

namespace {
using cds::String;
using cds::StringView;

namespace internalValidation {
using cds::impl::UnionBestMatch;
using cds::meta::IsSame;
using cds::meta::impl::Pack;
using cds::impl::unionBestMatch::Best;
using cds::impl::unionBestMatch::IndexOf;
using cds::impl::IsUnionBestMatch;
using cds::impl::IdealUnionNodeBase;
using cds::impl::UnionNode;

static_assert(Best<String, Pack<String>>::IsIdeal::value, "valid");
static_assert(!Best<String, Pack<StringView>>::IsIdeal::value, "valid");
static_assert(!Best<String, Pack<int>>::IsIdeal::value, "valid");
static_assert(!Best<String, Pack<int, String>>::IsIdeal::value, "valid");
static_assert(Best<String, Pack<String, int>>::IsIdeal::value, "valid");

static_assert(Best<String, Pack<String>>::IsMatching::value, "valid");
static_assert(Best<String, Pack<StringView>>::IsMatching::value, "valid");
static_assert(Best<String, Pack<String, int>>::IsMatching::value, "valid");
static_assert(Best<String, Pack<StringView, int>>::IsMatching::value, "valid");
static_assert(!Best<String, Pack<int, String>>::IsMatching::value, "valid");
static_assert(!Best<String, Pack<int, StringView>>::IsMatching::value, "valid");

static_assert(Best<String, Pack<void, void>>::TIsIdeal<String>::value, "valid");
static_assert(!Best<String, Pack<void, void>>::TIsIdeal<int>::value, "valid");
static_assert(Best<int, Pack<void, void>>::TIsIdeal<int>::value, "valid");
static_assert(!Best<int, Pack<void, void>>::TIsIdeal<String>::value, "valid");
static_assert(Best<String, Pack<void, void>>::TIsIdeal<String>::value, "valid");

static_assert(Best<String, Pack<int, String>>::AnyIdealAhead::value, "valid");
static_assert(!Best<String, Pack<String, int>>::AnyIdealAhead::value, "valid");
static_assert(!Best<String, Pack<int, StringView>>::AnyIdealAhead::value, "valid");
static_assert(Best<String, Pack<int, StringView, String>>::AnyIdealAhead::value, "valid");

static_assert(IsSame<String, Best<String, Pack<int, StringView, String>>::Type>::value, "valid");
static_assert(IsSame<StringView, Best<StringView, Pack<int, StringView, String>>::Type>::value, "valid");
static_assert(IsSame<StringView, Best<std::string, Pack<int, StringView, String>>::Type>::value, "valid");
static_assert(IsSame<StringView, Best<char const*, Pack<int, StringView, String>>::Type>::value, "valid");
static_assert(IsSame<int, Best<float, Pack<int, StringView, String>>::Type>::value, "valid");

static_assert(IndexOf<int, int>::Type::value == 0u, "valid");
static_assert(IndexOf<int, int, String>::Type::value == 0u, "valid");
static_assert(IndexOf<String, int, String>::Type::value == 1u, "valid");

static_assert(IsUnionBestMatch<int, int, int, String>::value, "valid");
static_assert(IsUnionBestMatch<int, int&&, int, String>::value, "valid");

static_assert(IsSame<typename IdealUnionNodeBase<0, int, float>::Type, void>::value, "valid");
static_assert(IsSame<typename IdealUnionNodeBase<0, int, int>::Type, UnionNode<0u, int>>::value, "valid");
static_assert(IsSame<typename IdealUnionNodeBase<0, int, int, String>::Type, UnionNode<0u, int, String>>::value, "valid");
static_assert(IsSame<typename IdealUnionNodeBase<0, String, int, String>::Type, UnionNode<1u, String>>::value, "valid");

using cds::Size;
using cds::Union;
using cds::meta::Integral;
template <Size v> using SizeIntegral = Integral<Size, v>;

template <typename L, typename R> struct Max : SizeIntegral<L::value >= R::value ? L::value : R::value> {};

template <template <typename...> class F, typename...> struct Accumulate {};

template <template <typename...> class F, typename I, typename D> struct Accumulate<F, I, D> :
    F<I, D> {};

template <template <typename...> class F, typename I, typename... R> struct Accumulate<F, I, R...> :
    F<I, Accumulate<F, R...>> {};

template <typename... Ts> constexpr auto sizeValidation() noexcept -> Size {
  return sizeof(Union<Ts...>)
      == Accumulate<Max, SizeIntegral<sizeof(Ts)>..., SizeIntegral<alignof(Size)>>::value
          + SizeIntegral<sizeof(Size)>::value;
}

static_assert(sizeValidation<int>(), "valid");
static_assert(sizeValidation<int, int>(), "valid");
static_assert(sizeValidation<int, float>(), "valid");
static_assert(sizeValidation<int, String>(), "valid");
static_assert(sizeValidation<String>(), "valid");
static_assert(sizeValidation<String, int[512]>(), "valid");
} // namespace internalValidation

using cds::Union;

template <typename E, typename R> auto throws(R const& r, StringView message) -> bool {
  try {
    r();
    return false;
  } catch (E const& e) {
    return e.message() == message;
  }
}
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

  ASSERT_TRUE(throws<cds::UnionTypeException>(
      [&a1](){ cds::ignore = a1.get<String>(); },
      "Union Type Exception: 'String' is not the active Union member. Actual: 'signed int'"
  ));

  ASSERT_TRUE(throws<cds::UnionTypeException>(
      [&a2](){ cds::ignore = a2.get<int>(); },
      "Union Type Exception: 'signed int' is not the active Union member. Actual: 'String'"
  ));

  ASSERT_EQ(get<int>(a1), 3);
  ASSERT_EQ(get<String>(a2), "abc");

  ASSERT_TRUE(throws<cds::UnionTypeException>(
      [&a1](){ cds::ignore = get<String>(a1); },
      "Union Type Exception: 'String' is not the active Union member. Actual: 'signed int'"
  ));

  ASSERT_TRUE(throws<cds::UnionTypeException>(
      [&a2](){ cds::ignore = get<int>(a2); },
      "Union Type Exception: 'signed int' is not the active Union member. Actual: 'String'"
  ));
}

TEST(UnionTest, getMutate) {
  using cds::impl::sbo::StringData;
  ASSERT_EQ(sizeof(StringData<char>), 24);
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

  try {
    get<String>(a1) = "abc";
    ASSERT_TRUE(false);
  } catch (cds::UnionTypeException const& ex) {
    ASSERT_EQ(ex.message(), "Union Type Exception: 'String' is not the active Union member. Actual: 'signed int'");
  }
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

TEST(UnionTest, throwInCtorDefined) {
  struct X {
    X() = default;
    X(X const&) { throw cds::RuntimeException("intended"); }
    X(X&&) = default;
  };

  Union<int, X> const u1 = X{};
  try {
    auto const u2 = u1;
    ASSERT_TRUE(false);
  } catch (cds::Exception const& ex) {
    ASSERT_EQ(ex.message(), "intended");
  }
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
  ASSERT_FALSE(noexcept(u1 = "abc"));
}

TEST(UnionTest, assignThrowResultsInValueless) {
  struct X {
    X() = default;
    X(int) { throw cds::RuntimeException("expected"); }
    auto operator=(int) -> X& {
      throw cds::RuntimeException("expected");
    }
  };

  struct Y {};

  Union<X, Y> u1;
  ASSERT_FALSE(u1.valueless());
  u1 = X{};
  ASSERT_FALSE(u1.valueless());
  u1 = Y{};
  ASSERT_FALSE(u1.valueless());
  try {
    u1 = 3;
    ASSERT_TRUE(false);
  } catch (cds::Exception const& e) {
    ASSERT_EQ("expected", e.message());
  }

  ASSERT_TRUE(u1.valueless());
  u1 = X{};
  ASSERT_FALSE(u1.valueless());
  try {
    u1 = 3;
    ASSERT_TRUE(false);
  } catch (cds::Exception const& e) {
    ASSERT_EQ("expected", e.message());
  }
  ASSERT_TRUE(u1.valueless());
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
    X(int) { throw cds::RuntimeException("expected"); }
    auto operator=(int) -> X& {
      throw cds::RuntimeException("expected");
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
  try {
    u1.emplace<X>(1);
    ASSERT_TRUE(false);
  } catch (cds::Exception const& e) {
    ASSERT_EQ(e.message(), "expected");
  }

  ASSERT_TRUE(u1.valueless());
  u1.emplace<Y>();
  ASSERT_FALSE(u1.valueless());
  try {
    u1.emplace<X>(1);
    ASSERT_TRUE(false);
  } catch (cds::Exception const& e) {
    ASSERT_EQ(e.message(), "expected");
  }
  ASSERT_TRUE(u1.valueless());
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
    X(X const&) { throw cds::RuntimeException("expected"); }
    X(X&&) = default;
    auto operator=(X const&) -> X& {
      throw cds::RuntimeException("expected");
    }
    auto operator=(X&&) -> X& = default;
  };

  struct Y{};

  Union <X, Y> u1;
  ASSERT_FALSE(u1.valueless());
  try {
    auto const u2 = Union<X, Y>();
    u1 = u2;
    ASSERT_TRUE(false);
  } catch (cds::Exception const& ex) {
    ASSERT_EQ(ex.message(), "expected");
  }
  ASSERT_TRUE(u1.valueless());

  u1 = Union<X, Y>{Y{}};
  ASSERT_FALSE(u1.valueless());
  try {
    auto const u2 = Union<X, Y>();
    u1 = u2;
    ASSERT_TRUE(false);
  } catch (cds::Exception const& ex) {
    ASSERT_EQ(ex.message(), "expected");
  }
  ASSERT_TRUE(u1.valueless());
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
    X(X&&) { throw cds::RuntimeException("expected"); }
    auto operator=(X const&) -> X& = default;
    auto operator=(X&&) -> X& {
      throw cds::RuntimeException("expected");
    }
  };

  struct Y{};

  Union <X, Y> u1;
  ASSERT_FALSE(u1.valueless());
  try {
    auto u2 = Union<X, Y>();
    u1 = cds::move(u2);
    ASSERT_TRUE(false);
  } catch (cds::Exception const& ex) {
    ASSERT_EQ(ex.message(), "expected");
  }
  ASSERT_TRUE(u1.valueless());

  Union <X, Y> const u3 {Y{}};
  u1 = u3;
  ASSERT_FALSE(u1.valueless());
  try {
    auto u2 = Union<X, Y>();
    u1 = cds::move(u2);
    ASSERT_TRUE(false);
  } catch (cds::Exception const& ex) {
    ASSERT_EQ(ex.message(), "expected");
  }
  ASSERT_TRUE(u1.valueless());
}

TEST(UnionTest, ifIs) {
  Union<int, String> u1 = 3;
  u1.ifIs<int>([](int v) {
    ASSERT_EQ(v, 3);
  });

  u1.ifIs<String>([](CDS_ATTR(unused) String const&) {
    ASSERT_TRUE(false);
  });

  u1 = "abc";

  u1.ifIs<int>([](CDS_ATTR(unused) int) {
    ASSERT_TRUE(false);
  });
  u1.ifIs<String>([](String const& s) {
    ASSERT_EQ(s, "abc");
  });
  u1.ifIs<String>([](StringView const s) {
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
