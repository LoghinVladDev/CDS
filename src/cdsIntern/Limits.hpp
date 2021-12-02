//
// Created by loghin on 25/09/2021.
//

#ifndef CDS_LIMITS_HPP
#define CDS_LIMITS_HPP

#include <CDS/Types>

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace limits {
        __CDS_MaybeUnused constexpr uint8 U8_MAX      = 0xFFU;
        __CDS_MaybeUnused constexpr uint16 U16_MAX    = 0xFFFFU;
        __CDS_MaybeUnused constexpr uint32 U32_MAX    = 0xFFFFFFFFU;
        __CDS_MaybeUnused constexpr uint64 U64_MAX    = 0xFFFFFFFFFFFFFFFFLLU;

        __CDS_MaybeUnused constexpr uint8 U8_MIN      = 0x00U;
        __CDS_MaybeUnused constexpr uint16 U16_MIN    = 0x0000U;
        __CDS_MaybeUnused constexpr uint32 U32_MIN    = 0x00000000U;
        __CDS_MaybeUnused constexpr uint64 U64_MIN    = 0x0000000000000000LLU;

        __CDS_MaybeUnused constexpr sint8 S8_MAX      = 0x7F;
        __CDS_MaybeUnused constexpr sint16 S16_MAX    = 0x7FFF;
        __CDS_MaybeUnused constexpr sint32 S32_MAX    = 0x7FFFFFFF;
        __CDS_MaybeUnused constexpr sint64 S64_MAX    = 0x7FFFFFFFFFFFFFFFLL;

        __CDS_MaybeUnused constexpr sint8 S8_MIN      = - 0x80;
        __CDS_MaybeUnused constexpr sint16 S16_MIN    = - 0x8000;
        __CDS_MaybeUnused constexpr sint32 S32_MIN    = - 0x80000000L;
        __CDS_MaybeUnused constexpr sint64 S64_MIN    = - S64_MAX - 1;
    }
}

#endif //CDS_LIMITS_HPP
