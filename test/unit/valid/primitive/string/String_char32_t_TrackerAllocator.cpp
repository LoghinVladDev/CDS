// DCR-TEST
// STEPS: compile(linux:gcc;linux:clang),run(linux:gcc;linux:clang)
// STD: 11+

#define CHAR_TYPE char32_t
#define SBO_CAPACITY 4
#define ALLOCATOR_TYPE TrackerAllocator
#define LITERAL(text) U ## text
#define LITERAL_OP(text) U ## text ## _s
#include "String.hpp"
