//
// Created by loghin on 12/1/23.
//

#ifndef CDS_DCR_ASSERT_HPP
#define CDS_DCR_ASSERT_HPP

#include <utility>
#include <sstream>

#define ASSERT_EQ(lhs, rhs)                                                         \
  ::dcr::compare<::dcr::CompareType::Eq>(__FILE__, __LINE__, #lhs, #rhs, lhs, rhs)

#define ASSERT_NE(lhs, rhs) \
  ::dcr::compare<::dcr::CompareType::Ne>(__FILE__, __LINE__, #lhs, #rhs, lhs, rhs)

namespace dcr {
enum class CompareType { Eq, Ne };
template <CompareType> struct Comparator {};

template <> struct Comparator<CompareType::Eq> {
  static constexpr auto expectationDesc = "Expected equality of these values";
  template <typename Lhs, typename Rhs> static auto invoke(Lhs&& lhs, Rhs&& rhs) -> bool {
    return std::forward<Lhs>(lhs) == std::forward<Rhs>(rhs);
  }
};

template <> struct Comparator<CompareType::Ne> {
  static constexpr auto expectationDesc = "Expected inequality of these values";
  template <typename Lhs, typename Rhs> static auto invoke(Lhs&& lhs, Rhs&& rhs) -> bool {
    return std::forward<Lhs>(lhs) != std::forward<Rhs>(rhs);
  }
};

template <typename T> auto descOperand(std::string const& asStr, T&& op) -> std::string {
  std::stringstream oss;
  oss << "  " << asStr;

  std::stringstream valueOss;
  valueOss << std::forward<T>(op);
  auto const valueAsStr = valueOss.str();
  if (asStr != valueAsStr) {
    oss << "\n    Which is: " << valueAsStr;
  }

  return oss.str();
}

class AssertionFailure final : public std::exception {
public:
  explicit AssertionFailure(std::string message): _message(std::move(message)) {}
  [[nodiscard]] auto what() const noexcept -> char const* override {
    return _message.c_str();
  }
private:
  std::string _message;
};

template <CompareType type, typename Lhs, typename Rhs = Lhs>
auto compare(
    char const* file,
    int const line,
    char const* lhsAsStr,
    char const* rhsAsStr,
    Lhs&& lhs,
    Rhs&& rhs
) -> void {
  using Op = Comparator<type>;
  auto const result = Op::invoke(std::forward<Lhs>(lhs), std::forward<Rhs>(rhs));
  if (!result) {
    std::stringstream oss;
    oss << file << ":" << line << ": Failure\n"
      << Op::expectationDesc << ":\n"
      << descOperand(lhsAsStr, std::forward<Lhs>(lhs)) << '\n'
      << descOperand(rhsAsStr, std::forward<Rhs>(rhs)) << '\n';
    throw AssertionFailure(oss.str());
  }
}
} // namespace dcr

#endif // CDS_DCR_ASSERT_HPP
