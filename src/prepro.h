//
// Created by vladl on 3/29/2021.
//

#ifndef CDS_PREPRO_H
#define CDS_PREPRO_H

#include "std-types.h"

#define CDS_STRING_POSTFIX

#if defined(CDS_NO_POSTFIX_FUNCTIONS)

#undef CDS_INTEGER_POSTFIX
#undef CDS_BOOLEAN_POSTFIX
#undef CDS_STRING_POSTFIX
#undef CDS_LONG_POSTFIX
#undef CDS_FLOAT_POSTFIX
#undef CDS_DOUBLE_POSTFIX

#endif

#include <CDS/Compiler>
#include <CDS/Platform>

#ifdef CDS_DEBUG

#if ! defined(_MSC_VER)
#warning CDS Object Debug Enabled
#endif

#ifndef debug_private
#define debug_private public
#endif

#else

#ifndef debug_private
#define debug_private private
#endif

#endif

#include <CDS/Warnings>


#endif //CDS_PREPRO_H
