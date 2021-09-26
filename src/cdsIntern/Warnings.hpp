//
// CDS Warning Suppression Extension Header - Do not modify this header directly
//
// Generated for CDS through Warning Suppression Generator Tool
// Author: Loghin Vlad-Andrei - github.com/LoghinVladDev
// Generation Date: 26/09/21 - 05:44:10
// CDS Version - 0.0.2
// Licenced under Project Licence - https://github.com/LoghinVladDev/CDS/blob/master/LICENSE
//


//// Start of Include Guards

#ifndef CDS_WARNINGS_HPP
#define CDS_WARNINGS_HPP

//// End of Include Guards


//// Start of Platform Dependent Macros

#if defined(_MSC_VER)



#define __CDS_WarningSuppression_MSVC_SuppressEnable(_warningName) /* NOLINT(bugprone-reserved-identifier) */ \
__pragma(warning(push)) \
__pragma(warning(disable:_warningName))

#define __CDS_WarningSuppression_MSVC_SuppressDisable(_warningName) /* NOLINT(bugprone-reserved-identifier) */ \
__pragma(warning(pop))


#else // if defined(_MSC_VER)


#define __CDS_WarningSuppression_MSVC_SuppressEnable(_warningName) /* NOLINT(bugprone-reserved-identifier) */
#define __CDS_WarningSuppression_MSVC_SuppressDisable(_warningName) /* NOLINT(bugprone-reserved-identifier) */


#endif // if defined(_MSC_VER)

#if defined(__GNUC__) && !defined(__clang__)

#define __CDS_WarningSuppression_GCC_CreatePragma(_text) #_text

