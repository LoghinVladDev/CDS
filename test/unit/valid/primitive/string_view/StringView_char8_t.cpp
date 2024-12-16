// DCR-TEST
// STEPS: compile(linux:gcc;linux:clang;apple:clang;apple:gcc),run(linux:gcc;linux:clang;apple:clang;apple:gcc)
// STD: 20+

#ifdef DCR_SINCECPP20
#define CHAR_TYPE char8_t
#define LITERAL(text) u8 ## text
#define LITERAL_OP(text) u8 ## text ## _sv
#include "StringView.hpp"
#endif
