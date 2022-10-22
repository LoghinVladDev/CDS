/*
 * Created by loghin on 23/10/22.
 */

#ifndef __CDS_ATOMIC_CTAD_HPP__ /* NOLINT(llvm-header-guard) */
#define __CDS_ATOMIC_CTAD_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

#if __CDS_cpplang_CTAD_available

namespace cds {

    template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    Atomic ( __ElementType ) -> Atomic < __ElementType >;

} /* namespace cds */

#endif

#endif /* __CDS_ATOMIC_CTAD_HPP__ */
