// DCR-TEST
// STEPS: compile(linux:gcc;linux:clang;apple:clang;apple:gcc),run(linux:gcc;linux:clang;apple:clang;apple:gcc)
// STD: 11+

#include <cds/json/JSON>
#include "UnitTest.hpp"

#include <cds/collection/Vector>

namespace {
using namespace cds;
using namespace cds::json::impl;
} // namespace

TEST(JsonElementPresenterTest, exceptionFormat) {
  try {
    throw JsonPresentationFormulaException("test");
    ASSERT_TRUE(false);
  } catch (Exception const& e) {
    ASSERT_EQ("Invalid formula: 'test'", e.message());
  }
}

TEST(JsonElementPresenterTest, actionFor) {
  ASSERT_EQ(JsonElementPresenterAction::Key, actionFor("key"));
  ASSERT_EQ(JsonElementPresenterAction::Value, actionFor("value"));
  ASSERT_EQ(JsonElementPresenterAction::Index, actionFor("index"));
  try {
    actionFor("unknown");
    ASSERT_FALSE(true);
  } catch (Exception const& e) {
    ASSERT_EQ("Invalid formula: 'unknown'", e.message());
  }
}

TEST(JsonElementPresenterTest, presentationDataCtor) {
  auto pres1 = JsonElementPresentationData{"abc"};
  auto pres2 = JsonElementPresentationData{"${key}x${value}"};
  auto pres3 = JsonElementPresentationData{"y${key}x${value}"};
  auto pres4 = JsonElementPresentationData{"${key}x${value}z"};
  auto presAll = JsonElementPresentationData{"aaa${key}bbb${value}ccc${key}ddd${index}eee${value}fff${key}ggg"};

  ASSERT_EQ(Vector<StringView>{"abc"}, pres1.constants);
  ASSERT_EQ(Vector<JsonElementPresenterAction>{JsonElementPresenterAction::Constant}, pres1.actions);

  ASSERT_EQ(Vector<StringView>{"x"}, pres2.constants);
  ASSERT_EQ(Vector<JsonElementPresenterAction>({
      JsonElementPresenterAction::Key,
      JsonElementPresenterAction::Constant,
      JsonElementPresenterAction::Value,
  }), pres2.actions);

  ASSERT_EQ(Vector<StringView>({"y", "x"}), pres3.constants);
  ASSERT_EQ(Vector<JsonElementPresenterAction>({
      JsonElementPresenterAction::Constant,
      JsonElementPresenterAction::Key,
      JsonElementPresenterAction::Constant,
      JsonElementPresenterAction::Value,
  }), pres3.actions);

  ASSERT_EQ(Vector<StringView>({"x", "z"}), pres4.constants);
  ASSERT_EQ(Vector<JsonElementPresenterAction>({
      JsonElementPresenterAction::Key,
      JsonElementPresenterAction::Constant,
      JsonElementPresenterAction::Value,
      JsonElementPresenterAction::Constant,
  }), pres4.actions);

  ASSERT_EQ(Vector<StringView>({"aaa", "bbb", "ccc", "ddd", "eee", "fff", "ggg"}), presAll.constants);
  ASSERT_EQ(Vector<JsonElementPresenterAction>({
      JsonElementPresenterAction::Constant,
      JsonElementPresenterAction::Key,
      JsonElementPresenterAction::Constant,
      JsonElementPresenterAction::Value,
      JsonElementPresenterAction::Constant,
      JsonElementPresenterAction::Key,
      JsonElementPresenterAction::Constant,
      JsonElementPresenterAction::Index,
      JsonElementPresenterAction::Constant,
      JsonElementPresenterAction::Value,
      JsonElementPresenterAction::Constant,
      JsonElementPresenterAction::Key,
      JsonElementPresenterAction::Constant,
  }), presAll.actions);
}

TEST(JsonElementPresenterTest, presentationDataCtorThrows) {
  try {
    JsonElementPresentationData obj{"abc${test}cdef"};
    ASSERT_FALSE(true);
  } catch(Exception const& e) {
    ASSERT_EQ("Invalid formula: 'test'", e.message());
  }
}

