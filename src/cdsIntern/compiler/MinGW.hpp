//
// Created by vladl on 9/25/2021.
//

#ifndef CDS_MINGW_H
#define CDS_MINGW_H

#if defined(__MINGW64__) && !defined(GCC_VERSION)

#if !defined(__MINGW64_VERSION_MAJOR)
#define __MINGW64_VERSION_MAJOR 0
#endif

#if !defined(__MINGW64_VERSION_MINOR)
#define __MINGW64_VERSION_MINOR 0
#endif

#if !defined(__MINGW64_VERSION_BUGFIX)
#define __MINGW64_VERSION_BUGFIX 0
#endif

#define GCC_VERSION ( __MINGW64_VERSION_MAJOR * 10000 + __MINGW64_VERSION_MINOR * 100 + __MINGW64_VERSION_BUGFIX )

#undef __CDS_compiler_name
#undef __CDS_compiler_version

#define __CDS_compiler_name "MinGW-w64" /* NOLINT(bugprone-reserved-identifier) */
#define __CDS_compiler_version GCC_VERSION /* NOLINT(bugprone-reserved-identifier) */


#undef __CDS_cpplang_ConstexprPureAbstract
#define __CDS_cpplang_ConstexprPureAbstract /* NOLINT(bugprone-reserved-identifier) */


#endif

#endif //CDS_MINGW_H
