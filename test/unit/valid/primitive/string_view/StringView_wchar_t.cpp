// DCR-TEST
// STEPS: compile(linux:gcc;linux:clang;apple:clang;apple:gcc),run(linux:gcc;linux:clang;apple:clang;apple:gcc)
// STD: 11+

#define CHAR_TYPE wchar_t
#define LITERAL(text) L ## text
#define LITERAL_OP(text) L ## text ## _sv
#include "StringView.hpp"
