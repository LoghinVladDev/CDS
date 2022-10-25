/*
 * Created by loghin on 24/10/22.
 */

#if defined (__linux)
#ifndef __CDS_THREAD_LINUX_HPP__ /* NOLINT(llvm-header-guard) */
#define __CDS_THREAD_LINUX_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

#include <pthread.h>

namespace cds {             /* NOLINT(modernize-concat-nested-namespaces) */
    namespace __hidden {    /* NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        namespace __impl {  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            using __ThreadPlatformHandleType            = pthread_t;   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            using __ThreadPlatformIdType                = pthread_t;   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            using __ThreadPlatformFunctionReturnType    = void *;      /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            constexpr __ThreadPlatformFunctionReturnType const __threadPlatformFunctionReturn = nullptr;  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            template < typename __ThreadLaunchFunction >    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            inline auto __threadPlatformLaunch (            /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __ThreadPlatformHandleType * pHandle,
                    __ThreadLaunchFunction       pFunction,
                    void                       * pArgument
            ) noexcept -> void {

                (void) pthread_create ( pHandle, nullptr, pFunction, pArgument );
            }


            inline auto __threadPlatformHardwareConcurrency () noexcept -> Size {   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

                return static_cast < Size > ( sysconf ( _SC_NPROCESSORS_ONLN ) );
            }


            inline auto __threadPlatformCurrentId () noexcept -> __ThreadPlatformIdType {   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

                return pthread_self();
            }


            inline auto __threadPlatformKill (    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __ThreadPlatformHandleType * pThreadHandle
            ) noexcept -> void {

                if ( * pThreadHandle != 0ULL ) {
                    pthread_cancel ( * pThreadHandle );
                    * pThreadHandle = 0ULL;
                }
            }


            inline auto __threadPlatformJoin (    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __ThreadPlatformHandleType * pThreadHandle
            ) noexcept -> void {

                if ( * pThreadHandle != 0ULL ) {
                    pthread_join ( * pThreadHandle, nullptr );
                    * pThreadHandle = 0ULL;
                }
            }


            inline auto __threadPlatformDetach (    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __ThreadPlatformHandleType * pThreadHandle
            ) noexcept -> void {

                if ( * pThreadHandle != 0ULL ) {
                    pthread_detach ( * pThreadHandle );
                    * pThreadHandle = 0ULL;
                }
            }


            inline auto __threadPlatformSleep (    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    uint64 milliseconds
            ) noexcept -> void {

                constexpr uint32 const toSecondsStep = 1000U;           /* NOLINT(cppcoreguidelines-init-variables) */
                constexpr uint32 const toNanoSecondsStep = 1000000U;    /* NOLINT(cppcoreguidelines-init-variables) */

                timespec timeSpecification {};
                timeSpecification.tv_sec    = static_cast < time_t > ( milliseconds / toSecondsStep );
                timeSpecification.tv_nsec   = ( ( milliseconds % toSecondsStep ) * toNanoSecondsStep );
                (void) nanosleep ( & timeSpecification, & timeSpecification );
            }

        } /* namespace __impl */
    } /* namespace __hidden */
} /* namespace cds */

#endif /* __CDS_THREAD_LINUX_HPP__ */
#endif
