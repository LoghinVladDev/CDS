/*
 * Created by loghin on 30/11/22.
 */

#ifndef __CDS_OUT_OF_BOUNDS_EXCEPTION_HPP__ /* NOLINT(llvm-header-guard) */
#define __CDS_OUT_OF_BOUNDS_EXCEPTION_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

#include <CDS/exception/RuntimeException>

namespace cds {

    class OutOfBoundsException : public RuntimeException {

    public:
        OutOfBoundsException () noexcept;

    public:
        OutOfBoundsException (
                OutOfBoundsException const & exception
        ) noexcept;

    public:
        OutOfBoundsException (
                OutOfBoundsException && exception
        ) noexcept;

    public:
        explicit OutOfBoundsException (
                StringView message
        ) noexcept;

    public:
        explicit OutOfBoundsException (
                Index requested,
                Index capacity
        ) noexcept;

    public:
        ~OutOfBoundsException() noexcept override = default;
    };

} /* namespace cds */

#include "exception/impl/OutOfBoundsException.hpp"

__CDS_Meta_RegisterParseType(OutOfBoundsException)

#endif /* __CDS_OUT_OF_BOUNDS_EXCEPTION_HPP__ */
