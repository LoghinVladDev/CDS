// DCR-TEST
// STEPS: compile(linux:gcc;linux:clang),run(linux:gcc;linux:clang)
// STD: 11-2b

#include "cds/meta/ObjectTraits"
#include "UnitTest.hpp"

using namespace cds;
using namespace cds::meta;

void func();
TEST(MetaObjectTraits, IsTriviallyCopyable) {
  struct A{};
  union B{};
  struct C{explicit C(C const&) noexcept;};
  static_assert(Eq<IsTriviallyCopyable<int>, True>::value, "Failed IsTriviallyCopyable");
  static_assert(IsTriviallyCopyable<unsigned int>::value, "Failed IsTriviallyCopyable");
  static_assert(IsTriviallyCopyable<bool>::value, "Failed IsTriviallyCopyable");
  static_assert(IsTriviallyCopyable<float>::value, "Failed IsTriviallyCopyable");
  static_assert(!IsTriviallyCopyable<void>::value, "Failed IsTriviallyCopyable");
  static_assert(IsTriviallyCopyable<void*>::value, "Failed IsTriviallyCopyable");
  static_assert(IsTriviallyCopyable<A>::value, "Failed IsTriviallyCopyable");
  static_assert(IsTriviallyCopyable<B>::value, "Failed IsTriviallyCopyable");
  static_assert(!IsTriviallyCopyable<C>::value, "Failed IsTriviallyCopyable");
  static_assert(!IsTriviallyCopyable<decltype(func)>::value, "Failed IsTriviallyCopyable");
}

TEST(MetaObjectTraits, IsTriviallyConstructible) {
  struct A{};
  union B{};
  struct C{explicit C() noexcept;};
  struct D{explicit D() noexcept = default; explicit D(int) noexcept;};
  static_assert(Eq<True, IsTriviallyConstructible<int>>::value, "Failed IsTriviallyConstructible");
  static_assert(IsTriviallyConstructible<unsigned int>::value, "Failed IsTriviallyConstructible");
  static_assert(IsTriviallyConstructible<bool>::value, "Failed IsTriviallyConstructible");
  static_assert(IsTriviallyConstructible<float>::value, "Failed IsTriviallyConstructible");
  static_assert(!IsTriviallyConstructible<void>::value, "Failed IsTriviallyConstructible");
  static_assert(IsTriviallyConstructible<void*>::value, "Failed IsTriviallyConstructible");
  static_assert(IsTriviallyConstructible<A>::value, "Failed IsTriviallyConstructible");
  static_assert(IsTriviallyConstructible<B>::value, "Failed IsTriviallyConstructible");
  static_assert(!IsTriviallyConstructible<C>::value, "Failed IsTriviallyConstructible");
  static_assert(IsTriviallyConstructible<D>::value, "Failed IsTriviallyConstructible");
  static_assert(!IsTriviallyConstructible<D, int>::value, "Failed IsTriviallyConstructible");
  static_assert(!IsTriviallyConstructible<decltype(func)>::value, "Failed IsTriviallyConstructible");
}

TEST(MetaObjectTraits, IsTriviallyAssignable) {
  struct A{};
  union B{};
  struct C{C& operator=(C const&) noexcept = default;};
  struct D{D& operator=(D const&) noexcept;};
  static_assert(Eq<True, IsTriviallyAssignable<int, int>>::value, "Failed IsTriviallyAssignable");
  static_assert(Eq<True, IsTriviallyAssignable<int&, int>>::value, "Failed IsTriviallyAssignable");
  static_assert(IsTriviallyAssignable<bool&, bool>::value, "Failed IsTriviallyAssignable");
  static_assert(IsTriviallyAssignable<float&, float>::value, "Failed IsTriviallyAssignable");
  static_assert(!IsTriviallyAssignable<void, void>::value, "Failed IsTriviallyAssignable");
  static_assert(IsTriviallyAssignable<void*&, void*>::value, "Failed IsTriviallyAssignable");
  static_assert(IsTriviallyAssignable<A, A>::value, "Failed IsTriviallyAssignable");
  static_assert(IsTriviallyAssignable<B, B>::value, "Failed IsTriviallyAssignable");
  static_assert(IsTriviallyAssignable<C, C>::value, "Failed IsTriviallyAssignable");
  static_assert(IsTriviallyAssignable<C&, C>::value, "Failed IsTriviallyAssignable");
  static_assert(!IsTriviallyAssignable<C const&, C>::value, "Failed IsTriviallyAssignable");
  static_assert(!IsTriviallyAssignable<D, D>::value, "Failed IsTriviallyAssignable");
  static_assert(!IsTriviallyAssignable<decltype(func), decltype(func)>::value, "Failed IsTriviallyAssignable");
}

TEST(MetaObjectTraits, IsTriviallyDestructible) {
  struct A{};
  struct B{~B();};
  static_assert(Eq<True, IsTriviallyDestructible<int>>::value, "Failed IsTriviallyDestructible");
  static_assert(Eq<True, IsTriviallyDestructible<int&>>::value, "Failed IsTriviallyDestructible");
  static_assert(Eq<False, IsTriviallyDestructible<void>>::value, "Failed IsTriviallyDestructible");
  static_assert(Eq<True, IsTriviallyDestructible<A>>::value, "Failed IsTriviallyDestructible");
  static_assert(Eq<False, IsTriviallyDestructible<B>>::value, "Failed IsTriviallyDestructible");
}

TEST(MetaObjectTraits, IsTriviallyDefaultCopyMove) {
  struct A{};
  struct B{B() = default; B(B const&) = default; B(B&&) = default; B& operator=(B const&) = default; B& operator=(B&&) = default;};
  struct C{C(); C(C const&); C(C&&) noexcept; C& operator=(C const&); C& operator=(C&&) noexcept;};

  static_assert(Eq<True, IsTriviallyDefaultConstructible<int>>::value, "Failed IsTriviallyDefaultConstructible");
  static_assert(Eq<True, IsTriviallyCopyConstructible<int>>::value, "Failed IsTriviallyCopyConstructible");
  static_assert(Eq<True, IsTriviallyMoveConstructible<int>>::value, "Failed IsTriviallyMoveConstructible");
  static_assert(Eq<True, IsTriviallyCopyAssignable<int>>::value, "Failed IsTriviallyCopyAssignable");
  static_assert(Eq<True, IsTriviallyMoveAssignable<int>>::value, "Failed IsTriviallyMoveAssignable");

  static_assert(Eq<True, IsTriviallyDefaultConstructible<A>>::value, "Failed IsTriviallyDefaultConstructible");
  static_assert(Eq<True, IsTriviallyCopyConstructible<A>>::value, "Failed IsTriviallyCopyConstructible");
  static_assert(Eq<True, IsTriviallyMoveConstructible<A>>::value, "Failed IsTriviallyMoveConstructible");
  static_assert(Eq<True, IsTriviallyCopyAssignable<A>>::value, "Failed IsTriviallyCopyAssignable");
  static_assert(Eq<True, IsTriviallyMoveAssignable<A>>::value, "Failed IsTriviallyMoveAssignable");

  static_assert(Eq<True, IsTriviallyDefaultConstructible<B>>::value, "Failed IsTriviallyDefaultConstructible");
  static_assert(Eq<True, IsTriviallyCopyConstructible<B>>::value, "Failed IsTriviallyCopyConstructible");
  static_assert(Eq<True, IsTriviallyMoveConstructible<B>>::value, "Failed IsTriviallyMoveConstructible");
  static_assert(Eq<True, IsTriviallyCopyAssignable<B>>::value, "Failed IsTriviallyCopyAssignable");
  static_assert(Eq<True, IsTriviallyMoveAssignable<B>>::value, "Failed IsTriviallyMoveAssignable");

  static_assert(Eq<False, IsTriviallyDefaultConstructible<C>>::value, "Failed IsTriviallyDefaultConstructible");
  static_assert(Eq<False, IsTriviallyCopyConstructible<C>>::value, "Failed IsTriviallyCopyConstructible");
  static_assert(Eq<False, IsTriviallyMoveConstructible<C>>::value, "Failed IsTriviallyMoveConstructible");
  static_assert(Eq<False, IsTriviallyCopyAssignable<C>>::value, "Failed IsTriviallyCopyAssignable");
  static_assert(Eq<False, IsTriviallyMoveAssignable<C>>::value, "Failed IsTriviallyMoveAssignable");
}

TEST(MetaObjectTraits, IsDefaultCopyMove) {
  struct A{};
  struct B{B() = default; B(B const&) = default; B(B&&) = default; B& operator=(B const&) = default; B& operator=(B&&) = default;};
  struct C{C(); C(C const&); C(C&&) noexcept; C& operator=(C const&); C& operator=(C&&) noexcept;};
  struct D{D() = delete; D(D const&) = delete; D(D&&) = delete; D& operator=(D const&) = delete; D& operator=(D&&) = delete;};

  static_assert(Eq<True, IsDefaultConstructible<int>>::value, "Failed IsDefaultConstructible");
  static_assert(Eq<True, IsCopyConstructible<int>>::value, "Failed IsCopyConstructible");
  static_assert(Eq<True, IsMoveConstructible<int>>::value, "Failed IsMoveConstructible");
  static_assert(Eq<True, IsCopyAssignable<int>>::value, "Failed IsCopyAssignable");
  static_assert(Eq<True, IsMoveAssignable<int>>::value, "Failed IsMoveAssignable");

  static_assert(Eq<True, IsDefaultConstructible<A>>::value, "Failed IsDefaultConstructible");
  static_assert(Eq<True, IsCopyConstructible<A>>::value, "Failed IsCopyConstructible");
  static_assert(Eq<True, IsMoveConstructible<A>>::value, "Failed IsMoveConstructible");
  static_assert(Eq<True, IsCopyAssignable<A>>::value, "Failed IsCopyAssignable");
  static_assert(Eq<True, IsMoveAssignable<A>>::value, "Failed IsMoveAssignable");

  static_assert(Eq<True, IsDefaultConstructible<B>>::value, "Failed IsDefaultConstructible");
  static_assert(Eq<True, IsCopyConstructible<B>>::value, "Failed IsCopyConstructible");
  static_assert(Eq<True, IsMoveConstructible<B>>::value, "Failed IsMoveConstructible");
  static_assert(Eq<True, IsCopyAssignable<B>>::value, "Failed IsCopyAssignable");
  static_assert(Eq<True, IsMoveAssignable<B>>::value, "Failed IsMoveAssignable");

  static_assert(Eq<True, IsDefaultConstructible<C>>::value, "Failed IsDefaultConstructible");
  static_assert(Eq<True, IsCopyConstructible<C>>::value, "Failed IsCopyConstructible");
  static_assert(Eq<True, IsMoveConstructible<C>>::value, "Failed IsMoveConstructible");
  static_assert(Eq<True, IsCopyAssignable<C>>::value, "Failed IsCopyAssignable");
  static_assert(Eq<True, IsMoveAssignable<C>>::value, "Failed IsMoveAssignable");

  static_assert(Eq<False, IsDefaultConstructible<D>>::value, "Failed IsDefaultConstructible");
  static_assert(Eq<False, IsCopyConstructible<D>>::value, "Failed IsCopyConstructible");
  static_assert(Eq<False, IsMoveConstructible<D>>::value, "Failed IsMoveConstructible");
  static_assert(Eq<False, IsCopyAssignable<D>>::value, "Failed IsCopyAssignable");
  static_assert(Eq<False, IsMoveAssignable<D>>::value, "Failed IsMoveAssignable");
}

TEST(MetaObjectTraits, IsConstructible) {
  struct A{};
  struct B{B(A const&); B(int);};

  static_assert(Eq<True, IsConstructible<int, int>>::value, "Failed IsConstructible");
  static_assert(Eq<True, IsConstructible<int, float>>::value, "Failed IsConstructible");
  static_assert(Eq<False, IsConstructible<int, void>>::value, "Failed IsConstructible");
  static_assert(Eq<True, IsConstructible<A, A>>::value, "Failed IsConstructible");
  static_assert(Eq<False, IsConstructible<A, B>>::value, "Failed IsConstructible");
  static_assert(Eq<False, IsConstructible<A, int>>::value, "Failed IsConstructible");
  static_assert(Eq<True, IsConstructible<B, A>>::value, "Failed IsConstructible");
  static_assert(Eq<True, IsConstructible<B, A const&>>::value, "Failed IsConstructible");
  static_assert(Eq<True, IsConstructible<B, A&>>::value, "Failed IsConstructible");
  static_assert(Eq<True, IsConstructible<B, A&&>>::value, "Failed IsConstructible");
  static_assert(Eq<True, IsConstructible<B, B>>::value, "Failed IsConstructible");
  static_assert(Eq<True, IsConstructible<B, int>>::value, "Failed IsConstructible");
  static_assert(Eq<True, IsConstructible<B, float>>::value, "Failed IsConstructible");
  static_assert(Eq<False, IsConstructible<B, void>>::value, "Failed IsConstructible");
}

TEST(MetaObjectTraits, IsAddCompatible) {
  struct A{};
  struct B{B operator+(B const&); B operator+(int);};
  struct C{C operator+(C const&); C operator+(B const&);};
  struct D{D operator+(D const&) = delete; D operator+(A const&);};
  static_assert(IsAddCompatible<int>::value, "Failed IsAddCompatible");
  static_assert(IsAddCompatible<int, int>::value, "Failed IsAddCompatible");
  static_assert(IsAddCompatible<int, float>::value, "Failed IsAddCompatible");
  static_assert(IsAddCompatible<int*, int>::value, "Failed IsAddCompatible");
  static_assert(!IsAddCompatible<int, A>::value, "Failed IsAddCompatible");
  static_assert(!IsAddCompatible<int, B>::value, "Failed IsAddCompatible");
  static_assert(!IsAddCompatible<int, C>::value, "Failed IsAddCompatible");
  static_assert(!IsAddCompatible<int, D>::value, "Failed IsAddCompatible");

  static_assert(!IsAddCompatible<A>::value, "Failed IsAddCompatible");
  static_assert(!IsAddCompatible<A, int>::value, "Failed IsAddCompatible");
  static_assert(!IsAddCompatible<A, A>::value, "Failed IsAddCompatible");
  static_assert(!IsAddCompatible<A, B>::value, "Failed IsAddCompatible");
  static_assert(!IsAddCompatible<A, C>::value, "Failed IsAddCompatible");
  static_assert(!IsAddCompatible<A, D>::value, "Failed IsAddCompatible");

  static_assert(IsAddCompatible<B>::value, "Failed IsAddCompatible");
  static_assert(IsAddCompatible<B, int>::value, "Failed IsAddCompatible");
  static_assert(!IsAddCompatible<B, A>::value, "Failed IsAddCompatible");
  static_assert(IsAddCompatible<B, B>::value, "Failed IsAddCompatible");
  static_assert(!IsAddCompatible<B, C>::value, "Failed IsAddCompatible");
  static_assert(!IsAddCompatible<B, D>::value, "Failed IsAddCompatible");

  static_assert(IsAddCompatible<C>::value, "Failed IsAddCompatible");
  static_assert(!IsAddCompatible<C, int>::value, "Failed IsAddCompatible");
  static_assert(!IsAddCompatible<C, A>::value, "Failed IsAddCompatible");
  static_assert(IsAddCompatible<C, B>::value, "Failed IsAddCompatible");
  static_assert(IsAddCompatible<C, C>::value, "Failed IsAddCompatible");
  static_assert(!IsAddCompatible<C, D>::value, "Failed IsAddCompatible");

  static_assert(!IsAddCompatible<D>::value, "Failed IsAddCompatible");
  static_assert(!IsAddCompatible<D, int>::value, "Failed IsAddCompatible");
  static_assert(IsAddCompatible<D, A>::value, "Failed IsAddCompatible");
  static_assert(!IsAddCompatible<D, B>::value, "Failed IsAddCompatible");
  static_assert(!IsAddCompatible<D, C>::value, "Failed IsAddCompatible");
  static_assert(!IsAddCompatible<D, D>::value, "Failed IsAddCompatible");
}

TEST(MetaObjectTraits, IsSubCompatible) {
  struct A{};
  struct B{B operator-(B const&); B operator-(int);};
  struct C{C operator-(C const&); C operator-(B const&);};
  struct D{D operator-(D const&) = delete; D operator-(A const&);};
  static_assert(IsSubCompatible<int>::value, "Failed IsSubCompatible");
  static_assert(IsSubCompatible<int, int>::value, "Failed IsSubCompatible");
  static_assert(IsSubCompatible<int, float>::value, "Failed IsSubCompatible");
  static_assert(IsSubCompatible<int*, int>::value, "Failed IsSubCompatible");
  static_assert(!IsSubCompatible<int, A>::value, "Failed IsSubCompatible");
  static_assert(!IsSubCompatible<int, B>::value, "Failed IsSubCompatible");
  static_assert(!IsSubCompatible<int, C>::value, "Failed IsSubCompatible");
  static_assert(!IsSubCompatible<int, D>::value, "Failed IsSubCompatible");

  static_assert(!IsSubCompatible<A>::value, "Failed IsSubCompatible");
  static_assert(!IsSubCompatible<A, int>::value, "Failed IsSubCompatible");
  static_assert(!IsSubCompatible<A, A>::value, "Failed IsSubCompatible");
  static_assert(!IsSubCompatible<A, B>::value, "Failed IsSubCompatible");
  static_assert(!IsSubCompatible<A, C>::value, "Failed IsSubCompatible");
  static_assert(!IsSubCompatible<A, D>::value, "Failed IsSubCompatible");

  static_assert(IsSubCompatible<B>::value, "Failed IsSubCompatible");
  static_assert(IsSubCompatible<B, int>::value, "Failed IsSubCompatible");
  static_assert(!IsSubCompatible<B, A>::value, "Failed IsSubCompatible");
  static_assert(IsSubCompatible<B, B>::value, "Failed IsSubCompatible");
  static_assert(!IsSubCompatible<B, C>::value, "Failed IsSubCompatible");
  static_assert(!IsSubCompatible<B, D>::value, "Failed IsSubCompatible");

  static_assert(IsSubCompatible<C>::value, "Failed IsSubCompatible");
  static_assert(!IsSubCompatible<C, int>::value, "Failed IsSubCompatible");
  static_assert(!IsSubCompatible<C, A>::value, "Failed IsSubCompatible");
  static_assert(IsSubCompatible<C, B>::value, "Failed IsSubCompatible");
  static_assert(IsSubCompatible<C, C>::value, "Failed IsSubCompatible");
  static_assert(!IsSubCompatible<C, D>::value, "Failed IsSubCompatible");

  static_assert(!IsSubCompatible<D>::value, "Failed IsSubCompatible");
  static_assert(!IsSubCompatible<D, int>::value, "Failed IsSubCompatible");
  static_assert(IsSubCompatible<D, A>::value, "Failed IsSubCompatible");
  static_assert(!IsSubCompatible<D, B>::value, "Failed IsSubCompatible");
  static_assert(!IsSubCompatible<D, C>::value, "Failed IsSubCompatible");
  static_assert(!IsSubCompatible<D, D>::value, "Failed IsSubCompatible");
}

