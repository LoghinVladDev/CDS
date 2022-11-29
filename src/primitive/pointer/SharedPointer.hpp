/* NOLINT(llvm-header-guard)
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
        __CDS_Implicit SharedPointer (  /* NOLINT(*-explicit-*, clion-misra-cpp2008-12-1-3) */
                std :: nullptr_t pointer
        ) noexcept;

    public:                             /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_Implicit SharedPointer (  /* NOLINT(*-explicit-*, clion-misra-cpp2008-12-1-3) */
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

    public:
        __CDS_NoDiscard auto ownerCount () const noexcept -> Size;

    public:
        __CDS_NoDiscard auto observerCount () const noexcept -> Size;

    public:
        __CDS_NoDiscard auto observe () const noexcept -> WeakPointer < __ElementType, __Deleter >;
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
        __CDS_Implicit SharedPointer (  /* NOLINT(*-explicit-*, clion-misra-cpp2008-12-1-3) */
                std :: nullptr_t pointer
        ) noexcept;

    public:                             /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_Implicit SharedPointer (  /* NOLINT(*-explicit-*, clion-misra-cpp2008-12-1-3) */
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

    public:
        __CDS_NoDiscard auto ownerCount () const noexcept -> Size;

    public:
        __CDS_NoDiscard auto observerCount () const noexcept -> Size;

    public:
        __CDS_NoDiscard auto observe () const noexcept -> WeakPointer < __ElementType [], __Deleter >;
    };


    template < typename __ElementType, typename ... __ConstructionArguments >   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    __CDS_NoDiscard auto makeShared (
            __ConstructionArguments && ... arguments
    ) noexcept (
            noexcept ( __ElementType ( std :: forward < __ConstructionArguments > ( arguments ) ... ) )
    ) -> cds :: meta :: EnableIf <
            ! cds :: meta :: isArray < __ElementType > (),                      /* NOLINT(clion-misra-cpp2008-5-3-1) */
            SharedPointer < __ElementType, __hidden :: __impl :: __DefaultSmartPointerDeleter < __ElementType > >
    >;


    template <
            typename __ElementType, /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            cds :: meta :: EnableIf <
                    cds :: meta :: isUnboundedArray < __ElementType > ()
            > = 0
    > __CDS_NoDiscard auto makeShared (
            Size size
    ) noexcept -> SharedPointer < __ElementType, __hidden :: __impl :: __DefaultSmartPointerDeleter < __ElementType > >;


    template < typename __ElementType, typename ... __ConstructionArguments >   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    __CDS_NoDiscard auto makeShared () noexcept -> cds :: meta :: EnableIf < cds :: meta :: isBoundedArray < __ElementType > () > = delete;


    template <
            typename __ElementType,                                 /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            cds :: meta :: EnableIf <
                    ! cds :: meta :: isArray < __ElementType > ()   /* NOLINT(clion-misra-cpp2008-5-3-1) */
            > = 0
    > __CDS_NoDiscard auto makeSharedDefault () noexcept ( noexcept ( __ElementType () ) ) -> SharedPointer < __ElementType, __hidden :: __impl :: __DefaultSmartPointerDeleter < __ElementType > >;


    template <
            typename __ElementType, /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            cds :: meta :: EnableIf <
                    cds :: meta :: isUnboundedArray < __ElementType > ()
            > = 0
    > __CDS_NoDiscard auto makeSharedDefault (
            Size size
    ) noexcept -> SharedPointer < __ElementType, __hidden :: __impl :: __DefaultSmartPointerDeleter < __ElementType > >;


    template < typename __ElementType, typename ... __ConstructionArguments >   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    __CDS_NoDiscard auto makeSharedDefault (
            __ConstructionArguments && ...
    ) noexcept -> cds :: meta :: EnableIf < cds :: meta :: isBoundedArray < __ElementType > () > = delete;

} /* namespace cds */

#include "pointer/impl/SharedPointer.hpp"
#include "pointer/impl/SharedPointerCTAD.hpp"
#include "pointer/impl/SharedPointerControlBlock.hpp"
#include "pointer/impl/WeakSharedPointer.hpp"

#endif /* __CDS_SHARED_POINTER_HPP__ */
