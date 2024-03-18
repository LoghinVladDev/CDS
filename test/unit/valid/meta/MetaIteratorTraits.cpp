// DCR-TEST
// STEPS: compile(linux:gcc;linux:clang),run(linux:clang)
// STD: 11+

#include "cds/meta/IteratorTraits"
#include "UnitTest.hpp"

using namespace cds::meta;

TEST(MetaIteratorTraits, IsSentinelFor) {
  struct A{};
  struct B{};
  struct C{bool operator==(A const&) const;};

  static_assert(IsSentinelFor<int*, int*>::value, "Failed IsSentinelFor");
  static_assert(!IsSentinelFor<int*, int>::value, "Failed IsSentinelFor");
  static_assert(!IsSentinelFor<A, A>::value, "Failed IsSentinelFor");
  static_assert(!IsSentinelFor<A, B>::value, "Failed IsSentinelFor");
  static_assert((cds::compiler::CurrentStd::version >= 20 ? true : false) == IsSentinelFor<A, C>::value, "Failed IsSentinelFor");
  static_assert(IsSentinelFor<C, A>::value, "Failed IsSentinelFor");
}

TEST(MetaIteratorTraits, IsInputIterator) {
  struct A{A& operator++(); bool operator==(A const&) const; int const& operator*() const;};
  struct A_DerefNc{A_DerefNc& operator++(); bool operator==(A_DerefNc const&) const; int& operator*() const;};
  struct A_MissingInc{bool operator==(A_MissingInc const&) const; int const& operator*() const;};
  struct A_MissingComp{A_MissingComp& operator++(); int const& operator*() const;};
  struct A_MissingInd{A_MissingInd& operator++(); bool operator==(A_MissingInd const&) const;};
  struct A_InvalidInc{A_InvalidInc operator++(); bool operator==(A_InvalidInc const&) const; int const& operator*() const;};
  struct A_InvalidComp{A_InvalidComp& operator++(); bool operator==(int) const; int const& operator*() const;};

  static_assert(!IsInputIterator<int>::value, "Failed IsInputIterator");
  static_assert(IsInputIterator<int*>::value, "Failed IsInputIterator");
  static_assert(IsInputIterator<A>::value, "Failed IsInputIterator");
  static_assert(IsInputIterator<A_DerefNc>::value, "Failed IsInputIterator");
  static_assert(!IsInputIterator<A_MissingInc>::value, "Failed IsInputIterator");
  static_assert(!IsInputIterator<A_MissingComp>::value, "Failed IsInputIterator");
  static_assert(!IsInputIterator<A_MissingInd>::value, "Failed IsInputIterator");
  static_assert(!IsInputIterator<A_InvalidInc>::value, "Failed IsInputIterator");
  static_assert(!IsInputIterator<A_InvalidComp>::value, "Failed IsInputIterator");
}

TEST(MetaIteratorTraits, IsOutputIterator) {
  struct A{A& operator++(); bool operator==(A const&) const; int const& operator*() const;};
  struct A_DerefNc{A_DerefNc& operator++(); bool operator==(A_DerefNc const&) const; int& operator*() const;};
  struct A_MissingInc{bool operator==(A_MissingInc const&) const; int const& operator*() const;};
  struct A_MissingComp{A_MissingComp& operator++(); int const& operator*() const;};
  struct A_MissingInd{A_MissingInd& operator++(); bool operator==(A_MissingInd const&) const;};
  struct A_InvalidInc{A_InvalidInc operator++(); bool operator==(A_InvalidInc const&) const; int const& operator*() const;};
  struct A_InvalidComp{A_InvalidComp& operator++(); bool operator==(int) const; int const& operator*() const;};

  static_assert(!IsOutputIterator<int>::value, "Failed IsOutputIterator");
  static_assert(IsOutputIterator<int*>::value, "Failed IsOutputIterator");
  static_assert(!IsOutputIterator<A>::value, "Failed IsOutputIterator");
  static_assert(IsOutputIterator<A_DerefNc>::value, "Failed IsOutputIterator");
  static_assert(!IsOutputIterator<A_MissingInc>::value, "Failed IsOutputIterator");
  static_assert(!IsOutputIterator<A_MissingComp>::value, "Failed IsOutputIterator");
  static_assert(!IsOutputIterator<A_MissingInd>::value, "Failed IsOutputIterator");
  static_assert(!IsOutputIterator<A_InvalidInc>::value, "Failed IsOutputIterator");
  static_assert(!IsOutputIterator<A_InvalidComp>::value, "Failed IsOutputIterator");
}