TEST(MetaObjectTraits, IsMulCompatible) {
  struct A{};
  struct B{B operator*(B const&); B operator*(int);};
  struct C{C operator*(C const&); C operator*(B const&);};
  struct D{D operator*(D const&) = delete; D operator*(A const&);};
  static_assert(IsMulCompatible<int>::value, "Failed IsMulCompatible");
  static_assert(IsMulCompatible<int, int>::value, "Failed IsMulCompatible");
  static_assert(IsMulCompatible<int, float>::value, "Failed IsMulCompatible");
  static_assert(!IsMulCompatible<int*, int>::value, "Failed IsMulCompatible");
  static_assert(!IsMulCompatible<int, A>::value, "Failed IsMulCompatible");
  static_assert(!IsMulCompatible<int, B>::value, "Failed IsMulCompatible");
  static_assert(!IsMulCompatible<int, C>::value, "Failed IsMulCompatible");
  static_assert(!IsMulCompatible<int, D>::value, "Failed IsMulCompatible");

  static_assert(!IsMulCompatible<A>::value, "Failed IsMulCompatible");
  static_assert(!IsMulCompatible<A, int>::value, "Failed IsMulCompatible");
  static_assert(!IsMulCompatible<A, A>::value, "Failed IsMulCompatible");
  static_assert(!IsMulCompatible<A, B>::value, "Failed IsMulCompatible");
  static_assert(!IsMulCompatible<A, C>::value, "Failed IsMulCompatible");
  static_assert(!IsMulCompatible<A, D>::value, "Failed IsMulCompatible");

  static_assert(IsMulCompatible<B>::value, "Failed IsMulCompatible");
  static_assert(IsMulCompatible<B, int>::value, "Failed IsMulCompatible");
  static_assert(!IsMulCompatible<B, A>::value, "Failed IsMulCompatible");
  static_assert(IsMulCompatible<B, B>::value, "Failed IsMulCompatible");
  static_assert(!IsMulCompatible<B, C>::value, "Failed IsMulCompatible");
  static_assert(!IsMulCompatible<B, D>::value, "Failed IsMulCompatible");

  static_assert(IsMulCompatible<C>::value, "Failed IsMulCompatible");
  static_assert(!IsMulCompatible<C, int>::value, "Failed IsMulCompatible");
  static_assert(!IsMulCompatible<C, A>::value, "Failed IsMulCompatible");
  static_assert(IsMulCompatible<C, B>::value, "Failed IsMulCompatible");
  static_assert(IsMulCompatible<C, C>::value, "Failed IsMulCompatible");
  static_assert(!IsMulCompatible<C, D>::value, "Failed IsMulCompatible");

  static_assert(!IsMulCompatible<D>::value, "Failed IsMulCompatible");
  static_assert(!IsMulCompatible<D, int>::value, "Failed IsMulCompatible");
  static_assert(IsMulCompatible<D, A>::value, "Failed IsMulCompatible");
  static_assert(!IsMulCompatible<D, B>::value, "Failed IsMulCompatible");
  static_assert(!IsMulCompatible<D, C>::value, "Failed IsMulCompatible");
  static_assert(!IsMulCompatible<D, D>::value, "Failed IsMulCompatible");
}

TEST(MetaObjectTraits, IsDivCompatible) {
  struct A{};
  struct B{B operator/(B const&); B operator/(int);};
  struct C{C operator/(C const&); C operator/(B const&);};
  struct D{D operator/(D const&) = delete; D operator/(A const&);};
  static_assert(IsDivCompatible<int>::value, "Failed IsDivCompatible");
  static_assert(IsDivCompatible<int, int>::value, "Failed IsDivCompatible");
  static_assert(IsDivCompatible<int, float>::value, "Failed IsDivCompatible");
  static_assert(!IsDivCompatible<int*, int>::value, "Failed IsDivCompatible");
  static_assert(!IsDivCompatible<int, A>::value, "Failed IsDivCompatible");
  static_assert(!IsDivCompatible<int, B>::value, "Failed IsDivCompatible");
  static_assert(!IsDivCompatible<int, C>::value, "Failed IsDivCompatible");
  static_assert(!IsDivCompatible<int, D>::value, "Failed IsDivCompatible");

  static_assert(!IsDivCompatible<A>::value, "Failed IsDivCompatible");
  static_assert(!IsDivCompatible<A, int>::value, "Failed IsDivCompatible");
  static_assert(!IsDivCompatible<A, A>::value, "Failed IsDivCompatible");
  static_assert(!IsDivCompatible<A, B>::value, "Failed IsDivCompatible");
  static_assert(!IsDivCompatible<A, C>::value, "Failed IsDivCompatible");
  static_assert(!IsDivCompatible<A, D>::value, "Failed IsDivCompatible");

  static_assert(IsDivCompatible<B>::value, "Failed IsDivCompatible");
  static_assert(IsDivCompatible<B, int>::value, "Failed IsDivCompatible");
  static_assert(!IsDivCompatible<B, A>::value, "Failed IsDivCompatible");
  static_assert(IsDivCompatible<B, B>::value, "Failed IsDivCompatible");
  static_assert(!IsDivCompatible<B, C>::value, "Failed IsDivCompatible");
  static_assert(!IsDivCompatible<B, D>::value, "Failed IsDivCompatible");

  static_assert(IsDivCompatible<C>::value, "Failed IsDivCompatible");
  static_assert(!IsDivCompatible<C, int>::value, "Failed IsDivCompatible");
  static_assert(!IsDivCompatible<C, A>::value, "Failed IsDivCompatible");
  static_assert(IsDivCompatible<C, B>::value, "Failed IsDivCompatible");
  static_assert(IsDivCompatible<C, C>::value, "Failed IsDivCompatible");
  static_assert(!IsDivCompatible<C, D>::value, "Failed IsDivCompatible");

  static_assert(!IsDivCompatible<D>::value, "Failed IsDivCompatible");
  static_assert(!IsDivCompatible<D, int>::value, "Failed IsDivCompatible");
  static_assert(IsDivCompatible<D, A>::value, "Failed IsDivCompatible");
  static_assert(!IsDivCompatible<D, B>::value, "Failed IsDivCompatible");
  static_assert(!IsDivCompatible<D, C>::value, "Failed IsDivCompatible");
  static_assert(!IsDivCompatible<D, D>::value, "Failed IsDivCompatible");
}

TEST(MetaObjectTraits, IsModCompatible) {
  struct A{};
  struct B{B operator%(B const&); B operator%(int);};
  struct C{C operator%(C const&); C operator%(B const&);};
  struct D{D operator%(D const&) = delete; D operator%(A const&);};
  static_assert(IsModCompatible<int>::value, "Failed IsModCompatible");
  static_assert(IsModCompatible<int, int>::value, "Failed IsModCompatible");
  static_assert(!IsModCompatible<int, float>::value, "Failed IsModCompatible");
  static_assert(!IsModCompatible<int*, int>::value, "Failed IsModCompatible");
  static_assert(!IsModCompatible<int, A>::value, "Failed IsModCompatible");
  static_assert(!IsModCompatible<int, B>::value, "Failed IsModCompatible");
  static_assert(!IsModCompatible<int, C>::value, "Failed IsModCompatible");
  static_assert(!IsModCompatible<int, D>::value, "Failed IsModCompatible");

  static_assert(!IsModCompatible<A>::value, "Failed IsModCompatible");
  static_assert(!IsModCompatible<A, int>::value, "Failed IsModCompatible");
  static_assert(!IsModCompatible<A, A>::value, "Failed IsModCompatible");
  static_assert(!IsModCompatible<A, B>::value, "Failed IsModCompatible");
  static_assert(!IsModCompatible<A, C>::value, "Failed IsModCompatible");
  static_assert(!IsModCompatible<A, D>::value, "Failed IsModCompatible");

  static_assert(IsModCompatible<B>::value, "Failed IsModCompatible");
  static_assert(IsModCompatible<B, int>::value, "Failed IsModCompatible");
  static_assert(!IsModCompatible<B, A>::value, "Failed IsModCompatible");
  static_assert(IsModCompatible<B, B>::value, "Failed IsModCompatible");
  static_assert(!IsModCompatible<B, C>::value, "Failed IsModCompatible");
  static_assert(!IsModCompatible<B, D>::value, "Failed IsModCompatible");

  static_assert(IsModCompatible<C>::value, "Failed IsModCompatible");
  static_assert(!IsModCompatible<C, int>::value, "Failed IsModCompatible");
  static_assert(!IsModCompatible<C, A>::value, "Failed IsModCompatible");
  static_assert(IsModCompatible<C, B>::value, "Failed IsModCompatible");
  static_assert(IsModCompatible<C, C>::value, "Failed IsModCompatible");
  static_assert(!IsModCompatible<C, D>::value, "Failed IsModCompatible");

  static_assert(!IsModCompatible<D>::value, "Failed IsModCompatible");
  static_assert(!IsModCompatible<D, int>::value, "Failed IsModCompatible");
  static_assert(IsModCompatible<D, A>::value, "Failed IsModCompatible");
  static_assert(!IsModCompatible<D, B>::value, "Failed IsModCompatible");
  static_assert(!IsModCompatible<D, C>::value, "Failed IsModCompatible");
  static_assert(!IsModCompatible<D, D>::value, "Failed IsModCompatible");
}

TEST(MetaObjectTraits, IsPrefixIncrementable) {
  struct A{};
  struct B{B& operator++();};
  struct C{C& operator++() = delete;};
  struct D{D& operator++() = delete; D operator++(int);};
  static_assert(IsPrefixIncrementable<int>::value, "Failed IsPrefixIncrementable");
  static_assert(!IsPrefixIncrementable<bool>::value, "Failed IsPrefixIncrementable");
  static_assert(IsPrefixIncrementable<int*>::value, "Failed IsPrefixIncrementable");
  static_assert(!IsPrefixIncrementable<void*>::value, "Failed IsPrefixIncrementable");

  static_assert(!IsPrefixIncrementable<A>::value, "Failed IsPrefixIncrementable");
  static_assert(IsPrefixIncrementable<B>::value, "Failed IsPrefixIncrementable");
  static_assert(!IsPrefixIncrementable<C>::value, "Failed IsPrefixIncrementable");
  static_assert(!IsPrefixIncrementable<D>::value, "Failed IsPrefixIncrementable");
}

TEST(MetaObjectTraits, IsPostfixIncrementable) {
  struct A{};
  struct B{B operator++(int);};
  struct C{C operator++(int) = delete;};
  struct D{D operator++(int) = delete; D& operator++();};
  static_assert(IsPostfixIncrementable<int>::value, "Failed IsPostfixIncrementable");
  static_assert(!IsPostfixIncrementable<bool>::value, "Failed IsPostfixIncrementable");
  static_assert(IsPostfixIncrementable<int*>::value, "Failed IsPostfixIncrementable");
  static_assert(!IsPostfixIncrementable<void*>::value, "Failed IsPostfixIncrementable");

  static_assert(!IsPostfixIncrementable<A>::value, "Failed IsPostfixIncrementable");
  static_assert(IsPostfixIncrementable<B>::value, "Failed IsPostfixIncrementable");
  static_assert(!IsPostfixIncrementable<C>::value, "Failed IsPostfixIncrementable");
  static_assert(!IsPostfixIncrementable<D>::value, "Failed IsPostfixIncrementable");
}

TEST(MetaObjectTraits, IsPrefixDecrementable) {
  struct A{};
  struct B{B& operator--();};
  struct C{C& operator--() = delete;};
  struct D{D& operator--() = delete; D operator--(int);};
  static_assert(IsPrefixDecrementable<int>::value, "Failed IsPrefixDecrementable");
  static_assert(!IsPrefixDecrementable<bool>::value, "Failed IsPrefixDecrementable");
  static_assert(IsPrefixDecrementable<int*>::value, "Failed IsPrefixDecrementable");
  static_assert(!IsPrefixDecrementable<void*>::value, "Failed IsPrefixDecrementable");

  static_assert(!IsPrefixDecrementable<A>::value, "Failed IsPrefixDecrementable");
  static_assert(IsPrefixDecrementable<B>::value, "Failed IsPrefixDecrementable");
  static_assert(!IsPrefixDecrementable<C>::value, "Failed IsPrefixDecrementable");
  static_assert(!IsPrefixDecrementable<D>::value, "Failed IsPrefixDecrementable");
}

TEST(MetaObjectTraits, IsPostfixDecrementable) {
  struct A{};
  struct B{B operator--(int);};
  struct C{C operator--(int) = delete;};
  struct D{D operator--(int) = delete; D& operator--();};
  static_assert(IsPostfixDecrementable<int>::value, "Failed IsPostfixDecrementable");
  static_assert(!IsPostfixDecrementable<bool>::value, "Failed IsPostfixDecrementable");
  static_assert(IsPostfixDecrementable<int*>::value, "Failed IsPostfixDecrementable");
  static_assert(!IsPostfixDecrementable<void*>::value, "Failed IsPostfixDecrementable");

  static_assert(!IsPostfixDecrementable<A>::value, "Failed IsPostfixDecrementable");
  static_assert(IsPostfixDecrementable<B>::value, "Failed IsPostfixDecrementable");
  static_assert(!IsPostfixDecrementable<C>::value, "Failed IsPostfixDecrementable");
  static_assert(!IsPostfixDecrementable<D>::value, "Failed IsPostfixDecrementable");
}

TEST(MetaObjectTraits, IsLtCompatible) {
  struct A{};
  struct B{bool operator<(B const&); bool operator<(int);};
  struct C{bool operator<(C const&); bool operator<(B const&);};
  struct D{bool operator<(D const&) = delete; bool operator<(A const&);};
  static_assert(IsLtCompatible<int>::value, "Failed IsLtCompatible");
  static_assert(IsLtCompatible<int, int>::value, "Failed IsLtCompatible");
  static_assert(IsLtCompatible<int, float>::value, "Failed IsLtCompatible");
  static_assert(!IsLtCompatible<int*, int>::value, "Failed IsLtCompatible");
  static_assert(!IsLtCompatible<int, A>::value, "Failed IsLtCompatible");
  static_assert(!IsLtCompatible<int, B>::value, "Failed IsLtCompatible");
  static_assert(!IsLtCompatible<int, C>::value, "Failed IsLtCompatible");
  static_assert(!IsLtCompatible<int, D>::value, "Failed IsLtCompatible");

  static_assert(!IsLtCompatible<A>::value, "Failed IsLtCompatible");
  static_assert(!IsLtCompatible<A, int>::value, "Failed IsLtCompatible");
  static_assert(!IsLtCompatible<A, A>::value, "Failed IsLtCompatible");
  static_assert(!IsLtCompatible<A, B>::value, "Failed IsLtCompatible");
  static_assert(!IsLtCompatible<A, C>::value, "Failed IsLtCompatible");
  static_assert(!IsLtCompatible<A, D>::value, "Failed IsLtCompatible");

  static_assert(IsLtCompatible<B>::value, "Failed IsLtCompatible");
  static_assert(IsLtCompatible<B, int>::value, "Failed IsLtCompatible");
  static_assert(!IsLtCompatible<B, A>::value, "Failed IsLtCompatible");
  static_assert(IsLtCompatible<B, B>::value, "Failed IsLtCompatible");
  static_assert(!IsLtCompatible<B, C>::value, "Failed IsLtCompatible");
  static_assert(!IsLtCompatible<B, D>::value, "Failed IsLtCompatible");

  static_assert(IsLtCompatible<C>::value, "Failed IsLtCompatible");
  static_assert(!IsLtCompatible<C, int>::value, "Failed IsLtCompatible");
  static_assert(!IsLtCompatible<C, A>::value, "Failed IsLtCompatible");
  static_assert(IsLtCompatible<C, B>::value, "Failed IsLtCompatible");
  static_assert(IsLtCompatible<C, C>::value, "Failed IsLtCompatible");
  static_assert(!IsLtCompatible<C, D>::value, "Failed IsLtCompatible");

  static_assert(!IsLtCompatible<D>::value, "Failed IsLtCompatible");
  static_assert(!IsLtCompatible<D, int>::value, "Failed IsLtCompatible");
  static_assert(IsLtCompatible<D, A>::value, "Failed IsLtCompatible");
  static_assert(!IsLtCompatible<D, B>::value, "Failed IsLtCompatible");
  static_assert(!IsLtCompatible<D, C>::value, "Failed IsLtCompatible");
  static_assert(!IsLtCompatible<D, D>::value, "Failed IsLtCompatible");
}

