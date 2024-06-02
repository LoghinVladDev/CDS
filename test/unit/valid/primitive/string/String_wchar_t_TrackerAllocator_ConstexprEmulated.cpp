// DCR-TEST
// STEPS: compile(linux:gcc;linux:clang),run(linux:gcc;linux:clang)
// STD: 11+
// FLAGS[compile(linux:*)]: -DCDS_ATTR_emulated_in_constexpr=true

#define CHAR_TYPE wchar_t
#define SBO_CAPACITY 4
#define ALLOCATOR_TYPE TrackerAllocator
#define LITERAL(text) L ## text
#define LITERAL_OP(text) L ## text ## _s
#define CDS_ATTR_emulated_in_constexpr true
#include "String.hpp"
