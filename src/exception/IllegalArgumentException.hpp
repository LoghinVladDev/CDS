/*
 * Created by loghin on 30/11/22.
 */

#ifndef __CDS_ILLEGAL_ARGUMENT_EXCEPTION_HPP__ /* NOLINT(llvm-header-guard) */
#define __CDS_ILLEGAL_ARGUMENT_EXCEPTION_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

#include <CDS/exception/RuntimeException>

namespace cds {

    class IllegalArgumentException : public RuntimeException {

    public:
        IllegalArgumentException () noexcept;

    public:
        IllegalArgumentException (
                IllegalArgumentException const & exception
        ) noexcept;

    public:
        IllegalArgumentException (
                IllegalArgumentException && exception
        ) noexcept;

    public:
        explicit IllegalArgumentException (
                StringView message
        ) noexcept;

    public:
        ~IllegalArgumentException() noexcept override = default;
    };

} /* namespace cds */

#include "exception/impl/IllegalArgumentException.hpp"

__CDS_Meta_RegisterParseType(IllegalArgumentException)

#endif /* __CDS_ILLEGAL_ARGUMENT_EXCEPTION_HPP__ */