TEST(MetaObjectTraits, IsLeCompatible) {
  struct A{};
  struct B{bool operator<=(B const&); bool operator<=(int);};
  struct C{bool operator<=(C const&); bool operator<=(B const&);};
  struct D{bool operator<=(D const&) = delete; bool operator<=(A const&);};
  static_assert(IsLeCompatible<int>::value, "Failed IsLeCompatible");
  static_assert(IsLeCompatible<int, int>::value, "Failed IsLeCompatible");
  static_assert(IsLeCompatible<int, float>::value, "Failed IsLeCompatible");
  static_assert(!IsLeCompatible<int*, int>::value, "Failed IsLeCompatible");
  static_assert(!IsLeCompatible<int, A>::value, "Failed IsLeCompatible");
  static_assert(!IsLeCompatible<int, B>::value, "Failed IsLeCompatible");
  static_assert(!IsLeCompatible<int, C>::value, "Failed IsLeCompatible");
  static_assert(!IsLeCompatible<int, D>::value, "Failed IsLeCompatible");

  static_assert(!IsLeCompatible<A>::value, "Failed IsLeCompatible");
  static_assert(!IsLeCompatible<A, int>::value, "Failed IsLeCompatible");
  static_assert(!IsLeCompatible<A, A>::value, "Failed IsLeCompatible");
  static_assert(!IsLeCompatible<A, B>::value, "Failed IsLeCompatible");
  static_assert(!IsLeCompatible<A, C>::value, "Failed IsLeCompatible");
  static_assert(!IsLeCompatible<A, D>::value, "Failed IsLeCompatible");

  static_assert(IsLeCompatible<B>::value, "Failed IsLeCompatible");
  static_assert(IsLeCompatible<B, int>::value, "Failed IsLeCompatible");
  static_assert(!IsLeCompatible<B, A>::value, "Failed IsLeCompatible");
  static_assert(IsLeCompatible<B, B>::value, "Failed IsLeCompatible");
  static_assert(!IsLeCompatible<B, C>::value, "Failed IsLeCompatible");
  static_assert(!IsLeCompatible<B, D>::value, "Failed IsLeCompatible");

  static_assert(IsLeCompatible<C>::value, "Failed IsLeCompatible");
  static_assert(!IsLeCompatible<C, int>::value, "Failed IsLeCompatible");
  static_assert(!IsLeCompatible<C, A>::value, "Failed IsLeCompatible");
  static_assert(IsLeCompatible<C, B>::value, "Failed IsLeCompatible");
  static_assert(IsLeCompatible<C, C>::value, "Failed IsLeCompatible");
  static_assert(!IsLeCompatible<C, D>::value, "Failed IsLeCompatible");

  static_assert(!IsLeCompatible<D>::value, "Failed IsLeCompatible");
  static_assert(!IsLeCompatible<D, int>::value, "Failed IsLeCompatible");
  static_assert(IsLeCompatible<D, A>::value, "Failed IsLeCompatible");
  static_assert(!IsLeCompatible<D, B>::value, "Failed IsLeCompatible");
  static_assert(!IsLeCompatible<D, C>::value, "Failed IsLeCompatible");
  static_assert(!IsLeCompatible<D, D>::value, "Failed IsLeCompatible");
}

TEST(MetaObjectTraits, IsGtCompatible) {
  struct A{};
  struct B{bool operator>(B const&); bool operator>(int);};
  struct C{bool operator>(C const&); bool operator>(B const&);};
  struct D{bool operator>(D const&) = delete; bool operator>(A const&);};
  static_assert(IsGtCompatible<int>::value, "Failed IsGtCompatible");
  static_assert(IsGtCompatible<int, int>::value, "Failed IsGtCompatible");
  static_assert(IsGtCompatible<int, float>::value, "Failed IsGtCompatible");
  static_assert(!IsGtCompatible<int*, int>::value, "Failed IsGtCompatible");
  static_assert(!IsGtCompatible<int, A>::value, "Failed IsGtCompatible");
  static_assert(!IsGtCompatible<int, B>::value, "Failed IsGtCompatible");
  static_assert(!IsGtCompatible<int, C>::value, "Failed IsGtCompatible");
  static_assert(!IsGtCompatible<int, D>::value, "Failed IsGtCompatible");

  static_assert(!IsGtCompatible<A>::value, "Failed IsGtCompatible");
  static_assert(!IsGtCompatible<A, int>::value, "Failed IsGtCompatible");
  static_assert(!IsGtCompatible<A, A>::value, "Failed IsGtCompatible");
  static_assert(!IsGtCompatible<A, B>::value, "Failed IsGtCompatible");
  static_assert(!IsGtCompatible<A, C>::value, "Failed IsGtCompatible");
  static_assert(!IsGtCompatible<A, D>::value, "Failed IsGtCompatible");

  static_assert(IsGtCompatible<B>::value, "Failed IsGtCompatible");
  static_assert(IsGtCompatible<B, int>::value, "Failed IsGtCompatible");
  static_assert(!IsGtCompatible<B, A>::value, "Failed IsGtCompatible");
  static_assert(IsGtCompatible<B, B>::value, "Failed IsGtCompatible");
  static_assert(!IsGtCompatible<B, C>::value, "Failed IsGtCompatible");
  static_assert(!IsGtCompatible<B, D>::value, "Failed IsGtCompatible");

  static_assert(IsGtCompatible<C>::value, "Failed IsGtCompatible");
  static_assert(!IsGtCompatible<C, int>::value, "Failed IsGtCompatible");
  static_assert(!IsGtCompatible<C, A>::value, "Failed IsGtCompatible");
  static_assert(IsGtCompatible<C, B>::value, "Failed IsGtCompatible");
  static_assert(IsGtCompatible<C, C>::value, "Failed IsGtCompatible");
  static_assert(!IsGtCompatible<C, D>::value, "Failed IsGtCompatible");

  static_assert(!IsGtCompatible<D>::value, "Failed IsGtCompatible");
  static_assert(!IsGtCompatible<D, int>::value, "Failed IsGtCompatible");
  static_assert(IsGtCompatible<D, A>::value, "Failed IsGtCompatible");
  static_assert(!IsGtCompatible<D, B>::value, "Failed IsGtCompatible");
  static_assert(!IsGtCompatible<D, C>::value, "Failed IsGtCompatible");
  static_assert(!IsGtCompatible<D, D>::value, "Failed IsGtCompatible");
}

TEST(MetaObjectTraits, IsGeCompatible) {
  struct A{};
  struct B{bool operator>=(B const&); bool operator>=(int);};
  struct C{bool operator>=(C const&); bool operator>=(B const&);};
  struct D{bool operator>=(D const&) = delete; bool operator>=(A const&);};
  static_assert(IsGeCompatible<int>::value, "Failed IsGeCompatible");
  static_assert(IsGeCompatible<int, int>::value, "Failed IsGeCompatible");
  static_assert(IsGeCompatible<int, float>::value, "Failed IsGeCompatible");
  static_assert(!IsGeCompatible<int*, int>::value, "Failed IsGeCompatible");
  static_assert(!IsGeCompatible<int, A>::value, "Failed IsGeCompatible");
  static_assert(!IsGeCompatible<int, B>::value, "Failed IsGeCompatible");
  static_assert(!IsGeCompatible<int, C>::value, "Failed IsGeCompatible");
  static_assert(!IsGeCompatible<int, D>::value, "Failed IsGeCompatible");

  static_assert(!IsGeCompatible<A>::value, "Failed IsGeCompatible");
  static_assert(!IsGeCompatible<A, int>::value, "Failed IsGeCompatible");
  static_assert(!IsGeCompatible<A, A>::value, "Failed IsGeCompatible");
  static_assert(!IsGeCompatible<A, B>::value, "Failed IsGeCompatible");
  static_assert(!IsGeCompatible<A, C>::value, "Failed IsGeCompatible");
  static_assert(!IsGeCompatible<A, D>::value, "Failed IsGeCompatible");

  static_assert(IsGeCompatible<B>::value, "Failed IsGeCompatible");
  static_assert(IsGeCompatible<B, int>::value, "Failed IsGeCompatible");
  static_assert(!IsGeCompatible<B, A>::value, "Failed IsGeCompatible");
  static_assert(IsGeCompatible<B, B>::value, "Failed IsGeCompatible");
  static_assert(!IsGeCompatible<B, C>::value, "Failed IsGeCompatible");
  static_assert(!IsGeCompatible<B, D>::value, "Failed IsGeCompatible");

  static_assert(IsGeCompatible<C>::value, "Failed IsGeCompatible");
  static_assert(!IsGeCompatible<C, int>::value, "Failed IsGeCompatible");
  static_assert(!IsGeCompatible<C, A>::value, "Failed IsGeCompatible");
  static_assert(IsGeCompatible<C, B>::value, "Failed IsGeCompatible");
  static_assert(IsGeCompatible<C, C>::value, "Failed IsGeCompatible");
  static_assert(!IsGeCompatible<C, D>::value, "Failed IsGeCompatible");

  static_assert(!IsGeCompatible<D>::value, "Failed IsGeCompatible");
  static_assert(!IsGeCompatible<D, int>::value, "Failed IsGeCompatible");
  static_assert(IsGeCompatible<D, A>::value, "Failed IsGeCompatible");
  static_assert(!IsGeCompatible<D, B>::value, "Failed IsGeCompatible");
  static_assert(!IsGeCompatible<D, C>::value, "Failed IsGeCompatible");
  static_assert(!IsGeCompatible<D, D>::value, "Failed IsGeCompatible");
}

TEST(MetaObjectTraits, IsEqCompatible) {
  struct A{};
  struct B{bool operator==(B const&) const; bool operator==(int) const;};
  struct C{bool operator==(C const&) const; bool operator==(B const&) const;};
  struct D{bool operator==(D const&) const = delete; bool operator==(A const&) const;};
  static_assert(IsEqCompatible<int>::value, "Failed IsEqCompatible");
  static_assert(IsEqCompatible<int, int>::value, "Failed IsEqCompatible");
  static_assert(IsEqCompatible<int, float>::value, "Failed IsEqCompatible");
  static_assert(!IsEqCompatible<int*, int>::value, "Failed IsEqCompatible");
  static_assert(!IsEqCompatible<int, A>::value, "Failed IsEqCompatible");
  static_assert((compiler::CurrentStd::version >= 20 ? true : false) == IsEqCompatible<int, B>::value, "Failed IsEqCompatible");
  static_assert(!IsEqCompatible<int, C>::value, "Failed IsEqCompatible");
  static_assert(!IsEqCompatible<int, D>::value, "Failed IsEqCompatible");

  static_assert(!IsEqCompatible<A>::value, "Failed IsEqCompatible");
  static_assert(!IsEqCompatible<A, int>::value, "Failed IsEqCompatible");
  static_assert(!IsEqCompatible<A, A>::value, "Failed IsEqCompatible");
  static_assert(!IsEqCompatible<A, B>::value, "Failed IsEqCompatible");
  static_assert(!IsEqCompatible<A, C>::value, "Failed IsEqCompatible");
  static_assert((compiler::CurrentStd::version >= 20 ? true : false) == IsEqCompatible<A, D>::value, "Failed IsEqCompatible");

  static_assert(IsEqCompatible<B>::value, "Failed IsEqCompatible");
  static_assert(IsEqCompatible<B, int>::value, "Failed IsEqCompatible");
  static_assert(!IsEqCompatible<B, A>::value, "Failed IsEqCompatible");
  static_assert(IsEqCompatible<B, B>::value, "Failed IsEqCompatible");
  static_assert((compiler::CurrentStd::version >= 20 ? true : false) == IsEqCompatible<B, C>::value, "Failed IsEqCompatible");
  static_assert(!IsEqCompatible<B, D>::value, "Failed IsEqCompatible");

  static_assert(IsEqCompatible<C>::value, "Failed IsEqCompatible");
  static_assert(!IsEqCompatible<C, int>::value, "Failed IsEqCompatible");
  static_assert(!IsEqCompatible<C, A>::value, "Failed IsEqCompatible");
  static_assert(IsEqCompatible<C, B>::value, "Failed IsEqCompatible");
  static_assert(IsEqCompatible<C, C>::value, "Failed IsEqCompatible");
  static_assert(!IsEqCompatible<C, D>::value, "Failed IsEqCompatible");

  static_assert(!IsEqCompatible<D>::value, "Failed IsEqCompatible");
  static_assert(!IsEqCompatible<D, int>::value, "Failed IsEqCompatible");
  static_assert(IsEqCompatible<D, A>::value, "Failed IsEqCompatible");
  static_assert(!IsEqCompatible<D, B>::value, "Failed IsEqCompatible");
  static_assert(!IsEqCompatible<D, C>::value, "Failed IsEqCompatible");
  static_assert(!IsEqCompatible<D, D>::value, "Failed IsEqCompatible");
}

TEST(MetaObjectTraits, IsNeCompatible) {
  struct A{};
  struct B{bool operator!=(B const&) const; bool operator!=(int) const;};
  struct C{bool operator!=(C const&) const; bool operator!=(B const&) const;};
  struct D{bool operator!=(D const&) const = delete; bool operator!=(A const&) const;};
  static_assert(IsNeCompatible<int>::value, "Failed IsNeCompatible");
  static_assert(IsNeCompatible<int, int>::value, "Failed IsNeCompatible");
  static_assert(IsNeCompatible<int, float>::value, "Failed IsNeCompatible");
  static_assert(!IsNeCompatible<int*, int>::value, "Failed IsNeCompatible");
  static_assert(!IsNeCompatible<int, A>::value, "Failed IsNeCompatible");
  static_assert(!IsNeCompatible<int, B>::value, "Failed IsNeCompatible");
  static_assert(!IsNeCompatible<int, C>::value, "Failed IsNeCompatible");
  static_assert(!IsNeCompatible<int, D>::value, "Failed IsNeCompatible");

  static_assert(!IsNeCompatible<A>::value, "Failed IsNeCompatible");
  static_assert(!IsNeCompatible<A, int>::value, "Failed IsNeCompatible");
  static_assert(!IsNeCompatible<A, A>::value, "Failed IsNeCompatible");
  static_assert(!IsNeCompatible<A, B>::value, "Failed IsNeCompatible");
  static_assert(!IsNeCompatible<A, C>::value, "Failed IsNeCompatible");
  static_assert(!IsNeCompatible<A, D>::value, "Failed IsNeCompatible");

  static_assert(IsNeCompatible<B>::value, "Failed IsNeCompatible");
  static_assert(IsNeCompatible<B, int>::value, "Failed IsNeCompatible");
  static_assert(!IsNeCompatible<B, A>::value, "Failed IsNeCompatible");
  static_assert(IsNeCompatible<B, B>::value, "Failed IsNeCompatible");
  static_assert(!IsNeCompatible<B, C>::value, "Failed IsNeCompatible");
  static_assert(!IsNeCompatible<B, D>::value, "Failed IsNeCompatible");

  static_assert(IsNeCompatible<C>::value, "Failed IsNeCompatible");
  static_assert(!IsNeCompatible<C, int>::value, "Failed IsNeCompatible");
  static_assert(!IsNeCompatible<C, A>::value, "Failed IsNeCompatible");
  static_assert(IsNeCompatible<C, B>::value, "Failed IsNeCompatible");
  static_assert(IsNeCompatible<C, C>::value, "Failed IsNeCompatible");
  static_assert(!IsNeCompatible<C, D>::value, "Failed IsNeCompatible");

  static_assert(!IsNeCompatible<D>::value, "Failed IsNeCompatible");
  static_assert(!IsNeCompatible<D, int>::value, "Failed IsNeCompatible");
  static_assert(IsNeCompatible<D, A>::value, "Failed IsNeCompatible");
  static_assert(!IsNeCompatible<D, B>::value, "Failed IsNeCompatible");
  static_assert(!IsNeCompatible<D, C>::value, "Failed IsNeCompatible");
  static_assert(!IsNeCompatible<D, D>::value, "Failed IsNeCompatible");
}

#ifdef DCR_SINCECPP20
TEST(MetaObjectTraits, IsSpaceshipCompatible) {
  struct A{};
  struct B{std::strong_ordering operator<=>(B const&) const; std::strong_ordering operator<=>(int) const;};
  struct C{std::strong_ordering operator<=>(C const&) const; std::strong_ordering operator<=>(B const&) const;};
  struct D{std::strong_ordering operator<=>(D const&) const = delete; std::strong_ordering operator<=>(A const&) const;};
  static_assert(IsSpaceshipCompatible<int>::value, "Failed IsSpaceshipCompatible");
  static_assert(IsSpaceshipCompatible<int, int>::value, "Failed IsSpaceshipCompatible");
  static_assert(IsSpaceshipCompatible<int, float>::value, "Failed IsSpaceshipCompatible");
  static_assert(!IsSpaceshipCompatible<int*, int>::value, "Failed IsSpaceshipCompatible");
  static_assert(!IsSpaceshipCompatible<int, A>::value, "Failed IsSpaceshipCompatible");
  static_assert(IsSpaceshipCompatible<int, B>::value, "Failed IsSpaceshipCompatible");
  static_assert(!IsSpaceshipCompatible<int, C>::value, "Failed IsSpaceshipCompatible");
  static_assert(!IsSpaceshipCompatible<int, D>::value, "Failed IsSpaceshipCompatible");

  static_assert(!IsSpaceshipCompatible<A>::value, "Failed IsSpaceshipCompatible");
  static_assert(!IsSpaceshipCompatible<A, int>::value, "Failed IsSpaceshipCompatible");
  static_assert(!IsSpaceshipCompatible<A, A>::value, "Failed IsSpaceshipCompatible");
  static_assert(!IsSpaceshipCompatible<A, B>::value, "Failed IsSpaceshipCompatible");
  static_assert(!IsSpaceshipCompatible<A, C>::value, "Failed IsSpaceshipCompatible");
  static_assert(IsSpaceshipCompatible<A, D>::value, "Failed IsSpaceshipCompatible");

  static_assert(IsSpaceshipCompatible<B>::value, "Failed IsSpaceshipCompatible");
  static_assert(IsSpaceshipCompatible<B, int>::value, "Failed IsSpaceshipCompatible");
  static_assert(!IsSpaceshipCompatible<B, A>::value, "Failed IsSpaceshipCompatible");
  static_assert(IsSpaceshipCompatible<B, B>::value, "Failed IsSpaceshipCompatible");
  static_assert(IsSpaceshipCompatible<B, C>::value, "Failed IsSpaceshipCompatible");
  static_assert(!IsSpaceshipCompatible<B, D>::value, "Failed IsSpaceshipCompatible");

  static_assert(IsSpaceshipCompatible<C>::value, "Failed IsSpaceshipCompatible");
  static_assert(!IsSpaceshipCompatible<C, int>::value, "Failed IsSpaceshipCompatible");
  static_assert(!IsSpaceshipCompatible<C, A>::value, "Failed IsSpaceshipCompatible");
  static_assert(IsSpaceshipCompatible<C, B>::value, "Failed IsSpaceshipCompatible");
  static_assert(IsSpaceshipCompatible<C, C>::value, "Failed IsSpaceshipCompatible");
  static_assert(!IsSpaceshipCompatible<C, D>::value, "Failed IsSpaceshipCompatible");

  static_assert(!IsSpaceshipCompatible<D>::value, "Failed IsSpaceshipCompatible");
  static_assert(!IsSpaceshipCompatible<D, int>::value, "Failed IsSpaceshipCompatible");
  static_assert(IsSpaceshipCompatible<D, A>::value, "Failed IsSpaceshipCompatible");
  static_assert(!IsSpaceshipCompatible<D, B>::value, "Failed IsSpaceshipCompatible");
  static_assert(!IsSpaceshipCompatible<D, C>::value, "Failed IsSpaceshipCompatible");
  static_assert(!IsSpaceshipCompatible<D, D>::value, "Failed IsSpaceshipCompatible");
}
#endif

