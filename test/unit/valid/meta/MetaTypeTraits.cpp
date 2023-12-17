// DCR-TEST
// STEPS: compile(linux:gcc;linux:clang),run(linux:clang)
// STD: 11

#include "cds/meta/TypeTraits"
#include "UnitTest.hpp"

using namespace cds;
using namespace cds::meta;

TEST(MetaTypeTraits, RemoveConst) {
  static_assert(IsSame<RemoveConst<int>, int>::value, "Failed RemoveConst");
  static_assert(IsSame<RemoveConst<int const>, int>::value, "Failed RemoveConst");
  static_assert(IsSame<RemoveConst<int volatile>, int volatile>::value, "Failed RemoveConst");
  static_assert(IsSame<RemoveConst<int const volatile>, int volatile>::value, "Failed RemoveConst");
  static_assert(IsSame<RemoveConst<int const*>, int const*>::value, "Failed RemoveConst");
  static_assert(IsSame<RemoveConst<int const* const>, int const*>::value, "Failed RemoveConst");
  static_assert(IsSame<RemoveConst<int&>, int&>::value, "Failed RemoveConst");
  static_assert(IsSame<RemoveConst<int&&>, int&&>::value, "Failed RemoveConst");
  static_assert(IsSame<RemoveConst<int const&>, int const&>::value, "Failed RemoveConst");
  static_assert(IsSame<RemoveConst<int const&&>, int const&&>::value, "Failed RemoveConst");
  static_assert(IsSame<RemoveConst<int[]>, int[]>::value, "Failed RemoveConst");
  static_assert(IsSame<RemoveConst<int const[]>, int[]>::value, "Failed RemoveConst");
  static_assert(IsSame<RemoveConst<int const[][10]>, int[][10]>::value, "Failed RemoveConst");
}

TEST(MetaTypeTraits, RemoveVolatile) {
  static_assert(IsSame<RemoveVolatile<int>, int>::value, "Failed RemoveVolatile");
  static_assert(IsSame<RemoveVolatile<int const>, int const>::value, "Failed RemoveVolatile");
  static_assert(IsSame<RemoveVolatile<int volatile>, int>::value, "Failed RemoveVolatile");
  static_assert(IsSame<RemoveVolatile<int const volatile>, int const>::value, "Failed RemoveVolatile");
  static_assert(IsSame<RemoveVolatile<int volatile*>, int volatile*>::value, "Failed RemoveVolatile");
  static_assert(IsSame<RemoveVolatile<int volatile* volatile>, int volatile*>::value, "Failed RemoveVolatile");
  static_assert(IsSame<RemoveVolatile<int&>, int&>::value, "Failed RemoveVolatile");
  static_assert(IsSame<RemoveVolatile<int&&>, int&&>::value, "Failed RemoveVolatile");
  static_assert(IsSame<RemoveVolatile<int volatile&>, int volatile&>::value, "Failed RemoveVolatile");
  static_assert(IsSame<RemoveVolatile<int volatile&&>, int volatile&&>::value, "Failed RemoveVolatile");
  static_assert(IsSame<RemoveVolatile<int[]>, int[]>::value, "Failed RemoveVolatile");
  static_assert(IsSame<RemoveVolatile<int volatile[]>, int[]>::value, "Failed RemoveVolatile");
  static_assert(IsSame<RemoveVolatile<int volatile[][10]>, int[][10]>::value, "Failed RemoveVolatile");
}

TEST(MetaTypeTraits, RemoveConstVolatile) {
  static_assert(IsSame<RemoveConstVolatile<int>, int>::value, "Failed RemoveConstVolatile");
  static_assert(IsSame<RemoveConstVolatile<int const>, int>::value, "Failed RemoveConstVolatile");
  static_assert(IsSame<RemoveConstVolatile<int volatile>, int>::value, "Failed RemoveConstVolatile");
  static_assert(IsSame<RemoveConstVolatile<int const volatile>, int>::value, "Failed RemoveConstVolatile");
  static_assert(IsSame<RemoveConstVolatile<int const volatile*>, int const volatile*>::value, "Failed RemoveConstVolatile");
  static_assert(IsSame<RemoveConstVolatile<int const volatile* const volatile>, int const volatile*>::value, "Failed RemoveConstVolatile");
  static_assert(IsSame<RemoveConstVolatile<int&>, int&>::value, "Failed RemoveConstVolatile");
  static_assert(IsSame<RemoveConstVolatile<int&&>, int&&>::value, "Failed RemoveConstVolatile");
  static_assert(IsSame<RemoveConstVolatile<int const volatile&>, int const volatile&>::value, "Failed RemoveConstVolatile");
  static_assert(IsSame<RemoveConstVolatile<int const volatile&&>, int const volatile&&>::value, "Failed RemoveConstVolatile");
  static_assert(IsSame<RemoveConstVolatile<int[]>, int[]>::value, "Failed RemoveConstVolatile");
  static_assert(IsSame<RemoveConstVolatile<int const volatile[]>, int[]>::value, "Failed RemoveConstVolatile");
  static_assert(IsSame<RemoveConstVolatile<int const volatile[][10]>, int[][10]>::value, "Failed RemoveConstVolatile");
}

TEST(MetaTypeTraits, RemoveRef) {
  static_assert(IsSame<RemoveRef<int>, int>::value, "Failed RemoveRef");
  static_assert(IsSame<RemoveRef<int const>, int const>::value, "Failed RemoveRef");
  static_assert(IsSame<RemoveRef<int volatile>, int volatile>::value, "Failed RemoveRef");
  static_assert(IsSame<RemoveRef<int const volatile>, int const volatile>::value, "Failed RemoveRef");
  static_assert(IsSame<RemoveRef<int const volatile*>, int const volatile*>::value, "Failed RemoveRef");
  static_assert(IsSame<RemoveRef<int const volatile* const volatile>, int const volatile* const volatile>::value, "Failed RemoveRef");
  static_assert(IsSame<RemoveRef<int&>, int>::value, "Failed RemoveRef");
  static_assert(IsSame<RemoveRef<int&&>, int>::value, "Failed RemoveRef");
  static_assert(IsSame<RemoveRef<int const volatile&>, int const volatile>::value, "Failed RemoveRef");
  static_assert(IsSame<RemoveRef<int const volatile&&>, int const volatile>::value, "Failed RemoveRef");
  static_assert(IsSame<RemoveRef<int[]>, int[]>::value, "Failed RemoveRef");
  static_assert(IsSame<RemoveRef<int[]>, int[]>::value, "Failed RemoveRef");
  static_assert(IsSame<RemoveRef<int const volatile[]>, int const volatile[]>::value, "Failed RemoveRef");
  static_assert(IsSame<RemoveRef<int const volatile[][10]>, int const volatile[][10]>::value, "Failed RemoveRef");
}

