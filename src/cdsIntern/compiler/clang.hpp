//
// Created by loghin on 26.09.2021.
//

#ifndef CDS_CLANG_HPP
#define CDS_CLANG_HPP

#if defined(__clang__)

#define GCC_VERSION ( __clang_major__ * 10000 + __clang_minor__ * 100 + __clang_patchlevel__ )

#undef __CDS_compiler_name
#undef __CDS_compiler_version
#define __CDS_compiler_name "clang" /* NOLINT(bugprone-reserved-identifier) */
#define __CDS_compiler_version GCC_VERSION /* NOLINT(bugprone-reserved-identifier) */


#if __CDS_cpplang_core_version >= __CDS_cpplang_core_version_17

#else

#undef __CDS_cpplang_FunctionAliasNoexcept
#define __CDS_cpplang_FunctionAliasNoexcept(_exceptspec) /* NOLINT(bugprone-reserved-identifier) */

#endif


#endif

#endif //CDS_CLANG_HPP
