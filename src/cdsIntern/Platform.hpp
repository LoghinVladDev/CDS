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

#endif

#if defined(linux)

#define __CDS_Platform_Linux "Linux" /* NOLINT(bugprone-reserved-identifier) */

#undef __CDS_Platform
#define __CDS_Platform __CDS_Platform_Linux /* NOLINT(bugprone-reserved-identifier) */

#endif

#endif //CDS_PLATFORM_HPP