TEST(MetaTypeTraits, RemoveCVRef) {
  static_assert(IsSame<RemoveCVRef<int>, int>::value, "Failed RemoveCVRef");
  static_assert(IsSame<RemoveCVRef<int const>, int>::value, "Failed RemoveCVRef");
  static_assert(IsSame<RemoveCVRef<int volatile>, int>::value, "Failed RemoveCVRef");
  static_assert(IsSame<RemoveCVRef<int const volatile>, int>::value, "Failed RemoveCVRef");
  static_assert(IsSame<RemoveCVRef<int const volatile*>, int const volatile*>::value, "Failed RemoveCVRef");
  static_assert(IsSame<RemoveCVRef<int const volatile* const volatile>, int const volatile*>::value, "Failed RemoveCVRef");
  static_assert(IsSame<RemoveCVRef<int&>, int>::value, "Failed RemoveCVRef");
  static_assert(IsSame<RemoveCVRef<int&&>, int>::value, "Failed RemoveCVRef");
  static_assert(IsSame<RemoveCVRef<int const volatile&>, int const volatile>::value, "Failed RemoveCVRef");
  static_assert(IsSame<RemoveCVRef<int const volatile&&>, int const volatile>::value, "Failed RemoveCVRef");
  static_assert(IsSame<RemoveCVRef<int[]>, int[]>::value, "Failed RemoveCVRef");
  static_assert(IsSame<RemoveCVRef<int[]>, int[]>::value, "Failed RemoveCVRef");
  static_assert(IsSame<RemoveCVRef<int const volatile[]>, int[]>::value, "Failed RemoveCVRef");
  static_assert(IsSame<RemoveCVRef<int const volatile[][10]>, int[][10]>::value, "Failed RemoveCVRef");
}

TEST(MetaTypeTraits, RemovePointer) {
  static_assert(IsSame<RemovePointer<int>, int>::value, "Failed RemovePointer");
  static_assert(IsSame<RemovePointer<int const>, int const>::value, "Failed RemovePointer");
  static_assert(IsSame<RemovePointer<int volatile>, int volatile>::value, "Failed RemovePointer");
  static_assert(IsSame<RemovePointer<int const volatile>, int const volatile>::value, "Failed RemovePointer");
  static_assert(IsSame<RemovePointer<int const volatile*>, int const volatile>::value, "Failed RemovePointer");
  static_assert(IsSame<RemovePointer<int const volatile* const volatile>, int const volatile>::value, "Failed RemovePointer");
  static_assert(IsSame<RemovePointer<int&>, int&>::value, "Failed RemovePointer");
  static_assert(IsSame<RemovePointer<int&&>, int&&>::value, "Failed RemovePointer");
  static_assert(IsSame<RemovePointer<int const volatile&>, int const volatile&>::value, "Failed RemovePointer");
  static_assert(IsSame<RemovePointer<int const volatile&&>, int const volatile&&>::value, "Failed RemovePointer");
  static_assert(IsSame<RemovePointer<int[]>, int[]>::value, "Failed RemovePointer");
  static_assert(IsSame<RemovePointer<int[]>, int[]>::value, "Failed RemovePointer");
  static_assert(IsSame<RemovePointer<int const volatile[]>, int const volatile[]>::value, "Failed RemovePointer");
  static_assert(IsSame<RemovePointer<int const volatile[][10]>, int const volatile[][10]>::value, "Failed RemovePointer");
}

TEST(MetaTypeTraits, RemoveExtent) {
  static_assert(IsSame<RemoveExtent<int>, int>::value, "Failed RemoveExtent");
  static_assert(IsSame<RemoveExtent<int const>, int const>::value, "Failed RemoveExtent");
  static_assert(IsSame<RemoveExtent<int volatile>, int volatile>::value, "Failed RemoveExtent");
  static_assert(IsSame<RemoveExtent<int const volatile>, int const volatile>::value, "Failed RemoveExtent");
  static_assert(IsSame<RemoveExtent<int const volatile*>, int const volatile*>::value, "Failed RemoveExtent");
  static_assert(IsSame<RemoveExtent<int const volatile* const volatile>, int const volatile* const volatile>::value, "Failed RemoveExtent");
  static_assert(IsSame<RemoveExtent<int&>, int&>::value, "Failed RemoveExtent");
  static_assert(IsSame<RemoveExtent<int&&>, int&&>::value, "Failed RemoveExtent");
  static_assert(IsSame<RemoveExtent<int const volatile&>, int const volatile&>::value, "Failed RemoveExtent");
  static_assert(IsSame<RemoveExtent<int const volatile&&>, int const volatile&&>::value, "Failed RemoveExtent");
  static_assert(IsSame<RemoveExtent<int[]>, int>::value, "Failed RemoveExtent");
  static_assert(IsSame<RemoveExtent<int[]>, int>::value, "Failed RemoveExtent");
  static_assert(IsSame<RemoveExtent<int const volatile[]>, int const volatile>::value, "Failed RemoveExtent");
  static_assert(IsSame<RemoveExtent<int const volatile[][10]>, int const volatile[10]>::value, "Failed RemoveExtent");
}

TEST(MetaTypeTraits, RemoveAllExtents) {
  static_assert(IsSame<RemoveAllExtents<int>, int>::value, "Failed RemoveAllExtents");
  static_assert(IsSame<RemoveAllExtents<int const>, int const>::value, "Failed RemoveAllExtents");
  static_assert(IsSame<RemoveAllExtents<int volatile>, int volatile>::value, "Failed RemoveAllExtents");
  static_assert(IsSame<RemoveAllExtents<int const volatile>, int const volatile>::value, "Failed RemoveAllExtents");
  static_assert(IsSame<RemoveAllExtents<int const volatile*>, int const volatile*>::value, "Failed RemoveAllExtents");
  static_assert(IsSame<RemoveAllExtents<int const volatile* const volatile>, int const volatile* const volatile>::value, "Failed RemoveAllExtents");
  static_assert(IsSame<RemoveAllExtents<int&>, int&>::value, "Failed RemoveAllExtents");
  static_assert(IsSame<RemoveAllExtents<int&&>, int&&>::value, "Failed RemoveAllExtents");
  static_assert(IsSame<RemoveAllExtents<int const volatile&>, int const volatile&>::value, "Failed RemoveAllExtents");
  static_assert(IsSame<RemoveAllExtents<int const volatile&&>, int const volatile&&>::value, "Failed RemoveAllExtents");
  static_assert(IsSame<RemoveAllExtents<int[]>, int>::value, "Failed RemoveAllExtents");
  static_assert(IsSame<RemoveAllExtents<int[]>, int>::value, "Failed RemoveAllExtents");
  static_assert(IsSame<RemoveAllExtents<int const volatile[]>, int const volatile>::value, "Failed RemoveAllExtents");
  static_assert(IsSame<RemoveAllExtents<int const volatile[][10]>, int const volatile>::value, "Failed RemoveAllExtents");
}

