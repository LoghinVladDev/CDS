//
// Created by loghin on 31.10.2021.
//

#ifndef CDS_ARRAYSIZEMANAGER_H
#define CDS_ARRAYSIZEMANAGER_H

#include <CDS/Options>
#include <CDS/Compiler>
#include <CDS/Warnings>
#include <cstring>
#include <algorithm>

#if defined(__CDS_Platform_Linux)

#include <pthread.h>

#elif defined(__CDS_Platform_Microsoft_Windows)

#include <windows.h>

#endif

#if defined(_MSC_VER)

#pragma push_macro("min")
#pragma push_macro("max")
#undef min
#undef max

#endif

namespace cds { // NOLINT(modernize-concat-nested-namespaces) c++ 14 and lower do not support namespace concatenation
    namespace utility { // NOLINT(modernize-concat-nested-namespaces) c++ 14 and lower do not support namespace concatenation
        namespace hidden { // NOLINT(modernize-concat-nested-namespaces) c++ 14 and lower do not support namespace concatenation
            namespace memoryImpl {

                class ArraySizeManager {
                private:
                    struct Record {
                        AddressValueType address;
                        Size size;
                    };

                    struct Partition {
                        Record * partition = nullptr;
                        Size size = 0;
                        Size capacity = 0;

                        inline auto enlarge ( Size required ) noexcept -> void {
                            Size newCap = std :: max ( 2 * this->capacity, required + this->size );
                            auto newPartition = new Record [ newCap ];

                            if ( this->partition != nullptr )
                                std :: memcpy ( newPartition, this->partition, sizeof(Record) * this->size );

                            delete [] this->partition;
                            this->partition = newPartition;

                            this->capacity = newCap;
                        }

                    } pSizeDistribution[__CDS_Memory_ArrayManagerCacheRange];

        #if defined(__CDS_Platform_Linux)

                    pthread_mutex_t opLock;

        #elif defined(__CDS_Platform_Microsoft_Windows)

                    CRITICAL_SECTION criticalSection;

        #endif

                public:
                    ArraySizeManager() noexcept { // NOLINT(cppcoreguidelines-pro-type-member-init,modernize-use-equals-default)

        #if defined(__CDS_Platform_Linux)

                        pthread_mutex_init( & this->opLock, nullptr );

        #elif defined(__CDS_Platform_Microsoft_Windows)

                        InitializeCriticalSection( & this->criticalSection );

        #endif

                    }

                    inline auto save ( Byte * pAddress, Size size ) noexcept -> Byte * {
                        const auto address = reinterpret_cast < AddressValueType > ( pAddress );
                        Partition & partition = this->pSizeDistribution[ address % __CDS_Memory_ArrayManagerCacheRange ];

        #if defined(__CDS_Platform_Linux)
                        pthread_mutex_lock ( & this->opLock );
        #elif defined(__CDS_Platform_Microsoft_Windows)
                        EnterCriticalSection ( & this->criticalSection );
        #endif

                        if ( partition.size >= partition.capacity )
                            partition.enlarge( 1 );

                        partition.partition[ partition.size ++ ] = { address, size };

        #if defined(__CDS_Platform_Linux)
                        pthread_mutex_unlock ( & this->opLock );
        #elif defined(__CDS_Platform_Microsoft_Windows)
                        LeaveCriticalSection( & this->criticalSection );
        #endif

                        return pAddress;
                    }

                    inline auto load ( Byte const * pAddress ) noexcept -> Size {
                        static Size loadCount = 0;

                        const auto address = reinterpret_cast < AddressValueType > ( pAddress );
                        Partition & partition = this->pSizeDistribution[ address % __CDS_Memory_ArrayManagerCacheRange ];

        #if defined(__CDS_Platform_Linux)
                        pthread_mutex_lock ( & this->opLock );
        #elif defined(__CDS_Platform_Microsoft_Windows)
                        EnterCriticalSection ( & this->criticalSection );
        #endif

                        Size arraySize = 0;

                        for ( Size i = 0; i < partition.size; ++ i )
                            if ( partition.partition[i].address == address ) {
                                arraySize = exchange( partition.partition[i].size, 0 );
                                break;
                            }

                        if ( loadCount + 1 % __CDS_Memory_ArrayManagerCacheLifetimeCycles == 0 )
                            this->cleanRecords ();

        #if defined(__CDS_Platform_Linux)
                        pthread_mutex_unlock ( & this->opLock );
        #elif defined(__CDS_Platform_Microsoft_Windows)
                        LeaveCriticalSection( & this->criticalSection );
        #endif

                        return arraySize;
                    }

                    inline auto cleanRecords () noexcept -> void {
                        for ( auto & partition : this->pSizeDistribution ) {
                            auto pNewRecordArea = new Record [ partition.size ];
                            Size newSize = 0;

                            for ( Size i = 0; i < partition.size; ++ i )
                                if ( partition.partition[i].size > 0 )
                                    pNewRecordArea [ newSize ++ ] = partition.partition[i];

                            delete [] partition.partition;
                            partition.partition = pNewRecordArea;
                            partition.capacity = partition.size;
                            partition.size = newSize;
                        }
                    }

                    ~ArraySizeManager() noexcept {
                        for ( auto & p : this->pSizeDistribution )
                            delete [] p.partition;

        #if defined(__CDS_Platform_Linux)

                        pthread_mutex_destroy( & this->opLock );

        #elif defined(__CDS_Platform_Microsoft_Windows)

                        DeleteCriticalSection( & this->criticalSection );

        #endif

                    }

                };

            }
        }
    }
}

#if defined(_MSC_VER)

#pragma pop_macro("max")
#pragma pop_macro("min")

#endif

#endif //CDS_ARRAYSIZEMANAGER_H
