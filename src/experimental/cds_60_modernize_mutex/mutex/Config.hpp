/*
 * Created by loghin on 23/10/22.
 */

#ifndef __CDS_MUTEX_CONFIG_HPP__ /* NOLINT(llvm-header-guard) */
#define __CDS_MUTEX_CONFIG_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

#include "platform/Linux.hpp"
#include "platform/Win32.hpp"

#define __CDS_mutex_minimal_implementation  0U  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
#define __CDS_mutex_full_implementation     1U  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

#if defined(CDS_Threading_Minimal) || defined (CDS_Mutex_Minimal)
#define __CDS_mutex_implementation __CDS_mutex_minimal_implementation   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
#else
#define __CDS_mutex_implementation __CDS_mutex_full_implementation  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
#endif

#endif /* __CDS_MUTEX_CONFIG_HPP__ */
