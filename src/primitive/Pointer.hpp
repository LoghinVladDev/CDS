//
// Created by loghin on 26.01.2021.
//

#ifndef CDS_POINTER_HPP
#define CDS_POINTER_HPP

#include <CDS/Object>
#include <sstream>

#include <CDS/Traits>
#include <CDS/Utility>
#include <CDS/Memory>

namespace cds {

    template < typename T >
    class PointerBase : public Object {
    public:
        using PointerType           = std::size_t;
        using Value                 = T;
        using ValueReference        = T &;
        using Pointer               = T *;
        using ConstPointer          = T const *;

    protected:
        Pointer mutable pObj {nullptr}; // NOLINT(clion-misra-cpp2008-11-0-1)

    protected:
        constexpr PointerBase() noexcept = default;
        explicit constexpr PointerBase(Pointer pointer) noexcept : pObj(pointer) {}

        template < typename DerivedType, EnableIf < isDerivedFrom < DerivedType, T > :: value > = 0 >
        explicit constexpr PointerBase(DerivedType pointer) noexcept : pObj ( (T*) pointer ) { }

    public:
        __CDS_cpplang_ConstexprDestructor ~PointerBase() noexcept override = default;

        __CDS_cpplang_VirtualConstexpr auto equals ( Object const & object ) const noexcept -> bool final {
            if ( this == & object ) {
                return true;
            }

            auto pPointerBase = dynamic_cast < PointerBase < T > const * > ( & object );
            if (pPointerBase == nullptr ) {
                return false;
            }

            return this->operator==(*pPointerBase);
        }

        constexpr auto operator == (PointerBase const & pointerBase) const noexcept -> bool {
            return this->pObj == pointerBase.pObj;
        }

        constexpr auto operator == (ConstPointer const pointer) const noexcept -> bool {
            return this->pObj == pointer;
        }

        constexpr auto operator == ( std :: nullptr_t pointer ) const noexcept -> bool {
            return this->pObj == pointer;
        }

        template < typename V >
        __CDS_OptimalInline auto operator == ( V const * const pointer ) const noexcept -> bool {
            return reinterpret_cast < T const * > ( pointer ) == this;
        }

        constexpr auto operator != (PointerBase const & pointerBase) const noexcept -> bool {
            return this->pObj != pointerBase.pObj;
        }

        constexpr auto operator != (ConstPointer const pointer) const noexcept -> bool {
            return this->pObj != pointer;
        }

        constexpr auto operator != ( std :: nullptr_t pointer ) const noexcept -> bool {
            return this->pObj != pointer;
        }

        template < typename V >
        __CDS_OptimalInline auto operator != ( V const * const pointer ) const noexcept -> bool {
            return reinterpret_cast < T const * > ( pointer ) != this;
        }

        __CDS_cpplang_ConstexprConditioned auto operator * () const noexcept (false) -> ValueReference {
            if ( this->pObj == nullptr ) {
                throw NullPointerException();
            }

            return * this->pObj;
        }

        __CDS_cpplang_ConstexprConditioned auto valueAt () const noexcept (false) -> ValueReference {
            if ( this->pObj == nullptr ) {
                throw NullPointerException();
            }

            return * this->pObj;
        }

        constexpr auto isNull () const noexcept -> bool { return this->pObj == nullptr; }

        __CDS_cpplang_ConstexprConditioned auto operator -> () const noexcept (false) -> Pointer {
            if ( this->pObj == nullptr ) {
                throw NullPointerException();
            }

            return this->pObj;
        }

        constexpr explicit operator bool () const noexcept {
            return this != nullptr;
        }

        constexpr auto get () const noexcept -> Pointer {
            return this->pObj;
        }

        constexpr operator Pointer () const noexcept { // NOLINT(google-explicit-constructor)
            return this->pObj;
        }

        __CDS_cpplang_VirtualConstexpr virtual auto release () noexcept -> Pointer {
            return cds :: exchange ( this->pObj, nullptr );
        }

        __CDS_OptimalInline virtual auto reset ( Pointer pointer ) noexcept -> void {
            Memory::instance().destroy ( cds :: exchange (this->pObj, pointer ) );
        }

