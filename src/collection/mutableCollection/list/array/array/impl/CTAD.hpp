/* NOLINT(llvm-header-guard)
 * Created by loghin on 6/3/22.
 */

#ifndef __CDS_ARRAY_CTAD_HPP__ /* NOLINT(llvm-header-guard) */
#define __CDS_ARRAY_CTAD_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

#if __CDS_cpplang_CTAD_available

namespace cds { /* NOLINT(modernize-concat-nested-namespaces) */

    template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    Array (
            std :: initializer_list < __ElementType >
    ) -> Array < __ElementType >;

} /* namespace cds */

#endif

#endif /* __CDS_ARRAY_CTAD_HPP__ */
