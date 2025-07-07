// DCR-TEST
// STEPS: compile(linux:gcc;linux:clang;apple:clang;apple:gcc),run(linux:gcc;linux:clang;apple:clang;apple:gcc)
// STD: 11+

#include <cds/json/JSON>

#include "UnitTest.hpp"

namespace {
using cds::StringView;

using cds::json::JsonObject;

using cds::json::impl::JsonParseError;
using cds::json::impl::JsonParseOptions;

using cds::json::impl::parseJsonObject;
using cds::json::impl::parseJsonObjectMember;
} // namespace

TEST(JsonObjectParserTest, parseMemberKeyErr) {
  JsonObject obj;
  JsonParseOptions opt{};

  auto const res = parseJsonObjectMember(obj, StringView{R"("ab)"}, opt);

  ASSERT_EQ(JsonParseError::ErrorStringWithoutEndingQuote, cds::get<1>(res));
  ASSERT_EQ(R"("ab)", cds::get<0>(res));
}

TEST(JsonObjectParserTest, parseMemberSepErr) {
  JsonObject obj;
  JsonParseOptions opt{};

  auto const res = parseJsonObjectMember(obj, StringView{R"("a" "d")"}, opt);

  ASSERT_EQ(JsonParseError::ErrorObjectMemberWithoutKeyValueSeparator, cds::get<1>(res));
  ASSERT_EQ(R"("d")", cds::get<0>(res));
}

TEST(JsonObjectParserTest, parseMemberValErr) {
  JsonObject obj;
  JsonParseOptions opt{};

  auto const res = parseJsonObjectMember(obj, StringView{R"("a" : test)"}, opt);

  ASSERT_EQ(JsonParseError::ErrorValueInvalid, cds::get<1>(res));
  ASSERT_EQ(R"(test)", cds::get<0>(res));
}

TEST(JsonObjectParserTest, parseMemberValid) {
  JsonObject obj;
  JsonParseOptions opt{};

  auto const res = parseJsonObjectMember(obj, StringView{R"("a" : 54, "b": 53)"}, opt);

  ASSERT_EQ(JsonParseError::None, cds::get<1>(res));
  ASSERT_EQ(R"(, "b": 53)", cds::get<0>(res));
  ASSERT_EQ(1, obj.size());
  ASSERT_EQ(54, obj["a"]);
}

TEST(JsonObjectParserTest, parseObjectErrNoBrace) {
  JsonObject obj;
  JsonParseOptions opt{};

  auto const res = parseJsonObject(obj, StringView{R"(test)"}, opt);

  ASSERT_EQ(JsonParseError::ErrorObjectWithoutStartingBrace, cds::get<1>(res));
  ASSERT_EQ(R"(test)", cds::get<0>(res));
}

TEST(JsonObjectParserTest, parseObjectErrNoContentAfterBrace) {
  JsonObject obj;
  JsonParseOptions opt{};

  auto const res = parseJsonObject(obj, StringView{R"({ )"}, opt);

  ASSERT_EQ(JsonParseError::ErrorObjectWithoutEndingBrace, cds::get<1>(res));
  ASSERT_EQ(R"()", cds::get<0>(res));
}

TEST(JsonObjectParserTest, parseObjectEmpty) {
  JsonObject obj;
  JsonParseOptions opt{};

  auto const res = parseJsonObject(obj, StringView{R"({  }ab)"}, opt);

  ASSERT_EQ(JsonParseError::None, cds::get<1>(res));
  ASSERT_EQ(R"(ab)", cds::get<0>(res));

  ASSERT_TRUE(obj.empty());
}

TEST(JsonObjectParserTest, parseObjectErrFirstMember) {
  JsonObject obj;
  JsonParseOptions opt{};

  auto const res = parseJsonObject(obj, StringView{R"({"a" "d")"}, opt);

  ASSERT_EQ(JsonParseError::ErrorObjectMemberWithoutKeyValueSeparator, cds::get<1>(res));
  ASSERT_EQ(R"("d")", cds::get<0>(res));

  ASSERT_TRUE(obj.empty());
}

TEST(JsonObjectParserTest, parseObjectErrNoSep) {
  JsonObject obj;
  JsonParseOptions opt{};

  auto const res = parseJsonObject(obj, StringView{R"({"a": 123 "b": 456)"}, opt);

  ASSERT_EQ(JsonParseError::ErrorObjectWithoutMemberSeparator, cds::get<1>(res));
  ASSERT_EQ(R"("b": 456)", cds::get<0>(res));
}

TEST(JsonObjectParserTest, parseObjectErrNotTerm0) {
  JsonObject obj;
  JsonParseOptions opt{};

  auto const res = parseJsonObject(obj, StringView{R"({"a": 123,)"}, opt);

  ASSERT_EQ(JsonParseError::ErrorObjectWithoutEndingBrace, cds::get<1>(res));
  ASSERT_EQ(R"()", cds::get<0>(res));
}

TEST(JsonObjectParserTest, parseObjectErrNotTerm1) {
  JsonObject obj;
  JsonParseOptions opt{};

  auto const res = parseJsonObject(obj, StringView{R"({"a": 123, "b": 456)"}, opt);

  ASSERT_EQ(JsonParseError::ErrorObjectWithoutEndingBrace, cds::get<1>(res));
  ASSERT_EQ(R"()", cds::get<0>(res));
}

TEST(JsonObjectParserTest, parseObjectErrNextMem) {
  JsonObject obj;
  JsonParseOptions opt{};

  auto const res = parseJsonObject(obj, StringView{R"({"a": 123, "b" 456)"}, opt);

  ASSERT_EQ(JsonParseError::ErrorObjectMemberWithoutKeyValueSeparator, cds::get<1>(res));
  ASSERT_EQ(R"(456)", cds::get<0>(res));
}

TEST(JsonObjectParserTest, parseObjectValid) {
  JsonObject obj;
  JsonParseOptions opt{};

  auto const res = parseJsonObject(obj, StringView{R"({"a": 123, "b": false, "c": "abc"}xy)"}, opt);

  ASSERT_EQ(JsonParseError::None, cds::get<1>(res));
  ASSERT_EQ(R"(xy)", cds::get<0>(res));
  ASSERT_EQ(3, obj.size());
  ASSERT_EQ(123, obj["a"]);
  ASSERT_EQ(false, obj["b"]);
  ASSERT_EQ("abc", obj["c"]);
}
