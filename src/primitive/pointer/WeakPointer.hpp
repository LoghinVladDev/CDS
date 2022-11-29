/*
 * Created by loghin on 28/11/22.
 */

#ifndef __CDS_WEAK_POINTER_HPP__ /* NOLINT(llvm-header-guard) */
#define __CDS_WEAK_POINTER_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

#include <CDS/threading/Atomic>

#include "pointer/SharedPointerControlBlock.hpp"

namespace cds {

    template < typename __ElementType, typename __Deleter > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    class WeakPointer : public cds :: Object {

    private:
        friend class SharedPointer < __ElementType, __Deleter >;

    private:
        using ControlBlock = __hidden :: __impl :: __SharedPointerControlBlock < __ElementType >;

    private:
        ControlBlock * _pControl { nullptr };

    public:
        constexpr WeakPointer () noexcept = default;

    public:
        WeakPointer (
                WeakPointer const & pointer
        ) noexcept;

    public:
        constexpr WeakPointer (
                WeakPointer && pointer
        ) noexcept;

    public:
        WeakPointer (
                SharedPointer < __ElementType, __Deleter > const & pointer
        ) noexcept;

    public:
        WeakPointer (
                SharedPointer < __ElementType, __Deleter > && pointer
        ) noexcept;

    public:
        ~WeakPointer () noexcept override;

    public:
        auto operator = (
                std :: nullptr_t pointer
        ) noexcept -> WeakPointer &;

    public:
        auto operator = (
                WeakPointer const & pointer
        ) noexcept -> WeakPointer &;

    public:
        __CDS_cpplang_NonConstConstexprMemberFunction auto operator = (
                WeakPointer && pointer
        ) noexcept -> WeakPointer &;

    public:
        auto operator = (
                SharedPointer < __ElementType, __Deleter > const & pointer
        ) noexcept -> WeakPointer &;

    public:
        auto operator = (
                SharedPointer < __ElementType, __Deleter > && pointer
        ) noexcept -> WeakPointer &;

    public:
        __CDS_NoDiscard constexpr auto operator == (
                WeakPointer const & pointer
        ) const noexcept -> bool;

    public:
        __CDS_NoDiscard constexpr auto operator != (
                WeakPointer const & pointer
        ) const noexcept -> bool;

    public:
        auto reset () noexcept -> void;

    public:
        auto reset (
                SharedPointer < __ElementType, __Deleter > const & pointer
        ) noexcept -> void;

    public:
        auto reset (
                SharedPointer < __ElementType, __Deleter > && pointer
        ) noexcept -> void;

    public:
        auto reset (
                WeakPointer const & pointer
        ) noexcept -> void;

    public:
        auto reset (
                WeakPointer && pointer
        ) noexcept -> void;

    public:
        __CDS_NoDiscard auto expired () const noexcept -> bool;

    public:
        __CDS_NoDiscard auto acquire () const noexcept -> SharedPointer < __ElementType, __Deleter >;

    public:
        __CDS_NoDiscard auto toString () const noexcept -> String override;

    public:
        __CDS_NoDiscard auto equals (
                Object const & object
        ) const noexcept -> bool override;

    public:
        __CDS_NoDiscard auto hash () const noexcept -> Size override;
    };


    template < typename __ElementType, typename __Deleter > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    class WeakPointer < __ElementType [], __Deleter > : public cds :: Object {

    private:
        friend class SharedPointer < __ElementType [], __Deleter >;

    private:
        using ControlBlock = __hidden :: __impl :: __SharedPointerControlBlock < __ElementType >;

    private:
        ControlBlock * _pControl { nullptr };

    public:
        constexpr WeakPointer () noexcept = default;

    public:
        WeakPointer (
                WeakPointer const & pointer
        ) noexcept;

    public:
        constexpr WeakPointer (
                WeakPointer && pointer
        ) noexcept;

    public:
        WeakPointer (
                SharedPointer < __ElementType [], __Deleter > const & pointer
        ) noexcept;

    public:
        WeakPointer (
                SharedPointer < __ElementType [], __Deleter > && pointer
        ) noexcept;

    public:
        ~WeakPointer () noexcept override;

    public:
        auto operator = (
                std :: nullptr_t pointer
        ) noexcept -> WeakPointer &;

    public:
        auto operator = (
                WeakPointer const & pointer
        ) noexcept -> WeakPointer &;

    public:
        __CDS_cpplang_NonConstConstexprMemberFunction auto operator = (
                WeakPointer && pointer
        ) noexcept -> WeakPointer &;

    public:
        auto operator = (
                SharedPointer < __ElementType [], __Deleter > const & pointer
        ) noexcept -> WeakPointer &;

    public:
        auto operator = (
                SharedPointer < __ElementType [], __Deleter > && pointer
        ) noexcept -> WeakPointer &;

    public:
        __CDS_NoDiscard constexpr auto operator == (
                WeakPointer const & pointer
        ) const noexcept -> bool;

    public:
        __CDS_NoDiscard constexpr auto operator != (
                WeakPointer const & pointer
        ) const noexcept -> bool;

    public:
        auto reset () noexcept -> void;

    public:
        auto reset (
                SharedPointer < __ElementType [], __Deleter > const & pointer
        ) noexcept -> void;

    public:
        auto reset (
                SharedPointer < __ElementType [], __Deleter > && pointer
        ) noexcept -> void;

    public:
        auto reset (
                WeakPointer const & pointer
        ) noexcept -> void;

    public:
        auto reset (
                WeakPointer && pointer
        ) noexcept -> void;

    public:
        __CDS_NoDiscard auto expired () const noexcept -> bool;

    public:
        __CDS_NoDiscard auto acquire () const noexcept -> SharedPointer < __ElementType [], __Deleter >;

    public:
        __CDS_NoDiscard auto toString () const noexcept -> String override;

    public:
        __CDS_NoDiscard auto equals (
                Object const & object
        ) const noexcept -> bool override;

    public:
        __CDS_NoDiscard auto hash () const noexcept -> Size override;
    };

} /* namespace cds */

#include "pointer/impl/WeakPointer.hpp"
#include "pointer/impl/SharedPointerControlBlock.hpp"
#include "pointer/impl/WeakSharedPointer.hpp"

#endif /* __CDS_WEAK_POINTER_HPP__ */