TEST(MetaTypeTraits, IsReferenceable) {
  static_assert(Eq<IsReferenceable<int>, True>::value, "Failed IsReferenceable");
  static_assert(!IsReferenceable<void>::value, "Failed IsReferenceable");
  static_assert(!IsReferenceable<void const>::value, "Failed IsReferenceable");
  static_assert(IsReferenceable<void*>::value, "Failed IsReferenceable");
}

TEST(MetaTypeTraits, IsVoid) {
  static_assert(Eq<IsVoid<int>, False>::value, "Failed IsVoid");
  static_assert(IsVoid<void>::value, "Failed IsVoid");
  static_assert(IsVoid<void const>::value, "Failed IsVoid");
  static_assert(!IsVoid<void*>::value, "Failed IsVoid");
}

TEST(MetaTypeTraits, IsEnum) {
  enum A{Ab};
  enum class B{a};
  static_assert(Eq<IsEnum<int>, False>::value, "Failed IsEnum");
  static_assert(!IsEnum<void>::value, "Failed IsEnum");
  static_assert(IsEnum<A>::value, "Failed IsEnum");
  static_assert(IsEnum<B>::value, "Failed IsEnum");
  static_assert(IsEnum<decltype(Ab)>::value, "Failed IsEnum");
  static_assert(IsEnum<decltype(B::a)>::value, "Failed IsEnum");
}

TEST(MetaTypeTraits, IsUnion) {
  struct A{};
  union B{};
  static_assert(Eq<IsUnion<int>, False>::value, "Failed IsUnion");
  static_assert(!IsUnion<void>::value, "Failed IsUnion");
  static_assert(!IsUnion<A>::value, "Failed IsUnion");
  static_assert(IsUnion<B>::value, "Failed IsUnion");
}

TEST(MetaTypeTraits, IsClass) {
  struct A{};
  union B{};
  class C{};
  static_assert(Eq<IsClass<int>, False>::value, "Failed IsClass");
  static_assert(!IsClass<void>::value, "Failed IsClass");
  static_assert(IsClass<A>::value, "Failed IsClass");
  static_assert(!IsClass<B>::value, "Failed IsClass");
  static_assert(IsClass<C>::value, "Failed IsClass");
}

void func();
TEST(MetaTypeTraits, IsFunction) {
  struct A{};
  union B{};
  class C{};
  struct D{void operator()();};
  auto lbd = [](){};

  static_assert(Eq<False, IsFunction<int>>::value, "Failed IsFunction");
  static_assert(!IsFunction<void>::value, "Failed IsFunction");
  static_assert(!IsFunction<A>::value, "Failed IsFunction");
  static_assert(!IsFunction<B>::value, "Failed IsFunction");
  static_assert(!IsFunction<C>::value, "Failed IsFunction");
  static_assert(!IsFunction<D>::value, "Failed IsFunction");
  static_assert(!IsFunction<decltype(value<D>())>::value, "Failed IsFunction");
  static_assert(!IsFunction<decltype(&D::operator())>::value, "Failed IsFunction");
  static_assert(!IsFunction<decltype(lbd)>::value, "Failed IsFunction");
  static_assert(IsFunction<decltype(func)>::value, "Failed IsFunction");
  static_assert(!IsFunction<decltype(&func)>::value, "Failed IsFunction");
}

TEST(MetaTypeTraits, IsFundamental) {
  struct A{};
  union B{};
  static_assert(Eq<True, IsFundamental<int>>::value, "Failed IsFundamental");
  static_assert(IsFundamental<void>::value, "Failed IsFundamental");
  static_assert(!IsFundamental<void*>::value, "Failed IsFundamental");
  static_assert(!IsFundamental<A>::value, "Failed IsFundamental");
  static_assert(!IsFundamental<B>::value, "Failed IsFundamental");
  static_assert(!IsFundamental<decltype(func)>::value, "Failed IsFundamental");
}

TEST(MetaTypeTraits, IsIntegral) {
  struct A{};
  union B{};
  static_assert(Eq<True, IsIntegral<int>>::value, "Failed IsIntegral");
  static_assert(IsIntegral<bool>::value, "Failed IsIntegral");
  static_assert(!IsIntegral<float>::value, "Failed IsIntegral");
  static_assert(!IsIntegral<void>::value, "Failed IsIntegral");
  static_assert(!IsIntegral<void*>::value, "Failed IsIntegral");
  static_assert(!IsIntegral<A>::value, "Failed IsIntegral");
  static_assert(!IsIntegral<B>::value, "Failed IsIntegral");
  static_assert(!IsIntegral<decltype(func)>::value, "Failed IsIntegral");
}

TEST(MetaTypeTraits, IsFloating) {
  struct A{};
  union B{};
  static_assert(Eq<False, IsFloating<int>>::value, "Failed IsFloating");
  static_assert(!IsFloating<bool>::value, "Failed IsFloating");
  static_assert(IsFloating<float>::value, "Failed IsFloating");
  static_assert(!IsFloating<void>::value, "Failed IsFloating");
  static_assert(!IsFloating<void*>::value, "Failed IsFloating");
  static_assert(!IsFloating<A>::value, "Failed IsFloating");
  static_assert(!IsFloating<B>::value, "Failed IsFloating");
  static_assert(!IsFloating<decltype(func)>::value, "Failed IsFloating");
}

