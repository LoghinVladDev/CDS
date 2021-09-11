//
// Created by vladl on 3/29/2021.
//

#ifndef CDS_TIMER_HPP
#define CDS_TIMER_HPP

#include <functional>
#include <tuple>

#include <CDS/Thread>
#include <CDS/Pointer>
#include <CDS/Mutex>
#include <CDS/Semaphore>

#include <atomic>
#include <chrono>

class __CDS_MaybeUnused Timer: public Object {
public:
    constexpr static sint32 TIMER_INFINITE_PERIODICITY = -1;

private:
    UniquePointer < Thread > _pThread;
    sint32                   _millisCallback {TIMER_INFINITE_PERIODICITY };

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

    __CDS_MaybeUnused auto setInterval (sint32 periodicityMillis ) noexcept -> void {
        this->_millisCallback = periodicityMillis;
    }

    __CDS_MaybeUnused auto pause () noexcept -> void {
        this->_timerPaused = true;
    }

    __CDS_MaybeUnused auto unpause () noexcept -> void {
        this->_timerPaused = false;
    }

    auto stop () noexcept -> void {
        if ( ! this->_pThread.isNull() ) {
            this->_timerShouldStop = true;
            this->_timerFinished.wait();

            this->_pThread->join();
            this->_pThread.reset(nullptr);
        }
    }

    template <typename Function, typename ... Args >
    auto start (Function const & f, Args && ... args) noexcept -> void {
        if ( this->_pThread.isNull() ) {
            this->_pThread.reset(
                    new Runnable(
                            [args = std::make_tuple(std::forward<Args>(args) ... ), this, & f] () mutable -> void {
                                 return std::apply(
                                        [this, & f](Args && ... args) -> void {
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
                                                        f(std::forward<Args>(args) ... );

                                                    continue;
                                                }

                                                auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(
                                                        std::chrono::steady_clock::now() - lastStart
                                                ).count();

                                                if (elapsed < this->_millisCallback)
                                                    continue;

                                                lastStart = std::chrono::steady_clock::now();

                                                if ( ! this->_timerShouldStop )
                                                    f( std::forward < Args > (args) ... );
                                            }

                                            this->_timerFinished.notify();
                                        },
                                        std::move(args)
                                );
                            }
                    )
            );

            this->_pThread->start();
        }

        this->_timerPaused = false;
    }
};

#endif //CDS_TIMER_
