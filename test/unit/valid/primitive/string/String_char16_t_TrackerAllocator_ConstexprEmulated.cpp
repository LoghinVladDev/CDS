// DCR-TEST
// STEPS: compile(linux:gcc;linux:clang;apple:clang;apple:gcc),run(linux:gcc;linux:clang;apple:clang;apple:gcc)
// STD: 11+
// FLAGS[compile(linux:*)]: -DCDS_ATTR_emulated_in_constexpr=true

#define CHAR_TYPE char16_t
#define SBO_CAPACITY 10
#define ALLOCATOR_TYPE TrackerAllocator
#define LITERAL(text) u ## text
#define LITERAL_OP(text) u ## text ## _s
#define CDS_ATTR_emulated_in_constexpr true
#include "String.hpp"
