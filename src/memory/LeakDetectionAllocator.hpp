//
// Created by loghin on 31.10.2021.
//

#ifndef CDS_LEAKDETECTIONALLOCATOR_HPP
#define CDS_LEAKDETECTIONALLOCATOR_HPP

#include <CDS/Memory>
#include <CDS/HashMap>
#include <CDS/Mutex>

class Memory::LeakDetectionAllocator : public Memory::Allocator {
private:
    class AddressComparator : public Comparator < Byte * > {
    public:
        inline auto operator ()(Byte * const & pAddrA, Byte * const & pAddrB) const noexcept -> bool override {
            return reinterpret_cast < AddressValueType > ( pAddrA ) < reinterpret_cast < AddressValueType > ( pAddrB );
        }
    };

    HashMap < Byte *, Size > addressSet;
    Allocator * pDefaultAllocator = new DefaultHeapAllocator ();
    Mutex opLock;

public:
    inline auto allocate ( Size size ) noexcept -> void * override {

        this->opLock.lock();

        auto pAddress = malloc ( size );
// 0x5586c03c99c0
        Memory::instance().replaceAllocator( this->pDefaultAllocator );
        this->addressSet.emplace ( reinterpret_cast < Byte * > (pAddress), size );
        Memory::instance().replaceAllocator( this );

        this->opLock.unlock();

        return pAddress;
    }

    inline auto deallocate ( void * pAddress ) noexcept -> void override {

        this->opLock.lock();

        Memory::instance().replaceAllocator( this->pDefaultAllocator );
        this->addressSet.remove ( reinterpret_cast < Byte * > ( pAddress ) );
        Memory::instance().replaceAllocator( this );

        free (pAddress);

        this->opLock.unlock();
    }

    ~LeakDetectionAllocator() noexcept override {
        Memory::instance().replaceAllocator( this->pDefaultAllocator );
        if ( ! this->addressSet.empty() ) {

            std :: cerr << "\t" << this->addressSet.size() << " addresses leaked\n";
            for (auto const & item : this->addressSet)
                std :: cerr << "\t\t" << std :: hex << reinterpret_cast < AddressValueType > ( item.first() ) << std :: dec << ", " << item.second() << " bytes\n";

            std :: cerr.flush();
        }
    }
};


#endif //CDS_LEAKDETECTIONALLOCATOR_HPP
