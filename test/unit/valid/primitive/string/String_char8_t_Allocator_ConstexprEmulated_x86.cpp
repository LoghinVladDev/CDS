// DCR-TEST
// STEPS: compile(linux:gcc;linux:clang),run(linux:gcc;linux:clang)
// STD: 20+
// FLAGS[compile(linux:*)]: -m32 -DCDS_ATTR_emulated_in_constexpr=true

#if DCR_SINCECPP20
#define CHAR_TYPE char8_t
#define SBO_CAPACITY 10
#define ALLOCATOR_TYPE Allocator
#define LITERAL(text) u8 ## text
#define LITERAL_OP(text) u8 ## text ## _s
#define CDS_ATTR_emulated_in_constexpr true
#include "String.hpp"
#endif