TEST(MetaTypeTraits, IsArithmetic) {
  struct A{};
  union B{};
  static_assert(Eq<True, IsArithmetic<int>>::value, "Failed IsArithmetic");
  static_assert(IsArithmetic<bool>::value, "Failed IsArithmetic");
  static_assert(IsArithmetic<float>::value, "Failed IsArithmetic");
  static_assert(!IsArithmetic<void>::value, "Failed IsArithmetic");
  static_assert(!IsArithmetic<void*>::value, "Failed IsArithmetic");
  static_assert(!IsArithmetic<A>::value, "Failed IsArithmetic");
  static_assert(!IsArithmetic<B>::value, "Failed IsArithmetic");
  static_assert(!IsArithmetic<decltype(func)>::value, "Failed IsArithmetic");
}

TEST(MetaTypeTraits, IsSigned) {
  struct A{};
  union B{};
  static_assert(Eq<True, IsSigned<int>>::value, "Failed IsSigned");
  static_assert(!IsSigned<unsigned int>::value, "Failed IsSigned");
  static_assert(!IsSigned<bool>::value, "Failed IsSigned");
  static_assert(IsSigned<float>::value, "Failed IsSigned");
  static_assert(!IsSigned<void>::value, "Failed IsSigned");
  static_assert(!IsSigned<void*>::value, "Failed IsSigned");
  static_assert(!IsSigned<A>::value, "Failed IsSigned");
  static_assert(!IsSigned<B>::value, "Failed IsSigned");
  static_assert(!IsSigned<decltype(func)>::value, "Failed IsSigned");
}

TEST(MetaTypeTraits, IsArray) {
  static_assert(Eq<False, IsArray<int>>::value, "Failed IsArray");
  static_assert(Eq<True, IsArray<int[]>>::value, "Failed IsArray");
  static_assert(Eq<True, IsArray<int[10]>>::value, "Failed IsArray");
  static_assert(Eq<True, IsArray<int const[]>>::value, "Failed IsArray");
  static_assert(Eq<True, IsArray<int const[10]>>::value, "Failed IsArray");
  static_assert(Eq<True, IsArray<int volatile[]>>::value, "Failed IsArray");
  static_assert(Eq<True, IsArray<int volatile[10]>>::value, "Failed IsArray");
  static_assert(Eq<True, IsArray<int const volatile[]>>::value, "Failed IsArray");
  static_assert(Eq<True, IsArray<int const volatile[10]>>::value, "Failed IsArray");
}

TEST(MetaTypeTraits, IsBoundedArray) {
  static_assert(Eq<False, IsBoundedArray<int>>::value, "Failed IsBoundedArray");
  static_assert(Eq<False, IsBoundedArray<int[]>>::value, "Failed IsBoundedArray");
  static_assert(Eq<True, IsBoundedArray<int[10]>>::value, "Failed IsBoundedArray");
  static_assert(Eq<False, IsBoundedArray<int const[]>>::value, "Failed IsBoundedArray");
  static_assert(Eq<True, IsBoundedArray<int const[10]>>::value, "Failed IsBoundedArray");
  static_assert(Eq<False, IsBoundedArray<int volatile[]>>::value, "Failed IsBoundedArray");
  static_assert(Eq<True, IsBoundedArray<int volatile[10]>>::value, "Failed IsBoundedArray");
  static_assert(Eq<False, IsBoundedArray<int const volatile[]>>::value, "Failed IsBoundedArray");
  static_assert(Eq<True, IsBoundedArray<int const volatile[10]>>::value, "Failed IsBoundedArray");
}

TEST(MetaTypeTraits, IsUnboundedArray) {
  static_assert(Eq<False, IsUnboundedArray<int>>::value, "Failed IsUnboundedArray");
  static_assert(Eq<True, IsUnboundedArray<int[]>>::value, "Failed IsUnboundedArray");
  static_assert(Eq<False, IsUnboundedArray<int[10]>>::value, "Failed IsUnboundedArray");
  static_assert(Eq<True, IsUnboundedArray<int const[]>>::value, "Failed IsUnboundedArray");
  static_assert(Eq<False, IsUnboundedArray<int const[10]>>::value, "Failed IsUnboundedArray");
  static_assert(Eq<True, IsUnboundedArray<int volatile[]>>::value, "Failed IsUnboundedArray");
  static_assert(Eq<False, IsUnboundedArray<int volatile[10]>>::value, "Failed IsUnboundedArray");
  static_assert(Eq<True, IsUnboundedArray<int const volatile[]>>::value, "Failed IsUnboundedArray");
  static_assert(Eq<False, IsUnboundedArray<int const volatile[10]>>::value, "Failed IsUnboundedArray");
}

TEST(MetaTypeTraits, IsPointer) {
  static_assert(Eq<False, IsPointer<int>>::value, "Failed IsPointer");
  static_assert(Eq<False, IsPointer<int[]>>::value, "Failed IsPointer");
  static_assert(Eq<False, IsPointer<int[10]>>::value, "Failed IsPointer");
  static_assert(Eq<True, IsPointer<int*>>::value, "Failed IsPointer");
  static_assert(Eq<True, IsPointer<int**>>::value, "Failed IsPointer");
}

TEST(MetaTypeTraits, IsLValRef) {
  static_assert(Eq<False, IsLValRef<int>>::value, "Failed IsLValRef");
  static_assert(Eq<False, IsLValRef<int const>>::value, "Failed IsLValRef");
  static_assert(Eq<True, IsLValRef<int&>>::value, "Failed IsLValRef");
  static_assert(Eq<False, IsLValRef<int&&>>::value, "Failed IsLValRef");
  static_assert(Eq<True, IsLValRef<int const&>>::value, "Failed IsLValRef");
  static_assert(Eq<False, IsLValRef<int const&&>>::value, "Failed IsLValRef");
}

TEST(MetaTypeTraits, IsRValRef) {
  static_assert(Eq<False, IsRValRef<int>>::value, "Failed IsRValRef");
  static_assert(Eq<False, IsRValRef<int const>>::value, "Failed IsRValRef");
  static_assert(Eq<False, IsRValRef<int&>>::value, "Failed IsRValRef");
  static_assert(Eq<True, IsRValRef<int&&>>::value, "Failed IsRValRef");
  static_assert(Eq<False, IsRValRef<int const&>>::value, "Failed IsRValRef");
  static_assert(Eq<True, IsRValRef<int const&&>>::value, "Failed IsRValRef");
}

TEST(MetaTypeTraits, IsRef) {
  static_assert(Eq<False, IsRef<int>>::value, "Failed IsRef");
  static_assert(Eq<False, IsRef<int const>>::value, "Failed IsRef");
  static_assert(Eq<True, IsRef<int&>>::value, "Failed IsRef");
  static_assert(Eq<True, IsRef<int&&>>::value, "Failed IsRef");
  static_assert(Eq<True, IsRef<int const&>>::value, "Failed IsRef");
  static_assert(Eq<True, IsRef<int const&&>>::value, "Failed IsRef");
}

