/*
 * Created by loghin on 30/11/22.
 */

#ifndef __CDS_RUNTIME_EXCEPTION_HPP__ /* NOLINT(llvm-header-guard) */
#define __CDS_RUNTIME_EXCEPTION_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

#include <CDS/exception/Exception>

namespace cds {

    class RuntimeException : public Exception {

    public:
        RuntimeException () noexcept;

    public:
        RuntimeException (
                RuntimeException const & exception
        ) noexcept;

    public:
        RuntimeException (
                RuntimeException && exception
        ) noexcept;

    public:
        explicit RuntimeException (
                StringView message
        ) noexcept;

    public:
        ~RuntimeException() noexcept override = default;
    };

} /* namespace cds */

#include "exception/impl/RuntimeException.hpp"

__CDS_Meta_RegisterParseType(RuntimeException)

#endif /* __CDS_RUNTIME_EXCEPTION_HPP__ */
