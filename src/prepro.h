//
// Created by vladl on 3/29/2021.
//

#ifndef CDS_PREPRO_H
#define CDS_PREPRO_H

#include "std-types.h"

# if defined(__GNUC__) && !defined (GCC_VERSION)

# if ! defined(GCC_VERSION)

# define GCC_VERSION ( __GNUC__ * 10000 + __GNUC_MINOR__ * 100 + __GNUC_PATCHLEVEL__ )

# endif

# else

# if ! defined(GCC_VERSION)

# define GCC_VERSION 0

# endif

# endif

#ifdef CDS_DEBUG

#warning CDS Object Debug Enabled

#ifndef debug_private
#define debug_private public
#endif

#else

#ifndef debug_private
#define debug_private private
#endif

#endif

#define __CDS_cpplang_core_version_pre_98 1 /* NOLINT(bugprone-reserved-identifier) */
#define __CDS_cpplang_core_version_98 199711L /* NOLINT(bugprone-reserved-identifier) */
#define __CDS_cpplang_core_version_11 201103L /* NOLINT(bugprone-reserved-identifier) */
#define __CDS_cpplang_core_version_14 201402L /* NOLINT(bugprone-reserved-identifier) */
#define __CDS_cpplang_core_version_17 201703L /* NOLINT(bugprone-reserved-identifier) */
#define __CDS_cpplang_core_version_20 202002L /* NOLINT(bugprone-reserved-identifier) */

#define __CDS_cpplang_core_version __cplusplus /* NOLINT(bugprone-reserved-identifier) */

#define __CDS_Attribute(_attr) [[_attr]] /* NOLINT(bugprone-reserved-identifier) */
#define __CDS_OldAttribute(_attr) __attribute__((_attr)) /* NOLINT(bugprone-reserved-identifier) */

#define __CDS_CarriesDependency /* NOLINT(bugprone-reserved-identifier) */
#define __CDS_Deprecated /* NOLINT(bugprone-reserved-identifier) */
#define __CDS_Fallthrough /* NOLINT(bugprone-reserved-identifier) */
#define __CDS_Likely /* NOLINT(bugprone-reserved-identifier) */
#define __CDS_MaybeUnused /* NOLINT(bugprone-reserved-identifier) */
#define __CDS_NoUniqueAddress /* NOLINT(bugprone-reserved-identifier) */
#define __CDS_NoDiscard /* NOLINT(bugprone-reserved-identifier) */
#define __CDS_NoReturn /* NOLINT(bugprone-reserved-identifier) */
#define __CDS_Unlikely /* NOLINT(bugprone-reserved-identifier) */


#include <utility>

/**
 *
 *
 *
 * CPP-11 Specific
 *
 *
 */
#if __CDS_cpplang_core_version >= __CDS_cpplang_core_version_11

#undef __CDS_CarriesDependency
#undef __CDS_NoReturn
#undef __CDS_MaybeUnused

#define __CDS_CarriesDependency __CDS_Attribute(carries_dependency) /* NOLINT(bugprone-reserved-identifier) */
#define __CDS_NoReturn __CDS_Attribute(noreturn) /* NOLINT(bugprone-reserved-identifier) */
#define __CDS_MaybeUnused __CDS_OldAttribute(unused) /* NOLINT(bugprone-reserved-identifier) */

#else

#endif

/**
 *
 *
 *
 * CPP-14 Specific
 *
 *
 */
#if __CDS_cpplang_core_version >= __CDS_cpplang_core_version_14 /* NOLINT(bugprone-reserved-identifier) */

#undef __CDS_Deprecated

#define __CDS_Deprecated __CDS_Attribute(deprecated) /* NOLINT(bugprone-reserved-identifier) */

#define __CDS_cpplang_NonConstConstexprMemberFunction constexpr /* NOLINT(bugprone-reserved-identifier) */
#define __CDS_cpplang_ConstexprConditioned constexpr /* NOLINT(bugprone-reserved-identifier) */
#define __CDS_cpplang_StructBracesInitialization_available true /* NOLINT(bugprone-reserved-identifier) */
#define __CDS_cpplang_VariableTemplates_available true /* NOLINT(bugprone-reserved-identifier) */

template < typename T, typename U = T >
constexpr auto forward (T & value) noexcept -> T && {
    return std :: forward (value);
}

