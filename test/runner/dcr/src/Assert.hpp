//
// Created by loghin on 12/1/23.
//

#ifndef CDS_DCR_ASSERT_HPP
#define CDS_DCR_ASSERT_HPP

#include <utility>
#include <sstream>

#define ASSERT_EQ(lhs, rhs) \
  ::dcr::internal::compare<::dcr::internal::CompareType::Eq>(__FILE__, __LINE__, #lhs, #rhs, lhs, rhs)

#define ASSERT_NE(lhs, rhs) \
  ::dcr::internal::compare<::dcr::internal::CompareType::Ne>(__FILE__, __LINE__, #lhs, #rhs, lhs, rhs)

#define ASSERT_LT(lhs, rhs) \
  ::dcr::internal::compare<::dcr::internal::CompareType::Lt>(__FILE__, __LINE__, #lhs, #rhs, lhs, rhs)

#define ASSERT_LE(lhs, rhs) \
  ::dcr::internal::compare<::dcr::internal::CompareType::Le>(__FILE__, __LINE__, #lhs, #rhs, lhs, rhs)

#define ASSERT_GT(lhs, rhs) \
  ::dcr::internal::compare<::dcr::internal::CompareType::Gt>(__FILE__, __LINE__, #lhs, #rhs, lhs, rhs)

#define ASSERT_GE(lhs, rhs) \
  ::dcr::internal::compare<::dcr::internal::CompareType::Ge>(__FILE__, __LINE__, #lhs, #rhs, lhs, rhs)

#define ASSERT_TRUE(expr) \
  ::dcr::internal::affirm(__FILE__, __LINE__, #expr, expr)

#define ASSERT_FALSE(expr) \
  ::dcr::internal::deny(__FILE__, __LINE__, #expr, expr)

namespace dcr {
namespace internal {
enum class CompareType { Eq, Ne, Lt, Le, Gt, Ge };
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

template <> struct Comparator<CompareType::Lt> {
  static constexpr auto expectationDesc = "Expected left value to be less than right value";
  template <typename Lhs, typename Rhs> static auto invoke(Lhs&& lhs, Rhs&& rhs) -> bool {
    return std::forward<Lhs>(lhs) < std::forward<Rhs>(rhs);
  }
};

template <> struct Comparator<CompareType::Le> {
  static constexpr auto expectationDesc = "Expected left value to be less than right value";
  template <typename Lhs, typename Rhs> static auto invoke(Lhs&& lhs, Rhs&& rhs) -> bool {
    return std::forward<Lhs>(lhs) <= std::forward<Rhs>(rhs);
  }
};

template <> struct Comparator<CompareType::Gt> {
  static constexpr auto expectationDesc = "Expected left value to be less than right value";
  template <typename Lhs, typename Rhs> static auto invoke(Lhs&& lhs, Rhs&& rhs) -> bool {
    return std::forward<Lhs>(lhs) > std::forward<Rhs>(rhs);
  }
};

template <> struct Comparator<CompareType::Ge> {
  static constexpr auto expectationDesc = "Expected left value to be less than right value";
  template <typename Lhs, typename Rhs> static auto invoke(Lhs&& lhs, Rhs&& rhs) -> bool {
    return std::forward<Lhs>(lhs) >= std::forward<Rhs>(rhs);
  }
};

template <typename> using LocalVoid = void;
template <typename T> auto localVOf() -> T;
template <typename T> auto localLVOf() -> T;

template <typename T, typename = void> struct StreamPrint {
  template <typename VT> static auto doIt(std::ostream& out, VT const& value) -> void {
    out << "Unknown@" << &value;
  }
};

template <typename T> struct StreamPrint<T, LocalVoid<decltype(localLVOf<std::ostream>() << localVOf<T>())>> {
  template <typename VT> static auto doIt(std::ostream& out, VT&& value) -> void {
    out << std::forward<VT>(value);
  }
};

template <typename T> auto descOperand(std::string const& asStr, T&& op) -> std::string {
  std::stringstream oss;
  oss << "  " << asStr;

  std::stringstream valueOss;
  StreamPrint<T>::doIt(valueOss, std::forward<T>(op));
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

template <CompareType type, typename Lhs, typename Rhs = Lhs> auto compare(
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

template <typename Expr> auto affirm(
    char const* file,
    int const line,
    char const* exprAsStr,
    Expr&& expr
) -> void {
  if (!std::forward<Expr>(expr)) {
    std::stringstream oss;
    oss << file << ":" << line << ": Failure\n"
      << "Expected expression to be true:\n"
      << descOperand(exprAsStr, std::forward<Expr>(expr)) << '\n';
    throw AssertionFailure(oss.str());
  }
}

template <typename Expr> auto deny(
    char const* file,
    int const line,
    char const* exprAsStr,
    Expr&& expr
) -> void {
  if (std::forward<Expr>(expr)) {
    std::stringstream oss;
    oss << file << ":" << line << ": Failure\n"
      << "Expected expression to be false:\n"
      << descOperand(exprAsStr, std::forward<Expr>(expr)) << '\n';
    throw AssertionFailure(oss.str());
  }
}
} // namespace internal
} // namespace dcr

#endif // CDS_DCR_ASSERT_HPP
