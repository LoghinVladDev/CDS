// DCR-TEST
// STEPS: compile(linux:gcc;linux:clang)
// STD: 11

#include "UnitTest.hpp"
#include "../../../src/meta/Base.hpp"

using namespace cds;
using namespace cds::meta;

TEST(MetaBase, IsSame) {
  static_assert(IsSame<S32, S32>::value, "Failed IsSame");
}

template <typename, typename = void> struct HasInvoke : False {};
template <typename T> struct HasInvoke<T, Void<decltype(&T::operator())>> : True {};

struct Invokable {int operator()() const {return 0;}};

TEST(MetaBase, Void) {
  static_assert(IsSame<Void<>, void>::value, "Failed Void");
  static_assert(!HasInvoke<int>::value, "Failed Void");
  static_assert(HasInvoke<Invokable>::value, "Failed Void");
}

TEST(MetaBase, Integral) {
  using I = Integral<int, 5>;
  static_assert(I::value == 5, "Failed Integral");
  static_assert(IsSame<I::ValueType, int>::value, "Failed Integral");
  static_assert(IsSame<I::Type, I>::value, "Failed Integral");
}

TEST(MetaBase, Bool) {
  static_assert(IsSame<Bool<true>, True>::value, "Failed Bool");
  static_assert(IsSame<Bool<false>, False>::value, "Failed Bool");
}

TEST(MetaBase, valueTypes) {
  static_assert(IsSame<decltype(value<int>()), int>::value, "Failed value");
  static_assert(IsSame<decltype(reference<int>()), int&>::value, "Failed value");
  static_assert(IsSame<decltype(address<int>()), int*>::value, "Failed value");
}

TEST(MetaBase, Conditional) {
  using intForSure = Conditional<true, int, float>;
  using floatForSure = Conditional<false, int, float>;
  static_assert(IsSame<intForSure, int>::value, "Failed Conditional");
  static_assert(IsSame<floatForSure, float>::value, "Failed Conditional");
}

TEST(MetaBase, IsCdsIntegral) {
  static_assert(IsSame<impl::IsCdsIntegral<True>::Type, True>::value, "Failed IsCdsIntegral");
  static_assert(IsSame<impl::IsCdsIntegral<std::true_type>::Type, False>::value, "Failed IsCdsIntegral");
}

TEST(MetaBase, IsStdIntegral) {
  static_assert(IsSame<impl::IsStdIntegral<True>::Type, False>::value, "Failed IsStdIntegral");
  static_assert(IsSame<impl::IsStdIntegral<std::true_type>::Type, True>::value, "Failed IsStdIntegral");
}

TEST(MetaBase, ConvertIntegral) {
  static_assert(IsSame<impl::ConvertIntegral<std::true_type>::Type, True>::value, "Failed ConvertIntegral");
  static_assert(IsSame<impl::ConvertIntegral<True>::Type, True>::value, "Failed ConvertIntegral");
}

TEST(MetaBase, And) {
  static_assert(IsSame<And<False>, False>::value, "Failed And");
  static_assert(IsSame<And<True>, True>::value, "Failed And");
  static_assert(IsSame<And<False, False>, False>::value, "Failed And");
  static_assert(IsSame<And<False, True>, False>::value, "Failed And");
  static_assert(IsSame<And<True, False>, False>::value, "Failed And");
  static_assert(IsSame<And<True, True>, True>::value, "Failed And");
  static_assert(IsSame<And<False, False, False>, False>::value, "Failed And");
  static_assert(IsSame<And<False, False, True>, False>::value, "Failed And");
  static_assert(IsSame<And<False, True, False>, False>::value, "Failed And");
  static_assert(IsSame<And<True, False, False>, False>::value, "Failed And");
  static_assert(IsSame<And<False, True, True>, False>::value, "Failed And");
  static_assert(IsSame<And<True, False, True>, False>::value, "Failed And");
  static_assert(IsSame<And<True, True, False>, False>::value, "Failed And");
  static_assert(IsSame<And<True, True, True>, True>::value, "Failed And");
  static_assert(IsSame<And<std::false_type>, False>::value, "Failed And");
  static_assert(IsSame<And<std::true_type>, True>::value, "Failed And");
  static_assert(IsSame<And<std::false_type, False>, False>::value, "Failed And");
  static_assert(IsSame<And<std::false_type, True>, False>::value, "Failed And");
  static_assert(IsSame<And<std::true_type, False>, False>::value, "Failed And");
  static_assert(IsSame<And<std::true_type, True>, True>::value, "Failed And");
  static_assert(IsSame<And<std::false_type, False, False>, False>::value, "Failed And");
  static_assert(IsSame<And<std::false_type, False, True>, False>::value, "Failed And");
  static_assert(IsSame<And<std::false_type, True, False>, False>::value, "Failed And");
  static_assert(IsSame<And<std::true_type, False, False>, False>::value, "Failed And");
  static_assert(IsSame<And<std::false_type, True, True>, False>::value, "Failed And");
  static_assert(IsSame<And<std::true_type, False, True>, False>::value, "Failed And");
  static_assert(IsSame<And<std::true_type, True, False>, False>::value, "Failed And");
  static_assert(IsSame<And<std::true_type, True, True>, True>::value, "Failed And");
}

