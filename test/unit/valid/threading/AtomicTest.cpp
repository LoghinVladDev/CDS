//
// Created by vloghin on 19.12.2024.
//

#include "UnitTest.hpp"
#include <cds/collection/Vector>
#include <cds/threading/Atomic>
#include <thread>

namespace {
using cds::Atomic;
using cds::AtomicFlag;
using cds::AtomicMemoryOrder;
using cds::Vector;
} // namespace

TEST(AtomicTest, atomicFlag) {
  AtomicFlag inSec;
  auto constexpr threshold = 100;
  unsigned uniqueAccess = 0;

  auto thFn = [&inSec, &uniqueAccess]() {
    if (!inSec.testAndSet()) {
      ++uniqueAccess;
    }
  };

  for (unsigned idx = 0; idx < threshold; ++idx) {
    uniqueAccess = 0u;
    Vector<std::thread> threads;
    threads.emplaceBack(thFn);
    threads.emplaceBack(thFn);
    threads.emplaceBack(thFn);
    threads.emplaceBack(thFn);

    threads.forEach(&std::thread::join);
    inSec.clear();
    ASSERT_EQ(1, uniqueAccess);
  }
}

TEST(AtomicTest, volatileAtomicFlag) {
  AtomicFlag volatile inSec;
  auto constexpr threshold = 100;
  unsigned uniqueAccess = 0;

  auto thFn = [&inSec, &uniqueAccess]() {
    if (!inSec.testAndSet()) {
      ++uniqueAccess;
    }
  };

  for (unsigned idx = 0; idx < threshold; ++idx) {
    uniqueAccess = 0u;
    Vector<std::thread> threads;
    threads.emplaceBack(thFn);
    threads.emplaceBack(thFn);
    threads.emplaceBack(thFn);
    threads.emplaceBack(thFn);

    threads.forEach(&std::thread::join);
    inSec.clear();
    ASSERT_EQ(1, uniqueAccess);
  }
}

TEST(AtomicTest, incrementRelaxed) {
  Atomic<int> inc{0};
  unsigned constexpr spin = 1000;

  auto thFn = [&inc, spin]() {
    for (auto idx = 0u; idx < spin; ++idx) {
      inc.fetchAdd(1, AtomicMemoryOrder::Relaxed);
    }
  };

  Vector<std::thread> threads;
  threads.emplaceBack(thFn);
  threads.emplaceBack(thFn);
  threads.emplaceBack(thFn);
  threads.emplaceBack(thFn);
  threads.forEach(&std::thread::join);
  ASSERT_EQ(4 * spin, inc.load());
}

TEST(AtomicTest, volatileIncrementRelaxed) {
  Atomic<int> volatile inc{0};
  unsigned constexpr spin = 1000;

  auto thFn = [&inc, spin]() {
    for (auto idx = 0u; idx < spin; ++idx) {
      inc.fetchAdd(1, AtomicMemoryOrder::Relaxed);
    }
  };

  Vector<std::thread> threads;
  threads.emplaceBack(thFn);
  threads.emplaceBack(thFn);
  threads.emplaceBack(thFn);
  threads.emplaceBack(thFn);
  threads.forEach(&std::thread::join);
  ASSERT_EQ(4 * spin, inc.load());
}

TEST(AtomicTest, ptrIncrement) {
  int array[500];
  Atomic<int*> inc{&array[50]};
  unsigned constexpr spin = 100;
  memset(&array, 0, 500 * sizeof(int));

  auto thFn = [&inc, spin](int thIdx) {
    for (auto idx = 0u; idx < spin; ++idx) {
      *inc.fetchAdd(1) = thIdx;
    }
  };

  auto makeThFn = [&thFn](int thIdx) {
    return [&thFn, thIdx]() {
      return thFn(thIdx);
    };
  };

  Vector<std::thread> threads;
  threads.emplaceBack(makeThFn(1));
  threads.emplaceBack(makeThFn(2));
  threads.emplaceBack(makeThFn(3));
  threads.emplaceBack(makeThFn(4));
  threads.forEach(&std::thread::join);
  ASSERT_EQ(&array[450], inc.load());
  for (unsigned idx = 0; idx < 50; ++idx) {
    ASSERT_EQ(0, array[idx]);
  }
  for (unsigned idx = 50; idx < 450; ++idx) {
    ASSERT_NE(0, array[idx]);
  }
  for (unsigned idx = 450; idx < 500; ++idx) {
    ASSERT_EQ(0, array[idx]);
  }
}
