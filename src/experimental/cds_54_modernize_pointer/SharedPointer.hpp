/*
 * Created by loghin on 5/1/22.
 */

#ifndef __CDS_SHARED_POINTER_HPP__ /* NOLINT(llvm-header-guard) */
#define __CDS_SHARED_POINTER_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

#include <CDS/memory/SmartPointer>
#include <CDS/threading/Atomic>

namespace cds {

    namespace __hidden {
        namespace __impl {

            class __SharedPointerControlBlock {

            private:
                Atomic < uint32 >           _ownerCount;

            private:
                Atomic < uint32 >           _observerCount;

            private:
                std :: atomic_flag          _dataExpired;

            private:
                std :: atomic_flag          _blockExpired;

            public:
                static auto __new () noexcept -> __SharedPointerControlBlock *;

            public:
                auto __use () noexcept -> __SharedPointerControlBlock *;

            public:
                auto __release () noexcept -> bool;

            public:
                auto __disposeSelf () noexcept -> void;
            };

        }
    }

    template < typename __ElementType, typename __Deleter > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    class SharedPointer : public SmartPointer < __ElementType > {

    private:
        using Base = SmartPointer < __ElementType >;

    private:
        using ControlBlock = __hidden :: __impl :: __SharedPointerControlBlock;

    private:
        ControlBlock * _pControl { nullptr };

    public:
        SharedPointer () noexcept;

    public:
        SharedPointer (
                __ElementType * pointer
        ) noexcept;

    public:
        SharedPointer (
                SharedPointer const & pointer
        ) noexcept;

    public:
        constexpr SharedPointer (
                SharedPointer && pointer
        ) noexcept;

    public:
        SharedPointer (
                WeakPointer < __ElementType, __Deleter > const &
        ) noexcept;

    public:
        SharedPointer (
                WeakPointer < __ElementType, __Deleter > &&
        ) noexcept;

    public:
        ~SharedPointer () noexcept;

    public:
        auto operator = (
                __ElementType * pointer
        ) noexcept -> SharedPointer &;

    public:
        auto operator = (
                SharedPointer const & pointer
        ) noexcept -> SharedPointer &;

    public:
        auto operator = (
                SharedPointer && pointer
        ) noexcept -> SharedPointer &;

    public:
        auto operator = (
                WeakPointer < __ElementType, __Deleter > const & pointer
        ) noexcept -> SharedPointer &;

    public:
        auto operator = (
                WeakPointer < __ElementType, __Deleter > && pointer
        ) noexcept -> SharedPointer &;

    public:
        auto exchange (
                __ElementType * pointer
        ) noexcept -> __ElementType * override;

    public:
        auto release () noexcept -> __ElementType * override;

    public:
        auto reset () noexcept -> void override;

    public:
        auto reset (
                __ElementType * pointer
        ) noexcept -> void override;
    };


    template < typename __ElementType, typename __Deleter > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    class SharedPointer < __ElementType [], __Deleter > : public SmartPointer < __ElementType > {

    private:
        using Base = SmartPointer < __ElementType >;

    private:
        using ControlBlock = __hidden :: __impl :: __SharedPointerControlBlock;

    private:
        ControlBlock * _pControl { nullptr };

    public:
        SharedPointer () noexcept;

    public:
        SharedPointer (
                __ElementType * pointer
        ) noexcept;

    public:
        SharedPointer (
                SharedPointer const & pointer
        ) noexcept;

    public:
        constexpr SharedPointer (
                SharedPointer && pointer
        ) noexcept;

    public:
        SharedPointer (
                WeakPointer < __ElementType, __Deleter > const &
        ) noexcept;

    public:
        SharedPointer (
                WeakPointer < __ElementType, __Deleter > &&
        ) noexcept;

    public:
        ~SharedPointer () noexcept;

    public:
        auto operator = (
                __ElementType * pointer
        ) noexcept -> SharedPointer &;

    public:
        auto operator = (
                SharedPointer const & pointer
        ) noexcept -> SharedPointer &;

    public:
        auto operator = (
                SharedPointer && pointer
        ) noexcept -> SharedPointer &;

    public:
        auto operator = (
                WeakPointer < __ElementType, __Deleter > const & pointer
        ) noexcept -> SharedPointer &;

    public:
        auto operator = (
                WeakPointer < __ElementType, __Deleter > && pointer
        ) noexcept -> SharedPointer &;

    public:
        auto exchange (
                __ElementType * pointer
        ) noexcept -> __ElementType * override;

    public:
        auto release () noexcept -> __ElementType * override;

    public:
        auto reset () noexcept -> void override;

    public:
        auto reset (
                __ElementType * pointer
        ) noexcept -> void override;

    public:
        template < typename __NumericType >
        __CDS_NoDiscard constexpr auto operator [] (
                __NumericType index
        ) const noexcept -> __ElementType &;
    };

} /* namespace cds */

#include "pointer/impl/SharedPointer.hpp"

#endif /* __CDS_SHARED_POINTER_HPP__ */
