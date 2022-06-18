//
// Created by loghin on 30.10.2021.
//

#ifndef CDS_MEMORY_HPP
#define CDS_MEMORY_HPP

#include <new>
#include <CDS/meta/TypeTraits>

#include "ArraySizeManager.hpp"

#if ! defined ( __CDS_Memory_ForceDisable )
#define __CDS_Memory_ForceDisable
#endif

#if ! defined(__CDS_Memory_CustomManager)
#define __CDS_Memory_Manager DefaultManager
#else
#define __CDS_Memory_Manager __CDS_Memory_CustomManager
#endif

namespace cds {

    class Memory {
    public:
        class DefaultManager {
        public:
            template < typename T, typename ... ArgumentTypes >
            constexpr static auto create ( void * pRawMemory, ArgumentTypes && ... arguments ) noexcept ( noexcept ( T ( std :: forward < ArgumentTypes > ( arguments ) ... ) ) ) -> T * {
                return new (pRawMemory) T ( std :: forward < ArgumentTypes > ( arguments ) ... );
            }

            template < typename T, meta :: EnableIf < ! meta :: isSame < meta :: Decay < T >, void > () > = 0 > // NOLINT(clion-misra-cpp2008-5-3-1)
            inline static auto destroy ( T * pObject ) noexcept (false) -> void * {
                if ( pObject != nullptr ) {
                    pObject->~T();
                }

                return reinterpret_cast < void * > ( const_cast < meta :: RemoveConst < T > * > ( pObject ) );
            }

            template < typename T, meta :: EnableIf < meta :: isSame < meta :: Decay < T >, void > () > = 0 >
            inline static auto destroy ( T * ) noexcept (false) -> void * {
                return nullptr;
            }
        };


        class Allocator {
            using MemoryManager = __CDS_Memory_Manager;

        protected:
            __CDS_NoDiscard virtual auto allocate ( Size ) noexcept -> void * = 0;
            virtual auto deallocate ( void * ) noexcept -> void = 0;
            __CDS_NoDiscard __CDS_OptimalInline virtual auto reallocate ( void * pAddress, Size newSize ) noexcept -> void * {
                this->deallocate ( pAddress );
                return this->allocate ( newSize );
            }

        public:
            virtual ~Allocator () noexcept = default;

            __CDS_WarningSuppression_DeducedNoexceptTermination_SuppressEnable

            template < typename T, typename ... ArgumentTypes >
            inline auto create ( ArgumentTypes ... arguments ) noexcept ( noexcept ( T ( std :: forward < ArgumentTypes > ( arguments ) ... ) ) ) -> T * {
                void * pRawMemory = nullptr;

                try {
                    pRawMemory = this->allocate ( sizeof ( T ) );
                    return MemoryManager :: create < T > ( pRawMemory, std :: forward < ArgumentTypes > ( arguments ) ... );
                } catch ( ... ) {
                    this->deallocate ( pRawMemory );
                    throw;
                }
            }

            template < typename T >
            inline auto createArray ( Size size ) noexcept ( noexcept ( T ( ) ) ) -> T * {
                void * pRawMemory = nullptr;

                try {
                    pRawMemory = this->allocate ( sizeof ( T ) * size );

                    Byte * startAddress = reinterpret_cast < Byte * > ( pRawMemory );
                    Byte * endAddress = reinterpret_cast < Byte * > ( pRawMemory ) + sizeof ( T ) * size;

                    for ( auto * pObject = startAddress; pObject < endAddress; pObject += sizeof ( T ) ) { // NOLINT(clion-misra-cpp2008-6-5-4)
                        MemoryManager :: create < T > ( pObject );
                    }

                    return reinterpret_cast < T * > ( pRawMemory );

                } catch ( ... ) {
                    this->deallocate ( pRawMemory );
                    throw;
                }
            }

            __CDS_WarningSuppression_DeducedNoexceptTermination_SuppressDisable