TEST(JsonElementPresenterTest, ctrFromOptions) {
  auto options = JsonPrinterOptions{};
  options.arrayElementPresentation = "x${key}${value}z${index}t";
  options.objectEntryPresentation = "<${key}>${value}</${key}>";
  auto presenter = JsonElementPresenter{options};
  ASSERT_EQ(Vector<StringView>({"x", "z", "t"}), presenter.arrayPresentation.constants);
  ASSERT_EQ(Vector<JsonElementPresenterAction>({
      JsonElementPresenterAction::Constant,
      JsonElementPresenterAction::Key,
      JsonElementPresenterAction::Value,
      JsonElementPresenterAction::Constant,
      JsonElementPresenterAction::Index,
      JsonElementPresenterAction::Constant,
  }), presenter.arrayPresentation.actions);

  ASSERT_EQ(Vector<StringView>({"<", ">", "</", ">"}), presenter.objectPresentation.constants);
  ASSERT_EQ(Vector<JsonElementPresenterAction>({
      JsonElementPresenterAction::Constant,
      JsonElementPresenterAction::Key,
      JsonElementPresenterAction::Constant,
      JsonElementPresenterAction::Value,
      JsonElementPresenterAction::Constant,
      JsonElementPresenterAction::Key,
      JsonElementPresenterAction::Constant,
  }), presenter.objectPresentation.actions);
}

TEST(JsonElementPresenterTest, imbueAndPopKey) {
  auto options = JsonPrinterOptions{};
  options.arrayElementPresentation = "";
  options.objectEntryPresentation = "";
  auto presenter = JsonElementPresenter{options};
  ASSERT_TRUE(presenter.keyStore.empty());

  presenter.imbue("this-is-a-key");
  ASSERT_EQ(1, presenter.keyStore.size());
  ASSERT_EQ("this-is-a-key", presenter.keyStore.back());

  presenter.imbue("this-is-another-key");
  ASSERT_EQ(2, presenter.keyStore.size());
  ASSERT_EQ(Vector<StringView>({"this-is-a-key", "this-is-another-key"}), presenter.keyStore);

  presenter.popKey();
  ASSERT_EQ(1, presenter.keyStore.size());
  ASSERT_EQ("this-is-a-key", presenter.keyStore.back());
}

TEST(JsonElementPresenterTest, imbueIndex) {
  auto options = JsonPrinterOptions{};
  options.arrayElementPresentation = "";
  options.objectEntryPresentation = "";
  auto presenter = JsonElementPresenter{options};
  ASSERT_TRUE(presenter.indexStore.empty());

  presenter.imbue(3);
  ASSERT_EQ(1, presenter.indexStore.size());
  ASSERT_EQ(Vector<String>({"3"}), presenter.indexStore);

  presenter.imbue(5);
  ASSERT_EQ(2, presenter.indexStore.size());
  ASSERT_EQ(Vector<String>({"3", "5"}), presenter.indexStore);

  presenter.popIndex();
  ASSERT_EQ(1, presenter.indexStore.size());
  ASSERT_EQ("3", presenter.indexStore.back());
}

TEST(JsonElementPresenterTest, invoke) {
  auto options = JsonPrinterOptions{};
  options.arrayElementPresentation = "x${key}${value}z${index}t";
  options.objectEntryPresentation = "<${key}>${value}</${key}>";
  auto presenter = JsonElementPresenter{options};
  presenter.imbue("(a-key)");
  presenter.imbue(5);

  String output;
  JsonPrinterContext ctx{options};
  JsonPrinterOutput<String> printer{ctx, output};
  JsonNodeBase<> node = "this-is-a-test-node";

  presenter(presenter.arrayPresentation, printer, node, ctx);
  ASSERT_EQ("x(a-key)\"this-is-a-test-node\"z5t", output);

  output.clear();
  presenter(presenter.objectPresentation, printer, node, ctx);
  ASSERT_EQ("<(a-key)>\"this-is-a-test-node\"</(a-key)>", output);
}
