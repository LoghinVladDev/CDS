/*
 * Created by loghin on 30/11/22.
 */

#ifndef __CDS_DIVIDE_BY_ZERO_EXCEPTION_HPP__ /* NOLINT(llvm-header-guard) */
#define __CDS_DIVIDE_BY_ZERO_EXCEPTION_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

#include <CDS/exception/ArithmeticException>

namespace cds {

    class DivideByZeroException : public ArithmeticException {

    public:
        DivideByZeroException () noexcept;

    public:
        DivideByZeroException (
                DivideByZeroException const & exception
        ) noexcept;

    public:
        DivideByZeroException (
                DivideByZeroException && exception
        ) noexcept;

    public:
        explicit DivideByZeroException (
                StringView message
        ) noexcept;

    public:
        ~DivideByZeroException() noexcept override = default;
    };

} /* namespace cds */

#include "exception/impl/DivideByZeroException.hpp"

__CDS_Meta_RegisterParseType(DivideByZeroException)

#endif /* __CDS_DIVIDE_BY_ZERO_EXCEPTION_HPP__ */
