// DCR-TEST
// STEPS: compile(linux:gcc;linux:clang),run(linux:clang)
// STD: 11

#include <cds/meta/Base>
#include "UnitTest.hpp"

#include <cds/meta/Compiler>

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
  static_assert(Eq<Bool<true>, True>::value, "Failed Bool");
  static_assert(Eq<Bool<false>, False>::value, "Failed Bool");
}

TEST(MetaBase, Int) {
  static_assert(Eq<Int<0>, Integral<int, 0>>::value, "Failed Int");
  static_assert(Eq<Int<1>, Integral<int, 1>>::value, "Failed Int");
}

TEST(MetaBase, valueTypes) {
  static_assert(IsSame<decltype(value<int>()), int>::value, "Failed value");
  static_assert(IsSame<decltype(lvalue<int>()), int&>::value, "Failed value");
  static_assert(IsSame<decltype(rvalue<int>()), int&&>::value, "Failed value");
  static_assert(IsSame<decltype(address<int>()), int*>::value, "Failed value");
}

TEST(MetaBase, Conditional) {
  using intForSure = Conditional<True , int, float>;
  using floatForSure = Conditional<False, int, float>;
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
  static_assert(Eq<And<False, False>, False>::value, "Failed And");
  static_assert(Eq<And<False, True>, False>::value, "Failed And");
  static_assert(Eq<And<True, False>, False>::value, "Failed And");
  static_assert(Eq<And<True, True>, True>::value, "Failed And");
  static_assert(Eq<And<False, False, False>, False>::value, "Failed And");
  static_assert(Eq<And<False, False, True>, False>::value, "Failed And");
  static_assert(Eq<And<False, True, False>, False>::value, "Failed And");
  static_assert(Eq<And<True, False, False>, False>::value, "Failed And");
  static_assert(Eq<And<False, True, True>, False>::value, "Failed And");
  static_assert(Eq<And<True, False, True>, False>::value, "Failed And");
  static_assert(Eq<And<True, True, False>, False>::value, "Failed And");
  static_assert(Eq<And<True, True, True>, True>::value, "Failed And");

  static_assert(Eq<And<std::false_type, False>, False>::value, "Failed And");
  static_assert(Eq<And<std::false_type, True>, False>::value, "Failed And");
  static_assert(Eq<And<std::true_type, False>, False>::value, "Failed And");
  static_assert(Eq<And<std::true_type, True>, True>::value, "Failed And");
  static_assert(Eq<And<std::false_type, False, False>, False>::value, "Failed And");
  static_assert(Eq<And<std::false_type, False, True>, False>::value, "Failed And");
  static_assert(Eq<And<std::false_type, True, False>, False>::value, "Failed And");
  static_assert(Eq<And<std::true_type, False, False>, False>::value, "Failed And");
  static_assert(Eq<And<std::false_type, True, True>, False>::value, "Failed And");
  static_assert(Eq<And<std::true_type, False, True>, False>::value, "Failed And");
  static_assert(Eq<And<std::true_type, True, False>, False>::value, "Failed And");
  static_assert(Eq<And<std::true_type, True, True>, True>::value, "Failed And");
}

TEST(MetaBase, Or) {
  static_assert(Eq<Or<False, False>, False>::value, "Failed And");
  static_assert(Eq<Or<False, True>, True>::value, "Failed And");
  static_assert(Eq<Or<True, False>, True>::value, "Failed And");
  static_assert(Eq<Or<True, True>, True>::value, "Failed And");
  static_assert(Eq<Or<False, False, False>, False>::value, "Failed And");
  static_assert(Eq<Or<False, False, True>, True>::value, "Failed And");
  static_assert(Eq<Or<False, True, False>, True>::value, "Failed And");
  static_assert(Eq<Or<True, False, False>, True>::value, "Failed And");
  static_assert(Eq<Or<False, True, True>, True>::value, "Failed And");
  static_assert(Eq<Or<True, False, True>, True>::value, "Failed And");
  static_assert(Eq<Or<True, True, False>, True>::value, "Failed And");
  static_assert(Eq<Or<True, True, True>, True>::value, "Failed And");

  static_assert(Eq<Or<std::false_type, False>, False>::value, "Failed And");
  static_assert(Eq<Or<std::false_type, True>, True>::value, "Failed And");
  static_assert(Eq<Or<std::true_type, False>, True>::value, "Failed And");
  static_assert(Eq<Or<std::true_type, True>, True>::value, "Failed And");
  static_assert(Eq<Or<std::false_type, False, False>, False>::value, "Failed And");
  static_assert(Eq<Or<std::false_type, False, True>, True>::value, "Failed And");
  static_assert(Eq<Or<std::false_type, True, False>, True>::value, "Failed And");
  static_assert(Eq<Or<std::true_type, False, False>, True>::value, "Failed And");
  static_assert(Eq<Or<std::false_type, True, True>, True>::value, "Failed And");
  static_assert(Eq<Or<std::true_type, False, True>, True>::value, "Failed And");
  static_assert(Eq<Or<std::true_type, True, False>, True>::value, "Failed And");
  static_assert(Eq<Or<std::true_type, True, True>, True>::value, "Failed And");
}

