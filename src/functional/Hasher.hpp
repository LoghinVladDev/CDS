/*
 * Created by loghin on 10.11.2021.
 */

#ifndef __CDS_HASHER_HPP__ /* NOLINT(llvm-header-guard) */
#define __CDS_HASHER_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

#include <CDS/Compiler>        /* NOLINT(llvm-include-order) */
#include <CDS/FunctionalInterface>
#include "../primitive/baseTypes/object/impl/HashBase.hpp"

namespace cds {

    namespace utility {

        template < typename __Type > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        using HashFunction __CDS_DeprecatedHint("Use Standard Functional Interfaces instead of fixed Interface") =   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-avoid-non-const-global-variables) */
                functional :: MapperFunction < Size, __Type const & >;

    } /* namespace utility */

    template < typename __Type, utility :: HashFunction < __Type > __hashFunction > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    using FunctionHasher __CDS_DeprecatedHint("Use Standard Functional Interface Decorator instead of fixed Interface") =  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-avoid-non-const-global-variables) */
            functional :: DecoratedMapper < decltype ( __hashFunction ), __hashFunction >;

} /* namespace cds */

#endif /* __CDS_HASHER_HPP__ */
