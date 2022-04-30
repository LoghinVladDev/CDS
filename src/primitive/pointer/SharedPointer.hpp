//
// Created by loghin on 5/1/22.
//

#ifndef __CDS_SHARED_POINTER_HPP__
#define __CDS_SHARED_POINTER_HPP__

#include <CDS/pointer/SmartPointer>

namespace cds {

    template < typename T >
    class SharedPointer : public SmartPointer < T > { // NOLINT(cppcoreguidelines-virtual-class-destructor)
    private:
        struct SharedPointerControlBlock {
            int ownerCount {1}; // NOLINT(clion-misra-cpp2008-11-0-1)

#if defined CDS_PTR_DEBUG

            constexpr SharedPointerControlBlock() noexcept : ownerCount(1) {
                std::cout << "Created Shared Pointer Control Block : 0x" << std::hex << reinterpret_cast < AddressValueType > (this) << '\n' << std :: dec;
            }

            __CDS_cpplang_ConstexprDestructor ~SharedPointerControlBlock () noexcept {
                std::cout << "Destroyed Shared Pointer Control Block : 0x" << std::hex << reinterpret_cast < AddressValueType > (this) << '\n' << std :: dec;
            }

#endif

#if __CDS_cpplang_StructBracesInitialization_available == false
            constexpr explicit SharedPointerControlBlock(int ownerCount = 1) noexcept : ownerCount(ownerCount) {}
#endif

        };

        SharedPointerControlBlock * pControl { nullptr };

    public:
        constexpr SharedPointer() noexcept = default;
        __CDS_OptimalInline SharedPointer(SharedPointer const & pointer) noexcept :
                SmartPointer<T>(pointer.pObj),
                pControl(pointer.pControl) {

            ++ pointer.pControl->ownerCount;
        }

        __CDS_cpplang_VirtualConstexpr auto copy () const noexcept -> SharedPointer * override {
            return Memory :: instance().create < SharedPointer > (* this);
        }

        __CDS_cpplang_ConstexprDynamicAllocation SharedPointer(typename SmartPointer<T>::Pointer pointer) noexcept : // NOLINT(google-explicit-constructor)
                SmartPointer<T>(pointer),
                pControl(Memory :: instance().create < SharedPointerControlBlock > ()){

        }

        __CDS_cpplang_ConstexprDynamicAllocation auto operator = ( SharedPointer const & pointer ) noexcept -> SharedPointer & {
            if ( this == & pointer ) {
                return * this;
            }

            this-> SharedPointer :: reset(pointer );
            return * this;
        }

        __CDS_cpplang_ConstexprDynamicAllocation auto operator = ( typename SmartPointer < T > :: Pointer pointer ) noexcept -> SharedPointer & {
            this-> SharedPointer :: reset(pointer);
            return * this;
        }

        __CDS_cpplang_ConstexprDestructor ~SharedPointer() noexcept override {
            this-> SharedPointer :: reset( nullptr );
        }

        __CDS_cpplang_ConstexprDynamicAllocation auto release () noexcept -> typename SmartPointer<T>::Pointer override {
            auto pointer = this->pObj;
            this-> SharedPointer :: reset ( nullptr );
            return pointer;
        }

        __CDS_cpplang_ConstexprDynamicAllocation auto reset ( typename SmartPointer<T>::Pointer pointer ) noexcept -> void override {
            if (this->pObj == pointer ) {
                return;
            }

            auto pVal = this->pObj;
            this->pObj = pointer;

            if ( this->pControl != nullptr ) {
                if ( -- this->pControl->ownerCount == 0 ) {
                    Memory :: instance().destroy ( this->pControl );
                    Memory :: instance().destroy ( pVal );
                }

                this->pControl = nullptr;
            }

            if ( this->pObj != nullptr ) {
                this->pControl = Memory :: instance () .create < SharedPointerControlBlock > ();
            }
        }

        __CDS_cpplang_ConstexprDynamicAllocation auto reset ( SharedPointer const & pointer ) noexcept -> void {
            if (this->pControl == pointer.pControl ) {
                return;
            }

            auto oldAddress = this->pObj;
            this->pObj = pointer.pObj;

            if ( this->pControl != nullptr ) {
                if ( -- this->pControl->ownerCount == 0 ) {
                    Memory :: instance().destroy ( this->pControl );
                    Memory :: instance().destroy ( oldAddress );
                }

                this->pControl = nullptr;
            }

            if (pointer.pControl != nullptr ) {
                this->pControl = pointer.pControl;
                ++ this->pControl->ownerCount;
            }
        }
    };

}

#endif // __CDS_SHARED_POINTER_HPP__