template < typename T, typename U = T >
constexpr auto exchange ( T & obj, U && newValue ) -> T {
    return std :: exchange (obj, newValue);
}

#else

#define __CDS_cpplang_NonConstConstexprMemberFunction inline /* NOLINT(bugprone-reserved-identifier) */
#define __CDS_cpplang_ConstexprConditioned inline /* NOLINT(bugprone-reserved-identifier) */
#define __CDS_cpplang_StructBracesInitialization_available false /* NOLINT(bugprone-reserved-identifier) */
#define __CDS_cpplang_VariableTemplates_available false /* NOLINT(bugprone-reserved-identifier) */

template < typename T >
constexpr auto forward ( typename std :: remove_reference < T > :: type & value ) noexcept -> T && { return static_cast < T && > ( value ); }

template < typename T, typename U = T >
inline auto exchange ( T & obj, U && newValue ) -> T {
    T oldValue = std :: move ( obj );
    obj = std :: forward < U > ( std :: forward < U > ( newValue ) );
    return oldValue;
}

#endif

/**
 *
 *
 *
 * CPP-17 Specific
 *
 *
 */
#if __CDS_cpplang_core_version >= __CDS_cpplang_core_version_17

#undef __CDS_Fallthrough
#undef __CDS_MaybeUnused
#undef __CDS_NoDiscard

#define __CDS_Fallthrough __CDS_Attribute(fallthrough) /* NOLINT(bugprone-reserved-identifier) */
#define __CDS_MaybeUnused __CDS_Attribute(maybe_unused) /* NOLINT(bugprone-reserved-identifier) */
#define __CDS_NoDiscard __CDS_Attribute(nodiscard) /* NOLINT(bugprone-reserved-identifier) */

#define __CDS_cpplang_IfConstexpr constexpr /* NOLINT(bugprone-reserved-identifier) */
#define __CDS_cpplang_CTAD_available true /* NOLINT(bugprone-reserved-identifier) */
#define __CDS_cpplang_ConstexprLambda constexpr /* NOLINT(bugprone-reserved-identifier) */

#else

#define __CDS_cpplang_IfConstexpr /* NOLINT(bugprone-reserved-identifier) */
#define __CDS_cpplang_CTAD_available false /* NOLINT(bugprone-reserved-identifier) */
#define __CDS_cpplang_ConstexprLambda /* NOLINT(bugprone-reserved-identifier) */

#endif

/**
 *
 *
 *
 * CPP-20 Specific
 *
 *
 */
#if __CDS_cpplang_core_version >= __CDS_cpplang_core_version_20

#undef __CDS_Likely
#undef __CDS_NoUniqueAddress
#undef __CDS_NoDiscard
#undef __CDS_Unlikely

#define __CDS_Likely __CDS_Attribute(likely) /* NOLINT(bugprone-reserved-identifier) */
#define __CDS_NoUniqueAddress __CDS_Attribute(no_unique_address) /* NOLINT(bugprone-reserved-identifier) */
#define __CDS_NoDiscard __CDS_Attribute(nodiscard) /* NOLINT(bugprone-reserved-identifier) */
#define __CDS_Unlikely __CDS_Attribute(unlikely) /* NOLINT(bugprone-reserved-identifier) */

#define __CDS_cpplang_ConstexprDestructor constexpr /* NOLINT(bugprone-reserved-identifier) */
#define __CDS_cpplang_Concepts_available true /* NOLINT(bugprone-reserved-identifier) */
#define __CDS_cpplang_VirtualConstexpr constexpr /* NOLINT(bugprone-reserved-identifier) */

#else

#define __CDS_cpplang_ConstexprDestructor inline /* NOLINT(bugprone-reserved-identifier) */
#define __CDS_cpplang_VirtualConstexpr inline /* NOLINT(bugprone-reserved-identifier) */
#define __CDS_cpplang_Concepts_available false /* NOLINT(bugprone-reserved-identifier) */

#endif




#if !defined(__CDS_Requires)
#if defined(__cpp_concepts)

#define __CDS_Requires(_concepts) requires _concepts /* NOLINT(bugprone-reserved-identifier) */

#else

#define __CDS_Requires(_concepts) /* NOLINT(bugprone-reserved-identifier) */

#endif
#endif


#endif //CDS_PREPRO_H
