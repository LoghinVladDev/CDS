/*
 * Created by loghin on 30/11/22.
 */

#ifndef __CDS_UNSUPPORTED_OPERATION_EXCEPTION_HPP__ /* NOLINT(llvm-header-guard) */
#define __CDS_UNSUPPORTED_OPERATION_EXCEPTION_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

#include <CDS/exception/Exception>

namespace cds {

    class UnsupportedOperationException : public Exception {

    public:
        UnsupportedOperationException () noexcept;

    public:
        UnsupportedOperationException (
                UnsupportedOperationException const & exception
        ) noexcept;

    public:
        UnsupportedOperationException (
                UnsupportedOperationException && exception
        ) noexcept;

    public:
        explicit UnsupportedOperationException (
                StringView message
        ) noexcept;

    public:
        ~UnsupportedOperationException() noexcept override = default;
    };

} /* namespace cds */

#include "exception/impl/UnsupportedOperationException.hpp"

__CDS_Meta_RegisterParseType(UnsupportedOperationException)

#endif /* __CDS_UNSUPPORTED_OPERATION_EXCEPTION_HPP__ */
