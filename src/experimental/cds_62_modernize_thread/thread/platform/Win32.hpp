/*
 * Created by loghin on 24/10/22.
 */

#if defined(WIN32)
#ifndef __CDS_THREAD_WIN32_HPP__ /* NOLINT(llvm-header-guard) */
#define __CDS_THREAD_WIN32_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

#include <windows.h>

namespace cds {             /* NOLINT(modernize-concat-nested-namespaces) */
    namespace __hidden {    /* NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        namespace __impl {  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            struct __ThreadPlatformHandleType { /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                HANDLE  _handle;
                DWORD   _threadId;
                DWORD   _accessFlags;
                LPVOID  _threadSharedData;
            };

            using __ThreadPlatformIdType        = DWORD;   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            template < typename __ThreadLaunchFunction >    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            inline auto __threadPlatformLaunch (            /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __ThreadPlatformHandleType * pHandle,
                    __ThreadLaunchFunction       pFunction,
                    void                       * pArgument
            ) noexcept -> void {

                pHandle->_handle = CreateThread (
                        nullptr,
                        0,
                        pFunction,
                        pArgument,
                        0,
                        & pHandle->_threadId
                );

                pHandle->_accessFlags = THREAD_ALL_ACCESS;
            }


            inline auto __threadPlatformHardwareConcurrency () noexcept -> Size {   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

                SYSTEM_INFO systemInformation;
                GetSystemInfo ( & systemInformation );
                return static_cast < Size > ( systemInformation.dwNumberOfProcessors );
            }


            inline auto __threadPlatformCurrentId () noexcept -> __ThreadPlatformIdType {   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

                return GetCurrentThreadId();
            }


            inline auto __threadPlatformKill (    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __ThreadPlatformHandleType const * pThreadHandle
            ) noexcept -> void {

                TerminateThread ( pThreadHandle->_handle, 0 );
            }


            inline auto __threadPlatformJoin (    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __ThreadPlatformHandleType const * pThreadHandle
            ) noexcept -> void {

                WaitForSingleObject ( pThreadHandle->_handle, INFINITE );
            }


            inline auto __threadPlatformDetach (    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __ThreadPlatformHandleType const * pThreadHandle
            ) noexcept -> void {

                CloseHandle ( pThreadHandle->_handle );
            }


            inline auto __threadPlatformSleep (    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    uint64 milliseconds
            ) noexcept -> void {

                Sleep ( milliseconds );
            }

        } /* namespace __impl */
    } /* namespace __hidden */
} /* namespace cds */

#endif /* __CDS_THREAD_WIN32_HPP__ */
#endif
