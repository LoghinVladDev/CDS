//
// Created by loghin on 31.10.2021.
//

#ifndef CDS_LEAKDETECTIONALLOCATOR_HPP
#define CDS_LEAKDETECTIONALLOCATOR_HPP

#include <CDS/memory/Allocation>
#include <CDS/HashMap>
#include <CDS/Mutex>

namespace cds {

    class __CDS_MaybeUnused Memory::LeakDetectionAllocator : public Memory::Allocator {
    private:
        class __CDS_MaybeUnused AddressComparator : public Comparator < Byte * > {
        public:
            inline auto operator ()(Byte * const & pAddrA, Byte * const & pAddrB) const noexcept -> bool override {
                return reinterpret_cast < AddressValueType const > ( pAddrA ) < reinterpret_cast < AddressValueType const > ( pAddrB );
            }
        };

        HashMap < Byte *, Size > addressSet;
        Allocator * pDefaultAllocator = new DefaultHeapAllocator (); // NOLINT(clion-misra-cpp2008-18-4-1)
        Mutex opLock;

    public:
        inline auto allocate ( Size size ) noexcept -> void * override {

            this->opLock.lock();

            auto pAddress = malloc ( size ); // NOLINT(clion-misra-cpp2008-18-4-1)

            (void) Memory::instance().replaceAllocator( this->pDefaultAllocator );
            (void) this->addressSet.emplace ( reinterpret_cast < Byte * > (pAddress), size );
            (void) Memory::instance().replaceAllocator( this );

            this->opLock.unlock();

            return pAddress;
        }

        inline auto deallocate ( void * pAddress ) noexcept -> void override {

            this->opLock.lock();

            (void) Memory::instance().replaceAllocator( this->pDefaultAllocator );
            (void) this->addressSet.remove ( reinterpret_cast < Byte * > ( pAddress ) );
            (void) Memory::instance().replaceAllocator( this );

            free (pAddress);

            this->opLock.unlock();
        }

        ~LeakDetectionAllocator() noexcept override {
            (void) Memory::instance().replaceAllocator( this->pDefaultAllocator );
            if ( ! this->addressSet.empty() ) {

                std :: cerr << "\t" << this->addressSet.size() << " addresses leaked\n";
                for (auto const & item : this->addressSet) {
                    std :: cerr << "\t\t" << std :: hex << reinterpret_cast < AddressValueType > ( item.first() ) << std :: dec << ", " << item.second() << " bytes\n";
                }

                (void) std :: cerr.flush();
            }
        }
    };

}


#endif //CDS_LEAKDETECTIONALLOCATOR_HPP
