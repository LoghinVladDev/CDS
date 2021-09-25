//
// Created by loghin on 25/09/2021.
//

#ifndef CDS_LIMITS_HPP
#define CDS_LIMITS_HPP

#include <CDS/Types>

namespace Limits {
    constexpr uint8 U8_MAX      = 0xFFu;
    constexpr uint16 U16_MAX    = 0xFFFFu;
    constexpr uint32 U32_MAX    = 0xFFFFFFFFlu;
    constexpr uint64 U64_MAX    = 0xFFFFFFFFFFFFFFFFllu;

    constexpr uint8 U8_MIN      = 0x00u;
    constexpr uint16 U16_MIN    = 0x0000u;
    constexpr uint32 U32_MIN    = 0x00000000lu;
    constexpr uint64 U64_MIN    = 0x0000000000000000llu;

    constexpr sint8 S8_MAX      = 0x7F;
    constexpr sint16 S16_MAX    = 0x7FFF;
    constexpr sint32 S32_MAX    = 0x7FFFFFFFl;
    constexpr sint64 S64_MAX    = 0x7FFFFFFFFFFFFFFFll;

    constexpr sint8 S8_MIN      = - 0x80;
    constexpr sint16 S16_MIN    = - 0x8000;
    constexpr sint32 S32_MIN    = - 0x80000000l;
    constexpr sint64 S64_MIN    = - 0x8000000000000000ll;
}

#endif //CDS_LIMITS_HPP