TEST(MetaTypeTraits, IsConst) {
  static_assert(Eq<False, IsConst<int>>::value, "Failed IsConst");
  static_assert(Eq<True, IsConst<int const>>::value, "Failed IsConst");
  static_assert(Eq<False, IsConst<int&>>::value, "Failed IsConst");
  static_assert(Eq<False, IsConst<int&&>>::value, "Failed IsConst");
  static_assert(Eq<False, IsConst<int const&>>::value, "Failed IsConst");
  static_assert(Eq<False, IsConst<int const&&>>::value, "Failed IsConst");
}

TEST(MetaTypeTraits, IsVolatile) {
  static_assert(Eq<False, IsVolatile<int>>::value, "Failed IsVolatile");
  static_assert(Eq<True, IsVolatile<int volatile>>::value, "Failed IsVolatile");
  static_assert(Eq<False, IsVolatile<int&>>::value, "Failed IsVolatile");
  static_assert(Eq<False, IsVolatile<int&&>>::value, "Failed IsVolatile");
  static_assert(Eq<False, IsVolatile<int volatile&>>::value, "Failed IsVolatile");
  static_assert(Eq<False, IsVolatile<int volatile&&>>::value, "Failed IsVolatile");
}

TEST(MetaTypeTraits, IsConstVolatile) {
  static_assert(Eq<False, IsConstVolatile<int>>::value, "Failed IsConstVolatile");
  static_assert(Eq<False, IsConstVolatile<int volatile>>::value, "Failed IsConstVolatile");
  static_assert(Eq<False, IsConstVolatile<int const>>::value, "Failed IsConstVolatile");
  static_assert(Eq<True, IsConstVolatile<int const volatile>>::value, "Failed IsConstVolatile");
  static_assert(Eq<False, IsConstVolatile<int&>>::value, "Failed IsConstVolatile");
  static_assert(Eq<False, IsConstVolatile<int&&>>::value, "Failed IsConstVolatile");
  static_assert(Eq<False, IsConstVolatile<int const volatile&>>::value, "Failed IsConstVolatile");
  static_assert(Eq<False, IsConstVolatile<int const volatile&&>>::value, "Failed IsConstVolatile");
}

TEST(MetaTypeTraits, IsConvertible) {
  struct A{};
  struct B{B(A);};
  static_assert(Eq<True, IsConvertible<int, int>>::value, "Failed IsConstVolatile");
  static_assert(Eq<True, IsConvertible<int, float>>::value, "Failed IsConstVolatile");
  static_assert(Eq<True, IsConvertible<float, int>>::value, "Failed IsConstVolatile");
  static_assert(Eq<True, IsConvertible<bool, int>>::value, "Failed IsConstVolatile");
  static_assert(Eq<True, IsConvertible<int, bool>>::value, "Failed IsConstVolatile");
  static_assert(Eq<False, IsConvertible<void, bool>>::value, "Failed IsConstVolatile");
  static_assert(Eq<False, IsConvertible<bool, void>>::value, "Failed IsConstVolatile");
  static_assert(Eq<False, IsConvertible<bool, bool*>>::value, "Failed IsConstVolatile");
  static_assert(Eq<True, IsConvertible<A, B>>::value, "Failed IsConstVolatile");
  static_assert(Eq<False, IsConvertible<B, A>>::value, "Failed IsConstVolatile");
}

TEST(MetaTypeTraits, AddPointer) {
  static_assert(IsSame<AddPointer<int>, int*>::value, "Failed AddPointer");
  static_assert(IsSame<AddPointer<int&>, int*>::value, "Failed AddPointer");
  static_assert(IsSame<AddPointer<int*&>, int**>::value, "Failed AddPointer");
  static_assert(IsSame<AddPointer<int*>, int**>::value, "Failed AddPointer");
  static_assert(IsSame<AddPointer<int const>, int const*>::value, "Failed AddPointer");
  static_assert(IsSame<AddPointer<int volatile>, int volatile*>::value, "Failed AddPointer");
  static_assert(IsSame<AddPointer<int const volatile>, int const volatile*>::value, "Failed AddPointer");
  static_assert(IsSame<AddPointer<int[]>, int(*)[]>::value, "Failed AddPointer");
}

TEST(MetaTypeTraits, AddConst) {
  static_assert(IsSame<AddConst<int>, int const>::value, "Failed AddConst");
  static_assert(IsSame<AddConst<int&>, int&>::value, "Failed AddConst");
  static_assert(IsSame<AddConst<int&&>, int&&>::value, "Failed AddConst");
  static_assert(IsSame<AddConst<int*>, int* const>::value, "Failed AddConst");
  static_assert(IsSame<AddConst<int const>, int const>::value, "Failed AddConst");
  static_assert(IsSame<AddConst<int[]>, int const[]>::value, "Failed AddConst");
  static_assert(IsSame<AddConst<int volatile>, int const volatile>::value, "Failed AddConst");
}

TEST(MetaTypeTraits, AddVolatile) {
  static_assert(IsSame<AddVolatile<int>, int volatile>::value, "Failed AddVolatile");
  static_assert(IsSame<AddVolatile<int&>, int&>::value, "Failed AddVolatile");
  static_assert(IsSame<AddVolatile<int&&>, int&&>::value, "Failed AddVolatile");
  static_assert(IsSame<AddVolatile<int*>, int* volatile>::value, "Failed AddVolatile");
  static_assert(IsSame<AddVolatile<int const>, int const volatile>::value, "Failed AddVolatile");
  static_assert(IsSame<AddVolatile<int[]>, int volatile[]>::value, "Failed AddVolatile");
  static_assert(IsSame<AddVolatile<int volatile>, int volatile>::value, "Failed AddVolatile");
}

TEST(MetaTypeTraits, AddConstVolatile) {
  static_assert(IsSame<AddConstVolatile<int>, int const volatile>::value, "Failed AddConstVolatile");
  static_assert(IsSame<AddConstVolatile<int&>, int&>::value, "Failed AddConstVolatile");
  static_assert(IsSame<AddConstVolatile<int&&>, int&&>::value, "Failed AddConstVolatile");
  static_assert(IsSame<AddConstVolatile<int*>, int* const volatile>::value, "Failed AddConstVolatile");
  static_assert(IsSame<AddConstVolatile<int const>, int const volatile>::value, "Failed AddConstVolatile");
  static_assert(IsSame<AddConstVolatile<int[]>, int const volatile[]>::value, "Failed AddConstVolatile");
  static_assert(IsSame<AddConstVolatile<int volatile>, int const volatile>::value, "Failed AddConstVolatile");
}

