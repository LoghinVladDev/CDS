/*
 * Created by loghin on 6/22/22.
 */

#ifndef __CDS_COPY_CONSTRUCTOR_HPP__ /* NOLINT(llvm-header-guard) */
#define __CDS_COPY_CONSTRUCTOR_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

#include <CDS/Compiler>        /* NOLINT(llvm-include-order) */
#include <CDS/FunctionalInterface>

namespace cds {

    namespace utility {

        template < typename __Type > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        using CopyConstructorFunction __CDS_DeprecatedHint("Use Standard Functional Interfaces instead of fixed Interface") =   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-avoid-non-const-global-variables) */
                functional :: ConsumerFunction < __Type &, __Type const & >;

    } /* namespace utility */

    template < typename __Type, utility :: CopyConstructorFunction < __Type > __copyConstructor > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    using FunctionCopyConstructor __CDS_DeprecatedHint("Use Standard Functional Interface Decorator instead of fixed Interface") =  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-avoid-non-const-global-variables) */
            functional :: DecoratedConsumer < decltype ( __copyConstructor ), __copyConstructor >;

} /* namespace cds */

#endif /* __CDS_COPY_CONSTRUCTOR_HPP__ */
