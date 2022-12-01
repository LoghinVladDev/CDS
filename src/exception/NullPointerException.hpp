/*
 * Created by loghin on 30/11/22.
 */

#ifndef __CDS_NULL_POINTER_EXCEPTION_HPP__ /* NOLINT(llvm-header-guard) */
#define __CDS_NULL_POINTER_EXCEPTION_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

#include <CDS/exception/RuntimeException>

namespace cds {

    class NullPointerException : public RuntimeException {

    public:
        NullPointerException () noexcept;

    public:
        NullPointerException (
                NullPointerException const & exception
        ) noexcept;

    public:
        NullPointerException (
                NullPointerException && exception
        ) noexcept;

    public:
        explicit NullPointerException (
                StringView message
        ) noexcept;

    public:
        ~NullPointerException() noexcept override = default;
    };

} /* namespace cds */

#include "exception/impl/NullPointerException.hpp"

__CDS_Meta_RegisterParseType(NullPointerException)

#endif /* __CDS_NULL_POINTER_EXCEPTION_HPP__ */
