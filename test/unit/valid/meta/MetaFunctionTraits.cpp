// DCR-TEST
// STEPS: compile(linux:gcc;linux:clang)
// STD: 11-2b

#include <cds/meta/FunctionTraits>
#include <cds/meta/Base>
#include "UnitTest.hpp"

using namespace cds;
using namespace cds::meta;

int f1();
long f2(int, long);
void f3(double);

int f1_n();
long f2_n(int, long);
void f3_n(double);

class X {
public:
  void f1();
  void f2() const;
  void f3() volatile;
  void f4() const volatile;
  void f5()&;
  void f6() const&;
  void f7() volatile&;
  void f8() const volatile&;
  void f9()&&;
  void f10() const&&;
  void f11() volatile&&;
  void f12() const volatile&&;

  int f13();
  long f14(int, long);

  void f1_n() noexcept;
  void f2_n() const noexcept;
  void f3_n() volatile noexcept;
  void f4_n() const volatile noexcept;
  void f5_n()& noexcept;
  void f6_n() const& noexcept;
  void f7_n() volatile& noexcept;
  void f8_n() const volatile& noexcept;
  void f9_n()&& noexcept;
  void f10_n() const&& noexcept;
  void f11_n() volatile&& noexcept;
  void f12_n() const volatile&& noexcept;
  int f13_n() noexcept;
  long f14_n(int, long) noexcept;
};

TEST(FunctionTraits, ReturnOf) {
  static_assert(IsSame<typename FunctionTraits<decltype(f1)>::Return, int>::value, "Failed ReturnOf");
  static_assert(IsSame<ReturnOf<decltype(f1)>, int>::value, "Failed ReturnOf");
  static_assert(IsSame<ReturnOf<int()>, int>::value, "Failed ReturnOf");
  static_assert(IsSame<ReturnOf<decltype(f2)>, long>::value, "Failed ReturnOf");
  static_assert(IsSame<ReturnOf<long(int, long)>, long>::value, "Failed ReturnOf");
  static_assert(IsSame<ReturnOf<decltype(f3)>, void>::value, "Failed ReturnOf");
  static_assert(IsSame<ReturnOf<void(int)>, void>::value, "Failed ReturnOf");

  static_assert(IsSame<ReturnOf<decltype(f1_n)>, int>::value, "Failed ReturnOf");
  static_assert(IsSame<ReturnOf<int()>, int>::value, "Failed ReturnOf");
  static_assert(IsSame<ReturnOf<decltype(f2_n)>, long>::value, "Failed ReturnOf");
  static_assert(IsSame<ReturnOf<long(int, long)>, long>::value, "Failed ReturnOf");
  static_assert(IsSame<ReturnOf<decltype(f3_n)>, void>::value, "Failed ReturnOf");
  static_assert(IsSame<ReturnOf<void(int)>, void>::value, "Failed ReturnOf");

  static_assert(IsSame<ReturnOf<decltype(&X::f1)>, void>::value, "Failed ReturnOf");
  static_assert(IsSame<ReturnOf<decltype(&X::f2)>, void>::value, "Failed ReturnOf");
  static_assert(IsSame<ReturnOf<decltype(&X::f3)>, void>::value, "Failed ReturnOf");
  static_assert(IsSame<ReturnOf<decltype(&X::f4)>, void>::value, "Failed ReturnOf");
  static_assert(IsSame<ReturnOf<decltype(&X::f5)>, void>::value, "Failed ReturnOf");
  static_assert(IsSame<ReturnOf<decltype(&X::f6)>, void>::value, "Failed ReturnOf");
  static_assert(IsSame<ReturnOf<decltype(&X::f7)>, void>::value, "Failed ReturnOf");
  static_assert(IsSame<ReturnOf<decltype(&X::f8)>, void>::value, "Failed ReturnOf");
  static_assert(IsSame<ReturnOf<decltype(&X::f9)>, void>::value, "Failed ReturnOf");
  static_assert(IsSame<ReturnOf<decltype(&X::f10)>, void>::value, "Failed ReturnOf");
  static_assert(IsSame<ReturnOf<decltype(&X::f11)>, void>::value, "Failed ReturnOf");
  static_assert(IsSame<ReturnOf<decltype(&X::f12)>, void>::value, "Failed ReturnOf");
  static_assert(IsSame<ReturnOf<decltype(&X::f13)>, int>::value, "Failed ReturnOf");
  static_assert(IsSame<ReturnOf<decltype(&X::f14)>, long>::value, "Failed ReturnOf");

  static_assert(IsSame<ReturnOf<decltype(&X::f1_n)>, void>::value, "Failed ReturnOf");
  static_assert(IsSame<ReturnOf<decltype(&X::f2_n)>, void>::value, "Failed ReturnOf");
  static_assert(IsSame<ReturnOf<decltype(&X::f3_n)>, void>::value, "Failed ReturnOf");
  static_assert(IsSame<ReturnOf<decltype(&X::f4_n)>, void>::value, "Failed ReturnOf");
  static_assert(IsSame<ReturnOf<decltype(&X::f5_n)>, void>::value, "Failed ReturnOf");
  static_assert(IsSame<ReturnOf<decltype(&X::f6_n)>, void>::value, "Failed ReturnOf");
  static_assert(IsSame<ReturnOf<decltype(&X::f7_n)>, void>::value, "Failed ReturnOf");
  static_assert(IsSame<ReturnOf<decltype(&X::f8_n)>, void>::value, "Failed ReturnOf");
  static_assert(IsSame<ReturnOf<decltype(&X::f9_n)>, void>::value, "Failed ReturnOf");
  static_assert(IsSame<ReturnOf<decltype(&X::f10_n)>, void>::value, "Failed ReturnOf");
  static_assert(IsSame<ReturnOf<decltype(&X::f11_n)>, void>::value, "Failed ReturnOf");
  static_assert(IsSame<ReturnOf<decltype(&X::f12_n)>, void>::value, "Failed ReturnOf");
  static_assert(IsSame<ReturnOf<decltype(&X::f13_n)>, int>::value, "Failed ReturnOf");
  static_assert(IsSame<ReturnOf<decltype(&X::f14_n)>, long>::value, "Failed ReturnOf");
}