TEST(MetaBase, Not) {
  static_assert(Eq<Not<False>, True>::value, "Failed Not");
  static_assert(Eq<Not<True>, False>::value, "Failed Not");
  static_assert(Eq<Not<std::false_type>, True>::value, "Failed Not");
  static_assert(Eq<Not<std::true_type>, False>::value, "Failed Not");
}

TEST(MetaBase, Eq) {
  static_assert(Eq<True, True>::value, "Failed Eq");
  static_assert(!Eq<False, True>::value, "Failed Eq");
  static_assert(Eq<False, False, False>::value, "Failed Eq");
  static_assert(!Eq<False, True, False>::value, "Failed Eq");
  static_assert(Eq<Int<0>, Int<0>, Int<0>>::value, "Failed Eq");
  static_assert(!Eq<Int<0>, Int<1>, Int<0>>::value, "Failed Eq");
  static_assert(!Eq<Int<1>, Int<0>, Int<1>>::value, "Failed Eq");
}

TEST(MetaBase, Ne) {
  static_assert(!Ne<True, True>::value, "Failed Ne");
  static_assert(!Ne<False, False>::value, "Failed Ne");
  static_assert(Ne<True, False>::value, "Failed Ne");
  static_assert(Ne<False, True>::value, "Failed Ne");
  static_assert(Ne<Int<0>, Int<1>>::value, "Failed Ne");
  static_assert(!Ne<Int<1>, Int<1>>::value, "Failed Ne");
}

TEST(MetaBase, Lt) {
  static_assert(Lt<Int<0>, Int<1>>::value, "Failed Lt");
  static_assert(!Lt<Int<1>, Int<1>>::value, "Failed Lt");
  static_assert(!Lt<Int<1>, Int<0>>::value, "Failed Lt");
}

TEST(MetaBase, Le) {
  static_assert(Le<Int<0>, Int<1>>::value, "Failed Le");
  static_assert(Le<Int<1>, Int<1>>::value, "Failed Le");
  static_assert(!Le<Int<1>, Int<0>>::value, "Failed Le");
}

TEST(MetaBase, Gt) {
  static_assert(!Gt<Int<0>, Int<1>>::value, "Failed Gt");
  static_assert(!Gt<Int<1>, Int<1>>::value, "Failed Gt");
  static_assert(Gt<Int<1>, Int<0>>::value, "Failed Gt");
}

TEST(MetaBase, Ge) {
  static_assert(!Ge<Int<0>, Int<1>>::value, "Failed Ge");
  static_assert(Ge<Int<1>, Int<1>>::value, "Failed Ge");
  static_assert(Ge<Int<1>, Int<0>>::value, "Failed Ge");
}

template <typename T, EnableIf<IsSame<T, int>> = 0> constexpr int enabled() { return 1; }
template <typename T, EnableIf<IsSame<T, float>> = 0> constexpr int enabled() { return 2; }

template <typename T, EnableIf<std::is_same<T, int>> = 0> constexpr int enabledStd() { return 1; }
template <typename T, EnableIf<std::is_same<T, float>> = 0> constexpr int enabledStd() { return 2; }

template <typename T> constexpr EnableIf<IsSame<T, int>> enableIfRet() { return 1; }
template <typename T> constexpr EnableIf<IsSame<T, float>> enableIfRet() { return 2; }

template <typename T> constexpr ReturnIf<bool, IsSame<T, int>> returnIf() { return false; }
template <typename T> constexpr ReturnIf<bool, IsSame<T, float>> returnIf() { return true; }