TEST(MetaIteratorTraits, IsForwardIterator) {
  struct A{A& operator++(); bool operator==(A const&) const; int const& operator*() const;};
  struct A_DerefNc{A_DerefNc& operator++(); bool operator==(A_DerefNc const&) const; int& operator*() const;};
  struct A_MissingInc{bool operator==(A_MissingInc const&) const; int const& operator*() const;};
  struct A_MissingComp{A_MissingComp& operator++(); int const& operator*() const;};
  struct A_MissingInd{A_MissingInd& operator++(); bool operator==(A_MissingInd const&) const;};
  struct A_InvalidInc{A_InvalidInc operator++(); bool operator==(A_InvalidInc const&) const; int const& operator*() const;};
  struct A_InvalidComp{A_InvalidComp& operator++(); bool operator==(int) const; int const& operator*() const;};

  static_assert(!IsForwardIterator<int>::value, "Failed IsForwardIterator");
  static_assert(IsForwardIterator<int*>::value, "Failed IsForwardIterator");
  static_assert(IsForwardIterator<A>::value, "Failed IsForwardIterator");
  static_assert(IsForwardIterator<A_DerefNc>::value, "Failed IsForwardIterator");
  static_assert(!IsForwardIterator<A_MissingInc>::value, "Failed IsForwardIterator");
  static_assert(!IsForwardIterator<A_MissingComp>::value, "Failed IsForwardIterator");
  static_assert(!IsForwardIterator<A_MissingInd>::value, "Failed IsForwardIterator");
  static_assert(IsForwardIterator<A_InvalidInc>::value, "Failed IsForwardIterator");
  static_assert(!IsForwardIterator<A_InvalidComp>::value, "Failed IsForwardIterator");
}

TEST(MetaIteratorTraits, IsBidirectionalIterator) {
  struct A{A& operator++(); A& operator--(); bool operator==(A const&) const; int const& operator*() const;};
  struct A_NoDec{A& operator++(); bool operator==(A const&) const; int const& operator*() const;};

  static_assert(!IsBidirectionalIterator<int>::value, "Failed IsBidirectionalIterator");
  static_assert(IsBidirectionalIterator<int*>::value, "Failed IsBidirectionalIterator");
  static_assert(IsBidirectionalIterator<A>::value, "Failed IsBidirectionalIterator");
  static_assert(!IsBidirectionalIterator<A_NoDec>::value, "Failed IsBidirectionalIterator");
}

