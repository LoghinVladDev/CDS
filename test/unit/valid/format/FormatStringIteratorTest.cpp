// DCR-TEST
// STEPS: compile(linux:gcc;linux:clang;apple:clang;apple:gcc),run(linux:gcc;linux:clang;apple:clang;apple:gcc)
// STD: 11+

#include "UnitTest.hpp"
#include <cds/Format>
#include <cds/String>
#include <cds/StringView>
#include <cds/Union>
#include <cds/collection/Vector>
#include <cds/exception/FormatException>
#include "../Shared.hpp"

namespace {
using testing::citeq;

using cds::FormatException;
using cds::StringView;
using cds::Union;
using cds::Vector;

using cds::ignore;
using cds::meta::visitors;

using ST = cds::impl::StringTraits<char>;
using SU = cds::impl::StringUtils<char, ST>;

using FmtTok = cds::impl::fmt::FormatStringToken<char, SU>;
using FmtRn = cds::impl::fmt::FormatStringTokenRange<char, SU>;
} // namespace

TEST(FormatStringIteratorTest, init) {
  using V = Union<StringView, FmtTok>;
  ASSERT_TRUE(citeq(FmtRn("{}"), Vector<V>{"", FmtTok{"", 0}}));
  ASSERT_TRUE(citeq(FmtRn(" {}"), Vector<V>{" ", FmtTok{"", 0}}));
  ASSERT_TRUE(citeq(FmtRn("{} "), Vector<V>{"", FmtTok{"", 0}, " "}));
  ASSERT_TRUE(citeq(FmtRn(" { } "), Vector<V>{" ", FmtTok{" ", 0}, " "}));
  ASSERT_TRUE(citeq(FmtRn("{ }"), Vector<V>{"", FmtTok{" ", 0}}));
  ASSERT_TRUE(citeq(FmtRn("{}{}"), Vector<V>{"", FmtTok{"", 0}, "", FmtTok{"", 1}}));
  ASSERT_TRUE(citeq(FmtRn("{{}}"), Vector<V>{"{{}}"}));
  ASSERT_TRUE(citeq(FmtRn("{ {}}"), Vector<V>{"", FmtTok{" {}", 0}}));
  ASSERT_TRUE(citeq(FmtRn("{ {} }"), Vector<V>{"", FmtTok{" {} ", 0}}));
  ASSERT_TRUE(citeq(FmtRn("{:}"), Vector<V>{"", FmtTok{"", 0}}));
  ASSERT_TRUE(citeq(FmtRn("{ :}"), Vector<V>{"", FmtTok{"", 0}}));
  ASSERT_TRUE(citeq(FmtRn("{ : }"), Vector<V>{"", FmtTok{" ", 0}}));
  ASSERT_TRUE(citeq(FmtRn("{1: }"), Vector<V>{"", FmtTok{" ", 1}}));
  ASSERT_TRUE(citeq(FmtRn("{ 1: }"), Vector<V>{"", FmtTok{" ", 1}}));
  ASSERT_TRUE(citeq(FmtRn("{ 1 : }"), Vector<V>{"", FmtTok{" ", 1}}));
  ASSERT_TRUE(citeq(FmtRn("{2:}{0:}"), Vector<V>{"", FmtTok{"", 2}, "", FmtTok{"", 0}}));
  ASSERT_TRUE(citeq(FmtRn("{2}{0}"), Vector<V>{"", FmtTok{"", 2}, "", FmtTok{"", 0}}));
  ASSERT_TRUE(citeq(FmtRn("{::}"), Vector<V>{"", FmtTok{":", 0}}));
}

TEST(FormatStringIteratorTest, addressAccess) {
  auto rn = FmtRn("ab{0}cd{0}ef");
  auto it = rn.begin();
  unsigned plainTextCount = 0;
  unsigned tokenCount = 0;
  for (auto end = rn.end(); it != end; ++it) {
    if (it->visit(visitors(
        [](StringView) { return true; },
        [](FmtTok) { return false; }
    ))) {
      ++plainTextCount;
    } else {
      ++tokenCount;
    }
  }
  ASSERT_EQ(3u, plainTextCount);
  ASSERT_EQ(2u, tokenCount);
}

TEST(FormatStringIteratorTest, implicitArgIdx) {
  auto rn = FmtRn("ab{}cd{}ef");
  auto it = rn.begin();
  bool implicit = false;
  for (auto end = rn.end(); it != end; ++it) {
    implicit = it.usesImplicitArgumentIndexing();
  }
  ASSERT_TRUE(implicit);
}

TEST(FormatStringIteratorTest, explicitArgIdx) {
  auto rn = FmtRn("ab{0}cd{0}ef");
  auto it = rn.begin();
  bool explicitIdx = false;
  for (auto end = rn.end(); it != end; ++it) {
    explicitIdx = it.usesExplicitArgumentIndexing();
  }
  ASSERT_TRUE(explicitIdx);
}

TEST(FormatStringIteratorTest, unescapedRBrace) {
  try {
    auto rn = FmtRn{"}ab"};
    auto b = rn.begin();
    for (auto e = rn.end(); b != e; ++b) {
      ignore = b;
    }
    ASSERT_TRUE(false);
  } catch (FormatException const& e) {
    ASSERT_EQ("Right brace encountered without an open left brace", e.message());
  }

  try {
    auto rn = FmtRn{"}"};
    auto b = rn.begin();
    for (auto e = rn.end(); b != e; ++b) {
      ignore = b;
    }
    ASSERT_TRUE(false);
  } catch (FormatException const& e) {
    ASSERT_EQ("Right brace encountered without an open left brace", e.message());
  }

  try {
    auto rn = FmtRn{"ab}"};
    auto b = rn.begin();
    for (auto e = rn.end(); b != e; ++b) {
      ignore = b;
    }
    ASSERT_TRUE(false);
  } catch (FormatException const& e) {
    ASSERT_EQ("Right brace encountered without an open left brace", e.message());
  }
}

TEST(FormatStringIteratorTest, indexTypeMix) {
  try {
    auto rn = FmtRn{"{}{0}"};
    auto b = rn.begin();
    for (auto e = rn.end(); b != e; ++b) {
      ignore = b;
    }
    ASSERT_TRUE(false);
  } catch (FormatException const& e) {
    ASSERT_EQ("Explicit argument indexing requires all arguments to be indexed", e.message());
  }

  try {
    auto rn = FmtRn{"{0}{}"};
    auto b = rn.begin();
    for (auto e = rn.end(); b != e; ++b) {
      ignore = b;
    }
    ASSERT_TRUE(false);
  } catch (FormatException const& e) {
    ASSERT_EQ("Explicit argument indexing requires all arguments to be indexed", e.message());
  }
}