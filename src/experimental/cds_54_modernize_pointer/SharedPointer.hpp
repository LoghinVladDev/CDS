/*
 * Created by loghin on 5/1/22.
 */

#ifndef __CDS_SHARED_POINTER_HPP__ /* NOLINT(llvm-header-guard) */
#define __CDS_SHARED_POINTER_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

#include <CDS/memory/SmartPointer>
#include <CDS/threading/Atomic>

#include "pointer/SharedPointerControlBlock.hpp"

namespace cds {

    template < typename __ElementType, typename __Deleter > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    class SharedPointer : public SmartPointer < __ElementType > {

    private:
        friend class WeakPointer < __ElementType, __Deleter >;

    private:
        using Base = SmartPointer < __ElementType >;

    private:
        using ControlBlock = __hidden :: __impl :: __SharedPointerControlBlock < __ElementType >;

    private:
        ControlBlock * _pControl { nullptr };

    public:
        SharedPointer () noexcept;

    public:
        __CDS_Implicit SharedPointer (
                std :: nullptr_t pointer
        ) noexcept;

    public:
        __CDS_Implicit SharedPointer (
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
                WeakPointer < __ElementType, __Deleter > const & pointer
        ) noexcept;

    public:
        SharedPointer (
                WeakPointer < __ElementType, __Deleter > && pointer
        ) noexcept;

    public:
        ~SharedPointer () noexcept;

    public:
        auto operator = (
                std :: nullptr_t pointer
        ) noexcept -> SharedPointer &;

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
        __CDS_NoDiscard constexpr auto operator == (
                __ElementType const * pointer
        ) const noexcept -> bool;

    public:
        __CDS_NoDiscard constexpr auto operator != (
                __ElementType const * pointer
        ) const noexcept -> bool;

    public:
        __CDS_NoDiscard __CDS_cpplang_VirtualConstexpr auto operator == (
                Base const & pointer
        ) const noexcept -> bool;

    public:
        __CDS_NoDiscard __CDS_cpplang_VirtualConstexpr auto operator != (
                Base const & pointer
        ) const noexcept -> bool;

    public:
        __CDS_NoDiscard constexpr auto operator == (
                SharedPointer const & pointer
        ) const noexcept -> bool;

    public:
        __CDS_NoDiscard constexpr auto operator != (
                SharedPointer const & pointer
        ) const noexcept -> bool;

    public:
        __CDS_NoDiscard constexpr auto operator == (
                std :: nullptr_t pointer
        ) const noexcept -> bool;

    public:
        __CDS_NoDiscard constexpr auto operator != (
                std :: nullptr_t pointer
        ) const noexcept -> bool;

    public:
        __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto valueAt () const noexcept (false) -> __ElementType &;

    public:
        __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto get () const noexcept -> __ElementType *;

    public:
        auto exchange (
                __ElementType * pointer
        ) noexcept -> __ElementType * override;

    public:
        auto exchange (
                std :: nullptr_t pointer
        ) noexcept -> __ElementType *;

    public:
        auto release () noexcept -> __ElementType * override;

    public:
        auto reset () noexcept -> void override;

    public:
        auto reset (
                std :: nullptr_t pointer
        ) noexcept -> void;

    public:
        auto reset (
                __ElementType * pointer
        ) noexcept -> void override;
    };


    template < typename __ElementType, typename __Deleter > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    class SharedPointer < __ElementType [], __Deleter > : public SmartPointer < __ElementType [] > {

    private:
        friend class WeakPointer < __ElementType [], __Deleter >;

    private:
        using Base = SmartPointer < __ElementType >;

    private:
        using ControlBlock = __hidden :: __impl :: __SharedPointerControlBlock < __ElementType >;

    private:
        ControlBlock * _pControl { nullptr };

    public:
        SharedPointer () noexcept;

    public:
        __CDS_Implicit SharedPointer (
                std :: nullptr_t pointer
        ) noexcept;

    public:
        __CDS_Implicit SharedPointer (
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
                WeakPointer < __ElementType, __Deleter > const & pointer
        ) noexcept;

    public:
        SharedPointer (
                WeakPointer < __ElementType, __Deleter > && pointer
        ) noexcept;

    public:
        ~SharedPointer () noexcept;

    public:
        auto operator = (
                std :: nullptr_t pointer
        ) noexcept -> SharedPointer &;

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
        __CDS_NoDiscard constexpr auto operator == (
                __ElementType const * pointer
        ) const noexcept -> bool;

    public:
        __CDS_NoDiscard constexpr auto operator != (
                __ElementType const * pointer
        ) const noexcept -> bool;

    public:
        __CDS_NoDiscard __CDS_cpplang_VirtualConstexpr auto operator == (
                Base const & pointer
        ) const noexcept -> bool;

    public:
        __CDS_NoDiscard __CDS_cpplang_VirtualConstexpr auto operator != (
                Base const & pointer
        ) const noexcept -> bool;

    public:
        __CDS_NoDiscard constexpr auto operator == (
                SharedPointer const & pointer
        ) const noexcept -> bool;

    public:
        __CDS_NoDiscard constexpr auto operator != (
                SharedPointer const & pointer
        ) const noexcept -> bool;

    public:
        __CDS_NoDiscard constexpr auto operator == (
                std :: nullptr_t pointer
        ) const noexcept -> bool;

    public:
        __CDS_NoDiscard constexpr auto operator != (
                std :: nullptr_t pointer
        ) const noexcept -> bool;

    public:
        __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto valueAt () const noexcept (false) -> __ElementType &;

    public:
        __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto get () const noexcept -> __ElementType *;

    public:
        auto exchange (
                std :: nullptr_t pointer
        ) noexcept -> __ElementType *;

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
                std :: nullptr_t pointer
        ) noexcept -> void;

    public:
        auto reset (
                __ElementType * pointer
        ) noexcept -> void override;
    };

} /* namespace cds */

#include "pointer/impl/SharedPointer.hpp"
#include "pointer/impl/SharedPointerControlBlock.hpp"

#endif /* __CDS_SHARED_POINTER_HPP__ */