TEST(MetaIteratorTraits, IsRandomAccessIterator) {
  struct A{
    A& operator++();
    A& operator--();
    bool operator==(A const&) const;
    int const& operator*() const;
    int const& operator[](int i) const;
    A operator+(int b) const;
    A operator-(int b) const;
    int operator-(A const& b) const;
  };

  struct A_InvSumInt{
    A& operator++();
    A& operator--();
    bool operator==(A const&) const;
    int const& operator*() const;
    int const& operator[](int i) const;
    A operator+(void* b) const;
    A operator-(int b) const;
    int operator-(A const& b) const;
  };

  struct A_MisSumInt{
    A& operator++();
    A& operator--();
    bool operator==(A const&) const;
    int const& operator*() const;
    int const& operator[](int i) const;
    A operator-(int b) const;
    int operator-(A const& b) const;
  };

  struct A_InvSubInt{
    A& operator++();
    A& operator--();
    bool operator==(A const&) const;
    int const& operator*() const;
    int const& operator[](int i) const;
    A operator+(int b) const;
    A operator-(int* b) const;
    int operator-(A const& b) const;
  };

  struct A_MisSubInt{
    A& operator++();
    A& operator--();
    bool operator==(A const&) const;
    int const& operator*() const;
    int const& operator[](int i) const;
    A operator+(int b) const;
    int operator-(A const& b) const;
  };

  struct A_InvSubIt{
    A& operator++();
    A& operator--();
    bool operator==(A const&) const;
    int const& operator*() const;
    int const& operator[](int i) const;
    A operator+(int b) const;
    A operator-(int b) const;
    int operator-(double b) const;
  };

  struct A_MisSubIt{
    A& operator++();
    A& operator--();
    bool operator==(A const&) const;
    int const& operator*() const;
    int const& operator[](int i) const;
    A operator+(int b) const;
    A operator-(int b) const;
  };

  struct A_InvAccess{
    A& operator++();
    A& operator--();
    bool operator==(A const&) const;
    int const& operator*() const;
    int const& operator[](A const& i) const;
    A operator+(int b) const;
    A operator-(int b) const;
    int operator-(A const& b) const;
  };

  struct A_MisAccess{
    A& operator++();
    A& operator--();
    bool operator==(A const&) const;
    int const& operator*() const;
    A operator+(int b) const;
    A operator-(int b) const;
    int operator-(A const& b) const;
  };

  static_assert(!IsRandomAccessIterator<int>::value, "Failed IsRandomAccessIterator");
  static_assert(IsRandomAccessIterator<int*>::value, "Failed IsRandomAccessIterator");
  static_assert(IsRandomAccessIterator<A>::value, "Failed IsRandomAccessIterator");
  static_assert(!IsRandomAccessIterator<A_InvSumInt>::value, "Failed IsRandomAccessIterator");
  static_assert(!IsRandomAccessIterator<A_MisSumInt>::value, "Failed IsRandomAccessIterator");
  static_assert(!IsRandomAccessIterator<A_InvSubInt>::value, "Failed IsRandomAccessIterator");
  static_assert(!IsRandomAccessIterator<A_MisSubInt>::value, "Failed IsRandomAccessIterator");
  static_assert(!IsRandomAccessIterator<A_InvSubIt>::value, "Failed IsRandomAccessIterator");
  static_assert(!IsRandomAccessIterator<A_MisSubIt>::value, "Failed IsRandomAccessIterator");
  static_assert(!IsRandomAccessIterator<A_InvAccess>::value, "Failed IsRandomAccessIterator");
  static_assert(!IsRandomAccessIterator<A_MisAccess>::value, "Failed IsRandomAccessIterator");
}

