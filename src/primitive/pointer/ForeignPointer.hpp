//
// Created by loghin on 5/1/22.
//

#ifndef __CDS_FOREIGN_POINTER_HPP__
#define __CDS_FOREIGN_POINTER_HPP__

#include <CDS/pointer/SmartPointer>

namespace cds {

    template < typename T >
    class ForeignPointer : public SmartPointer<T> {
    public:
        constexpr ForeignPointer() noexcept : SmartPointer<T>(nullptr) {}
        constexpr ForeignPointer(typename SmartPointer<T>::Pointer pointer) noexcept : SmartPointer<T>(pointer) {} // NOLINT(google-explicit-constructor)

        constexpr ForeignPointer( ForeignPointer const & pointer ) noexcept : SmartPointer<T>(pointer.pObj) {}
        constexpr ForeignPointer( ForeignPointer && pointer ) noexcept : SmartPointer<T>(pointer.release()) {}

        constexpr ForeignPointer ( SmartPointer < T > const & pointer ) noexcept : SmartPointer <T> ( pointer.get() ) {}
        constexpr ForeignPointer ( SmartPointer < T > && ) noexcept = delete;

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

        __CDS_cpplang_NonConstConstexprMemberFunction auto operator = ( typename SmartPointer < T > :: Pointer pointer ) noexcept -> ForeignPointer & {
            this->reset(pointer);
            return * this;
        }

        __CDS_cpplang_NonConstConstexprMemberFunction auto reset ( typename SmartPointer<T>::Pointer pointer = nullptr ) noexcept -> void override {
            this->pObj = pointer;
        }
    };

}

#endif // __CDS_FOREIGN_POINTER_HPP__
