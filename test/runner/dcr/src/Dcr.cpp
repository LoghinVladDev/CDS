//
// Created by loghin on 12/1/23.
//

#include "Dcr.hpp"

#include <algorithm>
#include <atomic>
#include <cassert>
#include <charconv>
#include <cxxabi.h>
#include <filesystem>
#include <fstream>
#include <functional>
#include <iostream>
#include <memory>
#include <mutex>
#include <optional>
#include <source_location>
#include <sstream>
#include <thread>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <variant>
#include <vector>

#include <sys/wait.h>
#include <unistd.h>

#if defined(__APPLE__)
extern char** environ;

int execvpe(const char* name, char* const* const argv, char* const* const envv) {
  // std::ignore = envv;
  // return execvp(name, argv);
  return execve(name, argv, envv);
}
#endif

namespace {
class expanded_string : public std::string {
public:
  using std::string::string;
  using std::string::operator=;

  [[nodiscard]] constexpr auto starts_with(char value) const noexcept -> bool {
    return !empty() && front() == value;
  }

  template <size_t n> [[nodiscard]] constexpr auto starts_with(char const (&str)[n]) const noexcept -> bool {
    return size() >= n - 1 && std::char_traits<char>::compare(c_str(), str, n - 1) == 0;
  }

  [[nodiscard]] constexpr auto starts_with(std::string_view const& sv) const noexcept -> bool {
    return size() >= sv.size() && std::char_traits<char>::compare(c_str(), sv.data(), sv.size()) == 0;
  }
};

class expanded_string_view : public std::string_view {
public:
  using std::string_view::string_view;
  using std::string_view::operator=;

  constexpr expanded_string_view(expanded_string const& str) noexcept : std::string_view{str} {}
  constexpr expanded_string_view(std::string_view const& str) noexcept : std::string_view{str} {}

  template <typename... Args> [[nodiscard]] constexpr auto substr(Args&&... args) const noexcept -> expanded_string_view {
    return expanded_string_view{std::string_view::substr(std::forward<Args>(args)...)};
  }

  [[nodiscard]] constexpr auto starts_with(char value) const noexcept -> bool {
    return !empty() && front() == value;
  }

  template <size_t n> [[nodiscard]] constexpr auto starts_with(char const (&str)[n]) const noexcept -> bool {
    return size() >= n - 1 && std::char_traits<char>::compare(data(), str, n - 1) == 0;
  }

  [[nodiscard]] constexpr auto starts_with(std::string_view const& sv) const noexcept -> bool {
    return size() >= sv.size() && std::char_traits<char>::compare(data(), sv.data(), sv.size()) == 0;
  }
};

class jthread : public std::thread {
public:
  using std::thread::thread;
  ~jthread() noexcept {
    join();
  }
};
}

