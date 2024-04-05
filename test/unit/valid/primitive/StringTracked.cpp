// DCR-TEST
// STEPS: compile(linux:gcc;linux:clang),run(linux:gcc;linux:clang)
// STD: 11+

#include <cds/String>
#include <cds/StringView>
#include <cassert>
#include <iostream>
#include <array>

#include "UnitTest.hpp"
#include "../Shared.hpp"
#include "../TrackerAllocator.hpp"

namespace {
using String = cds::impl::BaseString<
    char,
    cds::impl::StringUtils<char, cds::meta::StringTraits<char>>,
    testing::TrackerAllocator<char>
>;
using cds::StringView;
}

#define STRING_TEST_ID StringTracked
#include "StringTest.hpp"
