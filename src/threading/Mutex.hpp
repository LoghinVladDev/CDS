//
// Created by loghin on 08.03.2021.
//

#ifndef CDS_MUTEX_HPP
#define CDS_MUTEX_HPP

#include <CDS/Object>

#if defined(WIN32)

#if defined(MUTEX_IMPLEMENTATION_WINAPI_CRITICAL_SECTION) && defined(MUTEX_IMPLEMENTATION_WINAPI_MUTEX)
#error Only one Implementation for Mutex from WINAPI can be chosen
#endif

#if !defined(MUTEX_IMPLEMENTATION_WINAPI_CRITICAL_SECTION) && !defined(MUTEX_IMPLEMENTATION_WINAPI_MUTEX)
#define MUTEX_IMPLEMENTATION_WINAPI_CRITICAL_SECTION
#define IN_PLACE
#endif

#elif defined(__linux)

#if defined(MUTEX_IMPLEMENTATION_WINAPI_CRITICAL_SECTION) || defined(MUTEX_IMPLEMENTATION_WINAPI_MUTEX)
#error Linux does not support WINAPI calls
#endif

#endif

#if defined(__linux)
#include <pthread.h>
#elif defined(WIN32)
#include <windows.h>
#else
#endif

class Mutex : public Object {
private:

#if defined(__linux)
    typedef pthread_mutex_t PrimitiveMutex;

    constexpr static StringLiteral IMPLEMENTATION_TYPE = "POSIX Mutex (pthread)";
#elif defined(WIN32)
#if defined(MUTEX_IMPLEMENTATION_WINAPI_CRITICAL_SECTION)
    typedef CRITICAL_SECTION PrimitiveMutex;

    constexpr static StringLiteral IMPLEMENTATION_TYPE = "WINAPI Critical Sections (windows)";
#elif defined(MUTEX_IMPLEMENTATION_WINAPI_MUTEX)
    typedef struct {
        HANDLE                  handle;
        LPSECURITY_ATTRIBUTES   pSecurityAttributes;
    } PrimitiveMutex;

    constexpr static StringLiteral IMPLEMENTATION_TYPE = "WINAPI Anonymous/Named Mutex (windows)";
#endif
#else
#error Unsupported : Mutex
#endif

    enum class State: uint8 {
        LOCKED = 0x01,
        UNLOCKED = 0x02
    };

    __CDS_cpplang_ConstexprConditioned static auto stateToString ( State s ) noexcept -> StringLiteral {
        switch (s) {
            case State::LOCKED:    return "Locked";
            case State::UNLOCKED:  return "Unlocked";
        }

        return "Undefined State";
    }

    PrimitiveMutex  handle;
    State           state;

public:

#if defined(MUTEX_IMPLEMENTATION_WINAPI_MUTEX)
#define CTR_PARAM TCHAR const * pMutexName = nullptr, LPSECURITY_ATTRIBUTES pAttributes = nullptr
#else
#define CTR_PARAM
#endif

    Mutex (CTR_PARAM) noexcept : state(State::UNLOCKED) { // NOLINT(cppcoreguidelines-pro-type-member-init)

#if defined(__linux)
        pthread_mutex_init( & this->handle, nullptr );
#elif defined(WIN32)
#if defined(MUTEX_IMPLEMENTATION_WINAPI_CRITICAL_SECTION)
        InitializeCriticalSection( & this->handle );
#elif defined(MUTEX_IMPLEMENTATION_WINAPI_MUTEX)
        this->handle.handle = CreateMutex ( pAttributes, FALSE, pMutexName );
#endif
#else
#error Unsupported : Mutex
#endif

    }

    ~Mutex () noexcept override {

#if defined(__linux)
        pthread_mutex_destroy( & this->handle );
#elif defined(WIN32)
#if defined(MUTEX_IMPLEMENTATION_WINAPI_CRITICAL_SECTION)
        DeleteCriticalSection( & this->handle );
#elif defined(MUTEX_IMPLEMENTATION_WINAPI_MUTEX)
        CloseHandle(this->handle.handle);
#endif
#else
#error Unsupported : Mutex
#endif

    }

