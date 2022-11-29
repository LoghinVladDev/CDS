/*
 * Created by loghin on 26.01.2021.
 */

#ifndef __CDS_SMART_POINTER_HPP__ /* NOLINT(llvm-header-guard) */
#define __CDS_SMART_POINTER_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

#include <CDS/Object>

namespace cds {

    template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    class SmartPointer : public Object {

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using AddressType           = Size;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using ValueType             = __ElementType;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using ValueReferenceType    = __ElementType &;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using PointerType           = __ElementType *;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using ConstPointerType      = __ElementType const *;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        constexpr SmartPointer () noexcept = default;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        constexpr SmartPointer (
                SmartPointer const & pointer
        ) noexcept = default;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        constexpr SmartPointer (
                SmartPointer && pointer
        ) noexcept = default;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_cpplang_ConstexprDestructor ~SmartPointer () noexcept override = default;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        auto operator = (
                SmartPointer const & pointer
        ) noexcept -> SmartPointer & = default;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        auto operator = (
                SmartPointer && pointer
        ) noexcept -> SmartPointer & = default;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard __CDS_cpplang_VirtualConstexpr auto isNull () const noexcept -> bool;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard __CDS_cpplang_VirtualConstexpr auto operator * () const noexcept (false) -> __ElementType &;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard __CDS_cpplang_VirtualConstexpr virtual auto valueAt () const noexcept (false) -> __ElementType & = 0;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard __CDS_cpplang_VirtualConstexpr auto operator -> () const noexcept (false) -> __ElementType *;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard __CDS_cpplang_VirtualConstexpr virtual auto get () const noexcept -> __ElementType * = 0;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard __CDS_cpplang_VirtualConstexpr __CDS_Implicit operator bool () const noexcept; /* NOLINT(*-explicit-*) */

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard __CDS_cpplang_VirtualConstexpr explicit operator __ElementType * () const noexcept;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard virtual auto exchange (
                __ElementType * pointer
        ) noexcept -> __ElementType * = 0;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard virtual auto release () noexcept -> __ElementType * = 0;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        virtual auto reset (
                __ElementType * pointer
        ) noexcept -> void = 0;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        virtual auto reset () noexcept -> void = 0;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard auto equals (
                Object const & object
        ) const noexcept -> bool override;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard auto toString () const noexcept -> String override;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto hash () const noexcept -> Size override;
    };


    template < typename __ElementType >                         /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    class SmartPointer < __ElementType [] > : public Object {   /* NOLINT(*-avoid-c-arrays) */

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using AddressType           = Size;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using ValueType             = __ElementType;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using ValueReferenceType    = __ElementType &;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using PointerType           = __ElementType *;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using ConstPointerType      = __ElementType const *;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        constexpr SmartPointer () noexcept = default;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        constexpr SmartPointer (
                SmartPointer const & pointer
        ) noexcept = default;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        constexpr SmartPointer (
                SmartPointer && pointer
        ) noexcept = default;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_cpplang_ConstexprDestructor ~SmartPointer () noexcept override = default;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        auto operator = (
                SmartPointer const & pointer
        ) noexcept -> SmartPointer & = default;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        auto operator = (
                SmartPointer && pointer
        ) noexcept -> SmartPointer & = default;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard __CDS_cpplang_VirtualConstexpr auto isNull () const noexcept -> bool;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard __CDS_cpplang_VirtualConstexpr auto operator * () const noexcept (false) -> __ElementType &;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard virtual auto valueAt () const noexcept (false) -> __ElementType & = 0;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard __CDS_cpplang_VirtualConstexpr auto operator -> () const noexcept (false) -> __ElementType *;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard virtual auto get () const noexcept -> __ElementType * = 0;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard __CDS_cpplang_VirtualConstexpr __CDS_Implicit operator bool () const noexcept; /* NOLINT(*-explicit-*) */

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard __CDS_cpplang_VirtualConstexpr explicit operator __ElementType * () const noexcept;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard virtual auto exchange (
                __ElementType * pointer
        ) noexcept -> __ElementType * = 0;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard virtual auto release () noexcept -> __ElementType * = 0;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        virtual auto reset (
                __ElementType * pointer
        ) noexcept -> void = 0;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        virtual auto reset () noexcept -> void = 0;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard auto equals (
                Object const & object
        ) const noexcept -> bool override;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard auto toString () const noexcept -> String override;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto hash () const noexcept -> Size override;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        template < typename __NumericType > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        __CDS_NoDiscard __CDS_cpplang_VirtualConstexpr auto operator [] (
                __NumericType index
        ) const noexcept -> __ElementType &;
    };

} /* namespace cds */

#include "pointer/impl/SmartPointer.hpp"

#endif /* __CDS_SMART_POINTER_HPP__ */
