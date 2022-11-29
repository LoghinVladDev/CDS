/* NOLINT(llvm-header-guard)
 * Created by loghin on 23/10/22.
 */

#if defined(__linux)
#ifndef __CDS_MUTEX_LINUX_HPP__ /* NOLINT(llvm-header-guard) */
#define __CDS_MUTEX_LINUX_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

#include <pthread.h>

namespace cds {             /* NOLINT(modernize-concat-nested-namespaces) */
    namespace __hidden {    /* NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        namespace __impl {  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            using __MutexPlatformHandleType = pthread_mutex_t;   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            inline auto __mutexPlatformInit (    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __MutexPlatformHandleType * pMutexHandle
            ) noexcept -> void {

                (void) pthread_mutex_init ( pMutexHandle, nullptr );
            }


            inline auto __mutexPlatformDestroy (    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __MutexPlatformHandleType * pMutexHandle
            ) noexcept -> void {

                (void) pthread_mutex_destroy ( pMutexHandle );
            }


            inline auto __mutexPlatformLock (    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __MutexPlatformHandleType * pMutexHandle
            ) noexcept -> void {

                (void) pthread_mutex_lock ( pMutexHandle );
            }


            inline auto __mutexPlatformUnlock (    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __MutexPlatformHandleType * pMutexHandle
            ) noexcept -> void {

                (void) pthread_mutex_unlock ( pMutexHandle );
            }


            inline auto __mutexPlatformTryLock (    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __MutexPlatformHandleType * pMutexHandle
            ) noexcept -> bool {

                return pthread_mutex_trylock ( pMutexHandle ) == 0;
            }

        } /* namespace __impl */
    } /* namespace __hidden */
} /* namespace cds */

#endif /* __CDS_MUTEX_LINUX_HPP__ */
#endif