        __CDS_OptimalInline auto reset () noexcept -> void {
            return this->reset ( nullptr );
        }

    private:
        template < typename U = T >
        __CDS_NoDiscard __CDS_OptionalInline auto ptrStringRep() const noexcept -> typename std::enable_if < Type < U > :: ostreamPrintable, String > :: type {
            std::stringstream oss;

            oss << "< 0x" << std::hex << reinterpret_cast < PointerType > ( pObj ) << std::dec << " : ";
            if ( pObj == nullptr ) {
                oss << "null";
            } else {
                oss << (*pObj);
            }

            oss << " >";
            return oss.str();
        }

        template < typename U = T >
        __CDS_NoDiscard __CDS_OptionalInline auto ptrStringRep() const noexcept -> typename std::enable_if < ! Type < U > :: ostreamPrintable, String > :: type { // NOLINT(clion-misra-cpp2008-5-3-1)
            std::stringstream oss;

            oss << "< 0x" << std::hex << reinterpret_cast < PointerType > ( pObj ) << std::dec << " : ";
            if ( pObj == nullptr ) {
                oss << "null";
            }
            else {
                oss << "unknown";
            }

            oss << " >";
            return oss.str();
        }

    public:
        __CDS_NoDiscard __CDS_OptimalInline auto toString () const noexcept -> String override {
            return this->ptrStringRep();
        }

        __CDS_NoDiscard __CDS_OptimalInline auto hash () const noexcept -> Index override {
            return reinterpret_cast < Index > ( this->pObj );
        }
    };

    template <class T>
    class UniquePointer final : public PointerBase<T> { // NOLINT(cppcoreguidelines-virtual-class-destructor)
    public:
        constexpr UniquePointer() noexcept = default;
        constexpr UniquePointer( typename PointerBase<T>::Pointer pointer ) noexcept : PointerBase<T>(pointer) { } // NOLINT(google-explicit-constructor)

        constexpr UniquePointer( UniquePointer const & pointer ) noexcept = delete;

        __CDS_cpplang_VirtualConstexpr UniquePointer( UniquePointer & pointer ) noexcept : PointerBase<T>(pointer.release()) { }
        __CDS_cpplang_VirtualConstexpr UniquePointer( UniquePointer && pointer ) noexcept : PointerBase<T>(pointer.release()) { }

        template < typename DerivedType, EnableIf < isDerivedFrom < DerivedType, T > :: value > = 0 >
        __CDS_cpplang_VirtualConstexpr UniquePointer ( UniquePointer < DerivedType > && pointer ) noexcept : PointerBase < T > ( pointer.release() ) { } // NOLINT(google-explicit-constructor)

        __CDS_cpplang_NonConstConstexprMemberFunction auto operator = ( UniquePointer && pointer ) noexcept -> UniquePointer & {
            if (&pointer == this ) {
                return * this;
            }

            this->reset(pointer.release());
            return * this;
        }

        __CDS_cpplang_NonConstConstexprMemberFunction auto operator = ( UniquePointer & pointer ) noexcept -> UniquePointer & { // NOLINT(misc-unconventional-assign-operator)
            if (&pointer == this ) {
                return * this;
            }

            this->reset(pointer.release());
            return * this;
        }

        __CDS_cpplang_NonConstConstexprMemberFunction auto operator = ( typename PointerBase < T > :: Pointer pointer ) noexcept -> UniquePointer & {
            this->reset(pointer);
            return * this;
        }

        template < typename D, EnableIf < isDerivedFrom < RemovePointer < D >, T > :: value > = 0 >
        __CDS_cpplang_NonConstConstexprMemberFunction auto operator = ( D pointer ) noexcept -> UniquePointer & {
            this->reset((T *)pointer);
            return * this;
        }

        __CDS_cpplang_NonConstConstexprMemberFunction auto operator = ( decltype(nullptr) ) noexcept -> UniquePointer & {
            this->reset();
            return * this;
        }

        __CDS_cpplang_ConstexprDestructor ~UniquePointer() noexcept final {
            Memory :: instance () . destroy ( this->pObj );
        }
    };

