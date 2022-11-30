/*
 * Created by loghin on 30/11/22.
 */

#ifndef __CDS_FORMAT_EXCEPTION_HPP__ /* NOLINT(llvm-header-guard) */
#define __CDS_FORMAT_EXCEPTION_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

#include <CDS/exception/IllegalArgumentException>

namespace cds {

    class FormatException : public IllegalArgumentException {

    public:
        FormatException () noexcept;

    public:
        FormatException (
                FormatException const & exception
        ) noexcept;

    public:
        FormatException (
                FormatException && exception
        ) noexcept;

    public:
        explicit FormatException (
                StringView message
        ) noexcept;

    public:
        ~FormatException() noexcept override = default;
    };

} /* namespace cds */

#include "exception/impl/FormatException.hpp"

__CDS_Meta_RegisterParseType(FormatException)

#endif /* __CDS_FORMAT_EXCEPTION_HPP__ */