#define __CDS_WarningSuppression_GCC_SuppressEnable(_warningName) /* NOLINT(bugprone-reserved-identifier) */ \
_Pragma("GCC diagnostic push") \
_Pragma(__CDS_WarningSuppression_GCC_CreatePragma(GCC diagnostic ignored #_warningName))

#define __CDS_WarningSuppression_GCC_SuppressDisable(_warningName) /* NOLINT(bugprone-reserved-identifier) */ \
_Pragma("GCC diagnostic pop")


#else // if defined(__GCC__)


#define __CDS_WarningSuppression_GCC_SuppressEnable(_warningName) /* NOLINT(bugprone-reserved-identifier) */
#define __CDS_WarningSuppression_GCC_SuppressDisable(_warningName) /* NOLINT(bugprone-reserved-identifier) */


#endif // if defined(__GNUC__)

//// End of Platform Dependent Macros


//// Start of Platform Independent Macros

#define __CDS_WarningSuppression_Platform_SuppressEnable(_platform, _warning) __CDS_WarningSuppression_ ## _platform ## _ ## _warning ## _SuppressEnable /* NOLINT(bugprone-reserved-identifier) */
#define __CDS_WarningSuppression_Platform_SuppressDisable(_platform, _warning) __CDS_WarningSuppression_ ## _platform ## _ ## _warning ## _SuppressDisable /* NOLINT(bugprone-reserved-identifier) */

//// End of Platform Independent Macros


//// Start of Platform Dependent Config Macros

#define __CDS_WarningSuppression_MSVC_ArgumentPossibleUnexpectedValue_SuppressEnable __CDS_WarningSuppression_MSVC_SuppressEnable(6387) /* NOLINT(bugprone-reserved-identifier) */
#define __CDS_WarningSuppression_MSVC_ArgumentPossibleUnexpectedValue_SuppressDisable __CDS_WarningSuppression_MSVC_SuppressDisable(6387) /* NOLINT(bugprone-reserved-identifier) */

#define __CDS_WarningSuppression_MSVC_UseScopedEnum_SuppressEnable __CDS_WarningSuppression_MSVC_SuppressEnable(26812) /* NOLINT(bugprone-reserved-identifier) */
#define __CDS_WarningSuppression_MSVC_UseScopedEnum_SuppressDisable __CDS_WarningSuppression_MSVC_SuppressDisable(26812) /* NOLINT(bugprone-reserved-identifier) */

#define __CDS_WarningSuppression_MSVC_DelegateCtorSuppressUninitializedMembers_SuppressEnable __CDS_WarningSuppression_MSVC_SuppressEnable(26495) /* NOLINT(bugprone-reserved-identifier) */
#define __CDS_WarningSuppression_MSVC_DelegateCtorSuppressUninitializedMembers_SuppressDisable __CDS_WarningSuppression_MSVC_SuppressDisable(26495) /* NOLINT(bugprone-reserved-identifier) */

#define __CDS_WarningSuppression_MSVC_ArithmeticOverflow_SuppressEnable __CDS_WarningSuppression_MSVC_SuppressEnable(26451) /* NOLINT(bugprone-reserved-identifier) */
#define __CDS_WarningSuppression_MSVC_ArithmeticOverflow_SuppressDisable __CDS_WarningSuppression_MSVC_SuppressDisable(26451) /* NOLINT(bugprone-reserved-identifier) */

#define __CDS_WarningSuppression_MSVC_ThreadForceTermination_SuppressEnable __CDS_WarningSuppression_MSVC_SuppressEnable(6258) /* NOLINT(bugprone-reserved-identifier) */
#define __CDS_WarningSuppression_MSVC_ThreadForceTermination_SuppressDisable __CDS_WarningSuppression_MSVC_SuppressDisable(6258) /* NOLINT(bugprone-reserved-identifier) */

#define __CDS_WarningSuppression_MSVC_StringOperationOverflow_SuppressEnable /* NOLINT(bugprone-reserved-identifier) */
#define __CDS_WarningSuppression_MSVC_StringOperationOverflow_SuppressDisable /* NOLINT(bugprone-reserved-identifier) */

#define __CDS_WarningSuppression_MSVC_UnusedResult_SuppressEnable /* NOLINT(bugprone-reserved-identifier) */
#define __CDS_WarningSuppression_MSVC_UnusedResult_SuppressDisable /* NOLINT(bugprone-reserved-identifier) */

#define __CDS_WarningSuppression_GCC_ArgumentPossibleUnexpectedValue_SuppressEnable /* NOLINT(bugprone-reserved-identifier) */
#define __CDS_WarningSuppression_GCC_ArgumentPossibleUnexpectedValue_SuppressDisable /* NOLINT(bugprone-reserved-identifier) */

#define __CDS_WarningSuppression_GCC_UseScopedEnum_SuppressEnable /* NOLINT(bugprone-reserved-identifier) */
#define __CDS_WarningSuppression_GCC_UseScopedEnum_SuppressDisable /* NOLINT(bugprone-reserved-identifier) */

#define __CDS_WarningSuppression_GCC_DelegateCtorSuppressUninitializedMembers_SuppressEnable /* NOLINT(bugprone-reserved-identifier) */
#define __CDS_WarningSuppression_GCC_DelegateCtorSuppressUninitializedMembers_SuppressDisable /* NOLINT(bugprone-reserved-identifier) */

#define __CDS_WarningSuppression_GCC_ArithmeticOverflow_SuppressEnable /* NOLINT(bugprone-reserved-identifier) */
#define __CDS_WarningSuppression_GCC_ArithmeticOverflow_SuppressDisable /* NOLINT(bugprone-reserved-identifier) */

#define __CDS_WarningSuppression_GCC_ThreadForceTermination_SuppressEnable /* NOLINT(bugprone-reserved-identifier) */
#define __CDS_WarningSuppression_GCC_ThreadForceTermination_SuppressDisable /* NOLINT(bugprone-reserved-identifier) */

#define __CDS_WarningSuppression_GCC_StringOperationOverflow_SuppressEnable __CDS_WarningSuppression_GCC_SuppressEnable(-Wstringop-overflow) /* NOLINT(bugprone-reserved-identifier) */
#define __CDS_WarningSuppression_GCC_StringOperationOverflow_SuppressDisable __CDS_WarningSuppression_GCC_SuppressDisable(-Wstringop-overflow) /* NOLINT(bugprone-reserved-identifier) */

#define __CDS_WarningSuppression_GCC_UnusedResult_SuppressEnable __CDS_WarningSuppression_GCC_SuppressEnable(-Wunused-result) /* NOLINT(bugprone-reserved-identifier) */
#define __CDS_WarningSuppression_GCC_UnusedResult_SuppressDisable __CDS_WarningSuppression_GCC_SuppressDisable(-Wunused-result) /* NOLINT(bugprone-reserved-identifier) */


#define __CDS_WarningSuppression_SuppressEnable(_warning) /* NOLINT(bugprone-reserved-identifier) */ \
	__CDS_WarningSuppression_Platform_SuppressEnable(MSVC, _warning)\
	__CDS_WarningSuppression_Platform_SuppressEnable(GCC, _warning)

#define __CDS_WarningSuppression_SuppressDisable(_warning) /* NOLINT(bugprone-reserved-identifier) */ \
	__CDS_WarningSuppression_Platform_SuppressDisable(MSVC, _warning)\
	__CDS_WarningSuppression_Platform_SuppressDisable(GCC, _warning)

//// End of Platform Dependent Config Macros


//// Start of Platform Dependent Config Macros

#define __CDS_WarningSuppression_ArgumentPossibleUnexpectedValue_SuppressEnable __CDS_WarningSuppression_SuppressEnable(ArgumentPossibleUnexpectedValue) /* NOLINT(bugprone-reserved-identifier) */
#define __CDS_WarningSuppression_ArgumentPossibleUnexpectedValue_SuppressDisable __CDS_WarningSuppression_SuppressDisable(ArgumentPossibleUnexpectedValue) /* NOLINT(bugprone-reserved-identifier) */

#define __CDS_WarningSuppression_UseScopedEnum_SuppressEnable __CDS_WarningSuppression_SuppressEnable(UseScopedEnum) /* NOLINT(bugprone-reserved-identifier) */
#define __CDS_WarningSuppression_UseScopedEnum_SuppressDisable __CDS_WarningSuppression_SuppressDisable(UseScopedEnum) /* NOLINT(bugprone-reserved-identifier) */

#define __CDS_WarningSuppression_DelegateCtorSuppressUninitializedMembers_SuppressEnable __CDS_WarningSuppression_SuppressEnable(DelegateCtorSuppressUninitializedMembers) /* NOLINT(bugprone-reserved-identifier) */
#define __CDS_WarningSuppression_DelegateCtorSuppressUninitializedMembers_SuppressDisable __CDS_WarningSuppression_SuppressDisable(DelegateCtorSuppressUninitializedMembers) /* NOLINT(bugprone-reserved-identifier) */

#define __CDS_WarningSuppression_ArithmeticOverflow_SuppressEnable __CDS_WarningSuppression_SuppressEnable(ArithmeticOverflow) /* NOLINT(bugprone-reserved-identifier) */
#define __CDS_WarningSuppression_ArithmeticOverflow_SuppressDisable __CDS_WarningSuppression_SuppressDisable(ArithmeticOverflow) /* NOLINT(bugprone-reserved-identifier) */

#define __CDS_WarningSuppression_ThreadForceTermination_SuppressEnable __CDS_WarningSuppression_SuppressEnable(ThreadForceTermination) /* NOLINT(bugprone-reserved-identifier) */
#define __CDS_WarningSuppression_ThreadForceTermination_SuppressDisable __CDS_WarningSuppression_SuppressDisable(ThreadForceTermination) /* NOLINT(bugprone-reserved-identifier) */

#define __CDS_WarningSuppression_StringOperationOverflow_SuppressEnable __CDS_WarningSuppression_SuppressEnable(StringOperationOverflow) /* NOLINT(bugprone-reserved-identifier) */
#define __CDS_WarningSuppression_StringOperationOverflow_SuppressDisable __CDS_WarningSuppression_SuppressDisable(StringOperationOverflow) /* NOLINT(bugprone-reserved-identifier) */

#define __CDS_WarningSuppression_UnusedResult_SuppressEnable __CDS_WarningSuppression_SuppressEnable(UnusedResult) /* NOLINT(bugprone-reserved-identifier) */
#define __CDS_WarningSuppression_UnusedResult_SuppressDisable __CDS_WarningSuppression_SuppressDisable(UnusedResult) /* NOLINT(bugprone-reserved-identifier) */

//// End of Platform Dependent Config Macros


//// Start of Include Guards

#endif // CDS_WARNINGS_HPP

//// End of Include Guards


