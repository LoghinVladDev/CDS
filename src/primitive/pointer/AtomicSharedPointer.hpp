//
// Created by loghin on 5/1/22.
//

#ifndef __CDS_ATOMIC_SHARED_POINTER_HPP__
#define __CDS_ATOMIC_SHARED_POINTER_HPP__

#include <CDS/pointer/SmartPointer>
#include <CDS/Mutex>

namespace cds {

    template < typename T >
    class __CDS_MaybeUnused AtomicSharedPointer : public SmartPointer<T> { // NOLINT(cppcoreguidelines-virtual-class-destructor)
    private:
        struct SharedPointerControlBlock {
            int ownerCount = 1; // NOLINT(clion-misra-cpp2008-11-0-1)
            Mutex lock; // NOLINT(clion-misra-cpp2008-11-0-1)

            SharedPointerControlBlock() noexcept = default;
        };

        SharedPointerControlBlock * pControl { nullptr };

    public:
        constexpr AtomicSharedPointer() noexcept = default;
        __CDS_OptimalInline AtomicSharedPointer(AtomicSharedPointer const & pointer) noexcept :
                SmartPointer<T>(pointer.pObj),
                pControl(pointer.pControl) {

            pointer.pControl->lock.lock();
            ++ pointer.pControl->ownerCount;
            pointer.pControl->lock.unlock();
        }

        __CDS_OptimalInline auto copy () const noexcept -> AtomicSharedPointer * override {
            return Memory :: instance().create < AtomicSharedPointer >(* this);
        }

        __CDS_OptimalInline AtomicSharedPointer(typename SmartPointer<T>::Pointer pointer) noexcept : // NOLINT(google-explicit-constructor)
                SmartPointer<T>(pointer),
                pControl(Memory :: instance().create < SharedPointerControlBlock > ()){

        }

        __CDS_OptimalInline auto operator = ( AtomicSharedPointer const & pointer ) noexcept -> AtomicSharedPointer & {
            if ( this == & pointer ) {
                return * this;
            }

            this-> AtomicSharedPointer :: reset(pointer );
            return * this;
        }

        __CDS_OptimalInline auto operator = ( typename SmartPointer < T > :: Pointer pointer ) noexcept -> AtomicSharedPointer & {
            this-> AtomicSharedPointer :: reset(pointer );
            return * this;
        }

        __CDS_OptimalInline ~AtomicSharedPointer() noexcept override {
            this-> AtomicSharedPointer :: reset( nullptr );
        }

        __CDS_OptimalInline auto release () noexcept -> typename SmartPointer<T>::Pointer override {
            auto pointer = this->pObj;
            this-> AtomicSharedPointer :: reset( nullptr );
            return pointer;
        }

        __CDS_OptionalInline auto reset ( typename SmartPointer<T>::Pointer pointer ) noexcept -> void override {
            if (this->pObj == pointer ) {
                return;
            }

            auto pVal = this->pObj;
            this->pObj = pointer;

            if ( this->pControl != nullptr ) {
                if ( this->pControl->ownerCount == 1 ) {
                    Memory::instance().destroy ( this->pControl );
                    Memory::instance().destroy ( pVal );
                }

                this->pControl = nullptr;
            }

            if ( this->pObj != nullptr ) {
                this->pControl = Memory :: instance().create < SharedPointerControlBlock > ();
            }
        }

        __CDS_OptionalInline auto reset ( AtomicSharedPointer const & pointer ) noexcept -> void override {
            if (this->pControl == pointer.pControl ) {
                return;
            }

            auto oldAddress = this->pObj;
            this->pObj = pointer;

            if ( this->pControl != nullptr ) {
                if ( this->pControl->ownerCount == 1 ) {
                    Memory::instance().destroy ( this->pControl );
                    Memory::instance().destroy ( oldAddress );
                }

                this->pControl = nullptr;
            }

            if (pointer.pControl != nullptr ) {
                this->pControl = pointer.pControl;
                pointer.pControl->lock.lock();
                ++ this->pControl->ownerCount;
                pointer.pControl->lock.unlock();
            }
        }
    };

}

#endif // __CDS_ATOMIC_SHARED_POINTER_HPP__
