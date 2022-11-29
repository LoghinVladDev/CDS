/* NOLINT(llvm-header-guard)
 * Created by loghin on 28/11/22.
 */

#ifndef __CDS_WEAK_POINTER_HPP__ /* NOLINT(llvm-header-guard) */
#define __CDS_WEAK_POINTER_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

#include <CDS/threading/Atomic>

#include "pointer/SharedPointerControlBlock.hpp"

namespace cds {

    template < typename __ElementType, typename __Deleter > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    class WeakPointer : public cds :: Object {

    private:    /* NOLINT(readability-redundant-access-specifiers) */
        friend class SharedPointer < __ElementType, __Deleter >;

    private:    /* NOLINT(readability-redundant-access-specifiers) */
        using ControlBlock = __hidden :: __impl :: __SharedPointerControlBlock < __ElementType >;

    private:    /* NOLINT(readability-redundant-access-specifiers) */
        ControlBlock * _pControl { nullptr };

    public: /* NOLINT(readability-redundant-access-specifiers) */
        constexpr WeakPointer () noexcept = default;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        WeakPointer (
                WeakPointer const & pointer
        ) noexcept;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        constexpr WeakPointer (
                WeakPointer && pointer
        ) noexcept;

    public:                             /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_Implicit WeakPointer (    /* NOLINT(*-explicit-*) */
                SharedPointer < __ElementType, __Deleter > const & pointer
        ) noexcept;

    public:                             /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_Implicit WeakPointer (    /* NOLINT(*-explicit-*) */
                SharedPointer < __ElementType, __Deleter > && pointer
        ) noexcept;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        ~WeakPointer () noexcept override;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        auto operator = (
                std :: nullptr_t pointer
        ) noexcept -> WeakPointer &;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        auto operator = (
                WeakPointer const & pointer
        ) noexcept -> WeakPointer &;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_cpplang_NonConstConstexprMemberFunction auto operator = (
                WeakPointer && pointer
        ) noexcept -> WeakPointer &;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        auto operator = (
                SharedPointer < __ElementType, __Deleter > const & pointer
        ) noexcept -> WeakPointer &;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        auto operator = (
                SharedPointer < __ElementType, __Deleter > && pointer
        ) noexcept -> WeakPointer &;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard constexpr auto operator == (
                WeakPointer const & pointer
        ) const noexcept -> bool;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard constexpr auto operator != (
                WeakPointer const & pointer
        ) const noexcept -> bool;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        auto reset () noexcept -> void;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        auto reset (
                SharedPointer < __ElementType, __Deleter > const & pointer
        ) noexcept -> void;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        auto reset (
                SharedPointer < __ElementType, __Deleter > && pointer
        ) noexcept -> void;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        auto reset (
                WeakPointer const & pointer
        ) noexcept -> void;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        auto reset (
                WeakPointer && pointer
        ) noexcept -> void;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard auto expired () const noexcept -> bool;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard auto acquire () const noexcept -> SharedPointer < __ElementType, __Deleter >;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard auto toString () const noexcept -> String override;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard auto equals (
                Object const & object
        ) const noexcept -> bool override;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard auto hash () const noexcept -> Size override;
    };


    template < typename __ElementType, typename __Deleter >                     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    class WeakPointer < __ElementType [], __Deleter > : public cds :: Object {  /* NOLINT(*-avoid-c-arrays) */

    private:                                                        /* NOLINT(readability-redundant-access-specifiers) */
        friend class SharedPointer < __ElementType [], __Deleter >; /* NOLINT(*-avoid-c-arrays) */

    private:    /* NOLINT(readability-redundant-access-specifiers) */
        using ControlBlock = __hidden :: __impl :: __SharedPointerControlBlock < __ElementType >;

    private:    /* NOLINT(readability-redundant-access-specifiers) */
        ControlBlock * _pControl { nullptr };

    public: /* NOLINT(readability-redundant-access-specifiers) */
        constexpr WeakPointer () noexcept = default;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        WeakPointer (
                WeakPointer const & pointer
        ) noexcept;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        constexpr WeakPointer (
                WeakPointer && pointer
        ) noexcept;

    public:                                                                     /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_Implicit WeakPointer (                                            /* NOLINT(*-explicit-*) */
                SharedPointer < __ElementType [], __Deleter > const & pointer   /* NOLINT(*-avoid-c-arrays) */
        ) noexcept;

    public:                                                                 /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_Implicit WeakPointer (                                        /* NOLINT(*-explicit-*) */
                SharedPointer < __ElementType [], __Deleter > && pointer    /* NOLINT(*-avoid-c-arrays) */
        ) noexcept;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        ~WeakPointer () noexcept override;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        auto operator = (
                std :: nullptr_t pointer
        ) noexcept -> WeakPointer &;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        auto operator = (
                WeakPointer const & pointer
        ) noexcept -> WeakPointer &;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_cpplang_NonConstConstexprMemberFunction auto operator = (
                WeakPointer && pointer
        ) noexcept -> WeakPointer &;

    public:                                                                     /* NOLINT(readability-redundant-access-specifiers) */
        auto operator = (
                SharedPointer < __ElementType [], __Deleter > const & pointer   /* NOLINT(*-avoid-c-arrays) */
        ) noexcept -> WeakPointer &;

    public:                                                                 /* NOLINT(readability-redundant-access-specifiers) */
        auto operator = (
                SharedPointer < __ElementType [], __Deleter > && pointer    /* NOLINT(*-avoid-c-arrays) */
        ) noexcept -> WeakPointer &;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard constexpr auto operator == (
                WeakPointer const & pointer
        ) const noexcept -> bool;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard constexpr auto operator != (
                WeakPointer const & pointer
        ) const noexcept -> bool;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        auto reset () noexcept -> void;

    public:                                                                     /* NOLINT(readability-redundant-access-specifiers) */
        auto reset (
                SharedPointer < __ElementType [], __Deleter > const & pointer   /* NOLINT(*-avoid-c-arrays) */
        ) noexcept -> void;

    public:                                                                 /* NOLINT(readability-redundant-access-specifiers) */
        auto reset (
                SharedPointer < __ElementType [], __Deleter > && pointer    /* NOLINT(*-avoid-c-arrays) */
        ) noexcept -> void;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        auto reset (
                WeakPointer const & pointer
        ) noexcept -> void;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        auto reset (
                WeakPointer && pointer
        ) noexcept -> void;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard auto expired () const noexcept -> bool;

    public:                                                                                                 /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard auto acquire () const noexcept -> SharedPointer < __ElementType [], __Deleter >;    /* NOLINT(*-avoid-c-arrays) */

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard auto toString () const noexcept -> String override;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard auto equals (
                Object const & object
        ) const noexcept -> bool override;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard auto hash () const noexcept -> Size override;
    };

} /* namespace cds */

#include "pointer/impl/SharedPointerControlBlock.hpp"
#include "pointer/impl/WeakPointer.hpp"
#include "pointer/impl/WeakSharedPointer.hpp"

#endif /* __CDS_WEAK_POINTER_HPP__ */