TEST(MetaBase, EnableIf) {
  static_assert(enabled<int>() == 1, "Failed EnableIf");
  static_assert(enabled<float>() == 2, "Failed EnableIf");
  static_assert(enabledStd<int>() == 1, "Failed EnableIf");
  static_assert(enabledStd<float>() == 2, "Failed EnableIf");
  static_assert(enableIfRet<int>() == 1, "Failed EnableIf");
  static_assert(enableIfRet<float>() == 2, "Failed EnableIf");
  static_assert(!returnIf<int>(), "Failed ReturnIf");
  static_assert(returnIf<float>(), "Failed ReturnIf");
}

TEST(MetaBase, BindLeft) {
  static_assert(Eq<True, All<BindLeft<IsSame, True>::Type, True>>::value, "Failed BindLeft");
  static_assert(Eq<False, All<BindLeft<IsSame, True>::Type, False>>::value, "Failed BindLeft");
  static_assert(Eq<True, All<BindLeft<BindLeft<Eq, True>::Type, True>::Type, True>>::value, "Failed BindLeft");
  static_assert(Eq<False, All<BindLeft<BindLeft<Eq, False>::Type, True>::Type, True>>::value, "Failed BindLeft");
  static_assert(Eq<False, All<BindLeft<BindLeft<Eq, True>::Type, False>::Type, True>>::value, "Failed BindLeft");
  static_assert(Eq<False, All<BindLeft<BindLeft<Eq, True>::Type, True>::Type, False>>::value, "Failed BindLeft");
  static_assert(Eq<False, All<BindLeft<Gt, Int<1>>::Type, Int<2>>>::value, "Failed BindLeft");
}

TEST(MetaBase, BindRight) {
  static_assert(Eq<True, All<BindRight<IsSame, True>::Type, True>>::value, "Failed BindRight");
  static_assert(Eq<False, All<BindRight<IsSame, True>::Type, False>>::value, "Failed BindRight");
  static_assert(Eq<True, All<BindRight<BindRight<Eq, True>::Type, True>::Type, True>>::value, "Failed BindRight");
  static_assert(Eq<False, All<BindRight<BindRight<Eq, False>::Type, True>::Type, True>>::value, "Failed BindRight");
  static_assert(Eq<False, All<BindRight<BindRight<Eq, True>::Type, False>::Type, True>>::value, "Failed BindRight");
  static_assert(Eq<False, All<BindRight<BindRight<Eq, True>::Type, True>::Type, False>>::value, "Failed BindRight");
  static_assert(Eq<False, All<BindRight<Gt, Int<2>>::Type, Int<1>>>::value, "Failed BindRight");
}

TEST(MetaBase, Bind) {
  static_assert(Eq<True, All<Bind<IsSame, True, Ph<0>>::Type, True>>::value, "Failed Bind");
  static_assert(Ne<True, All<Bind<IsSame, True, Ph<0>>::Type, False>>::value, "Failed Bind");
  static_assert(Ne<True, All<Bind<IsSame, False, Ph<0>>::Type, True>>::value, "Failed Bind");
  static_assert(Eq<True, All<Bind<IsSame, False, Ph<0>>::Type, False>>::value, "Failed Bind");
  static_assert(Eq<True, All<Bind<Bind<Eq, Int<0>, Ph<0>, Ph<1>>::Type, Int<0>, Ph<0>>::Type, Int<0>>>::value, "Failed Bind");
  static_assert(!Eq<True, All<Bind<Bind<Eq, Int<0>, Ph<0>, Ph<1>>::Type, Int<0>, Ph<0>>::Type, Int<1>>>::value, "Failed Bind");
  static_assert(!Eq<True, All<Bind<Bind<Eq, Int<0>, Ph<0>, Ph<1>>::Type, Int<1>, Ph<0>>::Type, Int<0>>>::value, "Failed Bind");
  static_assert(!Eq<True, All<Bind<Bind<Eq, Int<1>, Ph<0>, Ph<1>>::Type, Int<0>, Ph<0>>::Type, Int<0>>>::value, "Failed Bind");
}

TEST(MetaBase, Unless) {
  static_assert(Eq<False, Unless<IsSame>::Type<int, int>>::value, "Failed Bind");
  static_assert(Eq<True, Unless<IsSame>::Type<int, float>>::value, "Failed Bind");
}

TEST(MetaBase, BindUnless) {
  static_assert(Eq<True, All<Bind<Unless<IsSame>::Type, void, Ph<0>>::Type, int, float, double>>::value, "Failed Bind with Unless");
  static_assert(Eq<False, All<Bind<Unless<IsSame>::Type, void, Ph<0>>::Type, int, void, double>>::value, "Failed Bind with Unless");
}
