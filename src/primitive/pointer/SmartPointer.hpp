//
// Created by loghin on 5/1/22.
//

#ifndef __CDS_SMART_POINTER_HPP__
#define __CDS_SMART_POINTER_HPP__

#include <CDS/Object>
#include <sstream>

#include <CDS/Traits>
#include <CDS/Utility>
#include <CDS/Memory>

namespace cds {

    template < typename T >
    class SmartPointer : public Object {
    public:
        using PointerType           = std::size_t;
        using Value                 = T;
        using ValueReference        = T &;
        using Pointer               = T *;
        using ConstPointer          = T const *;

    protected:
        Pointer mutable pObj {nullptr}; // NOLINT(clion-misra-cpp2008-11-0-1)

    protected:
        constexpr SmartPointer() noexcept = default;
        explicit constexpr SmartPointer(Pointer pointer) noexcept : pObj(pointer) {}

        template < typename DerivedType, EnableIf < isDerivedFrom < DerivedType, T > :: value > = 0 >
        explicit constexpr SmartPointer(DerivedType pointer) noexcept : pObj ( (T*) pointer ) { }

    public:
        __CDS_cpplang_ConstexprDestructor ~SmartPointer() noexcept override = default;

        __CDS_cpplang_VirtualConstexpr auto equals ( Object const & object ) const noexcept -> bool final {
            if ( this == & object ) {
                return true;
            }

            auto pPointerBase = dynamic_cast < SmartPointer < T > const * > ( & object );
            if (pPointerBase == nullptr ) {
                return false;
            }

            return this->operator==(*pPointerBase);
        }

        constexpr auto operator == (SmartPointer const & pointerBase) const noexcept -> bool {
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

        constexpr auto operator != (SmartPointer const & pointerBase) const noexcept -> bool {
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

}

#endif // __CDS_SMART_POINTER_HPP__
