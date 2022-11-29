/*
 * Created by loghin on 26.01.2021.
 */

#ifndef __CDS_UNIQUE_POINTER_HPP__ /* NOLINT(llvm-header-guard) */
#define __CDS_UNIQUE_POINTER_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

#include <CDS/memory/SmartPointer>

namespace cds {

    template < typename __ElementType, typename __Deleter > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    class UniquePointer : public SmartPointer < __ElementType > {

    private:
        using Base = SmartPointer < __ElementType >;

    private:
        __ElementType * _pObject { nullptr };

    public:
        constexpr UniquePointer () noexcept = default;

    public:
        constexpr UniquePointer (
                __ElementType * pointer
        ) noexcept;

    public:
        UniquePointer (
                UniquePointer const & /* pointer */
        ) noexcept = delete;

    public:
        constexpr UniquePointer (
                UniquePointer && pointer
        ) noexcept;

    public:
        __CDS_cpplang_ConstexprDestructor ~UniquePointer () noexcept override;

    public:
        auto operator = (
                __ElementType * pointer
        ) noexcept -> UniquePointer &;

    public:
        auto operator = (
                UniquePointer const & pointer
        ) noexcept -> UniquePointer & = delete;

    public:
        auto operator = (
                UniquePointer && pointer
        ) noexcept -> UniquePointer &;

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
                UniquePointer const & pointer
        ) const noexcept -> bool;

    public:
        __CDS_NoDiscard constexpr auto operator != (
                UniquePointer const & pointer
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
        __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto valueAt () const noexcept (false) -> __ElementType & override;

    public:
        __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto get () const noexcept -> __ElementType * override;

    public:
        __CDS_cpplang_ConstexprOverride auto exchange (
                __ElementType * pointer
        ) noexcept -> __ElementType * override;

    public:
        __CDS_cpplang_ConstexprOverride auto release () noexcept -> __ElementType * override;

    public:
        auto reset () noexcept -> void override;

    public:
        auto reset (
                __ElementType * pointer
        ) noexcept -> void override;
    };


    template < typename __ElementType, typename __Deleter > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    class UniquePointer < __ElementType [], __Deleter > : public SmartPointer < __ElementType [] > {

    private:
        using Base = SmartPointer < __ElementType >;

    private:
        __ElementType * _pObject { nullptr };

    public:
        constexpr UniquePointer () noexcept = default;

    public:
        constexpr UniquePointer (
                __ElementType * pointer
        ) noexcept;

    public:
        UniquePointer (
                UniquePointer const & /* pointer */
        ) noexcept = delete;

    public:
        constexpr UniquePointer (
                UniquePointer && pointer
        ) noexcept;

    public:
        __CDS_cpplang_ConstexprDestructor ~UniquePointer () noexcept override;

    public:
        auto operator = (
                __ElementType * pointer
        ) noexcept -> UniquePointer &;

    public:
        auto operator = (
                UniquePointer const & pointer
        ) noexcept -> UniquePointer & = delete;

    public:
        auto operator = (
                UniquePointer && pointer
        ) noexcept -> UniquePointer &;

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
                UniquePointer const & pointer
        ) const noexcept -> bool;

    public:
        __CDS_NoDiscard constexpr auto operator != (
                UniquePointer const & pointer
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
        __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto valueAt () const noexcept (false) -> __ElementType & override;

    public:
        __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto get () const noexcept -> __ElementType * override;

    public:
        __CDS_cpplang_ConstexprOverride auto exchange (
                __ElementType * pointer
        ) noexcept -> __ElementType * override;

    public:
        __CDS_cpplang_ConstexprOverride auto release () noexcept -> __ElementType * override;

    public:
        auto reset () noexcept -> void override;

    public:
        auto reset (
                __ElementType * pointer
        ) noexcept -> void override;
    };

} /* namespace cds */

#include "pointer/impl/UniquePointer.hpp"

#endif /* __CDS_UNIQUE_POINTER_HPP__ */