TEST(MetaObjectTraits, IsNotCompatible) {
  struct A{};
  struct B{bool operator!() const;};
  struct C{bool operator!() const = delete;};
  static_assert(IsNotCompatible<bool>::value, "Failed IsNotCompatible");
  static_assert(IsNotCompatible<int>::value, "Failed IsNotCompatible");
  static_assert(IsNotCompatible<float>::value, "Failed IsNotCompatible");
  static_assert(IsNotCompatible<void*>::value, "Failed IsNotCompatible");
  static_assert(!IsNotCompatible<void>::value, "Failed IsNotCompatible");

  static_assert(!IsNotCompatible<A>::value, "Failed IsNotCompatible");
  static_assert(IsNotCompatible<B>::value, "Failed IsNotCompatible");
  static_assert(!IsNotCompatible<C>::value, "Failed IsNotCompatible");
}

TEST(MetaObjectTraits, IsAndCompatible) {
  struct A{};
  struct B{bool operator&&(B const&) const; bool operator&&(int) const;};
  struct C{bool operator&&(C const&) const; bool operator&&(B const&) const;};
  struct D{bool operator&&(D const&) const = delete; bool operator&&(A const&) const;};
  static_assert(IsAndCompatible<int>::value, "Failed IsAndCompatible");
  static_assert(IsAndCompatible<int, int>::value, "Failed IsAndCompatible");
  static_assert(IsAndCompatible<int, float>::value, "Failed IsAndCompatible");
  static_assert(IsAndCompatible<int*, int>::value, "Failed IsAndCompatible");
  static_assert(!IsAndCompatible<int, A>::value, "Failed IsAndCompatible");
  static_assert(!IsAndCompatible<int, B>::value, "Failed IsAndCompatible");
  static_assert(!IsAndCompatible<int, C>::value, "Failed IsAndCompatible");
  static_assert(!IsAndCompatible<int, D>::value, "Failed IsAndCompatible");

  static_assert(!IsAndCompatible<A>::value, "Failed IsAndCompatible");
  static_assert(!IsAndCompatible<A, int>::value, "Failed IsAndCompatible");
  static_assert(!IsAndCompatible<A, A>::value, "Failed IsAndCompatible");
  static_assert(!IsAndCompatible<A, B>::value, "Failed IsAndCompatible");
  static_assert(!IsAndCompatible<A, C>::value, "Failed IsAndCompatible");
  static_assert(!IsAndCompatible<A, D>::value, "Failed IsAndCompatible");

  static_assert(IsAndCompatible<B>::value, "Failed IsAndCompatible");
  static_assert(IsAndCompatible<B, int>::value, "Failed IsAndCompatible");
  static_assert(!IsAndCompatible<B, A>::value, "Failed IsAndCompatible");
  static_assert(IsAndCompatible<B, B>::value, "Failed IsAndCompatible");
  static_assert(!IsAndCompatible<B, C>::value, "Failed IsAndCompatible");
  static_assert(!IsAndCompatible<B, D>::value, "Failed IsAndCompatible");

  static_assert(IsAndCompatible<C>::value, "Failed IsAndCompatible");
  static_assert(!IsAndCompatible<C, int>::value, "Failed IsAndCompatible");
  static_assert(!IsAndCompatible<C, A>::value, "Failed IsAndCompatible");
  static_assert(IsAndCompatible<C, B>::value, "Failed IsAndCompatible");
  static_assert(IsAndCompatible<C, C>::value, "Failed IsAndCompatible");
  static_assert(!IsAndCompatible<C, D>::value, "Failed IsAndCompatible");

  static_assert(!IsAndCompatible<D>::value, "Failed IsAndCompatible");
  static_assert(!IsAndCompatible<D, int>::value, "Failed IsAndCompatible");
  static_assert(IsAndCompatible<D, A>::value, "Failed IsAndCompatible");
  static_assert(!IsAndCompatible<D, B>::value, "Failed IsAndCompatible");
  static_assert(!IsAndCompatible<D, C>::value, "Failed IsAndCompatible");
  static_assert(!IsAndCompatible<D, D>::value, "Failed IsAndCompatible");
}

TEST(MetaObjectTraits, IsOrCompatible) {
  struct A{};
  struct B{bool operator||(B const&) const; bool operator||(int) const;};
  struct C{bool operator||(C const&) const; bool operator||(B const&) const;};
  struct D{bool operator||(D const&) const = delete; bool operator||(A const&) const;};
  static_assert(IsOrCompatible<int>::value, "Failed IsOrCompatible");
  static_assert(IsOrCompatible<int, int>::value, "Failed IsOrCompatible");
  static_assert(IsOrCompatible<int, float>::value, "Failed IsOrCompatible");
  static_assert(IsOrCompatible<int*, int>::value, "Failed IsOrCompatible");
  static_assert(!IsOrCompatible<int, A>::value, "Failed IsOrCompatible");
  static_assert(!IsOrCompatible<int, B>::value, "Failed IsOrCompatible");
  static_assert(!IsOrCompatible<int, C>::value, "Failed IsOrCompatible");
  static_assert(!IsOrCompatible<int, D>::value, "Failed IsOrCompatible");

  static_assert(!IsOrCompatible<A>::value, "Failed IsOrCompatible");
  static_assert(!IsOrCompatible<A, int>::value, "Failed IsOrCompatible");
  static_assert(!IsOrCompatible<A, A>::value, "Failed IsOrCompatible");
  static_assert(!IsOrCompatible<A, B>::value, "Failed IsOrCompatible");
  static_assert(!IsOrCompatible<A, C>::value, "Failed IsOrCompatible");
  static_assert(!IsOrCompatible<A, D>::value, "Failed IsOrCompatible");

  static_assert(IsOrCompatible<B>::value, "Failed IsOrCompatible");
  static_assert(IsOrCompatible<B, int>::value, "Failed IsOrCompatible");
  static_assert(!IsOrCompatible<B, A>::value, "Failed IsOrCompatible");
  static_assert(IsOrCompatible<B, B>::value, "Failed IsOrCompatible");
  static_assert(!IsOrCompatible<B, C>::value, "Failed IsOrCompatible");
  static_assert(!IsOrCompatible<B, D>::value, "Failed IsOrCompatible");

  static_assert(IsOrCompatible<C>::value, "Failed IsOrCompatible");
  static_assert(!IsOrCompatible<C, int>::value, "Failed IsOrCompatible");
  static_assert(!IsOrCompatible<C, A>::value, "Failed IsOrCompatible");
  static_assert(IsOrCompatible<C, B>::value, "Failed IsOrCompatible");
  static_assert(IsOrCompatible<C, C>::value, "Failed IsOrCompatible");
  static_assert(!IsOrCompatible<C, D>::value, "Failed IsOrCompatible");

  static_assert(!IsOrCompatible<D>::value, "Failed IsOrCompatible");
  static_assert(!IsOrCompatible<D, int>::value, "Failed IsOrCompatible");
  static_assert(IsOrCompatible<D, A>::value, "Failed IsOrCompatible");
  static_assert(!IsOrCompatible<D, B>::value, "Failed IsOrCompatible");
  static_assert(!IsOrCompatible<D, C>::value, "Failed IsOrCompatible");
  static_assert(!IsOrCompatible<D, D>::value, "Failed IsOrCompatible");
}

TEST(MetaObjectTraits, IsBitwiseNotCompatible) {
  struct A{};
  struct B{bool operator~() const;};
  struct C{bool operator~() const = delete;};
  static_assert(IsBitwiseNotCompatible<bool>::value, "Failed IsBitwiseNotCompatible");
  static_assert(IsBitwiseNotCompatible<int>::value, "Failed IsBitwiseNotCompatible");
  static_assert(!IsBitwiseNotCompatible<float>::value, "Failed IsBitwiseNotCompatible");
  static_assert(!IsBitwiseNotCompatible<void*>::value, "Failed IsBitwiseNotCompatible");
  static_assert(!IsBitwiseNotCompatible<void>::value, "Failed IsBitwiseNotCompatible");

  static_assert(!IsBitwiseNotCompatible<A>::value, "Failed IsBitwiseNotCompatible");
  static_assert(IsBitwiseNotCompatible<B>::value, "Failed IsBitwiseNotCompatible");
  static_assert(!IsBitwiseNotCompatible<C>::value, "Failed IsBitwiseNotCompatible");
}

TEST(MetaObjectTraits, IsBitwiseAndCompatible) {
  struct A{};
  struct B{bool operator&(B const&) const; bool operator&(int) const;};
  struct C{bool operator&(C const&) const; bool operator&(B const&) const;};
  struct D{bool operator&(D const&) const = delete; bool operator&(A const&) const;};
  static_assert(IsBitwiseAndCompatible<int>::value, "Failed IsBitwiseAndCompatible");
  static_assert(IsBitwiseAndCompatible<int, int>::value, "Failed IsBitwiseAndCompatible");
  static_assert(!IsBitwiseAndCompatible<int, float>::value, "Failed IsBitwiseAndCompatible");
  static_assert(!IsBitwiseAndCompatible<int*, int>::value, "Failed IsBitwiseAndCompatible");
  static_assert(!IsBitwiseAndCompatible<int, A>::value, "Failed IsBitwiseAndCompatible");
  static_assert(!IsBitwiseAndCompatible<int, B>::value, "Failed IsBitwiseAndCompatible");
  static_assert(!IsBitwiseAndCompatible<int, C>::value, "Failed IsBitwiseAndCompatible");
  static_assert(!IsBitwiseAndCompatible<int, D>::value, "Failed IsBitwiseAndCompatible");

  static_assert(!IsBitwiseAndCompatible<A>::value, "Failed IsBitwiseAndCompatible");
  static_assert(!IsBitwiseAndCompatible<A, int>::value, "Failed IsBitwiseAndCompatible");
  static_assert(!IsBitwiseAndCompatible<A, A>::value, "Failed IsBitwiseAndCompatible");
  static_assert(!IsBitwiseAndCompatible<A, B>::value, "Failed IsBitwiseAndCompatible");
  static_assert(!IsBitwiseAndCompatible<A, C>::value, "Failed IsBitwiseAndCompatible");
  static_assert(!IsBitwiseAndCompatible<A, D>::value, "Failed IsBitwiseAndCompatible");

  static_assert(IsBitwiseAndCompatible<B>::value, "Failed IsBitwiseAndCompatible");
  static_assert(IsBitwiseAndCompatible<B, int>::value, "Failed IsBitwiseAndCompatible");
  static_assert(!IsBitwiseAndCompatible<B, A>::value, "Failed IsBitwiseAndCompatible");
  static_assert(IsBitwiseAndCompatible<B, B>::value, "Failed IsBitwiseAndCompatible");
  static_assert(!IsBitwiseAndCompatible<B, C>::value, "Failed IsBitwiseAndCompatible");
  static_assert(!IsBitwiseAndCompatible<B, D>::value, "Failed IsBitwiseAndCompatible");

  static_assert(IsBitwiseAndCompatible<C>::value, "Failed IsBitwiseAndCompatible");
  static_assert(!IsBitwiseAndCompatible<C, int>::value, "Failed IsBitwiseAndCompatible");
  static_assert(!IsBitwiseAndCompatible<C, A>::value, "Failed IsBitwiseAndCompatible");
  static_assert(IsBitwiseAndCompatible<C, B>::value, "Failed IsBitwiseAndCompatible");
  static_assert(IsBitwiseAndCompatible<C, C>::value, "Failed IsBitwiseAndCompatible");
  static_assert(!IsBitwiseAndCompatible<C, D>::value, "Failed IsBitwiseAndCompatible");

  static_assert(!IsBitwiseAndCompatible<D>::value, "Failed IsBitwiseAndCompatible");
  static_assert(!IsBitwiseAndCompatible<D, int>::value, "Failed IsBitwiseAndCompatible");
  static_assert(IsBitwiseAndCompatible<D, A>::value, "Failed IsBitwiseAndCompatible");
  static_assert(!IsBitwiseAndCompatible<D, B>::value, "Failed IsBitwiseAndCompatible");
  static_assert(!IsBitwiseAndCompatible<D, C>::value, "Failed IsBitwiseAndCompatible");
  static_assert(!IsBitwiseAndCompatible<D, D>::value, "Failed IsBitwiseAndCompatible");
}

TEST(MetaObjectTraits, IsBitwiseOrCompatible) {
  struct A{};
  struct B{bool operator|(B const&) const; bool operator|(int) const;};
  struct C{bool operator|(C const&) const; bool operator|(B const&) const;};
  struct D{bool operator|(D const&) const = delete; bool operator|(A const&) const;};
  static_assert(IsBitwiseOrCompatible<int>::value, "Failed IsBitwiseOrCompatible");
  static_assert(IsBitwiseOrCompatible<int, int>::value, "Failed IsBitwiseOrCompatible");
  static_assert(!IsBitwiseOrCompatible<int, float>::value, "Failed IsBitwiseOrCompatible");
  static_assert(!IsBitwiseOrCompatible<int*, int>::value, "Failed IsBitwiseOrCompatible");
  static_assert(!IsBitwiseOrCompatible<int, A>::value, "Failed IsBitwiseOrCompatible");
  static_assert(!IsBitwiseOrCompatible<int, B>::value, "Failed IsBitwiseOrCompatible");
  static_assert(!IsBitwiseOrCompatible<int, C>::value, "Failed IsBitwiseOrCompatible");
  static_assert(!IsBitwiseOrCompatible<int, D>::value, "Failed IsBitwiseOrCompatible");

  static_assert(!IsBitwiseOrCompatible<A>::value, "Failed IsBitwiseOrCompatible");
  static_assert(!IsBitwiseOrCompatible<A, int>::value, "Failed IsBitwiseOrCompatible");
  static_assert(!IsBitwiseOrCompatible<A, A>::value, "Failed IsBitwiseOrCompatible");
  static_assert(!IsBitwiseOrCompatible<A, B>::value, "Failed IsBitwiseOrCompatible");
  static_assert(!IsBitwiseOrCompatible<A, C>::value, "Failed IsBitwiseOrCompatible");
  static_assert(!IsBitwiseOrCompatible<A, D>::value, "Failed IsBitwiseOrCompatible");

  static_assert(IsBitwiseOrCompatible<B>::value, "Failed IsBitwiseOrCompatible");
  static_assert(IsBitwiseOrCompatible<B, int>::value, "Failed IsBitwiseOrCompatible");
  static_assert(!IsBitwiseOrCompatible<B, A>::value, "Failed IsBitwiseOrCompatible");
  static_assert(IsBitwiseOrCompatible<B, B>::value, "Failed IsBitwiseOrCompatible");
  static_assert(!IsBitwiseOrCompatible<B, C>::value, "Failed IsBitwiseOrCompatible");
  static_assert(!IsBitwiseOrCompatible<B, D>::value, "Failed IsBitwiseOrCompatible");

  static_assert(IsBitwiseOrCompatible<C>::value, "Failed IsBitwiseOrCompatible");
  static_assert(!IsBitwiseOrCompatible<C, int>::value, "Failed IsBitwiseOrCompatible");
  static_assert(!IsBitwiseOrCompatible<C, A>::value, "Failed IsBitwiseOrCompatible");
  static_assert(IsBitwiseOrCompatible<C, B>::value, "Failed IsBitwiseOrCompatible");
  static_assert(IsBitwiseOrCompatible<C, C>::value, "Failed IsBitwiseOrCompatible");
  static_assert(!IsBitwiseOrCompatible<C, D>::value, "Failed IsBitwiseOrCompatible");

  static_assert(!IsBitwiseOrCompatible<D>::value, "Failed IsBitwiseOrCompatible");
  static_assert(!IsBitwiseOrCompatible<D, int>::value, "Failed IsBitwiseOrCompatible");
  static_assert(IsBitwiseOrCompatible<D, A>::value, "Failed IsBitwiseOrCompatible");
  static_assert(!IsBitwiseOrCompatible<D, B>::value, "Failed IsBitwiseOrCompatible");
  static_assert(!IsBitwiseOrCompatible<D, C>::value, "Failed IsBitwiseOrCompatible");
  static_assert(!IsBitwiseOrCompatible<D, D>::value, "Failed IsBitwiseOrCompatible");
}

