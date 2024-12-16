// DCR-TEST
// STEPS: compile(linux:gcc;linux:clang;apple:clang;apple:gcc),run(linux:gcc;linux:clang;apple:clang;apple:gcc)
// STD: 11+
// FLAGS[compile(linux:*)]: -m32

#define CHAR_TYPE char32_t
#define LITERAL(text) U ## text
#define LITERAL_OP(text) U ## text ## _sv
#include "StringView.hpp"
