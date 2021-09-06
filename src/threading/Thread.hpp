//
// Created by loghin on 07.03.2021.
//

#ifndef CDS_THREAD_H
#define CDS_THREAD_H

#include <CDS/Object>
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

class Thread : public Object {
public:
    inline static auto hardwareConcurrency () noexcept -> Size {
#if defined(WIN32)
        SYSTEM_INFO systemInformation;
        GetSystemInfo ( & systemInformation );
        return static_cast < Size > ( systemInformation.dwNumberOfProcessors );
#elif defined(__linux)
        return static_cast < Size > ( sysconf ( _SC_NPROCESSORS_ONLN ) );
#else
#error Thread not supported
#endif
        return 0;
    }

    typedef auto ( * ErrorCallback ) ( String const &, Thread *, std::exception const * ) noexcept -> void;

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
        CREATED                 = 0x01u,
        RUNNING                 = 0x02u,
        FINISHED                = 0x04u,
        KILLED                  = 0x08u,
        EXCEPTION_TERMINATED    = 0x16u
    };

    constexpr static auto stateToString ( State s ) noexcept -> StringLiteral {
        switch ( s ) {
            case State::CREATED:                return "Not Started";
            case State::RUNNING:                return "Running";
            case State::FINISHED:               return "Finished Execution";
            case State::KILLED:                 return "Killed Externally";
            case State::EXCEPTION_TERMINATED:   return "Terminated by Exception inside Thread";
        }

        return "Undefined State";
    }

    PrimitiveThread        MUTABLE_SPEC handle         { Thread::PRIMITIVE_NULL_HANDLE };
    State                               state          { Thread::State::CREATED };
    inline static ErrorCallback         pErrorCallback { nullptr };

    virtual auto run () noexcept (false) -> void = 0;

    static auto launcher ( void * pThreadObject ) noexcept -> THREAD_RETURN_TYPE {
        auto pThread = reinterpret_cast < Thread * > ( pThreadObject );

        try {
            pThread->state = State::RUNNING;
            pThread->run();
            pThread->state = State::FINISHED;
        } catch ( std::exception const & e ) {
            pThread->state = State::EXCEPTION_TERMINATED;

            if ( Thread::pErrorCallback != nullptr )
                Thread::pErrorCallback( "Exception caught in Thread runtime", pThread, & e );
            else
                std::cerr << "Exception caught in Thread runtime : " << e.what() << '\n';
        }

        return THREAD_RETURN_OK;
    }

protected:
    Thread () noexcept = default;

public:
    auto start () noexcept(THREAD_EXCEPT_STAT) -> void {

#if defined(__linux)
        pthread_create ( & this->handle, nullptr, Thread::launcher, reinterpret_cast < void * > ( this ) );
#elif defined(WIN32)
        this->handle = new Thread_t;
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
        pthread_cancel ( this->handle );
#elif defined(WIN32)
        if ( this->handle != PRIMITIVE_NULL_HANDLE )
            TerminateThread( this->handle->handle, 0 );
        delete this->handle;
        this->handle = PRIMITIVE_NULL_HANDLE;
#else
#error Unsupported : Thread
#endif

        this->state = State::KILLED;

    }

    auto join () const noexcept -> void {

#if defined(__linux)
        pthread_join( this->handle, nullptr );
#elif defined(WIN32)
        if ( this->handle != PRIMITIVE_NULL_HANDLE )
            WaitForSingleObject( this->handle->handle, INFINITE );
        delete this->handle;
        this->handle = PRIMITIVE_NULL_HANDLE;
#else
#error Unsupported : Thread
#endif

    }

    ~Thread () noexcept override {
        this->kill();
    }

    [[nodiscard]] auto toString() const noexcept -> String override {
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

#include <functional>
#include <tuple>

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
    explicit Runnable ( ThreadFunction f ) noexcept : Thread(), function(f) {}
};

#undef THREAD_RETURN_TYPE
#undef THREAD_RETURN_OK
#undef THREAD_EXCEPT_STAT
#undef MUTABLE_SPEC

#endif //CDS_THREAD_H
