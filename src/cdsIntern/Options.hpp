//
// Created by loghin on 26.09.2021.
//

#ifndef CDS_OPTIONS_HPP
#define CDS_OPTIONS_HPP

#define CDS_STRING_POSTFIX

#if defined(CDS_NO_POSTFIX_FUNCTIONS)

#undef CDS_INTEGER_POSTFIX
#undef CDS_BOOLEAN_POSTFIX
#undef CDS_STRING_POSTFIX
#undef CDS_LONG_POSTFIX
#undef CDS_FLOAT_POSTFIX
#undef CDS_DOUBLE_POSTFIX

#endif

#define __CDS_StringFormat_StartSize 128
#define __CDS_StringFormat_SizeMultiplier 4
#define __CDS_StringFormat_MaxSize INT32_MAX

#if defined(__CDS_StringFormat_SizeMultiplier_Fast)

#undef __CDS_StringFormat_SizeMultiplier
#define __CDS_StringFormat_SizeMultiplier 8

#endif

#if defined(__CDS_StringFormat_SizeMultiplier_VeryFast)

#undef __CDS_StringFormat_SizeMultiplier
#define __CDS_StringFormat_SizeMultiplier 16

#endif

#if defined(__CDS_StringFormat_StartSize_Large)

#undef __CDS_StringFormat_StartSize
#define __CDS_StringFormat_StartSize 2048

#endif

#if defined(__CDS_StringFormat_StartSize_VeryLarge)

#undef __CDS_StringFormat_StartSize
#define __CDS_StringFormat_StartSize 32768

#endif

#if ! defined(__CDS_InlineFunctions_None) && ! defined(__CDS_InlineFunctions_Optimal) && ! defined(__CDS_InlineFunctions_Aggressive)

#define __CDS_InlineFunctions_Aggressive

#endif


#if defined(__CDS_InlineFunctions_None)

#define __CDS_OptimalInline
#define __CDS_OptionalInline

#elif defined(__CDS_InlineFunctions_Optimal)

#define __CDS_OptimalInline inline
#define __CDS_OptionalInline

#elif defined(__CDS_InlineFunctions_Aggressive)

#define __CDS_OptimalInline inline
#define __CDS_OptionalInline inline

#endif


#endif //CDS_OPTIONS_HPP