TEST(MetaTypeTraits, AddLValRef) {
  static_assert(IsSame<AddLValRef<int>, int&>::value, "Failed AddLValRef");
  static_assert(IsSame<AddLValRef<int&>, int&>::value, "Failed AddLValRef");
  static_assert(IsSame<AddLValRef<int&&>, int&>::value, "Failed AddLValRef");
  static_assert(IsSame<AddLValRef<int*>, int*&>::value, "Failed AddLValRef");
  static_assert(IsSame<AddLValRef<int const>, int const&>::value, "Failed AddLValRef");
  static_assert(IsSame<AddLValRef<int[]>, int(&)[]>::value, "Failed AddLValRef");
  static_assert(IsSame<AddLValRef<int volatile>, int volatile&>::value, "Failed AddLValRef");
}

TEST(MetaTypeTraits, AddRValRef) {
  static_assert(IsSame<AddRValRef<int>, int&&>::value, "Failed AddRValRef");
  static_assert(IsSame<AddRValRef<int&>, int&>::value, "Failed AddRValRef");
  static_assert(IsSame<AddRValRef<int&&>, int&&>::value, "Failed AddRValRef");
  static_assert(IsSame<AddRValRef<int*>, int*&&>::value, "Failed AddRValRef");
  static_assert(IsSame<AddRValRef<int const>, int const&&>::value, "Failed AddRValRef");
  static_assert(IsSame<AddRValRef<int[]>, int(&&)[]>::value, "Failed AddRValRef");
  static_assert(IsSame<AddRValRef<int volatile>, int volatile&&>::value, "Failed AddRValRef");
}

