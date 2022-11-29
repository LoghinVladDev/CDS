/*
 * Created by loghin on 28/11/22.
 */

#ifndef __CDS_RAW_POINTER_HPP__ /* NOLINT(llvm-header-guard) */
#define __CDS_RAW_POINTER_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

#include <CDS/memory/SmartPointer>

namespace cds {

    template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    class RawPointer : public SmartPointer < __ElementType > {

    private:
        using Base = SmartPointer < __ElementType >;

    private:
        __ElementType * _pObject { nullptr };

    public:
        constexpr RawPointer () noexcept = default;

    public:
        __CDS_Explicit constexpr RawPointer (
                __ElementType * pointer
        ) noexcept;

    public:
        constexpr RawPointer (
                RawPointer const & pointer
        ) noexcept;

    public:
        constexpr RawPointer (
                RawPointer && pointer
        ) noexcept;

    public:
        __CDS_cpplang_ConstexprDestructor ~RawPointer () noexcept override = default;

    public:
        __CDS_cpplang_NonConstConstexprMemberFunction auto operator = (
                __ElementType * pointer
        ) noexcept -> RawPointer &;

    public:
        __CDS_cpplang_NonConstConstexprMemberFunction auto operator = (
                RawPointer const & pointer
        ) noexcept -> RawPointer &;

    public:
        __CDS_cpplang_NonConstConstexprMemberFunction auto operator = (
                RawPointer && pointer
        ) noexcept -> RawPointer &;

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
                RawPointer const & pointer
        ) const noexcept -> bool;

    public:
        __CDS_NoDiscard constexpr auto operator != (
                RawPointer const & pointer
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
        __CDS_cpplang_ConstexprOverride auto reset () noexcept -> void override;

    public:
        __CDS_cpplang_ConstexprOverride auto reset (
                __ElementType * pointer
        ) noexcept -> void override;
    };


    template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    class RawPointer < __ElementType [] > : public SmartPointer < __ElementType [] > {

    private:
        using Base = SmartPointer < __ElementType >;

    private:
        __ElementType * _pObject { nullptr };

    public:
        constexpr RawPointer () noexcept = default;

    public:
        __CDS_Explicit constexpr RawPointer (
                __ElementType * pointer
        ) noexcept;

    public:
        constexpr RawPointer (
                RawPointer const & pointer
        ) noexcept;

    public:
        constexpr RawPointer (
                RawPointer && pointer
        ) noexcept;

    public:
        __CDS_cpplang_ConstexprDestructor ~RawPointer () noexcept override = default;

    public:
        __CDS_cpplang_NonConstConstexprMemberFunction auto operator = (
                __ElementType * pointer
        ) noexcept -> RawPointer &;

    public:
        __CDS_cpplang_NonConstConstexprMemberFunction auto operator = (
                RawPointer const & pointer
        ) noexcept -> RawPointer &;

    public:
        __CDS_cpplang_NonConstConstexprMemberFunction auto operator = (
                RawPointer && pointer
        ) noexcept -> RawPointer &;

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
                RawPointer const & pointer
        ) const noexcept -> bool;

    public:
        __CDS_NoDiscard constexpr auto operator != (
                RawPointer const & pointer
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
        __CDS_cpplang_ConstexprOverride auto reset () noexcept -> void override;

    public:
        __CDS_cpplang_ConstexprOverride auto reset (
                __ElementType * pointer
        ) noexcept -> void override;
    };

} /* namespace cds */

#include "pointer/impl/RawPointer.hpp"

#endif /* __CDS_RAW_POINTER_HPP__ */
