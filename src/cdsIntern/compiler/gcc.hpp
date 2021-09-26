//
// Created by loghin on 22/09/2021.
//

#ifndef CDS_GCC_HPP
#define CDS_GCC_HPP

#if defined(__GNUC__) && !defined (GCC_VERSION) && !defined(__clang__)

#define GCC_VERSION ( __GNUC__ * 10000 + __GNUC_MINOR__ * 100 + __GNUC_PATCHLEVEL__ )

#undef __CDS_compiler_name
#undef __CDS_compiler_version
#define __CDS_compiler_name "GNU GCC" /* NOLINT(bugprone-reserved-identifier) */
#define __CDS_compiler_version GCC_VERSION /* NOLINT(bugprone-reserved-identifier) */

#endif

#endif //CDS_GCC_HPP
