//
// Created by loghin on 5/1/22.
//

#ifndef __CDS_UNIQUE_POINTER_HPP__
#define __CDS_UNIQUE_POINTER_HPP__

#include <CDS/smartPointers/SmartPointer>

namespace cds {

    template < typename T >
    class UniquePointer : public SmartPointer < T > { // NOLINT(cppcoreguidelines-virtual-class-destructor)
    public:
        constexpr UniquePointer() noexcept = default;
        constexpr UniquePointer( typename SmartPointer < T > :: Pointer pointer ) noexcept : SmartPointer<T>(pointer) { } // NOLINT(google-explicit-constructor)

        constexpr UniquePointer( UniquePointer const & pointer ) noexcept = delete;

        __CDS_cpplang_VirtualConstexpr UniquePointer( UniquePointer & pointer ) noexcept : SmartPointer<T>(pointer.release()) { }
        __CDS_cpplang_VirtualConstexpr UniquePointer( UniquePointer && pointer ) noexcept : SmartPointer<T>(pointer.release()) { }

        template < typename DerivedType, meta :: EnableIf < meta :: isDerivedFrom < DerivedType, T > () > = 0 >
        __CDS_cpplang_VirtualConstexpr UniquePointer ( UniquePointer < DerivedType > && pointer ) noexcept : SmartPointer < T > ( pointer.release() ) { } // NOLINT(google-explicit-constructor)

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

        __CDS_cpplang_NonConstConstexprMemberFunction auto operator = ( typename SmartPointer < T > :: Pointer pointer ) noexcept -> UniquePointer & {
            this->reset(pointer);
            return * this;
        }

        template < typename D, meta :: EnableIf < meta :: isDerivedFrom < meta :: RemovePointer < D >, T > () > = 0 >
        __CDS_cpplang_NonConstConstexprMemberFunction auto operator = ( D pointer ) noexcept -> UniquePointer & {
            this->reset((T *)pointer);
            return * this;
        }

        __CDS_cpplang_NonConstConstexprMemberFunction auto operator = ( decltype(nullptr) ) noexcept -> UniquePointer & {
            this->reset();
            return * this;
        }

        __CDS_cpplang_ConstexprDestructor ~UniquePointer() noexcept override {
            Memory :: instance () . destroy ( this->pObj );
        }
    };

    template < typename T, typename ... ArgumentTypes >
    __CDS_NoDiscard __CDS_MaybeUnused __CDS_OptimalInline auto makeUnique ( ArgumentTypes && ... arguments ) noexcept -> UniquePointer < T > {
        return UniquePointer < T > ( Memory :: instance ().create < T > ( std :: forward < ArgumentTypes > ( arguments ) ... ) );
    }

}

#endif // __CDS_UNIQUE_POINTER_HPP__
