/*
 * Created by loghin on 6/22/22.
 */

#ifndef __CDS_DESTRUCTOR_HPP__ /* NOLINT(llvm-header-guard) */
#define __CDS_DESTRUCTOR_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

#include <CDS/Compiler>        /* NOLINT(llvm-include-order) */
#include <CDS/FunctionalInterface>

namespace cds {

    namespace utility {

        template < typename __Type > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        using DestructorFunction __CDS_DeprecatedHint("Use Standard Functional Interfaces instead of fixed Interface") =    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-avoid-non-const-global-variables) */
                functional :: ConsumerFunction < __Type & >;

    } /* namespace utility */

    template < typename __Type, utility :: DestructorFunction < __Type > __destructor > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    using FunctionDestructor __CDS_DeprecatedHint("Use Standard Functional Interface Decorator instead of fixed Interface") =   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-avoid-non-const-global-variables) */
            functional :: DecoratedConsumer < decltype ( & __destructor ), __destructor >;

} /* namespace cds */

#endif /* __CDS_DESTRUCTOR_HPP__ */
