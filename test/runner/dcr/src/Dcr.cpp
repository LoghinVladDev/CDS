//
// Created by loghin on 12/1/23.
//

#include "Dcr.hpp"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <vector>
#include <functional>
#include <memory>
#include <optional>
#include <unordered_map>
#include <utility>
#include <bits/ranges_algo.h>
#include <sys/wait.h>

namespace dcr {
namespace {
std::function alwaysAccept = [](std::string const&) { return true; };
std::function alwaysReject = [](std::string const&) { return false; };

class ArgParser {
public:
  using Accepter = std::function<void(std::vector<std::string> const&)>;
  using Filter = std::function<bool(std::string const&)>;

  template <typename A, typename F>
  ArgParser(
      A&& accepter,
      F&& filters
  ): _accepter(std::forward<A>(accepter)), _filters(std::forward<F>(filters)) {}

  [[nodiscard]] auto filter(int const idx) const -> Filter const& {
    if (idx >= _filters.size()) {
      return _sink;
    }

    return _filters[idx];
  }

  [[nodiscard]] auto filterCount() const {
    return _filters.size();
  }

  auto accept(std::vector<std::string> const& args) const {
    _accepter(args);
  }

  [[nodiscard]] auto isSink() const {
    return _isSink;
  }

  auto withSink(Filter const& filter) {
    _isSink = true;
    _sink = filter;
  }

