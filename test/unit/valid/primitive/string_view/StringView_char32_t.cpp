// DCR-TEST
// STEPS: compile(linux:gcc;linux:clang),run(linux:gcc;linux:clang)
// STD: 11+

#define CHAR_TYPE char32_t
#define LITERAL(text) U ## text
#define LITERAL_OP(text) U ## text ## _sv
#include "StringView.hpp"