TEST(MetaObjectTraits, IsBitwiseXorCompatible) {
  struct A{};
  struct B{bool operator^(B const&) const; bool operator^(int) const;};
  struct C{bool operator^(C const&) const; bool operator^(B const&) const;};
  struct D{bool operator^(D const&) const = delete; bool operator^(A const&) const;};
  static_assert(IsBitwiseXorCompatible<int>::value, "Failed IsBitwiseXorCompatible");
  static_assert(IsBitwiseXorCompatible<int, int>::value, "Failed IsBitwiseXorCompatible");
  static_assert(!IsBitwiseXorCompatible<int, float>::value, "Failed IsBitwiseXorCompatible");
  static_assert(!IsBitwiseXorCompatible<int*, int>::value, "Failed IsBitwiseXorCompatible");
  static_assert(!IsBitwiseXorCompatible<int, A>::value, "Failed IsBitwiseXorCompatible");
  static_assert(!IsBitwiseXorCompatible<int, B>::value, "Failed IsBitwiseXorCompatible");
  static_assert(!IsBitwiseXorCompatible<int, C>::value, "Failed IsBitwiseXorCompatible");
  static_assert(!IsBitwiseXorCompatible<int, D>::value, "Failed IsBitwiseXorCompatible");

  static_assert(!IsBitwiseXorCompatible<A>::value, "Failed IsBitwiseXorCompatible");
  static_assert(!IsBitwiseXorCompatible<A, int>::value, "Failed IsBitwiseXorCompatible");
  static_assert(!IsBitwiseXorCompatible<A, A>::value, "Failed IsBitwiseXorCompatible");
  static_assert(!IsBitwiseXorCompatible<A, B>::value, "Failed IsBitwiseXorCompatible");
  static_assert(!IsBitwiseXorCompatible<A, C>::value, "Failed IsBitwiseXorCompatible");
  static_assert(!IsBitwiseXorCompatible<A, D>::value, "Failed IsBitwiseXorCompatible");

  static_assert(IsBitwiseXorCompatible<B>::value, "Failed IsBitwiseXorCompatible");
  static_assert(IsBitwiseXorCompatible<B, int>::value, "Failed IsBitwiseXorCompatible");
  static_assert(!IsBitwiseXorCompatible<B, A>::value, "Failed IsBitwiseXorCompatible");
  static_assert(IsBitwiseXorCompatible<B, B>::value, "Failed IsBitwiseXorCompatible");
  static_assert(!IsBitwiseXorCompatible<B, C>::value, "Failed IsBitwiseXorCompatible");
  static_assert(!IsBitwiseXorCompatible<B, D>::value, "Failed IsBitwiseXorCompatible");

  static_assert(IsBitwiseXorCompatible<C>::value, "Failed IsBitwiseXorCompatible");
  static_assert(!IsBitwiseXorCompatible<C, int>::value, "Failed IsBitwiseXorCompatible");
  static_assert(!IsBitwiseXorCompatible<C, A>::value, "Failed IsBitwiseXorCompatible");
  static_assert(IsBitwiseXorCompatible<C, B>::value, "Failed IsBitwiseXorCompatible");
  static_assert(IsBitwiseXorCompatible<C, C>::value, "Failed IsBitwiseXorCompatible");
  static_assert(!IsBitwiseXorCompatible<C, D>::value, "Failed IsBitwiseXorCompatible");

  static_assert(!IsBitwiseXorCompatible<D>::value, "Failed IsBitwiseXorCompatible");
  static_assert(!IsBitwiseXorCompatible<D, int>::value, "Failed IsBitwiseXorCompatible");
  static_assert(IsBitwiseXorCompatible<D, A>::value, "Failed IsBitwiseXorCompatible");
  static_assert(!IsBitwiseXorCompatible<D, B>::value, "Failed IsBitwiseXorCompatible");
  static_assert(!IsBitwiseXorCompatible<D, C>::value, "Failed IsBitwiseXorCompatible");
  static_assert(!IsBitwiseXorCompatible<D, D>::value, "Failed IsBitwiseXorCompatible");
}

TEST(MetaObjectTraits, IsBitwiseLshCompatible) {
  struct A{};
  struct B{bool operator<<(B const&) const; bool operator<<(int) const;};
  struct C{bool operator<<(C const&) const; bool operator<<(B const&) const;};
  struct D{bool operator<<(D const&) const = delete; bool operator<<(A const&) const;};
  static_assert(IsBitwiseLshCompatible<int>::value, "Failed IsBitwiseLshCompatible");
  static_assert(IsBitwiseLshCompatible<int, int>::value, "Failed IsBitwiseLshCompatible");
  static_assert(!IsBitwiseLshCompatible<int, float>::value, "Failed IsBitwiseLshCompatible");
  static_assert(!IsBitwiseLshCompatible<int*, int>::value, "Failed IsBitwiseLshCompatible");
  static_assert(!IsBitwiseLshCompatible<int, A>::value, "Failed IsBitwiseLshCompatible");
  static_assert(!IsBitwiseLshCompatible<int, B>::value, "Failed IsBitwiseLshCompatible");
  static_assert(!IsBitwiseLshCompatible<int, C>::value, "Failed IsBitwiseLshCompatible");
  static_assert(!IsBitwiseLshCompatible<int, D>::value, "Failed IsBitwiseLshCompatible");

  static_assert(!IsBitwiseLshCompatible<A>::value, "Failed IsBitwiseLshCompatible");
  static_assert(!IsBitwiseLshCompatible<A, int>::value, "Failed IsBitwiseLshCompatible");
  static_assert(!IsBitwiseLshCompatible<A, A>::value, "Failed IsBitwiseLshCompatible");
  static_assert(!IsBitwiseLshCompatible<A, B>::value, "Failed IsBitwiseLshCompatible");
  static_assert(!IsBitwiseLshCompatible<A, C>::value, "Failed IsBitwiseLshCompatible");
  static_assert(!IsBitwiseLshCompatible<A, D>::value, "Failed IsBitwiseLshCompatible");

  static_assert(IsBitwiseLshCompatible<B>::value, "Failed IsBitwiseLshCompatible");
  static_assert(IsBitwiseLshCompatible<B, int>::value, "Failed IsBitwiseLshCompatible");
  static_assert(!IsBitwiseLshCompatible<B, A>::value, "Failed IsBitwiseLshCompatible");
  static_assert(IsBitwiseLshCompatible<B, B>::value, "Failed IsBitwiseLshCompatible");
  static_assert(!IsBitwiseLshCompatible<B, C>::value, "Failed IsBitwiseLshCompatible");
  static_assert(!IsBitwiseLshCompatible<B, D>::value, "Failed IsBitwiseLshCompatible");

  static_assert(IsBitwiseLshCompatible<C>::value, "Failed IsBitwiseLshCompatible");
  static_assert(!IsBitwiseLshCompatible<C, int>::value, "Failed IsBitwiseLshCompatible");
  static_assert(!IsBitwiseLshCompatible<C, A>::value, "Failed IsBitwiseLshCompatible");
  static_assert(IsBitwiseLshCompatible<C, B>::value, "Failed IsBitwiseLshCompatible");
  static_assert(IsBitwiseLshCompatible<C, C>::value, "Failed IsBitwiseLshCompatible");
  static_assert(!IsBitwiseLshCompatible<C, D>::value, "Failed IsBitwiseLshCompatible");

  static_assert(!IsBitwiseLshCompatible<D>::value, "Failed IsBitwiseLshCompatible");
  static_assert(!IsBitwiseLshCompatible<D, int>::value, "Failed IsBitwiseLshCompatible");
  static_assert(IsBitwiseLshCompatible<D, A>::value, "Failed IsBitwiseLshCompatible");
  static_assert(!IsBitwiseLshCompatible<D, B>::value, "Failed IsBitwiseLshCompatible");
  static_assert(!IsBitwiseLshCompatible<D, C>::value, "Failed IsBitwiseLshCompatible");
  static_assert(!IsBitwiseLshCompatible<D, D>::value, "Failed IsBitwiseLshCompatible");
}

TEST(MetaObjectTraits, IsBitwiseRshCompatible) {
  struct A{};
  struct B{bool operator>>(B const&) const; bool operator>>(int) const;};
  struct C{bool operator>>(C const&) const; bool operator>>(B const&) const;};
  struct D{bool operator>>(D const&) const = delete; bool operator>>(A const&) const;};
  static_assert(IsBitwiseRshCompatible<int>::value, "Failed IsBitwiseRshCompatible");
  static_assert(IsBitwiseRshCompatible<int, int>::value, "Failed IsBitwiseRshCompatible");
  static_assert(!IsBitwiseRshCompatible<int, float>::value, "Failed IsBitwiseRshCompatible");
  static_assert(!IsBitwiseRshCompatible<int*, int>::value, "Failed IsBitwiseRshCompatible");
  static_assert(!IsBitwiseRshCompatible<int, A>::value, "Failed IsBitwiseRshCompatible");
  static_assert(!IsBitwiseRshCompatible<int, B>::value, "Failed IsBitwiseRshCompatible");
  static_assert(!IsBitwiseRshCompatible<int, C>::value, "Failed IsBitwiseRshCompatible");
  static_assert(!IsBitwiseRshCompatible<int, D>::value, "Failed IsBitwiseRshCompatible");

  static_assert(!IsBitwiseRshCompatible<A>::value, "Failed IsBitwiseRshCompatible");
  static_assert(!IsBitwiseRshCompatible<A, int>::value, "Failed IsBitwiseRshCompatible");
  static_assert(!IsBitwiseRshCompatible<A, A>::value, "Failed IsBitwiseRshCompatible");
  static_assert(!IsBitwiseRshCompatible<A, B>::value, "Failed IsBitwiseRshCompatible");
  static_assert(!IsBitwiseRshCompatible<A, C>::value, "Failed IsBitwiseRshCompatible");
  static_assert(!IsBitwiseRshCompatible<A, D>::value, "Failed IsBitwiseRshCompatible");

  static_assert(IsBitwiseRshCompatible<B>::value, "Failed IsBitwiseRshCompatible");
  static_assert(IsBitwiseRshCompatible<B, int>::value, "Failed IsBitwiseRshCompatible");
  static_assert(!IsBitwiseRshCompatible<B, A>::value, "Failed IsBitwiseRshCompatible");
  static_assert(IsBitwiseRshCompatible<B, B>::value, "Failed IsBitwiseRshCompatible");
  static_assert(!IsBitwiseRshCompatible<B, C>::value, "Failed IsBitwiseRshCompatible");
  static_assert(!IsBitwiseRshCompatible<B, D>::value, "Failed IsBitwiseRshCompatible");

  static_assert(IsBitwiseRshCompatible<C>::value, "Failed IsBitwiseRshCompatible");
  static_assert(!IsBitwiseRshCompatible<C, int>::value, "Failed IsBitwiseRshCompatible");
  static_assert(!IsBitwiseRshCompatible<C, A>::value, "Failed IsBitwiseRshCompatible");
  static_assert(IsBitwiseRshCompatible<C, B>::value, "Failed IsBitwiseRshCompatible");
  static_assert(IsBitwiseRshCompatible<C, C>::value, "Failed IsBitwiseRshCompatible");
  static_assert(!IsBitwiseRshCompatible<C, D>::value, "Failed IsBitwiseRshCompatible");

  static_assert(!IsBitwiseRshCompatible<D>::value, "Failed IsBitwiseRshCompatible");
  static_assert(!IsBitwiseRshCompatible<D, int>::value, "Failed IsBitwiseRshCompatible");
  static_assert(IsBitwiseRshCompatible<D, A>::value, "Failed IsBitwiseRshCompatible");
  static_assert(!IsBitwiseRshCompatible<D, B>::value, "Failed IsBitwiseRshCompatible");
  static_assert(!IsBitwiseRshCompatible<D, C>::value, "Failed IsBitwiseRshCompatible");
  static_assert(!IsBitwiseRshCompatible<D, D>::value, "Failed IsBitwiseRshCompatible");
}

TEST(MetaObjectTraits, IsAddAssignCompatible) {
  struct A{};
  struct B{bool operator+=(B const&); bool operator+=(int);};
  struct C{bool operator+=(C const&); bool operator+=(B const&);};
  struct D{bool operator+=(D const&) = delete; bool operator+=(A const&);};
  static_assert(IsAddAssignCompatible<int>::value, "Failed IsAddAssignCompatible");
  static_assert(IsAddAssignCompatible<int, int>::value, "Failed IsAddAssignCompatible");
  static_assert(IsAddAssignCompatible<int, float>::value, "Failed IsAddAssignCompatible");
  static_assert(IsAddAssignCompatible<int*, int>::value, "Failed IsAddAssignCompatible");
  static_assert(!IsAddAssignCompatible<int, A>::value, "Failed IsAddAssignCompatible");
  static_assert(!IsAddAssignCompatible<int, B>::value, "Failed IsAddAssignCompatible");
  static_assert(!IsAddAssignCompatible<int, C>::value, "Failed IsAddAssignCompatible");
  static_assert(!IsAddAssignCompatible<int, D>::value, "Failed IsAddAssignCompatible");

  static_assert(!IsAddAssignCompatible<A>::value, "Failed IsAddAssignCompatible");
  static_assert(!IsAddAssignCompatible<A, int>::value, "Failed IsAddAssignCompatible");
  static_assert(!IsAddAssignCompatible<A, A>::value, "Failed IsAddAssignCompatible");
  static_assert(!IsAddAssignCompatible<A, B>::value, "Failed IsAddAssignCompatible");
  static_assert(!IsAddAssignCompatible<A, C>::value, "Failed IsAddAssignCompatible");
  static_assert(!IsAddAssignCompatible<A, D>::value, "Failed IsAddAssignCompatible");

  static_assert(IsAddAssignCompatible<B>::value, "Failed IsAddAssignCompatible");
  static_assert(IsAddAssignCompatible<B, int>::value, "Failed IsAddAssignCompatible");
  static_assert(!IsAddAssignCompatible<B, A>::value, "Failed IsAddAssignCompatible");
  static_assert(IsAddAssignCompatible<B, B>::value, "Failed IsAddAssignCompatible");
  static_assert(!IsAddAssignCompatible<B, C>::value, "Failed IsAddAssignCompatible");
  static_assert(!IsAddAssignCompatible<B, D>::value, "Failed IsAddAssignCompatible");

  static_assert(IsAddAssignCompatible<C>::value, "Failed IsAddAssignCompatible");
  static_assert(!IsAddAssignCompatible<C, int>::value, "Failed IsAddAssignCompatible");
  static_assert(!IsAddAssignCompatible<C, A>::value, "Failed IsAddAssignCompatible");
  static_assert(IsAddAssignCompatible<C, B>::value, "Failed IsAddAssignCompatible");
  static_assert(IsAddAssignCompatible<C, C>::value, "Failed IsAddAssignCompatible");
  static_assert(!IsAddAssignCompatible<C, D>::value, "Failed IsAddAssignCompatible");

  static_assert(!IsAddAssignCompatible<D>::value, "Failed IsAddAssignCompatible");
  static_assert(!IsAddAssignCompatible<D, int>::value, "Failed IsAddAssignCompatible");
  static_assert(IsAddAssignCompatible<D, A>::value, "Failed IsAddAssignCompatible");
  static_assert(!IsAddAssignCompatible<D, B>::value, "Failed IsAddAssignCompatible");
  static_assert(!IsAddAssignCompatible<D, C>::value, "Failed IsAddAssignCompatible");
  static_assert(!IsAddAssignCompatible<D, D>::value, "Failed IsAddAssignCompatible");
}

TEST(MetaObjectTraits, IsSubAssignCompatible) {
  struct A{};
  struct B{bool operator-=(B const&); bool operator-=(int);};
  struct C{bool operator-=(C const&); bool operator-=(B const&);};
  struct D{bool operator-=(D const&) = delete; bool operator-=(A const&);};
  static_assert(IsSubAssignCompatible<int>::value, "Failed IsSubAssignCompatible");
  static_assert(IsSubAssignCompatible<int, int>::value, "Failed IsSubAssignCompatible");
  static_assert(IsSubAssignCompatible<int, float>::value, "Failed IsSubAssignCompatible");
  static_assert(IsSubAssignCompatible<int*, int>::value, "Failed IsSubAssignCompatible");
  static_assert(!IsSubAssignCompatible<int, A>::value, "Failed IsSubAssignCompatible");
  static_assert(!IsSubAssignCompatible<int, B>::value, "Failed IsSubAssignCompatible");
  static_assert(!IsSubAssignCompatible<int, C>::value, "Failed IsSubAssignCompatible");
  static_assert(!IsSubAssignCompatible<int, D>::value, "Failed IsSubAssignCompatible");

  static_assert(!IsSubAssignCompatible<A>::value, "Failed IsSubAssignCompatible");
  static_assert(!IsSubAssignCompatible<A, int>::value, "Failed IsSubAssignCompatible");
  static_assert(!IsSubAssignCompatible<A, A>::value, "Failed IsSubAssignCompatible");
  static_assert(!IsSubAssignCompatible<A, B>::value, "Failed IsSubAssignCompatible");
  static_assert(!IsSubAssignCompatible<A, C>::value, "Failed IsSubAssignCompatible");
  static_assert(!IsSubAssignCompatible<A, D>::value, "Failed IsSubAssignCompatible");

  static_assert(IsSubAssignCompatible<B>::value, "Failed IsSubAssignCompatible");
  static_assert(IsSubAssignCompatible<B, int>::value, "Failed IsSubAssignCompatible");
  static_assert(!IsSubAssignCompatible<B, A>::value, "Failed IsSubAssignCompatible");
  static_assert(IsSubAssignCompatible<B, B>::value, "Failed IsSubAssignCompatible");
  static_assert(!IsSubAssignCompatible<B, C>::value, "Failed IsSubAssignCompatible");
  static_assert(!IsSubAssignCompatible<B, D>::value, "Failed IsSubAssignCompatible");

  static_assert(IsSubAssignCompatible<C>::value, "Failed IsSubAssignCompatible");
  static_assert(!IsSubAssignCompatible<C, int>::value, "Failed IsSubAssignCompatible");
  static_assert(!IsSubAssignCompatible<C, A>::value, "Failed IsSubAssignCompatible");
  static_assert(IsSubAssignCompatible<C, B>::value, "Failed IsSubAssignCompatible");
  static_assert(IsSubAssignCompatible<C, C>::value, "Failed IsSubAssignCompatible");
  static_assert(!IsSubAssignCompatible<C, D>::value, "Failed IsSubAssignCompatible");

  static_assert(!IsSubAssignCompatible<D>::value, "Failed IsSubAssignCompatible");
  static_assert(!IsSubAssignCompatible<D, int>::value, "Failed IsSubAssignCompatible");
  static_assert(IsSubAssignCompatible<D, A>::value, "Failed IsSubAssignCompatible");
  static_assert(!IsSubAssignCompatible<D, B>::value, "Failed IsSubAssignCompatible");
  static_assert(!IsSubAssignCompatible<D, C>::value, "Failed IsSubAssignCompatible");
  static_assert(!IsSubAssignCompatible<D, D>::value, "Failed IsSubAssignCompatible");
}