TEST(FunctionTraits, ClassOf) {
  static_assert(IsSame<typename FunctionTraits<decltype(f1)>::Class, void>::value, "Failed ReturnOf");
  static_assert(IsSame<ClassOf<decltype(f1)>, void>::value, "Failed ClassOf");
  static_assert(IsSame<ClassOf<int()>, void>::value, "Failed ClassOf");
  static_assert(IsSame<ClassOf<decltype(f2)>, void>::value, "Failed ClassOf");
  static_assert(IsSame<ClassOf<long(int, long)>, void>::value, "Failed ClassOf");
  static_assert(IsSame<ClassOf<decltype(f3)>, void>::value, "Failed ClassOf");
  static_assert(IsSame<ClassOf<void(int)>, void>::value, "Failed ClassOf");

  static_assert(IsSame<ClassOf<decltype(f1_n)>, void>::value, "Failed ClassOf");
  static_assert(IsSame<ClassOf<int()>, void>::value, "Failed ClassOf");
  static_assert(IsSame<ClassOf<decltype(f2_n)>, void>::value, "Failed ClassOf");
  static_assert(IsSame<ClassOf<long(int, long)>, void>::value, "Failed ClassOf");
  static_assert(IsSame<ClassOf<decltype(f3_n)>, void>::value, "Failed ClassOf");
  static_assert(IsSame<ClassOf<void(int)>, void>::value, "Failed ClassOf");

  static_assert(IsSame<ClassOf<decltype(&X::f1)>, X>::value, "Failed ClassOf");
  static_assert(IsSame<ClassOf<decltype(&X::f2)>, X>::value, "Failed ClassOf");
  static_assert(IsSame<ClassOf<decltype(&X::f3)>, X>::value, "Failed ClassOf");
  static_assert(IsSame<ClassOf<decltype(&X::f4)>, X>::value, "Failed ClassOf");
  static_assert(IsSame<ClassOf<decltype(&X::f5)>, X>::value, "Failed ClassOf");
  static_assert(IsSame<ClassOf<decltype(&X::f6)>, X>::value, "Failed ClassOf");
  static_assert(IsSame<ClassOf<decltype(&X::f7)>, X>::value, "Failed ClassOf");
  static_assert(IsSame<ClassOf<decltype(&X::f8)>, X>::value, "Failed ClassOf");
  static_assert(IsSame<ClassOf<decltype(&X::f9)>, X>::value, "Failed ClassOf");
  static_assert(IsSame<ClassOf<decltype(&X::f10)>, X>::value, "Failed ClassOf");
  static_assert(IsSame<ClassOf<decltype(&X::f11)>, X>::value, "Failed ClassOf");
  static_assert(IsSame<ClassOf<decltype(&X::f12)>, X>::value, "Failed ClassOf");
  static_assert(IsSame<ClassOf<decltype(&X::f13)>, X>::value, "Failed ClassOf");
  static_assert(IsSame<ClassOf<decltype(&X::f14)>, X>::value, "Failed ClassOf");

  static_assert(IsSame<ClassOf<decltype(&X::f1_n)>, X>::value, "Failed ClassOf");
  static_assert(IsSame<ClassOf<decltype(&X::f2_n)>, X>::value, "Failed ClassOf");
  static_assert(IsSame<ClassOf<decltype(&X::f3_n)>, X>::value, "Failed ClassOf");
  static_assert(IsSame<ClassOf<decltype(&X::f4_n)>, X>::value, "Failed ClassOf");
  static_assert(IsSame<ClassOf<decltype(&X::f5_n)>, X>::value, "Failed ClassOf");
  static_assert(IsSame<ClassOf<decltype(&X::f6_n)>, X>::value, "Failed ClassOf");
  static_assert(IsSame<ClassOf<decltype(&X::f7_n)>, X>::value, "Failed ClassOf");
  static_assert(IsSame<ClassOf<decltype(&X::f8_n)>, X>::value, "Failed ClassOf");
  static_assert(IsSame<ClassOf<decltype(&X::f9_n)>, X>::value, "Failed ClassOf");
  static_assert(IsSame<ClassOf<decltype(&X::f10_n)>, X>::value, "Failed ClassOf");
  static_assert(IsSame<ClassOf<decltype(&X::f11_n)>, X>::value, "Failed ClassOf");
  static_assert(IsSame<ClassOf<decltype(&X::f12_n)>, X>::value, "Failed ClassOf");
  static_assert(IsSame<ClassOf<decltype(&X::f13_n)>, X>::value, "Failed ClassOf");
  static_assert(IsSame<ClassOf<decltype(&X::f14_n)>, X>::value, "Failed ClassOf");
}

