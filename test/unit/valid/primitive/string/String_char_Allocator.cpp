// DCR-TEST
// STEPS: compile(linux:gcc;linux:clang;apple:clang;apple:gcc),run(linux:gcc;linux:clang;apple:clang;apple:gcc)
// STD: 11+

#define CHAR_TYPE char
#define SBO_CAPACITY 22
#define ALLOCATOR_TYPE Allocator
#define LITERAL(text) text
#define LITERAL_OP(text) text ## _s
#include "String.hpp"