TEST(MetaTypeTraits, BindCompat) {
  static_assert(Eq<True, All<Bind<IsConvertible, int, Ph<0>>::Type, int>>::value, "Failed Bind");
  static_assert(Eq<True, All<Bind<IsConvertible, int, Ph<0>>::Type, float>>::value, "Failed Bind");
  static_assert(Eq<True, All<Bind<IsConvertible, int, Ph<0>>::Type, bool>>::value, "Failed Bind");
  static_assert(Ne<True, All<Bind<IsConvertible, int*, Ph<0>>::Type, int>>::value, "Failed Bind");
  static_assert(Ne<True, All<Bind<IsConvertible, bool, Ph<0>>::Type, int*>>::value, "Failed Bind");
  static_assert(Eq<True, All<Bind<IsConvertible, int*, Ph<0>>::Type, bool>>::value, "Failed Bind");
  static_assert(Eq<True, All<BindLeft<IsConvertible, int>::Type, int>>::value, "Failed BindLeft");
  static_assert(!Eq<True, All<BindLeft<IsConvertible, int>::Type, int*>>::value, "Failed BindLeft");
  static_assert(Eq<True, All<BindLeft<IsConvertible, int*>::Type, bool>>::value, "Failed BindLeft");
  static_assert(Eq<True, All<BindRight<IsConvertible, bool>::Type, int*>>::value, "Failed BindLeft");
  static_assert(!Eq<True, All<BindRight<IsConvertible, int>::Type, int*>>::value, "Failed BindLeft");

  static_assert(All<Bind<IsReferenceable, Ph<0>>::Type, int, int>::value, "Failed Bind IsReferenceable");
  static_assert(!All<Bind<IsReferenceable, Ph<0>>::Type, void, int>::value, "Failed Bind IsReferenceable");
  static_assert(!All<Bind<IsReferenceable, Ph<0>>::Type, int, void>::value, "Failed Bind IsReferenceable");

  static_assert(All<Bind<IsVoid, Ph<0>>::Type, void, void>::value, "Failed Bind IsVoid");
  static_assert(!All<Bind<IsVoid, Ph<0>>::Type, void, int>::value, "Failed Bind IsVoid");
  static_assert(!All<Bind<IsVoid, Ph<0>>::Type, int, void>::value, "Failed Bind IsVoid");

  enum A{aa}; enum class B{ab};
  static_assert(All<Bind<IsEnum, Ph<0>>::Type, A, B>::value, "Failed Bind IsEnum");
  static_assert(!All<Bind<IsEnum, Ph<0>>::Type, A, int>::value, "Failed Bind IsEnum");
  static_assert(!All<Bind<IsEnum, Ph<0>>::Type, int, A>::value, "Failed Bind IsEnum");

  union U1{}; union U2{};
  static_assert(All<Bind<IsUnion, Ph<0>>::Type, U1, U2>::value, "Failed Bind IsUnion");
  static_assert(!All<Bind<IsUnion, Ph<0>>::Type, U1, int>::value, "Failed Bind IsUnion");
  static_assert(!All<Bind<IsUnion, Ph<0>>::Type, int, U2>::value, "Failed Bind IsUnion");

  class C1{}; struct S1{};
  static_assert(All<Bind<IsClass, Ph<0>>::Type, C1, S1>::value, "Failed Bind IsClass");
  static_assert(!All<Bind<IsClass, Ph<0>>::Type, C1, int>::value, "Failed Bind IsClass");
  static_assert(!All<Bind<IsClass, Ph<0>>::Type, int, S1>::value, "Failed Bind IsClass");

  static_assert(All<Bind<IsFunction, Ph<0>>::Type, decltype(func), decltype(func)>::value, "Failed Bind IsFunction");
  static_assert(!All<Bind<IsFunction, Ph<0>>::Type, decltype(func), int>::value, "Failed Bind IsFunction");
  static_assert(!All<Bind<IsFunction, Ph<0>>::Type, int, decltype(func)>::value, "Failed Bind IsFunction");

  static_assert(All<Bind<IsFundamental, Ph<0>>::Type, int, void>::value, "Failed Bind IsFundamental");
  static_assert(!All<Bind<IsFundamental, Ph<0>>::Type, int, int*>::value, "Failed Bind IsFundamental");
  static_assert(!All<Bind<IsFundamental, Ph<0>>::Type, B, int>::value, "Failed Bind IsFundamental");

  static_assert(All<Bind<IsIntegral, Ph<0>>::Type, int, long>::value, "Failed Bind IsIntegral");
  static_assert(!All<Bind<IsIntegral, Ph<0>>::Type, int, float>::value, "Failed Bind IsIntegral");
  static_assert(!All<Bind<IsIntegral, Ph<0>>::Type, int*, int>::value, "Failed Bind IsIntegral");

  static_assert(All<Bind<IsFloating, Ph<0>>::Type, float, double>::value, "Failed Bind IsFloating");
  static_assert(!All<Bind<IsFloating, Ph<0>>::Type, float, int>::value, "Failed Bind IsFloating");
  static_assert(!All<Bind<IsFloating, Ph<0>>::Type, int*, double>::value, "Failed Bind IsFloating");

  static_assert(All<Bind<IsArithmetic, Ph<0>>::Type, float, int>::value, "Failed Bind IsArithmetic");
  static_assert(!All<Bind<IsArithmetic, Ph<0>>::Type, float, int*>::value, "Failed Bind IsArithmetic");
  static_assert(!All<Bind<IsArithmetic, Ph<0>>::Type, void, int>::value, "Failed Bind IsArithmetic");

  static_assert(All<Bind<IsSigned, Ph<0>>::Type, float, int>::value, "Failed Bind IsSigned");
  static_assert(!All<Bind<IsSigned, Ph<0>>::Type, float, unsigned int>::value, "Failed Bind IsSigned");
  static_assert(!All<Bind<IsSigned, Ph<0>>::Type, void*, int>::value, "Failed Bind IsSigned");

  static_assert(All<Bind<IsArray, Ph<0>>::Type, float[], int[10]>::value, "Failed Bind IsArray");
  static_assert(!All<Bind<IsArray, Ph<0>>::Type, float*, int[10]>::value, "Failed Bind IsArray");
  static_assert(!All<Bind<IsArray, Ph<0>>::Type, float, int[]>::value, "Failed Bind IsArray");

  static_assert(All<Bind<IsBoundedArray, Ph<0>>::Type, float[5], int[10]>::value, "Failed Bind IsBoundedArray");
  static_assert(!All<Bind<IsBoundedArray, Ph<0>>::Type, float[], int[10]>::value, "Failed Bind IsBoundedArray");
  static_assert(!All<Bind<IsBoundedArray, Ph<0>>::Type, float[5], int>::value, "Failed Bind IsBoundedArray");

  static_assert(All<Bind<IsUnboundedArray, Ph<0>>::Type, float[], int[]>::value, "Failed Bind IsUnboundedArray");
  static_assert(!All<Bind<IsUnboundedArray, Ph<0>>::Type, float[], int[10]>::value, "Failed Bind IsUnboundedArray");
  static_assert(!All<Bind<IsUnboundedArray, Ph<0>>::Type, float*, int[]>::value, "Failed Bind IsUnboundedArray");

  static_assert(All<Bind<IsPointer, Ph<0>>::Type, float*, int*>::value, "Failed Bind IsPointer");
  static_assert(!All<Bind<IsPointer, Ph<0>>::Type, float[], int*>::value, "Failed Bind IsPointer");
  static_assert(!All<Bind<IsPointer, Ph<0>>::Type, float*, int[]>::value, "Failed Bind IsPointer");

  static_assert(All<Bind<IsLValRef, Ph<0>>::Type, float&, int&>::value, "Failed Bind IsLValRef");
  static_assert(!All<Bind<IsLValRef, Ph<0>>::Type, float[], int&>::value, "Failed Bind IsLValRef");
  static_assert(!All<Bind<IsLValRef, Ph<0>>::Type, float&, int[]>::value, "Failed Bind IsLValRef");

  static_assert(All<Bind<IsRValRef, Ph<0>>::Type, float&&, int&&>::value, "Failed Bind IsRValRef");
  static_assert(!All<Bind<IsRValRef, Ph<0>>::Type, float&, int&&>::value, "Failed Bind IsRValRef");
  static_assert(!All<Bind<IsRValRef, Ph<0>>::Type, float&&, int&>::value, "Failed Bind IsRValRef");

  static_assert(All<Bind<IsRef, Ph<0>>::Type, float&&, int&>::value, "Failed Bind IsRef");
  static_assert(!All<Bind<IsRef, Ph<0>>::Type, float&, int>::value, "Failed Bind IsRef");
  static_assert(!All<Bind<IsRef, Ph<0>>::Type, float, int&&>::value, "Failed Bind IsRef");

  static_assert(All<Bind<IsConst, Ph<0>>::Type, float const, int const>::value, "Failed Bind IsConst");
  static_assert(!All<Bind<IsConst, Ph<0>>::Type, float, int const>::value, "Failed Bind IsConst");
  static_assert(!All<Bind<IsConst, Ph<0>>::Type, float const, int>::value, "Failed Bind IsConst");

  static_assert(All<Bind<IsVolatile, Ph<0>>::Type, float volatile, int volatile>::value, "Failed Bind IsVolatile");
  static_assert(!All<Bind<IsVolatile, Ph<0>>::Type, float, int volatile>::value, "Failed Bind IsVolatile");
  static_assert(!All<Bind<IsVolatile, Ph<0>>::Type, float volatile, int>::value, "Failed Bind IsVolatile");

  static_assert(All<Bind<IsConstVolatile, Ph<0>>::Type, float const volatile, int const volatile>::value, "Failed Bind IsConstVolatile");
  static_assert(!All<Bind<IsConstVolatile, Ph<0>>::Type, float const, int const volatile>::value, "Failed Bind IsConstVolatile");
  static_assert(!All<Bind<IsConstVolatile, Ph<0>>::Type, float const volatile, int const>::value, "Failed Bind IsConstVolatile");
}

TEST(MetaObjectTraits, TypeInfoPrimitives) {
  ASSERT_EQ("void", std::string(TypeInfo<void>::name));
  ASSERT_EQ("bool", std::string(TypeInfo<bool>::name));
  ASSERT_EQ(IsSigned<short>::value ? "signed short" : "unsigned short", std::string(TypeInfo<short>::name));
  ASSERT_EQ(IsSigned<int>::value ? "signed int" : "unsigned int", std::string(TypeInfo<int>::name));
  ASSERT_EQ(IsSigned<long>::value ? "signed long" : "unsigned long", std::string(TypeInfo<long>::name));
  ASSERT_EQ("unsigned char", std::string(TypeInfo<unsigned char>::name));
  ASSERT_EQ("unsigned short", std::string(TypeInfo<unsigned short>::name));
  ASSERT_EQ("unsigned int", std::string(TypeInfo<unsigned int>::name));
  ASSERT_EQ("unsigned long", std::string(TypeInfo<unsigned long>::name));
  ASSERT_EQ("signed char", std::string(TypeInfo<signed char>::name));
  ASSERT_EQ("signed short", std::string(TypeInfo<signed short>::name));
  ASSERT_EQ("signed int", std::string(TypeInfo<signed int>::name));
  ASSERT_EQ("signed long", std::string(TypeInfo<signed long>::name));
  ASSERT_EQ("float", std::string(TypeInfo<float>::name));
  ASSERT_EQ("double", std::string(TypeInfo<double>::name));
}

