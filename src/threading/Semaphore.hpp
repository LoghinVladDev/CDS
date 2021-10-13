//
// Created by loghin on 05.11.2020.
//

#ifndef CDS_SEMAPHORE_HPP
#define CDS_SEMAPHORE_HPP

#include <CDS/Mutex>
#include <CDS/Pointer>

class Semaphore : public Object {
private:
    PointerBase < Mutex > * _pBase;
    volatile uint8  _count {0};

public:
    Semaphore () noexcept : _pBase(new SharedPointer < Mutex >(new Mutex())) {}
    __CDS_MaybeUnused explicit Semaphore ( Mutex & m ) noexcept : _pBase(new ForeignPointer < Mutex >(& m)) {}
    Semaphore ( Semaphore const & o ) noexcept : _pBase(o._pBase->copy()) { }

    ~Semaphore() noexcept override {
        delete this->_pBase;
    }

    inline auto wait () noexcept -> void {
        while ( true )
            if ( ( * this->_pBase )->tryLock() ) {
                if ( this->_count != 0 ) {
                    ( * this->_pBase )->unlock();
                    this->_count = this->_count - 1;
                    break;
                }
                ( * this->_pBase )->unlock();
            }
    }

    inline auto notify () noexcept -> void {
        ( * this->_pBase )->lock();
        this->_count = this->_count + 1;
        ( * this->_pBase )->unlock();
    }

    inline auto reset () noexcept -> void {
        this->_count = 0;
        (*(* this->_pBase)).reset();
    }

    __CDS_NoDiscard auto toString () const noexcept -> String override {
        return String()
            .append("Semaphore{mutexBase=").append(this->_pBase->get()->toString())
            .append(",signalCount=").append(this->_count).append("}");
    }
};

__CDS_RegisterParseType(Semaphore)


#endif //CDS_SEMAPHORE_HPP
