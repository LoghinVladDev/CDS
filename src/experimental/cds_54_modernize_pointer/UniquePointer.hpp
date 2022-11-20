/*
 * Created by loghin on 26.01.2021.
 */

#ifndef __CDS_UNIQUE_POINTER_HPP__ /* NOLINT(llvm-header-guard) */
#define __CDS_UNIQUE_POINTER_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

#include <CDS/smartPointers/SmartPointer>

namespace cds {

    template < typename __ElementType, typename __Deleter >
    class UniquePointer : public SmartPointer < __ElementType > {

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
        UniquePointer (
                UniquePointer && pointer
        ) noexcept;

    public:
        ~UniquePointer () noexcept override;

    public:
        auto operator = (
                __ElementType * pointer
        ) noexcept -> UniquePointer &;

    public:
        auto operator = (
                UniquePointer const & pointer
        ) noexcept -> UniquePointer &;

    public:
        auto operator = (
                UniquePointer && pointer
        ) noexcept -> UniquePointer &;

    public:
        auto exchange (
                __ElementType * pointer
        ) noexcept -> __ElementType * override;

    public:
        auto release () noexcept -> __ElementType * override;

    public:
        auto reset () noexcept -> void override;

    public:
        auto reset (
                __ElementType * pointer
        ) noexcept -> void override;
    };

} /* namespace cds */

#endif /* __CDS_UNIQUE_POINTER_HPP__ */
