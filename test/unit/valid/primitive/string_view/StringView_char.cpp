// DCR-TEST
// STEPS: compile(linux:gcc;linux:clang;apple:clang;apple:gcc),run(linux:gcc;linux:clang;apple:clang;apple:gcc)
// STD: 11+

#define CHAR_TYPE char
#define LITERAL(text) text
#define LITERAL_OP(text) text ## _sv
#include "StringView.hpp"