    auto reset (CTR_PARAM) noexcept -> void {
#if defined(__linux)
        pthread_mutex_destroy( & this->handle );
        pthread_mutex_init( & this->handle, nullptr );
#elif defined(WIN32)
#if defined(MUTEX_IMPLEMENTATION_WINAPI_CRITICAL_SECTION)
        DeleteCriticalSection( & this->handle );
        InitializeCriticalSection( & this->handle );
#elif defined(MUTEX_IMPLEMENTATION_WINAPI_MUTEX)
        CloseHandle(this->handle.handle);
        this->handle.handle = CreateMutex ( pAttributes, FALSE, pMutexName );
#endif
#else
#error Unsupported : Mutex
#endif

    }

#undef CTR_PARAM

#if defined(MUTEX_IMPLEMENTATION_WINAPI_MUTEX)
#define LOCK_EXCEPT_SPEC false
#else
#define LOCK_EXCEPT_SPEC true
#endif

    auto lock () noexcept (LOCK_EXCEPT_SPEC) -> void {

#if defined(__linux)
        pthread_mutex_lock( & this->handle );
#elif defined(WIN32)
#if defined(MUTEX_IMPLEMENTATION_WINAPI_CRITICAL_SECTION)
        EnterCriticalSection( & this->handle );
#elif defined(MUTEX_IMPLEMENTATION_WINAPI_MUTEX)
        auto result = WaitForSingleObject( this->handle.handle, INFINITE );

        if ( result == WAIT_ABANDONED )
            throw std::runtime_error ("Mutex Abandoned");
#endif
#else
#error Unsupported : Mutex
#endif

        this->state = State::LOCKED;

    }

    auto tryLock () noexcept(LOCK_EXCEPT_SPEC) -> bool {

#if defined(__linux)
        auto lockSuccess = pthread_mutex_trylock(& this->handle ) == 0;
        if ( lockSuccess ) this->state = State::LOCKED;
        return lockSuccess;
#elif defined(WIN32)
#if defined(MUTEX_IMPLEMENTATION_WINAPI_CRITICAL_SECTION)
        auto lockSuccess = TryEnterCriticalSection( & this->handle ) != 0;
        if ( lockSuccess ) this->state = State::LOCKED;
        return lockSuccess;
#elif defined(MUTEX_IMPLEMENTATION_WINAPI_MUTEX)
        auto lockStatus = WaitForSingleObject( this->handle.handle, 0 );
        if ( lockStatus == WAIT_OBJECT_0 ) {
            this->state = State::LOCKED;
            return true;
        } else if ( lockStatus == WAIT_ABANDONED )
            throw std::runtime_error("Mutex Abandoned");
        return false;
#endif
#else
#error Unsupported : Mutex
#endif

    }

#undef LOCK_EXCEPT_SPEC

    auto unlock () noexcept -> void {

#if defined(__linux)
        pthread_mutex_unlock( & this->handle );
#elif defined(WIN32)
#if defined(MUTEX_IMPLEMENTATION_WINAPI_CRITICAL_SECTION)
        LeaveCriticalSection( & this->handle );
#elif defined(MUTEX_IMPLEMENTATION_WINAPI_MUTEX)
        ReleaseMutex( this->handle.handle );
#endif
#else
#error Unsupported : Mutex
#endif

        this->state = State::UNLOCKED;

    }

    __CDS_NoDiscard auto toString() const noexcept -> String override {
        return String()
            .append("Mutex { <").append(Mutex::IMPLEMENTATION_TYPE).append(">; state = ")
            .append(Mutex::stateToString(this->state)).append(" }");
    }
};

#if defined(IN_PLACE)
#undef IN_PLACE
#undef MUTEX_IMPLEMENTATION_WINAPI_CRITICAL_SECTION
#endif


#endif //CDS_MUTEX_HPP
