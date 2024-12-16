// DCR-TEST
// STEPS: compile(linux:gcc;linux:clang;apple:clang;apple:gcc),run(linux:gcc;linux:clang;apple:clang;apple:gcc)
// STD: 11+

#define CHAR_TYPE char16_t
#define LITERAL(text) u ## text
#define LITERAL_OP(text) u ## text ## _sv
#include "StringView.hpp"
