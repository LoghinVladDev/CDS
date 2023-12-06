// DCR-TEST
// STEPS: compile(linux:gcc;linux:clang)
// STD: 11-2b

#include "UnitTest.hpp"
#include "../../../src/meta/ObjectTraits.hpp"

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
  static_assert(Eq<False, IsTriviallyAssignable<int, int>>::value, "Failed IsTriviallyAssignable");
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
  struct C{C(); C(C const&); C(C&&); C& operator=(C const&); C& operator=(C&&);};

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
  struct C{C(); C(C const&); C(C&&); C& operator=(C const&); C& operator=(C&&);};
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