TEST(MetaObjectTraits, IsMulAssignCompatible) {
  struct A{};
  struct B{bool operator*=(B const&); bool operator*=(int);};
  struct C{bool operator*=(C const&); bool operator*=(B const&);};
  struct D{bool operator*=(D const&) = delete; bool operator*=(A const&);};
  static_assert(IsMulAssignCompatible<int>::value, "Failed IsMulAssignCompatible");
  static_assert(IsMulAssignCompatible<int, int>::value, "Failed IsMulAssignCompatible");
  static_assert(IsMulAssignCompatible<int, float>::value, "Failed IsMulAssignCompatible");
  static_assert(!IsMulAssignCompatible<int*, int>::value, "Failed IsMulAssignCompatible");
  static_assert(!IsMulAssignCompatible<int, A>::value, "Failed IsMulAssignCompatible");
  static_assert(!IsMulAssignCompatible<int, B>::value, "Failed IsMulAssignCompatible");
  static_assert(!IsMulAssignCompatible<int, C>::value, "Failed IsMulAssignCompatible");
  static_assert(!IsMulAssignCompatible<int, D>::value, "Failed IsMulAssignCompatible");

  static_assert(!IsMulAssignCompatible<A>::value, "Failed IsMulAssignCompatible");
  static_assert(!IsMulAssignCompatible<A, int>::value, "Failed IsMulAssignCompatible");
  static_assert(!IsMulAssignCompatible<A, A>::value, "Failed IsMulAssignCompatible");
  static_assert(!IsMulAssignCompatible<A, B>::value, "Failed IsMulAssignCompatible");
  static_assert(!IsMulAssignCompatible<A, C>::value, "Failed IsMulAssignCompatible");
  static_assert(!IsMulAssignCompatible<A, D>::value, "Failed IsMulAssignCompatible");

  static_assert(IsMulAssignCompatible<B>::value, "Failed IsMulAssignCompatible");
  static_assert(IsMulAssignCompatible<B, int>::value, "Failed IsMulAssignCompatible");
  static_assert(!IsMulAssignCompatible<B, A>::value, "Failed IsMulAssignCompatible");
  static_assert(IsMulAssignCompatible<B, B>::value, "Failed IsMulAssignCompatible");
  static_assert(!IsMulAssignCompatible<B, C>::value, "Failed IsMulAssignCompatible");
  static_assert(!IsMulAssignCompatible<B, D>::value, "Failed IsMulAssignCompatible");

  static_assert(IsMulAssignCompatible<C>::value, "Failed IsMulAssignCompatible");
  static_assert(!IsMulAssignCompatible<C, int>::value, "Failed IsMulAssignCompatible");
  static_assert(!IsMulAssignCompatible<C, A>::value, "Failed IsMulAssignCompatible");
  static_assert(IsMulAssignCompatible<C, B>::value, "Failed IsMulAssignCompatible");
  static_assert(IsMulAssignCompatible<C, C>::value, "Failed IsMulAssignCompatible");
  static_assert(!IsMulAssignCompatible<C, D>::value, "Failed IsMulAssignCompatible");

  static_assert(!IsMulAssignCompatible<D>::value, "Failed IsMulAssignCompatible");
  static_assert(!IsMulAssignCompatible<D, int>::value, "Failed IsMulAssignCompatible");
  static_assert(IsMulAssignCompatible<D, A>::value, "Failed IsMulAssignCompatible");
  static_assert(!IsMulAssignCompatible<D, B>::value, "Failed IsMulAssignCompatible");
  static_assert(!IsMulAssignCompatible<D, C>::value, "Failed IsMulAssignCompatible");
  static_assert(!IsMulAssignCompatible<D, D>::value, "Failed IsMulAssignCompatible");
}

TEST(MetaObjectTraits, IsDivAssignCompatible) {
  struct A{};
  struct B{bool operator/=(B const&); bool operator/=(int);};
  struct C{bool operator/=(C const&); bool operator/=(B const&);};
  struct D{bool operator/=(D const&) = delete; bool operator/=(A const&);};
  static_assert(IsDivAssignCompatible<int>::value, "Failed IsDivAssignCompatible");
  static_assert(IsDivAssignCompatible<int, int>::value, "Failed IsDivAssignCompatible");
  static_assert(IsDivAssignCompatible<int, float>::value, "Failed IsDivAssignCompatible");
  static_assert(!IsDivAssignCompatible<int*, int>::value, "Failed IsDivAssignCompatible");
  static_assert(!IsDivAssignCompatible<int, A>::value, "Failed IsDivAssignCompatible");
  static_assert(!IsDivAssignCompatible<int, B>::value, "Failed IsDivAssignCompatible");
  static_assert(!IsDivAssignCompatible<int, C>::value, "Failed IsDivAssignCompatible");
  static_assert(!IsDivAssignCompatible<int, D>::value, "Failed IsDivAssignCompatible");

  static_assert(!IsDivAssignCompatible<A>::value, "Failed IsDivAssignCompatible");
  static_assert(!IsDivAssignCompatible<A, int>::value, "Failed IsDivAssignCompatible");
  static_assert(!IsDivAssignCompatible<A, A>::value, "Failed IsDivAssignCompatible");
  static_assert(!IsDivAssignCompatible<A, B>::value, "Failed IsDivAssignCompatible");
  static_assert(!IsDivAssignCompatible<A, C>::value, "Failed IsDivAssignCompatible");
  static_assert(!IsDivAssignCompatible<A, D>::value, "Failed IsDivAssignCompatible");

  static_assert(IsDivAssignCompatible<B>::value, "Failed IsDivAssignCompatible");
  static_assert(IsDivAssignCompatible<B, int>::value, "Failed IsDivAssignCompatible");
  static_assert(!IsDivAssignCompatible<B, A>::value, "Failed IsDivAssignCompatible");
  static_assert(IsDivAssignCompatible<B, B>::value, "Failed IsDivAssignCompatible");
  static_assert(!IsDivAssignCompatible<B, C>::value, "Failed IsDivAssignCompatible");
  static_assert(!IsDivAssignCompatible<B, D>::value, "Failed IsDivAssignCompatible");

  static_assert(IsDivAssignCompatible<C>::value, "Failed IsDivAssignCompatible");
  static_assert(!IsDivAssignCompatible<C, int>::value, "Failed IsDivAssignCompatible");
  static_assert(!IsDivAssignCompatible<C, A>::value, "Failed IsDivAssignCompatible");
  static_assert(IsDivAssignCompatible<C, B>::value, "Failed IsDivAssignCompatible");
  static_assert(IsDivAssignCompatible<C, C>::value, "Failed IsDivAssignCompatible");
  static_assert(!IsDivAssignCompatible<C, D>::value, "Failed IsDivAssignCompatible");

  static_assert(!IsDivAssignCompatible<D>::value, "Failed IsDivAssignCompatible");
  static_assert(!IsDivAssignCompatible<D, int>::value, "Failed IsDivAssignCompatible");
  static_assert(IsDivAssignCompatible<D, A>::value, "Failed IsDivAssignCompatible");
  static_assert(!IsDivAssignCompatible<D, B>::value, "Failed IsDivAssignCompatible");
  static_assert(!IsDivAssignCompatible<D, C>::value, "Failed IsDivAssignCompatible");
  static_assert(!IsDivAssignCompatible<D, D>::value, "Failed IsDivAssignCompatible");
}

TEST(MetaObjectTraits, IsModAssignCompatible) {
  struct A{};
  struct B{bool operator%=(B const&); bool operator%=(int);};
  struct C{bool operator%=(C const&); bool operator%=(B const&);};
  struct D{bool operator%=(D const&) = delete; bool operator%=(A const&);};
  static_assert(IsModAssignCompatible<int>::value, "Failed IsModAssignCompatible");
  static_assert(IsModAssignCompatible<int, int>::value, "Failed IsModAssignCompatible");
  static_assert(!IsModAssignCompatible<int, float>::value, "Failed IsModAssignCompatible");
  static_assert(!IsModAssignCompatible<int*, int>::value, "Failed IsModAssignCompatible");
  static_assert(!IsModAssignCompatible<int, A>::value, "Failed IsModAssignCompatible");
  static_assert(!IsModAssignCompatible<int, B>::value, "Failed IsModAssignCompatible");
  static_assert(!IsModAssignCompatible<int, C>::value, "Failed IsModAssignCompatible");
  static_assert(!IsModAssignCompatible<int, D>::value, "Failed IsModAssignCompatible");

  static_assert(!IsModAssignCompatible<A>::value, "Failed IsModAssignCompatible");
  static_assert(!IsModAssignCompatible<A, int>::value, "Failed IsModAssignCompatible");
  static_assert(!IsModAssignCompatible<A, A>::value, "Failed IsModAssignCompatible");
  static_assert(!IsModAssignCompatible<A, B>::value, "Failed IsModAssignCompatible");
  static_assert(!IsModAssignCompatible<A, C>::value, "Failed IsModAssignCompatible");
  static_assert(!IsModAssignCompatible<A, D>::value, "Failed IsModAssignCompatible");

  static_assert(IsModAssignCompatible<B>::value, "Failed IsModAssignCompatible");
  static_assert(IsModAssignCompatible<B, int>::value, "Failed IsModAssignCompatible");
  static_assert(!IsModAssignCompatible<B, A>::value, "Failed IsModAssignCompatible");
  static_assert(IsModAssignCompatible<B, B>::value, "Failed IsModAssignCompatible");
  static_assert(!IsModAssignCompatible<B, C>::value, "Failed IsModAssignCompatible");
  static_assert(!IsModAssignCompatible<B, D>::value, "Failed IsModAssignCompatible");

  static_assert(IsModAssignCompatible<C>::value, "Failed IsModAssignCompatible");
  static_assert(!IsModAssignCompatible<C, int>::value, "Failed IsModAssignCompatible");
  static_assert(!IsModAssignCompatible<C, A>::value, "Failed IsModAssignCompatible");
  static_assert(IsModAssignCompatible<C, B>::value, "Failed IsModAssignCompatible");
  static_assert(IsModAssignCompatible<C, C>::value, "Failed IsModAssignCompatible");
  static_assert(!IsModAssignCompatible<C, D>::value, "Failed IsModAssignCompatible");

  static_assert(!IsModAssignCompatible<D>::value, "Failed IsModAssignCompatible");
  static_assert(!IsModAssignCompatible<D, int>::value, "Failed IsModAssignCompatible");
  static_assert(IsModAssignCompatible<D, A>::value, "Failed IsModAssignCompatible");
  static_assert(!IsModAssignCompatible<D, B>::value, "Failed IsModAssignCompatible");
  static_assert(!IsModAssignCompatible<D, C>::value, "Failed IsModAssignCompatible");
  static_assert(!IsModAssignCompatible<D, D>::value, "Failed IsModAssignCompatible");
}

TEST(MetaObjectTraits, IsBitwiseAndAssignCompatible) {
  struct A{};
  struct B{bool operator&=(B const&); bool operator&=(int);};
  struct C{bool operator&=(C const&); bool operator&=(B const&);};
  struct D{bool operator&=(D const&) = delete; bool operator&=(A const&);};
  static_assert(IsBitwiseAndAssignCompatible<int>::value, "Failed IsBitwiseAndAssignCompatible");
  static_assert(IsBitwiseAndAssignCompatible<int, int>::value, "Failed IsBitwiseAndAssignCompatible");
  static_assert(!IsBitwiseAndAssignCompatible<int, float>::value, "Failed IsBitwiseAndAssignCompatible");
  static_assert(!IsBitwiseAndAssignCompatible<int*, int>::value, "Failed IsBitwiseAndAssignCompatible");
  static_assert(!IsBitwiseAndAssignCompatible<int, A>::value, "Failed IsBitwiseAndAssignCompatible");
  static_assert(!IsBitwiseAndAssignCompatible<int, B>::value, "Failed IsBitwiseAndAssignCompatible");
  static_assert(!IsBitwiseAndAssignCompatible<int, C>::value, "Failed IsBitwiseAndAssignCompatible");
  static_assert(!IsBitwiseAndAssignCompatible<int, D>::value, "Failed IsBitwiseAndAssignCompatible");

  static_assert(!IsBitwiseAndAssignCompatible<A>::value, "Failed IsBitwiseAndAssignCompatible");
  static_assert(!IsBitwiseAndAssignCompatible<A, int>::value, "Failed IsBitwiseAndAssignCompatible");
  static_assert(!IsBitwiseAndAssignCompatible<A, A>::value, "Failed IsBitwiseAndAssignCompatible");
  static_assert(!IsBitwiseAndAssignCompatible<A, B>::value, "Failed IsBitwiseAndAssignCompatible");
  static_assert(!IsBitwiseAndAssignCompatible<A, C>::value, "Failed IsBitwiseAndAssignCompatible");
  static_assert(!IsBitwiseAndAssignCompatible<A, D>::value, "Failed IsBitwiseAndAssignCompatible");

  static_assert(IsBitwiseAndAssignCompatible<B>::value, "Failed IsBitwiseAndAssignCompatible");
  static_assert(IsBitwiseAndAssignCompatible<B, int>::value, "Failed IsBitwiseAndAssignCompatible");
  static_assert(!IsBitwiseAndAssignCompatible<B, A>::value, "Failed IsBitwiseAndAssignCompatible");
  static_assert(IsBitwiseAndAssignCompatible<B, B>::value, "Failed IsBitwiseAndAssignCompatible");
  static_assert(!IsBitwiseAndAssignCompatible<B, C>::value, "Failed IsBitwiseAndAssignCompatible");
  static_assert(!IsBitwiseAndAssignCompatible<B, D>::value, "Failed IsBitwiseAndAssignCompatible");

  static_assert(IsBitwiseAndAssignCompatible<C>::value, "Failed IsBitwiseAndAssignCompatible");
  static_assert(!IsBitwiseAndAssignCompatible<C, int>::value, "Failed IsBitwiseAndAssignCompatible");
  static_assert(!IsBitwiseAndAssignCompatible<C, A>::value, "Failed IsBitwiseAndAssignCompatible");
  static_assert(IsBitwiseAndAssignCompatible<C, B>::value, "Failed IsBitwiseAndAssignCompatible");
  static_assert(IsBitwiseAndAssignCompatible<C, C>::value, "Failed IsBitwiseAndAssignCompatible");
  static_assert(!IsBitwiseAndAssignCompatible<C, D>::value, "Failed IsBitwiseAndAssignCompatible");

  static_assert(!IsBitwiseAndAssignCompatible<D>::value, "Failed IsBitwiseAndAssignCompatible");
  static_assert(!IsBitwiseAndAssignCompatible<D, int>::value, "Failed IsBitwiseAndAssignCompatible");
  static_assert(IsBitwiseAndAssignCompatible<D, A>::value, "Failed IsBitwiseAndAssignCompatible");
  static_assert(!IsBitwiseAndAssignCompatible<D, B>::value, "Failed IsBitwiseAndAssignCompatible");
  static_assert(!IsBitwiseAndAssignCompatible<D, C>::value, "Failed IsBitwiseAndAssignCompatible");
  static_assert(!IsBitwiseAndAssignCompatible<D, D>::value, "Failed IsBitwiseAndAssignCompatible");
}

