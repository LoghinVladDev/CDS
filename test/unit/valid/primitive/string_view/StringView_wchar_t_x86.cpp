// DCR-TEST
// STEPS: compile(linux:gcc;linux:clang),run(linux:gcc;linux:clang)
// STD: 11+
// FLAGS[compile(linux:*)]: -m32

#define CHAR_TYPE wchar_t
#define LITERAL(text) L ## text
#define LITERAL_OP(text) L ## text ## _sv
#include "StringView.hpp"
