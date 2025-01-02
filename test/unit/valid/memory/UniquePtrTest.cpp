//
// Created by vloghin on 24.12.2024.
//

#include "UnitTest.hpp"
#include <cds/memory/UniquePtr>

namespace {
using cds::UniquePtr;

using cds::makeUnique;
using cds::makeUniqueUninitialized;
using cds::makeUniqueForOverwrite;
} // namespace

TEST(UniquePtrTest, InitDefaultCtorDefaultDeleter) {
  auto ptr = UniquePtr<int>{};
  ASSERT_EQ(nullptr, ptr.get());
  ASSERT_FALSE(ptr);
}
