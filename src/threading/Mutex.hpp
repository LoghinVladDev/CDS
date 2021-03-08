//
// Created by loghin on 08.03.2021.
//

#ifndef CDS_MUTEX_HPP
#define CDS_MUTEX_HPP

#include <CDS/Object>

#if defined(__linux)
#include <pthread.h>
#endif

class Mutex : public Object {
private:

#if defined(__linux)
    typedef pthread_mutex_t PrimitiveMutex;

    constexpr static StringLiteral IMPLEMENTATION_TYPE = "POSIX Mutex (pthread)";
#else
#error Unsupported : Mutex
#endif

    enum State: CDS_uint8 {
        LOCKED = 0x01,
        UNLOCKED = 0x02
    };

    constexpr static auto stateToString ( State s ) noexcept -> StringLiteral {
        switch (s) {
            case LOCKED:    return "Locked";
            case UNLOCKED:  return "Unlocked";
        }

        return "Undefined State";
    }

    PrimitiveMutex  handle;
    State           state;

public:
    Mutex () noexcept : state(UNLOCKED) { // NOLINT(cppcoreguidelines-pro-type-member-init)

#if defined(__linux)
        pthread_mutex_init( & this->handle, nullptr );
#else
#error Unsupported : Mutex
#endif

    }

    auto lock () noexcept -> void {

#if defined(__linux)
        pthread_mutex_lock( & this->handle );
#else
#error Unsupported : Mutex
#endif

        this->state = LOCKED;

    }

    auto tryLock () noexcept -> bool {

#if defined(__linux)
        auto lockSuccess = pthread_mutex_trylock(& this->handle ) == 0;
        if ( lockSuccess ) this->state = LOCKED;
        return lockSuccess;
#else
#error Unsupported : Mutex
#endif

    }

    auto unlock () noexcept -> void {

#if defined(__linux)
        pthread_mutex_unlock( & this->handle );
        this->state = UNLOCKED;
#else
#error Unsupported : Mutex
#endif

    }

    ~Mutex () noexcept override {

#if defined(__linux)
        pthread_mutex_destroy( & this->handle );
#else
#error Unsupported : Mutex
#endif

    }

    auto toString() const noexcept -> String override {
        return String()
            .append("Mutex { <").append(Mutex::IMPLEMENTATION_TYPE).append(">; state = ")
            .append(Mutex::stateToString(this->state)).append(" }");
    }
};

#include <condition_variable>

#endif //CDS_MUTEX_HPP