TEST(FunctionTraits, ArgsOf) {
  static_assert(IsSame<typename FunctionTraits<decltype(f1)>::Args, Tuple<>>::value, "Failed ReturnOf");
  static_assert(IsSame<ArgsOf<decltype(f1)>, Tuple<>>::value, "Failed ArgsOf");
  static_assert(IsSame<ArgsOf<int()>, Tuple<>>::value, "Failed ArgsOf");
  static_assert(IsSame<ArgsOf<decltype(f2)>, Tuple<int, long>>::value, "Failed ArgsOf");
  static_assert(IsSame<ArgsOf<long(int, long)>, Tuple<int, long>>::value, "Failed ArgsOf");
  static_assert(IsSame<ArgsOf<decltype(f3)>, Tuple<double>>::value, "Failed ArgsOf");
  static_assert(IsSame<ArgsOf<void(int)>, Tuple<int>>::value, "Failed ArgsOf");

  static_assert(IsSame<ArgsOf<decltype(f1_n)>, Tuple<>>::value, "Failed ArgsOf");
  static_assert(IsSame<ArgsOf<int()>, Tuple<>>::value, "Failed ArgsOf");
  static_assert(IsSame<ArgsOf<decltype(f2_n)>, Tuple<int, long>>::value, "Failed ArgsOf");
  static_assert(IsSame<ArgsOf<long(int, long)>, Tuple<int, long>>::value, "Failed ArgsOf");
  static_assert(IsSame<ArgsOf<decltype(f3_n)>, Tuple<double>>::value, "Failed ArgsOf");
  static_assert(IsSame<ArgsOf<void(int)>, Tuple<int>>::value, "Failed ArgsOf");

  static_assert(IsSame<ArgsOf<decltype(&X::f1)>, Tuple<>>::value, "Failed ArgsOf");
  static_assert(IsSame<ArgsOf<decltype(&X::f2)>, Tuple<>>::value, "Failed ArgsOf");
  static_assert(IsSame<ArgsOf<decltype(&X::f3)>, Tuple<>>::value, "Failed ArgsOf");
  static_assert(IsSame<ArgsOf<decltype(&X::f4)>, Tuple<>>::value, "Failed ArgsOf");
  static_assert(IsSame<ArgsOf<decltype(&X::f5)>, Tuple<>>::value, "Failed ArgsOf");
  static_assert(IsSame<ArgsOf<decltype(&X::f6)>, Tuple<>>::value, "Failed ArgsOf");
  static_assert(IsSame<ArgsOf<decltype(&X::f7)>, Tuple<>>::value, "Failed ArgsOf");
  static_assert(IsSame<ArgsOf<decltype(&X::f8)>, Tuple<>>::value, "Failed ArgsOf");
  static_assert(IsSame<ArgsOf<decltype(&X::f9)>, Tuple<>>::value, "Failed ArgsOf");
  static_assert(IsSame<ArgsOf<decltype(&X::f10)>, Tuple<>>::value, "Failed ArgsOf");
  static_assert(IsSame<ArgsOf<decltype(&X::f11)>, Tuple<>>::value, "Failed ArgsOf");
  static_assert(IsSame<ArgsOf<decltype(&X::f12)>, Tuple<>>::value, "Failed ArgsOf");
  static_assert(IsSame<ArgsOf<decltype(&X::f13)>, Tuple<>>::value, "Failed ArgsOf");
  static_assert(IsSame<ArgsOf<decltype(&X::f14)>, Tuple<int, long>>::value, "Failed ArgsOf");

  static_assert(IsSame<ArgsOf<decltype(&X::f1_n)>, Tuple<>>::value, "Failed ArgsOf");
  static_assert(IsSame<ArgsOf<decltype(&X::f2_n)>, Tuple<>>::value, "Failed ArgsOf");
  static_assert(IsSame<ArgsOf<decltype(&X::f3_n)>, Tuple<>>::value, "Failed ArgsOf");
  static_assert(IsSame<ArgsOf<decltype(&X::f4_n)>, Tuple<>>::value, "Failed ArgsOf");
  static_assert(IsSame<ArgsOf<decltype(&X::f5_n)>, Tuple<>>::value, "Failed ArgsOf");
  static_assert(IsSame<ArgsOf<decltype(&X::f6_n)>, Tuple<>>::value, "Failed ArgsOf");
  static_assert(IsSame<ArgsOf<decltype(&X::f7_n)>, Tuple<>>::value, "Failed ArgsOf");
  static_assert(IsSame<ArgsOf<decltype(&X::f8_n)>, Tuple<>>::value, "Failed ArgsOf");
  static_assert(IsSame<ArgsOf<decltype(&X::f9_n)>, Tuple<>>::value, "Failed ArgsOf");
  static_assert(IsSame<ArgsOf<decltype(&X::f10_n)>, Tuple<>>::value, "Failed ArgsOf");
  static_assert(IsSame<ArgsOf<decltype(&X::f11_n)>, Tuple<>>::value, "Failed ArgsOf");
  static_assert(IsSame<ArgsOf<decltype(&X::f12_n)>, Tuple<>>::value, "Failed ArgsOf");
  static_assert(IsSame<ArgsOf<decltype(&X::f13_n)>, Tuple<>>::value, "Failed ArgsOf");
  static_assert(IsSame<ArgsOf<decltype(&X::f14_n)>, Tuple<int, long>>::value, "Failed ArgsOf");
}
