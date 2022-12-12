/* NOLINT(llvm-header-guard)
 * Created by loghin on 24/10/22.
 */

#ifndef __CDS_THREAD_CTAD_HPP__ /* NOLINT(llvm-header-guard) */
#define __CDS_THREAD_CTAD_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

#if __CDS_cpplang_CTAD_available

namespace cds {

    template < typename __ThreadFunction > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    Runnable ( __ThreadFunction ) -> Runnable < __ThreadFunction >; /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-avoid-non-const-global-variables) */

} /* namespace cds */

#endif

#endif /* __CDS_THREAD_CTAD_HPP__ */