    template <class T>
    class SharedPointer : public PointerBase<T> { // NOLINT(cppcoreguidelines-virtual-class-destructor)
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
                PointerBase<T>(pointer.pObj),
                pControl(pointer.pControl) {

            ++ pointer.pControl->ownerCount;
        }

        __CDS_cpplang_VirtualConstexpr auto copy () const noexcept -> SharedPointer * override {
            return Memory :: instance().create < SharedPointer > (* this);
        }

        __CDS_cpplang_ConstexprDynamicAllocation SharedPointer(typename PointerBase<T>::Pointer pointer) noexcept : // NOLINT(google-explicit-constructor)
                PointerBase<T>(pointer),
                pControl(Memory :: instance().create < SharedPointerControlBlock > ()){

        }

        __CDS_cpplang_ConstexprDynamicAllocation auto operator = ( SharedPointer const & pointer ) noexcept -> SharedPointer & {
            if ( this == & pointer ) {
                return * this;
            }

            this-> SharedPointer :: reset(pointer );
            return * this;
        }

        __CDS_cpplang_ConstexprDynamicAllocation auto operator = ( typename PointerBase < T > :: Pointer pointer ) noexcept -> SharedPointer & {
            this-> SharedPointer :: reset(pointer);
            return * this;
        }

        __CDS_cpplang_ConstexprDestructor ~SharedPointer() noexcept override {
            this-> SharedPointer :: reset( nullptr );
        }

        __CDS_cpplang_ConstexprDynamicAllocation auto release () noexcept -> typename PointerBase<T>::Pointer final {
            auto pointer = this->pObj;
            this-> SharedPointer :: reset ( nullptr );
            return pointer;
        }

