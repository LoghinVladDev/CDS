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

    template <class T>
    class PointerBase : public Object {
    public:
        using PointerType           = std::size_t;
        using Value                 = T;
        using ValueReference        = T &;
        using Pointer               = T *;
        using ConstPointer          = T const *;

    protected:
        Pointer mutable pObj {nullptr};

    public:

        constexpr PointerBase() noexcept = default;
        explicit constexpr PointerBase(Pointer p) noexcept : pObj(p) {}

        __CDS_cpplang_ConstexprDestructor ~PointerBase() noexcept override = default;

        __CDS_cpplang_ConstexprPureAbstract auto copy () const noexcept -> PointerBase * override = 0;

        __CDS_cpplang_VirtualConstexpr auto equals ( Object const & o ) const noexcept -> bool final {
            if ( this == & o ) return true;
            auto p = dynamic_cast < decltype (this) > ( & o );
            if ( p == nullptr ) return false;

            return this->operator==(*p);
        }

        constexpr auto operator == (PointerBase const & o) const noexcept -> bool {
            return this->pObj == o.pObj;
        }

        constexpr auto operator == (ConstPointer const p) const noexcept -> bool {
            return this->pObj == p;
        }

        constexpr auto operator == ( std :: nullptr_t p ) const noexcept -> bool {
            return this->pObj == p;
        }

        template < typename V >
        __CDS_OptimalInline auto operator == ( V const * const p ) const noexcept -> bool {
            return reinterpret_cast < decltype (this) > ( p ) == this;
        }

        constexpr auto operator != (PointerBase const & o) const noexcept -> bool {
            return this->pObj != o.pObj;
        }

        constexpr auto operator != (ConstPointer const p) const noexcept -> bool {
            return this->pObj != p;
        }

        constexpr auto operator != ( std :: nullptr_t p ) const noexcept -> bool {
            return this->pObj != p;
        }

        template < typename V >
        __CDS_OptimalInline auto operator != ( V const * const p ) const noexcept -> bool {
            return reinterpret_cast < decltype (this) > ( p ) != this;
        }

        __CDS_cpplang_ConstexprConditioned auto operator * () const noexcept (false) -> ValueReference {
            if ( this->pObj == nullptr )
                throw NullPointerException();
            return * this->pObj;
        }

        __CDS_cpplang_ConstexprConditioned auto valueAt () const noexcept (false) -> ValueReference {
            if ( this->pObj == nullptr )
                throw NullPointerException();
            return * this->pObj;
        }

        constexpr auto isNull () const noexcept -> bool { return this->pObj == nullptr; }

        __CDS_cpplang_ConstexprConditioned auto operator -> () const noexcept (false) -> Pointer {
            if ( this->pObj == nullptr )
                throw NullPointerException();

            return this->pObj;
        }

        constexpr explicit operator bool () const noexcept { return ! this->isNull(); }
        constexpr auto get () const noexcept -> Pointer { return this->pObj; }

        __CDS_cpplang_VirtualConstexpr virtual auto release () noexcept -> Pointer {
            return cds :: exchange ( this->pObj, nullptr );
        }

        __CDS_OptimalInline virtual auto reset ( Pointer p ) noexcept -> void {
            Memory::instance().destroy ( cds :: exchange ( this->pObj, p ) );
        }

        __CDS_OptimalInline auto reset () noexcept -> void {
            return this->reset ( nullptr );
        }

    private:
        template < typename U = T >
        __CDS_NoDiscard __CDS_OptionalInline auto ptrStringRep() const noexcept -> typename std::enable_if < Type < U > :: ostreamPrintable, String > :: type {
            std::stringstream oss;

            oss << "< 0x" << std::hex << reinterpret_cast < PointerType > ( pObj ) << std::dec << " : ";
            if ( pObj == nullptr ) oss << "null";
            else oss << (* pObj);

            oss << " >";
            return oss.str();
        }

        template < typename U = T >
        __CDS_NoDiscard __CDS_OptionalInline auto ptrStringRep() const noexcept -> typename std::enable_if < ! Type < U > :: ostreamPrintable, String > :: type {
            std::stringstream oss;

            oss << "< 0x" << std::hex << reinterpret_cast < PointerType > ( pObj ) << std::dec << " : ";
            if ( pObj == nullptr ) oss << "null";
            else oss << "unknown";

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
    class UniquePointer final : public PointerBase<T> {
    public:
        constexpr UniquePointer() noexcept = default;
        constexpr UniquePointer( typename PointerBase<T>::Pointer p ) noexcept : PointerBase<T>(p) { } // NOLINT(google-explicit-constructor)

        constexpr UniquePointer( UniquePointer const & o ) noexcept = delete;
        __CDS_cpplang_VirtualConstexpr UniquePointer( UniquePointer & o ) noexcept : PointerBase<T>(o.release()) { }
        __CDS_cpplang_VirtualConstexpr UniquePointer( UniquePointer && o ) noexcept : PointerBase<T>(o.release()) { }

        __CDS_cpplang_VirtualConstexpr auto copy () const noexcept -> UniquePointer * override {
            return nullptr;
        }

        __CDS_cpplang_NonConstConstexprMemberFunction auto operator = ( UniquePointer && p ) noexcept -> UniquePointer & {
            if ( &p == this ) return * this;

            this->reset(p.release());
            return * this;
        }

        __CDS_cpplang_NonConstConstexprMemberFunction auto operator = ( UniquePointer & p ) noexcept -> UniquePointer & { // NOLINT(misc-unconventional-assign-operator)
            if ( &p == this ) return * this;

            this->reset(p.release());
            return * this;
        }

        __CDS_cpplang_NonConstConstexprMemberFunction auto operator = ( typename PointerBase < T > :: Pointer p ) noexcept -> UniquePointer & {
            this->reset(p);
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
    class SharedPointer : public PointerBase<T> {
    private:
        struct SharedPointerControlBlock {
            int ownerCount {1};

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
        __CDS_OptimalInline SharedPointer(SharedPointer const & p) noexcept :
                PointerBase<T>(p.pObj),
                pControl(p.pControl) {

            ++ p.pControl->ownerCount;
        }

        __CDS_cpplang_VirtualConstexpr auto copy () const noexcept -> SharedPointer * override {
            return Memory :: instance().create < SharedPointer > (* this);
        }

        __CDS_cpplang_ConstexprDynamicAllocation SharedPointer(typename PointerBase<T>::Pointer p) noexcept : // NOLINT(google-explicit-constructor)
                PointerBase<T>(p),
                pControl(Memory :: instance().create < SharedPointerControlBlock > ()){

        }

        __CDS_cpplang_ConstexprDynamicAllocation auto operator = ( SharedPointer const & o ) noexcept -> SharedPointer & {
            if ( this == & o )
                return * this;

            this-> SharedPointer :: reset( o );
            return * this;
        }

        __CDS_cpplang_ConstexprDynamicAllocation auto operator = ( typename PointerBase < T > :: Pointer p ) noexcept -> SharedPointer & {
            this-> SharedPointer :: reset(p);
            return * this;
        }

        __CDS_cpplang_ConstexprDestructor ~SharedPointer() noexcept override {
            this-> SharedPointer :: reset( nullptr );
        }

        __CDS_cpplang_ConstexprDynamicAllocation auto release () noexcept -> typename PointerBase<T>::Pointer final {
            auto p = this->pObj;
            this-> SharedPointer :: reset ( nullptr );
            return p;
        }

        __CDS_cpplang_ConstexprDynamicAllocation auto reset ( typename PointerBase<T>::Pointer p ) noexcept -> void final {
            if ( this->pObj == p ) return;

            auto pVal = this->pObj;
            this->pObj = p;

            if ( this->pControl != nullptr ) {
                if ( -- this->pControl->ownerCount == 0 ) {
                    Memory :: instance().destroy ( this->pControl );
                    Memory :: instance().destroy ( pVal );
                }

                this->pControl = nullptr;
            }

            if ( this->pObj != nullptr )
                this->pControl = Memory :: instance () .create < SharedPointerControlBlock > ();
        }

        __CDS_cpplang_ConstexprDynamicAllocation auto reset ( SharedPointer const & p ) noexcept -> void {
            if ( this->pControl == p.pControl ) return;

            auto oldAddress = this->pObj;
            this->pObj = p.pObj;

            if ( this->pControl != nullptr ) {
                if ( -- this->pControl->ownerCount == 0 ) {
                    Memory :: instance().destroy ( this->pControl );
                    Memory :: instance().destroy ( oldAddress );
                }

                this->pControl = nullptr;
            }

            if ( p.pControl != nullptr ) {
                this->pControl = p.pControl;
                ++ this->pControl->ownerCount;
            }
        }
    };

}

#include <CDS/Mutex>

namespace cds {

    template <class T>
    class __CDS_MaybeUnused AtomicSharedPointer final : public PointerBase<T> {
    private:
        struct SharedPointerControlBlock {
            int ownerCount = 1u;
            Mutex lock;

            SharedPointerControlBlock() noexcept = default;
        };

        SharedPointerControlBlock * pControl { nullptr };

    public:
        constexpr AtomicSharedPointer() noexcept = default;
        __CDS_OptimalInline AtomicSharedPointer(AtomicSharedPointer const & p) noexcept :
                PointerBase<T>(p.pObj),
                pControl(p.pControl) {

            p.pControl->lock.lock();
            ++ p.pControl->ownerCount;
            p.pControl->lock.unlock();
        }

        __CDS_OptimalInline auto copy () const noexcept -> AtomicSharedPointer * override {
            return Memory :: instance().create < AtomicSharedPointer >(* this);
        }

        __CDS_OptimalInline AtomicSharedPointer(typename PointerBase<T>::Pointer p) noexcept : // NOLINT(google-explicit-constructor)
                PointerBase<T>(p),
                pControl(Memory :: instance().create < SharedPointerControlBlock > ()){

        }

        __CDS_OptimalInline auto operator = ( AtomicSharedPointer const & o ) noexcept -> AtomicSharedPointer & {
            if ( this == & o )
                return * this;

            this-> AtomicSharedPointer :: reset( o );
            return * this;
        }

        __CDS_OptimalInline auto operator = ( typename PointerBase < T > :: Pointer p ) noexcept -> AtomicSharedPointer & {
            this-> AtomicSharedPointer :: reset( p );
            return * this;
        }

        __CDS_OptimalInline ~AtomicSharedPointer() noexcept final {
            this-> AtomicSharedPointer :: reset( nullptr );
        }

        __CDS_OptimalInline auto release () noexcept -> typename PointerBase<T>::Pointer final {
            auto p = this->pObj;
            this-> AtomicSharedPointer :: reset( nullptr );
            return p;
        }

        __CDS_OptionalInline auto reset ( typename PointerBase<T>::Pointer p ) noexcept -> void final {
            if ( this->pObj == p ) return;

            auto pVal = this->pObj;
            this->pObj = p;

            if ( this->pControl != nullptr ) {
                if ( this->pControl->ownerCount == 1 ) {
                    Memory::instance().destroy ( this->pControl );
                    Memory::instance().destroy ( pVal );
                }

                this->pControl = nullptr;
            }

            if ( this->pObj != nullptr )
                this->pControl = Memory :: instance().create < SharedPointerControlBlock > ();
        }

        __CDS_OptionalInline auto reset ( AtomicSharedPointer const & p ) noexcept -> void final {
            if ( this->pControl == p.pControl ) return;

            auto oldAddress = this->pObj;
            this->pObj = p;

            if ( this->pControl != nullptr ) {
                if ( this->pControl->ownerCount == 1 ) {
                    Memory::instance().destroy ( this->pControl );
                    Memory::instance().destroy ( oldAddress );
                }

                this->pControl = nullptr;
            }

            if ( p.pControl != nullptr ) {
                this->pControl = p.pControl;
                p.pControl->lock.lock();
                ++ this->pControl->ownerCount;
                p.pControl->lock.unlock();
            }
        }
    };

    template <class T>
    class ForeignPointer : public PointerBase<T> {
    public:
        constexpr ForeignPointer() noexcept : PointerBase<T>(nullptr) {}
        constexpr ForeignPointer(typename PointerBase<T>::Pointer p) noexcept : PointerBase<T>(p) {} // NOLINT(google-explicit-constructor)

        constexpr ForeignPointer( ForeignPointer const & o ) noexcept : PointerBase<T>(o.pObj) {}
        constexpr ForeignPointer( ForeignPointer && o ) noexcept : PointerBase<T>(o.release()) {}

        __CDS_cpplang_VirtualConstexpr auto copy () const noexcept -> ForeignPointer * override {
            return Memory :: instance().create < ForeignPointer > ( * this );
        }

        __CDS_cpplang_NonConstConstexprMemberFunction auto operator = ( ForeignPointer const & p ) noexcept -> ForeignPointer & {
            if ( &p == this ) return * this;

            this->reset( p.pObj );
            return * this;
        }

        __CDS_cpplang_NonConstConstexprMemberFunction auto operator = ( ForeignPointer && o ) noexcept -> ForeignPointer & {
            if ( &o == this ) return * this;

            this->reset( o.release() );
            return * this;
        }

        __CDS_cpplang_NonConstConstexprMemberFunction auto operator = ( typename PointerBase < T > :: Pointer p ) noexcept -> ForeignPointer & {
            this->reset(p);
            return * this;
        }

        __CDS_cpplang_NonConstConstexprMemberFunction auto reset ( typename PointerBase<T>::Pointer p = nullptr ) noexcept -> void final {
            this->pObj = p;
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

__CDS_RegisterParseTypeTemplateT(PointerBase)
__CDS_RegisterParseTypeTemplateT(UniquePointer)
__CDS_RegisterParseTypeTemplateT(SharedPointer)
__CDS_RegisterParseTypeTemplateT(AtomicSharedPointer)
__CDS_RegisterParseTypeTemplateT(ForeignPointer)

#endif //CDS_POINTER_HPP
