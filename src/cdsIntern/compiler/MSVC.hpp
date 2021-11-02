//
// Created by loghin on 22/09/2021.
//

#ifndef CDS_MSVC_HPP
#define CDS_MSVC_HPP

#if defined(_MSC_VER)

#define MSVC_VERSION ( _MSC_VER * 100 )

#undef __CDS_compiler_name
#undef __CDS_compiler_version
#define __CDS_compiler_name "Microsoft Visual C++" /* NOLINT(bugprone-reserved-identifier) */
#define __CDS_compiler_version MSVC_VERSION /* NOLINT(bugprone-reserved-identifier) */

/**
* List of features in the c++ standard that Microsoft is too retarded to support
*/

#undef __CDS_Requires
#define __CDS_Requires(_concepts) /* NOLINT(bugprone-reserved-identifier) */

#undef __CDS_cpplang_ConstexprSTLIteratorOp

#if __CDS_cpplang_core_version <=  __CDS_cpplang_core_version_20

#define __CDS_cpplang_ConstexprSTLIteratorOp __CDS_OptimalInline /* NOLINT(bugprone-reserved-identifier) */

#else

#define __CDS_cpplang_ConstexprSTLIteratorOp constexpr /* NOLINT(bugprone-reserved-identifier) */

#endif

#if __CDS_cpplang_core_version <= __CDS_cpplang_core_version_14 

#undef __CDS_MaybeUnused
#define __CDS_MaybeUnused /* NOLINT(bugprone-reserved-identifier) */

#undef __CDS_Deprecated
#define __CDS_Deprecated __CDS_Attribute(deprecated) /* NOLINT(bugprone-reserved-identifier) */

#endif

#undef __CDS_cpplang_NestedInheritedOverride
#define __CDS_cpplang_NestedInheritedOverride /* NOLINT(bugprone-reserved-identifier) */

#undef __CDS_Requires
#define __CDS_Requires(_requirements) /* NOLINT(bugprone-reserved-identifier) */

#endif

#undef __CDS_cpplang_DynamicCastConstexpr
#define __CDS_cpplang_DynamicCastConstexpr /* NOLINT(bugprone-reserved-identifier) */

#endif //CDS_MSVC_HPP
