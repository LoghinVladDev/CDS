//
// Created by loghin on 07.03.2021.
//

#ifndef CDS_THREAD_H
#define CDS_THREAD_H

#include <CDS/Object>
#include <CDS/Atomic>
#include <CDS/Memory>
#include <iostream>

#if defined(__linux)
#include <pthread.h>
#include <unistd.h>
#define THREAD_RETURN_TYPE void *
#define THREAD_RETURN_OK nullptr
#define THREAD_EXCEPT_STAT true
#elif defined(WIN32)
#include <windows.h>
#define THREAD_RETURN_TYPE DWORD
#define THREAD_RETURN_OK 0
#define THREAD_EXCEPT_STAT false
#else
#endif

namespace cds {

    class Thread : public Object {
    public:
        __CDS_OptimalInline static auto hardwareConcurrency () noexcept -> Size {
    #if defined(WIN32)
            SYSTEM_INFO systemInformation;
            GetSystemInfo ( & systemInformation );
            return static_cast < Size > ( systemInformation.dwNumberOfProcessors );
    #elif defined(__linux)
            return static_cast < Size > ( sysconf ( _SC_NPROCESSORS_ONLN ) );
    #else
    #error Thread not supported
            return 0;
    #endif
        }

        using ErrorCallback = auto ( * ) ( String const &, Thread *, std::exception const * ) __CDS_cpplang_FunctionAliasNoexcept(false) -> void;

    private:

    #if defined(__linux)
        typedef pthread_t PrimitiveThread;

        constexpr static PrimitiveThread PRIMITIVE_NULL_HANDLE = 0llu;
        constexpr static StringLiteral IMPLEMENTATION_TYPE = "POSIX Thread (pthread)";

    #define MUTABLE_SPEC

    #elif defined(WIN32)
        typedef struct {
            HANDLE  handle;
            DWORD   threadID;
            DWORD   accessFlags;
            LPVOID  threadSharedData;
        } Thread_t;

        typedef Thread_t * PrimitiveThread;

        constexpr static PrimitiveThread PRIMITIVE_NULL_HANDLE = nullptr;
        constexpr static StringLiteral IMPLEMENTATION_TYPE = "WINAPI Thread (windows)";

    #define MUTABLE_SPEC mutable

    #else
    #error Unsupported : Thread
    #endif

        enum State: uint8 {
            CREATED                 = 0x01U,
            RUNNING                 = 0x02U,
            FINISHED                = 0x04U,
            KILLED                  = 0x08U,
            EXCEPTION_TERMINATED    = 0x10U
        };

        __CDS_WarningSuppression_UseScopedEnum_SuppressEnable

        __CDS_cpplang_ConstexprConditioned static auto stateToString ( State state ) noexcept -> StringLiteral {
            switch ( state ) {
                case State::CREATED:                return "Not Started"; // NOLINT(clion-misra-cpp2008-6-4-5)
                case State::RUNNING:                return "Running"; // NOLINT(clion-misra-cpp2008-6-4-5)
                case State::FINISHED:               return "Finished Execution"; // NOLINT(clion-misra-cpp2008-6-4-5)
                case State::KILLED:                 return "Killed Externally"; // NOLINT(clion-misra-cpp2008-6-4-5)
                case State::EXCEPTION_TERMINATED:   return "Terminated by Exception inside Thread"; // NOLINT(clion-misra-cpp2008-6-4-5)
            }

            return "Undefined State";
        }

        __CDS_WarningSuppression_UseScopedEnum_SuppressDisable

        PrimitiveThread        MUTABLE_SPEC handle         { Thread::PRIMITIVE_NULL_HANDLE };
        Atomic < State >                    state          { Thread::State::CREATED };

    #if __CDS_cpplang_InlineStaticVariable_available == true

        inline static ErrorCallback         pErrorCallback { nullptr };

    #else

        ErrorCallback                       pErrorCallback { nullptr };

    #endif

        virtual auto run () noexcept (false) -> void = 0;

