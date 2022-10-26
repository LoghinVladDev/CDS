/*
 * Created by loghin on 23/10/22.
 */

#ifndef __CDS_ATOMIC_CONFIG_HPP__ /* NOLINT(llvm-header-guard) */
#define __CDS_ATOMIC_CONFIG_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

#define __CDS_atomic_flag_stl_atomic_flag_implementation    0U  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
#define __CDS_atomic_flag_stl_atomic_implementation         1U  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

#if __CDS_cpplang_core_version >= __CDS_cpplang_core_version_20
#define __CDS_atomic_flag_implementation __CDS_atomic_flag_stl_atomic_flag_implementation   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
#else
#define __CDS_atomic_flag_implementation __CDS_atomic_flag_stl_atomic_implementation        /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
#endif


#define __CDS_atomic_ref_stl_atomic_ref_implementation      0U /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
#define __CDS_atomic_ref_unavailable                        1U /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

#if __CDS_cpplang_core_version >= __CDS_cpplang_core_version_20
#define __CDS_atomic_ref_implementation __CDS_atomic_ref_stl_atomic_ref_implementation   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
#else
#define __CDS_atomic_ref_implementation __CDS_atomic_ref_unavailable        /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
#endif

#endif /* __CDS_ATOMIC_CONFIG_HPP__ */