namespace dcr {
namespace {
struct DcrParams {
  bool verbose;
  bool coverage;
  bool release;
  int threadCount;
};

std::function const alwaysAccept = [](std::string const&) { return true; };
std::function const alwaysReject = [](std::string const&) { return false; };

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
  auto advance = 0u;
  for (auto argIdx = 0u; argIdx < args.size(); argIdx += advance) {
    for (auto const& parser: argParsers) {
      if (
        std::find_if(
            acceptedParsers.begin(),
            acceptedParsers.end(),
            [&parser](auto const* accepted){ return accepted == parser.get(); }
        ) != acceptedParsers.end()
      ) {
        continue;
      }

      auto filterIdx = 0u;
      auto lookaheadArgIdx = argIdx;
      while (lookaheadArgIdx < args.size() && parser->filter(filterIdx)(args[lookaheadArgIdx])) {
        ++filterIdx;
        ++lookaheadArgIdx;
      }

      if (filterIdx == parser->filterCount() || (parser->isSink() && filterIdx > 0u)) {
        parser->accept({args.begin() + argIdx, args.end()});
        advance = filterIdx;
        acceptedParsers.push_back(parser.get());
        break;
      }
    }

    if (advance == 0u) {
      std::cerr << "Invalid Argument: " << args[argIdx];
      break;
    }
  }
}

template <typename... ArgParsers>
auto argParse(std::vector<std::string> const& args, ArgParsers&&... parsers) {
  std::vector<std::unique_ptr<ArgParser>> parserArray;
  (parserArray.push_back(std::forward<ArgParsers>(parsers)), ...);
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

auto locateTests(std::vector<std::filesystem::path>&& fileOrPaths) -> std::vector<std::string> {
  std::vector<std::string> resolvedPaths;
  for (auto&& fileOrPath : fileOrPaths) {
    if (std::filesystem::is_directory(fileOrPath)) {
      for (auto&& path : locateTestsRecursively(fileOrPath)) {
        resolvedPaths.emplace_back(std::move(path));
      }
    } else if (std::filesystem::is_regular_file(fileOrPath)) {
      resolvedPaths.emplace_back(std::move(fileOrPath));
    } else {
      std::cerr << "Path '" << fileOrPath << "' is not a file or directory\n";
      return {};
    }
  }

  fileOrPaths.clear();
  return resolvedPaths;
}

enum class TestStepType : std::uint8_t {Compile, Run};
enum class TestStepResult : std::uint8_t {Success, Failure};
enum class TestStepPlatform : std::uint8_t {Linux, MacOs, All};
enum class TestStepCompiler : std::uint8_t {Clang, Gcc, All};
enum class Standard : std::uint8_t {
  Cpp11 = 0, Cpp14 = 1, Cpp17 = 2, Cpp20 = 3, Cpp23 = 4, Cpp2c = 5, Highest=Cpp2c, End = 6
};

#if defined(__linux)
auto constexpr currentPlatform = TestStepPlatform::Linux;
#elif defined(__APPLE__)
auto constexpr currentPlatform = TestStepPlatform::MacOs;
#elif defined(WIN32)
#error Undefined current platform
#else
#error Undefined current platform
#endif

auto toString(Standard const std) {
  switch(std) {
    case Standard::Cpp11: return "11";
    case Standard::Cpp14: return "14";
    case Standard::Cpp17: return "17";
    case Standard::Cpp20: return "20";
    case Standard::Cpp23: return "23";
    case Standard::Cpp2c: return "26";
    default:
      return "";
  }
}

auto toString(TestStepPlatform const plat) {
  switch (plat) {
    case TestStepPlatform::Linux: return "linux";
    case TestStepPlatform::MacOs: return "macos";
    case TestStepPlatform::All: return "all";
    default:
      assert(false && "Undefined platform type");
      return "";
  }
}

auto toString(TestStepCompiler const comp) {
  switch(comp) {
    case TestStepCompiler::Clang: return "clang++";
    case TestStepCompiler::Gcc: return "g++";
    case TestStepCompiler::All: return "<all, undefined invocation>";
    default:
      assert(false && "Undefined compiler type");
      return "";
  }
}

struct TestStepEnv {
  std::optional<TestStepPlatform> platform;
  std::optional<TestStepCompiler> compiler;
  std::vector<std::string> flags;
};

struct TestStep {
  TestStepType type;
  std::vector<TestStepEnv> enviroments;
  TestStepResult result;

  template <typename A0, typename A1, typename A2> TestStep(A0&& a0, A1&& a1, A2&& a2) :
      type{std::forward<A0>(a0)},
      enviroments{std::forward<A1>(a1)},
      result{std::forward<A2>(a2)} {}
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
constexpr auto headerPrefixFlags = "FLAGS"sv;
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
    {"26", Standard::Cpp2c},
    {"2c", Standard::Cpp2c},
};

std::unordered_map<std::string_view, TestStepType> const stepTypeMap = {
    {"compile", TestStepType::Compile},
    {"run", TestStepType::Run},
};

std::unordered_map<std::string_view, TestStepResult> const expectationMap = {
    {"success", TestStepResult::Success},
    {"failure", TestStepResult::Failure},
};

std::unordered_map<std::string_view, TestStepCompiler> const compilerMap = {
    {"clang", TestStepCompiler::Clang},
    {"gcc", TestStepCompiler::Gcc},
    {"*", TestStepCompiler::All},
};

std::unordered_map<std::string_view, TestStepPlatform> const platformMap = {
    {"linux", TestStepPlatform::Linux},
    {"macos", TestStepPlatform::MacOs},
    {"apple", TestStepPlatform::MacOs},
    {"*", TestStepPlatform::All},
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

auto platform(std::string_view const pString) -> std::optional<TestStepPlatform> {
  if (auto const pIt = platformMap.find(pString); pIt != platformMap.end()) {
    return pIt->second;
  }
  return std::nullopt;
}

auto compiler(std::string_view const cString) -> std::optional<TestStepCompiler> {
  if (auto const cIt = compilerMap.find(cString); cIt != compilerMap.end()) {
    return cIt->second;
  }
  return std::nullopt;
}

auto parseCompilerAndPlatform(std::string_view const compilerAndPlatform) -> std::optional<TestStepEnv> {
  auto const colonIdx = compilerAndPlatform.find(':');
  if (colonIdx == std::string_view::npos) {
    return std::nullopt;
  }

  return {{platform(compilerAndPlatform.substr(0, colonIdx)), compiler(compilerAndPlatform.substr(colonIdx + 1))}};
}

auto parseCompilerAndPlatforms(std::string_view compilerAndPlatforms) -> std::optional<std::vector<TestStepEnv>> {
  std::vector<TestStepEnv> envs;
  compilerAndPlatforms = trim(compilerAndPlatforms);
  while (!compilerAndPlatforms.empty()) {
    auto const idxOfSemiC = compilerAndPlatforms.find(';');
    auto const current = compilerAndPlatforms.substr(0, idxOfSemiC);
    compilerAndPlatforms = idxOfSemiC == std::string_view::npos ? "" : compilerAndPlatforms.substr(idxOfSemiC + 1);
    if (auto const step = parseCompilerAndPlatform(current)) {
      envs.push_back(*step);
    }
  }

  return envs;
}

auto parseStepCompilerAndPlatforms(std::string_view const stepTypeString) -> std::optional<std::tuple<TestStepType, std::vector<TestStepEnv>>> {
  auto const lbraceIdx = stepTypeString.find('(');
  if (lbraceIdx == std::string_view::npos) {
    if (auto const stepIt = stepTypeMap.find(stepTypeString); stepIt == stepTypeMap.end()) {
      return std::nullopt;
    } else {
      return std::tuple{stepIt->second, std::vector<TestStepEnv>()};
    }
  }

  auto const typeString = stepTypeString.substr(0, lbraceIdx);
  auto const remaining = stepTypeString.substr(lbraceIdx + 1);
  std::optional<TestStepType> step;
  if (auto const stepIt = stepTypeMap.find(typeString); stepIt == stepTypeMap.end()) {
    step = std::nullopt;
  } else {
    step = stepIt->second;
  }

  auto const rbraceIdx = remaining.rfind(')');
  if (rbraceIdx == std::string_view::npos) {
    return std::nullopt;
  }

  auto const compilerAndPlatformsString = remaining.substr(0, rbraceIdx);
  auto const envs = parseCompilerAndPlatforms(compilerAndPlatformsString);
  if (!envs) {
    return std::nullopt;
  }

  return std::tuple{*step, *envs};
}


auto stepType(TestStep const& t) {
  return t.type;
}

auto parseStepTypes(std::string_view stepTypes) -> std::optional<std::vector<std::tuple<TestStepType, std::vector<TestStepEnv>>>> {
  std::vector<std::tuple<TestStepType, std::vector<TestStepEnv>>> stepsAndEnvs;
  stepTypes = trim(stepTypes);
  while (!stepTypes.empty()) {
    auto const idxOfComma = stepTypes.find(',');
    auto const current = stepTypes.substr(0, idxOfComma);
    stepTypes = idxOfComma == std::string_view::npos ? "" : stepTypes.substr(idxOfComma + 1);
    if (auto const step = parseStepCompilerAndPlatforms(current)) {
      stepsAndEnvs.push_back(*step);
    }
  }

  return {stepsAndEnvs};
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
  if (stepsAndExpectedString.empty() || stepsAndExpectedString.front() != '[') {
    std::cout << "Expected '[' after EXPECTED\n";
    return;
  }

  stepsAndExpectedString = stepsAndExpectedString.substr(1);
  auto const brIdx = stepsAndExpectedString.find("]: ");
  if (brIdx == std::string_view::npos) {
    std::cout << "Expected ']: ' after EXPECTED[<steps>\n";
    return;
  }

  auto const stepsString = stepsAndExpectedString.substr(0, brIdx);
  auto const expectedString = stepsAndExpectedString.substr(brIdx + "]: "sv.length());
  auto const stepTypes = parseStepTypes(stepsString);
  if (!stepTypes) {
    std::cout << "Warning: Invalid step types '" << stepsString << "'\n";
  }

  auto const result = expected(expectedString);
  if (!result) {
    std::cout << "Warning: Invalid expectation '" << expectedString << "'\n";
  }

  for (auto& [type, environments, stepResult]: steps) {
    auto type2 = type;
    if (std::find_if(stepTypes->begin(), stepTypes->end(), [type2](auto const& t) { return std::get<0>(t) == type2; }) != stepTypes->end()) {
      stepResult = *result;
    }
  }
}

auto parseFlagsGetWholeStep(std::string_view step)
    -> std::optional<std::tuple<TestStepType, TestStepPlatform, TestStepCompiler>> {
  if (auto const stepIt = stepTypeMap.find(step); stepIt != stepTypeMap.end()) {
    return {{stepIt->second, TestStepPlatform::All, TestStepCompiler::All}};
  }
  std::cout << "Invalid step specified : '" << step << "'\n";
  return std::nullopt;
}

auto parseFlagsGetStepInfo(TestStepType type, std::string_view conditionsString)
    -> std::optional<std::tuple<TestStepType, TestStepPlatform, TestStepCompiler>> {
  auto const sepIdx = conditionsString.find(':');
  if (sepIdx == std::string_view::npos) {
    std::cout << "Expected ':' in step condition - platform/*:compiler/*\n";
    return std::nullopt;
  }

  auto const platString = conditionsString.substr(0, sepIdx);
  auto const platIt = platformMap.find(platString);
  if (platIt == platformMap.end()) {
    std::cout << "Invalid platform specified : '" << platString << "'\n";
    return std::nullopt;
  }
  auto const compString = conditionsString.substr(sepIdx + 1);
  auto const compIt = compilerMap.find(compString);
  if (compIt == compilerMap.end()) {
    std::cout << "Invalid compiler specified : '" << compString << "'\n";
    return std::nullopt;
  }
  return {{type, {platIt->second}, {compIt->second}}};
}

auto parseFlagsGetWildcardStep(std::string_view stepsString)
    -> std::optional<std::tuple<TestStepType, TestStepPlatform, TestStepCompiler>> {
  auto lbraceIdx = stepsString.find('(');
  if (lbraceIdx == std::string_view::npos) {
    return parseFlagsGetWholeStep(stepsString);
  }

  auto const rbraceIdx = stepsString.find(')');
  if (rbraceIdx == std::string_view::npos) {
    std::cout << "Expected ')' after <step>(<conditions>\n";
    return std::nullopt;
  }

  if (auto const stepIt = stepTypeMap.find(stepsString.substr(0, lbraceIdx)); stepIt != stepTypeMap.end()) {
    return parseFlagsGetStepInfo(stepIt->second, stepsString.substr(lbraceIdx + 1, stepsString.length() - lbraceIdx - 2));
  }
  return std::nullopt;
}

auto parseAndAppendStepFlagsFor(std::vector<TestStep>& steps, std::string_view stepsString, std::string_view flagsString) {
  auto const flagsApplyTo = parseFlagsGetWildcardStep(stepsString);
  if (!flagsApplyTo) {
    return;
  }

  auto const [stepType, stepPlat, stepComp] = *flagsApplyTo;
  for (auto& step : steps) {
    if (step.type != stepType) {
      continue;
    }

    for (auto& env : step.enviroments) {
      if (env.platform && stepPlat != TestStepPlatform::All && stepPlat != *env.platform
          || env.compiler && stepComp != TestStepCompiler::All && stepComp != *env.compiler) {
        continue;
      }

      std::stringstream asBuf;
      asBuf << flagsString;
      std::string flag;
      while (asBuf >> flag) {
        env.flags.push_back(std::move(flag));
      }
    }
  }
}

auto parseAndAppendStepFlags(std::vector<TestStep>& steps, expanded_string_view stepsAndFlagsString) {
  if (!stepsAndFlagsString.starts_with('[')) {
    std::cout << "Expected '[' after FLAGS\n";
    return;
  }

  stepsAndFlagsString = stepsAndFlagsString.substr(1);
  auto const endIdx = stepsAndFlagsString.find("]: ");
  if (endIdx == std::string_view::npos) {
    std::cout << "Expected ']: ' after FLAGS[<steps>\n";
    return;
  }

  parseAndAppendStepFlagsFor(steps, stepsAndFlagsString.substr(0, endIdx), stepsAndFlagsString.substr(endIdx + "]: "sv.length()));
}

auto processTestHeader(std::string const& path) -> std::optional<TestData> {
  std::ifstream testFile(path);
  std::vector<TestStep> steps;
  StandardRange standard {.begin = Standard::Cpp11};

  std::ifstream file(path);
  expanded_string line;
  bool isDcrTest = false;
  while (std::getline(file, line)) {
    if (!line.starts_with("// ")) {
      break;
    }

    if (auto const headerItem = expanded_string_view(line).substr(3); headerItem.starts_with("DCR-TEST")) {
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
      if (auto const stepTypesAndEnvs = parseStepTypes(stepString); !stepTypesAndEnvs) {
        std::cout << "Warning in '" << path << "': Invalid Step Types '" << stepString << "'\n";
      } else {
        std::for_each(stepTypesAndEnvs->begin(), stepTypesAndEnvs->end(), [&steps](auto const typeAndEnv) {
          auto const& [type, envs] = typeAndEnv;
          steps.emplace_back(type, envs, TestStepResult::Success);
        });
      }
    } else if (headerItem.starts_with(headerPrefixExpected)) {
      parseAndAdjustSteps(steps, headerItem.substr(headerPrefixExpected.length()));
    } else if (headerItem.starts_with(headerPrefixFlags)) {
      parseAndAppendStepFlags(steps, headerItem.substr(headerPrefixFlags.length()));
    }
  }

  if (!isDcrTest) {
    std::cout << "skipped file '" << path << "' since it does not have a DCR header.\n";
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

std::vector const allStandardsArray =
  {Standard::Cpp11, Standard::Cpp14, Standard::Cpp17, Standard::Cpp20, Standard::Cpp23, Standard::Cpp2c, Standard::End};
auto stdRange(StandardRange range) {
  if (!range.end) {
    range.end = Standard::Highest;
  }

  return std::vector(
    std::find(allStandardsArray.begin(), allStandardsArray.end(), range.begin),
    std::find(allStandardsArray.begin(), allStandardsArray.end(), range.end) + 1
  );
}

auto executablePath(std::string const& src, Standard standard, TestStepEnv const& env) {
  assert(env.compiler && "Env must have compiler value");
  assert(env.platform && "Env must have platform value");
  auto const lastSlIdx = src.rfind('/');
  auto relative = src;
  if (lastSlIdx != std::string::npos) {
    relative = src.substr(lastSlIdx + 1);
  }

  auto const& [plat, comp, _] = env;
  auto const extensionIdx = relative.rfind('.');
  auto const binary = relative.substr(0, extensionIdx) + "_" + toString(standard) + "_" + toString(*plat) + "_" + toString(*comp) + ".bin";
  return "./test_binaries/" + binary;
}

auto profPath(std::string const& src, Standard standard, TestStepEnv const& env) {
  auto const execPath = executablePath(src, standard, env);
  auto const extLoc = execPath.rfind('.');
  auto const withoutExt = execPath.substr(0, extLoc);
  return withoutExt + ".profraw";
}

[[maybe_unused]] auto debugCmd(char const* cmd, char** args, [[maybe_unused]] char** env) {
  static std::mutex debugLock;
  std::lock_guard g(debugLock);
  std::stringstream oss;
  oss
      << "[DEBUG] - " << cmd;
  oss << " [ARGS] -\n";
  for (auto s = args; *s; ++s) {
    oss << " " << *s << '\n';
  }
  std::cout << oss.str();
}

auto awaitProcess(std::optional<std::string> executable, std::vector<std::string>& args, std::vector<std::string>& env) -> std::tuple<bool, std::string, std::string, bool> {
  if (!executable) {
    return {true, "", "", true};
  }

  std::array outRedir{0, 0};
  std::array errRedir{0, 0};
  pipe(outRedir.data());
  pipe(errRedir.data());

  auto toCArr = [](std::vector<char*>& dst, std::vector<std::string>& arr, std::optional<char*> first = std::nullopt) {
    if (first) { dst.emplace_back(*first); }
    std::for_each(arr.begin(), arr.end(), [&dst](auto& s){ dst.emplace_back(s.data()); });
    dst.emplace_back(nullptr);
  };

  std::vector<char*> cArgs;
  toCArr(cArgs, args, executable->data());

  std::vector<char*> cEnv;
  auto fillOtherEnv = [](auto& envArr){
    for (auto* s = environ; *s; ++s) {
      envArr.push_back(*s);
    }
  };

  fillOtherEnv(cEnv);
  toCArr(cEnv, env);

  pid_t const childId = fork();
  if (childId == 0) {
    close(STDOUT_FILENO);
    close(STDERR_FILENO);
    dup2(outRedir[1], STDOUT_FILENO);
    dup2(errRedir[1], STDERR_FILENO);
    close(outRedir[0]);
    close(outRedir[1]);
    close(errRedir[0]);
    close(errRedir[1]);

    if (0 != execvpe(executable->c_str(), cArgs.data(), cEnv.data())) {
      std::cerr << "Execvpe run failed with error code: " << errno << '\n';
    }

    exit(1);
  }

  close(outRedir[1]);
  close(errRedir[1]);
  if (childId < 0) {
    close(outRedir[0]);
    close(errRedir[0]);
    std::cerr << "Unknown error\n";
    return {false, "", "", false};
  }

  auto outputAwaiter = [](auto fd, auto& out) {
    return [fd, &out]() {
      std::array<char, BUFSIZ> buf{0};
      bool reading = true;
      while (reading) {
        auto readCount = read(fd, buf.data(), BUFSIZ);
        if (readCount != 0) { out += std::string_view(buf.data(), readCount); }
        else { reading = false; }
      }
    };
  };

  std::string errContents;
  std::string outContents;
  [&await = outputAwaiter, &errR = errRedir, &errC = errContents, &outR = outRedir, &outC = outContents] {
    (void)std::array{jthread(await(errR[0], errC)), jthread(await(outR[0], outC))};
  }();

  int stat;
  waitpid(childId, &stat, 0);

  close(outRedir[0]);
  close(errRedir[0]);
  if (WIFEXITED(stat)) {
    return {WEXITSTATUS(stat) == 0, outContents, errContents, false};
  }

  return {false, outContents, errContents, false};
}

struct CompileData {
  std::string const& path;
  Standard standard;
  TestStepEnv testEnv;
};

struct RunData {
  std::string const& path;
  Standard standard;
  TestStepEnv testEnv;
};

std::unordered_map<TestStepCompiler, std::string> mappedCompilers;
std::unordered_map<TestStepCompiler, std::vector<std::string>> mappedCompilerAdditionalArgs;
auto getCompilerName(std::optional<TestStepCompiler> const& compiler) -> std::optional<std::string> {
  if (!compiler) {
    return std::nullopt;
  }

  if (auto const idIt = mappedCompilers.find(*compiler); idIt != mappedCompilers.end()) {
    return idIt->second;
  }

  return std::nullopt;
}

auto defineDcrStdIdentifier(std::vector<std::string>& args, Standard std) {
  using namespace std::string_literals;
  args.emplace_back("-D");
  args.emplace_back("DCR_CPP"s + toString(std));
  auto const sinceStds = stdRange(StandardRange{.begin = Standard::Cpp11, .end = std});
  for (auto const& sinceStd: sinceStds) {
    args.emplace_back("-D");
    args.emplace_back("DCR_SINCECPP"s + toString(sinceStd));
  }
}

auto addFlags(std::vector<std::string>& args, std::vector<std::string> const& flags) {
  for (auto const& flag : flags) {
    args.emplace_back(flag);
  }
}

auto executeCompile(CompileData const& data, std::vector<std::string> const& extraArgs) {
  auto const& [path, standard, testEnv] = data;
  std::vector<std::string> fullArgs = extraArgs;
  std::vector<std::string> env;
  defineDcrStdIdentifier(fullArgs, data.standard);
  addFlags(fullArgs, data.testEnv.flags);
  fullArgs.push_back(path);
  fullArgs.emplace_back("-o");
  fullArgs.push_back(executablePath(path, standard, testEnv));
  auto&& compilerName = getCompilerName(data.testEnv.compiler);
  if (compilerName) {
    assert(data.testEnv.compiler);
    if (auto const addArgsIt = mappedCompilerAdditionalArgs.find(*data.testEnv.compiler);
        addArgsIt != mappedCompilerAdditionalArgs.end()) {
      fullArgs.insert(fullArgs.begin(), addArgsIt->second.begin(), addArgsIt->second.end());
        }
  }
  return awaitProcess(std::move(compilerName), fullArgs, env);
}

auto executeRun(RunData const& data) {
  using namespace std::string_literals;
  auto const& [path, standard, testEnv] = data;
  auto const& execPath = executablePath(path, standard, testEnv);
  auto const& profrawPath = profPath(path, standard, testEnv);
  std::vector<std::string> args;
  addFlags(args, testEnv.flags);
  std::vector env = {"LLVM_PROFILE_FILE="s + profrawPath};
  return awaitProcess(execPath, args, env);
}

struct Job {
  TestStepType type;
  TestStepResult expected;
  std::variant<CompileData, RunData> data;
  std::unique_ptr<Job> creates;

  template <typename A0, typename A1, typename A2, typename A3> Job(A0&& a0, A1&& a1, A2&& a2, A3&& a3) :
      type{std::forward<A0>(a0)},
      expected{std::forward<A1>(a1)},
      data{std::forward<A2>(a2)},
      creates{std::forward<A3>(a3)} {}
};

/**
 * Acquires jobs for the "Standard" test step, updates the total and skipped counts,
 * and adds the acquired jobs to the specified vector.
 *
 * @param total     [in, out] the total number of jobs
 * @param skipped   [in, out] the number of jobs skipped
 * @param placeInto [out] the vector to place acquired jobs into
 * @param path      [in] the path of the test
 * @param standard  [in] the standard to use for the test
 * @param steps     [in] the list of test steps
 */
auto acquireJobsForStandard(
    int& total,
    int& skipped,
    std::vector<std::unique_ptr<Job>>& placeInto,
    std::string const& path,
    Standard standard,
    std::vector<TestStep> const& steps
) {
  if (auto const it = std::find_if(steps.begin(), steps.end(), [](TestStep const& step) { return step.type == TestStepType::Compile; }); it != steps.end()) {
    for (auto const& env: it->enviroments) {
      if (!env.compiler || !env.platform) {
        ++skipped;
        continue;
      }

      if (env.platform != currentPlatform) {
        ++skipped;
        continue;
      }

      if (!getCompilerName(env.compiler)) {
        ++skipped;
        continue;
      }

      placeInto.push_back(
          std::make_unique<Job>(
              TestStepType::Compile,
              it->result,
              CompileData {
                  /* .path = */ path,
                  /* .standard = */ standard,
                  /* .testEnv = */ env
              },
              nullptr
          )
      );
      ++total;
    }
  }

  if (auto const it = std::find_if(steps.begin(), steps.end(), [](auto const& step) { return step.type == TestStepType::Run; }); it != steps.end()) {
    for (auto const& env: it->enviroments) {
      if (auto compileJobIt = std::find_if(placeInto.begin(), placeInto.end(), [&env](std::unique_ptr<Job> const& j) {
          return j->type == TestStepType::Compile
                 && env.compiler == std::get<CompileData>(j->data).testEnv.compiler
                 && env.platform == std::get<CompileData>(j->data).testEnv.platform;
        }); compileJobIt != placeInto.end()) {
        (*compileJobIt)->creates = std::make_unique<Job>(
            TestStepType::Run,
            it->result,
            RunData {
                /* .path = */ path,
                /* .standard = */ standard,
                /* .testEnv = */ env
            },
            nullptr
        );
        ++total;
      } else {
        ++skipped;
      }
    }
  }
}

auto acquireJobsFromTest(int& total, std::vector<std::unique_ptr<Job>>& placeInto, TestData const& test) -> int {
  int skipped = 0;
  auto const& [path, steps, standards] = test;
  for (auto const& standard: stdRange(standards)) {
    std::vector<std::unique_ptr<Job>> jobs;
    acquireJobsForStandard(total, skipped, jobs, path, standard, steps);
    std::for_each(jobs.begin(), jobs.end(), [&placeInto](auto& j){ placeInto.push_back(std::move(j)); });
  }
  return skipped;
}

auto addCoverageFlags(std::vector<std::string>& args, TestStepEnv const& env) {
  if (env.compiler && *env.compiler == TestStepCompiler::Clang) {
    args.emplace_back("-fcoverage-mapping");
    args.emplace_back("-fprofile-instr-generate");
    args.emplace_back("-O0");
    args.emplace_back("-g");
    args.emplace_back("-mllvm");
    args.emplace_back("-enable-name-compression=false");
  }
}

auto addReleaseFlags(std::vector<std::string>& args, TestStepEnv const& env) {
  if (env.compiler && (*env.compiler == TestStepCompiler::Clang || *env.compiler == TestStepCompiler::Gcc)) {
    args.emplace_back("-O3");
    args.emplace_back("-DNDEBUG");
  }
}

template <typename J> auto executeJob(J& job, std::vector<std::string> const& passToCompiler, DcrParams const& params) -> std::tuple<bool, std::string, std::string, bool> {
#ifdef CDS_DCR_BLOCK_MULTIACCESS_TO_PROFRAW
  static std::mutex profrawBlock;
#endif

  using namespace std::string_literals;
  if (job->type == TestStepType::Compile) {
    std::vector withStd = passToCompiler;
    auto const& data = std::get<CompileData>(job->data);
    withStd.push_back("-std=c++"s + toString(data.standard));
    if (params.coverage) {
      addCoverageFlags(withStd, data.testEnv);
    }
    if (params.release) {
      addReleaseFlags(withStd, data.testEnv);
    }

    return executeCompile(data, withStd);
  }

  if (job->type == TestStepType::Run) {
#ifdef CDS_DCR_BLOCK_MULTIACCESS_TO_PROFRAW
    if (!params.release) {
      std::lock_guard prowrawGuard(profrawBlock);
      auto const& data = std::get<RunData>(job->data);
      return executeRun(data);
    }
#else
    auto const& data = std::get<RunData>(job->data);
    return executeRun(data);
#endif
  }

  return {false, "", "Unknown Job Type", false};
}

template <typename T> auto toString(std::optional<T> const& obj) {
  if (!obj) {
    return "unknown";
  }
  return toString(*obj);
}

auto rpad(int const size, std::string const& str) {
  auto const padLen = std::max(0, size - static_cast<int>(str.length()));
  return str + std::string(padLen, ' ');
}

template <typename J> auto toString(J const& job) {
  std::stringstream oss;

  if (job->type == TestStepType::Compile) {
    auto const& data = std::get<CompileData>(job->data);
    oss << "compile [" << rpad(5, toString(data.testEnv.platform)) << "," << rpad(7, toString(data.testEnv.compiler)) << ",cpp" << toString(data.standard) << "] " << data.path;
  } else if (job->type == TestStepType::Run) {
    auto const& data = std::get<RunData>(job->data);
    oss << "run     [" << rpad(5, toString(data.testEnv.platform)) << "," << rpad(7, toString(data.testEnv.compiler)) << ",cpp" << toString(data.standard) << "] " << data.path;
  }

  return oss.str();
}

template <typename J, typename L> auto buildJobQueueFunctions(
    J& jobs,
    L& jobsLock
) {
  return std::make_tuple(
      [&jobs, &jobsLock]{
        std::lock_guard g(jobsLock);
        if (jobs.empty()) {
          return std::unique_ptr<Job>();
        }
        auto job = std::move(jobs.back());
        jobs.pop_back();
        return job;
      },
      [&jobs, &jobsLock](std::unique_ptr<Job>&& job){
        std::lock_guard g(jobsLock);
        jobs.push_back(std::move(job));
      }
  );
}

template <typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6> auto buildJobLoggers(
    A0& totalCount,
    A1& runCount,
    A2& successful,
    A3& otherUpdatersLock,
    A4& failedTestPaths,
    A5& dcrParams,
    A6& skipped
) {
  auto const statusHeader = [&totalCount, &runCount, &skipped] {
    return std::to_string(runCount++ + 1) + "/" + std::to_string(totalCount - skipped);
  };

  return std::make_tuple(
      [statusHeader, &successful, &otherUpdatersLock](std::string const& jobName) {
        ++successful;
        std::lock_guard g(otherUpdatersLock);
        std::cout << '[' << statusHeader() << "] " << jobName << " successful\n";
      },
      [statusHeader, &otherUpdatersLock, &failedTestPaths, &dcrParams](std::string const& jobName, std::string const& out, std::string const& err) {
        std::lock_guard g(otherUpdatersLock);
        failedTestPaths.emplace_back(jobName);
        std::cout << '[' << statusHeader() << "] " << jobName << " failed\n";
        if (dcrParams.verbose) {
          std::cout << "  Output: " << out << " " << err << "\n";
        }
      }
  );
}

template <typename A0, typename A1, typename A2, typename A3> auto buildRunJob(
    A0& logJobSuccess,
    A1& logJobFailure,
    A2& passToCompiler,
    A3& dcrParams
) {
  return [&logJobSuccess, &logJobFailure, &passToCompiler, &dcrParams](std::unique_ptr<Job> const& job) {
    auto const [status, outputText, errorText, wasSkipped] = executeJob(job, passToCompiler, dcrParams);
    if (wasSkipped) {
      return false;
    }

    auto const asStr = toString(job);
    auto const wasSuccessful = job->expected == TestStepResult::Success ? status : !status;
    if (wasSuccessful) {
      logJobSuccess(asStr);
    } else {
      logJobFailure(asStr, outputText, errorText);
    }
    return wasSuccessful;
  };
}

template <typename A0, typename A1, typename A2> auto executeRunners(
    A0& threadRunnerFn,
    A1& dcrParams,
    A2& jobs
) {
  std::vector<std::unique_ptr<jthread>> runners;
  for (int thIdx = 0; thIdx < std::min(dcrParams.threadCount, static_cast<int>(std::size(jobs))); ++ thIdx) {
    runners.emplace_back(std::make_unique<jthread>(threadRunnerFn));
  }
}

auto execute(std::vector<TestData> const& tests, std::vector<std::string> const& extraArgs, DcrParams const& dcrParams) -> int {
  std::vector<std::unique_ptr<Job>> jobs;
  int total = 0;
  std::atomic successful = 0;
  std::atomic skipped = 0;
  for (auto const& test: tests) {
    auto currentSkipped = acquireJobsFromTest(total, jobs, test);
    total += currentSkipped;
    skipped += currentSkipped;
  }

  using namespace std::string_literals;

  std::cout << "[DCR] Skipping " << skipped << " incompatible tests\n"
            << "[DCR] Starting async execution...\n";
  auto dcrPath = std::filesystem::path(__FILE__).parent_path();
  std::vector<std::string> passToCompiler = extraArgs;
  passToCompiler.emplace_back(dcrPath / "DcrMain.cpp");
  passToCompiler.emplace_back(dcrPath / "Test.cpp");

  std::mutex jobsLock;
  std::mutex otherUpdatersLock;
  std::vector<std::string> failedTestPaths;
  int finished = 0;

  auto queueOps = buildJobQueueFunctions(jobs, jobsLock);
  auto [logJobSuccess, logJobFailure] = buildJobLoggers(total, finished, successful, otherUpdatersLock, failedTestPaths, dcrParams, skipped);
  auto runJob = buildRunJob(logJobSuccess, logJobFailure, passToCompiler, dcrParams);

  auto threadRunnerFn = [&runJob, &queueOps, &skipped] {
    auto& [getJob, pushJob] = queueOps;
    bool shouldTerminate = false;
    while (!shouldTerminate) {
      auto job = getJob();
      if (!job) {
        shouldTerminate = true;
        continue;
      }

      auto const wasSuccessful = runJob(job);
      if (job->creates) {
        if (wasSuccessful) {
          pushJob(std::move(job->creates));
        } else {
          ++skipped;
        }
      }
    }
  };

  executeRunners(threadRunnerFn, dcrParams, jobs);
  std::cout << total << " tests ran, out of which " << successful << " were successful, " << skipped << " were skipped";
  if (!failedTestPaths.empty()) {
    std::cout << " and the following " << (total - successful - skipped) << " failed:\n";
  } else {
    std::cout << '\n';
  }

  for (auto const& testPath: failedTestPaths) {
    std::cout << "  " << testPath << '\n';
  }

  assert((total == skipped + successful + failedTestPaths.size()) && "Invalid sum of tests");
  return total != skipped + successful;
}

auto amendCompilerBasedOnPlatform(auto cname, auto platform)
    -> std::tuple<std::string, std::vector<std::string>> {
  if (platform == TestStepPlatform::Linux) {
    return {cname, {}};
  }

  if (platform == TestStepPlatform::MacOs) {
    if (cname == "clang++") {
      return {"/usr/bin/clang++", {}};
      // return {"/Library/Developer/CommandLineTools/usr/bin/clang++",
      // {"/Library/Developer/CommandLineTools/usr/share/man/man1/clang++.1"}};
    }

    if (cname == "g++") {
      auto const hbPath = "/opt/homebrew/Cellar/gcc";
      if (!std::filesystem::exists(hbPath)) {
        return {cname, {}};
      }

      auto const asPath = std::filesystem::path(hbPath);
      int maxGccVer = -1;
      for (auto const& entry : std::filesystem::directory_iterator{asPath}) {
        if (entry.is_directory()) {
          auto&& asStr = entry.path().filename().generic_string();
          auto firstDotPos = asStr.find('.');
          assert(firstDotPos != std::string_view::npos);
          auto const ver = expanded_string_view{asStr}.substr(0, firstDotPos);
          int verInt{0};
          auto const verIntRes = std::from_chars(ver.data(), ver.data() + ver.length(), verInt, 10);
          assert(verIntRes.ec == std::errc{});
          maxGccVer = std::max(maxGccVer, verInt);
        }
      }

      if (maxGccVer == -1) {
        return {cname, {}};
      }

      return {std::string{"/opt/homebrew/bin/g++-"} + std::to_string(maxGccVer), {}};
    }
  }

  assert(false && "Unable to ascertain whether to use path relative or local translation of compiler paths");
  return {cname, {}};
}

auto mapCompilers(std::vector<TestStepCompiler> const& compilersToMap) {
  for (auto c : compilersToMap) {
    std::string cname = toString(c);
    std::vector<std::string> additionalArgs;
    std::tie(cname, additionalArgs) = amendCompilerBasedOnPlatform(cname, currentPlatform);
    if (!additionalArgs.empty()) {
      mappedCompilerAdditionalArgs.try_emplace(c, std::move(additionalArgs));
    }
    std::vector<std::string> args = {"--version"};
    std::vector<std::string> env;
    if (std::get<0>(awaitProcess(cname, args, env))) {
      mappedCompilers.try_emplace(c, cname);
    }
  }
}
} // namespace

auto locateWildcardMatches(std::vector<std::filesystem::path>&& paths) {
  std::vector<std::filesystem::path> resolved;
  for (auto&& path : paths) {
    auto const parent = path.parent_path();
    auto const asStr = path.string();
    if (asStr.find('*') == std::string::npos) {
      resolved.emplace_back(std::move(path));
      continue;
    }

    auto const lastSep = asStr.rfind(std::filesystem::path::preferred_separator);
    auto const child = lastSep == std::string::npos ? asStr : asStr.substr(lastSep + 1);
    auto const wPos = child.rfind('*');
    auto const extPos = child.rfind('.');
    assert(wPos != std::string::npos && "Only supports leaf-level wildcard");
    assert(child.find('*') == child.rfind('*') && "Only support single wildcard");
    assert(wPos + 1 == extPos && "Only supports wildcard before extension");
    auto const startingWith = child.substr(0, wPos);
    for (auto const& file : std::filesystem::directory_iterator(parent)) {
      auto const fileAsStr = file.path().string();
      auto const leaf = expanded_string_view{
        fileAsStr.substr(fileAsStr.rfind(std::filesystem::path::preferred_separator) + 1)};
      if (leaf.starts_with(startingWith)) {
        resolved.emplace_back(file.path());
      }
    }
  }

  paths.clear();
  return resolved;
}

auto run(int const argc, char const* const* argv) -> int {
  if (argc == 1) {
    std::cerr << "No path/file provided to DCR test runner\n";
    return 1;
  }
  mapCompilers({TestStepCompiler::Clang, TestStepCompiler::Gcc});
  std::filesystem::path inputFileOrDir;
  std::vector<std::string> passedToCompiler;
  std::filesystem::create_directory("test_binaries");
  DcrParams dcrParams {.verbose = false, .threadCount = 1};
  argParse(
      {&argv[1], &argv[argc]},
      makeParser(
          [&dcrParams](auto const&) { dcrParams.verbose = true; },
          [](auto const& arg) { return arg == "-v"; }
      ),
      makeParser(
          [&dcrParams](auto const&) { dcrParams.coverage = true; },
          [](auto const& arg) { return arg == "-c"; }
      ),
      makeParser(
          [&dcrParams](auto const&) { dcrParams.release = true; },
          [](auto const& arg) { return arg == "-r"; }
      ),
      makeParser(
          [&dcrParams](auto const& params) { dcrParams.threadCount = static_cast<int>(std::strtol(params[1].c_str(), nullptr, 10)); },
          [](auto const& arg) { return arg == "-j"; },
          [](auto const& arg) { return std::all_of(arg.begin(), arg.end(),
            [](char const c){ return c >= '0' && c <= '9'; }); }
      ),
      makeParser(
          [&inputFileOrDir](auto const& args) { inputFileOrDir = args[0]; },
          [](auto const&) { return true; }
      ),
      makeParserWithSink(
          [&passedToCompiler](auto const& args) { passedToCompiler = {args.begin() + 1, args.end()}; },
          alwaysAccept,
          [](auto const& arg) { return arg == "--"; }
      )
  );

  if (dcrParams.coverage && dcrParams.release) {
    std::cout << "Launching tests in both release and coverage is unsupported\n";
    return 0;
  }

  if (dcrParams.verbose) {
    std::cout << "[DCR] Locating DCR compatible files at given path\n";
  }

  std::vector<std::filesystem::path> inputPaths = locateWildcardMatches({std::move(inputFileOrDir)});
  for (auto const& path: inputPaths) {
    if (!std::filesystem::exists(path)) {
      std::cout << "Invalid input path '" << path << "'\n";
      return 1;
    }
  }

  auto const testPaths = locateTests(std::move(inputPaths));
  if (testPaths.empty()) {
    std::cout << "No tests found at given path\n";
    return 1;
  }

  if (dcrParams.verbose) {
    std::cout << "[DCR] Located " << testPaths.size() << " compatible file(s) at given location\n";
  }

  auto const tests = processTests(testPaths);
  if (dcrParams.verbose) {
    auto accum = [](auto const& it, auto const& sel) {
      auto sum = 0;
      for (auto const& e : it) {
        sum += std::invoke(sel, e);
      }
      return sum;
    };

    auto numStds = [](StandardRange const& rng) {
      auto const end = rng.end ? *rng.end : Standard::Highest;
      return static_cast<std::underlying_type_t<Standard>>(end)
          - static_cast<std::underlying_type_t<Standard>>(rng.begin)
          + 1;
    };

    auto testCount = [&tests, &accum, &numStds] {
      return accum(tests, [&accum, &numStds](TestData const& td) {
        return accum(td.steps, [&accum](TestStep const& ts) {
          return accum(ts.enviroments, [](auto const&){ return 1; });
        }) * numStds(td.standard);
      });
    };
    std::cout << "[DCR] Located " << testCount() << " tests in compatible files\n";
  }

  return execute(tests, passedToCompiler, dcrParams);
}
} // namespace dcr
