//
// Created by loghin on 22/09/2021.
//

#ifndef CDS_PLATFORM_HPP
#define CDS_PLATFORM_HPP

#define __CDS_platform_name "Undefined" /* NOLINT(bugprone-reserved-identifier) */

#if defined(_WIN32)

#undef __CDS_platform_name
#define __CDS_platform_name "Microsoft Windows"

#endif

#if defined(linux)

#undef __CDS_platform_name
#define __CDS_platform_name "Linux" /* NOLINT(bugprone-reserved-identifier) */

#endif

#endif //CDS_PLATFORM_HPP
