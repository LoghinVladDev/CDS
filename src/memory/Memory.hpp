//
// Created by loghin on 30.10.2021.
//

#ifndef CDS_MEMORY_HPP
#define CDS_MEMORY_HPP

#include <new>

#include "ArraySizeManager.hpp"

#if ! defined(__CDS_Memory_CustomManager)
#define __CDS_Memory_Manager DefaultManager
#else
#define __CDS_Memory_Manager __CDS_Memory_CustomManager
#endif

class Memory {
public:
    class DefaultManager {
    public:
        template < typename T, typename ... ArgumentTypes >
        constexpr static auto create ( void * pRawMemory, ArgumentTypes && ... arguments ) noexcept ( noexcept ( T ( std :: forward < ArgumentTypes > ( arguments ) ... ) ) ) -> T * {
            return new (pRawMemory) T ( std :: forward < ArgumentTypes > ( arguments ) ... );
        }

        template < typename T, EnableIf < ! std :: is_same < RemoveModifiers < T >, void > :: value > = 0 >
        inline static auto destroy ( T * pObject ) noexcept (false) -> void * {
            if ( pObject != nullptr )
                pObject->~T();
            return reinterpret_cast < void * > ( const_cast < RemoveConst < T > * > ( pObject ) );
        }

        template < typename T, EnableIf < std :: is_same < RemoveModifiers < T >, void > :: value > = 0 >
        inline static auto destroy ( T * pObject ) noexcept (false) -> void * {
            return nullptr;
        }
    };


    class Allocator {
        using MemoryManager = __CDS_Memory_Manager;

    protected:
        virtual auto allocate ( Size ) noexcept -> void * = 0;
        virtual auto deallocate ( void * ) noexcept -> void = 0;

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

                for ( auto * pObject = startAddress; pObject < endAddress; pObject += sizeof ( T ) )
                    MemoryManager :: create < T > ( pObject );

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

            for ( auto * pObject = startAddress; pObject < endAddress; pObject += sizeof ( T ) )
                MemoryManager :: destroy ( reinterpret_cast < T * > ( pObject ) );

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
            return malloc ( size );
        }

        inline auto deallocate ( void * pMemory ) noexcept -> void override {
            free ( pMemory );
        }
    };

    class LeakDetectionAllocator;

private:
    Allocator * pAllocator { new DefaultHeapAllocator };
    Utility::MemoryImpl::ArraySizeManager sizeManager;

    Memory () noexcept { } // NOLINT(modernize-use-equals-default) Windows cannot identify noexcept composite in default

public:
    static auto instance () noexcept -> Memory &;

    __CDS_OptimalInline auto replaceAllocator ( Allocator * allocator ) noexcept -> Allocator * {
        return Utility :: exchange ( this->pAllocator, allocator );
    }

    template < typename T, typename ... ArgumentTypes >
    inline auto create ( ArgumentTypes ... arguments ) noexcept( noexcept ( T ( std :: forward < ArgumentTypes > ( arguments ) ... ) ) ) -> T * {

#if defined(__CDS_Memory_ForceDisable)
        return new T ( std :: forward < ArgumentTypes > ( arguments ) ... );
#else
        return this->pAllocator->create <T> ( std :: forward < ArgumentTypes > ( arguments ) ... );
#endif

    }

    template < typename T >
    inline auto createArray ( Size size ) noexcept ( noexcept ( T () ) ) -> T * {

#if defined(__CDS_Memory_ForceDisable)
        return new T[size];
#else
        return reinterpret_cast < T * > ( this->sizeManager.save ( reinterpret_cast < Byte * > ( this->pAllocator->createArray < T > ( size ) ), size ) );
#endif

    }

    template < typename T >
    inline auto destroy ( T * pObject ) noexcept -> void {

#if defined(__CDS_Memory_ForceDisable)
        delete pObject;
#else
        return this->pAllocator->destroy( pObject );
#endif

    }

    template < typename T >
    inline auto destroyArray ( T * pArray ) noexcept -> void {

#if defined(__CDS_Memory_ForceDisable)
        delete [] pArray;
#else
        return this->pAllocator->destroyArray ( pArray, this->sizeManager.load (reinterpret_cast < Byte const * > ( pArray ) ) );
#endif

    }

    ~Memory() noexcept {
        delete this->pAllocator;
    }
};

inline auto Memory::instance() noexcept -> Memory & {
    static Memory instance;
    return instance;
}

#undef __CDS_Memory_Manager

#endif //CDS_MEMORY_HPP
