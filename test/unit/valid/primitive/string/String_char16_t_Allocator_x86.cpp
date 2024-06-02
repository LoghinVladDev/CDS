// DCR-TEST
// STEPS: compile(linux:gcc;linux:clang),run(linux:gcc;linux:clang)
// STD: 11+
// FLAGS[compile(linux:*)]: -m32

#define CHAR_TYPE char16_t
#define SBO_CAPACITY 4
#define ALLOCATOR_TYPE Allocator
#define LITERAL(text) u ## text
#define LITERAL_OP(text) u ## text ## _s
#include "String.hpp"
