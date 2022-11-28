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
    class UniquePointer < __ElementType [], __Deleter > : public SmartPointer < __ElementType > {

    private:
        using Base = SmartPointer < __ElementType >;

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
        __CDS_cpplang_NonConstConstexprMemberFunction auto exchange (
                __ElementType * pointer
        ) noexcept -> __ElementType * override;

    public:
        __CDS_cpplang_NonConstConstexprMemberFunction auto release () noexcept -> __ElementType * override;

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

#include "pointer/impl/UniquePointer.hpp"

#endif /* __CDS_UNIQUE_POINTER_HPP__ */
