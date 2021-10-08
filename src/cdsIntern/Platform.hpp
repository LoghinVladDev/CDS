//
// Created by loghin on 22/09/2021.
//

#ifndef CDS_PLATFORM_HPP
#define CDS_PLATFORM_HPP

#define __CDS_Platform "Undefined" /* NOLINT(bugprone-reserved-identifier) */

#if defined(_WIN32)

#define __CDS_Platform_Microsoft_Windows "Microsoft Windows" /* NOLINT(bugprone-reserved-identifier) */

#undef __CDS_Platform
#define __CDS_Platform __CDS_Platform_Microsoft_Windows

#define __CDS_Platform_Microsoft_Windows_Version_Win7 _WIN32_WINNT_WIN7
#define __CDS_Platform_Microsoft_Windows_Version_Win8 _WIN32_WINNT_WIN8
#define __CDS_Platform_Microsoft_Windows_Version_Win8_1 _WIN32_WINNT_WINBLUE
#define __CDS_Platform_Microsoft_Windows_Version_Win10 _WIN32_WINNT_WIN10
#define __CDS_Platform_Microsoft_Windows_Version_Win11 _WIN32_WINNT_WIN11

#if !defined(__CDS_Platform_Version)
#define __CDS_Platform_Version __CDS_Platform_Microsoft_Windows_Version_Win7
#endif

#undef _WIN32_WINNT
#define _WIN32_WINNT __CDS_Platform_Version

#endif

#if defined(linux)

#define __CDS_Platform_Linux "Linux" /* NOLINT(bugprone-reserved-identifier) */

#undef __CDS_Platform
#define __CDS_Platform __CDS_Platform_Linux /* NOLINT(bugprone-reserved-identifier) */

#endif

#endif //CDS_PLATFORM_HPP
