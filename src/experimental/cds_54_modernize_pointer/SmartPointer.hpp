/*
 * Created by loghin on 26.01.2021.
 */

#ifndef __CDS_SMART_POINTER_HPP__ /* NOLINT(llvm-header-guard) */
#define __CDS_SMART_POINTER_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

#include <CDS/Object>

namespace cds {

    template < typename __ElementType >
    class SmartPointer : public Object {

    public:
        using AddressType           = Size;

    public:
        using ValueType             = __ElementType;

    public:
        using ValueReferenceType    = __ElementType &;

    public:
        using PointerType           = __ElementType *;

    public:
        using ConstPointerType      = __ElementType const *;

    protected:
        __ElementType * _pObject { nullptr };

    protected:
        constexpr SmartPointer () noexcept = default;

    protected:
        constexpr SmartPointer (
                __ElementType * pObject
        ) noexcept;

    protected:
        constexpr SmartPointer (
                SmartPointer const & pointer
        ) noexcept;

    protected:
        constexpr SmartPointer (
                SmartPointer && pointer
        ) noexcept;

    public:
        __CDS_cpplang_ConstexprDestructor ~SmartPointer () noexcept override = default;

    public:
        __CDS_NoDiscard constexpr auto operator == (
                SmartPointer const & pointer
        ) const noexcept -> bool;

    public:
        __CDS_NoDiscard constexpr auto operator != (
                SmartPointer const & pointer
        ) const noexcept -> bool;

    public:
        __CDS_NoDiscard constexpr auto operator == (
                __ElementType const * pointer
        ) const noexcept -> bool;

    public:
        __CDS_NoDiscard constexpr auto operator != (
                __ElementType const * pointer
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
        __CDS_NoDiscard constexpr auto isNull () const noexcept -> bool;

    public:
        __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto operator * () const noexcept (false) -> __ElementType &;

    public:
        __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto valueAt () const noexcept (false) -> __ElementType &;

    public:
        __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto operator -> () const noexcept (false) -> __ElementType *;

    public:
        __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto get () const noexcept (false) -> __ElementType *;

    public:
        __CDS_NoDiscard constexpr explicit operator bool () const noexcept;

    public:
        __CDS_NoDiscard constexpr explicit operator __ElementType * () const noexcept;

    public:
        __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction auto exchange (
                __ElementType * pointer
        ) noexcept -> __ElementType *;

    public:
        __CDS_cpplang_VirtualConstexpr virtual auto release () noexcept -> __ElementType *;

    public:
        virtual auto reset (
                __ElementType pointer
        ) noexcept -> void;

    public:
        virtual auto reset () noexcept -> void;

    public:
        __CDS_NoDiscard auto equals (
                Object const & object
        ) const noexcept -> bool override;

    public:
        __CDS_NoDiscard auto toString () const noexcept -> String override;

    public:
        __CDS_NoDiscard auto hash () const noexcept -> Size override;
    };

}

#endif /* __CDS_SMART_POINTER_HPP__ */
