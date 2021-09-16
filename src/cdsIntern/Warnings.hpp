//
// CDS Warning Suppression Extension Header - Do not modify this header directly
//
// Generated for CDS through Warning Suppression Generator Tool
// Author: Loghin Vlad-Andrei - github.com/LoghinVladDev
// Generation Date: 16/09/21 - 15:06:42
// CDS Version - 0.0.2
// Licenced under Project Licence - https://github.com/LoghinVladDev/CDS/blob/master/LICENSE
//


//// Start of Include Guards

#ifndef CDS_WARNINGS_HPP
#define CDS_WARNINGS_HPP

//// End of Include Guards


//// Start of Platform Dependent Macros

#if defined(_MSC_VER)


#define __CDS_WarningSuppression_MSVC_SuppressEnable(_warningName) \
__pragma(warning(push)) \
__pragma(warning(disable:_warningName))

#define __CDS_WarningSuppression_MSVC_SuppressDisable(_warningName) \
__pragma(warning(pop))


#else // if defined(_MSC_VER)


#define __CDS_WarningSuppression_MSVC_SuppressEnable(_warningName)
#define __CDS_WarningSuppression_MSVC_SuppressDisable(_warningName)


#endif // if defined(_MSC_VER)

//// End of Platform Dependent Macros


//// Start of Platform Independent Macros

#define __CDS_WarningSuppression_Platform_SuppressEnable(_platform, _warning) __CDS_WarningSuppression _ ## _platform ## _ ## _warning ## _SuppressEnable
#define __CDS_WarningSuppression_Platform_SuppressDisable(_platform, _warning) __CDS_WarningSuppression_ ## _platform ## _ ## _warning ## _SuppressDisable

//// End of Platform Independent Macros


//// Start of Platform Dependent Config Macros

#define __CDS_WarningSuppression_MSVC_ArgumentPossibleUnexpectedValues_SuppressEnable __CDS_WarningSuppression_MSVC_SuppressEnable(6387)
#define __CDS_WarningSuppression_MSVC_ArgumentPossibleUnexpectedValues_SuppressDisable __CDS_WarningSuppression_MSVC_SuppressDisable(6387)

#define __CDS_WarningSuppression_MSVC_UseScopedEnum_SuppressEnable __CDS_WarningSuppression_MSVC_SuppressEnable(26812)
#define __CDS_WarningSuppression_MSVC_UseScopedEnum_SuppressDisable __CDS_WarningSuppression_MSVC_SuppressDisable(26812)


#define __CDS_WarningSuppression_SuppressEnable(_warning) \
	__CDS_WarningSuppression_Platform_SuppressEnable(MSVC, _warning)

#define __CDS_WarningSuppression_SuppressDisable(_warning) \
	__CDS_WarningSuppression_Platform_SuppressDisable(MSVC, _warning)

//// End of Platform Dependent Config Macros


//// Start of Platform Dependent Config Macros

#define __CDS_WarningSuppression_ArgumentPossibleUnexpectedValues_SuppressEnable __CDS_WarningSuppression_SuppressEnable(ArgumentPossibleUnexpectedValues)
#define __CDS_WarningSuppression_ArgumentPossibleUnexpectedValues_SuppressDisable __CDS_WarningSuppression_SuppressDisable(ArgumentPossibleUnexpectedValues)

#define __CDS_WarningSuppression_UseScopedEnum_SuppressEnable __CDS_WarningSuppression_SuppressEnable(UseScopedEnum)
#define __CDS_WarningSuppression_UseScopedEnum_SuppressDisable __CDS_WarningSuppression_SuppressDisable(UseScopedEnum)

//// End of Platform Dependent Config Macros


//// Start of Include Guards

#endif // CDS_WARNINGS_HPP

//// End of Include Guards


