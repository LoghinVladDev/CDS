/*
 * Created by loghin on 30/11/22.
 */

#ifndef __CDS_TYPE_EXCEPTION_HPP__ /* NOLINT(llvm-header-guard) */
#define __CDS_TYPE_EXCEPTION_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

#include <CDS/exception/RuntimeException>

namespace cds {

    class TypeException : public RuntimeException {

    public:
        TypeException () noexcept;

    public:
        TypeException (
                TypeException const & exception
        ) noexcept;

    public:
        TypeException (
                TypeException && exception
        ) noexcept;

    public:
        explicit TypeException (
                StringView message
        ) noexcept;

    public:
        template < typename __FromType, typename __ToType > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        TypeException () noexcept;

    public:
        template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        TypeException () noexcept;

    public:
        ~TypeException() noexcept override = default;
    };

} /* namespace cds */

#include "exception/impl/TypeException.hpp"

__CDS_Meta_RegisterParseType(TypeException)

#endif /* __CDS_TYPE_EXCEPTION_HPP__ */
