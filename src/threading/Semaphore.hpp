//
// Created by loghin on 05.11.2020.
//

#ifndef CDS_SEMAPHORE_HPP
#define CDS_SEMAPHORE_HPP

#include <CDS/Mutex>
#include <CDS/Pointer>

namespace cds {

    class Semaphore : public Object {
    private:
        PointerBase < Mutex > * volatile _pBase;
        uint8                   volatile _count {0u};

    public:
        Semaphore () noexcept : _pBase(Memory :: instance().create < SharedPointer < Mutex > > (Memory :: instance().create < Mutex >())) {}
        __CDS_MaybeUnused explicit Semaphore ( Mutex & mutex ) noexcept : _pBase(Memory :: instance().create < ForeignPointer < Mutex > > (& mutex)) {}
        Semaphore ( Semaphore const & semaphore ) noexcept : _pBase ( cds :: copy ( * semaphore._pBase ) ) { }

        ~Semaphore() noexcept override {
            Memory :: instance().destroy ( this->_pBase );
        }

        __CDS_OptionalInline auto wait () noexcept -> void {
            while ( true ) {
                if ( ( * this->_pBase )->tryLock() ) {
                    if ( this->_count != 0u ) {
                        ( * this->_pBase )->unlock();
                        this->_count = this->_count - 1u;  // NOLINT(clion-misra-cpp2008-5-0-4)
                        break;
                    }
                    ( * this->_pBase )->unlock();
                }
            }
        }

        __CDS_OptionalInline auto notify () noexcept -> void {
            ( * this->_pBase )->lock();
            this->_count = this->_count + 1u;  // NOLINT(clion-misra-cpp2008-5-0-4)
            ( * this->_pBase )->unlock();
        }

        __CDS_OptionalInline auto reset () noexcept -> void {
            this->_count = 0u;
            (*(* this->_pBase)).reset();
        }

        __CDS_NoDiscard auto toString () const noexcept -> String override {
            return String()
                .append("Semaphore{mutexBase=").append(this->_pBase->get()->toString())
                .append(",signalCount=").append(this->_count).append("}");
        }
    };

}

__CDS_RegisterParseType(Semaphore) // NOLINT(clion-misra-cpp2008-8-0-1)


#endif //CDS_SEMAPHORE_HPP
