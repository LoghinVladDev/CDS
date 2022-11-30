/*
 * Created by loghin on 30/11/22.
 */

#ifndef __CDS_EXCEPTION_HPP__ /* NOLINT(llvm-header-guard) */
#define __CDS_EXCEPTION_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

#include <CDS/String>

namespace cds {

    class Exception : public Object, public std :: exception {

    private:
        String _message;

    private:
        __CDS_NoDiscard __CDS_cpplang_VirtualConstexpr auto what () const noexcept -> StringLiteral override;

    protected:
        Exception () noexcept;

    protected:
        Exception (
                Exception const & exception
        ) noexcept;

    protected:
        Exception (
                Exception && exception
        ) noexcept;

    public:
        Exception (
                std :: exception const & exception
        ) noexcept;

    protected:
        __CDS_Explicit Exception (
                StringView message
        ) noexcept;

    public:
        ~Exception () noexcept override = default;

    public:
        __CDS_NoDiscard auto toString () const noexcept -> String override;

    public:
        __CDS_NoDiscard auto hash () const noexcept -> Size override;

    public:
        __CDS_NoDiscard auto equals (
                Object const & object
        ) const noexcept -> bool override;

    public:
        __CDS_NoDiscard constexpr auto message () const noexcept -> String const & {

            return this->_message;
        }
    };

} /* namespace cds */

#include "exception/impl/Exception.hpp"

__CDS_Meta_RegisterParseType(Exception)

#endif /* __CDS_EXCEPTION_HPP__ */