  Accepter _accepter;
  std::vector<Filter> _filters;
  Filter _sink = alwaysReject;
  bool _isSink = false;
};

auto makeParser(ArgParser::Accepter&& accepter, std::vector<ArgParser::Filter>&& filters) {
  return std::make_unique<ArgParser>(std::move(accepter), std::move(filters));
}

template <typename... Filters>
auto makeParser(ArgParser::Accepter&& accepter, Filters&&... filters) {
  return makeParser(std::move(accepter), {std::forward<Filters>(filters)...});
}

auto makeParserWithSink(ArgParser::Accepter&& accepter, ArgParser::Filter const& sink, std::vector<ArgParser::Filter>&& filters) {
  auto parser = std::make_unique<ArgParser>(std::move(accepter), std::move(filters));
  parser->withSink(sink);
  return parser;
}

template <typename... Filters>
auto makeParserWithSink(ArgParser::Accepter&& accepter, ArgParser::Filter const& sink, Filters&&... filters) {
  return makeParserWithSink(std::move(accepter), sink, {std::forward<Filters>(filters)...});
}

auto argParse(std::vector<std::string> const& args, std::vector<std::unique_ptr<ArgParser>> const& argParsers) {
  std::vector<ArgParser const*> acceptedParsers;
  auto advance = 0;
  for (auto argIdx = 0; argIdx < args.size(); argIdx += advance) {
    for (auto const& parser: argParsers) {
      if (std::ranges::find_if(acceptedParsers, [&parser](auto const* accepted){ return accepted == parser.get(); }) != acceptedParsers.end()) {
        continue;
      }

      auto filterIdx = 0;
      auto lookaheadArgIdx = argIdx;
      while (lookaheadArgIdx < args.size() && parser->filter(filterIdx)(args[lookaheadArgIdx])) {
        ++filterIdx;
        ++lookaheadArgIdx;
      }

      if (filterIdx == parser->filterCount() || parser->isSink()) {
        parser->accept({&args[argIdx], &args[lookaheadArgIdx]});
        advance = filterIdx;
        acceptedParsers.push_back(parser.get());
        break;
      }
    }

    if (advance == 0) {
      std::cerr << "Invalid Argument: " << args[argIdx];
      break;
    }
  }
}

template <typename A, typename Last>
auto pushMove(A& a, Last&& last) {
  a.push_back(std::forward<Last>(last));
}

template <typename A, typename First, typename... Remaining>
auto pushMove(A& a, First&& last, Remaining&&... remaining) {
  a.push_back(std::forward<First>(last));
  pushMove(a, std::forward<Remaining>(remaining)...);
}

template <typename... ArgParsers>
auto argParse(std::vector<std::string> const& args, ArgParsers&&... parsers) {
  std::vector<std::unique_ptr<ArgParser>> parserArray;
  pushMove(parserArray, std::forward<ArgParsers>(parsers)...);
  return argParse(args, std::as_const(parserArray));
}

auto locateTestsRecursively(std::string const& dirPath) {
  std::vector<std::string> filePaths;
  for (auto const& dirEntry: std::filesystem::recursive_directory_iterator(dirPath)) {
    if (auto const& path = dirEntry.path(); is_regular_file(path) && path.extension() == ".cpp") {
      filePaths.push_back(path);
    }
  }

  return filePaths;
}

auto locateTests(std::string const& fileOrPath) -> std::vector<std::string> {
  if (std::filesystem::is_directory(fileOrPath)) {
    return locateTestsRecursively(fileOrPath);
  }

  if (std::filesystem::is_regular_file(fileOrPath)) {
    return {&fileOrPath, &fileOrPath + 1};
  }

  std::cerr << "Path '" << fileOrPath << "' is not a file or directory\n";
  return {};
}

enum class TestStepType {Compile, Run};
enum class TestStepResult {Success, Failure};
enum class Standard {Cpp11, Cpp14, Cpp17, Cpp20, Cpp23, Cpp2c, Highest=Cpp23, End};

struct TestStep {
  TestStepType type;
  TestStepResult result;
};

struct StandardRange {
  Standard begin;
  std::optional<Standard> end;
};

struct TestData {
  std::string path;
  std::vector<TestStep> steps;
  StandardRange standard;
};

using namespace std::string_view_literals;
constexpr auto headerPrefixStd = "STD: "sv;
constexpr auto headerPrefixSteps = "STEPS: "sv;
constexpr auto headerPrefixExpected = "EXPECTED"sv;
std::unordered_map<std::string_view, Standard> const standardMap = {
    {"11", Standard::Cpp11},
    {"1a", Standard::Cpp11},
    {"14", Standard::Cpp14},
    {"1b", Standard::Cpp14},
    {"17", Standard::Cpp17},
    {"1c", Standard::Cpp17},
    {"20", Standard::Cpp20},
    {"2a", Standard::Cpp20},
    {"23", Standard::Cpp23},
    {"2b", Standard::Cpp23},
    {"2c", Standard::Cpp2c},
};

std::unordered_map<std::string_view, TestStepType> const stepTypeMap = {
    {"compile", TestStepType::Compile},
    {"run", TestStepType::Run}
};

std::unordered_map<std::string_view, TestStepResult> const expectationMap = {
    {"success", TestStepResult::Success},
    {"failure", TestStepResult::Failure}
};

auto trim(std::string_view const str) -> std::string_view {
  const auto whIdx = str.find_first_of(" \t\n\r");
  auto const trimmedFront = str.substr(whIdx == std::string_view::npos ? 0 : whIdx);
  auto const trimmed = trimmedFront.substr(0, trimmedFront.find_last_of(" \t\n\r"));
  return trimmed;
}

auto standard(std::string_view const versionString) -> std::optional<Standard> {
  if (auto const stdIt = standardMap.find(trim(versionString)); stdIt != standardMap.end()) {
    return {stdIt->second};
  }
  return std::nullopt;
}

auto expected(std::string_view const resultString) -> std::optional<TestStepResult> {
  if (auto const resultIt = expectationMap.find(trim(resultString)); resultIt != expectationMap.end()) {
    return {resultIt->second};
  }
  return std::nullopt;
}

auto parseStepTypes(std::string_view stepTypes) -> std::optional<std::vector<TestStepType>> {
  std::vector<TestStepType> steps;
  stepTypes = trim(stepTypes);
  while (!stepTypes.empty()) {
    auto const idxOfComma = stepTypes.find(',');
    auto const current = stepTypes.substr(0, idxOfComma);
    stepTypes = idxOfComma == std::string_view::npos ? "" : stepTypes.substr(idxOfComma + 1);
    if (auto const stepIt = stepTypeMap.find(current); stepIt == stepTypeMap.end()) {
      return std::nullopt;
    } else {
      steps.push_back(stepIt->second);
    }
  }

  return {steps};
}

auto parseStandard(std::string_view const standardString) -> std::optional<StandardRange> {
  if (auto const fromUntilRangeIdPos = standardString.find('-'); fromUntilRangeIdPos != std::string_view::npos) {
    auto const begin = standard(standardString.substr(0, fromUntilRangeIdPos));
    auto const end = standard(standardString.substr(fromUntilRangeIdPos + 1));

    if (!begin || !end) {
      return std::nullopt;
    }

    return {{*begin, end}};
  }

  if (auto const fromRangeIdPos = standardString.find('+'); fromRangeIdPos != std::string_view::npos) {
    auto const begin = standard(standardString.substr(0, fromRangeIdPos));
    if (!begin) {
      return std::nullopt;
    }

    return {{*begin, std::nullopt}};
  }

  auto const singleVersion = standard(standardString);
  if (!singleVersion) {
    return std::nullopt;
  }

  return {{*singleVersion, singleVersion}};
}

auto parseAndAdjustSteps(std::vector<TestStep>& steps, std::string_view stepsAndExpectedString) {
  if (!stepsAndExpectedString.starts_with('[')) {
    std::cout << "Expected '[' after EXPECTED\n";
    return;
  }

  stepsAndExpectedString = stepsAndExpectedString.substr(1);
  auto const brIdx = stepsAndExpectedString.find("]: ");
  if (brIdx == std::string_view::npos) {
    std::cout << "Expected ']: ' after EXPECTED[<steps>\n";
    return;
  }

  auto const stepsString = stepsAndExpectedString.substr(brIdx);
  auto const stepTypes = parseStepTypes(stepsString);
  if (!stepTypes) {
    std::cout << "Warning: Invalid step types '" << stepsString << "'\n";
  }

  auto const expectedString = stepsAndExpectedString.substr(brIdx + "]: "sv.length());
  auto const result = expected(expectedString);
  if (!result) {
    std::cout << "Warning: Invalid expectation '" << expectedString << "'\n";
  }

  for (auto& [type, stepResult]: steps) {
    if (std::ranges::find(*stepTypes, type) != stepTypes->end()) {
      stepResult = *result;
    }
  }
}

auto processTestHeader(std::string const& path) -> std::optional<TestData> {
  std::ifstream testFile(path);
  std::vector<TestStep> steps;
  StandardRange standard {.begin = Standard::Cpp11};

  std::ifstream file(path);
  std::string line;
  bool isDcrTest = false;
  while (std::getline(file, line)) {
    if (!line.starts_with("// ")) {
      break;
    }

    if (auto const headerItem = std::string_view(line).substr(3); headerItem.starts_with("DCR-TEST")) {
      isDcrTest = true;
    } else if (headerItem.starts_with(headerPrefixStd)) {
      auto const standardString = headerItem.substr(headerPrefixStd.length());
      if (auto const newStandard = parseStandard(standardString); !newStandard) {
        std::cout << "Warning in '" << path << "': Invalid Standard '" << standardString << "'\n";
      } else {
        standard = *newStandard;
      }
    } else if (headerItem.starts_with(headerPrefixSteps)) {
      auto const stepString = headerItem.substr(headerPrefixSteps.length());
      if (auto const stepTypes = parseStepTypes(stepString); !stepTypes) {
        std::cout << "Warning in '" << path << "': Invalid Step Types '" << stepString << "'\n";
      } else {
        std::ranges::for_each(*stepTypes, [&steps](auto const type) { steps.emplace_back(type, TestStepResult::Success); });
      }
    } else if (headerItem.starts_with(headerPrefixExpected)) {
      parseAndAdjustSteps(steps, headerItem.substr(headerPrefixExpected.length()));
    }
  }

  if (!isDcrTest) {
    return {};
  }

  return {{.path = path, .steps = std::move(steps), .standard = standard}};
}

auto processTests(std::vector<std::string> const& paths) {
  std::vector<TestData> tests;

  for (auto const& path: paths) {
    if (auto const data = processTestHeader(path)) {
      tests.push_back(*data);
    }
  }

  return tests;
}

enum class ExecutionPolicy {
  Sequential
};

std::vector const allStandardsArray =
  {Standard::Cpp11, Standard::Cpp14, Standard::Cpp17, Standard::Cpp20, Standard::Cpp23, Standard::Cpp2c, Standard::End};
auto stdRange(StandardRange range) {
  if (!range.end) {
    range.end = Standard::Highest;
  }

  return std::vector(std::ranges::find(allStandardsArray, range.begin), std::ranges::find(allStandardsArray, range.end) + 1);
}

auto toString(Standard std) {
  switch(std) {
    case Standard::Cpp11: return "11";
    case Standard::Cpp14: return "14";
    case Standard::Cpp17: return "17";
    case Standard::Cpp20: return "20";
    case Standard::Cpp23: return "2b";
    case Standard::Cpp2c: return "2c";
    default:
      return "";
  }
}

auto executablePath(std::string const& src, Standard standard) {
  auto const extensionIdx = src.rfind('.');
  return src.substr(0, extensionIdx) + "_" + toString(standard) + ".bin";
}

auto awaitProcess(std::string executable, std::vector<std::string>& args) {
  std::stringstream oss;
  oss
      << "[DEBUG] - " << executable;
  std::ranges::for_each(args, [&oss](auto const& s) { oss << " " << s; });
  std::cout << oss.str() << "\n";

  std::vector<char*> cArgs;
  cArgs.emplace_back(executable.data());
  std::ranges::for_each(args, [&cArgs](std::string& s) { cArgs.emplace_back(s.data()); });
  cArgs.emplace_back(nullptr);

  if (pid_t const childId = fork(); childId == 0) {
    if (-1 == execvp(executable.c_str(), cArgs.data())) {
      exit(2);
    }
    [[unlikely]]
    exit(3);
  } else if (childId < 0) {
    std::cerr << "Unknown error\n";
    return false;
  } else {
    int stat;
    waitpid(childId, &stat, 0);
    return WEXITSTATUS(stat) == 0;
  }
}

auto executeCompile(std::string const& path, Standard standard, std::vector<std::string> const& extraArgs) {
  std::vector<std::string> fullArgs = extraArgs;
  fullArgs.push_back(path);
  fullArgs.emplace_back("-o");
  fullArgs.push_back(executablePath(path, standard));

  awaitProcess("clang++", fullArgs);

  return true;
}

auto executeRun(std::string const& path, Standard standard) {
  auto const& execPath = executablePath(path, standard);
  return true;
}

auto executeSequentially(std::vector<TestData> const& tests, std::vector<std::string> const& passToCompiler) -> int {
  int skipped = 0;
  int successful = 0;
  int total = 0;

  auto const stepType = [](TestStep const& t) { return t.type; };
  std::vector<TestData> withoutInvalid;
  for (auto const& tData: tests) {
    if (!(!std::ranges::contains(tData.steps, TestStepType::Compile, stepType)
        && std::ranges::contains(tData.steps, TestStepType::Run, stepType))) {
      withoutInvalid.push_back(tData);
    }
  }

  for (const auto& [_, steps, standard]: withoutInvalid) {
    total += static_cast<int>(steps.size() * stdRange(standard).size());
  }

  std::vector<std::string> failedTestPaths;
  using namespace std::string_literals;
  auto const dcrPath = "../test/runner/dcr"s; // TODO: change this later
  std::vector<std::string> compilerArgs = passToCompiler;
  compilerArgs.emplace_back(dcrPath + "/src/DCRMain.cpp");
  compilerArgs.emplace_back(dcrPath + "/src/Test.cpp");

  for (auto const& [path, steps, standard]: withoutInvalid) {
    for (auto const& std: stdRange(standard)) {
      std::vector<std::string> withStd = compilerArgs;
      withStd.push_back("-std=c++"s + toString(std));
      bool result = false;
      if (std::ranges::contains(steps, TestStepType::Compile, stepType)) {
        result = executeCompile(path, std, withStd);
      }

      if (result) {
        ++successful;
      } else {
        failedTestPaths.emplace_back("compile " + path);
      }

      if (std::ranges::contains(steps, TestStepType::Run, stepType)) {
        if (!result) {
          ++ skipped;
        } else {
          result = executeRun(path, std);

          if (result) {
            ++successful;
          } else {
            failedTestPaths.emplace_back("run " + path);
          }
        }
      }
    }
  }

  std::cout << total << " tests ran, out of which " << successful << " were successful, " << skipped << " were skipped, and the following " << (total - successful - skipped) << " failed:\n";
  for (auto const& testPath: failedTestPaths) {
    std::cout << "  " << testPath << '\n';
  }

  return total == skipped + successful;
}

auto execute(ExecutionPolicy, std::vector<TestData> const& tests, std::vector<std::string> const& passToCompiler) -> int {
  return executeSequentially(tests, passToCompiler);
}
} // namespace

auto run(int const argc, char const* const* argv) -> int {
  if (argc == 1) {
    std::cerr << "No path/file provided to DCR test runner\n";
    return 1;
  }

  std::string inputFileOrDir;
  std::vector<std::string> passedToCompiler;
  argParse(
      {&argv[1], &argv[argc]},
      makeParser(
          [&inputFileOrDir](auto const& args) { inputFileOrDir = args[0]; },
          [](auto const&) { return true; }
      ),
      makeParserWithSink(
          [&passedToCompiler](auto const& args) { passedToCompiler = {&args[1], &args[args.size()]}; },
          alwaysAccept,
          [](auto const& arg) { return arg == "--"; }
      )
  );

  auto const testPaths = locateTests(inputFileOrDir);
  if (testPaths.empty()) {
    std::cout << "No tests found at given path '" << inputFileOrDir << "'\n";
    return 1;
  }

  auto const tests = processTests(testPaths);
  return execute(ExecutionPolicy::Sequential, tests, passedToCompiler);
}
} // namespace dcr
