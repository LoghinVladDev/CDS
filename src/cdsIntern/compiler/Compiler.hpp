//
// Created by loghin on 22/09/2021.
//

#ifndef CDS_COMPILER_HPP
#define CDS_COMPILER_HPP

#include "../../std-types.h"

#define __CDS_compiler_name "Undefined" /* NOLINT(bugprone-reserved-identifier) */
#define __CDS_compiler_version 0 /* NOLINT(bugprone-reserved-identifier) */
#define __CDS_compiler_undefined /* NOLINT(bugprone-reserved-identifier) */

#define __CDS_cpplang_core_version_name "cpp-xx (unknown)" /* NOLINT(bugprone-reserved-identifier) */



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
#define __CDS_DeprecatedHint(...) /* NOLINT(bugprone-reserved-identifier) */
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

#undef __CDS_cpplang_core_version_name
#define __CDS_cpplang_core_version_name "cpp-11" /* NOLINT(bugprone-reserved-identifier) */

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
#undef __CDS_DeprecatedHint

#define __CDS_Deprecated __CDS_Attribute(deprecated) /* NOLINT(bugprone-reserved-identifier) */
#define __CDS_DeprecatedHint(_message) __CDS_Attribute(deprecated(_message)) /* NOLINT(bugprone-reserved-identifier) */

#define __CDS_cpplang_ConstexprNonLiteralReturn constexpr /* NOLINT(bugprone-reserved-identifier) */
#define __CDS_cpplang_NonConstConstexprMemberFunction constexpr /* NOLINT(bugprone-reserved-identifier) */
#define __CDS_cpplang_ConstexprConditioned constexpr /* NOLINT(bugprone-reserved-identifier) */
#define __CDS_cpplang_StructBracesInitialization_available true /* NOLINT(bugprone-reserved-identifier) */
#define __CDS_cpplang_VariableTemplates_available true /* NOLINT(bugprone-reserved-identifier) */

#define __CDS_cpplang_DynamicCastConstexpr constexpr /* NOLINT(bugprone-reserved-identifier) */
#define __CDS_cpplang_ConstexprConstructorNonEmptyBody constexpr /* NOLINT(bugprone-reserved-identifier) */

namespace cds {

    template < typename T, typename U = T >
    constexpr auto forward ( typename std :: remove_reference < T > :: type & value ) noexcept -> T && {
        return std::forward < T > (value);
    }

    template<typename T, typename U = T>
    constexpr auto exchange(T & obj, U && newValue) -> T {
        return std::exchange(obj, newValue);
    }

}

#undef __CDS_cpplang_core_version_name
#define __CDS_cpplang_core_version_name "cpp-14" /* NOLINT(bugprone-reserved-identifier) */

#else

#define __CDS_cpplang_ConstexprNonLiteralReturn __CDS_OptimalInline /* NOLINT(bugprone-reserved-identifier) */
#define __CDS_cpplang_NonConstConstexprMemberFunction __CDS_OptionalInline /* NOLINT(bugprone-reserved-identifier) */
#define __CDS_cpplang_ConstexprConditioned __CDS_OptionalInline /* NOLINT(bugprone-reserved-identifier) */
#define __CDS_cpplang_StructBracesInitialization_available false /* NOLINT(bugprone-reserved-identifier) */
#define __CDS_cpplang_VariableTemplates_available false /* NOLINT(bugprone-reserved-identifier) */

#define __CDS_cpplang_DynamicCastConstexpr __CDS_OptimalInline /* NOLINT(bugprone-reserved-identifier) */
#define __CDS_cpplang_ConstexprConstructorNonEmptyBody __CDS_OptimalInline /* NOLINT(bugprone-reserved-identifier) */

namespace cds {

    template < typename T >
    constexpr auto forward ( typename std :: remove_reference < T > :: type & value ) noexcept -> T && {
        return static_cast < T && > ( value );
    }