TEST(MetaBase, Or) {
  static_assert(IsSame<Or<False>, False>::value, "Failed And");
  static_assert(IsSame<Or<True>, True>::value, "Failed And");
  static_assert(IsSame<Or<False, False>, False>::value, "Failed And");
  static_assert(IsSame<Or<False, True>, True>::value, "Failed And");
  static_assert(IsSame<Or<True, False>, True>::value, "Failed And");
  static_assert(IsSame<Or<True, True>, True>::value, "Failed And");
  static_assert(IsSame<Or<False, False, False>, False>::value, "Failed And");
  static_assert(IsSame<Or<False, False, True>, True>::value, "Failed And");
  static_assert(IsSame<Or<False, True, False>, True>::value, "Failed And");
  static_assert(IsSame<Or<True, False, False>, True>::value, "Failed And");
  static_assert(IsSame<Or<False, True, True>, True>::value, "Failed And");
  static_assert(IsSame<Or<True, False, True>, True>::value, "Failed And");
  static_assert(IsSame<Or<True, True, False>, True>::value, "Failed And");
  static_assert(IsSame<Or<True, True, True>, True>::value, "Failed And");
  static_assert(IsSame<Or<std::false_type>, False>::value, "Failed And");
  static_assert(IsSame<Or<std::true_type>, True>::value, "Failed And");
  static_assert(IsSame<Or<std::false_type, False>, False>::value, "Failed And");
  static_assert(IsSame<Or<std::false_type, True>, True>::value, "Failed And");
  static_assert(IsSame<Or<std::true_type, False>, True>::value, "Failed And");
  static_assert(IsSame<Or<std::true_type, True>, True>::value, "Failed And");
  static_assert(IsSame<Or<std::false_type, False, False>, False>::value, "Failed And");
  static_assert(IsSame<Or<std::false_type, False, True>, True>::value, "Failed And");
  static_assert(IsSame<Or<std::false_type, True, False>, True>::value, "Failed And");
  static_assert(IsSame<Or<std::true_type, False, False>, True>::value, "Failed And");
  static_assert(IsSame<Or<std::false_type, True, True>, True>::value, "Failed And");
  static_assert(IsSame<Or<std::true_type, False, True>, True>::value, "Failed And");
  static_assert(IsSame<Or<std::true_type, True, False>, True>::value, "Failed And");
  static_assert(IsSame<Or<std::true_type, True, True>, True>::value, "Failed And");
}

TEST(MetaBase, Not) {
  static_assert(IsSame<Not<False>, True>::value, "Failed Not");
  static_assert(IsSame<Not<True>, False>::value, "Failed Not");
  static_assert(IsSame<Not<std::false_type>, True>::value, "Failed Not");
  static_assert(IsSame<Not<std::true_type>, False>::value, "Failed Not");
}

template <typename T, EnableIf<IsSame<T, int>::value, int> = 0> constexpr int enabled() { return 1; }
template <typename T, EnableIf<IsSame<T, float>::value, int> = 0> constexpr int enabled() { return 2; }

TEST(MetaBase, EnableIf) {
  static_assert(enabled<int>() == 1, "Failed EnableIf");
  static_assert(enabled<float>() == 2, "Failed EnableIf");
}
