// DCR-TEST
// STEPS: compile(linux:gcc;linux:clang;apple:clang;apple:gcc),run(linux:gcc;linux:clang;apple:clang;apple:gcc)
// STD: 11+
// FLAGS[compile(linux:*)]: -m32

#ifdef _WIN32
#define SBO_CAPACITY 4
#else
#define SBO_CAPACITY 0
#endif

#define CHAR_TYPE wchar_t
#define ALLOCATOR_TYPE TrackerAllocator
#define LITERAL(text) L ## text
#define LITERAL_OP(text) L ## text ## _s
#include "String.hpp"