    template < typename T, typename U = T >
    inline auto exchange ( T & obj, U && newValue ) -> T {
        T oldValue = std :: move ( obj );
        obj = std :: forward < U > ( std :: forward < U > ( newValue ) );
        return oldValue;
    }

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
#define __CDS_cpplang_InlineStaticVariable_available true /* NOLINT(bugprone-reserved-identifier) */
#define __CDS_cpplang_TemplatePartialSpecNoexceptFunction_available true /* NOLINT(bugprone-reserved-identifier) */
#define __CDS_cpplang_ConstexprMultipleReturn constexpr /* NOLINT(bugprone-reserved-identifier) */

#define __CDS_cpplang_FunctionAliasNoexcept(_exceptSpec) noexcept(_exceptSpec) /* NOLINT(bugprone-reserved-identifier) */

#undef __CDS_cpplang_core_version_name
#define __CDS_cpplang_core_version_name "cpp-17" /* NOLINT(bugprone-reserved-identifier) */

#else

#define __CDS_cpplang_IfConstexpr /* NOLINT(bugprone-reserved-identifier) */
#define __CDS_cpplang_CTAD_available false /* NOLINT(bugprone-reserved-identifier) */
#define __CDS_cpplang_ConstexprLambda /* NOLINT(bugprone-reserved-identifier) */
#define __CDS_cpplang_InlineStaticVariable_available false /* NOLINT(bugprone-reserved-identifier) */
#define __CDS_cpplang_TemplatePartialSpecNoexceptFunction_available false /* NOLINT(bugprone-reserved-identifier) */
#define __CDS_cpplang_ConstexprMultipleReturn __CDS_OptimalInline /* NOLINT(bugprone-reserved-identifier) */

#define __CDS_cpplang_FunctionAliasNoexcept(_exceptSpec) /* NOLINT(bugprone-reserved-identifier) */

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

#define __CDS_cpplang_ConstexprDynamicAllocation constexpr /* NOLINT(bugprone-reserved-identifier) */
#define __CDS_cpplang_ConstexprDestructor constexpr /* NOLINT(bugprone-reserved-identifier) */
#define __CDS_cpplang_Concepts_available true /* NOLINT(bugprone-reserved-identifier) */
#define __CDS_cpplang_VirtualConstexpr constexpr /* NOLINT(bugprone-reserved-identifier) */

#define __CDS_cpplang_ThreeWayComparison_available true /* NOLINT(bugprone-reserved-identifier) */

#define __CDS_cpplang_ConstexprPostfixLiteral constexpr /* NOLINT(bugprone-reserved-identifier) */
#define __CDS_cpplang_ConstexprPlacementNew constexpr /* NOLINT(bugprone-reserved-identifier) */

#define __CDS_Explicit explicit(true) /* NOLINT(bugprone-reserved-identifier) */
#define __CDS_Implicit explicit(false) /* NOLINT(bugprone-reserved-identifier) */

#undef __CDS_cpplang_core_version_name
#define __CDS_cpplang_core_version_name "cpp-20" /* NOLINT(bugprone-reserved-identifier) */

#define __CDS_cpplang_ConstexprOverride constexpr /* NOLINT(bugprone-reserved-identifier) */

#else

#define __CDS_cpplang_ConstexprDynamicAllocation __CDS_OptionalInline /* NOLINT(bugprone-reserved-identifier) */
#define __CDS_cpplang_ConstexprDestructor __CDS_OptimalInline /* NOLINT(bugprone-reserved-identifier) */
#define __CDS_cpplang_VirtualConstexpr __CDS_OptionalInline /* NOLINT(bugprone-reserved-identifier) */
#define __CDS_cpplang_Concepts_available false /* NOLINT(bugprone-reserved-identifier) */

#define __CDS_cpplang_ThreeWayComparison_available false /* NOLINT(bugprone-reserved-identifier) */

#define __CDS_cpplang_ConstexprPostfixLiteral inline /* NOLINT(bugprone-reserved-identifier) */
#define __CDS_cpplang_ConstexprPlacementNew inline /* NOLINT(bugprone-reserved-identifier) */

#define __CDS_Explicit explicit /* NOLINT(bugprone-reserved-identifier) */
#define __CDS_Implicit /* NOLINT(bugprone-reserved-identifier) */

#define __CDS_cpplang_ConstexprOverride __CDS_OptionalInline /* NOLINT(bugprone-reserved-identifier) */

#endif



#define __CDS_cpplang_ConstexprPureAbstract __CDS_cpplang_VirtualConstexpr /* NOLINT(bugprone-reserved-identifier) */
#define __CDS_cpplang_ConstexprSTLIteratorOp __CDS_cpplang_ConstexprConditioned /* NOLINT(bugprone-reserved-identifier) */
#define __CDS_cpplang_NestedInheritedOverride override /* NOLINT(bugprone-reserved-identifier) */


#if defined(__GNUC__) && ! defined(__MINGW64__) && ! defined(__clang__)

#include "gcc.hpp"

#endif

#if defined(__MINGW64__)

#include "MinGW.hpp"

#endif

#if defined(__clang__)

#include "clang.hpp"

#endif

#if defined(_MSC_VER)

#include "MSVC.hpp"

#endif

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace utility {
        __CDS_MaybeUnused static inline auto __CDS_compilerVersionString() noexcept -> StringLiteral { /* NOLINT(bugprone-reserved-identifier) */
            static char buffer[9] = {
                    __CDS_compiler_version / 10000 % 100 / 10 + '0',
                    __CDS_compiler_version / 10000 % 100 % 10 + '0',
                    '.',
                    __CDS_compiler_version / 100 % 100 / 10 + '0',
                    __CDS_compiler_version / 100 % 100 % 10 + '0',
                    '.',
                    __CDS_compiler_version % 100 / 10 + '0',
                    __CDS_compiler_version % 100 % 10 + '0',
                    '\0'
            };

            return buffer;
        }
    }
}

//// UNCOMMENT last condition if compiling MSVC c++latest
#if !defined(__CDS_Requires)
#if __CDS_cpplang_Concepts_available //  && !defined(_MSC_VER) // to remove once MS pulls their head out of their arse

#define __CDS_Requires(...) requires __VA_ARGS__ /* NOLINT(bugprone-reserved-identifier) */

#else

#define __CDS_Requires(...) /* NOLINT(bugprone-reserved-identifier) */

#endif
#endif

#endif //CDS_COMPILER_HPP