struct Unspecialized{};
template <typename> struct TUnspecialized{};
struct Specialized{};
template <typename> struct TSpecialized{};

namespace cds {
namespace meta {
template <> struct TypeInfo<Specialized> {
  constexpr static char const* name = "Specialized";
};

template <> struct TemplateTypeInfo<TSpecialized> {
  constexpr static char const* name = "TSpecialized";
};
} // namespace meta
} // namespace cds

TEST(MetaObjectTraits, TypeInfoObjects) {
  ASSERT_EQ("unknown", std::string(TypeInfo<Unspecialized>::name));
  ASSERT_EQ("unknown", std::string(TemplateTypeInfo<TUnspecialized>::name));
  ASSERT_EQ("Specialized", std::string(TypeInfo<Specialized>::name));
  ASSERT_EQ("TSpecialized", std::string(TemplateTypeInfo<TSpecialized>::name));
}

TEST(MetaObjectTest, Decay) {
  static_assert(IsSame<Decay<int>, int>::value, "Failed Decay");
  static_assert(IsSame<Decay<int&>, int>::value, "Failed Decay");
  static_assert(IsSame<Decay<int&&>, int>::value, "Failed Decay");
  static_assert(IsSame<Decay<int const>, int>::value, "Failed Decay");
  static_assert(IsSame<Decay<int const&>, int>::value, "Failed Decay");
  static_assert(IsSame<Decay<int const&&>, int>::value, "Failed Decay");
  static_assert(IsSame<Decay<int volatile>, int>::value, "Failed Decay");
  static_assert(IsSame<Decay<int volatile&>, int>::value, "Failed Decay");
  static_assert(IsSame<Decay<int volatile&&>, int>::value, "Failed Decay");
  static_assert(IsSame<Decay<int const volatile>, int>::value, "Failed Decay");
  static_assert(IsSame<Decay<int const volatile&>, int>::value, "Failed Decay");
  static_assert(IsSame<Decay<int const volatile&&>, int>::value, "Failed Decay");
  static_assert(IsSame<Decay<int*>, int*>::value, "Failed Decay");
  static_assert(IsSame<Decay<int const*>, int const*>::value, "Failed Decay");
  static_assert(IsSame<Decay<int volatile*>, int volatile*>::value, "Failed Decay");
  static_assert(IsSame<Decay<int const volatile*>, int const volatile*>::value, "Failed Decay");
  static_assert(IsSame<Decay<int[]>, int*>::value, "Failed Decay");
  static_assert(IsSame<Decay<int const[]>, int const*>::value, "Failed Decay");
  static_assert(IsSame<Decay<int volatile[]>, int volatile*>::value, "Failed Decay");
  static_assert(IsSame<Decay<int const volatile[]>, int const volatile*>::value, "Failed Decay");
  static_assert(IsSame<Decay<int[1]>, int*>::value, "Failed Decay");
  static_assert(IsSame<Decay<int const[1]>, int const*>::value, "Failed Decay");
  static_assert(IsSame<Decay<int volatile[1]>, int volatile*>::value, "Failed Decay");
  static_assert(IsSame<Decay<int const volatile[1]>, int const volatile*>::value, "Failed Decay");
  static_assert(IsSame<Decay<int(&)[1]>, int*>::value, "Failed Decay");
  static_assert(IsSame<Decay<int(&&)[1]>, int*>::value, "Failed Decay");
  static_assert(IsSame<Decay<int(bool)>, int(*)(bool)>::value, "Failed Decay");
}

TEST(MetaObjectTest, Common) {
  class A {public: A(int);};
  class B {public: B(int); B(A);};
  static_assert(IsSame<Common<int>, int>::value, "Failed Common");
  static_assert(IsSame<Common<int, int>, int>::value, "Failed Common");
  static_assert(IsSame<Common<int, int, int>, int>::value, "Failed Common");
  static_assert(IsSame<Common<int, long, int>, long>::value, "Failed Common");
  static_assert(IsSame<Common<int, float, int>, float>::value, "Failed Common");
  static_assert(IsSame<Common<int, float, long>, float>::value, "Failed Common");
  static_assert(IsSame<Common<int, int&>, int>::value, "Failed Common");
  static_assert(IsSame<Common<int, int&&>, int>::value, "Failed Common");
  static_assert(IsSame<Common<int&, int&&>, int>::value, "Failed Common");
  static_assert(IsSame<Common<int&&, int&>, int>::value, "Failed Common");
  static_assert(IsSame<Common<A>, A>::value, "Failed Common");
  static_assert(IsSame<Common<int, A, int>, A>::value, "Failed Common");
  static_assert(IsSame<Common<int, A, B, int>, B>::value, "Failed Common");
}

int& f() {
  static int x = 3;
  return x;
}

TEST(MetaBase, Apply) {
  static_assert(Eq<True, All<Unless<Apply<IsConst, RemoveRef>::Type>::Type, int, int&>>::value, "Failed Bind of Apply");
  static_assert(!Eq<True, All<Unless<Apply<IsConst, RemoveRef>::Type>::Type, int, int const&>>::value, "Failed Bind of Apply");
  static_assert(!Eq<True, All<Unless<Apply<IsConst, RemoveRef>::Type>::Type, int const&, int>>::value, "Failed Bind of Apply");

  static_assert(Eq<True, All<Bind<Unless<Apply<IsConst, RemoveRef>::Type>::Type, Ph<0>>::Type, int, float>>::value, "Failed Bind of Apply");
  static_assert(Eq<True, All<Bind<Unless<Apply<IsConst, RemoveRef>::Type>::Type, Ph<0>>::Type, int, int&>>::value, "Failed Bind of Apply");
  static_assert(!Eq<True, All<Bind<Unless<Apply<IsConst, RemoveRef>::Type>::Type, Ph<0>>::Type, int, int const&>>::value, "Failed Bind of Apply");
}
