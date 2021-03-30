//
// Created by vladl on 3/29/2021.
//

#ifndef CDS_TIMER_HPP
#define CDS_TIMER_HPP


#include <CDS/Thread>
#include <CDS/Pointer>
#include <CDS/Mutex>
#include <CDS/Semaphore>

#include <atomic>
#include <chrono>

class Timer: public Object {
public:
    CDS_sint32                TIMER_INFINITE_PERIODICITY = -1;

private:
    Mutex                    _threadModifyLock;
    UniquePointer < Thread > _pThread;
    CDS_sint32               _millisCallback { TIMER_INFINITE_PERIODICITY };

    std::atomic < bool >     _timerPaused {true};
    std::atomic < bool >     _timerShouldStop {false};

    Semaphore                _timerFinished;


public:
    explicit Timer () noexcept = default;

    ~Timer () noexcept override {
        this->stop();
    }

    auto toString() const noexcept -> String override {
        return String()
                .append("Timer{")
                .append("thread=").append(this->_pThread.toString())
                .append(", periodicity=").append(this->_millisCallback).append(" ms")
                .append(", paused=").append(this->_timerPaused).append("}");
    }

    auto setInterval ( CDS_sint32 periodicityMillis ) noexcept -> void {
        this->_millisCallback = periodicityMillis;
    }

    auto pause () noexcept -> void {
        this->_timerPaused = true;
    }

    auto unpause () noexcept -> void {
        this->_timerPaused = false;
    }

    auto stop () noexcept -> void {
        if ( ! this->_pThread.isNull() ) {
            this->_timerShouldStop = true;
            this->_timerFinished.wait();

            this->_pThread->join();
            this->_pThread.reset(nullptr);
            this->_threadModifyLock.unlock();
        }
    }

#pragma clang diagnostic push
#pragma ide diagnostic ignored "EndlessLoop"
    template <typename Function>
    auto start (Function f) noexcept -> void {
        this->_threadModifyLock.lock();
        if ( this->_pThread.isNull() ) {
            this->_pThread.reset(
                    new Runnable(
                            [this, & f]() {
                                decltype(std::chrono::steady_clock::now()) lastStart;
                                bool firstStart = true;

                                while (! this->_timerShouldStop) {
                                    if (this->_millisCallback == TIMER_INFINITE_PERIODICITY)
                                        continue;

                                    if (this->_timerPaused)
                                        continue;

                                    if (firstStart) {
                                        firstStart = false;
                                        lastStart = std::chrono::steady_clock::now();
                                        if ( ! this->_timerShouldStop )
                                            f();

                                        continue;
                                    }

                                    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(
                                            std::chrono::steady_clock::now() - lastStart
                                    ).count();

                                    if (elapsed < this->_millisCallback)
                                        continue;

                                    lastStart = std::chrono::steady_clock::now();

                                    if ( ! this->_timerShouldStop )
                                        f();
                                }

                                this->_timerFinished.notify();
                            }
                    )
            );

            this->_pThread->start();
        }
        this->_threadModifyLock.unlock();

        this->_timerPaused = false;
    }
#pragma clang diagnostic pop

};

#endif //CDS_TIMER_HPP