        __CDS_cpplang_ConstexprDynamicAllocation auto reset ( typename PointerBase<T>::Pointer pointer ) noexcept -> void final {
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

#include <CDS/Mutex>

namespace cds {

    template <class T>
    class __CDS_MaybeUnused AtomicSharedPointer final : public PointerBase<T> { // NOLINT(cppcoreguidelines-virtual-class-destructor)
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
                PointerBase<T>(pointer.pObj),
                pControl(pointer.pControl) {

            pointer.pControl->lock.lock();
            ++ pointer.pControl->ownerCount;
            pointer.pControl->lock.unlock();
        }

        __CDS_OptimalInline auto copy () const noexcept -> AtomicSharedPointer * override {
            return Memory :: instance().create < AtomicSharedPointer >(* this);
        }

        __CDS_OptimalInline AtomicSharedPointer(typename PointerBase<T>::Pointer pointer) noexcept : // NOLINT(google-explicit-constructor)
                PointerBase<T>(pointer),
                pControl(Memory :: instance().create < SharedPointerControlBlock > ()){

        }

        __CDS_OptimalInline auto operator = ( AtomicSharedPointer const & pointer ) noexcept -> AtomicSharedPointer & {
            if ( this == & pointer ) {
                return * this;
            }

            this-> AtomicSharedPointer :: reset(pointer );
            return * this;
        }

        __CDS_OptimalInline auto operator = ( typename PointerBase < T > :: Pointer pointer ) noexcept -> AtomicSharedPointer & {
            this-> AtomicSharedPointer :: reset(pointer );
            return * this;
        }

        __CDS_OptimalInline ~AtomicSharedPointer() noexcept final {
            this-> AtomicSharedPointer :: reset( nullptr );
        }

        __CDS_OptimalInline auto release () noexcept -> typename PointerBase<T>::Pointer final {
            auto pointer = this->pObj;
            this-> AtomicSharedPointer :: reset( nullptr );
            return pointer;
        }

        __CDS_OptionalInline auto reset ( typename PointerBase<T>::Pointer pointer ) noexcept -> void final {
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

        __CDS_OptionalInline auto reset ( AtomicSharedPointer const & pointer ) noexcept -> void final {
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

    template <class T>
    class ForeignPointer : public PointerBase<T> {
    public:
        constexpr ForeignPointer() noexcept : PointerBase<T>(nullptr) {}
        constexpr ForeignPointer(typename PointerBase<T>::Pointer pointer) noexcept : PointerBase<T>(pointer) {} // NOLINT(google-explicit-constructor)

        constexpr ForeignPointer( ForeignPointer const & pointer ) noexcept : PointerBase<T>(pointer.pObj) {}
        constexpr ForeignPointer( ForeignPointer && pointer ) noexcept : PointerBase<T>(pointer.release()) {}

        constexpr ForeignPointer ( UniquePointer < T > const & pointer ) noexcept : PointerBase <T> ( pointer.get() ) {}
        constexpr ForeignPointer ( UniquePointer < T > && ) noexcept = delete;

        __CDS_cpplang_NonConstConstexprMemberFunction auto operator = ( ForeignPointer const & pointer ) noexcept -> ForeignPointer & {
            if (&pointer == this ) {
                return * this;
            }

            this->reset(pointer.pObj );
            return * this;
        }

        __CDS_cpplang_NonConstConstexprMemberFunction auto operator = ( ForeignPointer && pointer ) noexcept -> ForeignPointer & {
            if (&pointer == this ) {
                return * this;
            }

            this->reset(pointer.release() );
            return * this;
        }

        __CDS_cpplang_NonConstConstexprMemberFunction auto operator = ( typename PointerBase < T > :: Pointer pointer ) noexcept -> ForeignPointer & {
            this->reset(pointer);
            return * this;
        }

        __CDS_cpplang_NonConstConstexprMemberFunction auto reset ( typename PointerBase<T>::Pointer pointer = nullptr ) noexcept -> void final {
            this->pObj = pointer;
        }
    };

}

#if __CDS_cpplang_CTAD_available

namespace cds {

    template < typename T >
    UniquePointer ( T * ) -> UniquePointer < T >;

    template < typename T >
    SharedPointer ( T * ) -> SharedPointer < T >;

    template < typename T >
    ForeignPointer ( T * ) -> ForeignPointer < T >;

    template < typename T >
    ForeignPointer ( const T * ) -> ForeignPointer < const T >;

}

#endif

namespace cds {

    template < typename T, typename ... Arguments >
    __CDS_NoDiscard __CDS_MaybeUnused __CDS_OptimalInline auto makeUnique ( Arguments && ... arguments ) noexcept -> UniquePointer < T > {
        return UniquePointer < T > ( Memory :: instance () . create < T > ( std :: forward < Arguments > ( arguments ) ... ) );
    }

    template < typename T, typename ... Arguments >
    __CDS_NoDiscard __CDS_MaybeUnused __CDS_OptimalInline auto makeShared ( Arguments && ... arguments ) noexcept -> SharedPointer < T > {
        return SharedPointer < T > ( Memory :: instance () . create < T > ( std :: forward < Arguments > ( arguments ) ... ) );
    }

    template < typename T, typename ... Arguments >
    __CDS_NoDiscard __CDS_MaybeUnused __CDS_OptimalInline auto makeAtomicShared ( Arguments && ... arguments ) noexcept -> AtomicSharedPointer < T > {
        return AtomicSharedPointer < T > ( Memory :: instance () . create < T > ( std :: forward < Arguments > ( arguments ) ... ) );
    }

    template < typename T >
    __CDS_NoDiscard __CDS_MaybeUnused __CDS_OptimalInline auto makeForeignPointer ( T * addr ) noexcept -> ForeignPointer < T > {
        return ForeignPointer < T > ( addr );
    }

}

__CDS_RegisterParseTypeTemplateT(PointerBase) // NOLINT(clion-misra-cpp2008-8-0-1)
__CDS_RegisterParseTypeTemplateT(UniquePointer) // NOLINT(clion-misra-cpp2008-8-0-1)
__CDS_RegisterParseTypeTemplateT(SharedPointer) // NOLINT(clion-misra-cpp2008-8-0-1)
__CDS_RegisterParseTypeTemplateT(AtomicSharedPointer) // NOLINT(clion-misra-cpp2008-8-0-1)
__CDS_RegisterParseTypeTemplateT(ForeignPointer) // NOLINT(clion-misra-cpp2008-8-0-1)

#endif //CDS_POINTER_HPP
