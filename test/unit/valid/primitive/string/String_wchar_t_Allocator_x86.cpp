// DCR-TEST
// STEPS: compile(linux:gcc;linux:clang),run(linux:gcc;linux:clang)
// STD: 11+
// FLAGS[compile(linux:*)]: -m32

#define CHAR_TYPE wchar_t
#define SBO_CAPACITY 0
#define ALLOCATOR_TYPE Allocator
#define LITERAL(text) L ## text
#define LITERAL_OP(text) L ## text ## _s
#include "String.hpp"
