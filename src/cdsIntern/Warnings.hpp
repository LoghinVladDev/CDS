//
// CDS Warning Suppression Extension Header - Do not modify this header directly
//
// Generated for CDS through Warning Suppression Generator Tool
// Author: Loghin Vlad-Andrei - github.com/LoghinVladDev
// Generation Date: 11/03/22 - 03:25:03
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

#if defined(__clang__)

#define __CDS_WarningSuppression_clang_CreatePragma(_text) #_text

#define __CDS_WarningSuppression_clang_SuppressEnable(_warningName) /* NOLINT(bugprone-reserved-identifier) */ \
_Pragma("clang diagnostic push") \
_Pragma(__CDS_WarningSuppression_clang_CreatePragma(clang diagnostic ignored #_warningName))

#define __CDS_WarningSuppression_clang_SuppressDisable(_warningName) /* NOLINT(bugprone-reserved-identifier) */ \
_Pragma("clang diagnostic pop")


#else // if defined(__clang__)


#define __CDS_WarningSuppression_clang_SuppressEnable(_warningName) /* NOLINT(bugprone-reserved-identifier) */
#define __CDS_WarningSuppression_clang_SuppressDisable(_warningName) /* NOLINT(bugprone-reserved-identifier) */


#endif // if defined(__clang__)

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

#define __CDS_WarningSuppression_MSVC_UnsafeDeleteVoidPtr_SuppressEnable /* NOLINT(bugprone-reserved-identifier) */
#define __CDS_WarningSuppression_MSVC_UnsafeDeleteVoidPtr_SuppressDisable /* NOLINT(bugprone-reserved-identifier) */

#define __CDS_WarningSuppression_MSVC_FunctionTypeTraits_SuppressEnable __CDS_WarningSuppression_MSVC_SuppressEnable(4180) /* NOLINT(bugprone-reserved-identifier) */
#define __CDS_WarningSuppression_MSVC_FunctionTypeTraits_SuppressDisable __CDS_WarningSuppression_MSVC_SuppressDisable(4180) /* NOLINT(bugprone-reserved-identifier) */

#define __CDS_WarningSuppression_MSVC_DeducedNoexceptTermination_SuppressEnable __CDS_WarningSuppression_MSVC_SuppressEnable(4297) /* NOLINT(bugprone-reserved-identifier) */
#define __CDS_WarningSuppression_MSVC_DeducedNoexceptTermination_SuppressDisable __CDS_WarningSuppression_MSVC_SuppressDisable(4297) /* NOLINT(bugprone-reserved-identifier) */

#define __CDS_WarningSuppression_MSVC_NoReturnStatement_SuppressEnable /* NOLINT(bugprone-reserved-identifier) */
#define __CDS_WarningSuppression_MSVC_NoReturnStatement_SuppressDisable /* NOLINT(bugprone-reserved-identifier) */

#define __CDS_WarningSuppression_MSVC_VoidPtrDereference_SuppressEnable /* NOLINT(bugprone-reserved-identifier) */
#define __CDS_WarningSuppression_MSVC_VoidPtrDereference_SuppressDisable /* NOLINT(bugprone-reserved-identifier) */

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

#define __CDS_WarningSuppression_GCC_UnsafeDeleteVoidPtr_SuppressEnable __CDS_WarningSuppression_GCC_SuppressEnable(-Wdelete-incomplete) /* NOLINT(bugprone-reserved-identifier) */
#define __CDS_WarningSuppression_GCC_UnsafeDeleteVoidPtr_SuppressDisable __CDS_WarningSuppression_GCC_SuppressDisable(-Wdelete-incomplete) /* NOLINT(bugprone-reserved-identifier) */

#define __CDS_WarningSuppression_GCC_FunctionTypeTraits_SuppressEnable /* NOLINT(bugprone-reserved-identifier) */
#define __CDS_WarningSuppression_GCC_FunctionTypeTraits_SuppressDisable /* NOLINT(bugprone-reserved-identifier) */

#define __CDS_WarningSuppression_GCC_DeducedNoexceptTermination_SuppressEnable __CDS_WarningSuppression_GCC_SuppressEnable(-Wterminate) /* NOLINT(bugprone-reserved-identifier) */
#define __CDS_WarningSuppression_GCC_DeducedNoexceptTermination_SuppressDisable __CDS_WarningSuppression_GCC_SuppressDisable(-Wterminate) /* NOLINT(bugprone-reserved-identifier) */

#define __CDS_WarningSuppression_GCC_NoReturnStatement_SuppressEnable __CDS_WarningSuppression_GCC_SuppressEnable(-Wreturn-type) /* NOLINT(bugprone-reserved-identifier) */
#define __CDS_WarningSuppression_GCC_NoReturnStatement_SuppressDisable __CDS_WarningSuppression_GCC_SuppressDisable(-Wreturn-type) /* NOLINT(bugprone-reserved-identifier) */

#define __CDS_WarningSuppression_GCC_VoidPtrDereference_SuppressEnable __CDS_WarningSuppression_GCC_SuppressEnable(-Wvoid-ptr-dereference) /* NOLINT(bugprone-reserved-identifier) */
#define __CDS_WarningSuppression_GCC_VoidPtrDereference_SuppressDisable __CDS_WarningSuppression_GCC_SuppressDisable(-Wvoid-ptr-dereference) /* NOLINT(bugprone-reserved-identifier) */

#define __CDS_WarningSuppression_clang_ArgumentPossibleUnexpectedValue_SuppressEnable /* NOLINT(bugprone-reserved-identifier) */
#define __CDS_WarningSuppression_clang_ArgumentPossibleUnexpectedValue_SuppressDisable /* NOLINT(bugprone-reserved-identifier) */

#define __CDS_WarningSuppression_clang_UseScopedEnum_SuppressEnable /* NOLINT(bugprone-reserved-identifier) */
#define __CDS_WarningSuppression_clang_UseScopedEnum_SuppressDisable /* NOLINT(bugprone-reserved-identifier) */

#define __CDS_WarningSuppression_clang_DelegateCtorSuppressUninitializedMembers_SuppressEnable /* NOLINT(bugprone-reserved-identifier) */
#define __CDS_WarningSuppression_clang_DelegateCtorSuppressUninitializedMembers_SuppressDisable /* NOLINT(bugprone-reserved-identifier) */

#define __CDS_WarningSuppression_clang_ArithmeticOverflow_SuppressEnable /* NOLINT(bugprone-reserved-identifier) */
#define __CDS_WarningSuppression_clang_ArithmeticOverflow_SuppressDisable /* NOLINT(bugprone-reserved-identifier) */

#define __CDS_WarningSuppression_clang_ThreadForceTermination_SuppressEnable /* NOLINT(bugprone-reserved-identifier) */
#define __CDS_WarningSuppression_clang_ThreadForceTermination_SuppressDisable /* NOLINT(bugprone-reserved-identifier) */

#define __CDS_WarningSuppression_clang_StringOperationOverflow_SuppressEnable /* NOLINT(bugprone-reserved-identifier) */
#define __CDS_WarningSuppression_clang_StringOperationOverflow_SuppressDisable /* NOLINT(bugprone-reserved-identifier) */

#define __CDS_WarningSuppression_clang_UnusedResult_SuppressEnable __CDS_WarningSuppression_clang_SuppressEnable(-Wunused-result) /* NOLINT(bugprone-reserved-identifier) */
#define __CDS_WarningSuppression_clang_UnusedResult_SuppressDisable __CDS_WarningSuppression_clang_SuppressDisable(-Wunused-result) /* NOLINT(bugprone-reserved-identifier) */

#define __CDS_WarningSuppression_clang_UnsafeDeleteVoidPtr_SuppressEnable __CDS_WarningSuppression_clang_SuppressEnable(-Wdelete-incomplete) /* NOLINT(bugprone-reserved-identifier) */
#define __CDS_WarningSuppression_clang_UnsafeDeleteVoidPtr_SuppressDisable __CDS_WarningSuppression_clang_SuppressDisable(-Wdelete-incomplete) /* NOLINT(bugprone-reserved-identifier) */

#define __CDS_WarningSuppression_clang_FunctionTypeTraits_SuppressEnable /* NOLINT(bugprone-reserved-identifier) */
#define __CDS_WarningSuppression_clang_FunctionTypeTraits_SuppressDisable /* NOLINT(bugprone-reserved-identifier) */

#define __CDS_WarningSuppression_clang_DeducedNoexceptTermination_SuppressEnable /* NOLINT(bugprone-reserved-identifier) */
#define __CDS_WarningSuppression_clang_DeducedNoexceptTermination_SuppressDisable /* NOLINT(bugprone-reserved-identifier) */

#define __CDS_WarningSuppression_clang_NoReturnStatement_SuppressEnable __CDS_WarningSuppression_clang_SuppressEnable(-Wreturn-type) /* NOLINT(bugprone-reserved-identifier) */
#define __CDS_WarningSuppression_clang_NoReturnStatement_SuppressDisable __CDS_WarningSuppression_clang_SuppressDisable(-Wreturn-type) /* NOLINT(bugprone-reserved-identifier) */

#define __CDS_WarningSuppression_clang_VoidPtrDereference_SuppressEnable __CDS_WarningSuppression_clang_SuppressEnable(-Wvoid-ptr-dereference) /* NOLINT(bugprone-reserved-identifier) */
#define __CDS_WarningSuppression_clang_VoidPtrDereference_SuppressDisable __CDS_WarningSuppression_clang_SuppressDisable(-Wvoid-ptr-dereference) /* NOLINT(bugprone-reserved-identifier) */


#define __CDS_WarningSuppression_SuppressEnable(_warning) /* NOLINT(bugprone-reserved-identifier) */ \
	__CDS_WarningSuppression_Platform_SuppressEnable(MSVC, _warning)\
	__CDS_WarningSuppression_Platform_SuppressEnable(GCC, _warning)\
	__CDS_WarningSuppression_Platform_SuppressEnable(clang, _warning)

#define __CDS_WarningSuppression_SuppressDisable(_warning) /* NOLINT(bugprone-reserved-identifier) */ \
	__CDS_WarningSuppression_Platform_SuppressDisable(MSVC, _warning)\
	__CDS_WarningSuppression_Platform_SuppressDisable(GCC, _warning)\
	__CDS_WarningSuppression_Platform_SuppressDisable(clang, _warning)

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

#define __CDS_WarningSuppression_UnsafeDeleteVoidPtr_SuppressEnable __CDS_WarningSuppression_SuppressEnable(UnsafeDeleteVoidPtr) /* NOLINT(bugprone-reserved-identifier) */
#define __CDS_WarningSuppression_UnsafeDeleteVoidPtr_SuppressDisable __CDS_WarningSuppression_SuppressDisable(UnsafeDeleteVoidPtr) /* NOLINT(bugprone-reserved-identifier) */

#define __CDS_WarningSuppression_FunctionTypeTraits_SuppressEnable __CDS_WarningSuppression_SuppressEnable(FunctionTypeTraits) /* NOLINT(bugprone-reserved-identifier) */
#define __CDS_WarningSuppression_FunctionTypeTraits_SuppressDisable __CDS_WarningSuppression_SuppressDisable(FunctionTypeTraits) /* NOLINT(bugprone-reserved-identifier) */

#define __CDS_WarningSuppression_DeducedNoexceptTermination_SuppressEnable __CDS_WarningSuppression_SuppressEnable(DeducedNoexceptTermination) /* NOLINT(bugprone-reserved-identifier) */
#define __CDS_WarningSuppression_DeducedNoexceptTermination_SuppressDisable __CDS_WarningSuppression_SuppressDisable(DeducedNoexceptTermination) /* NOLINT(bugprone-reserved-identifier) */

#define __CDS_WarningSuppression_NoReturnStatement_SuppressEnable __CDS_WarningSuppression_SuppressEnable(NoReturnStatement) /* NOLINT(bugprone-reserved-identifier) */
#define __CDS_WarningSuppression_NoReturnStatement_SuppressDisable __CDS_WarningSuppression_SuppressDisable(NoReturnStatement) /* NOLINT(bugprone-reserved-identifier) */

#define __CDS_WarningSuppression_VoidPtrDereference_SuppressEnable __CDS_WarningSuppression_SuppressEnable(VoidPtrDereference) /* NOLINT(bugprone-reserved-identifier) */
#define __CDS_WarningSuppression_VoidPtrDereference_SuppressDisable __CDS_WarningSuppression_SuppressDisable(VoidPtrDereference) /* NOLINT(bugprone-reserved-identifier) */

//// End of Platform Dependent Config Macros


//// Start of Include Guards

#endif // CDS_WARNINGS_HPP

//// End of Include Guards


