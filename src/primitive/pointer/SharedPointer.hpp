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

    private:    /* NOLINT(readability-redundant-access-specifiers) */
        friend class WeakPointer < __ElementType, __Deleter >;

    private:    /* NOLINT(readability-redundant-access-specifiers) */
        using Base = SmartPointer < __ElementType >;

    private:    /* NOLINT(readability-redundant-access-specifiers) */
        using ControlBlock = __hidden :: __impl :: __SharedPointerControlBlock < __ElementType >;

    private:    /* NOLINT(readability-redundant-access-specifiers) */
        ControlBlock * _pControl { nullptr };

    public: /* NOLINT(readability-redundant-access-specifiers) */
        SharedPointer () noexcept;

    public:                             /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_Implicit SharedPointer (  /* NOLINT(*-explicit-*) */
                std :: nullptr_t pointer
        ) noexcept;

    public:                             /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_Implicit SharedPointer (  /* NOLINT(*-explicit-*) */
                __ElementType * pointer
        ) noexcept;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        SharedPointer (
                SharedPointer const & pointer
        ) noexcept;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        constexpr SharedPointer (
                SharedPointer && pointer
        ) noexcept;

    public:                             /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_Explicit SharedPointer (  /* NOLINT(*-explicit-*) */
                WeakPointer < __ElementType, __Deleter > const & pointer
        ) noexcept;

    public:                             /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_Explicit SharedPointer (  /* NOLINT(*-explicit-*) */
                WeakPointer < __ElementType, __Deleter > && pointer
        ) noexcept;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        ~SharedPointer () noexcept override;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        auto operator = (
                std :: nullptr_t pointer
        ) noexcept -> SharedPointer &;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        auto operator = (
                __ElementType * pointer
        ) noexcept -> SharedPointer &;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        auto operator = (
                SharedPointer const & pointer
        ) noexcept -> SharedPointer &;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        auto operator = (
                SharedPointer && pointer
        ) noexcept -> SharedPointer &;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        auto operator = (
                WeakPointer < __ElementType, __Deleter > const & pointer
        ) noexcept -> SharedPointer &;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        auto operator = (
                WeakPointer < __ElementType, __Deleter > && pointer
        ) noexcept -> SharedPointer &;

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
                SharedPointer const & pointer
        ) const noexcept -> bool;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard constexpr auto operator != (
                SharedPointer const & pointer
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
        auto exchange (
                __ElementType * pointer
        ) noexcept -> __ElementType * override;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        auto exchange (
                std :: nullptr_t pointer
        ) noexcept -> __ElementType *;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        auto release () noexcept -> __ElementType * override;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        auto reset () noexcept -> void override;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        auto reset (
                std :: nullptr_t pointer
        ) noexcept -> void;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        auto reset (
                __ElementType * pointer
        ) noexcept -> void override;
    };


    template < typename __ElementType, typename __Deleter >                                             /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    class SharedPointer < __ElementType [], __Deleter > : public SmartPointer < __ElementType [] > {    /* NOLINT(*-avoid-c-arrays) */

    private:                                                        /* NOLINT(readability-redundant-access-specifiers) */
        friend class WeakPointer < __ElementType [], __Deleter >;   /* NOLINT(*-avoid-c-arrays) */

    private:    /* NOLINT(readability-redundant-access-specifiers) */
        using Base = SmartPointer < __ElementType >;

    private:    /* NOLINT(readability-redundant-access-specifiers) */
        using ControlBlock = __hidden :: __impl :: __SharedPointerControlBlock < __ElementType >;

    private:    /* NOLINT(readability-redundant-access-specifiers) */
        ControlBlock * _pControl { nullptr };

    public: /* NOLINT(readability-redundant-access-specifiers) */
        SharedPointer () noexcept;

    public:                             /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_Implicit SharedPointer (  /* NOLINT(*-explicit-*) */
                std :: nullptr_t pointer
        ) noexcept;

    public:                             /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_Implicit SharedPointer (  /* NOLINT(*-explicit-*) */
                __ElementType * pointer
        ) noexcept;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        SharedPointer (
                SharedPointer const & pointer
        ) noexcept;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        constexpr SharedPointer (
                SharedPointer && pointer
        ) noexcept;

    public:                                                                 /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_Implicit SharedPointer (                                      /* NOLINT(*-explicit-*) */
                WeakPointer < __ElementType [], __Deleter > const & pointer /* NOLINT(*-avoid-c-arrays) */
        ) noexcept;

    public:                                                             /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_Implicit SharedPointer (                                  /* NOLINT(*-explicit-*) */
                WeakPointer < __ElementType [], __Deleter > && pointer  /* NOLINT(*-avoid-c-arrays) */
        ) noexcept;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        ~SharedPointer () noexcept override;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        auto operator = (
                std :: nullptr_t pointer
        ) noexcept -> SharedPointer &;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        auto operator = (
                __ElementType * pointer
        ) noexcept -> SharedPointer &;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        auto operator = (
                SharedPointer const & pointer
        ) noexcept -> SharedPointer &;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        auto operator = (
                SharedPointer && pointer
        ) noexcept -> SharedPointer &;

    public:                                                                 /* NOLINT(readability-redundant-access-specifiers) */
        auto operator = (
                WeakPointer < __ElementType [], __Deleter > const & pointer /* NOLINT(*-avoid-c-arrays) */
        ) noexcept -> SharedPointer &;

    public:                                                             /* NOLINT(readability-redundant-access-specifiers) */
        auto operator = (
                WeakPointer < __ElementType [], __Deleter > && pointer  /* NOLINT(*-avoid-c-arrays) */
        ) noexcept -> SharedPointer &;

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
                SharedPointer const & pointer
        ) const noexcept -> bool;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard constexpr auto operator != (
                SharedPointer const & pointer
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
        auto exchange (
                std :: nullptr_t pointer
        ) noexcept -> __ElementType *;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        auto exchange (
                __ElementType * pointer
        ) noexcept -> __ElementType * override;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        auto release () noexcept -> __ElementType * override;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        auto reset () noexcept -> void override;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        auto reset (
                std :: nullptr_t pointer
        ) noexcept -> void;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        auto reset (
                __ElementType * pointer
        ) noexcept -> void override;
    };

} /* namespace cds */

#include "pointer/impl/SharedPointer.hpp"
#include "pointer/impl/SharedPointerControlBlock.hpp"
#include "pointer/impl/WeakSharedPointer.hpp"

#endif /* __CDS_SHARED_POINTER_HPP__ */
