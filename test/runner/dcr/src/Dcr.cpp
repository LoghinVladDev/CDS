//
// Created by loghin on 12/1/23.
//

#include "Dcr.hpp"

#include <atomic>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <vector>
#include <functional>
#include <memory>
#include <optional>
#include <thread>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <variant>
#include <bits/ranges_algo.h>
#include <sys/wait.h>

extern char** environ;
namespace std {
class thread;
}

namespace dcr {
namespace {
struct DcrParams {
  bool verbose;
  int threadCount;
};

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

      if (filterIdx == parser->filterCount() || (parser->isSink() && filterIdx > 0)) {
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
enum class TestStepPlatform {Linux, Win32, Apple};
enum class TestStepCompiler {Clang, Gcc, Msvc};
enum class Standard {Cpp11, Cpp14, Cpp17, Cpp20, Cpp23, Cpp2c, Highest=Cpp23, End};

struct TestStepEnv {
  TestStepPlatform platform;
  TestStepCompiler compiler;
};

struct TestStep {
  TestStepType type;
  std::vector<TestStepEnv> enviroments;
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

auto parseStepCompilerAndPlatforms(std::string_view stepTypeString) -> std::optional<std::tuple<TestStepType, std::vector<TestStepEnv>>> {
  auto const rbraceIdx = stepTypeString.find('(');
  if (rbraceIdx == std::string_view::npos) {
    if (auto const stepIt = stepTypeMap.find(stepTypeString); stepIt == stepTypeMap.end()) {
      return std::nullopt;
    } else {
      return std::tuple{stepIt->second, std::vector<TestStepEnv>()};
    }
  }

  auto const typeString = stepTypeString.substr(0, rbraceIdx);
  auto const remaining = stepTypeString.substr(rbraceIdx + 1);
  std::optional<TestStepType> step;
  if (auto const stepIt = stepTypeMap.find(typeString); stepIt == stepTypeMap.end()) {
    step = std::nullopt;
  } else {
    step = stepIt->second;
  }

  return std::tuple{*step, std::vector<TestStepEnv>()};
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
    if (std::ranges::find(*stepTypes, type, [](auto const& t) { return std::get<0>(t); }) != stepTypes->end()) {
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
      if (auto const stepTypesAndEnvs = parseStepTypes(stepString); !stepTypesAndEnvs) {
        std::cout << "Warning in '" << path << "': Invalid Step Types '" << stepString << "'\n";
      } else {
        std::ranges::for_each(*stepTypesAndEnvs, [&steps](auto const typeAndEnv) {
          auto const& [type, envs] = typeAndEnv;
          steps.emplace_back(type, envs, TestStepResult::Success);
        });
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
  Sequential,
  Parallel
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
  auto const lastSlIdx = src.rfind('/');
  auto relative = src;
  if (lastSlIdx != std::string::npos) {
    relative = src.substr(lastSlIdx + 1);
  }

  auto const extensionIdx = relative.rfind('.');
  auto const binary = relative.substr(0, extensionIdx) + "_" + toString(standard) + ".bin";
  return "./test_binaries/" + binary;
}

auto profPath(std::string const& src, Standard standard) {
  auto execPath = executablePath(src, standard);
  auto extLoc = execPath.rfind('.');
  auto withoutExt = execPath.substr(0, extLoc);
  return withoutExt + ".profraw";
}

auto awaitProcess(std::string executable, std::vector<std::string>& args, std::vector<std::string>& env) -> std::tuple<bool, std::string, std::string> {
  int outRedir[2];
  int errRedir[2];
  pipe(outRedir);
  pipe(errRedir);

  auto toCArr = [](std::vector<char*>& dst, std::vector<std::string>& arr, std::optional<char*> first = std::nullopt) {
    if (first) { dst.emplace_back(*first); }
    std::ranges::for_each(arr, [&dst](auto& s){ dst.emplace_back(s.data()); });
    dst.emplace_back(nullptr);
  };

  std::vector<char*> cArgs;
  toCArr(cArgs, args, executable.data());

  std::vector<char*> cEnv;
  auto fillOtherEnv = [](auto& env){
    for (auto s = environ; *s; ++s) {
      std::string asStr = *s;
      env.push_back(*s);
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

    execvpe(executable.c_str(), cArgs.data(), cEnv.data());

    exit(1);
  }

  close(outRedir[1]);
  close(errRedir[1]);
  if (childId < 0) {
    close(outRedir[0]);
    close(errRedir[0]);
    std::cerr << "Unknown error\n";
    return {false, "", ""};
  }

  int stat;
  waitpid(childId, &stat, 0);

  int readCount;
  char buf[1024];
  std::string outContents;
  while (0 != (readCount = read(outRedir[0], buf, 1024))) {
    outContents += std::string_view(buf, readCount);
  }
  std::string errContents;
  while (0 != (readCount = read(errRedir[0], buf, 1024))) {
    errContents += std::string_view(buf, readCount);
  }

  close(outRedir[0]);
  close(errRedir[0]);
  if (WIFEXITED(stat)) {
    return {WEXITSTATUS(stat) == 0, outContents, errContents};
  }

  return {false, outContents, errContents};
}

auto executeCompile(std::string const& path, Standard standard, std::vector<std::string> const& extraArgs) {
  std::vector<std::string> fullArgs = extraArgs;
  std::vector<std::string> env;
  fullArgs.push_back(path);
  fullArgs.emplace_back("-o");
  fullArgs.push_back(executablePath(path, standard));

  return awaitProcess("clang++", fullArgs, env);
}

auto executeRun(std::string const& path, Standard standard) -> std::tuple<bool, std::string, std::string> {
  using namespace std::string_literals;
  auto const& execPath = executablePath(path, standard);
  auto const& profrawPath = profPath(path, standard);
  std::vector<std::string> args;
  std::vector env = {"LLVM_PROFILE_FILE="s + profrawPath};
  return awaitProcess(execPath, args, env);
}

struct CompileData {
  std::string const& path;
  Standard standard;
};

struct RunData {
  std::string const& path;
  Standard standard;
};

struct Job {
  TestStepType type;
  TestStepResult expected;
  std::variant<CompileData, RunData> data;
  std::unique_ptr<Job> creates;
};

auto acquireJobsFromTest(int& total, std::vector<std::unique_ptr<Job>>& placeInto, TestData const& test) {
  for (auto const& [path, steps, standards] = test; auto const& standard: stdRange(standards)) {
    std::unique_ptr<Job> job = nullptr;
    if (auto const it = std::ranges::find(steps, TestStepType::Compile, stepType); it != steps.end()) {
      job = std::make_unique<Job>(
        TestStepType::Compile,
        it->result,
        CompileData {
          .path = path,
          .standard = standard
        },
        nullptr
      );
      ++total;
    }

    if (auto const it = std::ranges::find(steps, TestStepType::Run, stepType); job && it != steps.end()) {
      job->creates = std::make_unique<Job>(
        TestStepType::Run,
        it->result,
        RunData {
          .path = path,
          .standard = standard
        },
        nullptr
      );
      ++total;
    }

    if (job) {
      placeInto.push_back(std::move(job));
    }
  }
}

#ifdef CDS_DCR_BLOCK_MULTIACCESS_TO_PROFRAW
std::mutex profrawBlock;
#endif
auto executeJob(std::unique_ptr<Job> const& job, std::vector<std::string> const& passToCompiler) -> std::tuple<bool, std::string, std::string> {
  using namespace std::string_literals;
  if (job->type == TestStepType::Compile) {
    auto const& [path, standard] = std::get<CompileData>(job->data);
    std::vector withStd = passToCompiler;
    withStd.push_back("-std=c++"s + toString(standard));
    return executeCompile(path, standard, withStd);
  }

  if (job->type == TestStepType::Run) {
#ifdef CDS_DCR_BLOCK_MULTIACCESS_TO_PROFRAW
    std::lock_guard prowrawGuard(profrawBlock);
#endif
    auto const& [path, standard] = std::get<RunData>(job->data);
    return executeRun(path, standard);
  }

  return {false, "", "Unknown Job Type"};
}

auto toString(TestStepType const type) {
  switch (type) {
    using enum TestStepType;
    case Compile: return "compile";
    case Run: return "run";
  }

  return "unknown test type";
}

std::string const unknownData = "unknown test data";
auto toString(std::variant<CompileData, RunData> const& data) -> std::string const& {
  if (std::holds_alternative<CompileData>(data)) {
    return std::get<CompileData>(data).path;
  }

  if (std::holds_alternative<RunData>(data)) {
    return std::get<RunData>(data).path;
  }

  return unknownData;
}

auto toString(std::unique_ptr<Job> const& job) {
  std::stringstream oss;
  oss << toString(job->type) << " " << toString(job->data);
  return oss.str();
}

auto execute(std::vector<TestData> const& tests, std::vector<std::string> const& extraArgs, DcrParams const& dcrParams) -> int {
  std::vector<std::unique_ptr<Job>> jobs;
  int total = 0;
  std::atomic successful = 0;
  std::atomic skipped = 0;
  for (auto const& test: tests) {
    acquireJobsFromTest(total, jobs, test);
  }

  using namespace std::string_literals;
  auto const dcrPath = "../test/runner/dcr"s; // TODO: change this later
  std::vector<std::string> passToCompiler = extraArgs;
  passToCompiler.emplace_back(dcrPath + "/src/DcrMain.cpp");
  passToCompiler.emplace_back(dcrPath + "/src/Test.cpp");

  std::mutex jobsLock;
  auto getJob = [&jobs, &jobsLock] {
    std::lock_guard g(jobsLock);
    if (jobs.empty()) { return std::unique_ptr<Job>(); }
    auto job = std::move(jobs.back());
    jobs.pop_back();
    return job;
  };

  auto pushJob = [&jobs, &jobsLock]<typename T>(T&& job) {
    std::lock_guard g(jobsLock);
    jobs.push_back(std::forward<T>(job));
  };

  std::mutex otherUpdatersLock;
  std::vector<std::string> failedTestPaths;
  auto threadRunnerFn = [&getJob, &pushJob, &successful, &skipped, &passToCompiler, &dcrParams, &otherUpdatersLock, &failedTestPaths] {
    bool shouldTerminate = false;
    while (!shouldTerminate) {
      if (auto job = getJob()) {
        std::stringstream out;
        auto const [status, outputText, errorText] = executeJob(job, passToCompiler);
        auto const asStr = toString(job);
        auto const wasSuccessful = job->expected == TestStepResult::Success ? status : !status;
        if (wasSuccessful) {
          ++successful;
          out << asStr + " successful\n";

          std::lock_guard g(otherUpdatersLock);
          std::cout << out.str();
        } else {
          out << asStr + " failed\n";
          if (dcrParams.verbose) {
            out << "  Output: " << outputText << " " << errorText << "\n";
          }

          std::lock_guard g(otherUpdatersLock);
          failedTestPaths.emplace_back(asStr);
          std::cout << out.str();
        }

        if (job->creates) {
          if (wasSuccessful) {
            pushJob(std::move(job->creates));
          } else {
            ++skipped;
          }
        }
      } else {
        shouldTerminate = true;
      }
    }
  };

  std::vector<std::thread> runners;
  for (int thIdx = 0; thIdx < std::min(dcrParams.threadCount, static_cast<int>(jobs.size())); ++ thIdx) {
    runners.emplace_back(threadRunnerFn);
  }

  for (auto& runner: runners) {
    runner.join();
  }

  std::cout << total << " tests ran, out of which " << successful << " were successful, " << skipped << " were skipped";
  if (!failedTestPaths.empty()) {
    std::cout << " and the following " << (total - successful - skipped) << " failed:\n";
  } else {
    std::cout << '\n';
  }

  for (auto const& testPath: failedTestPaths) {
    std::cout << "  " << testPath << '\n';
  }

  return total != skipped + successful;
}
} // namespace

auto run(int const argc, char const* const* argv) -> int {
  if (argc == 1) {
    std::cerr << "No path/file provided to DCR test runner\n";
    return 1;
  }

  std::string inputFileOrDir;
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
          [&dcrParams](auto const& params) { dcrParams.threadCount = std::strtol(params[1].c_str(), nullptr, 10); },
          [](auto const& arg) { return arg == "-j"; },
          [](auto const& arg) { return std::ranges::all_of(arg, [](char const c){ return c >= '0' && c <= '9'; }); }
      ),
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
  return execute(tests, passedToCompiler, dcrParams);
}
} // namespace dcr
