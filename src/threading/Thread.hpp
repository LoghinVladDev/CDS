//
// Created by loghin on 07.03.2021.
//

#ifndef CDS_THREAD_H
#define CDS_THREAD_H

#include <CDS/Object>
#include <iostream>

#if defined(__linux)
#include <pthread.h>
#endif

class Thread : public Object {
public:
    typedef auto ( * ErrorCallback ) ( String const &, Thread *, std::exception const * ) noexcept -> void;

private:

#if defined(__linux)
    typedef pthread_t PrimitiveThread;

    constexpr static PrimitiveThread PRIMITIVE_NULL_HANDLE = 0llu;
    constexpr static StringLiteral IMPLEMENTATION_TYPE = "POSIX Thread (pthread)";
#else
#error Unsupported : Thread
#endif

    enum State: CDS_uint8 {
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

    PrimitiveThread                     handle         { Thread::PRIMITIVE_NULL_HANDLE };
    State                               state          { Thread::State::CREATED };
    inline static ErrorCallback         pErrorCallback { nullptr };

    virtual auto run () noexcept -> void = 0;

    static auto launcher ( void * pThreadObject ) noexcept -> void * {
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

        return nullptr;
    }

protected:
    Thread () noexcept = default;

public:
    auto start () -> void {

#if defined(__linux)
        pthread_create ( & this->handle, nullptr, Thread::launcher, reinterpret_cast < void * > ( this ) );
#else
#error Unsupported : Thread
#endif

    }

    auto kill () noexcept -> void {

#if defined(__linux)
        pthread_cancel ( this->handle );
#else
#error Unsupported : Thread
#endif

        this->state = State::KILLED;

    }

    auto join () const noexcept -> void {

#if defined(__linux)
        pthread_join( this->handle, nullptr );
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
            .append(static_cast<CDS_uint64>(this->handle)).append(", state = ")
            .append(Thread::stateToString(this->state)).append(" }");
    }
};

#include <functional>

template <class ThreadFunction>
class Runnable : public Thread {
public:

private:
    ThreadFunction function;

    auto run () noexcept -> void override {
        this->function();
    }
public:

    Runnable () noexcept = delete;
    explicit Runnable ( ThreadFunction f ) noexcept : Thread(), function(f) {}
};

#endif //CDS_THREAD_H
