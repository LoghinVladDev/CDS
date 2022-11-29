/* NOLINT(llvm-header-guard)
 * Created by loghin on 26.01.2021.
 */

#ifndef __CDS_UNIQUE_POINTER_HPP__ /* NOLINT(llvm-header-guard) */
#define __CDS_UNIQUE_POINTER_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

#include <CDS/memory/SmartPointer>

namespace cds {

    template < typename __ElementType, typename __Deleter > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    class UniquePointer : public SmartPointer < __ElementType > {

    private:    /* NOLINT(readability-redundant-access-specifiers) */
        using Base = SmartPointer < __ElementType >;

    private:    /* NOLINT(readability-redundant-access-specifiers) */
        __ElementType * _pObject { nullptr };

    public: /* NOLINT(readability-redundant-access-specifiers) */
        constexpr UniquePointer () noexcept = default;

    public:                                         /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_Implicit constexpr UniquePointer (    /* NOLINT(*-explicit-*) */
                __ElementType * pointer
        ) noexcept;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        UniquePointer (
                UniquePointer const & /* pointer */
        ) noexcept = delete;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        constexpr UniquePointer (
                UniquePointer && pointer
        ) noexcept;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_cpplang_ConstexprDestructor ~UniquePointer () noexcept override;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        auto operator = (
                __ElementType * pointer
        ) noexcept -> UniquePointer &;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        auto operator = (
                UniquePointer const & pointer
        ) noexcept -> UniquePointer & = delete;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        auto operator = (
                UniquePointer && pointer
        ) noexcept -> UniquePointer &;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard constexpr auto operator == (
                __ElementType const * pointer
        ) const noexcept -> bool;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard constexpr auto operator != (
                __ElementType const * pointer
        ) const noexcept -> bool;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard __CDS_cpplang_VirtualConstexpr auto operator == (
                Base const & pointer
        ) const noexcept -> bool;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard __CDS_cpplang_VirtualConstexpr auto operator != (
                Base const & pointer
        ) const noexcept -> bool;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard constexpr auto operator == (
                UniquePointer const & pointer
        ) const noexcept -> bool;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard constexpr auto operator != (
                UniquePointer const & pointer
        ) const noexcept -> bool;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard constexpr auto operator == (
                std :: nullptr_t pointer
        ) const noexcept -> bool;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard constexpr auto operator != (
                std :: nullptr_t pointer
        ) const noexcept -> bool;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto valueAt () const noexcept (false) -> __ElementType & override;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto get () const noexcept -> __ElementType * override;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_cpplang_ConstexprOverride auto exchange (
                __ElementType * pointer
        ) noexcept -> __ElementType * override;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_cpplang_ConstexprOverride auto release () noexcept -> __ElementType * override;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        auto reset () noexcept -> void override;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        auto reset (
                __ElementType * pointer
        ) noexcept -> void override;
    };


    template < typename __ElementType, typename __Deleter >                                             /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    class UniquePointer < __ElementType [], __Deleter > : public SmartPointer < __ElementType [] > {    /* NOLINT(*-avoid-c-arrays) */

    private:    /* NOLINT(readability-redundant-access-specifiers) */
        using Base = SmartPointer < __ElementType >;

    private:    /* NOLINT(readability-redundant-access-specifiers) */
        __ElementType * _pObject { nullptr };

    public: /* NOLINT(readability-redundant-access-specifiers) */
        constexpr UniquePointer () noexcept = default;

    public:                                         /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_Implicit constexpr UniquePointer (    /* NOLINT(*-explicit-*) */
                __ElementType * pointer
        ) noexcept;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        UniquePointer (
                UniquePointer const & /* pointer */
        ) noexcept = delete;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        constexpr UniquePointer (
                UniquePointer && pointer
        ) noexcept;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_cpplang_ConstexprDestructor ~UniquePointer () noexcept override;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        auto operator = (
                __ElementType * pointer
        ) noexcept -> UniquePointer &;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        auto operator = (
                UniquePointer const & pointer
        ) noexcept -> UniquePointer & = delete;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        auto operator = (
                UniquePointer && pointer
        ) noexcept -> UniquePointer &;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard constexpr auto operator == (
                __ElementType const * pointer
        ) const noexcept -> bool;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard constexpr auto operator != (
                __ElementType const * pointer
        ) const noexcept -> bool;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard __CDS_cpplang_VirtualConstexpr auto operator == (
                Base const & pointer
        ) const noexcept -> bool;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard __CDS_cpplang_VirtualConstexpr auto operator != (
                Base const & pointer
        ) const noexcept -> bool;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard constexpr auto operator == (
                UniquePointer const & pointer
        ) const noexcept -> bool;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard constexpr auto operator != (
                UniquePointer const & pointer
        ) const noexcept -> bool;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard constexpr auto operator == (
                std :: nullptr_t pointer
        ) const noexcept -> bool;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard constexpr auto operator != (
                std :: nullptr_t pointer
        ) const noexcept -> bool;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto valueAt () const noexcept (false) -> __ElementType & override;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto get () const noexcept -> __ElementType * override;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_cpplang_ConstexprOverride auto exchange (
                __ElementType * pointer
        ) noexcept -> __ElementType * override;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_cpplang_ConstexprOverride auto release () noexcept -> __ElementType * override;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        auto reset () noexcept -> void override;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        auto reset (
                __ElementType * pointer
        ) noexcept -> void override;
    };

} /* namespace cds */

#include "pointer/impl/UniquePointer.hpp"

#endif /* __CDS_UNIQUE_POINTER_HPP__ */