TEST(MetaIteratorTraits, HasIterableMemberFns) {
  struct None {};
  struct It { int* begin(); int* end(); };
  struct CIt { CDS_ATTR(nodiscard) int const* cbegin() const; CDS_ATTR(nodiscard) int const* cend() const; };
  struct RIt { int* rbegin(); int* rend(); };
  struct CRIt { CDS_ATTR(nodiscard) int const* crbegin() const; CDS_ATTR(nodiscard) int const* crend() const; };
  struct All : It, CIt, RIt, CRIt {};
  struct ItExtra : It { CDS_ATTR(nodiscard) int const* begin() const; CDS_ATTR(nodiscard) int const* end() const; };
  struct RItExtra : RIt { CDS_ATTR(nodiscard) int const* rbegin() const; CDS_ATTR(nodiscard) int const* rend() const; };
  struct AllExtra : ItExtra, CIt, RItExtra, CRIt {};

  static_assert(!impl::HasIterableMemberFns<None>::value, "Failed HasIterableMemberFns");
  static_assert(!impl::HasConstIterableMemberFns<None>::value, "Failed HasIterableMemberFns");
  static_assert(!impl::HasReverseIterableMemberFns<None>::value, "Failed HasIterableMemberFns");
  static_assert(!impl::HasConstReverseIterableMemberFns<None>::value, "Failed HasIterableMemberFns");

  static_assert(impl::HasIterableMemberFns<It>::value, "Failed HasIterableMemberFns");
  static_assert(!impl::HasConstIterableMemberFns<It>::value, "Failed HasIterableMemberFns");
  static_assert(!impl::HasReverseIterableMemberFns<It>::value, "Failed HasIterableMemberFns");
  static_assert(!impl::HasConstReverseIterableMemberFns<It>::value, "Failed HasIterableMemberFns");

  static_assert(!impl::HasIterableMemberFns<CIt>::value, "Failed HasIterableMemberFns");
  static_assert(impl::HasConstIterableMemberFns<CIt>::value, "Failed HasIterableMemberFns");
  static_assert(!impl::HasReverseIterableMemberFns<CIt>::value, "Failed HasIterableMemberFns");
  static_assert(!impl::HasConstReverseIterableMemberFns<CIt>::value, "Failed HasIterableMemberFns");

  static_assert(!impl::HasIterableMemberFns<RIt>::value, "Failed HasIterableMemberFns");
  static_assert(!impl::HasConstIterableMemberFns<RIt>::value, "Failed HasIterableMemberFns");
  static_assert(impl::HasReverseIterableMemberFns<RIt>::value, "Failed HasIterableMemberFns");
  static_assert(!impl::HasConstReverseIterableMemberFns<RIt>::value, "Failed HasIterableMemberFns");

  static_assert(!impl::HasIterableMemberFns<CRIt>::value, "Failed HasIterableMemberFns");
  static_assert(!impl::HasConstIterableMemberFns<CRIt>::value, "Failed HasIterableMemberFns");
  static_assert(!impl::HasReverseIterableMemberFns<CRIt>::value, "Failed HasIterableMemberFns");
  static_assert(impl::HasConstReverseIterableMemberFns<CRIt>::value, "Failed HasIterableMemberFns");

  static_assert(impl::HasIterableMemberFns<All>::value, "Failed HasIterableMemberFns");
  static_assert(impl::HasConstIterableMemberFns<All>::value, "Failed HasIterableMemberFns");
  static_assert(impl::HasReverseIterableMemberFns<All>::value, "Failed HasIterableMemberFns");
  static_assert(impl::HasConstReverseIterableMemberFns<All>::value, "Failed HasIterableMemberFns");

  static_assert(impl::HasIterableMemberFns<ItExtra>::value, "Failed HasIterableMemberFns");
  static_assert(!impl::HasConstIterableMemberFns<ItExtra>::value, "Failed HasIterableMemberFns");
  static_assert(!impl::HasReverseIterableMemberFns<ItExtra>::value, "Failed HasIterableMemberFns");
  static_assert(!impl::HasConstReverseIterableMemberFns<ItExtra>::value, "Failed HasIterableMemberFns");

  static_assert(!impl::HasIterableMemberFns<RItExtra>::value, "Failed HasIterableMemberFns");
  static_assert(!impl::HasConstIterableMemberFns<RItExtra>::value, "Failed HasIterableMemberFns");
  static_assert(impl::HasReverseIterableMemberFns<RItExtra>::value, "Failed HasIterableMemberFns");
  static_assert(!impl::HasConstReverseIterableMemberFns<RItExtra>::value, "Failed HasIterableMemberFns");

  static_assert(impl::HasIterableMemberFns<AllExtra>::value, "Failed HasIterableMemberFns");
  static_assert(impl::HasConstIterableMemberFns<AllExtra>::value, "Failed HasIterableMemberFns");
  static_assert(impl::HasReverseIterableMemberFns<AllExtra>::value, "Failed HasIterableMemberFns");
  static_assert(impl::HasConstReverseIterableMemberFns<AllExtra>::value, "Failed HasIterableMemberFns");
}
