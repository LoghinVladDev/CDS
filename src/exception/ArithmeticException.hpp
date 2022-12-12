/*
 * Created by loghin on 30/11/22.
 */

#ifndef __CDS_ARITHMETIC_EXCEPTION_HPP__ /* NOLINT(llvm-header-guard) */
#define __CDS_ARITHMETIC_EXCEPTION_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

#include <CDS/exception/RuntimeException>

namespace cds {

    class ArithmeticException : public RuntimeException {

    public:
        ArithmeticException () noexcept;

    public:
        ArithmeticException (
                ArithmeticException const & exception
        ) noexcept;

    public:
        ArithmeticException (
                ArithmeticException && exception
        ) noexcept;

    public:
        explicit ArithmeticException (
                StringView message
        ) noexcept;

    public:
        ~ArithmeticException() noexcept override = default;
    };

} /* namespace cds */

#include "exception/impl/ArithmeticException.hpp"

__CDS_Meta_RegisterParseType(ArithmeticException)

#endif /* __CDS_ARITHMETIC_EXCEPTION_HPP__ */
