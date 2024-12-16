// DCR-TEST
// STEPS: compile(linux:gcc;linux:clang;apple:clang;apple:gcc),run(linux:gcc;linux:clang;apple:clang;apple:gcc)
// STD: 11+
// FLAGS[compile(linux:*)]: -m32 -DCDS_ATTR_emulated_in_constexpr=true

#define CHAR_TYPE char32_t
#define SBO_CAPACITY 0
#define ALLOCATOR_TYPE TrackerAllocator
#define LITERAL(text) U ## text
#define LITERAL_OP(text) U ## text ## _s
#define CDS_ATTR_emulated_in_constexpr true
#include "String.hpp"
