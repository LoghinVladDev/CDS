// DCR-TEST
// STEPS: compile(linux:gcc;linux:clang;apple:clang;apple:gcc),run(linux:gcc;linux:clang;apple:clang;apple:gcc)
// STD: 11+
// FLAGS[compile(linux:*)]: -DCDS_ATTR_emulated_in_constexpr=true

#ifdef _WIN32
#define SBO_CAPACITY 10
#else
#define SBO_CAPACITY 4
#endif

#define CHAR_TYPE wchar_t
#define ALLOCATOR_TYPE Allocator
#define LITERAL(text) L ## text
#define LITERAL_OP(text) L ## text ## _s
#define CDS_ATTR_emulated_in_constexpr true
#include "String.hpp"
