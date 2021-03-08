//
// Created by loghin on 05.11.2020.
//

#ifndef CDS_SEMAPHORE_HPP
#define CDS_SEMAPHORE_HPP

#include <CDS/Mutex>

class Semaphore : public Object {
private:
    Mutex               & _lock;
    volatile CDS_uint8  _count {0};

public:
    Semaphore () noexcept = delete;
    explicit Semaphore ( Mutex & m ) noexcept : _lock(m) {}
    Semaphore ( Semaphore const & o ) noexcept : _lock(o._lock) {}

    inline auto wait () noexcept -> void {
        while ( true )
            if ( this->_lock.tryLock() ) {
                if ( this->_count != 0 ) {
                    this->_lock.unlock();
                    this->_count = this->_count - 1;
                    break;
                }
                this->_lock.unlock();
            }
    }

    inline auto notify () noexcept -> void {
        this->_lock.lock();
        this->_count = this->_count + 1;
        this->_lock.unlock();
    }

    [[nodiscard]] auto toString () const noexcept -> String override {
        return "";
    }
};


#endif //CDS_SEMAPHORE_HPP