TEST(MetaObjectTraits, IsBitwiseOrAssignCompatible) {
  struct A{};
  struct B{bool operator|=(B const&); bool operator|=(int);};
  struct C{bool operator|=(C const&); bool operator|=(B const&);};
  struct D{bool operator|=(D const&) = delete; bool operator|=(A const&);};
  static_assert(IsBitwiseOrAssignCompatible<int>::value, "Failed IsBitwiseOrAssignCompatible");
  static_assert(IsBitwiseOrAssignCompatible<int, int>::value, "Failed IsBitwiseOrAssignCompatible");
  static_assert(!IsBitwiseOrAssignCompatible<int, float>::value, "Failed IsBitwiseOrAssignCompatible");
  static_assert(!IsBitwiseOrAssignCompatible<int*, int>::value, "Failed IsBitwiseOrAssignCompatible");
  static_assert(!IsBitwiseOrAssignCompatible<int, A>::value, "Failed IsBitwiseOrAssignCompatible");
  static_assert(!IsBitwiseOrAssignCompatible<int, B>::value, "Failed IsBitwiseOrAssignCompatible");
  static_assert(!IsBitwiseOrAssignCompatible<int, C>::value, "Failed IsBitwiseOrAssignCompatible");
  static_assert(!IsBitwiseOrAssignCompatible<int, D>::value, "Failed IsBitwiseOrAssignCompatible");

  static_assert(!IsBitwiseOrAssignCompatible<A>::value, "Failed IsBitwiseOrAssignCompatible");
  static_assert(!IsBitwiseOrAssignCompatible<A, int>::value, "Failed IsBitwiseOrAssignCompatible");
  static_assert(!IsBitwiseOrAssignCompatible<A, A>::value, "Failed IsBitwiseOrAssignCompatible");
  static_assert(!IsBitwiseOrAssignCompatible<A, B>::value, "Failed IsBitwiseOrAssignCompatible");
  static_assert(!IsBitwiseOrAssignCompatible<A, C>::value, "Failed IsBitwiseOrAssignCompatible");
  static_assert(!IsBitwiseOrAssignCompatible<A, D>::value, "Failed IsBitwiseOrAssignCompatible");

  static_assert(IsBitwiseOrAssignCompatible<B>::value, "Failed IsBitwiseOrAssignCompatible");
  static_assert(IsBitwiseOrAssignCompatible<B, int>::value, "Failed IsBitwiseOrAssignCompatible");
  static_assert(!IsBitwiseOrAssignCompatible<B, A>::value, "Failed IsBitwiseOrAssignCompatible");
  static_assert(IsBitwiseOrAssignCompatible<B, B>::value, "Failed IsBitwiseOrAssignCompatible");
  static_assert(!IsBitwiseOrAssignCompatible<B, C>::value, "Failed IsBitwiseOrAssignCompatible");
  static_assert(!IsBitwiseOrAssignCompatible<B, D>::value, "Failed IsBitwiseOrAssignCompatible");

  static_assert(IsBitwiseOrAssignCompatible<C>::value, "Failed IsBitwiseOrAssignCompatible");
  static_assert(!IsBitwiseOrAssignCompatible<C, int>::value, "Failed IsBitwiseOrAssignCompatible");
  static_assert(!IsBitwiseOrAssignCompatible<C, A>::value, "Failed IsBitwiseOrAssignCompatible");
  static_assert(IsBitwiseOrAssignCompatible<C, B>::value, "Failed IsBitwiseOrAssignCompatible");
  static_assert(IsBitwiseOrAssignCompatible<C, C>::value, "Failed IsBitwiseOrAssignCompatible");
  static_assert(!IsBitwiseOrAssignCompatible<C, D>::value, "Failed IsBitwiseOrAssignCompatible");

  static_assert(!IsBitwiseOrAssignCompatible<D>::value, "Failed IsBitwiseOrAssignCompatible");
  static_assert(!IsBitwiseOrAssignCompatible<D, int>::value, "Failed IsBitwiseOrAssignCompatible");
  static_assert(IsBitwiseOrAssignCompatible<D, A>::value, "Failed IsBitwiseOrAssignCompatible");
  static_assert(!IsBitwiseOrAssignCompatible<D, B>::value, "Failed IsBitwiseOrAssignCompatible");
  static_assert(!IsBitwiseOrAssignCompatible<D, C>::value, "Failed IsBitwiseOrAssignCompatible");
  static_assert(!IsBitwiseOrAssignCompatible<D, D>::value, "Failed IsBitwiseOrAssignCompatible");
}

TEST(MetaObjectTraits, IsBitwiseXorAssignCompatible) {
  struct A{};
  struct B{bool operator^=(B const&); bool operator^=(int);};
  struct C{bool operator^=(C const&); bool operator^=(B const&);};
  struct D{bool operator^=(D const&) = delete; bool operator^=(A const&);};
  static_assert(IsBitwiseXorAssignCompatible<int>::value, "Failed IsBitwiseXorAssignCompatible");
  static_assert(IsBitwiseXorAssignCompatible<int, int>::value, "Failed IsBitwiseXorAssignCompatible");
  static_assert(!IsBitwiseXorAssignCompatible<int, float>::value, "Failed IsBitwiseXorAssignCompatible");
  static_assert(!IsBitwiseXorAssignCompatible<int*, int>::value, "Failed IsBitwiseXorAssignCompatible");
  static_assert(!IsBitwiseXorAssignCompatible<int, A>::value, "Failed IsBitwiseXorAssignCompatible");
  static_assert(!IsBitwiseXorAssignCompatible<int, B>::value, "Failed IsBitwiseXorAssignCompatible");
  static_assert(!IsBitwiseXorAssignCompatible<int, C>::value, "Failed IsBitwiseXorAssignCompatible");
  static_assert(!IsBitwiseXorAssignCompatible<int, D>::value, "Failed IsBitwiseXorAssignCompatible");

  static_assert(!IsBitwiseXorAssignCompatible<A>::value, "Failed IsBitwiseXorAssignCompatible");
  static_assert(!IsBitwiseXorAssignCompatible<A, int>::value, "Failed IsBitwiseXorAssignCompatible");
  static_assert(!IsBitwiseXorAssignCompatible<A, A>::value, "Failed IsBitwiseXorAssignCompatible");
  static_assert(!IsBitwiseXorAssignCompatible<A, B>::value, "Failed IsBitwiseXorAssignCompatible");
  static_assert(!IsBitwiseXorAssignCompatible<A, C>::value, "Failed IsBitwiseXorAssignCompatible");
  static_assert(!IsBitwiseXorAssignCompatible<A, D>::value, "Failed IsBitwiseXorAssignCompatible");

  static_assert(IsBitwiseXorAssignCompatible<B>::value, "Failed IsBitwiseXorAssignCompatible");
  static_assert(IsBitwiseXorAssignCompatible<B, int>::value, "Failed IsBitwiseXorAssignCompatible");
  static_assert(!IsBitwiseXorAssignCompatible<B, A>::value, "Failed IsBitwiseXorAssignCompatible");
  static_assert(IsBitwiseXorAssignCompatible<B, B>::value, "Failed IsBitwiseXorAssignCompatible");
  static_assert(!IsBitwiseXorAssignCompatible<B, C>::value, "Failed IsBitwiseXorAssignCompatible");
  static_assert(!IsBitwiseXorAssignCompatible<B, D>::value, "Failed IsBitwiseXorAssignCompatible");

  static_assert(IsBitwiseXorAssignCompatible<C>::value, "Failed IsBitwiseXorAssignCompatible");
  static_assert(!IsBitwiseXorAssignCompatible<C, int>::value, "Failed IsBitwiseXorAssignCompatible");
  static_assert(!IsBitwiseXorAssignCompatible<C, A>::value, "Failed IsBitwiseXorAssignCompatible");
  static_assert(IsBitwiseXorAssignCompatible<C, B>::value, "Failed IsBitwiseXorAssignCompatible");
  static_assert(IsBitwiseXorAssignCompatible<C, C>::value, "Failed IsBitwiseXorAssignCompatible");
  static_assert(!IsBitwiseXorAssignCompatible<C, D>::value, "Failed IsBitwiseXorAssignCompatible");

  static_assert(!IsBitwiseXorAssignCompatible<D>::value, "Failed IsBitwiseXorAssignCompatible");
  static_assert(!IsBitwiseXorAssignCompatible<D, int>::value, "Failed IsBitwiseXorAssignCompatible");
  static_assert(IsBitwiseXorAssignCompatible<D, A>::value, "Failed IsBitwiseXorAssignCompatible");
  static_assert(!IsBitwiseXorAssignCompatible<D, B>::value, "Failed IsBitwiseXorAssignCompatible");
  static_assert(!IsBitwiseXorAssignCompatible<D, C>::value, "Failed IsBitwiseXorAssignCompatible");
  static_assert(!IsBitwiseXorAssignCompatible<D, D>::value, "Failed IsBitwiseXorAssignCompatible");
}

TEST(MetaObjectTraits, IsBitwiseLshAssignCompatible) {
  struct A{};
  struct B{bool operator<<=(B const&); bool operator<<=(int);};
  struct C{bool operator<<=(C const&); bool operator<<=(B const&);};
  struct D{bool operator<<=(D const&) = delete; bool operator<<=(A const&);};
  static_assert(IsBitwiseLshAssignCompatible<int>::value, "Failed IsBitwiseLshAssignCompatible");
  static_assert(IsBitwiseLshAssignCompatible<int, int>::value, "Failed IsBitwiseLshAssignCompatible");
  static_assert(!IsBitwiseLshAssignCompatible<int, float>::value, "Failed IsBitwiseLshAssignCompatible");
  static_assert(!IsBitwiseLshAssignCompatible<int*, int>::value, "Failed IsBitwiseLshAssignCompatible");
  static_assert(!IsBitwiseLshAssignCompatible<int, A>::value, "Failed IsBitwiseLshAssignCompatible");
  static_assert(!IsBitwiseLshAssignCompatible<int, B>::value, "Failed IsBitwiseLshAssignCompatible");
  static_assert(!IsBitwiseLshAssignCompatible<int, C>::value, "Failed IsBitwiseLshAssignCompatible");
  static_assert(!IsBitwiseLshAssignCompatible<int, D>::value, "Failed IsBitwiseLshAssignCompatible");

  static_assert(!IsBitwiseLshAssignCompatible<A>::value, "Failed IsBitwiseLshAssignCompatible");
  static_assert(!IsBitwiseLshAssignCompatible<A, int>::value, "Failed IsBitwiseLshAssignCompatible");
  static_assert(!IsBitwiseLshAssignCompatible<A, A>::value, "Failed IsBitwiseLshAssignCompatible");
  static_assert(!IsBitwiseLshAssignCompatible<A, B>::value, "Failed IsBitwiseLshAssignCompatible");
  static_assert(!IsBitwiseLshAssignCompatible<A, C>::value, "Failed IsBitwiseLshAssignCompatible");
  static_assert(!IsBitwiseLshAssignCompatible<A, D>::value, "Failed IsBitwiseLshAssignCompatible");

  static_assert(IsBitwiseLshAssignCompatible<B>::value, "Failed IsBitwiseLshAssignCompatible");
  static_assert(IsBitwiseLshAssignCompatible<B, int>::value, "Failed IsBitwiseLshAssignCompatible");
  static_assert(!IsBitwiseLshAssignCompatible<B, A>::value, "Failed IsBitwiseLshAssignCompatible");
  static_assert(IsBitwiseLshAssignCompatible<B, B>::value, "Failed IsBitwiseLshAssignCompatible");
  static_assert(!IsBitwiseLshAssignCompatible<B, C>::value, "Failed IsBitwiseLshAssignCompatible");
  static_assert(!IsBitwiseLshAssignCompatible<B, D>::value, "Failed IsBitwiseLshAssignCompatible");

  static_assert(IsBitwiseLshAssignCompatible<C>::value, "Failed IsBitwiseLshAssignCompatible");
  static_assert(!IsBitwiseLshAssignCompatible<C, int>::value, "Failed IsBitwiseLshAssignCompatible");
  static_assert(!IsBitwiseLshAssignCompatible<C, A>::value, "Failed IsBitwiseLshAssignCompatible");
  static_assert(IsBitwiseLshAssignCompatible<C, B>::value, "Failed IsBitwiseLshAssignCompatible");
  static_assert(IsBitwiseLshAssignCompatible<C, C>::value, "Failed IsBitwiseLshAssignCompatible");
  static_assert(!IsBitwiseLshAssignCompatible<C, D>::value, "Failed IsBitwiseLshAssignCompatible");

  static_assert(!IsBitwiseLshAssignCompatible<D>::value, "Failed IsBitwiseLshAssignCompatible");
  static_assert(!IsBitwiseLshAssignCompatible<D, int>::value, "Failed IsBitwiseLshAssignCompatible");
  static_assert(IsBitwiseLshAssignCompatible<D, A>::value, "Failed IsBitwiseLshAssignCompatible");
  static_assert(!IsBitwiseLshAssignCompatible<D, B>::value, "Failed IsBitwiseLshAssignCompatible");
  static_assert(!IsBitwiseLshAssignCompatible<D, C>::value, "Failed IsBitwiseLshAssignCompatible");
  static_assert(!IsBitwiseLshAssignCompatible<D, D>::value, "Failed IsBitwiseLshAssignCompatible");
}

TEST(MetaObjectTraits, IsBitwiseRshAssignCompatible) {
  struct A{};
  struct B{bool operator>>=(B const&); bool operator>>=(int);};
  struct C{bool operator>>=(C const&); bool operator>>=(B const&);};
  struct D{bool operator>>=(D const&) = delete; bool operator>>=(A const&);};
  static_assert(IsBitwiseRshAssignCompatible<int>::value, "Failed IsBitwiseRshAssignCompatible");
  static_assert(IsBitwiseRshAssignCompatible<int, int>::value, "Failed IsBitwiseRshAssignCompatible");
  static_assert(!IsBitwiseRshAssignCompatible<int, float>::value, "Failed IsBitwiseRshAssignCompatible");
  static_assert(!IsBitwiseRshAssignCompatible<int*, int>::value, "Failed IsBitwiseRshAssignCompatible");
  static_assert(!IsBitwiseRshAssignCompatible<int, A>::value, "Failed IsBitwiseRshAssignCompatible");
  static_assert(!IsBitwiseRshAssignCompatible<int, B>::value, "Failed IsBitwiseRshAssignCompatible");
  static_assert(!IsBitwiseRshAssignCompatible<int, C>::value, "Failed IsBitwiseRshAssignCompatible");
  static_assert(!IsBitwiseRshAssignCompatible<int, D>::value, "Failed IsBitwiseRshAssignCompatible");

  static_assert(!IsBitwiseRshAssignCompatible<A>::value, "Failed IsBitwiseRshAssignCompatible");
  static_assert(!IsBitwiseRshAssignCompatible<A, int>::value, "Failed IsBitwiseRshAssignCompatible");
  static_assert(!IsBitwiseRshAssignCompatible<A, A>::value, "Failed IsBitwiseRshAssignCompatible");
  static_assert(!IsBitwiseRshAssignCompatible<A, B>::value, "Failed IsBitwiseRshAssignCompatible");
  static_assert(!IsBitwiseRshAssignCompatible<A, C>::value, "Failed IsBitwiseRshAssignCompatible");
  static_assert(!IsBitwiseRshAssignCompatible<A, D>::value, "Failed IsBitwiseRshAssignCompatible");

  static_assert(IsBitwiseRshAssignCompatible<B>::value, "Failed IsBitwiseRshAssignCompatible");
  static_assert(IsBitwiseRshAssignCompatible<B, int>::value, "Failed IsBitwiseRshAssignCompatible");
  static_assert(!IsBitwiseRshAssignCompatible<B, A>::value, "Failed IsBitwiseRshAssignCompatible");
  static_assert(IsBitwiseRshAssignCompatible<B, B>::value, "Failed IsBitwiseRshAssignCompatible");
  static_assert(!IsBitwiseRshAssignCompatible<B, C>::value, "Failed IsBitwiseRshAssignCompatible");
  static_assert(!IsBitwiseRshAssignCompatible<B, D>::value, "Failed IsBitwiseRshAssignCompatible");

  static_assert(IsBitwiseRshAssignCompatible<C>::value, "Failed IsBitwiseRshAssignCompatible");
  static_assert(!IsBitwiseRshAssignCompatible<C, int>::value, "Failed IsBitwiseRshAssignCompatible");
  static_assert(!IsBitwiseRshAssignCompatible<C, A>::value, "Failed IsBitwiseRshAssignCompatible");
  static_assert(IsBitwiseRshAssignCompatible<C, B>::value, "Failed IsBitwiseRshAssignCompatible");
  static_assert(IsBitwiseRshAssignCompatible<C, C>::value, "Failed IsBitwiseRshAssignCompatible");
  static_assert(!IsBitwiseRshAssignCompatible<C, D>::value, "Failed IsBitwiseRshAssignCompatible");

  static_assert(!IsBitwiseRshAssignCompatible<D>::value, "Failed IsBitwiseRshAssignCompatible");
  static_assert(!IsBitwiseRshAssignCompatible<D, int>::value, "Failed IsBitwiseRshAssignCompatible");
  static_assert(IsBitwiseRshAssignCompatible<D, A>::value, "Failed IsBitwiseRshAssignCompatible");
  static_assert(!IsBitwiseRshAssignCompatible<D, B>::value, "Failed IsBitwiseRshAssignCompatible");
  static_assert(!IsBitwiseRshAssignCompatible<D, C>::value, "Failed IsBitwiseRshAssignCompatible");
  static_assert(!IsBitwiseRshAssignCompatible<D, D>::value, "Failed IsBitwiseRshAssignCompatible");
}

