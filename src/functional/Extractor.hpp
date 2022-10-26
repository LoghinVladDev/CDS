/*
 * Created by loghin on 6/22/22.
 */

#ifndef __CDS_EXTRACTOR_HPP__ /* NOLINT(llvm-header-guard) */
#define __CDS_EXTRACTOR_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

#include <CDS/Compiler>        /* NOLINT(llvm-include-order) */
#include <CDS/FunctionalInterface>

namespace cds {

    namespace utility {

        template < typename __BaseType, typename __ExtractedType > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        using ExtractorFunction __CDS_DeprecatedHint("Use Standard Functional Interfaces instead of fixed Interface") = /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-avoid-non-const-global-variables) */
                functional :: MapperFunction < __ExtractedType const &, __BaseType const & >;

    } /* namespace utility */

    template <
            typename                                                            __BaseType,          /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename                                                            __ExtractedType,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            cds :: utility :: ExtractorFunction < __BaseType, __ExtractedType > __extractor          /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    > using FunctionExtractor __CDS_DeprecatedHint("Use Standard Functional Interface Decorator instead of fixed Interface") =   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-avoid-non-const-global-variables) */
            functional :: DecoratedMapper < decltype ( & __extractor ), __extractor >;

} /* namespace cds */

#endif /* __CDS_EXTRACTOR_HPP__ */