            template < typename T >
            inline auto destroyArray ( T * pArray, Size size ) noexcept -> void {
                Byte * startAddress = reinterpret_cast < Byte * > ( pArray );
                Byte * endAddress = reinterpret_cast < Byte * > ( pArray ) + sizeof ( T ) * size;

                for ( auto * pObject = startAddress; pObject < endAddress; pObject += sizeof ( T ) ) { // NOLINT(clion-misra-cpp2008-6-5-4)
                    MemoryManager :: destroy ( reinterpret_cast < T * > ( pObject ) );
                }

                this->deallocate( pArray );
            }

            template < typename T >
            inline auto destroy ( T * pObject ) noexcept -> void {
                return this->deallocate ( MemoryManager :: destroy ( pObject ) );
            }
        };

        class DefaultHeapAllocator : public Allocator  {
        public:
            DefaultHeapAllocator() noexcept = default;

            inline auto allocate ( Size size ) noexcept -> void * override {
                return malloc ( size ); // NOLINT(clion-misra-cpp2008-18-4-1)
            }

            inline auto reallocate ( void * pMemory, Size size ) noexcept -> void * override {
                return realloc ( pMemory, size );
            }

            inline auto deallocate ( void * pMemory ) noexcept -> void override {
                free ( pMemory );
            }
        };

        class __CDS_MaybeUnused LeakDetectionAllocator;

    private:
        Allocator * pAllocator { nullptr }; // NOLINT(clion-misra-cpp2008-18-4-1)
        utility :: hidden :: memoryImpl :: ArraySizeManager sizeManager;

        Memory () noexcept { } // NOLINT(modernize-use-equals-default) Windows cannot identify noexcept composite in default

    public:
        static auto instance () noexcept -> Memory & {
            static Memory instance;
            return instance;
        }

        __CDS_MaybeUnused __CDS_OptimalInline auto replaceAllocator ( Allocator * allocator ) noexcept -> Allocator * {
            return exchange ( this->pAllocator, allocator );
        }

        template < typename T, typename ... ArgumentTypes >
        inline auto create ( ArgumentTypes && ... arguments ) noexcept ( noexcept ( T ( std :: forward < ArgumentTypes > ( arguments ) ... ) ) ) -> T * {

    #if defined(__CDS_Memory_ForceDisable)
            return new T ( std :: forward < ArgumentTypes > ( arguments ) ... );
    #else
            if ( this->pAllocator == nullptr ) {
                return new T ( std :: forward < ArgumentTypes && > ( arguments ) ... );
            }

            return this->pAllocator->create <T> ( std :: forward < ArgumentTypes > ( arguments ) ... );
    #endif

        }

        template < typename T >
        inline auto createArray ( Size size ) noexcept ( noexcept ( T () ) ) -> T * {

    #if defined(__CDS_Memory_ForceDisable)
            return new T[size];
    #else
            if ( this->pAllocator == nullptr ) {
                return new T [size];
            }

            return reinterpret_cast < T * > ( this->sizeManager.save ( reinterpret_cast < Byte * > ( this->pAllocator->createArray < T > ( size ) ), size ) );
    #endif

        }

        template < typename T >
        inline auto destroy ( T * pObject ) noexcept -> void {

    #if defined(__CDS_Memory_ForceDisable)
            delete pObject;
    #else
            if ( this->pAllocator == nullptr ) {
                delete pObject;
                return;
            }

            return this->pAllocator->destroy( pObject );
    #endif

        }

        template < typename T >
        inline auto destroyArray ( T * pArray ) noexcept -> void {

    #if defined(__CDS_Memory_ForceDisable)
            delete [] pArray;
    #else
            if ( this->pAllocator == nullptr ) {
                delete[] pArray;
                return;
            }

            return this->pAllocator->destroyArray ( pArray, this->sizeManager.load (reinterpret_cast < Byte const * > ( pArray ) ) );
    #endif

        }

        ~Memory() noexcept {
            delete this->pAllocator;
        }
    };

}

#undef __CDS_Memory_Manager

#endif //CDS_MEMORY_HPP