        static auto launcher ( void * pThreadObject ) noexcept -> THREAD_RETURN_TYPE {
            auto pThread = reinterpret_cast < Thread * > ( pThreadObject );

            try {
                pThread->state = State::RUNNING;
                pThread->run();
                pThread->state = State::FINISHED;
            } catch ( std::exception const & e ) {
                pThread->state = State::EXCEPTION_TERMINATED;

    #if __CDS_cpplang_InlineStaticVariable_available == true

                if ( Thread::pErrorCallback != nullptr ) {
                    Thread::pErrorCallback("Exception caught in Thread runtime", pThread, &e);
                }

    #else

                if ( pThread->pErrorCallback != nullptr )
                    pThread->pErrorCallback( "Exception caught in Thread runtime", pThread, & e );

    #endif

                else {
                    std::cerr << "Exception caught in Thread runtime : " << e.what() << '\n';
                }
            }

            return THREAD_RETURN_OK;
        }

    protected:
        Thread () noexcept = default;

    public:
        auto start () noexcept(THREAD_EXCEPT_STAT) -> void {

    #if defined(__linux)
            (void) pthread_create ( & this->handle, nullptr, & Thread::launcher, reinterpret_cast < void * > ( this ) );
    #elif defined(WIN32)
            this->handle = Memory :: instance().create < Thread_t > ();
            memset ( this->handle, 0, sizeof ( Thread_t ) );

            this->handle->handle = CreateThread (
                nullptr,
                0,
                Thread::launcher,
                this,
                0,
                & this->handle->threadID
            );

            if ( this->handle == PRIMITIVE_NULL_HANDLE )
                throw std::runtime_error ("Could not start thread execution");

            this->handle->accessFlags = THREAD_ALL_ACCESS;
    #else
    #error Unsupported : Thread
    #endif

        }

        auto kill () noexcept -> void {

    #if defined(__linux)
            (void) pthread_cancel ( this->handle );
    #elif defined(WIN32)
            if ( this->handle != PRIMITIVE_NULL_HANDLE )

                __CDS_WarningSuppression_ThreadForceTermination_SuppressEnable

                TerminateThread( this->handle->handle, 0 );

                __CDS_WarningSuppression_ThreadForceTermination_SuppressDisable

            Memory :: instance().destroy ( this->handle );
            this->handle = PRIMITIVE_NULL_HANDLE;
    #else
    #error Unsupported : Thread
    #endif

            this->state = State::KILLED;

        }

        auto join () const noexcept -> void {

    #if defined(__linux)
            (void) pthread_join( this->handle, nullptr );
    #elif defined(WIN32)
            if ( this->handle != PRIMITIVE_NULL_HANDLE )
                WaitForSingleObject( this->handle->handle, INFINITE );
            Memory :: instance().destroy ( this->handle );
            this->handle = PRIMITIVE_NULL_HANDLE;
    #else
    #error Unsupported : Thread
    #endif

        }

        ~Thread () noexcept override {
            auto stateValue = this->state.get();

            if (
                stateValue != Thread::State::FINISHED &&
                stateValue != Thread::State::KILLED &&
                stateValue != Thread::State::EXCEPTION_TERMINATED
            ) {
                this->kill();
            }
        }

        __CDS_NoDiscard auto toString() const noexcept -> String override {
            return String()
                .append("Thread { <").append(Thread::IMPLEMENTATION_TYPE).append(">; handle = ")
                .append(
    #if defined(__linux)
                        static_cast<uint64>(this->handle)
    #elif defined(WIN32)
                        static_cast<uint64>(this->handle == PRIMITIVE_NULL_HANDLE ? 0 : this->handle->threadID)
    #else
    #error Unsupported : Thread
    0
    #endif
                ).append(", state = ")
                .append(Thread::stateToString(this->state)).append(" }");
        }
    };

}

#include <functional>
#include <tuple>

namespace cds {

    template <class ThreadFunction>
    class Runnable : public Thread {
    public:

    private:
        ThreadFunction          function;

        auto run () noexcept (false) -> void override {
            this->function();
        }
    public:

        Runnable () noexcept = delete;
        explicit Runnable ( ThreadFunction threadFunction ) noexcept : Thread(), function(threadFunction) {}
    };

}

#undef THREAD_RETURN_TYPE
#undef THREAD_RETURN_OK
#undef THREAD_EXCEPT_STAT
#undef MUTABLE_SPEC

__CDS_RegisterParseType(Thread) // NOLINT(clion-misra-cpp2008-8-0-1)
__CDS_RegisterParseTypeTemplateT(Runnable) // NOLINT(clion-misra-cpp2008-8-0-1)

#endif //CDS_THREAD_H