TEST(MetaObjectTraits, IsSubscriptCompatible) {
  struct A{};
  struct B{bool operator[](B const&); bool operator[](int);};
  struct C{bool operator[](C const&); bool operator[](B const&);};
  struct D{bool operator[](D const&) = delete; bool operator[](A const&);};
  static_assert(!IsSubscriptCompatible<int>::value, "Failed IsSubscriptCompatible");
  static_assert(!IsSubscriptCompatible<int, int>::value, "Failed IsSubscriptCompatible");
  static_assert(!IsSubscriptCompatible<int, float>::value, "Failed IsSubscriptCompatible");
  static_assert(IsSubscriptCompatible<int*, int>::value, "Failed IsSubscriptCompatible");
  static_assert(!IsSubscriptCompatible<int, A>::value, "Failed IsSubscriptCompatible");
  static_assert(!IsSubscriptCompatible<int, B>::value, "Failed IsSubscriptCompatible");
  static_assert(!IsSubscriptCompatible<int, C>::value, "Failed IsSubscriptCompatible");
  static_assert(!IsSubscriptCompatible<int, D>::value, "Failed IsSubscriptCompatible");

  static_assert(!IsSubscriptCompatible<A>::value, "Failed IsSubscriptCompatible");
  static_assert(!IsSubscriptCompatible<A, int>::value, "Failed IsSubscriptCompatible");
  static_assert(!IsSubscriptCompatible<A, A>::value, "Failed IsSubscriptCompatible");
  static_assert(!IsSubscriptCompatible<A, B>::value, "Failed IsSubscriptCompatible");
  static_assert(!IsSubscriptCompatible<A, C>::value, "Failed IsSubscriptCompatible");
  static_assert(!IsSubscriptCompatible<A, D>::value, "Failed IsSubscriptCompatible");

  static_assert(IsSubscriptCompatible<B>::value, "Failed IsSubscriptCompatible");
  static_assert(IsSubscriptCompatible<B, int>::value, "Failed IsSubscriptCompatible");
  static_assert(!IsSubscriptCompatible<B, A>::value, "Failed IsSubscriptCompatible");
  static_assert(IsSubscriptCompatible<B, B>::value, "Failed IsSubscriptCompatible");
  static_assert(!IsSubscriptCompatible<B, C>::value, "Failed IsSubscriptCompatible");
  static_assert(!IsSubscriptCompatible<B, D>::value, "Failed IsSubscriptCompatible");

  static_assert(!IsSubscriptCompatible<C>::value, "Failed IsSubscriptCompatible");
  static_assert(!IsSubscriptCompatible<C, int>::value, "Failed IsSubscriptCompatible");
  static_assert(!IsSubscriptCompatible<C, A>::value, "Failed IsSubscriptCompatible");
  static_assert(IsSubscriptCompatible<C, B>::value, "Failed IsSubscriptCompatible");
  static_assert(IsSubscriptCompatible<C, C>::value, "Failed IsSubscriptCompatible");
  static_assert(!IsSubscriptCompatible<C, D>::value, "Failed IsSubscriptCompatible");

  static_assert(!IsSubscriptCompatible<D>::value, "Failed IsSubscriptCompatible");
  static_assert(!IsSubscriptCompatible<D, int>::value, "Failed IsSubscriptCompatible");
  static_assert(IsSubscriptCompatible<D, A>::value, "Failed IsSubscriptCompatible");
  static_assert(!IsSubscriptCompatible<D, B>::value, "Failed IsSubscriptCompatible");
  static_assert(!IsSubscriptCompatible<D, C>::value, "Failed IsSubscriptCompatible");
  static_assert(!IsSubscriptCompatible<D, D>::value, "Failed IsSubscriptCompatible");
}

TEST(MetaObjectTraits, IsIndirectionCompatible) {
  struct A{};
  struct B{int operator*();};
  struct C{int operator*() = delete;};
  static_assert(!IsIndirectionCompatible<bool>::value, "Failed IsIndirectionCompatible");
  static_assert(!IsIndirectionCompatible<int>::value, "Failed IsIndirectionCompatible");
  static_assert(!IsIndirectionCompatible<float>::value, "Failed IsIndirectionCompatible");
  static_assert(!IsIndirectionCompatible<void*>::value, "Failed IsIndirectionCompatible");
  static_assert(IsIndirectionCompatible<int*>::value, "Failed IsIndirectionCompatible");
  static_assert(!IsIndirectionCompatible<A>::value, "Failed IsIndirectionCompatible");
  static_assert(IsIndirectionCompatible<B>::value, "Failed IsIndirectionCompatible");
  static_assert(!IsIndirectionCompatible<C>::value, "Failed IsIndirectionCompatible");
}

TEST(MetaObjectTraits, IsAddressOfCompatible) {
  struct A{};
  struct B{int operator&();};
  struct C{int operator&() = delete;};
  static_assert(IsAddressOfCompatible<bool>::value, "Failed IsAddressOfCompatible");
  static_assert(IsAddressOfCompatible<int>::value, "Failed IsAddressOfCompatible");
  static_assert(IsAddressOfCompatible<float>::value, "Failed IsAddressOfCompatible");
  static_assert(IsAddressOfCompatible<void*>::value, "Failed IsAddressOfCompatible");
  static_assert(IsAddressOfCompatible<int*>::value, "Failed IsAddressOfCompatible");
  static_assert(IsAddressOfCompatible<A>::value, "Failed IsAddressOfCompatible");
  static_assert(IsAddressOfCompatible<B>::value, "Failed IsAddressOfCompatible");
  static_assert(!IsAddressOfCompatible<C>::value, "Failed IsAddressOfCompatible");
}

TEST(MetaObjectTraits, BindCompatibilityWithIsCompatible) {
  struct A{int a;};
  struct B{B() = default; B(B const&) = default; B(B&&) = default; B& operator=(B const&) = default; B& operator=(B&&) = default;};
  struct C{C(); C(C const&); C(C&&) noexcept; C& operator=(C const&); C& operator=(C&&) noexcept;};
  struct D{D() = delete; D(D const&) = delete; D(D&&) = delete; D& operator=(D const&) = delete; D& operator=(D&&) = delete;};
  static_assert(All<Bind<IsTriviallyConstructible, A, Ph<0>>::Type, A>::value, "Failed BindIsTriviallyConstructible");
  static_assert(!All<Bind<IsTriviallyConstructible, A, Ph<0>>::Type, int, long, void>::value, "Failed BindIsTriviallyConstructible");
  static_assert(!All<Bind<IsTriviallyConstructible, A, Ph<0>>::Type, int, long, B>::value, "Failed BindIsTriviallyConstructible");
  static_assert(!All<Bind<IsTriviallyAssignable, A, Ph<0>>::Type, int>::value, "Failed IsTriviallyAssignable");

  static_assert(All<Bind<IsTriviallyAssignable, A, Ph<0>>::Type, A>::value, "Failed IsTriviallyAssignable");
  static_assert(All<Bind<IsTriviallyAssignable, B, Ph<0>>::Type, B>::value, "Failed IsTriviallyAssignable");
  static_assert(!All<Bind<IsTriviallyAssignable, C, Ph<0>>::Type, C>::value, "Failed IsTriviallyAssignable");
  static_assert(!All<Bind<IsTriviallyAssignable, D, Ph<0>>::Type, D>::value, "Failed IsTriviallyAssignable");

  static_assert(All<Bind<IsAddCompatible, int, Ph<0>>::Type, int, float>::value, "Failed IsAddCompatible");
  static_assert(All<Bind<IsSubCompatible, int, Ph<0>>::Type, int, float>::value, "Failed IsSubCompatible");
  static_assert(All<Bind<IsMulCompatible, int, Ph<0>>::Type, int, float>::value, "Failed IsMulCompatible");
  static_assert(All<Bind<IsDivCompatible, int, Ph<0>>::Type, int, float>::value, "Failed IsDivCompatible");
  static_assert(All<Bind<IsModCompatible, int, Ph<0>>::Type, int, long>::value, "Failed IsModCompatible");

  static_assert(!All<Bind<IsAddCompatible, int, Ph<0>>::Type, int, void>::value, "Failed IsAddCompatible");
  static_assert(!All<Bind<IsSubCompatible, int, Ph<0>>::Type, int, void>::value, "Failed IsSubCompatible");
  static_assert(!All<Bind<IsMulCompatible, int, Ph<0>>::Type, int, void>::value, "Failed IsMulCompatible");
  static_assert(!All<Bind<IsDivCompatible, int, Ph<0>>::Type, int, void>::value, "Failed IsDivCompatible");
  static_assert(!All<Bind<IsModCompatible, int, Ph<0>>::Type, int, float>::value, "Failed IsModCompatible");

  static_assert(All<Bind<IsLtCompatible, int, Ph<0>>::Type, int, float>::value, "Failed IsLtCompatible");
  static_assert(All<Bind<IsLeCompatible, int, Ph<0>>::Type, int, float>::value, "Failed IsLeCompatible");
  static_assert(All<Bind<IsGtCompatible, int, Ph<0>>::Type, int, float>::value, "Failed IsGtCompatible");
  static_assert(All<Bind<IsGeCompatible, int, Ph<0>>::Type, int, float>::value, "Failed IsGeCompatible");
  static_assert(All<Bind<IsEqCompatible, int, Ph<0>>::Type, int, float>::value, "Failed IsEqCompatible");
  static_assert(All<Bind<IsNeCompatible, int, Ph<0>>::Type, int, float>::value, "Failed IsNeCompatible");

  static_assert(!All<Bind<IsLtCompatible, int, Ph<0>>::Type, int, void>::value, "Failed IsLtCompatible");
  static_assert(!All<Bind<IsLeCompatible, int, Ph<0>>::Type, int, void>::value, "Failed IsLeCompatible");
  static_assert(!All<Bind<IsGtCompatible, int, Ph<0>>::Type, int, void>::value, "Failed IsGtCompatible");
  static_assert(!All<Bind<IsGeCompatible, int, Ph<0>>::Type, int, void>::value, "Failed IsGeCompatible");
  static_assert(!All<Bind<IsEqCompatible, int, Ph<0>>::Type, int, void>::value, "Failed IsEqCompatible");
  static_assert(!All<Bind<IsNeCompatible, int, Ph<0>>::Type, int, void>::value, "Failed IsNeCompatible");

#if DCR_SINCECPP20
  static_assert(All<Bind<IsSpaceshipCompatible, int, Ph<0>>::Type, int, float>::value, "Failed IsSpaceshipCompatible");
  static_assert(!All<Bind<IsSpaceshipCompatible, int, Ph<0>>::Type, int, void>::value, "Failed IsSpaceshipCompatible");
#endif

  static_assert(All<Bind<IsAndCompatible, int, Ph<0>>::Type, int, float>::value, "Failed IsAndCompatible");
  static_assert(All<Bind<IsOrCompatible, int, Ph<0>>::Type, int, float>::value, "Failed IsAndCompatible");

  static_assert(!All<Bind<IsAndCompatible, int, Ph<0>>::Type, int, void>::value, "Failed IsAndCompatible");
  static_assert(!All<Bind<IsOrCompatible, int, Ph<0>>::Type, int, void>::value, "Failed IsAndCompatible");

  static_assert(All<Bind<IsBitwiseAndCompatible, int, Ph<0>>::Type, int, long>::value, "Failed IsBitwiseAndCompatible");
  static_assert(All<Bind<IsBitwiseOrCompatible, int, Ph<0>>::Type, int, long>::value, "Failed IsBitwiseOrCompatible");
  static_assert(All<Bind<IsBitwiseXorCompatible, int, Ph<0>>::Type, int, long>::value, "Failed IsBitwiseXorCompatible");
  static_assert(All<Bind<IsBitwiseLshCompatible, int, Ph<0>>::Type, int, long>::value, "Failed IsBitwiseLshCompatible");
  static_assert(All<Bind<IsBitwiseRshCompatible, int, Ph<0>>::Type, int, long>::value, "Failed IsBitwiseRshCompatible");

  static_assert(!All<Bind<IsBitwiseAndCompatible, int, Ph<0>>::Type, int, float>::value, "Failed IsBitwiseAndCompatible");
  static_assert(!All<Bind<IsBitwiseOrCompatible, int, Ph<0>>::Type, int, float>::value, "Failed IsBitwiseOrCompatible");
  static_assert(!All<Bind<IsBitwiseXorCompatible, int, Ph<0>>::Type, int, float>::value, "Failed IsBitwiseXorCompatible");
  static_assert(!All<Bind<IsBitwiseLshCompatible, int, Ph<0>>::Type, int, float>::value, "Failed IsBitwiseLshCompatible");
  static_assert(!All<Bind<IsBitwiseRshCompatible, int, Ph<0>>::Type, int, float>::value, "Failed IsBitwiseRshCompatible");

  static_assert(All<Bind<IsAddAssignCompatible, int, Ph<0>>::Type, int, long, float>::value, "Failed IsAddAssignCompatible");
  static_assert(All<Bind<IsSubAssignCompatible, int, Ph<0>>::Type, int, long, float>::value, "Failed IsSubAssignCompatible");
  static_assert(All<Bind<IsMulAssignCompatible, int, Ph<0>>::Type, int, long, float>::value, "Failed IsMulAssignCompatible");
  static_assert(All<Bind<IsDivAssignCompatible, int, Ph<0>>::Type, int, long, float>::value, "Failed IsDivAssignCompatible");
  static_assert(All<Bind<IsModAssignCompatible, int, Ph<0>>::Type, int, long>::value, "Failed IsModAssignCompatible");

  static_assert(!All<Bind<IsAddAssignCompatible, int, Ph<0>>::Type, int, void, float>::value, "Failed IsAddAssignCompatible");
  static_assert(!All<Bind<IsSubAssignCompatible, int, Ph<0>>::Type, int, void, float>::value, "Failed IsSubAssignCompatible");
  static_assert(!All<Bind<IsMulAssignCompatible, int, Ph<0>>::Type, int, void, float>::value, "Failed IsMulAssignCompatible");
  static_assert(!All<Bind<IsDivAssignCompatible, int, Ph<0>>::Type, int, void, float>::value, "Failed IsDivAssignCompatible");
  static_assert(!All<Bind<IsModAssignCompatible, int, Ph<0>>::Type, int, void>::value, "Failed IsModAssignCompatible");

  static_assert(All<Bind<IsBitwiseAndAssignCompatible, int, Ph<0>>::Type, int, long>::value, "Failed IsBitwiseAndAssignCompatible");
  static_assert(All<Bind<IsBitwiseOrAssignCompatible, int, Ph<0>>::Type, int, long>::value, "Failed IsBitwiseOrAssignCompatible");
  static_assert(All<Bind<IsBitwiseXorAssignCompatible, int, Ph<0>>::Type, int, long>::value, "Failed IsBitwiseXorAssignCompatible");
  static_assert(All<Bind<IsBitwiseLshAssignCompatible, int, Ph<0>>::Type, int, long>::value, "Failed IsBitwiseLshAssignCompatible");
  static_assert(All<Bind<IsBitwiseRshAssignCompatible, int, Ph<0>>::Type, int, long>::value, "Failed IsBitwiseRshAssignCompatible");

  static_assert(!All<Bind<IsBitwiseAndAssignCompatible, int, Ph<0>>::Type, int, float>::value, "Failed IsBitwiseAndAssignCompatible");
  static_assert(!All<Bind<IsBitwiseOrAssignCompatible, int, Ph<0>>::Type, int, float>::value, "Failed IsBitwiseOrAssignCompatible");
  static_assert(!All<Bind<IsBitwiseXorAssignCompatible, int, Ph<0>>::Type, int, float>::value, "Failed IsBitwiseXorAssignCompatible");
  static_assert(!All<Bind<IsBitwiseLshAssignCompatible, int, Ph<0>>::Type, int, float>::value, "Failed IsBitwiseLshAssignCompatible");
  static_assert(!All<Bind<IsBitwiseRshAssignCompatible, int, Ph<0>>::Type, int, float>::value, "Failed IsBitwiseRshAssignCompatible");

  static_assert(All<Bind<IsSubscriptCompatible, int*, Ph<0>>::Type, int, long>::value, "Failed IsSubscriptCompatible");
  static_assert(!All<Bind<IsSubscriptCompatible, int*, Ph<0>>::Type, int, float>::value, "Failed IsSubscriptCompatible");
}

TEST(MetaObjectTraits, IsBaseOf) {
  struct A {};
  struct B : A {};
  struct C : B {};
  struct D : A {};
  struct E {};

  static_assert(!IsBaseOf<int, int>::value, "Failed IsBaseOf");
  static_assert(IsBaseOf<A, B>::value, "Failed IsBaseOf");
  static_assert(!IsBaseOf<B, A>::value, "Failed IsBaseOf");
  static_assert(IsBaseOf<A, C>::value, "Failed IsBaseOf");
  static_assert(IsBaseOf<B, C>::value, "Failed IsBaseOf");
  static_assert(IsBaseOf<A, D>::value, "Failed IsBaseOf");
  static_assert(!IsBaseOf<B, D>::value, "Failed IsBaseOf");
  static_assert(!IsBaseOf<A, E>::value, "Failed IsBaseOf");
}

TEST(MetaObjectTraits, IsDerivedFrom) {
  struct A {};
  struct B : A {};
  struct C : B {};
  struct D : A {};
  struct E {};

  static_assert(!IsDerivedFrom<int, int>::value, "Failed IsDerivedFrom");
  static_assert(IsDerivedFrom<B, A>::value, "Failed IsDerivedFrom");
  static_assert(!IsDerivedFrom<A, B>::value, "Failed IsDerivedFrom");
  static_assert(IsDerivedFrom<C, A>::value, "Failed IsDerivedFrom");
  static_assert(IsDerivedFrom<C, B>::value, "Failed IsDerivedFrom");
  static_assert(IsDerivedFrom<D, A>::value, "Failed IsDerivedFrom");
  static_assert(!IsDerivedFrom<D, B>::value, "Failed IsDerivedFrom");
  static_assert(!IsDerivedFrom<E, A>::value, "Failed IsDerivedFrom");
}

TEST(MetaObjectTraits, IsAssignable) {
  struct A {};
  struct C {};
  struct D { D& operator=(D const&) = delete; };
  struct B { B& operator=(B const&); B& operator=(A const&); C& operator=(C const&); };

  static_assert(IsAssignable<int, int, int&>::value, "Failed IsAssignable");
  static_assert(IsAssignable<int&, int, int&>::value, "Failed IsAssignable");
  static_assert(IsAssignable<A, A, A&>::value, "Failed IsAssignable");
  static_assert(!IsAssignable<D, D, D&>::value, "Failed IsAssignable");
  static_assert(IsAssignable<B, B, B&>::value, "Failed IsAssignable");
  static_assert(IsAssignable<B, B const&, B&>::value, "Failed IsAssignable");
  static_assert(IsAssignable<B, A const&, B&>::value, "Failed IsAssignable");
  static_assert(IsAssignable<B, C const&, C&>::value, "Failed IsAssignable");
}
